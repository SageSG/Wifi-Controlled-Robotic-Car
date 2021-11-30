from webportal import db


class Map(db.Model):
	"""
	Class to contain the map attributes. 
	:param: None.
	:return: None.
	"""
	# Columns in Map table in the DB. 
	id = db.Column(db.Integer, primary_key=True)
	map_coordinates = db.Column(db.String)

	def __init__(self, map_coordinates):
		"""
		Initialise a CarStats object. 
		:param: self, temp, dist, speed, line. 
		:return: None. 
		"""          
		self.map_coordinates = map_coordinates


def insert_map(coordinates):
	"""
	Insert a map object into the DB. 
	:param: coordinates. 
	:return: None. 
	"""   
	map = Map(coordinates[1::])
	try:
		db.session.add(map)
		db.session.commit()	
	except:
		db.session.rollback()
	finally: 
		db.session.close()


def get_map():
	"""
	Get a map object from the DB. 
	:param: None. 
	:return: latest_entry. 
	"""       
	# Retrieve the latest map from the DB
	data = db.session.query(Map).all()
	return data[-1]


def delete_map():
	"""
	Deletes all of the map entries from the DB. 
	:param: None. 
	:return: True or False.
	"""         
	# Remove all entires in the DB
	num_rows_deleted = db.session.query(Map).delete()
	try:
		db.session.commit()
	except:
		db.session.rollback()
		return False
	finally: 
		db.session.close()
	return True    