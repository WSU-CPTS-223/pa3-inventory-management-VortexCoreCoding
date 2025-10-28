/*
* Class: Cpts 223
* Professor: Subu Kandaswamy
* Assignment: PA3
* Due: 10/28/25
* Programmer: Logan Spinali
* Description: Items/Product cpp implementation (mostly constructors and parsing of input strings)
*/

#include "item.hpp"
#include <iostream>

using std::cout;
using std::endl;

AmazonItem::AmazonItem(const string &id, const string &product_name, const string &brand_name, const string &asin, const vector<string> &categories, const string &upc_ean_code, const string &list_price, const string &sell_price, const string &qty, const string &model_num, const string &about_desc, const string &product_specs, const string &technical_det, const string &weight, const string &product_dimensions, const string &image_link, const string &var, const string &sku, const string &product_url, const string &stock, const string &product_det, const string &dimensions, const string &color, const string &ingredients, const string &directions, char is_az_seller, const string &size_qty_var, const string &product_desc) {
    id_ = id;
    product_name_ = product_name;
    brand_name_ = brand_name;
    asin_ = asin;
    categories_ = categories;
    upc_ean_code_ = upc_ean_code;
    list_price_ = list_price;
    sell_price_ = sell_price;
    qty_ = qty;
    model_num_ = model_num;
    about_desc_ = about_desc;
    product_specs_ = product_specs;
    technical_det_ = technical_det;
    weight_ = weight;
    product_dimensions_ = product_dimensions;
    image_link_ = image_link;
    var_ = var;
    sku_ = sku;
    product_url_ = product_url;
    stock_ = stock;
    product_det_ = product_det;
    dimensions_ = dimensions;
    color_ = color;
    ingredients_ = ingredients;
    directions_ = directions;
    is_az_seller_ = is_az_seller;
    size_qty_var_ = size_qty_var;
    product_desc_ = product_desc;
}

AmazonItem::AmazonItem(const AmazonItem &other) {
    id_ = other.id_;
    product_name_ = other.product_name_;
    brand_name_ = other.brand_name_;
    asin_ = other.asin_;
    categories_ = other.categories_;
    upc_ean_code_ = other.upc_ean_code_;
    list_price_ = other.list_price_;
    sell_price_ = other.sell_price_;
    qty_ = other.qty_;
    model_num_ = other.model_num_;
    about_desc_ = other.about_desc_;
    product_specs_ = other.product_specs_;
    technical_det_ = other.technical_det_;
    weight_ = other.weight_;
    product_dimensions_ = other.product_dimensions_;
    image_link_ = other.image_link_;
    var_ = other.var_;
    sku_ = other.sku_;
    product_url_ = other.product_url_;
    stock_ = other.stock_;
    product_det_ = other.product_det_;
    dimensions_ = other.dimensions_;
    color_ = other.color_;
    ingredients_ = other.ingredients_;
    directions_ = other.directions_;
    is_az_seller_ = other.is_az_seller_;
    size_qty_var_ = other.size_qty_var_;
    product_desc_ = other.product_desc_;
}

