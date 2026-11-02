#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cctype>


using namespace std;

struct User
{
string fullName;
string email;
string phone;
string password;

};

struct Product
{
    int id;
    string name;
    string category;
   string description;
    double price;
    int stock;
};

struct CartItem
{
    int userIndex;
    int ProductId;
    int quantity;
};

void addProduct(vector<Product>& products)
{
    Product newProduct;

    cout << "\n========== ADD NEW PRODUCT ==========\n";

    cout << "Enter product name: ";
    getline(cin, newProduct.name);

    cout << "Enter product category: ";
    getline(cin, newProduct.category);

    cout << "Enter product description: ";
    getline(cin, newProduct.description);

    cout << "Enter product price: ";
    cin >> newProduct.price;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nError: Invalid price!\n";
        return;
    }

    if (newProduct.price <= 0)
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nError: Price must be greater than zero!\n";
        return;
    }

    cout << "Enter product stock: ";
    cin >> newProduct.stock;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nError: Invalid stock quantity!\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (newProduct.stock < 0)
    {
        cout << "\nError: Stock cannot be negative!\n";
        return;
    }

    newProduct.id = 1001 + products.size();

    products.push_back(newProduct);

    cout << "\nProduct added successfully!\n";
    cout << "Product ID: " << newProduct.id << endl;
}

void viewAllProducts(const vector<Product>& products)
{
cout << "\n========== ALL PRODUCTS ==========\n";


if (products.empty())
{
    cout << "No products available.\n";
    return;
}

for (const Product& product : products)
{
    cout << "\nProduct ID: " << product.id << '\n';
    cout << "Name: " << product.name << '\n';
    cout << "Category: " << product.category << '\n';
    cout << "Description: " << product.description << '\n';
    cout << "Price: " << product.price << '\n';
    cout << "Stock: " << product.stock << '\n';

    cout << "------------------------------\n";
}

}

void searchProducts(const vector<Product>& products)
{
    string searchName;

    cout << "\nEnter product name to search: ";
    getline(cin, searchName);

    bool found = false;

    for (const Product& product : products)
    {
        if (product.name.find(searchName) != string::npos)
        {
            cout << "\nProduct Found!\n";
            cout << "ID: " << product.id << '\n';
            cout << "Name: " << product.name << '\n';
            cout << "Category: " << product.category << '\n';
            cout << "Description: " << product.description << '\n';
            cout << "Price: " << product.price << '\n';
            cout << "Stock: " << product.stock << '\n';

            found = true;
        }
    }

    if (!found)
    {
        cout << "\nNo product found!\n";
    }
}

void editProduct(vector<Product>& products)
{
    int productId;
    bool found = false;

    cout << "\nEnter Product ID to edit: ";
    cin >> productId;

    for (Product& product : products)
    {
        if (product.id == productId)
        {
            found = true;

            cout << "\nProduct Found!\n";
            cout << "Name: " << product.name << '\n';
            cout << "Price: " << product.price << '\n';
            cout << "\nWhich information do you want to edit?\n";
cout << "1. Name\n";
cout << "2. Category\n";
cout << "3. Description\n";
cout << "4. Price\n";
cout << "5. Stock\n";

int choice;
cout << "Enter your choice: ";
cin >> choice;

cin.ignore(numeric_limits<streamsize>::max(), '\n');

switch (choice)
{
    case 1:
        cout << "Enter new name: ";
        getline(cin, product.name);
        break;

    case 2:
        cout << "Enter new category: ";
        getline(cin, product.category);
        break;

    case 3:
        cout << "Enter new description: ";
        getline(cin, product.description);
        break;

    case 4:
        cout << "Enter new price: ";
        cin >> product.price;
        break;

    case 5:
        cout << "Enter new stock: ";
        cin >> product.stock;
        break;

    default:
        cout << "Invalid choice!\n";
        return;
}

cout << "\nProduct updated successfully!\n";
            break;
        }
    }

    if (!found)
    {
        cout << "\nProduct not found!\n";
    }
}

