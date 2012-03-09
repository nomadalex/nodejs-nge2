/**
 * @file  font.cpp
 * @author Kun Wang <ifreedom.cn@gmail.com>
 * @date 2012/03/09 15:27:32
 *
 *  Copyright  2012  Kun Wang <ifreedom.cn@gmail.com>
 *
 */
#include "common.h"
#include "font.hpp"
#include "font_object.hpp"
#include "image_object.hpp"
#include <node_buffer.h>

namespace wrapper {
	WRAPPER_FUNC(SetFontEncoding) {
		HandleScope scope;

		CHECK_ARG_LEN(1);

		CHECK_ARGS_TYPE(!CHECK_INT_ARG(0));

		GET_INT_ARG(encoding, 0);
		::NGE_SetFontEncoding(encoding);

		return Undefined();
	}

	WRAPPER_FUNC(create_font_hzk) {
		HandleScope scope;

		CHECK_ARG_LEN(4);

		CHECK_ARGS_TYPE(!CHECK_STR_ARG(0) ||
						!CHECK_STR_ARG(1) ||
						!CHECK_INT_ARG(2) ||
						!CHECK_INT_ARG(3));

		GET_STR_ARG(cname, 0);
		GET_STR_ARG(aname, 1);
		GET_INT_ARG(height, 2);
		GET_INT_ARG(disp, 3);

		CREATE_FONT(pf);

		pf->data = ::create_font_hzk(*cname, *aname, height, disp);

		CHECK_FONT_AND_RETURN(pf);
	}

	WRAPPER_FUNC(create_font_hzk_buf) {
		HandleScope scope;

		CHECK_ARG_LEN(4);

		CHECK_ARGS_TYPE(!CHECK_WRAPPED_OBJ_ARG(Buffer, 0) ||
						!CHECK_WRAPPED_OBJ_ARG(Buffer, 1) ||
						!CHECK_INT_ARG(2) ||
						!CHECK_INT_ARG(3));

		GET_WRAPPED_OBJ_ARG(Buffer, cbuf, 0);
		GET_WRAPPED_OBJ_ARG(Buffer, abuf, 1);
		GET_INT_ARG(height, 2);
		GET_INT_ARG(disp, 3);

		CREATE_FONT(pf);

		pf->data = ::create_font_hzk_buf(Buffer::Data(cbuf), Buffer::Length(cbuf),
										 Buffer::Data(abuf), Buffer::Length(abuf),
										 height, disp);

		CHECK_FONT_AND_RETURN(pf);
	}

	WRAPPER_FUNC(create_font_freetype) {
		HandleScope scope;

		CHECK_ARG_LEN(3);

		CHECK_ARGS_TYPE(!CHECK_STR_ARG(0) ||
						!CHECK_INT_ARG(1) ||
						!CHECK_INT_ARG(2));

		GET_STR_ARG(name, 0);
		GET_INT_ARG(height, 1);
		GET_INT_ARG(disp, 2);

		CREATE_FONT(pf);

		pf->data = ::create_font_freetype(*name, height, disp);

		CHECK_FONT_AND_RETURN(pf);
	}

	WRAPPER_FUNC(create_font_freetype_buf) {
		HandleScope scope;

		CHECK_ARG_LEN(3);

		CHECK_ARGS_TYPE(!CHECK_WRAPPED_OBJ_ARG(Buffer, 0) ||
						!CHECK_INT_ARG(1) ||
						!CHECK_INT_ARG(2));

		GET_WRAPPED_OBJ_ARG(Buffer, buf, 0);
		GET_INT_ARG(height, 1);
		GET_INT_ARG(disp, 2);

		CREATE_FONT(pf);

		pf->data = ::create_font_freetype_buf(Buffer::Data(buf), Buffer::Length(buf),
											  height, disp);

		CHECK_FONT_AND_RETURN(pf);
	}

	WRAPPER_FUNC(create_font_nfont) {
		HandleScope scope;

		CHECK_ARG_LEN(2);

		CHECK_ARGS_TYPE(!CHECK_STR_ARG(0) ||
						!CHECK_INT_ARG(1));

		GET_STR_ARG(name, 0);
		GET_INT_ARG(disp, 1);

		CREATE_FONT(pf);

		pf->data = ::create_font_nfont(*name, disp);

		CHECK_FONT_AND_RETURN(pf);
	}

	WRAPPER_FUNC(create_font_nfont_buf) {
		HandleScope scope;

		CHECK_ARG_LEN(2);

		CHECK_ARGS_TYPE(!CHECK_WRAPPED_OBJ_ARG(Buffer, 0) ||
						!CHECK_INT_ARG(1));

		GET_WRAPPED_OBJ_ARG(Buffer, buf, 0);
		GET_INT_ARG(disp, 1);

		CREATE_FONT(pf);

		pf->data = ::create_font_nfont_buf(Buffer::Data(buf), Buffer::Length(buf),
										   disp);

		CHECK_FONT_AND_RETURN(pf);
	}

