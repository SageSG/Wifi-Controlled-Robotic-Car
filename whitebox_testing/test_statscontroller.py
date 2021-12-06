from flask import Flask
from flask_testing import TestCase
from webportal.controller.statscontroller import *
from webportal import create_test_app
from webportal import app
import unittest

app = create_test_app()

class TestStatsController(unittest.TestCase):
    '''
        Test cases for the statscontroller.py file.
    '''
    def setUp(self):
        db.create_all()
        insert_stats(100, 101, 105, True)
        insert_stats(200, 201, 205, True)

    def test_post_delete(self):
        """
            Test the post and delete HTTP methods for statscontroller.py
        """
        tester = app.test_client(self)
        response = tester.post("/stats_controller?temp=25&dist=10&speed=50&line=1")
        statuscode1 = response.status_code
        self.assertEqual(statuscode1, 200)

        response = tester.delete("/stats_controller")
        statuscode2 = response.status_code
        self.assertEqual(statuscode2, 200)

    def tearDown(self):
        db.drop_all()
