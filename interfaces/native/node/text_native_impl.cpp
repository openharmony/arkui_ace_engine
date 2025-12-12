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
#include "text_native_impl.h"

#include <securec.h>

#include "node_extened.h"
#include "node_model.h"

#include "base/utils/utils.h"

#ifdef __cplusplus
extern "C" {
#endif
ArkUI_TextMenuItem* OH_ArkUI_TextMenuItem_Create()
{
    ArkUI_TextMenuItem* item = new ArkUI_TextMenuItem();
    item->isDelContent = false;
    item->isDelIcon = false;
    item->isDelLabel = false;
    return item;
}

void OH_ArkUI_TextMenuItem_Dispose(ArkUI_TextMenuItem* textMenuItem)
{
    if (!textMenuItem) {
        return;
    }
    if (textMenuItem->isDelContent && textMenuItem->content) {
        delete[] textMenuItem->content;
        textMenuItem->content = nullptr;
        textMenuItem->isDelContent = false;
    }
    if (textMenuItem->isDelIcon && textMenuItem->icon) {
        delete[] textMenuItem->icon;
        textMenuItem->icon = nullptr;
        textMenuItem->isDelIcon = false;
    }
    if (textMenuItem->isDelLabel && textMenuItem->labelInfo) {
        delete[] textMenuItem->labelInfo;
        textMenuItem->labelInfo = nullptr;
        textMenuItem->isDelLabel = false;
    }
    delete textMenuItem;
}

ArkUI_ErrorCode OH_ArkUI_TextMenuItem_SetContent(ArkUI_TextMenuItem* item, const char* content)
{
    CHECK_NULL_RETURN(item, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(content, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);

    if (item->isDelContent && item->content) {
        delete[] item->content;
        item->content = nullptr;
        item->isDelContent = false;
    }
    size_t contentLen = strlen(content) + 1;
    char* newContent = new char[contentLen];
    item->isDelContent = true;
    if (strcpy_s(newContent, contentLen, content) != 0) {
        delete[] newContent;
        newContent = nullptr;
        item->isDelContent = false;
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_INTERNAL_ERROR;
    }
    item->content = newContent;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextMenuItem_GetContent(
    const ArkUI_TextMenuItem* item, char* buffer, int32_t bufferSize, int32_t* writeLength)
{
    CHECK_NULL_RETURN(item, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(item->content, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(buffer, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(writeLength, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    int32_t contentLength = static_cast<int32_t>(strlen(item->content));
    if (bufferSize < contentLength + 1) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    if (strcpy_s(buffer, bufferSize, item->content) != 0) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    *writeLength = contentLength;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextMenuItem_SetIcon(ArkUI_TextMenuItem* item, const char* icon)
{
    CHECK_NULL_RETURN(item, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(icon, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);

    if (item->isDelIcon && item->icon) {
        delete[] item->icon;
        item->icon = nullptr;
        item->isDelIcon = false;
    }

    size_t iconLen = strlen(icon) + 1;
    char* newIcon = new char[iconLen];
    item->isDelIcon = true;
    if (strcpy_s(newIcon, iconLen, icon) != 0) {
        delete[] newIcon;
        newIcon = nullptr;
        item->isDelIcon = false;
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_INTERNAL_ERROR;
    }
    item->icon = newIcon;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextMenuItem_GetIcon(
    const ArkUI_TextMenuItem* item, char* buffer, int32_t bufferSize, int32_t* writeLength)
{
    CHECK_NULL_RETURN(item, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(item->icon, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(buffer, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(writeLength, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    int32_t iconLength = static_cast<int32_t>(strlen(item->icon));
    if (bufferSize < iconLength + 1) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    if (strcpy_s(buffer, bufferSize, item->icon) != 0) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    *writeLength = iconLength;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextMenuItem_SetLabelInfo(ArkUI_TextMenuItem* item, const char* labelInfo)
{
    CHECK_NULL_RETURN(item, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(labelInfo, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);

    if (item->isDelLabel && item->labelInfo) {
        delete[] item->labelInfo;
        item->labelInfo = nullptr;
        item->isDelLabel = false;
    }

    size_t labelInfoLen = strlen(labelInfo) + 1;
    char* newLabelInfo = new char[labelInfoLen];
    item->isDelLabel = true;
    if (strcpy_s(newLabelInfo, labelInfoLen, labelInfo) != 0) {
        delete[] newLabelInfo;
        newLabelInfo = nullptr;
        item->isDelLabel = false;
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_INTERNAL_ERROR;
    }
    item->labelInfo = newLabelInfo;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextMenuItem_GetLabelInfo(
    const ArkUI_TextMenuItem* item, char* buffer, int32_t bufferSize, int32_t* writeLength)
{
    CHECK_NULL_RETURN(item, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(item->labelInfo, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(buffer, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(writeLength, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    int32_t labelInfoLength = static_cast<int32_t>(strlen(item->labelInfo));
    if (bufferSize < labelInfoLength + 1) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    if (strcpy_s(buffer, bufferSize, item->labelInfo) != 0) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    *writeLength = labelInfoLength;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextMenuItem_SetId(ArkUI_TextMenuItem* item, int32_t id)
{
    CHECK_NULL_RETURN(item, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    item->id = id;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextMenuItem_GetId(const ArkUI_TextMenuItem* item, int32_t* id)
{
    CHECK_NULL_RETURN(item, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(id, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *id = item->id;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_TextEditMenuOptions* OH_ArkUI_TextEditMenuOptions_Create()
{
    ArkUI_TextEditMenuOptions* options = new ArkUI_TextEditMenuOptions();
    return options;
}

void OH_ArkUI_TextEditMenuOptions_Dispose(ArkUI_TextEditMenuOptions* editMenuOptions)
{
    if (!editMenuOptions) {
        return;
    }
    delete editMenuOptions;
    editMenuOptions = nullptr;
}

ArkUI_ErrorCode OH_ArkUI_TextMenuItemArray_GetSize(ArkUI_TextMenuItemArray* itemArray, int32_t* size)
{
    CHECK_NULL_RETURN(itemArray, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *size = static_cast<int32_t>(itemArray->items.size());
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextMenuItemArray_GetItem(
    ArkUI_TextMenuItemArray* itemArray, int32_t index, ArkUI_TextMenuItem** item)
{
    CHECK_NULL_RETURN(itemArray, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(item, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    if (index < 0 || index >= static_cast<int32_t>(itemArray->items.size())) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *item = itemArray->items.data() + index;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextMenuItemArray_Insert(
    ArkUI_TextMenuItemArray* itemArray, ArkUI_TextMenuItem* item, int32_t index)
{
    CHECK_NULL_RETURN(itemArray, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(item, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(item->content, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    if (index < 0 || index > static_cast<int32_t>(itemArray->items.size())) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    ArkUI_TextMenuItem insertItem;
    insertItem.content = nullptr;
    insertItem.isDelContent = false;
    insertItem.icon = nullptr;
    insertItem.isDelIcon = false;
    insertItem.labelInfo = nullptr;
    insertItem.isDelLabel = false;
    if (OH_ArkUI_TextMenuItem_SetContent(&insertItem, item->content) != ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_INTERNAL_ERROR;
    }
    OH_ArkUI_TextMenuItem_SetIcon(&insertItem, item->icon);
    OH_ArkUI_TextMenuItem_SetLabelInfo(&insertItem, item->labelInfo);
    insertItem.id = item->id;
    itemArray->items.insert(itemArray->items.begin() + index, insertItem);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextMenuItemArray_Erase(ArkUI_TextMenuItemArray* itemArray, int32_t index)
{
    CHECK_NULL_RETURN(itemArray, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    if (index < 0 || index >= static_cast<int32_t>(itemArray->items.size())) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    auto eraseIter = itemArray->items.begin() + index;
    if (eraseIter->isDelContent && eraseIter->content) {
        delete[] eraseIter->content;
        eraseIter->content = nullptr;
        eraseIter->isDelContent = false;
    }
    if (eraseIter->isDelIcon && eraseIter->icon) {
        delete[] eraseIter->icon;
        eraseIter->icon = nullptr;
        eraseIter->isDelIcon = false;
    }
    if (eraseIter->isDelLabel && eraseIter->labelInfo) {
        delete[] eraseIter->labelInfo;
        eraseIter->labelInfo = nullptr;
        eraseIter->isDelLabel = false;
    }
    itemArray->items.erase(eraseIter);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextMenuItemArray_Clear(ArkUI_TextMenuItemArray* itemArray)
{
    CHECK_NULL_RETURN(itemArray, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    for (auto& eraseItem : itemArray->items) {
        if (eraseItem.isDelContent && eraseItem.content) {
            delete[] eraseItem.content;
            eraseItem.content = nullptr;
            eraseItem.isDelContent = false;
        }
        if (eraseItem.isDelIcon && eraseItem.icon) {
            delete[] eraseItem.icon;
            eraseItem.icon = nullptr;
            eraseItem.isDelIcon = false;
        }
        if (eraseItem.isDelLabel && eraseItem.labelInfo) {
            delete[] eraseItem.labelInfo;
            eraseItem.labelInfo = nullptr;
            eraseItem.isDelLabel = false;
        }
    }
    itemArray->items.clear();
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditMenuOptions_RegisterOnCreateMenuCallback(
    ArkUI_TextEditMenuOptions* editMenuOptions, void* userData, ArkUI_TextCreateMenuCallback cb)
{
    CHECK_NULL_RETURN(editMenuOptions, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    editMenuOptions->onCreateMenu = cb;
    editMenuOptions->createUserData = userData;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditMenuOptions_RegisterOnPrepareMenuCallback(
    ArkUI_TextEditMenuOptions* editMenuOptions, void* userData, ArkUI_TextPrepareMenuCallback cb)
{
    CHECK_NULL_RETURN(editMenuOptions, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    editMenuOptions->onPrepareMenu = cb;
    editMenuOptions->prepareUserData = userData;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditMenuOptions_RegisterOnMenuItemClickCallback(
    ArkUI_TextEditMenuOptions* editMenuOptions, void* userData, ArkUI_TextMenuItemClickCallback cb)
{
    CHECK_NULL_RETURN(editMenuOptions, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    editMenuOptions->onMenuItemClick = cb;
    editMenuOptions->clickUserData = userData;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_TextSelectionMenuOptions* OH_ArkUI_TextSelectionMenuOptions_Create()
{
    ArkUI_TextSelectionMenuOptions* options = new ArkUI_TextSelectionMenuOptions();
    options->textSpanType = ArkUI_TextSpanType::ARKUI_TEXT_SPAN_TYPE_TEXT;
    options->textResponseType = ArkUI_TextResponseType::ARKUI_TEXT_RESPONSE_TYPE_LONG_PRESS;
    options->hapticFeedbackMode = ArkUI_HapticFeedbackMode::ARKUI_HAPTIC_FEEDBACK_MODE_DISABLED;
    return options;
}

void OH_ArkUI_TextSelectionMenuOptions_Dispose(ArkUI_TextSelectionMenuOptions* selectionMenuOptions)
{
    if (!selectionMenuOptions) {
        return;
    }
    delete selectionMenuOptions;
    selectionMenuOptions = nullptr;
}

ArkUI_ErrorCode OH_ArkUI_TextSelectionMenuOptions_SetSpanType(
    ArkUI_TextSelectionMenuOptions* selectionMenuOptions, ArkUI_TextSpanType textSpanType)
{
    CHECK_NULL_RETURN(selectionMenuOptions, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    selectionMenuOptions->textSpanType = textSpanType;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextSelectionMenuOptions_GetSpanType(
    ArkUI_TextSelectionMenuOptions* selectionMenuOptions, ArkUI_TextSpanType* textSpanType)
{
    CHECK_NULL_RETURN(selectionMenuOptions, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(textSpanType, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *textSpanType = selectionMenuOptions->textSpanType;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextSelectionMenuOptions_SetContentNode(
    ArkUI_TextSelectionMenuOptions* selectionMenuOptions, ArkUI_NodeHandle node)
{
    CHECK_NULL_RETURN(selectionMenuOptions, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(node, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    selectionMenuOptions->contentNode = node;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextSelectionMenuOptions_GetContentNode(
    ArkUI_TextSelectionMenuOptions* selectionMenuOptions, ArkUI_NodeHandle* node)
{
    CHECK_NULL_RETURN(selectionMenuOptions, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(node, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *node = selectionMenuOptions->contentNode;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextSelectionMenuOptions_SetResponseType(
    ArkUI_TextSelectionMenuOptions* selectionMenuOptions, ArkUI_TextResponseType responseType)
{
    CHECK_NULL_RETURN(selectionMenuOptions, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    selectionMenuOptions->textResponseType = responseType;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextSelectionMenuOptions_GetResponseType(
    ArkUI_TextSelectionMenuOptions* selectionMenuOptions, ArkUI_TextResponseType* responseType)
{
    CHECK_NULL_RETURN(selectionMenuOptions, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(responseType, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *responseType = selectionMenuOptions->textResponseType;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextSelectionMenuOptions_SetHapticFeedbackMode(
    ArkUI_TextSelectionMenuOptions* selectionMenuOptions, ArkUI_HapticFeedbackMode hapticFeedbackMode)
{
    CHECK_NULL_RETURN(selectionMenuOptions, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    selectionMenuOptions->hapticFeedbackMode = hapticFeedbackMode;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextSelectionMenuOptions_GetHapticFeedbackMode(
    ArkUI_TextSelectionMenuOptions* selectionMenuOptions, ArkUI_HapticFeedbackMode* hapticFeedbackMode)
{
    CHECK_NULL_RETURN(selectionMenuOptions, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(hapticFeedbackMode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *hapticFeedbackMode = selectionMenuOptions->hapticFeedbackMode;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextSelectionMenuOptions_RegisterOnMenuShowCallback(
    ArkUI_TextSelectionMenuOptions* selectionMenuOptions, void* userData,
    void (*callback)(int32_t start, int32_t end, void* userData))
{
    CHECK_NULL_RETURN(selectionMenuOptions, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(callback, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    selectionMenuOptions->onMenuShow = reinterpret_cast<void*>(callback);
    selectionMenuOptions->onMenuShowUserData = userData;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextSelectionMenuOptions_RegisterOnMenuHideCallback(
    ArkUI_TextSelectionMenuOptions* selectionMenuOptions, void* userData,
    void (*callback)(int32_t start, int32_t end, void* userData))
{
    CHECK_NULL_RETURN(selectionMenuOptions, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(callback, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    selectionMenuOptions->onMenuHide = reinterpret_cast<void*>(callback);
    selectionMenuOptions->onMenuHideUserData = userData;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

void OH_ArkUI_TextContentBaseController_ScrollToVisible(
    ArkUI_TextContentBaseController* controller, int32_t start, int32_t end)
{
    CHECK_NULL_VOID(controller);
    auto fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    if (controller->textFieldType == NODE_TEXT_INPUT_TEXT_CONTENT_CONTROLLER_BASE) {
        fullImpl->getNodeModifiers()->getTextInputModifier()->scrollToVisible(
            controller->node->uiNodeHandle, start, end);
        return;
    }
    if (controller->textFieldType == NODE_TEXT_AREA_TEXT_CONTENT_CONTROLLER_BASE) {
        fullImpl->getNodeModifiers()->getTextAreaModifier()->scrollToVisible(
            controller->node->uiNodeHandle, start, end);
    }
}
ArkUI_TextMarqueeOptions* OH_ArkUI_TextMarqueeOptions_Create()
{
    ArkUI_TextMarqueeOptions* option = new ArkUI_TextMarqueeOptions();
    option->step = -1.0f;
    option->delay = 0;
    option->loop = -1;
    option->marqueeStartPolicy = ArkUI_MarqueeStartPolicy::ARKUI_MARQUEESTARTPOLICY_DEFAULT;
    option->start = true;
    option->fromStart = true;
    option->fadeout = false;
    option->marqueeUpdatePolicy = ArkUI_MarqueeUpdatePolicy::ARKUI_MARQUEEUPDATEPOLICY_DEFAULT;
    option->spacing = -1.0f;
    return option;
}

void OH_ArkUI_TextMarqueeOptions_Dispose(ArkUI_TextMarqueeOptions* option)
{
    if (!option) {
        return;
    }
    delete option;
}

void OH_ArkUI_TextMarqueeOptions_SetStart(ArkUI_TextMarqueeOptions* option, bool start)
{
    CHECK_NULL_VOID(option);
    option->start = start;
}

bool OH_ArkUI_TextMarqueeOptions_GetStart(ArkUI_TextMarqueeOptions* option)
{
    CHECK_NULL_RETURN(option, false);
    return option->start;
}

void OH_ArkUI_TextMarqueeOptions_SetStep(ArkUI_TextMarqueeOptions* option, float step)
{
    CHECK_NULL_VOID(option);
    option->step = step;
}

float OH_ArkUI_TextMarqueeOptions_GetStep(ArkUI_TextMarqueeOptions* option)
{
    CHECK_NULL_RETURN(option, 0.0f);
    return option->step;
}

void OH_ArkUI_TextMarqueeOptions_SetSpacing(ArkUI_TextMarqueeOptions* option, float spacing)
{
    CHECK_NULL_VOID(option);
    option->spacing = spacing;
}

float OH_ArkUI_TextMarqueeOptions_GetSpacing(ArkUI_TextMarqueeOptions* option)
{
    CHECK_NULL_RETURN(option, 0.0f);
    return option->spacing;
}

void OH_ArkUI_TextMarqueeOptions_SetLoop(ArkUI_TextMarqueeOptions* option, int32_t loop)
{
    CHECK_NULL_VOID(option);
    option->loop = loop;
}

int32_t OH_ArkUI_TextMarqueeOptions_GetLoop(ArkUI_TextMarqueeOptions* option)
{
    CHECK_NULL_RETURN(option, 0);
    return option->loop;
}

void OH_ArkUI_TextMarqueeOptions_SetFromStart(ArkUI_TextMarqueeOptions* option, bool fromStart)
{
    CHECK_NULL_VOID(option);
    option->fromStart = fromStart;
}

bool OH_ArkUI_TextMarqueeOptions_GetFromStart(ArkUI_TextMarqueeOptions* option)
{
    CHECK_NULL_RETURN(option, false);
    return option->fromStart;
}

void OH_ArkUI_TextMarqueeOptions_SetDelay(ArkUI_TextMarqueeOptions* option, int32_t delay)
{
    CHECK_NULL_VOID(option);
    option->delay = delay;
}

int32_t OH_ArkUI_TextMarqueeOptions_GetDelay(ArkUI_TextMarqueeOptions* option)
{
    CHECK_NULL_RETURN(option, 0);
    return option->delay;
}

void OH_ArkUI_TextMarqueeOptions_SetFadeout(ArkUI_TextMarqueeOptions* option, bool fadeout)
{
    CHECK_NULL_VOID(option);
    option->fadeout = fadeout;
}

bool OH_ArkUI_TextMarqueeOptions_GetFadeout(ArkUI_TextMarqueeOptions* option)
{
    CHECK_NULL_RETURN(option, false);
    return option->fadeout;
}

void OH_ArkUI_TextMarqueeOptions_SetStartPolicy(ArkUI_TextMarqueeOptions* option, ArkUI_MarqueeStartPolicy startPolicy)
{
    CHECK_NULL_VOID(option);
    option->marqueeStartPolicy = startPolicy;
}

ArkUI_MarqueeStartPolicy OH_ArkUI_TextMarqueeOptions_GetStartPolicy(ArkUI_TextMarqueeOptions* option)
{
    CHECK_NULL_RETURN(option, ArkUI_MarqueeStartPolicy::ARKUI_MARQUEESTARTPOLICY_DEFAULT);
    return option->marqueeStartPolicy;
}

void OH_ArkUI_TextMarqueeOptions_SetUpdatePolicy(ArkUI_TextMarqueeOptions* option,
    ArkUI_MarqueeUpdatePolicy updatePolicy)
{
    CHECK_NULL_VOID(option);
    option->marqueeUpdatePolicy = updatePolicy;
}

ArkUI_MarqueeUpdatePolicy OH_ArkUI_TextMarqueeOptions_GetUpdatePolicy(ArkUI_TextMarqueeOptions* option)
{
    CHECK_NULL_RETURN(option, ArkUI_MarqueeUpdatePolicy::ARKUI_MARQUEEUPDATEPOLICY_DEFAULT);
    return option->marqueeUpdatePolicy;
}


ArkUI_SelectedDragPreviewStyle* OH_ArkUI_SelectedDragPreviewStyle_Create()
{
    ArkUI_SelectedDragPreviewStyle* options = new ArkUI_SelectedDragPreviewStyle();
    return options;
}

void OH_ArkUI_SelectedDragPreviewStyle_Dispose(ArkUI_SelectedDragPreviewStyle* config)
{
    if (!config) {
        return;
    }
    delete config;
    config = nullptr;
}

void OH_ArkUI_SelectedDragPreviewStyle_SetColor(
    ArkUI_SelectedDragPreviewStyle* config, uint32_t color)
{
    CHECK_NULL_VOID(config);
    config->color = {1, color};
}

uint32_t OH_ArkUI_SelectedDragPreviewStyle_GetColor(
    ArkUI_SelectedDragPreviewStyle* config)
{
    CHECK_NULL_RETURN(config, -1);
    return config->color.value;
}
#ifdef __cplusplus
}
#endif
