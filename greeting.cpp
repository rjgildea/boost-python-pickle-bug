#include <boost/python.hpp>

#include <string>

namespace greeting {

  class Greeting {
  public:
    virtual void greet() = 0;
  };

  /**
   * Wrapper class to allow python function to inherit
   */
  struct GreetingWrapper : Greeting, boost::python::wrapper<Greeting> {
    void greet() {
      this->get_override("greet")();
    }
  };

}

BOOST_PYTHON_MODULE(greeting_ext)
{
  using namespace boost::python;
  using namespace greeting;

  class_<GreetingWrapper, boost::noncopyable>("Greeting")
    .def("greet", pure_virtual(&Greeting::greet))
    .enable_pickling();
}
