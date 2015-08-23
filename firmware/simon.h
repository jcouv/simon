
#include "InternetButton/InternetButton.h"

class Simon {
 enum Position: int { Top = 0 , Right = 1, Bottom = 2, Left = 3, None = -1};
  
 public:

  Simon();

  void
    setup(),
    loop();
    
 private: 
    
  void 
    welcome(),
    demo(),
    ready(),
    setColor(),
    start(),
    generate(int size),
    show(),
    listenDown(),
    listenUp(),
    celebrate(),
    flash(Position p, bool timed, bool sound),
    unflash(),
    fail();

 public: 
  
  Position anyButtonOn();
  InternetButton b;

  Position *solution;
  int solutionSize;

  enum State: int { Welcome, Ready, Showing, ListeningDown, ListeningUp, CompleteSuccess, Failed };
  State state;

  int difficulty;
  int successMax;
  int successCount;
};
    
    
