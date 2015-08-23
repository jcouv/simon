# Simon
Simon game for Particle Photon with "Internet Button" shield.

To use this in your Internet Button project, here is the code to use in the Particle IDE. You will need to include the "InternetButton" and "Simon" libraries.

```
#include "InternetButton/InternetButton.h"
#include "Simon/Simon.h"

Simon s = Simon();

void setup() {
    s.setup();   
}

void loop() {
    s.loop();
}
```

More information at https://particle.hackster.io/Dumky/particle-photon-simon
