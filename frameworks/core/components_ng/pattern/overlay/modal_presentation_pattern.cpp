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

#include "core/components_ng/pattern/overlay/modal_presentation_pattern.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void ModalPresentationPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    host->GetLayoutProperty()->UpdateAlignment(Alignment::TOP_LEFT);
}

void ModalPresentationPattern::ModalInteractiveDismiss()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->SetDismissTarget(DismissTarget(targetId_));
    CallOnWillDismiss(static_cast<int32_t>(ContentCoverDismissReason::BACK_PRESSED));
}
} // namespace OHOS::Ace::NG
