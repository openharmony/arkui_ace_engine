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

#include "core/pipeline_ng/pipeline_context.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/divider/divider_theme.h"
#include "core/components_ng/base/inspector_filter.h"
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
        value->propDividerColor_ = CloneDividerColor();
        value->propLineCap_ = CloneLineCap();
        return value;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetDividerColor();
        ResetLineCap();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        PaintProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto theme = pipelineContext->GetTheme<DividerTheme>();
        CHECK_NULL_VOID(theme);
        json->PutExtAttr("color", propDividerColor_.value_or(theme->GetColor()).ColorToString().c_str(), filter);
        json->PutExtAttr("lineCap",
            propLineCap_.value_or(LineCap::SQUARE) == LineCap::BUTT
                ? "BUTT"
                : (propLineCap_.value_or(LineCap::SQUARE) == LineCap::ROUND ? "ROUND" : "SQUARE"),
            filter);
    }

    void FromJson(const std::unique_ptr<JsonValue>& json) override
    {
        UpdateDividerColor(Color::ColorFromString(json->GetString("color")));
        PaintProperty::FromJson(json);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DividerColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(LineCap, LineCap, PROPERTY_UPDATE_RENDER);
    ACE_DISALLOW_COPY_AND_MOVE(DividerRenderProperty);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIVIDER_DIVIDER_RENDER_PROPERTY_H
