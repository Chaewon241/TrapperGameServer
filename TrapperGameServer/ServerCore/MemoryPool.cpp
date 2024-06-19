#include "pch.h"
#include "MemoryPool.h"

MemoryPool::MemoryPool(int32 allocSize): _allocSize(allocSize)
{
	::InitializeSListHead(&_header);
}

MemoryPool::~MemoryPool()
{
	// _aligned_malloc���� ��������� _aligned_free�� ������Ѵ�.
	// �޸𸮰� null�� �ƴϸ�~
	while (MemoryHeader* memory = static_cast<MemoryHeader*>(::InterlockedPopEntrySList(&_header)))
		::_aligned_free(memory);
}

void MemoryPool::Push(MemoryHeader* ptr)
{
	ptr->allocSize = 0;

	// Pool�� �޸� �ݳ�
	::InterlockedPushEntrySList(&_header, static_cast<PSLIST_ENTRY>(ptr));

	_useCount.fetch_sub(1);
	_reserveCount.fetch_add(1);
}

MemoryHeader* MemoryPool::Pop()
{
	// ������ ������ �ִ��� Ȯ���ϰ� ������ ���� ������ִ� ����̾��µ�
	MemoryHeader* memory = static_cast<MemoryHeader*>(::InterlockedPopEntrySList(&_header));

	// ������ ���� �����
	if (memory == nullptr)
	{
		// _aligned_malloc���� ���ϴ� ���ĵ� malloc�� �� �� �ִ�.
		memory = reinterpret_cast<MemoryHeader*>(::_aligned_malloc(_allocSize, SLIST_ALIGNMENT));
	}
	else
	{
		ASSERT_CRASH(memory->allocSize == 0);
		_reserveCount.fetch_sub(1);
	}

	_useCount.fetch_add(1);

	return memory;
}
