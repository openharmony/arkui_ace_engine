/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/utility/reverse_converter.h"
#include "ui/event/touch_event.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TouchEventExtenderAccessor {
Ark_NativePointer GetNativePtrImpl(const Ark_TouchEventProxy* event)
{
    return event->ptr;
}
void StopPropagationImpl(Ark_NativePointer node)
{
    auto eventInfo = static_cast<TouchEventInfo*>(node);
    if (eventInfo) {
        eventInfo->SetStopPropagation(true);
    }
}
Opt_Array_HistoricalPoint GetHistoricalPointsImpl(Ark_NativePointer node)
{
    auto eventInfo = static_cast<TouchEventInfo*>(node);
    std::list<TouchLocationInfo> history;
    if (eventInfo) {
        history = eventInfo->GetHistory();
    }
    return Converter::ArkValue<Opt_Array_HistoricalPoint>(history, Converter::FC);
}
void PreventDefaultImpl(Ark_NativePointer node)
{
    auto eventInfo = static_cast<TouchEventInfo*>(node);
    if (eventInfo) {
        eventInfo->SetPreventDefault(true);
    }
}
} // TouchEventExtenderAccessor
const GENERATED_ArkUITouchEventExtenderAccessor* GetTouchEventExtenderAccessor()
{
    static const GENERATED_ArkUITouchEventExtenderAccessor TouchEventExtenderAccessorImpl {
        TouchEventExtenderAccessor::GetNativePtrImpl,
        TouchEventExtenderAccessor::StopPropagationImpl,
        TouchEventExtenderAccessor::GetHistoricalPointsImpl,
        TouchEventExtenderAccessor::PreventDefaultImpl,
    };
    return &TouchEventExtenderAccessorImpl;
}

}
