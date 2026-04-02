import React from "react";
import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Tooltip,
  Legend
} from "chart.js";
import { Line } from "react-chartjs-2";

ChartJS.register(
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Tooltip,
  Legend
);

export default function Chart({ history }) {
  const labels = history.map(f => new Date(f.ts).toLocaleTimeString());
  const tempData = history.map(f => Number(f.temperature));
  const humData = history.map(f => Number(f.humidity));

  const data = {
    labels,
    datasets: [
      {
        label: "Temperature (°C)",
        data: tempData,
        borderColor: "red",
        backgroundColor: "rgba(255,0,0,0.2)",
        yAxisID: "y1",
      },
      {
        label: "Humidity (%)",
        data: humData,
        borderColor: "blue",
        backgroundColor: "rgba(0,0,255,0.2)",
        yAxisID: "y2",
      }
    ]
  };

  const options = {
    responsive: true,
    interaction: { mode: "index", intersect: false },
    stacked: false,
    scales: {
      y1: { type: "linear", position: "left", title: { display: true, text: "°C" } },
      y2: { type: "linear", position: "right", title: { display: true, text: "%" } },
    }
  };

  return <Line data={data} options={options} />;
}
