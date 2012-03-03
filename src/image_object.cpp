/**
 * @file  image_object.cpp
 * @author Kun Wang <ifreedom.cn@gmail.com>
 * @date 2012/03/02 14:00:17
 *
 *  Copyright  2012  Kun Wang <ifreedom.cn@gmail.com>
 *
 */
#include "common.h"
#include "image_object.hpp"

namespace wrapper {
	Persistent<FunctionTemplate> Image::constructor_template;

	void Image::Init(Handle<Object> target) {
		Local<String> name = String::NewSymbol("ImageHandle");

		Local<FunctionTemplate> t = FunctionTemplate::New(Image::New);

		t->InstanceTemplate()->SetInternalFieldCount(1);
		t->SetClassName(name);

		target->Set(name, t->GetFunction());
		constructor_template = Persistent<FunctionTemplate>::New(t);
	}

	Handle<Value> Image::New(const Arguments& args) {
		HandleScope scope;

		Image* o = new Image();

		o->Wrap(args.This());
		return scope.Close(args.This());
	}

	void Image::updateProp() {
		if (img_) {
			OBJECT_SET_PROP(handle_, "isVaild", Boolean::New(true));
			COPY_PROP(handle_, UINT, img_, w);
			COPY_PROP(handle_, UINT, img_, h);
			COPY_PROP(handle_, UINT, img_, texw);
			COPY_PROP(handle_, UINT, img_, texh);
			COPY_PROP(handle_, UINT, img_, dtype);
			COPY_PROP(handle_, UINT, img_, texid);
			COPY_PROP(handle_, INT, img_, mask);
		}
		else {
			OBJECT_SET_PROP(handle_, "isVaild", Boolean::New(false));
		}
	}

	Handle<Value> Image::NewInstance() {
		HandleScope scope;

		Local<Object> obj = constructor_template->GetFunction()->NewInstance(0, NULL);

		return scope.Close(obj);
	}
}
