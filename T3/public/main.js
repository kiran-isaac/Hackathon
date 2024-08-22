async function getData() {
  const dateformelem = document.getElementById('date');
  const priceformelem = document.getElementById('price');
  const output = document.getElementById("output");
  const image = document.getElementById("him");

  let date_selected = dateformelem.value;
  let price = priceformelem.value;

  let closePrice = await fetch('/closepriceondate?date=' + date_selected)
    .catch(error => console.error('Error:', error));

  if (closePrice.ok) {
    let data = await closePrice.json();
    output.innerText = data.close - price;
    if (data.close - price >= 0) {
      image.src = "/stonks.png"
    } else {
      image.src = "/notstonks.png"
    }
  }
  
  return false;
}