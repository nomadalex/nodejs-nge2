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
#include "image_async.hpp"
#include "graphics.hpp"
#include "NgeApp.hpp"
#include "audio.hpp"
#include "audio_async.hpp"
#include "font.hpp"
#include "font_async.hpp"

extern "C" {
	void init (Handle<Object> target) {
		HandleScope scope;

		wrapper::NgeApp::Init(target);
		InitForNgeMain(target);
		InitForNgeInput(target);
		InitForNgeImage(target);
		InitForNgeImageAsync(target);
		InitForNgeGraphics(target);
		InitForNgeAudio(target);
		InitForNgeAudioAsync(target);
		InitForNgeFont(target);
		InitForNgeFontAsync(target);
	}

	NODE_MODULE(node_nge2, init);
}
