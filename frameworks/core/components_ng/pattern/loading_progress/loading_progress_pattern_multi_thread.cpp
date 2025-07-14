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

#include "core/components_ng/pattern/loading_progress/loading_progress_pattern.h"

namespace OHOS::Ace::NG {
void LoadingProgressPattern::OnAttachToMainTreeMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
    host->GetRenderContext()->SetClipToBounds(true);
    RegisterVisibleAreaChange();
}

void LoadingProgressPattern::OnDetachFromMainTreeMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveVisibleAreaChangeNode(host->GetId());
    pipeline->RemoveWindowStateChangedCallback(host->GetId());
    hasVisibleChangeRegistered_ = false;
}
} // namespace OHOS::Ace::NG
