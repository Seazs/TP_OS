int *f() {
  int i = 42; // i is a local variable so it is allocated on the stack and will be destroyed when the function returns
  int *p = &i;
  return p;
}
int g(int *p) {
  return *p; // the value of p is returned but p is destroyed so the value is undefined
}
int main() {
  return g(f());
}

// en gros on essaie d'accéder à une variable qui n'existe plus
// donc erreur comme le 