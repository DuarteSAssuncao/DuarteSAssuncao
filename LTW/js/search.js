"use strict";

const searchForm = document.querySelector(".search");
const searchInput = searchForm.querySelector("#search");
const searchCondition = searchForm.querySelector("#condition");
const searchCategory = searchForm.querySelector("#category");
const searchSize = searchForm.querySelector("#size");

searchInput.addEventListener("input", action);
searchCondition.addEventListener("change", action);
searchCategory.addEventListener("change", action);
searchSize.addEventListener("change", action);

async function action() {
  const responseItems = await fetch(
    "../js/api_search.php?" +
      encodeForAjax({
        search: searchInput.value,
        condition: searchCondition.value,
        category: searchCategory.value,
        size: searchSize.value,
      })
  );
  const items = await responseItems.json();

  const section = document.querySelector(".items");
  if (!section) console.error("Items section not found");

  section.innerHTML = "";

  if (items.length === 0) {
    const error = document.createElement("bold");
    error.textContent =
      "No items found. Please check the filters or try again later.";
    section.appendChild(error);
  } else {
    for (const item of items) {
      const card = await createCard(item);
      section.appendChild(card);
    }
  }
}

function encodeForAjax(data) {
  return Object.keys(data)
    .map(function (k) {
      return encodeURIComponent(k) + "=" + encodeURIComponent(data[k]);
    })
    .join("&");
}

async function createCard(item) {
  /* 
    <a class="card" href="../src/item.php?id=<?= $item['id'] ?>">
        <article onclick="this.parentNode.submit()">
            <img src="<?= $photo ?>" alt="<?=$item['descript']?>">
            <h3><?=$item['brand'] . ' ' . $item['model']?></h3>
            <p><?= $item['price'] ?></p>
        </article>
    </a>
  */

  const a = document.createElement("a");
  a.classList.add("card");
  a.href = "../src/item.php?id=" + item.id;

  const article = document.createElement("article");
  article.onclick = () => a.submit();

  const img = document.createElement("img");
  const responsePhoto = await fetch(
    "../js/api_photo.php?" + encodeForAjax({ item_id: item.id })
  );
  const photo = await responsePhoto.json();
  img.src = photo;
  img.alt = item.descript;
  article.appendChild(img);

  const h3 = document.createElement("h3");
  h3.textContent = item.brand + " - " + item.model;
  article.appendChild(h3);

  const p = document.createElement("p");
  article.appendChild(p);
  p.textContent = item.price;

  a.appendChild(article);
  return a;
}
