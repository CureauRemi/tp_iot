import serial
from flask import Flask, jsonify, request
app = Flask(__name__)

# Connexion avec l'arduino
try:
	serialArduino = serial.Serial('/dev/ttyACM0', 9600)
except serial.serialutil.SerialException:
	serialArduino = None

# Récupération de la température
# retour en json
@app.route('/api/sean_paul', methods=['GET'])
def get_sean_paul():
	try:
		serialArduino = serial.Serial('/dev/ttyACM0', 9600)
	except serial.serialutil.SerialException:
		serialArduino = None

	if serialArduino is not None:
		return jsonify(status="True",
		result = {"result" : serialArduino.readline() })
	else:
		return jsonify(status="False")

# Inversion du clignotement de la LED ajouter en paramètre  type=true ou false pour changer ou non 
# le mode
# retour en json
@app.route('/api/reverse', methods=['GET'])
def get_reverse():
	if serialArduino is not None:
		type = request.args.get('type')
		if type is not None:
			if type == 'true':
				serialArduino.write(True)
			else :
				serialArduino.write(False)
			return jsonify(status="True")
		else:
			return jsonify(status="False")
	else:
		return jsonify(status="False")
