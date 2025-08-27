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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_HYPERLINK_HYPERLINK_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_HYPERLINK_HYPERLINK_PATTERN_H

#include "core/components_ng/pattern/hyperlink/hyperlink_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
class HyperlinkPattern : public TextPattern {
    DECLARE_ACE_TYPE(HyperlinkPattern, TextPattern);

public:
    HyperlinkPattern() = default;
    ~HyperlinkPattern() override = default;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<HyperlinkLayoutProperty>();
    }

    void EnableDrag();

    bool DefaultSupportDrag() override
    {
        return true;
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::NODE, true, FocusStyleType::OUTER_BORDER };
    }

    bool IsEnabledObscured() const override
    {
        return false;
    }

    void UpdatePropertyImpl(const std::string& key, RefPtr<PropertyValueBase> value) override;

private:
    void LinkToAddress();
    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* node) override;
    void OnModifyDone() override;

    void InitClickEvent(const RefPtr<GestureEventHub>& gestureHub) override;
    void InitInputEvent(const RefPtr<InputEventHub>& inputHub);
    void OnHoverEvent(bool isHovered);
    void OnMouseEvent(MouseInfo& info);
    void InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub);
    void InitLongPressEvent(const RefPtr<GestureEventHub>& gestureHub);
    void OnTouchEvent(const TouchEventInfo& info);
    void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    bool OnKeyEvent(const KeyEvent& event);

    bool isLinked_ = false;
    bool isTouchPreventDefault_ = false;
    RefPtr<TouchEventImpl> onTouchEvent_;
    RefPtr<InputEvent> onHoverEvent_;
    RefPtr<InputEvent> onMouseEvent_;
    RefPtr<ClickEvent> clickListener_;
    
    ACE_DISALLOW_COPY_AND_MOVE(HyperlinkPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_HYPERLINK_HYPERLINK_PATTERN_H
