#ifndef AMAZON_ITEM
#define AMAZON_ITEM

#include <string>
#include <vector>
#include <ostream>

using std::string;
using std::vector;

class AmazonItem {
private:
    string id_;
    string product_name_;
    string brand_name_;
    string asin_;
    vector<string> categories_;
    string upc_ean_code_;
    string list_price_;
    string sell_price_;
    string qty_;
    string model_num_;
    string about_desc_;
    string product_specs_;
    string technical_det_;
    string weight_;
    string product_dimensions_;
    string image_link_;
    string var_;
    string sku_;
    string product_url_;
    string stock_;
    string product_det_;
    string dimensions_;
    string color_;
    string ingredients_;
    string directions_;
    char is_az_seller_;
    string size_qty_var_;
    string product_desc_;

public:
    // Constructor, Copy-Constructor, Parsing-Constructor
    AmazonItem(const string& id = "",
        const string& product_name = "",
        const string& brand_name = "",
        const string& asin = "",
        const vector<string>& categories = vector<string>(),
        const string& upc_ean_code = "",
        const string& list_price = "",
        const string& sell_price = "",
        const string& qty = "",
        const string& model_num = "",
        const string& about_desc = "",
        const string& product_specs = "",
        const string& technical_det = "",
        const string& weight = "",
        const string& product_dimensions = "",
        const string& image_link = "",
        const string& var = "",
        const string& sku = "",
        const string& product_url = "",
        const string& stock = "",
        const string& product_det = "",
        const string& dimensions = "",
        const string& color = "",
        const string& ingredients = "",
        const string& directions = "",
        char is_az_seller = 'N',
        const string& size_qty_var = "",
        const string& product_desc = "");
    AmazonItem(const AmazonItem& other);
    AmazonItem(string& input);

    void print() const;

    // Getters
    const string& getId() const { return id_; }
    const string& getProductName() const { return product_name_; }
    const string& getBrandName() const { return brand_name_; }
    const string& getAsin() const { return asin_; }
    const vector<string>& getCategories() const { return categories_; }
    const string& getUpcEanCode() const { return upc_ean_code_; }
    const string& getListPrice() const { return list_price_; }
    const string& getSellPrice() const { return sell_price_; }
    const string& getQty() const { return qty_; }
    const string& getModelNum() const { return model_num_; }
    const string& getAboutDesc() const { return about_desc_; }
    const string& getProductSpecs() const { return product_specs_; }
    const string& getTechnicalDet() const { return technical_det_; }
    const string& getWeight() const { return weight_; }
    const string& getProductDimensions() const { return product_dimensions_; }
    const string& getImageLink() const { return image_link_; }
    const string& getVar() const { return var_; }
    const string& getSku() const { return sku_; }
    const string& getProductUrl() const { return product_url_; }
    const string& getStock() const { return stock_; }
    const string& getProductDet() const { return product_det_; }
    const string& getDimensions() const { return dimensions_; }
    const string& getColor() const { return color_; }
    const string& getIngredients() const { return ingredients_; }
    const string& getDirections() const { return directions_; }
    char getIsAzSeller() const { return is_az_seller_; }
    const string& getSizeQtyVar() const { return size_qty_var_; }
    const string& getProductDesc() const { return product_desc_; }

    // Setters
    void setId(const string& id) { id_ = id; }
    void setProductName(const string& name) { product_name_ = name; }
    void setBrandName(const string& brand) { brand_name_ = brand; }
    void setAsin(const string& asin) { asin_ = asin; }
    void setCategories(const vector<string>& categories) { categories_ = categories; }
    void setUpcEanCode(const string& code) { upc_ean_code_ = code; }
    void setListPrice(const string& price) { list_price_ = price; }
    void setSellPrice(const string& price) { sell_price_ = price; }
    void setQty(const string& qty) { qty_ = qty; }
    void setModelNum(const string& num) { model_num_ = num; }
    void setAboutDesc(const string& desc) { about_desc_ = desc; }
    void setProductSpecs(const string& specs) { product_specs_ = specs; }
    void setTechnicalDet(const string& det) { technical_det_ = det; }
    void setWeight(const string& weight) { weight_ = weight; }
    void setProductDimensions(const string& dim) { product_dimensions_ = dim; }
    void setImageLink(const string& link) { image_link_ = link; }
    void setVar(const string& var) { var_ = var; }
    void setSku(const string& sku) { sku_ = sku; }
    void setProductUrl(const string& url) { product_url_ = url; }
    void setStock(const string& stock) { stock_ = stock; }
    void setProductDet(const string& det) { product_det_ = det; }
    void setDimensions(const string& dim) { dimensions_ = dim; }
    void setColor(const string& color) { color_ = color; }
    void setIngredients(const string& ingredients) { ingredients_ = ingredients; }
    void setDirections(const string& directions) { directions_ = directions; }
    void setIsAzSeller(char isSeller) { is_az_seller_ = isSeller; }
    void setSizeQtyVar(const string& var) { size_qty_var_ = var; }
    void setProductDesc(const string& desc) { product_desc_ = desc; }

    friend std::ostream& operator<<(std::ostream& os, const AmazonItem& item) {
        os << "{ID: " << item.id_ << ", Name: " << item.product_name_ << "}";
        return os;
    }

    bool operator==(const AmazonItem& other) const {
        return id_ == other.id_;
    }
};

#endif