/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "manager.h"
#include "napi/native_api.h"
#include "manager/plugin_manager.h"
#include "common.h"
#include "snap_speed/snap_speed_test.h"
#include "swipe_action/swipe_action_test.h"

#include <hilog/log.h>

namespace ScrollableNDK {
EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        // —— WaterFlow 示例 —— //
        {"CreateWaterFlowInfiniteScrollingEarly", nullptr, Manager::CreateWaterFlowInfiniteScrollingEarly, nullptr,
         nullptr, nullptr, napi_default, nullptr},

        // —— Grid 示例 —— //
        {"CreateScrollableGrid", nullptr, Manager::CreateScrollableGrid, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        { "gridTest", nullptr, GridTest::CreateNativeNode, nullptr, nullptr, nullptr,
            napi_default, nullptr },

        // —— List 示例 —— //
        {"CreateAlphabetIndexedList", nullptr, Manager::CreateAlphabetIndexedList, nullptr, nullptr, nullptr,
         napi_default, nullptr},
        {"createNormalTextListExample", nullptr, Manager::CreateNormalTextListExample, nullptr, nullptr, nullptr,
         napi_default, nullptr},
        {"createLazyTextListExample", nullptr, Manager::CreateLazyTextListExample, nullptr, nullptr, nullptr,
         napi_default, nullptr},
        {"createListItemGroupExample", nullptr, Manager::CreateListItemGroupExample, nullptr, nullptr, nullptr,
         napi_default, nullptr},
        {"destroyListExample", nullptr, Manager::DestroyListExample, nullptr, nullptr, nullptr, napi_default, nullptr},
        { "SwipeActionTest", nullptr, SwipeActionTest::CreateNativeNode, nullptr, nullptr,
            nullptr, napi_default, nullptr },
        { "SwipeActionTestWithDirection", nullptr, SwipeActionTest::CreateNativeNode, nullptr, nullptr,
            nullptr, napi_default, nullptr },
        { "SnapSpeedTest", nullptr, SnapSpeedTest::CreateNativeNode, nullptr, nullptr,
            nullptr, napi_default, nullptr },
        { "SnapSpeedTestNoLazyForeach", nullptr, SnapSpeedTest::CreateNativeNodeNoLazyForeach, nullptr, nullptr,
            nullptr, napi_default, nullptr },

        // —— Refresh 示例 —— //
        {"CreateRefreshList", nullptr, Manager::CreateRefreshList, nullptr, nullptr, nullptr, napi_default, nullptr},

        // —— Refresh 示例 —— //
        {"CreateScrollableInfiniteScroll", nullptr, Manager::CreateScrollableInfiniteScroll, nullptr, nullptr, nullptr,
         napi_default, nullptr},
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}
EXTERN_C_END

static napi_module entryModule = {.nm_version = 1,
                                  .nm_flags = 0,
                                  .nm_filename = nullptr,
                                  .nm_register_func = Init,
                                  .nm_modname = "entry",
                                  .nm_priv = ((void *)0),
                                  .reserved = {0}};

extern "C" __attribute__((constructor)) void RegisterModule(void)
{
    napi_module_register(&entryModule);
}
} // namespace ScrollableNDK
