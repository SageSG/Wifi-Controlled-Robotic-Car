function allowDrop(ev) {
      /*
       Set on the elements that should allow allow drops
      :param: node. 
      :return: None.
    */
    ev.preventDefault();
}


function drag(ev) {
      /*
      Sets the data of the item being dragged to either start_tile, end_tile, route_tile, or empty_tile (based on the element's ID)
      :param: node. 
      :return: None.
    */
    ev.dataTransfer.setData("text", ev.target.id);
}


function removeNode(node) {
    /*
      Remove tile from the map grid
      :param: node. 
      :return: None.
    */
        node.parentNode.removeChild(node);
      }


function drop(ev) {
    /*
      Allows the user to drop an draggable element into the grid. Drops the item into the 8x8 Map grid by cloning and appending nodes.
      :param: None. 
      :return: None.
    */
      ev.preventDefault();
      var data = ev.dataTransfer.getData("text");   // Get the ID of the item to be dropped which can be either start_tile, end_tile, route_tile, or empty_tile
      var routing_tile = 'route_tile' == data

      // Clone the selected tile & set a new id on cloned tile.
      var nodeCopy = document.getElementById(data).cloneNode(true);
      nodeCopy.id = "cloned_" + data;

      // clean target space if needed

      // Tile dropped is either a route tile or empty tile
      if (routing_tile) {
        // Tile placed on top of another existing tile on the map
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


function saveMap() {
	/*
    Saves the map created by the user. 
    :param: None. 
    :return: None.
	*/
  // List that stores start point, routes, and end point
  const mapGrid = [];

  // Numbers that specify if the tile is empty, the starting point, ending point, or a route
  const empty = 0;
  const start = 1;
  const route = 2;
  const end = 3;


  // Iterate through 8 rows of the map
  for (let r = 1; r < 9; r++) {

    var row = "grid_row_" + r.toString();
    const map_row = document.getElementById(row)

      const map_column = map_row.childNodes;

      var columns = [];

      // Iterate through 8 columns of the rows in the map
      for (let c = 1; c < 16; c+=2) {

        // Column has either a start, route, or end tile
        if (map_column[c].hasChildNodes()) {
            var tile = map_column[c].firstChild.id.toString();
            if (tile.includes("start_tile")) {
                columns.push(start)
            }
            else if (tile.includes("end_tile")) {
                columns.push(end)
            }
            else if (tile.includes("route_tile")) {
                columns.push(route)
            }
        }
        else {
            columns.push(empty)
        }
      }
        mapGrid[r] = columns
    }
  
    // Deletes the previous stats from the previous game and creates a new map
    var xhttp = new XMLHttpRequest();
    xhttp.open("DELETE", "/stats_controller");
    xhttp.send();
    xhttp.open("POST", "/map_controller");
    xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    xhttp.send("coordinates=" + mapGrid);
    $("#map_modal").modal("show");
}