const CHANNEL_ID = "3098774";
const READ_KEY = "3091TKOY92OS03AF";

export async function getLatest() {
  const url = `https://api.thingspeak.com/channels/${CHANNEL_ID}/feeds/last.json?api_key=${READ_KEY}`;
  const res = await fetch(url);
  return res.json();
}

export async function getHistory(limit = 100) {
  const url = `https://api.thingspeak.com/channels/${CHANNEL_ID}/feeds.json?api_key=${READ_KEY}&results=${limit}`;
  const res = await fetch(url);
  return res.json();
}
