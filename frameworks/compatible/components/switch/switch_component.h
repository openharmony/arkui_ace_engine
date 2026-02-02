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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPATIABLE_SWITCH_SWITCH_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_COMPATIABLE_SWITCH_SWITCH_COMPONENT_H

#include "core/components/checkable/checkable_component.h"
#include "core/components/checkable/checkable_element.h"

namespace OHOS::Ace {
namespace {

constexpr bool DEFAULT_SWITCH_VALUE = false;

} // namespace
class ACE_EXPORT SwitchComponent : public CheckableComponent, public CheckableValue<bool> {
    DECLARE_ACE_TYPE(SwitchComponent, CheckableComponent);

public:
    explicit SwitchComponent(const RefPtr<SwitchTheme>& theme);
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
    const CommonMultimodalAttribute& GetMultimodalProperties() const
    {
        return multimodalProperties_;
    }

    void SetMultimodalProperties(const CommonMultimodalAttribute& multimodalProperties)
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
    CommonMultimodalAttribute multimodalProperties_;
#endif
    Dimension textPadding_ { 0, DimensionUnit::PX };
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_COMPATIABLE_SWITCH_SWITCH_COMPONENT_H
