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

#include "core/components_ng/pattern/custom/custom_node_pattern.h"

#include "base/utils/utils.h"

namespace OHOS::Ace::NG {

bool CustomNodePattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout)
{
    CHECK_NULL_RETURN(dirty, false);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto customNodeLayoutAlgorithm =
        DynamicCast<CustomNodeLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm());
    if (!customNodeLayoutAlgorithm) {
        // second measure.
        return false;
    }
    auto uiNode = customNodeLayoutAlgorithm->MoveBuildItem();
    if (uiNode) {
        uiNode->MountToParent(host);
        renderFunction_ = nullptr;
    }
    return false;
}

} // namespace OHOS::Ace::NG