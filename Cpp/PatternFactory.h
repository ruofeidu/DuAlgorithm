#pragma once
#include <iostream>
using namespace std;

class Product {
 public:
  virtual void Show() = 0;
};

class ProductX : public Product {
 public:
  void Show() { cout << "I'm ProductX" << endl; }
};

class ProductY : public Product {
 public:
  void Show() { cout << "I'm ProductY" << endl; }
};

class Factory {
 public:
  virtual Product *CreateProduct() = 0;
};

class FactoryX : public Factory {
 public:
  Product *CreateProduct() { return new ProductX(); }
};

class FactoryY : public Factory {
 public:
  Product *CreateProduct() { return new ProductY(); }
};
