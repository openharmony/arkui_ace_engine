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

#include "core/components_ng/pattern/web/web_layout_algorithm.h"

#include "core/components_ng/base/frame_node.h"

#if !defined(ANDROID_PLATFORM) && !defined(IOS_PLATFORM)
#include "core/components_ng/pattern/web/web_pattern.h"
#else
#include "core/components_ng/pattern/web/cross_platform/web_pattern.h"
#endif
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

constexpr int32_t MAX_TEXTURE_SIZE = 16000;
constexpr int32_t MAX_SURFACE_SIZE = 8000;

namespace OHOS::Ace::NG {
WebLayoutAlgorithm::WebLayoutAlgorithm() = default;

std::optional<SizeF> WebLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto layoutSize = contentConstraint.selfIdealSize.IsValid() ? contentConstraint.selfIdealSize.ConvertToSizeT()
                                                                : contentConstraint.maxSize;
    return layoutSize;
}

void WebLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = DynamicCast<WebPattern>(host->GetPattern());
    CHECK_NULL_VOID(pattern);
    int rootLayerWidth = pattern->GetRootLayerWidth();
    int rootLayerHeight = pattern->GetRootLayerHeight();
    auto type = pattern->GetWebType();
    if (pattern->GetLayoutMode() == WebLayoutMode::FIT_CONTENT && IsValidRootLayer(rootLayerWidth, type) &&
        IsValidRootLayer(rootLayerHeight, type)) {
        layoutWrapper->GetGeometryNode()->SetFrameSize(SizeF(rootLayerWidth, rootLayerHeight));
    } else {
        BoxLayoutAlgorithm::Measure(layoutWrapper);
    }
}

bool WebLayoutAlgorithm::IsValidRootLayer(int32_t x, WebType type)
{
    int32_t maxSize = 0;
    if (type == WebType::TEXTURE) {
        maxSize = MAX_TEXTURE_SIZE;
    } else {
        maxSize = MAX_SURFACE_SIZE;
    }
    return x > 0 && x <= maxSize;
}
} // namespace OHOS::Ace::NG
