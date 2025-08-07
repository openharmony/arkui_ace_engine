/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#include "base/ressched/ressched_report.h"

namespace OHOS::Ace {
std::atomic<int32_t> ResSchedReport::createPageCount(0);
bool ResSchedReport::triggerExecuted(false);
namespace Ressched {
constexpr uint32_t RES_TYPE_CLICK_RECOGNIZE = 9;
constexpr uint32_t RES_TYPE_PUSH_PAGE       = 10;
constexpr uint32_t RES_TYPE_SLIDE           = 11;
constexpr uint32_t RES_TYPE_POP_PAGE        = 28;
constexpr uint32_t RES_TYPE_WEB_GESTURE     = 29;
constexpr uint32_t RES_TYPE_LOAD_PAGE       = 34;
constexpr uint32_t RES_TYPE_KEY_EVENT       = 122;
constexpr uint32_t RES_TYPE_AXIS_EVENT      = 123;
constexpr uint32_t RES_TYPE_PAGE_TRANSITION = 140;
constexpr uint32_t RES_TYPE_ABILITY_OR_PAGE_SWITCH = 156;
constexpr uint32_t RES_TYPE_CHECK_APP_IS_IN_SCHEDULE_LIST = 504;
#ifdef FFRT_EXISTS
constexpr uint32_t RES_TYPE_LONG_FRAME     = 71;
#endif
constexpr uint32_t RES_TYPE_OVERLAY        = 151;
constexpr int32_t TOUCH_DOWN_EVENT          = 1;
constexpr int32_t CLICK_EVENT               = 2;
constexpr int32_t TOUCH_UP_EVENT            = 3;
constexpr int32_t TOUCH_PULL_UP_EVENT = 4;
constexpr int32_t KEY_DOWN_EVENT = 1;
constexpr int32_t KEY_UP_EVENT = 2;
constexpr int32_t SLIDE_OFF_EVENT = 0;
constexpr int32_t SLIDE_DETECTING = 2;
constexpr int32_t AUTO_PLAY_ON_EVENT = 5;
constexpr int32_t AUTO_PLAY_OFF_EVENT = 6;
constexpr int32_t MOVE_DETECTING = 7;
constexpr int32_t PUSH_PAGE_START_EVENT = 0;
constexpr int32_t PUSH_PAGE_COMPLETE_EVENT = 1;
constexpr int32_t POP_PAGE_EVENT = 0;
constexpr int32_t AXIS_OFF_EVENT = 1;
constexpr int32_t AXIS_IS_PAD = 0;
constexpr int32_t AXIS_IS_MOUSE = 1;
constexpr int64_t TIME_INTERVAL = 300;
constexpr int32_t ABILITY_OR_PAGE_SWITCH_START_EVENT = 0;
constexpr int32_t ABILITY_OR_PAGE_SWITCH_END_EVENT = 1;
constexpr int32_t MODULE_SERIALIZER_COUNT = 3;
#ifdef FFRT_EXISTS
constexpr int32_t LONG_FRAME_START_EVENT = 0;
constexpr int32_t LONG_FRAME_END_EVENT = 1;
#endif
constexpr int32_t OVERLAY_ADD_EVENT = 0;
constexpr int32_t OVERLAY_REMOVE_EVENT = 1;
constexpr char NAME[] = "name";
constexpr char PID[] = "pid";
constexpr char UID[] = "uid";
constexpr char SCRTID[] = "scrTid";
constexpr char BUNDLE_NAME[] = "bundleName";
constexpr char ABILITY_NAME[] = "abilityName";
constexpr char CLICK[] = "click";
constexpr char KEY_EVENT[] = "key_event";
constexpr char PUSH_PAGE[] = "push_page";
constexpr char POP_PAGE[] = "pop_page";
constexpr char PAGE_END_FLUSH[] = "page_end_flush";
constexpr char AUTO_PLAY_ON[] = "auto_play_on";
constexpr char AUTO_PLAY_OFF[] = "auto_play_off";
constexpr char SLIDE_OFF[] = "slide_off";
constexpr char OVERLAY_ADD[] = "overlay_add";
constexpr char OVERLAY_REMOVE[] = "overlay_remove";
constexpr char TOUCH[] = "touch";
constexpr char WEB_GESTURE[] = "web_gesture";
constexpr char LOAD_PAGE[] = "load_page";
constexpr char UP_SPEED_KEY[] = "up_speed";
constexpr char KEY_CODE[] = "key_code";
constexpr char AXIS_OFF[] = "axis_off";
constexpr char AXIS_NORMAL_UP_SPEED[] = "0.0";
constexpr char AXIS_EVENT_TYPE[] = "axis_event_type";
constexpr char FROM_PAGE_INFO[] = "from_page";
constexpr char TO_PAGE_INFO[] = "to_page";
constexpr char TRANSITION_MODE[] = "transition_mode";
constexpr char ABILITY_OR_PAGE_SWITCH_START[] = "ability_or_page_switch_start";
constexpr char ABILITY_OR_PAGE_SWITCH_END[] = "ability_or_page_switch_end";
#ifdef FFRT_EXISTS
constexpr char LONG_FRAME_START[] = "long_frame_start";
constexpr char LONG_FRAME_END[] = "long_frame_end";
#endif

void LoadAceApplicationContext(std::unordered_map<std::string, std::string>& payload)
{
    auto& aceApplicationInfo = AceApplicationInfo::GetInstance();
    payload[PID] = std::to_string(aceApplicationInfo.GetPid());
    payload[UID] = std::to_string(aceApplicationInfo.GetUid());
    payload[BUNDLE_NAME] = aceApplicationInfo.GetPackageName();
    payload[ABILITY_NAME] = aceApplicationInfo.GetAbilityName();
}

void LoadReportConfig(
    const ReportConfig& config, std::unordered_map<std::string, std::string>& payload)
{
    if (config.isReportTid) {
        payload[SCRTID] = std::to_string(config.tid);
    }
}
}

using namespace Ressched;

thread_local bool ResSchedReport::isInSlide_ = false;
thread_local bool ResSchedReport::isInTouch_ = false;
thread_local Offset ResSchedReport::averageDistance_;

ResSchedReport& ResSchedReport::GetInstance()
{
    thread_local ResSchedReport instance;
    return instance;
}

ResSchedReport::ResSchedReport()
{
    reportDataFunc_ = LoadReportDataFunc();
    reportSyncEventFunc_ = LoadReportSyncEventFunc();
}

void ResSchedReport::TriggerModuleSerializer()
{
    if (triggerExecuted) {
        return;
    }
    auto curContainer = Container::Current();
    auto taskExecutor = curContainer->GetTaskExecutor();
    auto serializerTask = [weak = WeakPtr<Container>(curContainer)]() {
        auto container = weak.Upgrade();
        if (!container) {
            LOGW("container is null, serializerTask failed.");
            return;
        }
        container->TriggerModuleSerializer();
    };
    if (createPageCount == MODULE_SERIALIZER_COUNT) {
        taskExecutor->PostTask(serializerTask, TaskExecutor::TaskType::UI, "TriggerModuleSerializer");
        triggerExecuted = true;
        delayTask_.Cancel();
        return;
    }
    auto task = [taskExecutor, serializerTask]() {
        if (!triggerExecuted) {
            taskExecutor->PostTask(serializerTask, TaskExecutor::TaskType::UI, "TriggerModuleSerializer");
            triggerExecuted = true;
        }
    };
    delayTask_.Cancel();
    delayTask_.Reset(std::move(task));
    const uint32_t delay = 5000;
    taskExecutor->PostDelayedTask(delayTask_, TaskExecutor::TaskType::UI, delay, "TriggerModuleSerializer");
}

void ResSchedReport::ResSchedDataReport(const char* name, const std::unordered_map<std::string, std::string>& param)
{
    std::unordered_map<std::string, std::string> payload = param;
    payload[Ressched::NAME] = name;
    if (!reportDataFunc_) {
        reportDataFunc_ = LoadReportDataFunc();
    }
    if (!reportDataFunc_) {
        return;
    }
    static std::unordered_map<std::string, std::function<void(std::unordered_map<std::string, std::string>&)>>
        functionMap = {
            { CLICK,
                [this](std::unordered_map<std::string, std::string>& payload) {
                    reportDataFunc_(RES_TYPE_CLICK_RECOGNIZE, CLICK_EVENT, payload);
                }
            },
            { AUTO_PLAY_ON,
                [this](std::unordered_map<std::string, std::string>& payload) {
                    reportDataFunc_(RES_TYPE_SLIDE, AUTO_PLAY_ON_EVENT, payload);
                }
            },
            { AUTO_PLAY_OFF,
                [this](std::unordered_map<std::string, std::string>& payload) {
                    reportDataFunc_(RES_TYPE_SLIDE, AUTO_PLAY_OFF_EVENT, payload);
                }
            },
            { SLIDE_OFF,
                [this](std::unordered_map<std::string, std::string>& payload) {
                    reportDataFunc_(RES_TYPE_SLIDE, SLIDE_OFF_EVENT, payload);
                }
            },
            { POP_PAGE,
                [this](std::unordered_map<std::string, std::string>& payload) {
                    LoadAceApplicationContext(payload);
                    reportDataFunc_(RES_TYPE_POP_PAGE, POP_PAGE_EVENT, payload);
                }
            },
            { PAGE_END_FLUSH,
                [this](std::unordered_map<std::string, std::string>& payload) {
                    ResSchedReport::GetInstance().LoadPageEvent(ResDefine::LOAD_PAGE_NO_REQUEST_FRAME_EVENT);
                }
            },
            { WEB_GESTURE,
                [this](std::unordered_map<std::string, std::string>& payload) {
                    reportDataFunc_(RES_TYPE_WEB_GESTURE, 0, payload);
                }
            },
            { AXIS_OFF,
                [this](std::unordered_map<std::string, std::string>& payload) {
                    ResSchedReport::GetInstance().AxisEventReportEnd();
                }
            },
#ifdef FFRT_EXISTS
            { LONG_FRAME_START,
                [this](std::unordered_map<std::string, std::string>& payload) {
                    LoadAceApplicationContext(payload);
                    reportDataFunc_(RES_TYPE_LONG_FRAME, LONG_FRAME_START_EVENT, payload);
                }
            },
            { LONG_FRAME_END,
                [this](std::unordered_map<std::string, std::string>& payload) {
                    LoadAceApplicationContext(payload);
                    reportDataFunc_(RES_TYPE_LONG_FRAME, LONG_FRAME_END_EVENT, payload);
                }
            },
#endif
            { OVERLAY_ADD,
                [this](std::unordered_map<std::string, std::string>& payload) {
                    LoadAceApplicationContext(payload);
                    reportDataFunc_(RES_TYPE_OVERLAY, OVERLAY_ADD_EVENT, payload);
                }
            },
            { OVERLAY_REMOVE,
                [this](std::unordered_map<std::string, std::string>& payload) {
                    LoadAceApplicationContext(payload);
                    reportDataFunc_(RES_TYPE_OVERLAY, OVERLAY_REMOVE_EVENT, payload);
                }
            },
            { ABILITY_OR_PAGE_SWITCH_START,
                [this](std::unordered_map<std::string, std::string>& payload) {
                    LoadAceApplicationContext(payload);
                    reportDataFunc_(RES_TYPE_ABILITY_OR_PAGE_SWITCH, ABILITY_OR_PAGE_SWITCH_START_EVENT, payload);
                }
            },
            { ABILITY_OR_PAGE_SWITCH_END,
                [this](std::unordered_map<std::string, std::string>& payload) {
                    LoadAceApplicationContext(payload);
                    reportDataFunc_(RES_TYPE_ABILITY_OR_PAGE_SWITCH, ABILITY_OR_PAGE_SWITCH_END_EVENT, payload);
                }
            },
        };
    auto it = functionMap.find(name);
    if (it == functionMap.end()) {
        return;
    }
    it->second(payload);
}

void ResSchedReport::ResSchedDataReport(uint32_t resType, int32_t value,
    const std::unordered_map<std::string, std::string>& payload)
{
    if (!reportDataFunc_) {
        LOGD("reportDataFunc_ is null!");
        return;
    }
    reportDataFunc_(resType, value, payload);
}

void ResSchedReport::ResScheSyncEventReport(const uint32_t resType, const int64_t value,
    const std::unordered_map<std::string, std::string>& payload, std::unordered_map<std::string, std::string>& reply)
{
    if (!reportSyncEventFunc_) {
        LOGD("reportSyncEventFunc_ is null!");
        return;
    }
    reportSyncEventFunc_(resType, value, payload, reply);
}

bool ResSchedReport::AppWhiteListCheck(const std::unordered_map<std::string, std::string>& payload,
    std::unordered_map<std::string, std::string>& reply)
{
    ResScheSyncEventReport(RES_TYPE_CHECK_APP_IS_IN_SCHEDULE_LIST, 0, payload, reply);
    return reply["result"] == "\"true\"" ? true : false;
}

void ResSchedReport::OnTouchEvent(const TouchEvent& touchEvent, const ReportConfig& config)
{
    if (!triggerExecuted) {
        auto curContainer = Container::Current();
        auto taskExecutor = curContainer->GetTaskExecutor();
        auto serializerTask = [weak = WeakPtr<Container>(curContainer)]() {
            auto container = weak.Upgrade();
            if (!container) {
                LOGW("container is null, serializerTask failed.");
                return;
            }
            container->TriggerModuleSerializer();
        };
        taskExecutor->PostTask(serializerTask, TaskExecutor::TaskType::UI, "TriggerModuleSerializer");
        triggerExecuted = true;
    }
    switch (touchEvent.type) {
        case TouchType::DOWN:
            HandleTouchDown(touchEvent, config);
            break;
        case TouchType::UP:
            HandleTouchUp(touchEvent, config);
            break;
        case TouchType::MOVE:
            HandleTouchMove(touchEvent, config);
            break;
        case TouchType::CANCEL:
            HandleTouchCancel(touchEvent, config);
            break;
        case TouchType::PULL_DOWN:
            HandleTouchPullDown(touchEvent, config);
            break;
        case TouchType::PULL_UP:
            HandleTouchPullUp(touchEvent, config);
            break;
        case TouchType::PULL_MOVE:
            HandleTouchPullMove(touchEvent, config);
            break;
        default:
            break;
    }
}

bool ResSchedReport::IsRateLimit(int64_t maxCount, std::chrono::seconds durTime,
    int64_t& keyEventCount, std::chrono::steady_clock::time_point& startTime)
{
    if (keyEventCount == -1) {
        startTime = std::chrono::steady_clock::now();
        keyEventCount = 0;
    }

    if (keyEventCount > maxCount) {
        auto curTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(curTime - startTime).count();
        if (elapsedTime < durTime.count()) {
            LOGD("The event report exceeds the throttling limit");
            return true;
        }
        keyEventCount = 0;
        startTime = curTime;
    }
    keyEventCount++;
    return false;
}

bool ResSchedReport::IsPerSecRateLimit()
{
    int64_t maxCountMS = 10;
    auto durTimeMS = std::chrono::seconds(1);
    return IsRateLimit(maxCountMS, durTimeMS, keyEventCountMS, startTimeMS);
}

bool ResSchedReport::IsPerMinRateLimit()
{
    int64_t maxCountS = 180;
    auto durTimeS = std::chrono::seconds(60);
    return IsRateLimit(maxCountS, durTimeS, keyEventCountS, startTimeS);
}

void ResSchedReport::OnKeyEvent(const KeyEvent& event)
{
    if (IsPerSecRateLimit() || IsPerMinRateLimit()) {
        return;
    }
    switch (event.action) {
        case KeyAction::DOWN:
            HandleKeyDown(event);
            break;
        case KeyAction::UP:
            HandleKeyUp(event);
            break;
        default:
            break;
    }
}

void ResSchedReport::RecordTouchEvent(const TouchEvent& touchEvent, bool enforce)
{
    if (enforce) {
        lastTouchEvent_.timeStamp = touchEvent.GetTimeStamp();
        lastTouchEvent_.offset = touchEvent.GetOffset();
        curTouchEvent_.timeStamp = touchEvent.GetTimeStamp();
        curTouchEvent_.offset = touchEvent.GetOffset();
    } else if (curTouchEvent_.offset != touchEvent.GetOffset()) {
        lastTouchEvent_.timeStamp = curTouchEvent_.timeStamp;
        lastTouchEvent_.offset = curTouchEvent_.offset;
        curTouchEvent_.timeStamp = touchEvent.GetTimeStamp();
        curTouchEvent_.offset = touchEvent.GetOffset();
    }
}

void ResSchedReport::HandleTouchDown(const TouchEvent& touchEvent, const ReportConfig& config)
{
    std::unordered_map<std::string, std::string> payload;
    payload[Ressched::NAME] = TOUCH;
    LoadReportConfig(config, payload);
    ResSchedDataReport(RES_TYPE_CLICK_RECOGNIZE, TOUCH_DOWN_EVENT, payload);
    RecordTouchEvent(touchEvent, true);
    isInTouch_ = true;
}

void ResSchedReport::HandleKeyDown(const KeyEvent& event)
{
    std::unordered_map<std::string, std::string> payload;
    payload[Ressched::NAME] = KEY_EVENT;
    payload[KEY_CODE] = std::to_string(static_cast<int>(event.code));
    ResSchedDataReport(RES_TYPE_KEY_EVENT, KEY_DOWN_EVENT, payload);
}

void ResSchedReport::HandleTouchUp(const TouchEvent& touchEvent, const ReportConfig& config)
{
    std::unordered_map<std::string, std::string> payload;
    LoadReportConfig(config, payload);
    RecordTouchEvent(touchEvent);
    payload[Ressched::NAME] = TOUCH;
    payload[UP_SPEED_KEY] = std::to_string(GetUpVelocity(lastTouchEvent_, curTouchEvent_));
    LoadAceApplicationContext(payload);
    ResSchedDataReport(RES_TYPE_CLICK_RECOGNIZE, TOUCH_UP_EVENT, payload);
    isInSlide_ = false;
    isInTouch_ = false;
    averageDistance_.Reset();
}

void ResSchedReport::HandleKeyUp(const KeyEvent& event)
{
    std::unordered_map<std::string, std::string> payload;
    payload[Ressched::NAME] = KEY_EVENT;
    payload[KEY_CODE] = std::to_string(static_cast<int>(event.code));
    ResSchedDataReport(RES_TYPE_KEY_EVENT, KEY_UP_EVENT, payload);
}

void ResSchedReport::HandleTouchMove(const TouchEvent& touchEvent, const ReportConfig& config)
{
    RecordTouchEvent(touchEvent);
    averageDistance_ += curTouchEvent_.offset - lastTouchEvent_.offset;
    bool ret = averageDistance_.GetDistance() >= ResDefine::JUDGE_DISTANCE &&
        !isInSlide_ && isInTouch_;
    if (ret) {
        std::unordered_map<std::string, std::string> payload;
        LoadReportConfig(config, payload);
        LoadAceApplicationContext(payload);
        ResSchedDataReport(RES_TYPE_SLIDE, SLIDE_DETECTING, payload);
        isInSlide_ = true;
    }
    static uint64_t lastTime = 0;
    auto now = std::chrono::steady_clock::now();
    uint64_t curMs = static_cast<uint64_t>(
        std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count());
    if (isInSlide_ && curMs > lastTime && curMs - lastTime >= TIME_INTERVAL) {
        lastTime = curMs;
        std::unordered_map<std::string, std::string> payload;
        LoadAceApplicationContext(payload);
        ResSchedDataReport(RES_TYPE_SLIDE, MOVE_DETECTING, payload);
    }
}

void ResSchedReport::HandleTouchCancel(const TouchEvent& touchEvent, const ReportConfig& config)
{
    isInSlide_ = false;
    isInTouch_ = false;
    averageDistance_.Reset();
}

void ResSchedReport::HandleTouchPullDown(const TouchEvent& touchEvent, const ReportConfig& config)
{
    RecordTouchEvent(touchEvent, true);
    isInTouch_ = true;
}

void ResSchedReport::HandleTouchPullUp(const TouchEvent& touchEvent, const ReportConfig& config)
{
    std::unordered_map<std::string, std::string> payload;
    LoadReportConfig(config, payload);
    payload[Ressched::NAME] = TOUCH;
    ResSchedDataReport(RES_TYPE_CLICK_RECOGNIZE, TOUCH_PULL_UP_EVENT, payload);
    averageDistance_.Reset();
    isInTouch_ = false;
}

void ResSchedReport::HandleTouchPullMove(const TouchEvent& touchEvent, const ReportConfig& config)
{
    if (!isInSlide_) {
        std::unordered_map<std::string, std::string> payload;
        LoadReportConfig(config, payload);
        LoadAceApplicationContext(payload);
        ResSchedDataReport(RES_TYPE_SLIDE, SLIDE_DETECTING, payload);
        isInSlide_ = true;
    }
    RecordTouchEvent(touchEvent);
}

double ResSchedReport::GetUpVelocity(const ResEventInfo& lastMoveInfo,
    const ResEventInfo& upEventInfo)
{
    double distance = (upEventInfo.offset - lastMoveInfo.offset).GetDistance();
    int64_t time = std::chrono::duration_cast<std::chrono::milliseconds>(upEventInfo.timeStamp -
        lastMoveInfo.timeStamp).count();
    if (time <= 0) {
        return 0.0f;
    }
    return distance * dpi_ / static_cast<double>(time); //unit: pixel/ms
}

void ResSchedReport::LoadPageEvent(int32_t value)
{
    if (ACE_LIKELY((value == ResDefine::LOAD_PAGE_COMPLETE_EVENT && loadPageOn_ == false)
        || (value == ResDefine::LOAD_PAGE_NO_REQUEST_FRAME_EVENT && loadPageRequestFrameOn_ == false))) {
        return;
    } else if (value == ResDefine::LOAD_PAGE_COMPLETE_EVENT && loadPageOn_ == true) {
        loadPageOn_ = false;
    } else if (value == ResDefine::LOAD_PAGE_NO_REQUEST_FRAME_EVENT && loadPageRequestFrameOn_ == true) {
        loadPageRequestFrameOn_ = false;
    } else if (value == ResDefine::LOAD_PAGE_START_EVENT) {
        loadPageOn_ = true;
        loadPageRequestFrameOn_ = true;
    }

    std::unordered_map<std::string, std::string> payload;
    payload[Ressched::NAME] = LOAD_PAGE;
    LoadAceApplicationContext(payload);
    ResSchedDataReport(RES_TYPE_LOAD_PAGE, value, payload);
}

void ResSchedReport::HandleAxisBegin(const AxisEvent& axisEvent)
{
    RecordAxisEvent(axisEvent, true);
    std::unordered_map<std::string, std::string> payload;
    LoadAceApplicationContext(payload);
    ResSchedDataReport(RES_TYPE_SLIDE, SLIDE_DETECTING, payload);
}

void ResSchedReport::HandleAxisUpdate(const AxisEvent& axisEvent)
{
    RecordAxisEvent(axisEvent);
}

void ResSchedReport::HandleAxisEnd(const AxisEvent& axisEvent)
{
    RecordAxisEvent(axisEvent);
}

void ResSchedReport::RecordAxisEvent(const AxisEvent& axisEvent, bool enforce)
{
    if (enforce) {
        lastAxisEvent_.timeStamp = axisEvent.time;
        lastAxisEvent_.offset = axisEvent.ConvertToOffset();
        lastAxisEvent_.sourceTool = axisEvent.sourceTool;
        curAxisEvent_.timeStamp = axisEvent.time;
        curAxisEvent_.offset = axisEvent.ConvertToOffset();
        curAxisEvent_.sourceTool = axisEvent.sourceTool;
    } else if (axisEvent.ConvertToOffset().GetX() != 0 || axisEvent.ConvertToOffset().GetY() != 0) {
        lastAxisEvent_.timeStamp = curAxisEvent_.timeStamp;
        lastAxisEvent_.offset = curAxisEvent_.offset;
        lastAxisEvent_.sourceTool = curAxisEvent_.sourceTool;
        curAxisEvent_.timeStamp = axisEvent.time;
        curAxisEvent_.offset = axisEvent.ConvertToOffset();
        curAxisEvent_.sourceTool = axisEvent.sourceTool;
    }
}

double ResSchedReport::GetAxisUpVelocity(const ResEventInfo& lastAxisEvent, const ResEventInfo& curAxisEvent)
{
    double distance = curAxisEvent.offset.GetDistance();
    int64_t time = std::chrono::duration_cast<std::chrono::milliseconds>(curAxisEvent.timeStamp -
        lastAxisEvent.timeStamp).count();
    if (time <= 0) {
        return 0.0;
    }
    return distance * dpi_ / static_cast<double>(time); //unit: pixel/ms
}

void ResSchedReport::AxisEventReportEnd()
{
    std::unordered_map<std::string, std::string> payload;
    payload[Ressched::NAME] = TOUCH;
    if (curAxisEvent_.sourceTool != SourceTool::TOUCHPAD) {
        payload[UP_SPEED_KEY] = Ressched::AXIS_NORMAL_UP_SPEED;
        payload[AXIS_EVENT_TYPE] = AXIS_IS_MOUSE;
    } else {
        payload[UP_SPEED_KEY] = std::to_string(GetAxisUpVelocity(lastAxisEvent_, curAxisEvent_));
        payload[AXIS_EVENT_TYPE] = AXIS_IS_PAD;
    }
    ResSchedReport::GetInstance().ResSchedDataReport(Ressched::RES_TYPE_AXIS_EVENT, Ressched::AXIS_OFF_EVENT, payload);
}

void ResSchedReport::OnAxisEvent(const AxisEvent& axisEvent)
{
    switch (axisEvent.action) {
        case AxisAction::BEGIN:
            HandleAxisBegin(axisEvent);
            break;
        case AxisAction::UPDATE:
            HandleAxisUpdate(axisEvent);
            break;
        case AxisAction::END:
            HandleAxisEnd(axisEvent);
            break;
        default:
            break;
    }
}

void ResSchedReport::HandlePageTransition(const std::string& fromPage,
    const std::string& toPage, const std::string& mode)
{
    if (fromPage.empty() && toPage.empty()) {
        TAG_LOGD(AceLogTag::ACE_ROUTER, "rss report page transition empty info:%{public}s, %{public}s",
            fromPage.c_str(), toPage.c_str());
        return;
    }
    std::unordered_map<std::string, std::string> payload;
    payload[FROM_PAGE_INFO] = fromPage;
    payload[TO_PAGE_INFO] = toPage;
    payload[TRANSITION_MODE] = mode;
    LoadAceApplicationContext(payload);
    ResSchedDataReport(RES_TYPE_PAGE_TRANSITION, 0, payload);
}

ResSchedReportScope::ResSchedReportScope(const std::string& name,
    const std::unordered_map<std::string, std::string>& param) : name_(name), payload_(param)
{
    name_ = name;
    payload_[Ressched::NAME] = name;
    LoadAceApplicationContext(payload_);
    if (name_ == PUSH_PAGE) {
        ResSchedReport::GetInstance().ResSchedDataReport(RES_TYPE_PUSH_PAGE, PUSH_PAGE_START_EVENT, payload_);
        ResSchedReport::GetInstance().LoadPageEvent(ResDefine::LOAD_PAGE_START_EVENT);
    }
}

ResSchedReportScope::~ResSchedReportScope()
{
    if (!ResSchedReport::triggerExecuted) {
        ResSchedReport::createPageCount++;
        ResSchedReport::GetInstance().TriggerModuleSerializer();
    }
    if (name_ == PUSH_PAGE) {
        ResSchedReport::GetInstance().ResSchedDataReport(RES_TYPE_PUSH_PAGE, PUSH_PAGE_COMPLETE_EVENT, payload_);
    }
}
} // namespace OHOS::Ace
