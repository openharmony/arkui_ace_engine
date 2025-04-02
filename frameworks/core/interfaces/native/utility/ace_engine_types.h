/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef GENERATED_FOUNDATION_ACE_FRAMEWORKS_CORE_UTILITY_ACE_ENGINE_TYPES_H
#define GENERATED_FOUNDATION_ACE_FRAMEWORKS_CORE_UTILITY_ACE_ENGINE_TYPES_H

#include <optional>
#include <variant>

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/animation_option.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_v2/list/list_properties.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"

namespace OHOS::Ace::NG {
struct KeyboardOptions {
    bool supportAvoidance;
};
struct PathShapeOptions {
    std::optional<std::string> commands;
};
}

namespace OHOS::Ace::NG::Converter {
/*
 * Keep this enum in sync with the same enum in frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h
 */
enum class ResourceType : uint32_t {
    COLOR = 10001,
    FLOAT,
    STRING,
    PLURAL,
    BOOLEAN,
    INTARRAY,
    INTEGER,
    PATTERN,
    STRARRAY,
    MEDIA = 20000,
    RAWFILE = 30000
};

struct RadioStyle {
    std::optional<Color> checkedBackgroundColor;
    std::optional<Color> uncheckedBorderColor;
    std::optional<Color> indicatorColor;
};

typedef std::tuple<
    std::optional<Dimension>,
    std::optional<FontWeight>
    // here it can be expanded by Family and Style data
> FontMetaData;

struct CaretStyle {
    std::optional<Dimension> width;
    std::optional<Color> color;
};
struct TextDecorationOptions {
    std::optional<TextDecoration> textDecoration;
    std::optional<Color> color;
    std::optional<TextDecorationStyle> textDecorationStyle;
};
struct ListItemOptions {
    std::optional<V2::ListItemStyle> style;
};

struct AnimateParam {
    std::optional<int32_t> duration;
    std::optional<int32_t> delay;
    std::optional<int32_t> iterations;
    std::optional<float> tempo;
    std::optional<AnimationDirection> direction;
    std::optional<FinishCallbackType> finishCallbackType;
    std::optional<RefPtr<Curve>> curve;
    std::optional<RefPtr<FrameRateRange>> frameRateRange;
};

struct SymbolData {
    std::optional<uint32_t> symbol;
};

struct FontFamilies {
    std::vector<std::string> families;
};

enum class MessageLevel {
    DEBUG = 1,
    INFO = 2,
    WARN = 3,
    ERROR = 4,
    LOG = 5
};

enum class RenderExitReason {
    ABNORMAL_TERMINATION = 0,
    WAS_KILLED = 1,
    CRASHED = 2,
    OOM = 3,
    EXIT_UNKNOWN = 4
};

enum class SslError {
    INVALID = 0,
    HOST_MISMATCH = 1,
    DATE_INVALID = 2,
    UNTRUSTED = 3,
};

enum class ThreatType {
    ILLEGAL = 0,
    FRAUD = 1,
    RISK = 2,
    WARNING = 3,
};

struct Header {
    std::string headerKey;
    std::string headerValue;

    bool operator==(const Header& other) const
    {
        return (headerKey == other.headerKey && headerValue == other.headerValue);
    }
};

using PickerSelectedType = std::variant<uint32_t, std::vector<uint32_t>>;
using PickerValueType = std::variant<std::string, std::vector<std::string>>;

struct LightSource {
    std::optional<CalcDimension> x;
    std::optional<CalcDimension> y;
    std::optional<CalcDimension> z;
    std::optional<float> intensity;
    std::optional<Color> lightColor;
};

struct PointLightStyle {
    std::optional<LightSource> lightSource;
    std::optional<int> illuminationType;
    std::optional<float> bloom;
};

struct ScaleOpt {
    std::optional<float> x;
    std::optional<float> y;
    std::optional<float> z;
    std::optional<Dimension> centerX;
    std::optional<Dimension> centerY;
};
} // namespace OHOS::Ace::NG::Converter
#endif  // GENERATED_FOUNDATION_ACE_FRAMEWORKS_CORE_UTILITY_ACE_ENGINE_TYPES_H
