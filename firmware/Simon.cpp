#include "Simon.h"
 
Simon::Simon(){

}

void Simon::setup() {
    b = InternetButton();
    solution = new Position[0];
    solutionSize = 0;

    state = Welcome;

    difficulty = 3;
    successMax = 0;
    successCount = 0;
    
    
    RGB.control(true);
    this.b.begin();
    this.b.allLedsOff();
}

void Simon::loop() {
    switch (state) { 
        case Welcome: 
            welcome();
            break;
        case Ready: 
            ready();
            break;
        case Showing:
            show();
            break;
        case ListeningDown:
            listenDown();
            break;
        case ListeningUp:
            listenUp();
            break;
        case CompleteSuccess:
            celebrate();
            break;
        case Failed:
            fail();
            break;
    }
}

void Simon::welcome() {
    b.playSong("C4,8,E4,8,G4,8,C5,8,G5,4");
    b.allLedsOn(0,20,20); 
    delay(500);
    b.allLedsOff();
    
    flash(Top, true, true);
    flash(Right, true, true);
    flash(Bottom, true, true);
    flash(Left, true, true);
    state = Ready;
}

void Simon::demo() {
      b.ledOn(11, 25, 0, 0);
            b.ledOn(1, 25, 0, 0);

            b.ledOn(2, 0, 0, 25);
            b.ledOn(3, 0, 0, 25);
            b.ledOn(4, 0, 0, 25);

            b.ledOn(5, 12, 12, 0);
            b.ledOn(6, 12, 12, 0);
            b.ledOn(7, 12, 12, 0);

            b.ledOn(8, 0, 25, 0);
            b.ledOn(9, 0, 25, 0);
            b.ledOn(10, 0, 25, 0);
    
    delay(10000);
}

void Simon::ready() {
    Position read = anyButtonOn();
    
    switch (read) {
        case None:
            return;
        case Top:
            difficulty = 4;
            break;
        case Right:
            difficulty = 9;
            break;
        case Bottom:
            difficulty = 14;
            break;
        case Left:
            difficulty = 29;
            break;
    }
    celebrate();
}

void Simon::setColor() {
    if (difficulty < 10) {
        RGB.color(255, 0, 0);
        return;    
    }
    if (difficulty < 15) { 
        RGB.color(120, 120, 0);
        return;
    }
    if (difficulty < 30) { 
        RGB.color(0, 255, 0);
        return;
    }
    
    RGB.color(0, 0, 255);
}

void Simon::start() {
    //b.allLedsOn(0,20,20); 
    //delay(500);
    //b.allLedsOff();
    
    successMax = 0;
        
    generate(difficulty);
    setColor();
    
    state = Showing;
}

void Simon::generate(int size) {
    solutionSize = size;
    solution = new Position[solutionSize];
    
    for (int i = 0; i < size; i++) {
        while(true) {
            Position next = (Position) random(4);
            
            if (i-2 >= 0 && next == solution[i-1] && next == solution[i-2]) {
                continue;
            }
            
            solution[i] = next;
            break;
        }
    }
}

void Simon::show() {
    for (int i = 0; i < successMax + 1; i++) {
        Position next = solution[i];
        flash(next, true, true);
        delay(100);
    }
    
    successCount = 0;
    state = ListeningDown;
}

void Simon::listenDown() {
    Position read = anyButtonOn();
    if (read == None) {
        return;
    }
    
    if (solution[successCount] == read) {
        flash(read, false, true);
        state = ListeningUp;
        return;
    }

    state = Failed;
}


void Simon::listenUp() {
    Position read = anyButtonOn();
    
    if (read == None) {
        unflash();
        
        successCount++;
        
        if (successCount > successMax) {
                if (successCount == solutionSize) {
                    state = CompleteSuccess;
                    return;
                }
    
            successMax++;
            
            delay(1000);
            state = Showing;
            return;
        }
        
      
        state = ListeningDown;
        return;
    }
    
     if (solution[successCount] != read) { 
         state = Failed;
         return;
     }
}

Position Simon::anyButtonOn() {
    if (b.buttonOn(1)) {
        return Top; 
    }
    if (b.buttonOn(2)) {
        return Right; 
    }
    if (b.buttonOn(3)) {
        return Bottom; 
    }
    if (b.buttonOn(4)) {
        return Left; 
    }
    return None;
}

void Simon::celebrate() {
    flash(Top, false, false);
    flash(Right, false, false);
    flash(Bottom, false, false);
    flash(Left, false, false);
    b.playSong("C4,8,E4,8,G4,8,C5,8,G5,4");
    
    //b.allLedsOn(0, 255, 0);
    delay(300);
    b.allLedsOff();
    
    delay(500);
    difficulty++;
    start();
}



void Simon::flash(Position p, bool timed, bool sound) {
    switch (p) {
        case Top:
            b.ledOn(11, 255, 0, 0);
            b.ledOn(1, 255, 0, 0);
            if (sound) { b.playNote("C4",4); }
            break;
        case Right:
            b.ledOn(2, 0, 0, 255);
            b.ledOn(3, 0, 0, 255);
            b.ledOn(4, 0, 0, 255);
            if (sound) { b.playNote("E4",4); }
            break;
        case Bottom:
            b.ledOn(5, 120, 120, 0);
            b.ledOn(6, 120, 120, 0);
            b.ledOn(7, 120, 120, 0);
            if (sound) { b.playNote("G4",4); }
            break;
        case Left:
            b.ledOn(8, 0, 255, 0);
            b.ledOn(9, 0, 255, 0);
            b.ledOn(10, 0, 255, 0);
            if (sound) { b.playNote("C5",4); }
            break;
        case None: 
            delay(100);
            return;
    }
    if (timed) {
        b.allLedsOff();
    }
}

void Simon::unflash() {
    // TODO: stop sound
    b.allLedsOff();
}

void Simon::fail() {
    flash(solution[successCount], false, false);
    b.playNote("C2",1);
    
    for( int a = 0; a < 3; a = a + 1 )
    {
        
        b.allLedsOn(255,0,0); 
        RGB.brightness(255);
        delay(500);
        b.allLedsOff();
        RGB.brightness(1);
        delay(500);
    }
   
    RGB.color(0, 0, 0);
    RGB.brightness(255);
    state = Welcome;
}

    
