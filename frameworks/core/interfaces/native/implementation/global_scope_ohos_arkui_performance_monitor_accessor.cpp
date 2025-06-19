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

#include "base/perfmonitor/perf_monitor.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG {
namespace {
const auto EMPTY_STRING = "";
} // namespace
namespace Converter {
template<>
void AssignCast(std::optional<PerfActionType>& dst, const Ark_PerfMonitorActionType& src)
{
    switch (src) {
        case ARK_PERF_MONITOR_ACTION_TYPE_LAST_DOWN: dst = PerfActionType::LAST_DOWN; break;
        case ARK_PERF_MONITOR_ACTION_TYPE_LAST_UP: dst = PerfActionType::LAST_UP; break;
        case ARK_PERF_MONITOR_ACTION_TYPE_FIRST_MOVE: dst = PerfActionType::FIRST_MOVE; break;
        default: LOGE("Unexpected enum value in Ark_PerfMonitorActionType: %{public}d", src);
    }
}
template<>
void AssignCast(std::optional<PerfSourceType>& dst, const Ark_PerfMonitorSourceType& src)
{
    switch (src) {
        case ARK_PERF_MONITOR_SOURCE_TYPE_PERF_TOUCH_EVENT: dst = PerfSourceType::PERF_TOUCH_EVENT; break;
        case ARK_PERF_MONITOR_SOURCE_TYPE_PERF_MOUSE_EVENT: dst = PerfSourceType::PERF_MOUSE_EVENT; break;
        case ARK_PERF_MONITOR_SOURCE_TYPE_PERF_TOUCHPAD_EVENT: dst = PerfSourceType::PERF_TOUCH_PAD; break;
        case ARK_PERF_MONITOR_SOURCE_TYPE_PERF_JOYSTICK_EVENT: dst = PerfSourceType::PERF_JOY_STICK; break;
        case ARK_PERF_MONITOR_SOURCE_TYPE_PERF_KEY_EVENT: dst = PerfSourceType::PERF_KEY_EVENT; break;
        default: LOGE("Unexpected enum value in Ark_PerfMonitorSourceType: %{public}d", src);
    }
}
} // namespace Converter
} // OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GlobalScope_ohos_arkui_performanceMonitorAccessor {
void BeginImpl(const Ark_String* scene,
               Ark_PerfMonitorActionType startInputType,
               const Opt_String* note)
{
    CHECK_NULL_VOID(scene);
    CHECK_NULL_VOID(note);
    auto sceneId = Converter::Convert<std::string>(*scene);
    auto action = Converter::OptConvert<PerfActionType>(startInputType).value_or(PerfActionType::UNKNOWN_ACTION);
    auto notes = Converter::OptConvert<std::string>(*note).value_or(EMPTY_STRING);
    auto pMonitor = PerfMonitor::GetPerfMonitor();
    CHECK_NULL_VOID(pMonitor);
    pMonitor->Start(sceneId, action, notes);
}
void EndImpl(const Ark_String* scene)
{
    CHECK_NULL_VOID(scene);
    auto sceneId = Converter::Convert<std::string>(*scene);
    auto pMonitor = PerfMonitor::GetPerfMonitor();
    CHECK_NULL_VOID(pMonitor);
    pMonitor->End(sceneId, false);
}
void RecordInputEventTimeImpl(Ark_PerfMonitorActionType actionType,
                              Ark_PerfMonitorSourceType sourceType,
                              const Ark_Number* time)
{
    CHECK_NULL_VOID(time);
    auto action = Converter::OptConvert<PerfActionType>(actionType).value_or(PerfActionType::UNKNOWN_ACTION);
    auto source = Converter::OptConvert<PerfSourceType>(sourceType).value_or(PerfSourceType::UNKNOWN_SOURCE);
    auto timestamp = Converter::Convert<int32_t>(*time);
    LOGE("ARKOALA GlobalScope_ohos_arkui_performanceMonitorAccessor::RecordInputEventTimeImpl - "
        "Ark_Number width of int32_t is not enough for implementation of int64_t functionality.");
    auto pMonitor = PerfMonitor::GetPerfMonitor();
    CHECK_NULL_VOID(pMonitor);
    pMonitor->RecordInputEvent(action, source, timestamp);
}
} // GlobalScope_ohos_arkui_performanceMonitorAccessor
const GENERATED_ArkUIGlobalScope_ohos_arkui_performanceMonitorAccessor* GetGlobalScope_ohos_arkui_performanceMonitorAccessor()
{
    static const GENERATED_ArkUIGlobalScope_ohos_arkui_performanceMonitorAccessor GlobalScope_ohos_arkui_performanceMonitorAccessorImpl {
        GlobalScope_ohos_arkui_performanceMonitorAccessor::BeginImpl,
        GlobalScope_ohos_arkui_performanceMonitorAccessor::EndImpl,
        GlobalScope_ohos_arkui_performanceMonitorAccessor::RecordInputEventTimeImpl,
    };
    return &GlobalScope_ohos_arkui_performanceMonitorAccessorImpl;
}

}
