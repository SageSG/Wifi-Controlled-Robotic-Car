from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from flask_testing import TestCase
from webportal.models.map import *
from webportal import db, create_test_app

# Unit testing carstats.py functions
class TestMap(TestCase):
    '''
        Test cases for the map.py file.
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

    def test_insert_map(self):
        '''
            Tests that the insert_map() function in map.py is able to insert correct
            values into the map table in the database without errors.
        '''
        insert_map(",0,0,0,1,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0")
        # Retrieve the latest stats from the DB
        data = db.session.query(Map).order_by('id').all()

        # Latest entry data
        latest_entry = data[-1]

        self.assertEqual(latest_entry.map_coordinates, "0,0,0,1,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0")

    def test_get_map(self):
        '''
            Tests that data is retrieved accurately from the database.
        '''
        data = get_map()
        self.assertEquals(data.map_coordinates, "1,2,2,2,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0")

    def test_delete_map(self):
        '''
            Tests if the delete_map() function of the map.py file is able to delete all the entries in the
            map table when called.
        '''
        bool_value = delete_map()
        num_rows = db.session.query(Map).count()

        # Check if values stored in Map table are deleted
        self.assertEquals(num_rows, 0)
        self.assertEqual(bool_value, True)
