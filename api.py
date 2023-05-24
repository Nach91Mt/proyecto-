import json
from flask import Flask ,request, render_template,jsonify

app =Flask(__name__)
datos={}
ilu=0
pro=0
led=0
color='0xFF0000'
datos['ilu']=0
datos['pro']=0
datos['leds']=0
datos['color']='0xFF0000'
@app.route('/')

def api():
    #recogemos los datos introducidos por la app del movil
    ilu=request.args.get('ilu')  
    pro=request.args.get('pro')
    id= request.args.get('id')
    led=request.args.get('leds')
    color=request.args.get('color')
    #guardamos los datos introducidos por la app
    if ilu != None :
        datos['ilu']=ilu
    if pro != None :
        datos['pro']=pro
    if led != None :
        datos['leds']=led
    if color!=None:
        datos['color']=color
    if id == "Nacho":
        return render_template('index.html',datos=datos)
    else:
        return "<h1 >Usuario incorrecto</h1>"
@app.route("/json")
def data():
    return jsonify(datos)
if __name__ =='__main__':
    app.run(debug=True)