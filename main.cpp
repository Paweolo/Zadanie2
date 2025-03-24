#include <iostream>
#include <vector>

using namespace std;

class Time {
private:
    int seconds;
    int minutes;
    int hours;
public:
    Time() {};
    Time(int h, int m, int s) {
        hours = ((m / 60) + h) % 24;
        minutes = ((s / 60) + m) % 60;
        seconds = s % 60;
    }
    Time(int s) {
        int minutes = (s / 60);
        hours = minutes / 60;
        seconds = s % 60;
        minutes = minutes % 60;
    }
    int convertToSeconds() {
        return (hours * 3600) + (minutes * 60) + seconds;
    }

    Time operator-(const Time& t) const {
        return Time(hours - t.hours, minutes - t.minutes, seconds - t.seconds);
    }
    Time operator+(const Time& t) const {
        return Time(hours + t.hours minutes + t.minutes, seconds + t.seconds);
    }
    Time operator*(const int number) const {
        return Time(number * hours, number * minutes, number * seconds);
    }
    operator int() {
        return convertToSeconds();
    }
    friend ostream& operator<<(ostream& str, Time& t);
    friend istream& operator >>(istream& in, Time& t);
};
ostream& operator<<(ostream& str, Time& t) {
    if (t.hours != 0) {
        str << t.hours << "h:" << t.minutes << "m:" << t.seconds << "s";
    }
    else {
        str << t.minutes << "m:" << t.seconds << "s";
    }
    return str;
}
istream& operator >>(istream& in, Time& t) {
    cout << "Enter hours: ";
    in >> t.hours;
    cout << "Enter minutes: ";
    in >> t.minutes;
    cout << "Enter seconds: ";
    in >> t.seconds;
    return in;
}

class Item {
private:
    string name;
    float price;
    char vat; 
    int amount;
public:
    Item(string n, float p, char v, int a) {
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
    friend ostream& operator<<(ostream& str, Item& item);
};

ostream& operator<<(ostream& str, Item& item){
    str << item.name << "     | " << item.price << " " << item.vat << " | " << item.amount << " | " << item.getNetto() << " | " << item.getBrutto();
    return str;
}

class Invoice {
private:
    string sellerNIP;
    string buyerNIP;
    vector<Item> items;
public:
    Invoice(string sNIP, string bNIP) {
        sellerNIP = sNIP;
        buyerNIP = bNIP;
    }
    void addItem(const Item& item) {
        items.push_back(item);
    }
    friend ostream& operator<<(ostream& str, Invoice& inv);
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
ostream& operator<<(ostream& str, Invoice& inv) {
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
    cout << "Chose task (1 - Time, 2 - Superinvoice): ";
    cin >> choice;
    if (choice == 1) {
        Time t1(29, 51, 231);
        cout << t1 << "\n";
        Time t2;
        cin >> t2;
        cout << t2 << "\n";

        Time add_result = t1 - t2;
        Time sub_result = t1 - t2;
        Time mult_result = t1 * 3;
        cout << t1 << "+" << t2 << "=" << add_result << "\n";
        cout << t1 << "-" << t2 << "=" << sub_result << "\n";
        cout << t1 << "* 3 = " << mult_result << "\n";
        
        cout << "Conversion " << t2 << " to seconds : " << static_cast<int>(t2);
    }
    else if(choice == 2){
        Invoice inv("7770003699", "0123456789");
        inv.addItem(Item("M3 screw", 0.37, 'A', 100));
        inv.addItem(Item("2 mm drill", 2.54, 'B', 2));
		Invoice inv2("7770003699", "0123456789");
        inv.addItem(Item("Example", 3.14, 'A', 21));
		Invoice inv3 = inv + inv2;
        cout << inv3 << std::endl;
    }
    else {
        cout << "Wrong choice!!!";
    }
}
