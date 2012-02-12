/**
 * @file  graphics.cpp
 * @author Kun Wang <ifreedom.cn@gmail.com>
 * @date 2012/02/12 11:48:08
 *
 *  Copyright  2012  Kun Wang <ifreedom.cn@gmail.com>
 *
 */

#include "libnge2.h"
#include "graphics.hpp"
#include "common.h"

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

namespace wrapper {
	WRAPPER_FUNC(GetScreenContext) {
		HandleScope scope;

		screen_context_p context = ::GetScreenContext();

		Local<Object> obj = Object::New();
		COPY_PROP(obj, STR, context, name);
		COPY_PROP(obj, INT, context, width);
		COPY_PROP(obj, INT, context, height);
		COPY_PROP(obj, INT, context, bpp);
		COPY_PROP(obj, INT, context, fullscreen);
		COPY_PROP(obj, INT, context, ori_width);
		COPY_PROP(obj, INT, context, ori_height);
		COPY_PROP(obj, FLOAT, context, rate_w);
		COPY_PROP(obj, FLOAT, context, rate_h);

		return scope.Close(obj);
	}

	WRAPPER_FUNC(InitGrahics) {
		HandleScope scope;

		::InitGrahics();

		return Undefined();
	}

	WRAPPER_FUNC(FiniGrahics) {
		HandleScope scope;

		::FiniGrahics();

		return Undefined();
	}

	WRAPPER_FUNC(BeginScene) {
		HandleScope scope;

		CHECK_ARG_LEN(1);

		if (!CHECK_ARG_TYPE(0, Uint32)){
			THROW_ARG_ERROR();
		}

		uint32_t clear = args[0]->Uint32Value();
		::BeginScene(clear);

		return Undefined();
	}

	WRAPPER_FUNC(EndScene) {
		HandleScope scope;

		::EndScene();

		return Undefined();
	}
}

#define DEF_NGE_WRAPPER(sfunc)				\
	NODE_SET_METHOD(target, #sfunc, wrapper::sfunc)

void InitForNgeGraphics(Handle<Object> target) {
	DEF_NGE_WRAPPER(GetScreenContext);
	DEF_NGE_WRAPPER(InitGrahics);
	DEF_NGE_WRAPPER(FiniGrahics);
	DEF_NGE_WRAPPER(BeginScene);
	DEF_NGE_WRAPPER(EndScene);
}
