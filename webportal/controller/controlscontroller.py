from flask_restful import Resource, reqparse
from webportal.models.carcommands import *


parser = reqparse.RequestParser()
parser.add_argument('command', required=True)


class ControlsControllerAPI(Resource):
	"""
	Class to control the behaviour of the Controls Controller API. 
	:param: Resource. 
	:return: None.
	"""    	
	def get(self):
		"""
		Defines the behaviour of how the Controls Controller API reacts to a HTTP GET request. 
		:param: self. 
		:return: 201.
		"""    	
		data = delete_command() 
		return data


	def post(self):
		"""
		Defines the behaviour of how the Controls Controller API reacts to a HTTP GET request. 
		:param: self. 
		:return: 201.
		"""  		
		args = parser.parse_args()
		if args['command'] == "motor_start()":
			command = 1

		elif args['command'] == "motor_back()":
			command = 2

		elif args['command'] == "motor_left()":
			command = 3

		elif args['command'] == "motor_right()":
			command = 4
		insert_commands(command)
		return 200
