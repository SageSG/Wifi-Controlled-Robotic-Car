from webportal import create_webportal
from flask import Flask
import jyserver.Flask as jsf

app = create_webportal()

if __name__ == "__main__":
    # app.run(host="192.168.10.139",port="80",debug=True)
    app.run(debug=True)
