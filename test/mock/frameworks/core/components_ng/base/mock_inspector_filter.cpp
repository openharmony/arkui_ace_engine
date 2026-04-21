/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/inspector_filter.h"

namespace OHOS::Ace::NG {
bool InspectorFilter::CheckFixedAttr(const FixedAttrBit attrBit) const
{
    return (filterFixed & (1ULL << attrBit)) != 0;
}

bool InspectorFilter::CheckExtAttr(const std::string& attr) const
{
    return std::find(filterExt.begin(), filterExt.end(), attr) != filterExt.end();
}

bool InspectorFilter::CheckFilterAttr(const FixedAttrBit fixedAttrBit, const char* extAttr) const
{
    if (CheckFixedAttr(fixedAttrBit)) {
        return true;
    }
    if (extAttr == nullptr) {
        return false;
    }
    return CheckExtAttr(extAttr);
}

bool InspectorFilter::IsFastFilter() const
{
    return FilterEmpty();
}

void InspectorFilter::AddFilterAttr(const std::string& attr)
{
    filterExt.emplace_back(attr);
}

void InspectorFilter::SetFilterID(std::string& id)
{
    filterId = id;
}

std::string InspectorFilter::GetFilterID(void) const
{
    return filterId;
}

void InspectorFilter::SetFilterDepth(size_t depth)
{
    filterDepth = static_cast<uint32_t>(depth);
}

size_t InspectorFilter::GetFilterDepth() const
{
    return filterDepth;
}

bool InspectorFilter::FilterEmpty() const
{
    return filterId.empty() && filterDepth == 0 && filterFixed == 0 && filterExt.empty();
}
} // namespace OHOS::Ace::NG
