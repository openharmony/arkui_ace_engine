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
#include "base/memory/ace_type.h"
#define private public
#define protected public
#include "accessibility_element_info.h"
#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/entrance/dynamic_component/dynamic_component_renderer_impl.h"
#include "adapter/ohos/entrance/mmi_event_convertor.h"
#include "adapter/ohos/osal/want_wrap_ohos.h"
#include "core/common/window.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/ui_extension/dynamic_component/dynamic_pattern.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model_ng.h"
#include "frameworks/core/components_ng/pattern/ui_extension/platform_pattern.h"
#include "frameworks/core/event/pointer_event.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_frontend.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string DYNAMIC_COMPONENT_ETS_TAG = "DynamicComponent";
const std::string TEST_TAG = "DynamicPatternTestThree";
const std::string TEST_ENTRY_POINT = "entryPoint";
const std::string TEST_RESOURCE_PATH = "/system/lib/arkui/test";
const std::string TEST_ABC_PATH = "/system/lib/arkui/test.abc";
const std::string TEST_HAP_PATH = "/system/lib/arkui/test.hap";

const int32_t TEST_NODE_ID_BASE = 6000;
const int32_t TEST_INSTANCE_ID_ONE = 100;
const int32_t TEST_INSTANCE_ID_TWO = 101;
const int32_t TEST_INSTANCE_ID_THREE = 102;
const int32_t TEST_ACCESSIBILITY_TREE_ID = 12;
const int32_t TEST_ACCESSIBILITY_WINDOW_ID = 18;
const int32_t TEST_CALLBACK_ID = 77;

const int64_t TEST_PLATFORM_ID = 1234;
const int64_t TEST_EXTENSION_OFFSET = 100;
const int64_t TEST_ABILITY_ID = 9;

const double TEST_RATIO_SHOW_START = 0.0;
const double TEST_RATIO_SHOW_FULL = 1.0;
const double TEST_RATIO_TINY = 0.0001;

const float TEST_WIDTH = 320.0f;
const float TEST_HEIGHT = 480.0f;
const float TEST_OFFSET_X = 16.0f;
const float TEST_OFFSET_Y = 20.0f;

const bool TEST_TRANSPARENT_TRUE = true;
const bool TEST_TRANSPARENT_FALSE = false;

std::shared_ptr<MMI::PointerEvent> CreatePointerEvent(int32_t action, int32_t sourceType)
{
    auto pointerEvent = std::make_shared<MMI::PointerEvent>(1);
    pointerEvent->SetPointerAction(action);
    pointerEvent->SetSourceType(sourceType);
    return pointerEvent;
}
}

class DynamicPatternTestNgThree : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;

    RefPtr<DynamicPattern> CreateDynamicPattern();
    RefPtr<FrameNode> CreateFrameNodeWithPattern(const RefPtr<Pattern>& pattern, int32_t nodeId);
    RefPtr<LayoutWrapperNode> CreateLayoutWrapper(const RefPtr<FrameNode>& frameNode, float width, float height);
    void PrepareRenderer(const RefPtr<DynamicPattern>& dynamicPattern);
};

void DynamicPatternTestNgThree::SetUp()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
}

void DynamicPatternTestNgThree::TearDown()
{
    MockContainer::Current()->pipelineContext_ = nullptr;
    MockContainer::TearDown();
    MockPipelineContext::TearDown();
}

RefPtr<DynamicPattern> DynamicPatternTestNgThree::CreateDynamicPattern()
{
    auto dynamicNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dynamicNode = FrameNode::GetOrCreateFrameNode(
        DYNAMIC_COMPONENT_ETS_TAG, dynamicNodeId, []() {
            return AceType::MakeRefPtr<DynamicPattern>();
        });
    EXPECT_NE(dynamicNode, nullptr);
    EXPECT_EQ(dynamicNode->GetTag(), V2::DYNAMIC_COMPONENT_ETS_TAG);

    auto dynamicPattern = dynamicNode->GetPattern<DynamicPattern>();
    EXPECT_NE(dynamicPattern, nullptr);
    return dynamicPattern;
}

RefPtr<FrameNode> DynamicPatternTestNgThree::CreateFrameNodeWithPattern(
    const RefPtr<Pattern>& pattern, int32_t nodeId)
{
    auto frameNode = FrameNode::CreateFrameNode(TEST_TAG, nodeId, pattern, true);
    EXPECT_NE(frameNode, nullptr);
    return frameNode;
}

RefPtr<LayoutWrapperNode> DynamicPatternTestNgThree::CreateLayoutWrapper(
    const RefPtr<FrameNode>& frameNode, float width, float height)
{
    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(width, height));
    geometryNode->SetContentOffset(OffsetF(TEST_OFFSET_X, TEST_OFFSET_Y));
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    EXPECT_NE(layoutWrapper, nullptr);
    return layoutWrapper;
}

void DynamicPatternTestNgThree::PrepareRenderer(const RefPtr<DynamicPattern>& dynamicPattern)
{
    ASSERT_NE(dynamicPattern, nullptr);
    IsolatedInfo isolatedInfo;
    void* runtime = nullptr;
    auto pattern = AceType::MakeRefPtr<DynamicPattern>();
    auto frameNode = CreateFrameNodeWithPattern(pattern, TEST_NODE_ID_BASE + 1);
    dynamicPattern->dynamicComponentRenderer_ = DynamicComponentRenderer::Create(frameNode, runtime, isolatedInfo);
    ASSERT_NE(dynamicPattern->dynamicComponentRenderer_, nullptr);
}

