from webportal import db

class CarCommands(db.Model):
	id = db.Column(db.Integer , primary_key=True)
	command = db.Column(db.Integer)

	def __init__(self, command):
		self.command = command 


def insert_commands(command):
	# Inserts the commands to the db 
	command = CarCommands(command)
	db.session.add(command)
	db.session.commit()


# def send_commands():
# 	# Get the commands from the db and send it to the car (ask HL or Jas)
# 	pass 


# def get_command_stats():
# 	data = db.session.query(CarCommands).order_by('id').all() 
# 	command_dict = {"foward": 0, "left": 0, "right": 0, "backwards": 0}
# 	print(data)


# def reset_command():
# 	# Delete all entires in the database 
# 	num_rows_deleted = db.session.query(CarCommands).delete()
# 	db.session.commit() 


def delete_command():
	data = db.session.query(CarCommands).first()
	db.session.query(CarCommands).filter(CarCommands.id==data.id).delete()
	db.session.commit()
	return {"command": data.command}