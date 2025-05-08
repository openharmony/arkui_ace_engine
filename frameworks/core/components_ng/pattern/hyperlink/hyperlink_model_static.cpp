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

#include "core/components/hyperlink/hyperlink_theme.h"
#include "core/components_ng/pattern/hyperlink/hyperlink_model_static.h"
#include "core/components_ng/pattern/hyperlink/hyperlink_model_ng.h"
#include "core/components_ng/pattern/hyperlink/hyperlink_pattern.h"

namespace OHOS::Ace::NG {

void HyperlinkModelStatic::SetColor(FrameNode* frameNode, const std::optional<Color>& value)
{
    if (value.has_value()) {
        HyperlinkModelNG::SetColor(frameNode, value.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(HyperlinkLayoutProperty, TextColor, frameNode);
        ACE_RESET_NODE_LAYOUT_PROPERTY(HyperlinkLayoutProperty, Color, frameNode);
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColor, frameNode);
    }
}

} // namespace OHOS::Ace::NG