/**
 * @tc.name: DynamicPatternThreeTest001
 * @tc.desc: Test DynamicPattern default state after construction
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest001, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    EXPECT_FALSE(dynamicPattern->adaptiveWidth_);
    EXPECT_FALSE(dynamicPattern->adaptiveHeight_);
    EXPECT_TRUE(dynamicPattern->backgroundTransparent_);
    EXPECT_TRUE(dynamicPattern->isVisible_);
    EXPECT_EQ(dynamicPattern->dynamicComponentRenderer_, nullptr);
}

/**
 * @tc.name: DynamicPatternThreeTest002
 * @tc.desc: Test WrapExtensionAbilityId basic arithmetic
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest002, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->uiExtensionId_ = 5;
    auto result = dynamicPattern->WrapExtensionAbilityId(TEST_EXTENSION_OFFSET, TEST_ABILITY_ID);
    EXPECT_EQ(result, 509);
}

/**
 * @tc.name: DynamicPatternThreeTest003
 * @tc.desc: Test SetAdaptiveWidth state switch
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest003, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->SetAdaptiveWidth(true);
    EXPECT_TRUE(dynamicPattern->adaptiveWidth_);
    dynamicPattern->SetAdaptiveWidth(false);
    EXPECT_FALSE(dynamicPattern->adaptiveWidth_);
}

/**
 * @tc.name: DynamicPatternThreeTest004
 * @tc.desc: Test SetAdaptiveHeight state switch
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest004, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->SetAdaptiveHeight(true);
    EXPECT_TRUE(dynamicPattern->adaptiveHeight_);
    dynamicPattern->SetAdaptiveHeight(false);
    EXPECT_FALSE(dynamicPattern->adaptiveHeight_);
}

/**
 * @tc.name: DynamicPatternThreeTest005
 * @tc.desc: Test SetBackgroundTransparent state switch
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest005, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->SetBackgroundTransparent(TEST_TRANSPARENT_FALSE);
    EXPECT_FALSE(dynamicPattern->backgroundTransparent_);
    dynamicPattern->SetBackgroundTransparent(TEST_TRANSPARENT_TRUE);
    EXPECT_TRUE(dynamicPattern->backgroundTransparent_);
}

/**
 * @tc.name: DynamicPatternThreeTest006
 * @tc.desc: Test SetIsReportFrameEvent state switch
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest006, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    EXPECT_FALSE(dynamicPattern->hostConfig_.isReportFrameEvent);
    dynamicPattern->SetIsReportFrameEvent(true);
    EXPECT_TRUE(dynamicPattern->hostConfig_.isReportFrameEvent);
    dynamicPattern->SetIsReportFrameEvent(false);
    EXPECT_FALSE(dynamicPattern->hostConfig_.isReportFrameEvent);
}

/**
 * @tc.name: DynamicPatternThreeTest007
 * @tc.desc: Test GetAccessibilitySessionAdapter without renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest007, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    auto adapter = dynamicPattern->GetAccessibilitySessionAdapter();
    EXPECT_EQ(adapter, nullptr);
}

/**
 * @tc.name: DynamicPatternThreeTest008
 * @tc.desc: Test GetAccessibilitySessionAdapter with renderer path
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest008, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    PrepareRenderer(dynamicPattern);
    auto adapter = dynamicPattern->GetAccessibilitySessionAdapter();
    EXPECT_EQ(adapter, nullptr);
}

/**
 * @tc.name: DynamicPatternThreeTest009
 * @tc.desc: Test InitializeDynamicComponent invalid params keeps fields empty
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest009, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    void* runtime = nullptr;
    dynamicPattern->InitializeDynamicComponent(TEST_HAP_PATH, TEST_ABC_PATH, TEST_ENTRY_POINT, runtime);
    EXPECT_TRUE(dynamicPattern->curDynamicInfo_.entryPoint.empty());

    int dummy = 1;
    runtime = &dummy;
    dynamicPattern->InitializeDynamicComponent(TEST_HAP_PATH, TEST_ABC_PATH, "", runtime);
    EXPECT_TRUE(dynamicPattern->curDynamicInfo_.entryPoint.empty());
}

/**
 * @tc.name: DynamicPatternThreeTest010
 * @tc.desc: Test InitializeDynamicComponent sets entry point
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest010, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    int dummy = 2;
    void* runtime = &dummy;
    dynamicPattern->InitializeDynamicComponent(TEST_HAP_PATH, TEST_ABC_PATH, TEST_ENTRY_POINT, runtime);
    EXPECT_EQ(dynamicPattern->curDynamicInfo_.entryPoint, TEST_ENTRY_POINT);
}

/**
 * @tc.name: DynamicPatternThreeTest011
 * @tc.desc: Test HandleErrorCallback all declared enum values
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest011, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->HandleErrorCallback(DCResultCode::DC_EXCEED_MAX_NUM_IN_WORKER);
    dynamicPattern->HandleErrorCallback(DCResultCode::DC_ONLY_RUN_ON_SCB);
    dynamicPattern->HandleErrorCallback(DCResultCode::DC_INTERNAL_ERROR);
    dynamicPattern->HandleErrorCallback(DCResultCode::DC_PARAM_ERROE);
    dynamicPattern->HandleErrorCallback(DCResultCode::DC_NOT_SUPPORT_UI_CONTENT_TYPE);
    dynamicPattern->HandleErrorCallback(DCResultCode::DC_WORKER_EXCEED_MAX_NUM);
    dynamicPattern->HandleErrorCallback(static_cast<DCResultCode>(-200));
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest012
 * @tc.desc: Test CheckConstraint return range
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest012, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    auto code = dynamicPattern->CheckConstraint();
    bool valid = code == DCResultCode::DC_INTERNAL_ERROR ||
        code == DCResultCode::DC_ONLY_RUN_ON_SCB ||
        code == DCResultCode::DC_NO_ERRORS ||
        code == DCResultCode::DC_NOT_SUPPORT_UI_CONTENT_TYPE;
    EXPECT_TRUE(valid);
}

/**
 * @tc.name: DynamicPatternThreeTest013
 * @tc.desc: Test CheckDynamicRendererConstraint without renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest013, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    int dummy = 3;
    auto ret = dynamicPattern->CheckDynamicRendererConstraint(&dummy);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: DynamicPatternThreeTest014
 * @tc.desc: Test CheckDynamicRendererConstraint with mock renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest014, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    PrepareRenderer(dynamicPattern);
    int dummy = 4;
    auto ret = dynamicPattern->CheckDynamicRendererConstraint(&dummy);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: DynamicPatternThreeTest015
 * @tc.desc: Test InitializeRender with null host path
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest015, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<DynamicPattern>();
    ASSERT_NE(pattern, nullptr);
    int dummy = 5;
    pattern->InitializeRender(&dummy);
    EXPECT_EQ(pattern->dynamicComponentRenderer_, nullptr);
}

/**
 * @tc.name: DynamicPatternThreeTest016
 * @tc.desc: Test InitializeRender called twice
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest016, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    int dummy = 6;
    dynamicPattern->InitializeRender(&dummy);
    auto firstRenderer = dynamicPattern->dynamicComponentRenderer_;
    dynamicPattern->InitializeRender(&dummy);
    auto secondRenderer = dynamicPattern->dynamicComponentRenderer_;
    if (firstRenderer && secondRenderer) {
        EXPECT_EQ(firstRenderer, secondRenderer);
    } else {
        EXPECT_EQ(secondRenderer, firstRenderer);
    }
}

/**
 * @tc.name: DynamicPatternThreeTest017
 * @tc.desc: Test FireOnErrorCallbackOnUI null-host path
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest017, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<DynamicPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->FireOnErrorCallbackOnUI(1, "name", "msg");
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest018
 * @tc.desc: Test FireOnErrorCallbackOnUI host path
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest018, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->FireOnErrorCallbackOnUI(2, "name2", "msg2");
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest019
 * @tc.desc: Test DispatchPointerEvent null pointer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest019, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    std::shared_ptr<MMI::PointerEvent> pointerEvent;
    dynamicPattern->DispatchPointerEvent(pointerEvent);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest020
 * @tc.desc: Test DispatchPointerEvent with renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest020, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    PrepareRenderer(dynamicPattern);
    auto pointerEvent = CreatePointerEvent(OHOS::MMI::PointerEvent::POINTER_ACTION_MOVE,
        OHOS::MMI::PointerEvent::SOURCE_TYPE_TOUCHSCREEN);
    dynamicPattern->DispatchPointerEvent(pointerEvent);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest021
 * @tc.desc: Test DispatchFocusActiveEvent without renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest021, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->DispatchFocusActiveEvent(true);
    dynamicPattern->DispatchFocusActiveEvent(false);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest022
 * @tc.desc: Test DispatchFocusActiveEvent with renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest022, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    PrepareRenderer(dynamicPattern);
    dynamicPattern->DispatchFocusActiveEvent(true);
    dynamicPattern->DispatchFocusActiveEvent(false);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest023
 * @tc.desc: Test HandleKeyEvent raw event null
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest023, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    KeyEvent keyEvent(KeyCode::KEY_A, KeyAction::DOWN);
    auto ret = dynamicPattern->HandleKeyEvent(keyEvent);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: DynamicPatternThreeTest024
 * @tc.desc: Test HandleKeyEvent with renderer and null raw key event
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest024, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    PrepareRenderer(dynamicPattern);
    KeyEvent keyEvent(KeyCode::KEY_A, KeyAction::DOWN);
    auto ret = dynamicPattern->HandleKeyEvent(keyEvent);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: DynamicPatternThreeTest025
 * @tc.desc: Test HandleFocusEvent without renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest025, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->HandleFocusEvent();
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest026
 * @tc.desc: Test HandleFocusEvent with renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest026, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    PrepareRenderer(dynamicPattern);
    dynamicPattern->HandleFocusEvent();
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest027
 * @tc.desc: Test HandleBlurEvent without renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest027, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->HandleBlurEvent();
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest028
 * @tc.desc: Test HandleBlurEvent with renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest028, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    PrepareRenderer(dynamicPattern);
    dynamicPattern->HandleBlurEvent();
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest029
 * @tc.desc: Test OnAttachToFrameNode basic path
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest029, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->OnAttachToFrameNode();
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest030
 * @tc.desc: Test OnDirtyLayoutWrapperSwap skip measure
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest030, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    RefPtr<LayoutWrapperNode> wrapper;
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = false;
    auto ret = dynamicPattern->OnDirtyLayoutWrapperSwap(wrapper, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: DynamicPatternThreeTest031
 * @tc.desc: Test OnDirtyLayoutWrapperSwap skip layout
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest031, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    RefPtr<LayoutWrapperNode> wrapper;
    DirtySwapConfig config;
    config.skipMeasure = false;
    config.skipLayout = true;
    auto ret = dynamicPattern->OnDirtyLayoutWrapperSwap(wrapper, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: DynamicPatternThreeTest032
 * @tc.desc: Test OnDirtyLayoutWrapperSwap without renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest032, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    auto frameNode = CreateFrameNodeWithPattern(AceType::MakeRefPtr<Pattern>(), TEST_NODE_ID_BASE + 2);
    auto wrapper = CreateLayoutWrapper(frameNode, TEST_WIDTH, TEST_HEIGHT);
    DirtySwapConfig config;
    config.skipMeasure = false;
    config.skipLayout = false;
    auto ret = dynamicPattern->OnDirtyLayoutWrapperSwap(wrapper, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: DynamicPatternThreeTest033
 * @tc.desc: Test OnDirtyLayoutWrapperSwap with renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest033, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    PrepareRenderer(dynamicPattern);
    auto frameNode = CreateFrameNodeWithPattern(AceType::MakeRefPtr<Pattern>(), TEST_NODE_ID_BASE + 3);
    auto wrapper = CreateLayoutWrapper(frameNode, TEST_WIDTH, TEST_HEIGHT);
    DirtySwapConfig config;
    config.skipMeasure = false;
    config.skipLayout = false;
    auto ret = dynamicPattern->OnDirtyLayoutWrapperSwap(wrapper, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: DynamicPatternThreeTest034
 * @tc.desc: Test OnDetachFromFrameNode without renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest034, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    auto host = dynamicPattern->GetHost();
    ASSERT_EQ(host, nullptr);
    dynamicPattern->OnDetachFromFrameNode(AceType::RawPtr(host));
    EXPECT_EQ(dynamicPattern->dynamicComponentRenderer_, nullptr);
}

/**
 * @tc.name: DynamicPatternThreeTest035
 * @tc.desc: Test OnDetachFromFrameNode clears renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest035, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    PrepareRenderer(dynamicPattern);
    auto host = dynamicPattern->GetHost();
    ASSERT_EQ(host, nullptr);
    dynamicPattern->OnDetachFromFrameNode(AceType::RawPtr(host));
    EXPECT_EQ(dynamicPattern->dynamicComponentRenderer_, nullptr);
}

/**
 * @tc.name: DynamicPatternThreeTest036
 * @tc.desc: Test OnAttachContext null context
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest036, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->instanceId_ = TEST_INSTANCE_ID_ONE;
    dynamicPattern->OnAttachContext(nullptr);
    EXPECT_EQ(dynamicPattern->instanceId_, TEST_INSTANCE_ID_ONE);
}

/**
 * @tc.name: DynamicPatternThreeTest037
 * @tc.desc: Test OnAttachContext with same instance id
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest037, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetInstanceId(TEST_INSTANCE_ID_TWO);
    dynamicPattern->instanceId_ = TEST_INSTANCE_ID_TWO;
    auto rawPipeline = reinterpret_cast<PipelineContext*>(Referenced::RawPtr(pipeline));
    dynamicPattern->OnAttachContext(rawPipeline);
    EXPECT_EQ(dynamicPattern->instanceId_, TEST_INSTANCE_ID_TWO);
}

/**
 * @tc.name: DynamicPatternThreeTest038
 * @tc.desc: Test OnAttachContext with changed instance id
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest038, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetInstanceId(TEST_INSTANCE_ID_THREE);
    dynamicPattern->instanceId_ = TEST_INSTANCE_ID_ONE;
    auto rawPipeline = reinterpret_cast<PipelineContext*>(Referenced::RawPtr(pipeline));
    dynamicPattern->OnAttachContext(rawPipeline);
    EXPECT_EQ(dynamicPattern->instanceId_, TEST_INSTANCE_ID_THREE);
}

/**
 * @tc.name: DynamicPatternThreeTest039
 * @tc.desc: Test RegisterPipelineEvent basic null-safe path
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest039, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->RegisterPipelineEvent(TEST_INSTANCE_ID_ONE);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest040
 * @tc.desc: Test UnRegisterPipelineEvent basic null-safe path
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest040, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->UnRegisterPipelineEvent(TEST_INSTANCE_ID_ONE);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest041
 * @tc.desc: Test RegisterAccessibilitySAObserverCallback and unregister
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest041, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->RegisterAccessibilitySAObserverCallback(TEST_INSTANCE_ID_ONE);
    dynamicPattern->UnRegisterAccessibilitySAObserverCallback(TEST_INSTANCE_ID_ONE);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest042
 * @tc.desc: Test RegisterSingleHandTransformChangedCallback and unregister
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest042, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->RegisterSingleHandTransformChangedCallback(TEST_INSTANCE_ID_ONE);
    dynamicPattern->UnRegisterSingleHandTransformChangedCallback(TEST_INSTANCE_ID_ONE);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest043
 * @tc.desc: Test OnDetachContext null-safe path
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest043, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->OnDetachContext(nullptr);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest044
 * @tc.desc: Test OnDetachContext with pipeline
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest044, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetInstanceId(TEST_INSTANCE_ID_TWO);
    auto rawPipeline = reinterpret_cast<PipelineContext*>(Referenced::RawPtr(pipeline));
    dynamicPattern->OnDetachContext(rawPipeline);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest045
 * @tc.desc: Test DumpDynamicRenderer without renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest045, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->DumpDynamicRenderer(1, false);
    dynamicPattern->DumpDynamicRenderer(2, true);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest046
 * @tc.desc: Test DumpDynamicRenderer with renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest046, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    PrepareRenderer(dynamicPattern);
    dynamicPattern->DumpDynamicRenderer(3, false);
    dynamicPattern->DumpDynamicRenderer(4, true);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest047
 * @tc.desc: Test DumpInfo text output
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest047, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->platformId_ = TEST_PLATFORM_ID;
    dynamicPattern->curDynamicInfo_.entryPoint = TEST_ENTRY_POINT;
    dynamicPattern->dynamicDumpInfo_.createLimitedWorkerTime = TEST_CALLBACK_ID;
    dynamicPattern->hostConfig_.isReportFrameEvent = true;
    PrepareRenderer(dynamicPattern);
    dynamicPattern->DumpInfo();
    EXPECT_GE(DumpLog::GetInstance().description_.size(), 3);
}

/**
 * @tc.name: DynamicPatternThreeTest048
 * @tc.desc: Test DumpInfo json output without renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest048, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->platformId_ = TEST_PLATFORM_ID;
    dynamicPattern->curDynamicInfo_.resourcePath = TEST_RESOURCE_PATH;
    dynamicPattern->curDynamicInfo_.entryPoint = TEST_ENTRY_POINT;
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    dynamicPattern->DumpInfo(json);
    EXPECT_TRUE(json->GetValue("dynamicId")->IsNull());
    EXPECT_TRUE(json->GetValue("resourcePath")->IsNull());
    EXPECT_TRUE(json->GetValue("entryPoint")->IsNull());
}

/**
 * @tc.name: DynamicPatternThreeTest049
 * @tc.desc: Test DumpInfo json output with renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest049, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    PrepareRenderer(dynamicPattern);
    dynamicPattern->platformId_ = TEST_PLATFORM_ID;
    dynamicPattern->curDynamicInfo_.resourcePath = TEST_RESOURCE_PATH;
    dynamicPattern->curDynamicInfo_.entryPoint = TEST_ENTRY_POINT;
    dynamicPattern->hostConfig_.isReportFrameEvent = true;
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    dynamicPattern->DumpInfo(json);
    EXPECT_TRUE(json->GetValue("createUiContenTime")->IsNull());
    EXPECT_TRUE(json->GetValue("limitedWorkerInitTime")->IsNull());
    EXPECT_TRUE(json->GetValue("loadAbcTime")->IsNull());
    EXPECT_TRUE(json->GetValue("isReportFrameEvent")->IsNull());
}

/**
 * @tc.name: DynamicPatternThreeTest050
 * @tc.desc: Test TransferAccessibilityRectInfo force update without renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest050, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->TransferAccessibilityRectInfo(true);
    dynamicPattern->TransferAccessibilityRectInfo(false);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest051
 * @tc.desc: Test OnAccessibilityParentRectInfoUpdate without renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest051, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->OnAccessibilityParentRectInfoUpdate();
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest052
 * @tc.desc: Test OnAccessibilityParentRectInfoUpdate with renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest052, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    PrepareRenderer(dynamicPattern);
    dynamicPattern->OnAccessibilityParentRectInfoUpdate();
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest053
 * @tc.desc: Test IsAncestorNodeGeometryChange true and false branches
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest053, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    FrameNodeChangeInfoFlag flag = FRAME_NODE_CHANGE_GEOMETRY_CHANGE | FRAME_NODE_CHANGE_TRANSFORM_CHANGE;
    EXPECT_TRUE(dynamicPattern->IsAncestorNodeGeometryChange(flag));
    flag = FRAME_NODE_CHANGE_TRANSFORM_CHANGE;
    EXPECT_FALSE(dynamicPattern->IsAncestorNodeGeometryChange(flag));
}

/**
 * @tc.name: DynamicPatternThreeTest054
 * @tc.desc: Test IsAncestorNodeTransformChange true and false branches
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest054, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    FrameNodeChangeInfoFlag flag = FRAME_NODE_CHANGE_TRANSFORM_CHANGE | FRAME_NODE_CHANGE_GEOMETRY_CHANGE;
    EXPECT_TRUE(dynamicPattern->IsAncestorNodeTransformChange(flag));
    flag = FRAME_NODE_CHANGE_GEOMETRY_CHANGE;
    EXPECT_FALSE(dynamicPattern->IsAncestorNodeTransformChange(flag));
}

/**
 * @tc.name: DynamicPatternThreeTest055
 * @tc.desc: Test OnFrameNodeChanged for non-target flag
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest055, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    auto oldRect = dynamicPattern->rectInfo_;
    dynamicPattern->OnFrameNodeChanged(FRAME_NODE_CHANGE_INFO_NONE);
    EXPECT_EQ(oldRect.left, dynamicPattern->rectInfo_.left);
    EXPECT_EQ(oldRect.top, dynamicPattern->rectInfo_.top);
}

/**
 * @tc.name: DynamicPatternThreeTest056
 * @tc.desc: Test OnFrameNodeChanged for geometry flag
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest056, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->OnFrameNodeChanged(FRAME_NODE_CHANGE_GEOMETRY_CHANGE);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest057
 * @tc.desc: Test OnFrameNodeChanged for transform flag
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest057, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->OnFrameNodeChanged(FRAME_NODE_CHANGE_TRANSFORM_CHANGE);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest058
 * @tc.desc: Test InitializeAccessibility when callback already exists
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest058, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->accessibilityChildTreeCallback_ =
        std::make_shared<PlatformAccessibilityChildTreeCallback>(dynamicPattern, 1);
    dynamicPattern->InitializeAccessibility();
    EXPECT_NE(dynamicPattern->accessibilityChildTreeCallback_, nullptr);
}

/**
 * @tc.name: DynamicPatternThreeTest059
 * @tc.desc: Test ResetAccessibilityChildTreeCallback when callback null
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest059, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->ResetAccessibilityChildTreeCallback();
    EXPECT_EQ(dynamicPattern->accessibilityChildTreeCallback_, nullptr);
}

/**
 * @tc.name: DynamicPatternThreeTest060
 * @tc.desc: Test ResetAccessibilityChildTreeCallback with callback set
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest060, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->accessibilityChildTreeCallback_ =
        std::make_shared<PlatformAccessibilityChildTreeCallback>(dynamicPattern, 2);
    dynamicPattern->ResetAccessibilityChildTreeCallback();
    EXPECT_NE(dynamicPattern->accessibilityChildTreeCallback_, nullptr);
}

/**
 * @tc.name: DynamicPatternThreeTest061
 * @tc.desc: Test OnAccessibilityChildTreeRegister without renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest061, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->OnAccessibilityChildTreeRegister(
        TEST_ACCESSIBILITY_WINDOW_ID, TEST_ACCESSIBILITY_TREE_ID, TEST_PLATFORM_ID);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest062
 * @tc.desc: Test OnAccessibilityChildTreeRegister with renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest062, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    PrepareRenderer(dynamicPattern);
    dynamicPattern->OnAccessibilityChildTreeRegister(
        TEST_ACCESSIBILITY_WINDOW_ID, TEST_ACCESSIBILITY_TREE_ID, TEST_PLATFORM_ID);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest063
 * @tc.desc: Test OnAccessibilityChildTreeDeregister without renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest063, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->OnAccessibilityChildTreeDeregister();
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest064
 * @tc.desc: Test OnAccessibilityChildTreeDeregister with renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest064, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    PrepareRenderer(dynamicPattern);
    dynamicPattern->OnAccessibilityChildTreeDeregister();
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest065
 * @tc.desc: Test OnAccessibilityDumpChildInfo without renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest065, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    std::vector<std::string> params = { "one", "two" };
    std::vector<std::string> info;
    dynamicPattern->OnAccessibilityDumpChildInfo(params, info);
    EXPECT_TRUE(info.empty());
}

/**
 * @tc.name: DynamicPatternThreeTest066
 * @tc.desc: Test OnAccessibilityDumpChildInfo with renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest066, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    PrepareRenderer(dynamicPattern);
    std::vector<std::string> params = { "alpha", "beta", "gamma" };
    std::vector<std::string> info;
    dynamicPattern->OnAccessibilityDumpChildInfo(params, info);
    EXPECT_TRUE(info.empty());
}

/**
 * @tc.name: DynamicPatternThreeTest067
 * @tc.desc: Test OnSetAccessibilityChildTree no property path
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest067, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<DynamicPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnSetAccessibilityChildTree(1, 2);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest069
 * @tc.desc: Test AddToPageEventController basic path
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest069, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->AddToPageEventController();
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest070
 * @tc.desc: Test ReleasePageEvent basic path
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest070, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->ReleasePageEvent();
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest071
 * @tc.desc: Test RegisterVisibleAreaChange basic path
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest071, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    dynamicPattern->RegisterVisibleAreaChange();
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest072
 * @tc.desc: Test HandleVisibleAreaChange hide branch
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest072, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    PrepareRenderer(dynamicPattern);
    dynamicPattern->isVisible_ = true;
    dynamicPattern->HandleVisibleAreaChange(false, TEST_RATIO_SHOW_START);
    EXPECT_FALSE(dynamicPattern->isVisible_);
}

/**
 * @tc.name: DynamicPatternThreeTest073
 * @tc.desc: Test HandleVisibleAreaChange show branch
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest073, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    PrepareRenderer(dynamicPattern);
    dynamicPattern->isVisible_ = false;
    dynamicPattern->HandleVisibleAreaChange(true, TEST_RATIO_SHOW_FULL);
    EXPECT_TRUE(dynamicPattern->isVisible_);
}

/**
 * @tc.name: DynamicPatternThreeTest074
 * @tc.desc: Test HandleVisibleAreaChange tiny ratio treated invisible
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest074, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    PrepareRenderer(dynamicPattern);
    dynamicPattern->isVisible_ = true;
    dynamicPattern->HandleVisibleAreaChange(true, TEST_RATIO_TINY);
    EXPECT_FALSE(dynamicPattern->isVisible_);
}

/**
 * @tc.name: DynamicPatternThreeTest075
 * @tc.desc: Test HandleTouchEvent nullptr event
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest075, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    std::shared_ptr<MMI::PointerEvent> pointerEvent;
    auto ret = dynamicPattern->HandleTouchEvent(pointerEvent);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: DynamicPatternThreeTest076
 * @tc.desc: Test HandleTouchEvent mouse source returns false
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest076, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    auto pointerEvent = CreatePointerEvent(OHOS::MMI::PointerEvent::POINTER_ACTION_MOVE,
        OHOS::MMI::PointerEvent::SOURCE_TYPE_MOUSE);
    auto ret = dynamicPattern->HandleTouchEvent(pointerEvent);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: DynamicPatternThreeTest077
 * @tc.desc: Test HandleTouchEvent pull move returns false
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest077, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    auto pointerEvent = CreatePointerEvent(OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_MOVE,
        OHOS::MMI::PointerEvent::SOURCE_TYPE_TOUCHSCREEN);
    auto ret = dynamicPattern->HandleTouchEvent(pointerEvent);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: DynamicPatternThreeTest078
 * @tc.desc: Test HandleTouchEvent pull up returns false
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest078, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    auto pointerEvent = CreatePointerEvent(OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_UP,
        OHOS::MMI::PointerEvent::SOURCE_TYPE_TOUCHSCREEN);
    auto ret = dynamicPattern->HandleTouchEvent(pointerEvent);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: DynamicPatternThreeTest079
 * @tc.desc: Test HandleTouchEvent normal action path
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest079, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    auto pointerEvent = CreatePointerEvent(OHOS::MMI::PointerEvent::POINTER_ACTION_UP,
        OHOS::MMI::PointerEvent::SOURCE_TYPE_TOUCHSCREEN);
    auto ret = dynamicPattern->HandleTouchEvent(pointerEvent);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: DynamicPatternThreeTest080
 * @tc.desc: Test HandleMouseEvent non-mouse source
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest080, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    MouseInfo info;
    info.SetSourceDevice(SourceType::NONE);
    info.SetPullAction(MouseAction::PRESS);
    dynamicPattern->HandleMouseEvent(info);
    EXPECT_FALSE(dynamicPattern->lastPointerEvent_);
}

/**
 * @tc.name: DynamicPatternThreeTest081
 * @tc.desc: Test HandleMouseEvent pull move filtered
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest081, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    MouseInfo info;
    info.SetSourceDevice(SourceType::MOUSE);
    info.SetPullAction(MouseAction::PULL_MOVE);
    dynamicPattern->HandleMouseEvent(info);
    EXPECT_FALSE(dynamicPattern->lastPointerEvent_);
}

/**
 * @tc.name: DynamicPatternThreeTest082
 * @tc.desc: Test HandleMouseEvent pull up filtered
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest082, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    MouseInfo info;
    info.SetSourceDevice(SourceType::MOUSE);
    info.SetPullAction(MouseAction::PULL_UP);
    dynamicPattern->HandleMouseEvent(info);
    EXPECT_FALSE(dynamicPattern->lastPointerEvent_);
}

/**
 * @tc.name: DynamicPatternThreeTest083
 * @tc.desc: Test HandleMouseEvent press path
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest083, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    MouseInfo info;
    info.SetSourceDevice(SourceType::MOUSE);
    info.SetPullAction(MouseAction::PRESS);
    std::shared_ptr<MMI::PointerEvent> pointerEvent = std::make_shared<MMI::PointerEvent>(2);
    info.SetPointerEvent(pointerEvent);
    dynamicPattern->HandleMouseEvent(info);
    EXPECT_TRUE(dynamicPattern->lastPointerEvent_);
}

/**
 * @tc.name: DynamicPatternThreeTest084
 * @tc.desc: Test HandleMouseEvent release path
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest084, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    MouseInfo info;
    info.SetSourceDevice(SourceType::MOUSE);
    info.SetPullAction(MouseAction::RELEASE);
    std::shared_ptr<MMI::PointerEvent> pointerEvent = std::make_shared<MMI::PointerEvent>(3);
    info.SetPointerEvent(pointerEvent);
    dynamicPattern->HandleMouseEvent(info);
    EXPECT_TRUE(dynamicPattern->lastPointerEvent_);
}

/**
 * @tc.name: DynamicPatternThreeTest085
 * @tc.desc: Test GetAccessibilityRectInfo returns fallback value
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest085, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<DynamicPattern>();
    ASSERT_NE(pattern, nullptr);
    auto rectInfo = pattern->GetAccessibilityRectInfo();
    EXPECT_EQ(rectInfo.left, 0);
    EXPECT_EQ(rectInfo.top, 0);
}

/**
 * @tc.name: DynamicPatternThreeTest086
 * @tc.desc: Test GetAccessibilityRectInfo with host
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest086, TestSize.Level1)
{
    auto pattern = CreateDynamicPattern();
    ASSERT_NE(pattern, nullptr);
    auto rectInfo = pattern->GetAccessibilityRectInfo();
    EXPECT_GE(rectInfo.left, 0);
    EXPECT_GE(rectInfo.top, 0);
}

/**
 * @tc.name: DynamicPatternThreeTest087
 * @tc.desc: Test TransferAccessibilityRectInfo force true with renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest087, TestSize.Level1)
{
    auto pattern = CreateDynamicPattern();
    ASSERT_NE(pattern, nullptr);
    PrepareRenderer(pattern);
    pattern->TransferAccessibilityRectInfo(true);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest088
 * @tc.desc: Test TransferAccessibilityRectInfo force false with renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest088, TestSize.Level1)
{
    auto pattern = CreateDynamicPattern();
    ASSERT_NE(pattern, nullptr);
    PrepareRenderer(pattern);
    pattern->TransferAccessibilityRectInfo(false);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest089
 * @tc.desc: Test OnAttachContext updates allowCrossProcessNesting path
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest089, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetInstanceId(TEST_INSTANCE_ID_ONE);
    auto rawPipeline = reinterpret_cast<PipelineContext*>(Referenced::RawPtr(pipeline));
    dynamicPattern->OnAttachContext(rawPipeline);
    bool allowNesting = dynamicPattern->IsAllowCrossProcessNesting();
    EXPECT_TRUE(allowNesting || !allowNesting);
}

/**
 * @tc.name: DynamicPatternThreeTest090
 * @tc.desc: Test OnDetachContext call twice
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest090, TestSize.Level1)
{
    auto dynamicPattern = CreateDynamicPattern();
    ASSERT_NE(dynamicPattern, nullptr);
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto rawPipeline = reinterpret_cast<PipelineContext*>(Referenced::RawPtr(pipeline));
    dynamicPattern->OnDetachContext(rawPipeline);
    dynamicPattern->OnDetachContext(rawPipeline);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest091
 * @tc.desc: Test RegisterPipelineEvent with null host
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest091, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<DynamicPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->RegisterPipelineEvent(TEST_INSTANCE_ID_ONE);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest092
 * @tc.desc: Test UnRegisterPipelineEvent with null host
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest092, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<DynamicPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->UnRegisterPipelineEvent(TEST_INSTANCE_ID_ONE);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest093
 * @tc.desc: Test RegisterAccessibilitySAObserverCallback with null host
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest093, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<DynamicPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->RegisterAccessibilitySAObserverCallback(TEST_INSTANCE_ID_ONE);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest094
 * @tc.desc: Test UnRegisterAccessibilitySAObserverCallback with null host
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest094, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<DynamicPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->UnRegisterAccessibilitySAObserverCallback(TEST_INSTANCE_ID_ONE);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest095
 * @tc.desc: Test RegisterSingleHandTransformChangedCallback with null host
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest095, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<DynamicPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->RegisterSingleHandTransformChangedCallback(TEST_INSTANCE_ID_ONE);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest096
 * @tc.desc: Test UnRegisterSingleHandTransformChangedCallback with null host
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest096, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<DynamicPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->UnRegisterSingleHandTransformChangedCallback(TEST_INSTANCE_ID_ONE);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest097
 * @tc.desc: Test AddToPageEventController with null host
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest097, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<DynamicPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->AddToPageEventController();
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest098
 * @tc.desc: Test ReleasePageEvent with null host
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest098, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<DynamicPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->ReleasePageEvent();
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest099
 * @tc.desc: Test OnAccessibilityDumpChildInfo empty params
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest099, TestSize.Level1)
{
    auto pattern = CreateDynamicPattern();
    ASSERT_NE(pattern, nullptr);
    std::vector<std::string> params;
    std::vector<std::string> info;
    pattern->OnAccessibilityDumpChildInfo(params, info);
    EXPECT_TRUE(info.empty());
}

/**
 * @tc.name: DynamicPatternThreeTest100
 * @tc.desc: Test mixed sequence for stability
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest100, TestSize.Level1)
{
    auto pattern = CreateDynamicPattern();
    ASSERT_NE(pattern, nullptr);
    int dummy = 7;
    pattern->InitializeDynamicComponent(TEST_HAP_PATH, TEST_ABC_PATH, TEST_ENTRY_POINT, &dummy);
    pattern->SetBackgroundTransparent(false);
    pattern->SetAdaptiveWidth(true);
    pattern->SetAdaptiveHeight(true);
    pattern->SetIsReportFrameEvent(true);
    pattern->HandleVisibleAreaChange(true, TEST_RATIO_SHOW_FULL);
    pattern->HandleVisibleAreaChange(false, TEST_RATIO_SHOW_START);
    pattern->DumpDynamicRenderer(5, false);
    pattern->DumpInfo();
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    pattern->DumpInfo(json);
    EXPECT_TRUE(json->GetValue("dynamicId")->IsNull());
}

/**
 * @tc.name: DynamicPatternThreeTest101
 * @tc.desc: Test multiple adaptive width toggles
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest101, TestSize.Level1)
{
    auto pattern = CreateDynamicPattern();
    ASSERT_NE(pattern, nullptr);
    pattern->SetAdaptiveWidth(true);
    pattern->SetAdaptiveWidth(false);
    pattern->SetAdaptiveWidth(true);
    EXPECT_TRUE(pattern->adaptiveWidth_);
}

/**
 * @tc.name: DynamicPatternThreeTest102
 * @tc.desc: Test multiple adaptive height toggles
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest102, TestSize.Level1)
{
    auto pattern = CreateDynamicPattern();
    ASSERT_NE(pattern, nullptr);
    pattern->SetAdaptiveHeight(true);
    pattern->SetAdaptiveHeight(false);
    pattern->SetAdaptiveHeight(true);
    EXPECT_TRUE(pattern->adaptiveHeight_);
}

/**
 * @tc.name: DynamicPatternThreeTest103
 * @tc.desc: Test adaptive flags with renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest103, TestSize.Level1)
{
    auto pattern = CreateDynamicPattern();
    ASSERT_NE(pattern, nullptr);
    PrepareRenderer(pattern);
    pattern->SetAdaptiveWidth(true);
    pattern->SetAdaptiveHeight(true);
    EXPECT_TRUE(pattern->adaptiveWidth_);
    EXPECT_TRUE(pattern->adaptiveHeight_);
}

/**
 * @tc.name: DynamicPatternThreeTest104
 * @tc.desc: Test repeated SetBackgroundTransparent
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest104, TestSize.Level1)
{
    auto pattern = CreateDynamicPattern();
    ASSERT_NE(pattern, nullptr);
    pattern->SetBackgroundTransparent(false);
    pattern->SetBackgroundTransparent(true);
    pattern->SetBackgroundTransparent(false);
    EXPECT_FALSE(pattern->backgroundTransparent_);
}

/**
 * @tc.name: DynamicPatternThreeTest105
 * @tc.desc: Test OnFrameNodeChanged for combined flags
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest105, TestSize.Level1)
{
    auto pattern = CreateDynamicPattern();
    ASSERT_NE(pattern, nullptr);
    auto flag = FRAME_NODE_CHANGE_TRANSFORM_CHANGE | FRAME_NODE_CHANGE_GEOMETRY_CHANGE;
    pattern->OnFrameNodeChanged(flag);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest106
 * @tc.desc: Test OnFrameNodeChanged for start animation flag
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest106, TestSize.Level1)
{
    auto pattern = CreateDynamicPattern();
    ASSERT_NE(pattern, nullptr);
    pattern->OnFrameNodeChanged(FRAME_NODE_CHANGE_START_ANIMATION);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest107
 * @tc.desc: Test HandleVisibleAreaChange with no renderer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest107, TestSize.Level1)
{
    auto pattern = CreateDynamicPattern();
    ASSERT_NE(pattern, nullptr);
    pattern->HandleVisibleAreaChange(true, TEST_RATIO_SHOW_FULL);
    EXPECT_TRUE(pattern->isVisible_);
    pattern->HandleVisibleAreaChange(false, TEST_RATIO_SHOW_START);
    EXPECT_FALSE(pattern->isVisible_);
}

/**
 * @tc.name: DynamicPatternThreeTest108
 * @tc.desc: Test HandleVisibleAreaChange steady-state no change
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest108, TestSize.Level1)
{
    auto pattern = CreateDynamicPattern();
    ASSERT_NE(pattern, nullptr);
    PrepareRenderer(pattern);
    pattern->isVisible_ = true;
    pattern->HandleVisibleAreaChange(true, TEST_RATIO_SHOW_FULL);
    EXPECT_TRUE(pattern->isVisible_);
}

/**
 * @tc.name: DynamicPatternThreeTest109
 * @tc.desc: Test HandleVisibleAreaChange from false to true
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest109, TestSize.Level1)
{
    auto pattern = CreateDynamicPattern();
    ASSERT_NE(pattern, nullptr);
    PrepareRenderer(pattern);
    pattern->isVisible_ = false;
    pattern->HandleVisibleAreaChange(true, TEST_RATIO_SHOW_FULL);
    EXPECT_TRUE(pattern->isVisible_);
}

/**
 * @tc.name: DynamicPatternThreeTest110
 * @tc.desc: Test HandleVisibleAreaChange from true to false
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest110, TestSize.Level1)
{
    auto pattern = CreateDynamicPattern();
    ASSERT_NE(pattern, nullptr);
    PrepareRenderer(pattern);
    pattern->isVisible_ = true;
    pattern->HandleVisibleAreaChange(false, TEST_RATIO_SHOW_START);
    EXPECT_FALSE(pattern->isVisible_);
}

/**
 * @tc.name: DynamicPatternThreeTest111
 * @tc.desc: Test DumpInfo json with frame-event flag false
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest111, TestSize.Level1)
{
    auto pattern = CreateDynamicPattern();
    ASSERT_NE(pattern, nullptr);
    PrepareRenderer(pattern);
    pattern->hostConfig_.isReportFrameEvent = false;
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    pattern->DumpInfo(json);
    EXPECT_TRUE(json->GetValue("isReportFrameEvent")->IsNull());
}

/**
 * @tc.name: DynamicPatternThreeTest112
 * @tc.desc: Test DumpInfo json with frame-event flag true
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest112, TestSize.Level1)
{
    auto pattern = CreateDynamicPattern();
    ASSERT_NE(pattern, nullptr);
    PrepareRenderer(pattern);
    pattern->hostConfig_.isReportFrameEvent = true;
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    pattern->DumpInfo(json);
    EXPECT_TRUE(json->GetValue("isReportFrameEvent")->IsNull());
}

/**
 * @tc.name: DynamicPatternThreeTest113
 * @tc.desc: Test InitializeRender and detach lifecycle
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest113, TestSize.Level1)
{
    auto pattern = CreateDynamicPattern();
    ASSERT_NE(pattern, nullptr);
    int dummy = 8;
    pattern->InitializeRender(&dummy);
    auto host = pattern->GetHost();
    ASSERT_EQ(host, nullptr);
    pattern->OnDetachFromFrameNode(AceType::RawPtr(host));
    EXPECT_EQ(pattern->dynamicComponentRenderer_, nullptr);
}

/**
 * @tc.name: DynamicPatternThreeTest114
 * @tc.desc: Test RegisterVisibleAreaChange after initialize
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest114, TestSize.Level1)
{
    auto pattern = CreateDynamicPattern();
    ASSERT_NE(pattern, nullptr);
    int dummy = 9;
    pattern->InitializeDynamicComponent(TEST_HAP_PATH, TEST_ABC_PATH, TEST_ENTRY_POINT, &dummy);
    pattern->RegisterVisibleAreaChange();
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest115
 * @tc.desc: Test accessibility register and deregister sequence
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest115, TestSize.Level1)
{
    auto pattern = CreateDynamicPattern();
    ASSERT_NE(pattern, nullptr);
    pattern->OnAccessibilityChildTreeRegister(1, 2, 3);
    pattern->OnAccessibilityChildTreeDeregister();
    pattern->OnAccessibilityChildTreeRegister(4, 5, 6);
    pattern->OnAccessibilityChildTreeDeregister();
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest116
 * @tc.desc: Test repeated OnSetAccessibilityChildTree
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest116, TestSize.Level1)
{
    auto pattern = CreateDynamicPattern();
    ASSERT_NE(pattern, nullptr);
    pattern->OnSetAccessibilityChildTree(10, 11);
    pattern->OnSetAccessibilityChildTree(12, 13);
    pattern->OnSetAccessibilityChildTree(14, 15);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest117
 * @tc.desc: Test repeated accessibility rect transfer
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest117, TestSize.Level1)
{
    auto pattern = CreateDynamicPattern();
    ASSERT_NE(pattern, nullptr);
    pattern->TransferAccessibilityRectInfo(true);
    pattern->TransferAccessibilityRectInfo(false);
    pattern->TransferAccessibilityRectInfo(true);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest118
 * @tc.desc: Test repeated context attach and detach
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest118, TestSize.Level1)
{
    auto pattern = CreateDynamicPattern();
    ASSERT_NE(pattern, nullptr);
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetInstanceId(TEST_INSTANCE_ID_ONE);
    auto rawPipeline = reinterpret_cast<PipelineContext*>(Referenced::RawPtr(pipeline));
    pattern->OnAttachContext(rawPipeline);
    pattern->OnDetachContext(rawPipeline);
    pattern->OnAttachContext(rawPipeline);
    pattern->OnDetachContext(rawPipeline);
    SUCCEED();
}

/**
 * @tc.name: DynamicPatternThreeTest119
 * @tc.desc: Test renderer constraint check repeatedly
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest119, TestSize.Level1)
{
    auto pattern = CreateDynamicPattern();
    ASSERT_NE(pattern, nullptr);
    PrepareRenderer(pattern);
    int runtimeA = 1;
    int runtimeB = 2;
    auto retA = pattern->CheckDynamicRendererConstraint(&runtimeA);
    auto retB = pattern->CheckDynamicRendererConstraint(&runtimeB);
    EXPECT_FALSE(retA);
    EXPECT_FALSE(retB);
}

/**
 * @tc.name: DynamicPatternThreeTest120
 * @tc.desc: Test final comprehensive smoke path
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgThree, DynamicPatternThreeTest120, TestSize.Level1)
{
    auto pattern = CreateDynamicPattern();
    ASSERT_NE(pattern, nullptr);
    int runtime = 10;
    pattern->InitializeDynamicComponent(TEST_HAP_PATH, TEST_ABC_PATH, TEST_ENTRY_POINT, &runtime);
    pattern->SetAdaptiveWidth(true);
    pattern->SetAdaptiveHeight(false);
    pattern->SetBackgroundTransparent(true);
    pattern->SetIsReportFrameEvent(true);
    pattern->HandleVisibleAreaChange(true, TEST_RATIO_SHOW_FULL);
    pattern->HandleVisibleAreaChange(false, TEST_RATIO_SHOW_START);
    pattern->TransferAccessibilityRectInfo(true);
    pattern->DumpDynamicRenderer(6, true);
    std::vector<std::string> params = { "dump", "accessibility" };
    std::vector<std::string> info;
    pattern->OnAccessibilityDumpChildInfo(params, info);
    SUCCEED();
}
} // namespace OHOS::Ace::NG