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

#include "napi/native_api.h"
#include <ace/xcomponent/native_interface_xcomponent.h>
#include <arkui/native_animate.h>
#include <arkui/native_gesture.h>
#include <arkui/native_interface.h>
#include <arkui/native_key_event.h>
#include <arkui/native_node.h>
#include <arkui/native_node_napi.h>
#include <arkui/native_type.h>
#include <cstdint>
#include <cstdio>
#include <hilog/log.h>
#include <iostream>
#include <string>

#include "manager.h"


namespace NativeXComponentSample {
Manager Manager::manager_;

Manager::~Manager()
{
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "~Manager");
    for (auto iter = nativeXComponentMap_.begin(); iter != nativeXComponentMap_.end(); ++iter) {
        if (iter->second != nullptr) {
            iter->second = nullptr;
        }
    }
    nativeXComponentMap_.clear();

    for (auto iter = containerMap_.begin(); iter != containerMap_.end(); ++iter) {
        if (iter->second != nullptr) {
            delete iter->second;
            iter->second = nullptr;
        }
    }
    containerMap_.clear();
}

static ArkUI_NativeNodeAPI_1 *nodeAPI = nullptr;
static ArkUI_NativeGestureAPI_1 *gestureApi = nullptr;
static ArkUI_NativeGestureAPI_2 *gestureApi2 = nullptr;
static const int NUM_6 = 6;
static const int CHILD_SIZE = 20;

namespace {

void SetGestureEnableState(float offsetY, ArkUI_GestureRecognizer *childRecognizer,
                           ArkUI_GestureRecognizer *currentRecognizer, ArkUI_GestureEventTargetInfo *childTargetInfo,
                           ArkUI_GestureEventTargetInfo *currentTargetInfo)
{
    // 获取当前父子组件的滚动容器状态
    bool childIsEnd = false;
    OH_ArkUI_GestureEventTargetInfo_IsScrollEnd(childTargetInfo, &childIsEnd);
    bool childIsBegin = false;
    auto errorCode = OH_ArkUI_GestureEventTargetInfo_IsScrollBegin(childTargetInfo, &childIsBegin);
    if (errorCode == ARKUI_ERROR_CODE_NON_SCROLLABLE_CONTAINER) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "not scrollable container");
    }
    bool currentIsEnd = false;
    OH_ArkUI_GestureEventTargetInfo_IsScrollEnd(currentTargetInfo, &currentIsEnd);
    bool currentIsBegin = false;
    OH_ArkUI_GestureEventTargetInfo_IsScrollBegin(currentTargetInfo, &currentIsBegin);
    if (offsetY < 0) {
        if (currentIsEnd) {
            // 当父组件已经到达底部时，继续向上滑动时，设置子组件滑动，父组件禁止滑动
            OH_ArkUI_SetGestureRecognizerEnabled(childRecognizer, true);
            OH_ArkUI_SetGestureRecognizerEnabled(currentRecognizer, false);
        } else {
            // 当父组件没有到达底部时，继续向上滑动时，设置子组件禁止滑动，父组件滑动
            OH_ArkUI_SetGestureRecognizerEnabled(childRecognizer, false);
            OH_ArkUI_SetGestureRecognizerEnabled(currentRecognizer, true);
        }
    } else if (offsetY > 0) {
        if (childIsBegin) {
            // 当子组件到达顶部时，继续向下滑动时，设置子组件禁止滑动，父组件滑动
            OH_ArkUI_SetGestureRecognizerEnabled(childRecognizer, false);
            OH_ArkUI_SetGestureRecognizerEnabled(currentRecognizer, true);
        } else {
            // 当子组件没有到达顶部时，继续向下滑动时，设置子组件滑动，父组件禁止滑动
            OH_ArkUI_SetGestureRecognizerEnabled(childRecognizer, true);
            OH_ArkUI_SetGestureRecognizerEnabled(currentRecognizer, false);
        }
    }
}

