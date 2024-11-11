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

#include "base/geometry/dimension.h"
#include "core/components/common/properties/color.h"
#include "core/components_v2/list/list_properties.h"

namespace OHOS::Ace::NG::GeneratedModifier {
class WebCookiePeerImpl : public Referenced {
    // this is a stub because all WebCookieAccessor interfaces are deprecated
};
} // OHOS::Ace::NG::GeneratedModifier

namespace OHOS::Ace::NG::Converter {
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

struct ListItemGroupOptions {
    std::optional<Dimension> space;
    std::optional<V2::ListItemGroupStyle> style;
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
} // namespace OHOS::Ace::NG::Converter
#endif  // GENERATED_FOUNDATION_ACE_FRAMEWORKS_CORE_UTILITY_ACE_ENGINE_TYPES_H