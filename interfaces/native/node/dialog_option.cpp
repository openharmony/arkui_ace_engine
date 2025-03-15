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

#include "dialog_option.h"

#include "native_dialog.h"
#include "node_model.h"

#include "base/error/error_code.h"
#include "base/utils/utils.h"

#ifdef __cplusplus
extern "C" {
#endif

namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_6 = 6;
const int ALLOW_SIZE_7(7);
constexpr int COLOR_STRATEGY_STYLE = 1;
constexpr int COLOR_STYLE = 2;
constexpr int32_t REQUIRED_ONE_PARAM = 1;
constexpr int32_t BLURSTYLE_COLOR_MODE = 0;
constexpr int32_t BLURSTYLE_ADAPTIVE_COLOR = 1;
constexpr int32_t BLURSTYLE_SCALE = 2;
constexpr int32_t BLURSTYLE_GRAY_SCALE_BLACK = 3;
constexpr int32_t BLURSTYLE_GRAY_SCALE_WHITE = 4;
constexpr int32_t BLURSTYLE_POLICY = 5;
constexpr int32_t BLURSTYLE_INACTIVE_COLOR = 6;
constexpr int32_t EFFECT_RADIUS = 0;
constexpr int32_t EFFECT_SATURATION = 1;
constexpr int32_t EFFECT_BRIGHTNESS = 2;
constexpr int32_t EFFECT_COLOR = 3;
constexpr int32_t EFFECT_ADAPTIVE_COLOR = 4;
constexpr int32_t EFFECT_GRAY_SCALE_BLACK = 5;
constexpr int32_t EFFECT_GRAY_SCALE_WHITE = 6;
constexpr int32_t EFFECT_POLICY = 7;
constexpr int32_t EFFECT_COLOR_INDEX = 8;
constexpr uint32_t COLOR_TRANSPARENT = 0x00000000;
constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;

uint32_t ColorAlphaAdapt(uint32_t origin)
{
    uint32_t result = origin;
    if ((origin >> COLOR_ALPHA_OFFSET) == 0) {
        result = origin | COLOR_ALPHA_VALUE;
    }
    return result;
}

int32_t ParseColorMode(const ArkUI_AttributeItem* item, int32_t index)
{
    auto size = item->size;
    int32_t colorMode = ARKUI_COLOR_MODE_SYSTEM;
    if (size > index) {
        int32_t value = item->value[index].i32;
        if (value >= static_cast<int32_t>(ARKUI_COLOR_MODE_SYSTEM) &&
            value <= static_cast<int32_t>(ARKUI_COLOR_MODE_DARK)) {
            colorMode = value;
        }
    }
    return colorMode;
}

int32_t ParseAdaptiveColor(const ArkUI_AttributeItem* item, int32_t index)
{
    auto size = item->size;
    int32_t adaptiveColor = ARKUI_ADAPTIVE_COLOR_DEFAULT;
    if (size > index) {
        int32_t value = item->value[index].i32;
        if (value >= static_cast<int32_t>(ARKUI_ADAPTIVE_COLOR_DEFAULT) &&
            value <= static_cast<int32_t>(ARKUI_ADAPTIVE_COLOR_AVERAGE)) {
            adaptiveColor = value;
        }
    }
    return adaptiveColor;
}

float ParseScale(const ArkUI_AttributeItem* item, int32_t index)
{
    auto size = item->size;
    float scale = 1.0f;
    if (size > index) {
        scale = std::clamp(item->value[index].f32, 0.0f, 1.0f);
    }
    return scale;
}

uint32_t ParseGrayScaleBlack(const ArkUI_AttributeItem* item, int32_t index)
{
    auto size = item->size;
    uint32_t grayScaleBlack = 0;
    if (size > index) {
        grayScaleBlack = item->value[index].u32;
    }
    return grayScaleBlack;
}

uint32_t ParseGrayScaleWhite(const ArkUI_AttributeItem* item, int32_t index)
{
    auto size = item->size;
    uint32_t grayScaleWhite = 0;
    if (size > index) {
        grayScaleWhite = item->value[index].u32;
    }
    return grayScaleWhite;
}

int32_t ParsePolicy(const ArkUI_AttributeItem* item, int32_t index)
{
    auto size = item->size;
    int32_t policy = ARKUI_BLUR_STYLE_ACTIVE_POLICY_ALWAYS_ACTIVE;
    if (size > index) {
        int32_t value = item->value[index].i32;
        if (value >= static_cast<int32_t>(ARKUI_BLUR_STYLE_ACTIVE_POLICY_FOLLOWS_WINDOW_ACTIVE_STATE) &&
            value <= static_cast<int32_t>(ARKUI_BLUR_STYLE_ACTIVE_POLICY_ALWAYS_INACTIVE)) {
            policy = value;
        }
    }
    return policy;
}

float ParseRadius(const ArkUI_AttributeItem* item, int32_t index)
{
    auto size = item->size;
    float radius = 0.0f;
    if (size > index) {
        float value = item->value[index].f32;
        if (OHOS::Ace::GreatOrEqual(value, 0.0f)) {
            radius = value;
        }
    }
    return radius;
}

float ParseSaturation(const ArkUI_AttributeItem* item, int32_t index)
{
    auto size = item->size;
    float saturation = 1.0f;
    if (size > index) {
        float value = item->value[index].f32;
        if (value > 0.0f || OHOS::Ace::NearZero(value)) {
            saturation = value;
        }
    }
    return saturation;
}

float ParseBrightness(const ArkUI_AttributeItem* item, int32_t index)
{
    auto size = item->size;
    float brightness = 1.0f;
    if (size > index) {
        float value = item->value[index].f32;
        if (value > 0.0f || OHOS::Ace::NearZero(value)) {
            brightness = value;
        }
    }
    return brightness;
}

uint32_t ParseColor(const ArkUI_AttributeItem* item, int32_t index)
{
    auto size = item->size;
    uint32_t color = COLOR_TRANSPARENT;
    if (size > index) {
        color = ColorAlphaAdapt(item->value[index].u32);
    }
    return color;
}
} // namespace