// 子组件自定义手势判定回调
ArkUI_GestureInterruptResult ChildGestureInterruptFunc(ArkUI_GestureInterruptInfo *info)
{
    auto manager = NativeXComponentSample::Manager::GetInstance();
    if (!manager) {
        return ArkUI_GestureInterruptResult::GESTURE_INTERRUPT_RESULT_CONTINUE;
    }
    // 获取自定义手势判定回调中的用户自定义信息
    int *userData = reinterpret_cast<int *>(OH_ArkUI_GestureInterrupter_GetUserData(info));
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "ArkUI_GestureInterruptInfo userData is %{public}d",
                 *userData);
    auto currentRecognizer = manager->GetCurrentRecognizer();
    auto childRecognizer = manager->GetChildRecognizer();
    char *nodeId = (char *)malloc(sizeof(char) * NUM_6);
    int result = 0;
    // 获取手势绑定的节点的inspectorId
    auto errorCode = OH_ArkUI_GetGestureBindNodeId(currentRecognizer, nodeId, NUM_6, &result);
    if (errorCode == ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "buffer size is not enough");
    }
    char *childNodeId = (char *)malloc(sizeof(char) * NUM_6);
    int childResult = 0;
    // 获取手势绑定的节点的inspectorId
    OH_ArkUI_GetGestureBindNodeId(childRecognizer, childNodeId, NUM_6, &childResult);
    if (!gestureApi) {
        return ArkUI_GestureInterruptResult::GESTURE_INTERRUPT_RESULT_CONTINUE;
    }
    ArkUI_GestureDirectionMask mask;
    // 获取pan手势的方向
    OH_ArkUI_GetPanGestureDirectionMask(currentRecognizer, &mask);
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "currentRecognizer direction mask is %{public}d",
                 mask);
    if (strcmp(nodeId, "outer") == 0 && OH_ArkUI_IsBuiltInGesture(currentRecognizer) &&
        gestureApi->getGestureType(currentRecognizer) == ArkUI_GestureRecognizerType::PAN_GESTURE &&
        strcmp(childNodeId, "inner") == 0) {
        ArkUI_GestureEvent *event = OH_ArkUI_GestureInterruptInfo_GetGestureEvent(info);
        if (!event) {
            return ArkUI_GestureInterruptResult::GESTURE_INTERRUPT_RESULT_CONTINUE;
        }
        // 获取手势的垂直位移
        auto offsetY = OH_ArkUI_PanGesture_GetOffsetY(event);
        ArkUI_GestureEventTargetInfo *childTargetInfo;
        OH_ArkUI_GetGestureEventTargetInfo(childRecognizer, &childTargetInfo);
        ArkUI_GestureEventTargetInfo *currentTargetInfo;
        OH_ArkUI_GetGestureEventTargetInfo(currentRecognizer, &currentTargetInfo);
        if (!childTargetInfo || !currentTargetInfo) {
            return ArkUI_GestureInterruptResult::GESTURE_INTERRUPT_RESULT_CONTINUE;
        }
        SetGestureEnableState(offsetY, childRecognizer, currentRecognizer, childTargetInfo, currentTargetInfo);
    }
    return ArkUI_GestureInterruptResult::GESTURE_INTERRUPT_RESULT_CONTINUE;
}

