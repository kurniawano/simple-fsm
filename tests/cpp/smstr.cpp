#include <iostream>
#include "sm.hpp"
#include <string>
#include <boost/tuple/tuple.hpp>

class Switch: public SM<std::string,std::string,std::string>{
  private:
    std::string *nextState, *output;
  public:
    Switch() { startState = new std::string("OFF");};
    ~Switch(){delete nextState; };
    boost::tuple<std::string*,std::string*> getNextValues(std::string *s,std::string *i)
    {
      if (*state=="OFF" && *i=="P")
        nextState = new std::string("ON");
      else if(*state=="ON" && *i=="P")
        nextState = new std::string("OFF");
      else
        nextState=state;
      output=nextState;
      return boost::tuple<std::string*,std::string*>(nextState,output);
    };
};

int main()
{
  Switch *test = new Switch();
  std::string *pressed = new std::string("P");
  std::string *notpressed = new std::string("NP");
  std::list<std::string*> inps;
  inps.push_back(pressed);
  inps.push_back(pressed);
  inps.push_back(pressed);
  inps.push_back(notpressed);
  inps.push_back(pressed);
  std::string *startState=test->getStartState();
  std::cout<<"Start State: "<<*startState<<"\n";
  std::list<std::string*> myouts=test->transduce(inps);
  std::cout<<"Inputs:\n";
  for(std::list<std::string*>::iterator it=inps.begin(); it!=inps.end(); ++it)
  {
    std::cout<<**it<<"\n";
  }
  
  std::cout<<"Output:\n";
  for(std::list<std::string*>::iterator it=myouts.begin(); it!=myouts.end(); ++it)
  {
    std::cout<<**it<<"\n";
  }

  delete test;
  return 0;
}
