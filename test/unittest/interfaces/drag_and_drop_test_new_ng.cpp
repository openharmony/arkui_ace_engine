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

class DragAndDropTestNewNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        NG::MockPipelineContext::SetUp();
        MockContainer::SetUp();
        MockContainer::Current()->pipelineContext_ = NG::MockPipelineContext::GetCurrent();
        MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
        MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    }

    static void TearDownTestSuite()
    {
        NG::MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }
};

/**
 * @tc.name: OH_ArkUI_DragEvent_GetDisplayId_001
 * @tc.desc: Test OH_ArkUI_DragEvent_GetDisplayId with null event
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragEvent_GetDisplayId_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null event pointer
     * @tc.expected: Returns ARKUI_ERROR_CODE_PARAM_INVALID
     */
    int32_t displayId;
    auto result = OH_ArkUI_DragEvent_GetDisplayId(nullptr, &displayId);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_DragEvent_GetDisplayId_002
 * @tc.desc: Test OH_ArkUI_DragEvent_GetDisplayId with null displayId
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragEvent_GetDisplayId_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null displayId pointer
     * @tc.expected: Returns ARKUI_ERROR_CODE_PARAM_INVALID
     */
    ArkUIDragEvent dragEvent;
    auto* drag_Event = reinterpret_cast<ArkUI_DragEvent*>(&dragEvent);
    auto result = OH_ArkUI_DragEvent_GetDisplayId(drag_Event, nullptr);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_DragEvent_GetModifierKeyStates_001
 * @tc.desc: Test OH_ArkUI_DragEvent_GetModifierKeyStates with null event
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragEvent_GetModifierKeyStates_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null event pointer
     * @tc.expected: Returns ARKUI_ERROR_CODE_PARAM_INVALID
     */
    uint64_t keys;
    auto result = OH_ArkUI_DragEvent_GetModifierKeyStates(nullptr, &keys);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_DragEvent_GetModifierKeyStates_002
 * @tc.desc: Test OH_ArkUI_DragEvent_GetModifierKeyStates with null keys
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragEvent_GetModifierKeyStates_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null keys pointer
     * @tc.expected: Returns ARKUI_ERROR_CODE_PARAM_INVALID
     */
    ArkUIDragEvent dragEvent;
    auto* drag_Event = reinterpret_cast<ArkUI_DragEvent*>(&dragEvent);
    auto result = OH_ArkUI_DragEvent_GetModifierKeyStates(drag_Event, nullptr);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_DragEvent_SetData_001
 * @tc.desc: Test OH_ArkUI_DragEvent_SetData with null event
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragEvent_SetData_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null event pointer
     * @tc.expected: Returns ARKUI_ERROR_CODE_PARAM_INVALID
     */
    OH_UdmfData* data = OH_UdmfData_Create();
    ASSERT_NE(data, nullptr);
    auto result = OH_ArkUI_DragEvent_SetData(nullptr, data);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_DragEvent_SetData_002
 * @tc.desc: Test OH_ArkUI_DragEvent_SetData with null data
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragEvent_SetData_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null data pointer
     * @tc.expected: Returns ARKUI_ERROR_CODE_PARAM_INVALID
     */
    ArkUIDragEvent dragEvent;
    auto* drag_Event = reinterpret_cast<ArkUI_DragEvent*>(&dragEvent);
    auto result = OH_ArkUI_DragEvent_SetData(drag_Event, nullptr);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_DragEvent_GetDragSource_001
 * @tc.desc: Test OH_ArkUI_DragEvent_GetDragSource with null event
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragEvent_GetDragSource_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null event pointer
     * @tc.expected: Returns ARKUI_ERROR_CODE_PARAM_INVALID
     */
    char bundleName[100];
    auto result = OH_ArkUI_DragEvent_GetDragSource(nullptr, bundleName, 100);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_DragEvent_GetDragSource_002
 * @tc.desc: Test OH_ArkUI_DragEvent_GetDragSource with null bundleName
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragEvent_GetDragSource_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null bundleName pointer
     * @tc.expected: Returns ARKUI_ERROR_CODE_PARAM_INVALID
     */
    ArkUIDragEvent dragEvent;
    auto* drag_Event = reinterpret_cast<ArkUI_DragEvent*>(&dragEvent);
    auto result = OH_ArkUI_DragEvent_GetDragSource(drag_Event, nullptr, 100);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_DragEvent_IsRemote_001
 * @tc.desc: Test OH_ArkUI_DragEvent_IsRemote with null event
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragEvent_IsRemote_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null event pointer
     * @tc.expected: Returns ARKUI_ERROR_CODE_PARAM_INVALID
     */
    bool isRemote;
    auto result = OH_ArkUI_DragEvent_IsRemote(nullptr, &isRemote);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_DragEvent_IsRemote_002
 * @tc.desc: Test OH_ArkUI_DragEvent_IsRemote with null isRemote
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragEvent_IsRemote_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null isRemote pointer
     * @tc.expected: Returns ARKUI_ERROR_CODE_PARAM_INVALID
     */
    ArkUIDragEvent dragEvent;
    auto* drag_Event = reinterpret_cast<ArkUI_DragEvent*>(&dragEvent);
    auto result = OH_ArkUI_DragEvent_IsRemote(drag_Event, nullptr);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_DragEvent_GetUdmfData_001
 * @tc.desc: Test OH_ArkUI_DragEvent_GetUdmfData with null event
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragEvent_GetUdmfData_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null event pointer
     * @tc.expected: Returns ARKUI_ERROR_CODE_PARAM_INVALID
     */
    OH_UdmfData* data = OH_UdmfData_Create();
    ASSERT_NE(data, nullptr);
    auto result = OH_ArkUI_DragEvent_GetUdmfData(nullptr, data);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_DragEvent_GetUdmfData_002
 * @tc.desc: Test OH_ArkUI_DragEvent_GetUdmfData with null data
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragEvent_GetUdmfData_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null data pointer
     * @tc.expected: Returns ARKUI_ERROR_CODE_PARAM_INVALID
     */
    ArkUIDragEvent dragEvent;
    auto* drag_Event = reinterpret_cast<ArkUI_DragEvent*>(&dragEvent);
    auto result = OH_ArkUI_DragEvent_GetUdmfData(drag_Event, nullptr);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_DragEvent_GetDataTypeCount_001
 * @tc.desc: Test OH_ArkUI_DragEvent_GetDataTypeCount with null event
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragEvent_GetDataTypeCount_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null event pointer
     * @tc.expected: Returns ARKUI_ERROR_CODE_PARAM_INVALID
     */
    int32_t count;
    auto result = OH_ArkUI_DragEvent_GetDataTypeCount(nullptr, &count);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_DragEvent_GetDataTypeCount_002
 * @tc.desc: Test OH_ArkUI_DragEvent_GetDataTypeCount with null count
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragEvent_GetDataTypeCount_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null count pointer
     * @tc.expected: Returns ARKUI_ERROR_CODE_PARAM_INVALID
     */
    ArkUIDragEvent dragEvent;
    auto* drag_Event = reinterpret_cast<ArkUI_DragEvent*>(&dragEvent);
    auto result = OH_ArkUI_DragEvent_GetDataTypeCount(drag_Event, nullptr);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_DragEvent_GetDataTypes_001
 * @tc.desc: Test OH_ArkUI_DragEvent_GetDataTypes with null event
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragEvent_GetDataTypes_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null event pointer
     * @tc.expected: Returns ARKUI_ERROR_CODE_PARAM_INVALID
     */
    char* eventTypeArray[10];
    auto result = OH_ArkUI_DragEvent_GetDataTypes(nullptr, eventTypeArray, 10, 100);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_DragEvent_GetDataTypes_002
 * @tc.desc: Test OH_ArkUI_DragEvent_GetDataTypes with null array
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragEvent_GetDataTypes_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null eventTypeArray pointer
     * @tc.expected: Returns ARKUI_ERROR_CODE_PARAM_INVALID
     */
    ArkUIDragEvent dragEvent;
    auto* drag_Event = reinterpret_cast<ArkUI_DragEvent*>(&dragEvent);
    auto result = OH_ArkUI_DragEvent_GetDataTypes(drag_Event, nullptr, 10, 100);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_CreateDragActionWithNode_001
 * @tc.desc: Test OH_ArkUI_CreateDragActionWithNode with null node
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_CreateDragActionWithNode_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null node pointer
     * @tc.expected: Returns nullptr
     */
    auto dragAction = OH_ArkUI_CreateDragActionWithNode(nullptr);
    EXPECT_EQ(dragAction, nullptr);
}

