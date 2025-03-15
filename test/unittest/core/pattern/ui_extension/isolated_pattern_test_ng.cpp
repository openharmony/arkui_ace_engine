/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "frameworks/core/event/pointer_event.h"
#include "accessibility_element_info.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "adapter/ohos/osal/want_wrap_ohos.h"
#include "core/components_ng/pattern/ui_extension/isolated_component/isolated_pattern.h"
#include "frameworks/core/components_ng/pattern/ui_extension/platform_pattern.h"

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const std::string ISOLATED_COMPONENT_ETS_TAG = "IsolatedComponent";
    const std::string BUNDLE_NAME = "Test bundle name";
    const std::string ABILITY_NAME = "Test ability name";
    const std::string MOCK_HAP_PATH = "Test hap path";
    const std::string MOCK_ABC_PATH = "Test abc path";
    const std::string MOCK_ABC_ENTRY_POINT = "Test entry point";
    constexpr char RESOURCE_PATH[] = "resourcePath";
    constexpr char ABC_PATH[] = "abcPath";
    constexpr char ENTRY_POINT[] = "entryPoint";
    constexpr char REGISTER_COMPONENTS[] = "registerComponents";
    const SizeF CONTENT_SIZE = SizeF(400.0, 500.0);
    const OffsetF CONTENT_OFFSET = OffsetF(50.0, 60.0);
    const std::string TAG = "Test node tag";
} // namespace

class IsolatedPatternTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void IsolatedPatternTestNg::SetUp() {}

void IsolatedPatternTestNg::TearDown() {}


void IsolatedPatternTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;

    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
}

void IsolatedPatternTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: IsolatedPatternTest001
 * @tc.desc: Test IsolatedPattern GetUiExtensionId/WrapExtensionAbilityId
 * @tc.type: FUNC
 */
HWTEST_F(IsolatedPatternTestNg, IsolatedPatternTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a IsolatedComponent Node
     */
    auto isolatedNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto isolatedNode = FrameNode::GetOrCreateFrameNode(
        ISOLATED_COMPONENT_ETS_TAG, isolatedNodeId, []() { return AceType::MakeRefPtr<IsolatedPattern>(); });
    ASSERT_NE(isolatedNode, nullptr);
    EXPECT_EQ(isolatedNode->GetTag(), V2::ISOLATED_COMPONENT_ETS_TAG);
    
    /**
     * @tc.steps: step2. get IsolatedPattern
     */
    auto isolatedPattern = isolatedNode->GetPattern<IsolatedPattern>();
    ASSERT_NE(isolatedPattern, nullptr);

    /**
     * @tc.steps: step3. call GetUiExtensionId.
     * @tc.expected: expect result is 1
     */
    ASSERT_EQ(isolatedPattern->GetUiExtensionId(), 1);

    /**
     * @tc.steps: step4. call WrapExtensionAbilityId.
     * @tc.expected: expect result is 1.
     */
    int32_t extensionOffset = 1;
    int32_t abilityId = 1;
    int32_t result = isolatedPattern->WrapExtensionAbilityId(extensionOffset, abilityId);
    EXPECT_EQ(result, 2);
#endif
}

