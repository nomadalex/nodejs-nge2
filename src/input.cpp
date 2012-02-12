/**
 * @file  input.cpp
 * @author Kun Wang <ifreedom.cn@gmail.com>
 * @date 2012/02/12 10:32:22
 *
 *  Copyright  2012  Kun Wang <ifreedom.cn@gmail.com>
 *
 */
#include "input.hpp"
#include "common.h"
#include "libnge2.h"

namespace wrapper {

	Persistent<Function> keyDownCb, keyUpCb;

#define DO_KEY_FUNC(proc)										\
	if (CHECK_PFUNCTION(proc)) {								\
		Local<Value> argv[1] = { Integer::New(key) };			\
		proc->Call(Context::GetCurrent()->Global(), 1, argv); \
	}

	void KeyDown(int key) {
		DO_KEY_FUNC(keyDownCb);
	}
	void KeyUp(int key) {
		DO_KEY_FUNC(keyUpCb);
	}

	WRAPPER_FUNC(InitInput) {
		HandleScope scope;

		CHECK_ARG_LEN(3);

		CHECK_AND_DISPOSE(keyDownCb);
		CHECK_AND_DISPOSE(keyUpCb);

		if (CHECK_ARG_TYPE(0, Function))
			keyDownCb = CAST_TO_PFUNCTION(args[0]);
		if (CHECK_ARG_TYPE(1, Function))
			keyUpCb = CAST_TO_PFUNCTION(args[1]);

		int32_t doneflag;
		if (CHECK_ARG_TYPE(2, Int32))
			doneflag = args[2]->Int32Value();
		else
			doneflag = 0;

		::InitInput(KeyDown, KeyUp, doneflag);

		return Undefined();
	}

	Persistent<Function> mouseButtonCb, mouseMoveCb;

	void MouseButton(int type, int x, int y) {
		if (CHECK_PFUNCTION(mouseButtonCb)) {
			Local<Value> argv[3] = { Integer::New(type),
									 Integer::New(x),
									 Integer::New(y) };
			mouseButtonCb->Call(Context::GetCurrent()->Global(), 3, argv);
		}
	}

	void MouseMove(int x, int y) {
		if (CHECK_PFUNCTION(mouseMoveCb)) {
			Local<Value> argv[2] = { Integer::New(x),
									 Integer::New(y) };
			mouseMoveCb->Call(Context::GetCurrent()->Global(), 2, argv);
		}
	}

	WRAPPER_FUNC(InitMouse) {
		HandleScope scope;

		CHECK_ARG_LEN(2);

		CHECK_AND_DISPOSE(mouseButtonCb);
		CHECK_AND_DISPOSE(mouseMoveCb);

		if (CHECK_ARG_TYPE(0, Function))
			mouseButtonCb = CAST_TO_PFUNCTION(args[0]);
		if (CHECK_ARG_TYPE(1, Function))
			mouseMoveCb = CAST_TO_PFUNCTION(args[1]);

		::InitMouse(MouseButton, MouseMove);

		return Undefined();
	}

#ifdef NGE_INPUT_HAS_PROC
	WRAPPER_FUNC(InputProc) {
		HandleScope scope;

		::InputProc();

		return Undefined();
	}
#endif

	// WRAPPER_FUNC(FiniInput) {
	// 	HandleScope scope;

	// 	::FiniInput();

	// 	return Undefined();
	// }
}

#define DEF_NGE_WRAPPER(sfunc)						\
	NODE_SET_METHOD(target, #sfunc, wrapper::sfunc)

void InitForNgeInput(Handle<Object> target) {

#define DEF_BUTTON_CONSTANT(name)						\
	NODE_DEFINE_CONSTANT(target, PSP_BUTTON_##name);

#ifdef NGE_INPUT_BUTTON_SUPPORT
	DEF_BUTTON_CONSTANT(UP);
	DEF_BUTTON_CONSTANT(DOWN);
	DEF_BUTTON_CONSTANT(LEFT);
	DEF_BUTTON_CONSTANT(RIGHT);
	DEF_BUTTON_CONSTANT(TRIANGLE);
	DEF_BUTTON_CONSTANT(CIRCLE);
	DEF_BUTTON_CONSTANT(CROSS);
	DEF_BUTTON_CONSTANT(SQUARE);
	DEF_BUTTON_CONSTANT(LEFT_TRIGGER);
	DEF_BUTTON_CONSTANT(RIGHT_TRIGGER);
	DEF_BUTTON_CONSTANT(SELECT);
	DEF_BUTTON_CONSTANT(HOME);
	DEF_BUTTON_CONSTANT(HOLD);
#endif

#ifdef NGE_INPUT_MOUSE_SUPPORT
	NODE_DEFINE_CONSTANT(target, MOUSE_LBUTTON_DOWN);
	NODE_DEFINE_CONSTANT(target, MOUSE_LBUTTON_UP);
#endif
#ifdef NGE_INPUT_MOUSE_FULL_SUPPORT
	NODE_DEFINE_CONSTANT(target, MOUSE_RBUTTON_DOWN);
	NODE_DEFINE_CONSTANT(target, MOUSE_RBUTTON_UP);
	NODE_DEFINE_CONSTANT(target, MOUSE_MBUTTON_DOWN);
	NODE_DEFINE_CONSTANT(target, MOUSE_MBUTTON_UP);
#endif


#ifdef NGE_INPUT_BUTTON_SUPPORT
	DEF_NGE_WRAPPER(InitInput);
#endif
#ifdef NGE_INPUT_MOUSE_SUPPORT
	DEF_NGE_WRAPPER(InitMouse);
#endif
#ifdef NGE_INPUT_HAS_PROC
	DEF_NGE_WRAPPER(InputProc);
#endif
	// DEF_NGE_WRAPPER(FiniInput);
}
