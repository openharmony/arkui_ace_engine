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
#include <cstdint>
#include <cstring>
#include <iostream>

#include "gtest/gtest.h"
#define private public
#define protected public
#include "drag_and_drop.h"
#include "event_converter.h"
#include "udmf.h"
#include "native_interface.h"
#include "native_node.h"
#include "native_type.h"
#include "node_model.h"
#include "securec.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {
namespace {
const float WINDOW_X = 1.0f;
const float WINDOW_Y = 1.0f;
const float TOUCH_POINT_X = 1.0f;
const float TOUCH_POINT_Y = 1.0f;
const float PREVIEW_RECT_WIDTH = 1.0f;
const float PREVIEW_RECT_HEIGHT = 1.0f;
const float DISPLAY_X = 1.0f;
const float DISPLAY_Y = 1.0f;
const float GLOBAL_DISPLAY_X = 1.0f;
const float GLOBAL_DISPLAY_Y = 1.0f;
const float VELOCITY_X = 1.0f;
const float VELOCITY_Y = 1.0f;
const float VELOCITY = 1.0f;
const int32_t DISPLAYID = 0;
} // namespace
class DragAndDropTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        NG::MockPipelineContext::SetUp();
        MockContainer::SetUp();
        MockContainer::Current()->pipelineContext_ = NG::MockPipelineContext::GetCurrent();
        MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
        MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        PipelineBase::GetCurrentContext()->SetThemeManager(themeManager);
    }
    static void TearDownTestSuite()
    {
        NG::MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }
};

/**
 * @tc.name: DragAndDropTest001
 * @tc.desc: Test the DragAction for C-API.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create dragAction.
     */
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_STACK);
    auto rootFrameNode = reinterpret_cast<ArkUI_Node*>(rootNode);
    auto frameNode = reinterpret_cast<NG::FrameNode*>(rootFrameNode->uiNodeHandle);
    auto context = NG::MockPipelineContext::GetCurrent();
    frameNode->context_ = AceType::RawPtr(context);
    auto* dragAction = OH_ArkUI_CreateDragActionWithNode(rootNode);
    EXPECT_NE(dragAction, nullptr);
    EXPECT_EQ(OH_ArkUI_DragAction_SetPointerId(dragAction, 0), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_DragAction_SetTouchPointX(dragAction, 1.0), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_DragAction_SetTouchPointY(dragAction, 1.0), ARKUI_ERROR_CODE_NO_ERROR);
    auto* interalDragAction = reinterpret_cast<ArkUIDragAction*>(dragAction);
    EXPECT_EQ(interalDragAction->pointerId, 0);
    EXPECT_EQ(interalDragAction->touchPointX, 1.0);
    EXPECT_EQ(interalDragAction->touchPointY, 1.0);
    OH_ArkUI_DragAction_RegisterStatusListener(
        dragAction, nullptr, [](ArkUI_DragAndDropInfo* dragAndDropInfo, void* userData) -> void {
            EXPECT_NE(
                OH_ArkUI_DragAndDropInfo_GetDragStatus(dragAndDropInfo), ArkUI_DragStatus::ARKUI_DRAG_STATUS_UNKNOWN);
            EXPECT_NE(OH_ArkUI_DragAndDropInfo_GetDragEvent(dragAndDropInfo), nullptr);
        });
    OH_ArkUI_DragAction_UnregisterStatusListener(dragAction);
    EXPECT_EQ(OH_ArkUI_StartDrag(dragAction), ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_DragAction_Dispose(dragAction);
}

/**
 * @tc.name: DragAndDropTest002
 * @tc.desc: Test the DragAction for C-API.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create dragAction.
     */
    auto uiContext = new ArkUI_Context({ .id = 1 });
    auto dragAction = OH_ArkUI_CreateDragActionWithContext(uiContext);
    EXPECT_NE(dragAction, nullptr);
    EXPECT_EQ(OH_ArkUI_DragAction_SetPointerId(dragAction, 0), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_DragAction_SetTouchPointX(dragAction, 1.0), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_DragAction_SetTouchPointY(dragAction, 1.0), ARKUI_ERROR_CODE_NO_ERROR);
    auto* interalDragAction = reinterpret_cast<ArkUIDragAction*>(dragAction);
    EXPECT_EQ(interalDragAction->pointerId, 0);
    EXPECT_EQ(interalDragAction->touchPointX, 1.0);
    EXPECT_EQ(interalDragAction->touchPointY, 1.0);
    OH_ArkUI_DragAction_RegisterStatusListener(
        dragAction, nullptr, [](ArkUI_DragAndDropInfo* dragAndDropInfo, void* userData) -> void {
            EXPECT_NE(
                OH_ArkUI_DragAndDropInfo_GetDragStatus(dragAndDropInfo), ArkUI_DragStatus::ARKUI_DRAG_STATUS_UNKNOWN);
            EXPECT_NE(OH_ArkUI_DragAndDropInfo_GetDragEvent(dragAndDropInfo), nullptr);
        });
    OH_ArkUI_DragAction_UnregisterStatusListener(dragAction);
    EXPECT_EQ(OH_ArkUI_StartDrag(dragAction), ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_DragAction_Dispose(dragAction);
    delete uiContext;
}

/**
 * @tc.name: DragAndDropTest003
 * @tc.desc: test OH_ArkUI_NodeEvent_GetDragEvent function;
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest003, TestSize.Level1)
{
    ArkUI_NodeEvent event = { 0, -1 };
    auto eventType = OH_ArkUI_NodeEvent_GetDragEvent(&event);
    EXPECT_EQ(eventType, nullptr);
}

/**
 * @tc.name: DragAndDropTest004
 * @tc.desc: test NodeDrag function;
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create FrameNode is not null, related function is called.
     */
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto textNode = new ArkUI_Node({ ARKUI_NODE_TEXT, nullptr, true });
    auto areaNode = new ArkUI_Node({ ARKUI_NODE_TEXT_AREA, nullptr, true });

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(nodeAPI->registerNodeEvent(textNode, NODE_ON_PRE_DRAG, 0, nullptr), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->registerNodeEvent(textNode, NODE_ON_DRAG_START, 1, nullptr), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->registerNodeEvent(textNode, NODE_ON_DRAG_ENTER, 2, nullptr), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->registerNodeEvent(textNode, NODE_ON_DRAG_MOVE, 3, nullptr), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->registerNodeEvent(textNode, NODE_ON_DRAG_LEAVE, 4, nullptr), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->registerNodeEvent(areaNode, NODE_ON_DROP, 5, nullptr), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->registerNodeEvent(textNode, NODE_ON_DRAG_END, 6, nullptr), ARKUI_ERROR_CODE_NO_ERROR);
    delete textNode;
    delete areaNode;
}

/**
 * @tc.name: DragAndDropTest005
 * @tc.desc: Test the OH_ArkUI_NodeEvent_GetPreDragStatus.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    event.kind = ArkUIEventCategory::COMPONENT_ASYNC_EVENT;
    event.componentAsyncEvent.subKind = ON_PRE_DRAG;
    event.componentAsyncEvent.data[0].i32 =
        static_cast<ArkUI_Int32>(OHOS::Ace::PreDragStatus::READY_TO_TRIGGER_DRAG_ACTION);
    nodeEvent.origin = &event;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_COMPONENT_EVENT;
    auto ret1 = OH_ArkUI_NodeEvent_GetPreDragStatus(&nodeEvent);

    /**
     * @tc.steps: step2.set DragEvent is nullptr, related function is called.
     */
    auto ret2 = OH_ArkUI_NodeEvent_GetPreDragStatus(nullptr);

    /**
     * @tc.steps: step3.set category to other type, related function is called.
     */
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    auto ret3 = OH_ArkUI_NodeEvent_GetPreDragStatus(&nodeEvent);

    /**
     * @tc.steps: step4.set origin to nullptr, related function is called.
     */
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_COMPONENT_EVENT;
    nodeEvent.origin = nullptr;
    auto ret4 = OH_ArkUI_NodeEvent_GetPreDragStatus(&nodeEvent);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ret1, ArkUI_PreDragStatus::ARKUI_PRE_DRAG_STATUS_READY_TO_TRIGGER_DRAG);
    EXPECT_EQ(ret2, ArkUI_PreDragStatus::ARKUI_PRE_DRAG_STATUS_UNKNOWN);
    EXPECT_EQ(ret3, ArkUI_PreDragStatus::ARKUI_PRE_DRAG_STATUS_UNKNOWN);
    EXPECT_EQ(ret4, ArkUI_PreDragStatus::ARKUI_PRE_DRAG_STATUS_UNKNOWN);
}

