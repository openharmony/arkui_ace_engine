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
#include "accessibility_element_info.h"
#include "adapter/ohos/osal/want_wrap_ohos.h"
#include "core/common/window.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/ui_extension/dynamic_component/dynamic_pattern.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model_ng.h"
#include "frameworks/core/components_ng/pattern/ui_extension/platform_pattern.h"
#include "frameworks/core/event/pointer_event.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const std::string BUNDLE_NAME = "Test bundle name";
    const std::string ABILITY_NAME = "Test ability name";
    const std::string DYNAMIC_COMPONENT_ETS_TAG = "DynamicComponent";
    const std::string MOCK_ABC_ENTRY_POINT = "Test entry point";
    const SizeF CONTENT_SIZE = SizeF(400.0, 500.0);
    const OffsetF CONTENT_OFFSET = OffsetF(50.0, 60.0);
    const std::string TAG = "Test node tag";
} // namespace

class DynamicPatternTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    RefPtr<DynamicPattern> CreateDynamicComponent();
};

void DynamicPatternTestNg::SetUp() {}

void DynamicPatternTestNg::TearDown() {}

RefPtr<DynamicPattern> DynamicPatternTestNg::CreateDynamicComponent()
{
    auto dynamicNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dynamicNode = FrameNode::GetOrCreateFrameNode(
        DYNAMIC_COMPONENT_ETS_TAG, dynamicNodeId, []() { return AceType::MakeRefPtr<DynamicPattern>(); });
    EXPECT_NE(dynamicNode, nullptr);
    EXPECT_EQ(dynamicNode->GetTag(), V2::DYNAMIC_COMPONENT_ETS_TAG);

    return dynamicNode->GetPattern<DynamicPattern>();
}

/**
 * @tc.name: DynamicPatternTest001
 * @tc.desc: Test DynamicPattern WrapExtensionAbilityId/DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNg, DynamicPatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get DynamicPattern
     */
    auto dynamicPattern = CreateDynamicComponent();
    EXPECT_NE(dynamicPattern, nullptr);

    /**
     * @tc.steps: step2. call InitializeDynamicComponent.
     * @tc.expected: expect the feature of curDynamicInfo_ is null after called due to the runtime.
     */
    void* runtime = nullptr;
    dynamicPattern->InitializeDynamicComponent("", "", MOCK_ABC_ENTRY_POINT, runtime);
    EXPECT_TRUE(dynamicPattern->curDynamicInfo_.abcPath.empty());
    EXPECT_TRUE(dynamicPattern->curDynamicInfo_.entryPoint.empty());
    EXPECT_TRUE(dynamicPattern->curDynamicInfo_.reourcePath.empty());
    EXPECT_TRUE(dynamicPattern->curDynamicInfo_.registerComponents.empty());

     /**
     * @tc.steps: step3. call DumpInfo.
     */
    dynamicPattern->curDynamicInfo_.abcPath = MOCK_ABC_ENTRY_POINT;
    dynamicPattern->DumpInfo();
}

/**
 * @tc.name: DynamicPatternTest002
 * @tc.desc: Test DynamicPattern SetAdaptiveWidth/SetAdaptiveHeight
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNg, DynamicPatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get DynamicPattern
     */
    auto dynamicPattern = CreateDynamicComponent();
    EXPECT_NE(dynamicPattern, nullptr);

    /**
     * @tc.steps: step2. call SetAdaptiveWidth.
     * @tc.expected: expect adaptiveHeight_ is true.
     */
    dynamicPattern->SetAdaptiveWidth(true);
    EXPECT_TRUE(dynamicPattern->adaptiveWidth_);
    dynamicPattern->SetAdaptiveWidth(false);
    EXPECT_FALSE(dynamicPattern->adaptiveWidth_);

    /**
     * @tc.steps: step3. call SetAdaptiveHeight.
     * @tc.expected: expect adaptiveHeight_ is true.
     */
    dynamicPattern->SetAdaptiveHeight(true);
    EXPECT_TRUE(dynamicPattern->adaptiveHeight_);
    dynamicPattern->SetAdaptiveHeight(false);
    EXPECT_FALSE(dynamicPattern->adaptiveHeight_);
}