/**
 * @tc.name: OH_ArkUI_CreateDragActionWithContext_001
 * @tc.desc: Test OH_ArkUI_CreateDragActionWithContext with null context
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_CreateDragActionWithContext_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null context pointer
     * @tc.expected: Returns nullptr
     */
    auto dragAction = OH_ArkUI_CreateDragActionWithContext(nullptr);
    EXPECT_EQ(dragAction, nullptr);
}

/**
 * @tc.name: OH_ArkUI_DragAction_Dispose_001
 * @tc.desc: Test OH_ArkUI_DragAction_Dispose with null action
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragAction_Dispose_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null action pointer
     * @tc.expected: Function executes without crash
     */
    OH_ArkUI_DragAction_Dispose(nullptr);
    SUCCEED();
}

/**
 * @tc.name: OH_ArkUI_DragAction_SetPointerId_001
 * @tc.desc: Test OH_ArkUI_DragAction_SetPointerId with null action
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragAction_SetPointerId_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null action pointer
     * @tc.expected: Returns ARKUI_ERROR_CODE_PARAM_INVALID
     */
    auto result = OH_ArkUI_DragAction_SetPointerId(nullptr, 0);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_DragAction_SetPointerId_002
 * @tc.desc: Test OH_ArkUI_DragAction_SetPointerId with invalid pointerId (too large)
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragAction_SetPointerId_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with pointerId > MAX_POINTID (9)
     * @tc.expected: Returns ARKUI_ERROR_CODE_PARAM_INVALID
     */
    auto uiContext = new ArkUI_Context({ .id = 1 });
    auto dragAction = OH_ArkUI_CreateDragActionWithContext(uiContext);
    ASSERT_NE(dragAction, nullptr);
    auto result = OH_ArkUI_DragAction_SetPointerId(dragAction, 10);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_DragAction_SetPointerId_003
 * @tc.desc: Test OH_ArkUI_DragAction_SetPointerId with invalid pointerId (negative)
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragAction_SetPointerId_003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with negative pointerId
     * @tc.expected: Returns ARKUI_ERROR_CODE_PARAM_INVALID
     */
    auto uiContext = new ArkUI_Context({ .id = 1 });
    auto dragAction = OH_ArkUI_CreateDragActionWithContext(uiContext);
    ASSERT_NE(dragAction, nullptr);
    auto result = OH_ArkUI_DragAction_SetPointerId(dragAction, -1);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_DragAction_SetPixelMaps_001
 * @tc.desc: Test OH_ArkUI_DragAction_SetPixelMaps with null action
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragAction_SetPixelMaps_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null action pointer
     * @tc.expected: Returns ARKUI_ERROR_CODE_PARAM_INVALID
     */
    OH_PixelmapNative* pixelmapArray[1] = { nullptr };
    auto result = OH_ArkUI_DragAction_SetPixelMaps(nullptr, pixelmapArray, 1);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_DragAction_SetPixelMaps_002
 * @tc.desc: Test OH_ArkUI_DragAction_SetPixelMaps with null array
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragAction_SetPixelMaps_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null pixelmapArray pointer
     * @tc.expected: Returns ARKUI_ERROR_CODE_PARAM_INVALID
     */
    auto uiContext = new ArkUI_Context({ .id = 1 });
    auto dragAction = OH_ArkUI_CreateDragActionWithContext(uiContext);
    ASSERT_NE(dragAction, nullptr);
    auto result = OH_ArkUI_DragAction_SetPixelMaps(dragAction, nullptr, 1);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_DragAction_SetTouchPointX_001
 * @tc.desc: Test OH_ArkUI_DragAction_SetTouchPointX with null action
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragAction_SetTouchPointX_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null action pointer
     * @tc.expected: Returns ARKUI_ERROR_CODE_PARAM_INVALID
     */
    auto result = OH_ArkUI_DragAction_SetTouchPointX(nullptr, 100.0f);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_DragAction_SetTouchPointY_001
 * @tc.desc: Test OH_ArkUI_DragAction_SetTouchPointY with null action
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragAction_SetTouchPointY_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null action pointer
     * @tc.expected: Returns ARKUI_ERROR_CODE_PARAM_INVALID
     */
    auto result = OH_ArkUI_DragAction_SetTouchPointY(nullptr, 100.0f);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_DragAction_SetData_001
 * @tc.desc: Test OH_ArkUI_DragAction_SetData with null action
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragAction_SetData_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null action pointer
     * @tc.expected: Returns ARKUI_ERROR_CODE_PARAM_INVALID
     */
    OH_UdmfData* data = OH_UdmfData_Create();
    ASSERT_NE(data, nullptr);
    auto result = OH_ArkUI_DragAction_SetData(nullptr, data);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_DragAction_SetData_002
 * @tc.desc: Test OH_ArkUI_DragAction_SetData with null data
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragAction_SetData_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null data pointer
     * @tc.expected: Returns ARKUI_ERROR_CODE_PARAM_INVALID
     */
    auto uiContext = new ArkUI_Context({ .id = 1 });
    auto dragAction = OH_ArkUI_CreateDragActionWithContext(uiContext);
    ASSERT_NE(dragAction, nullptr);
    auto result = OH_ArkUI_DragAction_SetData(dragAction, nullptr);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_DragAction_SetDragPreviewOption_001
 * @tc.desc: Test OH_ArkUI_DragAction_SetDragPreviewOption with null action
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragAction_SetDragPreviewOption_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null action pointer
     * @tc.expected: Returns ARKUI_ERROR_CODE_PARAM_INVALID
     */
    auto *previewOptions = OH_ArkUI_CreateDragPreviewOption();
    EXPECT_NE(previewOptions, nullptr);
    auto result = OH_ArkUI_DragAction_SetDragPreviewOption(nullptr, previewOptions);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_DragAction_SetDragPreviewOption_002
 * @tc.desc: Test OH_ArkUI_DragAction_SetDragPreviewOption with null option
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragAction_SetDragPreviewOption_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null option pointer
     * @tc.expected: Returns ARKUI_ERROR_CODE_PARAM_INVALID
     */
    auto uiContext = new ArkUI_Context({ .id = 1 });
    auto dragAction = OH_ArkUI_CreateDragActionWithContext(uiContext);
    ASSERT_NE(dragAction, nullptr);
    auto result = OH_ArkUI_DragAction_SetDragPreviewOption(dragAction, nullptr);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_CreateDragPreviewOption_001
 * @tc.desc: Test OH_ArkUI_CreateDragPreviewOption
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_CreateDragPreviewOption_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create drag preview option
     * @tc.expected: Returns non-null pointer
     */
    auto option = OH_ArkUI_CreateDragPreviewOption();
    EXPECT_NE(option, nullptr);
    OH_ArkUI_DragPreviewOption_Dispose(option);
}

