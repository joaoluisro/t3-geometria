#include <bits/stdc++.h>

using namespace std;

struct point{
  int x,y,z;
  point(int x_val = 0, int y_val = 0, int z_val = 0){
    x = x_val;
    y = y_val;
    z = z_val;
  }

  void print(){
    cout << x << " "<< y << " " << z << endl;
  }
};


point subtract(const point &a, const point &b){
  int x,y,z;
  x = b.x - a.x;
  y = b.y - a.y;
  z = b.z - a.z;
  return point(x,y,z);
}

point cross_product(const point &a, const point &b){
  int x,y,z;
  x = a.y * b.z - a.z * b.y;
  y = a.z * b.x - a.x * b.z;
  z = a.x * b.y - a.y * b.x;
  return point(x,y,z);
}

int dot_product(const point &a, const point &b){
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

struct face{
  int a,b,c;
  point normal;
  face(int a_val, int b_val, int c_val, const point &q){
    a = a_val;
    b = b_val;
    c = c_val;
    normal = q;
  }

  void print(){
    cout << a << " " << b << " " << c << endl;
    normal.print();
    cout << endl;
  }
};

struct convex_hull{
  vector<face> faces;
};

point* init_ch(point *v, int n, convex_hull &ch){
  bool *active = new bool[n];
  int *comb = new int[n];

  for(int i = 0; i < n; i++) comb[i] = i, active[i] = true;
  bool check = false;
  int a,b,c,q;

  while(!check){
    a = comb[0],  b = comb[1],  c = comb[2],  q = comb[3];
    point normal = cross_product(subtract(v[a],v[b]), subtract(v[a],v[c]));
    check = (dot_product(normal, subtract(v[a],v[q]))) > 0;
    next_permutation(comb, comb + n);
  }

  ch.faces.push_back(face(a,b,c, cross_product(subtract(v[a],v[b]), subtract(v[a],v[c]))));
  ch.faces.push_back(face(a,b,q, cross_product(subtract(v[a],v[b]), subtract(v[a],v[q]))));
  ch.faces.push_back(face(a,c,q, cross_product(subtract(v[a],v[c]), subtract(v[a],v[q]))));
  ch.faces.push_back(face(b,c,q, cross_product(subtract(v[b],v[c]), subtract(v[b],v[q]))));
  active[a] = false, active[b] = false, active[c] = false, active[q] = false;

  point *new_vertices = new point[n - 4];
  int j = 0;
  for(int i = 0; i < n; i++){
    if(active[i]){
      new_vertices[j] = v[i];
      j++;
    }
  }
  return new_vertices;
}

convex_hull solve(point *vertices, int n){

  // constrói o primeiro fecho com 4 vértices
  convex_hull ch;
  point *vert = init_ch(vertices, n, ch);

  bool conflict;
  int dot;

  // incrementa o ch
  for(int i = 0; i < n - 4; i++){
    conflict = false;
    for(int j = 0; j < ch.faces.size(); j++){

      dot = dot_product(ch.faces[j].normal, subtract(vertices[ch.faces[j].a],vert[i]));
      conflict = (dot > 0);
      if(conflict){

      }
    }
  }

  return ch;
}


int main(){

  // processa a entrada
  point *vertices;
  int n;
  cin >> n;
  int x,y,z;
  vertices = new point[n];

  for(int i = 0; i < n; i++){
    cin >> x >> y >> z;
    vertices[i] = point(x,y,z);
  }

  convex_hull ch = solve(vertices, n);
  for(int i = 0; i < 4;i++){
    ch.faces[i].print();
  }

}
