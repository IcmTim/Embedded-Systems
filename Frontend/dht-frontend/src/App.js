import { useEffect, useState } from "react";
import { getLatest, getHistory } from "./api";
import CurrentValues from "./components/CurrentValues";
import Chart from "./components/Chart";

function App() {
  const [latest, setLatest] = useState(null);
  const [history, setHistory] = useState([]);

  async function loadData() {
    try {
      const latestData = await getLatest();
      const historyData = await getHistory(50);

      setLatest({
        temperature: latestData.field1,
        humidity: latestData.field2,
        ts: latestData.created_at,
      });

      setHistory(
        historyData.feeds.map(f => ({
          ts: f.created_at,
          temperature: f.field1,
          humidity: f.field2,
        }))
      );
    } catch (e) {
      console.error("Error loading data:", e);
    }
  }

  useEffect(() => {
    loadData();
    const timer = setInterval(loadData, 15000);
    return () => clearInterval(timer);
  }, []);

  return (
    <div style={{ padding: 20 }}>
      <h1>Monitoring</h1>
      {latest && <CurrentValues {...latest} />}
      <Chart history={history} />
    </div>
  );
}

export default App;
