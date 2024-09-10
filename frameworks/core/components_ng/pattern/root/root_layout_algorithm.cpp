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

#include "core/components_ng/pattern/root/root_layout_algorithm.h"

#include "core/components_ng/layout/layout_wrapper.h"

namespace OHOS::Ace::NG {

void RootLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    PerformLayout(layoutWrapper);
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        if (child->GetHostTag() == V2::KEYBOARD_ETS_TAG) {
            auto rootSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
            auto size = child->GetGeometryNode()->GetFrameSize();
            auto offset = OffsetF(0, rootSize.Height() - size.Height());
            child->GetGeometryNode()->SetFrameOffset(offset);
        }
        child->Layout();
    }
}
} // namespace OHOS::Ace::NG
