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
#include "core/components_ng/pattern/scrollable/scrollable_utils.h"

#include "core/pipeline_ng/pipeline_context.h"
namespace OHOS::Ace::NG {
float ScrollableUtils::CheckHeightExpansion(const RefPtr<LayoutProperty>& layoutProps, Axis axis)
{
    float expandHeight = 0.0f;
    auto&& safeAreaOpts = layoutProps->GetSafeAreaExpandOpts();
    bool canExpand = axis == Axis::VERTICAL && safeAreaOpts && (safeAreaOpts->edges & SAFE_AREA_EDGE_BOTTOM) &&
                     (safeAreaOpts->type & SAFE_AREA_TYPE_SYSTEM);
    if (canExpand) {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipeline, {});
        auto safeArea = pipeline->GetSafeArea();
        expandHeight = safeArea.bottom_.Length();
    }
    return expandHeight;
}
} // namespace OHOS::Ace::NG
