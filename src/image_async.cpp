/**
 * @file  image_async.cpp
 * @author Kun Wang <ifreedom.cn@gmail.com>
 * @date 2012/03/12 10:25:23
 *
 *  Copyright  2012  Kun Wang <ifreedom.cn@gmail.com>
 *
 */
#include "common.h"
#include "async_common.h"
#include "image.hpp"
#include "image_object.hpp"

#define GET_IMAGE_ASYNC_DATA(var)				\
	GET_ASYNC_DATA(wrapper::ImageAsyncData, var)

#define DEF_IMAGE_ARG_DATA(n) DEF_ARG_DATA(Image, n)

#define CREATE_IMAGE_ARG_DATA(n, var)			\
	CREATE_ARG_DATA(Image, n, var)

#define GET_IMAGE_ARG_DATA(n, var, async_data)	\
	GET_ARG_DATA(Image, n, var, async_data)

#define DELETE_IMAGE_ARG_DATA(n, var, async_data)	\
	DELETE_ARG_DATA(Image, n, var, async_data)

#define NEED_UPDATER(async_data, img)								\
	async_data->updater = new ExternalMemoryAutoUpdate<Image>(img)

#define CHECK_UPDATER(async_data)				\
	if (async_data->updater != NULL)			\
		delete async_data->updater

namespace wrapper {
	struct ImageAsyncData {
		uv_work_t request;
		Image* img;
		void* arg;
		Persistent<Function> callback;
		ExternalMemoryAutoUpdate<Image> *updater;
	};

	DEF_IMAGE_ARG_DATA(1) {
		char* filename;
		bool hasColorkey;
		int dtype;
		int colorkey;
		int swizzle;
	};

	namespace async {
		ASYNC_FUNC(image_load) {
			GET_IMAGE_ASYNC_DATA(data);
			GET_IMAGE_ARG_DATA(1, args, data);

			if (!args->hasColorkey)
				data->img->img_ = ::image_load(args->filename, args->dtype, args->swizzle);
			else
				data->img->img_ = ::image_load_colorkey(args->filename, args->dtype, args->colorkey, args->swizzle);
			delete args->filename;
		}
		ASYNC_FUNC(image_loadAfter) {
			HandleScope scope;
			GET_IMAGE_ASYNC_DATA(data);
			GET_IMAGE_ARG_DATA(1, args, data);

			CHECK_UPDATER(data);
			const unsigned argc = 2;
			Local<Value> argv[argc] = {
				Local<Value>::New(Null()),
				Local<Value>::New(data->img->handle_)
			};

			data->img->updateProp();
			data->img->release();
			delete args;

			DO_ASYNC_CALLBACK(data, argc, argv);
			delete data;
		}
	}

	WRAPPER_FUNC(image_load_async) {
		HandleScope scope;

		CHECK_ARG_LEN(4);

		CHECK_ARGS_TYPE(!CHECK_STR_ARG(0) ||
						!CHECK_INT_ARG(1) ||
						!CHECK_INT_ARG(2) ||
						!CHECK_FUNC_ARG(3));

		ImageAsyncData* data = new ImageAsyncData;

		CREATE_IMAGE_ARG_DATA(1, arg);
		GET_ASYNC_STR_ARG(arg, filename, 0);
		GET_ASYNC_INT_ARG(arg, dtype, 1);
		GET_ASYNC_INT_ARG(arg, swizzle, 2);
		GET_ASYNC_CALLBACK_ARG(data, 3);
		arg->hasColorkey = false;

		CREATE_IMG(img);

		NEED_UPDATER(data, img);
		img->retain();
		data->img = img;

		SET_ARG_DATA(data, arg);
		SET_REQUEST_DATA(data);
		PUT_UV_QUEUE(data, image_load);

		return Undefined();
	}

	WRAPPER_FUNC(image_load_colorkey_async) {
		HandleScope scope;

		CHECK_ARG_LEN(5);

		CHECK_ARGS_TYPE(!CHECK_STR_ARG(0) ||
						!CHECK_INT_ARG(1) ||
						!CHECK_INT_ARG(2) ||
						!CHECK_INT_ARG(3) ||
						!CHECK_FUNC_ARG(4));

		ImageAsyncData* data = new ImageAsyncData;

		CREATE_IMAGE_ARG_DATA(1, arg);
		GET_ASYNC_STR_ARG(arg, filename, 0);
		GET_ASYNC_INT_ARG(arg, dtype, 1);
		GET_ASYNC_INT_ARG(arg, colorkey, 2);
		GET_ASYNC_INT_ARG(arg, swizzle, 3);
		GET_ASYNC_CALLBACK_ARG(data, 4);
		arg->hasColorkey = true;

		CREATE_IMG(img);

		NEED_UPDATER(data, img);
		img->retain();
		data->img = img;

		SET_ARG_DATA(data, arg);
		SET_REQUEST_DATA(data);
		PUT_UV_QUEUE(data, image_load);

		return Undefined();
	}

	DEF_IMAGE_ARG_DATA(2) {
		char* filename;
		uint32_t alpha, rle;
		int ret;
	};

	namespace async {
		ASYNC_FUNC(image_save) {
			GET_IMAGE_ASYNC_DATA(data);
			GET_IMAGE_ARG_DATA(2, args, data);

			args->ret = ::image_save(data->img->img_, args->filename, (uint8)(args->alpha), (uint8)(args->rle));
			delete args->filename;
		}
		ASYNC_FUNC(image_saveAfter) {
			HandleScope scope;
			GET_IMAGE_ASYNC_DATA(data);
			GET_IMAGE_ARG_DATA(2, args, data);

			const unsigned argc = 2;
			Local<Value> argv[argc] = {
				Local<Value>::New(Null()),
				Integer::New(args->ret)
			};

			data->img->release();
			delete args;

			DO_ASYNC_CALLBACK(data, argc, argv);
			delete data;
		}
	}

	WRAPPER_FUNC(image_save_async) {
		HandleScope scope;

		CHECK_ARG_LEN(5);

		CHECK_ARGS_TYPE(!CHECK_IMG_ARG(0) ||
						!CHECK_STR_ARG(1) ||
						!CHECK_UINT_ARG(2) ||
						!CHECK_UINT_ARG(3) ||
						!CHECK_FUNC_ARG(4));

		ImageAsyncData* data = new ImageAsyncData;

		CREATE_IMAGE_ARG_DATA(2, arg);
		GET_IMG_ARG(img, 0);
		GET_ASYNC_STR_ARG(arg, filename, 1);
		GET_ASYNC_UINT_ARG(arg, alpha, 2);
		GET_ASYNC_UINT_ARG(arg, rle, 3);
		GET_ASYNC_CALLBACK_ARG(data, 4);

		img->retain();
		data->img = img;

		SET_ARG_DATA(data, arg);
		SET_REQUEST_DATA(data);
		PUT_UV_QUEUE(data, image_save);

		return Undefined();
	}
}

#define DEF_NGE_WRAPPER(sfunc)						\
	NODE_SET_METHOD(target, #sfunc, wrapper::sfunc)

void InitForNgeImageAsync(Handle<Object> target) {
	DEF_NGE_WRAPPER(image_load_async);
	DEF_NGE_WRAPPER(image_load_colorkey_async);
	DEF_NGE_WRAPPER(image_save_async);
}