// 父组件自定义手势判定回调
ArkUI_GestureInterruptResult GestureInterruptFunc(ArkUI_GestureInterruptInfo *info)
{
    auto outerRecognizer = OH_ArkUI_GestureInterruptInfo_GetRecognizer(info);
    if (!outerRecognizer) {
        return ArkUI_GestureInterruptResult::GESTURE_INTERRUPT_RESULT_CONTINUE;
    }
    char *nodeId = (char *)malloc(sizeof(char) * NUM_6);
    int result = 0;
    OH_ArkUI_GetGestureBindNodeId(outerRecognizer, nodeId, NUM_6, &result);
    if (!gestureApi) {
        return ArkUI_GestureInterruptResult::GESTURE_INTERRUPT_RESULT_CONTINUE;
    }
    if (strcmp(nodeId, "outer") == 0 && OH_ArkUI_IsBuiltInGesture(outerRecognizer) &&
        gestureApi->getGestureType(outerRecognizer) == ArkUI_GestureRecognizerType::PAN_GESTURE) {
        int count = 0;
        ArkUI_GestureRecognizer **recognizers;
        // 获取响应链上的手势识别器
        OH_ArkUI_GetResponseRecognizersFromInterruptInfo(info, &recognizers, &count);
        for (int index = 0; index < count; index++) {
            auto item = recognizers[index];
            if (!item) {
                continue;
            }
            char *childNodeId = (char *)malloc(sizeof(char) * NUM_6);
            int childResult = 0;
            OH_ArkUI_GetGestureBindNodeId(item, childNodeId, NUM_6, &childResult);
            if (strcmp(childNodeId, "inner") != 0) {
                return ArkUI_GestureInterruptResult::GESTURE_INTERRUPT_RESULT_CONTINUE;
            }
            ArkUI_GestureEvent *event = OH_ArkUI_GestureInterruptInfo_GetGestureEvent(info);
            if (!event) {
                return ArkUI_GestureInterruptResult::GESTURE_INTERRUPT_RESULT_CONTINUE;
            }
            // 获取手势的垂直位移
            auto offsetY = OH_ArkUI_PanGesture_GetOffsetY(event);
            auto manager = NativeXComponentSample::Manager::GetInstance();
            if (!manager) {
                return ArkUI_GestureInterruptResult::GESTURE_INTERRUPT_RESULT_CONTINUE;
            }
            auto currentRecognizer = manager->GetCurrentRecognizer();
            auto childRecognizer = manager->GetChildRecognizer();
            ArkUI_GestureEventTargetInfo *childTargetInfo;
            OH_ArkUI_GetGestureEventTargetInfo(childRecognizer, &childTargetInfo);
            ArkUI_GestureEventTargetInfo *currentTargetInfo;
            OH_ArkUI_GetGestureEventTargetInfo(currentRecognizer, &currentTargetInfo);
            if (!childTargetInfo || !currentTargetInfo) {
                return ArkUI_GestureInterruptResult::GESTURE_INTERRUPT_RESULT_CONTINUE;
            }
            SetGestureEnableState(offsetY, childRecognizer, currentRecognizer, childTargetInfo, currentTargetInfo);
        }
    }
    return ArkUI_GestureInterruptResult::GESTURE_INTERRUPT_RESULT_CONTINUE;
}

// 并行内部手势事件回调
ArkUI_GestureRecognizer *ParallelInnerGestureFunc(ArkUI_ParallelInnerGestureEvent *event)
{
    // 获取并行内部手势事件回调中的用户自定义信息
    int *userData = reinterpret_cast<int *>(OH_ArkUI_ParallelInnerGestureEvent_GetUserData(event));
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "ArkUI_GestureInterruptInfo userData is %{public}d",
                 *userData);
    int count = 0;
    ArkUI_GestureRecognizer **others;
    // 获取并行内部手势事件回调中的冲突手势
    OH_ArkUI_ParallelInnerGestureEvent_GetConflictRecognizers(event, &others, &count);
    // 获取并行内部手势事件回调中的当前手势
    auto current = OH_ArkUI_ParallelInnerGestureEvent_GetCurrentRecognizer(event);
    for (auto index = 0; index < count; index++) {
        auto item = others[index];
        if (!item) {
            continue;
        }
        char *nodeId = (char *)malloc(sizeof(char) * NUM_6);
        int result = 0;
        OH_ArkUI_GetGestureBindNodeId(item, nodeId, NUM_6, &result);
        if (strcmp(nodeId, "inner") != 0) {
            continue;
        }
        // 判断是否为内置手势
        auto isBuiltIn = OH_ArkUI_IsBuiltInGesture(item);
        ArkUI_GestureRecognizerType type = ArkUI_GestureRecognizerType::TAP_GESTURE;
        if (gestureApi != nullptr) {
            type = gestureApi->getGestureType(item);
        }
        if (isBuiltIn && type == ArkUI_GestureRecognizerType::PAN_GESTURE) {
            auto manager = NativeXComponentSample::Manager::GetInstance();
            // 保存并行的父组件手势和子组件手势
            manager->SetCurrentRecognizer(current);
            manager->SetChildRecognizer(item);
            // 绑定手势识别器析构回调
            OH_ArkUI_SetArkUIGestureRecognizerDisposeNotify(
                current,
                [](ArkUI_GestureRecognizer *recognizer, void *userData) {
                    auto manager = NativeXComponentSample::Manager::GetInstance();
                    manager->SetCurrentRecognizer(nullptr);
                },
                nullptr);
            OH_ArkUI_SetArkUIGestureRecognizerDisposeNotify(
                item,
                [](ArkUI_GestureRecognizer *recognizer, void *userData) {
                    auto manager = NativeXComponentSample::Manager::GetInstance();
                    manager->SetChildRecognizer(nullptr);
                },
                nullptr);
            return item;
        }
    }
    return nullptr;
}
} // namespace

