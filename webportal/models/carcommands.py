from webportal import db

class CarCommands(db.Model):
	"""
	Class to contain the car command attributes. 
	:param: None.
	:return: None.
	"""	
	id = db.Column(db.Integer , primary_key=True)
	direction = db.Column(db.String(20))
	command = db.Column(db.Integer)

	def __init__(self, direction, command):
		self.direction = direction
		self.command = command 


def insert_commands(command):
	"""
	Inserts the car commands into the DB. 
	:param: command.
	:return: None.
	"""	
	# Inserts the commands to the db 
	command = CarCommands(command)
	try:
		db.session.add(command)
		db.session.commit()
	except:
		db.session.rollback()
	finally: 
		db.session.close()


def delete_command():
	"""
	Deletes the queried car command from the DB. 
	:param: None.
	:return: {"command": data.command}.
	"""		
	data = db.session.query(CarCommands).first()
	db.session.query(CarCommands).filter(CarCommands.id==data.id).delete()
	db.session.commit()
	return {"command": data.command}


def reset():
	"""
	Deletes all of the data from the car command DB.
	:param: None.
	:return: None.
	"""			
	# Delete all entires in the database 
	num_rows_deleted = db.session.query(CarCommands).delete()
	db.session.commit() 