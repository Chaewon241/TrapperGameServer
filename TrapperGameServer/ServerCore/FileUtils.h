#pragma once
#include <vector>
#include "Types.h"

/// <summary>
/// ��θ� �о ������ �д� Ŭ����
/// </summary>

class FileUtils
{
public:
	static Vector<BYTE>		ReadFile(const WCHAR* path);
	static String			Convert(string str);
};