void SetListAttribute(ArkUI_NodeHandle &list)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue listWidthValue[] = {400};
    ArkUI_AttributeItem listWidthItem = {listWidthValue, 1};
    nodeAPI->setAttribute(list, NODE_WIDTH, &listWidthItem);
    ArkUI_NumberValue listHeightValue[] = {400};
    ArkUI_AttributeItem listHeightItem = {listHeightValue, 1};
    nodeAPI->setAttribute(list, NODE_HEIGHT, &listHeightItem);
    ArkUI_NumberValue borderColorValue[] = {{.u32 = 0xCCCCCCCC}};
    ArkUI_AttributeItem borderColorItem = {borderColorValue, 1};
    nodeAPI->setAttribute(list, NODE_BORDER_COLOR, &borderColorItem);
    ArkUI_NumberValue borderWidthValue[] = {5};
    ArkUI_AttributeItem borderWidthItem = {borderWidthValue, 1};
    nodeAPI->setAttribute(list, NODE_BORDER_WIDTH, &borderWidthItem);
    ArkUI_NumberValue initialIndexValue[] = {{.i32 = 5}};
    ArkUI_AttributeItem initialIndexItem = {initialIndexValue, 1};
    nodeAPI->setAttribute(list, NODE_LIST_INITIAL_INDEX, &initialIndexItem);
    ArkUI_NumberValue edgeEffectValue[] = {{.i32 = ARKUI_EDGE_EFFECT_NONE}};
    ArkUI_AttributeItem edgeEffectItem = {edgeEffectValue, 1};
    nodeAPI->setAttribute(list, NODE_SCROLL_EDGE_EFFECT, &edgeEffectItem);
    ArkUI_AttributeItem nodeIdItem = {.string = "inner"};
    nodeAPI->setAttribute(list, NODE_ID, &nodeIdItem);
}

void SetScrollAttribute(ArkUI_NodeHandle &scroll)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue scrollWidthValue[] = {500};
    ArkUI_AttributeItem scrollWidthItem = {scrollWidthValue, 1};
    nodeAPI->setAttribute(scroll, NODE_WIDTH, &scrollWidthItem);
    ArkUI_NumberValue scrollHeightValue[] = {600};
    ArkUI_AttributeItem scrollHeightItem = {scrollHeightValue, 1};
    nodeAPI->setAttribute(scroll, NODE_HEIGHT, &scrollHeightItem);
    ArkUI_NumberValue scrollColorValue[] = {{.u32 = 0xFF2F2F4F}};
    ArkUI_AttributeItem backColorItem = {scrollColorValue, 1};
    nodeAPI->setAttribute(scroll, NODE_BACKGROUND_COLOR, &backColorItem);
    ArkUI_AttributeItem scrollNodeIdItem = {.string = "outer"};
    nodeAPI->setAttribute(scroll, NODE_ID, &scrollNodeIdItem);
}

