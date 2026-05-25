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

#ifndef DRAGANDDROP_THIRDMODULE_H
#define DRAGANDDROP_THIRDMODULE_H

#include "common.h"
#include "container.h"
#include <arkui/drag_and_drop.h>
#include <arkui/native_node.h>
#include <arkui/native_type.h>
#include <hilog/log.h>
#include <thread>
#include <unistd.h>

namespace NativeXComponentSample {

ArkUI_NodeHandle dragImage2 = nullptr;
ArkUI_NodeHandle dropImage2 = nullptr;
// [Start drag_start]
void SetImageData(ArkUI_DragEvent* dragEvent)
{
    int returnValue;
    OH_UdmfRecord *record = OH_UdmfRecord_Create();
    OH_UdsFileUri *imageValue = OH_UdsFileUri_Create();
    // 图片src/main/resources/base/media/startIcon.png需要替换为开发者所需的资源文件
    returnValue = OH_UdsFileUri_SetFileUri(imageValue, "/resources/base/media/startIcon.png");
    returnValue = OH_UdmfRecord_AddFileUri(record, imageValue);
    OH_UdmfData *data = OH_UdmfData_Create();
    returnValue = OH_UdmfData_AddRecord(data, record);
    returnValue = OH_ArkUI_DragEvent_SetData(dragEvent, data);
}
// [StartExclude drag_start]

void ExecuteDragPending(ArkUI_DragEvent* dragEvent)
{
    int32_t requestId = -1;
    auto ret = OH_ArkUI_DragEvent_RequestDragEndPending(dragEvent, &requestId);
    if (ret == ARKUI_ERROR_CODE_DRAG_DROP_OPERATION_NOT_ALLOWED) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "dragTest", "The operation is not allowed!");
        return;
    }
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest",
        "NODE_ON_DROP get id = %{public}d, ret = %{public}d", requestId, ret);
    std::thread tt([requestId]() {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest", "NODE_ON_DROP_ASYNC 1");
        sleep(1);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest", "NODE_ON_DROP_ASYNC 2");
        OH_ArkUI_NotifyDragResult(requestId, ARKUI_DRAG_RESULT_SUCCESSFUL);
        OH_ArkUI_NotifyDragEndPendingDone(requestId);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest", "NODE_ON_DROP_ASYNC");
    });
    tt.detach();
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest", "NODE_ON_DROP_DONE");
}

void GetThirdDragResult(ArkUI_DragEvent* dragEvent)
{
    ArkUI_DragResult result;
    OH_ArkUI_DragEvent_GetDragResult(dragEvent, &result);
    if (result == ARKUI_DRAG_RESULT_SUCCESSFUL) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest", "Drag Successful!");
        nodeAPI->resetAttribute(dragImage2, NODE_IMAGE_SRC);
        SetImageSrc(dropImage2, "/resources/base/media/startIcon.png");
    } else if (result == ARKUI_DRAG_RESULT_FAILED) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest", "Drag Failed!");
    }
}

void RegisterNodeEventThirdReceiver1(ArkUI_NodeHandle &dragNode)
{
    if (!nodeAPI) {
        return;
    }

    nodeAPI->addNodeEventReceiver(dragNode, [](ArkUI_NodeEvent *event) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest", "RegisterNodeEventThirdReceiver called");
        auto eventType = OH_ArkUI_NodeEvent_GetEventType(event);
        auto preDragStatus = OH_ArkUI_NodeEvent_GetPreDragStatus(event);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest",
            "eventType = %{public}d, preDragStatus = %{public}d", eventType, preDragStatus);
        auto *dragEvent = OH_ArkUI_NodeEvent_GetDragEvent(event);
        switch (eventType) {
            // [EndExclude drag_start]
            case NODE_ON_DRAG_START: {
                OH_LOG_Print(LOG_APP, LOG_INFO, 0xFF00U, "dragTest", "NODE_ON_DRAG_START EventReceiver");
                SetImageData(dragEvent);
                break;
            }
            // [End drag_start]
            case NODE_ON_DRAG_END: {
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest", "NODE_ON_DRAG_END EventReceiver");
                GetThirdDragResult(dragEvent);
                break;
            }
            default: {
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest", "UNKNOWN EventReceiver");
                break;
            }
        }
    });
}

