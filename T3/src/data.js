

// module.exports.fetchData = async function(interval = "1min", startDate) {
//   let fs = require("fs");
//   let data = fs.readFileSync("data.json");
//   // return JSON.parse(data);
//   // return await fetch("https://api.twelvedata.com/time_series?symbol=ARM&start_date=" + interval + "&outputsize=" + n + "&apikey=" + process.env.API_KEY)
// }

module.exports.closePrice = async function(date) {
  let data = await fetch("https://api.twelvedata.com/eod?date=" + date + "&symbol=ARM&apikey=" + process.env.API_KEY);
  let json = await data.json();
  return json;
}

module.exports.saveData = async function(data) {
  let json = await data.json();
  let fs = require("fs");
  fs.writeFileSync("data.json", JSON.stringify(json));
  return json;
}

module.exports.printData = async function(data) {
  let json = await data.json();
  console.log(json);
  return json;
}