void AddListChild(ArkUI_NodeHandle &list)
{
    if (!nodeAPI) {
        return;
    }
    for (int i = 0; i < CHILD_SIZE; i++) {
        ArkUI_NumberValue widthValue[] = {400};
        ArkUI_AttributeItem widthItem = {widthValue, 1};
        ArkUI_NumberValue heightValue[] = {100};
        ArkUI_AttributeItem heightItem = {heightValue, 1};
        ArkUI_NumberValue backColorValue[] = {{.u32 = 0xF2F2F3F0}};
        ArkUI_AttributeItem backColorItem = {backColorValue, 1};
        ArkUI_NodeHandle listItem = nodeAPI->createNode(ARKUI_NODE_LIST_ITEM);
        ArkUI_NodeHandle text = nodeAPI->createNode(ARKUI_NODE_TEXT);
        nodeAPI->setAttribute(text, NODE_WIDTH, &widthItem);
        nodeAPI->setAttribute(text, NODE_HEIGHT, &heightItem);
        nodeAPI->setAttribute(text, NODE_BACKGROUND_COLOR, &backColorItem);
        std::string content = "listItem";
        content.append(std::to_string(i));
        ArkUI_AttributeItem contentItem = {.string = content.c_str()};
        nodeAPI->setAttribute(text, NODE_TEXT_CONTENT, &contentItem);
        nodeAPI->addChild(listItem, text);
        nodeAPI->addChild(list, listItem);
    }
}

void AddScrollChild(ArkUI_NodeHandle &scroll, ArkUI_NodeHandle &list)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue itemWidthValue[] = {400};
    ArkUI_AttributeItem itemWidthItem = {itemWidthValue, 1};
    ArkUI_NumberValue itemHeightValue[] = {400};
    ArkUI_AttributeItem itemHeightItem = {itemHeightValue, 1};
    ArkUI_NumberValue itemBackColorvalue[] = {{.u32 = 0xFF00FFFF}};
    ArkUI_AttributeItem itemBackColoritem = {itemBackColorvalue, 1};
    ArkUI_NodeHandle text = nodeAPI->createNode(ARKUI_NODE_TEXT);
    nodeAPI->setAttribute(text, NODE_WIDTH, &itemWidthItem);
    nodeAPI->setAttribute(text, NODE_HEIGHT, &itemHeightItem);
    nodeAPI->setAttribute(text, NODE_BACKGROUND_COLOR, &itemBackColoritem);
    ArkUI_AttributeItem contentItem = {.string = "scrollItem"};
    nodeAPI->setAttribute(text, NODE_TEXT_CONTENT, &contentItem);
    ArkUI_NodeHandle column = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    nodeAPI->addChild(column, text);
    nodeAPI->addChild(column, list);

    nodeAPI->addChild(scroll, column);
}