/**
 * @tc.name: IsolatedPatternTest002
 * @tc.desc: Test IsolatedPattern WrapExtensionAbilityId/DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(IsolatedPatternTestNg, IsolatedPatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a IsolatedComponent Node
     */
    auto isolatedNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto isolatedNode = FrameNode::GetOrCreateFrameNode(
        ISOLATED_COMPONENT_ETS_TAG, isolatedNodeId, []() { return AceType::MakeRefPtr<IsolatedPattern>(); });
    ASSERT_NE(isolatedNode, nullptr);
    EXPECT_EQ(isolatedNode->GetTag(), V2::ISOLATED_COMPONENT_ETS_TAG);
    
    /**
     * @tc.steps: step2. get IsolatedPattern
     */
    auto isolatedPattern = isolatedNode->GetPattern<IsolatedPattern>();
    ASSERT_NE(isolatedPattern, nullptr);

    /**
     * @tc.steps: step3. call InitializeIsolatedComponent.
     * @tc.expected: expect the feature of curIsolatedInfo_ is null after called due to the runtime.
     */
    auto wantWrap = AceType::MakeRefPtr<WantWrapOhos>(BUNDLE_NAME, ABILITY_NAME);
    void* runtime = nullptr;
    isolatedPattern->InitializeIsolatedComponent(wantWrap, runtime);
    EXPECT_TRUE(isolatedPattern->curIsolatedInfo_.abcPath.empty());
    EXPECT_TRUE(isolatedPattern->curIsolatedInfo_.resourcePath.empty());
    EXPECT_TRUE(isolatedPattern->curIsolatedInfo_.entryPoint.empty());
    EXPECT_TRUE(isolatedPattern->curIsolatedInfo_.registerComponents.empty());

     /**
     * @tc.steps: step4. call DumpInfo.
     */
    auto want = AceType::DynamicCast<WantWrapOhos>(wantWrap)->GetWant();
    auto resourcePath = want.GetStringParam(RESOURCE_PATH);
    auto abcPath = want.GetStringParam(ABC_PATH);
    auto entryPoint = want.GetStringParam(ENTRY_POINT);
    auto registerComponents = want.GetStringArrayParam(REGISTER_COMPONENTS);
    isolatedPattern->curIsolatedInfo_.abcPath = abcPath;
    isolatedPattern->curIsolatedInfo_.resourcePath = resourcePath;
    isolatedPattern->curIsolatedInfo_.entryPoint = entryPoint;
    isolatedPattern->curIsolatedInfo_.registerComponents = registerComponents;
    isolatedPattern->DumpInfo();
}

/**
 * @tc.name: IsolatedPatternTest003
 * @tc.desc: Test IsolatedPattern
 * @tc.type: FUNC
 */
HWTEST_F(IsolatedPatternTestNg, IsolatedPatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a IsolatedComponent Node
     */
    auto isolatedNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto isolatedNode = FrameNode::GetOrCreateFrameNode(
        ISOLATED_COMPONENT_ETS_TAG, isolatedNodeId, []() { return AceType::MakeRefPtr<IsolatedPattern>(); });
    ASSERT_NE(isolatedNode, nullptr);
    EXPECT_EQ(isolatedNode->GetTag(), V2::ISOLATED_COMPONENT_ETS_TAG);
    
    /**
     * @tc.steps: step2. get IsolatedPattern
     */
    auto isolatedPattern = isolatedNode->GetPattern<IsolatedPattern>();
    ASSERT_NE(isolatedPattern, nullptr);
}

/**
 * @tc.name: IsolatedPatternTest004
 * @tc.desc: Test IsolatedPattern SetAdaptiveWidth/SetAdaptiveHeight
 * @tc.type: FUNC
 */
HWTEST_F(IsolatedPatternTestNg, IsolatedPatternTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a IsolatedComponent Node
     */
    auto isolatedNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto isolatedNode = FrameNode::GetOrCreateFrameNode(
        ISOLATED_COMPONENT_ETS_TAG, isolatedNodeId, []() { return AceType::MakeRefPtr<IsolatedPattern>(); });
    ASSERT_NE(isolatedNode, nullptr);
    EXPECT_EQ(isolatedNode->GetTag(), V2::ISOLATED_COMPONENT_ETS_TAG);
    
    /**
     * @tc.steps: step2. get IsolatedPattern
     */
    auto isolatedPattern = isolatedNode->GetPattern<IsolatedPattern>();
    ASSERT_NE(isolatedPattern, nullptr);

    /**
     * @tc.steps: step3. call SetAdaptiveWidth.
     * @tc.expected: expect adaptiveHeight_ is true.
     */
    isolatedPattern->SetAdaptiveWidth(true);
    EXPECT_TRUE(isolatedPattern->adaptiveWidth_);
    isolatedPattern->SetAdaptiveWidth(false);
    EXPECT_FALSE(isolatedPattern->adaptiveWidth_);

    /**
     * @tc.steps: step4. call SetAdaptiveHeight.
     * @tc.expected: expect adaptiveHeight_ is true.
     */
    isolatedPattern->SetAdaptiveHeight(true);
    EXPECT_TRUE(isolatedPattern->adaptiveHeight_);
    isolatedPattern->SetAdaptiveHeight(false);
    EXPECT_FALSE(isolatedPattern->adaptiveHeight_);
}

