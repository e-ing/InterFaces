#ifndef ABSTRACT_IFCS_H
#define ABSTRACT_IFCS_H
//v1-08.04.21
//input
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
	virtual ~Abstract_iBit() {}
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
	virtual ~Abstract_iInt() {}
};

//serial ports in and etc
class Abstract_iString : public  Abstract_iPort
{
protected:
	virtual char* GetStr() = 0;
public:
	virtual Abstract_iPort& operator >> (void* any)
	{
		any = GetStr();
		return *this;
	}
	virtual operator char* () { return GetStr(); }
	virtual int GetDataLen() = 0;
	virtual ~Abstract_iString() {}
};

////Memorys in  and etc

class Abstract_iArray : public  Abstract_iPort
{
	unsigned int index;
	unsigned int rdSz;
	virtual unsigned int GetData(unsigned int idx, void* data, unsigned int sz) = 0;
	virtual unsigned int GetData(unsigned int idx) = 0;
public:
	virtual void SetIdx(unsigned int idx) { index = idx; }
	virtual unsigned int operator[] (unsigned int idx)
	{
		return GetData(index);
	}
	virtual unsigned int GetIdx() { return index; }
	void SetSz(unsigned int sz) { rdSz = sz; }
	virtual Abstract_iPort& operator >> (void* any) 
	{
			GetData(index, any, rdSz);
		return *this;
	}

	virtual operator int()
	{
		return GetData(index);
	}
	virtual ~Abstract_iArray() {}
};
//out
class Abstract_oPort
{
public:
	virtual Abstract_oPort& operator << (void* any) = 0;
	virtual ~Abstract_oPort() {}
};

//GPout and etc
class Abstract_oBit : public  Abstract_oPort
{
protected:
	virtual bool GetState() = 0;
	virtual void SetValue( bool x) =0;
	virtual void Toggle () = 0;
	virtual void SetState(void* state)
	{
		SetValue(*((bool*) state));
	}
public:
	virtual void Set() = 0;
	virtual void Clear() = 0;
	virtual void SetSpeed(unsigned int speed) = 0;
	
	virtual Abstract_oPort& operator << (void* any)
	{
		SetState(any);
		return *this;
	}
	virtual operator bool() { return GetState(); }
	virtual operator int() { return (GetState() == false) ? 0 : 1; };
	virtual Abstract_oBit&  operator = (bool val) 
	{
		SetValue(val);
		return *this;
	} 
	virtual Abstract_oBit& operator = (int val) 
	{
		SetValue((val==0)? false : true);
		return *this;
	}
	virtual Abstract_oBit& operator !()
	{
		Toggle();
		return *this;
	}
	virtual ~Abstract_oBit() {}
};


#endif