/**
 * @tc.name: DragAndDropTest006
 * @tc.desc: Test the OH_ArkUI_DragEvent_DisableDefaultDropAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create DragEvent, related function is called.
     */
    ArkUIDragEvent dragEvent;
    auto* drag_Event = reinterpret_cast<ArkUI_DragEvent*>(&dragEvent);
    auto ret1 = OH_ArkUI_DragEvent_DisableDefaultDropAnimation(drag_Event, true);
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(dragEvent.useCustomDropAnimation, true);
    auto ret2 = OH_ArkUI_DragEvent_DisableDefaultDropAnimation(drag_Event, false);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(dragEvent.useCustomDropAnimation, false);

    /**
     * @tc.steps: step2.set DragEvent is nullptr, related function is called.
     */
    auto ret3 = OH_ArkUI_DragEvent_DisableDefaultDropAnimation(nullptr, false);
    EXPECT_EQ(ret3, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto ret4 = OH_ArkUI_DragEvent_DisableDefaultDropAnimation(nullptr, false);
    EXPECT_EQ(ret4, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: DragAndDropTest007
 * @tc.desc: Test the OH_ArkUI_SetNodeDraggable.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create DragEvent, related function is called.
     */
    auto textNode = new ArkUI_Node({ ARKUI_NODE_TEXT, nullptr, true });
    auto ret1 = OH_ArkUI_SetNodeDraggable(textNode, true);
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_NO_ERROR);

    auto ret2 = OH_ArkUI_SetNodeDraggable(textNode, false);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step2.set DragEvent is nullptr, related function is called.
     */
    auto ret3 = OH_ArkUI_SetNodeDraggable(nullptr, true);
    EXPECT_EQ(ret3, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto ret4 = OH_ArkUI_SetNodeDraggable(nullptr, false);
    EXPECT_EQ(ret4, ARKUI_ERROR_CODE_PARAM_INVALID);
    delete textNode;
}

/**
 * @tc.name: DragAndDropTest008
 * @tc.desc: Test the OH_ArkUI_CreateDragPreviewOption.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_DragPreviewOption.
     * @tc.expected: Return expected results.
     */
    auto* dragPreviewOption = OH_ArkUI_CreateDragPreviewOption();
    EXPECT_NE(dragPreviewOption, nullptr);

    /**
     * @tc.steps: step2.create ArkUI_DragPreviewOption.
     * @tc.expected: Return expected results.
     */
    OH_ArkUI_DragPreviewOption_Dispose(dragPreviewOption);
    dragPreviewOption = nullptr;
    EXPECT_EQ(dragPreviewOption, nullptr);
}

/**
 * @tc.name: DragAndDropTest009
 * @tc.desc: Test the OH_ArkUI_DragPreviewOption_SetScaleMode.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create dragPreviewOption and set scaleMode.
     * @tc.expected: Return expected results.
     */
    auto* dragPreviewOption = OH_ArkUI_CreateDragPreviewOption();
    auto ret1 = OH_ArkUI_DragPreviewOption_SetScaleMode(
        dragPreviewOption, ArkUI_DragPreviewScaleMode::ARKUI_DRAG_PREVIEW_SCALE_AUTO);
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_NO_ERROR);
    auto* option = reinterpret_cast<ArkUIDragPreViewAndInteractionOptions*>(dragPreviewOption);
    EXPECT_TRUE(option->isScaleEnabled);
    EXPECT_FALSE(option->isDefaultShadowEnabled);
    EXPECT_FALSE(option->isDefaultRadiusEnabled);
    auto ret2 = OH_ArkUI_DragPreviewOption_SetScaleMode(
        dragPreviewOption, ArkUI_DragPreviewScaleMode::ARKUI_DRAG_PREVIEW_SCALE_DISABLED);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_FALSE(option->isScaleEnabled);

    /**
     * @tc.steps: step2.set preview option with nullptr.
     * @tc.expected: Return expected results.
     */
    auto ret3 =
        OH_ArkUI_DragPreviewOption_SetScaleMode(nullptr, ArkUI_DragPreviewScaleMode::ARKUI_DRAG_PREVIEW_SCALE_AUTO);
    EXPECT_EQ(ret3, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto ret4 =
        OH_ArkUI_DragPreviewOption_SetScaleMode(nullptr, ArkUI_DragPreviewScaleMode::ARKUI_DRAG_PREVIEW_SCALE_DISABLED);
    EXPECT_EQ(ret4, ARKUI_ERROR_CODE_PARAM_INVALID);
    OH_ArkUI_DragPreviewOption_Dispose(dragPreviewOption);
}

/**
 * @tc.name: DragAndDropTest010
 * @tc.desc: Test the OH_ArkUI_DragPreviewOption_SetDefaultShadowEnabled.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create dragPreviewOption and call related function.
     * @tc.expected: Return expected results.
     */
    auto* dragPreviewOption = OH_ArkUI_CreateDragPreviewOption();
    auto ret1 = OH_ArkUI_DragPreviewOption_SetDefaultShadowEnabled(dragPreviewOption, true);
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_NO_ERROR);
    auto* option = reinterpret_cast<ArkUIDragPreViewAndInteractionOptions*>(dragPreviewOption);
    EXPECT_TRUE(option->isDefaultShadowEnabled);
    auto ret2 = OH_ArkUI_DragPreviewOption_SetDefaultShadowEnabled(dragPreviewOption, false);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_FALSE(option->isDefaultShadowEnabled);

    /**
     * @tc.steps: step2.set preview option with nullptr.
     * @tc.expected: Return expected results.
     */
    auto ret3 = OH_ArkUI_DragPreviewOption_SetDefaultShadowEnabled(nullptr, true);
    EXPECT_EQ(ret3, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto ret4 = OH_ArkUI_DragPreviewOption_SetDefaultShadowEnabled(nullptr, false);
    EXPECT_EQ(ret4, ARKUI_ERROR_CODE_PARAM_INVALID);
    OH_ArkUI_DragPreviewOption_Dispose(dragPreviewOption);
}

/**
 * @tc.name: DragAndDropTest011
 * @tc.desc: Test the OH_ArkUI_DragPreviewOption_SetDefaultRadiusEnabled.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create dragPreviewOption and call related function.
     * @tc.expected: Return expected results.
     */
    auto* dragPreviewOption = OH_ArkUI_CreateDragPreviewOption();
    auto ret1 = OH_ArkUI_DragPreviewOption_SetDefaultRadiusEnabled(dragPreviewOption, true);
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_NO_ERROR);
    auto* option = reinterpret_cast<ArkUIDragPreViewAndInteractionOptions*>(dragPreviewOption);
    EXPECT_TRUE(option->isDefaultRadiusEnabled);

    auto ret2 = OH_ArkUI_DragPreviewOption_SetDefaultRadiusEnabled(dragPreviewOption, false);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_FALSE(option->isDefaultRadiusEnabled);

    /**
     * @tc.steps: step2.set preview option with nullptr.
     * @tc.expected: Return expected results.
     */
    auto ret3 = OH_ArkUI_DragPreviewOption_SetDefaultRadiusEnabled(nullptr, true);
    EXPECT_EQ(ret3, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto ret4 = OH_ArkUI_DragPreviewOption_SetDefaultRadiusEnabled(nullptr, false);
    EXPECT_EQ(ret4, ARKUI_ERROR_CODE_PARAM_INVALID);
    OH_ArkUI_DragPreviewOption_Dispose(dragPreviewOption);
}

