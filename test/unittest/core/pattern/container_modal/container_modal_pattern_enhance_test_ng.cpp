/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd. All rights reserved.
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

#define protected public
#define private public

#include "test/mock/base/mock_subwindow.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/subwindow/subwindow_manager.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/theme/theme_constants.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_theme.h"
#include "core/components_ng/pattern/container_modal/container_modal_view.h"
#include "core/components_ng/pattern/container_modal/enhance/container_modal_pattern_enhance.h"
#include "core/components_ng/pattern/container_modal/enhance/container_modal_view_enhance.h"
#include "core/components_ng/pattern/custom/custom_title_node.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/relative_container/relative_container_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t VALID_CURRENT_ID = 6;
}
class ContainerModalPatternEnhanceTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    RefPtr<FrameNode> CreateContent();
    void CreateContainerModal();
    void GetInstance();
    RefPtr<PaintWrapper> FlushLayoutTask(const RefPtr<FrameNode>& frameNode);
    std::unique_ptr<ContainerModalViewEnhance> viewEnhance_;
    RefPtr<FrameNode> frameNode_;
    RefPtr<LayoutProperty> layoutProperty_;
    RefPtr<ContainerModalAccessibilityProperty> accessibilityProperty_;
    RefPtr<ContainerModalPatternEnhance> pattern_;
};
void ContainerModalPatternEnhanceTestNg::SetUpTestCase()
{
    MockContainer::SetUp();
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ContainerModalTheme>()));
}

void ContainerModalPatternEnhanceTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void ContainerModalPatternEnhanceTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    CHECK_NULL_VOID(frameNode_);
    viewEnhance_ = std::make_unique<ContainerModalViewEnhance>();
    pattern_ = frameNode_->GetPattern<ContainerModalPatternEnhance>();
    CHECK_NULL_VOID(pattern_);
    pattern_->AttachToFrameNode(frameNode_);
    layoutProperty_ = frameNode_->GetLayoutProperty();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<ContainerModalAccessibilityProperty>();
}

void ContainerModalPatternEnhanceTestNg::CreateContainerModal()
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::CONTAINER_MODAL_ETS_TAG, nodeId,
        []() { return AceType::MakeRefPtr<OHOS::Ace::NG::ContainerModalPatternEnhance>(); });
    ViewStackProcessor::GetInstance()->Push(frameNode);
    GetInstance();
    FlushLayoutTask(frameNode_);
    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    auto windowMode = WindowMode::WINDOW_MODE_FULLSCREEN;
    auto windowModeCallback = [windowMode]() { return windowMode; };
    windowManager->SetWindowGetModeCallBack(std::move(windowModeCallback));
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_ = windowManager;
}

RefPtr<PaintWrapper> ContainerModalPatternEnhanceTestNg::FlushLayoutTask(const RefPtr<FrameNode>& frameNode)
{
    frameNode->SetActive();
    frameNode->isLayoutDirtyMarked_ = true;
    frameNode->CreateLayoutTask();
    auto paintProperty = frameNode->GetPaintProperty<PaintProperty>();
    auto wrapper = frameNode->CreatePaintWrapper();
    if (wrapper != nullptr) {
        wrapper->FlushRender();
    }
    paintProperty->CleanDirty();
    frameNode->SetActive(false);
    return wrapper;
}

RefPtr<FrameNode> ContainerModalPatternEnhanceTestNg ::CreateContent()
{
    return AceType::MakeRefPtr<FrameNode>("content", 0, AceType::MakeRefPtr<Pattern>());
}

