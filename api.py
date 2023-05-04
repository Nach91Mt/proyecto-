from flask import Flask ,request, render_template

app =Flask(__name__)
datos={}
@app.route('/')
def api():
        #ejemplo http://127.0.0.1:5000/?id=Nacho&ilu=22
        #recogemos los datos introducidos por la app del movil
    ilu=request.args.get('ilu')  
    pro=request.args.get('pro')
    id= request.args.get('id')
    led=request.args.get('leds')

    #guardamos los datos introducidos por la app
    datos['ilu']=ilu
    datos['pro']=pro
    datos['leds']=led
    if id == "Nacho":
        return render_template('index.html',datos=datos)
    else:
        return "Usuario incorrecto"
if __name__ =='__main__':
    app.run(debug=True)