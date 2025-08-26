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

#include "NativeEntry.h"
#include "ListItemGroupExample.h"
#include "NormalTextListExample.h"
#include "LazyTextListExample.h"
#include <arkui/native_node_napi.h>
#include <js_native_api.h>

namespace NativeModule {

enum PageID {
    NORMAL_TEXT_LIST_EXAMPLE = 0,
    LAZY_TEXT_LIST_EXAMPLE = 1,
    LIST_ITEM_GROUP_EXAMPLE = 2,
};

napi_value CreateNativeRoot(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[2] = {nullptr};

    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    // 获取NodeContent
    ArkUI_NodeContentHandle contentHandle;
    OH_ArkUI_GetNodeContentFromNapiValue(env, args[0], &contentHandle);
    NativeEntry::GetInstance()->SetContentHandle(contentHandle);
    
    int32_t pageId = 0;
    if (argc > 1) {
        napi_get_value_int32(env, args[1], &pageId);
    }
    // 创建文本列表
    std::shared_ptr<ArkUIBaseNode> root;
    switch (pageId) {
        case NORMAL_TEXT_LIST_EXAMPLE:
            root = CreateTextListExample();
            break;
        case LAZY_TEXT_LIST_EXAMPLE:
            root = CreateLazyTextListExample();
            break;
        case LIST_ITEM_GROUP_EXAMPLE:
            root = CreateListItemGroupExample();
            break;
        default:
            root = CreateTextListExample();
            break;
    }

    // 保持Native侧对象到管理类中，维护生命周期。
    NativeEntry::GetInstance()->SetRootNode(root);
    return nullptr;
}

napi_value DestroyNativeRoot(napi_env env, napi_callback_info info)
{
    // 从管理类中释放Native侧对象。
    NativeEntry::GetInstance()->DisposeRootNode();
    return nullptr;
}

} // namespace NativeModule