AmazonItem::AmazonItem(string &input) {
    // parses as is in the data.csv file:

    //Uniq Id,Product Name,Brand Name,Asin,Category,Upc Ean Code,List Price,Selling Price,Quantity,
    //Model Number,About Product,Product Specification,Technical Details,Shipping Weight,Product Dimensions,
    //Image,Variants,Sku,Product Url,Stock,Product Details,Dimensions,Color,Ingredients,Direction To Use,
    //Is Amazon Seller,Size Quantity Variant,Product Description

    string parser = input; // 3de177e1a695a48dbf706d14e587021f,"EVAN-MOOR 4545 Skill Sharpeners Math Book, Grade 1...
    string temp; // used for parsing the vector of categories and other more complex parsing processes

    // Uniq Id
    this->id_ = parser.substr(0, parser.find(","));

    // Product Name
    parser = parser.substr(parser.find(",") + 1); // "EVAN-MOOR 4545 Skill Sharpeners Math Book, Grade 1, 0.5"" Height, 8.5"" Width, 11"" Length",,,Toys & Games | Learning ...
    if (parser.at(0) == '\"') {
        parser = parser.substr(1); // EVAN-MOOR 4545 Skill ... ",
        temp = "";
        // Next tasks: parse out double "" to be " in actual name, name end marked with ",
        while (parser.find("\"\"") < parser.find("\",")) {
            // there is a "" in the name
            temp += parser.substr(0, parser.find("\"\"") + 1); // should only copy the first "
            parser = parser.substr(parser.find("\"\"") + 2); // sets the new string past the "" placement
        }
        temp += parser.substr(0, parser.find("\",")); // appends the end of the string
        parser = parser.substr(parser.find("\",") + 2);
    }
    else {
        // No other , present in name
        temp = parser.substr(0, parser.find(","));
        parser = parser.substr(parser.find(",") + 1);
    }
    this->product_name_ = temp;

    // Brand Name
    
    if (parser.find(",") == 0 || parser.find("\"\",") == 0) {
        this->brand_name_ = "NA";
    }
    else {
        this->brand_name_ = parser.substr(0, parser.find(","));
    }
    
    // Asin
    parser = parser.substr(parser.find(",") + 1);
    if (parser.find(",") == 0 || parser.find("\"\"") == 0) {
        this->asin_ = "NA";
    }
    else {
        this->asin_ = parser.substr(0, parser.find(","));
    }

    // Categories - can be "x | y | z" or x | y | z or "x" or x
    parser = parser.substr(parser.find(",") + 1);
    if (parser.find(",") == 0 || parser.find("\"\",") == 0) {
        this->categories_.push_back("NA");
    }
    else if (parser.find("\"") == 0) {
        parser = parser.substr(1);
        while (parser.find("|") < parser.find("\","))  {
            this->categories_.push_back(parser.substr(0, parser.find(" |")));
            parser = parser.substr(parser.find("| ") + 2);
        }
        this->categories_.push_back(parser.substr(0, parser.find("\",")));
        parser = parser.substr(parser.find("\",") + 2);
    }
    else {
        while (parser.find("|") < parser.find(","))  {
            this->categories_.push_back(parser.substr(0, parser.find(" |")));
            parser = parser.substr(parser.find("| ") + 2);
        }
        this->categories_.push_back(parser.substr(0, parser.find(",")));
        parser = parser.substr(parser.find(",") + 1);
    }

    // Upc ean code
    if (parser.find(",") == 0 || parser.find("\"\",") == 0) {
        this->upc_ean_code_ = "NA";
    }
    else {
        this->upc_ean_code_ = parser.substr(0, parser.find(","));
    }

    // List price
    parser = parser.substr(parser.find(",") + 1);
    if (parser.find(",") == 0 || parser.find("\"\",") == 0) {
        this->list_price_ = "NA";
    }
    else {
        this->list_price_ = parser.substr(0, parser.find(","));
    }

    // Selling price
    parser = parser.substr(parser.find(",") + 1);
    if (parser.find(",") == 0 || parser.find("\"\",") == 0) {
        this->sell_price_ = "NA";
    }
    else {
        this->sell_price_ = parser.substr(0, parser.find(","));
    }

    // Quantity
    parser = parser.substr(parser.find(",") + 1);
    if (parser.find(",") == 0 || parser.find("\"\",") == 0) {
        this->qty_ = "NA";
    }
    else {
        this->qty_ = parser.substr(0, parser.find(","));
    }

    // Model number
    parser = parser.substr(parser.find(",") + 1);
    if (parser.find(",") == 0 || parser.find("\"\",") == 0) {
        this->model_num_ = "NA";
    }
    else {
        this->model_num_ = parser.substr(0, parser.find(","));
    }

    // About product (similar to product name)
    parser = parser.substr(parser.find(",") + 1);
    if (parser.find(",") == 0 || parser.find("\"\",") == 0) {
        temp = "NA";
        parser = parser.substr(parser.find(",") + 1);
    }
    else if (parser.at(0) == '\"') {
        parser = parser.substr(1);
        temp = "";
        while (parser.find("\"\"") < parser.find("\",")) {
            temp += parser.substr(0, parser.find("\"\"") + 1);
            parser = parser.substr(parser.find("\"\"") + 2);
        }
        temp += parser.substr(0, parser.find("\","));
        parser = parser.substr(parser.find("\",") + 2);
    }
    else {
        temp = parser.substr(0, parser.find(","));
        parser = parser.substr(parser.find(",") + 1);
    }
    this->about_desc_ = temp;

    // Product specs
    if (parser.find(",") == 0 || parser.find("\"\",") == 0) {
        this->product_specs_ = "NA";
    }
    else {
        this->product_specs_ = parser.substr(0, parser.find(","));
    }

    // technical details
    parser = parser.substr(parser.find(",") + 1);
    if (parser.find(",") == 0 || parser.find("\"\",") == 0) {
        temp = "NA";
        parser = parser.substr(parser.find(",") + 1);
    }
    else if (parser.at(0) == '\"') {
        parser = parser.substr(1); // EVAN-MOOR 4545 Skill ... ",
        temp = "";
        while (parser.find("\"\"") < parser.find("\",")) {
            temp += parser.substr(0, parser.find("\"\""));
            parser = parser.substr(parser.find("\"\"") + 2);
        }
        temp += parser.substr(0, parser.find("\","));
        parser = parser.substr(parser.find("\",") + 2);
    }
    else {
        temp = parser.substr(0, parser.find(","));
        parser = parser.substr(parser.find(",") + 1);
    }
    this->technical_det_ = temp;

    // shipping weight
    if (parser.find(",") == 0 || parser.find("\"\",") == 0) {
        this->weight_ = "NA";
    }
    else {
        this->weight_ = parser.substr(0, parser.find(","));
    }

    // product dimensions
    parser = parser.substr(parser.find(",") + 1);
    if (parser.find(",") == 0 || parser.find("\"\",") == 0) {
        this->product_dimensions_ = "NA";
    }
    else {
        this->product_dimensions_ = parser.substr(0, parser.find(","));
    }

    // images
    parser = parser.substr(parser.find(",") + 1);
    if (parser.find(",") == 0 || parser.find("\"\",") == 0) {
        this->image_link_ = "NA";
    }
    else {
        this->image_link_ = parser.substr(0, parser.find(","));
    }

    // variant images
    parser = parser.substr(parser.find(",") + 1);
    if (parser.find(",") == 0 || parser.find("\"\",") == 0) {
        this->var_ = "NA";
    }
    else {
        this->var_ = parser.substr(0, parser.find(","));
    }

    // Sku
    parser = parser.substr(parser.find(",") + 1);
    if (parser.find(",") == 0 || parser.find("\"\",") == 0) {
        this->sku_ = "NA";
    }
    else {
        this->sku_ = parser.substr(0, parser.find(","));
    }

    // product URL
    parser = parser.substr(parser.find(",") + 1);
    if (parser.find(",") == 0 || parser.find("\"\",") == 0) {
        this->product_url_ = "NA";
    }
    else {
        this->product_url_ = parser.substr(0, parser.find(","));
    }

    // Stock
    parser = parser.substr(parser.find(",") + 1);
    if (parser.find(",") == 0 || parser.find("\"\",") == 0) {
        this->stock_ = "NA";
    }
    else {
        this->stock_ = parser.substr(0, parser.find(","));
    }

    // product detes
    parser = parser.substr(parser.find(",") + 1);
    if (parser.find(",") == 0 || parser.find("\"\",") == 0) {
        this->product_det_ = "NA";
    }
    else {
        this->product_det_ = parser.substr(0, parser.find(","));
    }

    // dimensions
    parser = parser.substr(parser.find(",") + 1);
    if (parser.find(",") == 0 || parser.find("\"\",") == 0) {
        this->dimensions_ = "NA";
    }
    else {
        this->dimensions_ = parser.substr(0, parser.find(","));
    }

    // color
    parser = parser.substr(parser.find(",") + 1);
    if (parser.find(",") == 0 || parser.find("\"\",") == 0) {
        this->color_ = "NA";
    }
    else {
        this->color_ = parser.substr(0, parser.find(","));
    }

    // Ingredients
    parser = parser.substr(parser.find(",") + 1);
    if (parser.find(",") == 0 || parser.find("\"\",") == 0) {
        this->ingredients_ = "NA";
    }
    else {
        this->ingredients_ = parser.substr(0, parser.find(","));
    }

    // Directions
    parser = parser.substr(parser.find(",") + 1);
    if (parser.find(",") == 0 || parser.find("\"\",") == 0) {
        this->directions_ = "NA";
    }
    else {
        this->directions_ = parser.substr(0, parser.find(","));
    }

    // isamazonseller
    parser = parser.substr(parser.find(",") + 1);
    if (parser.find(",") == 0 || parser.find("\"\",") == 0) {
        this->is_az_seller_ = 'N';
    }
    else {
        if (parser.substr(0, parser.find(",")) == "Y") {
            this->is_az_seller_ = 'Y';
        }
        else {
            this->is_az_seller_ = 'N';
        }
    }

    // Size Quantity Variant
    parser = parser.substr(parser.find(",") + 1);
    if (parser.find(",") == 0 || parser.find("\"\",") == 0) {
        this->size_qty_var_ = "NA";
    }
    else {
        this->size_qty_var_ = parser.substr(0, parser.find(","));
    }

    // product description
    parser = parser.substr(parser.find(",") + 1);
    if (parser.size() == 0) {
        this->product_desc_ = "NA";
    }
    else {
        this->product_desc_ = parser;
    }
}

