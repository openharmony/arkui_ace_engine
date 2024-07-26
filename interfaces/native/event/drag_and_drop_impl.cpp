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
#include "interfaces/native/drag_and_drop.h"
#include "interfaces/native/node/event_converter.h"
#include "interfaces/native/node/node_model.h"
#include "native_node.h"
#include "native_type.h"
#include "ndk_data_conversion.h"
#include "pixelmap_native_impl.h"
#include "securec.h"

#include "base/error/error_code.h"
#include "base/log/log_wrapper.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/core/common/ace_engine.h"
#include "frameworks/core/common/container.h"
#include "frameworks/core/interfaces/native/node/node_api.h"

#ifdef __cplusplus
extern "C" {
#endif

int32_t OH_ArkUI_DragEvent_GetModifierKeyStates(ArkUI_DragEvent* event, int64_t* keys)
{
    if (!event || !keys) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    auto dragEvent = reinterpret_cast<ArkUIDragEvent*>(event);
    *keys = dragEvent->modifierKeyState;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_DragEvent_SetData(ArkUI_DragEvent* event, OH_UdmfData* data)
{
    auto dragEvent = reinterpret_cast<ArkUIDragEvent*>(event);

    if (!event || !data || !dragEvent) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    dragEvent->unifiedData = data;

    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_DragEvent_GetUdmfData(ArkUI_DragEvent* event, OH_UdmfData* data)
{
    auto dragEvent = reinterpret_cast<ArkUIDragEvent*>(event);

    if (!event || !(dragEvent->unifiedData) || !data) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    auto unifiedData =
        std::make_shared<OHOS::UDMF::UnifiedData>(*reinterpret_cast<OHOS::UDMF::UnifiedData*>(dragEvent->unifiedData));

    auto status = OHOS::UDMF::NdkDataConversion::GetNdkUnifiedData(unifiedData, data);
    if (status) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_DragEvent_GetDataTypeCount(ArkUI_DragEvent* event, int32_t* count)
{
    auto dragEvent = reinterpret_cast<ArkUIDragEvent*>(event);

    if (!event || !count || !dragEvent) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *count = dragEvent->dataTypesCount;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_DragEvent_GetDataTypes(
    ArkUI_DragEvent* event, char* eventTypeArray[], int32_t length, int32_t maxStrLen)
{
    auto dragEvent = reinterpret_cast<ArkUIDragEvent*>(event);
    if (!event || !eventTypeArray || !dragEvent) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }

    if (length < dragEvent->dataTypesCount || maxStrLen < dragEvent->dataTypesMaxStrLength) {
        return ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    for (int32_t i = 0; i < length; i++) {
        if (dragEvent->dataTypes[i]) {
            auto strLeng = strlen(dragEvent->dataTypes[i]) + 1;
            auto ret = strncpy_s(eventTypeArray[i], strLeng, dragEvent->dataTypes[i], strLeng - 1);
            if (ret != 0) {
                return ARKUI_ERROR_CODE_PARAM_INVALID;
            }
            eventTypeArray[i][strLeng] = '\0';
        } else {
            eventTypeArray[i][0] = '\0';
        }
    }
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_PreviewDragStatus OH_ArkUI_NodeEvent_GetPreviewDragStatus(ArkUI_NodeEvent* nodeEvent)
{
    if (!nodeEvent || nodeEvent->category != static_cast<int32_t>(NODE_EVENT_CATEGORY_COMPONENT_EVENT)) {
        return ArkUI_PreviewDragStatus::ARKUI_PREVIEW_DRAG_STATUS_UNKNOWN;
    }
    const auto* originNodeEvent = reinterpret_cast<ArkUINodeEvent*>(nodeEvent->origin);
    if (!originNodeEvent) {
        return ArkUI_PreviewDragStatus::ARKUI_PREVIEW_DRAG_STATUS_UNKNOWN;
    }
    auto status = static_cast<ArkUI_PreviewDragStatus>(originNodeEvent->componentAsyncEvent.data[0].i32);
    return status;
}

int32_t OH_ArkUI_DragEvent_DisableDefaultDropAnimation(ArkUI_DragEvent* event, bool disable)
{
    if (!event) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    auto* dragEvent = reinterpret_cast<ArkUIDragEvent*>(event);
    dragEvent->useCustomDropAnimation = disable;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_SetNodeDraggable(ArkUI_NodeHandle node, bool enabled)
{
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !node) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    impl->getNodeModifiers()->getCommonModifier()->setDraggable(node->uiNodeHandle, enabled);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_DragPreviewOption* OH_ArkUI_CreateDragPreviewOption(void)
{
    auto* previewOptions = new ArkUIDragPreViewAndInteractionOptions();
    return reinterpret_cast<ArkUI_DragPreviewOption*>(previewOptions);
}

void OH_ArkUI_DragPreviewOption_Dispose(ArkUI_DragPreviewOption* option)
{
    delete reinterpret_cast<ArkUIDragPreViewAndInteractionOptions*>(option);
    option = nullptr;
}

int32_t OH_ArkUI_DragPreviewOption_SetScaleMode(ArkUI_DragPreviewOption* option, ArkUI_DragPreviewScaleMode scaleMode)
{
    if (!option) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    auto* options = reinterpret_cast<ArkUIDragPreViewAndInteractionOptions*>(option);
    if (scaleMode == ArkUI_DragPreviewScaleMode::ARKUI_DRAG_PREVIEW_SCALE_AUTO) {
        options->isScaleEnabled = true;
        options->isDefaultShadowEnabled = false;
        options->isDefaultRadiusEnabled = false;
    } else {
        options->isScaleEnabled = false;
    }
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_DragPreviewOption_SetDefaultShadowEnabled(ArkUI_DragPreviewOption* option, bool enabled)
{
    if (!option) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    auto* options = reinterpret_cast<ArkUIDragPreViewAndInteractionOptions*>(option);
    options->isDefaultShadowEnabled = enabled;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_DragPreviewOption_SetDefaultRadiusEnabled(ArkUI_DragPreviewOption* option, bool enabled)
{
    if (!option) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    auto* options = reinterpret_cast<ArkUIDragPreViewAndInteractionOptions*>(option);
    options->isDefaultRadiusEnabled = enabled;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_DragPreviewOption_SetNumberBadgeEnabled(ArkUI_DragPreviewOption* option, bool enabled)
{
    if (!option) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    auto* options = reinterpret_cast<ArkUIDragPreViewAndInteractionOptions*>(option);
    options->isNumberBadgeEnabled = enabled;
    options->badgeNumber = static_cast<ArkUI_Int32>(enabled);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_DragPreviewOption_SetBadgeNumber(ArkUI_DragPreviewOption* option, uint32_t forcedNumber)
{
    if (!option) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    auto* options = reinterpret_cast<ArkUIDragPreViewAndInteractionOptions*>(option);
    options->badgeNumber = static_cast<ArkUI_Int32>(forcedNumber);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_DragPreviewOption_SetDefaultAnimationBeforeLiftingEnabled(
    ArkUI_DragPreviewOption* option, bool enabled)
{
    if (!option) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    auto* options = reinterpret_cast<ArkUIDragPreViewAndInteractionOptions*>(option);
    options->defaultAnimationBeforeLifting = enabled;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_SetNodeDragPreviewOption(ArkUI_NodeHandle node, ArkUI_DragPreviewOption* option)
{
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !node) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    auto* previewOption = reinterpret_cast<ArkUIDragPreViewAndInteractionOptions*>(option);
    ArkUIDragPreViewOptions dragPreviewOptions;
    ArkUI_Int32 modeArray[3] = { -1, -1, -1 };
    ArkUI_Int32 modeSize = 0;

    if (previewOption->isScaleEnabled) {
        modeArray[modeSize] = 1; // 1: DragPreviewMode::AUTO
        modeSize++;
    } else {
        modeArray[modeSize] = 2; // 2:  DragPreviewMode::DISABLE_SCAL
        modeSize++;
        if (previewOption->isDefaultShadowEnabled) {
            modeArray[modeSize] = 3; // 3: DragPreviewMode::ENABLE_DEFAULT_SHADOW
            modeSize++;
        }
        if (previewOption->isDefaultRadiusEnabled) {
            modeArray[modeSize] = 4; // 4: DragPreviewMode::ENABLE_DEFAULT_RADIUS
            modeSize++;
        }
    }
    dragPreviewOptions.isModeArray = true;
    dragPreviewOptions.modeArray = modeArray;
    dragPreviewOptions.modeArrayLength = modeSize;
    dragPreviewOptions.isBadgeNumber = previewOption->isNumberBadgeEnabled;
    dragPreviewOptions.badgeNumber = previewOption->badgeNumber;
    dragPreviewOptions.isShowBadge = previewOption->isShowBadge;

    ArkUIDragInteractionOptions dragInteractionOptions;
    dragInteractionOptions.defaultAnimationBeforeLifting = previewOption->defaultAnimationBeforeLifting;
    dragInteractionOptions.isMultiSelectionEnabled = previewOption->isMultiSelectionEnabled;

    impl->getNodeModifiers()->getCommonModifier()->setDragPreviewOptions(
        node->uiNodeHandle, dragPreviewOptions, dragInteractionOptions);

    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_SetNodeDragPreview(ArkUI_NodeHandle node, OH_PixelmapNative* preview)
{
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !node || !preview) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    auto previewPixelNative = reinterpret_cast<OH_PixelmapNativeHandle>(preview);
    auto pixelMap = previewPixelNative->GetInnerPixelmap();
    impl->getDragAdapterAPI()->setDragPreview(node->uiNodeHandle, &pixelMap);
    return ARKUI_ERROR_CODE_NO_ERROR;
}
int32_t OH_ArkUI_SetNodeAllowedDropDataTypes(ArkUI_NodeHandle node, const char* typesArray[], int32_t count)
{
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!fullImpl || !node || !typesArray) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setAllowDrop(node->uiNodeHandle, typesArray, count);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_SetDragEventStrictReportWithNode(ArkUI_NodeHandle node, bool enabled)
{
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!fullImpl || !node) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getDragAdapterAPI()->setDragEventStrictReportingEnabledWithNode(enabled);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_SetDragEventStrictReportWithContext(ArkUI_ContextHandle uiContext, bool enabled)
{
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!fullImpl || !uiContext) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    auto* context = reinterpret_cast<ArkUI_Context*>(uiContext);
    auto id = context->id;
    fullImpl->getDragAdapterAPI()->setDragEventStrictReportingEnabledWithContext(id, enabled);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_DisallowNodeAnyDropDataTypes(ArkUI_NodeHandle node)
{
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!fullImpl || !node) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->setDisAllowDrop(node->uiNodeHandle);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_AllowNodeAllDropDataTypes(ArkUI_NodeHandle node)
{
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!fullImpl || !node) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getCommonModifier()->resetAllowDrop(node->uiNodeHandle);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_DragEvent_GetDragResult(ArkUI_DragEvent* event, ArkUI_DragResult* result)
{
    if (!event || !result) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    auto* dragEvent = reinterpret_cast<ArkUIDragEvent*>(event);
    *result = static_cast<ArkUI_DragResult>(dragEvent->dragResult);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_DragEvent_SetDragResult(ArkUI_DragEvent* event, ArkUI_DragResult result)
{
    if (!event) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    auto* dragEvent = reinterpret_cast<ArkUIDragEvent*>(event);
    dragEvent->dragResult = static_cast<ArkUI_Int32>(result);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_DragEvent_SetSuggestedDropOperation(ArkUI_DragEvent* event, ArkUI_DropOperation proposal)
{
    if (!event) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    auto* dragEvent = reinterpret_cast<ArkUIDragEvent*>(event);
    dragEvent->dragBehavior = static_cast<ArkUI_Int32>(proposal);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

float OH_ArkUI_DragEvent_GetPreviewTouchPointX(ArkUI_DragEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    auto* dragEvent = reinterpret_cast<ArkUIDragEvent*>(event);
    auto result = static_cast<float>(dragEvent->touchPointX);
    return result;
}

float OH_ArkUI_DragEvent_GetPreviewTouchPointY(ArkUI_DragEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    auto* dragEvent = reinterpret_cast<ArkUIDragEvent*>(event);
    auto result = static_cast<float>(dragEvent->touchPointY);
    return result;
}

float OH_ArkUI_DragEvent_GetPreviewRectWidth(ArkUI_DragEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    auto* dragEvent = reinterpret_cast<ArkUIDragEvent*>(event);
    auto result = static_cast<float>(dragEvent->previewRectWidth);
    return result;
}

float OH_ArkUI_DragEvent_GetPreviewRectHeight(ArkUI_DragEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    auto* dragEvent = reinterpret_cast<ArkUIDragEvent*>(event);
    auto result = static_cast<float>(dragEvent->previewRectHeight);
    return result;
}

float OH_ArkUI_DragEvent_GetTouchPointXToWindow(ArkUI_DragEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    auto* dragEvent = reinterpret_cast<ArkUIDragEvent*>(event);
    auto result = static_cast<float>(dragEvent->windowX);
    return result;
}

float OH_ArkUI_DragEvent_GetTouchPointYToWindow(ArkUI_DragEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    auto* dragEvent = reinterpret_cast<ArkUIDragEvent*>(event);
    auto result = static_cast<float>(dragEvent->windowY);
    return result;
}

float OH_ArkUI_DragEvent_GetTouchPointXToDisplay(ArkUI_DragEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    auto* dragEvent = reinterpret_cast<ArkUIDragEvent*>(event);
    auto result = static_cast<float>(dragEvent->displayX);
    return result;
}

float OH_ArkUI_DragEvent_GetTouchPointYToDisplay(ArkUI_DragEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    auto* dragEvent = reinterpret_cast<ArkUIDragEvent*>(event);
    auto result = static_cast<float>(dragEvent->displayY);
    return result;
}

float OH_ArkUI_DragEvent_GetVelocityX(ArkUI_DragEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    auto* dragEvent = reinterpret_cast<ArkUIDragEvent*>(event);
    auto result = static_cast<float>(dragEvent->velocityX);
    return result;
}

float OH_ArkUI_DragEvent_GetVelocityY(ArkUI_DragEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    auto* dragEvent = reinterpret_cast<ArkUIDragEvent*>(event);
    auto result = static_cast<float>(dragEvent->velocityY);
    return result;
}

float OH_ArkUI_DragEvent_GetVelocity(ArkUI_DragEvent* event)
{
    if (!event) {
        return 0.0f;
    }
    auto* dragEvent = reinterpret_cast<ArkUIDragEvent*>(event);
    auto result = static_cast<float>(dragEvent->velocity);
    return result;
}
#ifdef __cplusplus
};
#endif