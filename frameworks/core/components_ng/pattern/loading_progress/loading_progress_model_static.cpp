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

#include "core/components_ng/pattern/loading_progress/loading_progress_model_static.h"

#include "core/components_ng/pattern/loading_progress/loading_progress_pattern.h"

namespace OHOS::Ace::NG {
void LoadingProgressModelStatic::SetColor(FrameNode* frameNode, const std::optional<Color>& valueOpt)
{
    if (valueOpt) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(LoadingProgressPaintProperty, Color, valueOpt.value(), frameNode);
        ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, valueOpt.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(LoadingProgressPaintProperty, Color, frameNode);
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColor, frameNode);
    }
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, true, frameNode);
}
} // namespace OHOS::Ace::NG
