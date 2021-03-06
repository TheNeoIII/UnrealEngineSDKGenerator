#include "NameValidator.hpp"

#include <cctype>

#include "ObjectsStore.hpp"

std::string MakeValidName(std::string&& name)
{
	std::string valid(name);

	for (auto i = 0u; i < name.length(); ++i)
	{
		if (valid[i] == ' '
			|| valid[i] == '?'
			|| valid[i] == '-'
			|| valid[i] == ':'
			|| valid[i] == '/'
			|| valid[i] == '('
			|| valid[i] == ')'
			|| valid[i] == '['
			|| valid[i] == ']'
			|| valid[i] == '&')
		{
			valid[i] = '_';
		}
	}

	if (!valid.empty())
	{
		if (std::isdigit(valid[0]))
		{
			valid = '_' + valid;
		}
	}

	return valid;
}

template<typename T>
std::string MakeUniqueCppNameImpl(const T& t)
{
	std::string name;
	if (ObjectsStore().CountObjects<T>(t.GetName()) > 1)
	{
		name += MakeValidName(t.GetOuter().GetName()) + "_";
	}
	return name + MakeValidName(t.GetName());
}

std::string MakeUniqueCppName(const UEConst& c)
{
	return MakeUniqueCppNameImpl(c);
}

std::string MakeUniqueCppName(const UEEnum& e)
{
	return MakeUniqueCppNameImpl(e);
}

std::string MakeUniqueCppName(const UEStruct& ss)
{
	std::string name;
	if (ObjectsStore().CountObjects<UEStruct>(ss.GetName()) > 1)
	{
		name += MakeValidName(ss.GetOuter().GetNameCPP()) + "_";
	}
	return name + MakeValidName(ss.GetNameCPP());
}
