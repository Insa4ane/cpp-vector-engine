from config.config import PATH
from sentence_transformers import SentenceTransformer

class VectorAgent():
    def __init__(self):
        self.model=SentenceTransformer('all-MiniLM-L6-v2', cache_folder=PATH)
    
    def text_to_vector(self, text: str)->list[float]:
        vector=self.model.encode(text)
        return vector.tolist()


    