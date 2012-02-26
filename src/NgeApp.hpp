/**
 * @file  NgeApp.hpp
 * @author Kun Wang <ifreedom.cn@gmail.com>
 * @date 2012/02/12 05:15:35
 *
 *  Copyright  2012  Kun Wang <ifreedom.cn@gmail.com>
 *
 */

#ifndef _NGEAPP_HPP
#define _NGEAPP_HPP

#include <v8.h>
#include <node.h>
#include "nge_app.hpp"

using namespace node;
using namespace v8;

class NgeApp : public ObjectWrap {
public:
    NgeApp() : ObjectWrap() {}
    static void Init(Handle<Object> target);

protected:
    static Handle<Value> New(const Arguments& args);

    static Handle<Value> StartRun(const Arguments& args);
	static Handle<Value> GetCurrent(const Arguments& args);

    static Handle<Value> Step(const Arguments& args);
};

#endif /* _NGEAPP_HPP */
