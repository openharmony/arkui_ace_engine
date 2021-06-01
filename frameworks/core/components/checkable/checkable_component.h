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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CHECKABLE_CHECKABLE_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CHECKABLE_CHECKABLE_COMPONENT_H

#include "base/geometry/dimension.h"
#include "base/utils/label_target.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/pipeline/base/render_component.h"
#include "core/pipeline/base/render_node.h"
#ifndef WEARABLE_PRODUCT
#include "core/event/multimodal/multimodal_properties.h"
#endif

namespace OHOS::Ace {

enum class CheckableType {
    RADIO,
    CHECKBOX,
    SWITCH,
    UNKNOWN,
};

template<class T>
class CheckableValue {
public:
    CheckableValue() = default;
    explicit CheckableValue(T value) : value_(value) {}
    virtual ~CheckableValue() = default;

    T GetValue() const
    {
        return value_;
    }

    void SetValue(T value)
    {
        value_ = value;
    }

private:
    T value_;
};

class CheckableComponent : public RenderComponent {
    DECLARE_ACE_TYPE(CheckableComponent, RenderComponent);

public:
    CheckableComponent(CheckableType type, const RefPtr<CheckableTheme>& theme);
    ~CheckableComponent() override = default;

    RefPtr<RenderNode> CreateRenderNode() override;
    RefPtr<Element> CreateElement() override;

    void ApplyTheme(const RefPtr<CheckableTheme>& theme);

    const EventMarker& GetChangeEvent() const
    {
        return changeEvent_;
    }

    void SetChangeEvent(const EventMarker& changeEvent)
    {
        changeEvent_ = changeEvent;
    }

    const EventMarker& GetClickEvent() const
    {
        return clickEvent_;
    }

    void SetClickEvent(const EventMarker& clickEvent)
    {
        clickEvent_ = clickEvent;
    }

    const EventMarker& GetDomChangeEvent() const
    {
        return domChangeEvent_;
    }

    void SetDomChangeEvent(const EventMarker& domChangeEvent)
    {
        domChangeEvent_ = domChangeEvent;
    }

    const Dimension& GetWidth() const
    {
        return width_;
    }

    const Dimension& GetHeight() const
    {
        return height_;
    }

    void SetWidth(const Dimension& width)
    {
        width_ = width;
    }

    void SetHeight(const Dimension& height)
    {
        height_ = height;
    }

    void SetHorizontalPadding(const Dimension& hotZoneHorizontalPadding)
    {
        hotZoneHorizontalPadding_ = hotZoneHorizontalPadding;
    }

    const Dimension& GetHotZoneHorizontalPadding() const
    {
        return hotZoneHorizontalPadding_;
    }

    void SetHotZoneVerticalPadding(const Dimension& hotZoneVerticalPadding)
    {
        hotZoneVerticalPadding_ = hotZoneVerticalPadding;
    }

    const Dimension& GetHotZoneVerticalPadding() const
    {
        return hotZoneVerticalPadding_;
    }

    void SetAspectRatio(double aspectRatio)
    {
        aspectRatio_ = aspectRatio;
    }

    double GetAspectRatio() const
    {
        return aspectRatio_;
    }

    double GetRadioInnerSizeRatio() const
    {
        return radioInnerSizeRatio_;
    }

    bool IsBackgroundSolid() const
    {
        return backgroundSolid_;
    }

    void SetBackgroundSolid(bool backgroundSolid)
    {
        backgroundSolid_ = backgroundSolid;
    }

    bool IsDisabled() const
    {
        return disabled_;
    }

    void SetDisabled(bool disabled)
    {
        disabled_ = disabled;
    }

    const Color& GetPointColor() const
    {
        return pointColor_;
    }

    void SetPointColor(const Color& pointColor)
    {
        pointColor_ = pointColor;
    }

    const Color& GetActiveColor() const
    {
        return activeColor_;
    }

    void SetActiveColor(const Color& activeColor)
    {
        activeColor_ = activeColor;
    }

    const Color& GetInactiveColor() const
    {
        return inactiveColor_;
    }

    void SetInactiveColor(const Color& inactiveColor)
    {
        inactiveColor_ = inactiveColor;
    }

    const Color& GetFocusColor() const
    {
        return focusColor_;
    }

    void SetFocusColor(const Color& focusColor)
    {
        focusColor_ = focusColor;
    }

    void SetDefaultWidth(const Dimension& defaultWidth)
    {
        defaultWidth_ = defaultWidth;
    }

    const Dimension& GetDefaultWidth() const
    {
        return defaultWidth_;
    }

    void SetDefaultHeight(const Dimension& defaultHeight)
    {
        defaultHeight_ = defaultHeight;
    }

    const Dimension& GetDefaultHeight() const
    {
        return defaultHeight_;
    }

    void SetNeedFocus(bool needFocus)
    {
        needFocus_ = needFocus;
    }

    bool GetNeedFocus() const
    {
        return needFocus_;
    }

    void SetHoverColor(const Color& hoverColor)
    {
        hoverColor_ = hoverColor;
    }

    const Color& GetHoverColor() const
    {
        return hoverColor_;
    }

    const Color& GetInactivePointColor() const
    {
        return inactivePointColor_;
    }

    const Color& GetShadowColor() const
    {
        return shadowColor_;
    }

    const Dimension& GetShadowWidth() const
    {
        return shadowWidth_;
    }