/**
 * @tc.name: DragAndDropTest012
 * @tc.desc: Test the OH_ArkUI_DragPreviewOption_SetDefaultShadowEnabled.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create dragPreviewOption and call related function.
     * @tc.expected: Return expected results.
     */
    auto* dragPreviewOption = OH_ArkUI_CreateDragPreviewOption();
    auto ret1 = OH_ArkUI_DragPreviewOption_SetNumberBadgeEnabled(dragPreviewOption, true);
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_NO_ERROR);
    auto* option = reinterpret_cast<ArkUIDragPreViewAndInteractionOptions*>(dragPreviewOption);
    EXPECT_FALSE(option->isNumberBadgeEnabled);
    EXPECT_TRUE(option->isShowBadge);

    auto ret2 = OH_ArkUI_DragPreviewOption_SetNumberBadgeEnabled(dragPreviewOption, false);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_FALSE(option->isNumberBadgeEnabled);
    EXPECT_FALSE(option->isShowBadge);

    /**
     * @tc.steps: step2.set preview option with nullptr.
     * @tc.expected: Return expected results.
     */
    auto ret3 = OH_ArkUI_DragPreviewOption_SetNumberBadgeEnabled(nullptr, true);
    EXPECT_EQ(ret3, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto ret4 = OH_ArkUI_DragPreviewOption_SetNumberBadgeEnabled(nullptr, false);
    EXPECT_EQ(ret4, ARKUI_ERROR_CODE_PARAM_INVALID);
    OH_ArkUI_DragPreviewOption_Dispose(dragPreviewOption);
}

/**
 * @tc.name: DragAndDropTest013
 * @tc.desc: Test the OH_ArkUI_DragPreviewOption_SetBadgeNumber.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create dragPreviewOption and call related function.
     * @tc.expected: Return expected results.
     */
    auto* dragPreviewOption = OH_ArkUI_CreateDragPreviewOption();
    auto ret1 = OH_ArkUI_DragPreviewOption_SetBadgeNumber(dragPreviewOption, 2);
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_NO_ERROR);
    auto* option = reinterpret_cast<ArkUIDragPreViewAndInteractionOptions*>(dragPreviewOption);
    EXPECT_TRUE(option->isNumberBadgeEnabled);
    EXPECT_EQ(option->badgeNumber, 2);

    /**
     * @tc.steps: step2.set preview option with nullptr.
     * @tc.expected: Return expected results.
     */
    auto ret2 = OH_ArkUI_DragPreviewOption_SetBadgeNumber(nullptr, true);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);
    OH_ArkUI_DragPreviewOption_Dispose(dragPreviewOption);
}

/**
 * @tc.name: DragAndDropTest014
 * @tc.desc: Test the OH_ArkUI_DragPreviewOption_SetDefaultAnimationBeforeLiftingEnabled.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create dragPreviewOption and call related function.
     * @tc.expected: Return expected results.
     */
    auto* dragPreviewOption = OH_ArkUI_CreateDragPreviewOption();
    auto ret1 = OH_ArkUI_DragPreviewOption_SetDefaultAnimationBeforeLiftingEnabled(dragPreviewOption, true);
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_NO_ERROR);
    auto* option = reinterpret_cast<ArkUIDragPreViewAndInteractionOptions*>(dragPreviewOption);
    EXPECT_TRUE(option->defaultAnimationBeforeLifting);
    auto ret2 = OH_ArkUI_DragPreviewOption_SetDefaultAnimationBeforeLiftingEnabled(dragPreviewOption, false);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_FALSE(option->defaultAnimationBeforeLifting);

    /**
     * @tc.steps: step2.set preview option with nullptr.
     * @tc.expected: Return expected results.
     */
    auto ret3 = OH_ArkUI_DragPreviewOption_SetDefaultAnimationBeforeLiftingEnabled(nullptr, true);
    EXPECT_EQ(ret3, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto ret4 = OH_ArkUI_DragPreviewOption_SetDefaultAnimationBeforeLiftingEnabled(nullptr, false);
    EXPECT_EQ(ret4, ARKUI_ERROR_CODE_PARAM_INVALID);
    OH_ArkUI_DragPreviewOption_Dispose(dragPreviewOption);
}

/**
 * @tc.name: DragAndDropTest015
 * @tc.desc: Test the preview option mix setting.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create dragPreviewOption and call mix related function.
     * @tc.expected: Return expected results.
     */
    auto* dragPreviewOption = OH_ArkUI_CreateDragPreviewOption();
    OH_ArkUI_DragPreviewOption_SetDefaultRadiusEnabled(dragPreviewOption, true);
    OH_ArkUI_DragPreviewOption_SetDefaultShadowEnabled(dragPreviewOption, true);
    OH_ArkUI_DragPreviewOption_SetScaleMode(
        dragPreviewOption, ArkUI_DragPreviewScaleMode::ARKUI_DRAG_PREVIEW_SCALE_AUTO);
    auto* option = reinterpret_cast<ArkUIDragPreViewAndInteractionOptions*>(dragPreviewOption);
    EXPECT_TRUE(option->isScaleEnabled);
    EXPECT_FALSE(option->isDefaultShadowEnabled);
    EXPECT_FALSE(option->isDefaultRadiusEnabled);
    OH_ArkUI_DragPreviewOption_Dispose(dragPreviewOption);
}

/**
 * @tc.name: DragAndDropTest016
 * @tc.desc: Test OH_ArkUI_SetNodeDragPreviewOption.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create dragPreviewOption and call mix related function.
     * @tc.expected: Return expected results.
     */
    auto* dragPreviewOption = OH_ArkUI_CreateDragPreviewOption();
    OH_ArkUI_DragPreviewOption_SetDefaultRadiusEnabled(dragPreviewOption, true);
    OH_ArkUI_DragPreviewOption_SetDefaultShadowEnabled(dragPreviewOption, true);
    OH_ArkUI_DragPreviewOption_SetScaleMode(
        dragPreviewOption, ArkUI_DragPreviewScaleMode::ARKUI_DRAG_PREVIEW_SCALE_AUTO);
    auto textNode = new ArkUI_Node({ ARKUI_NODE_TEXT, nullptr, true });
    EXPECT_EQ(OH_ArkUI_SetNodeDragPreviewOption(textNode, dragPreviewOption), ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_DragPreviewOption_SetScaleMode(
    dragPreviewOption, ArkUI_DragPreviewScaleMode::ARKUI_DRAG_PREVIEW_SCALE_DISABLED);
    EXPECT_EQ(OH_ArkUI_SetNodeDragPreviewOption(textNode, dragPreviewOption), ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_DragPreviewOption_SetDefaultShadowEnabled(dragPreviewOption, true);
    EXPECT_EQ(OH_ArkUI_SetNodeDragPreviewOption(textNode, dragPreviewOption), ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_DragPreviewOption_SetDefaultShadowEnabled(dragPreviewOption, false);
    EXPECT_EQ(OH_ArkUI_SetNodeDragPreviewOption(textNode, dragPreviewOption), ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_DragPreviewOption_SetDefaultRadiusEnabled(dragPreviewOption, true);
    EXPECT_EQ(OH_ArkUI_SetNodeDragPreviewOption(textNode, dragPreviewOption), ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_DragPreviewOption_SetDefaultRadiusEnabled(dragPreviewOption, false);
    EXPECT_EQ(OH_ArkUI_SetNodeDragPreviewOption(textNode, dragPreviewOption), ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step2.set preview option with nullptr.
     * @tc.expected: Return expected results.
     */
    auto ret2 = OH_ArkUI_SetNodeDragPreviewOption(nullptr, dragPreviewOption);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);
    OH_ArkUI_DragPreviewOption_Dispose(dragPreviewOption);
    delete textNode;
}

/**
 * @tc.name: DragAndDropTest0017
 * @tc.desc: test set DragEvent property function;
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0017, TestSize.Level1)
{
    /**
     *@tc.steps : step1.create and set property.
     */
    ArkUIDragEvent dragEvent;
    dragEvent.windowX = WINDOW_X;
    dragEvent.windowY = WINDOW_Y;
    dragEvent.displayX = DISPLAY_X;
    dragEvent.displayY = DISPLAY_Y;
    dragEvent.touchPointX = TOUCH_POINT_X;
    dragEvent.touchPointY = TOUCH_POINT_Y;

    dragEvent.previewRectWidth = PREVIEW_RECT_WIDTH;
    dragEvent.previewRectHeight = PREVIEW_RECT_HEIGHT;
    dragEvent.velocityX = VELOCITY_X;
    dragEvent.velocityY = VELOCITY_Y;
    dragEvent.velocity = VELOCITY;
    auto* drag_Event = reinterpret_cast<ArkUI_DragEvent*>(&dragEvent);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(OH_ArkUI_DragEvent_GetTouchPointXToWindow(drag_Event), WINDOW_X);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetTouchPointYToWindow(drag_Event), WINDOW_Y);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetPreviewTouchPointX(drag_Event), TOUCH_POINT_X);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetPreviewTouchPointY(drag_Event), TOUCH_POINT_Y);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetTouchPointXToDisplay(drag_Event), DISPLAY_X);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetTouchPointYToDisplay(drag_Event), DISPLAY_Y);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetPreviewRectWidth(drag_Event), PREVIEW_RECT_WIDTH);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetPreviewRectHeight(drag_Event), PREVIEW_RECT_HEIGHT);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetVelocityX(drag_Event), VELOCITY_X);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetVelocityY(drag_Event), VELOCITY_Y);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetVelocity(drag_Event), VELOCITY);
}

