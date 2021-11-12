from flask_restful import Resource, reqparse


parser = reqparse.RequestParser()
parser.add_argument('name', required=True)


class TestControllerAPI(Resource):
	def get(self):
		return 200