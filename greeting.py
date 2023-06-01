import greeting_ext
import pickle

class HelloWorld(greeting_ext.Greeting):
    def __init__(self, country):
        self.country = country
        super().__init__()

    def greet(self):
        print(f"Hello {self.country}")

    def __getinitargs__(self):
        return (self.country,)

hw = HelloWorld("California")
hw.greet()
print(f"{getattr(hw, '__getstate__', None)=}")
print(f"{hw.__dict__=}")
pstr = pickle.dumps(hw)
hw = pickle.loads(pstr)
hw.greet()
