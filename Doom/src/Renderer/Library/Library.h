#pragma once

#include <list>
#include <optional>
#include <mutex>

#include "Utility/Log.h"

class LibraryElement
{
private:
	const std::string name;
public:
	LibraryElement(const std::string& name) : name(name) {}

	virtual ~LibraryElement() = default;

	virtual const std::string& GetName() const { return name; };
};

template<class Data>
class Library
{
private:
	std::list<Data> dataList;
	mutable std::mutex libraryMutex;
protected:
	Library()
	{
		static_assert(std::is_base_of<LibraryElement, Data>::value, "Library: Data not derived from LibraryElement");
	}

	virtual ~Library() = default;

public:
	virtual inline std::optional<const Data*> Get(const std::string& name) const { return FindElement(name); }

protected:

	template<typename... Values>
	const Data* InsertData(Values&&... values)
	{
		std::lock_guard<std::mutex> guard(libraryMutex);
		dataList.emplace_back(values...);
		return &dataList.back();
	}

	std::optional<const Data*> FindElement(const std::string& name) const
	{
		std::lock_guard<std::mutex> guard(libraryMutex);
		auto iterator = std::find_if(dataList.begin(), dataList.end(), [&](const Data& data) { return data.GetName() == name; });
		if (iterator != dataList.end()) return &(*iterator);
		return {};
	}
private:
	Library(Library const&) = delete;
	void operator=(Library const&) = delete;
};

