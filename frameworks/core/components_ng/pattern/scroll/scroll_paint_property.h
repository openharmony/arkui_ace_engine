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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_SCROLL_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_SCROLL_PAINT_PROPERTY_H

#include <algorithm>
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {

class ScrollPaintProperty : public ScrollablePaintProperty {
    DECLARE_ACE_TYPE(ScrollPaintProperty, ScrollablePaintProperty)

public:
    ScrollPaintProperty() = default;
    ~ScrollPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<ScrollPaintProperty>();
        paintProperty->UpdatePaintProperty(this);
        paintProperty->currentOffset_ = currentOffset_;
        paintProperty->viewPortExtent_ = viewPortExtent_;
        paintProperty->propAxis_ = CloneAxis();
        return paintProperty;
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override
    {
        ScrollablePaintProperty::ToJsonValue(json);
    }

    void Reset() override
    {
        ScrollablePaintProperty::Reset();
        ResetAxis();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Axis, Axis, PROPERTY_UPDATE_MEASURE);

private:
    float currentOffset_ = 0.0f;
    SizeF viewPortExtent_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_SCROLL_PAINT_PROPERTY_H
