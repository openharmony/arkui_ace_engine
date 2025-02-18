/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_PAINT_PROPERTY_H

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/render/paint_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
// PaintProperty are used to set paint properties.
class SelectPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(SelectPaintProperty, PaintProperty)
public:
    SelectPaintProperty() = default;
    ~SelectPaintProperty() override = default;
    RefPtr<PaintProperty> Clone() const override
    {
        auto value = MakeRefPtr<SelectPaintProperty>();
        value->PaintProperty::UpdatePaintProperty(DynamicCast<PaintProperty>(this));
        value->propBackgroundColor_ = CloneBackgroundColor();
        return value;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetBackgroundColor();
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
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto theme = pipelineContext->GetTheme<SelectTheme>(host->GetThemeScopeId());
        CHECK_NULL_VOID(theme);
        json->PutExtAttr("backgroundColor",
            propBackgroundColor_.value_or(theme->GetButtonBackgroundColor()).ColorToString().c_str(), filter);
    }

    void FromJson(const std::unique_ptr<JsonValue>& json) override
    {
        UpdateBackgroundColor(Color::ColorFromString(json->GetString("backgroundColor")));
        PaintProperty::FromJson(json);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BackgroundColor, Color, PROPERTY_UPDATE_RENDER);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_PAINT_PROPERTY_H