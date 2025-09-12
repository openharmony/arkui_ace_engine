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

#include "base/utils/utf_helper.h"
#include "core/components/image/image_theme.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void ImagePattern::OnAttachToMainTreeMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderCtx = host->GetRenderContext();
    CHECK_NULL_VOID(renderCtx);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    imagePaintMethod_ = MakeRefPtr<ImagePaintMethod>(nullptr);
    renderCtx->SetClipToBounds(false);
    renderCtx->SetUsingContentRectForRenderFrame(true);
    pipeline->AddWindowStateChangedCallback(host->GetId());
    auto textTheme = pipeline->GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme);
    selectedColor_ = textTheme->GetSelectedColor();
    overlayMod_ = MakeRefPtr<ImageOverlayModifier>(selectedColor_);
    auto imageTheme = pipeline->GetTheme<ImageTheme>();
    CHECK_NULL_VOID(imageTheme);
    smoothEdge_ = imageTheme->GetMinEdgeAntialiasing();
}

void ImagePattern::OnDetachFromMainTreeMultiThread()
{
    if (isNeedReset_) {
        ResetImageAndAlt();
        isNeedReset_ = false;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CloseSelectOverlay();

    auto id = host->GetId();
    auto pipeline = AceType::DynamicCast<PipelineContext>(PipelineBase::GetCurrentContextSafelyWithCheck());
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowStateChangedCallback(id);
}
} // namespace OHOS::Ace::NG