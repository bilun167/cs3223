NBuffers = 9;

printf("Initializing buffer pool with %d pages\n", NBuffers);
InitBufferPool();
printf("Beginning tests...\n");
printBuffers();

GET_WRITE(0,18,'a');
printBuffers();
GET_WRITE(0,14,'b');
printBuffers();
GET_WRITE(0,7,'c');
printBuffers();
GET_WRITE(0,12,'d');
printBuffers();
GET_WRITE(0,6,'e');
printBuffers();
GET_WRITE(0,3,'f');
printBuffers();
GET_WRITE_PIN(0,17,'g',true);
printBuffers();
GET_WRITE_PIN(0,12,'h',true);
printBuffers();
unpinPage(0,12);
GET_WRITE(0,17,'i');
printBuffers();
GET_WRITE(0,7,'j');
printBuffers();
GET_WRITE(0,0,'k');
printBuffers();
GET_WRITE(0,13,'l');
printBuffers();
GET_WRITE(0,10,'m');
printBuffers();
GET_WRITE(0,16,'n');
printBuffers();
GET_WRITE(0,2,'o');
printBuffers();
GET_WRITE(0,5,'p');
printBuffers();
GET_WRITE(0,2,'q');
printBuffers();
GET_WRITE(0,10,'r');
printBuffers();
GET_WRITE(0,6,'s');
printBuffers();
GET_WRITE(0,19,'t');
printBuffers();
GET_WRITE_PIN(0,0,'u',true);
printBuffers();
GET_WRITE(0,16,'v');
printBuffers();
unpinPage(0,0);
GET_WRITE(0,4,'w');
printBuffers();
GET_WRITE_PIN(0,4,'x',true);
printBuffers();
GET_WRITE(0,2,'y');
printBuffers();
GET_WRITE(0,19,'a');
printBuffers();
GET_WRITE(0,15,'b');
printBuffers();
GET_WRITE(0,6,'c');
printBuffers();
GET_WRITE(0,8,'d');
printBuffers();
GET_WRITE(0,7,'e');
printBuffers();
GET_WRITE(0,6,'f');
printBuffers();
GET_WRITE_PIN(0,0,'g',true);
printBuffers();
GET_WRITE(0,10,'h');
printBuffers();
unpinPage(0,17);
GET_WRITE(0,8,'i');
printBuffers();
GET_WRITE(0,13,'j');
printBuffers();
unpinPage(0,4);
GET_WRITE(0,0,'k');
printBuffers();
GET_WRITE(0,19,'l');
printBuffers();
GET_WRITE(0,20,'m');
printBuffers();
GET_WRITE(0,17,'n');
printBuffers();
GET_WRITE(0,8,'o');
printBuffers();
GET_WRITE(0,19,'p');
printBuffers();
GET_WRITE_PIN(0,11,'q',true);
printBuffers();
GET_WRITE(0,19,'r');
printBuffers();
GET_WRITE(0,16,'s');
printBuffers();
unpinPage(0,0);
GET_WRITE(0,16,'t');
printBuffers();
GET_WRITE(0,2,'u');
printBuffers();
GET_WRITE(0,3,'v');
printBuffers();
GET_WRITE(0,15,'w');
printBuffers();
GET_WRITE(0,3,'x');
printBuffers();
GET_WRITE_PIN(0,15,'y',true);
printBuffers();
unpinPage(0,15);
GET_WRITE(0,6,'a');
printBuffers();
GET_WRITE(0,5,'b');
printBuffers();
GET_WRITE(0,13,'c');
printBuffers();
GET_WRITE(0,16,'d');
printBuffers();
GET_WRITE(0,11,'e');
printBuffers();
GET_WRITE(0,12,'f');
printBuffers();
GET_WRITE(0,8,'g');
printBuffers();
GET_WRITE(0,18,'h');
printBuffers();
GET_WRITE(0,6,'i');
printBuffers();
GET_WRITE(0,20,'j');
printBuffers();
GET_WRITE(0,18,'k');
printBuffers();
GET_WRITE(0,1,'l');
printBuffers();
GET_WRITE_PIN(0,15,'m',true);
printBuffers();
GET_WRITE(0,12,'n');
printBuffers();
GET_WRITE(0,1,'o');
printBuffers();
GET_WRITE(0,13,'p');
printBuffers();
GET_WRITE(0,2,'q');
printBuffers();
GET_WRITE(0,13,'r');
printBuffers();
GET_WRITE(0,19,'s');
printBuffers();
unpinPage(0,11);
unpinPage(0,15);
GET_WRITE(0,4,'t');
printBuffers();
GET_WRITE(0,5,'u');
printBuffers();
GET_WRITE(0,16,'v');
printBuffers();
GET_WRITE(0,5,'w');
printBuffers();
GET_WRITE(0,13,'x');
printBuffers();
GET_WRITE(0,12,'y');
printBuffers();
GET_WRITE(0,1,'a');
printBuffers();
GET_WRITE(0,12,'b');
printBuffers();
GET_WRITE(0,6,'c');
printBuffers();
GET_WRITE(0,9,'d');
printBuffers();
GET_WRITE(0,20,'e');
printBuffers();
GET_WRITE(0,11,'f');
printBuffers();
GET_WRITE(0,19,'g');
printBuffers();
GET_WRITE(0,12,'h');
printBuffers();
GET_WRITE(0,6,'i');
printBuffers();
GET_WRITE(0,8,'j');
printBuffers();
GET_WRITE(0,5,'k');
printBuffers();
GET_WRITE(0,4,'l');
printBuffers();
GET_WRITE(0,1,'m');
printBuffers();
GET_WRITE(0,16,'n');
printBuffers();
GET_WRITE(0,15,'o');
printBuffers();
GET_WRITE(0,13,'p');
printBuffers();
GET_WRITE(0,13,'q');
printBuffers();
GET_WRITE(0,8,'r');
printBuffers();
GET_WRITE(0,0,'s');
printBuffers();
GET_WRITE(0,10,'t');
printBuffers();
GET_WRITE(0,7,'u');
printBuffers();
GET_WRITE(0,12,'v');
printBuffers();
GET_WRITE_PIN(0,7,'w',true);
printBuffers();
unpinPage(0,7);
GET_WRITE(0,11,'x');
printBuffers();
GET_WRITE(0,0,'y');
printBuffers();
GET_WRITE(0,19,'a');
printBuffers();
GET_WRITE_PIN(0,5,'b',true);
printBuffers();
GET_WRITE(0,4,'c');
printBuffers();
GET_WRITE(0,8,'d');
printBuffers();
GET_WRITE(0,4,'e');
printBuffers();
GET_WRITE_PIN(0,11,'f',true);
printBuffers();
GET_WRITE(0,15,'g');
printBuffers();
GET_WRITE(0,2,'h');
printBuffers();
GET_WRITE(0,2,'i');
printBuffers();
unpinPage(0,5);
GET_WRITE(0,1,'j');
printBuffers();
GET_WRITE(0,11,'k');
printBuffers();
unpinPage(0,11);
GET_WRITE(0,1,'l');
printBuffers();
GET_WRITE(0,17,'m');
printBuffers();
GET_WRITE(0,3,'n');
printBuffers();
GET_WRITE(0,20,'o');
printBuffers();
GET_WRITE(0,19,'p');
printBuffers();
GET_WRITE(0,14,'q');
printBuffers();
GET_WRITE(0,6,'r');
printBuffers();
GET_WRITE(0,15,'s');
printBuffers();
GET_WRITE(0,16,'t');
printBuffers();
GET_WRITE(0,17,'u');
printBuffers();
GET_WRITE(0,4,'v');
printBuffers();
GET_WRITE(0,11,'w');
printBuffers();
GET_WRITE(0,17,'x');
printBuffers();
GET_WRITE(0,9,'y');
printBuffers();
GET_WRITE(0,16,'a');
printBuffers();
GET_WRITE(0,9,'b');
printBuffers();
GET_WRITE(0,3,'c');
printBuffers();
GET_WRITE(0,13,'d');
printBuffers();
GET_WRITE(0,2,'e');
printBuffers();
GET_WRITE(0,19,'f');
printBuffers();
GET_WRITE_PIN(0,1,'g',true);
printBuffers();
GET_WRITE(0,18,'h');
printBuffers();
unpinPage(0,1);
GET_WRITE(0,7,'i');
printBuffers();
GET_WRITE(0,9,'j');
printBuffers();
GET_WRITE(0,11,'k');
printBuffers();
GET_WRITE_PIN(0,1,'l',true);
printBuffers();
unpinPage(0,1);
GET_WRITE(0,6,'m');
printBuffers();
GET_WRITE(0,9,'n');
printBuffers();
GET_WRITE(0,1,'o');
printBuffers();
GET_WRITE(0,17,'p');
printBuffers();
GET_WRITE_PIN(0,16,'q',true);
printBuffers();
GET_WRITE(0,19,'r');
printBuffers();
GET_WRITE(0,0,'s');
printBuffers();
GET_WRITE(0,8,'t');
printBuffers();
GET_WRITE(0,12,'u');
printBuffers();
GET_WRITE(0,11,'v');
printBuffers();
GET_WRITE(0,9,'w');
printBuffers();
GET_WRITE(0,8,'x');
printBuffers();
GET_WRITE(0,2,'y');
printBuffers();
GET_WRITE(0,20,'a');
printBuffers();
GET_WRITE(0,17,'b');
printBuffers();
GET_WRITE(0,14,'c');
printBuffers();
GET_WRITE(0,3,'d');
printBuffers();
unpinPage(0,16);
GET_WRITE_PIN(0,20,'e',true);
printBuffers();
GET_WRITE(0,20,'f');
printBuffers();
GET_WRITE(0,2,'g');
printBuffers();
GET_WRITE(0,10,'h');
printBuffers();
GET_WRITE(0,16,'i');
printBuffers();
GET_WRITE(0,1,'j');
printBuffers();
GET_WRITE(0,19,'k');
printBuffers();
GET_WRITE(0,6,'l');
printBuffers();
GET_WRITE(0,17,'m');
printBuffers();
GET_WRITE(0,2,'n');
printBuffers();
GET_WRITE(0,15,'o');
printBuffers();
GET_WRITE(0,15,'p');
printBuffers();
GET_WRITE(0,2,'q');
printBuffers();
GET_WRITE(0,0,'r');
printBuffers();
GET_WRITE(0,8,'s');
printBuffers();
GET_WRITE(0,11,'t');
printBuffers();
GET_WRITE(0,8,'u');
printBuffers();
GET_WRITE(0,12,'v');
printBuffers();
GET_WRITE(0,15,'w');
printBuffers();
GET_WRITE(0,12,'x');
printBuffers();
GET_WRITE(0,3,'y');
printBuffers();
unpinPage(0,20);
GET_WRITE(0,10,'a');
printBuffers();
GET_WRITE_PIN(0,0,'b',true);
printBuffers();
GET_WRITE(0,16,'c');
printBuffers();
GET_WRITE(0,7,'d');
printBuffers();
unpinPage(0,0);
GET_WRITE_PIN(0,7,'e',true);
printBuffers();
GET_WRITE(0,4,'f');
printBuffers();
GET_WRITE(0,9,'g');
printBuffers();
GET_WRITE(0,5,'h');
printBuffers();
GET_WRITE(0,8,'i');
printBuffers();
unpinPage(0,7);
GET_WRITE(0,4,'j');
printBuffers();
GET_WRITE_PIN(0,19,'k',true);
printBuffers();
GET_WRITE(0,2,'l');
printBuffers();
unpinPage(0,19);
GET_WRITE(0,8,'m');
printBuffers();
GET_WRITE(0,11,'n');
printBuffers();
GET_WRITE(0,18,'o');
printBuffers();
GET_WRITE(0,10,'p');
printBuffers();
GET_WRITE(0,6,'q');
printBuffers();
GET_WRITE_PIN(0,0,'r',true);
printBuffers();
GET_WRITE(0,17,'s');
printBuffers();
GET_WRITE(0,3,'t');
printBuffers();
GET_WRITE(0,1,'u');
printBuffers();
GET_WRITE(0,15,'v');
printBuffers();
GET_WRITE(0,15,'w');
printBuffers();
GET_WRITE(0,13,'x');
printBuffers();
GET_WRITE(0,9,'y');
printBuffers();
