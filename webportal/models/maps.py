# Map id, Can_move, got obstacle

# Create Map Table
class Maps(db.Model):
    # Columns in DB
    id = db.Column(db.Integer, primary_key=True)
    # map_coordinates = db.Column(db.String)
    map_blob = db.Column(db.BLOB)

    # def __init__(self, map_coordinates):
    #     self.map_coordinates = map_coordinates
    def __init__(self, map_blob):
        self.map_blob = map_blob

def insert_map():
	pass 

def get_map():
	pass