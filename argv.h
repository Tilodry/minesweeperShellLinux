#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NumberOfArg		( argc - 1 )
#define LengthOfArg(N)		( argc > (N) ? strlen( argv[N] ) : 0 )

#define IntegerArg(N)		( argc > (N) ? atoi( argv[N] ) : 0 )
#define FloatArg(N)		( argc > (N) ? (float)atof( argv[N] ) : (float)0 )
#define DoubleArg(N)		( argc > (N) ? atof( argv[N] ) : (double)0 )
#define StringArg(N)		( argc > (N) ? argv[N] : NULL )
#define CharacterArg(N,I)	( argc > (N) ? *(argv[N] + (I)): '\0' )

#define BadNumberOfArg		( puts("mauvais nombre d'arguments" ) , -1 )
#define InvalidArg		( puts("argument non valide") , -2 )
