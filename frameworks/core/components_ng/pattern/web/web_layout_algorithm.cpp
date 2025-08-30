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

#include "core/components_ng/pattern/web/web_pattern.h"

constexpr int32_t MAX_TEXTURE_SIZE = 500000;
constexpr int32_t MAX_SURFACE_SIZE = 8000;

namespace OHOS::Ace::NG {
WebLayoutAlgorithm::WebLayoutAlgorithm() = default;

void WebLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = DynamicCast<WebPattern>(host->GetPattern());
    CHECK_NULL_VOID(pattern);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    BoxLayoutAlgorithm::Measure(layoutWrapper);
    int frameWidth = geometryNode->GetFrameSize().Width();
    int rootLayerHeight = pattern->GetRootLayerHeight();
    auto renderMode = pattern->GetRenderMode();
    if (pattern->GetLayoutMode() == WebLayoutMode::FIT_CONTENT && IsValidRootLayer(frameWidth, renderMode) &&
        IsValidRootLayer(rootLayerHeight, renderMode)) {
        auto drawSize = SizeF(frameWidth, rootLayerHeight);
        TAG_LOGD(AceLogTag::ACE_WEB, "WebLayoutAlgorithm::Measure,drawSize : %{public}s", drawSize.ToString().c_str());
        layoutWrapper->GetGeometryNode()->SetFrameSize(drawSize);
    }
}

bool WebLayoutAlgorithm::IsValidRootLayer(int32_t x, RenderMode renderMode)
{
    int32_t maxSize = 0;
    if (renderMode == RenderMode::SYNC_RENDER) {
        maxSize = MAX_TEXTURE_SIZE;
    } else {
        maxSize = MAX_SURFACE_SIZE;
    }
    return x > 0 && x <= maxSize;
}
} // namespace OHOS::Ace::NG
