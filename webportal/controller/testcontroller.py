from flask_restful import Resource, reqparse


class TestControllerAPI(Resource):
	def get(self):
		return {"test": "a"}