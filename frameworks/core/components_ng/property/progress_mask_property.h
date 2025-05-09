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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_PROGRESS_MASK_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_PROGRESS_MASK_PROPERTY_H

#include <vector>
#include <functional>
#include "base/memory/ace_type.h"
#include "core/components/common/properties/color.h"
#include "core/common/resource/resource_object.h"

namespace OHOS::Ace::NG {
class ProgressMaskProperty : public AceType {
    DECLARE_ACE_TYPE(ProgressMaskProperty, AceType);

public:
    ProgressMaskProperty() = default;
    ~ProgressMaskProperty() override = default;

    float GetValue() const
    {
        return value_;
    }

    float GetMaxValue() const
    {
        return maxValue_;
    }

    Color GetColor() const
    {
        return color_;
    }

    RefPtr<ResourceObject> GetResObj()
    {
        return resObj_;
    }

    bool GetEnableBreathe() const
    {
        return enableBreathe_;
    }

    void SetValue(const float& value)
    {
        value_ = value;
    }

    void SetMaxValue(const float& value)
    {
        maxValue_ = value;
    }

    void SetColor(const Color& color)
    {
        color_ = color;
    }

    void SetEnableBreathe(bool enableBreathe)
    {
        enableBreathe_ = enableBreathe;
    }

    void SetResObj(const RefPtr<ResourceObject> resObj)
    {
        resObj_ = resObj;
    }
    bool operator==(const ProgressMaskProperty& other) const
    {
        return  (value_ == other.GetValue() &&
                maxValue_ == other.GetMaxValue() &&
                color_ == other.GetColor());
    }

    ProgressMaskProperty& operator=(const ProgressMaskProperty& other)
    {
        if (this != &other) {
            value_ = other.GetValue();
            maxValue_ = other.GetMaxValue();
            color_ = other.GetColor();
        }
        return *this;
    }

private:
    float value_ = 0.0f;
    float maxValue_ = 100.0f;
    Color color_ = Color(0x99182431);
    bool enableBreathe_ = false;
    RefPtr<ResourceObject> resObj_;
};
} // namespace OHOS::Ace::NG {
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_PROGRESS_MASK_PROPERTY_H