void SetGestureEnableStateDynamic(float delta, ArkUI_GestureRecognizer *childRecognizer,
    ArkUI_GestureRecognizer *currentRecognizer, ArkUI_GestureEventTargetInfo *childTargetInfo,
    ArkUI_GestureEventTargetInfo *currentTargetInfo)
{
    // 获取当前父子组件的滚动容器状态
        bool childIsEnd = false;
        OH_ArkUI_GestureEventTargetInfo_IsScrollEnd(childTargetInfo, &childIsEnd);
        bool childIsBegin = false;
        OH_ArkUI_GestureEventTargetInfo_IsScrollBegin(childTargetInfo, &childIsBegin);
        bool currentIsEnd = false;
        OH_ArkUI_GestureEventTargetInfo_IsScrollEnd(currentTargetInfo, &currentIsEnd);
        bool currentIsBegin = false;
        OH_ArkUI_GestureEventTargetInfo_IsScrollBegin(currentTargetInfo, &currentIsBegin);
        if (delta < 0) {
            if (currentIsEnd) {
                // 当父组件已经到达底部时，继续向上滑动时，设置子组件滑动，父组件禁止滑动
                OH_ArkUI_SetGestureRecognizerEnabled(childRecognizer, true);
                bool isEnabled = OH_ArkUI_GetGestureRecognizerEnabled(childRecognizer);
                OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "child isEnabled state %{public}d",
                             isEnabled);
                OH_ArkUI_SetGestureRecognizerEnabled(currentRecognizer, false);
            } else {
                // 当父组件没有到达底部时，继续向上滑动时，设置子组件禁止滑动，父组件滑动
                OH_ArkUI_SetGestureRecognizerEnabled(childRecognizer, false);
                OH_ArkUI_SetGestureRecognizerEnabled(currentRecognizer, true);
            }
        } else if (delta > 0) {
            if (childIsBegin) {
                // 当子组件到达顶部时，继续向下滑动时，设置子组件禁止滑动，父组件滑动
                OH_ArkUI_SetGestureRecognizerEnabled(childRecognizer, false);
                OH_ArkUI_SetGestureRecognizerEnabled(currentRecognizer, true);
            } else {
                // 当子组件没有到达顶部时，继续向下滑动时，设置子组件滑动，父组件禁止滑动
                OH_ArkUI_SetGestureRecognizerEnabled(childRecognizer, true);
                OH_ArkUI_SetGestureRecognizerEnabled(currentRecognizer, false);
            }
        }
}

void LogRecognizerState(ArkUI_GestureRecognizerState state)
{
    // 判断当前手势识别器状态
    switch (state) {
        case ArkUI_GestureRecognizerState::ARKUI_GESTURE_RECOGNIZER_STATE_READY:
            OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "childState is ready");
            break;
        case ARKUI_GESTURE_RECOGNIZER_STATE_DETECTING:
            OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "childState is detecting");
            break;
        case ARKUI_GESTURE_RECOGNIZER_STATE_PENDING:
            OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "childState is pending");
            break;
        case ARKUI_GESTURE_RECOGNIZER_STATE_BLOCKED:
            OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "childState is block");
            break;
        case ARKUI_GESTURE_RECOGNIZER_STATE_SUCCESSFUL:
            OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "childState is success");
            break;
        case ARKUI_GESTURE_RECOGNIZER_STATE_FAILED:
            OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "childState is fail");
            break;
    }
}

// 绑定动态控制器
void BindPanGesture(ArkUI_NodeHandle &scroll)
{
    if (!gestureApi) {
        return;
    }
    auto panGesture = gestureApi->createPanGesture(1, 15, 5);
    // 设置回调
    auto onActionUpdateCallBack = [](ArkUI_GestureEvent *event, void *extraParam) {
        auto manager = NativeXComponentSample::Manager::GetInstance();
        if (!manager) {
            return;
        }
        auto currentRecognizer = manager->GetCurrentRecognizer();
        auto childRecognizer = manager->GetChildRecognizer();
        if (!OH_ArkUI_IsGestureRecognizerValid(currentRecognizer) ||
            !OH_ArkUI_IsGestureRecognizerValid(childRecognizer)) {
            return;
        }
        ArkUI_GestureRecognizerState childState;
        ArkUI_GestureRecognizerState currentState;
        OH_ArkUI_GetGestureRecognizerState(childRecognizer, &childState);
        OH_ArkUI_GetGestureRecognizerState(currentRecognizer, &currentState);
        LogRecognizerState(childState);
        if (childState != ArkUI_GestureRecognizerState::ARKUI_GESTURE_RECOGNIZER_STATE_SUCCESSFUL ||
            currentState != ArkUI_GestureRecognizerState::ARKUI_GESTURE_RECOGNIZER_STATE_SUCCESSFUL) {
            return;
        }
        // 获取手势的垂直位移
        auto offsetY = OH_ArkUI_PanGesture_GetOffsetY(event);
        ArkUI_GestureEventTargetInfo *childTargetInfo;
        OH_ArkUI_GetGestureEventTargetInfo(childRecognizer, &childTargetInfo);
        ArkUI_GestureEventTargetInfo *currentTargetInfo;
        OH_ArkUI_GetGestureEventTargetInfo(currentRecognizer, &currentTargetInfo);
        if (!childTargetInfo || !currentTargetInfo) {
            return;
        }
        SetGestureEnableStateDynamic(offsetY - manager->GetLastOffset(), childRecognizer, currentRecognizer,
                                     childTargetInfo, currentTargetInfo);
        // 更新前一次的offset
        manager->SetLastOffset(offsetY);
    };
    // 将手势设置到组件上
    gestureApi->setGestureEventTarget(panGesture, GESTURE_EVENT_ACTION_UPDATE, scroll, onActionUpdateCallBack);
    gestureApi->addGestureToNode(scroll, panGesture, PARALLEL, NORMAL_GESTURE_MASK);
}

