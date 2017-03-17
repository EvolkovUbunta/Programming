#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mdump(char mem[256])
{
  printf("shit\n");
  for(int i=0;i<32;i++)
  {
    printf("%5x ",i*8);
    for(int j=0;j<8;j++)
    {
      printf("%2x ",mem[i*8+j]);
    }
    printf("     ");
    for(int j=0;j<8;j++)
    {
      printf("%c ",(mem[i*8+j]>32)&&(mem[i*8+j]<127) ? mem[i+j] : '.');
    }
    printf("\n");
  }
}

void err(int pos, int code, char mem[256])
{
  printf("\nat position %d: ",pos);
  switch(code)
  {
    case 0:
      printf("ok\n");
      break;
    case 1:
      printf("missing bracket\n");
      break;
    case 2:
      printf("out of memory\n");
      break;
    default:
      printf("unknown error\n");
      break;
  }
  mdump(mem);
  exit(1);
}

int translate(char *scr, char mem[256], int pos=0, int mpos=0)
{
  int brc = 0, ep, sch;
  int sp = pos;

  while(pos<(unsigned)strlen(scr))
  {
     if((mpos<0)||(mpos>255)) 
     {
       printf("err: mem-pos:%d\n",mpos);
       err(pos,2,mem);
     }
     
     
     switch(scr[pos])
     {
      case '+':
	mem[mpos]++;
	break;
	
      case '-':
	mem[mpos]--;
	break;
	
      case '<':
	mpos--;
	break;
	
      case '>':
	mpos++;
	break;
	
      case '.':
	putchar(mem[mpos]);
	break;
	
      case ',':
	mem[mpos] = getchar();
	break;
	
      case '[':
	brc++;
	pos = translate(scr,mem,pos+1,mpos);
	break;
	
      case ']':
	if((unsigned)mem[mpos]==0)
	{
	  brc--;
	  return pos;
	}
	//else if(brc==0)err(pos,1);
	else
	{
	  //mem[mpos]--;
	  pos = sp-1;
	}
	break;
     }
     pos++;
  }
  printf("\n");
  
  return 0;
}



int main(int argc, char *argv[])
{
  FILE *f;
  char *filename, *buf, mem[256];
  int *pos, lSize;
  
  
  if(argc<2)
  {
    printf("BFRUN - loader of BrainFuck scripts\n");
    printf("USAGE:\n\tbfrun [-d] <filename>\n");
    return 1;
  }else{
    filename = argc==2 ? argv[1] : argv[2];

  }
  
  f = fopen(filename,"r");
  if(f==NULL) perror("can't open\n");
  else
  {
    //getting size
    fseek (f , 0 , SEEK_END);
    lSize = ftell (f);
    rewind (f); 
    
    buf = (char*) malloc (sizeof(char)*lSize);
    if (buf == NULL) 
    {
      fputs ("Memory error",stderr); 
      exit (2);
    }
    
    if (fread (buf,1,lSize,f) != lSize) 
    {
      fputs ("Reading error",stderr); 
      exit (3);
    }
    
    
    fclose(f);
    
    //init script memory
    for(int i=0;i<256;i++)mem[i]=0;
    
    //run

    mem[0] = 0;
    translate(buf,mem);

    if((argc==3)&&(argv[1][1]=='d')) mdump(mem);
    free(buf);
  }
  return 0;
}