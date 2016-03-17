/*
 * ASManager.cpp
 *
 *  Created on: Jan 17, 2016
 *      Author: Daniel G Billings Jr
 */

#include "ASManager.hpp"

namespace crunch
{
// Print the script string to the standard output stream
void print(std::string &msg)
{
	std::cout << msg;
}

ASManager::ASManager()
{
	engine = asCreateScriptEngine();	//create script engine
	int r = engine->SetMessageCallback(asMETHOD(ASManager, messageCallback),
			this, asCALL_THISCALL);	//register callback function
	ctx = engine->CreateContext();
	if (r < 0)
	{
		std::cerr << "problem setting up engine\n";
	}
	RegisterStdString(engine);		//Register std::string as string type
	RegisterScriptArray(engine, true);	//Register AngelScript Arrays
	//TODO: Create new string type to allow pass by reference and speed up strings.
	r = engine->RegisterGlobalFunction("void print(const string &in)",
			asFUNCTION(print), asCALL_CDECL);
	mod = nullptr;
	func = nullptr;

	executable = false;
}

ASManager::~ASManager()
{
	// Release order is important.
	ctx->Release();
	engine->ShutDownAndRelease();
//	mod->Discard();
}
// Implement a simple message callback function
void ASManager::messageCallback(const asSMessageInfo *msg, void *param)
{
	const char *type = "ERR ";
	if (msg->type == asMSGTYPE_WARNING)
		type = "WARN";
	else if (msg->type == asMSGTYPE_INFORMATION)
		type = "INFO";
	printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type,
			msg->message);

	//TODO: Change to C++ style cerr stream operator, and make it prettier
}
int ASManager::buildScripts()
{
	int r = builder.StartNewModule(engine, "testModule");

	if (r < 0)
	{
		std::cerr << "Unrecoverable error while starting a new module.\n";
		return (r);
		executable = false;
	}
	r = builder.AddSectionFromFile("test.as");
	if (r < 0)
	{
		std::cerr << "Errors found in script, can't run\n";
		return (r);
		executable = false;
	}
	r = builder.BuildModule();
	if (r < 0)
	{
		std::cerr << " Errors found in script, can't run\n";
		executable = false;
		return (r);
	}
	mod = engine->GetModule("testModule");
	executable = true;
	return (r);
}
void ASManager::changeFunc(std::string functionName)
{
	if (func != nullptr)
	{
		func->Release();
		func = nullptr;
	}
	if (executable)
	{
		func = mod->GetFunctionByDecl(functionName.c_str());
		if (func == 0)
		{
			std::cerr << "No function named " << functionName
					<< " could be found in " << mod->GetName() << ".\n";
			return;
		}
	}
}
void ASManager::runScript()
{
	int r = 0;
	if (func == nullptr)
	{
		r = asERROR;
		std::cerr << "Problem executing script: No entry function prepared\n";
	}
	else
	{
		r = ctx->Prepare(func);
		if (r == asSUCCESS)
		{
			r = ctx->Execute();
			if (r != asEXECUTION_FINISHED)
			{
				if (r == asEXECUTION_EXCEPTION)
				{
					std::cerr << "An exception " << ctx->GetExceptionString()
							<< " occurred.\n";
					//TODO: Improve exception handler
				}
			}
		}
		else
		{
			std::cerr << "Could not prepare " << func->GetNamespace()
					<< func->GetName() << " for execution\n";
		}
	}
}

} /* namespace crunch */
