# -*- coding: utf-8 -*-
from flask import Flask, render_template, jsonify
import json
import requests

app = Flask(__name__)
API_KEY = "9IAQFSILSKAZUNTC"
if API_KEY is None:
    mkr = "https://api.thingspeak.com/channels/1173906/feeds.json?api_key=PE1R3IX43BN54299&results=120&average=60"
else:
    mkr = "https://api.thingspeak.com/channels/1173906/feeds.json?api_key=PE1R3IX43BN54299&results=120&average=60" + API_KEY

@app.route("/", methods=['POST', 'GET'])
def hello():
    return "Hello World!"

@app.route('/dashboard/')
def dashboard():
    return render_template("dashboard.html")

@app.route('/send/')
def sending():
    response = requests.get(mkr)
    content = json.loads(response.content.decode('utf-8'))
    if (response.ok):
        try:
            print("acess ok")
        except:
            print("accessdenied")
    if response.status_code != 200:
        return jsonify({
            'status': 'error',
            'message': 'La requête à arduino a pas fonctionné'
        }), 500

    compt = 0
    data = []
    for prev in content["feeds"]:
        vari = prev['field1']
        var2 = prev['field2']
        temp = prev['field3']
        compt = compt + 1
        data.append([compt, vari, var2, temp])

    print(content)
    return jsonify({
        'status': 'ok',
        'data':data
    })

if __name__ == "__main__":
    app.run(debug=True)