ArkUI_CustomDialogOptions* OH_ArkUI_CustomDialog_CreateOptions(ArkUI_NodeHandle content)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !content) {
        return nullptr;
    }
    auto dialog = impl->getDialogAPI()->create();
    auto options = new ArkUI_CustomDialogOptions({ dialog });
    impl->getDialogAPI()->setContent(options->handle, content->uiNodeHandle);
    return options;
}

void OH_ArkUI_CustomDialog_DisposeOptions(ArkUI_CustomDialogOptions* options)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return;
    }
    impl->getDialogAPI()->dispose(options->handle);
    delete options;
    options = nullptr;
}

int32_t OH_ArkUI_CustomDialog_OpenDialog(ArkUI_CustomDialogOptions* options, void (*callback)(int32_t dialogId))
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->openCustomDialog(options->handle, callback);
}

int32_t OH_ArkUI_CustomDialog_UpdateDialog(ArkUI_CustomDialogOptions* options, void (*callback)(int32_t dialogId))
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->updateCustomDialog(options->handle, callback);
}

int32_t OH_ArkUI_CustomDialog_CloseDialog(int32_t dialogId)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->closeCustomDialog(dialogId);
}

int32_t OH_ArkUI_CustomDialog_SetLevelMode(ArkUI_CustomDialogOptions* options, ArkUI_LevelMode levelMode)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    if (static_cast<int32_t>(levelMode) < static_cast<int32_t>(ARKUI_LEVEL_MODE_OVERLAY) ||
        static_cast<int32_t>(levelMode) > static_cast<int32_t>(ARKUI_LEVEL_MODE_EMBEDDED)) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setLevelMode(options->handle, static_cast<int32_t>(levelMode));
}

int32_t OH_ArkUI_CustomDialog_SetLevelUniqueId(ArkUI_CustomDialogOptions* options, int32_t uniqueId)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    if (uniqueId < 0) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setLevelUniqueId(options->handle, uniqueId);
}