void BindingGesture(napi_env env, napi_value arg, OH_NativeXComponent *component)
{
    // 创建父子滚动容器
    ArkUI_NodeHandle scroll = nodeAPI->createNode(ARKUI_NODE_SCROLL);
    ArkUI_NodeHandle list = nodeAPI->createNode(ARKUI_NODE_LIST);
    // 设置属性
    SetListAttribute(list);
    SetScrollAttribute(scroll);
    AddListChild(list);
    AddScrollChild(scroll, list);
    OH_NativeXComponent_AttachNativeRootNode(component, scroll);
    if (!gestureApi) {
        return;
    }
    auto manager = NativeXComponentSample::Manager::GetInstance();
    if (!manager) {
        return;
    }
    // 绑定回调
    gestureApi2->setGestureInterrupterToNode(list, manager->GetCustomData(), ChildGestureInterruptFunc);
    gestureApi->setGestureInterrupterToNode(scroll, GestureInterruptFunc);
    gestureApi->setInnerGestureParallelTo(scroll, manager->GetCustomData(), ParallelInnerGestureFunc);
    // 绑定嵌套滚动的动态控制器
    BindPanGesture(scroll);
}

napi_value Manager::CreateNativeNode(napi_env env, napi_callback_info info)
{
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "CreateNativeNode env or info is null");
        return nullptr;
    }

    size_t argCnt = 2;
    napi_value args[2] = {nullptr};
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "CreateNativeNode napi_get_cb_info failed");
    }

    if (argCnt < 1) {
        napi_throw_type_error(env, NULL, "Wrong number of arguments");
        return nullptr;
    }

    napi_valuetype valuetype;
    if (napi_typeof(env, args[0], &valuetype) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_typeof failed");
        return nullptr;
    }

    if (valuetype != napi_string) {
        napi_throw_type_error(env, NULL, "Wrong type of arguments");
        return nullptr;
    }

    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {'\0'};
    constexpr uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    size_t length;
    if (napi_get_value_string_utf8(env, args[0], idStr, idSize, &length) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_get_value_int64 failed");
        return nullptr;
    }

    auto manager = Manager::GetInstance();
    if (manager == nullptr) {
        return nullptr;
    }

    OH_NativeXComponent *component = manager->GetNativeXComponent(idStr);
    if (component == nullptr) {
        return nullptr;
    }
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_GESTURE, ArkUI_NativeGestureAPI_1, gestureApi);
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_GESTURE, ArkUI_NativeGestureAPI_2, gestureApi2);

    if (nodeAPI != nullptr) {
        if (nodeAPI->createNode != nullptr && nodeAPI->addChild != nullptr) {
            BindingGesture(env, args[1], component);
        }
    }
    return nullptr;
}

