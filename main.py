from webportal import create_webportal
from flask import Flask
import jyserver.Flask as jsf

app = create_webportal()

if __name__ == "__main__":
    app.run(host="localhost",port="7000",debug=True,ssl_context=("Certificates/server-signed-cert.pem","Certificates/server-key-unencrypted.pem"))