from webportal import db

class Map(db.Model):
    # Columns in DB
    id = db.Column(db.Integer, primary_key=True)
    map_coordinates = db.Column(db.String)

    def __init__(self, map_coordinates):
        self.map_coordinates = map_coordinates


def insert_map(coordinates):
    map = Map(coordinates[1::])
    db.session.add(map)
    db.session.commit()	


def get_map():
    # Retrieve the latest stats from the DB
    data = db.session.query(Map).all()

    # Latest entry data 
    latest_entry = data[-1]

    return data