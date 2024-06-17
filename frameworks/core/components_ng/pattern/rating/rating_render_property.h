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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RATING_RATING_RENDER_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RATING_RATING_RENDER_PROPERTY_H

#include <cstdint>
#include <string>

#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {
// PaintProperty are used to set render properties.
class RatingRenderProperty : public PaintProperty {
    DECLARE_ACE_TYPE(RatingRenderProperty, PaintProperty)

public:
    RatingRenderProperty() = default;
    ~RatingRenderProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto renderProperty = MakeRefPtr<RatingRenderProperty>();
        renderProperty->UpdatePaintProperty(this);
        renderProperty->propRatingScore_ = CloneRatingScore();
        renderProperty->propStepSize_ = CloneStepSize();
        renderProperty->propTouchStar_ = CloneTouchStar();
        return renderProperty;
    }

    void Reset() override
    {
        propRatingScore_.reset();
        propStepSize_.reset();
        propTouchStar_.reset();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("rating", std::to_string(propRatingScore_.value_or(0.0)).c_str(), filter);
        constexpr double DEFAULT_STEP_SIZE = 0.5;
        json->PutExtAttr("stepSize", std::to_string(propStepSize_.value_or(DEFAULT_STEP_SIZE)).c_str(), filter);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(RatingScore, double, PROPERTY_UPDATE_RENDER);

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StepSize, double, PROPERTY_UPDATE_RENDER);

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TouchStar, int32_t, PROPERTY_UPDATE_RENDER);

private:
    ACE_DISALLOW_COPY_AND_MOVE(RatingRenderProperty);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RATING_RATING_RENDER_PROPERTY_H
