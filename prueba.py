import requests

from bs4 import BeautifulSoup

url='https://nach.pythonanywhere.com/?id=Nacho'
response = requests.get(url)

if response.status_code == 200:
    soup = BeautifulSoup(response.content, "html.parser")
    h1_element = soup.findAll("h1")
    print(h1_element)
    # Aquí puedes hacer lo que quieras con el contenido HTML obtenido, por ejemplo, puedes analizarlo con BeautifulSoup para extraer información específica de la página
else:
    print(f"La solicitud a {url} falló con el código de estado {response.status_code}.")