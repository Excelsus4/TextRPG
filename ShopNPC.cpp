#include "stdafx.h"
#include "ShopNPC.h"

ShopNPC::ShopNPC(vector<Sales> salesList):
	itemStand(salesList)
{
}

ShopNPC::~ShopNPC()
{
	for (auto p : itemStand) {
		delete p.item;
	}
}

void ShopNPC::GetShoppingList() const
{
	for (size_t i = 0; i < itemStand.size(); i++) {
		cout << i << ". " << itemStand[i].item->GetName() << " " << itemStand[i].price << "��� ��� " << itemStand[i].stack << "��" << endl;
	}
}

Item* ShopNPC::BuyItem(size_t index, int& money)
{
	Item* handover = nullptr;
	// ���� �Ŵ뺸�� ���� �ε���
	if (index < itemStand.size()) {
		// ���� ���ݺ��� ������ 
		if (money >= itemStand[index].price) {
			money -= itemStand[index].price;
			handover = itemStand[index].item;

			// ������ ���� ���̱�
			if (itemStand[index].stack > 1)
				itemStand[index].stack--;
			else
				itemStand.erase(itemStand.begin() + index);
		}
		else {
			cout << "��尡 �����մϴ�." << endl;
		}
	}
	else {
		cout << "�߸��� ������ �ε����Դϴ�" << endl;
	}
	return handover;
}
