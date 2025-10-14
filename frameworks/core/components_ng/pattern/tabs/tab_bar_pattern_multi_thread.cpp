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

#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"

#include "core/components_ng/base/frame_node.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void TabBarPattern::OnAttachToFrameNodeMultiThread()
{
}

void TabBarPattern::OnAttachToMainTreeMultiThread()
{
    InitSurfaceChangedCallback();
}

void TabBarPattern::OnDetachFromFrameNodeMultiThread(FrameNode* node)
{
}

void TabBarPattern::OnDetachFromMainTreeMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    if (HasSurfaceChangedCallback()) {
        pipeline->UnregisterSurfaceChangedCallback(surfaceChangedCallbackId_.value_or(-1));
        surfaceChangedCallbackId_ = std::nullopt;
    }
    pipeline->RemoveWindowStateChangedCallback(RawPtr(host)->GetId());
}
} // namespace OHOS::Ace::NG