/**
 * @tc.name: DragAndDropTest0018
 * @tc.desc: test set DragEvent property function;
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0018, TestSize.Level1)
{
    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(OH_ArkUI_DragEvent_GetTouchPointXToWindow(nullptr), 0.0f);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetTouchPointYToWindow(nullptr), 0.0f);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetPreviewTouchPointX(nullptr), 0.0f);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetPreviewTouchPointY(nullptr), 0.0f);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetTouchPointXToDisplay(nullptr), 0.0f);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetTouchPointYToDisplay(nullptr), 0.0f);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetPreviewRectWidth(nullptr), 0.0f);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetPreviewRectHeight(nullptr), 0.0f);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetVelocityX(nullptr), 0.0f);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetVelocityY(nullptr), 0.0f);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetVelocity(nullptr), 0.0f);
}

/**
 * @tc.name: DragAndDropTest0019
 * @tc.desc: test ConvertOriginEventType function for drag event.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest019, TestSize.Level1)
{
    int32_t ret;
    int32_t nodeType = static_cast<int32_t>(NODE_ON_PRE_DRAG);
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_ON_PRE_DRAG, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_PRE_DRAG));

    nodeType = static_cast<int32_t>(NODE_ON_DRAG_START);
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_ON_DRAG_START, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_DRAG_START));

    nodeType = static_cast<int32_t>(NODE_ON_DRAG_ENTER);
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_ON_DRAG_ENTER, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_DRAG_ENTER));

    nodeType = static_cast<int32_t>(NODE_ON_DRAG_MOVE);
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_ON_DRAG_MOVE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_DRAG_MOVE));

    nodeType = static_cast<int32_t>(NODE_ON_DRAG_LEAVE);
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_ON_DRAG_LEAVE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_DRAG_LEAVE));

    nodeType = static_cast<int32_t>(NODE_ON_DROP);
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_ON_DROP, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_DRAG_DROP));

    nodeType = static_cast<int32_t>(NODE_ON_DRAG_END);
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_ON_DRAG_END, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_DRAG_END));
}

/**
 * @tc.name: DragAndDropTest0020
 * @tc.desc: test ConvertToNodeEventType function for drag event.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest020, TestSize.Level1)
{
    int32_t ret;
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_PRE_DRAG);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_ON_PRE_DRAG));

    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_DRAG_START);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_ON_DRAG_START));

    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_DRAG_ENTER);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_ON_DRAG_ENTER));

    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_DRAG_MOVE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_ON_DRAG_MOVE));

    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_DRAG_LEAVE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_ON_DRAG_LEAVE));

    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_DRAG_DROP);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_ON_DROP));

    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_DRAG_END);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_ON_DRAG_END));
}

/**
 * @tc.name: DragAndDropTest0021
 * @tc.desc: test OH_ArkUI_DragEvent_GetDropOperation.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest021, TestSize.Level1)
{
    /**
     *@tc.steps : step1.create and set property.
     */
    ArkUIDragEvent dragEvent;
    dragEvent.dragBehavior = ArkUI_DropOperation::ARKUI_DROP_OPERATION_MOVE;
    auto* drag_Event = reinterpret_cast<ArkUI_DragEvent*>(&dragEvent);
    ArkUI_DropOperation operation;
    auto ret = OH_ArkUI_DragEvent_GetDropOperation(drag_Event, &operation);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(operation, ArkUI_DropOperation::ARKUI_DROP_OPERATION_MOVE);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetDropOperation(nullptr, &operation), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetDropOperation(drag_Event, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: DragAndDropTest0022
 * @tc.desc: Test the OH_ArkUI_DragEvent_GetModifierKeyStates.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0022, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create DragEvent, related function is called.
     */
    uint64_t pressedKeys = 0;
    ArkUIDragEvent dragEvent;
    dragEvent.modifierKeyState = (1 << 0);
    auto* drag_Event = reinterpret_cast<ArkUI_DragEvent*>(&dragEvent);
    auto ret1 = OH_ArkUI_DragEvent_GetModifierKeyStates(drag_Event, &pressedKeys);

    /**
     * @tc.steps: step2.set DragEvent is nullptr, related function is called.
     */
    auto ret2 = OH_ArkUI_DragEvent_GetModifierKeyStates(nullptr, nullptr);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(pressedKeys, (1 << 0));
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: DragAndDropTest0023
 * @tc.desc: Test the OH_ArkUI_DragEvent_GetDataTypeCount.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0023, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create DragEvent, related function is called.
     */
    int32_t count = 0;
    ArkUIDragEvent dragEvent;
    dragEvent.dataTypesCount = 2;
    auto* drag_Event = reinterpret_cast<ArkUI_DragEvent*>(&dragEvent);
    auto ret1 = OH_ArkUI_DragEvent_GetDataTypeCount(drag_Event, &count);

    /**
     * @tc.steps: step2.set DragEvent is nullptr, related function is called.
     */
    auto ret2 = OH_ArkUI_DragEvent_GetDataTypeCount(nullptr, nullptr);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(count, 2);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: DragAndDropTest0024
 * @tc.desc: Test the OH_ArkUI_DragEvent_GetDataTypes.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0024, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create DragEvent and set null parameters.
     * @tc.expected: Return expected results.
     */
    ArkUIDragEvent dragEvent;
    dragEvent.dataTypesCount = 5;
    dragEvent.dataTypesMaxStrLength = 128;
    auto* drag_Event = reinterpret_cast<ArkUI_DragEvent*>(&dragEvent);
    
    auto ret1 = OH_ArkUI_DragEvent_GetDataTypes(nullptr, nullptr, 1, 128);
    auto ret2 = OH_ArkUI_DragEvent_GetDataTypes(drag_Event, nullptr, 1, 128);
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);

    /**
     * @tc.steps: step1.create DragEvent and set BufferSizeError parameters.
     * @tc.expected: Return expected results.
     */
    char stringArray[10][128];
    char *types1[128];
    for (int i = 0; i < 10; i++) {
        types1[i] = stringArray[i];
    }
    auto ret3 = OH_ArkUI_DragEvent_GetDataTypes(drag_Event, types1, 1, 128);
    auto ret4 = OH_ArkUI_DragEvent_GetDataTypes(drag_Event, types1, 6, 127);
    EXPECT_EQ(ret3, ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR);
    EXPECT_EQ(ret4, ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR);

    /**
     * @tc.steps: step1.create DragEvent and set no error parameters.
     * @tc.expected: Return expected results.
     */
    const char *dataTypes[128];
    for (int i = 0; i < 10; i++) {
        dataTypes[i] = stringArray[i];
    }
    dragEvent.dataTypes = dataTypes;
    dragEvent.dataTypes[0] = strdup("text/plain");
    dragEvent.dataTypes[1] = strdup("image/png");
    drag_Event = reinterpret_cast<ArkUI_DragEvent*>(&dragEvent);
    auto ret5 = OH_ArkUI_DragEvent_GetDataTypes(drag_Event, types1, 6, 128);
    EXPECT_EQ(ret5, ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: DragAndDropTest0025
 * @tc.desc: Test the OH_ArkUI_CreateDragActionWithNode.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0025, TestSize.Level1)
{
    /**
     * @tc.steps: step1.set null ArkUI_NodeHandle, related function is called.
     */
    auto* dragAction = OH_ArkUI_CreateDragActionWithNode(nullptr);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(dragAction, nullptr);
}

