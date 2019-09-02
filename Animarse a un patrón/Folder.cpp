#ifndef FOLDER
#define FOLDER


#include <iostream>
#include <list>
#include "IListable.hpp"
#include "IComposableOfListable.hpp"

class Folder : public IListable, public IComposableOfListable
{
	private:
	
	std::string _foldername;
	std::list<IListable*> _innerContents;
	
	public:
	
	Folder( std::string name ) : _foldername(name)
	{
	
	}
	
    virtual void list()
    {
		for( auto element : _innerContents )
		{
			element->list();
		};
    }

    virtual void add(IListable* component)
    {
		if ( component != this && component != nullptr )
		{
			_innerContents.push_back( component );
		}
    }

    virtual void remove(IListable* component)
    {
		if ( component != this && component != nullptr )
		{
			std::list<IListable*>::iterator it;
		
			for( auto element : _innerContents )
			{
				if ( element != component )
				{
					it++;
				}
			};
			
			_innerContents.erase(it);
		}
		else if ( component == this )
		{
			_innerContents.clear();
		}
		
    }

    virtual IListable* getChild(int key)
    {
		int childCounter = 0;
		IListable* _element = nullptr;
		
		for( auto element : _innerContents )
		{
			if (childCounter == key )
			{
				_element = element;
				break;
			}
		}
		
		return _element;
    }
    
    virtual ~Folder() = default;
};

#endif
