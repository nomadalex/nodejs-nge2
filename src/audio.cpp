/**
 * @file  audio.cpp
 * @author Kun Wang <ifreedom.cn@gmail.com>
 * @date 2012/03/03 03:01:55
 *
 *  Copyright  2012  Kun Wang <ifreedom.cn@gmail.com>
 *
 */
#include "common.h"
#include "audio.hpp"
#include "audio_object.hpp"

#define GET_THIS() GET_AUDIO_ARG(audio, 0)

#define THIS audio->audio_

#define RETURN_RET()							\
	return scope.Close(Integer::New(ret))

#define __VOID_METHOD_PRE()						\
	HandleScope scope;							\
												\
	CHECK_ARG_LEN(1);							\
												\
	CHECK_ARGS_TYPE(!CHECK_AUDIO_ARG(0));		\
												\
	GET_THIS()

#define __VOID_VOID_METHOD(method)				\
	__VOID_METHOD_PRE();						\
	THIS->method(THIS)

#define __INT_VOID_METHOD(method)				\
	__VOID_METHOD_PRE();						\
	int ret = THIS->method(THIS)

#define _MAKE_VOID_VOID_METHOD(method)			\
	__VOID_VOID_METHOD(method);					\
	return Undefined()

#define _MAKE_INT_VOID_METHOD(method)			\
	__INT_VOID_METHOD(method);					\
	RETURN_RET()

namespace wrapper {
	WRAPPER_FUNC(audioLoad) {
		HandleScope scope;

		CHECK_ARG_LEN(2);

		CHECK_ARGS_TYPE(!CHECK_AUDIO_ARG(0) ||
						!CHECK_STR_ARG(1));

		GET_THIS();
		GET_STR_ARG(filename, 1);

		int ret = THIS->load(THIS, *filename);
		RETURN_RET();
	}

	WRAPPER_FUNC(audioPlay) {
		HandleScope scope;

		CHECK_ARG_LEN(3);

		CHECK_ARGS_TYPE(!CHECK_AUDIO_ARG(0) ||
						!CHECK_INT_ARG(1) ||
						!CHECK_INT_ARG(2));

		GET_THIS();
		GET_INT_ARG(times, 1);
		GET_INT_ARG(free_when_stop, 2);

		int ret = THIS->play(THIS, times, free_when_stop);
		RETURN_RET();
	}

	WRAPPER_FUNC(audioPlaystop) {
		_MAKE_INT_VOID_METHOD(playstop);
	}

	WRAPPER_FUNC(audioPause) {
		_MAKE_VOID_VOID_METHOD(pause);
	}

	WRAPPER_FUNC(audioStop) {
		_MAKE_INT_VOID_METHOD(stop);
	}

	WRAPPER_FUNC(audioResume) {
		_MAKE_VOID_VOID_METHOD(resume);
	}

	WRAPPER_FUNC(audioVolume) {
		HandleScope scope;

		CHECK_ARG_LEN(2);

		CHECK_ARGS_TYPE(!CHECK_AUDIO_ARG(0) ||
						!CHECK_INT_ARG(1));

		GET_THIS();
		GET_INT_ARG(volume, 1);

		int ret = THIS->volume(THIS, volume);
		RETURN_RET();
	}

	WRAPPER_FUNC(audioRewind) {
		_MAKE_VOID_VOID_METHOD(rewind);
	}

	WRAPPER_FUNC(audioSeek) {
		HandleScope scope;

		CHECK_ARG_LEN(3);

		CHECK_ARGS_TYPE(!CHECK_AUDIO_ARG(0) ||
						!CHECK_INT_ARG(1) ||
						!CHECK_INT_ARG(2));

		GET_THIS();
		GET_INT_ARG(ms, 1);
		GET_INT_ARG(flag, 2);

		THIS->seek(THIS, ms, flag);
		return Undefined();
	}

	WRAPPER_FUNC(audioIsEof) {
		_MAKE_INT_VOID_METHOD(iseof);
	}

	WRAPPER_FUNC(audioIsPaused) {
		_MAKE_INT_VOID_METHOD(ispaused);
	}

	WRAPPER_FUNC(audioDestroy) {
		_MAKE_INT_VOID_METHOD(destroy);
	}

	WRAPPER_FUNC(CoolAudioDefaultInit) {
		HandleScope scope;

		::CoolAudioDefaultInit();

		return Undefined();
	}

	WRAPPER_FUNC(CoolAudioDefaultFini) {
		HandleScope scope;

		::CoolAudioDefaultFini();

		return Undefined();
	}

	WRAPPER_FUNC(CreateMp3Player) {
		HandleScope scope;

		CREATE_AUDIO(audio);
		audio->audio_ = ::CreateMp3Player();

		CHECK_AUDIO_AND_RETURN(audio);
	}

	WRAPPER_FUNC(CreateWavPlayer) {
		HandleScope scope;

		CREATE_AUDIO(audio);
		audio->audio_ = ::CreateWavPlayer();

		CHECK_AUDIO_AND_RETURN(audio);
	}

	WRAPPER_FUNC(CreateOggPlayer) {
		HandleScope scope;

		CREATE_AUDIO(audio);
		audio->audio_ = ::CreateOggPlayer();

		CHECK_AUDIO_AND_RETURN(audio);
	}
}

#define DEF_NGE_WRAPPER(sfunc)						\
	NODE_SET_METHOD(target, #sfunc, wrapper::sfunc)

void InitForNgeAudio(Handle<Object> target) {
	wrapper::Audio::Init(target);

	NODE_DEFINE_CONSTANT(target, AUDIO_SEEK_SET);
	NODE_DEFINE_CONSTANT(target, AUDIO_SEEK_CUR);
	NODE_DEFINE_CONSTANT(target, AUDIO_SEEK_END);

	DEF_NGE_WRAPPER(audioLoad);
	DEF_NGE_WRAPPER(audioPlay);
	DEF_NGE_WRAPPER(audioPlaystop);
	DEF_NGE_WRAPPER(audioPause);
	DEF_NGE_WRAPPER(audioStop);
	DEF_NGE_WRAPPER(audioResume);
	DEF_NGE_WRAPPER(audioVolume);
	DEF_NGE_WRAPPER(audioRewind);
	DEF_NGE_WRAPPER(audioSeek);
	DEF_NGE_WRAPPER(audioIsEof);
	DEF_NGE_WRAPPER(audioIsPaused);
	DEF_NGE_WRAPPER(audioDestroy);

	DEF_NGE_WRAPPER(CoolAudioDefaultInit);
	DEF_NGE_WRAPPER(CoolAudioDefaultFini);
	DEF_NGE_WRAPPER(CreateMp3Player);
	DEF_NGE_WRAPPER(CreateWavPlayer);
	DEF_NGE_WRAPPER(CreateOggPlayer);
}

