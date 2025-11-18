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
  * Description: List组件支持基于断点配置lanes
  * Writer: renxiaowen
  */

#ifndef CAPIDEMO_LIST_TEST_H
#define CAPIDEMO_LIST_TEST_H

#include <ace/xcomponent/native_interface_xcomponent.h>
#include <arkui/native_dialog.h>
#include <arkui/native_interface.h>
#include <arkui/native_node.h>
#include <arkui/native_type.h>

#include "common.h"

namespace ArkUICApiDemo {

class ListTest {
public:
    ~ListTest();
    static napi_value CreateNativeNode(napi_env env, napi_callback_info info);
};
} // namespace ArkUICApiDemo

#endif // CAPIDEMO_LIST_TEST_H
