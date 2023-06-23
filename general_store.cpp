#include<iostream>
#include<fstream>
using namespace std;

class store
{
    string item_id,item_name;
    int item_quantity,item_price,total_amount=0;
    fstream file,newfile;
    string id_req;
    char choice;
public:
    void add_product(void);
    void view_product(void);
    void buy_product(void);
}obj;

void store::add_product()
{
    //taking input of the product details
        cout<<"Enter Product ID: ";
        cin>>item_id;
        cout<<"Enter Product Name: ";
        cin>>item_name;
        cout<<"Enter Product Quantity: ";
        cin>>item_quantity;
        cout<<"Enter Product Price: ";
        cin>>item_price;

    //storing the product details in the text file
        file.open("products.txt",ios :: out | ios :: app );
        file<<item_id<<"\t"<<item_name<<"\t"<<item_quantity<<"\t"<<item_price<<endl;
        file.close();
}
void store::view_product()
{
    cout<<"\n------Available products------"<<endl;
    file.open("products.txt",ios :: in);
    file>>item_id>>item_name>>item_quantity>>item_price;                //fetch details of 1st product
    while(!file.eof())                                    //displaying the product details till end of the file
    {
        cout<<"\nProduct Id: "<<item_id;
        cout<<"\nProduct Name: "<<item_name;
        cout<<"\nProduct Quantity: "<<item_quantity;
        cout<<"\nProduct Price: "<<item_price<<endl;
        cout<<"--------------------------"<<endl;
        file>>item_id>>item_name>>item_quantity>>item_price;
    }
    file.close();
}
void store::buy_product()
{
    //choice variable is used to run the while loop for buying
    char choice = 'y';
    while(choice == 'y')
    {
        int item_rate=0, quantity_req=0;
        cout<<"Enter ID of the product you want to buy: ";
        cin>>id_req;
        cout<<"Enter Quantity: ";
        cin>>quantity_req;

        file.open("products.txt",ios :: in);
        newfile.open("temp.txt",ios :: out | ios :: app);
        file>>item_id>>item_name>>item_quantity>>item_price;    //fetch details of the 1st item

        while(!file.eof())
        {
            if(item_id ==  id_req)            //if the fetched data is of the required product
            {
                if (quantity_req<=item_quantity)
                {
                    item_quantity = item_quantity - quantity_req;                                     //reduce the quantity available of the product
                    newfile<<item_id<<"\t"<<item_name<<"\t"<<item_quantity<<"\t"<<item_price<<endl;      //store the modified data in a new text file
                }
                else
                {
                    while(quantity_req>item_quantity)       
                    {
                        cout<<"\nRequired quantity exceeds the available product quantity.\nAvailable quantity: "<<item_quantity;
                        cout<<"\nEnter Quantity: ";
                        cin>>quantity_req;
                    }
                    item_quantity = item_quantity - quantity_req;
                    newfile<<item_id<<"\t"<<item_name<<"\t"<<item_quantity<<"\t"<<item_price<<endl;
                }
                item_rate = quantity_req * item_price;            //calculating the rate of the item purchased
                total_amount = total_amount + item_rate;          //adding the rate to total amount
                cout<<"\n------Payment Bill------"<<endl;
                cout<<"Total Amount : "<<total_amount<<endl;
                cout<<"------------------------"<<endl;
                }
            else                            //if product is not matched, fetch data of the next product
            {
                newfile<<item_id<<"\t"<<item_name<<"\t"<<item_quantity<<"\t"<<item_price<<endl;
            }
            file>>item_id>>item_name>>item_quantity>>item_price;
        }
        file.close();
        newfile.close();
        remove("products.txt");               //deleting the old file and renaming the new file
        rename("temp.txt","products.txt");
    
        cout<<"\nDo you want to continue Shoping? ( y/n ) ";
        cin>>choice;
    }
}

int main(){
    char choice;
    do
    {
        cout<<"\n1 --> Start Shopping";
        cout<<"\n0 --> Exit";
        cout<<"\nEnter your choice: ";
        cin>>choice;
        switch (choice)
        {
            case 'A':
                obj.add_product();       //for admin to add a product
                break;
            case '0':                  
                exit(1);
                break; 
            case '1':
                obj.view_product();
                obj.buy_product();
                break;
            default:
                cout<<"Invalid Selection!"<<endl;
                break;
        }
    }while(choice);

    return 0;
}