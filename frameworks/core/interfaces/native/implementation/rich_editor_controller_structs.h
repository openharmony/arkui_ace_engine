/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_RICHEDITOR_CONTROLLER_STRUCTS_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_RICHEDITOR_CONTROLLER_STRUCTS_H

#include <optional>

#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_controller.h"

namespace OHOS::Ace::NG::Converter {
struct TextSpanOptionsForUpdate {
    int32_t start;
    int32_t end;
    std::optional<TextStyle> textStyle;
    ImageSpanAttribute imageSpanAttribute;
};

struct TextDecorationStruct {
    TextDecoration textDecoration = TextDecoration::NONE;
    std::optional<TextDecorationStyle> style;
    std::optional<Color> color;
};

struct UpdateParagraphStyleForUpdate {
    int32_t start;
    int32_t end;
    std::optional<UpdateParagraphStyle> style;
};

struct RichEditorSymbolSpanStyle {
    std::optional<Dimension> fontSize;
};

} // namespace OHOS::Ace::NG::Converter
#endif
