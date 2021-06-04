#include <iostream>
#include <memory>

class Product {
public:
    virtual void someOperation() = 0;
    virtual ~Product() {}
};

class Product1 : public Product {
public:
    virtual void someOperation() {
        std::cout << "Operation on Product1" << std::endl;
    }
    virtual ~Product1() {}
};

class Product2 : public Product{
public:
    virtual void someOperation() {
        std::cout << "Operation on Product2" << std::endl;
    }
    virtual ~Product2() {}
};

class Creator {
public:
    virtual std::shared_ptr<Product> createProduct() = 0;
    virtual ~Creator() {}
};

class ConcreteCreator1 : public Creator {
public:
    virtual std::shared_ptr<Product> createProduct() {
        return std::make_shared<Product1>();
    }
    virtual ~ConcreteCreator1() {}
};

class ConcreteCreator2 : public Creator {
public:
    virtual std::shared_ptr<Product> createProduct() {
        return std::make_shared<Product2>();
    }
    virtual ~ConcreteCreator2() {}
};

void clientOperation(std::shared_ptr<Creator> creator) {
    auto product = creator->createProduct();
    product->someOperation();
}

int main() {
    auto c1 = std::make_shared<ConcreteCreator1>();
    clientOperation(c1);

    auto c2 = std::make_shared<ConcreteCreator2>();
    clientOperation(c2);
    return 0;
}