int32_t OH_ArkUI_CustomDialog_SetImmersiveMode(ArkUI_CustomDialogOptions* options, ArkUI_ImmersiveMode immersiveMode)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    if (static_cast<int32_t>(immersiveMode) < static_cast<int32_t>(ARKUI_IMMERSIVE_MODE_DEFAULT) ||
        static_cast<int32_t>(immersiveMode) > static_cast<int32_t>(ARKUI_IMMERSIVE_MODE_EXTEND)) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setImmersiveMode(options->handle, static_cast<int32_t>(immersiveMode));
}

int32_t OH_ArkUI_CustomDialog_SetBackgroundColor(ArkUI_CustomDialogOptions* options, uint32_t backgroundColor)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setBackgroundColor(options->handle, backgroundColor);
}

int32_t OH_ArkUI_CustomDialog_SetCornerRadius(
    ArkUI_CustomDialogOptions* options, float topLeft, float topRight, float bottomLeft, float bottomRight)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setCornerRadius(options->handle, topLeft, topRight, bottomLeft, bottomRight);
}

int32_t OH_ArkUI_CustomDialog_SetBorderWidth(
    ArkUI_CustomDialogOptions* options, float top, float right, float bottom, float left, ArkUI_LengthMetricUnit unit)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setBorderWidth(options->handle, top, right, bottom, left, unit);
}

int32_t OH_ArkUI_CustomDialog_SetBorderColor(
    ArkUI_CustomDialogOptions* options, uint32_t top, uint32_t right, uint32_t bottom, uint32_t left)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setBorderColor(options->handle, top, right, bottom, left);
}

int32_t OH_ArkUI_CustomDialog_SetBorderStyle(
    ArkUI_CustomDialogOptions* options, int32_t top, int32_t right, int32_t bottom, int32_t left)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setBorderStyle(options->handle, top, right, bottom, left);
}

int32_t OH_ArkUI_CustomDialog_SetWidth(ArkUI_CustomDialogOptions* options, float width, ArkUI_LengthMetricUnit unit)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setWidth(options->handle, width, unit);
}

int32_t OH_ArkUI_CustomDialog_SetHeight(ArkUI_CustomDialogOptions* options, float height, ArkUI_LengthMetricUnit unit)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setHeight(options->handle, height, unit);
}

int32_t OH_ArkUI_CustomDialog_SetShadow(ArkUI_CustomDialogOptions* options, ArkUI_ShadowStyle shadow)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setShadow(options->handle, shadow);
}

int32_t OH_ArkUI_CustomDialog_SetCustomShadow(
    ArkUI_CustomDialogOptions* options, const ArkUI_AttributeItem* customShadow)
{
    if (customShadow->size == 0) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    ArkUIInt32orFloat32 shadows[ALLOW_SIZE_7] = { 0, { .i32 = NUM_2 }, 0, 0, { .i32 = 0 }, { .u32 = 0 }, { .i32 = 0 } };
    int length = customShadow->size;
    if (length > NUM_0) {
        if (OHOS::Ace::LessNotEqual(customShadow->value[NUM_0].f32, 0.0f)) {
            return ARKUI_ERROR_CODE_PARAM_INVALID;
        }
        shadows[NUM_0].f32 = customShadow->value[NUM_0].f32; // radius
    }
    if (length > NUM_2) {
        shadows[NUM_2].f32 = customShadow->value[NUM_2].f32; // OffsetX
    }
    if (length > NUM_3) {
        shadows[NUM_3].f32 = customShadow->value[NUM_3].f32; // OffsetY
    }
    if (length > NUM_4) {
        if (!OHOS::Ace::InRegion(NUM_0, NUM_1, customShadow->value[NUM_4].i32)) {
            return ARKUI_ERROR_CODE_PARAM_INVALID;
        }
        shadows[NUM_4].i32 = customShadow->value[NUM_4].i32;
    }
    if (length > NUM_5) {
        if (customShadow->value[NUM_1].i32) {
            if (!OHOS::Ace::InRegion(NUM_0, NUM_2, customShadow->value[NUM_5].i32)) {
                return ARKUI_ERROR_CODE_PARAM_INVALID;
            }
            shadows[NUM_1].i32 = COLOR_STRATEGY_STYLE;
            shadows[NUM_5].i32 = customShadow->value[NUM_5].i32;
        } else {
            shadows[NUM_1].i32 = COLOR_STYLE;
            shadows[NUM_5].u32 = customShadow->value[NUM_5].u32;
        }
    }
    if (length > NUM_6) {
        shadows[NUM_6].i32 = customShadow->value[NUM_6].i32;
    }
    return impl->getDialogAPI()->setCustomShadow(options->handle, shadows, ALLOW_SIZE_7);
}

