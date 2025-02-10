/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/node_content_modifier.h"

#include "base/error/error_code.h"
#include "core/components_ng/syntax/node_content.h"

namespace OHOS::Ace::NG {
namespace {

ArkUI_Int32 AddChild(ArkUINodeContentHandle content, ArkUINodeHandle child)
{
    CHECK_NULL_RETURN(content, ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(child, ERROR_CODE_PARAM_INVALID);
    auto* nodeContent = reinterpret_cast<NodeContent*>(content);
    auto* uiNode = reinterpret_cast<UINode*>(child);
    nodeContent->AddNode(uiNode);
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 InsertChild(ArkUINodeContentHandle content, ArkUINodeHandle child, ArkUI_Int32 position)
{
    CHECK_NULL_RETURN(content, ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(child, ERROR_CODE_PARAM_INVALID);
    auto* nodeContent = reinterpret_cast<NodeContent*>(content);
    auto* uiNode = reinterpret_cast<UINode*>(child);
    nodeContent->AddNode(uiNode, position);
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 RemoveChild(ArkUINodeContentHandle content, ArkUINodeHandle child)
{
    CHECK_NULL_RETURN(content, ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(child, ERROR_CODE_PARAM_INVALID);
    auto* nodeContent = reinterpret_cast<NodeContent*>(content);
    auto* uiNode = reinterpret_cast<UINode*>(child);
    nodeContent->RemoveNode(uiNode);
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 RegisterEvent(
    ArkUINodeContentHandle content, void* userData, void (*receiver)(ArkUINodeContentEvent* event))
{
    CHECK_NULL_RETURN(content, ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(receiver, ERROR_CODE_PARAM_INVALID);
    auto onAttach = [receiver, userData, content]() {
        ArkUINodeContentEvent event { 0, userData, content };
        receiver(&event);
    };
    auto onDetach = [receiver, userData, content]() {
        ArkUINodeContentEvent event { 1, userData, content };
        receiver(&event);
    };
    auto* nodeContent = reinterpret_cast<NodeContent*>(content);
    nodeContent->SetAttachToMainTreeCallback(std::move(onAttach));
    nodeContent->SetDetachFromMainTreeCallback(std::move(onDetach));
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetUserData(ArkUINodeContentHandle content, void* userData)
{
    CHECK_NULL_RETURN(content, ERROR_CODE_PARAM_INVALID);
    auto* nodeContent = reinterpret_cast<NodeContent*>(content);
    nodeContent->SetUserData(userData);
    return ERROR_CODE_NO_ERROR;
}

void* GetUserData(ArkUINodeContentHandle content)
{
    CHECK_NULL_RETURN(content, nullptr);
    auto* nodeContent = reinterpret_cast<NodeContent*>(content);
    return nodeContent->GetUserData();
}
} // namespace

namespace NodeModifier {
const ArkUINodeContentModifier* GetNodeContentModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUINodeContentModifier modifier = {
        .addChild = AddChild,
        .insertChild = InsertChild,
        .removeChild = RemoveChild,
        .registerEvent = RegisterEvent,
        .setUserData = SetUserData,
        .getUserData = GetUserData,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUINodeContentModifier* GetCJUINodeContentModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUINodeContentModifier modifier = {
        .addChild = AddChild,
        .insertChild = InsertChild,
        .removeChild = RemoveChild,
        .registerEvent = RegisterEvent,
        .setUserData = SetUserData,
        .getUserData = GetUserData,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
