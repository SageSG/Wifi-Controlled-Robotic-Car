import json
from datetime import datetime
from webportal import db
from random import randint


class CarStats(db.Model):
	"""
	Class to contain the car's stats attributes. 
	:param: db.model. 
	:return: None.
	"""    
	# Columns in Car Stats table in the DB.  
	id = db.Column(db.Integer, primary_key=True)
	temp = db.Column(db.Float)
	dist = db.Column(db.Float)
	speed = db.Column(db.INT)
	line = db.Column(db.Boolean)
	time = db.Column(db.String)


	def __init__(self, temp, dist, speed, line):
		"""
		Initialise a CarStats object. 
		:param: self, temp, dist, speed, line. 
		:return: None. 
		"""        
		self.temp = temp
		self.dist = dist
		self.speed = speed
		self.line = int(line)
		self.time = datetime.now().strftime("%H:%M:%S")


def insert_stats(temp, dist, speed, line):
	"""
	Insert the stats sent from the car to the DB. 
	:param: self, temp, dist, speed, line. 
	:return: None.
	"""
	car_stats = CarStats(temp, dist, speed, line)
	try:
		db.session.add(car_stats)
		db.session.commit()
	except:
		db.session.rollback()
	finally: 
		db.session.close()


def get_stats():
	"""
	Gets all of the car statistics from the db. 
	:param: None.
	:return: current_stats, temps_graph_stats, speed_graph_stats, line_detect_graph_stats, line_count_graph_stats.
	"""
	# Retrieve the latest stats from the DB
	data = db.session.query(CarStats).order_by('id').all()

	# Latest entry data 
	latest_entry = data[-1]
	current_speed = latest_entry.speed
	current_temps = latest_entry.temp
	current_stats = {'current_speed': current_speed, 'current_temps': current_temps}

	# Dictionaries to store the various graph data 
	temps_graph_stats = {}
	speed_graph_stats = {}
	line_detect_graph_stats = {}
	line_count_graph_stats = {}

	# Variables to store the count for True and False for the Line Detect Graph 
	true_count = 0
	false_count = 0

	# Variable to store the total distance travelled 
	total_distance = 0

	# Traverse the data returned from the DB and place them accordingly into the appropirate dictionaires. 
	movement_placeholder = ""
	for item in data:
		movement_placeholder = item.time
		temps_graph_stats[movement_placeholder] = item.temp
		speed_graph_stats[movement_placeholder] = item.speed
		line_detect_graph_stats[movement_placeholder] = item.line 
		total_distance += item.dist   
		if item.line == 1:
			true_count += 1 
		else:
			false_count += 1 
	line_count_graph_stats["true_count"] = true_count
	line_count_graph_stats["false_count"] = false_count  
	current_stats["total_dist"] = total_distance
	return current_stats, temps_graph_stats, speed_graph_stats, line_detect_graph_stats, line_count_graph_stats


def delete_stats():
	"""
	Delete all of the car statistics from the db. 
	:param: None.
	:return: True or False.
	"""
	# Remove all entires in the DB
	num_rows_deleted = db.session.query(CarStats).delete()
	try:
		db.session.commit()
	except:
		db.session.rollback()
		return False
	finally: 
		db.session.close()
	return True    


def generate_stats():
	"""
	Generate random stats for the dashboard to display. This is only used when the robotic car is actually not finished. 
	:param: None.
	:return: None.
	"""	
	number_of_stats = randint(20, 30)
	for i in range(0, 30):
		temp = randint(20, 30)
		dist = randint(5, 10)
		speed = randint(5, 10)
		line = True
		insert_stats(temp, dist, speed, line)