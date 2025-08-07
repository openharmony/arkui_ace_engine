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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_QRCODE_QRCODE_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_QRCODE_QRCODE_PAINT_PROPERTY_H

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/qrcode/qrcode_theme.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/render/paint_property.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {

class QRCodePaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(QRCodePaintProperty, PaintProperty)

public:
    QRCodePaintProperty() = default;
    ~QRCodePaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<QRCodePaintProperty>();
        paintProperty->UpdatePaintProperty(this);
        paintProperty->propValue_ = CloneValue();
        paintProperty->propColor_ = CloneColor();
        paintProperty->propBackgroundColor_ = CloneBackgroundColor();
        paintProperty->propOpacity_ = CloneOpacity();
        return paintProperty;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetValue();
        ResetColor();
        ResetBackgroundColor();
        ResetOpacity();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        PaintProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        RefPtr<QrcodeTheme> qrCodeTheme = pipeline->GetTheme<QrcodeTheme>();
        CHECK_NULL_VOID(qrCodeTheme);
        json->PutExtAttr("value", propValue_.value_or("").c_str(), filter);
        json->PutExtAttr("color",
            propColor_.value_or(qrCodeTheme->GetQrcodeColor()).ColorToString().c_str(), filter);
        json->PutExtAttr("backgroundColor",
            propBackgroundColor_.value_or(qrCodeTheme->GetBackgroundColor()).ColorToString().c_str(), filter);
        json->PutExtAttr("opacity", propOpacity_.value_or(1.0f), filter);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Value, std::string, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Color, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BackgroundColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Opacity, double, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(QRCodeColorSetByUser, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(QRBackgroundColorSetByUser, bool, PROPERTY_UPDATE_RENDER);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_QRCODE_QRCODE_PAINT_PROPERTY_H
