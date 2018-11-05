/**
 * @Author: Atul Sahay <atul>
 * @Date:   2018-11-03T12:16:42+05:30
 * @Email:  atulsahay01@gmail.com
 * @Last modified by:   atul
 * @Last modified time: 2018-11-05T14:47:10+05:30
 */

 #include <sys/types.h>
 #include <sys/socket.h>
 #include <netdb.h>
 #include <stdio.h>
 #include <string.h>
 #include <stdbool.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <signal.h>

 // Maximum input size from the interactive mode or batch mode
 #define MAX_INPUT_SIZE 100000
 #define MAX_TOKEN_SIZE 100000
 #define MAX_NUM_TOKENS 100000
 #define MAX_KEYS_ALLOWED 20
 #define COMMAND_CHOICES 6
///////////////////////////////////////////

//Time check
// int alarm_stop = FALSE;
bool WITHIN_TIME = true;
unsigned int NThreads = 100;
unsigned int alarm_period = 3;
int count =0;
int key;
int commandChoice;
bool connectChoice = false;


// const char *command[5];
// command[0] = "connect 127.0.0.1 8000";
// command[1] = "hmm";
void my_init() {
    srand(time(NULL));
}

int get_random() {
    return rand() % COMMAND_CHOICES;
}

char * createCommand(void)
{
  int choice;
  char *command = (char *)malloc(50*sizeof(char));

  int commandChoice = get_random()+1;
  while( !connectChoice && commandChoice == 6)
      commandChoice = get_random()+1;

  while( connectChoice && commandChoice == 1)
        commandChoice = get_random()+1;
  switch(commandChoice)
  {
      case 1 :  sprintf(command,"connect 127.0.0.1 3000");
                connectChoice = true;
                break;

      case 2 :  choice = randomKeyChoices();
                sprintf(command,"create %d 4 atul",choice);
                break;

      case 3 :  choice = randomKeyChoices();
                sprintf(command,"read %d",choice);
                break;

      case 4 :  choice = randomKeyChoices();
                sprintf(command,"update %d 4 atul",choice);
                break;

      case 5 :  choice = randomKeyChoices();
                sprintf(command,"delete %d",choice);
                break;

      case 6 :  sprintf(command,"disconnect",choice);
                connectChoice = false;
                break;
  }




  // printf("%s\n",command );
  // printf("first Number =%d\n\n",i);
  // while (i >= 0) {
  //     printf ("Number = %3d\n", i);
  //     sprintf(command,"create %d 4 atul",i);
  //     printf("%s\n",command);
  //     i = myRandom (-1);
  // }
  // printf ("Final  = %3d\n", i);
  return command;
}



#define ERR_NO_NUM -1
#define ERR_NO_MEM -2


//// Random Key Values will be given
int randomKeyChoices()
{
  int i;
  while(key>=0){
    i=key;
    key = myRandom(-1);
    break;
  }
  if(key<0)
    key = myRandom(MAX_KEYS_ALLOWED);
  return i;
}

int myRandom (int size) {
    int i, n;
    static int numNums = 0;
    static int *numArr = NULL;

    // Initialize with a specific size.

    if (size >= 0) {
        if (numArr != NULL)
            free (numArr);
        if ((numArr = malloc (sizeof(int) * size)) == NULL)
            return ERR_NO_MEM;
        for (i = 0; i  < size; i++)
            numArr[i] = i;
        numNums = size;
    }

    // Error if no numbers left in pool.

    if (numNums == 0)
       return ERR_NO_NUM;

    // Get random number from pool and remove it (rnd in this
    //   case returns a number between 0 and numNums-1 inclusive).

    n = rand() % numNums;
    i = numArr[n];
    numArr[n] = numArr[numNums-1];
    numNums--;
    if (numNums == 0) {
        free (numArr);
        numArr = 0;
    }

    return i;
}



void on_alarm(int signal) {
    WITHIN_TIME=false;
    printf("Program exit\n");
}



