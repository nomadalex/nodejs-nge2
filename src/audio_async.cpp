/**
 * @file  audio_async.cpp
 * @author Kun Wang <ifreedom.cn@gmail.com>
 * @date 2012/03/13 11:11:21
 *
 *  Copyright  2012  Kun Wang <ifreedom.cn@gmail.com>
 *
 */

#include "common.h"
#include "async_common.h"
#include "audio_async.hpp"
#include "audio_object.hpp"

#define GET_AUDIO_ASYNC_DATA(var)					\
	GET_ASYNC_DATA(wrapper::AudioAsyncData, var)

#define DEF_AUDIO_ARG_DATA(n) DEF_ARG_DATA(Audio, n)

#define CREATE_AUDIO_ARG_DATA(n, var)			\
	CREATE_ARG_DATA(Audio, n, var)

#define GET_AUDIO_ARG_DATA(n, var, async_data)	\
	GET_ARG_DATA(Audio, n, var, async_data)

namespace wrapper {
	struct AudioAsyncData {
		uv_work_t request;
		Audio* audio;
		void* arg;
		Persistent<Function> callback;
	};

	DEF_AUDIO_ARG_DATA(1) {
		char* filename;
		int ret;
	};

#define THIS data->audio->audio_

	namespace async {
		ASYNC_FUNC(audioLoad) {
			GET_AUDIO_ASYNC_DATA(data);
			GET_AUDIO_ARG_DATA(1, args, data);

			args->ret = THIS->load(THIS, args->filename);
			delete args->filename;
		}
		ASYNC_FUNC(audioLoadAfter) {
			HandleScope scope;
			GET_AUDIO_ASYNC_DATA(data);
			GET_AUDIO_ARG_DATA(1, args, data);

			const unsigned argc = 2;
			Local<Value> argv[argc] = {
				Local<Value>::New(Null()),
				Integer::New(args->ret)
			};

			delete args;
			data->audio->release();

			DO_ASYNC_CALLBACK(data, argc, argv);
			delete data;
		}
	}

	WRAPPER_FUNC(audioLoadAsync) {
		HandleScope scope;

		CHECK_ARG_LEN(3);

		CHECK_ARGS_TYPE(!CHECK_AUDIO_ARG(0) ||
						!CHECK_STR_ARG(1) ||
						!CHECK_FUNC_ARG(2));

		AudioAsyncData* data = new AudioAsyncData;

		CREATE_AUDIO_ARG_DATA(1, arg);
		GET_AUDIO_ARG(audio, 0);
		GET_ASYNC_STR_ARG(arg, filename, 1);
		GET_ASYNC_CALLBACK_ARG(data, 2);

		audio->retain();
		data->audio = audio;

		SET_ARG_DATA(data, arg);
		SET_REQUEST_DATA(data);
		PUT_UV_QUEUE(data, audioLoad);

		return Undefined();
	}
}

#define DEF_NGE_WRAPPER(sfunc)						\
	NODE_SET_METHOD(target, #sfunc, wrapper::sfunc)

void InitForNgeAudioAsync(Handle<Object> target) {
	DEF_NGE_WRAPPER(audioLoadAsync);
}
