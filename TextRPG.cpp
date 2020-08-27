#pragma once
#include "stdafx.h"
#include "TextRPG.h"
#include "GameEngine.h"
#include "RandomEngine.h"
#include "Scrap.h"

TextRPG::TextRPG()
{
	// �÷��̾� �ʱ�ȭ
	statistics temp;
	temp.Name = "�÷��̾�";
	temp.Hp = 100;
	temp.Attack = 1;
	temp.Level = 1;
	temp.Strength = 10;
	temp.Agility = 4;
	player = new Player(temp);

	// �ʱ���� ����
	gold = 100;

	// ���� ���� �ʱ�ȭ
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
			cout << "System: ������ ���Ϳ� �����մϴ�." << endl;
			if (!RandomEncounter())
				return;
			break;
		case 2:
			cout << "System: ����� ������ �ε����� �Է��Ͻʽÿ�." << endl;
			cout << "�Է�> ";
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
			cout << "System: ������ �����մϴ�." << endl;
			return;
		default:
			cout << "System: �߸��� �Է°�: "<<selection<<endl;
		}
	}
}

void TextRPG::GainItem(Item* item)
{
	if (item->isStackable()) {
		cout << item->GetName() << "��(��) " << item->GetAmount() << "�� ȹ���ߴ�!" << endl;
		// ���� ���̶� �ߺ��� �������� ���ý�Ű��
		unordered_map<string, Item*>::iterator exist = stackItemHash.find(item->GetName());
		if (exist == stackItemHash.end()) {
			// ���ο� ������
			inventory.push_back(item);
			stackItemHash[item->GetName()] = *(inventory.end() - 1);
		}
		else {
			//������ �ִ� ������
			exist->second->StackItem(item->GetAmount());
			delete item;
		}
	}
	else {
		cout << item->GetName() << "��(��) ȹ���ߴ�!" << endl;
		inventory.push_back(item);
	}
}

void TextRPG::GainGold(int gold)
{
	cout << gold << "��带 ȹ���ߴ�!" << endl;
	this->gold += gold;
}

void TextRPG::PrintTitle()
{
	cout << "�ؽ�ƮRPG" << endl;
}

int TextRPG::MainMenu()
{
	int sel;
	cout << endl;
	cout << "1. ���� ��ī����" << endl;
	cout << "2. ���� ��ī����" << endl;
	cout << "4. ĳ���� ����â" << endl;
	cout << "6. �κ��丮" << endl;
	cout << "7. ����" << endl;
	cout << "-1. ��������" << endl;
	sel = GetInput();
	return sel;
}

bool TextRPG::Encounter(int index)
{
	// �������� �ʱ�ȭ
	GameEngine engine;

	// �÷��̾� ����
	engine.AddEntity(player);

	// ���� ����
	Mob* instance = new Mob(*library.GetMobByIndex(index));
	engine.AddEntity(instance);

	// ���� �� ���
	bool result = engine.Run();

	if (result) {
		// �¸��� ��� ���� ȹ��
		vector<GainChance> itemV = engine.Award(player);
		for (GainChance c : itemV) {
			TryToGetItem(c);
		}
	}
	// ������ ���� ���� ��ƼƼ �Ҵ�����
	delete instance;

	//���� ��� ��ȯ
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
		cout << endl << "�κ��丮" << endl;
		isize = PrintInventory();
		cout << "������: " << gold << "���" << endl;
		cout << "-1. ���ư���" << endl;
		input = GetInput();
		if (input < 0)
			return;
		else if (input < isize)
			UseItem(inventory[input]);
		else
			cout << "�߸��� ������ �ε���" << endl;
	}
}

void TextRPG::ShopInteract()
{
	int input;
	while (true) {
		cout << endl << "����" << endl;
		cout << "1. ����" << endl;
		cout << "2. �Ǹ�" << endl;
		cout << "-1. ���ư���" << endl;
		input = GetInput();
		if (input < 0)
			return;
		else if (input == 1) {
			// ���� ��Ʈ
			while (true) {
				cout << endl << "�����ϱ�" << endl;
				villageShop->GetShoppingList();
				cout << "������: " << gold << "���" << endl;
				cout << "-1. ���ư���" << endl;
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
			//�Ǹ� ��Ʈ
			while (true) {
				cout << endl << "�Ǹ��ϱ�" << endl;
				int isize = PrintInventory();
				cout << "������: " << gold << "���" << endl;
				cout << "-1. ���ư���" << endl;
				input = GetInput();
				if (input < 0)
					break;
				else if (input < isize) {
					// �ش� ������ �ȱ�
					int value = inventory[input]->Sell();
					cout << inventory[input]->GetName() << "��(��) " << value << "��忡 �Ľðڽ��ϱ�?" << endl;
					cout << "(Y/N)> ";
					string lastCheck;
					cin >> lastCheck;
					if (lastCheck == "Y") {
						if(RemoveItemSafely(inventory.begin()+input))
							GainGold(value);
						else
							cout << "�����Ǿ��ִ� �������� �Ǹ��� �� �����ϴ�." << endl;
					}
					else {
						cout << "�ŷ��� ����߽��ϴ�." << endl;
						continue;
					}
				}
				else {
					cout << "�߸��� ������ �ε���" << endl;
					continue;
				}
			}
		}
		else {
			cout << "�� �� ���� ����Դϴ�." << endl;
			continue;
		}
	}
}

void TextRPG::UseItem(Item* item)
{
	//������ ĳ���� ���
	if (Equipment* equipment = dynamic_cast<Equipment*>(item)) {
		player->Equip(equipment);
	}
	else if (Scrap* scrap = dynamic_cast<Scrap*>(item)) {
		cout << scrap->GetName() << " " << scrap->GetAmount() << "��" << endl;
		cout << scrap->GetDescription() << endl;
		cout << "������ ���� " << scrap->GetValue() << "��忡 ���� �� ����" << endl;
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
			cout << " " << inventory[i]->GetAmount() << "��";
		}
		cout << endl;
	}

	return isize;
}

int TextRPG::GetInput()
{
	int input;
	cout << "�Է�> ";
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
	cout << "Exception: ���ǵ��� ���� ������ Ÿ���Դϴ� @ TextRPG::RemoveItemSafely" << endl;
	return false;
}
