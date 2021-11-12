from flask_restful import Resource, reqparse


parser = reqparse.RequestParser()
parser.add_argument('name', required=True)


class TestControllerAPI(Resource):
	def post(self):
		args = parser.parse_args()
		return 200