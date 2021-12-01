from flask_restful import Resource, reqparse
from webportal.models.map import *

parser = reqparse.RequestParser()
parser.add_argument('coordinates', required=True)


class MapControllerAPI(Resource):
	def post(self):
		args = parser.parse_args()
		insert_map(args['coordinates'])
		return 201
