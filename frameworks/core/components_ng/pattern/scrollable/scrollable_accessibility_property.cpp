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

#include "core/components_ng/pattern/scrollable/scrollable_accessibility_property.h"

#if defined(OHOS_STANDARD_SYSTEM) and !defined(ACE_UNITTEST)
#include "accessibility_element_info.h"
#endif

#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"

namespace OHOS::Ace::NG {
#if defined(OHOS_STANDARD_SYSTEM) and !defined(ACE_UNITTEST)
namespace {
constexpr const char* AXIS_VERTICAL = "vertical";
constexpr const char* AXIS_HORIZONTAL = "horizontal";
constexpr const char* AXIS_FREE = "free";
constexpr const char* AXIS_NONE = "none";
} // namespace
#endif

float ScrollableAccessibilityProperty::GetScrollOffSet() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, 0.0f);
    auto pattern = frameNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_RETURN(pattern, 0.0f);
    return pattern->GetTotalOffset();
}

void ScrollableAccessibilityProperty::GetExtraElementInfo(Accessibility::ExtraElementInfo& extraElementInfo)
{
#if defined(OHOS_STANDARD_SYSTEM) and !defined(ACE_UNITTEST)
    auto frameNode = host_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto scrollablePattern = frameNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_VOID(scrollablePattern);

    std::string axisStr;
    switch (scrollablePattern->GetAxis()) {
        case Axis::VERTICAL:
            axisStr = AXIS_VERTICAL;
            break;
        case Axis::HORIZONTAL:
            axisStr = AXIS_HORIZONTAL;
            break;
        case Axis::FREE:
            axisStr = AXIS_FREE;
            break;
        case Axis::NONE:
            axisStr = AXIS_NONE;
            break;
        default:
            break;
    }
    extraElementInfo.SetExtraElementInfo("direction", axisStr);
#endif
}
} // namespace OHOS::Ace::NG
