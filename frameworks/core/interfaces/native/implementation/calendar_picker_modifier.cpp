/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CalendarPickerModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // CalendarPickerModifier
namespace CalendarPickerInterfaceModifier {
void SetCalendarPickerOptionsImpl(Ark_NativePointer node,
                                  const Opt_CalendarOptions* options)
{
}
} // CalendarPickerInterfaceModifier
namespace CalendarPickerAttributeModifier {
void TextStyle0Impl(Ark_NativePointer node,
                    const Opt_PickerTextStyle* value)
{
}
void TextStyle1Impl(Ark_NativePointer node,
                    const Opt_PickerTextStyle* value)
{
}
void OnChange0Impl(Ark_NativePointer node,
                   const Opt_Callback_Date_Void* value)
{
}
void OnChange1Impl(Ark_NativePointer node,
                   const Opt_Callback_Date_Void* value)
{
}
void MarkTodayImpl(Ark_NativePointer node,
                   const Opt_Boolean* value)
{
}
void EdgeAlign0Impl(Ark_NativePointer node,
                    const Opt_CalendarAlign* alignType,
                    const Opt_Offset* offset)
{
}
void EdgeAlign1Impl(Ark_NativePointer node,
                    const Opt_CalendarAlign* alignType,
                    const Opt_Offset* offset)
{
}
} // CalendarPickerAttributeModifier
const GENERATED_ArkUICalendarPickerModifier* GetCalendarPickerModifier()
{
    static const GENERATED_ArkUICalendarPickerModifier ArkUICalendarPickerModifierImpl {
        CalendarPickerModifier::ConstructImpl,
        CalendarPickerInterfaceModifier::SetCalendarPickerOptionsImpl,
        CalendarPickerAttributeModifier::TextStyle0Impl,
        CalendarPickerAttributeModifier::TextStyle1Impl,
        CalendarPickerAttributeModifier::OnChange0Impl,
        CalendarPickerAttributeModifier::OnChange1Impl,
        CalendarPickerAttributeModifier::MarkTodayImpl,
        CalendarPickerAttributeModifier::EdgeAlign0Impl,
        CalendarPickerAttributeModifier::EdgeAlign1Impl,
    };
    return &ArkUICalendarPickerModifierImpl;
}

}
