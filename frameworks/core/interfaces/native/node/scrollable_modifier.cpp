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
#include "core/interfaces/native/node/scrollable_modifier.h"

#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"

namespace OHOS::Ace::NG {

void SetContentClip(ArkUINodeHandle node, ArkUI_Int32 mode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto val = static_cast<ContentClipMode>(mode);
    if (val < ContentClipMode::CONTENT_ONLY || val > ContentClipMode::SAFE_AREA) {
        val = ContentClipMode::DEFAULT;
    }
    ScrollableModelNG::SetContentClip(frameNode, static_cast<ContentClipMode>(mode), nullptr);
}

void ResetContentClip(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    ScrollableModelNG::SetContentClip(frameNode, ContentClipMode::DEFAULT, nullptr);
}

namespace NodeModifier {
const ArkUIScrollableModifier* GetScrollableModifier()
{
    static const ArkUIScrollableModifier modifier = { SetContentClip, ResetContentClip };
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
