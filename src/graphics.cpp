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

		CHECK_ARGS_TYPE(!CHECK_ARG_TYPE(0, Uint32));

		uint32_t clear = args[0]->Uint32Value();
		::BeginScene(clear);

		return Undefined();
	}

	WRAPPER_FUNC(EndScene) {
		HandleScope scope;

		::EndScene();

		return Undefined();
	}

	WRAPPER_FUNC(ShowFps) {
		HandleScope scope;

		::ShowFps();

		return Undefined();
	}

	WRAPPER_FUNC(LimitFps) {
		HandleScope scope;

		CHECK_ARG_LEN(1);

		CHECK_ARGS_TYPE(!CHECK_ARG_TYPE(0, Uint32));

		uint32_t fps = args[0]->Uint32Value();

		::LimitFps(fps);

		return Undefined();
	}

	WRAPPER_FUNC(SetClip) {
		HandleScope scope;

		CHECK_ARG_LEN(4);

		CHECK_ARGS_TYPE(!CHECK_ARG_TYPE(0, Int32) ||
						!CHECK_ARG_TYPE(1, Int32) ||
						!CHECK_ARG_TYPE(2, Int32) ||
						!CHECK_ARG_TYPE(3, Int32));

		int x = args[0]->Int32Value();
		int y = args[1]->Int32Value();
		int w = args[2]->Int32Value();
		int h = args[3]->Int32Value();

		::SetClip(x,y,w,h);

		return Undefined();
	}

	WRAPPER_FUNC(ResetClip) {
		HandleScope scope;

		::ResetClip();

		return Undefined();
	}

	WRAPPER_FUNC(SetScreenColor) {
		HandleScope scope;

		CHECK_ARG_LEN(4);

		CHECK_ARGS_TYPE(!CHECK_ARG_TYPE(0, Uint32) ||
						!CHECK_ARG_TYPE(1, Uint32) ||
						!CHECK_ARG_TYPE(2, Uint32) ||
						!CHECK_ARG_TYPE(3, Uint32));

		uint8 r = (uint8)args[0]->Uint32Value();
		uint8 g = (uint8)args[1]->Uint32Value();
		uint8 b = (uint8)args[2]->Uint32Value();
		uint8 a = (uint8)args[3]->Uint32Value();

		int color = ::SetScreenColor(r, g, b, a);

		Local<Integer> _color = Integer::New(color);

		return scope.Close(_color);
	}

	WRAPPER_FUNC(CreateColor) {
		HandleScope scope;

		CHECK_ARG_LEN(5);

		CHECK_ARGS_TYPE(!CHECK_ARG_TYPE(0, Uint32) ||
						!CHECK_ARG_TYPE(1, Uint32) ||
						!CHECK_ARG_TYPE(2, Uint32) ||
						!CHECK_ARG_TYPE(3, Uint32) ||
						!CHECK_ARG_TYPE(4, Int32));

		uint8 r = (uint8)args[0]->Uint32Value();
		uint8 g = (uint8)args[1]->Uint32Value();
		uint8 b = (uint8)args[2]->Uint32Value();
		uint8 a = (uint8)args[3]->Uint32Value();
		int32_t dtype = args[4]->Int32Value();

		int color = ::CreateColor(r, g, b, a, dtype);

		Local<Integer> _color = Integer::New(color);

		return scope.Close(_color);
	}

#define CHECK_POINT_ARG(startpos)				\
	(CHECK_ARG_TYPE(startpos, Number) &&		\
	 CHECK_ARG_TYPE(startpos + 1, Number))

#define CHECK_WIDTH_HEIGHT_ARG(startpos) CHECK_POINT_ARG(startpos)

#define CHECK_COLOR_ARG(startpos)				\
	(CHECK_ARG_TYPE(startpos, Int32)  &&		\
	 CHECK_ARG_TYPE(startpos + 1, Int32))

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

	WRAPPER_FUNC(DrawLine) {
		HandleScope scope;

		CHECK_ARG_LEN(6);

		CHECK_ARGS_TYPE(!CHECK_POINT_ARG(0) ||
						!CHECK_POINT_ARG(2) ||
						!CHECK_COLOR_ARG(4));

		GET_POINT_ARG(p1, 0);
		GET_POINT_ARG(p2, 2);
		GET_COLOR_ARG(4);

		::DrawLine(p1.x, p1.y, p2.x, p2.y, color, dtype);

		return Undefined();
	}

	WRAPPER_FUNC(DrawRect) {
		HandleScope scope;

		CHECK_ARG_LEN(6);

		CHECK_ARGS_TYPE(!CHECK_POINT_ARG(0) ||
						!CHECK_WIDTH_HEIGHT_ARG(2) ||
						!CHECK_COLOR_ARG(4));

		GET_POINT_ARG(pt, 0);
		GET_WIDTH_HEIGHT_ARG(2);
		GET_COLOR_ARG(4);

		::DrawRect(pt.x, pt.y, width, height, color, dtype);

		return Undefined();
	}

