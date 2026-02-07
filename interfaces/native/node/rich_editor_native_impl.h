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

#ifndef FOUNDATION_ACE_FRAMEWORKS_INTERFACE_NATIVE_NODE_RICH_EDITOR_NATIVE_IMPL_H
#define FOUNDATION_ACE_FRAMEWORKS_INTERFACE_NATIVE_NODE_RICH_EDITOR_NATIVE_IMPL_H

#include "native_type.h"
#include "node/node_extened.h"
#ifdef __cplusplus
extern "C" {
#endif

struct OH_ArkUI_TextEditorPlaceholderOptions {
    std::string value;
    uint32_t fontWeight;
    float fontSize;
    std::string fontFamily;
    ArkUI_FontStyle fontStyle;
    uint32_t fontColor;
};

struct OH_ArkUI_TextEditorStyledStringController {
    ArkUI_NodeHandle node;
};

struct OH_ArkUI_TextEditorParagraphStyle {
    ArkUI_TextAlignment textAlign;
    OH_PixelmapNative* leadingMarginPixelMap;
    uint32_t width;
    uint32_t height;
    ArkUI_WordBreak wordBreak;
    OH_ArkUI_LineBreakStrategy lineBreakStrategy;
    uint32_t paragraphSpacing;
    ArkUI_TextVerticalAlignment textVerticalAlignment;
    ArkUI_TextDirection textDirection;
};

struct OH_ArkUI_ShadowOptions {
    float radius;
    ArkUI_ShadowType type;
    uint32_t color;
    float offsetX;
    float offsetY;
    bool isFill;
};

struct OH_ArkUI_TextEditorTextStyle {
    uint32_t fontColor;
    ArkUI_FontStyle fontStyle;
    float fontSize;
    uint32_t fontWeight;
    std::string fontFamily;
    OH_ArkUI_DecorationStyleOptions decoration;
    int32_t lineHeight;
    int32_t letterSpacing;
    std::string fontFeature;
    bool halfLeading;
    uint32_t textBackgroundColor;
    float textBackgroundTopLeftRadius;
    float textBackgroundTopRightRadius;
    float textBackgroundBottomLeftRadius;
    float textBackgroundBottomRightRadius;
    int32_t strokeWidth;
    uint32_t strokeColor;
    std::vector<OH_ArkUI_ShadowOptions> textShadow;
};
#ifdef __cplusplus
}
#endif

#endif // FOUNDATION_ACE_FRAMEWORKS_INTERFACE_NATIVE_NODE_RICH_EDITOR_NATIVE_IMPL_H