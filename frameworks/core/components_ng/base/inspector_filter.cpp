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

#include "core/components_ng/base/inspector_filter.h"

#include <algorithm>
#include <map>
#include <string>

namespace OHOS::Ace::NG {
namespace {
const static std::map<std::string, FixedAttrBit> FIXED_ATTR_MAP = {
    { "id",          FIXED_ATTR_ID          },
    { "content",     FIXED_ATTR_CONTENT     },
    { "src",         FIXED_ATTR_SRC         },
    { "editable",    FIXED_ATTR_EDITABLE    },
    { "scrollable",  FIXED_ATTR_SCROLLABLE  },
    { "selectable",  FIXED_ATTR_SELECTABLE  },
    { "focusable",   FIXED_ATTR_FOCUSABLE   },
    { "focused",     FIXED_ATTR_FOCUSED     },
};
}

bool InspectorFilter::CheckFixedAttr(const FixedAttrBit attrBit) const
{
    if (FilterEmpty()) {
        return true;
    }
    return (filterFixed >> attrBit) & 1;
}

bool InspectorFilter::CheckExtAttr(const std::string& attr) const
{
    if (FilterEmpty()) {
        return true;
    }
    return std::find(filterExt.begin(), filterExt.end(), attr) != filterExt.end();
}

bool InspectorFilter::CheckFilterAttr(const FixedAttrBit fixedAttrBit, const char* extAttr) const
{
    /* no filter attr set */
    if (FilterEmpty()) {
        return true;
    }
    /* fixed attr set */
    if ((filterFixed >> fixedAttrBit) & 1) {
        return true;
    }
    /* extend attr set */
    if (std::find(filterExt.begin(), filterExt.end(), extAttr) != filterExt.end()) {
        return true;
    }
    return false;
}

bool InspectorFilter::IsFastFilter() const
{
    /* no filter attr set */
    if (FilterEmpty()) {
        return false;
    }
    /* no extend attr set */
    if (!filterExt.empty()) {
        return false;
    }
    return true;
}

void InspectorFilter::AddFilterAttr(const std::string& attr)
{
    auto iter = FIXED_ATTR_MAP.find(attr);
    if (iter != FIXED_ATTR_MAP.end()) {
        filterFixed |= (1ULL << iter->second);  /* this is a fixed attr */
    } else {
        /* this is a extend attr */
        if (std::find(filterExt.begin(), filterExt.end(), attr) == filterExt.end()) {
            filterExt.emplace_back(attr);
        }
    }
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
    filterDepth = depth;
}

size_t InspectorFilter::GetFilterDepth() const
{
    return filterDepth;
}

bool InspectorFilter::FilterEmpty() const
{
    return !filterFixed && filterExt.empty();
}

} // namespace OHOS::Ace::NG
