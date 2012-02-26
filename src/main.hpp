/**
 * @file  main.hpp
 * @author Kun Wang <ifreedom.cn@gmail.com>
 * @date 2012/02/12 05:22:21
 *
 *  Copyright  2012  Kun Wang <ifreedom.cn@gmail.com>
 *
 */

#ifndef _MAIN_HPP
#define _MAIN_HPP

#include <v8.h>
#include <node.h>
#include "libnge2.h"

using namespace node;
using namespace v8;

void InitForNgeMain(Handle<Object> target);

#endif /* _MAIN_HPP */
