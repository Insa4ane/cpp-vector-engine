from agent.vector_agent import VectorAgent

#you might run this file to check correctness of model 
def check():
     try: 
        agent=VectorAgent()
        test_vector = agent.text_to_vector("C++ 5")
        return f"Model has been download and everything is alright: Generate vector: {len(test_vector)}"
     except Exception as e:
         return f"Something's gone wrong. Problem is: {e}"


if __name__ == '__main__':
    result=check()
    print(result)
