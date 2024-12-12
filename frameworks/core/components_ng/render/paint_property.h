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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_PAINT_PROPERTY_H

#include <memory>

#include "base/json/json_util.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class InspectorFilter;

// PaintProperty are used to set render properties.
class PaintProperty : public Property {
    DECLARE_ACE_TYPE(PaintProperty, Property)

public:
    PaintProperty() = default;
    ~PaintProperty() override = default;

    virtual RefPtr<PaintProperty> Clone() const
    {
        auto renderProperty = MakeRefPtr<PaintProperty>();
        renderProperty->UpdatePaintProperty(this);
        return renderProperty;
    }

    virtual void Reset() {}

    virtual void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const {}

    virtual void ToTreeJson(std::unique_ptr<JsonValue>& json, const InspectorConfig& config) const {}

    virtual void FromJson(const std::unique_ptr<JsonValue>& json) {}

protected:
    void UpdatePaintProperty(const PaintProperty* renderProperty) {}

    ACE_DISALLOW_COPY_AND_MOVE(PaintProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_PAINT_PROPERTY_H