/**
 * @tc.name: OH_ArkUI_DragPreviewOption_Dispose_001
 * @tc.desc: Test OH_ArkUI_DragPreviewOption_Dispose with null option
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragPreviewOption_Dispose_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null option pointer
     * @tc.expected: Function executes without crash
     */
    OH_ArkUI_DragPreviewOption_Dispose(nullptr);
    SUCCEED();
}

/**
 * @tc.name: OH_ArkUI_DragPreviewOption_SetScaleMode_001
 * @tc.desc: Test OH_ArkUI_DragPreviewOption_SetScaleMode with null option
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragPreviewOption_SetScaleMode_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null option pointer
     * @tc.expected: Returns ARKUI_ERROR_CODE_PARAM_INVALID
     */
    auto result =
        OH_ArkUI_DragPreviewOption_SetScaleMode(nullptr, ArkUI_DragPreviewScaleMode::ARKUI_DRAG_PREVIEW_SCALE_AUTO);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_DragPreviewOption_SetScaleMode_002
 * @tc.desc: Test OH_ArkUI_DragPreviewOption_SetScaleMode with AUTO mode
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragPreviewOption_SetScaleMode_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create option and set scale mode to AUTO
     * @tc.expected: Returns ARKUI_ERROR_CODE_NO_ERROR
     */
    auto option = OH_ArkUI_CreateDragPreviewOption();
    ASSERT_NE(option, nullptr);
    auto result =
        OH_ArkUI_DragPreviewOption_SetScaleMode(option, ArkUI_DragPreviewScaleMode::ARKUI_DRAG_PREVIEW_SCALE_AUTO);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_DragPreviewOption_Dispose(option);
}

