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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SECURITY_COMPONENT_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SECURITY_COMPONENT_PAINT_PROPERTY_H

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {
class SecurityComponentPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(SecurityComponentPaintProperty, PaintProperty)

public:
    SecurityComponentPaintProperty() = default;
    ~SecurityComponentPaintProperty() override = default;
    RefPtr<PaintProperty> Clone() const override
    {
        auto value = MakeRefPtr<SecurityComponentPaintProperty>();
        value->PaintProperty::UpdatePaintProperty(DynamicCast<PaintProperty>(this));
        value->propIconColor_ = CloneIconColor();
        value->propSymbolIconColor_ = CloneSymbolIconColor();
        value->propFontColor_ = CloneFontColor();
        value->propBackgroundColor_ = CloneBackgroundColor();
        value->propBackgroundBorderColor_ = CloneBackgroundBorderColor();
        value->propBackgroundBorderStyle_ = CloneBackgroundBorderStyle();
        return value;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetIconColor();
        ResetFontColor();
        ResetBackgroundColor();
        ResetBackgroundBorderColor();
        ResetBackgroundBorderStyle();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IconColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SymbolIconColor, std::vector<Color>, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(FontColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BackgroundColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BackgroundBorderColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BackgroundBorderStyle, BorderStyle, PROPERTY_UPDATE_RENDER);
    ACE_DISALLOW_COPY_AND_MOVE(SecurityComponentPaintProperty);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SECURITY_COMPONENT_PAINT_PROPERTY_H
