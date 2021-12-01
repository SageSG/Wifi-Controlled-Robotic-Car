from flask_restful import Resource, reqparse
from webportal.models.carstats import *


parser = reqparse.RequestParser()
parser.add_argument('temp', required=True)
parser.add_argument('dist', required=True)
parser.add_argument('speed', required=True)
parser.add_argument('line', required=True)


class CarStatsControllerAPI(Resource):
    # The car creates a new entry by POST
    def post(self):
        args = parser.parse_args()
        insert_stats(args['temp'], args['dist'], args['speed'], args['line'])
        return 201


    def display_dashboard_stats(self):
        stats = get_stats() 
        return stats


    def delete(self):
        pass 

# curl http://localhost:5000/car/stats -d "temp=27.5" -d "dist=10" -d "speed=5" -d "line=0" -X POST
# 