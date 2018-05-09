#include <date.h>
#include <stdio.h>
#include "interface.h"
#include <glib.h>
#include "Community.h"
#include "stdlib.h"

//tmp
#include "bArray.h"
#include "heap.h"
#include <time.h>
#include "comondec.h"
#include "limits.h"




int main(int argc, char *argv[])
{
    TAD_community com;
    if (argc < 2)
    {
        printf("--------------------------------------------------------\n");
        printf("\tIndica o path quando invocas o programa\n");
        printf("--------------------------------------------------------\n");
        exit(-1);
    }

    com = init();
    com = load(com, argv[1]);
    
    clean(com);
    return 1;

}


