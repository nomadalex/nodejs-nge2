/**
 * @file  common.h
 * @author Kun Wang <ifreedom.cn@gmail.com>
 * @date 2012/02/12 10:32:57
 *
 *  Copyright  2012  Kun Wang <ifreedom.cn@gmail.com>
 *
 */

#ifndef _COMMON_H
#define _COMMON_H

#include <v8.h>
#include <node.h>
#include "libnge2.h"

using namespace node;
using namespace v8;

namespace wrapper {
	struct Rect2 {
		float x, y, w, h;
	};

	template <class T>
		class ExternalMemoryAutoUpdate {
	public:
		ExternalMemoryAutoUpdate(T* obj) {
			V8::AdjustAmountOfExternalAllocatedMemory(-obj->getExternalAllocatedSize());
			obj_ = obj;
		}
		~ExternalMemoryAutoUpdate() {
			V8::AdjustAmountOfExternalAllocatedMemory(obj_->getExternalAllocatedSize());
		}

	private:
		T * obj_;
	};

	template <class T>
		class HandleWrap : public ObjectWrap {
	public:
	HandleWrap() : ObjectWrap() {}

		static Handle<Value> NewInstance() {
			HandleScope scope;

			Local<Object> obj = constructor_template->GetFunction()->NewInstance(0, NULL);

			return scope.Close(obj);
		}

		inline static bool HasInstance(Handle<Value> obj) {
			return constructor_template->HasInstance(obj);
		}

		void retain() {
			Ref();
		}

		void release() {
			Unref();
		}

	protected:
		inline static void Init(const char* ctor_name, Handle<Object> target) {
			Local<String> name = String::NewSymbol(ctor_name);

			Local<FunctionTemplate> t = FunctionTemplate::New(New);

			t->InstanceTemplate()->SetInternalFieldCount(1);
			t->SetClassName(name);

			target->Set(name, t->GetFunction());
			constructor_template = Persistent<FunctionTemplate>::New(t);
		}

		static Persistent<FunctionTemplate> constructor_template;

	private:
		static Handle<Value> New(const Arguments& args) {
			HandleScope scope;

			T* o = new T();

			o->Wrap(args.This());
			return scope.Close(args.This());
		}
	};
}

#define WRAPPER_FUNC(name)						\
	Handle<Value> name(const Arguments& args)

#define THROW_ARG_ERROR()												\
	return ThrowException(Exception::TypeError(String::New("Arguments Error.")))

#define CHECK_ARG_LEN(len)						\
	if (args.Length() < len) {					\
		THROW_ARG_ERROR();						\
	}

