#pragma once
#include "stdafx.h"
#include "TextRPG.h"
#include "GameEngine.h"
#include "RandomEngine.h"
#include "Scrap.h"

TextRPG::TextRPG()
{
	// 플레이어 초기화
	statistics temp;
	temp.Name = "플레이어";
	temp.Hp = 100;
	temp.Attack = 1;
	temp.Level = 1;
	temp.Strength = 10;
	temp.Agility = 4;
	player = new Player(temp);

	// 초기장비 지급
	gold = 100;

	// 마을 상인 초기화
	villageShop = new ShopNPC({
		make_pair(new Equipment(*library.GetEquipByIndex(0)), 100),
		make_pair(new Equipment(*library.GetEquipByIndex(1)), 35),
		make_pair(new Equipment(*library.GetEquipByIndex(3)), 800),
		make_pair(new Equipment(*library.GetEquipByIndex(2)), 3500),
		make_pair(new HealthPotion(*library.GetHpPotionByIndex(0)), 25)});
}

TextRPG::~TextRPG()
{
	for (Item* item : inventory) {
		delete item;
	}
	delete player;
}

void TextRPG::Run()
{
	PrintTitle();
	int selection;
	while(true) {
		selection = MainMenu();
		switch (selection) {
		case 1:
			cout << "System: 랜덤한 몬스터와 전투합니다." << endl;
			if (!RandomEncounter())
				return;
			break;
		case 2:
			cout << "System: 상대할 몬스터의 인덱스를 입력하십시오." << endl;
			cout << "입력> ";
			cin >> selection;
			if (!Encounter(selection))
				return;
			break;
		case 4:
			player->DisplayStat();
			break;
		case 6:
			InventoryInteract();
			break;
		case 7:
			ShopInteract();
			break;
		case -1:
			cout << "System: 게임을 종료합니다." << endl;
			return;
		default:
			cout << "System: 잘못된 입력값: "<<selection<<endl;
		}
	}
}

void TextRPG::GainItem(Item* item)
{
	if (item->isStackable()) {
		cout << item->GetName() << "을(를) " << item->GetAmount() << "개 획득했다!" << endl;
		// 기존 것이랑 중복된 아이템은 스택시키기
		unordered_map<string, Item*>::iterator exist = stackItemHash.find(item->GetName());
		if (exist == stackItemHash.end()) {
			// 새로운 아이템
			inventory.push_back(item);
			stackItemHash[item->GetName()] = *(inventory.end() - 1);
		}
		else {
			//기존에 있는 아이템
			exist->second->StackItem(item->GetAmount());
			delete item;
		}
	}
	else {
		cout << item->GetName() << "을(를) 획득했다!" << endl;
		inventory.push_back(item);
	}
}

void TextRPG::GainGold(int gold)
{
	cout << gold << "골드를 획득했다!" << endl;
	this->gold += gold;
}

void TextRPG::PrintTitle()
{
	cout << "텍스트RPG" << endl;
}

int TextRPG::MainMenu()
{
	int sel;
	cout << endl;
	cout << "1. 랜덤 인카운터" << endl;
	cout << "2. 지명 인카운터" << endl;
	cout << "4. 캐릭터 상태창" << endl;
	cout << "6. 인벤토리" << endl;
	cout << "7. 상인" << endl;
	cout << "-1. 게임종료" << endl;
	sel = GetInput();
	return sel;
}

bool TextRPG::Encounter(int index)
{
	// 전투엔진 초기화
	GameEngine engine;

	// 플레이어 삽입
	engine.AddEntity(player);

	// 몬스터 삽입
	Mob* instance = new Mob(*library.GetMobByIndex(index));
	engine.AddEntity(instance);

	// 전투 및 결과
	bool result = engine.Run();

	if (result) {
		// 승리한 경우 보상 획득
		vector<GainChance> itemV = engine.Award(player);
		for (GainChance c : itemV) {
			TryToGetItem(c);
		}
	}
	// 전투에 사용된 몬스터 엔티티 할당해제
	delete instance;

	//전투 결과 반환
	return result;
}

bool TextRPG::RandomEncounter()
{
	// Draw random seed and call Encounter()
	// Transfer the return value
	uniform_int_distribution<int> dist(0, library.GetMobBookSize()-1);
	return Encounter(dist(*Random::gen));
}

void TextRPG::InventoryInteract()
{
	int input, isize;
	while (true) {
		cout << endl << "인벤토리" << endl;
		isize = PrintInventory();
		cout << "소지금: " << gold << "골드" << endl;
		cout << "-1. 돌아가기" << endl;
		input = GetInput();
		if (input < 0)
			return;
		else if (input < isize)
			UseItem(inventory[input]);
		else
			cout << "잘못된 아이템 인덱스" << endl;
	}
}

