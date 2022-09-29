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

#include "grid_container_layout_property.h"

#include "base/log/log_wrapper.h"

namespace OHOS::Ace::NG {

void GridContainerLayoutProperty::RegistGridChild(const RefPtr<FrameNode>& child)
{
    childrenFramenode_.emplace_back(child);
}

void GridContainerLayoutProperty::OnContainerInfoUpdate(const GridContainerInfo& info)
{
    LOGD("GridContainer layout info update.");
    for (auto p = childrenFramenode_.begin(); p != childrenFramenode_.end(); ++p) {
        RefPtr<FrameNode> child;
        do {
            child = p->Upgrade();
            if (child) {
                LOGD("MarkDirtyNode, %{public}s", child->GetTag().c_str());
                child->MarkDirtyNode(PROPERTY_UPDATE_MEASURE | PROPERTY_UPDATE_LAYOUT);
            }
            p = childrenFramenode_.erase(p);
        } while (p != childrenFramenode_.end());
    }
}

void GridContainerLayoutProperty::BuildWidth(float width)
{
    if (NearEqual(width, Infinity<float>())) {
        propContainerInfo_->BuildColumnWidth();
    } else {
        propContainerInfo_->BuildColumnWidth(width);
    }
}

} // namespace OHOS::Ace::NG
