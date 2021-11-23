import json
from datetime import datetime
from webportal import db

class CarStats(db.Model):
    id = db.Column(db.Integer , primary_key=True)
    temp = db.Column(db.Float)
    dist = db.Column(db.Float)
    speed = db.Column(db.INT)
    line = db.Column(db.Boolean)
    time = db.Column(db.String)


    def __init__(self, temp, dist, speed, line):
        self.temp = temp
        self.dist = dist
        self.speed = speed
        self.line = int(line)
        self.time = datetime.now().strftime("%H:%M:%S")


def insert_stats(temp, dist, speed, line):
    # Inserts the stats sent from the car to the DB
    car_stats = CarStats(temp, dist, speed, line)
    db.session.add(car_stats)
    db.session.commit()


def get_car_stats():
    # Retrieve the latest stats from the DB
    data = db.session.query(CarStats).order_by('id').all()

    # Latest entry data 
    latest_entry = data[-1]
    current_speed = latest_entry.speed
    current_temps = latest_entry.temp
    current_stats = {'current_speed': current_speed, 'current_temps': current_temps}

    # For tempature graph 
    temps_graph_stats = {}
    movement_placeholder = ""
    for item in data:
        movement_placeholder = item.time
        temps_graph_stats[movement_placeholder] = item.temp

    # For speed graph
    speed_graph_stats = {}
    movement_placeholder = ""
    for item in data:
        movement_placeholder = item.time
        speed_graph_stats[movement_placeholder] = item.speed

    # For rate of line detection graph 
    line_detect_graph_stats = {}
    movement_placeholder = ""
    for item in data:
        movement_placeholder = item.time
        line_detect_graph_stats[movement_placeholder] = item.line    

    # Line detection count graph 
    line_count_graph_stats = {}
    true_count = 0
    false_count = 0 
    for item in data:   
        if item.line == 1:
            true_count += 1 
        else:
            false_count += 1 
    line_count_graph_stats["true_count"] = true_count
    line_count_graph_stats["false_count"] = false_count  

    return current_stats, temps_graph_stats, speed_graph_stats, line_detect_graph_stats, line_count_graph_stats


def reset():
    # Remove all entires in the DB
    num_rows_deleted = db.session.query(CarStats).delete()
    db.session.commit()