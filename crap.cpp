#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cmath>

using namespace std;

struct Point {
    int r, c;
};

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

vector<Point> tracePath(vector<vector<char>>& grid, char symbol) {
    int n = grid.size();
    int m = grid[0].size();
    vector<Point> path;
    
    // Find starting point (on edge)
    Point start = {-1, -1};
    for (int i = 0; i < n && start.r == -1; i++) {
        for (int j = 0; j < m && start.c == -1; j++) {
            if (grid[i][j] == symbol) {
                if (i == 0 || i == n-1 || j == 0 || j == m-1) {
                    start = {i, j};
                }
            }
        }
    }
    
    if (start.r == -1) return path;
    
    // Trace the path
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    Point curr = start;
    
    while (true) {
        path.push_back(curr);
        visited[curr.r][curr.c] = true;
        
        bool found = false;
        for (int d = 0; d < 4; d++) {
            int nr = curr.r + dr[d];
            int nc = curr.c + dc[d];
            
            if (nr >= 0 && nr < n && nc >= 0 && nc < m && 
                !visited[nr][nc] && grid[nr][nc] == symbol) {
                curr = {nr, nc};
                found = true;
                break;
            }
        }
        
        if (!found) break;
    }
    
    return path;
}

int calculateWindingNumber(vector<Point>& cable, vector<Point>& rod, 
                           vector<vector<char>>& grid) {
    int winding = 0;
    
    // For each intersection point
    for (int i = 1; i < cable.size() - 1; i++) {
        Point curr = cable[i];
        Point prev = cable[i-1];
        Point next = cable[i+1];
        
        // Check if this point is also on rod
        bool isIntersection = false;
        for (auto& rp : rod) {
            if (rp.r == curr.r && rp.c == curr.c) {
                isIntersection = true;
                break;
            }
        }
        
        if (!isIntersection) continue;
        
        // Calculate cable direction
        int cableDir = 0;
        if (next.c > prev.c) cableDir = 0; // right
        else if (next.c < prev.c) cableDir = 1; // left
        else if (next.r > prev.r) cableDir = 2; // down
        else if (next.r < prev.r) cableDir = 3; // up
        
        // Determine rod orientation
        bool rodHorizontal = false;
        for (int j = 1; j < rod.size(); j++) {
            if (rod[j].r == rod[j-1].r) {
                rodHorizontal = true;
                break;
            }
        }
        
        // Calculate signed crossing based on cable direction and who's on top
        bool cableOnTop = (grid[curr.r][curr.c] == 'C');
        
        if (rodHorizontal) {
            if (cableDir == 2) { // cable going down
                winding += cableOnTop ? 1 : -1;
            } else if (cableDir == 3) { // cable going up
                winding += cableOnTop ? -1 : 1;
            }
        } else { // rod vertical
            if (cableDir == 0) { // cable going right
                winding += cableOnTop ? -1 : 1;
            } else if (cableDir == 1) { // cable going left
                winding += cableOnTop ? 1 : -1;
            }
        }
    }
    
    return abs(winding);
}

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<char>> grid(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    
    vector<Point> cable = tracePath(grid, 'C');
    vector<Point> rod = tracePath(grid, 'R');
    
    int result = calculateWindingNumber(cable, rod, grid);
    
    cout << result << endl;
    
    return 0;
}