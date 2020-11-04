/*********** util.c file ****************/

#include "type.h"


int get_block(int dev, int blk, char *buf)
{
   lseek(dev, (long)blk*BLKSIZE, 0);
   read(dev, buf, BLKSIZE);
}   
int put_block(int dev, int blk, char *buf)
{
   lseek(dev, (long)blk*BLKSIZE, 0);
   write(dev, buf, BLKSIZE);
}   

int tokenize(char *pathname)
{
  // copy pathname into gpath[]; tokenize it into name[0] to name[n-1]
  // Code in Chapter 11.7.2 

  char *s;
  strcpy(gline, pathname);
  nname = 0;
  s = strtok(gline, "/");
  while(s)
  {
    name[nname++] = s;
    s = strtok(0, "/");
  }

}


MINODE *iget(int dev, int ino)
{
  // return minode pointer of loaded INODE=(dev, ino)
  // Code in Chapter 11.7.2
    MINODE *mip;
    MTABLE *mp;
    INODE *ip;
    int i, block, offset;
    char buf[BLKSIZE];
    //search in memory minodes first 
    for(i=0; i<NMINODES; i++;)
    {
      MINODE *mip = &MINODE[i];
    }
    if(mip->refCount && (mip->dev == dev) && (mip->ino == ino))
    {
      mip->refCount++;
      return mip;
    }

}

void iput(MINODE *mip)
{
  // dispose of minode pointed by mip
  // Code in Chapter 11.7.2

  INODE *ip;
  int i, block, offset;
  char buf[BLKSIZE];
  if(mip == 0)
  {
    return;
  }
  mip->refCount--;
  if(mip->refCount > 0)
  {
    return;
  }
  if(mip->dirty == )
  {
    return;
  }
  // write INODE back to disk
  block = (mip->ino - 1)/8 + iblock;
  offset = (mip->ino - 1) % 8;

  //get block containing this inode
  get_block(mip->dev, block, buf);
  ip = (INODE *)buf + offset; //ip points at INODE
  *ip = mip->INODE; //copy INODE to inode in block
  put_block(mip->dev, block, buf); //write back to disk
  midalloc(mip);  //mip->refCount = 0
} 

int search(MINODE *mip, char *name)
{
  // search for name in (DIRECT) data blocks of mip->INODE
  // return its ino
  // Code in Chapter 11.7.2

  int i;
  char *cp, temp[256], sbuf[BLKSIZE];
  DIR *dp;
  for(i=0; i<12; i++)
  {
    if(mip->INODE.i_block[i]==0)
    {
      return 0;
    }
    get_block(mip->dev, mip->INODE.i_block[i],sbuf);
    dp = (DIR *)sbuf;
    cp = sbuf;
    while(cp < sbuf + BLKSIZE)
    {
      strncpy(temp, dp->name, dp->name_len);
      temp[dp->name_len] = 0;
      printf("%8d%8d%8u %s\n", dp->inode, dp->rec_len, dp->name_len, temp);
      if(strcmp(name, temp) == 0)
      {
        printf("found %s : inumber = %d\n", name, dp->inode);
        return dp->inode;
      }
      cp += dp->rec_len;
      dp = (DIR *)cp;
    }
  }
  return 0;
}

int getino(char *pathname)
{
  // return ino of pathname
  // Code in Chapter 11.7.2
  MINODE *mip;
  int i, ino;
  if(strcmp(pathname, "/") == 0)
  {
    return 2; //return root ino = 2
  }
  if(pathname[0] == '/')
  {
    mip = root; //if absolute pathname : start from root
  }
  else
  {
    mip = running->cwd; // if relative pathname : start from CWD
    mip->refCount++; //in order to iput(mip) later
  }
  
}

int findmyname(MINODE *parent, u32 myino, char *myname) 
{
  // WRITE YOUR code here:
  // search parent's data block for myino;
  // copy its name STRING to myname[ ];
}

int findino(MINODE *mip, u32 *myino) // myino = ino of . return ino of ..
{
  // mip->a DIR minode. Write YOUR code to get mino=ino of .
  //                                         return ino of ..
}