void* sender(void *ptr) {
  int newsockfd,data;
  int thread_id = *((int *)ptr);
  printf("Thread comes to play id: %d\n",thread_id);
  while(WITHIN_TIME){
    // pthread_mutex_lock(&mutex);
    // while (queue_count==0){
    //         printf("Thread %d goes to sleep\n",thread_id);
    //   pthread_cond_wait(&condc, &mutex);
    //   printf("Thread %d starts executing\n",thread_id);
    // }
    // // if(written==MAXITERATIONS-1){
    // //   pthread_cond_signal(&condp);
    // //   pthread_cond_broadcast(&condc);
    // //   pthread_mutex_unlock(&mutex);
    // //   break;
    // // }
    // newsockfd = release();
    // printf("Thread %d Consumed %d Current Buffer size %d\n",thread_id,newsockfd,queue_count);
    // // doprocessing(newsockfd,thread_id); //{ when nothing works do this}
    // pthread_cond_broadcast(&condc);
    // pthread_cond_signal(&condp);
    // pthread_mutex_unlock(&mutex);
    // doprocessing(newsockfd,thread_id);
    //
    // // optional sleep to allow workers to run
    // struct timespec delay;
    // delay.tv_sec = 0;
    // delay.tv_nsec = SLEEP_NANOSEC_CONS;
    // //nanosleep(&delay, NULL);
  }
  // printf("Here Thread %d\n",thread_id);
  // pthread_cond_broadcast(&condc);
  // pthread_cond_broadcast(&condc);
  // pthread_cond_broadcast(&condc);
  // pthread_cond_broadcast(&condc);
  // pthread_cond_signal(&condp);
  // numT+=1;
  // if(numT==5)
  // {
  //   cleanup_routine();
    printf("Thread exit id: %d\n",thread_id);
    count+=1;
    // if(count==100)
    //     printf("count %d\nDone\n",count);
  //  pthread_exit(NULL);
  // }
  // //pthread_exit(NULL);
}


