/**
 * @file  NgeApp.cpp
 * @author Kun Wang <ifreedom.cn@gmail.com>
 * @date 2012/02/12 05:14:47
 *
 *  Copyright  2012  Kun Wang <ifreedom.cn@gmail.com>
 *
 */

#include "NgeApp.hpp"

class NgeAppImpl : public CNgeApp {
public:
	virtual	int Init();
	virtual	int Mainloop();
	virtual	int Fini();
};

static Persistent<String> init_sym;
static Persistent<String> mainloop_sym;
static Persistent<String> fini_sym;

static Persistent<Function> init_end_fn;
static Persistent<Function> mainloop_end_fn;
static Persistent<Function> fini_end_fn;

static Persistent<Function> step_fn;
static Persistent<Object> app_obj;
static NgeAppImpl impl;

#define GET_FUNC_BY_SYM_AND_CHECK(obj, val, sym)	\
	Local<Value> val = obj->Get(sym);				\
	if (!val->IsFunction())							\
		return 0

#define GET_AND_CALL(sym, end_fn)							\
	GET_FUNC_BY_SYM_AND_CHECK(app_obj, v, sym);				\
	Local<Function> fn = Local<Function>::Cast(v);			\
	Local<Value> argv[1] = { Local<Value>::New(end_fn) };	\
	fn->Call(app_obj, 1, argv);								\
	return 0

int NgeAppImpl::Init() {
	HandleScope scope;

	GET_AND_CALL(init_sym, init_end_fn);
}

int NgeAppImpl::Mainloop() {
	HandleScope scope;

	GET_AND_CALL(mainloop_sym, mainloop_end_fn);
}

int NgeAppImpl::Fini() {
	HandleScope scope;

	GET_AND_CALL(fini_sym, fini_end_fn);
}

namespace wrapper {
	void NgeApp::Init(Handle<Object> target) {
		HandleScope scope;

		NODE_DEFINE_CONSTANT(target, NGE_APP_QUIT);
		NODE_DEFINE_CONSTANT(target, NGE_APP_NORMAL);

		init_sym = NODE_PSYMBOL("init");
		mainloop_sym = NODE_PSYMBOL("mainloop");
		fini_sym = NODE_PSYMBOL("fini");

		step_fn = Persistent<Function>::New(FunctionTemplate::New(Step)->GetFunction());

		init_end_fn = Persistent<Function>::New(FunctionTemplate::New(StartRunEnd)->GetFunction());
		mainloop_end_fn = Persistent<Function>::New(FunctionTemplate::New(StepEnd)->GetFunction());
		fini_end_fn = Persistent<Function>::New(FunctionTemplate::New(FiniEnd)->GetFunction());

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

		return scope.Close(args.This());
	}

#define REG_NEXT()														\
	Local<Object> process = Context::GetCurrent()->Global()->Get(String::NewSymbol("process"))->ToObject(); \
	Local<Function> fn = Local<Function>::Cast(process->Get(String::NewSymbol("nextTick"))); \
	Local<Value> argv[1] = { Local<Value>::New(step_fn) };				\
	fn->Call(process, 1, argv)

	Handle<Value> NgeApp::Step(const Arguments& args) {
		HandleScope scope;

		impl.Mainloop();

		return Undefined();
	}

	Handle<Value> NgeApp::StepEnd(const Arguments& args) {
		HandleScope scope;

		if (args.Length() > 0) {
			int ret = args[0]->Int32Value();
			if (ret == NGE_APP_QUIT) {
				impl.Fini();
				return Undefined();
			}
			else
				goto reg_next;
		}

	reg_next:
		REG_NEXT();

		return Undefined();
	}

	Handle<Value> NgeApp::StartRun(const Arguments& args) {
		HandleScope scope;

		if (!app_obj.IsEmpty()) {
			return ThrowException(Exception::TypeError(
									  String::New("Already has a NgeApp to be run.")));
		}

		NgeApp* o = Unwrap<NgeApp>(args.This());
		o->Ref();

		app_obj = Persistent<Object>::New(args.This());
		nge_registerApp(&impl);

		impl.Init();

		return Undefined();
	}

	Handle<Value> NgeApp::StartRunEnd(const Arguments& args) {
		HandleScope scope;

		REG_NEXT();

		return Undefined();
	}

	Handle<Value> NgeApp::FiniEnd(const Arguments& args) {
		HandleScope scope;

		exit(0);

		return Undefined();
	}

	Handle<Value> NgeApp::GetCurrent(const Arguments& args) {
		HandleScope scope;

		return scope.Close(Local<Object>::New(app_obj));
	}
}
