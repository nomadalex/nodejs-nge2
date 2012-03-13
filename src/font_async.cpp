/**
 * @file  font_async.cpp
 * @author Kun Wang <ifreedom.cn@gmail.com>
 * @date 2012/03/13 11:50:03
 *
 *  Copyright  2012  Kun Wang <ifreedom.cn@gmail.com>
 *
 */

#include "common.h"
#include "async_common.h"
#include "font_async.hpp"
#include "font_object.hpp"

#define GET_FONT_ASYNC_DATA(var)					\
	GET_ASYNC_DATA(wrapper::FontAsyncData, var)

#define DEF_FONT_ARG_DATA(n) DEF_ARG_DATA(Font, n)

#define CREATE_FONT_ARG_DATA(n, var)			\
	CREATE_ARG_DATA(Font, n, var)

#define GET_FONT_ARG_DATA(n, var, async_data)	\
	GET_ARG_DATA(Font, n, var, async_data)

enum {
	TYPE_HZK = 0,
	TYPE_NFONT,
	TYPE_FREETYPE
};

namespace wrapper {
	struct FontAsyncData {
		uv_work_t request;
		Font* font;
		void* arg;
		Persistent<Function> callback;
	};

	DEF_FONT_ARG_DATA(1) {
		uint8_t type;
		char* cname;
		char* aname;
		int height, disp;
	};

	namespace async {
		ASYNC_FUNC(CreateFont) {
			GET_FONT_ASYNC_DATA(data);
			GET_FONT_ARG_DATA(1, args, data);

			switch (args->type) {
			case TYPE_HZK:
				data->font->data = ::create_font_hzk(args->cname, args->aname, args->height, args->disp);
				delete args->aname;
				break;
			case TYPE_NFONT:
				data->font->data = ::create_font_nfont(args->cname, args->disp);
				break;
			case TYPE_FREETYPE:
				data->font->data = ::create_font_freetype(args->cname, args->height, args->disp);
				break;
			}

			delete args->cname;
		}
		ASYNC_FUNC(CreateFontAfter) {
			HandleScope scope;
			GET_FONT_ASYNC_DATA(data);
			GET_FONT_ARG_DATA(1, args, data);

			const unsigned argc = 2;
			Local<Value> argv[argc] = {
				Local<Value>::New(Null()),
				Local<Value>::New(Null())
			};

			if (data->font->data)
				argv[1] = Local<Value>::New(data->font->handle_);

			delete args;
			data->font->release();

			DO_ASYNC_CALLBACK(data, argc, argv);
			delete data;
		}
	}

	WRAPPER_FUNC(create_font_hzk_async) {
		HandleScope scope;

		CHECK_ARG_LEN(5);

		CHECK_ARGS_TYPE(!CHECK_STR_ARG(0) ||
						!CHECK_STR_ARG(1) ||
						!CHECK_INT_ARG(2) ||
						!CHECK_INT_ARG(3) ||
						!CHECK_FUNC_ARG(4));

		FontAsyncData* data = new FontAsyncData;

		CREATE_FONT_ARG_DATA(1, arg);

		GET_ASYNC_STR_ARG(arg, cname, 0);
		GET_ASYNC_STR_ARG(arg, aname, 1);
		GET_ASYNC_INT_ARG(arg, height, 2);
		GET_ASYNC_INT_ARG(arg, disp, 3);
		GET_ASYNC_CALLBACK_ARG(data, 4);
		arg->type = TYPE_HZK;

		CREATE_FONT(font);

		font->retain();
		data->font = font;

		SET_ARG_DATA(data, arg);
		SET_REQUEST_DATA(data);
		PUT_UV_QUEUE(data, CreateFont);

		return Undefined();
	}

	WRAPPER_FUNC(create_font_freetype_async) {
		HandleScope scope;

		CHECK_ARG_LEN(4);

		CHECK_ARGS_TYPE(!CHECK_STR_ARG(0) ||
						!CHECK_INT_ARG(1) ||
						!CHECK_INT_ARG(2) ||
						!CHECK_FUNC_ARG(3));

		FontAsyncData* data = new FontAsyncData;

		CREATE_FONT_ARG_DATA(1, arg);

		GET_ASYNC_STR_ARG(arg, cname, 0);
		GET_ASYNC_INT_ARG(arg, height, 1);
		GET_ASYNC_INT_ARG(arg, disp, 2);
		GET_ASYNC_CALLBACK_ARG(data, 3);
		arg->type = TYPE_FREETYPE;

		CREATE_FONT(font);

		font->retain();
		data->font = font;

		SET_ARG_DATA(data, arg);
		SET_REQUEST_DATA(data);
		PUT_UV_QUEUE(data, CreateFont);

		return Undefined();
	}

	WRAPPER_FUNC(create_font_nfont_async) {
		HandleScope scope;

		CHECK_ARG_LEN(3);

		CHECK_ARGS_TYPE(!CHECK_STR_ARG(0) ||
						!CHECK_INT_ARG(1) ||
						!CHECK_FUNC_ARG(2));

		FontAsyncData* data = new FontAsyncData;

		CREATE_FONT_ARG_DATA(1, arg);

		GET_ASYNC_STR_ARG(arg, cname, 0);
		GET_ASYNC_INT_ARG(arg, disp, 1);
		GET_ASYNC_CALLBACK_ARG(data, 2);
		arg->type = TYPE_NFONT;

		CREATE_FONT(font);

		font->retain();
		data->font = font;

		SET_ARG_DATA(data, arg);
		SET_REQUEST_DATA(data);
		PUT_UV_QUEUE(data, CreateFont);

		return Undefined();
	}
}

#define DEF_NGE_WRAPPER(sfunc)						\
	NODE_SET_METHOD(target, #sfunc, wrapper::sfunc)

void InitForNgeFontAsync(Handle<Object> target) {
	DEF_NGE_WRAPPER(create_font_hzk_async);
	DEF_NGE_WRAPPER(create_font_freetype_async);
	DEF_NGE_WRAPPER(create_font_nfont_async);
}

