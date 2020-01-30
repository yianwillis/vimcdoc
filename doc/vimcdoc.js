window.addEventListener('DOMContentLoaded', (event) => {
  const tag = new URLSearchParams(window.location.search).get("tag");
  if (tag) {
    for(var i = 0; i < document.links.length; ++i) {
      const link = document.links[i];
      if (link.innerHTML == tag) {
        document.body.innerHTML = "JS executed";
        window.parent.location.replace(link.href);
      }
    } 
  }
});
