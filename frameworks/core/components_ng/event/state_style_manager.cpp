/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/event/state_style_manager.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/touch_event.h"
#include "core/components_ng/pattern/custom/custom_node_base.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

StateStyleManager::StateStyleManager(WeakPtr<FrameNode> frameNode) : host_(std::move(frameNode)) {}

StateStyleManager::~StateStyleManager() = default;

const RefPtr<TouchEventImpl>& StateStyleManager::GetPressedListener()
{
    if (pressedFunc_) {
        return pressedFunc_;
    }
    auto pressedCallback = [weak = WeakClaim(this)](TouchEventInfo& info) {
        auto stateStyleMgr = weak.Upgrade();
        CHECK_NULL_VOID(stateStyleMgr);
        const auto& touches = info.GetTouches();
        if (touches.empty()) {
            LOGW("the touch info is illegal");
            return;
        }
        const auto& type = touches.front().GetTouchType();
        if (type == TouchType::DOWN) {
            stateStyleMgr->UpdateCurrentUIState(UI_STATE_PRESSED);
            return;
        }
        if ((type == TouchType::UP) || (type == TouchType::CANCEL)) {
            stateStyleMgr->ResetCurrentUIState(UI_STATE_PRESSED);
        }
    };
    pressedFunc_ = MakeRefPtr<TouchEventImpl>(std::move(pressedCallback));
    return pressedFunc_;
}

void StateStyleManager::FireStateFunc()
{
    auto node = host_.Upgrade();
    CHECK_NULL_VOID(node);
    auto nodeId = node->GetId();
    RefPtr<CustomNodeBase> customNode;
    if (AceType::InstanceOf<CustomNodeBase>(node)) {
        customNode = DynamicCast<CustomNodeBase>(node);
    }
    if (!customNode) {
        auto parent = node->GetParent();
        while (parent) {
            if (AceType::InstanceOf<CustomNodeBase>(parent)) {
                customNode = DynamicCast<CustomNodeBase>(parent);
                break;
            }
            parent = parent->GetParent();
        }
    }
    if (!customNode) {
        LOGE("fail to find custom node to fire update func of %{public}d", nodeId);
        return;
    }
    ScopedViewStackProcessor processor;
    customNode->FireNodeUpdateFunc(nodeId);
}

} // namespace OHOS::Ace::NG