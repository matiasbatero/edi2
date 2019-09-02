#ifndef I_LISTABLE
#define I_LISTABLE

class IListable
{
	public:
	
	virtual void list() = 0;
	virtual ~IListable() = default;
};

#endif
