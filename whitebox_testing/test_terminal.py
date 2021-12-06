from flask import Flask
import unittest
from flask_sqlalchemy import SQLAlchemy
from webportal.models.carcommands import *
from webportal import create_test_app, db

app = create_test_app()


class TestTerminal(unittest.TestCase):
    '''
        Test cases for the MapControllerAPI class
    '''

    def setUp(self):
        '''
            Sets up the testing environment by creating a new database for the test cases to use and
            inserts three new rows into the map table.
        '''
        db.create_all()
        insert_commands(1)
        insert_commands(2)
        insert_commands(3)
        insert_commands(4)

    def test_init(self):
        '''
            Tests that the constructor in the carcommands.py file
            is able to assign the correct values to the right parameters.
        '''
        car_commands_object = CarCommands(2)
        self.assertEqual(car_commands_object.command, 2)

    def test_insert_commands(self):
        '''
            Tests that the insert_commands() function in carcommands.py is able to insert correct
            values into the car_commands table in the database without errors.
        '''

        insert_commands(3)

        data = db.session.query(CarCommands).order_by('id').all()

        latest_entry = data[-1]

        self.assertEquals(latest_entry.command, 3)

    def test_delete_command(self):
        '''
            Tests if the delete_command() function of the carcommands.py file is able to delete the first entry in the
            car_commands table when called.
        '''
        dict_deleted = delete_command()
        command_deleted = dict_deleted["command"]
        self.assertEquals(command_deleted, 1)

    def test_delete_all_commands(self):
        '''
            Tests if the delete_all_commands() function is able to remove all entries from the car_commands table in the database.
        '''
        delete_all_commands()
        num_rows = db.session.query(CarCommands).count()
        self.assertEqual(num_rows, 0)

    def tearDown(self):
        db.drop_all()