/**
 * @tc.name: DragAndDropTest0026
 * @tc.desc: Test the OH_ArkUI_CreateDragActionWithContext.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0026, TestSize.Level1)
{
    /**
     * @tc.steps: step1.set null ArkUI_ContextHandle, related function is called.
     */
    auto* dragAction = OH_ArkUI_CreateDragActionWithContext(nullptr);
    OH_ArkUI_DragAction_Dispose(dragAction);
    EXPECT_EQ(OH_ArkUI_DragAction_SetTouchPointX(dragAction, 1.0), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_DragAction_SetTouchPointY(dragAction, 1.0), ARKUI_ERROR_CODE_PARAM_INVALID);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(dragAction, nullptr);
}

/**
 * @tc.name: DragAndDropTest0027
 * @tc.desc: Test the OH_ArkUI_CreateDragActionWithContext.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0027, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create dragAction.
     */
    auto uiContext = new ArkUI_Context({ .id = 1 });
    auto dragAction = OH_ArkUI_CreateDragActionWithContext(uiContext);
    EXPECT_NE(dragAction, nullptr);

    /**
     * @tc.steps: step2.set pointer is smaller than MIN_POINTID, related function is called.
     */
    auto ret1 = OH_ArkUI_DragAction_SetPointerId(dragAction, -1);

    /**
     * @tc.steps: step2.set dragAction is null, related function is called.
     */
    auto ret2 = OH_ArkUI_DragAction_SetPointerId(nullptr, 1);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);
    OH_ArkUI_DragAction_Dispose(dragAction);
    delete uiContext;
}

/**
 * @tc.name: DragAndDropTest0028
 * @tc.desc: Test the OH_ArkUI_DragAction_SetDragPreviewOption.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0028, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create dragAction.
     */
    auto uiContext = new ArkUI_Context({ .id = 1 });
    auto dragAction = OH_ArkUI_CreateDragActionWithContext(uiContext);
    EXPECT_NE(dragAction, nullptr);
    auto *previewOptions = OH_ArkUI_CreateDragPreviewOption();
    OH_ArkUI_DragPreviewOption_SetDefaultShadowEnabled(previewOptions, true);
    auto ret1 = OH_ArkUI_DragAction_SetDragPreviewOption(dragAction, previewOptions);

    /**
     * @tc.steps: step2.set dragAction is null, related function is called.
     */
    auto ret2 = OH_ArkUI_DragAction_SetDragPreviewOption(nullptr, previewOptions);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);
    OH_ArkUI_DragPreviewOption_Dispose(previewOptions);
    OH_ArkUI_DragAction_Dispose(dragAction);
    delete uiContext;
}

/**
 * @tc.name: DragAndDropTest0029
 * @tc.desc: Test the OH_ArkUI_DragAction_RegisterStatusListener.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0029, TestSize.Level1)
{
    /**
     * @tc.steps: step1.set dragAction is null, related function is called.
     */
    auto ret = OH_ArkUI_DragAction_RegisterStatusListener(
        nullptr, nullptr, [](ArkUI_DragAndDropInfo* dragAndDropInfo, void* userData) -> void {
            EXPECT_NE(
                OH_ArkUI_DragAndDropInfo_GetDragStatus(dragAndDropInfo), ArkUI_DragStatus::ARKUI_DRAG_STATUS_UNKNOWN);
            EXPECT_NE(OH_ArkUI_DragAndDropInfo_GetDragEvent(dragAndDropInfo), nullptr);
        });
    OH_ArkUI_DragAction_UnregisterStatusListener(nullptr);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: DragAndDropTest0030
 * @tc.desc: Test the OH_ArkUI_DragAndDropInfo_GetDragStatus.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0030, TestSize.Level1)
{
    /**
     * @tc.steps: step1.set dragAction is null, related function is called.
     */
    auto ret1 = OH_ArkUI_DragAndDropInfo_GetDragStatus(nullptr);
    auto ret2 = OH_ArkUI_DragAndDropInfo_GetDragEvent(nullptr);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ret1, ArkUI_DragStatus::ARKUI_DRAG_STATUS_UNKNOWN);
    EXPECT_EQ(ret2, nullptr);
}

/**
 * @tc.name: DragAndDropTest0031
 * @tc.desc: Test the OH_ArkUI_SetNodeDragPreview.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0031, TestSize.Level1)
{
    /**
     * @tc.steps: step1.set ArkUI_NodeHandle is null, related function is called.
     * @tc.expected: Return expected results.
     */
    auto ret = OH_ArkUI_SetNodeDragPreview(nullptr, nullptr);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    /**
     * @tc.steps: step1.set ArkUI_NodeHandle is not null, related function is called.
     * @tc.expected: Return expected results.
     */
    ArkUI_NativeNodeAPI_1 *nodeAPI = nullptr;
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);
    auto dragNode = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    ret = OH_ArkUI_SetNodeDragPreview(dragNode, nullptr);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: DragAndDropTest0032
 * @tc.desc: Test the OH_ArkUI_SetNodeAllowedDropDataTypes.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0032, TestSize.Level1)
{
    /**
     * @tc.steps: step1.set ArkUI_NodeHandle is null, related function is called.
     */
    auto ret1 = OH_ArkUI_SetNodeAllowedDropDataTypes(nullptr, nullptr, -1);

    /**
     * @tc.steps: step1.set ArkUI_NodeHandle and typesArray, related function is called.
     */
    ArkUI_NativeNodeAPI_1 *nodeAPI = nullptr;
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);
    auto dragNode = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    std::vector<const char *> strlist;
    strlist.push_back("general.text");
    strlist.push_back("general.plain-text");
    auto ret2 = OH_ArkUI_SetNodeAllowedDropDataTypes(dragNode, strlist.data(), strlist.size());

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: DragAndDropTest0033
 * @tc.desc: Test the OH_ArkUI_SetDragEventStrictReportWithNode.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0033, TestSize.Level1)
{
    /**
     * @tc.steps: step1.set ArkUI_NodeHandle is null, related function is called.
     */
    auto ret1 = OH_ArkUI_SetDragEventStrictReportWithNode(nullptr, false);

    /**
     * @tc.steps: step1.set ArkUI_NodeHandle and typesArray, related function is called.
     */
    ArkUI_NativeNodeAPI_1 *nodeAPI = nullptr;
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);
    auto dragNode = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    auto ret2 = OH_ArkUI_SetDragEventStrictReportWithNode(dragNode, true);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: DragAndDropTest0034
 * @tc.desc: Test the OH_ArkUI_SetDragEventStrictReportWithContext.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0034, TestSize.Level1)
{
    /**
     * @tc.steps: step1.set ArkUI_NodeHandle is null, related function is called.
     */
    auto ret1 = OH_ArkUI_SetDragEventStrictReportWithContext(nullptr, false);

    /**
     * @tc.steps: step1.set ArkUI_NodeHandle and typesArray, related function is called.
     */
    auto uiContext = new ArkUI_Context({ .id = 1 });
    auto ret2 = OH_ArkUI_SetDragEventStrictReportWithContext(uiContext, true);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_NO_ERROR);
    delete uiContext;
}

