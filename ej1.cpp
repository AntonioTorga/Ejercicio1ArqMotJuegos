#include <iostream>
typedef struct  {
    int x,y;
} Vector2D;

class BoundingBox {
    public:
    BoundingBox();
    void set_izq(int x, int y){ izq_ = Vector2D{x,y};};
    void set_der(int x, int y){ der_ = Vector2D{x,y};};
    Vector2D get_izq() {return izq_;};
    Vector2D get_der() {return der_;};
    
    private:
    Vector2D izq_,der_;
};

BoundingBox::BoundingBox() {
    izq_ = Vector2D{1,1};
    der_ = Vector2D{-1,-1};
}

void enclose (BoundingBox& bb, const Vector2D& vec){
    Vector2D izq = bb.get_izq();
    Vector2D der = bb.get_der();
    int izq_x = izq.x;
    int izq_y = izq.y;
    int der_x = der.x;
    int der_y = der.y;
    
    if (izq_x>vec.x){
        izq_x = vec.x;
    }
    if (izq_y>vec.y){
        izq_y = vec.y;
    }
    if (der_x<vec.x){
        der_x = vec.x;
    }
    if (der_y<vec.y){
        der_y = vec.y;
    }
    bb.set_der(der_x,der_y);
    bb.set_izq(izq_x,izq_y);
}

bool collision(BoundingBox bb1,BoundingBox bb2){
    Vector2D izq1 = bb1.get_izq();
    Vector2D der1 = bb1.get_der();
    Vector2D izq2 = bb2.get_izq();
    Vector2D der2 = bb2.get_der();
    if(der1.x>=izq2.x and izq1.x <=der2.x and izq1.y<=der2.y and der1.y>=izq2.y){
        std::cout << "Collision \n";
        return true;
    }
    return false;
}

class Actor {
    public:
    Actor (const Vector2D& posicion2D, const Vector2D& velocidad2D, const BoundingBox bb);
    void update(int delta_tiempo);
    BoundingBox& get_bb(){return boundingbox_;}; 
    private:
    Vector2D posicion2D_;
    Vector2D velocidad2D_;
    BoundingBox boundingbox_;
};

Actor::Actor(const Vector2D& posicion2D, const Vector2D& velocidad2D, const BoundingBox bb){
    posicion2D_ = posicion2D;
    velocidad2D_=velocidad2D;
    boundingbox_=bb;
}
void Actor::update(int delta_tiempo){
    posicion2D_.x += delta_tiempo*velocidad2D_.x;
    posicion2D_.y += delta_tiempo*velocidad2D_.y;
    boundingbox_.set_izq(boundingbox_.get_izq().x+delta_tiempo*velocidad2D_.x, boundingbox_.get_izq().y+delta_tiempo*velocidad2D_.y);
    boundingbox_.set_der(boundingbox_.get_der().x+delta_tiempo*velocidad2D_.x, boundingbox_.get_der().y+delta_tiempo*velocidad2D_.y);
}
