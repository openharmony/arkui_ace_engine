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

#ifndef DRAGANDDROP_SECONDMODULE_H
#define DRAGANDDROP_SECONDMODULE_H

#include "common.h"
#include "container.h"
#include <arkui/drag_and_drop.h>
#include <arkui/native_node.h>
#include <arkui/native_type.h>
#include <database/udmf/udmf_meta.h>
#include <hilog/log.h>

namespace NativeXComponentSample {

ArkUI_NodeHandle dragImage = nullptr;
ArkUI_NodeHandle dropImage = nullptr;
bool dragResult = true;

void SetImageDataLoadParams1(ArkUI_DragEvent* dragEvent)
{
    // 异步传输拖拽数据
    OH_UdmfDataLoadParams *dataLoadParams = OH_UdmfDataLoadParams_Create();
    OH_UdmfDataLoadInfo *info = OH_UdmfDataLoadInfo_Create();
    OH_UdmfDataLoadInfo_SetType(info, "general.image");
    OH_UdmfDataLoadInfo_SetRecordCount(info, 1);
    OH_UdmfDataLoadParams_SetDataLoadInfo(dataLoadParams, info);
    OH_Udmf_DataLoadHandler dataLoadHandler = [](OH_UdmfDataLoadInfo *acceptableInfo) {
        OH_UdmfRecord *record = OH_UdmfRecord_Create();
        OH_UdsFileUri *imageValue = OH_UdsFileUri_Create();
        int returnValue = OH_UdsFileUri_SetFileUri(imageValue, "/resources/base/media/startIcon.png");
        returnValue = OH_UdmfRecord_AddFileUri(record, imageValue);
        OH_UdmfData *data = OH_UdmfData_Create();
        int dataCount = 6000;
        for (int i = 0; i < dataCount; i++) {
            returnValue = OH_UdmfData_AddRecord(data, record);
        }
        return data;
    };
    OH_UdmfDataLoadParams_SetLoadHandler(dataLoadParams, dataLoadHandler);
    OH_ArkUI_DragEvent_SetDataLoadParams(dragEvent, dataLoadParams);
}

void StartDataLoadingSecond1(ArkUI_DragEvent* dragEvent)
{
    // 异步流程
    int32_t count = 0;
    int returnValue = OH_ArkUI_DragEvent_GetDataTypeCount(dragEvent, &count);
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest", "GetDataTypesCount = %{public}d", count);

    char stringArray[count][128];
    char *dataTypes[128];
    for (int i = 0; i < count; i++) {
        dataTypes[i] = stringArray[i];
    }
    returnValue = OH_ArkUI_DragEvent_GetDataTypes(dragEvent, dataTypes, count, MAX_LENGTH);
    for (int32_t i = 0; i < count; ++i) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest",
            "GetDataTypes result [ %{public}d ] = %{public}s", i, dataTypes[i]);
    }

    OH_Udmf_DataProgressListener dataProgressListener = [](OH_Udmf_ProgressInfo *progressInfo,
        OH_UdmfData *data) {
        int32_t progress = OH_UdmfProgressInfo_GetProgress(progressInfo);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest",
            "OH_ArkUI_DragEvent_StartDataLoading progressInfo = %{public}d", progress);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest", "dataProgressListener callback");
        bool resultUdmf = OH_UdmfData_HasType(data, UDMF_META_GENERAL_FILE);
        if (resultUdmf) {
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest",
                "NODE_ON_DROP has UDMF_META_GENERAL_FILE");
            unsigned int recordsCount = 0;
            OH_UdmfRecord **records = OH_UdmfData_GetRecords(data, &recordsCount);
            // 获取records中的元素
            int returnStatus;
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest", "recordsCount = %{public}d",
                recordsCount);
            for (int i = 0; i < recordsCount; i++) {
                // 从OH_UdmfRecord中获取文件类型数据
                OH_UdsFileUri *imageValue = OH_UdsFileUri_Create();
                returnStatus = OH_UdmfRecord_GetFileUri(records[i], imageValue);
                const char *fileUri = OH_UdsFileUri_GetFileUri(imageValue);
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest",
                    "returnStatus = %{public}d fileUri = %{public}s", returnStatus, fileUri);
                // 使用结束后销毁指针
                OH_UdsFileUri_Destroy(imageValue);
            }
            OH_ArkUI_NotifyDragResult(g_requestIdentify, ARKUI_DRAG_RESULT_SUCCESSFUL);
            OH_ArkUI_NotifyDragEndPendingDone(g_requestIdentify);
        }
    };
    OH_UdmfGetDataParams *params = OH_UdmfGetDataParams_Create();
    OH_UdmfGetDataParams_SetFileConflictOptions(params, Udmf_FileConflictOptions::UDMF_OVERWRITE);
    OH_UdmfGetDataParams_SetProgressIndicator(params, Udmf_ProgressIndicator::UDMF_DEFAULT);
    OH_UdmfGetDataParams_SetDataProgressListener(params, dataProgressListener);
    OH_ArkUI_DragEvent_StartDataLoading(dragEvent, params, key, UDMF_KEY_BUFFER_LEN);
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest",
        "OH_ArkUI_DragEvent_StartDataLoading key = %{public}s", key);
    OH_UdmfGetDataParams_Destroy(params);
}