void RegisterNodeEventThirdReceiver2(ArkUI_NodeHandle &dropNode)
{
    if (!nodeAPI) {
        return;
    }

    nodeAPI->addNodeEventReceiver(dropNode, [](ArkUI_NodeEvent *event) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest", "RegisterNodeEventSecondReceiver called");
        auto eventType = OH_ArkUI_NodeEvent_GetEventType(event);
        auto preDragStatus = OH_ArkUI_NodeEvent_GetPreDragStatus(event);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest",
            "eventType = %{public}d, preDragStatus = %{public}d",
            eventType, preDragStatus);
        auto *dragEvent = OH_ArkUI_NodeEvent_GetDragEvent(event);
        switch (eventType) {
            case NODE_ON_DROP: {
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest", "NODE_ON_DROP EventReceiver");
                ExecuteDragPending(dragEvent);
                break;
            }
            default: {
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest", "UNKNOWN EventReceiver");
                break;
            }
        }
    });
}

void ResetButton(ArkUI_NodeHandle &column)
{
    auto resetButton = nodeAPI->createNode(ARKUI_NODE_BUTTON);
    SetButtonLabel(resetButton, "复位");
    nodeAPI->registerNodeEvent(resetButton, NODE_ON_CLICK_EVENT, 1, nullptr);
    nodeAPI->addNodeEventReceiver(resetButton, [](ArkUI_NodeEvent *event) {
        nodeAPI->resetAttribute(dropImage2, NODE_IMAGE_SRC);
        SetImageSrc(dragImage2, "/resources/base/media/startIcon.png");
    });
    nodeAPI->addChild(column, resetButton);
}

void ThirdModule(ArkUI_NodeHandle &root)
{
    auto column3 = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    SetWidthPercent(column3, 1);
    SetColumnJustifyContent(column3, ARKUI_FLEX_ALIGNMENT_START);
    SetColumnAlignItem(column3, ARKUI_HORIZONTAL_ALIGNMENT_START);
    SetPadding(column3, BLANK_10);
    SetBorderWidth(column3, BORDER_WIDTH_1);
    SetBorderStyle(column3, ARKUI_BORDER_STYLE_DASHED, DEFAULT_RADIUS);

    auto title = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(title, "延迟处理拖拽示例：", TEXT_FONT_SIZE_15, SIZE_140, SIZE_20);
    nodeAPI->addChild(column3, title);

    auto dragRow = nodeAPI->createNode(ARKUI_NODE_ROW);
    SetRowAlignItem(dragRow, ARKUI_VERTICAL_ALIGNMENT_TOP);

    nodeAPI->addChild(column3, dragRow);

    // 拖拽图像
    auto dragColumn = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    auto dragText = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(dragText, "请长按拖拽图像", TEXT_FONT_SIZE_15, SIZE_140, SIZE_20);
    // [Start create_imageNode]
    dragImage2 = nodeAPI->createNode(ARKUI_NODE_IMAGE);
    SetId(dragImage2, "dragImage");
    SetCommonAttribute(dragImage2, 140.0f, 140.0f, 0xFFFFFFFF, 5.0f);
    // 图片src/main/resources/base/media/startIcon.png需要替换为开发者所需的资源文件
    SetImageSrc(dragImage2, "/resources/base/media/startIcon.png");
    OH_ArkUI_SetNodeDraggable(dragImage2, true);
    nodeAPI->registerNodeEvent(dragImage2, NODE_ON_DRAG_START, 1, nullptr);
    // [End create_imageNode]
    nodeAPI->registerNodeEvent(dragImage2, NODE_ON_DRAG_END, 1, nullptr);
    nodeAPI->addChild(dragColumn, dragText);
    nodeAPI->addChild(dragColumn, dragImage2);

    nodeAPI->addChild(dragRow, dragColumn);

    // 拖拽落入区域
    auto dropColumn = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    auto dropText = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(dropText, "拖拽落入区域", TEXT_FONT_SIZE_15, SIZE_140, SIZE_20);
    dropImage2 = nodeAPI->createNode(ARKUI_NODE_IMAGE);
    SetId(dropImage2, "dropImage");
    SetCommonAttribute(dropImage2, SIZE_140, SIZE_140, DEFAULT_BG_COLOR, BLANK_5);
    SetBorderWidth(dropImage2, BORDER_WIDTH_1);
    OH_ArkUI_SetNodeDraggable(dropImage2, false);
    OH_ArkUI_DisableDropDataPrefetchOnNode(dropImage2, true);
    nodeAPI->registerNodeEvent(dropImage2, NODE_ON_DROP, 1, nullptr);
    nodeAPI->addChild(dropColumn, dropText);
    nodeAPI->addChild(dropColumn, dropImage2);

    nodeAPI->addChild(dragRow, dropColumn);

    ResetButton(column3);

    nodeAPI->addChild(root, column3);

    RegisterNodeEventThirdReceiver1(dragImage2);
    RegisterNodeEventThirdReceiver2(dropImage2);
}

} // namespace NativeXComponentSample

#endif // DRAGANDDROP_THIRDMODULE_H