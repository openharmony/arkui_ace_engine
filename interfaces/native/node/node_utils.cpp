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


#include "node_model.h"

#include "base/error/error_code.h"

#ifdef __cplusplus
extern "C" {
#endif

int32_t OH_ArkUI_NodeUtils_GetLayoutSize(ArkUI_NodeHandle node, ArkUI_IntSize* size)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    ArkUI_Int32* tempSize = new ArkUI_Int32[2];
    impl->getNodeModifiers()->getFrameNodeModifier()->getLayoutSize(node->uiNodeHandle, tempSize);
    size->width = tempSize[0];
    size->height = tempSize[1];
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_NodeUtils_GetLayoutPosition(ArkUI_NodeHandle node, ArkUI_IntOffset* localOffset)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    auto value = impl->getNodeModifiers()->getFrameNodeModifier()->getLayoutPositionWithoutMargin(node->uiNodeHandle);
    localOffset->x = static_cast<int32_t>(value[0]);
    localOffset->y = static_cast<int32_t>(value[1]);

    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_NodeUtils_GetLayoutPositionInWindow(ArkUI_NodeHandle node, ArkUI_IntOffset* globalOffset)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    ArkUI_Float32 tempOffset[2];
    impl->getNodeModifiers()->getFrameNodeModifier()->getPositionToWindow(node->uiNodeHandle, &tempOffset, false);
    globalOffset->x = tempOffset[0];
    globalOffset->y = tempOffset[1];

    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_NodeUtils_GetLayoutPositionInScreen(ArkUI_NodeHandle node, ArkUI_IntOffset* screenOffset)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    ArkUI_Float32 tempOffset[2];
    impl->getNodeModifiers()->getFrameNodeModifier()->getPositionToScreen(node->uiNodeHandle, &tempOffset, false);
    screenOffset->x = tempOffset[0];
    screenOffset->y = tempOffset[1];

    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_NodeUtils_GetPositionWithTranslateInWindow(ArkUI_NodeHandle node, ArkUI_IntOffset* translateOffset)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    ArkUI_Float32 tempOffset[2];
    impl->getNodeModifiers()->getFrameNodeModifier()->getPositionToWindowWithTransform(
        node->uiNodeHandle, &tempOffset, false);
    translateOffset->x = tempOffset[0];
    translateOffset->y = tempOffset[1];

    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_NodeUtils_GetPositionWithTranslateInScreen(ArkUI_NodeHandle node, ArkUI_IntOffset* translateOffset)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    ArkUI_Float32 tempOffset[2];
    impl->getNodeModifiers()->getFrameNodeModifier()->getPositionToScreenWithTransform(
        node->uiNodeHandle, &tempOffset, false);
    translateOffset->x = tempOffset[0];
    translateOffset->y = tempOffset[1];

    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_RegisterSystemColorModeChangeEvent(
    ArkUI_NodeHandle node, void* userData, void (*onColorModeChange)(ArkUI_SystemColorMode colorMode, void* userData))
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    impl->getNodeModifiers()->getFrameNodeModifier()->setSystemColorModeChangeEvent(
        node->uiNodeHandle, userData, reinterpret_cast<void*>(onColorModeChange));

    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

void OH_ArkUI_UnregisterSystemColorModeChangeEvent(ArkUI_NodeHandle node)
{
    if (node == nullptr) {
        return;
    }
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    impl->getNodeModifiers()->getFrameNodeModifier()->resetSystemColorModeChangeEvent(node->uiNodeHandle);
}

int32_t OH_ArkUI_RegisterSystemFontStyleChangeEvent(
    ArkUI_NodeHandle node, void* userData, void (*onFontStyleChange)(ArkUI_SystemFontStyleEvent* event, void* userData))
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    impl->getNodeModifiers()->getFrameNodeModifier()->setSystemFontStyleChangeEvent(
        node->uiNodeHandle, userData, reinterpret_cast<void*>(onFontStyleChange));

    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

void OH_ArkUI_UnregisterSystemFontStyleChangeEvent(ArkUI_NodeHandle node)
{
    if (node == nullptr) {
        return;
    }
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    impl->getNodeModifiers()->getFrameNodeModifier()->resetSystemFontStyleChangeEvent(node->uiNodeHandle);
}

float OH_ArkUI_SystemFontStyleEvent_GetFontSizeScale(const ArkUI_SystemFontStyleEvent* event)
{
    return event->fontSize;
}

float OH_ArkUI_SystemFontStyleEvent_GetFontWeightScale(const ArkUI_SystemFontStyleEvent* event)
{
    return event->fontWeight;
}

void OH_ArkUI_NodeUtils_AddCustomProperty(ArkUI_NodeHandle node, const char* name, const char* value)
{
    if (node == nullptr) {
        return;
    }
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    impl->getNodeModifiers()->getFrameNodeModifier()->addCustomProperty(node->uiNodeHandle, name, value);
}

void OH_ArkUI_NodeUtils_RemoveCustomProperty(ArkUI_NodeHandle node, const char* name)
{
    if (node == nullptr) {
        return;
    }
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    impl->getNodeModifiers()->getFrameNodeModifier()->removeCustomProperty(node->uiNodeHandle, name);
}

#ifdef __cplusplus
};
#endif
