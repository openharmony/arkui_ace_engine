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

#include "core/common/statistic_event_reporter.h"

#include "base/thread/task_executor.h"
#include "core/common/ace_application_info.h"
#include "core/common/container.h"
#include "core/common/statistic_event_adapter.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t MAX_PENDING_EVENT_COUNT = 20;
}
StatisticEventReporter::StatisticEventReporter()
{
    appInfo_.bundleName = AceApplicationInfo::GetInstance().GetPackageName();
}

StatisticEventReporter::StatisticEventReporter(int32_t instanceId)
{
    auto container = Container::GetContainer(instanceId);
    if (!container) {
        appInfo_.bundleName = AceApplicationInfo::GetInstance().GetPackageName();
        return;
    }
    auto bundleName = container->GetBundleName();
    appInfo_.bundleName = bundleName != "" ? bundleName : AceApplicationInfo::GetInstance().GetPackageName();
}

StatisticEventInfo StatisticEventReporter::ConvertToEvent(StatisticEventType eventType)
{
    switch (eventType) {
        case StatisticEventType::FA_APP_START:
            return { "FRAMEWORK", "FA_APP_START" };
        case StatisticEventType::XCOMPONENT_TYPE_USE_STRING:
            return { "XCOMPONENT", "TYPE_USE_STRING" };
        case StatisticEventType::XCOMPONENT_SET_SURFACE_SIZE:
            return { "XCOMPONENT", "SET_SURFACE_SIZE" };
        case StatisticEventType::XCOMPONENT_TYPE_COMPONENT:
            return { "XCOMPONENT", "TYPE_COMPONENT" };
        case StatisticEventType::XCOMPONENT_TYPE_NODE:
            return { "XCOMPONENT", "TYPE_NODE" };
        case StatisticEventType::XCOMPONENT_NATIVE_ATTACH_NATIVE_ROOT_NODE:
            return { "XCOMPONENT", "NATIVE_ATTACH_NATIVE_ROOT_NODE" };
        case StatisticEventType::XCOMPONENT_NATIVE_DETACH_NATIVE_ROOT_NODE:
            return { "XCOMPONENT", "NATIVE_DETACH_NATIVE_ROOT_NODE" };
        case StatisticEventType::XCOMPONENT_SET_ATTRIBUTE_NODE_TYPE:
            return { "XCOMPONENT", "SET_ATTRIBUTE_NODE_TYPE" };
        case StatisticEventType::XCOMPONENT_SET_ATTRIBUTE_NODE_SURFACE_SIZE:
            return { "XCOMPONENT", "SET_ATTRIBUTE_NODE_SURFACE_SIZE" };
        case StatisticEventType::CANVAS_FILL_STYLE_GETTER:
            return { "CANVAS", "FILL_STYLE_GETTER" };
        case StatisticEventType::CANVAS_LINE_WIDTH_GETTER:
            return { "CANVAS", "LINE_WIDTH_GETTER" };
        case StatisticEventType::CANVAS_STROKE_STYLE_GETTER:
            return { "CANVAS", "STROKE_STYLE_GETTER" };
        case StatisticEventType::CANVAS_LINE_CAP_GETTER:
            return { "CANVAS", "LINE_CAP_GETTER" };
        case StatisticEventType::CANVAS_LINE_JOIN_GETTER:
            return { "CANVAS", "LINE_JOIN_GETTER" };
        case StatisticEventType::CANVAS_MITER_LIMIT_GETTER:
            return { "CANVAS", "MITER_LIMIT_GETTER" };
        case StatisticEventType::CANVAS_FONT_GETTER:
            return { "CANVAS", "FONT_GETTER" };
        case StatisticEventType::CANVAS_TEXT_ALIGN_GETTER:
            return { "CANVAS", "TEXT_ALIGN_GETTER" };
        case StatisticEventType::CANVAS_TEXT_BASELINE_GETTER:
            return { "CANVAS", "TEXT_BASELINE_GETTER" };
        case StatisticEventType::CANVAS_GLOBAL_ALPHA_GETTER:
            return { "CANVAS", "GLOBAL_ALPHA_GETTER" };
        case StatisticEventType::CANVAS_LINE_DASH_OFFSET_GETTER:
            return { "CANVAS", "LINE_DASH_OFFSET_GETTER" };
        case StatisticEventType::CANVAS_SHADOW_BLUR_GETTER:
            return { "CANVAS", "SHADOW_BLUR_GETTER" };
        case StatisticEventType::CANVAS_GLOBAL_COMPOSITE_OPERATION_GETTER:
            return { "CANVAS", "GLOBAL_COMPOSITE_OPERATION_GETTER" };
        case StatisticEventType::CANVAS_SHADOW_COLOR_GETTER:
            return { "CANVAS", "SHADOW_COLOR_GETTER" };
        case StatisticEventType::CANVAS_SHADOW_OFFSET_X_GETTER:
            return { "CANVAS", "SHADOW_OFFSET_X_GETTER" };
        case StatisticEventType::CANVAS_SHADOW_OFFSET_Y_GETTER:
            return { "CANVAS", "SHADOW_OFFSET_Y_GETTER" };
        case StatisticEventType::CANVAS_IMAGE_SMOOTHING_ENABLE_GETTER:
            return { "CANVAS", "IMAGE_SMOOTHING_ENABLE_GETTER" };
        case StatisticEventType::CANVAS_IMAGE_SMOOTHING_QUALITY_GETTER:
            return { "CANVAS", "IMAGE_SMOOTHING_QUALITY_GETTER" };
        case StatisticEventType::CANVAS_DIRECTION_GETTER:
            return { "CANVAS", "DIRECTION_GETTER" };
        case StatisticEventType::CANVAS_FILTER_GETTER:
            return { "CANVAS", "FILTER_GETTER" };
        case StatisticEventType::CANVAS_LETTER_SPACING_GETTER:
            return { "CANVAS", "LETTER_SPACING_GETTER" };
        case StatisticEventType::CANVAS_TASKS_OVERFLOW:
            return { "CANVAS", "TASKS_OVERFLOW" };
        case StatisticEventType::CANVAS_BITMAP_SIZE_EXCEED_LIMIT:
            return { "CANVAS", "BITMAP_SIZE_EXCEED_LIMIT" };
        case StatisticEventType::CANVAS_CUSTOM_FONT:
            return { "CANVAS", "CUSTOM_FONT" };
        case StatisticEventType::CANVAS_NAN_INFINITY_PARAM:
            return { "CANVAS", "NAN_INFINITY_PARAM" };
        case StatisticEventType::CANVAS_NINE_PARAM_DRAWIMAGE:
            return { "CANVAS", "NINE_PARAM_DRAWIMAGE" };
        case StatisticEventType::CANVAS_GLOBAL_ALPHA_MINUS_ONE:
            return { "CANVAS", "GLOBAL_ALPHA_MINUS_ONE" };
        case StatisticEventType::VIDEO_INVALID_PROGRESS_RATE:
            return { "VIDEO", "INVALID_PROGRESS_RATE" };
        case StatisticEventType::VIDEO_EXCEED_PROGRESS_RATE:
            return { "VIDEO", "EXCEED_PROGRESS_RATE" };
        case StatisticEventType::CALL_SET_CACHE_RANGE:
            return { "List", "CALL_SET_CACHE_RANGE" };
        case StatisticEventType::SEARCH_ONDIDINSERT:
            return { "SEARCH", "ONDIDINSERT" };
        case StatisticEventType::SEARCH_ONWILLDELETE:
            return { "SEARCH", "ONWILLDELETE" };
        case StatisticEventType::SEARCH_ONDIDDELETE:
            return { "SEARCH", "ONDIDDELETE" };
        case StatisticEventType::CLICK_AI_MENU_PHONE_NUMBER:
            return { "CLICK_AI_MENU", "PHONE_NUMBER" };
        case StatisticEventType::CLICK_AI_MENU_URL:
            return { "CLICK_AI_MENU", "URL" };
        case StatisticEventType::CLICK_AI_MENU_EMAIL:
            return { "CLICK_AI_MENU", "EMAIL" };
        case StatisticEventType::CLICK_AI_MENU_ADDRESS:
            return { "CLICK_AI_MENU", "ADDRESS" };
        case StatisticEventType::CLICK_AI_MENU_DATE_TIME:
            return { "CLICK_AI_MENU", "DATE_TIME" };
        case StatisticEventType::CLICK_AI_MENU_ASK_CELIA:
            return { "CLICK_AI_MENU", "ASK_CELIA" };
        default:
            return { "", "" };
    }
}

