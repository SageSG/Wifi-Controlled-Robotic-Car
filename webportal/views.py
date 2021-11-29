from flask import Blueprint
from flask import Flask, render_template
from webportal.models.carstats import get_car_stats
from webportal.models.carcommands import get_command_stats
from webportal.models.map import get_map


views = Blueprint('views', __name__)

@views.route('/')
def home():
    return render_template('home.html', title="Home Page")


@views.route("/maps")
def maps():
    return render_template('maps.html', title="Maps")


@views.route("/dashboard")
def dashboard():
    try:
        car_data = get_car_stats()
    except IndexError:
        car_data = [] 
    # command_data = get_command_stats()
    return render_template('dashboard.html', title="Dashboard", car_data=car_data)


@views.route("/terminal")
def terminal():
    def divide_chunks(l, n):
        # looping till length l
        for i in range(0, len(l), n): 
            yield l[i:i + n]

    n = 8 
    data = get_map()
    map_rows = list(divide_chunks(data.map_coordinates.split(","), n))
    print(map_rows)
    return render_template('terminal.html', title="Terminal", map=map_rows)


@views.route("/tutorials")
def tutorials():
    return render_template('tutorials.html', title="Tutorials")


@views.route("/robots.txt")
def robots():
    return render_template('robots.txt', title="Robots")
