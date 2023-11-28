/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_panel_modifier.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/panel/sliding_panel_model_ng.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
void SetShowCloseIcon(NodeHandle node, bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetShowCloseIcon(frameNode, value);
}

void ResetShowCloseIcon(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetShowCloseIcon(frameNode, false);
}

void SetDragBar(NodeHandle node, bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetHasDragBar(frameNode, value);
}

void ResetDragBar(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetHasDragBar(frameNode, true);
}

void SetShow(NodeHandle node, bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetIsShow(frameNode, value);
}

void ResetShow(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetIsShow(frameNode, true);
}

ArkUIPanelModifierAPI GetPanelModifier()
{
    static const ArkUIPanelModifierAPI modifier = { SetShowCloseIcon, ResetShowCloseIcon, SetDragBar, ResetDragBar,
        SetShow, ResetShow };

    return modifier;
}
} // namespace OHOS::Ace::NG
