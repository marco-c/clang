// RUN: clang -fsyntax-only -verify %s 
struct X { 
  X();
  X(int); 
};

X operator+(X, X);
X operator-(X, X) { X x; return x; }

struct Y {
  Y operator-() const;
  void operator()(int x = 17) const;
  int operator[](int);

  static int operator+(Y, Y); // expected-error{{overloaded 'operator+' cannot be a static member function}}
};


void f(X x) {
  x = operator+(x, x);
}

X operator+(int, float); // expected-error{{overloaded 'operator+' must have at least one parameter of class or enumeration type}}

X operator*(X, X = 5); // expected-error{{parameter of overloaded 'operator*' cannot have a default argument}}

X operator/(X, X, ...); // expected-error{{overloaded 'operator/' cannot be variadic}}

X operator%(Y); // expected-error{{overloaded 'operator%' must be a binary operator (has 1 parameter)}}

void operator()(Y&, int, int); // expected-error{{overloaded 'operator()' must be a non-static member function}}

typedef int INT;
typedef float FLOAT;
Y& operator++(Y&);
Y operator++(Y&, INT);
X operator++(X&, FLOAT); // expected-error{{parameter of overloaded post-increment operator must have type 'int' (not 'float')}}

int operator+; // expected-error{{'operator+' cannot be the name of a variable or data member}}
