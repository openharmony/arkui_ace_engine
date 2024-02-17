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

#include "core/interfaces/native/node/hyperlink_modifier.h"
#include "core/components/hyperlink/hyperlink_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/hyperlink/hyperlink_model_ng.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components/theme/theme_manager.h"

namespace OHOS::Ace::NG {
void SetHyperlinkColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    HyperlinkModelNG::SetColor(frameNode, Color(color));
}

void ResetHyperlinkColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto hyperlinkTheme = themeManager->GetTheme<HyperlinkTheme>();
    CHECK_NULL_VOID(hyperlinkTheme);

    HyperlinkModelNG::SetColor(frameNode, Color(hyperlinkTheme->GetTextColor()));
}

void SetHyperlinkDraggable(ArkUINodeHandle node, ArkUI_Bool draggable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    HyperlinkModelNG::SetDraggable(frameNode, draggable);
}

void ResetHyperlinkDraggable(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    HyperlinkModelNG::SetDraggable(frameNode, false);
}

namespace NodeModifier {
const ArkUIHyperlinkModifier* GetHyperlinkModifier()
{
    static const ArkUIHyperlinkModifier modifier = { SetHyperlinkColor, ResetHyperlinkColor, SetHyperlinkDraggable,
        ResetHyperlinkDraggable };

    return &modifier;
}
}
} // namespace OHOS::Ace::NG