/**
 * @tc.name: DragAndDropTest0035
 * @tc.desc: Test the OH_ArkUI_DisallowNodeAnyDropDataTypes.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0035, TestSize.Level1)
{
    /**
     * @tc.steps: step1.set ArkUI_ContextHandle is null, related function is called.
     */
    auto ret1 = OH_ArkUI_DisallowNodeAnyDropDataTypes(nullptr);

    /**
     * @tc.steps: step1.set ArkUI_ContextHandle, related function is called.
     */
    ArkUI_NativeNodeAPI_1 *nodeAPI = nullptr;
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);
    auto dragNode = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    auto ret2 = OH_ArkUI_DisallowNodeAnyDropDataTypes(dragNode);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: DragAndDropTest0036
 * @tc.desc: Test the OH_ArkUI_AllowNodeAllDropDataTypes.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0036, TestSize.Level1)
{
    /**
     * @tc.steps: step1.set ArkUI_ContextHandle is null, related function is called.
     */
    auto ret1 = OH_ArkUI_AllowNodeAllDropDataTypes(nullptr);

    /**
     * @tc.steps: step1.set ArkUI_ContextHandle, related function is called.
     */
    ArkUI_NativeNodeAPI_1 *nodeAPI = nullptr;
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);
    auto dragNode = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    auto ret2 = OH_ArkUI_AllowNodeAllDropDataTypes(dragNode);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: DragAndDropTest0037
 * @tc.desc: Test the OH_ArkUI_DragEvent_GetDragResult.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0037, TestSize.Level1)
{
    /**
     * @tc.steps: step1.set ArkUI_DragEvent is null, related function is called.
     */
    auto ret1 = OH_ArkUI_DragEvent_GetDragResult(nullptr, nullptr);

    /**
     * @tc.steps: step1.set ArkUI_DragEvent and DragResult, related function is called.
     */
    ArkUIDragEvent dragEvent;
    auto* drag_Event = reinterpret_cast<ArkUI_DragEvent*>(&dragEvent);
    ArkUI_DragResult result;
    auto ret2 = OH_ArkUI_DragEvent_GetDragResult(drag_Event, &result);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: DragAndDropTest0038
 * @tc.desc: Test the OH_ArkUI_DragEvent_SetDragResult.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0038, TestSize.Level1)
{
    /**
     * @tc.steps: step1.set ArkUI_DragEvent is null, related function is called.
     */
    auto ret1 = OH_ArkUI_DragEvent_SetDragResult(nullptr, ArkUI_DragResult::ARKUI_DRAG_RESULT_SUCCESSFUL);

    /**
     * @tc.steps: step1.set ArkUI_DragEvent and DragResult, related function is called.
     */
    ArkUIDragEvent dragEvent;
    auto* drag_Event = reinterpret_cast<ArkUI_DragEvent*>(&dragEvent);
    auto ret2 = OH_ArkUI_DragEvent_SetDragResult(drag_Event, ArkUI_DragResult::ARKUI_DRAG_RESULT_SUCCESSFUL);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: DragAndDropTest0039
 * @tc.desc: Test the OH_ArkUI_DragEvent_SetSuggestedDropOperation.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0039, TestSize.Level1)
{
    /**
     * @tc.steps: step1.set ArkUI_DragEvent is null, related function is called.
     */
    auto ret1 = OH_ArkUI_DragEvent_SetSuggestedDropOperation(nullptr,
        ArkUI_DropOperation::ARKUI_DROP_OPERATION_COPY);

    /**
     * @tc.steps: step1.set ArkUI_DragEvent and DropOperation, related function is called.
     */
    ArkUIDragEvent dragEvent;
    auto* drag_Event = reinterpret_cast<ArkUI_DragEvent*>(&dragEvent);
    auto ret2 = OH_ArkUI_DragEvent_SetSuggestedDropOperation(drag_Event,
        ArkUI_DropOperation::ARKUI_DROP_OPERATION_COPY);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: DragAndDropTest0040
 * @tc.desc: Test the OH_ArkUI_CancelDataLoading.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0040, TestSize.Level1)
{
    /**
     * @tc.steps: step1.set ArkUI_ContextHandle is null, related function is called.
     */
    const char* key = "testKey";
    auto ret1 = OH_ArkUI_CancelDataLoading(nullptr, key);
    
    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: DragAndDropTest0041
 * @tc.desc: Test the OH_ArkUI_DisableDropDataPrefetchOnNode.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0041, TestSize.Level1)
{
    /**
     * @tc.steps: step1.set ArkUI_NodeHandle is null, related function is called.
     */
    auto ret1 = OH_ArkUI_DisableDropDataPrefetchOnNode(nullptr, false);

    /**
     * @tc.steps: step1.set ArkUI_NodeHandle, related function is called.
     */
    ArkUI_NativeNodeAPI_1 *nodeAPI = nullptr;
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);
    auto dragNode = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    auto ret2 = OH_ArkUI_DisableDropDataPrefetchOnNode(dragNode, false);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: DragAndDropTest0042
 * @tc.desc: Test the OH_ArkUI_DragEvent_RequestDragEndPending.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0042, TestSize.Level1)
{
    /**
     * @tc.steps: step1.set ArkUI_DragEvent is null, related function is called.
     */
    auto ret1 = OH_ArkUI_DragEvent_RequestDragEndPending(nullptr, nullptr);

    /**
     * @tc.steps: step1.set ArkUI_DragEvent and requestIdentify, related function is called.
     */
    ArkUIDragEvent dragEvent;
    auto* drag_Event = reinterpret_cast<ArkUI_DragEvent*>(&dragEvent);
    int32_t requestIdentify = 0;
    auto ret2 = OH_ArkUI_DragEvent_RequestDragEndPending(drag_Event, &requestIdentify);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_DRAG_DROP_OPERATION_NOT_ALLOWED);
    EXPECT_EQ(dragEvent.isDragEndPending, false);
}

/**
 * @tc.name: DragAndDropTest0043
 * @tc.desc: test set DragEvent property function;
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0043, TestSize.Level1)
{
    /**
     *@tc.steps : step1.create and set property.
     */
    ArkUIDragEvent dragEvent;
    dragEvent.displayId = DISPLAYID;
    auto* drag_Event = reinterpret_cast<ArkUI_DragEvent*>(&dragEvent);
    int32_t displayId = -1;
    auto ret1 = OH_ArkUI_DragEvent_GetDisplayId(drag_Event, &displayId);
    auto ret2 = OH_ArkUI_DragEvent_GetDisplayId(nullptr, &displayId);
    auto ret3 = OH_ArkUI_DragEvent_GetDisplayId(drag_Event, nullptr);
    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(displayId, DISPLAYID);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(ret3, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: DragAndDropTest0044
 * @tc.desc: Test the OH_ArkUI_DragEvent_GetDragSource.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0044, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create DragEvent
     */
    char bundleNameError[10];
    int32_t lengthError = 10;
    ArkUIDragEvent dragEvent;
    char dragEventBundleName[] = "com.example.tdd";
    int32_t err = strcpy_s(dragEvent.bundleName, sizeof(dragEvent.bundleName), dragEventBundleName);
    ASSERT_EQ(err, 0);
    auto* drag_Event = reinterpret_cast<ArkUI_DragEvent*>(&dragEvent);

    /**
     * @tc.steps: step2.set bundleNameError length shorter than dragEventBundleName, related function is called.
     */
    auto ret1 = OH_ArkUI_DragEvent_GetDragSource(drag_Event, bundleNameError, lengthError);
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);

    /**
     * @tc.steps: step3.set ArkUI_DragEvent null, related function is called.
     */
    char bundleName[200];
    int32_t length = 200;
    auto ret2 = OH_ArkUI_DragEvent_GetDragSource(nullptr, bundleNameError, lengthError);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);

    /**
     * @tc.steps: step3.set bundleName null, related function is called.
     */
    auto ret3 = OH_ArkUI_DragEvent_GetDragSource(drag_Event, nullptr, length);
    EXPECT_EQ(ret3, ARKUI_ERROR_CODE_PARAM_INVALID);

    /**
     * @tc.steps: step4.set bundleName not null, related function is called.
     */
    auto ret4 = OH_ArkUI_DragEvent_GetDragSource(drag_Event, bundleName, length);
    EXPECT_EQ(ret4, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(*bundleName, *dragEventBundleName);
}

/**
 * @tc.name: DragAndDropTest0045
 * @tc.desc: Test the OH_ArkUI_DragEvent_IsRemote.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0045, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create DragEvent
     */
    bool isRemote = false;
    ArkUIDragEvent dragEvent;
    auto* drag_Event = reinterpret_cast<ArkUI_DragEvent*>(&dragEvent);

    /**
     * @tc.steps: step2.set ArkUI_DragEvent null, related function is called.
     */
    auto ret1 = OH_ArkUI_DragEvent_IsRemote(nullptr, &isRemote);
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);

    /**
     * @tc.steps: step2.set isRemote null, related function is called.
     */
    auto ret2 = OH_ArkUI_DragEvent_IsRemote(drag_Event, nullptr);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);

    /**
     * @tc.steps: step3.set isRemote not null, related function is called.
     */
    dragEvent.isRemoteDev = true;
    auto ret3 = OH_ArkUI_DragEvent_IsRemote(drag_Event, &isRemote);
    EXPECT_EQ(ret3, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(isRemote, dragEvent.isRemoteDev);
}

