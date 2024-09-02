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

namespace OHOS::Ace::NG {

void GridContainerLayoutProperty::RegistGridChild(const RefPtr<FrameNode>& child)
{
    childrenFramenode_.emplace_back(child);
}

void GridContainerLayoutProperty::OnContainerInfoUpdate(const GridContainerInfo& /* info */)
{
    auto p = childrenFramenode_.begin();
    while (p != childrenFramenode_.end()) {
        RefPtr<FrameNode> child = p->Upgrade();
        if (child) {
            child->MarkDirtyNode(PROPERTY_UPDATE_MEASURE | PROPERTY_UPDATE_LAYOUT);
        }
        p = childrenFramenode_.erase(p);
    }
}

void GridContainerLayoutProperty::BuildWidth(float width)
{
    if (GreaterOrEqualToInfinity(width)) {
        propContainerInfo_->BuildColumnWidth();
    } else {
        propContainerInfo_->BuildColumnWidth(width);
    }
}

void GridContainerLayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    LinearLayoutProperty::ToJsonValue(json, filter);
    if (!HasContainerInfo()) {
        return;
    }
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto info = GetContainerInfoValue();
    const std::string sizeTypeStrs[] { "SizeType.Auto", "SizeType.XS", "SizeType.SM", "SizeType.MD", "SizeType.LG",
        "SizeType.XL" };
    auto constructor = JsonUtil::Create(true);
    constructor->Put("columns", std::to_string(info.GetColumns()).c_str());
    constructor->Put("sizeType", sizeTypeStrs[static_cast<int32_t>(info.GetSizeType())].c_str());
    constructor->Put("gutter", info.GetGutterWidth().ToString().c_str());
    constructor->Put("margin", info.GetMarginLeft().ToString().c_str());

    json->PutExtAttr("constructor", constructor, filter);
}

} // namespace OHOS::Ace::NG
