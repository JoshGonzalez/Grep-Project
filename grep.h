#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include <stdio.h>
#include <string.h>
#include<sys/wait.h>
#include <regex.h>

#define	BLKSIZE	4096
#define	NBLK	2047
#define	FNSIZE	128
#define	LBSIZE	4096
#define	ESIZE	256
#define	GBSIZE	256
#define	NBRA	5
#define	KSIZE	9
#define	CBRA	1
#define	CCHR	2
#define	CDOT	4
#define	CCL	6
#define	NCCL	8
#define	CDOL	10
#define	CEOF	11
#define	CKET	12
#define	CBACK	14
#define	CCIRC	15
#define	STAR	01
#define	READ	0
#define	WRITE	1

unsigned nlall = 128;  unsigned int  *addr1, *addr2, *dot, *dol, *zero;
int peekc, lastc, io, pflag, given, ninbuf, vflag = 1, oflag, listf, listn, col, subolda, fchange, wrapp, bpagesize = 20, names[26], anymarks, nbra, subnewa, tfile = -1;
int tline, iblock = -1, oblock = -1, ichanged, nleft, reg_i = 0;
char  Q[] = "", T[] = "TMP", savedfile[FNSIZE], file[FNSIZE], linebuf[LBSIZE], rhsbuf[LBSIZE/2], expbuf[ESIZE+4], genbuf[LBSIZE], *nextip, *linebp, *globp, *mktemp(char *), *nep, *rbufp;
char  tmpXXXXX[50] = "/tmp/fileXXXXXX", *tfname, *loc1, *loc2, ibuff[BLKSIZE], obuff[BLKSIZE], WRERR[]  = "WRITE ERROR", *braslist[NBRA], *braelist[NBRA], line[70], *linp  = line;
char reg_buf[BUFSIZ];
long	count;
char grepbuf[GBSIZE], inputbuf[GBSIZE];
jmp_buf	savej;
typedef void	(*SIG_TYP)(int);
SIG_TYP	oldhup, oldquit; /* these two are not in ansi, but we need them const int	SIGHUP = 1	hangup;const int	SIGQUIT = 3	 quit (ASCII FS) */
void redo(int argc, char *argv[]);
void operation(char * f, char * t);
int advance(char *lp, char *ep);
void ungetch_(int c);
int append(int (*f)(void), unsigned int *a);
int backref(int i, char *lp);
void blkio(int b, char *buf, long (*iofcn)(int, void*, unsigned long));
int cclass(char *set, int c, int af);
void compile(int eof);
void error(char *s);
int execute(unsigned int *addr);
void exfile(void);
void filename(int comm);
char *getblock(unsigned int atl, int iof);
int getc_();
int getchr(void);
int getfile(void);
char *getline_(unsigned int tl);
void global(int k);
void init(void);
void onhup(int n);
void onintr(int n);
void putchr_(int ac);
void printbuffer();
int equal(const char *s, char *p);
void putd(void);  void putfile(void);
int putline(void);
void puts_(char *sp);
void reverse(char *s);
void setwide(void);  void setnoaddr(void);
void squeeze(int);
void readfile(const char* c);
void search(const char* c);
