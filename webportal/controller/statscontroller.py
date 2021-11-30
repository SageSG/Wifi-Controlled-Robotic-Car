from flask_restful import Resource, reqparse
from webportal.models.carstats import *

# Add arguments to the POST request 
parser = reqparse.RequestParser()
parser.add_argument('temp', required=True)
parser.add_argument('dist', required=True)
parser.add_argument('speed', required=True)
parser.add_argument('line', required=True)


class CarStatsControllerAPI(Resource):
	"""
	Class to control the behaviour of the Car Stats Controller API. 
	:param: Resource. 
	:return: None.
	"""    
	def post(self):
		"""
		Defines the behaviour of how the Map Controller API reacts to a HTTP POST request. 
		:param: self. 
		:return: 201.
		"""    	        
		args = parser.parse_args()
		insert_stats(args['temp'], args['dist'], args['speed'], args['line'])
		return 201


	def display_dashboard_stats(self):
		"""
		Retrieves the dashboard statistics and displays them on the dashboard UI. 
		:param: self. 
		:return: stats.
		"""    	       
		stats = get_stats() 
		return stats


	def delete(self):
		"""
		Defines the behaviour of how the Map Controller API reacts to a HTTP DELETE request. 
		:param: self. 
		:return: 200 or 500.
		"""         		
		status = delete_stats()
		if status is True:
			return 200
		else:
			return 500