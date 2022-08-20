/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIVIDER_DIVIDER_RENDER_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIVIDER_DIVIDER_RENDER_PROPERTY_H

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/divider/divider_paragraph.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {
// PaintProperty are used to set render properties.
class DividerRenderProperty : public PaintProperty {
    DECLARE_ACE_TYPE(DividerRenderProperty, PaintProperty)
public:
    DividerRenderProperty() = default;
    ~DividerRenderProperty() override = default;
    RefPtr<PaintProperty> Clone() const override
    {
        auto value = MakeRefPtr<DividerRenderProperty>();
        value->PaintProperty::UpdatePaintProperty(DynamicCast<PaintProperty>(this));
        value->propDividerRenderParagraph_ = CloneDividerRenderParagraph();
        return value;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetDividerRenderParagraph();
    }
    ACE_DEFINE_PROPERTY_GROUP(DividerRenderParagraph, DividerRenderParagraph);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(DividerRenderParagraph, DividerColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(DividerRenderParagraph, LineCap, LineCap, PROPERTY_UPDATE_RENDER);
    ACE_DISALLOW_COPY_AND_MOVE(DividerRenderProperty);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIVIDER_DIVIDER_RENDER_PROPERTY_H