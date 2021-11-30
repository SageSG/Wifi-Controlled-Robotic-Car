function registerTask(order) {
	/*
	Marks the task as complete for the user. 
      :param: order. 
      :return: None.
    */
	tutorialCompleted[order] = 1;
	console.log(tutorialCompleted)
	checkCompleted()
}


function checkCompleted() {
	/*
	Checks that the task is completed for the user. 
      :param: None. 
      :return: None.
    */	
	let confirmMap = 0
	for (let i = 0; i < 4; i++) {
		if (tutorialCompleted[i] == 1) {
			confirmMap++
		} else {
			confirmMap = 0
		}
		if (confirmMap == 4) {
			document.getElementById('mapTutorial').classList.remove('btn-danger');
			document.getElementById('mapTutorial').classList.add('btn-success');
			document.getElementById('mapTutorial').innerHTML = 'Completed';
		}
	}

	let confirmMap2 = 0
	for (let i = 4; i < 8; i++) {
		if (tutorialCompleted[i] == 1) {
			confirmMap2++
		} else {
			confirmMap2 = 0
		}
		if (confirmMap2 == 4) {
			document.getElementById('gameTutorial').classList.remove('btn-danger');
			document.getElementById('gameTutorial').classList.add('btn-success');
			document.getElementById('gameTutorial').innerHTML = 'Completed';
		}
	}

	let confirmMap3 = 0
	for (let i = 8; i < 12; i++) {
		if (tutorialCompleted[i] == 1) {
			confirmMap3++
		} else {
			confirmMap3 = 0
		}
		if (confirmMap3 == 4) {
			document.getElementById('dashboardTutorial').classList.remove('btn-danger');
			document.getElementById('dashboardTutorial').classList.add('btn-success');
			document.getElementById('dashboardTutorial').innerHTML = 'Completed';
		}
	}
}