void StatisticEventReporter::SendEvent(StatisticEventType eventType)
{
    auto iter = statisitcEventMap_.find(eventType);
    if (iter == statisitcEventMap_.end()) {
        StatisticEventInfo event = ConvertToEvent(eventType);
        if (event.eventName == "") {
            TAG_LOGE(AceLogTag::ACE_UI_SERVICE, "invalid statistic event type");
            return;
        }
        statisitcEventMap_[eventType] = event;
    } else {
        iter->second.eventCount++;
    }
    totalEventCount_++;
}

void StatisticEventReporter::ReportStatisticEvents(const std::map<StatisticEventType, StatisticEventInfo>& events)
{
    StatisticEventAdapter::ReportStatisticEvents(appInfo_, events);
}

void StatisticEventReporter::TryReportStatisticEvents(PipelineBase* pipeline)
{
    CHECK_NULL_VOID(pipeline);
    if (totalEventCount_ < MAX_PENDING_EVENT_COUNT) {
        return;
    }
    auto executor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(executor);
    std::map<StatisticEventType, StatisticEventInfo> statisitcEvents;
    std::swap(statisitcEvents, statisitcEventMap_);
    totalEventCount_ = 0;
    executor->PostTask(
        [statisitcEvents = std::move(statisitcEvents), reporter = shared_from_this()] () {
            if (reporter) {
                reporter->ReportStatisticEvents(statisitcEvents);
            }
        }, TaskExecutor::TaskType::BACKGROUND, "ReportStatisticEvents");
}

void StatisticEventReporter::ForceReportStatisticEvents()
{
    if (statisitcEventMap_.size() == 0) {
        return;
    }
    std::map<StatisticEventType, StatisticEventInfo> statisitcEvents;
    std::swap(statisitcEvents, statisitcEventMap_);
    totalEventCount_ = 0;
    ReportStatisticEvents(statisitcEvents);
}
} // namespace OHOS::Ace