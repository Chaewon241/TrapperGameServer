#pragma once

class IocpObject : public enable_shared_from_this<IocpObject>
{
public:
	virtual void Dispatch(class IocpEvent* iocpEvent, int32 numOfBytes = 0) abstract;
};