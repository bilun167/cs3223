NBuffers = 14;

printf("Initializing buffer pool with %d pages\n", NBuffers);
InitBufferPool();
printf("Beginning tests...\n");
printBuffers();

GET_WRITE(0,4,'a');
printBuffers();
GET_WRITE(0,2,'b');
printBuffers();
GET_WRITE_PIN(0,12,'c',true);
printBuffers();
unpinPage(0,12);
GET_WRITE(0,20,'d');
printBuffers();
GET_WRITE(0,1,'e');
printBuffers();
GET_WRITE(0,6,'f');
printBuffers();
GET_WRITE(0,16,'g');
printBuffers();
GET_WRITE(0,19,'h');
printBuffers();
GET_WRITE_PIN(0,4,'i',true);
printBuffers();
GET_WRITE(0,16,'j');
printBuffers();
GET_WRITE(0,7,'k');
printBuffers();
GET_WRITE(0,5,'l');
printBuffers();
GET_WRITE(0,18,'m');
printBuffers();
GET_WRITE_PIN(0,13,'n',true);
printBuffers();
GET_WRITE_PIN(0,16,'o',true);
printBuffers();
unpinPage(0,13);
GET_WRITE_PIN(0,4,'p',true);
printBuffers();
GET_WRITE(0,6,'q');
printBuffers();
GET_WRITE(0,2,'r');
printBuffers();
GET_WRITE_PIN(0,6,'s',true);
printBuffers();
GET_WRITE_PIN(0,11,'t',true);
printBuffers();
unpinPage(0,4);
unpinPage(0,11);
GET_WRITE_PIN(0,13,'u',true);
printBuffers();
GET_WRITE(0,16,'v');
printBuffers();
GET_WRITE_PIN(0,1,'w',true);
printBuffers();
unpinPage(0,13);
GET_WRITE(0,7,'x');
printBuffers();
GET_WRITE(0,8,'y');
printBuffers();
unpinPage(0,1);
GET_WRITE(0,2,'a');
printBuffers();
GET_WRITE(0,2,'b');
printBuffers();
unpinPage(0,16);
unpinPage(0,6);
GET_WRITE_PIN(0,4,'c',true);
printBuffers();
GET_WRITE(0,2,'d');
printBuffers();
unpinPage(0,4);
GET_WRITE(0,1,'e');
printBuffers();
GET_WRITE(0,10,'f');
printBuffers();
GET_WRITE_PIN(0,4,'g',true);
printBuffers();
GET_WRITE(0,17,'h');
printBuffers();
GET_WRITE(0,0,'i');
printBuffers();
unpinPage(0,4);
GET_WRITE(0,2,'j');
printBuffers();
GET_WRITE(0,13,'k');
printBuffers();
GET_WRITE(0,11,'l');
printBuffers();
GET_WRITE(0,16,'m');
printBuffers();
GET_WRITE(0,10,'n');
printBuffers();
GET_WRITE(0,14,'o');
printBuffers();
GET_WRITE(0,18,'p');
printBuffers();
GET_WRITE(0,2,'q');
printBuffers();
GET_WRITE_PIN(0,5,'r',true);
printBuffers();
GET_WRITE_PIN(0,4,'s',true);
printBuffers();
GET_WRITE_PIN(0,3,'t',true);
printBuffers();
unpinPage(0,4);
GET_WRITE_PIN(0,16,'u',true);
printBuffers();
unpinPage(0,5);
GET_WRITE_PIN(0,3,'v',true);
printBuffers();
unpinPage(0,4);
unpinPage(0,3);
unpinPage(0,16);
unpinPage(0,3);
GET_WRITE(0,17,'w');
printBuffers();
GET_WRITE(0,5,'x');
printBuffers();
GET_WRITE(0,13,'y');
printBuffers();
GET_WRITE_PIN(0,3,'a',true);
printBuffers();
GET_WRITE_PIN(0,18,'b',true);
printBuffers();
GET_WRITE(0,9,'c');
printBuffers();
GET_WRITE_PIN(0,8,'d',true);
printBuffers();
GET_WRITE_PIN(0,11,'e',true);
printBuffers();
unpinPage(0,18);
GET_WRITE_PIN(0,9,'f',true);
printBuffers();
GET_WRITE_PIN(0,4,'g',true);
printBuffers();
GET_WRITE(0,3,'h');
printBuffers();
unpinPage(0,3);
unpinPage(0,9);
GET_WRITE_PIN(0,10,'i',true);
printBuffers();
GET_WRITE_PIN(0,7,'j',true);
printBuffers();
GET_WRITE(0,12,'k');
printBuffers();
GET_WRITE(0,13,'l');
printBuffers();
GET_WRITE(0,8,'m');
printBuffers();
unpinPage(0,8);
unpinPage(0,7);
GET_WRITE(0,18,'n');
printBuffers();
unpinPage(0,11);
unpinPage(0,4);
GET_WRITE(0,10,'o');
printBuffers();
GET_WRITE_PIN(0,18,'p',true);
printBuffers();
GET_WRITE(0,8,'q');
printBuffers();
GET_WRITE_PIN(0,8,'r',true);
printBuffers();
GET_WRITE_PIN(0,0,'s',true);
printBuffers();
GET_WRITE(0,14,'t');
printBuffers();
GET_WRITE(0,17,'u');
printBuffers();
unpinPage(0,10);
GET_WRITE(0,10,'v');
printBuffers();
GET_WRITE(0,12,'w');
printBuffers();
unpinPage(0,18);
GET_WRITE(0,12,'x');
printBuffers();
unpinPage(0,8);
GET_WRITE(0,12,'y');
printBuffers();
GET_WRITE(0,20,'a');
printBuffers();
GET_WRITE(0,14,'b');
printBuffers();
unpinPage(0,0);
GET_WRITE(0,5,'c');
printBuffers();
GET_WRITE(0,10,'d');
printBuffers();
GET_WRITE_PIN(0,5,'e',true);
printBuffers();
GET_WRITE(0,0,'f');
printBuffers();
GET_WRITE(0,0,'g');
printBuffers();
GET_WRITE_PIN(0,1,'h',true);
printBuffers();
GET_WRITE(0,19,'i');
printBuffers();
GET_WRITE(0,13,'j');
printBuffers();
GET_WRITE(0,6,'k');
printBuffers();
GET_WRITE(0,20,'l');
printBuffers();
unpinPage(0,5);
unpinPage(0,1);
GET_WRITE(0,13,'m');
printBuffers();
GET_WRITE(0,17,'n');
printBuffers();
GET_WRITE_PIN(0,10,'o',true);
printBuffers();
GET_WRITE(0,14,'p');
printBuffers();
GET_WRITE_PIN(0,12,'q',true);
printBuffers();
unpinPage(0,10);
GET_WRITE(0,10,'r');
printBuffers();
GET_WRITE_PIN(0,17,'s',true);
printBuffers();
GET_WRITE_PIN(0,6,'t',true);
printBuffers();
GET_WRITE(0,11,'u');
printBuffers();
GET_WRITE(0,9,'v');
printBuffers();
GET_WRITE(0,3,'w');
printBuffers();
GET_WRITE_PIN(0,0,'x',true);
printBuffers();
GET_WRITE_PIN(0,2,'y',true);
printBuffers();
unpinPage(0,12);
GET_WRITE(0,4,'a');
printBuffers();
unpinPage(0,6);
GET_WRITE(0,20,'b');
printBuffers();
GET_WRITE_PIN(0,14,'c',true);
printBuffers();
GET_WRITE(0,16,'d');
printBuffers();
unpinPage(0,0);
GET_WRITE(0,13,'e');
printBuffers();
GET_WRITE_PIN(0,14,'f',true);
printBuffers();
GET_WRITE(0,2,'g');
printBuffers();
unpinPage(0,14);
GET_WRITE(0,6,'h');
printBuffers();
GET_WRITE(0,1,'i');
printBuffers();
GET_WRITE(0,7,'j');
printBuffers();
GET_WRITE_PIN(0,14,'k',true);
printBuffers();
unpinPage(0,2);
unpinPage(0,14);
GET_WRITE_PIN(0,15,'l',true);
printBuffers();
GET_WRITE_PIN(0,14,'m',true);
printBuffers();
GET_WRITE_PIN(0,2,'n',true);
printBuffers();
GET_WRITE_PIN(0,19,'o',true);
printBuffers();
GET_WRITE(0,1,'p');
printBuffers();
unpinPage(0,17);
GET_WRITE_PIN(0,18,'q',true);
printBuffers();
GET_WRITE(0,7,'r');
printBuffers();
GET_WRITE(0,6,'s');
printBuffers();
unpinPage(0,14);
unpinPage(0,18);
GET_WRITE_PIN(0,1,'t',true);
printBuffers();
GET_WRITE(0,3,'u');
printBuffers();
unpinPage(0,19);
GET_WRITE_PIN(0,11,'v',true);
printBuffers();
GET_WRITE(0,4,'w');
printBuffers();
GET_WRITE(0,7,'x');
printBuffers();
unpinPage(0,2);
GET_WRITE_PIN(0,2,'y',true);
printBuffers();
GET_WRITE(0,4,'a');
printBuffers();
GET_WRITE(0,11,'b');
printBuffers();
GET_WRITE(0,2,'c');
printBuffers();
unpinPage(0,14);
GET_WRITE_PIN(0,4,'d',true);
printBuffers();
GET_WRITE_PIN(0,6,'e',true);
printBuffers();
GET_WRITE(0,19,'f');
printBuffers();
GET_WRITE(0,9,'g');
printBuffers();
GET_WRITE(0,10,'h');
printBuffers();
unpinPage(0,4);
GET_WRITE_PIN(0,20,'i',true);
printBuffers();
GET_WRITE_PIN(0,17,'j',true);
printBuffers();
GET_WRITE(0,7,'k');
printBuffers();
unpinPage(0,11);
GET_WRITE_PIN(0,3,'l',true);
printBuffers();
unpinPage(0,6);
GET_WRITE(0,17,'m');
printBuffers();
unpinPage(0,20);
GET_WRITE_PIN(0,4,'n',true);
printBuffers();
unpinPage(0,2);
GET_WRITE(0,14,'o');
printBuffers();
GET_WRITE(0,4,'p');
printBuffers();
unpinPage(0,1);
GET_WRITE_PIN(0,10,'q',true);
printBuffers();
unpinPage(0,4);
GET_WRITE(0,1,'r');
printBuffers();
unpinPage(0,3);
GET_WRITE_PIN(0,0,'s',true);
printBuffers();
unpinPage(0,17);
GET_WRITE(0,1,'t');
printBuffers();
GET_WRITE_PIN(0,12,'u',true);
printBuffers();
unpinPage(0,15);
GET_WRITE_PIN(0,7,'v',true);
printBuffers();
GET_WRITE_PIN(0,0,'w',true);
printBuffers();
unpinPage(0,7);
GET_WRITE(0,20,'x');
printBuffers();
GET_WRITE(0,13,'y');
printBuffers();
unpinPage(0,12);
GET_WRITE(0,0,'a');
printBuffers();
unpinPage(0,10);
GET_WRITE(0,7,'b');
printBuffers();
GET_WRITE_PIN(0,13,'c',true);
printBuffers();
GET_WRITE(0,17,'d');
printBuffers();
GET_WRITE(0,3,'e');
printBuffers();
unpinPage(0,0);
GET_WRITE(0,16,'f');
printBuffers();
GET_WRITE(0,3,'g');
printBuffers();
GET_WRITE(0,15,'h');
printBuffers();
GET_WRITE(0,3,'i');
printBuffers();
GET_WRITE(0,6,'j');
printBuffers();
GET_WRITE(0,5,'k');
printBuffers();
unpinPage(0,13);
GET_WRITE(0,18,'l');
printBuffers();
GET_WRITE_PIN(0,5,'m',true);
printBuffers();
GET_WRITE(0,7,'n');
printBuffers();
GET_WRITE_PIN(0,15,'o',true);
printBuffers();
GET_WRITE(0,2,'p');
printBuffers();
GET_WRITE_PIN(0,7,'q',true);
printBuffers();
GET_WRITE(0,0,'r');
printBuffers();
unpinPage(0,7);
GET_WRITE_PIN(0,13,'s',true);
printBuffers();
unpinPage(0,15);
GET_WRITE_PIN(0,7,'t',true);
printBuffers();
GET_WRITE(0,3,'u');
printBuffers();
GET_WRITE(0,19,'v');
printBuffers();
GET_WRITE(0,16,'w');
printBuffers();
unpinPage(0,7);
GET_WRITE(0,4,'x');
printBuffers();
GET_WRITE(0,15,'y');
printBuffers();
unpinPage(0,0);
unpinPage(0,5);
GET_WRITE(0,0,'a');
printBuffers();
unpinPage(0,13);
GET_WRITE(0,2,'b');
printBuffers();
GET_WRITE(0,16,'c');
printBuffers();
GET_WRITE(0,16,'d');
printBuffers();
GET_WRITE(0,13,'e');
printBuffers();
GET_WRITE(0,9,'f');
printBuffers();
GET_WRITE(0,0,'g');
printBuffers();
GET_WRITE_PIN(0,13,'h',true);
printBuffers();
GET_WRITE(0,6,'i');
printBuffers();
GET_WRITE(0,2,'j');
printBuffers();
GET_WRITE_PIN(0,20,'k',true);
printBuffers();
unpinPage(0,20);
GET_WRITE(0,9,'l');
printBuffers();
GET_WRITE(0,9,'m');
printBuffers();
GET_WRITE(0,11,'n');
printBuffers();
GET_WRITE(0,3,'o');
printBuffers();
unpinPage(0,13);
GET_WRITE_PIN(0,10,'p',true);
printBuffers();
GET_WRITE_PIN(0,0,'q',true);
printBuffers();
GET_WRITE(0,20,'r');
printBuffers();
unpinPage(0,10);
GET_WRITE_PIN(0,13,'s',true);
printBuffers();
GET_WRITE(0,10,'t');
printBuffers();
GET_WRITE(0,12,'u');
printBuffers();
GET_WRITE_PIN(0,9,'v',true);
printBuffers();
unpinPage(0,13);
GET_WRITE(0,3,'w');
printBuffers();
GET_WRITE(0,2,'x');
printBuffers();
unpinPage(0,0);
GET_WRITE(0,6,'y');
printBuffers();
