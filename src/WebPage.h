#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <Arduino.h>

const char htmlPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>ESP32 Gyro App</title>
    <style>
        :root {
            --bg-top: #10233a;
            --bg-bottom: #05101c;
            --surface: rgba(14, 32, 51, 0.9);
            --surface-border: rgba(98, 146, 186, 0.3);
            --text-main: #ecf4ff;
            --text-muted: #9db4cb;
            --custom-color: #22c55e;
            --imu-color: #f59e0b;
        }

        * { box-sizing: border-box; }

        body {
            margin: 0;
            font-family: "Segoe UI", Tahoma, sans-serif;
            color: var(--text-main);
            background: radial-gradient(circle at 15% 15%, #1d436b 0%, transparent 45%),
                        linear-gradient(160deg, var(--bg-top), var(--bg-bottom));
            min-height: 100vh;
        }

        .page {
            width: min(1200px, 96vw);
            margin: 22px auto;
            display: grid;
            grid-template-columns: 1fr;
            gap: 16px;
        }

        .panel {
            background: var(--surface);
            border: 1px solid var(--surface-border);
            border-radius: 14px;
            box-shadow: 0 8px 24px rgba(0, 0, 0, 0.28);
            padding: 16px;
            backdrop-filter: blur(3px);
        }

        .metrics {
            display: grid;
            grid-template-columns: repeat(2, minmax(200px, 1fr));
            gap: 12px;
        }

        .metric-title {
            font-size: 0.85rem;
            color: var(--text-muted);
            text-transform: uppercase;
            letter-spacing: 0.05em;
            margin-bottom: 6px;
        }

        .metric-value {
            font-size: clamp(1.7rem, 3.2vw, 2.4rem);
            font-weight: 700;
            line-height: 1.1;
        }

        .custom { color: var(--custom-color); }
        .imu { color: var(--imu-color); }

        .unit {
            margin-top: 4px;
            color: var(--text-muted);
            font-size: 0.95rem;
        }

        .plot-head {
            display: flex;
            flex-wrap: wrap;
            align-items: center;
            justify-content: space-between;
            gap: 10px;
            margin-bottom: 12px;
        }

        .plot-title {
            margin: 0;
            font-size: 1.1rem;
            font-weight: 600;
        }

        label, select { font-size: 0.95rem; }

        select {
            border: 1px solid var(--surface-border);
            background: #0e2438;
            color: var(--text-main);
            border-radius: 8px;
            padding: 6px 10px;
        }

        .plot-wrap {
            width: 100%;
            height: min(52vh, 420px);
            border-radius: 12px;
            overflow: hidden;
            background: rgba(0, 0, 0, 0.2);
            border: 1px solid rgba(157, 180, 203, 0.2);
        }

        #plot {
            width: 100%;
            height: 100%;
            display: block;
        }

        details summary {
            cursor: pointer;
            font-weight: 600;
            color: #c4ddf4;
        }

        .debug-info {
            margin-top: 12px;
            display: grid;
            gap: 10px;
        }

        .encoder-read {
            font-size: 1.05rem;
        }

        #serial_log {
            margin: 0;
            background: #060d16;
            color: #d7e6f7;
            border-radius: 8px;
            border: 1px solid rgba(157, 180, 203, 0.25);
            padding: 10px;
            min-height: 150px;
            max-height: 280px;
            overflow: auto;
            font-size: 0.86rem;
            line-height: 1.35;
            text-align: left;
            white-space: pre-wrap;
        }

        @media (max-width: 760px) {
            .metrics { grid-template-columns: 1fr; }
        }
    </style>
