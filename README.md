# C++ / Python Hybrid Vector Engine

A production-ready, hybrid vector database engine demonstrating the powerful integration of high-performance C++ backend architecture with advanced Python-based AI models.

## 🚀 Overview
This project showcases a custom TCP/IP socket-based server written in C++17 that communicates seamlessly with a Python environment using `pybind11`. It leverages the `Sentence-Transformers` library (all-MiniLM-L6-v2) to perform semantic vector searches using cosine similarity.

To counter the numerical limitations of standard NLP models, the system implements **Prompt Engineering**, wrapping raw data into full sentences before generating embeddings, significantly improving search accuracy.

## 🏗️ Architecture
- **Backend:** C++17 (Custom TCP Sockets, Command Parser, Core Logic)
- **AI Integration:** Python 3.12, `pybind11`, `Sentence-Transformers`
- **Math:** Cosine Similarity for Semantic Search
- **Infrastructure:** Fully containerized with Docker & Docker Compose

## 🛠️ How to Run (Docker)
The entire environment is containerized. You don't need to install Python, C++ compilers, or AI libraries on your local machine.

1. Clone the repository and navigate to the project directory.
2. Build and start the server:
   ```bash
   sudo docker compose up --build
   ```
3. In a new terminal window, connect to the running server using the dummy client:
    ```bash 
    sudo docker exec -it cpp-vector-server ./klient
    ```


## Usage Examples
Once connected via the client, you can add records and query the vector database:
```bash
ADD Jacek,C++,10
ADD Anna,C++,55
ADD Kasia,C++,40
```

Perform a semantic search (e.g., looking for a mid/senior C++ dev)
```bash
GET C++,50
```

STOP the client
```bash
STOP
```

