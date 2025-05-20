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

 #ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_BAR_PAINT_PROPERTY_H
 #define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_BAR_PAINT_PROPERTY_H
 
 #include "core/animation/curve.h"
 #include "core/animation/curves.h"
 #include "core/components/common/layout/constants.h"
 #include "core/components/common/properties/color.h"
 #include "core/components_ng/pattern/scroll/inner/scroll_bar.h"
 #include "core/components_ng/render/paint_property.h"
 
 namespace OHOS::Ace::NG {
 
 class ScrollBarPaintProperty : public PaintProperty {
     DECLARE_ACE_TYPE(ScrollBarPaintProperty, PaintProperty)
 
 public:
 ScrollBarPaintProperty() = default;
     ~ScrollBarPaintProperty() override = default;
 
     RefPtr<PaintProperty> Clone() const override
     {
         auto paintProperty = MakeRefPtr<ScrollBarPaintProperty>();
         paintProperty->UpdatePaintProperty(this);
         paintProperty->propScrollBarColor_ = CloneScrollBarColor();
         return paintProperty;
     }
 
     void Reset() override
     {
         PaintProperty::Reset();
         ResetScrollBarColor();
     }

     Color GetBarColor() const
     {
         return propScrollBarColor_ ? propScrollBarColor_.value_or(DefaultScrollBarColor) : DefaultScrollBarColor;
     }

     void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
     {
        CHECK_NULL_VOID(json);
        PaintProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("scrollBarColor", GetBarColor().ColorToString().c_str(), filter);
    }
    void SetDefaultScrollBarColor(const Color& color)
    {
        DefaultScrollBarColor = color;
    }

    Color DefaultScrollBarColor;
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ScrollBarColor, Color, PROPERTY_UPDATE_RENDER);

    ACE_DISALLOW_COPY_AND_MOVE(ScrollBarPaintProperty);
 };
 } // namespace OHOS::Ace::NG
 
 #endif
 