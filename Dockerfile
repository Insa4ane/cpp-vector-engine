FROM python:3.12-slim

RUN apt-get update && apt-get install -y \
    g++ \
    python3-dev \
    && rm -rf /var/lib/apt/lists/*
WORKDIR /app
COPY Model/requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt
COPY . /app
WORKDIR /app/Database/src/Network
RUN g++ -std=c++17 -Wno-attributes Server/server_main.cpp Server/Server.cpp Socket.cpp ../Database/db.cpp -o serwer $(python3 -m pybind11 --includes) $(python3-config --cflags --embed) $(python3-config --ldflags --embed)
RUN g++ -std=c++17 Client/client_main.cpp Client/Client.cpp Socket.cpp -o klient
EXPOSE 8080

CMD ["./serwer"]