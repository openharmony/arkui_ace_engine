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
#include<cmath>

#include "core/common/ace_application_info.h"
#include "base/log/log.h"
#include "base/ressched/ressched_report.h"

#define LIKELY(x) __builtin_expect(!!(x), 1)

namespace OHOS::Ace {
namespace {
constexpr uint32_t RES_TYPE_CLICK_RECOGNIZE = 9;
constexpr uint32_t RES_TYPE_PUSH_PAGE       = 10;
constexpr uint32_t RES_TYPE_SLIDE           = 11;
constexpr uint32_t RES_TYPE_POP_PAGE        = 28;
constexpr uint32_t RES_TYPE_WEB_GESTURE     = 29;
constexpr uint32_t RES_TYPE_LOAD_PAGE       = 34;
#ifdef FFRT_EXISTS
constexpr uint32_t RES_TYPE_LONG_FRAME     = 71;
#endif
constexpr int32_t TOUCH_DOWN_EVENT          = 1;
constexpr int32_t CLICK_EVENT               = 2;
constexpr int32_t TOUCH_UP_EVENT            = 3;
constexpr int32_t TOUCH_PULL_UP_EVENT = 4;
constexpr int32_t SLIDE_DETECTING = 2;
constexpr int32_t SECOND_UNIT = 1000;
constexpr int32_t DISTANCE_UNIT = 1000 * 1000;
constexpr int32_t SLIDE_OFF_EVENT = 0;
constexpr int32_t SLIDE_ON_EVENT = 1;
constexpr int32_t AUTO_PLAY_ON_EVENT = 5;
constexpr int32_t AUTO_PLAY_OFF_EVENT = 6;
constexpr int32_t PUSH_PAGE_START_EVENT = 0;
constexpr int32_t PUSH_PAGE_COMPLETE_EVENT = 1;
constexpr int32_t POP_PAGE_EVENT = 0;
#ifdef FFRT_EXISTS
constexpr int32_t LONG_FRAME_START_EVENT = 0;
constexpr int32_t LONG_FRAME_END_EVENT = 1;
#endif
constexpr char NAME[] = "name";
constexpr char PID[] = "pid";
constexpr char UID[] = "uid";
constexpr char BUNDLE_NAME[] = "bundleName";
constexpr char ABILITY_NAME[] = "abilityName";
constexpr char CLICK[] = "click";
constexpr char PUSH_PAGE[] = "push_page";
constexpr char POP_PAGE[] = "pop_page";
constexpr char SLIDE_ON[] = "slide_on";
constexpr char SLIDE_OFF[] = "slide_off";
constexpr char AUTO_PLAY_ON[] = "auto_play_on";
constexpr char AUTO_PLAY_OFF[] = "auto_play_off";
constexpr char TOUCH[] = "touch";
constexpr char WEB_GESTURE[] = "web_gesture";
constexpr char LOAD_PAGE[] = "load_page";
constexpr char UP_SPEED_KEY[] = "up_speed";
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
}

ResSchedReport& ResSchedReport::GetInstance()
{
    static ResSchedReport instance;
    return instance;
}

void ResSchedReport::ResSchedDataReport(const char* name, const std::unordered_map<std::string, std::string>& param)
{
    std::unordered_map<std::string, std::string> payload = param;
    payload[NAME] = name;
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
            { POP_PAGE,
                [this](std::unordered_map<std::string, std::string>& payload) {
                    LoadAceApplicationContext(payload);
                    reportDataFunc_(RES_TYPE_POP_PAGE, POP_PAGE_EVENT, payload);
                }
            },
            { WEB_GESTURE,
                [this](std::unordered_map<std::string, std::string>& payload) {
                    reportDataFunc_(RES_TYPE_WEB_GESTURE, 0, payload);
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
    if (reportDataFunc_ == nullptr) {
        reportDataFunc_ = LoadReportDataFunc();
    }
    if (reportDataFunc_ != nullptr) {
        reportDataFunc_(resType, value, payload);
    }
}

void ResSchedReport::OnTouchEvent(const TouchEvent& touchEvent)
{
    switch(touchEvent.type) {
        case TouchType::DOWN:
            HandleTouchDown(touchEvent);
            break;
        case TouchType::UP:
            HandleTouchUp(touchEvent);
            break;
        case TouchType::MOVE:
            HandleTouchMove(touchEvent);
            break;
        case TouchType::CANCEL:
            HandleTouchCancel(touchEvent);
            break;
        case TouchType::PULL_DOWN:
            HandleTouchPullDown(touchEvent);
            break;
        case TouchType::PULL_UP:
            HandleTouchPullUp(touchEvent);
            break;
        case TouchType::PULL_MOVE:
            HandleTouchPullMove(touchEvent);
            break;
        default:
            break;
    }
}

void ResSchedReport::HandleTouchDown(const TouchEvent& touchEvent)
{
    std::unordered_map<std::string, std::string> payload;
    payload[NAME] = TOUCH;
    ResSchedDataReport(RES_TYPE_CLICK_RECOGNIZE, TOUCH_DOWN_EVENT, payload);
    touchPoints_[touchEvent.id] = touchEvent;
    currentFingers_ ++;
}

void ResSchedReport::HandleTouchUp(const TouchEvent& touchEvent)
{
    std::unordered_map<std::string, std::string> payload;
    payload[NAME] = TOUCH;
    payload[UP_SPEED_KEY] = std::to_string(GetUpVelocity(touchPoints_[touchEvent.id], touchEvent));
    ResSchedDataReport(RES_TYPE_CLICK_RECOGNIZE, TOUCH_UP_EVENT, payload);
    touchPoints_.erase(touchEvent.id);
    currentFingers_ = currentFingers_ > 0 ? currentFingers_ - 1 : 0;
    if (currentFingers_ == 0) {
        isInSilde = false;
        averageDistance_.Reset();
    }
}

void ResSchedReport::HandleTouchMove(const TouchEvent& touchEvent)
{
    int32_t id = touchEvent.id;
    auto offsetCurrent = Offset(touchEvent.GetOffset().GetX(), touchEvent.GetOffset().GetY());
    auto offsetPre = Offset(touchPoints_[id].GetOffset().GetX(), touchPoints_[id].GetOffset().GetY());
    averageDistance_ += (offsetCurrent - offsetPre) / touchPoints_.size();
    if (averageDistance_.GetDistance() >= ResDefine::JUDGE_DISTANCE && !isInSilde) {
        std::unordered_map<std::string, std::string> payload;
        LoadAceApplicationContext(payload);
        reportDataFunc_(RES_TYPE_SLIDE, SLIDE_DETECTING, payload);
        isInSilde = true;
    }
}

void ResSchedReport::HandleTouchCancel(const TouchEvent& touchEvent)
{
    currentFingers_ = currentFingers_ > 0 ? currentFingers_ - 1 : 0;
    touchPoints_.erase(touchEvent.id);
}

void ResSchedReport::HandleTouchPullDown(const TouchEvent& touchEvent)
{
    currentFingers_ ++;
    touchPoints_[touchEvent.id] = touchEvent;
}

void ResSchedReport::HandleTouchPullUp(const TouchEvent& touchEvent)
{
    std::unordered_map<std::string, std::string> payload;
    payload[NAME] = TOUCH;
    ResSchedDataReport(RES_TYPE_CLICK_RECOGNIZE, TOUCH_PULL_UP_EVENT, payload);
    currentFingers_ = currentFingers_ > 0 ? currentFingers_ - 1 : 0;
    touchPoints_.erase(touchEvent.id);
    averageDistance_.Reset();
}

void ResSchedReport::HandleTouchPullMove(const TouchEvent& touchEvent)
{
    if (!isInSilde) {
        std::unordered_map<std::string, std::string> payload;
        LoadAceApplicationContext(payload);
        reportDataFunc_(RES_TYPE_SLIDE, SLIDE_DETECTING, payload);
        isInSilde = true;
    }
}

float ResSchedReport::GetUpVelocity(const TouchEvent& lastMoveInfo,
    const TouchEvent& upEventInfo)
{
    float distance = sqrt(pow(lastMoveInfo.x - upEventInfo.x, SQUARE) + pow(lastMoveInfo.y - upEventInfo.y, SQUARE));
    int64_t time = abs(lastMoveInfo.GetTimeStamp().time_since_epoch().count() -
        upEventInfoGet.TimeStamp().time_since_epoch().count());
    if (time < SECOND_UNIT) {
        return 0.0f;
    }
    return distance * DISTANCE_UNIT / (time / SECOND_UNIT); //unit: pixel/ms
}

void ResSchedReport::LoadPageEvent(int32_t value)
{
    if (LIKELY(value == ResDefine::LOAD_PAGE_COMPLETE_EVENT && loadPageOn_ == false)) {
        return;
    } else if (value == ResDefine::LOAD_PAGE_COMPLETE_EVENT && loadPageOn_ == true) {
        loadPageOn_ = false;
    } else if (value == ResDefine::LOAD_PAGE_START_EVENT) {
        loadPageOn_ = true;
    }

    std::unordered_map<std::string, std::string> payload;
    payload[NAME] = LOAD_PAGE;
    LoadAceApplicationContext(payload);
    ResSchedDataReport(RES_TYPE_LOAD_PAGE, value, payload);
}

ResSchedReportScope::ResSchedReportScope(const std::string& name,
    const std::unordered_map<std::string, std::string>& param) : name_(name), payload_(param)
{
    name_ = name;
    payload_[NAME] = name;
    LoadAceApplicationContext(payload_);
    if (name_ == PUSH_PAGE) {
        ResSchedReport::GetInstance().ResSchedDataReport(RES_TYPE_PUSH_PAGE, PUSH_PAGE_START_EVENT, payload_);
        ResSchedReport::GetInstance().LoadPageEvent(ResDefine::LOAD_PAGE_START_EVENT);
    }
}

ResSchedReportScope::~ResSchedReportScope()
{
    if (name_ == PUSH_PAGE) {
        ResSchedReport::GetInstance().ResSchedDataReport(RES_TYPE_PUSH_PAGE, PUSH_PAGE_COMPLETE_EVENT, payload_);
    }
}
} // namespace OHOS::Ace
