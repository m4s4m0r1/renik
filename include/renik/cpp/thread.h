#pragma once
#ifndef RENIK_THREAD_CPP_H
#define RENIK_THREAD_CPP_H
#include <renik\cpp\common.h>

namespace renik {
	namespace Thread {
		struct ThreadData : public BaseObject<uint, ThreadData>{
			uint thread_id;
		};

		class ThreadMgr final {

		};
	}
}

#endif // !RENIK_THREAD_CPP_H
