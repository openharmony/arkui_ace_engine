/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"

namespace OHOS::Ace::NG {

using TextChangeEvent = std::function<void(const std::vector<std::string>&, const std::vector<double>&)>;
using TextValueChangeEvent = std::function<void(const std::vector<std::string>&)>;
using TextSelectedChangeEvent = std::function<void(const std::vector<double>&)>;
using DialogTextEvent = std::function<void(const std::string&)>;
using DialogCancelEvent = std::function<void()>;
using DialogGestureEvent = std::function<void(const GestureEvent& info)>;

class TextPickerEventHub : public EventHub {
    DECLARE_ACE_TYPE(TextPickerEventHub, EventHub)

public:
    TextPickerEventHub() = default;
    ~TextPickerEventHub() override = default;

    void SetOnChange(TextChangeEvent&& TextChangeEvent)
    {
        TextChangeEvent_ = std::move(TextChangeEvent);
    }

    void FireChangeEvent(const std::vector<std::string>& value, const std::vector<double>& index) const
    {
        if (onValueChangeEvent_) {
            onValueChangeEvent_(value);
        }
        if (onSelectedChangeEvent_) {
            onSelectedChangeEvent_(index);
        }
        if (TextChangeEvent_) {
            TextChangeEvent_(value, index);
        }
    }

    void SetOnScrollStop(TextChangeEvent&& onScrollStopEvent)
    {
        onScrollStopEvent_ = std::move(onScrollStopEvent);
    }

    void FireScrollStopEvent(const std::vector<std::string>& value, const std::vector<double>& index) const
    {
        if (onScrollStopEvent_) {
            onScrollStopEvent_(value, index);
        }
    }

    void SetOnEnterSelectedArea(TextChangeEvent&& onEnterSelectedArea)
    {
        onEnterSelectedAreaEvent_ = std::move(onEnterSelectedArea);
    }

    void FireEnterSelectedAreaEvent(const std::vector<std::string>& value, const std::vector<double>& index) const
    {
        if (onEnterSelectedAreaEvent_) {
            onEnterSelectedAreaEvent_(value, index);
        }
    }

    void SetDialogChange(DialogTextEvent&& onChange)
    {
        DialogChangeEvent_ = std::move(onChange);
    }

    void FireDialogChangeEvent(const std::string& info) const
    {
        if (DialogChangeEvent_) {
            DialogChangeEvent_(info);
        }
    }

    void SetDialogScrollStop(DialogTextEvent&& onScrollStopEvent)
    {
        dialogScrollStopEvent_ = std::move(onScrollStopEvent);
    }

    void FireDialogScrollStopEvent(const std::string& info) const
    {
        if (dialogScrollStopEvent_) {
            dialogScrollStopEvent_(info);
        }
    }

    void SetDialogEnterSelectedArea(DialogTextEvent&& onEnterSelectedAreaEvent)
    {
        dialogEnterSelectedAreaEvent_ = std::move(onEnterSelectedAreaEvent);
    }

    void FireDialogEnterSelectedAreaEvent(const std::string& info) const
    {
        if (dialogEnterSelectedAreaEvent_) {
            dialogEnterSelectedAreaEvent_(info);
        }
    }

    void SetDialogAcceptEvent(DialogTextEvent&& onChange)
    {
        DialogAcceptEvent_ = std::move(onChange);
    }

    void FireDialogAcceptEvent(const std::string& info) const
    {
        if (DialogAcceptEvent_) {
            DialogAcceptEvent_(info);
        }
    }

    void SetOnValueChangeEvent(TextValueChangeEvent&& onValueChangeEvent)
    {
        onValueChangeEvent_ = std::move(onValueChangeEvent);
    }

    void SetOnSelectedChangeEvent(TextSelectedChangeEvent&& onSelectedChangeEvent)
    {
        onSelectedChangeEvent_ = std::move(onSelectedChangeEvent);
    }
private:
    TextChangeEvent TextChangeEvent_;
    TextChangeEvent onScrollStopEvent_;
    TextChangeEvent onEnterSelectedAreaEvent_;
    DialogTextEvent DialogChangeEvent_;
    DialogTextEvent dialogScrollStopEvent_;
    DialogTextEvent dialogEnterSelectedAreaEvent_;
    DialogTextEvent DialogAcceptEvent_;
    TextValueChangeEvent onValueChangeEvent_;
    TextSelectedChangeEvent onSelectedChangeEvent_;

    ACE_DISALLOW_COPY_AND_MOVE(TextPickerEventHub);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_EVENT_HUB_H
