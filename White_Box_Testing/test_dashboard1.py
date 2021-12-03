import sqlite3
from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from flask_testing import TestCase
from webportal.models.carstats import *
from webportal.models.carstats import CarStats
from webportal import db, create_test_app
# Unit testing carstats.py functions

class TestCarStats(TestCase):

    def create_app(self):
        return create_test_app()

    def setUp(self):
        db.create_all()
        insert_stats(100,101,105, True)
        insert_stats(200,201,205, True)

    # Tests if values are properly inserted into CarStats object.
    def test_init(self):

        car_stats_object = CarStats(25, 5, 50, True)
        self.assertEqual(car_stats_object.temp, 25)
        self.assertEqual(car_stats_object.dist, 5)
        self.assertEqual(car_stats_object.speed, 50)
        self.assertEqual(car_stats_object.line, True)

    # Tests if values are properly inserted into car_stats table in DB
    def test_insert_stats(self):

        ## Insert values into DB without errors
        insert_stats(300,301,305, True)
        # Retrieve the latest stats from the DB
        data = db.session.query(CarStats).order_by('id').all()

        # Latest entry data
        latest_entry = data[-1]

        # Test if all values in DB matched what was inserted
        self.assertEquals(latest_entry.temp, 300)
        self.assertEquals(latest_entry.dist, 301)
        self.assertEquals(latest_entry.speed, 305)
        self.assertEquals(latest_entry.line, True)

    # Tests if
    def test_get_stats(self):
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

    def test_delete_stats(self):
        delete_stats()
        num_rows = db.session.query(CarStats).count()
        self.assertEquals(num_rows, 0)

