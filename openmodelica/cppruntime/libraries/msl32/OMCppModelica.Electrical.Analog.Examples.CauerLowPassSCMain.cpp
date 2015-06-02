
#include <Core/ModelicaDefine.h>
#include <Core/Modelica.h>
#include <SimController/ISimController.h>




#ifdef USE_BOOST_THREAD
  #include <boost/thread.hpp>
  static long unsigned int getThreadNumber()
  {
     boost::hash<std::string> string_hash;
     return (long unsigned int)string_hash(boost::lexical_cast<std::string>(boost::this_thread::get_id()));
  }
#else
  static long unsigned int getThreadNumber()
  {
     return 0;
  }
#endif

#if defined(_MSC_VER) || defined(__MINGW32__)
#include <tchar.h>
int _tmain(int argc, const _TCHAR* argv[])
#else
int main(int argc, const char* argv[])
#endif
{
    // default program options
    std::map<std::string, std::string> opts;
    opts["-s"] = "0.0";
    opts["-e"] = "60.0";
    opts["-f"] = "0.04";
    opts["-v"] = "1500";
    opts["-y"] = "1e-06";
    opts["-i"] = "dassl";
    opts["-r"] = "/home/marcus/workspace/openmodelica/openmodelica/OMCompiler/build/lib/x86_64-linux-gnu/omc/cpp/";
    opts["-m"] = "/home/marcus/workspace/openmodelica/openmodelica/OpenModelica-testsuite/openmodelica/cppruntime/libraries/msl32/";
    opts["-R"] = "/home/marcus/workspace/openmodelica/openmodelica/OpenModelica-testsuite/openmodelica/cppruntime/libraries/msl32//Modelica.Electrical.Analog.Examples.CauerLowPassSC_res.mat";
    opts["-o"] = "mat";
    
    //no profiling used
    try
    {
          
          #ifdef RUNTIME_STATIC_LINKING
            boost::shared_ptr<OMCFactory>  _factory =  boost::shared_ptr<OMCFactory>(new StaticOMCFactory());
          #else
            boost::shared_ptr<OMCFactory>  _factory =  boost::shared_ptr<OMCFactory>(new OMCFactory());
          #endif
          //SimController to start simulation
          
          
          std::pair<boost::shared_ptr<ISimController>, SimSettings> simulation = _factory->createSimulation(argc, argv, opts);
          
          
          
          //create Modelica system
          boost::weak_ptr<ISimData> simData = simulation.first->LoadSimData("CauerLowPassSC");
          boost::weak_ptr<ISimVars> simVars = simulation.first->LoadSimVars("CauerLowPassSC",429,1,45,475,16,0);
          boost::weak_ptr<IMixedSystem> system = simulation.first->LoadSystem("OMCppModelica.Electrical.Analog.Examples.CauerLowPassSC.so","CauerLowPassSC");
          simulation.first->Start(simulation.second, "CauerLowPassSC");
          
          
          return 0;
          
    }
    catch(ModelicaSimulationError& ex)
    {
    
         std::cerr << "Simulation stopped with error in " << error_id_string(ex.getErrorID()) << ": "  << ex.what();
         return 1;
    }
}