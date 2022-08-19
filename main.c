#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//atm the max field size is x=29 and y=26
#define playfield_x_size 10
#define playfield_y_size 10

void show_field(char *field);
void init_field(char *field);
void generate_ships(char *field, int ship_length);
int player_turn(char *field, char *player_field);

int main(void)
{
    //srand(time=NULL);

    char *bot_field, *player_field;
    int hits=0;

    //"." - empty field and "X" ship
    bot_field = (char*)malloc(sizeof(char) * playfield_x_size * playfield_y_size);
    player_field = (char*)malloc(sizeof(char) * playfield_x_size * playfield_y_size);


    init_field(bot_field);

    generate_ships(bot_field, 4);

    generate_ships(bot_field, 3);
    generate_ships(bot_field, 3);
    generate_ships(bot_field, 3);

    generate_ships(bot_field, 2);
    generate_ships(bot_field, 2);


    show_field(bot_field);

    init_field(player_field);

    show_field(player_field);

    do{

        if(player_turn(bot_field, player_field) == 1)
            hits ++;


        show_field(player_field);



    }while (hits < 18);

    return 0;

}


void init_field(char *field){
    //just fills the whole field with .
    for(int x=0; x < playfield_x_size; x++){
        for(int y=0; y < playfield_y_size; y++){
            *(field+playfield_x_size*x+y) = '.';
        }
    }
}



void show_field(char *field){
    printf(" ");
    for(int i=1; i < playfield_x_size+1; i++){
        printf(" %d ", i);
    }


    printf("\n");

    for(int y=0; y < playfield_y_size; y++){
        //goes through the array and prints all the contents
        printf("%c ", 'A'+y);
        for(int x=0; x < playfield_x_size; x++){
            printf("%c  ",  *(field+playfield_x_size*x+y) );
        }
        printf("\n");
    }
}


void generate_ships(char *field, int ship_length) {


    srand(time(NULL)); //Init the seed

    int i = 0, j;
    int x, y, vh, x_c, y_c, space;

    //repeat until the ship is placed
    do {

        //generate if the ship is either vertical or horizontal aligned
        vh = rand() % 2;

        //Generate the x and y position of the ship
        x = rand() % playfield_x_size;
        y = rand() % playfield_y_size;

        space = 0;


        //Horizontal
        //Check if the ship will not go across the sides
        if(vh == 0 && x <= (playfield_x_size - ship_length) && y <= (playfield_y_size - ship_length)){

            //Check the surrounding area of the ship if it is free
            for(x_c=-1; x_c < ship_length+1 ; x_c++){
                for(y_c = -1; y_c < 2; y_c ++){
                    if(*(field+playfield_x_size*(x+x_c)+(y+y_c)) != 'X'){
                        //if the area is free count the free spaces
                        space++;
                    }
                }
            }

            //if there are enough free spaces place the ship
            if(space > ((ship_length+2)*3-1)){
                for(j=0; j < ship_length; j++){
                    *(field+playfield_x_size*(x+j)+y) = 'X';
                }
                i++;
            }
        }

        //Vertical
        //Check if the ship will not go across the sides
        if(vh == 1 && x <= (playfield_x_size - ship_length) && y <= (playfield_y_size - ship_length)){

            //Check the surrounding area of the ship if it is free
            for(x_c=-1; x_c < 2; x_c++){
                for(y_c = -1; y_c < ship_length+1; y_c++){
                    if(*(field+10*(x+x_c)+(y+y_c)) != 'X'){
                        space++;
                    }
                }
            }

            //if there are enough free spaces place the ship
            if(space > ((ship_length+2)*3-1)){
                for(j=0; j < ship_length; j++){
                    *(field+playfield_x_size*x+(y+j)) = 'X';
                }
                i++;
            }
        }
    } while (i < 1);
}

int player_turn(char *field, char *player_field){

    int x,y,hit = 0;
    char c;

    //check x and y

    char *pos = (char*)malloc(sizeof(char)*4);

    //repeat until all the values are correct
    do{
        //read the input string
        fgets(pos, 4, stdin);

        //convert Letter Char into int
        if(*(pos+0) <= 'z' && *(pos+0) >= 'a'){
            y = *(pos+0) - 'a';
        }
        else if(*(pos+0) <= 'Z' && *(pos+0) >= 'A'){
            y = *(pos+0) - 'A';
        }
        else{
            y = -1;
        }


        //Convert Number Chars into int
        if(*(pos+2) == '\n' && *(pos+1) <= '9' && *(pos+1) >= '0'){
            x = *(pos+1)-'0'-1;
        }

        else if(*(pos+1) == '1' && *(pos+2) <= '9' && *(pos+2) >= '0'){
            x = *(pos+2) - '0' + 10-1;
        }

        else if(*(pos+1) == '2' && *(pos+2) <= '9' && *(pos+2) >= '0'){
            x = *(pos+2) - '0' + 20-1;
        }
        else{
            x=-1;
        }

    }while(y > playfield_y_size || x > playfield_x_size || x == -1 || y == -1);

    printf("%d %d", y,x );


    //check if field is a hit, then mark that on the player field and return the hit to main
    if(*(field+playfield_x_size*(x)+(y)) == 'X'){

        printf("HIT!!!\n");

        *(player_field+playfield_x_size*(x)+(y)) = 'x';

        hit = 1;
    }

    else{
        printf("MISS!!!!\n");
        *(player_field+playfield_x_size*(x)+(y)) = 'O';
    }

    return hit;
}
