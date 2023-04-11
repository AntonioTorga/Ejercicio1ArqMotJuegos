#include "ej1.cpp"
#include <iostream>
int main(){
    BoundingBox bb1 = BoundingBox();
    BoundingBox bb2 = BoundingBox();
    enclose(bb1,Vector2D{1,1});
    enclose(bb1,Vector2D{0,0});
    enclose(bb2,Vector2D{1,1});
    enclose(bb2,Vector2D{0,0});
    Actor act1 = Actor(Vector2D{0,0}, Vector2D{1,0},bb1);
    Actor act2 = Actor(Vector2D{5,0}, Vector2D{0,0},bb2);
    
    int counter = 0;
    while(true){
        std::cout << counter <<std::endl;
        act1.update(1);
        act2.update(1);
        if (collision(act1.get_bb(),act2.get_bb())){
            break;
        }
        counter++;
    }
    return 0;
}