#include <iostream>
#include <vector>

#include "class.h"

static const int START_ID = 10000;
static std::string CURRENT_WINDOW = "Main";


static bool Flip_ID = true;
static int ID_Counters = 0;
int getAvaiableID ()
{
	Flip_ID = !Flip_ID;
	ID_Counters++;
	return (Flip_ID ? START_ID - (ID_Counters / 2) : START_ID + (ID_Counters / 2));
}

int main(int argc, char* argv[])
{
	Hashtable map(10);

	
	
	while (true)
	{
		int User_Option;
		if (CURRENT_WINDOW == "Main")
		{
			system("CLS");
			std::cout << "Welcome to Online shop" << "\n\n";
			std::cout << "1- Join as admin" << std::endl;
			std::cout << "2- Join as user" << std::endl;
			std::cout << "3- Exit" << std::endl;

			std::cin >> User_Option;
			CURRENT_WINDOW = (User_Option == 1 ? "Admin" : "User");
			system("CLS");
		} else {
			User_Option = (CURRENT_WINDOW == "Admin" ? 1 : 2);
		}
			
		if (User_Option == 1) // Join as Admin
		{
			std::cout << "1- To add product" << std::endl;
			std::cout << "2- To delete product" << std::endl;
			std::cout << "3- To modify product" << std::endl;
			std::cout << "4- To display products" << std::endl;
			std::cout << "5- Return to main menu" << std::endl;

			std::cin >> User_Option;
			system("CLS");
			if (User_Option == 1) // to add product
			{	
				std::string product_Name; int product_quantity, product_price;
				std::cout << "Enter product name: "; std::cin >> product_Name;
				std::cout << "Enter product quantity: "; std::cin >> product_quantity;
				std::cout << "Enter product price: "; std::cin >> product_price;

				map.insert(getAvaiableID(), product_Name, product_quantity, product_price);
			} else if (User_Option == 2) { // to Delete product

				int product_ID;
				std::cout << "Enter product ID: "; std::cin >> product_ID;

				if (map.isKeyExist(product_ID))
					map.deleteObjectFromKey(product_ID);

			} else if (User_Option == 3) { // to modify product

				int product_ID;
				std::cout << "Enter product ID: "; std::cin >> product_ID;

				std::string product_Name; int product_quantity, product_price;
				std::cout << "Enter new product name: "; std::cin >> product_Name;
				std::cout << "Enter new product quantity: "; std::cin >> product_quantity;
				std::cout << "Enter new product price: "; std::cin >> product_price;

				if (map.isKeyExist(product_ID))
				{
					map.editObjectFromKey(product_ID, product_Name, product_quantity, product_price);
				}
					

			} else if (User_Option == 4) { // to display product
				map.printAll();
			} else if (User_Option == 5) { // return to main menu
				CURRENT_WINDOW = "Main";
			}

		} else if (User_Option == 2) { // Join as user

			std::cout << "1- To buy product" << std::endl;
			std::cout << "2- To display products" << std::endl;
			std::cout << "3- Return to main menu" << std::endl;

			std::cin >> User_Option;
			system("CLS");
			if (User_Option == 1) // to buy product
			{
				int product_ID;
				std::cout << "Enter product ID: "; std::cin >> product_ID;
				int product_quantity;
				std::cout << "Enter product quantity: "; std::cin >> product_quantity;

				if (map.isKeyExist(product_ID))
				{
					if (map[product_ID].m_Quantity >= product_quantity)
					{
						std::cout << "You have bought " << map[product_ID].m_Name << " for $" << (product_quantity * map[product_ID].m_Price) << std::endl;
						map.setQuantityFromKey(product_ID, map[product_ID].m_Quantity - product_quantity);
					}
				}
				
				
			} else if (User_Option == 2) { // to diplay product
				map.printAll();
			} else if (User_Option == 3) { // return to main menu
				CURRENT_WINDOW = "Main";
			}

		} else if (User_Option == 3) { // Exit
			break;
		}

	}
	return 0;
}