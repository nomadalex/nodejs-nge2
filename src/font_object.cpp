/**
 * @file  font_object.cpp
 * @author Kun Wang <ifreedom.cn@gmail.com>
 * @date 2012/03/09 15:34:55
 *
 *  Copyright  2012  Kun Wang <ifreedom.cn@gmail.com>
 *
 */
#include "common.h"
#include "font_object.hpp"

namespace wrapper {
	template<>
	Persistent<FunctionTemplate> HandleWrap<Font>::constructor_template;
}

