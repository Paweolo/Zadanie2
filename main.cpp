#include <iostream>
#include <vector>

class Time {
private:
    int seconds_;
    int minutes_;
    int hours_;
public:
    Time() {};
    Time(int h, int m, int s) {
        hours_ = ((m / 60) + h) % 24;
        minutes_ = ((s / 60) + m) % 60;
        seconds_ = s % 60;
    }
    Time(int s) {
        int minutes = (s / 60);
        hours_ = minutes / 60;
        seconds_ = s % 60;
        minutes_ = minutes % 60;
    }
    int convertToSeconds() {
        return (hours_ * 3600) + (minutes_ * 60) + seconds_;
    }

    Time operator-(const Time& t) const {
        return Time(hours_ - t.hours_, minutes_ - t.minutes_, seconds_ - t.seconds_);
    }
    Time operator+(const Time& t) const {
        return Time(hours_ + t.hours_, minutes_ + t.minutes_, seconds_ + t.seconds_);
    }
    Time operator*(const int scalar) const {
        return Time(scalar * hours_, scalar * minutes_, scalar * seconds_);
    }
    operator int() {
        return convertToSeconds();
    }
    friend std::ostream& operator<<(std::ostream& str, Time& t);
    friend std::istream& operator >>(std::istream& in, Time& t);
};
std::ostream& operator<<(std::ostream& str, Time& t) {
    if (t.hours_ != 0) {
        str << t.hours_ << "h:" << t.minutes_ << "m:" << t.seconds_ << "s";
    }
    else {
        str << t.minutes_ << "m:" << t.seconds_ << "s";
    }
    return str;
}
std::istream& operator >>(std::istream& in, Time& t) {
    std::cout << "Enter hours: ";
    in >> t.hours_;
    std::cout << "Enter minutes: ";
    in >> t.minutes_;
    std::cout << "Enter seconds: ";
    in >> t.seconds_;
    return in;
}

class Item {
private:
    std::string name;
    float price;
    char vat; 
    int amount;
public:
    Item(std::string n, float p, char v, int a) {
        name = n;
        price = p;
        vat = v;
        amount = a;
    }
    float getNetto() {
        return amount * price;
    }
    float getBrutto() {
        float localVat;
        if (vat == 'A') {
            localVat = 0.23;
        }
        else if (vat == 'B') {
            localVat = 0.08;
        }
        else {
            localVat = 0;
        }
        return getNetto() * localVat + getNetto();
    }
    friend std::ostream& operator<<(std::ostream& str, Item& item);
};

std::ostream& operator<<(std::ostream& str, Item& item){
    str << item.name << "     | " << item.price << " " << item.vat << " | " << item.amount << " | " << item.getNetto() << " | " << item.getBrutto();
    return str;
}

class Invoice {
private:
    std::string sellerNIP;
    std::string buyerNIP;
    std::vector<Item> items;
public:
    Invoice(std::string sNIP, std::string bNIP) {
        sellerNIP = sNIP;
        buyerNIP = bNIP;
    }
    void addItem(const Item& item) {
        items.push_back(item);
    }
    friend std::ostream& operator<<(std::ostream& str, Invoice& inv);
	Invoice operator+(const Invoice& inv) {
        Invoice result(sellerNIP, buyerNIP);
        if (sellerNIP == inv.sellerNIP) {
            for (Item item : items) {
                result.addItem(item);
            }
			for (Item item : inv.items) {
				result.addItem(item);
			}
            return result;
        }
        
	}
};
std::ostream& operator<<(std::ostream& str, Invoice& inv) {
    float totalNetto = 0;
    float totalBrutto = 0;
    str << "------------------VAT invoice------------------" << "\n";
    str << "===============================================" << "\n";
    str << "Seller: " << inv.sellerNIP << "      " << "Buyer: " << inv.buyerNIP << "\n\n";
    str << "                  c.j. VAT   il.    net   total" << "\n";
    for (Item item : inv.items) {
        std::cout << item << "\n";
        totalNetto += item.getNetto();
        totalBrutto += item.getBrutto();
    }
    str << "------------------------------------ TOTAL ----" << "\n";
    str << "                                  " << totalNetto << " | " << totalBrutto;
    return str;

}
int main()
{
    int choice = 0;
    std::cout << "Chose task (1 - Time, 2 - Superinvoice): ";
    std::cin >> choice;
    if (choice == 1) {
        Time t1(29, 51, 231);
        std::cout << t1 << "\n";
        Time t2;
        std::cin >> t2;
        std::cout << t2 << "\n";

        Time add_result = t1 - t2;
        Time sub_result = t1 - t2;
        Time mult_result = t1 * 3;
        std::cout << t1 << "+" << t2 << "=" << add_result << "\n";
        std::cout << t1 << "-" << t2 << "=" << sub_result << "\n";
        std::cout << t1 << "* 3 = " << mult_result << "\n";
        
        std::cout << "Conversion " << t2 << " to seconds : " << static_cast<int>(t2);
    }
    else if(choice == 2){
        Invoice inv("7770003699", "0123456789");
        inv.addItem(Item("M3 screw", 0.37, 'A', 100));
        inv.addItem(Item("2 mm drill", 2.54, 'B', 2));
		Invoice inv2("7770003699", "0123456789");
        inv.addItem(Item("Example", 3.14, 'A', 21));
		Invoice inv3 = inv + inv2;
        std::cout << inv3 << std::endl;
    }
    else {
        std::cout << "Wrong choice!!!";
    }
}
