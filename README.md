# Simon
Simon game for Particle Photon with "Internet Button" shield.

![Working game](https://hackster.imgix.net/uploads/cover_image/file/66545/IMG_1479.JPG?w=1600&h=1200&fit=crop&fm=jpg&s=7302fc96bb3cf34b1f39f8915fbdf099)

To use this in your Internet Button, start a new project in the Particle IDE, add the "InternetButton" and "Simon" libraries and copy the code below into your main file.

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