napi_value Manager::UpdateNativeNode(napi_env env, napi_callback_info info)
{
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "UpdateNativeNode env or info is null");
        return nullptr;
    }

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Callback", "UpdateNativeNode  1111");

    size_t argCnt = 1;
    napi_value args[1] = {nullptr};
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "UpdateNativeNode napi_get_cb_info failed");
    }

    if (argCnt != 1) {
        napi_throw_type_error(env, NULL, "Wrong number of arguments");
        return nullptr;
    }

    napi_valuetype valuetype;
    if (napi_typeof(env, args[0], &valuetype) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_typeof failed");
        return nullptr;
    }

    if (valuetype != napi_string) {
        napi_throw_type_error(env, NULL, "Wrong type of arguments");
        return nullptr;
    }

    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {'\0'};
    constexpr uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    size_t length;
    if (napi_get_value_string_utf8(env, args[0], idStr, idSize, &length) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_get_value_int64 failed");
        return nullptr;
    }
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Callback", "CreateNativeNode %{public}s", idStr);

    auto manager = Manager::GetInstance();
    if (manager == nullptr) {
        return nullptr;
    }

    OH_NativeXComponent *component = manager->GetNativeXComponent(idStr);
    if (component == nullptr) {
        return nullptr;
    }

    if ((env == nullptr) || (info == nullptr || component == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "GetContext env or info is null");
        return nullptr;
    }
    return nullptr;
}

napi_value Manager::GetContext(napi_env env, napi_callback_info info)
{
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "GetContext env or info is null");
        return nullptr;
    }

    size_t argCnt = 1;
    napi_value args[1] = {nullptr};
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "GetContext napi_get_cb_info failed");
    }

    if (argCnt != 1) {
        napi_throw_type_error(env, NULL, "Wrong number of arguments");
        return nullptr;
    }

    napi_valuetype valuetype;
    if (napi_typeof(env, args[0], &valuetype) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_typeof failed");
        return nullptr;
    }

    if (valuetype != napi_number) {
        napi_throw_type_error(env, NULL, "Wrong type of arguments");
        return nullptr;
    }

    int64_t value;
    if (napi_get_value_int64(env, args[0], &value) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_get_value_int64 failed");
        return nullptr;
    }

    napi_value exports;
    if (napi_create_object(env, &exports) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_create_object failed");
        return nullptr;
    }

    return exports;
}

void Manager::Export(napi_env env, napi_value exports)
{
    if ((env == nullptr) || (exports == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "Export: env or exports is null");
        return;
    }

    napi_value exportInstance = nullptr;
    if (napi_get_named_property(env, exports, OH_NATIVE_XCOMPONENT_OBJ, &exportInstance) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "Export: napi_get_named_property fail");
        return;
    }

    OH_NativeXComponent *nativeXComponent = nullptr;
    if (napi_unwrap(env, exportInstance, reinterpret_cast<void **>(&nativeXComponent)) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "Export: napi_unwrap fail");
        return;
    }

    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {'\0'};
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    if (OH_NativeXComponent_GetXComponentId(nativeXComponent, idStr, &idSize) != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager",
                     "Export: OH_NativeXComponent_GetXComponentId fail");
        return;
    }

    std::string id(idStr);
    auto manager = Manager::GetInstance();
    if ((manager != nullptr) && (nativeXComponent != nullptr)) {
        manager->SetNativeXComponent(id, nativeXComponent);
    }
}

void Manager::SetNativeXComponent(std::string &id, OH_NativeXComponent *nativeXComponent)
{
    if (nativeXComponent == nullptr) {
        return;
    }

    if (nativeXComponentMap_.find(id) == nativeXComponentMap_.end()) {
        nativeXComponentMap_[id] = nativeXComponent;
        return;
    }

    if (nativeXComponentMap_[id] != nativeXComponent) {
        OH_NativeXComponent *tmp = nativeXComponentMap_[id];
        tmp = nullptr;
        nativeXComponentMap_[id] = nativeXComponent;
    }
}

OH_NativeXComponent *Manager::GetNativeXComponent(const std::string &id) { return nativeXComponentMap_[id]; }
} // namespace NativeXComponentSample