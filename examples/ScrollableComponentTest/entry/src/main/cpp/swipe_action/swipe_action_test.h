/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Description: List支持展开指定ListItem的swipeAction
 * Writer: renxiaowen
 */

#ifndef SWIPEACTION_TEST_H
#define SWIPEACTION_TEST_H

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
