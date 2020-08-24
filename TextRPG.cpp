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
	gold = 0;
	GainItem(new Equipment(*library.GetEquipByIndex(0)));
	GainItem(new Equipment(*library.GetEquipByIndex(1)));
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
		case 0:
			cout << "System: ������ �����մϴ�." << endl;
			return;
		default:
			cout << "System: �߸��� �Է°�: "<<selection<<endl;
		}
	}
}

void TextRPG::GainItem(Equipment* item)
{
	cout << item->GetName() << "��(��) ȹ���ߴ�!" << endl;
	inventory.push_back(item);
}

void TextRPG::GainItem(Scrap* item)
{
	cout << item->GetName() << "��(��) " << item->GetAmount() << "�� ȹ���ߴ�!" << endl;
	//TODO: ���� ���̶� �ߺ��� �������� ���ý�Ű��
	auto exist = stackItemHash.find(item->GetName);
	if (exist == stackItemHash.end()) {
		//���ο� ������
		inventory.push_back(item);
		stackItemHash[item->GetName()] = inventory.end() - 1;
	}
	else {
		//������ �ִ� ������
		delete item;
	}
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
	cout << "0. ��������" << endl;
	cout << "�Է�> ";
	cin >> sel;
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
	int input;
	int isize = inventory.size();
	cout << endl << "�κ��丮" << endl;
	for (int i = 0; i < isize;i++) {
		cout << i << ". " << inventory[i]->GetName() << endl;
	}
	cout << "������: "<<gold << "���" << endl;
	cout << "-1. ���ư���" << endl;
	cout << "�Է�> ";
	cin >> input;
	if (input < 0)
		return;
	else if (input < isize)
		UseItem(inventory[input]);
	else
		cout << "�߸��� ������ �ε���" << endl;
	return;
}

void TextRPG::ShopInteract()
{
	int input;
	cout << endl << "����" << endl;
	cout << "1. ����" << endl;
	cout << "2. �Ǹ�" << endl;
	cout << "-1. ���ư���" << endl;
	cout << "�Է�> " << endl;
	cin >> input;
	if (input < 0)
		return;
	else if (input == 1) {
		//TODO: ���� ��Ʈ
	}
	else if (input == 2) {
		//TODO: �Ǹ� ��Ʈ
	}
	else {
		cout << "�� �� ���� ����Դϴ�." << endl;
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
	}
}
