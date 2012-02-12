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

#define CHECK_AND_DISPOSE(obj)					\
	if (!obj.IsEmpty())						\
		obj.Dispose()

#define CAST_TO_PFUNCTION(obj)								\
	Persistent<Function>::New(Local<Function>::Cast(obj))

#define CHECK_PFUNCTION(func)					\
	!func.IsEmpty() && func->IsFunction()

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif

#endif /* _COMMON_H */
