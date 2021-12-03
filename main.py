from webportal import create_webportal
from flask import Flask
import jyserver.Flask as jsf

app = create_webportal()

if __name__ == "__main__":
    # app.run(host="192.168.10.139", port="80", debug=True)
    # app.run(host="192.168.10.139",port="80",debug=True,ssl_context=("Certificates/server-signed-cert.pem","Certificates/server-key-unencrypted.pem"))
    app.run(host="192.168.1.7",port="7000",debug=True,ssl_context=("Certificates/server-signed-cert.pem","Certificates/server-key-unencrypted.pem"))    # app.run(host="192.168.10.139",port="80",debug=True,ssl_context=("Certificates/server-signed-cert.pem","Certificates/server-key-unencrypted.pem"))