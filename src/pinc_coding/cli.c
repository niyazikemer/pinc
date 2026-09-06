# include "cli.h"
# include "stdio.h"
# include "string.h"

int pinc_cli_run(int argc, char *argv[]){
    if(argc>=2 && strcmp(argv[1], "--version")==0){
        printf("pinc %s\n",PINC_VERSION);
        return 0;
    }
    printf("Pinc installed, for version pinc --version");
    return 0;
}