void deleteProduct(vector<Product>& products)
{
    int productId;

    if (products.empty())
    {
        cout << "\nNo products available to delete!\n";
        return;
    }

    cout << "\nEnter Product ID to delete: ";
    cin >> productId;

    for (size_t i = 0; i < products.size(); i++)
    {
        if (products[i].id == productId)
        {
            cout << "\nProduct Found!\n";
            cout << "Name: " << products[i].name << '\n';

            char confirm;

            cout << "\nAre you sure you want to delete this product? (y/n): ";
            cin >> confirm;

            if (confirm == 'y' || confirm == 'Y')
            {
                products.erase(products.begin() + i);
                cout << "\nProduct deleted successfully!\n";
            }
            else
            {
                cout << "\nDeletion cancelled!\n";
            }

            return;
        }
    }

    cout << "\nProduct not found!\n";
}

void addToCart(
    const vector<Product>& products,
    vector<CartItem>& cart,
    int userIndex)
{
    int productId;
    int quantity;

    cout << "\nEnter Product ID: ";
    cin >> productId;

    cout << "Enter Quantity: ";
    cin >> quantity;

    if (quantity <= 0)
    {
        cout << "\nInvalid quantity!\n";
        return;
    }

    for (const Product& product : products)
    {
        if (product.id == productId)
        {
            if (quantity > product.stock)
            {
                cout << "\nNot enough stock!\n";
                return;
            }

            for (CartItem& item : cart)
            {
                if (item.userIndex == userIndex &&
                    item.ProductId == productId)
                {
                    item.quantity += quantity;

                    cout << "\nProduct quantity updated in cart!\n";
                    return;
                }
            }

            CartItem newItem;

            newItem.userIndex = userIndex;
            newItem.ProductId = productId;
            newItem.quantity = quantity;

            cart.push_back(newItem);

            cout << "\nProduct added to cart successfully!\n";
            return;
        }
    }

    cout << "\nProduct not found!\n";
}

void viewCart(
    const vector<Product>& products,
    const vector<CartItem>& cart,
    int userIndex)
{
    cout << "\n========== MY SHOPPING CART ==========\n";

    bool found = false;
    double total = 0;

    for (const CartItem& item : cart)
    {
        if (item.userIndex == userIndex)
        {
            for (const Product& product : products)
            {
                if (product.id == item.ProductId)
                {
                    double subtotal = product.price * item.quantity;

                    cout << "\nProduct: " << product.name << '\n';
                    cout << "Price: " << product.price << '\n';
                    cout << "Quantity: " << item.quantity << '\n';
                    cout << "Subtotal: " << subtotal << '\n';

                    total += subtotal;
                    found = true;
                    break;
                }
            }
        }
    }

    if (!found)
    {
        cout << "\nYour cart is empty!\n";
        return;
    }

    cout << "\nTotal Amount: " << total << '\n';
}

