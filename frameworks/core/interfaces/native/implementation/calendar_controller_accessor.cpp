/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CalendarControllerAccessor {
void DestroyPeerImpl(CalendarControllerPeer* peer)
{
}
CalendarControllerPeer* CtorImpl()
{
    return new CalendarControllerPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void BackToTodayImpl(CalendarControllerPeer* peer)
{
}
void GoToImpl(CalendarControllerPeer* peer,
              const Ark_Literal_Number_day_month_year* value)
{
}
} // CalendarControllerAccessor
const GENERATED_ArkUICalendarControllerAccessor* GetCalendarControllerAccessor()
{
    static const GENERATED_ArkUICalendarControllerAccessor CalendarControllerAccessorImpl {
        CalendarControllerAccessor::DestroyPeerImpl,
        CalendarControllerAccessor::CtorImpl,
        CalendarControllerAccessor::GetFinalizerImpl,
        CalendarControllerAccessor::BackToTodayImpl,
        CalendarControllerAccessor::GoToImpl,
    };
    return &CalendarControllerAccessorImpl;
}

}
