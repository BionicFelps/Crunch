/*
 * ASManager.hpp
 *
 *  Created on: Jan 17, 2016
 *      Author: daniel
 */

#ifndef ASMANAGER_HPP_
#define ASMANAGER_HPP_
#include <angelscript.h>
#include "../AngelScriptAddons/scriptstdstring/scriptstdstring.h"
#include "../AngelScriptAddons/scriptbuilder/scriptbuilder.h"
#include "../AngelScriptAddons/scriptarray/scriptarray.h"
#include <iostream>
#include <string>

namespace crunch
{

class ASManager
{
public:
	ASManager();
	virtual ~ASManager();
	void messageCallback(const asSMessageInfo *msg, void *param);
	int buildScripts();
	void runScript();
	void changeFunc(std::string);
private:
	asIScriptEngine *engine;
	CScriptBuilder builder;
	asIScriptModule *mod;
	asIScriptContext *ctx;
	asIScriptFunction *func;
	bool executable;
};

} /* namespace crunch */

#endif /* ASMANAGER_HPP_ */
