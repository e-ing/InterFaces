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
protected:
	virtual bool GetState() = 0;
public:
	virtual Abstract_iPort& operator >> (void* any)
	{
		*((bool*)any) = GetState();
		return *this;
	}
	virtual operator bool() { return GetState(); }
	virtual operator int() { return (GetState() == false) ? 0 : 1; };
	virtual void PullH() = 0;
	virtual void PullD() = 0;
	virtual void SetSpeed(unsigned int speed) = 0;
	~Abstract_iBit() {}
};

//ADCs  and etc
class Abstract_iInt : public  Abstract_iPort
{
protected:
	virtual int GetValue() = 0;
public:
	virtual Abstract_iPort& operator >> (void* any)
	{
		*((int*)any) = GetValue();
		return *this;
	}
	virtual operator int() { return GetValue(); }
	~Abstract_iInt() {}
};

//serial ports in and etc
class Abstract_iString : public  Abstract_iPort
{
protected:
	virtual char* GetStr() = 0;
public:
	virtual Abstract_iPort& operator >> (void* any)
	{
		char* any = GetStr();
		return *this;
	}
	virtual operator char* () { return GetStr(); }
	virtual int GetDataLen() = 0;
	~Abstract_iString() {}
};

//Memorys in  and etc

class Abstract_iArray : public  Abstract_iPort
{
	unsigned int index;
	unsigned int rdSz;
	virtual unsigned int GetData(unsigned int idx, int* data, int sz) = 0;
	virtual unsigned int GetData(unsigned int idx) = 0;
public:
	virtual void SetIdx(unsigned int idx) { index = idx; }
	virtual unsigned int operator[] (unsigned int idx)
	{
		return GetData(index++);
	}
	virtual unsigned int GetIdx() { return index; }
	void SetSz(unsigned int sz) { rdSz = sz; }
	virtual Abstract_iPort& operator >> (void* any) 
	{
		for (int i = rdSz; i > 0; --i)
			(int*)any = GetData(index++);
	}

	virtual operator int()
	{
		return GetData(index++);
	}
	~Abstract_iArray() {}
};