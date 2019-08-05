//Get rid of wallPos1, wallPos2 etc
float wallPos[] = {100, 300, 500, 700};

if(wallLeftX < wallPos[pos] - 1000) {
   wallLeftX += speed2;
   wallRightX += speed2;
   if(wallLeftX >= wallPos[pos] - 1000) {
      pos = rand() % 4;
   }
} else {
   wallLeftX -= speed2;
   wallRightX -= speed2;
   if(wallLeftX <= wallPos[pos] - 1000) {
       pos = rand() % 4;
   }
} 
