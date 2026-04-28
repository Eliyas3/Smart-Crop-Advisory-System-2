function refreshData() {

let temp = Math.floor(Math.random() * 15) + 25;
let hum = Math.floor(Math.random() * 40) + 40;
let soil = Math.floor(Math.random() * 2000) + 1500;
let rain = Math.floor(Math.random() * 3000);
let light = Math.floor(Math.random() * 3000);

document.getElementById("temp").innerText = temp;
document.getElementById("hum").innerText = hum;
document.getElementById("soil").innerText = soil;
document.getElementById("rain").innerText = rain;
document.getElementById("light").innerText = light;

let advice = "";

if (soil > 2800) {
advice = "Soil is dry. Start irrigation.";
}
else if (rain < 1000) {
advice = "Rain expected. Stop irrigation.";
}
else if (temp > 38) {
advice = "High temperature detected. Protect crops.";
}
else if (light < 800) {
advice = "Low sunlight. Monitor crop growth.";
}
else {
advice = "All conditions normal for crops.";
}

document.getElementById("advice").innerText = advice;
}

refreshData();
setInterval(refreshData,5000);