/**
 * @tc.name: DragAndDropTest0046
 * @tc.desc: Test the OH_ArkUI_DragAction_SetDataLoadParams.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0046, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create dragAction
     */
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_STACK);
    auto rootFrameNode = reinterpret_cast<ArkUI_Node*>(rootNode);
    ASSERT_NE(rootFrameNode, nullptr);
    auto frameNode = reinterpret_cast<NG::FrameNode*>(rootFrameNode->uiNodeHandle);
    ASSERT_NE(frameNode, nullptr);
    auto context = NG::MockPipelineContext::GetCurrent();
    frameNode->context_ = AceType::RawPtr(context);
    auto* dragAction = OH_ArkUI_CreateDragActionWithNode(rootNode);
    ASSERT_NE(dragAction, nullptr);
    OH_UdmfDataLoadParams* dataLoadParams = OH_UdmfDataLoadParams_Create();

    /**
     * @tc.steps: step2.set dragAction null, related function is called.
     */
    auto ret1 = OH_ArkUI_DragAction_SetDataLoadParams(nullptr, dataLoadParams);
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);

    /**
     * @tc.steps: step3.set dataLoadParams null, related function is called.
     */
    auto ret2 = OH_ArkUI_DragAction_SetDataLoadParams(dragAction, nullptr);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);

    /**
     * @tc.steps: step4.set dragAction and dataLoadParams not null, related function is called.
     */
    auto ret3 = OH_ArkUI_DragAction_SetDataLoadParams(dragAction, dataLoadParams);
    OH_UdmfDataLoadParams_Destroy(dataLoadParams);
    EXPECT_EQ(ret3, ARKUI_ERROR_CODE_NO_ERROR);
    auto* dragActions = reinterpret_cast<ArkUIDragAction*>(dragAction);
    ASSERT_NE(dragAction, nullptr);
    EXPECT_EQ(dragActions->useDataLoadParams, true);
    OH_ArkUI_DragAction_Dispose(dragAction);
}

/**
 * @tc.name: DragAndDropTest0047
 * @tc.desc: Test the OH_ArkUI_DragEvent_SetDataLoadParams.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0047, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create DragEvent, related function is called.
     */
    ArkUIDragEvent dragEvent;
    dragEvent.key = "key_string";
    auto* drag_Event = reinterpret_cast<ArkUI_DragEvent*>(&dragEvent);
    ASSERT_NE(drag_Event, nullptr);
    OH_UdmfDataLoadParams* dataLoadParams = OH_UdmfDataLoadParams_Create();
    ASSERT_NE(dataLoadParams, nullptr);

    /**
     * @tc.steps: step2.set dragAction null, related function is called.
     */
    auto ret1 = OH_ArkUI_DragEvent_SetDataLoadParams(nullptr, dataLoadParams);
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);

    /**
     * @tc.steps: step3.set dataLoadParams null, related function is called.
     */
    auto ret2 = OH_ArkUI_DragEvent_SetDataLoadParams(drag_Event, nullptr);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);

    /**
     * @tc.steps: step4.set dragAction 、 dataLoadParams not null , related function is called.
     */
    OH_UdmfDataLoadInfo* info = OH_UdmfDataLoadInfo_Create();
    OH_UdmfDataLoadInfo_SetRecordCount(info, 100);
    OH_UdmfDataLoadParams_SetDataLoadInfo(dataLoadParams, info);
    auto ret3 = OH_ArkUI_DragEvent_SetDataLoadParams(drag_Event, dataLoadParams);
    OH_UdmfDataLoadInfo_Destroy(info);
    OH_UdmfDataLoadParams_Destroy(dataLoadParams);
    EXPECT_EQ(ret3, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(dragEvent.useDataLoadParams, true);
}

/**
 * @tc.name: DragAndDropTest0048
 * @tc.desc: test set DragEvent property function;
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0048, TestSize.Level1)
{
    /**
     *@tc.steps : step1.create and set property.
     */
    ArkUIDragEvent dragEvent;
    dragEvent.windowX = WINDOW_X;
    dragEvent.windowY = WINDOW_Y;
    dragEvent.displayX = DISPLAY_X;
    dragEvent.displayY = DISPLAY_Y;
    dragEvent.globalDisplayX = static_cast<double>(GLOBAL_DISPLAY_X);
    dragEvent.globalDisplayY = static_cast<double>(GLOBAL_DISPLAY_Y);
    dragEvent.touchPointX = TOUCH_POINT_X;
    dragEvent.touchPointY = TOUCH_POINT_Y;

    dragEvent.previewRectWidth = PREVIEW_RECT_WIDTH;
    dragEvent.previewRectHeight = PREVIEW_RECT_HEIGHT;
    dragEvent.velocityX = VELOCITY_X;
    dragEvent.velocityY = VELOCITY_Y;
    dragEvent.velocity = VELOCITY;
    auto* drag_Event = reinterpret_cast<ArkUI_DragEvent*>(&dragEvent);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(OH_ArkUI_DragEvent_GetTouchPointXToWindow(drag_Event), WINDOW_X);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetTouchPointYToWindow(drag_Event), WINDOW_Y);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetPreviewTouchPointX(drag_Event), TOUCH_POINT_X);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetPreviewTouchPointY(drag_Event), TOUCH_POINT_Y);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetTouchPointXToDisplay(drag_Event), DISPLAY_X);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetTouchPointYToDisplay(drag_Event), DISPLAY_Y);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetTouchPointXToGlobalDisplay(drag_Event), GLOBAL_DISPLAY_X);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetTouchPointYToGlobalDisplay(drag_Event), GLOBAL_DISPLAY_Y);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetPreviewRectWidth(drag_Event), PREVIEW_RECT_WIDTH);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetPreviewRectHeight(drag_Event), PREVIEW_RECT_HEIGHT);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetVelocityX(drag_Event), VELOCITY_X);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetVelocityY(drag_Event), VELOCITY_Y);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetVelocity(drag_Event), VELOCITY);
}

/**
 * @tc.name: DragAndDropTest0049
 * @tc.desc: test set DragEvent property function;
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0049, TestSize.Level1)
{
    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(OH_ArkUI_DragEvent_GetTouchPointXToWindow(nullptr), 0.0f);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetTouchPointYToWindow(nullptr), 0.0f);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetPreviewTouchPointX(nullptr), 0.0f);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetPreviewTouchPointY(nullptr), 0.0f);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetTouchPointXToDisplay(nullptr), 0.0f);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetTouchPointYToDisplay(nullptr), 0.0f);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetTouchPointXToGlobalDisplay(nullptr), 0.0f);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetTouchPointYToGlobalDisplay(nullptr), 0.0f);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetPreviewRectWidth(nullptr), 0.0f);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetPreviewRectHeight(nullptr), 0.0f);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetVelocityX(nullptr), 0.0f);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetVelocityY(nullptr), 0.0f);
    EXPECT_EQ(OH_ArkUI_DragEvent_GetVelocity(nullptr), 0.0f);
}

/**
 * @tc.name: DragAndDropTest0050
 * @tc.desc: Test OH_ArkUI_DragEvent_GetUdmfData.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0050, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create DragEvent, related function is called.
     */
    ArkUIDragEvent dragEvent;
    dragEvent.key = "key_string";
    auto* drag_Event = reinterpret_cast<ArkUI_DragEvent*>(&dragEvent);
    ASSERT_NE(drag_Event, nullptr);
    OH_UdmfData* data = OH_UdmfData_Create();
    ASSERT_NE(data, nullptr);

    /**
     * @tc.steps: step2.set params null.
     */
    int32_t ret = OH_ArkUI_DragEvent_GetUdmfData(nullptr, data);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    ret = OH_ArkUI_DragEvent_GetUdmfData(drag_Event, nullptr);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    /**
     * @tc.steps: step2.set params not null, related function is called.
     */
    ret = OH_ArkUI_DragEvent_GetUdmfData(drag_Event, data);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
    OH_UdmfData_Destroy(data);
}

