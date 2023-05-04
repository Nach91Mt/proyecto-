from flask import Flask ,request, render_template

app =Flask(__name__)
datos={}
ilu=0
pro=0
led=0
datos['ilu']=0
datos['pro']=0
datos['leds']=0
@app.route('/')

def api():
    i=1
    if i < 2:
        print('yes')
        #ejemplo http://127.0.0.1:5000/?id=Nacho&ilu=22
        #recogemos los datos introducidos por la app del movil
    ilu=request.args.get('ilu')  
    pro=request.args.get('pro')
    id= request.args.get('id')
    led=request.args.get('leds')
    #guardamos los datos introducidos por la app
    if ilu != None :
        datos['ilu']=ilu
    if pro != None :
        datos['pro']=pro
    if led != None :
        datos['leds']=led
    
    if id == "Nacho":
        return render_template('index.html',datos=datos)
    else:
        return "<h1>Usuario incorrecto</h1>"
if __name__ =='__main__':
    app.run(debug=True)