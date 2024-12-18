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

#include "core/components_ng/pattern/toast/toast_accessibility_property.h"

#if defined(OHOS_STANDARD_SYSTEM) and !defined(ACE_UNITTEST)
#include "accessibility_element_info.h"
#endif

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/toast/toast_layout_property.h"

namespace OHOS::Ace::NG {


void ToastAccessibilityProperty::GetExtraElementInfo(Accessibility::ExtraElementInfo& extraElementInfo)
{
#if defined(OHOS_STANDARD_SYSTEM) and !defined(ACE_UNITTEST)
    
    auto frameNode = host_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto toastProperty = frameNode->GetPaintProperty<ToastLayoutProperty>();
    CHECK_NULL_VOID(toastProperty);

    auto toastSelectStatus = toastProperty->GetSelectStatus();
    extraElementInfo.SetExtraElementInfo(
        "SideBarContainerStates", static_cast<int32_t>(toastSelectStatus));
#endif
}
} // namespace OHOS::Ace::NG
