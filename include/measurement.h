#include <fstream>
#include <cmath>
#include <iostream>
#include <vector>
#include "electron.h"

#ifdef BOOST_IT
#include <boost/python.hpp>
#endif

using namespace std;

#ifdef BOOST_IT
using namespace boost::python;
#endif

class Measurement{
 public:

  Measurement(std::string){};
  Measurement(double, double);
  Measurement(double, double, double);

  void findMomentum();
  double getMomentum(){return momentum;};

  void setPrecision(double prec){precision = prec;};

  void setVerbose(bool val=true){verbose = val;}
  
 private:

  double kink;
  double momentum;
  double current;

  double zrange;
  
  double precision;
  
  double angleIn;
  double angleOut;

  double zIn;
  double zOut;

  bool haveMomentum;

  bool verbose;


};

#ifdef BOOST_IT

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(setVerboseOverloads, setVerbose, 0, 1)

BOOST_PYTHON_MODULE(measurement)
{

  class_<Measurement>("Measurement", init<std::string>())
    .def(init<double,double>())
    .def("findMomentum", &Measurement::findMomentum)
    .def("getMomentum", &Measurement::getMomentum)
    .def("setPrecision", &Measurement::setPrecision)
    .def("setVerbose", &Measurement::setVerbose, setVerboseOverloads())
    ;

}
#endif
