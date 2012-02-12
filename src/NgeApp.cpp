/**
 * @file  NgeApp.cpp
 * @author Kun Wang <ifreedom.cn@gmail.com>
 * @date 2012/02/12 05:14:47
 *
 *  Copyright  2012  Kun Wang <ifreedom.cn@gmail.com>
 *
 */

#include "NgeApp.hpp"

#include "nge_app.hpp"

class NgeAppImpl : public CNgeApp {
public:
	virtual	int Init();
	virtual	int Mainloop();
	virtual	int Fini();
};

static Persistent<String> init_sym;
static Persistent<String> mainloop_sym;
static Persistent<String> fini_sym;

static Persistent<Function> step_fn;
static Persistent<Object> app_obj;
static NgeAppImpl impl;

Persistent<Function> log_fn;
Persistent<Object> console_obj;

#define GET_AND_CALL(sym)							\
	Local<Value> v = app_obj->Get(sym);				\
	if (!v->IsFunction())							\
		return 0;									\
													\
	Local<Function> fn = Local<Function>::Cast(v);	\
	Local<Value> ret = fn->Call(app_obj, 0, NULL);	\
	if (!ret->IsInt32())							\
		return -1;									\
	int32_t r = ret->Int32Value();					\
	return r

int NgeAppImpl::Init() {
	GET_AND_CALL(init_sym);
}

int NgeAppImpl::Mainloop() {
	GET_AND_CALL(mainloop_sym);
}

int NgeAppImpl::Fini() {
	GET_AND_CALL(fini_sym);
}

void NgeApp::Init(Handle<Object> target) {
    HandleScope scope;

	Local<Object> console = Context::GetCurrent()->Global()->Get(String::NewSymbol("console"))->ToObject();
	console_obj = Persistent<Object>::New(console);
	Local<Function> fn = Local<Function>::Cast(console->Get(String::NewSymbol("log")));
	log_fn = Persistent<Function>::New(fn);

	NODE_DEFINE_CONSTANT(target, NGE_APP_QUIT);
	NODE_DEFINE_CONSTANT(target, NGE_APP_NORMAL);

	init_sym = NODE_PSYMBOL("init");
	mainloop_sym = NODE_PSYMBOL("mainloop");
	fini_sym = NODE_PSYMBOL("fini");

	step_fn = Persistent<Function>::New(FunctionTemplate::New(Step)->GetFunction());

    Local<String> name = String::NewSymbol("NgeApp");

	Local<FunctionTemplate> t = FunctionTemplate::New(NgeApp::New);
    t->InstanceTemplate()->SetInternalFieldCount(1);
    t->SetClassName(name);

    NODE_SET_PROTOTYPE_METHOD(t, "startRun", StartRun);
	NODE_SET_METHOD(t, "getCurrent", GetCurrent);

    target->Set(name, t->GetFunction());
}

Handle<Value> NgeApp::New(const Arguments& args) {
    HandleScope scope;

    if (!args.IsConstructCall()) {
        return ThrowException(Exception::TypeError(
								  String::New("Use the new operator to create instances of this object."))
			);
    }

    NgeApp* o = new NgeApp();
    o->Wrap(args.This());
	o->Ref();

    return scope.Close(args.This());
}

#define REG_NEXT()														\
	Local<Object> process = Context::GetCurrent()->Global()->Get(String::NewSymbol("process"))->ToObject(); \
	Local<Function> fn = Local<Function>::Cast(process->Get(String::NewSymbol("nextTick"))); \
	Local<Value> argv[1] = { Local<Value>::New(step_fn) };				\
	fn->Call(process, 1, argv)

Handle<Value> NgeApp::Step(const Arguments& args) {
	int ret = impl.Mainloop();

	if (ret == NGE_APP_QUIT) {
		impl.Fini();
	}
	else {
		REG_NEXT();
	}

	return Undefined();
}

Handle<Value> NgeApp::StartRun(const Arguments& args) {
    HandleScope scope;

	if (!app_obj.IsEmpty()) {
        return ThrowException(Exception::TypeError(
								  String::New("Already has a NgeApp to be run.")));
	}

	app_obj = Persistent<Object>::New(args.This());
	nge_registerApp(&impl);

	impl.Init();

	REG_NEXT();

	return Undefined();
}

Handle<Value> NgeApp::GetCurrent(const Arguments& args) {
    HandleScope scope;

	return scope.Close(Local<Object>::New(app_obj));
}
