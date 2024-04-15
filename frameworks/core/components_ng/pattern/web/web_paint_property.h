/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WEB_WEB_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WEB_WEB_PAINT_PROPERTY_H

#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {
class WebPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(WebPaintProperty, PaintProperty)

public:
    WebPaintProperty() = default;
    ~WebPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<WebPaintProperty>();
        paintProperty->UpdatePaintProperty(this);
        return paintProperty;
    }

    void Reset() override
    {
        PaintProperty::Reset();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        PaintProperty::ToJsonValue(json, filter);
        json->PutFixedAttr("content", webPaintData_.value_or("null").c_str(), filter, FIXED_ATTR_CONTENT);
    }

    void SetWebPaintData(const std::string& webData)
    {
        if (webPaintData_ != webData) {
            webPaintData_ = webData;
        }
    }

    std::string GetWebPaintData()
    {
        return webPaintData_.value_or("");
    }

private:
    std::optional<std::string> webPaintData_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WEB_WEB_PAINT_PROPERTY_H
