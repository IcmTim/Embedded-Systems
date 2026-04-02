const express = require("express");
const cors = require("cors");
const sqlite3 = require("sqlite3").verbose();

const app = express();
app.use(cors());
app.use(express.json());

const db = new sqlite3.Database("db.sqlite");

db.run(`
  CREATE TABLE IF NOT EXISTS sensor_data (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    temperature REAL,
    humidity REAL,
    ts DATETIME DEFAULT CURRENT_TIMESTAMP
  )
`);

app.post("/webhook", (req, res) => {
  const { temperature, humidity } = req.body;

  db.run(
    "INSERT INTO sensor_data (temperature, humidity) VALUES (?, ?)",
    [temperature, humidity],
    (err) => {
      if (err) return res.status(500).json({ error: err.message });

      res.json({ message: "saved" });
    }
  );
});

app.get("/history", (req, res) => {
  db.all("SELECT * FROM sensor_data ORDER BY ts DESC LIMIT 50", (err, rows) => {
    if (err) return res.status(500).json({ error: err.message });

    res.json(rows);
  });
});

const PORT = 3001;
app.listen(PORT, () => console.log(`Backend running on port ${PORT}`));
