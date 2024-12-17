/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "customizeview_pattern.h"

#include "customizeview_paint_method.h"
#include "ui/base/referenced.h"
#include "ui/view/frame_node.h"
#include "ui/view/layout/box_layout_algorithm.h"
#include "ui/view/layout/layout_algorithm.h"

namespace OHOS::Customize {
Ace::RefPtr<Ace::Kit::LayoutAlgorithm> CustomizePattern::CreateLayoutAlgorithm()
{
    auto host = GetHost();
    auto layoutAlgorithm = Ace::Referenced::MakeRefPtr<Ace::Kit::BoxLayoutAlgorithm>(host);
    return layoutAlgorithm;
}

Ace::RefPtr<Ace::Kit::NodePaintMethod> CustomizePattern::CreateNodePaintMethod()
{
    auto paintMethod = Ace::Referenced::MakeRefPtr<CustomizeViewPaintMethod>();
    return paintMethod;
}

bool CustomizePattern::OnDirtyLayoutrSwap(const Ace::NG::DirtySwapConfig& config)
{
    return !config.skipMeasure;
}

} // namespace OHOS::Customize