/**
 * @tc.name: IsolatedPatternTest005
 * @tc.desc: Test IsolatedPattern OnDirtyLayoutWrapperSwap/OnDetachFromFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(IsolatedPatternTestNg, IsolatedPatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a IsolatedComponent Node
     */
    auto isolatedNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto isolatedNode = FrameNode::GetOrCreateFrameNode(
        ISOLATED_COMPONENT_ETS_TAG, isolatedNodeId, []() { return AceType::MakeRefPtr<IsolatedPattern>(); });
    ASSERT_NE(isolatedNode, nullptr);
    EXPECT_EQ(isolatedNode->GetTag(), V2::ISOLATED_COMPONENT_ETS_TAG);

    /**
     * @tc.steps: step2. get IsolatedPattern
     */
    auto isolatedPattern = isolatedNode->GetPattern<IsolatedPattern>();
    ASSERT_NE(isolatedPattern, nullptr);

    /**
     * @tc.steps: step3. call OnDirtyLayoutWrapperSwap.
     */
    auto pattern = AceType::MakeRefPtr<IsolatedPattern>();
    auto frameNode = FrameNode::CreateFrameNode(TAG, 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);

    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    isolatedPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    
    /**
     * @tc.steps: step4. call OnDetachFromFrameNode.
     * @tc.expected: expect dynamicComponentRenderer_ is null after called.
     */
    IsolatedInfo curIsolatedInfo;
    void* runtime = nullptr;
    RefPtr<FrameNode> host = FrameNode::CreateFrameNode(TAG, 2, pattern);
    isolatedPattern->dynamicComponentRenderer_ = DynamicComponentRenderer::Create(host, runtime, curIsolatedInfo);
    ASSERT_NE(isolatedPattern->dynamicComponentRenderer_, nullptr);
    isolatedPattern->OnDetachFromFrameNode(AceType::RawPtr(isolatedNode));
    EXPECT_EQ(isolatedPattern->dynamicComponentRenderer_, nullptr);
}

/**
 * @tc.name: IsolatedPatternTest006
 * @tc.desc: Test IsolatedPattern/InitializeRender/SearchElementInfosByText/DispatchFocusActiveEvent/
 * @tc.type: FUNC
 */
HWTEST_F(IsolatedPatternTestNg, IsolatedPatternTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a IsolatedComponent Node
     */
    auto isolatedNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto isolatedNode = FrameNode::GetOrCreateFrameNode(
        ISOLATED_COMPONENT_ETS_TAG, isolatedNodeId, []() { return AceType::MakeRefPtr<IsolatedPattern>(); });
    ASSERT_NE(isolatedNode, nullptr);
    EXPECT_EQ(isolatedNode->GetTag(), V2::ISOLATED_COMPONENT_ETS_TAG);

    /**
     * @tc.steps: step2. get IsolatedPattern
     */
    auto isolatedPattern = isolatedNode->GetPattern<IsolatedPattern>();
    ASSERT_NE(isolatedPattern, nullptr);

    /**
     * @tc.steps: step3. call InitializeRender.
     */
    void* runtime = nullptr;
    isolatedPattern->InitializeRender(runtime);
    EXPECT_EQ(isolatedPattern->dynamicComponentRenderer_, nullptr);

    /**
     * @tc.steps: step4. call DispatchPointerEvent.
     */
    std::shared_ptr<OHOS::MMI::PointerEvent> pointerEvent;
    isolatedPattern->DispatchPointerEvent(pointerEvent);

    
    /**
     * @tc.steps: step5. call DispatchPointerEvent.
     */
    IsolatedInfo curIsolatedInfo;
    auto pattern = AceType::MakeRefPtr<IsolatedPattern>();
    RefPtr<FrameNode> host = FrameNode::CreateFrameNode(TAG, 2, pattern);
    isolatedPattern->dynamicComponentRenderer_ = DynamicComponentRenderer::Create(host, runtime, curIsolatedInfo);
    isolatedPattern->DispatchPointerEvent(pointerEvent);
    
    /**
     * @tc.steps: step6. call DispatchFocusActiveEvent.
     */
    int32_t focusType = 1;
    isolatedPattern->DispatchFocusActiveEvent(true);
}

