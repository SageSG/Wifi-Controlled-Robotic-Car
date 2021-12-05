from flask import Flask
from flask_testing import TestCase
from flask_sqlalchemy import SQLAlchemy
from webportal.controller.mapcontroller import *
from webportal import create_test_app, db
from webportal import app

class TestMapController(TestCase):
    '''
        Test cases for the MapControllerAPI class
    '''
    def create_app(self):
        """
            Uses app context for testing environment instead of the production one.
        """
        return create_test_app()

    def setUp(self):
        '''
            Sets up the testing environment by creating a new database for the test cases to use and
            inserts three new rows into the map table.
        '''
        db.create_all()
        insert_map(",0,0,0,0,0,0,0,0,0,1,2,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0")
        insert_map(",0,0,0,0,0,0,0,0,1,2,2,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0")
        insert_map(",1,2,2,2,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0")


    def test_post(self):
        """
            Test the post and delete HTTP methods for mapontroller.py
        """
        # post function
        tester = app.test_client(self)
        response = tester.post("/map_controller?coordinates=,0,0,0,0,0,0,0,0,0,1,2,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0")
        statuscode = response.status_code
        self.assertEqual(statuscode, 200)
        post_response_body = response.data.decode("ascii").strip()
        self.assertEqual(post_response_body, "201")

        ## Check if insert map inserts coordinates correctly into the database
        data = db.session.query(Map).order_by('id').all()
        latest_entry = data[-1]
        self.assertEqual(latest_entry.map_coordinates, "0,0,0,0,0,0,0,0,0,1,2,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0")

        # delete function
        response = tester.delete("/map_controller")
        success_delete_response_body = response.data.decode("ascii").strip()
        self.assertEqual(success_delete_response_body, "200")

        ## Check if entries are deleted
        num_rows = db.session.query(Map).count()
        self.assertEqual(num_rows, 0)

        ## Make it such that status == False to get 500 message.
        response = tester.delete("/map_controller")
        failed_delete_response_body = response.data.decode("ascii").strip()

        self.assertEqual(failed_delete_response_body, "500")

    def tearDown(self):
        db.drop_all()