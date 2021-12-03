from webportal import db

class CarCommands(db.Model):
	id = db.Column(db.Integer , primary_key=True)
	direction = db.Column(db.String(20))
	command = db.Column(db.Integer)

	def __init__(self, direction, command):
		self.direction = direction
		self.command = command 


def insert_commands(command):
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
	data = db.session.query(CarCommands).first()
	db.session.query(CarCommands).filter(CarCommands.id==data.id).delete()
	db.session.commit()
	return {"command": data.command}


def reset():
	# Delete all entires in the database 
	num_rows_deleted = db.session.query(CarCommands).delete()
	db.session.commit() 