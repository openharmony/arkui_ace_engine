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

#include "core/components_ng/render/render_wrapper.h"

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
void RenderWrapper::FlushRender()
{
    auto renderContext = renderContext_.Upgrade();
    if (!renderContext) {
        LOGE("render context is nullptr");
        return;
    }
    renderContext->StartRecording();

    // first paint background.

    // then paint content.
    const auto& content = geometryNode_->GetContent();
    if (content && contentPaintImpl_) {
        auto offset = content->GetRect().GetOffset();
        contentPaintImpl_(RawPtr(renderContext), offset);
    }

    // at last paint border, mask, overlay and so on

    renderContext->StopRecordingIfNeeded();
    renderContext->RequestNextFrame();
}
} // namespace OHOS::Ace::NG
