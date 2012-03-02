/**
 * @file  nge2.cpp
 * @author Kun Wang <ifreedom.cn@gmail.com>
 * @date 2012/02/12 13:54:51
 *
 *  Copyright  2012  Kun Wang <ifreedom.cn@gmail.com>
 *
 */

#include "common.h"
#include "main.hpp"
#include "input.hpp"
#include "image.hpp"
#include "graphics.hpp"
#include "NgeApp.hpp"

extern "C" {
	void init (Handle<Object> target) {
		HandleScope scope;

		wrapper::NgeApp::Init(target);
		InitForNgeMain(target);
		InitForNgeInput(target);
		InitForNgeImage(target);
		InitForNgeGraphics(target);
	}

	NODE_MODULE(node_nge2, init);
}
