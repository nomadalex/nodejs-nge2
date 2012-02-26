/**
 * @file  input.hpp
 * @author Kun Wang <ifreedom.cn@gmail.com>
 * @date 2012/02/12 10:31:57
 *
 *  Copyright  2012  Kun Wang <ifreedom.cn@gmail.com>
 *
 */

#ifndef _INPUT_HPP
#define _INPUT_HPP

#include <v8.h>
#include <node.h>
#include "libnge2.h"

using namespace node;
using namespace v8;

void InitForNgeInput(Handle<Object> target);

#endif /* _INPUT_HPP */
