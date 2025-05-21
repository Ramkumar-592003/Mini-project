setInterval(() => {
    fetch("http://192.168.86.16/data")
      .then(res => {
        if (!res.ok) throw new Error("Network response was not OK");
        return res.json();
      })
      .then(data => {
        document.getElementById("temp").textContent = data.temperature;
        document.getElementById("hum").textContent = data.humidity;
        document.getElementById("soil").textContent = data.soil;
      })
      .catch(err => {
        console.error("Failed to fetch data:", err);
      });
  }, 3000);
  