#define CHECK_ARG_TYPE(idx, type)				\
	(args[idx]->Is##type())

#define CHECK_ARGS_TYPE(expr)					\
	if (expr) {									\
		THROW_ARG_ERROR();						\
	}

#define CHECK_AND_DISPOSE(obj)					\
	if (!obj.IsEmpty())						\
		obj.Dispose()

#define CAST_TO_PFUNCTION(obj)								\
	Persistent<Function>::New(Local<Function>::Cast(obj))

#define CHECK_PFUNCTION(func)					\
	!func.IsEmpty() && func->IsFunction()

#define CHECK_STR_ARG(pos)						\
	CHECK_ARG_TYPE(pos, String)

#define CHECK_UINT_ARG(pos)						\
	CHECK_ARG_TYPE(pos, Uint32)

#define CHECK_INT_ARG(pos)						\
	CHECK_ARG_TYPE(pos, Int32)

#define CHECK_FLOAT_ARG(pos)					\
	CHECK_ARG_TYPE(pos, Number)

#define CHECK_OBJ_ARG(pos)						\
	CHECK_ARG_TYPE(pos, Object)

#define CHECK_WRAPPED_OBJ_ARG(type, pos)					\
	(CHECK_ARG_TYPE(pos, Object) && type::HasInstance(args[pos]))

#define CHECK_ARRAY_ARG(pos)					\
	CHECK_ARG_TYPE(pos, Array)

#define CHECK_POINT_ARG(startpos)				\
	(CHECK_ARG_TYPE(startpos, Number) &&		\
	 CHECK_ARG_TYPE(startpos + 1, Number))

#define CHECK_WIDTH_HEIGHT_ARG(startpos) CHECK_POINT_ARG(startpos)

#define CHECK_COLOR_ARG(startpos)				\
	(CHECK_ARG_TYPE(startpos, Int32)  &&		\
	 CHECK_ARG_TYPE(startpos + 1, Int32))

#define CHECK_RECT_ARG(startpos)				\
	(CHECK_POINT_ARG(startpos) && \
	 CHECK_WIDTH_HEIGHT_ARG(startpos + 2))


#define GET_STR_ARG(var, pos)						\
	Local<String> var##___ = args[pos]->ToString();	\
	String::AsciiValue var(var##___)

#define GET_U8STR_ARG(var, pos)						\
	Local<String> var##___ = args[pos]->ToString();	\
	String::Utf8Value var(var##___)

#define GET_UINT_ARG(var, pos)					\
	int var = args[pos]->Uint32Value()

#define GET_INT_ARG(var, pos)					\
	int var = args[pos]->Int32Value()

#define GET_FLOAT_ARG(var, pos)					\
	float var = (float)args[pos]->ToNumber()->Value()

#define GET_OBJ_ARG(var, pos)					\
	Handle<Object> var = args[pos]->ToObject()

#define UNWRAP_OBJ(type, var, obj)				\
	type* var = type::Unwrap<type>(obj)

#define GET_WRAPPED_OBJ_ARG(type, var, pos)			\
	Handle<Object> var##__ = args[pos]->ToObject();	\
	UNWRAP_OBJ(type, var, var##__)

#define GET_ARRAY_ARG(native_type, value_expr, var, pos)			\
	native_type * var = NULL;										\
	do {															\
		Local<Array> __a = Array::Cast(*args[pos]);					\
		uint32_t len = __a->Length();								\
		if (len > 0)												\
			var = new native_type[len];								\
		for (uint32_t i=0; i<len; i++) {							\
			var[i] = (native_type)__a->Get(i)->value_expr;			\
		}															\
	} while(0)

#define GET_FLOAT_ARRAY_ARG(var, pos)								\
	GET_ARRAY_ARG(float, ToNumber()->Value(), var, pos)

#define GET_INT_ARRAY_ARG(var, pos)									\
	GET_ARRAY_ARG(int, Int32Value(), var, pos)

#define RELEASE_ARRAY_ARG(var)					\
	if (var != NULL)							\
		delete[] var

#define GET_POINT_ARG(var, startpos)						\
	pointf var;												\
	var.x = (float)args[startpos]->ToNumber()->Value();		\
	var.y = (float)args[startpos + 1]->ToNumber()->Value()

#define GET_WIDTH_HEIGHT_ARG(startpos)								\
	float width = (float)args[startpos]->ToNumber()->Value();		\
	float height = (float)args[startpos + 1]->ToNumber()->Value()

#define GET_COLOR_ARG(startpos)							\
	int32_t color = args[startpos]->Int32Value();		\
	int32_t dtype = args[startpos + 1]->Int32Value()

#define GET_RECT_ARG(var, startpos)							\
	Rect2 var;												\
	var.x = (float)args[startpos]->ToNumber()->Value();		\
	var.y = (float)args[startpos + 1]->ToNumber()->Value(); \
	var.w = (float)args[startpos + 2]->ToNumber()->Value();	\
	var.h = (float)args[startpos + 3]->ToNumber()->Value()


#define OBJECT_SET_PROP(obj, name, value)		\
	obj->Set(String::NewSymbol(name), value)

#define OBJECT_SET_STR_PROP(obj, name, value)		\
	OBJECT_SET_PROP(obj, name, String::New(value))

#define OBJECT_SET_INT_PROP(obj, name, value)		\
	OBJECT_SET_PROP(obj, name, Integer::New(value))

#define OBJECT_SET_UINT_PROP(obj, name, value)		\
	OBJECT_SET_PROP(obj, name, Integer::NewFromUnsigned(value))

#define OBJECT_SET_FLOAT_PROP(obj, name, value)		\
	OBJECT_SET_PROP(obj, name, Number::New(value))

#define COPY_PROP(obj, type, st, name)				\
	OBJECT_SET_##type##_PROP(obj, #name, st->name)

#define CHECK_FUNC_ARG(pos)						\
	CHECK_ARG_TYPE(pos, Function)

#define GET_FUNC_ARG(var, pos)								\
	Local<Function> var = Local<Function>::Cast(args[pos])

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif

#endif /* _COMMON_H */