</head>
<body>
    <div class="page">
        <div class="panel metrics">
            <div>
                <div class="metric-title">Custom Gyro</div>
                <div class="metric-value custom" id="omega_val">0.00</div>
                <div class="unit">rad / s</div>
            </div>
            <div>
                <div class="metric-title">MPU6500 (Z)</div>
                <div class="metric-value imu" id="imu_z">0.00</div>
                <div class="unit">rad / s</div>
            </div>
        </div>

        <div class="panel">
            <div class="plot-head">
                <h2 class="plot-title">Angular Velocity vs Time</h2>
                <div>
                    <label for="plot_mode">Display:</label>
                    <select id="plot_mode">
                        <option value="both">Both gyros</option>
                        <option value="custom">Custom only</option>
                        <option value="mpu">MPU6500 only</option>
                    </select>
                </div>
            </div>
            <div class="plot-wrap">
                <canvas id="plot"></canvas>
            </div>
        </div>

        <details class="panel">
            <summary>Debug</summary>
            <div class="debug-info">
                <div class="encoder-read">Encoder angle: <strong id="encoder_angle">0.000</strong> rad</div>
                <pre id="serial_log">Serial stream waiting...</pre>
            </div>
        </details>
    </div>

    <script>
        const maxSamples = 260;
        const dataPoints = [];
        const serialLines = [];
        let lastSeq = -1;

        const omegaEl = document.getElementById('omega_val');
        const imuEl = document.getElementById('imu_z');
        const angleEl = document.getElementById('encoder_angle');
        const serialEl = document.getElementById('serial_log');
        const modeEl = document.getElementById('plot_mode');

        const canvas = document.getElementById('plot');
        const ctx = canvas.getContext('2d');

        function resizeCanvas() {
            const rect = canvas.getBoundingClientRect();
            canvas.width = Math.max(320, Math.floor(rect.width));
            canvas.height = Math.max(180, Math.floor(rect.height));
            drawPlot();
        }

        function pushSerialLine(seq, omega, imuZ, angle) {
            serialLines.push(
                '[' + String(seq).padStart(5, '0') + '] '
                + 'omega=' + omega.toFixed(3)
                + ' imu_z=' + imuZ.toFixed(3)
                + ' encoder=' + angle.toFixed(3)
            );
            if (serialLines.length > 120) {
                serialLines.shift();
            }
            serialEl.textContent = serialLines.join('\n');
            serialEl.scrollTop = serialEl.scrollHeight;
        }

        function drawAxes(width, height, minY, maxY) {
            const left = 46;
            const right = width - 14;
            const top = 12;
            const bottom = height - 28;

            ctx.clearRect(0, 0, width, height);

            ctx.strokeStyle = 'rgba(157, 180, 203, 0.22)';
            ctx.lineWidth = 1;
            const hSteps = 5;
            const vSteps = 6;
            for (let i = 0; i <= hSteps; i++) {
                const y = top + (i * (bottom - top) / hSteps);
                ctx.beginPath();
                ctx.moveTo(left, y);
                ctx.lineTo(right, y);
                ctx.stroke();
            }
            for (let i = 0; i <= vSteps; i++) {
                const x = left + (i * (right - left) / vSteps);
                ctx.beginPath();
                ctx.moveTo(x, top);
                ctx.lineTo(x, bottom);
                ctx.stroke();
            }

            ctx.fillStyle = 'rgba(220, 235, 250, 0.8)';
            ctx.font = '12px Segoe UI';
            ctx.fillText(maxY.toFixed(2), 6, top + 8);
            ctx.fillText(minY.toFixed(2), 6, bottom + 4);
            ctx.fillText('time', right - 28, height - 8);
            ctx.fillText('rad/s', 6, height / 2);

            return { left, right, top, bottom };
        }

        function drawSeries(points, color, axes, minY, maxY, key) {
            if (points.length < 2) {
                return;
            }
            const ySpan = Math.max(0.001, maxY - minY);
            ctx.beginPath();
            points.forEach((point, idx) => {
                const x = axes.left + (idx * (axes.right - axes.left) / (points.length - 1));
                const normalized = (point[key] - minY) / ySpan;
                const y = axes.bottom - normalized * (axes.bottom - axes.top);
                if (idx === 0) {
                    ctx.moveTo(x, y);
                } else {
                    ctx.lineTo(x, y);
                }
            });
            ctx.strokeStyle = color;
            ctx.lineWidth = 2;
            ctx.stroke();
        }

        function drawPlot() {
            const mode = modeEl.value;
            const points = dataPoints;
            const width = canvas.width;
            const height = canvas.height;

            if (!points.length) {
                ctx.clearRect(0, 0, width, height);
                return;
            }

            let values = [];
            if (mode === 'both' || mode === 'custom') {
                values = values.concat(points.map(p => p.omega));
            }
            if (mode === 'both' || mode === 'mpu') {
                values = values.concat(points.map(p => p.imu));
            }

            const minY = Math.min.apply(null, values);
            const maxY = Math.max.apply(null, values);
            const margin = Math.max(0.2, (maxY - minY) * 0.15);
            const axes = drawAxes(width, height, minY - margin, maxY + margin);

            if (mode === 'both' || mode === 'custom') {
                drawSeries(points, getComputedStyle(document.documentElement).getPropertyValue('--custom-color').trim(), axes, minY - margin, maxY + margin, 'omega');
            }
            if (mode === 'both' || mode === 'mpu') {
                drawSeries(points, getComputedStyle(document.documentElement).getPropertyValue('--imu-color').trim(), axes, minY - margin, maxY + margin, 'imu');
            }
        }

        function updateData() {
            fetch('/data')
                .then(response => response.json())
                .then(json => {
                    const omega = Number(json.omega || 0);
                    const imuZ = Number(json.imu_z || 0);
                    const encoderAngle = Number(json.encoder_angle || 0);
                    const seq = Number(json.seq || 0);

                    omegaEl.textContent = omega.toFixed(2);
                    imuEl.textContent = imuZ.toFixed(2);
                    angleEl.textContent = encoderAngle.toFixed(3);

                    dataPoints.push({ omega: omega, imu: imuZ });
                    if (dataPoints.length > maxSamples) {
                        dataPoints.shift();
                    }

                    if (seq !== lastSeq) {
                        pushSerialLine(seq, omega, imuZ, encoderAngle);
                        lastSeq = seq;
                    }

                    drawPlot();
                })
                .catch(() => {
                    serialEl.textContent = 'Data fetch error. Check Wi-Fi/board connection.';
                });
        }

        window.addEventListener('resize', resizeCanvas);
        modeEl.addEventListener('change', drawPlot);

        resizeCanvas();
        updateData();
        setInterval(updateData, 120);
    </script>
</body>
</html>
)rawliteral";

#endif // WEBPAGE_H
