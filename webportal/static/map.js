// Javascript for Customise Map page

/*
    Notes for own reference:
    ev = event
    Node refers to an HTML element
*/

// Set on the elements that should allow allow drops
function allowDrop(ev) {
    ev.preventDefault();
}

/*
    Sets the data of the item being dragged to either start_tile,
    end_tile, route_tile, or empty_tile (based on the element's ID)
*/
function drag(ev) {
    ev.dataTransfer.setData("text", ev.target.id);
}

/* Remove tile from the map grid */
function removeNode(node) {
        node.parentNode.removeChild(node);
      }

/*
    - Customisation part of the map
    - Drops the item into the 8x8 Map grid by cloning and appending nodes
*/
function drop(ev) {
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
  console.log(mapGrid)
}