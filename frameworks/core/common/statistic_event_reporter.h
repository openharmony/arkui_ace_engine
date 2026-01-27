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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_STATISTIC_EVENT_REPORTRE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_STATISTIC_EVENT_REPORTRE_H

#include <map>
#include <memory>
#include <queue>
#include <string>

namespace OHOS::Ace {
class PipelineBase;
enum class StatisticEventType {
    FA_APP_START = 0,
    XCOMPONENT_TYPE_USE_STRING = 10100,
    XCOMPONENT_SET_SURFACE_SIZE = 10101,
    XCOMPONENT_TYPE_COMPONENT = 10102,
    XCOMPONENT_TYPE_NODE = 10103,
    XCOMPONENT_NATIVE_ATTACH_NATIVE_ROOT_NODE = 10104,
    XCOMPONENT_NATIVE_DETACH_NATIVE_ROOT_NODE = 10105,
    XCOMPONENT_SET_ATTRIBUTE_NODE_TYPE = 10106,
    XCOMPONENT_SET_ATTRIBUTE_NODE_SURFACE_SIZE = 10107,
    CANVAS_FILL_STYLE_GETTER = 10200,
    CANVAS_LINE_WIDTH_GETTER = 10201,
    CANVAS_STROKE_STYLE_GETTER = 10202,
    CANVAS_LINE_CAP_GETTER = 10203,
    CANVAS_LINE_JOIN_GETTER = 10204,
    CANVAS_MITER_LIMIT_GETTER = 10205,
    CANVAS_FONT_GETTER = 10206,
    CANVAS_TEXT_ALIGN_GETTER = 10207,
    CANVAS_TEXT_BASELINE_GETTER = 10208,
    CANVAS_GLOBAL_ALPHA_GETTER = 10209,
    CANVAS_LINE_DASH_OFFSET_GETTER = 10210,
    CANVAS_GLOBAL_COMPOSITE_OPERATION_GETTER = 10211,
    CANVAS_SHADOW_BLUR_GETTER = 10212,
    CANVAS_SHADOW_COLOR_GETTER = 10213,
    CANVAS_SHADOW_OFFSET_X_GETTER = 10214,
    CANVAS_SHADOW_OFFSET_Y_GETTER = 10215,
    CANVAS_IMAGE_SMOOTHING_ENABLE_GETTER = 10216,
    CANVAS_IMAGE_SMOOTHING_QUALITY_GETTER = 10217,
    CANVAS_DIRECTION_GETTER = 10218,
    CANVAS_FILTER_GETTER = 10219,
    CANVAS_LETTER_SPACING_GETTER = 10220,
    CANVAS_TASKS_OVERFLOW = 10221,
    CANVAS_BITMAP_SIZE_EXCEED_LIMIT = 10222,
    CANVAS_CUSTOM_FONT = 10223,
    CANVAS_NAN_INFINITY_PARAM = 10224,
    CANVAS_NINE_PARAM_DRAWIMAGE = 10225,
    CANVAS_GLOBAL_ALPHA_MINUS_ONE = 10226,
    CALL_SET_CACHE_RANGE,
    SEARCH_ONDIDINSERT,
    SEARCH_ONWILLDELETE,
    SEARCH_ONDIDDELETE,
    CLICK_AI_MENU_PHONE_NUMBER,
    CLICK_AI_MENU_URL,
    CLICK_AI_MENU_EMAIL,
    CLICK_AI_MENU_ADDRESS,
    CLICK_AI_MENU_DATE_TIME,
    CLICK_AI_MENU_ASK_CELIA,
};

struct StatisticAppInfo {
    std::string bundleName;
};

struct StatisticEventInfo {
    std::string eventName;
    std::string subEventName;
    int32_t eventCount = 1;
};

class StatisticEventReporter : public std::enable_shared_from_this<StatisticEventReporter> {
public:
    StatisticEventReporter();
    explicit StatisticEventReporter(int32_t instanceId);
    virtual ~StatisticEventReporter() = default;
    void SendEvent(StatisticEventType eventType);
    void TryReportStatisticEvents(PipelineBase* pipeline);
    void ForceReportStatisticEvents();
private:
    void ReportStatisticEvents(const std::map<StatisticEventType, StatisticEventInfo>& events);
    StatisticEventInfo ConvertToEvent(StatisticEventType eventType);
    int32_t totalEventCount_ = 0;
    StatisticAppInfo appInfo_;
    std::map<StatisticEventType, StatisticEventInfo> statisitcEventMap_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_STATISTIC_EVENT_REPORTRE_H