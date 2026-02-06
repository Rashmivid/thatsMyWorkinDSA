#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
};

struct Slide {
    Point start, end;
    
    bool isOnSlide(int x, int y) {
        int minX = min(start.x, end.x);
        int maxX = max(start.x, end.x);
        int minY = min(start.y, end.y);
        int maxY = max(start.y, end.y);
        
        if (x < minX || x > maxX || y < minY || y > maxY) return false;
   
        int dx = end.x - start.x;
        int dy = end.y - start.y;
        int dx2 = x - start.x;
        int dy2 = y - start.y;
        
        return dx * dy2 == dy * dx2;
    }
    
    int getSlope() {
        if (end.x > start.x && end.y > start.y) return 1;
        if (end.x < start.x && end.y < start.y) return 1;
        return -1;
    }
};

pair<int, int> simulate(vector<Slide>& slides, int startX, int startY, int energy) {
    int x = startX, y = startY;
    
    while (energy > 0 && y > 0) {
        Slide* currentSlide = nullptr;
        for (auto& slide : slides) {
            if (slide.isOnSlide(x, y)) {
                currentSlide = &slide;
                break;
            }
        }
        
        if (currentSlide != nullptr) {
            int slope = currentSlide->getSlope();
            int dx, dy;
            if (slope == 1) { 
                if (currentSlide->start.x < currentSlide->end.x) {
                    dx = -1; dy = -1;
                } else {
                    dx = 1; dy = 1;
                }
            } else { 
                if (currentSlide->start.x < currentSlide->end.x) {
                    dx = 1; dy = -1;
                } else {
                    dx = -1; dy = 1;
                }
            }
            if (dy > 0) {
                dx = -dx;
                dy = -dy;
            }
            
            int nx = x + dx;
            int ny = y + dy;
            
            if (currentSlide->isOnSlide(nx, ny) && energy > 0) {
                x = nx;
                y = ny;
                energy--;
            } else {
                bool moved = false;
                for (int checkY = y - 1; checkY >= 0; checkY--) {
                    bool onSlide = false;
                    for (auto& slide : slides) {
                        if (slide.isOnSlide(x, checkY)) {
                            y = checkY;
                            onSlide = true;
                            moved = true;
                            break;
                        }
                    }
                    if (onSlide) break;
                }
                
                if (!moved) {
                    // Check if stuck and need to unlock
                    bool hasSlideBelow = false;
                    for (auto& slide : slides) {
                        if (slide.isOnSlide(x, y - 1)) {
                            hasSlideBelow = true;
                            break;
                        }
                    }
                    
                    if (hasSlideBelow || y == 0) {
                        break;
                    }
                    
                    // Try to unlock
                    int unlockCost = x * y;
                    if (energy >= unlockCost) {
                        energy -= unlockCost;
                    } else {
                        break;
                    }
                }
            }
        } else {
            bool landed = false;
            for (int checkY = y - 1; checkY >= 0; checkY--) {
                for (auto& slide : slides) {
                    if (slide.isOnSlide(x, checkY)) {
                        y = checkY;
                        landed = true;
                        break;
                    }
                }
                if (landed) break;
            }
            
            if (!landed) {
                y = 0; // Hit ground
                break;
            }
        }
    }
    
    return {x, y};
}

int main() {
    int n;
    cin >> n;
    
    vector<Slide> slides(n);
    for (int i = 0; i < n; i++) {
        cin >> slides[i].start.x >> slides[i].start.y 
            >> slides[i].end.x >> slides[i].end.y;
    }
    
    int startX, startY, energy;
    cin >> startX >> startY >> energy;
    
    auto result = simulate(slides, startX, startY, energy);
    cout << result.first << " " << result.second << endl;
    
    return 0;
}