int main()
{
  ////Particular Initialisation of key with a value
  my_init();
  key = myRandom(MAX_KEYS_ALLOWED);
  commandChoice = myRandom(COMMAND_CHOICES);

  int i;
  char *command;
  for(i = 0; i < 22 ; i++)
  {
      command = createCommand();
      printf("Command : %s\n",command);
      free(command);
  }

  // sender threads
  pthread_t sender_th[NThreads];

  int sender_thread_id[NThreads];
  i = 0;
  for(i = 0 ; i < NThreads ; i++)
  {
      sender_thread_id[i] = i+1;
  }
  for(i = 0 ; i < NThreads ; i++)
  {
      pthread_create(&sender_th[i], NULL, sender, (void *)&sender_thread_id[i]);
  }
  signal(SIGALRM, on_alarm);
  alarm(alarm_period);
  pause();

  // so that all threads are joined that's sleep pf 1 sec
  sleep(2);
  printf("count of threads exit : %d\nDone\n",count);
  for(i=0; i < NThreads ; i++){
      pthread_join(sender_th[i],NULL);
  }
  return 0;
}
// //////////////////////////////////////
//  //tokenize the input string
//  char **tokenize(char *line);
//  ////////////////////////////////
//
//  // Global vars for connection related things
//  int sockfd;
//  bool activeConn; /* Needed to check whether client has any active connection or not*/
//  struct sockaddr_in servaddr; /* structure where all connection related things are stored*/
//
//  void parser(char **tokens);
//  void lineByline(FILE * file);
//  char * readline(FILE *fp, char *buffer);
//
//  /**** function I tried to read line by line not worked accordingly****/
//  // char * readMy()
//  // {
//  //
//  //       int ch;
//  //       int i = 0;
//  //       size_t buff_len = 0;
//  //
//  //       char *buffer = (char *)malloc(buff_len + 1);
//  //       if (!buffer) return NULL;  // Out of memory
//  //
//  //       while ((ch = fgetc(stdin)) != '\n' && ch != EOF)
//  //       {
//  //           buff_len++;
//  //           void *tmp = realloc(buffer, buff_len + 1);
//  //           if (tmp == NULL)
//  //           {
//  //               free(buffer);
//  //               return NULL; // Out of memory
//  //           }
//  //           buffer = tmp;
//  //
//  //           buffer[i] = (char) ch;
//  //           i++;
//  //       }
//  //       buffer[i] = '\0';
//  //
//  //       // Detect end
//  //       if (ch == EOF && (i == 0 || ferror(stdin)))
//  //       {
//  //           free(buffer);
//  //           return NULL;
//  //       }
//  //       return buffer;
//  // }
//  ////////////////////////////////////
//  int main(int argc,char **argv)
//  {
//
//      int sockfd,n;
//      char sendline[10000];
//      char recvline[10000];
//      struct sockaddr_in servaddr;
//
//      // whether the client have an active connection or not
//      bool activeConn = false;
//
//      char  *line = (char *)malloc(MAX_INPUT_SIZE*sizeof(char));
//      char **tokens;
//
//      // To select between batch and interactive mood
//      if(argc == 2)
//      {
//          printf("Welcome to Interactive Mode\n");
//          int i =0;
//          while(true)
//          {
//              int tokenCount=0;
//              printf("->");
//              bzero(line, MAX_INPUT_SIZE);
//              // line = readMy();
//              fgets(line,MAX_INPUT_SIZE,stdin);
//              line[strlen(line)] = '\n'; //terminate with new line
//              tokens = tokenize(line);
//              parser(tokens);
//              int i;
//              //Freeing up the acquired space by the tokens
//              for(i=0;tokens[i]!=NULL;i++){
//                  free(tokens[i]);
//              }
//              free(tokens);
//
//          }
//          free(line);
//      }
//      else if(argc == 3)
//      {
//          printf("Welcome to batch mode\nFile: %s\n",argv[2]);
//          //open and get the file handle
//          char *fileName = argv[2];
//          FILE* file = fopen(fileName, "r");
//          lineByline(file);
//          free(line);
//          return 0;
//      }
//      else
//      {
//          printf("Incorrect arguements\n");
//          free(line);
//          exit(0);
//      }
//
//      free(line);
//  }
//
//  ////////// Function Definition are written here ////////////////////////
//
//  /**************** Parsing the commands ***********/
//  void parser(char **tokens){
//    // char *sendline =(char*)malloc(MAX_INPUT_SIZE*sizeof(char));
//    // char *recvline =(char*)malloc(MAX_INPUT_SIZE*sizeof(char));
//    char sendline[MAX_INPUT_SIZE];
//    char recvline[MAX_INPUT_SIZE];
//    int n,i;          /* n for storing the reuturn values of each query made to the server*/
//    int tokenCount = 0;
//    bzero(sendline,MAX_INPUT_SIZE);
//    bzero(recvline,MAX_INPUT_SIZE);
//    //do whatever you want with the commands, here we just print them
//    for(i=0;tokens[i]!=NULL;i++){
//       // printf("found token %s\n", tokens[i]);
//       tokenCount++;
//    }
//
//    /// All the functions are going to be written here
//    if(strncmp(tokens[0],"connect",7)==0)
//    {
//        if(!activeConn)
//        {
//            char address[1024];
//            char portStr[1024];
//            strcpy(address,tokens[1]);
//            strcpy(portStr,tokens[2]);
//            // for string to int
//            int port;
//            sscanf(portStr, "%d", &port);
//
//            sockfd=socket(AF_INET,SOCK_STREAM,0);
//            bzero(&servaddr,sizeof servaddr);
//
//            servaddr.sin_family=AF_INET;
//            servaddr.sin_port=htons(port);
//
//            inet_pton(AF_INET,address,&(servaddr.sin_addr));
//
//            if(connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))<0)
//            {
//                printf("\nConnection Failed \n");
//            }
//            else{
//                activeConn = true;
//                printf("ok Connection made\n");
//            }
//        }
//
//        else{
//            printf("Already have a connection\n");
//        }
//    }
//    else if(strncmp(tokens[0],"disconnect",10)==0)
//    {
//        if(activeConn)
//        {
//            strcpy(sendline,"bye");
//            write(sockfd,sendline,strlen(sendline)+1);
//            read(sockfd,recvline,100);
//            printf("%s\n",recvline);
//            activeConn = false;
//        }
//        else
//        {
//            printf("Please first make an active connection\n");
//        }
//    }
//    else if(strncmp(tokens[0],"create",6)==0)
//    {
//        if(activeConn){
//            bool present = false;
//            strcpy(sendline,"create");
//            write(sockfd,sendline,strlen(sendline)+1);
//            read(sockfd,recvline,100);
//            printf("%s\n",recvline);
//
//            strcpy(sendline,tokens[1]);
//            write(sockfd,sendline,strlen(sendline)+1);
//            read(sockfd,recvline,100);
//            printf("%s\n",recvline);
//
//            if(strncmp(recvline,"present",7) == 0)
//            {
//                present=true;
//                printf("Error: key is already present\n");
//            }
//            if(!present){
//                bzero(sendline,MAX_INPUT_SIZE);
//                strcpy(sendline,tokens[2]);
//                write(sockfd,sendline,strlen(sendline)+1);
//                read(sockfd,recvline,100);
//                printf("%s\n",recvline);
//
//                int i = 3;
//                int totalStrLen = 0;
//                while(i<tokenCount)
//                {
//                    totalStrLen+=strlen(tokens[i]);
//                    totalStrLen+=1;
//                    i++;
//                }
//                bzero(sendline,MAX_INPUT_SIZE);
//                i=3;
//                while(i<tokenCount)
//                {
//                    strcat(sendline,tokens[i]);
//                    strcat(sendline," ");
//                    i+=1;
//                }
//                sendline[strlen(sendline)-1]=0;
//                printf("\nYour text ::::-> %s \n\nText size:%ld\n\n",sendline,strlen(sendline));
//                write(sockfd,sendline,strlen(sendline)+1);
//
//                n = read(sockfd,recvline,10000);
//                printf("%s\n",recvline);
//                // while(i<tokenCount){
//                //     strcpy(sendline,tokens[i]);
//                //     write(sockfd,sendline,strlen(sendline)+1);
//                //     n = read(sockfd,recvline,100);
//                //     printf("%s\n",recvline);
//                //     i+=1;
//                // }
//                n = read(sockfd,recvline,100);
//                printf("%s\n",recvline);
//            }
//        }
//        else{
//            printf("No active connection present\n");
//        }
//    }
//    else if(strncmp(tokens[0],"read",4)==0)
//    {
//        if(activeConn){
//            bool present = true;
//            bzero(sendline,MAX_INPUT_SIZE);
//            strcpy(sendline,"read");
//            write(sockfd,sendline,strlen(sendline)+1);
//            read(sockfd,recvline,100);
//            printf("%s\n",recvline);
//            bzero(sendline,MAX_INPUT_SIZE);
//            strcpy(sendline,tokens[1]);
//            // bzero(sendline,MAX_INPUT_SIZE);
//            write(sockfd,sendline,strlen(sendline)+1);
//            read(sockfd,recvline,100);
//            printf("%s\n",recvline);
//
//            if(strncmp(recvline,"not",3) == 0)
//            {
//                present=false;
//                printf("Error: key is not present\n");
//            }
//            if(present){
//              unsigned int length;
//              int size;
//              char buffer[256];
//              bzero(buffer,256);
//              n=read(sockfd,buffer,255);
//              // printf("%d\n",n);
//              sscanf(buffer, "%d", &size);
//              printf("Read: Got size value from the server= %d\n",size);
//              char dummy[10];
//              bzero(dummy,10);
//              n=write(sockfd,dummy,strlen(dummy)+1);
//              int bytesRead = 0;
//              int bytesToRead =size+1;
//              int readThisTime;
//              char *bufferRead = (char *)malloc(bytesToRead*sizeof(char));
//              bzero(bufferRead,size+1);
//              while (bytesToRead != bytesRead)
//              {
//                  do
//                  {
//                       readThisTime = read(sockfd, bufferRead + bytesRead, (bytesToRead - bytesRead));
//                  }
//                  while(readThisTime == -1);
//
//                  if (readThisTime == -1)
//                  {
//                      /* Real error. Do something appropriate. */
//                      return 0;
//                  }
//                  // printf("%d\n",readThisTime);
//                  bytesRead += readThisTime;
//              }
//
//              printf("RECEIVED TEXT : %s\n",bufferRead);
//              free(bufferRead);
//            }
//        }
//        else{
//            printf("No active connection present\n");
//        }
//    }
//    else if(strncmp(tokens[0],"update",6)==0)
//    {
//        if(activeConn){
//            bool present = true;
//            strcpy(sendline,"update");
//            write(sockfd,sendline,strlen(sendline)+1);
//            read(sockfd,recvline,100);
//            printf("%s\n",recvline);
//
//            strcpy(sendline,tokens[1]);
//            write(sockfd,sendline,strlen(sendline)+1);
//            read(sockfd,recvline,100);
//            printf("%s\n",recvline);
//
//            if(strncmp(recvline,"not",3) == 0)
//            {
//                present=false;
//                printf("Error: key is not present\n");
//            }
//            if(present){
//              bzero(sendline,MAX_INPUT_SIZE);
//              strcpy(sendline,tokens[2]);
//              write(sockfd,sendline,strlen(sendline)+1);
//              read(sockfd,recvline,100);
//              printf("%s\n",recvline);
//
//              int i = 3;
//              int totalStrLen = 0;
//              while(i<tokenCount)
//              {
//                  totalStrLen+=strlen(tokens[i]);
//                  totalStrLen+=1;
//                  i++;
//              }
//              bzero(sendline,MAX_INPUT_SIZE);
//              i=3;
//              // printf("%s\n","Going to count now" );
//              while(i<tokenCount)
//              {
//                  strcat(sendline,tokens[i]);
//                  strcat(sendline," ");
//                  i+=1;
//              }
//              sendline[strlen(sendline)-1]=0;
//              printf("\nText Read:::-> %s \n\nText size: %ld\n\n",sendline,strlen(sendline));
//              write(sockfd,sendline,strlen(sendline)+1);
//
//              n = read(sockfd,recvline,10000);
//              printf("%s\n",recvline);
//              // while(i<tokenCount){
//              //     strcpy(sendline,tokens[i]);
//              //     write(sockfd,sendline,strlen(sendline)+1);
//              //     n = read(sockfd,recvline,100);
//              //     printf("%s\n",recvline);
//              //     i+=1;
//              // }
//              n = read(sockfd,recvline,100);
//              printf("%s\n",recvline);
//            }
//        }
//        else{
//            printf("No active connection present\n");
//        }
//    }
//    else if(strncmp(tokens[0],"delete",6)==0)
//    {
//        if(activeConn){
//            bool present = true;
//            strcpy(sendline,"delete");
//            write(sockfd,sendline,strlen(sendline)+1);
//            read(sockfd,recvline,100);
//            printf("%s\n",recvline);
//            strcpy(sendline,tokens[1]);
//            write(sockfd,sendline,strlen(sendline)+1);
//            read(sockfd,recvline,100);
//            printf("%s\n",recvline);
//
//            if(strncmp(recvline,"not",3) == 0)
//            {
//                present=false;
//                printf("Error: key is not present\n");
//            }
//            if(present){
//              unsigned int length;
//              int size;
//              char buffer[256];
//              bzero(buffer,256);
//              n=read(sockfd,buffer,255);
//              printf("%s\n",buffer);
//            }
//        }
//        else{
//            printf("No active connection present\n");
//        }
//    }
//    else
//    {
//        printf("No command found!! Please try again\n");
//    }
//
//  }
//
//
//
//  //////// Reading FILE
//
//  char * readline(FILE *fp, char *buffer)
//  {
//      int ch;
//      int i = 0;
//      size_t buff_len = 0;
//
//      buffer = malloc(buff_len + 1);
//      if (!buffer) return NULL;  // Out of memory
//
//      while ((ch = fgetc(fp)) != '\n' && ch != EOF)
//      {
//          buff_len++;
//          void *tmp = realloc(buffer, buff_len + 1);
//          if (tmp == NULL)
//          {
//              free(buffer);
//              return NULL; // Out of memory
//          }
//          buffer = tmp;
//
//          buffer[i] = (char) ch;
//          i++;
//      }
//      buffer[i] = '\0';
//
//      // Detect end
//      if (ch == EOF && (i == 0 || ferror(fp)))
//      {
//          free(buffer);
//          return NULL;
//      }
//      return buffer;
//
//  }
//  ////////// Ends (Reading the file)
//
//  /* Line by line interpretation of the command*/
//  void lineByline(FILE * file){
//    char *s;
//    char **tokens;
//    int i;
//    int tokenCount=0;
//    char  *line = (char *)malloc(MAX_INPUT_SIZE*sizeof(char));
//
//    char sendline[10000];
//    char recvline[10000];
//
//    // whether the client have an active connection or not
//    bool activeConn = false;
//
//    int sockfd,n;
//    struct sockaddr_in servaddr;
//
//    while ((s = readline(file, 0)) != NULL){
//        printf("Command ---> %s\n",s);
//        bzero(line, MAX_INPUT_SIZE);
//        strcpy(line,s);
//        line[strlen(line)] = '\n'; //terminate with new line
//        // puts(line);
//        tokens = tokenize(line);
//
//        parser(tokens); // parser is called
//        int i;
//        //Freeing up the acquired space by tokens
//        for(i=0;tokens[i]!=NULL;i++){
//            free(tokens[i]);
//        }
//        free(tokens);
//        free(s);
//        printf("\n");
//      }
//      if(s!=NULL)
//        free(s);
//      free(line);
//  }
//
//  //tokenize the input string
//  char **tokenize(char *line)
//  {
//    char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
//    char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
//    int i, tokenIndex = 0, tokenNo = 0;
//
//    for(i =0; i < strlen(line); i++){
//
//      char readChar = line[i];
//
//      if (readChar == ' ' || readChar == '\n' || readChar == '\t'){
//        token[tokenIndex] = '\0';
//        if (tokenIndex != 0){
//  	tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE*sizeof(char));
//  	strcpy(tokens[tokenNo++], token);
//  	tokenIndex = 0;
//        }
//      } else {
//        token[tokenIndex++] = readChar;
//      }
//    }
//
//    free(token);
//    tokens[tokenNo] = NULL ;
//    return tokens;
//  }
