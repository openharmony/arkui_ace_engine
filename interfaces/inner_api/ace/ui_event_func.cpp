/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "interfaces/inner_api/ace/ui_event_func.h"

#include "ace_forward_compatibility.h"
#include "ui_event_observer.h"

namespace OHOS::Ace {
constexpr char REGISTER_UI_EVENT_OBSERVER_FUNC[] = "OHOS_ACE_RegisterUIEventObserver";
constexpr char UNREGISTER_UI_EVENT_OBSERVER_FUNC[] = "OHOS_ACE_UnregisterUIEventObserver";
constexpr char GET_NODE_PROPERTY_FUNC[] = "OHOS_ACE_GetNodeProperty";
constexpr char GET_SIMPLIFIED_INSPECTOR_TREE_FUNC[] = "OHOS_ACE_GetSimplifiedInspectorTree";
constexpr char GET_SIMPLIFIED_INSPECTOR_TREE_ASYNC_FUNC[] = "OHOS_ACE_GetSimplifiedInspectorTreeAsync";
constexpr char EXECUTE_COMMAND_ASYNC_FUNC[] = "OHOS_ACE_ExecuteCommandAsync";

UIEventFunc::UIEventFunc()
{
    handle_ = LOADLIB(AceForwardCompatibility::GetAceLibName());
    if (handle_ == nullptr) {
        ResetFunc();
        return;
    }
    registerFunc_ = reinterpret_cast<RegisterUIEventObserverFunc>(LOADSYM(handle_, REGISTER_UI_EVENT_OBSERVER_FUNC));
    unregisterFunc_ =
        reinterpret_cast<UnregisterUIEventObserverFunc>(LOADSYM(handle_, UNREGISTER_UI_EVENT_OBSERVER_FUNC));
    getPropFunc_ = reinterpret_cast<GetNodePropertyFunc>(LOADSYM(handle_, GET_NODE_PROPERTY_FUNC));
    getTreeFunc_ =
        reinterpret_cast<GetSimplifiedInspectorTreeFunc>(LOADSYM(handle_, GET_SIMPLIFIED_INSPECTOR_TREE_FUNC));
    getTreeAsyncFunc_ = reinterpret_cast<GetSimplifiedInspectorTreeAsyncFunc>(
        LOADSYM(handle_, GET_SIMPLIFIED_INSPECTOR_TREE_ASYNC_FUNC));
    executeCommandAsyncFunc_ = reinterpret_cast<ExecuteCommandAsyncFunc>(LOADSYM(handle_, EXECUTE_COMMAND_ASYNC_FUNC));
    if (!IsAvailable()) {
        FREELIB(handle_);
        ResetFunc();
    }
}

UIEventFunc::~UIEventFunc()
{
    if (handle_) {
        FREELIB(handle_);
        ResetFunc();
    }
}

UIEventFunc& UIEventFunc::Get()
{
    static UIEventFunc func;
    return func;
}

bool UIEventFunc::IsAvailable() const
{
    return registerFunc_ != nullptr && unregisterFunc_ != nullptr && getPropFunc_ != nullptr &&
           getTreeFunc_ != nullptr && getTreeAsyncFunc_ != nullptr && executeCommandAsyncFunc_ != nullptr;
}

void UIEventFunc::ResetFunc()
{
    registerFunc_ = nullptr;
    unregisterFunc_ = nullptr;
    getPropFunc_ = nullptr;
    getTreeFunc_ = nullptr;
    getTreeAsyncFunc_ = nullptr;
    executeCommandAsyncFunc_ = nullptr;
    handle_ = nullptr;
}

void UIEventFunc::RegisterUIEventObserver(const std::string& config, const std::shared_ptr<UIEventObserver>& observer)
{
    if (UIEventFunc::Get().registerFunc_) {
        UIEventFunc::Get().registerFunc_(config, observer);
    }
}

void UIEventFunc::UnregisterUIEventObserver(const std::shared_ptr<UIEventObserver>& observer)
{
    if (UIEventFunc::Get().unregisterFunc_) {
        UIEventFunc::Get().unregisterFunc_(observer);
    }
}

void UIEventFunc::GetNodeProperty(
    const std::string& pageUrl, std::unordered_map<std::string, std::string>& nodeProperties)
{
    if (UIEventFunc::Get().getPropFunc_) {
        UIEventFunc::Get().getPropFunc_(pageUrl, nodeProperties);
    }
}

void UIEventFunc::GetSimplifiedInspectorTree(const TreeParams& params, std::string& tree)
{
    if (UIEventFunc::Get().getTreeFunc_) {
        UIEventFunc::Get().getTreeFunc_(params, tree);
    }
}

void UIEventFunc::GetSimplifiedInspectorTreeAsync(const TreeParams& params, OnInspectorTreeResult&& callback)
{
    if (UIEventFunc::Get().getTreeAsyncFunc_) {
        UIEventFunc::Get().getTreeAsyncFunc_(params, std::move(callback));
    }
}

void UIEventFunc::ExecuteCommandAsync(const UICommandParams& params, UICommandResult&& callback)
{
    if (UIEventFunc::Get().executeCommandAsyncFunc_) {
        UIEventFunc::Get().executeCommandAsyncFunc_(params, std::move(callback));
    }
}
} // namespace OHOS::Ace
