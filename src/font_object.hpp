/**
 * @file  font_object.hpp
 * @author Kun Wang <ifreedom.cn@gmail.com>
 * @date 2012/03/09 15:28:42
 *
 *  Copyright  2012  Kun Wang <ifreedom.cn@gmail.com>
 *
 */

#ifndef _FONT_OBJECT_HPP
#define _FONT_OBJECT_HPP

namespace wrapper {
	class Font : public HandleWrap<Font> {
	public:
		Font() : HandleWrap<Font>() {
			data = NULL;
			V8::AdjustAmountOfExternalAllocatedMemory(sizeof(Font));
		}
		virtual ~Font() {
			if (data)
				font_destory(data);
			V8::AdjustAmountOfExternalAllocatedMemory(-(int)sizeof(Font));
		}

		inline static void Init(Handle<Object> target) {
			HandleWrap<Font>::Init("FontHandle", target);
		}

		PFont data;
	};
}

#define CHECK_FONT_ARG(pos)						\
	CHECK_WRAPPED_OBJ_ARG(Font, pos)

#define GET_FONT_ARG(var, pos)					\
	GET_WRAPPED_OBJ_ARG(Font, var, pos)

#define CREATE_FONT(var)										\
	Local<Object> var##__ = Font::NewInstance()->ToObject();	\
	UNWRAP_OBJ(Font, var, var##__)

#define CHECK_FONT_AND_RETURN(var)				\
	if (var->data)								\
		return scope.Close(var##__);			\
	else										\
		return Undefined()

#endif /* _FONT_OBJECT_HPP */
