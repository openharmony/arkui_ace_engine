/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_RECORDER_EVENT_RECORDER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_RECORDER_EVENT_RECORDER_H

#include <string>
#include <unordered_map>

#include "base/thread/task_executor.h"
#include "base/utils/noncopyable.h"
#include "core/common/recorder/event_config.h"

namespace OHOS::Ace::Recorder {
enum EventType : int32_t {
    INVALID = 0,
    PAGE_SHOW,
    PAGE_HIDE,
    CLICK,
    LONG_PRESS,
    CHANGE,
    EXPOSURE,
    NAVIGATOR,
    REFRESH,
    STEPPER_FINISH,
    STEPPER_SKIP,
    STEPPER_NEXT,
    STEPPER_PREVIOUS,
    SEARCH_SUBMIT,
    WEB_PAGE_BEGIN,
    WEB_PAGE_END,
    VIDEO_START,
    VIDEO_PAUSE,
    VIDEO_FINISH,
    VIDEO_ERROR,
    VIDEO_PREPARED,
    VIDEO_SEEKED,
    VIDEO_SCREEN_CHANGE,
    VIDEO_STOP,
    DIALOG_SHOW,
    DIALOG_CANCEL,
    DIALOG_ACTION,
    DIALOG_SELECT,
    DIALOG_ACCEPT,
};

enum PageEventType: int32_t {
    ROUTER_PAGE = 0,
    NAV_PAGE,
};

struct EventSwitch {
    bool pageEnable = true;
    bool exposureEnable = false;
    bool componentEnable = false;
    bool pageParamEnable = false;
};

constexpr char KEY_ID[] = "id";
constexpr char KEY_TYPE[] = "type";
constexpr char KEY_NAV_DST[] = "navDst";
constexpr char KEY_PAGE[] = "page";
constexpr char KEY_DESCRIPTION[] = "description";
constexpr char KEY_PAGE_PARAM[] = "pageParam";
constexpr char KEY_DURATION[] = "duration";
constexpr char KEY_TEXT[] = "text";
constexpr char KEY_CHECKED[] = "checked";
constexpr char KEY_INDEX[] = "index";
constexpr char KEY_TEXT_ARRAY[] = "textArray";
constexpr char KEY_TITLE[] = "title";
constexpr char KEY_SUB_TITLE[] = "subtitle";
constexpr char KEY_NAV_PAGE[] = "navPage";
constexpr char KEY_NAV_PAGE_TYPE[] = "navType";
constexpr char KEY_NAV_PAGE_PARAM[] = "navPageParam";

ACE_FORCE_EXPORT bool IsCacheAvaliable();

class ACE_FORCE_EXPORT EventParamsBuilder {
public:
    EventParamsBuilder();

    ~EventParamsBuilder() = default;

    EventParamsBuilder& SetEventType(EventType eventType);

    EventParamsBuilder& SetId(const std::string& id);

    EventParamsBuilder& SetType(const std::string& type);

    EventParamsBuilder& SetDescription(const std::string& desc);

    EventParamsBuilder& SetNavDst(const std::string& dstName);

    EventParamsBuilder& SetPageUrl(const std::string& pageUrl);

    EventParamsBuilder& SetText(const std::string& value);

    EventParamsBuilder& SetChecked(bool value);

    EventParamsBuilder& SetIndex(int value);

    EventParamsBuilder& SetTextArray(const std::vector<std::string>& value);

    EventParamsBuilder& SetExtra(const std::string& key, const std::string& value);

    std::shared_ptr<std::unordered_map<std::string, std::string>> build();

    EventType GetEventType() const;

    std::string GetText() const;

    std::string ToString() const;

private:
    std::shared_ptr<std::unordered_map<std::string, std::string>> params_;
    EventType eventType_ = EventType::INVALID;
};

std::string MapToString(const std::shared_ptr<std::unordered_map<std::string, std::string>>& input);

class ACE_FORCE_EXPORT EventRecorder final {
public:
    static EventRecorder& Get();

    bool IsPageRecordEnable() const;
    bool IsPageParamRecordEnable() const;
    bool IsExposureRecordEnable() const;
    bool IsComponentRecordEnable() const;
    void UpdateEventSwitch(const EventSwitch& eventSwitch);

    void SetContainerChanged()
    {
        isFocusContainerChanged_ = true;
    }

    void SetContainerInfo(const std::string& windowName, int32_t id, bool foreground);
    void SetFocusContainerInfo(const std::string& windowName, int32_t id);
    int32_t GetContainerId();
    const std::string& GetPageUrl();
    const std::string& GetNavDstName() const;

    void OnPageShow(const std::string& pageUrl, const std::string& param);
    void OnPageHide(const std::string& pageUrl, const int64_t duration);
    void OnClick(EventParamsBuilder&& builder);
    void OnChange(EventParamsBuilder&& builder);
    void OnEvent(EventParamsBuilder&& builder);
    void OnNavDstShow(EventParamsBuilder&& builder);
    void OnNavDstHide(EventParamsBuilder&& builder);
    void OnExposure(EventParamsBuilder&& builder);

private:
    EventRecorder();
    ~EventRecorder() = default;
    friend class EventConfig;

    EventSwitch eventSwitch_;

    bool pageEnable_ = true;
    bool pageParamEnable_ = false;
    bool componentEnable_ = true;
    bool exposureEnable_ = true;

    int32_t containerId_ = -1;
    int32_t focusContainerId_ = -1;
    int32_t containerCount_ = 0;

    std::string pageUrl_;
    std::string navDstName_;
    int64_t navShowTime_ = -1;
    bool isFocusContainerChanged_ = false;

    RefPtr<TaskExecutor> taskExecutor_;

    ACE_DISALLOW_COPY_AND_MOVE(EventRecorder);
};
} // namespace OHOS::Ace::Recorder
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_RECORDER_EVENT_RECORDER_H
