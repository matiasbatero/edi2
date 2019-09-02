#ifndef _FILE
#define _FILE


#include <iostream>
#include "IListable.hpp"

class File : public IListable
{
    private:
    
    std::string _filename;
    
    public:

	File( std::string name ) : _filename(name)
	{
	
	}
	
    virtual void list()
    {
		std::cout << _filename << std::endl;
    }
    
    virtual ~File() = default;
};

#endif
