/**
 * @file  image.hpp
 * @author Kun Wang <ifreedom.cn@gmail.com>
 * @date 2012/03/01 15:08:39
 *
 *  Copyright  2012  Kun Wang <ifreedom.cn@gmail.com>
 *
 */

#ifndef _IMAGE_HPP
#define _IMAGE_HPP

#include <v8.h>
#include <node.h>
#include "libnge2.h"

using namespace node;
using namespace v8;

namespace wrapper {
	class Image : public ObjectWrap {
	public:
		Image() : ObjectWrap() {
			img_ = NULL;
		}
		virtual ~Image();

		static void Init(Handle<Object> target);

		static Handle<Value> NewInstance();

	protected:
		static Handle<Value> New(const Arguments& args);
		static Handle<Value> CreateEx(const Arguments& args);
		static Handle<Value> Load(const Arguments& args);
		static Handle<Value> DrawImage(const Arguments& args);

		image_p img_;

		static Persistent<Function> constructor;
	};
}

#endif /* _IMAGE_HPP */
