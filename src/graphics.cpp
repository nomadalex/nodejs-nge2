/**
 * @file  graphics.cpp
 * @author Kun Wang <ifreedom.cn@gmail.com>
 * @date 2012/02/12 11:48:08
 *
 *  Copyright  2012  Kun Wang <ifreedom.cn@gmail.com>
 *
 */

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

	WRAPPER_FUNC(CreateColor) {
		HandleScope scope;

		CHECK_ARG_LEN(5);

		if (!CHECK_ARG_TYPE(0, Uint32) ||
			!CHECK_ARG_TYPE(1, Uint32) ||
			!CHECK_ARG_TYPE(2, Uint32) ||
			!CHECK_ARG_TYPE(3, Uint32) ||
			!CHECK_ARG_TYPE(4, Int32))
		{
			THROW_ARG_ERROR();
		}

		uint8 r = (uint8)args[0]->Uint32Value();
		uint8 g = (uint8)args[1]->Uint32Value();
		uint8 b = (uint8)args[2]->Uint32Value();
		uint8 a = (uint8)args[3]->Uint32Value();
		int32_t dtype = args[4]->Int32Value();

		int color = ::CreateColor(r, g, b, a, dtype);

		Local<Integer> _color = Integer::New(color);

		return scope.Close(_color);
	}

	WRAPPER_FUNC(DrawLine) {
		HandleScope scope;

		CHECK_ARG_LEN(6);

		if (!CHECK_ARG_TYPE(0, Number) ||
			!CHECK_ARG_TYPE(1, Number) ||
			!CHECK_ARG_TYPE(2, Number) ||
			!CHECK_ARG_TYPE(3, Number) ||
			!CHECK_ARG_TYPE(4, Int32)  ||
			!CHECK_ARG_TYPE(5, Int32))
		{
			THROW_ARG_ERROR();
		}

		float x1 = (float)args[0]->ToNumber()->Value();
		float y1 = (float)args[1]->ToNumber()->Value();
		float x2 = (float)args[2]->ToNumber()->Value();
		float y2 = (float)args[3]->ToNumber()->Value();
		int32_t color = args[4]->Int32Value();
		int32_t dtype = args[5]->Int32Value();

		::DrawLine(x1, y1, x2, y2, color, dtype);

		return Undefined();
	}
}

#define DEF_NGE_WRAPPER(sfunc)				\
	NODE_SET_METHOD(target, #sfunc, wrapper::sfunc)

#define DEF_NGE_COLOR_1(color)					\
	NODE_DEFINE_CONSTANT(target, color);		\
	NODE_DEFINE_CONSTANT(target, color##_5551)

#define DEF_NGE_COLOR_2(color)					\
	NODE_DEFINE_CONSTANT(target, color##_5551); \
	NODE_DEFINE_CONSTANT(target, color##_4444); \
	NODE_DEFINE_CONSTANT(target, color##_565);	\
	NODE_DEFINE_CONSTANT(target, color##_8888)


void InitForNgeGraphics(Handle<Object> target) {
	NODE_DEFINE_CONSTANT(target, DISPLAY_PIXEL_FORMAT_565);
	NODE_DEFINE_CONSTANT(target, DISPLAY_PIXEL_FORMAT_5551);
	NODE_DEFINE_CONSTANT(target, DISPLAY_PIXEL_FORMAT_4444);
	NODE_DEFINE_CONSTANT(target, DISPLAY_PIXEL_FORMAT_8888);

	NODE_DEFINE_CONSTANT(target, BLACK);
	NODE_DEFINE_CONSTANT(target, BLACK_5551);
	NODE_DEFINE_CONSTANT(target, BLUE);
	NODE_DEFINE_CONSTANT(target, BLUE_5551);
	NODE_DEFINE_CONSTANT(target, GREEN);
	NODE_DEFINE_CONSTANT(target, GREEN_5551);
	NODE_DEFINE_CONSTANT(target, CYAN);
	NODE_DEFINE_CONSTANT(target, CYAN_5551);
	NODE_DEFINE_CONSTANT(target, RED);
	NODE_DEFINE_CONSTANT(target, RED_5551);
	NODE_DEFINE_CONSTANT(target, MAGENTA);
	NODE_DEFINE_CONSTANT(target, MAGENTA_5551);
	NODE_DEFINE_CONSTANT(target, BROWN);
	NODE_DEFINE_CONSTANT(target, BROWN_5551);
	NODE_DEFINE_CONSTANT(target, LTGRAY);
	NODE_DEFINE_CONSTANT(target, LTGRAY_5551);
	NODE_DEFINE_CONSTANT(target, GRAY);
	NODE_DEFINE_CONSTANT(target, GRAY_5551);
	NODE_DEFINE_CONSTANT(target, LTBLUE);
	NODE_DEFINE_CONSTANT(target, LTBLUE_5551);
	NODE_DEFINE_CONSTANT(target, LTGREEN);
	NODE_DEFINE_CONSTANT(target, LTGREEN_5551);
	NODE_DEFINE_CONSTANT(target, LTCYAN);
	NODE_DEFINE_CONSTANT(target, LTCYAN_5551);
	NODE_DEFINE_CONSTANT(target, LTRED);
	NODE_DEFINE_CONSTANT(target, LTRED_5551);
	NODE_DEFINE_CONSTANT(target, LTMAGENTA);
	NODE_DEFINE_CONSTANT(target, LTMAGENTA_5551);
	NODE_DEFINE_CONSTANT(target, YELLOW);
	NODE_DEFINE_CONSTANT(target, YELLOW_5551);
	NODE_DEFINE_CONSTANT(target, WHITE);
	NODE_DEFINE_CONSTANT(target, WHITE_5551);
	NODE_DEFINE_CONSTANT(target, DKGRAY);
	NODE_DEFINE_CONSTANT(target, DKGRAY_5551);

	DEF_NGE_COLOR_2(FONT_BG);
	DEF_NGE_COLOR_2(FONT_FG);
	DEF_NGE_COLOR_2(FONT_SH);

	DEF_NGE_WRAPPER(GetScreenContext);
	DEF_NGE_WRAPPER(InitGrahics);
	DEF_NGE_WRAPPER(FiniGrahics);
	DEF_NGE_WRAPPER(BeginScene);
	DEF_NGE_WRAPPER(EndScene);

	DEF_NGE_WRAPPER(CreateColor);
	DEF_NGE_WRAPPER(DrawLine);
}
