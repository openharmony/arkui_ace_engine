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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_xcomponent_modifier.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model_ng.h"
#include "core/pipeline/base/element_register.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::NG {

void SetXComponentBackgroundColor(NodeHandle node, uint32_t color)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (!XComponentModelNG::IsTexture(frameNode)) {
        return;
    }
    ViewAbstract::SetBackgroundColor(frameNode, Color(color));
}

void ResetXComponentBackgroundColor(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (!XComponentModelNG::IsTexture(frameNode)) {
        return;
    }
    ViewAbstract::SetBackgroundColor(frameNode, Color(Color::TRANSPARENT));
}

void SetXComponentOpacity(NodeHandle node, double opacity)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (!XComponentModelNG::IsTexture(frameNode)) {
        return;
    }
    if ((LessNotEqual(opacity, 0.0)) || opacity > 1) {
        opacity = 1.0f;
    }
    ViewAbstract::SetOpacity(frameNode, opacity);
}

void ResetXComponentOpacity(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (!XComponentModelNG::IsTexture(frameNode)) {
        return;
    }
    ViewAbstract::SetOpacity(frameNode, 1.0f);
}

ArkUIXComponentModifierAPI GetXComponentModifier()
{
    static const ArkUIXComponentModifierAPI modifier = { SetXComponentBackgroundColor, ResetXComponentBackgroundColor,
        SetXComponentOpacity, ResetXComponentOpacity };

    return modifier;
}
} // namespace OHOS::Ace::NG