void TextRPG::ShopInteract()
{
	int input;
	while (true) {
		cout << endl << "상점" << endl;
		cout << "1. 구매" << endl;
		cout << "2. 판매" << endl;
		cout << "-1. 돌아가기" << endl;
		input = GetInput();
		if (input < 0)
			return;
		else if (input == 1) {
			// 구매 파트
			while (true) {
				cout << endl << "구매하기" << endl;
				villageShop->GetShoppingList();
				cout << "소지금: " << gold << "골드" << endl;
				cout << "-1. 돌아가기" << endl;
				input = GetInput();
				if (input < 0)
					break;
				else {
					Item* get = villageShop->BuyItem(input, gold);
					if (get != nullptr) {
						if (Equipment* equipment = dynamic_cast<Equipment*>(get)) {
							GainItem(new Equipment(*equipment));
						}
						else if (Scrap* scrap = dynamic_cast<Scrap*>(get)) {
							GainItem(new Scrap(*scrap));
						}
						else if (HealthPotion* cons = dynamic_cast<HealthPotion*>(get)) {
							GainItem(new HealthPotion(*cons));
						}
					}
				}
			}
		}
		else if (input == 2) {
			//판매 파트
			while (true) {
				cout << endl << "판매하기" << endl;
				int isize = PrintInventory();
				cout << "소지금: " << gold << "골드" << endl;
				cout << "-1. 돌아가기" << endl;
				input = GetInput();
				if (input < 0)
					break;
				else if (input < isize) {
					// 해당 아이템 팔기
					int value = inventory[input]->Sell();
					cout << inventory[input]->GetName() << "을(를) " << value << "골드에 파시겠습니까?" << endl;
					cout << "(Y/N)> ";
					string lastCheck;
					cin >> lastCheck;
					if (lastCheck == "Y") {
						if(RemoveItemSafely(inventory.begin()+input))
							GainGold(value);
						else
							cout << "장착되어있는 아이템은 판매할 수 없습니다." << endl;
					}
					else {
						cout << "거래를 취소했습니다." << endl;
						continue;
					}
				}
				else {
					cout << "잘못된 아이템 인덱스" << endl;
					continue;
				}
			}
		}
		else {
			cout << "알 수 없는 명령입니다." << endl;
			continue;
		}
	}
}

void TextRPG::UseItem(Item* item)
{
	//아이템 캐스팅 사용
	if (Equipment* equipment = dynamic_cast<Equipment*>(item)) {
		player->Equip(equipment);
	}
	else if (Scrap* scrap = dynamic_cast<Scrap*>(item)) {
		cout << scrap->GetName() << " " << scrap->GetAmount() << "개" << endl;
		cout << scrap->GetDescription() << endl;
		cout << "상인이 개당 " << scrap->GetValue() << "골드에 사줄 것 같다" << endl;
	}
	else if (Consumable* cons = dynamic_cast<Consumable*>(item)) {
		cons->Apply(player);
	}
}

void TextRPG::TryToGetItem(GainChance c)
{
	uniform_real_distribution<float> cDice(0, 1.f);
	if (cDice(*Random::gen) < c.chance) {
		if (Equipment* equipment = dynamic_cast<Equipment*>(c.item)) {
			GainItem(new Equipment(*equipment));
		}
		else if (Scrap* scrap = dynamic_cast<Scrap*>(c.item)) {
			uniform_int_distribution<int> aDice(c.minAmount, c.maxAmount);
			GainItem(new Scrap(*scrap, aDice(*Random::gen)));
		}
		else if (HealthPotion* potion = dynamic_cast<HealthPotion*>(c.item)) {
			uniform_int_distribution<int> aDice(c.minAmount, c.maxAmount);
			GainItem(new HealthPotion(*potion, aDice(*Random::gen)));
		}
	}
}

int TextRPG::PrintInventory()
{
	int isize = inventory.size();
	for (int i = 0; i < isize; i++) {
		cout << i << ". " << inventory[i]->GetName();
		if (inventory[i]->isStackable()) {
			cout << " " << inventory[i]->GetAmount() << "개";
		}
		cout << endl;
	}

	return isize;
}

int TextRPG::GetInput()
{
	int input;
	cout << "입력> ";
	cin >> input;
	
	return input;
}

bool TextRPG::RemoveItemSafely(vector<Item*>::iterator item)
{
	if (Equipment* equipment = dynamic_cast<Equipment*>(*item)) {
		// Check equipment list and find match.
		if(player->isEquiped(equipment)){
			return false;
		}
		else {
			inventory.erase(item);
			delete equipment;
			return true;
		}
	}
	else if (Scrap* scrap = dynamic_cast<Scrap*>(*item)) {
		stackItemHash.erase(scrap->GetName());
		inventory.erase(item);
		delete scrap;
		return true;
	}
	else if (Consumable* cons = dynamic_cast<Consumable*>(*item)) {
		stackItemHash.erase(cons->GetName());
		inventory.erase(item);
		delete cons;
		return true;
	}
	cout << "Exception: 정의되지 않은 아이템 타입입니다 @ TextRPG::RemoveItemSafely" << endl;
	return false;
}
