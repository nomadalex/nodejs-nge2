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

namespace wrapper {
	WRAPPER_FUNC(image_create_ex) {
		HandleScope scope;

		CHECK_ARG_LEN(4);

		CHECK_ARGS_TYPE(!CHECK_INT_ARG(0) ||
						!CHECK_INT_ARG(1) ||
						!CHECK_COLOR_ARG(2));

		GET_INT_ARG(w, 0);
		GET_INT_ARG(h, 1);
		GET_COLOR_ARG(2);

		Local<Object> obj = Image::NewInstance()->ToObject();

		Image* o = Image::Unwrap<Image>(obj);
		o->img_ = ::image_create_ex(w, h, color, dtype);

		if (o->img_)
			return scope.Close(obj);
		else
			return Undefined();
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

		Local<Object> obj = Image::NewInstance()->ToObject();

		Image* o = Image::Unwrap<Image>(obj);
		o->img_ = ::image_load(*filename, dtype, swizzle);

		if (o->img_)
			return scope.Close(obj);
		else
			return Undefined();
	}
}

#define DEF_NGE_WRAPPER(sfunc)						\
	NODE_SET_METHOD(target, #sfunc, wrapper::sfunc)

void InitForNgeImage(Handle<Object> target) {
	wrapper::Image::Init(target);
	DEF_NGE_WRAPPER(image_create_ex);
	DEF_NGE_WRAPPER(image_load);
}
