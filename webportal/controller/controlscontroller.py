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
		command = args['command']	
		insert_commands(command)
		return 200


	def delete(self):
		"""
		Defines the behaviour of how the Controls Controller API reacts to a HTTP DELETE request. 
		:param: self. 
		:return: 200 or 500.
		"""         		
		status = delete_all_commands()
		if status is True:
			return 200
		else:
			return 500