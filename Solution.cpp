#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

#define _DEBUG_

#define _DEBUG_COORD

namespace user
{
    struct coordinate
    {
        public: 
            int x; int y;
            coordinate() : x(0), y(0) {};
            coordinate(int _x, int _y) : x(_x), y(_y) {};
            coordinate(const coordinate& coord) : x(coord.x), y(coord.y) { };
            
            coordinate& operator = (const coordinate& right) {
                //check self-assignment
                if (this == &right) {
                    return *this;
                }
                this->x = right.x;
                this->y = right.y;
                return *this;
            }
    
        private:
            friend const coordinate operator+(const coordinate& left,const coordinate& right);
            friend const coordinate operator+=(const coordinate& left, const coordinate& right);
            friend const coordinate operator/(const coordinate& left, const coordinate& right);
            friend const coordinate operator/(const coordinate& left, int right);
        };
    
    const coordinate operator+(const coordinate& left, coordinate& right) 
    {
        return coordinate(left.x + right.x, left.y + right.y);
    }
    
    const coordinate operator+=(coordinate& left, coordinate& right) 
    {
        return coordinate(left + right);
    }
    
    const coordinate operator/(const coordinate& left, const coordinate& right) 
    {
        coordinate coord;
        coord.x = left.x / right.x;
        coord.y = left.y / right.x;
        
        #ifdef _DEBUG_COORD
            cerr << "|=========================|" << endl;
            cerr << "operator/(coordinate, coordinate)" << endl;
            cerr << coord.x << " " << coord.y << endl;
        #endif
        
        return coord;
    }
    
    const coordinate operator/(const coordinate& left, int right) 
    {
        coordinate coord;
        coord.x = left.x / right;
        coord.y = left.y / right;
        
        #ifdef _DEBUG_COORD
            cerr << "|=========================|" << endl;
            cerr << "operator/(coordinate, int)" << endl;
            cerr << coord.x << " " << coord.y << endl;
        #endif
        
        return coord;
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Rectangle {
        Rectangle(user::coordinate _vertex1, user::coordinate _vertex2)  : 
            vertex1(_vertex1), 
            vertex2(_vertex2)
        {
            #ifdef _DEBUG_
                cerr << "|-------------------|\n";
                cerr << "Constructor Rectangle \n";
                cerr << "vertex1 " << _vertex1.x << " " << _vertex1.y << "\n";
                cerr << "vertex2 " << _vertex2.x << " " << _vertex2.y << "\n\n\n";
            #endif
        }
        
        user::coordinate getRectangleCenter()
        {
            return user::coordinate(vertex2.x / 2, vertex1.y + (abs(vertex2.y - vertex1.y) / 2));
        }
        
        user::coordinate vertex1; /* HIGHT rectansle points */  
        user::coordinate vertex2; /* WIDTH rectansle points */
};     
            

class Search
{
    public:
            user::coordinate convertCoordinate(int x, int y)
            {
                 return user::coordinate(x, (H - y));
            }
            
            void Move(std::string position)
            {
                bool horizontalAlignment = H <= 3 ? true : false;
                bool firstMove = false;
                
                #ifdef _DEBUG_
                        cerr << "\n|-------------------|\n";
                        cerr << "Move: " << position << endl << endl;
                #endif
                
                if(position == "UNKNOWN")
                {
                    rectangles.push(Rectangle(user::coordinate(0, 0), user::coordinate(W, H / 2)));
                    rectangles.push(Rectangle(user::coordinate(0, H / 2), user::coordinate(W, H)));

                    cout << rectangles.top().getRectangleCenter().x << " " << rectangles.top().getRectangleCenter().y << endl;
                    //rectangles.pop();
                }
                
                if(position == "WARMER")
                {
                    if(horizontalAlignment == true)
                    {
                        //W = rectangles.top().vertex2.x;
                    } else 
                    {
                        if ()
                        #ifdef _DEBUG_
                            cerr << "\n|-------------------|\n";
                            cerr << "H: " << abs(rectangles.top().vertex1.y - rectangles.top().vertex2.y) << endl << endl;
                        #endif
                        
                        H = abs(rectangles.top().vertex1.y - rectangles.top().vertex2.y); /* width not change with vertical aligment */
                        
                        user::coordinate coordLastRectangleV1 =  rectangles.top().vertex1;
                        user::coordinate coordLastRectangleV2 =  rectangles.top().vertex2;
                        
                         #ifdef _DEBUG_
                            cerr << "\n|-------------------|\n";
                            cerr << "coordLastRectangleV1: " << coordLastRectangleV1.x << "  " <<  coordLastRectangleV1.y << endl;
                        #endif
                        
                        stack<Rectangle>().swap(rectangles); //clear stack
    
                        rectangles.push(Rectangle(user::coordinate(0, coordLastRectangleV1.y), user::coordinate(W, coordLastRectangleV1.y +  H / 2)));
                        rectangles.push(Rectangle(user::coordinate(0, coordLastRectangleV1.y +  H / 2), user::coordinate(W, coordLastRectangleV1.y +  H)));
                        
                        cout << rectangles.top().getRectangleCenter().x << " " << rectangles.top().getRectangleCenter().y << endl;
                    }
                }
                
                if(position == "COLDER")
                {
                    rectangles.pop();
                    cout << rectangles.top().getRectangleCenter().x << " " << rectangles.top().getRectangleCenter().y << endl;
                }
                
                if(position == "SAME")
                {
                    cout << "stop stop stop" << endl;
                }
            }
                        
            Search(int _H, int _W) : H(_H - 1), W(_W - 1) {};
    private:   
            //Triangle tr(user::coordinate(0, 16), user::coordinate(5, 0), user::coordinate(0, 0));
            std::stack<Rectangle> rectangles;
            int W, H;
};


int main()
{
    int W; // width of the building.
    int H; // height of the building.
    cin >> W >> H; cin.ignore();
    cerr << "H: " << H << " W:" << W << endl;
    
    Search tr(H, W);
    
    int N; // maximum number of turns before game over.
    cin >> N; cin.ignore();
    int X0;
    int Y0;
    cin >> X0 >> Y0; cin.ignore();
    
    // game loop
    while (1) {
        string bombDir; // Current distance to the bomb compared to previous distance (COLDER, WARMER, SAME or UNKNOWN)
        cin >> bombDir; cin.ignore();
        cerr << bombDir << endl;
        
        //cout << W / 2 << " " << (H / 2) / 2 << endl;
        //cout << "0 31" << endl;
        //cout << "17 0" << endl;
        //cout << "9 15" << endl;
        //cout <<"asdasdad" << endl;
        tr.Move(bombDir);
    }
}
