#pragma once

class Abstract_iPort
{
public:
	virtual Abstract_iPort& operator >> (void* any) = 0;
	virtual ~Abstract_iPort() {}
};

//GPin and etc
class Abstract_iBit : public  Abstract_iPort
{
public:
	virtual Abstract_iPort& operator >> (void* any) = 0;
	virtual Abstract_iPort& operator >> (bool& any) = 0;
	virtual Abstract_iPort& operator >> (int& any) = 0;
	virtual operator bool() = 0;
	virtual operator int() = 0;
	virtual void PullH() = 0;
	virtual void PullD() = 0;
	virtual void SetSpeed(unsigned int speed) = 0;
	~Abstract_iBit() {}
};

//ADCs  and etc
class Abstract_iInt : public  Abstract_iPort
{
public:
	virtual Abstract_iPort& operator >> (void* any) = 0;
	virtual Abstract_iPort& operator >> (int& any) = 0;
	virtual operator int() = 0;
	~Abstract_iInt() {}
};

//Uarts in and etc
class Abstract_iString : public  Abstract_iPort
{
public:
	virtual Abstract_iPort& operator >> (void* any) = 0;
	virtual Abstract_iPort& operator >> (char* any) = 0;
	virtual operator char*() = 0;
	~Abstract_iString() {}
};

//Memorys in  and etc
struct AddrData
{
	unsigned int addr;
	unsigned int data;
};

class Abstract_iArray : public  Abstract_iPort
{
	unsigned int index;
	virtual unsigned int GetData(unsigned int idx) = 0;
public:
	virtual void SetIdx(unsigned int idx) { index = idx; }
	virtual unsigned int operator[] (unsigned int idx)
	{
		return GetData (index++) ;
	}
	virtual unsigned int GetIdx() { return index; }
	virtual Abstract_iPort& operator >> (AddrData& any)
	{
		any.addr = index;
		any.data = GetData(index++);
	}
	virtual Abstract_iPort& operator >> (void* any) 
	{
		return operator >> ( *((AddrData*) any));
		//((AddrData*)any)->addr = index;
		//((AddrData*)any)->data = GetData(index++);
	}
	virtual Abstract_iPort& operator >> (unsigned int& any)
	{
		any = GetData(index++);
	}
	virtual operator int()
	{
		return GetData(index++);
	}
	~Abstract_iArray() {}
};