int32_t OH_ArkUI_CustomDialog_SetBackgroundBlurStyle(ArkUI_CustomDialogOptions* options, ArkUI_BlurStyle blurStyle)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setBackgroundBlurStyle(options->handle, blurStyle);
}

int32_t OH_ArkUI_CustomDialog_SetAlignment(
    ArkUI_CustomDialogOptions* options, int32_t alignment, float offsetX, float offsetY)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setContentAlignment(options->handle, alignment, offsetX, offsetY);
}

int32_t OH_ArkUI_CustomDialog_SetModalMode(ArkUI_CustomDialogOptions* options, bool isModal)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setModalMode(options->handle, isModal);
}

int32_t OH_ArkUI_CustomDialog_SetAutoCancel(ArkUI_CustomDialogOptions* options, bool autoCancel)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setAutoCancel(options->handle, autoCancel);
}

int32_t OH_ArkUI_CustomDialog_SetSubwindowMode(ArkUI_CustomDialogOptions* options, bool showInSubwindow)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setSubwindowMode(options->handle, showInSubwindow);
}

int32_t OH_ArkUI_CustomDialog_SetMask(
    ArkUI_CustomDialogOptions* options, uint32_t maskColor, const ArkUI_Rect* maskRect)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    if (maskRect) {
        ArkUIRect rect = { maskRect->x, maskRect->y, maskRect->width, maskRect->height };
        return impl->getDialogAPI()->setMask(options->handle, maskColor, &rect);
    } else {
        return impl->getDialogAPI()->setMask(options->handle, maskColor, nullptr);
    }
}

int32_t OH_ArkUI_CustomDialog_SetKeyboardAvoidMode(
    ArkUI_CustomDialogOptions* options, ArkUI_KeyboardAvoidMode keyboardAvoidMode)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setKeyboardAvoidMode(options->handle, keyboardAvoidMode);
}

int32_t OH_ArkUI_CustomDialog_SetHoverModeEnabled(ArkUI_CustomDialogOptions* options, bool enabled)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->enableHoverMode(options->handle, enabled);
}

int32_t OH_ArkUI_CustomDialog_SetHoverModeArea(
    ArkUI_CustomDialogOptions* options, ArkUI_HoverModeAreaType hoverModeAreaType)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setHoverModeArea(options->handle, hoverModeAreaType);
}

int32_t OH_ArkUI_CustomDialog_RegisterOnWillDismissCallback(
    ArkUI_CustomDialogOptions* options, void* userData, void (*callback)(ArkUI_DialogDismissEvent* event))
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->registerOnWillDismissWithUserData(options->handle, userData, callback);
}

int32_t OH_ArkUI_CustomDialog_RegisterOnWillAppearCallback(
    ArkUI_CustomDialogOptions* options, void* userData, void (*callback)(void* userData))
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->registerOnWillAppear(options->handle, userData, callback);
}

int32_t OH_ArkUI_CustomDialog_RegisterOnDidAppearCallback(
    ArkUI_CustomDialogOptions* options, void* userData, void (*callback)(void* userData))
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->registerOnDidAppear(options->handle, userData, callback);
}

int32_t OH_ArkUI_CustomDialog_RegisterOnWillDisappearCallback(
    ArkUI_CustomDialogOptions* options, void* userData, void (*callback)(void* userData))
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->registerOnWillDisappear(options->handle, userData, callback);
}

int32_t OH_ArkUI_CustomDialog_RegisterOnDidDisappearCallback(
    ArkUI_CustomDialogOptions* options, void* userData, void (*callback)(void* userData))
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->registerOnDidDisappear(options->handle, userData, callback);
}

