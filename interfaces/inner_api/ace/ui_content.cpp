/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "interfaces/inner_api/ace/ui_content.h"

#include "utils.h"
#include "ace_forward_compatibility.h"

#ifdef UICAST_COMPONENT_SUPPORTED
#include "interfaces/inner_api/ace/uicast/uicast_subscriber.h"
#endif

namespace OHOS::Ace {

using CreateCardFunc = UIContent* (*)(void*, void*, bool);
using CreateFunc = UIContent* (*)(void*, void*);
using CreateFunction = UIContent* (*)(void*);
using GetUIContentFunc = UIContent* (*)(int32_t);
using GetCurrentUIStackInfoFunction = char* (*)();
constexpr char UI_CONTENT_CREATE_FUNC[] = "OHOS_ACE_CreateUIContent";
constexpr char Card_CREATE_FUNC[] = "OHOS_ACE_CreateFormContent";
constexpr char SUB_WINDOW_UI_CONTENT_CREATE_FUNC[] = "OHOS_ACE_CreateSubWindowUIContent";
constexpr char GET_UI_CONTENT_CREATE_FUNC[] = "OHOS_ACE_GetUIContent";

OHOS::AbilityRuntime::Context* context_ = nullptr;

UIContent* CreateUIContent(void* context, void* runtime, bool isFormRender)
{
    LIBHANDLE handle = LOADLIB(AceForwardCompatibility::GetAceLibName());
    if (handle == nullptr) {
        return nullptr;
    }

    auto entry = reinterpret_cast<CreateCardFunc>(LOADSYM(handle, Card_CREATE_FUNC));
    if (entry == nullptr) {
        FREELIB(handle);
        return nullptr;
    }

    auto content = entry(context, runtime, isFormRender);
    return content;
}

UIContent* CreateUIContent(void* context, void* runtime)
{
    LIBHANDLE handle = LOADLIB(AceForwardCompatibility::GetAceLibName());
    if (handle == nullptr) {
        return nullptr;
    }

    auto entry = reinterpret_cast<CreateFunc>(LOADSYM(handle, UI_CONTENT_CREATE_FUNC));
    if (entry == nullptr) {
        FREELIB(handle);
        return nullptr;
    }

    auto content = entry(context, runtime);
#ifdef UICAST_COMPONENT_SUPPORTED
    UICastEventSubscribeProxy::GetInstance()->SubscribeStartEvent(content);
#endif

    return content;
}

UIContent* CreateUIContent(void* ability)
{
    LIBHANDLE handle = LOADLIB(AceForwardCompatibility::GetAceLibName());
    if (handle == nullptr) {
        return nullptr;
    }

    auto entry = reinterpret_cast<CreateFunction>(LOADSYM(handle, SUB_WINDOW_UI_CONTENT_CREATE_FUNC));
    if (entry == nullptr) {
        FREELIB(handle);
        return nullptr;
    }

    auto content = entry(ability);
#ifdef UICAST_COMPONENT_SUPPORTED
    UICastEventSubscribeProxy::GetInstance()->SubscribeStartEvent(content);
#endif

    return content;
}

std::unique_ptr<UIContent> UIContent::Create(OHOS::AbilityRuntime::Context* context, NativeEngine* runtime)
{
    std::unique_ptr<UIContent> content;
    content.reset(CreateUIContent(reinterpret_cast<void*>(context), reinterpret_cast<void*>(runtime)));
    return content;
}

std::unique_ptr<UIContent> UIContent::Create(
    OHOS::AbilityRuntime::Context* context, NativeEngine* runtime, bool isFormRender)
{
    std::unique_ptr<UIContent> content;
    content.reset(CreateUIContent(reinterpret_cast<void*>(context), reinterpret_cast<void*>(runtime), isFormRender));
    return content;
}

std::unique_ptr<UIContent> UIContent::Create(OHOS::AppExecFwk::Ability* ability)
{
    std::unique_ptr<UIContent> content;
    content.reset(CreateUIContent(reinterpret_cast<void*>(ability)));
    return content;
}

void UIContent::ShowDumpHelp(std::vector<std::string>& info)
{
    info.emplace_back(" -element                       |show element tree");
    info.emplace_back(" -render                        |show render tree");
    info.emplace_back(" -inspector                     |show inspector tree");
    info.emplace_back(" -frontend                      |show path and components count of current page");
    info.emplace_back(" -navigation                    |show navigation path stack");
}

UIContent* UIContent::GetUIContent(int32_t instanceId)
{
    LIBHANDLE handle = LOADLIB(AceForwardCompatibility::GetAceLibName());
    if (handle == nullptr) {
        return nullptr;
    }

    auto entry = reinterpret_cast<GetUIContentFunc>(LOADSYM(handle, GET_UI_CONTENT_CREATE_FUNC));
    if (entry == nullptr) {
        FREELIB(handle);
        return nullptr;
    }

    auto content = entry(instanceId);
    return content;
}

std::string UIContent::GetCurrentUIStackInfo()
{
    LIBHANDLE handle = LOADLIB(AceForwardCompatibility::GetAceLibName());
    if (handle == nullptr) {
        return std::string();
    }

    auto entry = reinterpret_cast<GetCurrentUIStackInfoFunction>(LOADSYM(handle, "OHOS_ACE_GetCurrentUIStackInfo"));
    if (entry == nullptr) {
        FREELIB(handle);
        return std::string();
    }

    auto content = entry();
    if (content == nullptr) {
        return std::string();
    }

    return content;
}
} // namespace OHOS::Ace
