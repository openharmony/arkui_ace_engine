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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_BASE_INSPECTOR_FILTER_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_BASE_INSPECTOR_FILTER_H

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include "ui/base/macros.h"

namespace OHOS::Ace::NG {
namespace TreeKey {
constexpr char ID[] = "id";
constexpr char CLICKABLE[] = "clickable";
constexpr char LONG_CLICKABLE[] = "longClickable";
constexpr char SCROLLABLE[] = "scrollable";
constexpr char CONTENT[] = "content";
constexpr char PLACEHOLDER[] = "placeholder";
constexpr char CHECKED[] = "checked";
}; // namespace TreeKey

enum FixedAttrBit : uint64_t {
    FIXED_ATTR_ID = 0,         /* "id"         */
    FIXED_ATTR_CONTENT = 1,    /* "content"    */
    FIXED_ATTR_SRC = 2,        /* "src"        */
    FIXED_ATTR_EDITABLE = 3,   /* "editable"   */
    FIXED_ATTR_SCROLLABLE = 4, /* "scrollable" */
    FIXED_ATTR_SELECTABLE = 5, /* "selectable" */
    FIXED_ATTR_FOCUSABLE = 6,  /* "focusable"  */
    FIXED_ATTR_FOCUSED = 7,    /* "focused"    */
};

class ACE_FORCE_EXPORT InspectorFilter {
public:
    InspectorFilter() {}
    bool CheckFixedAttr(const FixedAttrBit attrBit) const;
    bool CheckExtAttr(const std::string& attr) const;
    bool CheckFilterAttr(const FixedAttrBit fixedAttrBit, const char* extAttr) const;
    bool IsFastFilter() const;
    void AddFilterAttr(const std::string& attr);
    void SetFilterID(std::string& id);
    std::string GetFilterID(void) const;
    void SetFilterDepth(size_t depth);
    size_t GetFilterDepth() const;

private:
    bool FilterEmpty() const;
    std::string filterId;
    uint32_t filterDepth = 0;
    uint64_t filterFixed = 0;
    std::vector<std::string> filterExt;
};

struct InspectorConfig {
    bool contentOnly = false;
    bool callingOnMain = false;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_BASE_INSPECTOR_FILTER_H
