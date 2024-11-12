#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std; // Thêm namespace std

// Cấu trúc để lưu thông tin sản phẩm
struct Product {
    string name;
    double price;
    int rating;
};

// Hàm đọc dữ liệu từ file CSV và lưu vào vector
void readCSV(const string& filename, vector<Product>& products) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Không thể mở file: " << filename << endl;
        return;
    }

    string line;
    // Bỏ qua dòng tiêu đề
    getline(file, line);

    // Đọc từng dòng dữ liệu
    while (getline(file, line)) {
        stringstream ss(line);
        Product product;
        string priceStr, ratingStr;

        getline(ss, product.name, ',');   // Đọc tên sản phẩm
        getline(ss, priceStr, ',');       // Đọc giá (chuỗi)
        getline(ss, ratingStr, ',');      // Đọc xếp hạng (chuỗi)

        // Chuyển đổi chuỗi thành số
        product.price = stod(priceStr);
        product.rating = stoi(ratingStr);

        products.push_back(product);
    }
}

// Hàm sắp xếp theo giá (tăng dần)
bool compareByPrice(const Product& a, const Product& b) {
    return a.price < b.price;
}

// Hàm sắp xếp theo xếp hạng (giảm dần)
bool compareByRating(const Product& a, const Product& b) {
    return a.rating > b.rating;
}

int main() {
    vector<Product> products;
    readCSV("ElectronicsProductsPricingData.csv", products);

    if (products.empty()) {
        cerr << "Không có dữ liệu để sắp xếp." << endl;
        return 1;
    }

    // Sắp xếp sản phẩm theo giá
    sort(products.begin(), products.end(), compareByPrice);
    cout << "Sản phẩm sắp xếp theo giá (tăng dần):\n";
    for (const auto& product : products) {
        cout << product.name << " - Giá: " << product.price << ", Xếp hạng: " << product.rating << "\n";
    }

    // Sắp xếp sản phẩm theo xếp hạng
    sort(products.begin(), products.end(), compareByRating);
    cout << "\nSản phẩm sắp xếp theo xếp hạng (giảm dần):\n";
    for (const auto& product : products) {
        cout << product.name << " - Giá: " << product.price << ", Xếp hạng: " << product.rating << "\n";
    }

    return 0;
}
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std; // Thêm namespace std

// Cấu trúc để lưu thông tin sản phẩm
struct Product {
    string name;
    double price;
    int rating;
};

// Hàm đọc dữ liệu từ file CSV và lưu vào vector
void readCSV(const string& filename, vector<Product>& products) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Không thể mở file: " << filename << endl;
        return;
    }

    string line;
    // Bỏ qua dòng tiêu đề
    getline(file, line);

    // Đọc từng dòng dữ liệu
    while (getline(file, line)) {
        stringstream ss(line);
        Product product;
        string priceStr, ratingStr;

        getline(ss, product.name, ',');   // Đọc tên sản phẩm
        getline(ss, priceStr, ',');       // Đọc giá (chuỗi)
        getline(ss, ratingStr, ',');      // Đọc xếp hạng (chuỗi)

        // Chuyển đổi chuỗi thành số
        product.price = stod(priceStr);
        product.rating = stoi(ratingStr);

        products.push_back(product);
    }
}

// Hàm sắp xếp theo giá (tăng dần)
bool compareByPrice(const Product& a, const Product& b) {
    return a.price < b.price;
}

// Hàm sắp xếp theo xếp hạng (giảm dần)
bool compareByRating(const Product& a, const Product& b) {
    return a.rating > b.rating;
}

int main() {
    vector<Product> products;
    readCSV("ElectronicsProductsPricingData.csv", products);

    if (products.empty()) {
        cerr << "Không có dữ liệu để sắp xếp." << endl;
        return 1;
    }

    // Sắp xếp sản phẩm theo giá
    sort(products.begin(), products.end(), compareByPrice);
    cout << "Sản phẩm sắp xếp theo giá (tăng dần):\n";
    for (const auto& product : products) {
        cout << product.name << " - Giá: " << product.price << ", Xếp hạng: " << product.rating << "\n";
    }

    // Sắp xếp sản phẩm theo xếp hạng
    sort(products.begin(), products.end(), compareByRating);
    cout << "\nSản phẩm sắp xếp theo xếp hạng (giảm dần):\n";
    for (const auto& product : products) {
        cout << product.name << " - Giá: " << product.price << ", Xếp hạng: " << product.rating << "\n";
    }

    return 0;
}
