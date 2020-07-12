#pragma once
#ifndef RENIK_H
#define RENIK_H

#if defined(RENIK_STATIC)
	#include <renik\cpp\common.h>
	#include <renik\cpp\entity.h>
	#include <renik\cpp\graphic.h>
	#include <renik\cpp\thread.h>
	#include <renik\cpp\window.h>
#else
	#include <renik\renik_common.h>
	#include <renik\renik_entity.h>
	#include <renik\renik_graphic.h>
	#include <renik\renik_thread.h>
#endif

#endif