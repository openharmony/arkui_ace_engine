//
// Created on 2025/8/15.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef SWIPEACTION_SWIPE_ACTION_TEST_H
#define SWIPEACTION_SWIPE_ACTION_TEST_H

#include <napi/native_api.h>
namespace ArkUICApiDemo {

class SwipeActionTest {
public:
    static napi_value CreateNativeNode(napi_env env, napi_callback_info info);
    static int32_t direction;
    static int32_t listIndex;
    static int32_t listGroupIndex;
};

} // namespace ArkUICApiDemo

#endif // SWIPEACTION_SWIPE_ACTION_TEST_H