void removeFromCart(vector<CartItem>& cart, int userIndex)
{
    int productId;
    bool found = false;

    cout << "\nEnter Product ID to remove: ";
    cin >> productId;

    for (size_t i = 0; i < cart.size(); i++)
    {
        if (cart[i].userIndex == userIndex &&
            cart[i].ProductId == productId)
        {
            cart.erase(cart.begin() + i);

            cout << "\nProduct removed from cart successfully!\n";

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\nProduct not found in your cart!\n";
    }
}



bool emailExists(const vector<User>& users, const string& email, int currentUserIndex)
{
    for (size_t i = 0; i < users.size(); i++)
    {
        if (static_cast<int>(i) != currentUserIndex &&
            users[i].email == email)
        {
            return true;
        }
    }

    return false;
}
bool isValidEmail(const string& email)
{
    size_t at = email.find('@');

    if (at == string::npos || at == 0)
    {
        return false;
    }

    size_t dot = email.find('.', at);

    if (dot == string::npos || dot == at + 1 || dot == email.length() - 1)
    {
        return false;
    }

    return true;
}
bool normalizePhone(string& phone)
{
    string cleaned = "";

    
    for (char ch : phone)
    {
        if (ch != ' ' && ch != '-')
        {
            cleaned += ch;
        }
    }

    if (cleaned.substr(0, 2) == "00")
    {
        cleaned = "+" + cleaned.substr(2);
    }

    
    if (cleaned.empty() || cleaned[0] != '+')
    {
        return false;
    }

    
    string digits = cleaned.substr(1);

    if (digits.empty() || digits.length() > 15)
    {
        return false;
    }

    for (char ch : digits)
    {
        if (!isdigit(static_cast<unsigned char>(ch)))
        {
            return false;
        }
    }

    
    phone = cleaned;

    return true;
    }
bool phoneExists(const vector<User>& users, const string& phone, int currentUserIndex)
{
    for (size_t i = 0; i < users.size(); i++)
    {
        if (static_cast<int>(i) != currentUserIndex &&
            users[i].phone == phone)
        {
            return true;
        }
    }

    return false;
}
bool isValidPassword(const string& password)
{
    bool hasLetter = false;
    bool hasDigit = false;

    for (char ch : password)
    {
        if (isalpha(static_cast<unsigned char>(ch)))
        {
            hasLetter = true;
        }

        if (isdigit(static_cast<unsigned char>(ch)))
        {
            hasDigit = true;
        }
    }

    return password.length() >= 8 && hasLetter && hasDigit;
}
int loginUser(const vector<User>& users)
{
    string identifier;
    string password;

    cout << "\n--- User Login ---\n";

    cout << "Enter your email or phone number: ";
    getline(cin, identifier);

    cout << "Enter your password: ";
    getline(cin, password);

    for (size_t i = 0; i < users.size(); i++)
    {
        if (users[i].email == identifier || users[i].phone == identifier)
        {
            if (users[i].password == password)
            {
                cout << "\nWelcome back to NOVARA!\n";
                cout << "Login successful.\n";

                return static_cast < int > (i) ;
            }
            else
            {
                cout << "\nError: Incorrect password!\n";

                return -1;
            }
        }
    }

    cout << "\nError: Account not found!\n";

    return -1;
}
void editProfile(vector<User>& users, int userIndex)
{
    string newName;
    string newEmail;
    string newPhone;

    cout << "\n--- Edit My Profile ---\n";

    cout << "Enter new full name: ";
    getline(cin, newName);

    if (newName.empty())
    {
        cout << "\nError: Full name cannot be empty!\n";
        return;
    }

    cout << "Enter new email: ";
    getline(cin, newEmail);

    if (!isValidEmail(newEmail))
    {
        cout << "\nError: Invalid email address!\n";
        return;
    }

    if (emailExists(users, newEmail, userIndex))
    {
        cout << "\nError: This email is already registered!\n";
        return;
    }

    cout << "Enter new phone number: ";
    getline(cin, newPhone);

    if (!normalizePhone(newPhone))
    {
        cout << "\nError: Invalid phone number!\n";
        return;
    }

    if (phoneExists(users, newPhone, userIndex))
    {
        cout << "\nError: This phone number is already registered!\n";
        return;
    }

    users[userIndex].fullName = newName;
    users[userIndex].email = newEmail;
    users[userIndex].phone = newPhone;

    cout << "\nProfile updated successfully!\n";
}
void changePassword(vector<User>& users, int userIndex)
{
    string currentPassword;
    string newPassword;
    string confirmPassword;

    cout << "\n--- Change Password ---\n";


    cout << "Enter current password: ";
    getline(cin, currentPassword);

    if (currentPassword != users[userIndex].password)
    {
        cout << "\nError: Current password is incorrect!\n";
        return;
    }

    cout << "Enter new password: ";
    getline(cin, newPassword);

    if (!isValidPassword(newPassword))
    {
        cout << "\nError: Password must contain at least 8 characters, including letters and numbers!\n";
        return;
    }

    cout << "Confirm new password: ";
    getline(cin, confirmPassword);


    if (newPassword != confirmPassword)
    {
        cout << "\nError: Passwords do not match!\n";
        return;
    }

    users[userIndex].password = newPassword;

    cout << "\nPassword changed successfully!\n";
}
void userDashboard(vector < User>& users, vector<Product > & products, vector<CartItem>& cart, int userIndex)
{
    int choice;

    while (true)
    {
        cout << "\n======================\n";
        cout << "     NOVARA USER PANEL\n";
        cout << "======================\n";

        cout << "Welcome, " << users[userIndex].fullName << "!\n";

        cout << "\n1. View My Profile\n";
        cout << "2. Edit My Profile\n";
        cout << "3. Change Password\n";
        cout << "4. Logout\n";
        cout << "5. Add Product to Cart\n";
        cout << "6. View My Cart\n";
        cout << "7. Remove Product from Cart\n";

        cout << "\nChoose an option: ";

        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:

            cout << "\n--- My Profile ---\n";

            cout << "Full Name: " << users[userIndex].fullName << endl;
            cout << "Email: " << users[userIndex].email << endl;
            cout << "Phone: " << users[userIndex].phone << endl;

                break;

        case 2:

            editProfile(users, userIndex);

                break;

        case 3:

            changePassword(users, userIndex);

                break;

        case 4:

            cout << "\nYou have successfully logged out!\n";

                return;
        case 5:
            addToCart(products, cart, userIndex);
                break;


        case 6:
            viewCart(products, cart, userIndex);
                break;
        case 7:
            removeFromCart(cart, userIndex);
                break;

        default:

            cout << "\nInvalid option! Try again.\n";
        }
    }
}

