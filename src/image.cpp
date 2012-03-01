/**
 * @file  image.cpp
 * @author Kun Wang <ifreedom.cn@gmail.com>
 * @date 2012/03/01 11:23:53
 *
 *  Copyright  2012  Kun Wang <ifreedom.cn@gmail.com>
 *
 */
#include "image.hpp"
#include "common.h"

namespace wrapper {
	WRAPPER_FUNC(Image::DrawImage) {
		HandleScope scope;

		CHECK_ARG_LEN(8);

		CHECK_ARGS_TYPE(!CHECK_RECT_ARG(0) ||
						!CHECK_RECT_ARG(4));

		GET_RECT_ARG(src, 0);
		GET_RECT_ARG(dst, 4);

		Image* o = Unwrap<Image>(args.This());
		::DrawImage(o->img_, src.x, src.y, src.w, src.h, dst.x, dst.y, dst.w, dst.h);

		return Undefined();
	}

	Persistent<Function> Image::constructor;

	Image::~Image() {
		::image_free(img_);
	}

	void Image::Init(Handle<Object> target) {
		Local<String> name = String::NewSymbol("Image");

		Local<FunctionTemplate> t = FunctionTemplate::New(Image::New);

		t->InstanceTemplate()->SetInternalFieldCount(1);
		t->SetClassName(name);

		NODE_SET_METHOD(t, "createEx", CreateEx);
		NODE_SET_METHOD(t, "load", Load);
		NODE_SET_PROTOTYPE_METHOD(t, "draw", DrawImage);

		target->Set(name, t->GetFunction());

		constructor = Persistent<Function>::New(t->GetFunction());
	}

	Handle<Value> Image::New(const Arguments& args) {
		HandleScope scope;

		if (!args.IsConstructCall()) {
			return ThrowException(Exception::TypeError(
									  String::New("Use the new operator to create instances of this object."))
				);
		}

		Image* o = new Image();

		o->Wrap(args.This());
		return scope.Close(args.This());
	}

	Handle<Value> Image::NewInstance() {
		HandleScope scope;

		Local<Object> obj = constructor->NewInstance(0, NULL);

		return scope.Close(obj);
	}

	Handle<Value> Image::CreateEx(const Arguments& args) {
		HandleScope scope;

		CHECK_ARG_LEN(4);

		CHECK_ARGS_TYPE(!CHECK_INT_ARG(0) ||
						!CHECK_INT_ARG(1) ||
						!CHECK_COLOR_ARG(2));

		GET_INT_ARG(w, 0);
		GET_INT_ARG(h, 1);
		GET_COLOR_ARG(2);

		Local<Object> obj = NewInstance()->ToObject();

		Image* o = Unwrap<Image>(obj);
		o->img_ = ::image_create_ex(w, h, color, dtype);

		if (o->img_)
			return scope.Close(obj);
		else
			return Undefined();
	}

	Handle<Value> Image::Load(const Arguments& args) {
		HandleScope scope;

		CHECK_ARG_LEN(3);

		CHECK_ARGS_TYPE(!CHECK_STR_ARG(0) ||
						!CHECK_INT_ARG(1) ||
						!CHECK_INT_ARG(2));

		GET_STR_ARG(filename, 0);
		GET_INT_ARG(dtype, 1);
		GET_INT_ARG(swizzle, 2);

		Local<Object> obj = NewInstance()->ToObject();

		Image* o = Unwrap<Image>(obj);
		o->img_ = ::image_load(*filename, dtype, swizzle);

		if (o->img_)
			return scope.Close(obj);
		else
			return Undefined();
	}
}
