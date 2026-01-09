/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_TEXT_FIELD_MODIFIER_TEXT_FIELD_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_TEXT_FIELD_MODIFIER_TEXT_FIELD_MODIFIER_H

#include <cstdint>
#include <stddef.h>
#include <functional>
#include <unordered_map>
#include <string>
#include <utility>
#include "ui/base/referenced.h"

#ifdef __cplusplus
extern "C" {
#endif

namespace OHOS::Ace {
class RenderTextField;
struct OverlayShowOption;
class Rect;

struct ArkUITextFieldModifierCompatible {
    void (*setEditingValue)(const RefPtr<RenderTextField>& textfield, std::string selectedText);
    std::string (*getEditingValue)(const RefPtr<RenderTextField>& textfield);
    int32_t (*getTextEditingEnd)(const RefPtr<RenderTextField>& textfield);
    int32_t (*getEditingStart)(const RefPtr<RenderTextField>& textfield);
    int32_t (*getEditingEnd)(const RefPtr<RenderTextField>& textfield);
    bool (*liftPanelForVirtualKeyboard)(const RefPtr<RenderTextField>& textfield, double offsetY, double fullHeight);
    bool (*updatePanelHeightByCurrentMode)(const RefPtr<RenderTextField>& textfield);
    void (*setIsOverlayShowed)(const RefPtr<RenderTextField>& textfield, bool value, bool needStart);
    void (*setUpdateHandlePosition)(const RefPtr<RenderTextField>& textfield,
        const std::function<void(const OverlayShowOption&)>& updateHandlePosition);
    void (*setUpdateHandleDiameter)(
        const RefPtr<RenderTextField>& textfield, const std::function<void(const double&)>& updateHandleDiameter);
    void (*setUpdateHandleDiameterInner)(
        const RefPtr<RenderTextField>& textfield, const std::function<void(const double&)>& updateHandleDiameterInner);
    void (*setOnValueChange)(const RefPtr<RenderTextField>& textfield, const std::function<void()>& onValueChange);
    void (*setOnKeyboardClose)(
        const RefPtr<RenderTextField>& textfield, const std::function<void(bool)>& onKeyboardClose);
    void (*setOnClipRectChanged)(
        const RefPtr<RenderTextField>& textfield, const std::function<void(const Rect&)>& onClipRectChanged);
};

namespace TextFieldModifier {

const ArkUITextFieldModifierCompatible* GetTextFieldModifier();
} // namespace TextFieldModifier
} // namespace OHOS::Ace

#ifdef __cplusplus
};
#endif

#endif // FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_TEXT_FIELD_MODIFIER_TEXT_FIELD_MODIFIER_H