void GetSecondDragResult1(ArkUI_DragEvent* dragEvent)
{
    ArkUI_DragResult result;
    OH_ArkUI_DragEvent_GetDragResult(dragEvent, &result);
    if (result == ARKUI_DRAG_RESULT_SUCCESSFUL && dragResult == true) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest", "Drag Successful!");
        nodeAPI->resetAttribute(dragImage, NODE_IMAGE_SRC);
        SetImageSrc(dropImage, "/resources/base/media/startIcon.png");
    } else {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest", "Drag Failed!");
    }
    dragResult = true;
}

void RegisterNodeEventSecondReceiver1(ArkUI_NodeHandle &dragNode)
{
    if (!nodeAPI) {
        return;
    }

    nodeAPI->addNodeEventReceiver(dragNode, [](ArkUI_NodeEvent *event) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest", "RegisterNodeEventSecondReceiver called");
        auto eventType = OH_ArkUI_NodeEvent_GetEventType(event);
        auto preDragStatus = OH_ArkUI_NodeEvent_GetPreDragStatus(event);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest",
            "eventType = %{public}d, preDragStatus = %{public}d", eventType, preDragStatus);

        auto *dragEvent = OH_ArkUI_NodeEvent_GetDragEvent(event);
        switch (eventType) {
            case NODE_ON_PRE_DRAG: {
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest", "NODE_ON_PRE_DRAG EventReceiver");
                break;
            }
            case NODE_ON_DRAG_START: {
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest", "NODE_ON_DRAG_START EventReceiver");
                SetImageDataLoadParams1(dragEvent);
                break;
            }
            case NODE_ON_DRAG_END: {
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest", "NODE_ON_DRAG_END EventReceiver");
                GetSecondDragResult1(dragEvent);
                break;
            }
            default: {
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest", "UNKNOWN EventReceiver");
                break;
            }
        }
    });
}

void RegisterNodeEventSecondReceiver2(ArkUI_NodeHandle &dropNode)
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
                OH_ArkUI_DragEvent_DisableDefaultDropAnimation(dragEvent, true);
                OH_ArkUI_DragEvent_RequestDragEndPending(dragEvent, &g_requestIdentify);
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest",
                    "OH_ArkUI_DragEvent_RequestDragEndPending called");
                StartDataLoadingSecond1(dragEvent);
                break;
            }
            case NODE_ON_DRAG_ENTER: {
                OH_ArkUI_DragEvent_SetSuggestedDropOperation(dragEvent, ARKUI_DROP_OPERATION_COPY);
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest", "NODE_ON_DRAG_ENTER EventReceiver");
                break;
            }
            case NODE_ON_DRAG_MOVE: {
                OH_ArkUI_DragEvent_SetSuggestedDropOperation(dragEvent, ARKUI_DROP_OPERATION_COPY);
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest", "NODE_ON_DRAG_MOVE EventReceiver");
                break;
            }
            case NODE_ON_DRAG_LEAVE: {
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest", "NODE_ON_DRAG_LEAVE EventReceiver");
                break;
            }
            default: {
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "dragTest", "UNKNOWN EventReceiver");
                break;
            }
        }
    });
}