int32_t OH_ArkUI_CustomDialog_SetBackgroundBlurStyleOptions(
    ArkUI_CustomDialogOptions* options, const ArkUI_AttributeItem* backgroundBlurStyleOptions)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    auto size = backgroundBlurStyleOptions->size;
    if (size < REQUIRED_ONE_PARAM) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    int32_t colorMode = ParseColorMode(backgroundBlurStyleOptions, BLURSTYLE_COLOR_MODE);
    int32_t adaptiveColor = ParseAdaptiveColor(backgroundBlurStyleOptions, BLURSTYLE_ADAPTIVE_COLOR);
    float scale = ParseScale(backgroundBlurStyleOptions, BLURSTYLE_SCALE);
    uint32_t grayScaleBlack = ParseGrayScaleBlack(backgroundBlurStyleOptions, BLURSTYLE_GRAY_SCALE_BLACK);
    uint32_t grayScaleWhite = ParseGrayScaleWhite(backgroundBlurStyleOptions, BLURSTYLE_GRAY_SCALE_WHITE);
    int32_t policy = ParsePolicy(backgroundBlurStyleOptions, BLURSTYLE_POLICY);
    bool isValidColor = false;
    uint32_t inactiveColor = COLOR_TRANSPARENT;
    if (size > BLURSTYLE_INACTIVE_COLOR) {
        inactiveColor = ColorAlphaAdapt(backgroundBlurStyleOptions->value[BLURSTYLE_INACTIVE_COLOR].u32);
        isValidColor = true;
    }
    int32_t intArray[NUM_3];
    intArray[NUM_0] = colorMode;
    intArray[NUM_1] = adaptiveColor;
    intArray[NUM_2] = policy;
    uint32_t uintArray[NUM_3];
    uintArray[NUM_0] = grayScaleBlack;
    uintArray[NUM_1] = grayScaleWhite;
    uintArray[NUM_2] = inactiveColor;
    return impl->getDialogAPI()->setBackgroundBlurStyleOptions(
        options->handle, &intArray, scale, &uintArray, isValidColor);
    return ARKUI_ERROR_CODE_PARAM_INVALID;
}

int32_t OH_ArkUI_CustomDialog_SetBackgroundEffect(
    ArkUI_CustomDialogOptions* options, const ArkUI_AttributeItem* backgroundEffect)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    auto size = backgroundEffect->size;
    if (size < REQUIRED_ONE_PARAM) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    float radius = ParseRadius(backgroundEffect, EFFECT_RADIUS);
    float saturation = ParseSaturation(backgroundEffect, EFFECT_SATURATION);
    float brightness = ParseBrightness(backgroundEffect, EFFECT_BRIGHTNESS);
    uint32_t color = ParseColor(backgroundEffect, EFFECT_COLOR);
    int32_t adaptiveColor = ParseAdaptiveColor(backgroundEffect, EFFECT_ADAPTIVE_COLOR);
    uint32_t grayScaleBlack = ParseGrayScaleBlack(backgroundEffect, EFFECT_GRAY_SCALE_BLACK);
    uint32_t grayScaleWhite = ParseGrayScaleWhite(backgroundEffect, EFFECT_GRAY_SCALE_WHITE);
    int32_t policy = ParsePolicy(backgroundEffect, EFFECT_POLICY);
    bool isValidColor = false;
    uint32_t inactiveColor = COLOR_TRANSPARENT;
    if (size > EFFECT_COLOR_INDEX) {
        inactiveColor = ColorAlphaAdapt(backgroundEffect->value[EFFECT_COLOR_INDEX].u32);
        isValidColor = true;
    }
    float floatArray[NUM_3];
    floatArray[NUM_0] = radius;
    floatArray[NUM_1] = saturation;
    floatArray[NUM_2] = brightness;
    int32_t intArray[NUM_2];
    intArray[NUM_0] = adaptiveColor;
    intArray[NUM_1] = policy;
    uint32_t uintArray[NUM_4];
    uintArray[NUM_0] = color;
    uintArray[NUM_1] = grayScaleBlack;
    uintArray[NUM_2] = grayScaleWhite;
    uintArray[NUM_3] = inactiveColor;
    return impl->getDialogAPI()->setBackgroundEffect(options->handle, &floatArray, &intArray, &uintArray, isValidColor);
}

#ifdef __cplusplus
};
#endif
