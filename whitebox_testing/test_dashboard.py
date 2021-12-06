from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from webportal.models.carstats import CarStats
from webportal.models.carstats import *
from webportal import db, create_test_app
import unittest

app = create_test_app()

class TestCarStats(unittest.TestCase):
    '''
        Test cases for the carstats.py file.
    '''
    def setUp(self):
        '''
            Sets up the testing environment by creating a new database for the test cases to use and
            inserts two new rows into the car_stats table.
        '''
        db.create_all()
        insert_stats(100,101,105, True)
        insert_stats(200,201,205, True)

    def test_init(self):
        '''
            Tests that the constructor in the carstats.py file
            is able to assign the correct values to the right parameters.
        '''
        car_stats_object = CarStats(25, 5, 50, True)
        self.assertEqual(car_stats_object.temp, 25)
        self.assertEqual(car_stats_object.dist, 5)
        self.assertEqual(car_stats_object.speed, 50)
        self.assertEqual(car_stats_object.line, True)

    def test_insert_stats(self):

        '''
            Tests that the insert_stats() function in carstats.py is able to insert correct
            values into the car_stats table in the database without errors.
        '''

        insert_stats(300,301,305, True)

        data = db.session.query(CarStats).order_by('id').all()

        latest_entry = data[-1]

        self.assertEquals(latest_entry.temp, 300)
        self.assertEquals(latest_entry.dist, 301)
        self.assertEquals(latest_entry.speed, 305)
        self.assertEquals(latest_entry.line, True)

    def test_get_stats(self):

        '''
            Tests that data is retrieved accurately from the database.
        '''
        # [0] current_stats,
        # [1] temps_graph_stats,
        # [2] speed_graph_stats,
        # [3] line_detect_graph_stats,
        # [4] line_count_graph_stats
        stats = get_stats()

        # Test if current stats values are correct
        self.assertEqual(stats[0]["current_speed"], 205)
        self.assertEqual(stats[0]["total_dist"], 302)
        self.assertEqual(stats[0]["current_temps"], 200)

        temp_list = list(stats[1].values())
        self.assertEqual(temp_list[0], 200)

        speed_list = list(stats[2].values())
        self.assertEqual(speed_list[0], 205)

        line_list = list(stats[3].values())
        self.assertEqual(line_list[0], True)

        self.assertEqual(stats[4]["true_count"], 2)
        self.assertEqual(stats[4]["false_count"], 0)


    def test_delete_stats(self):
        '''
            Tests if the delete_stats() function of the carstats.py file is able to delete all the entries in the
            car_stats table when called.
        '''
        delete_stats()
        num_rows = db.session.query(CarStats).count()
        self.assertEquals(num_rows, 0)

    def tearDown(self):
        db.session.remove()
        db.drop_all()