/**
 * @tc.name: OH_ArkUI_DragEvent_GetPreviewTouchPointX_001
 * @tc.desc: Test OH_ArkUI_DragEvent_GetPreviewTouchPointX with null event
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragEvent_GetPreviewTouchPointX_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null event pointer
     * @tc.expected: Returns 0.0f
     */
    auto result = OH_ArkUI_DragEvent_GetPreviewTouchPointX(nullptr);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

/**
 * @tc.name: OH_ArkUI_DragEvent_GetPreviewTouchPointY_001
 * @tc.desc: Test OH_ArkUI_DragEvent_GetPreviewTouchPointY with null event
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragEvent_GetPreviewTouchPointY_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null event pointer
     * @tc.expected: Returns 0.0f
     */
    auto result = OH_ArkUI_DragEvent_GetPreviewTouchPointY(nullptr);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

/**
 * @tc.name: OH_ArkUI_DragEvent_GetPreviewRectWidth_001
 * @tc.desc: Test OH_ArkUI_DragEvent_GetPreviewRectWidth with null event
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragEvent_GetPreviewRectWidth_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null event pointer
     * @tc.expected: Returns 0.0f
     */
    auto result = OH_ArkUI_DragEvent_GetPreviewRectWidth(nullptr);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

/**
 * @tc.name: OH_ArkUI_DragEvent_GetPreviewRectHeight_001
 * @tc.desc: Test OH_ArkUI_DragEvent_GetPreviewRectHeight with null event
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragEvent_GetPreviewRectHeight_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null event pointer
     * @tc.expected: Returns 0.0f
     */
    auto result = OH_ArkUI_DragEvent_GetPreviewRectHeight(nullptr);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

