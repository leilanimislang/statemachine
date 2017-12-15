#include <iostream>

using namespace std;

class Machine
{
  class State *current;
  public:
    Machine();
    void setCurrent(State *s)
    {
        current = s;
    }
    void idle();
    void sensing();
    void processing();
};

class State
{
  public:
    virtual void idle(Machine *m)
    {
        cout << "   idle state \n";
    }
    virtual void sensing(Machine *m)
    {
        cout << "   sensing state. Preparing data. \n";
    }
    virtual void processing(Machine *m)
    {
        cout << "   processing state. Processing data. \n";
    }
};

void Machine::idle()
{
  current->idle(this);
}

void Machine::sensing()
{
  current->sensing(this);
}

void Machine::processing()
{
  current->processing(this);
}

class IDLE: public State
{
  public:
    IDLE()
    {
        cout << "   IDLE STATE. DO NOTHING. ";
    };
    ~IDLE()
    {

    };
    void sensing(Machine *m) {
        cout << "   going from IDLE to SENSING";
        //m->setCurrent(new SENSING());
        delete this;
    }
};

class SENSING: public State
{
  public:
    SENSING()
    {
        cout << "   SENSING STATE. PREPING DONE. ";
    };
    ~SENSING()
    {
        cout << "   Currently SENSING.\n";
    };
    void processing(Machine *m)
    {
        cout << "   going from SENSING to PROCESSING";
        //m->setCurrent(new PROCESSING());
        delete this;
    }
};

class PROCESSING: public State
{
  public:
    PROCESSING()
    {
        cout << "   PROCESSING STATE. PROCESSING DONE. ";
    };
    ~PROCESSING()
    {
        cout << "   Currently PROCESSING.\n";
    };
    void idle(Machine *m)
    {
        cout << "   going from PROCESSING to IDLE";
        //m->setCurrent(new IDLE());
        delete this;
    }
};

Machine::Machine()
{
  current = new IDLE();
  cout << '\n';
}

int main()
{
  void(Machine:: *ptrs[])() =
  {
    Machine::idle, Machine::sensing, Machine::processing
  };
  Machine fsm;
  int num;
  while (1)
  {
    cout << "Enter 0/1/2: ";
    cin >> num;
    (fsm.*ptrs[num])();
  }
}