    const Dimension& GetHoverRadius() const
    {
        return hoverRadius_;
    }

protected:
    CheckableType checkableType_ = CheckableType::UNKNOWN;
    Dimension width_;
    Dimension height_;
    Dimension hotZoneHorizontalPadding_;
    Dimension hotZoneVerticalPadding_;
    Dimension defaultWidth_;
    Dimension defaultHeight_;
    Dimension shadowWidth_;
    Dimension hoverRadius_;
    bool backgroundSolid_ = true;
    bool disabled_ = false;
    bool needFocus_ = true;
    Color pointColor_;
    Color activeColor_;
    Color inactiveColor_;
    Color inactivePointColor_;
    Color focusColor_;
    Color hoverColor_;
    Color shadowColor_;
    EventMarker changeEvent_;
    EventMarker clickEvent_;
    EventMarker domChangeEvent_;
    double aspectRatio_ = 1.0;
    double radioInnerSizeRatio_ = 0.5;
};

class CheckboxComponent : public CheckableComponent, public CheckableValue<bool>, public LabelTarget {
    DECLARE_ACE_TYPE(CheckboxComponent, CheckableComponent, LabelTarget);

public:
    CheckboxComponent(const RefPtr<CheckboxTheme>& theme);
    ~CheckboxComponent() override = default;
};

class SwitchComponent : public CheckableComponent, public CheckableValue<bool> {
    DECLARE_ACE_TYPE(SwitchComponent, CheckableComponent);

public:
    SwitchComponent(const RefPtr<SwitchTheme>& theme);
    ~SwitchComponent() override = default;

    void SetTextStyle(const TextStyle& textStyle)
    {
        textStyle_ = textStyle;
    }

    const TextStyle& GetTextStyle() const
    {
        return textStyle_;
    }

    const std::string& GetTextOn() const
    {
        return textOn_;
    }

    void SetTextOn(const std::string& textOn)
    {
        textOn_ = textOn;
    }

    const std::string& GetTextOff() const
    {
        return textOff_;
    }

    void SetTextOff(const std::string& textOff)
    {
        textOff_ = textOff;
    }

    bool GetShowText() const
    {
        return showText_;
    }

    void SetShowText(bool showText)
    {
        showText_ = showText;
    }

    const Color& GetTextColorOn() const
    {
        return textColorOn_;
    }

    void SetTextColorOn(const Color& textColorOn)
    {
        textColorOn_ = textColorOn;
    }

    const Color& GetTextColorOff() const
    {
        return textColorOff_;
    }

    void SetTextColorOff(const Color& textColorOff)
    {
        textColorOff_ = textColorOff;
    }

    const Dimension& GetTextPadding() const
    {
        return textPadding_;
    }

    void SetTextPadding(const Dimension& textPadding)
    {
        textPadding_ = textPadding;
    }

#ifndef WEARABLE_PRODUCT
    const MultimodalProperties& GetMultimodalProperties() const
    {
        return multimodalProperties_;
    }

    void SetMultimodalProperties(const MultimodalProperties& multimodalProperties)
    {
        multimodalProperties_ = multimodalProperties;
    }
#endif

private:
    std::string textOn_ = "On";
    std::string textOff_ = "Off";
    Color textColorOn_ = Color::BLACK;
    Color textColorOff_ = Color::BLACK;
    bool showText_ = false;
    TextStyle textStyle_;
#ifndef WEARABLE_PRODUCT
    MultimodalProperties multimodalProperties_;
#endif
    Dimension textPadding_ { 0, DimensionUnit::PX };
};

template<class VALUE_TYPE>
class RadioComponent : public CheckableComponent, public CheckableValue<VALUE_TYPE>, public LabelTarget {
    DECLARE_ACE_TYPE(RadioComponent<VALUE_TYPE>, CheckableComponent, LabelTarget);

public:
    RadioComponent(const RefPtr<RadioTheme>& theme) : CheckableComponent(CheckableType::RADIO, theme) {}
    ~RadioComponent() override = default;

    VALUE_TYPE GetGroupValue() const
    {
        return groupValue_;
    }

    void SetGroupValue(VALUE_TYPE groupValue)
    {
        groupValue_ = groupValue;
    }

    const std::function<void(VALUE_TYPE)>& GetGroupValueChangedListener() const
    {
        return groupValueChangedListener_;
    }

    void SetGroupValueChangedListener(const std::function<void(VALUE_TYPE)>& groupValueChangedListener)
    {
        groupValueChangedListener_ = groupValueChangedListener;
    }

    void SetGroupValueUpdateHandler(const std::function<void(VALUE_TYPE)>& groupValueUpdateHandler)
    {
        groupValueUpdateHandler_ = groupValueUpdateHandler;
    }

    void UpdateGroupValue(VALUE_TYPE groupValue)
    {
        if (groupValueUpdateHandler_) {
            groupValueUpdateHandler_(groupValue);
        }
    }

    const std::string& GetGroupName() const
    {
        return groupName_;
    }
    void SetGroupName(const std::string& groupName)
    {
        groupName_ = groupName;
    }

private:
    VALUE_TYPE groupValue_;
    std::string groupName_;
    std::function<void(VALUE_TYPE)> groupValueChangedListener_;
    std::function<void(VALUE_TYPE)> groupValueUpdateHandler_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CHECKABLE_CHECKABLE_COMPONENT_H
