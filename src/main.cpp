/**
 * @file  main.cpp
 * @author Kun Wang <ifreedom.cn@gmail.com>
 * @date 2012/02/12 05:21:38
 *
 *  Copyright  2012  Kun Wang <ifreedom.cn@gmail.com>
 *
 */
#include "main.hpp"
#include "common.h"

namespace wrapper {
	WRAPPER_FUNC(NGE_Init) {
		HandleScope scope;

		CHECK_ARG_LEN(1);
		CHECK_ARGS_TYPE(!CHECK_ARG_TYPE(0, Int32));

		GET_INT_ARG(flag, 0);

		::NGE_Init(flag);

		return Undefined();
	}

	WRAPPER_FUNC(NGE_Quit) {
		HandleScope scope;

		::NGE_Quit();

		return Undefined();
	}

	WRAPPER_FUNC(NGE_SetScreenContext) {
		HandleScope scope;

		CHECK_ARG_LEN(5);

		CHECK_ARGS_TYPE(!CHECK_ARG_TYPE(0, String) ||
						!CHECK_ARG_TYPE(1, Int32) ||
						!CHECK_ARG_TYPE(2, Int32) ||
						!CHECK_ARG_TYPE(3, Int32) ||
						!CHECK_ARG_TYPE(4, Int32));

		Local<String> arg1 = args[0]->ToString();
		String::AsciiValue winname(arg1);

		int32_t screen_width = args[1]->Int32Value();
		int32_t screen_height = args[2]->Int32Value();
		int32_t screen_bpp = args[3]->Int32Value();
		int32_t screen_full = args[4]->Int32Value();

		::NGE_SetScreenContext(*winname, screen_width, screen_height, screen_bpp, screen_full);

		return Undefined();
	}

	WRAPPER_FUNC(NGE_SetNativeResolution) {
		HandleScope scope;

		CHECK_ARG_LEN(2);
		CHECK_ARGS_TYPE(!CHECK_ARG_TYPE(0, Int32) ||
						!CHECK_ARG_TYPE(1, Int32));

		int32_t width = args[0]->Int32Value();
		int32_t height = args[1]->Int32Value();

		::NGE_SetNativeResolution(width, height);

		return Undefined();
	}
}

#define DEF_NGE_WRAPPER(target, sfunc) \
	NODE_SET_METHOD(target, #sfunc, wrapper::NGE_##sfunc)

void InitForNgeMain(Handle<Object> target) {
	NODE_DEFINE_CONSTANT(target, INIT_AUDIO);
	NODE_DEFINE_CONSTANT(target, INIT_VIDEO);
	NODE_DEFINE_CONSTANT(target, INIT_ALL);

	DEF_NGE_WRAPPER(target, Init);
	DEF_NGE_WRAPPER(target, Quit);
	DEF_NGE_WRAPPER(target, SetScreenContext);
	DEF_NGE_WRAPPER(target, SetNativeResolution);
}
