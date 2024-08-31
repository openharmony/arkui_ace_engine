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

#include "core/components_ng/pattern/bubble/bubble_accessibility_property.h"

#if defined(OHOS_STANDARD_SYSTEM) and !defined(ACE_UNITTEST)
#include "accessibility_element_info.h"
#endif

namespace OHOS::Ace::NG {
void BubbleAccessibilityProperty::GetExtraElementInfo(Accessibility::ExtraElementInfo& extraElementInfo)
{
#if defined(OHOS_STANDARD_SYSTEM) and !defined(ACE_UNITTEST)
    extraElementInfo.SetExtraElementInfo("SideBarContainerStates", showedState_);
#endif
}
} // namespace OHOS::Ace::NG