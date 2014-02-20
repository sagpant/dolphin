// Copyright 2013 Dolphin Emulator Project
// Licensed under GPLv2
// Refer to the license.txt file included.

#include "Common/SymbolDB.h"


void SymbolDB::List()
{
	for (XFuncMap::iterator iter = functions.begin(); iter != functions.end(); ++iter)
	{
		DEBUG_LOG(OSHLE, "%s @ %08x: %i bytes (hash %08x) : %i calls",
			iter->second.name.c_str(), iter->second.address,
			iter->second.size, iter->second.hash,
			iter->second.numCalls);
	}
	INFO_LOG(OSHLE, "%lu functions known in this program above.",
		(unsigned long)functions.size());
}

void SymbolDB::Clear(const char *prefix)
{
	// TODO: honor prefix
	functions.clear();
	checksumToFunction.clear();
}

void SymbolDB::Index()
{
	int i = 0;
	for (auto& func : functions)
	{
		func.second.index = i++;
	}
}

Symbol *SymbolDB::GetSymbolFromName(const char *name)
{
	for (auto& func : functions)
	{
		if (!strcmp(func.second.name.c_str(), name))
			return &func.second;
	}
	return 0;
}

void SymbolDB::AddCompleteSymbol(const Symbol &symbol)
{
	functions.insert(std::pair<u32, Symbol>(symbol.address, symbol));
}
