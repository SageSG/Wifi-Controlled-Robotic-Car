from flask_restful import Resource, reqparse
from webportal.models.map import *
from webportal.models.carstats import *

# Add arguments to the HTTP POST request 
parser = reqparse.RequestParser()
parser.add_argument('coordinates', required=True)


class MapControllerAPI(Resource):
	"""
	Class to control the behaviour of the Map Controller API. 
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
		insert_map(args['coordinates'])
		# generate_stats()
		return 201


	def delete(self):
		"""
		Defines the behaviour of how the Map Controller API reacts to a HTTP DELETE request. 
		:param: self. 
		:return: 200 or 500.
		"""         
		# Remove all entires in the DB		
		status = delete_map()
		if status is True:
			return 200
		else:
			return 500
