#if !defined(SEARCHSTRUCT_H)
#define SEARCHSTRUCT_H

#pragma warning (disable:4786)

#include <vector>

template <typename T>
class SearchTerm
{
public:
	SearchTerm() : _not(false) {}
	bool				_not;
	T					_term;
	std::vector<int>	_recordNumberVector;
};

class SStruct
{
public:
	virtual ~SStruct(){};
	virtual void AddSearchTerm(){};
	int			_fieldNumber;
	std::vector<int> _searchTermNumber;
};

template <typename T>
class SearchStruct : public SStruct
{
public:
	std::vector<SearchTerm<T> *> _searchTermVector;

	void AddSearchTerm()
	{
		SearchTerm<T>  * temp = new SearchTerm<T>;
		_searchTermVector.push_back(temp);
	}
	~SearchStruct()
	{
		for(std::vector<SearchTerm<T> *>::const_iterator iter = _searchTermVector.begin();
			iter != _searchTermVector.end(); iter++)
			{
				delete *iter;
			}
	}
private:

};

#endif