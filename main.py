from webportal import create_webportal

app = create_webportal()

if __name__ == "__main__":
    app.run(host="192.168.10.139",port="80",debug=True)
