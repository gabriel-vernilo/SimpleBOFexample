#include <stdio.h>
#include <string.h>

void vitoria(){
    printf("Boa! Voce passou! Hahahaha\n");
}

int main(int argc, char **argv){
    char teste[50];
    gets(teste);
    printf("Voce enviou: %s\n", teste);
    return(0);
}