void SecondButtonModule(ArkUI_NodeHandle &column)
{
    auto buttonRow = nodeAPI->createNode(ARKUI_NODE_ROW);
    nodeAPI->addChild(column, buttonRow);

    auto resetButton = nodeAPI->createNode(ARKUI_NODE_BUTTON);
    SetButtonLabel(resetButton, "复位");
    nodeAPI->registerNodeEvent(resetButton, NODE_ON_CLICK_EVENT, 1, nullptr);
    nodeAPI->addNodeEventReceiver(resetButton, [](ArkUI_NodeEvent *event) {
        nodeAPI->resetAttribute(dropImage, NODE_IMAGE_SRC);
        SetImageSrc(dragImage, "/resources/base/media/startIcon.png");
    });
    nodeAPI->addChild(buttonRow, resetButton);

    auto blank = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    SetWidth(blank, BLANK_10);
    nodeAPI->addChild(buttonRow, blank);

    auto cancelLoadButton = nodeAPI->createNode(ARKUI_NODE_BUTTON);
    SetButtonLabel(cancelLoadButton, "取消异步获取拖拽数据");
    nodeAPI->registerNodeEvent(cancelLoadButton, NODE_ON_CLICK_EVENT, 1, nullptr);
    nodeAPI->addNodeEventReceiver(cancelLoadButton, [](ArkUI_NodeEvent *event) {
        int ret = OH_ArkUI_CancelDataLoading(context, key);
        if (ret == 0) {
            dragResult = false;
        }
    });
    nodeAPI->addChild(buttonRow, cancelLoadButton);
}

void SecondModule(ArkUI_NodeHandle &root)
{
    auto column2 = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    SetWidthPercent(column2, 1);
    SetColumnJustifyContent(column2, ARKUI_FLEX_ALIGNMENT_START);
    SetColumnAlignItem(column2, ARKUI_HORIZONTAL_ALIGNMENT_START);
    SetPadding(column2, BLANK_10);
    SetBorderWidth(column2, BORDER_WIDTH_1);
    SetBorderStyle(column2, ARKUI_BORDER_STYLE_DASHED, DEFAULT_RADIUS);

    auto title = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(title, "异步拖拽示例：", TEXT_FONT_SIZE_15, SIZE_140, SIZE_20);
    nodeAPI->addChild(column2, title);

    auto dragRow = nodeAPI->createNode(ARKUI_NODE_ROW);
    SetRowAlignItem(dragRow, ARKUI_VERTICAL_ALIGNMENT_TOP);

    nodeAPI->addChild(column2, dragRow);

    // 拖拽图像
    auto dragColumn = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    auto dragText = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(dragText, "请长按拖拽图像", TEXT_FONT_SIZE_15, SIZE_140, SIZE_20);
    dragImage = nodeAPI->createNode(ARKUI_NODE_IMAGE);
    SetId(dragImage, "dragImage");
    SetCommonAttribute(dragImage, SIZE_140, SIZE_140, DEFAULT_BG_COLOR, BLANK_5);
    SetImageSrc(dragImage, "/resources/base/media/startIcon.png");
    OH_ArkUI_SetNodeDraggable(dragImage, true);
    nodeAPI->registerNodeEvent(dragImage, NODE_ON_PRE_DRAG, 1, nullptr);
    nodeAPI->registerNodeEvent(dragImage, NODE_ON_DRAG_START, 1, nullptr);
    nodeAPI->registerNodeEvent(dragImage, NODE_ON_DRAG_END, 1, nullptr);
    nodeAPI->addChild(dragColumn, dragText);
    nodeAPI->addChild(dragColumn, dragImage);

    nodeAPI->addChild(dragRow, dragColumn);
    
    // 拖拽落入区域
    auto dropColumn = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    auto dropText = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(dropText, "拖拽落入区域", TEXT_FONT_SIZE_15, SIZE_140, SIZE_20);
    dropImage = nodeAPI->createNode(ARKUI_NODE_IMAGE);
    SetId(dropImage, "dropImage");
    SetCommonAttribute(dropImage, SIZE_140, SIZE_140, DEFAULT_BG_COLOR, BLANK_5);
    SetBorderWidth(dropImage, BORDER_WIDTH_1);
    OH_ArkUI_SetNodeDraggable(dropImage, false);
    OH_ArkUI_DisableDropDataPrefetchOnNode(dropImage, true);
    nodeAPI->registerNodeEvent(dropImage, NODE_ON_DROP, 1, nullptr);
    nodeAPI->registerNodeEvent(dropImage, NODE_ON_DRAG_MOVE, 1, nullptr);
    nodeAPI->registerNodeEvent(dropImage, NODE_ON_DRAG_ENTER, 1, nullptr);
    nodeAPI->registerNodeEvent(dropImage, NODE_ON_DRAG_LEAVE, 1, nullptr);
    nodeAPI->addChild(dropColumn, dropText);
    nodeAPI->addChild(dropColumn, dropImage);

    nodeAPI->addChild(dragRow, dropColumn);

    SecondButtonModule(column2);

    nodeAPI->addChild(root, column2);

    RegisterNodeEventSecondReceiver1(dragImage);
    RegisterNodeEventSecondReceiver2(dropImage);
}

} // namespace NativeXComponentSample

#endif // DRAGANDDROP_SECONDMODULE_H