
//	This file is part of The Drwalin Engine project
// Copyright (C) 2018-2020 Marek Zalewski aka Drwalin aka DrwalinPCF

#include <Script.h>
#include <Engine.h>
#include <JSON.hpp>
#include <Singleton.h>

void New(const JSON& args) {
	if(args[1].String() == "entity") {
		if(args.size() == 3) {
			sing::engine->AddEntity(args[2]);
			return;
		}
		JSON json;
		json["class"] = args[2];
		json["shape"] = args[23];
		json["transform"] = args[4];
		if(args.size() >= 5)
			json["mass"] = args[5];
		if(args.size() >= 6)
			json["model"] = args[6];
		sing::engine->AddEntity(args);
	} else {
		MESSAGE(std::string("Invalid new argument (1): ") + args[1].Write());
	}
}

