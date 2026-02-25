/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SYMBOL_SYMBOL_GLYPH_CUSTOM_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SYMBOL_SYMBOL_GLYPH_CUSTOM_MODIFIER_H

#include <vector>

#include "base/geometry/dimension.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/node/node_api.h"

struct ArkUISymbolGlyphCustomModifier {
    void (*initialSymbol)(OHOS::Ace::NG::FrameNode* frameNode, ArkUI_Uint32 symbolId);
    void (*setFontSize)(OHOS::Ace::NG::FrameNode* frameNode, const OHOS::Ace::Dimension& value);
    void (*setFontColor)(OHOS::Ace::NG::FrameNode* frameNode, const std::vector<OHOS::Ace::Color>& symbolColor);
    ArkUINodeHandle (*createFrameNode)(ArkUI_Int32 nodeId);
};

#endif