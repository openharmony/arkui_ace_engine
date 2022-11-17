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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_REFRESH_RENDER_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_REFRESH_RENDER_PROPERTY_H

#include "frameworks/core/components/common/layout/constants.h"
#include "frameworks/core/components_ng/layout/layout_property.h"
#include "frameworks/core/components_ng/property/property.h"
#include "frameworks/core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {

class RefreshRenderProperty : public PaintProperty {
    DECLARE_ACE_TYPE(RefreshRenderProperty, PaintProperty)

public:
    RefreshRenderProperty() = default;
    ~RefreshRenderProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<RefreshRenderProperty>();
        paintProperty->UpdatePaintProperty(this);
        paintProperty->propIsRefreshing_ = CloneIsRefreshing();
        paintProperty->propTimeText_ = CloneTimeText();
        paintProperty->propLastTimeText_ = CloneLastTimeText();
        return paintProperty;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetIsRefreshing();
        ResetTimeText();
        ResetLastTimeText();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override
    {
        PaintProperty::ToJsonValue(json);
        json->Put("refreshing", propIsRefreshing_.value_or(false) ? "true" : "false");
    }
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsRefreshing, bool, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TimeText, std::string, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(LastTimeText, std::string, PROPERTY_UPDATE_LAYOUT);

private:
    ACE_DISALLOW_COPY_AND_MOVE(RefreshRenderProperty);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_REFRESH_RENDER_PROPERTY_H
