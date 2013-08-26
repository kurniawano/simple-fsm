#include <iostream>
#include "sm.hpp"
#include <boost/tuple/tuple.hpp>

class Switch: public SM<int,int,int>{
  private:
    int *nextState, *output;
  public:
    Switch() { startState = new int(0);};
    ~Switch(){delete nextState; };
    boost::tuple<int*,int*> getNextValues(int *s,int *i)
    {
      if (*state==0 && *i==1)
        nextState = new int(1);
      else if(*state==1 && *i==1)
        nextState = new int(0);
      else
        nextState=state;
      output=nextState;
      return boost::tuple<int*,int*>(nextState,output);
    };
};

int main()
{
  Switch *test = new Switch();
  int *pressed = new int(1);
  int *notpressed = new int(0);
  std::list<int*> inps;
  inps.push_back(pressed);
  inps.push_back(pressed);
  inps.push_back(pressed);
  inps.push_back(notpressed);
  inps.push_back(pressed);
  int *startState=test->getStartState();
  std::cout<<"Start State: "<<*startState<<"\n";
  std::list<int*> myouts=test->transduce(inps);
  std::cout<<"Inputs:\n";
  for(std::list<int*>::iterator it=inps.begin(); it!=inps.end(); ++it)
  {
    std::cout<<**it<<"\n";
  }
  
  std::cout<<"Output:\n";
  for(std::list<int*>::iterator it=myouts.begin(); it!=myouts.end(); ++it)
  {
    std::cout<<**it<<"\n";
  }

  delete test;
  return 0;
}
