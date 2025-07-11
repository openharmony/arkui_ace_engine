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

#include "core/components_ng/pattern/grid_row/grid_row_layout_pattern.h"

namespace OHOS::Ace::NG {

void GridRowLayoutPattern::OnAttachToFrameNodeMultiThread()
{
    // nothing, thread unsafe
}

void GridRowLayoutPattern::OnDetachFromFrameNodeMultiThread(FrameNode* frameNode)
{
    // nothing, thread unsafe
}

void GridRowLayoutPattern::OnAttachToMainTreeMultiThread()
{
    Pattern::OnAttachToFrameNode();
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    if (pipeline && !callbackId_.has_value()) {
        callbackId_ = pipeline->RegisterSurfaceChangedCallback(
            [weak = WeakClaim(this)](
                int32_t width, int32_t height, int32_t oldWidth, int32_t oldHeight, WindowSizeChangeReason type) {
                auto gridRow = weak.Upgrade();
                if (gridRow) {
                    gridRow->MarkDirty();
                }
            });
    }
}

void GridRowLayoutPattern::OnDetachFromMainTreeMultiThread()
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    if (callbackId_.has_value()) {
        pipeline->UnregisterSurfaceChangedCallback(callbackId_.value_or(-1));
    }
}

} // namespace OHOS::Ace::NG