/**
 * @tc.name: DynamicPatternTest003
 * @tc.desc: Test DynamicPattern OnDirtyLayoutWrapperSwap/OnDetachFromFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNg, DynamicPatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DynamicComponent Node
     */
    auto dynamicNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dynamicNode = FrameNode::GetOrCreateFrameNode(
        DYNAMIC_COMPONENT_ETS_TAG, dynamicNodeId, []() { return AceType::MakeRefPtr<DynamicPattern>(); });
    ASSERT_NE(dynamicNode, nullptr);
    EXPECT_EQ(dynamicNode->GetTag(), V2::DYNAMIC_COMPONENT_ETS_TAG);

    /**
     * @tc.steps: step2. get DynamicPattern
     */
    auto dynamicPattern = dynamicNode->GetPattern<DynamicPattern>();
    ASSERT_NE(dynamicPattern, nullptr);

    /**
     * @tc.steps: step3. call OnDirtyLayoutWrapperSwap.
     */
    auto pattern = AceType::MakeRefPtr<DynamicPattern>();
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
    dynamicPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);

    /**
     * @tc.steps: step4. call OnDetachFromFrameNode.
     * @tc.expected: expect dynamicComponentRenderer_ is null after called.
     */
    IsolatedInfo curDynamicInfo;
    void* runtime = nullptr;
    RefPtr<FrameNode> frameNode2 = FrameNode::CreateFrameNode(TAG, 2, pattern);
    dynamicPattern->dynamicComponentRenderer_ = DynamicComponentRenderer::Create(frameNode2, runtime, curDynamicInfo);
    ASSERT_NE(dynamicPattern->dynamicComponentRenderer_, nullptr);
    dynamicPattern->OnDetachFromFrameNode(AceType::RawPtr(dynamicNode));
    EXPECT_EQ(dynamicPattern->dynamicComponentRenderer_, nullptr);
}

/**
 * @tc.name: DynamicPatternTest004
 * @tc.desc: Test DynamicPattern/InitializeRender/SearchElementInfosByText/DispatchFocusActiveEvent/
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNg, DynamicPatternTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get DynamicPattern
     */
    auto dynamicPattern = CreateDynamicComponent();
    EXPECT_NE(dynamicPattern, nullptr);

    /**
     * @tc.steps: step2. call InitializeRender.
     */
    void* runtime = nullptr;
    dynamicPattern->InitializeRender(runtime);

    /**
     * @tc.steps: step3. call SearchElementInfosByText.
     */
    std::shared_ptr<OHOS::MMI::PointerEvent> pointerEvent;
    dynamicPattern->DispatchPointerEvent(pointerEvent);

    /**
     * @tc.steps: step4. call DispatchFocusActiveEvent.
     */
    int32_t focusType = 1;
    dynamicPattern->DispatchFocusActiveEvent(true);
}

/**
 * @tc.name: DynamicPatternTest005
 * @tc.desc: Test DynamicPattern HandleKeyEvent/HandleFocusEvent/HandleBlurEvent/OnAttachToFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNg, DynamicPatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get DynamicPattern
     */
    auto dynamicPattern = CreateDynamicComponent();
    EXPECT_NE(dynamicPattern, nullptr);

    /**
     * @tc.steps: step2. call HandleKeyEvent.
     */
    KeyEvent keyEventOne(KeyCode::KEY_NUMPAD_1, KeyAction::DOWN);
    auto result = dynamicPattern->HandleKeyEvent(keyEventOne);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step3. call HandleFocusEvent.
     */
    dynamicPattern->HandleFocusEvent();

    /**
     * @tc.steps: step4. call HandleBlurEvent.0
     */
    dynamicPattern->HandleBlurEvent();

    /**
     * @tc.steps: step5. call OnAttachToFrameNode.
     */
    dynamicPattern->HandleBlurEvent();
}

