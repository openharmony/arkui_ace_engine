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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_EVENT_HUB_H

#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_selection.h"

namespace OHOS::Ace::NG {
class TextInsertValueInfo {
public:
    TextInsertValueInfo() = default;
    ~TextInsertValueInfo() = default;
};

class RichEditorInsertValue : public BaseEventInfo {
    DECLARE_ACE_TYPE(RichEditorInsertValue, BaseEventInfo)
public:
    RichEditorInsertValue() : BaseEventInfo("RichEditorInsertValue") {}
    ~RichEditorInsertValue() override = default;
};

enum class SpanResultType { TEXT, IMAGE };

class RichEditorAbstractSpanResult {
public:
    RichEditorAbstractSpanResult() = default;
    ~RichEditorAbstractSpanResult() = default;
};

enum class RichEditorDeleteDirection { BACKWARD = 0, FORWARD };

class RichEditorDeleteValue : public BaseEventInfo {
    DECLARE_ACE_TYPE(RichEditorDeleteValue, BaseEventInfo)
public:
    RichEditorDeleteValue() : BaseEventInfo("RichEditorDeleteValue") {}
    ~RichEditorDeleteValue() = default;
};

class RichEditorEventHub : public EventHub {
    DECLARE_ACE_TYPE(RichEditorEventHub, EventHub)

public:
    RichEditorEventHub() = default;
    ~RichEditorEventHub() override = default;
    void SetOnReady(std::function<void()>&& func);
    void FireOnReady();

    void SetOnSelect(std::function<void(const BaseEventInfo*)>&& func)
    {
        onSelect_ = std::move(func);
    }

    void FireOnSelect(BaseEventInfo* value)
    {
        if (onSelect_) {
            onSelect_(value);
        }
    }

private:
    std::function<void()> onReady_;
    std::function<void(const BaseEventInfo*)> onSelect_;
    ACE_DISALLOW_COPY_AND_MOVE(RichEditorEventHub);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_EVENT_HUB_H