/**
 * @tc.name: OH_ArkUI_CancelDataLoading_001
 * @tc.desc: Test OH_ArkUI_CancelDataLoading with null uiContent
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_CancelDataLoading_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null uiContent pointer
     * @tc.expected: Returns ARKUI_ERROR_CODE_PARAM_INVALID
     */
    const char* key = "test_key";
    auto result = OH_ArkUI_CancelDataLoading(nullptr, key);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_CancelDataLoading_002
 * @tc.desc: Test OH_ArkUI_CancelDataLoading with null key
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_CancelDataLoading_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null key pointer
     * @tc.expected: Returns ARKUI_ERROR_CODE_PARAM_INVALID
     */
    auto uiContext = new ArkUI_Context({ .id = 1 });
    auto result = OH_ArkUI_CancelDataLoading(uiContext, nullptr);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_DragAndDropInfo_GetDragStatus_001
 * @tc.desc: Test OH_ArkUI_DragAndDropInfo_GetDragStatus with null info
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragAndDropInfo_GetDragStatus_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null dragAndDropInfo pointer
     * @tc.expected: Returns ARKUI_DRAG_STATUS_UNKNOWN
     */
    auto result = OH_ArkUI_DragAndDropInfo_GetDragStatus(nullptr);
    EXPECT_EQ(result, ArkUI_DragStatus::ARKUI_DRAG_STATUS_UNKNOWN);
}

/**
 * @tc.name: OH_ArkUI_DragAndDropInfo_GetDragEvent_001
 * @tc.desc: Test OH_ArkUI_DragAndDropInfo_GetDragEvent with null info
 * @tc.type: FUNC
 */
HWTEST_F(DragAndDropTestNewNg, OH_ArkUI_DragAndDropInfo_GetDragEvent_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null dragAndDropInfo pointer
     * @tc.expected: Returns nullptr
     */
    auto result = OH_ArkUI_DragAndDropInfo_GetDragEvent(nullptr);
    EXPECT_EQ(result, nullptr);
}

} // namespace OHOS::Ace
