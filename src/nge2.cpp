/**
 * @file  nge2.cpp
 * @author Kun Wang <ifreedom.cn@gmail.com>
 * @date 2012/02/12 13:54:51
 *
 *  Copyright  2012  Kun Wang <ifreedom.cn@gmail.com>
 *
 */

#include <cstdio>
#include <v8.h>
#include <node.h>
#include "main.hpp"
#include "input.hpp"
#include "graphics.hpp"
#include "NgeApp.hpp"

using namespace node;
using namespace v8;

extern "C" {
	void init (Handle<Object> target) {
		HandleScope scope;

		NgeApp::Init(target);
		InitForNgeMain(target);
		InitForNgeInput(target);
		InitForNgeGraphics(target);
	}

	NODE_MODULE(nge2, init);
}
