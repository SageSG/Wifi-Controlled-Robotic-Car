function createTempChart(temp_chart_stats){
	/*
	Creates the temperature chart for the dashboard. 
	:param: temp_chart_stats. 
	:return: None.
	*/
	const ctx = document.getElementById('temp_chart').getContext('2d');
	var temp_chart_labels = [];
	var temp_chart_data = [];

	for (const [key, value] of Object.entries(temp_chart_stats)) {
		temp_chart_labels.push(key);
		temp_chart_data.push(value);
	}	

	const temp_chart = new Chart(ctx, {
	    type: 'line',
	    data: {
	        labels: temp_chart_labels,
	        datasets: [{
	            data: temp_chart_data,
	            backgroundColor: [
	                'rgba(255, 99, 132, 0.2)',
	                'rgba(54, 162, 235, 0.2)',
	                'rgba(255, 206, 86, 0.2)',
	                'rgba(75, 192, 192, 0.2)',
	                'rgba(153, 102, 255, 0.2)',
	                'rgba(255, 159, 64, 0.2)'
	            ],
	            borderColor: [
	                'rgba(255, 99, 132, 1)',
	                'rgba(54, 162, 235, 1)',
	                'rgba(255, 206, 86, 1)',
	                'rgba(75, 192, 192, 1)',
	                'rgba(153, 102, 255, 1)',
	                'rgba(255, 159, 64, 1)'
	            ],
	            borderWidth: 1
	        }]
	    },

	    options: {
	        scales: {
	            y: {
	                beginAtZero: true,
	                precision: 0,
	            }
	        },

           plugins:{   
             legend: {
               display: false
					},
            },

            maintainAspectRatio: false,
	    	}
	})	
}


function createSpeedChart(speed_chart_stats){
	/*
	Creates the speed chart for the dashboard. 
	:param: speed_chart_stats. 
	:return: None.
	*/	
	var speed_chart_labels = [];
	var speed_chart_data = [];
	for (const [key, value] of Object.entries(speed_chart_stats)) {
		speed_chart_labels.push(key);
		speed_chart_data.push(value);
	}	

	const ctx1 = document.getElementById('speed_chart').getContext('2d');
	const myChart1 = new Chart(ctx1, {
	    type: 'line',
	    data: {
	        labels: speed_chart_labels,
	        datasets: [{
	            label: 'speed',
	            data: speed_chart_data,
	            backgroundColor: [
	                'rgba(255, 99, 132, 0.2)',
	                'rgba(54, 162, 235, 0.2)',
	                'rgba(255, 206, 86, 0.2)',
	                'rgba(75, 192, 192, 0.2)',
	                'rgba(153, 102, 255, 0.2)',
	                'rgba(255, 159, 64, 0.2)'
	            ],
	            borderColor: [
	                'rgba(255, 99, 132, 1)',
	                'rgba(54, 162, 235, 1)',
	                'rgba(255, 206, 86, 1)',
	                'rgba(75, 192, 192, 1)',
	                'rgba(153, 102, 255, 1)',
	                'rgba(255, 159, 64, 1)'
	            ],
	            borderWidth: 1
	        }]
	    },
	    options: {
	        scales: {
	            y: {
	                beginAtZero: true,
	                precision: 0,
	            }
	        },

           plugins:{   
             legend: {
               display: false
					},
            },

            maintainAspectRatio: false,
	    	}
	});	
}


function createLineDetectCountChart(line_detect_count_chart_stats){
	/*
	Creates the line detect count chart for the dashboard. 
	:param: line_detect_count_chart_stats. 
	:return: None.
	*/		
	var line_detect_count_chart_labels = [];
	var line_detect_count_chart_data = [];
	for (const [key, value] of Object.entries(line_detect_count_chart_stats)) {
		line_detect_count_chart_labels.push(key);
		line_detect_count_chart_data.push(value);
	}	

	const ctx3 = document.getElementById('line_detect_count_chart').getContext('2d');
	const myChart3 = new Chart(ctx3, {
	    type: 'bar',
	    data: {
	        labels: line_detect_count_chart_labels,
	        datasets: [{
	            label: 'Line Detected Count',
	            data: line_detect_count_chart_data,
	            backgroundColor: [
	                'rgba(255, 99, 132, 0.2)',
	                'rgba(54, 162, 235, 0.2)',
	                'rgba(255, 206, 86, 0.2)',
	                'rgba(75, 192, 192, 0.2)',
	                'rgba(153, 102, 255, 0.2)',
	                'rgba(255, 159, 64, 0.2)'
	            ],
	            borderColor: [
	                'rgba(255, 99, 132, 1)',
	                'rgba(54, 162, 235, 1)',
	                'rgba(255, 206, 86, 1)',
	                'rgba(75, 192, 192, 1)',
	                'rgba(153, 102, 255, 1)',
	                'rgba(255, 159, 64, 1)'
	            ],
	            borderWidth: 1
	        }]
	    },
	    options: {
	        scales: {
	            y: {
	                beginAtZero: true,
			        ticks: {
			            precision: 0,	            
			        }        
	            }
	        },

           plugins:{   
             legend: {
               display: false
					},
            },

            maintainAspectRatio: false,
	    	}
	});	
}


function createLineDetectGraph(line_detect_chart_stats){
	/*
	Creates the line detect chart for the dashboard. 
	:param: line_detect_chart_stats. 
	:return: None.
	*/			
	var line_detect_chart_labels = [];
	var line_detect_chart_data = [];
	for (const [key, value] of Object.entries(line_detect_chart_stats)) {
		line_detect_chart_labels.push(key);
		line_detect_chart_data.push(value);
	}	

	const ctx2 = document.getElementById('line_detect_chart').getContext('2d');
	const myChart2 = new Chart(ctx2, {
	    type: 'line',
	    data: {
	        labels: line_detect_chart_labels,
	        datasets: [{
	            label: 'Line Detected',
	            data: line_detect_chart_data,
	            backgroundColor: [
	                'rgba(255, 99, 132, 0.2)',
	                'rgba(54, 162, 235, 0.2)',
	                'rgba(255, 206, 86, 0.2)',
	                'rgba(75, 192, 192, 0.2)',
	                'rgba(153, 102, 255, 0.2)',
	                'rgba(255, 159, 64, 0.2)'
	            ],
	            borderColor: [
	                'rgba(255, 99, 132, 1)',
	                'rgba(54, 162, 235, 1)',
	                'rgba(255, 206, 86, 1)',
	                'rgba(75, 192, 192, 1)',
	                'rgba(153, 102, 255, 1)',
	                'rgba(255, 159, 64, 1)'
	            ],
	            borderWidth: 1
	        }]
	    },
	    options: {
	        scales: {
	            y: {
	                beginAtZero: true,
			        ticks: {
			            precision: 0,
				        callback:function(value,index,values){
				            if (value == 1) return "True";
				            if (value == 0) return "False";
				        }		            
			        }        
	            }
	        },

           plugins:{   
             legend: {
               display: false
					},
            },

            maintainAspectRatio: false,
	    	}
	});
}