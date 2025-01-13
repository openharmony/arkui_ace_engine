/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PROGRESS_PROGRESS_DATE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PROGRESS_PROGRESS_DATE_H

#include "base/geometry/dimension.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/property/gradient_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/base/common_configuration.h"

namespace OHOS::Ace::NG {

enum class ProgressType {
    LINEAR = 1,
    RING = 2,
    SCALE = 3,
    CIRCLE = 4,
    GAUGE = 5,
    ARC = 6,
    MOON = 7,
    BUBBLE = 8,
    CAPSULE = 9,
};

enum class ProgressStatus {
    PROGRESSING = 0,
    LOADING
};

class ProgressTypeUtils {
public:
    static std::string ConvertProgressTypeToString(ProgressType progressType)
    {
        std::string progressTypeUtils = "";
        switch (progressType) {
            case ProgressType::LINEAR:
                progressTypeUtils = "ProgressStyle.Linear";
                break;
            case ProgressType::MOON:
                progressTypeUtils = "ProgressStyle.Eclipse";
                break;
            case ProgressType::SCALE:
                progressTypeUtils = "ProgressStyle.ScaleRing";
                break;
            case ProgressType::RING:
                progressTypeUtils = "ProgressStyle.Ring";
                break;
            case ProgressType::CAPSULE:
                progressTypeUtils = "ProgressStyle.Capsule";
                break;
            default:
                progressTypeUtils = "ProgressStyle.Linear";
        }
        return progressTypeUtils;
    }
};

struct ProgressDate {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(MaxValue, double);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Value, double);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(StrokeWidth, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ScaleCount, int32_t);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ScaleWidth, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BorderWidth, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TextSize, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Text, std::string);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(EnableScanEffect, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FontWeight, FontWeight);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FontFamily, std::vector<std::string>);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ItalicFontStyle, Ace::FontStyle);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TextColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(EnableRingScanEffect, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(EnableLinearScanEffect, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(EnableShowText, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(StrokeRadius, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BorderRadius, Dimension);
};

struct ProgressStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Color, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BackgroundColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Type, ProgressType);
};

struct ProgressAnimatableProperty {
    Color color;
    Color bgColor;
    Color borderColor;
    Gradient ringProgressColor;
    float strokeWidth = 0.0f;
    float strokeRadius = 0.0f;
    float value = 0.0f;
};

class ProgressConfiguration : public CommonConfiguration {
    public:
        ProgressConfiguration(float value, float total, bool enabled)
            : CommonConfiguration(enabled), value_(value), total_(total) {}
        float value_ = 0.0f;
        float total_ = 0.0f;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PROGRESS_PROGRESS_DATE_H