void AmazonItem::print() const
{
    cout << "ITEM DETAILS:\n------------------------------\n";
    cout << "ID: " << id_ << endl;
    cout << "Product Name: " << product_name_ << endl;
    cout << "Brand Name: " << brand_name_ << endl;
    cout << "ASIN: " << asin_ << endl;
    cout << "Categories: ";
    for (int i = 0; i < categories_.size(); i++) {
        cout << categories_[i];
        if (i != categories_.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;
    cout << "UPC/EAN Code: " << upc_ean_code_ << endl;
    cout << "List Price: " << list_price_ << endl;
    cout << "Sell Price: " << sell_price_ << endl;
    cout << "Quantity: " << qty_ << endl;
    cout << "Model Number: " << model_num_ << endl;
    cout << "About Description: " << about_desc_ << endl;
    cout << "Product Specs: " << product_specs_ << endl;
    cout << "Technical Details: " << technical_det_ << endl;
    cout << "Weight: " << weight_ << endl;
    cout << "Product Dimensions: " << product_dimensions_ << endl;
    cout << "Image Link: " << image_link_ << endl;
    cout << "Var: " << var_ << endl;
    cout << "SKU: " << sku_ << endl;
    cout << "Product URL: " << product_url_ << endl;
    cout << "Stock: " << stock_ << endl;
    cout << "Product Details: " << product_det_ << endl;
    cout << "Dimensions: " << dimensions_ << endl;
    cout << "Color: " << color_ << endl;
    cout << "Ingredients: " << ingredients_ << endl;
    cout << "Directions: " << directions_ << endl;
    cout << "Is Amazon Seller: " << is_az_seller_ << endl;
    cout << "Size/Qty Variant: " << size_qty_var_ << endl;
    cout << "Product Description: " << product_desc_ << endl;
}
