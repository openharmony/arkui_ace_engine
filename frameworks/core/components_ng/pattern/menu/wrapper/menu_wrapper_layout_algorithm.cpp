/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_layout_algorithm.h"

#include "base/utils/utils.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
// set wrapper to full screen size
void MenuWrapperLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto screenSize = SizeF(pipeline->GetRootWidth(), pipeline->GetRootHeight());

    layoutWrapper->GetGeometryNode()->SetFrameSize(screenSize);

    auto menu = layoutWrapper->GetOrCreateChildByIndex(0);
    auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    menu->Measure(layoutConstraint);
}

void MenuWrapperLayoutAlgorithm::Layout(LayoutWrapper *layoutWrapper)
{
    auto menu = layoutWrapper->GetOrCreateChildByIndex(0);
    menu->Layout();
}

} // namespace OHOS::Ace::NG
