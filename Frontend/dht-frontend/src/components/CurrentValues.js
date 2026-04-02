export default function CurrentValues({ temperature, humidity, ts }) {
  return (
    <div style={{ marginBottom: 20 }}>
      <h2>Current Values</h2>

      <p>
        Temperature:{" "}
        <strong>{temperature !== undefined ? temperature + " °C" : "—"}</strong>
      </p>

      <p>
        Humidity:{" "}
        <strong>{humidity !== undefined ? humidity + " %" : "—"}</strong>
      </p>

      {ts && (
        <p style={{ fontSize: 12, color: "#777" }}>
          Updated at: {new Date(ts).toLocaleString()}
        </p>
      )}
    </div>
  );
}
