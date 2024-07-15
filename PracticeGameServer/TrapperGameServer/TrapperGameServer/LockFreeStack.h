#pragma once

// -------------------
//		1�� �õ�
// -------------------
/*
struct SListEntry
{
	SListEntry* next;
};

struct SListHeader
{
	SListEntry* next = nullptr;
};

void InitializeHead(SListHeader* header);
void PushEntrySList(SListHeader* header, SListEntry* entry);
SListEntry* PopEntrySList(SListHeader* header);
*/

// -------------------
//		2�� �õ�
// -------------------

//struct SListEntry
//{
//	SListEntry* next;
//};
//
//struct SListHeader
//{
//	SListEntry* next = nullptr;
//};
//
//void InitializeHead(SListHeader* header);
// Push�� Pop�� ���߾����忡�� �� �۵��ǰ� �ٲٱ�
//void PushEntrySList(SListHeader* header, SListEntry* entry);
//SListEntry* PopEntrySList(SListHeader* header);

// -------------------
//		3�� �õ�
// -------------------
// ������ �޸𸮰� 16����Ʈ�� ���ĵǰ� �ش޶�
DECLSPEC_ALIGN(16)
struct SListEntry
{
	SListEntry* next;
};

DECLSPEC_ALIGN(16)
struct SListHeader
{
	SListHeader()
	{
		alignment = 0;
		region = 0;
	}

	// �ȿ� �ִ� ����ü�� ���� �����ͷ� ���
	// ũ�� �����ϳ�(���� ����ü) ���������� �����ϳ�(�Ʒ� ����ü)
	union
	{
		struct
		{
			uint64 alignment;
			uint64 region;
		} DUMMYSTRUCTNAME;
		struct
		{
			// ��׵� �� ���ϸ� ������ �Ȱ��� 128
			uint64 depth : 16;
			uint64 sequence : 48;
			uint64 reserved : 4;
			uint64 next : 60;
		} HeaderX64;
	};
};

void InitializeHead(SListHeader* header);
void PushEntrySList(SListHeader* header, SListEntry* entry);
SListEntry* PopEntrySList(SListHeader* header);