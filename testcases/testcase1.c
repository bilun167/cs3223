NBuffers = 3;

printf("Initializing buffer pool with %d pages\n", NBuffers);
InitBufferPool();
printf("Beginning tests...\n");
printBuffers();

GET_WRITE(0,6,'a');
printBuffers();
GET_WRITE(0,1,'b');
printBuffers();
GET_WRITE_PIN(0,3,'c',true);
printBuffers();
GET_WRITE(0,6,'d');
printBuffers();
GET_WRITE(0,13,'e');
printBuffers();
GET_WRITE(0,16,'f');
printBuffers();
GET_WRITE(0,15,'g');
printBuffers();
GET_WRITE(0,12,'h');
printBuffers();
GET_WRITE(0,10,'i');
printBuffers();
GET_WRITE_PIN(0,5,'j',true);
printBuffers();
GET_WRITE(0,11,'k');
printBuffers();
GET_WRITE(0,5,'l');
printBuffers();
GET_WRITE(0,6,'m');
printBuffers();
GET_WRITE(0,7,'n');
printBuffers();
GET_WRITE(0,16,'o');
printBuffers();
GET_WRITE(0,16,'p');
printBuffers();
GET_WRITE(0,20,'q');
printBuffers();
GET_WRITE(0,14,'r');
printBuffers();
GET_WRITE(0,10,'s');
printBuffers();
GET_WRITE(0,8,'t');
printBuffers();
GET_WRITE(0,13,'u');
printBuffers();
unpinPage(0,3);
GET_WRITE(0,2,'v');
printBuffers();
GET_WRITE_PIN(0,19,'w',true);
printBuffers();
GET_WRITE(0,6,'x');
printBuffers();
GET_WRITE(0,0,'y');
printBuffers();
GET_WRITE(0,18,'a');
printBuffers();
GET_WRITE(0,9,'b');
printBuffers();
unpinPage(0,19);
GET_WRITE_PIN(0,2,'c',true);
printBuffers();
GET_WRITE(0,18,'d');
printBuffers();
GET_WRITE(0,12,'e');
printBuffers();
unpinPage(0,5);
GET_WRITE(0,3,'f');
printBuffers();
GET_WRITE(0,1,'g');
printBuffers();
GET_WRITE_PIN(0,11,'h',true);
printBuffers();
GET_WRITE(0,10,'i');
printBuffers();
GET_WRITE(0,4,'j');
printBuffers();
GET_WRITE(0,17,'k');
printBuffers();
GET_WRITE(0,1,'l');
printBuffers();
GET_WRITE(0,5,'m');
printBuffers();
GET_WRITE(0,5,'n');
printBuffers();
GET_WRITE(0,6,'o');
printBuffers();
GET_WRITE(0,1,'p');
printBuffers();
GET_WRITE(0,8,'q');
printBuffers();
GET_WRITE(0,4,'r');
printBuffers();
GET_WRITE(0,11,'s');
printBuffers();
GET_WRITE(0,20,'t');
printBuffers();
GET_WRITE(0,16,'u');
printBuffers();
GET_WRITE(0,14,'v');
printBuffers();
GET_WRITE(0,13,'w');
printBuffers();
GET_WRITE(0,5,'x');
printBuffers();
unpinPage(0,11);
GET_WRITE(0,8,'y');
printBuffers();
GET_WRITE(0,4,'a');
printBuffers();
GET_WRITE(0,12,'b');
printBuffers();
GET_WRITE(0,7,'c');
printBuffers();
GET_WRITE_PIN(0,13,'d',true);
printBuffers();
GET_WRITE(0,8,'e');
printBuffers();
GET_WRITE(0,3,'f');
printBuffers();
GET_WRITE(0,18,'g');
printBuffers();
GET_WRITE(0,1,'h');
printBuffers();
GET_WRITE(0,19,'i');
printBuffers();
GET_WRITE(0,5,'j');
printBuffers();
GET_WRITE(0,14,'k');
printBuffers();
GET_WRITE(0,17,'l');
printBuffers();
GET_WRITE(0,15,'m');
printBuffers();
GET_WRITE(0,6,'n');
printBuffers();
unpinPage(0,13);
GET_WRITE(0,17,'o');
printBuffers();
unpinPage(0,2);
GET_WRITE(0,14,'p');
printBuffers();
GET_WRITE(0,15,'q');
printBuffers();
GET_WRITE(0,6,'r');
printBuffers();
GET_WRITE_PIN(0,13,'s',true);
printBuffers();
GET_WRITE(0,2,'t');
printBuffers();
GET_WRITE_PIN(0,19,'u',true);
printBuffers();
GET_WRITE(0,11,'v');
printBuffers();
unpinPage(0,13);
GET_WRITE(0,14,'w');
printBuffers();
unpinPage(0,19);
GET_WRITE(0,17,'x');
printBuffers();
GET_WRITE(0,5,'y');
printBuffers();
GET_WRITE_PIN(0,6,'a',true);
printBuffers();
GET_WRITE(0,8,'b');
printBuffers();
GET_WRITE(0,8,'c');
printBuffers();
GET_WRITE_PIN(0,1,'d',true);
printBuffers();
GET_WRITE(0,17,'e');
printBuffers();
GET_WRITE(0,4,'f');
printBuffers();
unpinPage(0,6);
GET_WRITE(0,4,'g');
printBuffers();
GET_WRITE(0,18,'h');
printBuffers();
unpinPage(0,1);
GET_WRITE_PIN(0,9,'i',true);
printBuffers();
GET_WRITE_PIN(0,3,'j',true);
printBuffers();
unpinPage(0,9);
GET_WRITE(0,17,'k');
printBuffers();
GET_WRITE(0,2,'l');
printBuffers();
GET_WRITE_PIN(0,11,'m',true);
printBuffers();
GET_WRITE(0,5,'n');
printBuffers();
unpinPage(0,3);
GET_WRITE_PIN(0,1,'o',true);
printBuffers();
GET_WRITE(0,0,'p');
printBuffers();
unpinPage(0,1);
GET_WRITE(0,13,'q');
printBuffers();
GET_WRITE_PIN(0,16,'r',true);
printBuffers();
GET_WRITE(0,11,'s');
printBuffers();
unpinPage(0,11);
GET_WRITE(0,16,'t');
printBuffers();
GET_WRITE(0,9,'u');
printBuffers();
GET_WRITE_PIN(0,7,'v',true);
printBuffers();
GET_WRITE(0,13,'w');
printBuffers();
GET_WRITE(0,20,'x');
printBuffers();
GET_WRITE(0,7,'y');
printBuffers();
unpinPage(0,16);
GET_WRITE(0,8,'a');
printBuffers();
unpinPage(0,7);
GET_WRITE(0,11,'b');
printBuffers();
GET_WRITE_PIN(0,15,'c',true);
printBuffers();
GET_WRITE(0,4,'d');
printBuffers();
GET_WRITE(0,1,'e');
printBuffers();
GET_WRITE(0,4,'f');
printBuffers();
GET_WRITE(0,10,'g');
printBuffers();
GET_WRITE(0,20,'h');
printBuffers();
GET_WRITE(0,9,'i');
printBuffers();
unpinPage(0,15);
GET_WRITE(0,1,'j');
printBuffers();
GET_WRITE_PIN(0,1,'k',true);
printBuffers();
GET_WRITE_PIN(0,3,'l',true);
printBuffers();
GET_WRITE(0,12,'m');
printBuffers();
GET_WRITE(0,16,'n');
printBuffers();
GET_WRITE(0,6,'o');
printBuffers();
GET_WRITE(0,10,'p');
printBuffers();
unpinPage(0,3);
GET_WRITE(0,5,'q');
printBuffers();
GET_WRITE_PIN(0,18,'r',true);
printBuffers();
unpinPage(0,18);
GET_WRITE(0,12,'s');
printBuffers();
GET_WRITE_PIN(0,16,'t',true);
printBuffers();
GET_WRITE(0,14,'u');
printBuffers();
GET_WRITE(0,8,'v');
printBuffers();
GET_WRITE(0,4,'w');
printBuffers();
GET_WRITE(0,20,'x');
printBuffers();
GET_WRITE(0,7,'y');
printBuffers();
unpinPage(0,16);
GET_WRITE(0,18,'a');
printBuffers();
GET_WRITE(0,11,'b');
printBuffers();
GET_WRITE(0,7,'c');
printBuffers();
GET_WRITE(0,19,'d');
printBuffers();
GET_WRITE_PIN(0,3,'e',true);
printBuffers();
GET_WRITE(0,3,'f');
printBuffers();
GET_WRITE(0,17,'g');
printBuffers();
GET_WRITE(0,20,'h');
printBuffers();
GET_WRITE(0,9,'i');
printBuffers();
unpinPage(0,1);
GET_WRITE(0,0,'j');
printBuffers();
GET_WRITE(0,19,'k');
printBuffers();
unpinPage(0,3);
GET_WRITE(0,17,'l');
printBuffers();
GET_WRITE_PIN(0,14,'m',true);
printBuffers();
GET_WRITE(0,5,'n');
printBuffers();
GET_WRITE(0,10,'o');
printBuffers();
GET_WRITE(0,5,'p');
printBuffers();
GET_WRITE_PIN(0,5,'q',true);
printBuffers();
unpinPage(0,5);
GET_WRITE(0,4,'r');
printBuffers();
GET_WRITE_PIN(0,10,'s',true);
printBuffers();
unpinPage(0,14);
GET_WRITE(0,9,'t');
printBuffers();
GET_WRITE_PIN(0,2,'u',true);
printBuffers();
GET_WRITE(0,5,'v');
printBuffers();
GET_WRITE(0,14,'w');
printBuffers();
GET_WRITE(0,9,'x');
printBuffers();
GET_WRITE(0,12,'y');
printBuffers();
GET_WRITE(0,2,'a');
printBuffers();
unpinPage(0,2);
GET_WRITE_PIN(0,13,'b',true);
printBuffers();
GET_WRITE(0,3,'c');
printBuffers();
GET_WRITE(0,8,'d');
printBuffers();
unpinPage(0,10);
unpinPage(0,13);
GET_WRITE_PIN(0,17,'e',true);
printBuffers();
GET_WRITE_PIN(0,11,'f',true);
printBuffers();
unpinPage(0,11);
GET_WRITE_PIN(0,1,'g',true);
printBuffers();
GET_WRITE(0,10,'h');
printBuffers();
unpinPage(0,17);
GET_WRITE(0,10,'i');
printBuffers();
GET_WRITE(0,10,'j');
printBuffers();
GET_WRITE_PIN(0,18,'k',true);
printBuffers();
GET_WRITE(0,15,'l');
printBuffers();
GET_WRITE(0,10,'m');
printBuffers();
GET_WRITE(0,15,'n');
printBuffers();
GET_WRITE(0,20,'o');
printBuffers();
GET_WRITE(0,13,'p');
printBuffers();
GET_WRITE(0,2,'q');
printBuffers();
GET_WRITE(0,7,'r');
printBuffers();
GET_WRITE(0,19,'s');
printBuffers();
GET_WRITE(0,0,'t');
printBuffers();
GET_WRITE(0,3,'u');
printBuffers();
GET_WRITE(0,6,'v');
printBuffers();
GET_WRITE(0,3,'w');
printBuffers();
GET_WRITE(0,2,'x');
printBuffers();
GET_WRITE(0,3,'y');
printBuffers();
GET_WRITE(0,14,'a');
printBuffers();
GET_WRITE(0,9,'b');
printBuffers();
GET_WRITE(0,14,'c');
printBuffers();
GET_WRITE(0,9,'d');
printBuffers();
GET_WRITE(0,12,'e');
printBuffers();
GET_WRITE(0,8,'f');
printBuffers();
GET_WRITE(0,20,'g');
printBuffers();
GET_WRITE(0,16,'h');
printBuffers();
GET_WRITE(0,1,'i');
printBuffers();
GET_WRITE(0,19,'j');
printBuffers();
GET_WRITE(0,12,'k');
printBuffers();
GET_WRITE(0,10,'l');
printBuffers();
unpinPage(0,1);
GET_WRITE(0,13,'m');
printBuffers();
unpinPage(0,18);
GET_WRITE(0,12,'n');
printBuffers();
GET_WRITE_PIN(0,15,'o',true);
printBuffers();
GET_WRITE_PIN(0,0,'p',true);
printBuffers();
GET_WRITE(0,16,'q');
printBuffers();
GET_WRITE(0,10,'r');
printBuffers();
GET_WRITE(0,18,'s');
printBuffers();
GET_WRITE(0,20,'t');
printBuffers();
GET_WRITE(0,12,'u');
printBuffers();
GET_WRITE(0,8,'v');
printBuffers();
GET_WRITE(0,16,'w');
printBuffers();
unpinPage(0,15);
GET_WRITE_PIN(0,20,'x',true);
printBuffers();
GET_WRITE(0,9,'y');
printBuffers();