/**
 * @tc.name: ContainerModalPatternEnhanceTest001
 * @tc.desc: Test OnWindowUnfocused
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest001, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    containerModalPatternEnhance->OnWindowUnfocused();
    auto result = containerModalPatternEnhance->GetIsHoveredMenu();
    EXPECT_FALSE(result);
}
/**
 * @tc.name: ContainerModalPatternEnhanceTest002
 * @tc.desc: Test OnWindowUnfocused
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest002, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    auto subwindow = Subwindow::CreateSubwindow(VALID_CURRENT_ID);
    SubwindowManager::GetInstance()->SetCurrentSubwindow(subwindow);
    containerModalPatternEnhance->OnWindowUnfocused();
    auto result = containerModalPatternEnhance->GetIsHoveredMenu();
    EXPECT_FALSE(result);
}
/**
 * @tc.name: ContainerModalPatternEnhanceTest003
 * @tc.desc: Test OnWindowUnfocused
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest003, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    auto subwindow = AceType::MakeRefPtr<MockSubwindow>();
    SubwindowManager::GetInstance()->SetCurrentSubwindow(subwindow);
    containerModalPatternEnhance->isHoveredMenu_ = true;
    containerModalPatternEnhance->OnWindowUnfocused();
    auto result = containerModalPatternEnhance->GetIsHoveredMenu();
    EXPECT_TRUE(result);
}
/**
 * @tc.name: ContainerModalPatternEnhanceTest004
 * @tc.desc: Test OnWindowUnfocused
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest004, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    auto subwindow = AceType::MakeRefPtr<MockSubwindow>();
    SubwindowManager::GetInstance()->SetCurrentSubwindow(subwindow);
    containerModalPatternEnhance->OnWindowUnfocused();
    auto result = containerModalPatternEnhance->GetIsHoveredMenu();
    EXPECT_FALSE(result);
}
/**
 * @tc.name: ContainerModalPatternEnhanceTest005
 * @tc.desc: Test OnWindowForceUnfocused
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest005, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    containerModalPatternEnhance->OnWindowForceUnfocused();
    auto result = containerModalPatternEnhance->GetIsFocus();
    EXPECT_FALSE(result);
}
/**
 * @tc.name: ContainerModalPatternEnhanceTest007
 * @tc.desc: Test ChangeFloatingTitle
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest007, TestSize.Level1)
{
    auto windowMode = WindowMode::WINDOW_MODE_FLOATING;
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    auto windowModeCallback = [windowMode]() { return windowMode; };
    windowManager->SetWindowGetModeCallBack(std::move(windowModeCallback));
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_ = windowManager;
    containerModalPatternEnhance->ChangeFloatingTitle(true);
    auto result = containerModalPatternEnhance->GetIsFocus();
    EXPECT_FALSE(result);
}
/**
 * @tc.name: ContainerModalPatternEnhanceTest008
 * @tc.desc: Test ChangeFloatingTitle
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest008, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    auto windowMode = WindowMode::WINDOW_MODE_FULLSCREEN;
    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    auto windowModeCallback = [windowMode]() { return windowMode; };
    windowManager->SetWindowGetModeCallBack(std::move(windowModeCallback));
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_ = windowManager;
    containerModalPatternEnhance->ChangeFloatingTitle(true);
    auto result = containerModalPatternEnhance->GetIsFocus();
    EXPECT_FALSE(result);
}
/**
 * @tc.name: ContainerModalPatternEnhanceTest009
 * @tc.desc: Test ChangeFloatingTitle
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest009, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    auto windowMode = WindowMode::WINDOW_MODE_SPLIT_PRIMARY;
    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    auto windowModeCallback = [windowMode]() { return windowMode; };
    windowManager->SetWindowGetModeCallBack(std::move(windowModeCallback));
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_ = windowManager;
    containerModalPatternEnhance->ChangeFloatingTitle(true);
    auto result = containerModalPatternEnhance->GetIsFocus();
    EXPECT_FALSE(result);
}
/**
 * @tc.name: ContainerModalPatternEnhanceTest010
 * @tc.desc: Test ChangeFloatingTitle
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest010, TestSize.Level1)
{
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    containerModalNode->AddChild(
        FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 2, AceType::MakeRefPtr<ButtonPattern>()));
    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    containerPattern->SetContainerButtonHide(true, true, false, false);
    auto result = containerPattern->GetIsFocus();
    EXPECT_FALSE(result);
}
/**
 * @tc.name: ContainerModalPatternEnhanceTest011
 * @tc.desc: Test ChangeFloatingTitle
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest011, TestSize.Level1)
{
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    containerModalNode->AddChild(
        FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 2, AceType::MakeRefPtr<ButtonPattern>()));
    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    containerPattern->SetContainerButtonHide(true, false, true, false);
    auto result = containerPattern->GetIsFocus();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ContainerModalPatternEnhanceTest012
 * @tc.desc: Test ShowTitle
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest012, TestSize.Level1)
{
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto textNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<TextPickerColumnPattern>());
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(textNode);
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 6, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(buttonNode);
    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    containerPattern->ShowTitle(true, true, true);
    EXPECT_NE(containerPattern, nullptr);
}
/**
 * @tc.name: ContainerModalPatternEnhanceTest013
 * @tc.desc: Test ShowTitle
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest013, TestSize.Level1)
{
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto textNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<TextPickerColumnPattern>());
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(textNode);
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 6, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(buttonNode);
    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    containerPattern->ShowTitle(true, false, false);
    EXPECT_NE(containerPattern, nullptr);
}
/**
 * @tc.name: ContainerModalPatternEnhanceTest014
 * @tc.desc: Test ShowTitle
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest014, TestSize.Level1)
{
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto textNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<TextPickerColumnPattern>());
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(textNode);
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 6, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(buttonNode);
    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    containerPattern->ShowTitle(true, true, false);
    EXPECT_NE(containerPattern, nullptr);
}
/**
 * @tc.name: ContainerModalPatternEnhanceTest015
 * @tc.desc: Test ShowTitle
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest015, TestSize.Level1)
{
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto textNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<TextPickerColumnPattern>());
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(textNode);
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 6, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(buttonNode);
    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    auto pattern = containerModalNode->GetPattern<ContainerModalPattern>();
    pattern->SetContainerModalTitleVisible(true, true);
    containerPattern->ShowTitle(true, true, false);
    EXPECT_NE(containerPattern, nullptr);
}
/**
 * @tc.name: ContainerModalPatternEnhanceTest016
 * @tc.desc: Test ShowTitle
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest016, TestSize.Level1)
{
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto textNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<TextPickerColumnPattern>());
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(textNode);
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 6, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(buttonNode);
    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    auto windowMode = WindowMode::WINDOW_MODE_FLOATING;
    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    auto windowModeCallback = [windowMode]() { return windowMode; };
    windowManager->SetWindowGetModeCallBack(std::move(windowModeCallback));
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_ = windowManager;
    auto pattern = containerModalNode->GetPattern<ContainerModalPattern>();
    pattern->SetContainerModalTitleVisible(true, true);
    containerPattern->ShowTitle(true, true, false);
    EXPECT_NE(containerPattern, nullptr);
}
/**
 * @tc.name: ContainerModalPatternEnhanceTest017
 * @tc.desc: Test ShowTitle
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest017, TestSize.Level1)
{
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto textNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<TextPickerColumnPattern>());
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(textNode);
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 6, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(buttonNode);
    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    auto windowMode = WindowMode::WINDOW_MODE_FLOATING;
    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    auto windowModeCallback = [windowMode]() { return windowMode; };
    windowManager->SetWindowGetModeCallBack(std::move(windowModeCallback));
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_ = windowManager;
    auto pattern = containerModalNode->GetPattern<ContainerModalPattern>();
    pattern->SetContainerModalTitleVisible(false, true);
    containerPattern->ShowTitle(true, true, false);
    EXPECT_NE(containerPattern, nullptr);
}
/**
 * @tc.name: ContainerModalPatternEnhanceTest018
 * @tc.desc: Test ShowTitle
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest018, TestSize.Level1)
{
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto textNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<TextPickerColumnPattern>());
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(textNode);
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 6, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(buttonNode);
    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    containerPattern->UpdateTitleInTargetPos(true, true);
    EXPECT_NE(containerPattern, nullptr);
}
/**
 * @tc.name: ContainerModalPatternEnhanceTest019
 * @tc.desc: Test ShowTitle
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest019, TestSize.Level1)
{
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto textNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<TextPickerColumnPattern>());
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(textNode);
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 6, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(buttonNode);
    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    containerPattern->UpdateTitleInTargetPos(false, true);
    EXPECT_NE(containerPattern, nullptr);
}
/**
 * @tc.name: ContainerModalPatternEnhanceTest020
 * @tc.desc: Test ShowTitle
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest020, TestSize.Level1)
{
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto textNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<TextPickerColumnPattern>());
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(textNode);
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 6, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(buttonNode);
    auto windowMode = WindowMode::WINDOW_MODE_FULLSCREEN;
    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    auto windowModeCallback = [windowMode]() { return windowMode; };
    windowManager->SetWindowGetModeCallBack(std::move(windowModeCallback));
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_ = windowManager;
    auto pattern = containerModalNode->GetPattern<ContainerModalPattern>();
    pattern->windowMode_ = windowManager->GetWindowMode();
    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    containerPattern->UpdateTitleInTargetPos(true, true);
    EXPECT_NE(containerPattern, nullptr);
}
/**
 * @tc.name: ContainerModalPatternEnhanceTest021
 * @tc.desc: Test ShowTitle
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest021, TestSize.Level1)
{
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto textNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<TextPickerColumnPattern>());
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(textNode);
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 6, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(buttonNode);
    auto windowMode = WindowMode::WINDOW_MODE_FULLSCREEN;
    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    auto windowModeCallback = [windowMode]() { return windowMode; };
    windowManager->SetWindowGetModeCallBack(std::move(windowModeCallback));
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_ = windowManager;
    auto pattern = containerModalNode->GetPattern<ContainerModalPattern>();
    pattern->windowMode_ = windowManager->GetWindowMode();
    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    containerPattern->UpdateTitleInTargetPos(false, true);
    EXPECT_NE(containerPattern, nullptr);
}

/**
 * @tc.name: ContainerModalPatternEnhanceTest022
 * @tc.desc: Test GetContainerModalComponentRect
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest022, TestSize.Level1)
{
    RectF containerModal(0.0f, 0.0f, 0.0f, 0.0f);
    RectF buttons(0.0f, 0.0f, 0.0f, 0.0f);
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto textNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<TextPickerColumnPattern>());
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(textNode);
    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    auto ret = containerPattern->GetContainerModalComponentRect(containerModal, buttons);
    EXPECT_EQ(containerModal.Width(), 0);
    EXPECT_FALSE(ret);

    auto textGeometryNode = textNode->GetGeometryNode();
    textGeometryNode->frame_.rect_.width_ = 50.0f;
    textGeometryNode->frame_.rect_.height_ = 50.0f;
    ret = containerPattern->GetContainerModalComponentRect(containerModal, buttons);
    EXPECT_EQ(containerModal.Width(), 50.0f);
    EXPECT_FALSE(ret);

    containerPattern->customTitleSettedShow_ = false;
    ret = containerPattern->GetContainerModalComponentRect(containerModal, buttons);
    EXPECT_EQ(containerModal.Width(), 50.0f);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ContainerModalPatternEnhanceTest023
 * @tc.desc: Test GetContainerModalButtonsRect
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest023, TestSize.Level1)
{
    RectF containerModal(0.0f, 0.0f, 0.0f, 0.0f);
    RectF buttons(0.0f, 0.0f, 0.0f, 0.0f);
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto textNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<TextPickerColumnPattern>());
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(textNode);
    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    auto ret = containerPattern->GetContainerModalButtonsRect(containerModal, buttons);
    EXPECT_EQ(containerModal.Width(), 0);
    EXPECT_FALSE(ret);

    auto textGeometryNode = textNode->GetGeometryNode();
    textGeometryNode->frame_.rect_.width_ = 50.0f;
    textGeometryNode->frame_.rect_.height_ = 50.0f;
    ret = containerPattern->GetContainerModalButtonsRect(containerModal, buttons);
    EXPECT_EQ(containerModal.Width(), 50.0f);
    EXPECT_FALSE(ret);

    containerPattern->customTitleSettedShow_ = false;
    ret = containerPattern->GetContainerModalButtonsRect(containerModal, buttons);
    EXPECT_EQ(containerModal.Width(), 50.0f);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ContainerModalPatternEnhanceTest024
 * @tc.desc: Test use GetContainerModalButtonsRect after SetContainerModalTitleVisible
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest024, TestSize.Level1)
{
    RectF containerModal(0.0f, 0.0f, 1000.0f, 1000.0f);
    RectF buttons(0.0f, 0.0f, 50.0f, 50.0f);
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto textNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<TextPickerColumnPattern>());
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(textNode);
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 6, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(buttonNode);
    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    auto pattern = containerModalNode->GetPattern<ContainerModalPattern>();
    pattern->SetContainerModalTitleVisible(false, false);
    EXPECT_EQ(pattern->GetContainerModalTitleVisible(true), false);
}

/**
 * @tc.name: ContainerModalPatternEnhanceTest025
 * @tc.desc: Test use GetContainerModalButtonsRect after SetContainerModalTitleVisible
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest025, TestSize.Level1)
{
    RectF containerModal(0.0f, 0.0f, 1000.0f, 1000.0f);
    RectF buttons(0.0f, 0.0f, 50.0f, 50.0f);
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto textNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<TextPickerColumnPattern>());
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(textNode);
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 6, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(buttonNode);
    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    auto pattern = containerModalNode->GetPattern<ContainerModalPattern>();
    pattern->SetContainerModalTitleVisible(false, false);
    auto ret = containerPattern->GetContainerModalButtonsRect(containerModal, buttons);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ContainerModalPatternEnhanceTest026
 * @tc.desc: Test SetContainerModalTitleHeight
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest026, TestSize.Level1)
{
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto textNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<TextPickerColumnPattern>());
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(textNode);
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 6, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(buttonNode);
    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    auto pattern = containerModalNode->GetPattern<ContainerModalPattern>();
    pattern->SetContainerModalTitleHeight(100.0f);
    EXPECT_EQ(pattern->GetContainerModalTitleHeight(), 100.0f);
}

/**
 * @tc.name: ContainerModalPatternEnhanceTest027
 * @tc.desc: Test SetWindowContainerColor
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest027, TestSize.Level1)
{
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto textNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<TextPickerColumnPattern>());
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(textNode);
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 6, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(buttonNode);
    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    auto pattern = containerModalNode->GetPattern<ContainerModalPattern>();
    pattern->InitContainerColor();
    uint32_t value = 1;
    auto activeColor = Color(value);
    auto inactiveColor = Color(value);
    pattern->SetWindowContainerColor(activeColor, inactiveColor);
    auto windowscolor = pattern->GetContainerColor(true);
    EXPECT_EQ(windowscolor, activeColor);
}

/**
 * @tc.name: ContainerModalPatternEnhanceTest028
 * @tc.desc: Test ShowTitle
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest028, TestSize.Level1)
{
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto textNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<TextPickerColumnPattern>());
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(textNode);
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 6, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(buttonNode);
    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    bool isExecute = false;
    auto windowModeCallback = [isExecute](
                                  const std::string& name, const std::string& value) mutable { isExecute = true; };
    windowManager->SetWindowCallNativeCallback(std::move(windowModeCallback));
    windowManager->FireWindowCallNativeCallback("name", "value");
    EXPECT_EQ(isExecute, false);
}

/**
 * @tc.name: ContainerModalPatternEnhanceTest029
 * @tc.desc: Test ShowTitle
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest029, TestSize.Level1)
{
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto textNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<TextPickerColumnPattern>());
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(textNode);
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 6, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(buttonNode);
    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    bool isExecute = false;
    auto windowModeCallback = [isExecute](
                                  const std::string& name, const std::string& value) mutable { isExecute = true; };
    windowManager->SetWindowCallNativeCallback(std::move(windowModeCallback));
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_ = windowManager;
    auto pattern = containerModalNode->GetPattern<ContainerModalPattern>();
    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    containerPattern->OnContainerModalEvent("name", "value");
    EXPECT_NE(containerPattern, nullptr);
}

/**
 * @tc.name: ContainerModalPatternEnhanceTest030
 * @tc.desc: Test ShowTitle
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest030, TestSize.Level1)
{
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto textNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<TextPickerColumnPattern>());
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    textNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(textNode);
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 6, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(buttonNode);
    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    bool isExecute = false;
    auto windowModeCallback = [isExecute](
                                  const std::string& name, const std::string& value) mutable { isExecute = true; };
    windowManager->SetWindowCallNativeCallback(std::move(windowModeCallback));
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(containerModalNode, nullptr);
    ASSERT_NE(pipeline, nullptr);
    containerModalNode->AttachContext(AceType::RawPtr(pipeline));
    pipeline->windowManager_ = windowManager;
    auto pattern = containerModalNode->GetPattern<ContainerModalPattern>();
    ASSERT_NE(pattern, nullptr);
    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    ASSERT_NE(containerPattern, nullptr);
    containerPattern->CallContainerModalNative("name", "value");
    EXPECT_NE(containerPattern, nullptr);
}

/**
 * @tc.name: windowFocus or active
 * @tc.desc: Test windowFocus or active.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest031, TestSize.Level1)
{
    CreateContainerModal();
    auto cloumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(cloumn, nullptr);
    frameNode_->AddChild(cloumn);
    auto titleRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 1, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto titleRow2 = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 1, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto floatingTitleRow =
        FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 1, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    ASSERT_NE(titleRow, nullptr);
    ASSERT_NE(titleRow2, nullptr);
    ASSERT_NE(floatingTitleRow, nullptr);
    frameNode_->AddChild(floatingTitleRow);
    cloumn->AddChild(titleRow);
    titleRow->AddChild(titleRow2);
    auto customTitleNode = CustomTitleNode::CreateCustomTitleNode(-1, "");
    auto customFloatingTitleNode = CustomTitleNode::CreateCustomTitleNode(-1, "");
    ASSERT_NE(customTitleNode, nullptr);
    ASSERT_NE(customFloatingTitleNode, nullptr);
    titleRow2->AddChild(customTitleNode);
    floatingTitleRow->AddChild(customFloatingTitleNode);
    auto titleResult = false;
    auto focusCallback = [&titleResult]() { titleResult = true; };
    auto unfocusCallback = [&titleResult]() { titleResult = false; };
    auto floatingTitleResult = false;
    auto focusCallback2 = [&floatingTitleResult]() { floatingTitleResult = true; };
    auto unfocusCallback2 = [&floatingTitleResult]() { floatingTitleResult = false; };
    customTitleNode->SetOnWindowFocusedCallback(focusCallback);
    customFloatingTitleNode->SetOnWindowFocusedCallback(focusCallback2);
    customTitleNode->SetOnWindowUnfocusedCallback(unfocusCallback);
    customFloatingTitleNode->SetOnWindowUnfocusedCallback(unfocusCallback2);

    pattern_->WindowFocus(true);
    EXPECT_TRUE(pattern_->isFocus_);
    EXPECT_TRUE(titleResult);
    EXPECT_TRUE(floatingTitleResult);
    pattern_->WindowFocus(false);
    EXPECT_FALSE(pattern_->isFocus_);
    EXPECT_FALSE(titleResult);
    EXPECT_FALSE(floatingTitleResult);
}

/**
 * @tc.name: GetContainerModalButtonsRect001
 * @tc.desc: Test use GetContainerModalButtonsRect
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, GetContainerModalButtonsRect001, TestSize.Level1)
{
    RectF containerModal(0.0f, 0.0f, 1000.0f, 1000.0f);
    RectF buttons(0.0f, 0.0f, 50.0f, 50.0f);
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto cloumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    cloumn->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    cloumn->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(cloumn);
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 5, AceType::MakeRefPtr<TextPattern>()));
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 6, AceType::MakeRefPtr<TextPattern>()));
    containerModalNode->AddChild(buttonNode);
    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    auto pattern = containerModalNode->GetPattern<ContainerModalPattern>();
    pattern->SetContainerButtonHide(true, true, true, true);
    auto ret = containerPattern->GetContainerModalButtonsRect(containerModal, buttons);
    EXPECT_FALSE(ret);
}

} // namespace OHOS::Ace::NG