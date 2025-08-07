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

#include "core/components_ng/pattern/image_animator/image_animator_pattern.h"

namespace OHOS::Ace::NG {
void ImageAnimatorPattern::OnAttachToFrameNodeMultiThread()
{
    // nothing, thread unsafe
}

void ImageAnimatorPattern::OnAttachToMainTreeMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetClipToFrame(true);

    UpdateBorderRadius();
    RegisterVisibleAreaChange();
}
} // namespace OHOS::Ace::NG