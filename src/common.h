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

#define CHECK_UINT_ARG(pos)						\
	CHECK_ARG_TYPE(pos, Uint32)

#define CHECK_INT_ARG(pos)						\
	CHECK_ARG_TYPE(pos, Int32)

#define CHECK_FLOAT_ARG(pos)					\
	CHECK_ARG_TYPE(pos, Number)

#define CHECK_ARRAY_ARG(pos)					\
	CHECK_ARG_TYPE(pos, Array)

#define GET_UINT_ARG(var, pos)					\
	int var = args[pos]->Uint32Value()

#define GET_INT_ARG(var, pos)					\
	int var = args[pos]->Int32Value()

#define GET_FLOAT_ARG(var, pos)					\
	float var = (float)args[pos]->ToNumber()->Value()

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

#define OBJECT_SET_PROP(obj, name, value)		\
	obj->Set(String::NewSymbol(name), value)

#define OBJECT_SET_STR_PROP(obj, name, value)		\
	OBJECT_SET_PROP(obj, name, String::New(value))

#define OBJECT_SET_INT_PROP(obj, name, value)		\
	OBJECT_SET_PROP(obj, name, Integer::New(value))

#define OBJECT_SET_FLOAT_PROP(obj, name, value)		\
	OBJECT_SET_PROP(obj, name, Number::New(value))

#define COPY_PROP(obj, type, st, name)				\
	OBJECT_SET_##type##_PROP(obj, #name, st->name)

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif

#endif /* _COMMON_H */
