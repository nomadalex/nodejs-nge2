/**
 * @file  image.cpp
 * @author Kun Wang <ifreedom.cn@gmail.com>
 * @date 2012/03/01 11:23:53
 *
 *  Copyright  2012  Kun Wang <ifreedom.cn@gmail.com>
 *
 */
#include "common.h"
#include "image.hpp"
#include "image_object.hpp"
#include <node_buffer.h>

namespace wrapper {
	WRAPPER_FUNC(image_create) {
		HandleScope scope;

		CHECK_ARG_LEN(3);

		CHECK_ARGS_TYPE(!CHECK_INT_ARG(0) ||
						!CHECK_INT_ARG(1) ||
						!CHECK_INT_ARG(2));

		GET_INT_ARG(w, 0);
		GET_INT_ARG(h, 1);
		GET_INT_ARG(dtype, 2);

		CREATE_IMG(img);

		ExternalMemoryAutoUpdate<Image> update(img);
		img->img_ = ::image_create(w, h, dtype);

		CHECK_IMG_AND_RETURN(img);
	}

	WRAPPER_FUNC(image_create_ex) {
		HandleScope scope;

		CHECK_ARG_LEN(4);

		CHECK_ARGS_TYPE(!CHECK_INT_ARG(0) ||
						!CHECK_INT_ARG(1) ||
						!CHECK_COLOR_ARG(2));

		GET_INT_ARG(w, 0);
		GET_INT_ARG(h, 1);
		GET_COLOR_ARG(2);

		CREATE_IMG(img);

		ExternalMemoryAutoUpdate<Image> update(img);
		img->img_ = ::image_create_ex(w, h, color, dtype);

		CHECK_IMG_AND_RETURN(img);
	}

	WRAPPER_FUNC(image_load) {
		HandleScope scope;

		CHECK_ARG_LEN(3);

		CHECK_ARGS_TYPE(!CHECK_STR_ARG(0) ||
						!CHECK_INT_ARG(1) ||
						!CHECK_INT_ARG(2));

		GET_STR_ARG(filename, 0);
		GET_INT_ARG(dtype, 1);
		GET_INT_ARG(swizzle, 2);

		CREATE_IMG(img);

		ExternalMemoryAutoUpdate<Image> update(img);
		img->img_ = ::image_load(*filename, dtype, swizzle);

		CHECK_IMG_AND_RETURN(img);
	}

	WRAPPER_FUNC(image_load_colorkey) {
		HandleScope scope;

		CHECK_ARG_LEN(4);

		CHECK_ARGS_TYPE(!CHECK_STR_ARG(0) ||
						!CHECK_INT_ARG(1) ||
						!CHECK_INT_ARG(2) ||
						!CHECK_INT_ARG(3));

		GET_STR_ARG(filename, 0);
		GET_INT_ARG(dtype, 1);
		GET_INT_ARG(colorkey, 2);
		GET_INT_ARG(swizzle, 3);

		CREATE_IMG(img);

		ExternalMemoryAutoUpdate<Image> update(img);
		img->img_ = ::image_load_colorkey(*filename, dtype, colorkey, swizzle);

		CHECK_IMG_AND_RETURN(img);
	}

	WRAPPER_FUNC(image_save) {
		HandleScope scope;

		CHECK_ARG_LEN(4);

		CHECK_ARGS_TYPE(!CHECK_IMG_ARG(0) ||
						!CHECK_STR_ARG(1) ||
						!CHECK_UINT_ARG(2) ||
						!CHECK_UINT_ARG(3));

		GET_IMG_ARG(img, 0);
		GET_STR_ARG(filename, 1);
		GET_UINT_ARG(alpha, 2);
		GET_UINT_ARG(rle, 3);

		int ret = ::image_save(img->img_, *filename, (uint8)alpha, (uint8)rle);

		return scope.Close(Integer::New(ret));
	}

	WRAPPER_FUNC(image_free) {
		HandleScope scope;

		CHECK_ARG_LEN(1);

		CHECK_ARGS_TYPE(!CHECK_IMG_ARG(0));

		GET_IMG_ARG(img, 0);

		ExternalMemoryAutoUpdate<Image> update(img);
		::image_free(img->img_);
		img->img_ = NULL;

		return Undefined();
	}

	WRAPPER_FUNC(image_clone) {
		HandleScope scope;

		CHECK_ARG_LEN(1);

		CHECK_ARGS_TYPE(!CHECK_IMG_ARG(0));

		GET_WRAPPED_OBJ_ARG(Image, img2, 0);

		CREATE_IMG(img);

		ExternalMemoryAutoUpdate<Image> update(img);
		img->img_ = ::image_clone(img2->img_);

		CHECK_IMG_AND_RETURN(img);
	}

	WRAPPER_FUNC(image_clear) {
		HandleScope scope;

		CHECK_ARG_LEN(1);

		CHECK_ARGS_TYPE(!CHECK_IMG_ARG(0));

		GET_IMG_ARG(img, 0);

		::image_clear(img->img_);

		return Undefined();
	}

	WRAPPER_FUNC(image_to_image) {
		HandleScope scope;

		CHECK_ARG_LEN(4);

		CHECK_ARGS_TYPE(!CHECK_IMG_ARG(0) ||
						!CHECK_IMG_ARG(1) ||
						!CHECK_UINT_ARG(2) ||
						!CHECK_UINT_ARG(3));

		GET_IMG_ARG(src, 0);
		GET_IMG_ARG(dst, 1);
		GET_UINT_ARG(dx, 2);
		GET_UINT_ARG(dy, 3);

		::image_to_image(src->img_, dst->img_, dx, dy);

		return Undefined();
	}