/**
 * @tc.name: IsolatedPatternTest007
 * @tc.desc: Test IsolatedPattern HandleKeyEvent/HandleFocusEvent/HandleBlurEvent/OnAttachToFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(IsolatedPatternTestNg, IsolatedPatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a IsolatedComponent Node
     */
    auto isolatedNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto isolatedNode = FrameNode::GetOrCreateFrameNode(
        ISOLATED_COMPONENT_ETS_TAG, isolatedNodeId, []() { return AceType::MakeRefPtr<IsolatedPattern>(); });
    ASSERT_NE(isolatedNode, nullptr);
    EXPECT_EQ(isolatedNode->GetTag(), V2::ISOLATED_COMPONENT_ETS_TAG);

    /**
     * @tc.steps: step2. get IsolatedPattern
     */
    auto isolatedPattern = isolatedNode->GetPattern<IsolatedPattern>();
    ASSERT_NE(isolatedPattern, nullptr);

    /**
     * @tc.steps: step3. call HandleKeyEvent.
     */
    KeyEvent keyEventOne(KeyCode::KEY_NUMPAD_1, KeyAction::DOWN);
    auto result = isolatedPattern->HandleKeyEvent(keyEventOne);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step4. call HandleFocusEvent.
     */
    IsolatedInfo curIsolatedInfo;
    void* runtime = nullptr;
    auto pattern = AceType::MakeRefPtr<IsolatedPattern>();
    RefPtr<FrameNode> host = FrameNode::CreateFrameNode(TAG, 2, pattern);
    isolatedPattern->dynamicComponentRenderer_ = DynamicComponentRenderer::Create(host, runtime, curIsolatedInfo);
    isolatedPattern->HandleFocusEvent();
    EXPECT_NE(isolatedPattern->dynamicComponentRenderer_, nullptr);

    /**
     * @tc.steps: step5. call HandleBlurEvent.0

     */
    isolatedPattern->HandleBlurEvent();

    /**
     * @tc.steps: step6. call OnAttachToFrameNode.
     */
    isolatedPattern->HandleBlurEvent();
}

/**
 * @tc.name: IsolatedPatternTest008
 * @tc.desc: Test IsolatedPattern SearchExtensionElementInfoByAccessibilityId/
    SearchElementInfosByText/TransferExecuteAction
 * @tc.type: FUNC
 */
