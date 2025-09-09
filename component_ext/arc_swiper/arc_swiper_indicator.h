/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef COMPONENT_EXT_ARC_SWIPER_ARC_SWIPER_INDICATOR_H
#define COMPONENT_EXT_ARC_SWIPER_ARC_SWIPER_INDICATOR_H

#include <optional>

#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/swiper/swiper_model.h"
#include "core/components_ng/property/gradient_property.h"

namespace OHOS::Ace::NG {

class JsArcSwiperIndicator : public virtual AceType {
    DECLARE_ACE_TYPE(JsArcSwiperIndicator, AceType);

public:
    JsArcSwiperIndicator() = default;
    ~JsArcSwiperIndicator() override = default;

    void SetArcDirection(SwiperArcDirection direction)
    {
        arcDirection_ = direction;
    }

    SwiperArcDirection GetArcDirection() const
    {
        return arcDirection_.value();
    }

    bool HasArcDirection() const
    {
        return arcDirection_.has_value();
    }

    void SetItemColor(const Color& color)
    {
        itemColor_ = color;
    }

    void ResetItemColor()
    {
        itemColor_.reset();
    }

    const Color& GetItemColor() const
    {
        return itemColor_.value();
    }

    bool HasItemColor() const
    {
        return itemColor_.has_value();
    }

    void SetSelectedItemColor(const Color& color)
    {
        selectedItemColor_ = color;
    }

    void ResetSelectedItemColor()
    {
        selectedItemColor_.reset();
    }

    const Color& GetSelectedItemColor() const
    {
        return selectedItemColor_.value();
    }

    bool HasSelectedItemColor() const
    {
        return selectedItemColor_.has_value();
    }

    void SetContainerColor(const Color& color)
    {
        containerColor_ = color;
    }

    void ResetContainerColor()
    {
        containerColor_.reset();
    }

    const Color& GetContainerColor() const
    {
        return containerColor_.value();
    }

    bool HasContainerColor() const
    {
        return containerColor_.has_value();
    }

    void SetMaskColor(const NG::Gradient& GradientColor)
    {
        maskLinearGradientColor_ = GradientColor;
    }

    void ResetMaskColor()
    {
        maskLinearGradientColor_.reset();
    }

    const NG::Gradient& GetMaskColor() const
    {
        return maskLinearGradientColor_.value();
    }

    bool HasMaskColor() const
    {
        return maskLinearGradientColor_.has_value();
    }

private:
    std::optional<SwiperArcDirection> arcDirection_;
    std::optional<Color> itemColor_;
    std::optional<Color> selectedItemColor_;
    std::optional<Color> containerColor_;
    std::optional<NG::Gradient> maskLinearGradientColor_;

    ACE_DISALLOW_COPY_AND_MOVE(JsArcSwiperIndicator);
};

} // namespace OHOS::Ace::NG
 
#endif // COMPONENT_EXT_ARC_SWIPER_ARC_SWIPER_INDICATOR_H