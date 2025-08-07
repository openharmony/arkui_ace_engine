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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_COMPONENTS_CUSTOM_NODE_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_COMPONENTS_CUSTOM_NODE_H

#include "ui/base/macros.h"
#include "ui/view/frame_node.h"
#include "ui/view/view.h"

namespace OHOS::Ace::Kit {

class FrameNode;

class ACE_FORCE_EXPORT CustomNode : public View {
public:
    static RefPtr<CustomNode> Create(const std::string& tag);
    static RefPtr<CustomNode> GetOrCreateFrameNode(const std::string& tag);
    ~CustomNode() override;
    CustomNode(const RefPtr<FrameNode> aceNode);

    static void SetOnWindowFocusedCallback(const NodeHandle node, void (*onWindowFocused)(NodeHandle node));
    static void SetOnWindowUnfocusedCallback(const NodeHandle node, void (*onWindowUnfocused)(NodeHandle node));
    static void SetOnWindowActivatedCallback(const NodeHandle node, void (*onWindowActivated)(NodeHandle node));
    static void SetOnWindowDeactivatedCallback(const NodeHandle node, void (*onWindowDeactivated)(NodeHandle node));
    static void SetOnAttachToMainTreeCallback(const NodeHandle node, void (*onAttachToMainTree)(NodeHandle node));
    static void SetOnDetachFromMainTreeCallback(const NodeHandle node, void (*onDetachFromMainTree)(NodeHandle node));
    static void SetOnAvoidInfoChangeCallback(const NodeHandle node, void (*onAvoidInfoChange)(NodeHandle node));
    static void SetIsNeedRegisterAvoidInfoChangeListener(const NodeHandle node, bool isRegister);
};

} // namespace OHOS::Ace::Kit
#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_COMPONENTS_CUSTOM_NODE_H
