#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "scanner.h"

static void skipWhiteSpace(FILE *);
static char convertEscapedChar(int);
static void *allocateMsg(size_t,char *);
static void *reallocateMsg(void *,size_t,char *);

int readInt(FILE *fp)
    {
    int x,result;
    result = fscanf(fp,"%d",&x);
    if (result == EOF)
        {
        return 0;
        }
    if (result == 0)
        {
        fprintf(stderr,"SCAN ERROR: attempt to read an integer failed\n");
        fprintf(stderr,"offending character was <%c>\n",fgetc(fp));
        exit(1);
        }
    return x;
    }

double
readReal(FILE *fp)
    {
    int result;
    double x;
    result = fscanf(fp," %lf",&x);
    if (result == EOF)
        {
        return 0.0;
        }
    if (result == 0)
        {
        fprintf(stderr,"SCAN ERROR: attempt to read a real number failed\n");
        fprintf(stderr,"offending character was <%c>\n",fgetc(fp));
        exit(2);
        }
    return x;
    }

char
readChar(FILE *fp)
    {
    int result;
    char x;
    result = fscanf(fp," %c",&x);
    if (result == EOF)
        {
        return -1;
        }
    if (result == 0)
        {
        fprintf(stderr,"SCAN ERROR: attempt to read a real number failed\n");
        fprintf(stderr,"offending character was <%c>\n",fgetc(fp));
        exit(2);
        }
    return x;
    }

char
readRawChar(FILE *fp)
    {
    int result;
    char x;
    result = fscanf(fp,"%c",&x);
    if (result == EOF)
        {
        return -1;
        }
    if (result == 0)
        {
        fprintf(stderr,"SCAN ERROR: attempt to read a real number failed\n");
        fprintf(stderr,"offending character was <%c>\n",fgetc(fp));
        exit(2);
        }
    return x;
    }

char *
readString(FILE *fp)
    {
    int ch,index;
    char *buffer;
    int size = 512;

    skipWhiteSpace(fp);

    ch = fgetc(fp);
    if (ch == EOF) return 0;

    buffer = allocateMsg(size,"readString");

    if (ch != '\"')
        {
        fprintf(stderr,"SCAN ERROR: attempt to read a string failed\n");
        fprintf(stderr,"first character was <%c>\n",ch);
        exit(4);
        }

    ch = fgetc(fp);

    index = 0;

    while (ch != '\"')
        {
        if (ch == EOF)
            {
            fprintf(stderr,"SCAN ERROR: attempt to read a string failed\n");
            fprintf(stderr,"no closing double quote\n");
            exit(6);
            }
        if (index > size - 2) 
            {
            ++size;
            buffer = reallocateMsg(buffer,size,"readString");
            }

        if (ch == '\\')
            {
            ch = fgetc(fp);
            if (ch == EOF)
                {
                fprintf(stderr,"SCAN ERROR: attempt to read a string failed\n");
                fprintf(stderr,"escaped character missing\n");
                exit(6);
                }
            buffer[index] = convertEscapedChar(ch);
            }
        else
            buffer[index] = ch;
        ++index;
        ch = fgetc(fp);
        }

    buffer[index] = '\0';

    return buffer;
    }

char *
readToken(FILE *fp)
    {
    int ch,index;
    char *buffer;
    int size = 80;

    skipWhiteSpace(fp);

    ch = fgetc(fp);
    if (ch == EOF) return 0;

    buffer = allocateMsg(size,"readToken");

    index = 0;
    while (!isspace(ch))
        {
        if (ch == EOF) break;
        if (index > size - 2)
            {
            ++size;
            buffer = reallocateMsg(buffer,size,"readToken");
            }
        buffer[index] = ch;
        ++index;
        ch = fgetc(fp);
        }

    ungetc(ch,fp);
    buffer[index] = '\0';

    return buffer;
    }

char *
readLine(FILE *fp)
    {
    int ch,index;
    char *buffer;
    int size = 512;
    
    ch = fgetc(fp);
    if (ch == EOF) return 0;

    buffer = allocateMsg(size,"readLine");

    index = 0;
    while (ch != '\n')
        {
        if (ch == EOF) break;
        if (index > size - 2)
            {
            ++size;
            buffer = reallocateMsg(buffer,size,"readToken");
            }
        buffer[index] = ch;
        ++index;
        ch = fgetc(fp);
        }

    buffer[index] = '\0';

    return buffer;
    }

static void
skipWhiteSpace(FILE *fp)
    {
    int ch;

    while ((ch = fgetc(fp)) != EOF && isspace(ch))
        continue;

    ungetc(ch,fp);
    }

static char
convertEscapedChar(int ch)
    {
    switch (ch)
        {
        case 'n':  return '\n';
        case 't':  return '\t';
        case '"':  return '\"';
        case '\\': return '\\';
        }
    return ch;
    }

void *
allocate(size_t size)
    {
    char *s;
    s = malloc(size);
    if (s == 0)
        {
        fprintf(stderr,"could not allocate string, out of memory\n");
        exit(3);
        }

    return s;
    }

void *
reallocate(void *s,size_t size)
    {
    char *t;
    t = realloc(s,size);
    if (t == 0)
        {
        fprintf(stderr,"could not reallocate string, out of memory\n");
        exit(3);
        }

    return t;
    }


void *
allocateMsg(size_t size,char *where)
    {
    char *s;
    s = malloc(size);
    if (s == 0)
        {
        fprintf(stderr,"%s: could not allocate string, out of memory\n",
            where);
        exit(3);
        }

    return s;
    }

static void *
reallocateMsg(void *s,size_t size,char *where)
    {
    char *t;
    t = realloc(s,size);
    if (t == 0)
        {
        fprintf(stderr,"%s: could not reallocate string, out of memory\n",
            where);
        exit(3);
        }

    return t;
    }
