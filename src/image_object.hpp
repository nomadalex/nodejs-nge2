/**
 * @file  image_object.hpp
 * @author Kun Wang <ifreedom.cn@gmail.com>
 * @date 2012/03/02 13:47:26
 *
 *  Copyright  2012  Kun Wang <ifreedom.cn@gmail.com>
 *
 */

#ifndef _IMAGE_OBJECT_HPP
#define _IMAGE_OBJECT_HPP

namespace wrapper {
	class Image : public ObjectWrap {
	public:
		Image() : ObjectWrap() {
			img_ = NULL;
		}
		virtual ~Image() {
			if (img_)
				::image_free(img_);
		}

		static void Init(Handle<Object> target);
		static Handle<Value> NewInstance();

		inline static bool Check(Handle<Value> obj) {
			return constructor_name->Equals(obj->ToObject()->GetConstructorName());
		}

		void retain() {
			Ref();
		}
		void release() {
			Unref();
		}

		image_p img_;

	protected:
		static Handle<Value> New(const Arguments& args);

		static Persistent<Function> constructor;
		static Persistent<String> constructor_name;
	};
}

#endif /* _IMAGE_OBJECT_HPP */
