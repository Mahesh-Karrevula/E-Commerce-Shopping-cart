#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib>

using namespace std;

class Product {public:
    int id;
    string name;
    double price;
    
    Product(int id, string name, double price) {
        this->id = id;
        this->name = name;
        this->price = price;
    }
};

class User {
public:
    string username;
    string password;
    
    User(string username, string password) {
        this->username = username;
        this->password = password;
    }

    bool checkPassword(string password) {
        return this->password == password;
    }
};

class CartItem {
public:
    Product product;
    int quantity;
    
    CartItem(Product product, int quantity) : product(product), quantity(quantity) {}
};

class ShoppingCart {
private:
    vector<CartItem> items;
    
public:
    void addItem(Product product, int quantity) {
        if (quantity <= 0) {
            cout << "Invalid quantity!" << endl;
            return;
        }
        items.push_back(CartItem(product, quantity));
    }
    
    void removeItem(int productId) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->product.id == productId) {
                items.erase(it);
                cout << "Item removed from cart!" << endl;
                return;
            }
        }
        cout << "Product not found in the cart!" << endl;
    }
    
    void viewCart() {
        if (items.empty()) {
            cout << "Your cart is empty!" << endl;
            return;
        }
        double total = 0;
        for (auto &item : items) {
            cout << "Product: " << item.product.name << ", Quantity: " << item.quantity 
                 << ", Price: $" << item.product.price * item.quantity << endl;
            total += item.product.price * item.quantity;
        }
        cout << "Total: $" << total << endl;
    }
    
    double checkout() {
        double total = 0;
        for (auto &item : items) {
            total += item.product.price * item.quantity;
        }
        cout << "Your order total is: $" << total << endl;
        return total;
    }
    
    void clearCart() {
        items.clear();
    }
};

class ECommerce {
private:
    vector<Product> products;
    vector<User> users;
    User *currentUser;
    ShoppingCart cart;
    
public:
    ECommerce() : currentUser(nullptr) {
        // Sample products
        products.push_back(Product(1, "Laptop", 999.99));
        products.push_back(Product(2, "Phone", 499.99));
        products.push_back(Product(3, "Headphones", 89.99));
        
        // Sample users
        users.push_back(User("admin", "password123"));
        users.push_back(User("user1", "password456"));
    }
    
    void signup() {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        
        users.push_back(User(username, password));
        cout << "Signup successful!" << endl;
    }
    
    bool login() {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        
        for (auto &user : users) {
            if (user.username == username && user.checkPassword(password)) {
                currentUser = &user;
                cout << "Login successful!" << endl;
                return true;
            }
        }
        
        cout << "Invalid credentials!" << endl;
        return false;
    }
    
    void displayProducts() {
        cout << "Available Products:" << endl;
        for (auto &product : products) {
            cout << "ID: " << product.id << ", Name: " << product.name << ", Price: $" << product.price << endl;
        }
    }
    
    void addToCart() {
        int productId, quantity;
        cout << "Enter product ID to add to cart: ";
        cin >> productId;
        cout << "Enter quantity: ";
        cin >> quantity;
        
        if (quantity <= 0) {
            cout << "Quantity must be positive!" << endl;
            return;
        }
        
        for (auto &product : products) {
            if (product.id == productId) {
                cart.addItem(product, quantity);
                cout << "Item added to cart!" << endl;
                return;
            }
        }
        cout << "Product not found!" << endl;
    }
    
    void removeFromCart() {
        int productId;
        cout << "Enter product ID to remove from cart: ";
        cin >> productId;
        
        cart.removeItem(productId);
    }
    
    void viewCart() {
        cart.viewCart();
    }
    
    void checkout() {
        double total = cart.checkout();
        cout << "Proceeding to checkout..." << endl;
        cout << "Total amount: $" << total << endl;
        cart.clearCart();
        cout << "Order placed successfully!" << endl;
    }
    
    void mainMenu() {
        int choice;
        while (true) {
            cout << "E-Commerce System" << endl;
            cout << "1. Login" << endl;
            cout << "2. Signup" << endl;
            cout << "3. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            
            switch (choice) {
                case 1:
                    if (login()) {
                        userMenu();
                    }
                    break;
                case 2:
                    signup();
                    break;
                case 3:
                    exit(0);
                default:
                    cout << "Invalid choice!" << endl;
            }
        }
    }
    
    void userMenu() {
        int choice;
        while (true) {
            cout << "User Menu" << endl;
            cout << "1. View Products" << endl;
            cout << "2. Add to Cart" << endl;
            cout << "3. Remove from Cart" << endl;
            cout << "4. View Cart" << endl;
            cout << "5. Checkout" << endl;
            cout << "6. Logout" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            
            switch (choice) {
                case 1:
                    displayProducts();
                    break;
                case 2:
                    addToCart();
                    break;
                case 3:
                    removeFromCart();
                    break;
                case 4:
                    viewCart();
                    break;
                case 5:
                    checkout();
                    return;
                case 6:
                    currentUser = nullptr;
                    cout << "Logged out!" << endl;
                    return;
                default:
                    cout << "Invalid choice!" << endl;
            }
        }
    }
};

int main() {
    ECommerce system;
    system.mainMenu();
    return 0;
}
