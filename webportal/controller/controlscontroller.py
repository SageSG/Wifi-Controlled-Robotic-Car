from flask_restful import Resource, reqparse
from webportal.models.carcommands import *


parser = reqparse.RequestParser()
parser.add_argument('direction', required=True)
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
		print(args['command'])
		xlist = args['command'].split(",")
		for x in xlist:
			print (x)
			if x == "1":
				command = 1

			elif x == "2":
				command = 2

			elif x == "3":
				command = 3

			elif x == "4":
				command = 4
			
			insert_commands(command)
		return 200