HWTEST_F(IsolatedPatternTestNg, IsolatedPatternTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a IsolatedComponent Node
     */
    auto isolatedNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto isolatedNode = FrameNode::GetOrCreateFrameNode(
        ISOLATED_COMPONENT_ETS_TAG, isolatedNodeId, []() { return AceType::MakeRefPtr<IsolatedPattern>(); });
    ASSERT_NE(isolatedNode, nullptr);
    EXPECT_EQ(isolatedNode->GetTag(), V2::ISOLATED_COMPONENT_ETS_TAG);

    /**
     * @tc.steps: step2. get IsolatedPattern
     */
    auto isolatedPattern = isolatedNode->GetPattern<IsolatedPattern>();
    IsolatedInfo curIsolatedInfo;
    void* runtime = nullptr;
    auto pattern = AceType::MakeRefPtr<IsolatedPattern>();
    RefPtr<FrameNode> host = FrameNode::CreateFrameNode(TAG, 2, pattern);
    isolatedPattern->dynamicComponentRenderer_ = DynamicComponentRenderer::Create(host, runtime, curIsolatedInfo);
    ASSERT_NE(isolatedPattern, nullptr);

    /**
     * @tc.steps: step3. call SearchExtensionElementInfoByAccessibilityId.
     */
    int64_t elementId = 1;
    int32_t mode = 1;
    int64_t baseParent = 1;
    std::list<Accessibility::AccessibilityElementInfo> outputList;
    isolatedPattern->SearchExtensionElementInfoByAccessibilityId(elementId, mode, baseParent, outputList);

    /**
     * @tc.steps: step4. call SearchElementInfosByText.
     */
    std::string text = "test text";
    isolatedPattern->SearchElementInfosByText(elementId, text, baseParent, outputList);

    /**
     * @tc.steps: step5. call TransferExecuteAction.
     */
    int32_t action = 1;
    int32_t offset = 1;
    std::map<std::string, std::string> actionArguments;
    auto result = isolatedPattern->TransferExecuteAction(elementId, actionArguments, action, offset);
    ASSERT_TRUE(result);
}

/**
 * @tc.name: IsolatedPatternTest009
 * @tc.desc: Test InitializeRender
 * @tc.type: FUNC
 */
HWTEST_F(IsolatedPatternTestNg, IsolatedPatternTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a IsolatedComponent Node
     */
    auto isolatedNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto isolatedNode = FrameNode::GetOrCreateFrameNode(
        ISOLATED_COMPONENT_ETS_TAG, isolatedNodeId, []() { return AceType::MakeRefPtr<IsolatedPattern>(); });
    ASSERT_NE(isolatedNode, nullptr);
    EXPECT_EQ(isolatedNode->GetTag(), V2::ISOLATED_COMPONENT_ETS_TAG);

    /**
    * @tc.steps: step2. get IsolatedPattern
    */
    IsolatedInfo curIsolatedInfo;
    auto isolatedPattern = isolatedNode->GetPattern<IsolatedPattern>();
    void* runtime = nullptr;
    auto pattern = AceType::MakeRefPtr<IsolatedPattern>();
    RefPtr<FrameNode> host = FrameNode::CreateFrameNode(TAG, 2, pattern);
    auto mockRenderer = DynamicComponentRenderer::Create(host, runtime, curIsolatedInfo);
    isolatedPattern->dynamicComponentRenderer_ = mockRenderer;
    isolatedPattern->InitializeRender(runtime);
    //dynamicComponentRenderer_ not create again
    EXPECT_EQ(isolatedPattern->dynamicComponentRenderer_, mockRenderer);
}

/**
 * @tc.name: IsolatedPatternTest010
 * @tc.desc: Test CheckConstraint
 * @tc.type: FUNC
 */
HWTEST_F(IsolatedPatternTestNg, IsolatedPatternTest010, TestSize.Level1)
{
    /**
    * @tc.steps: step1. construct a IsolatedComponent Node
    */
    auto isolatedNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto isolatedNode = FrameNode::GetOrCreateFrameNode(
        V2::ISOLATED_COMPONENT_ETS_TAG, isolatedNodeId, []() { return AceType::MakeRefPtr<IsolatedPattern>(); });
    ASSERT_NE(isolatedNode, nullptr);
    EXPECT_EQ(isolatedNode->GetTag(), V2::ISOLATED_COMPONENT_ETS_TAG);

    /**
    * @tc.steps: step2. get IsolatedPattern
    */
    auto isolatedPattern = isolatedNode->GetPattern<IsolatedPattern>();
    EXPECT_FALSE(isolatedPattern->CheckConstraint());
}
} // namespace OHOS::Ace::NG