/**
 * @tc.name: DragAndDropTest0051
 * @tc.desc: Test OH_ArkUI_DragAction_SetPixelMaps.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0051, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create params.
     */
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_STACK);
    auto rootFrameNode = reinterpret_cast<ArkUI_Node*>(rootNode);
    ASSERT_NE(rootFrameNode, nullptr);
    auto frameNode = reinterpret_cast<NG::FrameNode*>(rootFrameNode->uiNodeHandle);
    ASSERT_NE(frameNode, nullptr);
    auto context = NG::MockPipelineContext::GetCurrent();
    frameNode->context_ = AceType::RawPtr(context);
    auto* dragAction = OH_ArkUI_CreateDragActionWithNode(rootNode);
    ASSERT_NE(dragAction, nullptr);
    OH_PixelmapNative* pixelmapArray[2];
    int32_t size = 2;

    /**
     * @tc.steps: step2.set params null, related function is called.
     */
    int32_t ret = OH_ArkUI_DragAction_SetPixelMaps(nullptr, nullptr, 0);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    ret = OH_ArkUI_DragAction_SetPixelMaps(dragAction, nullptr, 0);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    ret = OH_ArkUI_DragAction_SetPixelMaps(dragAction, pixelmapArray, 0);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step2.set params not null, related function is called.
     */
    ret = OH_ArkUI_DragAction_SetPixelMaps(dragAction, pixelmapArray, size);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
    OH_ArkUI_DragAction_Dispose(dragAction);
}

/**
 * @tc.name: DragAndDropTest0052
 * @tc.desc: Test OH_ArkUI_DragAction_SetData.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0052, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create DragEvent, related function is called.
     */
    auto uiContext = new ArkUI_Context({ .id = 1 });
    auto dragAction = OH_ArkUI_CreateDragActionWithContext(uiContext);
    EXPECT_NE(dragAction, nullptr);
    OH_UdmfData* data = OH_UdmfData_Create();
    ASSERT_NE(data, nullptr);

    /**
     * @tc.steps: step2.set params null.
     */
    int32_t ret = OH_ArkUI_DragAction_SetData(nullptr, data);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    ret = OH_ArkUI_DragAction_SetData(dragAction, nullptr);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    /**
     * @tc.steps: step2.set params not null, related function is called.
     */
    ret = OH_ArkUI_DragAction_SetData(dragAction, data);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_DragAction_Dispose(dragAction);
    OH_UdmfData_Destroy(data);
    delete uiContext;
}

/**
 * @tc.name: DragAndDropTest0053
 * @tc.desc: Test OH_ArkUI_DragEvent_StartDataLoading.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0053, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create params.
     */
    char key[] = "key_string1";
    OH_UdmfGetDataParams* options = OH_UdmfGetDataParams_Create();
    unsigned int keyLen = 513;
    ArkUIDragEvent dragEvent;
    dragEvent.key = "key_string";
    dragEvent.isSuitGetData = false;
    auto* drag_Event = reinterpret_cast<ArkUI_DragEvent*>(&dragEvent);
    ASSERT_NE(drag_Event, nullptr);

    /**
     * @tc.steps: step2.set params null, related function is called.
     */
    int32_t ret = OH_ArkUI_DragEvent_StartDataLoading(nullptr, nullptr, nullptr, 0);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    ret = OH_ArkUI_DragEvent_StartDataLoading(drag_Event, nullptr, nullptr, 0);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    ret = OH_ArkUI_DragEvent_StartDataLoading(drag_Event, options, nullptr, 0);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    ret = OH_ArkUI_DragEvent_StartDataLoading(drag_Event, options, key, 0);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    /**
     * @tc.steps: step2.set params not null, related function is called.
     */
    ret = OH_ArkUI_DragEvent_StartDataLoading(drag_Event, options, key, keyLen);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
    dragEvent.isSuitGetData = true;
    drag_Event = reinterpret_cast<ArkUI_DragEvent*>(&dragEvent);
    ASSERT_NE(drag_Event, nullptr);
    ret = OH_ArkUI_DragEvent_StartDataLoading(drag_Event, options, key, keyLen);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
    OH_UdmfGetDataParams_Destroy(options);
}

/**
 * @tc.name: DragAndDropTest0054
 * @tc.desc: Test OH_ArkUI_DragEvent_RequestDragEndPending.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0054, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create DragEvent, related function is called.
     */
    int32_t requestIdentify = 1;
    ArkUIDragEvent dragEvent;
    dragEvent.key = "key_string";
    auto* drag_Event = reinterpret_cast<ArkUI_DragEvent*>(&dragEvent);
    ASSERT_NE(drag_Event, nullptr);

    /**
     * @tc.steps: step2.set params null.
     */
    int32_t ret = OH_ArkUI_DragEvent_RequestDragEndPending(drag_Event, nullptr);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_DRAG_DROP_OPERATION_NOT_ALLOWED);
    ret = OH_ArkUI_DragEvent_RequestDragEndPending(nullptr, nullptr);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    /**
     * @tc.steps: step2.set params not null, related function is called.
     */
    ret = OH_ArkUI_DragEvent_RequestDragEndPending(drag_Event, &requestIdentify);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_DRAG_DROP_OPERATION_NOT_ALLOWED);
}

/**
 * @tc.name: DragAndDropTest0055
 * @tc.desc: Test OH_ArkUI_NotifyDragResult.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0055, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create DragEvent, related function is called.
     */
    int32_t requestIdentify = 1;
    ArkUI_DragResult result = ARKUI_DRAG_RESULT_SUCCESSFUL;

    /**
     * @tc.steps: step2.set params null.
     */
    int32_t ret = OH_ArkUI_NotifyDragResult(0, result);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_DRAG_DROP_OPERATION_NOT_ALLOWED);

    /**
     * @tc.steps: step2.set params not null, related function is called.
     */
    ret = OH_ArkUI_NotifyDragResult(requestIdentify, result);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_DRAG_DROP_OPERATION_NOT_ALLOWED);
}

/**
 * @tc.name: DragAndDropTest0056
 * @tc.desc: Test OH_ArkUI_NotifyDragEndPendingDone.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0056, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create DragEvent, related function is called.
     */
    int32_t requestIdentify = 1;

    /**
     * @tc.steps: step2.set params null.
     */
    int32_t ret = OH_ArkUI_NotifyDragEndPendingDone(0);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_DRAG_DROP_OPERATION_NOT_ALLOWED);

    /**
     * @tc.steps: step2.set params not null, related function is called.
     */
    ret = OH_ArkUI_NotifyDragEndPendingDone(requestIdentify);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_DRAG_DROP_OPERATION_NOT_ALLOWED);
}

/**
 * @tc.name: DragAndDropTest0057
 * @tc.desc: Test OH_ArkUI_EnableDropDisallowedBadge.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0057, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create DragEvent, related function is called.
     */
    int32_t requestIdentify = 1;
    auto uiContext = new ArkUI_Context({ .id = 1 });

    /**
     * @tc.steps: step2.set params null.
     */
    int32_t ret = OH_ArkUI_EnableDropDisallowedBadge(nullptr, requestIdentify);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    /**
     * @tc.steps: step2.set params not null, related function is called.
     */
    ret = OH_ArkUI_EnableDropDisallowedBadge(uiContext, requestIdentify);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    delete uiContext;
}

/**
 * @tc.name: DragAndDropTest0058
 * @tc.desc: Test OH_ArkUI_DragEvent_SetData.
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTest, DragAndDropTest0058, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create and set property.
     */
    ArkUIDragEvent dragEvent;
    OH_UdmfData* data = OH_UdmfData_Create();
    ASSERT_NE(data, nullptr);
    dragEvent.unifiedData = data;
    auto* drag_Event = reinterpret_cast<ArkUI_DragEvent*>(&dragEvent);

    auto ret1 = OH_ArkUI_DragEvent_SetData(nullptr, data);
    auto ret2 = OH_ArkUI_DragEvent_SetData(drag_Event, nullptr);
    auto ret3 = OH_ArkUI_DragEvent_SetData(drag_Event, data);
    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(ret3, ARKUI_ERROR_CODE_NO_ERROR);
    OH_UdmfData_Destroy(data);
}
} // namespace OHOS::Ace