#undef FillRect
	WRAPPER_FUNC(FillRect) {
		HandleScope scope;

		CHECK_ARG_LEN(6);

		CHECK_ARGS_TYPE(!CHECK_POINT_ARG(0) ||
						!CHECK_WIDTH_HEIGHT_ARG(2) ||
						!CHECK_COLOR_ARG(4));

		GET_POINT_ARG(pt, 0);
		GET_WIDTH_HEIGHT_ARG(2);
		GET_COLOR_ARG(4);

		::NGE_FillRect(pt.x, pt.y, width, height, color, dtype);

		return Undefined();
	}

	WRAPPER_FUNC(FillRectGrad) {
		HandleScope scope;

		CHECK_ARG_LEN(6);

		CHECK_ARGS_TYPE(!CHECK_POINT_ARG(0) ||
						!CHECK_WIDTH_HEIGHT_ARG(2) ||
						!CHECK_ARRAY_ARG(4) ||
						!CHECK_ARG_TYPE(5, Int32));

		GET_POINT_ARG(pt, 0);
		GET_WIDTH_HEIGHT_ARG(2);
		GET_INT_ARRAY_ARG(colors, 4);
		GET_INT_ARG(dtype, 5);

		::FillRectGrad(pt.x, pt.y, width, height, colors, dtype);

		RELEASE_ARRAY_ARG(colors);

		return Undefined();
	}

	WRAPPER_FUNC(PutPix) {
		HandleScope scope;

		CHECK_ARG_LEN(4);

		CHECK_ARGS_TYPE(!CHECK_POINT_ARG(0) ||
						!CHECK_COLOR_ARG(2));

		GET_POINT_ARG(pt, 0);
		GET_COLOR_ARG(2);

		::PutPix(pt.x, pt.y, color, dtype);

		return Undefined();
	}

	WRAPPER_FUNC(DrawCircle) {
		HandleScope scope;

		CHECK_ARG_LEN(5);

		CHECK_ARGS_TYPE(!CHECK_POINT_ARG(0) ||
						!CHECK_FLOAT_ARG(2) ||
						!CHECK_COLOR_ARG(3));

		GET_POINT_ARG(pt, 0);
		GET_FLOAT_ARG(radius, 2);
		GET_COLOR_ARG(3);

		::DrawCircle(pt.x, pt.y, radius, color, dtype);

		return Undefined();
	}

	WRAPPER_FUNC(FillCircle) {
		HandleScope scope;

		CHECK_ARG_LEN(5);

		CHECK_ARGS_TYPE(!CHECK_POINT_ARG(0) ||
						!CHECK_FLOAT_ARG(2) ||
						!CHECK_COLOR_ARG(3));

		GET_POINT_ARG(pt, 0);
		GET_FLOAT_ARG(radius, 2);
		GET_COLOR_ARG(3);

		::FillCircle(pt.x, pt.y, radius, color, dtype);

		return Undefined();
	}

	WRAPPER_FUNC(DrawEllipse) {
		HandleScope scope;

		CHECK_ARG_LEN(6);

		CHECK_ARGS_TYPE(!CHECK_POINT_ARG(0) ||
						!CHECK_FLOAT_ARG(2) ||
						!CHECK_FLOAT_ARG(3) ||
						!CHECK_COLOR_ARG(4));

		GET_POINT_ARG(pt, 0);
		GET_FLOAT_ARG(xradius, 2);
		GET_FLOAT_ARG(yradius, 3);
		GET_COLOR_ARG(4);

		::DrawEllipse(pt.x, pt.y, xradius, yradius, color, dtype);

		return Undefined();
	}

	WRAPPER_FUNC(FillEllipse) {
		HandleScope scope;

		CHECK_ARG_LEN(6);

		CHECK_ARGS_TYPE(!CHECK_POINT_ARG(0) ||
						!CHECK_FLOAT_ARG(2) ||
						!CHECK_FLOAT_ARG(3) ||
						!CHECK_COLOR_ARG(4));

		GET_POINT_ARG(pt, 0);
		GET_FLOAT_ARG(xradius, 2);
		GET_FLOAT_ARG(yradius, 3);
		GET_COLOR_ARG(4);

		::FillEllipse(pt.x, pt.y, xradius, yradius, color, dtype);

		return Undefined();
	}

	WRAPPER_FUNC(DrawPolygon) {
		HandleScope scope;

		CHECK_ARG_LEN(5);

		CHECK_ARGS_TYPE(!CHECK_ARRAY_ARG(0) ||
						!CHECK_ARRAY_ARG(1) ||
						!CHECK_ARG_TYPE(2, Int32) ||
						!CHECK_COLOR_ARG(3));

		GET_FLOAT_ARRAY_ARG(x, 0);
		GET_FLOAT_ARRAY_ARG(y, 1);
		GET_INT_ARG(count, 2);
		GET_COLOR_ARG(3);

		::DrawPolygon(x, y, count, color, dtype);

		RELEASE_ARRAY_ARG(x);
		RELEASE_ARRAY_ARG(y);

		return Undefined();
	}

	WRAPPER_FUNC(FillPolygon) {
		HandleScope scope;

		CHECK_ARG_LEN(5);

		CHECK_ARGS_TYPE(!CHECK_ARRAY_ARG(0) ||
						!CHECK_ARRAY_ARG(1) ||
						!CHECK_ARG_TYPE(2, Int32) ||
						!CHECK_ARG_TYPE(2, Int32) ||
						!CHECK_ARG_TYPE(4, Int32));

		GET_FLOAT_ARRAY_ARG(x, 0);
		GET_FLOAT_ARRAY_ARG(y, 1);
		GET_INT_ARG(count, 2);
		GET_INT_ARG(color, 3);
		GET_INT_ARG(dtype, 4);

		::FillPolygon(x, y, count, color, dtype);

		RELEASE_ARRAY_ARG(x);
		RELEASE_ARRAY_ARG(y);

		return Undefined();
	}

	WRAPPER_FUNC(FillPolygonGrad) {
		HandleScope scope;

		CHECK_ARG_LEN(5);

		CHECK_ARGS_TYPE(!CHECK_ARRAY_ARG(0) ||
						!CHECK_ARRAY_ARG(1) ||
						!CHECK_ARG_TYPE(2, Int32) ||
						!CHECK_ARRAY_ARG(3) ||
						!CHECK_ARG_TYPE(4, Int32));

		GET_FLOAT_ARRAY_ARG(x, 0);
		GET_FLOAT_ARRAY_ARG(y, 1);
		GET_INT_ARG(count, 2);
		GET_INT_ARRAY_ARG(colors, 3);
		GET_INT_ARG(dtype, 4);

		::FillPolygonGrad(x, y, count, colors, dtype);

		RELEASE_ARRAY_ARG(x);
		RELEASE_ARRAY_ARG(y);
		RELEASE_ARRAY_ARG(colors);

		return Undefined();
	}
}

#define DEF_NGE_WRAPPER(sfunc)						\
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

	DEF_NGE_WRAPPER(ShowFps);
	DEF_NGE_WRAPPER(LimitFps);

	DEF_NGE_WRAPPER(SetClip);
	DEF_NGE_WRAPPER(ResetClip);

	DEF_NGE_WRAPPER(SetScreenColor);
	DEF_NGE_WRAPPER(CreateColor);
	DEF_NGE_WRAPPER(DrawLine);
	DEF_NGE_WRAPPER(DrawRect);
	DEF_NGE_WRAPPER(FillRect);
	DEF_NGE_WRAPPER(FillRectGrad);
	DEF_NGE_WRAPPER(PutPix);
	DEF_NGE_WRAPPER(DrawCircle);
	DEF_NGE_WRAPPER(FillCircle);
	DEF_NGE_WRAPPER(DrawEllipse);
	DEF_NGE_WRAPPER(FillEllipse);
	DEF_NGE_WRAPPER(DrawPolygon);
	DEF_NGE_WRAPPER(FillPolygon);
	DEF_NGE_WRAPPER(FillPolygonGrad);
}
