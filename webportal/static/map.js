function allowDrop(ev) {
    ev.preventDefault();
}

function drag(ev) {
    ev.dataTransfer.setData("text", ev.target.id);
}

function removeNode(node) {
        node.parentNode.removeChild(node);
      }
      
function drop(ev) {
      ev.preventDefault();
      var data = ev.dataTransfer.getData("text");
      var isLeft = 'drag3' == data || "drag4" == data;
      var nodeCopy = document.getElementById(data).cloneNode(true);
      nodeCopy.id = "img" + ev.target.id;
      // clean target space if needed
      if (isLeft) {
        if (ev.target.nodeName == 'IMG') {
          ev.target.parentNode.appendChild(nodeCopy);
          removeNode(ev.target);
        }
        else 
          ev.target.appendChild(nodeCopy);
      }
      else {
        if (ev.target.nodeName != 'IMG') {
          removeNode(document.getElementById(data));
          ev.target.appendChild(nodeCopy);
        }
      }
      ev.stopPropagation();
      return false;
    }

function allowDrop(ev) {
  ev.preventDefault();
}

function savemap() { 
  var grids = [];
  var grids_to_send = [];

  const grid1 = document.getElementById("grid_row_1");
  const grid1_div = grid1.getElementsByTagName("div");
  grids[0] = grid1_div

  const grid2 = document.getElementById("grid_row_2");
  const grid2_div = grid2.getElementsByTagName("div");
  grids[1] = grid2_div

  const grid3 = document.getElementById("grid_row_3");
  const grid3_div = grid3.getElementsByTagName("div");
  grids[2] = grid3_div

  const grid4 = document.getElementById("grid_row_4");
  const grid4_div = grid4.getElementsByTagName("div");
  grids[3] = grid4_div

  const grid5 = document.getElementById("grid_row_5");
  const grid5_div = grid5.getElementsByTagName("div");
  grids[4] = grid5_div

  const grid6 = document.getElementById("grid_row_6");
  const grid6_div = grid6.getElementsByTagName("div");
  grids[5] = grid6_div

  const grid7 = document.getElementById("grid_row_7");
  const grid7_div = grid7.getElementsByTagName("div");
  grids[6] = grid7_div

  const grid8 = document.getElementById("grid_row_8");
  const grid8_div = grid8.getElementsByTagName("div");
  grids[7] = grid8_div


  for (let i = 0; i <= grids.length - 1; i++) {
    var temp = [];
    for (let y = 0; y <= grids[i].length - 1; y++) {
      
      
      // var parser = new DOMParser();
      // var doc = parser.parseFromString(grids[i].innerHTML, "text/html");
      // temp[y] = doc.getElementsByTagName("img")[0];
    }
    // grids_to_send[i] = temp;
  }

  console.log(grids_to_send);

  

}



    // document.getElementById("execute_btn").onclick = function () {
    //     const ul = document.getElementById('sqnce-list');
    //     const listItems = ul.getElementsByTagName('li');

    //     // Loop through the NodeList object.
    //     for (let i = 0; i <= listItems.length - 1; i++) {
    //         var http = new XMLHttpRequest();
    //         var url = 'http://127.0.0.1:5000/car/commands';
    //         var params = 'direction=webportal&command=' + listItems[i].innerHTML;
    //         http.open('POST', url, true);

    //         //Send the proper header information along with the request
    //         http.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    //         http.send(params);
    //     }