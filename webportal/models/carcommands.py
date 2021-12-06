from webportal import db

class CarCommands(db.Model):
	"""
	Class to control the behaviour of the Car Stats Controller API. 
	:param: Resource. 
	:return: None.
	"""    	
	id = db.Column(db.Integer , primary_key=True)
	command = db.Column(db.Integer)

	def __init__(self, command):
		self.command = command 


def insert_commands(command):
	"""
	Inserts the command into the DB.
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
	Deletes the most command entry from the db. 
	:param: None.
	:return: {"command": data.command} or False.
	"""			
	try:
		data = db.session.query(CarCommands).first()
		db.session.query(CarCommands).filter(CarCommands.id==data.id).delete()
		db.session.commit()
	except:
		db.session.rollback()
		return False
	finally: 
		db.session.close()
	return {"command": data.command}


def delete_all_commands():
	"""
	Delete all of the car commands from the db. 
	:param: None.
	:return: True or False.
	"""
	# Remove all entires in the DB
	num_rows_deleted = db.session.query(CarCommands).delete()
	try:
		db.session.commit()
	except:
		db.session.rollback()
		return False
	finally: 
		db.session.close()
	return True    