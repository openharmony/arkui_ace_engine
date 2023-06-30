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

#include "core/components_ng/pattern/toast/toast_pattern.h"

#include "base/utils/utils.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t API_VERSION_9 = 9;
} // namespace

bool ToastPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& changeConfig)
{
    CHECK_NULL_RETURN(dirty, false);
    auto toastProp = DynamicCast<ToastLayoutProperty>(dirty->GetLayoutProperty());
    CHECK_NULL_RETURN(toastProp, false);
    auto toastBottom = toastProp->GetBottomValue(Dimension()).ConvertToPx();
    // todo get parent width and height
    auto context = PipelineContext::GetCurrentContext();
    auto rootHeight = context->GetRootHeight();
    auto rootWidth = context->GetRootWidth();
    auto text = dirty->GetOrCreateChildByIndex(0);
    CHECK_NULL_RETURN(text, false);
    auto toastNode = dirty->GetHostNode();
    auto toastContext = toastNode->GetRenderContext();
    CHECK_NULL_RETURN(toastContext, false);
    auto pipeline = PipelineContext::GetCurrentContext();
    OffsetT<Dimension> offset { Dimension((rootWidth - text->GetGeometryNode()->GetMarginFrameSize().Width()) / 2.0f),
        {} };
    if (context->GetMinPlatformVersion() > API_VERSION_9) {
        auto safeArea = context->GetSafeArea();
        offset.SetY(Dimension { rootHeight - toastBottom - dirty->GetGeometryNode()->GetMarginFrameSize().Height() -
                                safeArea.bottom_.Length() });
    } else {
        offset.SetY(Dimension { rootHeight - toastBottom });
    }
    toastContext->UpdateOffset(offset);

    return true;
}
} // namespace OHOS::Ace::NG
