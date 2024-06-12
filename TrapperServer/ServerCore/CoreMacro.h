#pragma once

/*-----------
	Crash
------------*/

// ���������� ũ��������
// complie �ܰ迡�� ��ƹ����� �ʰ� �ϱ� ���� ��ũ�� ���
// ��� ũ���� ������ ���� ���������� ���� Ȯ���غ���.
//

// CRASH(�Է�)
#define CRASH(cause)						\
{											\
	uint32* crash = nullptr;				\
	__analysis_assume(crash != nullptr);	\
	*crash = 0xDEADBEEF;					\
}

// __analysis_assume(crash != nullptr); -> crash�� nullptr�� �ƴ϶�� ���� ���ֱ�
// crash�� nullptr�̸� �̸� �����Ϸ��� ����� �� �ֱ� ����.
// 

#define ASSERT_CRASH(expr)			\
{									\
	if (!(expr))					\
	{								\
		CRASH("ASSERT_CRASH");		\
		__analysis_assume(expr);	\
	}								\
}