void registerUser(vector<User>& users){
    User newUser;
        cout<<"\n--- User Registration---\n";

        cout<<"Enter your full name\n";
        getline(cin, newUser.fullName);

    if(newUser.fullName.empty()){
        cout<<"\nError : Full name cannot be empty!\n";
            return;
    }

        cout<<"Enter your Email\n";
        getline(cin, newUser. email);
if (!isValidEmail(newUser.email))
{
    cout << "\nInvalid email address!\n";
    return;
}

if (emailExists(users, newUser.email, -1))
{
    cout << "\nThis email is already registered!\n";
    return;
}

        cout<<"Enter your phone number\n";
        getline(cin, newUser.phone);

    if (!normalizePhone(newUser.phone))
    {
        cout<<"\nInvalid international phone number!\n";
            return;
    }
    if (phoneExists(users, newUser.phone, -1)){

        cout<<"\nThis phone number is already registered!\n";
            return;
    }

        cout<<"Enter your password\n";
        getline(cin, newUser.password);

if (!isValidPassword(newUser.password))
{
    cout << "\nError: Password must contain at least 8 characters, including letters and numbers!\n";
    return;
}
        users.push_back(newUser);

        cout<<"\n Registration completed successfully!\n";


}

int main()
{
  
    vector<User> users;
    vector<Product> Products;
    vector<CartItem> cart;

    int choice;

    while (true)
    {
        cout << "\n===========================\n";
        cout << "     WELCOME TO NOVARA\n";
        cout << "===========================\n";

        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. add product\n";
        cout << "4. View All Products\n";
        cout << "5. Exit\n";
        cout << "6. Search Products\n";
        cout << "7. Edit Product\n";
        cout << "8. Delete Product\n";
      
      
     

        cout << "\nChoose an option: ";

        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
            case 1:

                registerUser(users);

                break;

            case 2:
            {
                int userIndex = loginUser(users);

                if (userIndex != -1)
                {
                  userDashboard(users, Products, cart, userIndex);
                }

                break;
            }

        
        case 3:

            addProduct(Products);

                break;
        case 4:
            viewAllProducts(Products);
                 break;
        case 5:

            cout << "Thank you for using NOVARA!\n";

                return 0;
        case 6:
            searchProducts(Products);
                break;

        case 7:
            editProduct(Products);
                break;
        case 8:
            deleteProduct(Products);
                break;
     

        default:

            cout << "Invalid option! Try again.\n";
        }
    }

    return 0;
}