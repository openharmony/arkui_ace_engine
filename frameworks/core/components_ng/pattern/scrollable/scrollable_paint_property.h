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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_PAINT_PROPERTY_H

#include "core/animation/curve.h"
#include "core/animation/curves.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {
struct ScrollBarProperty {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ScrollBarMode, DisplayMode);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ScrollBarWidth, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ScrollBarColor, Color);
};

class ScrollablePaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(ScrollablePaintProperty, PaintProperty)

public:
    ScrollablePaintProperty() = default;
    ~ScrollablePaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<ScrollablePaintProperty>();
        paintProperty->UpdatePaintProperty(this);
        paintProperty->propScrollBarProperty_ = CloneScrollBarProperty();
        return paintProperty;
    }

    void Reset() override
    {
        ResetScrollBarProperty();
        PaintProperty::Reset();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override;

    ACE_DEFINE_PROPERTY_GROUP(ScrollBarProperty, ScrollBarProperty);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ScrollBarProperty, ScrollBarMode, DisplayMode, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ScrollBarProperty, ScrollBarWidth, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ScrollBarProperty, ScrollBarColor, Color, PROPERTY_UPDATE_RENDER);

private:
    Color GetBarColor() const;
    Dimension GetBarWidth() const;
    std::string GetBarStateString() const;
};
} // namespace OHOS::Ace::NG

#endif
