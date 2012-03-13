/**
 * @file  async_common.h
 * @author Kun Wang <ifreedom.cn@gmail.com>
 * @date 2012/03/12 10:24:43
 *
 *  Copyright  2012  Kun Wang <ifreedom.cn@gmail.com>
 *
 */

#ifndef _ASYNC_COMMON_H
#define _ASYNC_COMMON_H

#define SET_REQUEST_DATA(async_data)							\
	async_data->request.data = static_cast<void*>(async_data);

#define ASYNC_FUNC(func) void func (uv_work_t* req)

#define GET_ASYNC_DATA(type, var)				\
	type* var = static_cast<type*>(req->data)

#define DEF_ARG_DATA(type, n) struct type##FuncArg##n

#define CREATE_ARG_DATA(type, n, var) type##FuncArg##n * var = new type##FuncArg##n

#define SET_ARG_DATA(async_data, arg_data)			\
	async_data->arg = static_cast<void*>(arg_data)

#define GET_ARG_DATA(type, n, var, async_data)							\
	type##FuncArg##n * var = static_cast<type##FuncArg##n *>(async_data->arg)

#define DELETE_ARG_DATA(type, n, var, async_data)	\
	GET_ARG_DATA(type, n, var, async_data);			\
	delete var

#define GET_ASYNC_STR_ARG(arg, name, pos)		\
	GET_STR_ARG(name, pos);						\
	arg->name = new char[name.length()+1];		\
	memcpy(arg->name, *name, name.length()+1)

#define GET_ASYNC_UINT_ARG(arg, name, pos)		\
	arg->name = args[pos]->Uint32Value()

#define GET_ASYNC_INT_ARG(arg, name, pos)		\
	arg->name = args[pos]->Int32Value()

#define GET_ASYNC_FLOAT_ARG(arg, name, pos)				\
	arg->name = (float)args[pos]->ToNumber()->Value()

#define GET_ASYNC_CALLBACK_ARG(data, pos)								\
	data->callback = CAST_TO_PFUNCTION(args[pos])

#define PUT_UV_QUEUE(data, func)										\
	int status___ = uv_queue_work(uv_default_loop(), &data->request, async::func, async::func##After); \
	assert(status___ == 0)

#define DO_ASYNC_CALLBACK(data, argc, argv)								\
	TryCatch try_catch;													\
	data->callback->Call(Context::GetCurrent()->Global(), argc, argv);	\
	if (try_catch.HasCaught()) {										\
		node::FatalException(try_catch);								\
	}																	\
	data->callback.Dispose()

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif

#endif /* _ASYNC_COMMON_H */
