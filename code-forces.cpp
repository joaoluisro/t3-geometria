#include <bits/stdc++.h>

#define ll long long
#define sz(x) ((int) (x).size())
#define all(x) (x).begin(), (x).end()
#define vi vector<int>
#define pii pair<int, int>
#define rep(i, a, b) for(int i = (a); i < (b); i++)
using namespace std;
template<typename T>
using minpq = priority_queue<T, vector<T>, greater<T>>;

typedef long double ftype;

struct pt3 {
    ftype x, y, z;
    pt3(ftype x = 0, ftype y = 0, ftype z = 0) : x(x), y(y), z(z) {}
    pt3 operator-(const pt3 &o) const {
        return pt3(x - o.x, y - o.y, z - o.z);
    }
    pt3 cross(const pt3 &o) const {
        return pt3(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x);
    }
    ftype dot(const pt3 &o) const {
        return x * o.x + y * o.y + z * o.z;
    }
};

// A face is represented by the indices of its three points a, b, c.
// It also stores an outward-facing normal vector q
struct face {
    int a, b, c;
    pt3 q;
};

// modify this depending on the coordinate sizes in your use case
const ftype EPS = 1e-9;

vector<face> hull3(const vector<pt3> &p) {
    int n = sz(p);
    assert(n >= 3);
    vector<face> f;

    // Consider an edge (a->b) dead if it is not a CCW edge of some current face
    // If an edge is alive but not its reverse, this is an exposed edge.
    // We should add new faces on the exposed edges.
    vector<vector<bool>> dead(n, vector<bool>(n, true));
    auto add_face = [&](int a, int b, int c) {
        f.push_back({a, b, c, (p[b] - p[a]).cross(p[c] - p[a])});
        dead[a][b] = dead[b][c] = dead[c][a] = false;
    };

    // Initialize the convex hull of the first 3 points as a
    // triangular disk with two faces of opposite orientation
    add_face(0, 1, 2);
    add_face(0, 2, 1);
    rep(i, 3, n) {
        // f2 will be the list of faces invisible to the added point p[i]
        vector<face> f2;
        for(face &F : f) {
            if((p[i] - p[F.a]).dot(F.q) > EPS) {
                // this face is visible to the new point, so mark its edges as dead
                dead[F.a][F.b] = dead[F.b][F.c] = dead[F.c][F.a] = true;
            }else {
                f2.push_back(F);
            }
        }
        // Add a new face for each exposed edge.
        // Only check edges of alive faces for being exposed.
        f.clear();
        for(face &F : f2) {
            int arr[3] = {F.a, F.b, F.c};
            rep(j, 0, 3) {
                int a = arr[j], b = arr[(j + 1) % 3];
                if(dead[b][a]) {
                    add_face(b, a, i);
                }
            }
        }
        f.insert(f.end(), all(f2));
    }
    return f;
}


int main(){

  // processa a entrada
  vector<pt3> vertices;
  int n;
  cin >> n;
  int x,y,z;

  for(int i = 0; i < n; i++){
    cin >> x >> y >> z;
    vertices.push_back(pt3(x,y,z));
  }
  vector<face> f = hull3(vertices);
  cout << f.size();
}
