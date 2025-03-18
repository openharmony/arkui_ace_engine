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
#include "core/components_ng/pattern/window_scene/scene/window_layout_algorithm.h"

#include "core/components/toggle/toggle_theme.h"
#include "core/components_ng/pattern/window_scene/scene/window_pattern.h"

namespace OHOS::Ace::NG {
void WindowLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<WindowPattern>();
    CHECK_NULL_VOID(pattern);
    auto windowLayoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(windowLayoutProperty);
    auto layoutConstraint = windowLayoutProperty->CreateChildConstraint();
    pattern->CheckAndMeasureStartingWindow(layoutConstraint.maxSize);
    BoxLayoutAlgorithm::Measure(layoutWrapper);
}

void WindowLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    BoxLayoutAlgorithm::Layout(layoutWrapper);
}
} // namespace OHOS::Ace::NG