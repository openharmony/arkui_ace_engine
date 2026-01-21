/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/swiper/swiper_ui_session_adapter.h"

#include "interfaces/inner_api/ui_session/ui_session_manager.h"

namespace OHOS::Ace::NG {
constexpr char SWIPER_COMMAND_CHANGE[] = "change";
constexpr char SWIPER_COMMAND_FORWARD[] = "forward";
constexpr char SWIPER_COMMAND_BACKWARD[] = "backward";
constexpr char SWIPER_COMMAND_INDEX[] = "index";
constexpr char SWIPER_SCROLL_DIRECTION_FORWARD[] = "forward";
constexpr char SWIPER_SCROLL_DIRECTION_BACKWARD[] = "backward";
constexpr char SWIPER_SCROLL_DIRECTION_BIDIRECTIONAL[] = "bidirectional";
constexpr char SWIPER_SCROLL_DIRECTION_UNABLE[] = "unable";

SwiperCommand SwiperUISessionAdapter::ParseCommand(const std::string& command)
{
    auto json = JsonUtil::ParseJsonString(command);
    if (json->IsNull()) {
        return SwiperCommand::INVALID;
    }

    auto cmdType = json->GetString("cmd");
    if (cmdType != SWIPER_COMMAND_CHANGE) {
        return SwiperCommand::INVALID;
    }

    auto paramObj = json->GetObject("params");
    if (!paramObj || !paramObj->Contains("type") || !paramObj->GetValue("type")->IsString()) {
        return SwiperCommand::INVALID;
    }

    auto changeType = paramObj->GetString("type");
    if (strcmp(changeType.c_str(), SWIPER_COMMAND_FORWARD) == 0) {
        return SwiperCommand::FORWARD;
    }

    if (strcmp(changeType.c_str(), SWIPER_COMMAND_BACKWARD) == 0) {
        return SwiperCommand::BACKWARD;
    }

    if (strcmp(changeType.c_str(), SWIPER_COMMAND_INDEX) == 0) {
        return SwiperCommand::INDEX;
    }

    return SwiperCommand::INVALID;
}

int32_t SwiperUISessionAdapter::ParseIndexFromCommand(const std::string& command)
{
    auto json = JsonUtil::ParseJsonString(command);
    auto paramObj = json->GetObject("params");
    int32_t defaultErr = -1;
    if (!paramObj->Contains("index") || !paramObj->GetValue("index")->IsString()) {
        return defaultErr;
    }

    auto originIndex = paramObj->GetString("index");
    if (!StringUtils::IsNumber(originIndex)) {
        return defaultErr;
    }

    return StringUtils::StringToInt(originIndex, defaultErr);
}

int32_t SwiperUISessionAdapter::OnInjectionEvent(const std::string& command)
{
    CHECK_NULL_RETURN(pattern_, RET_FAILED);
    auto scrollAbility = GetScrollAbility();
    if (strcmp(scrollAbility, SWIPER_SCROLL_DIRECTION_UNABLE) == 0) {
        return RET_FAILED;
    }

    int32_t totalCount = pattern_->TotalCount();
    auto commandType = ParseCommand(command);
    switch (commandType) {
        case SwiperCommand::FORWARD: {
            if (scrollAbility == SWIPER_SCROLL_DIRECTION_BACKWARD) {
                ReportComponentChangeEvent(false, commandType);
                return RET_FAILED;
            }
            pattern_->ShowNext();
            break;
        }
        case SwiperCommand::BACKWARD: {
            if (scrollAbility == SWIPER_SCROLL_DIRECTION_FORWARD) {
                ReportComponentChangeEvent(false, commandType);
                return RET_FAILED;
            }

            if (pattern_->IsAutoLinear() && static_cast<int32_t>(pattern_->itemPosition_.size()) == totalCount) {
                pattern_->ChangeIndex(0, true);
            } else {
                pattern_->ShowPrevious();
            }
            break;
        }
        case SwiperCommand::INDEX: {
            int32_t index = ParseIndexFromCommand(command);
            if (index < 0 || index >= totalCount) {
                ReportComponentChangeEvent(false, commandType);
                return RET_FAILED;
            }
            pattern_->ChangeIndex(index, true);
            break;
        }
        default: {
            ReportComponentChangeEvent(false, commandType);
            return RET_FAILED;
        }
    }
    ReportComponentChangeEvent(true, commandType);
    return RET_SUCCESS;
}

void SwiperUISessionAdapter::ReportComponentChangeEvent(bool result, SwiperCommand type)
{
    auto json = JsonUtil::Create();
    switch (type) {
        case SwiperCommand::FORWARD: {
            json->Put("event", "forward");
            if (result) {
                json->Put("result", "success");
            } else {
                json->Put("result", "fail");
                json->Put("reason", "ForwardEnd");
            }
            break;
        }
        case SwiperCommand::BACKWARD: {
            json->Put("event", "backward");
            if (result) {
                json->Put("result", "success");
            } else {
                json->Put("result", "fail");
                json->Put("reason", "BackwardHead");
            }
            break;
        }
        case SwiperCommand::INDEX: {
            json->Put("event", "index");
            if (result) {
                json->Put("result", "success");
            } else {
                json->Put("result", "fail");
                json->Put("reason", "InvalidIndex");
            }
            break;
        }
        default: {
            json->Put("event", "change");
            json->Put("result", "fail");
            json->Put("reason", "InvalidCommand");
        }
    }
    UiSessionManager::GetInstance()->ReportComponentChangeEvent("swiperResult", json->ToString().c_str(),
        ComponentEventType::COMPONENT_EVENT_SWIPER);
}

const char* SwiperUISessionAdapter::GetScrollAbility()
{
    CHECK_NULL_RETURN(pattern_, SWIPER_SCROLL_DIRECTION_UNABLE);
    int32_t totalCount = pattern_->TotalCount();
    bool isLoop = pattern_->IsLoop();
    if (pattern_->IsDisableSwipe() || pattern_->IsVisibleChildrenSizeLessThanSwiper() || totalCount <= 1) {
        return SWIPER_SCROLL_DIRECTION_UNABLE;
    }

    if (pattern_->IsAutoLinear()) {
        bool isAtStart = pattern_->IsAtStart();
        bool isAtEnd = pattern_->IsAtEnd();
        if (isAtStart && isAtEnd) {
            return SWIPER_SCROLL_DIRECTION_UNABLE;
        }

        if (isLoop && pattern_->AutoLinearIsOutOfBoundary(0.0f)) {
            return SWIPER_SCROLL_DIRECTION_UNABLE;
        }

        // In Auto-Linear mode, when the Swiper scrolls to the end and makes all child elements visible with only the
        // first element displayed partly, it can scroll back to the head but showPrevious function is no effect.
        if (isLoop && static_cast<int32_t>(pattern_->itemPosition_.size()) == totalCount) {
            return SWIPER_SCROLL_DIRECTION_FORWARD;
        }

        if (!isLoop && isAtStart) {
            return SWIPER_SCROLL_DIRECTION_FORWARD;
        } else if (!isLoop && (isAtEnd || pattern_->currentIndex_ == totalCount - 1)) {
            return SWIPER_SCROLL_DIRECTION_BACKWARD;
        } else {
            return SWIPER_SCROLL_DIRECTION_BIDIRECTIONAL;
        }
    }

    auto displayCount = pattern_->GetDisplayCount();
    if (!isLoop && pattern_->currentIndex_ == 0) {
        return SWIPER_SCROLL_DIRECTION_FORWARD;
    } else if (!isLoop && pattern_->currentIndex_ >= totalCount - displayCount) {
        return SWIPER_SCROLL_DIRECTION_BACKWARD;
    } else {
        return SWIPER_SCROLL_DIRECTION_BIDIRECTIONAL;
    }
}
} // namespace OHOS::Ace::NG