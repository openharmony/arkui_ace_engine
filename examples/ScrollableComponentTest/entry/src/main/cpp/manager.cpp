/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License")
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

#include "components/grid/Grid.h"
#include "components/list/List.h"
#include "components/refresh/Refresh.h"
#include "components/scroll/Scroll.h"
#include "components/waterflow/WaterFlow.h"

#include "components/list/examples/NormalTextListExample.h"
#include "components/list/examples/LazyTextListExample.h"
#include "components/list/examples/ListItemGroupExample.h"

#include "napi/native_api.h"
#include <arkui/native_interface.h>
#include <arkui/native_node.h>
#include <arkui/native_node_napi.h>
#include <arkui/native_type.h>
#include <hilog/log.h>

namespace ConstIde {
constexpr uint32_t NUMBER_0 = 0;
constexpr uint32_t NUMBER_1 = 1;
constexpr const char *K_LOG_DOMAIN = "Manager";
} // namespace ConstIde

Manager Manager::manager_;
ArkUI_NativeNodeAPI_1 *Manager::nodeAPI_ = reinterpret_cast<ArkUI_NativeNodeAPI_1 *>(
    OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));

std::unordered_map<ArkUI_NodeContentHandle, std::shared_ptr<BaseNode>> Manager::examples_;

// ---------- 通用小工具 ----------
static napi_value NapiUndefined(napi_env env)
{
    napi_value v{};
    (void)napi_get_undefined(env, &v);
    return v;
}

// 读取 NodeContent（要求 args[0] 为 NodeContent）
static bool GetNodeContentFromArgs(napi_env env, napi_callback_info info, ArkUI_NodeContentHandle &outContent)
{
    size_t argc = ConstIde::NUMBER_1;
    napi_value args[ConstIde::NUMBER_1] = {nullptr};
    if (napi_get_cb_info(env, info, &argc, args, nullptr, nullptr) != napi_ok || argc < ConstIde::NUMBER_1) {
        return false;
    }
    OH_ArkUI_GetNodeContentFromNapiValue(env, args[ConstIde::NUMBER_0], &outContent);
    return outContent != nullptr;
}

// ---------- 移除已挂载的示例 ----------
void Manager::RemoveExistingIfAny(ArkUI_NodeContentHandle content)
{
    auto it = examples_.find(content);
    if (it == examples_.end()) {
        return;
    }
    if (it->second && it->second->GetHandle()) {
        OH_ArkUI_NodeContent_RemoveNode(content, it->second->GetHandle());
    }
    it->second.reset();
    examples_.erase(it);
}

template <class MakeNodeFn>
static napi_value CreateNativeNode(napi_env env, napi_callback_info info, const char *who, MakeNodeFn makeNodeFn)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, ConstIde::K_LOG_DOMAIN, "%{public}s BEGIN", who);

    ArkUI_NodeContentHandle content = nullptr;
    if (!GetNodeContentFromArgs(env, info, content)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, ConstIde::K_LOG_DOMAIN, "%{public}s invalid args/content",
                     who);
        return NapiUndefined(env);
    }

    ArkUI_NodeHandle page = makeNodeFn();
    if (page == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, ConstIde::K_LOG_DOMAIN,
                     "%{public}s makeNodeFn returned null", who);
        return NapiUndefined(env);
    }

    OH_ArkUI_NodeContent_AddNode(content, page);
    return NapiUndefined(env);
}

napi_value Manager::CreateWaterFlowInfiniteScrollingEarly(napi_env env, napi_callback_info info)
{
    return CreateNativeNode(env, info, "CreateWaterFlowInfiniteScrollingEarly",
                            []() -> ArkUI_NodeHandle { return WaterFlow::CreateWaterFlowInfiniteScrollingEarly(); });
}

napi_value Manager::CreateScrollableGrid(napi_env env, napi_callback_info info)
{
    return CreateNativeNode(env, info, "CreateScrollableGrid",
                            []() -> ArkUI_NodeHandle { return Grid::CreateScrollableGrid(); });
}

napi_value Manager::CreateAlphabetIndexedList(napi_env env, napi_callback_info info)
{
    return CreateNativeNode(env, info, "CreateAlphabetIndexedList",
                            []() -> ArkUI_NodeHandle { return List::CreateAlphabetIndexedList(); });
}

napi_value Manager::CreateRefreshList(napi_env env, napi_callback_info info)
{
    return CreateNativeNode(env, info, "CreateRefreshList",
                            []() -> ArkUI_NodeHandle { return Refresh::CreateRefreshList(); });
}

napi_value Manager::CreateScrollableInfiniteScroll(napi_env env, napi_callback_info info)
{
    return CreateNativeNode(env, info, "CreateScrollableInfiniteScroll",
                            []() -> ArkUI_NodeHandle { return Scroll::CreateScrollableInfiniteScroll(); });
}

napi_value Manager::CreateNormalTextListExample(napi_env env, napi_callback_info info)
{
    ArkUI_NodeContentHandle content = nullptr;
    if (!GetNodeContentFromArgs(env, info, content)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, ConstIde::K_LOG_DOMAIN,
                     "CreateNormalTextListExample invalid args/content");
        return NapiUndefined(env);
    }

    RemoveExistingIfAny(content);

    auto root = ::CreateTextListExample(); // 返回 std::shared_ptr<BaseNode>
    if (!root || !root->GetHandle()) {
        return NapiUndefined(env);
    }

    OH_ArkUI_NodeContent_AddNode(content, root->GetHandle());
    examples_[content] = root;
    return NapiUndefined(env);
}

napi_value Manager::CreateLazyTextListExample(napi_env env, napi_callback_info info)
{
    ArkUI_NodeContentHandle content = nullptr;
    if (!GetNodeContentFromArgs(env, info, content)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, ConstIde::K_LOG_DOMAIN,
                     "CreateLazyTextListExample invalid args/content");
        return NapiUndefined(env);
    }

    RemoveExistingIfAny(content);

    auto root = ::CreateLazyTextListExample();
    if (!root || !root->GetHandle()) {
        return NapiUndefined(env);
    }

    OH_ArkUI_NodeContent_AddNode(content, root->GetHandle());
    examples_[content] = root;
    return NapiUndefined(env);
}

napi_value Manager::CreateListItemGroupExample(napi_env env, napi_callback_info info)
{
    ArkUI_NodeContentHandle content = nullptr;
    if (!GetNodeContentFromArgs(env, info, content)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, ConstIde::K_LOG_DOMAIN,
                     "CreateListItemGroupExample invalid args/content");
        return NapiUndefined(env);
    }

    RemoveExistingIfAny(content);

    auto root = ::CreateListItemGroupExample();
    if (!root || !root->GetHandle()) {
        return NapiUndefined(env);
    }

    OH_ArkUI_NodeContent_AddNode(content, root->GetHandle());
    examples_[content] = root;
    return NapiUndefined(env);
}

napi_value Manager::DestroyListExample(napi_env env, napi_callback_info info)
{
    ArkUI_NodeContentHandle content = nullptr;
    if (!GetNodeContentFromArgs(env, info, content)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, ConstIde::K_LOG_DOMAIN,
                     "DestroyListExample invalid args/content");
        return NapiUndefined(env);
    }

    RemoveExistingIfAny(content);
    return NapiUndefined(env);
}