	WRAPPER_FUNC(font_drawtext) {
		HandleScope scope;

		CHECK_ARG_LEN(6);

		CHECK_ARGS_TYPE(!CHECK_FONT_ARG(0) ||
						!CHECK_STR_ARG(1) ||
						!CHECK_IMG_ARG(2) ||
						!CHECK_INT_ARG(3) ||
						!CHECK_INT_ARG(4) ||
						!CHECK_INT_ARG(5));

		GET_FONT_ARG(pf, 0);
		GET_U8STR_ARG(text, 1);
		GET_IMG_ARG(img, 2);
		GET_INT_ARG(dx, 3);
		GET_INT_ARG(dy, 4);
		GET_INT_ARG(flags, 5);

		::font_drawtext(pf->data, *text, text.length(), img->img_, dx, dy, flags);

		return Undefined();
	}

	WRAPPER_FUNC(font_setattr) {
		HandleScope scope;

		CHECK_ARG_LEN(3);

		CHECK_ARGS_TYPE(!CHECK_FONT_ARG(0) ||
						!CHECK_INT_ARG(1) ||
						!CHECK_INT_ARG(2));

		GET_FONT_ARG(pf, 0);
		GET_INT_ARG(attr, 1);
		GET_INT_ARG(setflag, 2);

		::font_setattr(pf->data, attr, setflag);

		return Undefined();
	}

	WRAPPER_FUNC(font_destory) {
		HandleScope scope;

		CHECK_ARG_LEN(1);

		CHECK_ARGS_TYPE(!CHECK_FONT_ARG(0));

		GET_FONT_ARG(pf, 0);

		::font_destory(pf->data);

		return Undefined();
	}

	WRAPPER_FUNC(font_setcolor) {
		HandleScope scope;

		CHECK_ARG_LEN(2);

		CHECK_ARGS_TYPE(!CHECK_FONT_ARG(0) ||
						!CHECK_UINT_ARG(1));

		GET_FONT_ARG(pf, 0);
		GET_UINT_ARG(color, 1);

		int last = ::font_setcolor(pf->data, color);

		return scope.Close(Integer::New(last));
	}

	WRAPPER_FUNC(font_setcolor_ex) {
		HandleScope scope;

		CHECK_ARG_LEN(4);

		CHECK_ARGS_TYPE(!CHECK_FONT_ARG(0) ||
						!CHECK_UINT_ARG(1) ||
						!CHECK_UINT_ARG(2) ||
						!CHECK_UINT_ARG(3));

		GET_FONT_ARG(pf, 0);
		GET_UINT_ARG(color_fg, 1);
		GET_UINT_ARG(color_bg, 2);
		GET_UINT_ARG(color_sh, 3);

		::font_setcolor_ex(pf->data, color_fg, color_bg, color_sh);

		return Undefined();
	}

	WRAPPER_FUNC(font_textsize) {
		HandleScope scope;

		CHECK_ARG_LEN(2);

		CHECK_ARGS_TYPE(!CHECK_FONT_ARG(0) ||
						!CHECK_STR_ARG(1));

		GET_FONT_ARG(pf, 0);
		GET_U8STR_ARG(text, 1);

		int width, height, base;
		::font_textsize(pf->data, *text, text.length(), &width, &height, &base);

		Local<Object> obj = Object::New();
		OBJECT_SET_INT_PROP(obj, "width", width);
		OBJECT_SET_INT_PROP(obj, "height", height);
		OBJECT_SET_INT_PROP(obj, "base", base);

		return scope.Close(obj);
	}
}

#define DEF_NGE_WRAPPER(sfunc)						\
	NODE_SET_METHOD(target, #sfunc, wrapper::sfunc)

void InitForNgeFont(Handle<Object> target) {
	NODE_DEFINE_CONSTANT(target, NGE_ENCODING_GBK);
	NODE_DEFINE_CONSTANT(target, NGE_ENCODING_UTF_8);

	NODE_DEFINE_CONSTANT(target, FONT_SHOW_NORMAL);
	NODE_DEFINE_CONSTANT(target, FONT_SHOW_SHADOW);

	NODE_DEFINE_CONSTANT(target, SET_ATTR_FIXWIDTH);
	NODE_DEFINE_CONSTANT(target, SET_ATTR_BOLD);
	NODE_DEFINE_CONSTANT(target, SET_ATTR_MARGIN);
	NODE_DEFINE_CONSTANT(target, SET_ATTR_SIZE);

	wrapper::Font::Init(target);
	DEF_NGE_WRAPPER(SetFontEncoding);
	DEF_NGE_WRAPPER(create_font_hzk);
	DEF_NGE_WRAPPER(create_font_hzk_buf);
	DEF_NGE_WRAPPER(create_font_freetype);
	DEF_NGE_WRAPPER(create_font_freetype_buf);
	DEF_NGE_WRAPPER(create_font_nfont);
	DEF_NGE_WRAPPER(create_font_nfont_buf);
	DEF_NGE_WRAPPER(font_drawtext);
	DEF_NGE_WRAPPER(font_setattr);
	DEF_NGE_WRAPPER(font_destory);
	DEF_NGE_WRAPPER(font_setcolor);
	DEF_NGE_WRAPPER(font_setcolor_ex);
	DEF_NGE_WRAPPER(font_textsize);
}
