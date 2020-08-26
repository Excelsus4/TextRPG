#include "stdafx.h"
#include "ShopNPC.h"

ShopNPC::ShopNPC(vector<pair<Item*, int>> salesList):
	itemStand(salesList)
{
}

ShopNPC::~ShopNPC()
{
	for (auto p : itemStand) {
		delete p.first;
	}
}

void ShopNPC::GetShoppingList() const
{
	for (size_t i = 0; i < itemStand.size(); i++) {
		cout << i << ". " << itemStand[i].first->GetName() << " " << itemStand[i].second << "���" << endl;
	}
}

Item* ShopNPC::BuyItem(size_t index, int& money)
{
	Item* handover = nullptr;
	// ���� �Ŵ뺸�� ���� �ε���
	if (index < itemStand.size()) {
		// ���� ���ݺ��� ������ 
		if (money >= itemStand[index].second) {
			money -= itemStand[index].second;
			handover = itemStand[index].first;
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
