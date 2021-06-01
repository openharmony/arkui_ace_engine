/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/common/dom/dom_image_animator.h"

#include "base/log/event_report.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::Framework {
namespace {

constexpr int32_t MS_TO_S = 1000;
const char* STATE_PLAYING = "playing";
const char* STATE_PAUSED = "paused";
const char* STATE_STOPPED = "stopped";
const char* ITERATIONS_INFINITE = "infinite";

} // namespace

DOMImageAnimator::DOMImageAnimator(NodeId nodeId, const std::string& nodeName) : DOMNode(nodeId, nodeName)
{
    imageAnimator_ = AceType::MakeRefPtr<ImageAnimatorComponent>(nodeName);
    controller_ = AceType::MakeRefPtr<Animator>();
    controller_->SetFillMode(FillMode::FORWARDS);
    imageAnimator_->SetAnimator(controller_);
}

bool DOMImageAnimator::SetSpecializedAttr(const std::pair<std::string, std::string>& attr)
{
    if (attr.first == DOM_ITERATION) {
        if (attr.second == ITERATIONS_INFINITE) {
            iteration_ = ANIMATION_REPEAT_INFINITE;
        } else {
            iteration_ = StringToInt(attr.second);
        }
        return true;
    }
    if (attr.first == DOM_PREDECODE) {
        preDecode_ = StringToInt(attr.second);
        return true;
    }
    if (attr.first == DOM_DURATION) {
        auto val = attr.second;
        if (val.find("ms") != std::string::npos) {
            duration_ = StringToInt(val);
        } else if (val.find('s') != std::string::npos) {
            duration_ = StringToInt(val) * MS_TO_S;
        } else {
            duration_ = StringToInt(val);
        }
        return true;
    }
    if (attr.first == DOM_FIXEDSIZE) {
        fixedSize_ = StringToBool(attr.second);
        return true;
    }
    if (attr.first == DOM_REVERSE) {
        isReverse_ = StringToBool(attr.second);
        return true;
    }
    if (attr.first == DOM_FILLMODE) {
        if (controller_) {
            controller_->SetFillMode(StringToFillMode(attr.second));
        }
        return true;
    }
    return false;
}

bool DOMImageAnimator::AddSpecializedEvent(int32_t pageId, const std::string& event)
{
    EventMarker eventMarker(GetNodeIdForEvent(), event, pageId);
    auto weakContext = pipelineContext_;
    if (event == DOM_IMAGE_ANIMATOR_START) {
        controller_->ClearStartListeners();
        controller_->AddStartListener([eventMarker, weakContext] {
            auto context = weakContext.Upgrade();
            if (!context) {
                LOGE("Start event: Context is null");
                return;
            }
            AceAsyncEvent<void()>::Create(eventMarker, context)();
        });
        return true;
    } else if (event == DOM_IMAGE_ANIMATOR_STOP) {
        controller_->ClearStopListeners();
        controller_->AddStopListener([eventMarker, weakContext] {
            auto context = weakContext.Upgrade();
            if (!context) {
                LOGE("Stop event: Context is null");
                return;
            }
            AceAsyncEvent<void()>::Create(eventMarker, context)();
        });
        return true;
    } else if (event == DOM_IMAGE_ANIMATOR_PAUSE) {
        controller_->ClearPauseListeners();
        controller_->AddPauseListener([eventMarker, weakContext] {
            auto context = weakContext.Upgrade();
            if (!context) {
                LOGE("Pause event: Context is null");
                return;
            }
            AceAsyncEvent<void()>::Create(eventMarker, context)();
        });
        return true;
    } else if (event == DOM_IMAGE_ANIMATOR_RESUME) {
        controller_->ClearResumeListeners();
        controller_->AddResumeListener([eventMarker, weakContext] {
            auto context = weakContext.Upgrade();
            if (!context) {
                LOGE("Resume event: Context is null");
                return;
            }
            AceAsyncEvent<void()>::Create(eventMarker, context)();
        });
        return true;
    } else {
        return false;
    }
}

void DOMImageAnimator::CallSpecializedMethod(const std::string& method, const std::string& args)
{
    if (!controller_) {
        LOGE("The controller is not created.");
        return;
    }
    auto nodeId = GetNodeId();
    if (method == DOM_IMAGE_ANIMATOR_START) {
        LOGI("JS call Start method, nodeId: %{public}d", nodeId);
        if (isReverse_) {
            controller_->Backward();
        } else {
            controller_->Forward();
        }
    } else if (method == DOM_IMAGE_ANIMATOR_STOP) {
        LOGI("JS call Stop method, nodeId: %{public}d", nodeId);
        controller_->Finish();
    } else if (method == DOM_IMAGE_ANIMATOR_PAUSE) {
        LOGI("JS call Pause method, nodeId: %{public}d", nodeId);
        controller_->Pause();
    } else if (method == DOM_IMAGE_ANIMATOR_RESUME) {
        LOGI("JS call Resume method, nodeId: %{public}d", nodeId);
        controller_->Resume();
    } else {
        LOGE("Do not support this method: %{public}s, nodeId: %{public}d.", method.c_str(), nodeId);
        EventReport::SendComponentException(ComponentExcepType::IMAGE_ANIMATOR_ERR);
    }
}

const char* DOMImageAnimator::GetState() const
{
    if (!controller_) {
        LOGE("The controller is not created.");
        return "";
    }
    auto currentStatus = controller_->GetStatus();
    if (currentStatus == Animator::Status::PAUSED) {
        return STATE_PAUSED;
    } else if (currentStatus == Animator::Status::RUNNING) {
        return STATE_PLAYING;
    } else {
        // IDLE and STOP
        return STATE_STOPPED;
    }
};

void DOMImageAnimator::PrepareSpecializedComponent()
{
    if (!imageAnimator_) {
        LOGE("The imageAnimator is not created.");
        EventReport::SendComponentException(ComponentExcepType::IMAGE_ANIMATOR_ERR);
        return;
    }
    if (border_.HasRadius()) {
        imageAnimator_->SetBorder(border_);
    }
    imageAnimator_->SetDuration(duration_);
    imageAnimator_->SetIteration(iteration_);
    imageAnimator_->SetIsReverse(isReverse_);
    imageAnimator_->SetImageProperties(imagesAttr_);
    imageAnimator_->SetIsFixedSize(fixedSize_);
    imageAnimator_->SetPreDecode(preDecode_);
}

} // namespace OHOS::Ace::Framework
