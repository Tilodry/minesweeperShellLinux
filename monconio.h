//
//  monconio.h
//  
//
//  Created by af on 11/02/2016.
//
//

#ifndef monconio_h
#define monconio_h

#include <stdio.h>
#include <termios.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>


int ttyreset(int fd);
int ttyraw(int fd);
int inputAvailable();


#endif /* monconio_h */