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
		cout << i << ". " << itemStand[i].item->GetName() << " " << itemStand[i].price << "골드 재고 " << itemStand[i].stack << "개" << endl;
	}
}

Item* ShopNPC::BuyItem(size_t index, int& money)
{
	Item* handover = nullptr;
	// 상점 매대보다 작은 인덱스
	if (index < itemStand.size()) {
		// 돈이 가격보다 많으면 
		if (money >= itemStand[index].price) {
			money -= itemStand[index].price;
			handover = itemStand[index].item;

			// 스택을 먼저 줄이기
			if (itemStand[index].stack > 1)
				itemStand[index].stack--;
			else
				itemStand.erase(itemStand.begin() + index);
		}
		else {
			cout << "골드가 부족합니다." << endl;
		}
	}
	else {
		cout << "잘못된 아이템 인덱스입니다" << endl;
	}
	return handover;
}
