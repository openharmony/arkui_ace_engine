/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_TEXT_TEXT_SPECIALIZED_STYLE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_TEXT_TEXT_SPECIALIZED_STYLE_H

#include "core/components/common/properties/color.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/declaration/common/attribute.h"
#include "core/components/declaration/common/style.h"

namespace OHOS::Ace {

struct TextSpecializedAttribute : Attribute {
    std::string data;
};

struct TextSpecializedStyle : Style {
    TextStyle textStyle;
    Color focusColor;
    CopyOptions copyOptions;
    bool isMaxWidthLayout = false;
    bool autoMaxLines = false;
};

enum class TextShadowSettings {
    OFFSET_ONLY = 2,
    OFFSET_EXTRA,
    OFFSET_BLUR_CLOR,
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_TEXT_TEXT_SPECIALIZED_STYLE_H
