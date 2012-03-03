/**
 * @file  audio_object.hpp
 * @author Kun Wang <ifreedom.cn@gmail.com>
 * @date 2012/03/03 03:16:56
 *
 *  Copyright  2012  Kun Wang <ifreedom.cn@gmail.com>
 *
 */

#ifndef _AUDIO_OBJECT_HPP
#define _AUDIO_OBJECT_HPP

namespace wrapper {
	class Audio : public HandleWrap<Audio>
	{
	public:
		Audio() : HandleWrap<Audio>() {
			audio_ = NULL;
			V8::AdjustAmountOfExternalAllocatedMemory(sizeof(Audio));
		}
		virtual ~Audio() {
			if (audio_) {
				audio_->destroy(audio_);
			}
			V8::AdjustAmountOfExternalAllocatedMemory(-(int)sizeof(Audio));
		}

		inline static void Init(Handle<Object> target) {
			HandleWrap<Audio>::Init("AudioHandle", target);
		}

		audio_play_p audio_;
	};
}

#define CHECK_AUDIO_ARG(pos)						\
	CHECK_WRAPPED_OBJ_ARG(Audio, pos)

#define GET_AUDIO_ARG(var, pos)					\
	GET_WRAPPED_OBJ_ARG(Audio, var, pos)

#define CREATE_AUDIO(var)											\
	Local<Object> var##__ = Audio::NewInstance()->ToObject();	\
	UNWRAP_OBJ(Audio, var, var##__)

#define CHECK_AUDIO_AND_RETURN(var)				\
	if (var->audio_)								\
		return scope.Close(var##__);			\
	else										\
		return Undefined()

#endif /* _AUDIO_OBJECT_HPP */
