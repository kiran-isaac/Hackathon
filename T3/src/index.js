require("dotenv").config();
const express = require("express");
const { printData, fetchData, saveData, closePrice } = require("./data");

const app = express();

app.use(express.json());
app.use(express.urlencoded({ extended: true }));
app.set("views", "./views");
app.use(express.static("public"));

app.get("/closepriceondate", async (req, res) => {
  let date = req.query.date;
  let data = await closePrice(date);
  res.json(data);
});

// send index.html
app.get("/", async (_, res) => {
  res.sendFile("index.html", { root: "views" });
});

app.listen(process.env.PORT, () => {
  console.log("Listening on port " + process.env.PORT);
});