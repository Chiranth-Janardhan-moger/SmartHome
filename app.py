from flask import Flask, request, jsonify, render_template
from flask_cors import CORS

app = Flask(__name__)
CORS(app)  # Enable CORS for all routes

# Global variable to store sensor data
sensor_data = {}



@app.route('/')
def index():
    return render_template('index.html')


# Route: Map page
@app.route('/map')
def map():
    return render_template('map.html', data=sensor_data)  # Pass data to HTML


# Route to handle sensor data sent from the Arduino/ESP32
@app.route('/sensor', methods=['POST'])
def handle_sensor_data():
    global sensor_data
    data = request.get_json()  # Parse the incoming JSON data
    print(data)  # Print data for debugging purposes
    sensor_data = data  # Store the data for later use
    return 'Data received', 200

# Route to return the sensor data in JSON format
@app.route('/data', methods=['GET'])
def get_sensor_data():
    global sensor_data
    if not sensor_data:
        return jsonify({'message': 'No data available'}), 404
    return jsonify(sensor_data), 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8000)  # Flask running on 192.168.1.102:8000
