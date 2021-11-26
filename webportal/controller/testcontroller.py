from flask_restful import Resource, reqparse


parser = reqparse.RequestParser()
parser.add_argument('name', required=True)


class TestControllerAPI(Resource):
	def post(self):
		args = parser.parse_args()
		return 200

	def get(self):
		return {"command": "1323232110"}