FROM python:3.8-slim-buster

WORKDIR /app

copy requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

COPY . .

CMD ["python","api.py","--host=0.0.0.0"]