/**
 * @tc.name: DynamicPatternTest006
 * @tc.desc: Test DynamicPattern SearchExtensionElementInfoByAccessibilityId/SearchElementInfosByText
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNg, DynamicPatternTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get DynamicPattern
     */
    auto dynamicPattern = CreateDynamicComponent();
    EXPECT_NE(dynamicPattern, nullptr);
    IsolatedInfo curDynamicInfo;
    void* runtime = nullptr;
    auto pattern = AceType::MakeRefPtr<DynamicPattern>();
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(TAG, 2, pattern);
    dynamicPattern->dynamicComponentRenderer_ = DynamicComponentRenderer::Create(frameNode, runtime, curDynamicInfo);
    ASSERT_NE(dynamicPattern, nullptr);

    /**
     * @tc.steps: step2. call SearchExtensionElementInfoByAccessibilityId.
     */
    int64_t elementId = 1;
    int32_t mode = 1;
    int64_t baseParent = 1;
    std::list<Accessibility::AccessibilityElementInfo> outputList;
    dynamicPattern->SearchExtensionElementInfoByAccessibilityId(elementId, mode, baseParent, outputList);

    /**
     * @tc.steps: step3. call SearchElementInfosByText.
     */
    std::string text = "test text";
    dynamicPattern->SearchElementInfosByText(elementId, text, baseParent, outputList);
}

/**
 * @tc.name: DynamicPatternTest007
 * @tc.desc: Test DynamicPattern SetBackgroundTransparent
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNg, DynamicPatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get DynamicPattern
     */
    auto dynamicPattern = CreateDynamicComponent();
    EXPECT_NE(dynamicPattern, nullptr);
    EXPECT_TRUE(dynamicPattern->backgroundTransparent_);

    /**
     * @tc.steps: step1. call SetBackgroundTransparent(false).
     */
    dynamicPattern->SetBackgroundTransparent(false);
    EXPECT_FALSE(dynamicPattern->backgroundTransparent_);

    /**
     * @tc.steps: step1. call SetBackgroundTransparent(true).
     */
    dynamicPattern->SetBackgroundTransparent(true);
    EXPECT_TRUE(dynamicPattern->backgroundTransparent_);
}

/**
 * @tc.name: DynamicPatternTest008
 * @tc.desc: Test DynamicPattern UIExtensionModelNG.create
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNg, DynamicPatternTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. UIExtensionModelNG create DynamicComponent
     */
    NG::UIExtensionConfig config;
    config.sessionType = SessionType::DYNAMIC_COMPONENT;
    config.backgroundTransparent = false;
    NG::UIExtensionModelNG uecNG;
    uecNG.Create(config);

    /**
     * @tc.steps: step2. test frameNode and pattern
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::DYNAMIC_COMPONENT_ETS_TAG);

    auto pattern = frameNode->GetPattern<DynamicPattern>();
    EXPECT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->backgroundTransparent_, false);
}

/**
 * @tc.name: DynamicPatternTest009
 * @tc.desc: Test DynamicPattern Accessibility
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNg, DynamicPatternTest009, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. UIExtensionModelNG create DynamicComponent
     */
    auto dynamicPattern = CreateDynamicComponent();
    EXPECT_NE(dynamicPattern, nullptr);
    IsolatedInfo curDynamicInfo;
    void* runtime = nullptr;
    auto pattern = AceType::MakeRefPtr<DynamicPattern>();
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(TAG, 2, pattern);
    dynamicPattern->dynamicComponentRenderer_ = DynamicComponentRenderer::Create(frameNode, runtime, curDynamicInfo);
    ASSERT_NE(dynamicPattern, nullptr);

    /**
     * @tc.steps: step2. test Accessibility
     */
    pattern->AttachToFrameNode(frameNode);
    pattern->OnModifyDone();
    auto property = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(property, nullptr);
    pattern->InitializeAccessibility();
    pattern->OnSetAccessibilityChildTree(1, 1);
    pattern->OnAccessibilityChildTreeRegister(1, 1, 1);
    pattern->OnAccessibilityChildTreeDeregister();
    EXPECT_EQ(property->GetChildWindowId(), 1);
    EXPECT_EQ(property->GetChildTreeId(), 1);

    frameNode->accessibilityProperty_ = nullptr;
    pattern->InitializeAccessibility();
    pattern->OnSetAccessibilityChildTree(1, 1);
    pattern->OnAccessibilityChildTreeRegister(1, 1, 1);
    pattern->OnAccessibilityChildTreeDeregister();
    std::vector<std::string> params;
    std::vector<std::string> info;
    pattern->OnAccessibilityDumpChildInfo(params, info);
    EXPECT_EQ(params.size(), 0);
#endif
}
} // namespace OHOS::Ace::NG
