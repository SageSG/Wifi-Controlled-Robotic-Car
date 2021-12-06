from flask import Flask
import unittest
from flask_sqlalchemy import SQLAlchemy
from webportal.controller.mapcontroller import *
from webportal import create_test_app, db
import logging

app = create_test_app()

class TestMapController(unittest.TestCase):
    '''
        Test cases for the MapControllerAPI class
    '''
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
            Test the post HTTP method for mapontroller.py
        """
        tester = app.test_client(self)

        print("\nTest Case: test_post")
        print("\nTesting post function in MapControllerAPI class...")
        print("Calling post function & parsing in values...")

        response = tester.post("/map_controller?coordinates=,0,0,0,0,0,0,0,0,0,1,2,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0")
        statuscode = response.status_code
        self.assertEqual(statuscode, 200)

        print("Received HTTP status code {}".format(statuscode))
        print("Success. First and second statements tested.")
        print("\nGiven input: ,0,0,0,0,0,0,0,0,0,1,2,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0")
        print("Expected Output: 201")

        post_response_body = response.data.decode("ascii").strip()
        self.assertEqual(post_response_body, "201")

        print("Actual Output: {}".format(post_response_body))
        print("Success. Fourth statement tested.")

        print("\nChecking if coordinates correctly inserted into the database...")
        print("Comparing values...")

        ## Check if insert map inserts coordinates correctly into the database
        data = db.session.query(Map).order_by('id').all()
        latest_entry = data[-1]

        print("expected_values = 0,0,0,0,0,0,0,0,0,1,2,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0")
        print("latest_entry = {}".format(latest_entry.map_coordinates))

        self.assertEqual(latest_entry.map_coordinates, "0,0,0,0,0,0,0,0,0,1,2,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0")

        print("Success. Third statement tested.")

        print("\nTotal number of statements for post function = 4")
        print("Number of statements tested for post function = 4")
        print("Statement code coverage statistics = 4/4 = 1")

        print("\n----------------------------------------------------------------------")

    def test_delete(self):
        """
            Test the delete HTTP method for mapontroller.py
        """

        tester = app.test_client(self)

        print("\nTest Case: test_delete")
        print("\nTesting delete function in MapControllerAPI class...")
        print("Calling delete function...")

        response = tester.delete("/map_controller")

        self.assertEqual(response.status_code, 200)

        print("Received HTTP status code {}".format(response.status_code))
        print("Success. First statement tested.")
        print("\nChecking if all entries in Map table removed...")

        ## Check if entries are deleted
        num_rows = db.session.query(Map).count()
        self.assertEqual(num_rows, 0)

        print("Success, number of rows is 0. Second statement tested.")
        print("\nExpected Output = 200")

        success_delete_response_body = response.data.decode("ascii").strip()
        self.assertEqual(success_delete_response_body, "200")

        print("Actual Output = {}".format(success_delete_response_body))
        print("Success. Third and fourth statements tested.")

        print("\nMake it such that status == False to return 500...")
        print("Expected Output = 500")

        ## Make it such that status == False to get 500 message.
        response = tester.delete("/map_controller")
        failed_delete_response_body = response.data.decode("ascii").strip()

        self.assertEqual(failed_delete_response_body, "500")

        print("Actual Output = 500")
        print("Success. Fifth and sixth statements tested.")

        print("\nTotal number of statements for post function = 6")
        print("Number of statements tested for post function = 6")
        print("Statement code coverage statistics = 6/6 = 1")

        print("\n----------------------------------------------------------------------")


    def tearDown(self):
        db.drop_all()