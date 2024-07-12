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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_LAYOUT_ADAPTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_LAYOUT_ADAPTER_H

#include <string>

#include "base/geometry/dimension.h"
#include "core/components_ng/pattern/text/text_styles.h"

namespace OHOS::Ace::NG {

struct FontScaleParameter {
    bool allowScale = false;
    float minFontScale = 0.0f;
    float maxFontScale = static_cast<float>(INT32_MAX);
    float height = 0.0f;
};

class TextLayoutadapter {
public:
    static bool IsLeftToRight(int32_t charOfShowingText);
    static bool IsRightToLeft(int32_t charOfShowingText);
    static bool IsRightTOLeftArabic(int32_t charOfShowingText);
    static double TextConvertToPx(const Dimension& value, FontScaleParameter parameter);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_LAYOUT_ADAPTER_H