	WRAPPER_FUNC(image_to_image_ex) {
		HandleScope scope;

		CHECK_ARG_LEN(8);

		CHECK_ARGS_TYPE(!CHECK_IMG_ARG(0) ||
						!CHECK_IMG_ARG(1) ||
						!CHECK_UINT_ARG(2) ||
						!CHECK_UINT_ARG(3) ||
						!CHECK_UINT_ARG(4) ||
						!CHECK_UINT_ARG(5) ||
						!CHECK_UINT_ARG(6) ||
						!CHECK_UINT_ARG(7));

		GET_IMG_ARG(src, 0);
		GET_IMG_ARG(dst, 1);
		GET_UINT_ARG(sx, 2);
		GET_UINT_ARG(sy, 3);
		GET_UINT_ARG(sw, 4);
		GET_UINT_ARG(sh, 5);
		GET_UINT_ARG(dx, 6);
		GET_UINT_ARG(dy, 7);

		::image_to_image_ex(src->img_, dst->img_, sx, sy, sw, sh, dx, dy);

		return Undefined();
	}

	WRAPPER_FUNC(image_to_image_alpha) {
		HandleScope scope;

		CHECK_ARG_LEN(5);

		CHECK_ARGS_TYPE(!CHECK_IMG_ARG(0) ||
						!CHECK_IMG_ARG(1) ||
						!CHECK_UINT_ARG(2) ||
						!CHECK_UINT_ARG(3) ||
						!CHECK_INT_ARG(4));

		GET_IMG_ARG(src, 0);
		GET_IMG_ARG(dst, 1);
		GET_UINT_ARG(dx, 2);
		GET_UINT_ARG(dy, 3);
		GET_INT_ARG(alpha, 4);

		::image_to_image_alpha(src->img_, dst->img_, dx, dy, alpha);

		return Undefined();
	}

	WRAPPER_FUNC(image_to_image_alpha_ex) {
		HandleScope scope;

		CHECK_ARG_LEN(9);

		CHECK_ARGS_TYPE(!CHECK_IMG_ARG(0) ||
						!CHECK_IMG_ARG(1) ||
						!CHECK_UINT_ARG(2) ||
						!CHECK_UINT_ARG(3) ||
						!CHECK_UINT_ARG(4) ||
						!CHECK_UINT_ARG(5) ||
						!CHECK_UINT_ARG(6) ||
						!CHECK_UINT_ARG(7) ||
						!CHECK_INT_ARG(8));

		GET_IMG_ARG(src, 0);
		GET_IMG_ARG(dst, 1);
		GET_UINT_ARG(sx, 2);
		GET_UINT_ARG(sy, 3);
		GET_UINT_ARG(sw, 4);
		GET_UINT_ARG(sh, 5);
		GET_UINT_ARG(dx, 6);
		GET_UINT_ARG(dy, 7);
		GET_INT_ARG(alpha, 4);

		::image_to_image_alpha_ex(src->img_, dst->img_, sx, sy, sw, sh, dx, dy, alpha);

		return Undefined();
	}

	WRAPPER_FUNC(rawdata_to_image) {
		HandleScope scope;

		CHECK_ARG_LEN(6);

		CHECK_ARGS_TYPE(!CHECK_WRAPPED_OBJ_ARG(Buffer, 0) ||
						!CHECK_IMG_ARG(1) ||
						!CHECK_UINT_ARG(2) ||
						!CHECK_UINT_ARG(3) ||
						!CHECK_UINT_ARG(4) ||
						!CHECK_UINT_ARG(5));

		GET_WRAPPED_OBJ_ARG(Buffer, buf, 0);
		GET_IMG_ARG(img, 1);
		GET_UINT_ARG(x, 2);
		GET_UINT_ARG(y, 3);
		GET_UINT_ARG(w, 4);
		GET_UINT_ARG(h, 5);

		::rawdata_to_image(Buffer::Data(buf), img->img_, x, y, w, h);

		return Undefined();
	}

	WRAPPER_FUNC(image_fliph) {
		HandleScope scope;

		CHECK_ARG_LEN(1);

		CHECK_ARGS_TYPE(!CHECK_IMG_ARG(0));

		GET_IMG_ARG(img, 0);

		int ret = ::image_fliph(img->img_);

		return scope.Close(Integer::New(ret));
	}

	WRAPPER_FUNC(image_flipv) {
		HandleScope scope;

		CHECK_ARG_LEN(1);

		CHECK_ARGS_TYPE(!CHECK_IMG_ARG(0));

		GET_IMG_ARG(img, 0);

		int ret = ::image_flipv(img->img_);

		return scope.Close(Integer::New(ret));
	}
}

#define DEF_NGE_WRAPPER(sfunc)						\
	NODE_SET_METHOD(target, #sfunc, wrapper::sfunc)

void InitForNgeImage(Handle<Object> target) {
	wrapper::Image::Init(target);
	DEF_NGE_WRAPPER(image_create);
	DEF_NGE_WRAPPER(image_create_ex);
	DEF_NGE_WRAPPER(image_load);
	DEF_NGE_WRAPPER(image_load_colorkey);
	DEF_NGE_WRAPPER(image_save);
	DEF_NGE_WRAPPER(image_free);
	DEF_NGE_WRAPPER(image_clone);
	DEF_NGE_WRAPPER(image_clear);
	DEF_NGE_WRAPPER(image_to_image);
	DEF_NGE_WRAPPER(image_to_image_ex);
	DEF_NGE_WRAPPER(image_to_image_alpha);
	DEF_NGE_WRAPPER(image_to_image_alpha_ex);
	DEF_NGE_WRAPPER(rawdata_to_image);
	DEF_NGE_WRAPPER(image_fliph);
	DEF_NGE_WRAPPER(image_flipv);
}
