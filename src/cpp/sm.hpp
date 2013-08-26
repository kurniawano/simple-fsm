#include <cstddef>
#include <iostream>
#include <list>
#include <boost/tuple/tuple.hpp>


/*!
* Generic superclass representing state machines. Don't instantiate this.
* Make a subclass with definitions for the following methods:
* - getNextValues: (state_t, inp_t) -> (state_t+1, output_t+1) or - getNextState: (state_t, inp_t) -> state_t+1
* - startState: state or startState() -> state
* optional:
* - done: (state) -> boolean (default always false)
* - legalInputs: list(inp)
*/
template<class SType, class IType, class OType>
class SM
{
  protected:
    SType *startState; /*! By default, startState is NULL*/
    SType *state;
  public:
    SM() : startState(NULL){}
    SType* getStartState(){ return startState; }
    virtual SType* getNextState(SType *state, IType *inp){}
    /*!
     * Default version for getNextValues(). If a subclass only defines
     * getNextState, then we assume that th eoutput of the machine is 
     * the same as its next state.
     */
    virtual boost::tuple<SType*, SType*> getNextValues(SType *state, IType *inp)
    {  
      SType *nextState = getNextState(state, inp);
      return boost::tuple<SType*,SType*>(nextState,nextState);
    }


    /*!
     * By default, machines don't terminate
     */
    bool done(SType *state){ return false;}

    /*!
     * Should only be used by transduce. Don't call this.
     */
    bool isDone(){ return done(state);}

    /*!
     * Call before providing input to a machine, or to reset it.
     * Sets state and arranges things.
     */
    void start()
    {
      state = getStartState();
    }
    
    /*! 
     * Execute one step of the machine by using input to get a result
     * then updating state.
     */
    OType* step(IType *inp)
    {
      boost::tuple<SType*, IType*> nv = this->getNextValues(state,inp);
      state = boost::get<0>(nv);

      return boost::get<1>(nv);
    }

    /*!
     * Start the machine fresh, and feed a sequence of values into
     * the machine, collecting the sequence of outputs
     */
    std::list<OType*> transduce(std::list<IType*> inps)
    {
      int n = inps.size();
      std::list<OType*> result;
      start();
      typename std::list<IType*>::iterator it=inps.begin();
      while(it!=inps.end() && !isDone())
      {
        result.push_back(step(*it));
        it++;
      }
      return result;
    }   
};
