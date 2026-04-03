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

#include "test/mock/frameworks/base/subwindow/mock_subwindow.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "base/subwindow/subwindow_manager.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/list/list_item_theme.h"
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
#include "core/components/select/select_theme.h"

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

/**
 * @tc.name: ContainerModalPatternEnhanceGetContextRefPtr
 * @tc.desc: Test ContainerModalPatternEnhanceGetContextRefPtr
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceGetContextRefPtr, TestSize.Level1)
{
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    containerModalNode->AddChild(
        FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 2, AceType::MakeRefPtr<ButtonPattern>()));
    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    auto  context = containerPattern->GetContextRefPtr();
    EXPECT_NE(context, nullptr);
}

/**
 * @tc.name: InitMenuDefaultRadius
 * @tc.desc: Test InitMenuDefaultRadius
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, InitMenuDefaultRadius, TestSize.Level1)
{
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    containerModalNode->AddChild(
        FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 2, AceType::MakeRefPtr<ButtonPattern>()));
    auto cloumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto titleResult = false;
    auto callback = [&titleResult](const std::string& eventName, const std::string& param) { titleResult = true; };
    auto customTitleNode = CustomTitleNode::CreateCustomTitleNode(-1, "");
    customTitleNode->SetCustomCallback(callback);
    cloumn->AddChild(customTitleNode);
    containerModalNode->AddChild(cloumn);
    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    containerPattern->InitMenuDefaultRadius();
    EXPECT_TRUE(titleResult);
}
/**
 * @tc.name: AddPanEvent001
 * @tc.desc: Test AddPanEvent001
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, AddPanEvent001, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    auto windowMode = WindowMode::WINDOW_MODE_FULLSCREEN;
    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    auto windowModeCallback = [windowMode]() { return windowMode; };
    windowManager->SetWindowGetModeCallBack(std::move(windowModeCallback));
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_ = windowManager;
    auto frameNode = AceType::MakeRefPtr<FrameNode>("frameNode", 100, AceType::MakeRefPtr<Pattern>());
    containerModalPatternEnhance->AddPanEvent(frameNode);
    EXPECT_NE(containerModalPatternEnhance->panEvent_, nullptr);
}

/**
 * @tc.name: NotifyButtonsRectChangeTest001
 * @tc.desc: Test function about NotifyButtonsRectChange.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, NotifyButtonsRectChangeTest001, TestSize.Level1)
{
    RectF containerModalRect;
    RectF buttonsRect;
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto textNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<TextPickerColumnPattern>());
    containerModalNode->AddChild(textNode);
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    containerModalNode->AddChild(buttonNode);
    auto buttonNodeProperty = buttonNode->GetLayoutProperty();
    buttonNodeProperty->UpdateVisibility(VisibleType::VISIBLE);
    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    bool callbackTriggered = false;
    auto callback1 = [&callbackTriggered](const RectF&, const RectF&) { callbackTriggered = true; };
    containerPattern->AddButtonsRectChangeListener(std::move(callback1));
    containerPattern->NotifyButtonsRectChange(containerModalRect, buttonsRect);
    EXPECT_FALSE(callbackTriggered);
    
    buttonNodeProperty->UpdateVisibility(VisibleType::INVISIBLE);
    auto callback2 = [&callbackTriggered](const RectF&, const RectF&) { callbackTriggered = true; };
    containerPattern->AddButtonsRectChangeListener(std::move(callback2));
    containerPattern->NotifyButtonsRectChange(containerModalRect, buttonsRect);
    EXPECT_TRUE(callbackTriggered);
}

/**
 * @tc.name: OnMaxButtonClick_WindowIsMoving
 * @tc.desc: Test OnMaxButtonClick does nothing when window is moving
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, OnMaxButtonClick_WindowIsMoving, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    containerModalNode->AddChild(
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true)));
    containerModalPatternEnhance->AttachToFrameNode(containerModalNode);

    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    auto windowMode = WindowMode::WINDOW_MODE_FLOATING;
    windowManager->SetWindowGetModeCallBack([windowMode]() { return windowMode; });
    windowManager->SetWindowIsStartMovingCallBack([]() { return true; });
    bool isMaximizeCalled = false;
    windowManager->SetWindowMaximizeCallBack([&isMaximizeCalled]() { isMaximizeCalled = true; });
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_ = windowManager;

    GestureEvent info;
    containerModalPatternEnhance->OnMaxButtonClick(info);
    EXPECT_FALSE(isMaximizeCalled);
}

/**
 * @tc.name: OnMinButtonClick_NotMoving
 * @tc.desc: Test OnMinButtonClick triggers WindowMinimize when window is not moving
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, OnMinButtonClick_NotMoving, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    containerModalNode->AddChild(
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true)));
    containerModalPatternEnhance->AttachToFrameNode(containerModalNode);

    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    auto windowMode = WindowMode::WINDOW_MODE_FLOATING;
    windowManager->SetWindowGetModeCallBack([windowMode]() { return windowMode; });
    windowManager->SetWindowIsStartMovingCallBack([]() { return false; });
    bool isMinimizeCalled = false;
    windowManager->SetWindowMinimizeCallBack([&isMinimizeCalled]() { isMinimizeCalled = true; });
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_ = windowManager;

    GestureEvent info;
    containerModalPatternEnhance->OnMinButtonClick(info);
    EXPECT_TRUE(isMinimizeCalled);
}

/**
 * @tc.name: OnMinButtonClickNoArg_NotMoving
 * @tc.desc: Test no-arg OnMinButtonClick triggers WindowMinimize
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, OnMinButtonClickNoArg_NotMoving, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    containerModalNode->AddChild(
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true)));
    containerModalPatternEnhance->AttachToFrameNode(containerModalNode);

    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    windowManager->SetWindowIsStartMovingCallBack([]() { return false; });
    bool isMinimizeCalled = false;
    windowManager->SetWindowMinimizeCallBack([&isMinimizeCalled]() { isMinimizeCalled = true; });
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_ = windowManager;

    containerModalPatternEnhance->OnMinButtonClick();
    EXPECT_TRUE(isMinimizeCalled);
}

/**
 * @tc.name: OnCloseButtonClick_NotMoving
 * @tc.desc: Test OnCloseButtonClick triggers WindowClose when window is not moving
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, OnCloseButtonClick_NotMoving, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    containerModalNode->AddChild(
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true)));
    containerModalPatternEnhance->AttachToFrameNode(containerModalNode);

    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    windowManager->SetWindowIsStartMovingCallBack([]() { return false; });
    bool isCloseCalled = false;
    windowManager->SetWindowCloseCallBack([&isCloseCalled]() { isCloseCalled = true; });
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_ = windowManager;

    GestureEvent info;
    containerModalPatternEnhance->OnCloseButtonClick(info);
    EXPECT_TRUE(isCloseCalled);
}

/**
 * @tc.name: OnCloseButtonClickNoArg_NotMoving
 * @tc.desc: Test no-arg OnCloseButtonClick triggers WindowClose
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, OnCloseButtonClickNoArg_NotMoving, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    containerModalNode->AddChild(
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true)));
    containerModalPatternEnhance->AttachToFrameNode(containerModalNode);

    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    windowManager->SetWindowIsStartMovingCallBack([]() { return false; });
    bool isCloseCalled = false;
    windowManager->SetWindowCloseCallBack([&isCloseCalled]() { isCloseCalled = true; });
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_ = windowManager;

    containerModalPatternEnhance->OnCloseButtonClick();
    EXPECT_TRUE(isCloseCalled);
}

/**
 * @tc.name: OnMaxBtnInputEvent_LeftButton
 * @tc.desc: Test OnMaxBtnInputEvent sets isForbidMenuEvent_ to true when left button is pressed
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, OnMaxBtnInputEvent_LeftButton, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    containerModalPatternEnhance->isForbidMenuEvent_ = false;

    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetScreenLocation(Offset(100, 100));
    containerModalPatternEnhance->OnMaxBtnInputEvent(info);
    EXPECT_TRUE(containerModalPatternEnhance->isForbidMenuEvent_);
}

/**
 * @tc.name: OnMaxBtnInputEvent_RightButton
 * @tc.desc: Test OnMaxBtnInputEvent does not set isForbidMenuEvent_ when right button is pressed
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, OnMaxBtnInputEvent_RightButton, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    containerModalPatternEnhance->isForbidMenuEvent_ = false;

    MouseInfo info;
    info.SetButton(MouseButton::RIGHT_BUTTON);
    info.SetScreenLocation(Offset(100, 100));
    containerModalPatternEnhance->OnMaxBtnInputEvent(info);
    EXPECT_FALSE(containerModalPatternEnhance->isForbidMenuEvent_);
}

/**
 * @tc.name: OnMaxBtnInputEvent_ZeroScreenLocation
 * @tc.desc: Test OnMaxBtnInputEvent sets isForbidMenuEvent_ to true when screen location is zero
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, OnMaxBtnInputEvent_ZeroScreenLocation, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    containerModalPatternEnhance->isForbidMenuEvent_ = false;

    MouseInfo info;
    info.SetButton(MouseButton::RIGHT_BUTTON);
    info.SetScreenLocation(Offset(0, 0));
    containerModalPatternEnhance->OnMaxBtnInputEvent(info);
    EXPECT_TRUE(containerModalPatternEnhance->isForbidMenuEvent_);
}

/**
 * @tc.name: OnMaxBtnHoverEvent_HoverFalse
 * @tc.desc: Test OnMaxBtnHoverEvent resets hover timer when hover is false
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, OnMaxBtnHoverEvent_HoverFalse, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    containerModalPatternEnhance->isMenuPending_ = true;

    RefPtr<FrameNode> btnNode =
        FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 1, AceType::MakeRefPtr<ButtonPattern>());
    WeakPtr<FrameNode> weakBtn = btnNode;

    containerModalPatternEnhance->OnMaxBtnHoverEvent(false, weakBtn);
    EXPECT_FALSE(containerModalPatternEnhance->isMenuPending_);
}

/**
 * @tc.name: OnMaxBtnHoverEvent_HoverTrueMenuPending
 * @tc.desc: Test OnMaxBtnHoverEvent does nothing when isMenuPending_ is true
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, OnMaxBtnHoverEvent_HoverTrueMenuPending, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    containerModalPatternEnhance->isMenuPending_ = true;

    RefPtr<FrameNode> btnNode =
        FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 1, AceType::MakeRefPtr<ButtonPattern>());
    WeakPtr<FrameNode> weakBtn = btnNode;

    containerModalPatternEnhance->OnMaxBtnHoverEvent(true, weakBtn);
    EXPECT_TRUE(containerModalPatternEnhance->isMenuPending_);
}

/**
 * @tc.name: OnMaxBtnHoverEvent_HoverTrueForbidMenuEvent
 * @tc.desc: Test OnMaxBtnHoverEvent does nothing when isForbidMenuEvent_ is true
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, OnMaxBtnHoverEvent_HoverTrueForbidMenuEvent, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    containerModalPatternEnhance->isForbidMenuEvent_ = true;

    RefPtr<FrameNode> btnNode =
        FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 1, AceType::MakeRefPtr<ButtonPattern>());
    WeakPtr<FrameNode> weakBtn = btnNode;

    containerModalPatternEnhance->OnMaxBtnHoverEvent(true, weakBtn);
    EXPECT_FALSE(containerModalPatternEnhance->isMenuPending_);
}

/**
 * @tc.name: OnMaxBtnHoverEvent_HoverTrueNotFocus
 * @tc.desc: Test OnMaxBtnHoverEvent does nothing when window is not focused
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, OnMaxBtnHoverEvent_HoverTrueNotFocus, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    containerModalPatternEnhance->isFocus_ = false;

    RefPtr<FrameNode> btnNode =
        FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 1, AceType::MakeRefPtr<ButtonPattern>());
    WeakPtr<FrameNode> weakBtn = btnNode;

    containerModalPatternEnhance->OnMaxBtnHoverEvent(true, weakBtn);
    EXPECT_FALSE(containerModalPatternEnhance->isMenuPending_);
}

/**
 * @tc.name: OnMenuItemClickGesture_LeftSplit
 * @tc.desc: Test OnMenuItemClickGesture fires split left callback
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, OnMenuItemClickGesture_LeftSplit, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    containerModalNode->AddChild(
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true)));
    containerModalPatternEnhance->AttachToFrameNode(containerModalNode);

    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    bool isSplitLeftCalled = false;
    windowManager->SetWindowSplitPrimaryCallBack([&isSplitLeftCalled]() { isSplitLeftCalled = true; });
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_ = windowManager;

    containerModalPatternEnhance->OnMenuItemClickGesture(true);
    EXPECT_TRUE(isSplitLeftCalled);
}

/**
 * @tc.name: OnMenuItemClickGesture_RightSplit
 * @tc.desc: Test OnMenuItemClickGesture fires split right callback
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, OnMenuItemClickGesture_RightSplit, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    containerModalNode->AddChild(
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true)));
    containerModalPatternEnhance->AttachToFrameNode(containerModalNode);

    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    bool isSplitRightCalled = false;
    windowManager->SetWindowSplitSecondaryCallBack([&isSplitRightCalled]() { isSplitRightCalled = true; });
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_ = windowManager;

    containerModalPatternEnhance->OnMenuItemClickGesture(false);
    EXPECT_TRUE(isSplitRightCalled);
}

/**
 * @tc.name: OnMenuItemClickEvent_PressAction
 * @tc.desc: Test OnMenuItemClickEvent updates background color on press action
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, OnMenuItemClickEvent_PressAction, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(themeManager);
    auto listItemTheme = AceType::MakeRefPtr<ListItemTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(listItemTheme));

    auto itemNode =
        FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 1, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    itemNode->AttachContext(AceType::RawPtr(pipeline));

    MouseInfo info;
    info.SetAction(MouseAction::PRESS);
    ContainerModalPatternEnhance::OnMenuItemClickEvent(itemNode, info);

    auto renderContext = itemNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto bgColor = renderContext->GetBackgroundColor();
    EXPECT_TRUE(bgColor.has_value());
}

/**
 * @tc.name: OnMenuItemClickEvent_ReleaseAction
 * @tc.desc: Test OnMenuItemClickEvent does not update background color on release action
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, OnMenuItemClickEvent_ReleaseAction, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(themeManager);
    auto listItemTheme = AceType::MakeRefPtr<ListItemTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(listItemTheme));

    auto itemNode =
        FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 1, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    itemNode->AttachContext(AceType::RawPtr(pipeline));

    auto renderContext = itemNode->GetRenderContext();
    Color originalColor(Color::WHITE);
    renderContext->UpdateBackgroundColor(originalColor);

    MouseInfo info;
    info.SetAction(MouseAction::RELEASE);
    ContainerModalPatternEnhance::OnMenuItemClickEvent(itemNode, info);

    auto bgColor = renderContext->GetBackgroundColor();
    EXPECT_TRUE(bgColor.has_value());
    EXPECT_EQ(bgColor.value(), originalColor);
}

/**
 * @tc.name: OnMenuItemHoverEvent_HoverTrue
 * @tc.desc: Test OnMenuItemHoverEvent updates background color when hovered
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, OnMenuItemHoverEvent_HoverTrue, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(themeManager);
    auto listItemTheme = AceType::MakeRefPtr<ListItemTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(listItemTheme));

    auto itemNode =
        FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 1, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    itemNode->AttachContext(AceType::RawPtr(pipeline));

    ContainerModalPatternEnhance::OnMenuItemHoverEvent(itemNode, true);
    auto renderContext = itemNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto bgColor = renderContext->GetBackgroundColor();
    EXPECT_TRUE(bgColor.has_value());
}

/**
 * @tc.name: OnMenuItemHoverEvent_HoverFalse
 * @tc.desc: Test OnMenuItemHoverEvent resets background color when not hovered
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, OnMenuItemHoverEvent_HoverFalse, TestSize.Level1)
{
    constexpr uint32_t COLOR_WHITE_VALUE = 0xffffff;
    auto itemNode =
        FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 1, AceType::MakeRefPtr<LinearLayoutPattern>(false));

    ContainerModalPatternEnhance::OnMenuItemHoverEvent(itemNode, false);
    auto renderContext = itemNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto bgColor = renderContext->GetBackgroundColor();
    EXPECT_TRUE(bgColor.has_value());
    EXPECT_EQ(bgColor.value(), Color(COLOR_WHITE_VALUE));
}

/**
 * @tc.name: SetTapGestureEvent_AddsGesture
 * @tc.desc: Test SetTapGestureEvent adds a tap gesture to the node
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, SetTapGestureEvent_AddsGesture, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    containerModalNode->AddChild(
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true)));
    containerModalPatternEnhance->AttachToFrameNode(containerModalNode);

    auto windowMode = WindowMode::WINDOW_MODE_FULLSCREEN;
    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    windowManager->SetWindowGetModeCallBack([windowMode]() { return windowMode; });
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_ = windowManager;

    auto targetNode =
        FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 3, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    containerModalPatternEnhance->SetTapGestureEvent(targetNode);

    auto eventHub = targetNode->GetOrCreateGestureEventHub();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_GT(eventHub->gestures_.size(), static_cast<size_t>(0));
}

/**
 * @tc.name: ClearTapGestureEvent_ClearsGesture
 * @tc.desc: Test ClearTapGestureEvent clears gestures from the node
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ClearTapGestureEvent_ClearsGesture, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    containerModalNode->AddChild(
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true)));
    containerModalPatternEnhance->AttachToFrameNode(containerModalNode);

    auto targetNode =
        FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 3, AceType::MakeRefPtr<LinearLayoutPattern>(false));

    containerModalPatternEnhance->ClearTapGestureEvent(targetNode);

    auto eventHub = targetNode->GetOrCreateGestureEventHub();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_EQ(eventHub->gestures_.size(), static_cast<size_t>(0));
}

/**
 * @tc.name: EnablePanEventOnNode_NullNode
 * @tc.desc: Test EnablePanEventOnNode does nothing when node is null
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, EnablePanEventOnNode_NullNode, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    RefPtr<FrameNode> nullNode = nullptr;
    containerModalPatternEnhance->EnablePanEventOnNode(nullNode, true, "testRow");
    // Should not crash
    EXPECT_TRUE(true);
}

/**
 * @tc.name: EnablePanEventOnNode_Enable
 * @tc.desc: Test EnablePanEventOnNode adds pan event when enabled
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, EnablePanEventOnNode_Enable, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    auto windowMode = WindowMode::WINDOW_MODE_FULLSCREEN;
    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    windowManager->SetWindowGetModeCallBack([windowMode]() { return windowMode; });
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_ = windowManager;

    auto targetNode =
        FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 1, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    containerModalPatternEnhance->EnablePanEventOnNode(targetNode, true, "testRow");
    EXPECT_NE(containerModalPatternEnhance->panEvent_, nullptr);
}

/**
 * @tc.name: EnableTapGestureOnNode_NullNode
 * @tc.desc: Test EnableTapGestureOnNode does nothing when node is null
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, EnableTapGestureOnNode_NullNode, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    RefPtr<FrameNode> nullNode = nullptr;
    containerModalPatternEnhance->EnableTapGestureOnNode(nullNode, true, "testRow");
    EXPECT_TRUE(true);
}

/**
 * @tc.name: EnableTapGestureOnNode_Enable
 * @tc.desc: Test EnableTapGestureOnNode adds tap gesture when enabled
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, EnableTapGestureOnNode_Enable, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    containerModalNode->AddChild(
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true)));
    containerModalPatternEnhance->AttachToFrameNode(containerModalNode);

    auto windowMode = WindowMode::WINDOW_MODE_FULLSCREEN;
    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    windowManager->SetWindowGetModeCallBack([windowMode]() { return windowMode; });
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_ = windowManager;

    auto targetNode =
        FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 3, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    containerModalPatternEnhance->EnableTapGestureOnNode(targetNode, true, "testRow");

    auto eventHub = targetNode->GetOrCreateGestureEventHub();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_GT(eventHub->gestures_.size(), static_cast<size_t>(0));
}

/**
 * @tc.name: EnableTapGestureOnNode_Disable
 * @tc.desc: Test EnableTapGestureOnNode clears tap gesture when disabled
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, EnableTapGestureOnNode_Disable, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    containerModalNode->AddChild(
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true)));
    containerModalPatternEnhance->AttachToFrameNode(containerModalNode);

    auto windowMode = WindowMode::WINDOW_MODE_FULLSCREEN;
    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    windowManager->SetWindowGetModeCallBack([windowMode]() { return windowMode; });
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_ = windowManager;

    auto targetNode =
        FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 3, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    containerModalPatternEnhance->EnableTapGestureOnNode(targetNode, true, "testRow");

    containerModalPatternEnhance->EnableTapGestureOnNode(targetNode, false, "testRow");
    auto eventHub = targetNode->GetOrCreateGestureEventHub();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_EQ(eventHub->gestures_.size(), static_cast<size_t>(0));
}

/**
 * @tc.name: GetFloatingTitleVisible_NullNode
 * @tc.desc: Test GetFloatingTitleVisible returns false when node is null
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, GetFloatingTitleVisible_NullNode, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    auto result = containerModalPatternEnhance->GetFloatingTitleVisible();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GetFloatingTitleVisible_Visible
 * @tc.desc: Test GetFloatingTitleVisible returns true when floating title is visible
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, GetFloatingTitleVisible_Visible, TestSize.Level1)
{
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto column = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    containerModalNode->AddChild(column);
    auto floatingTitleRow =
        FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 3, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    containerModalNode->AddChild(floatingTitleRow);
    floatingTitleRow->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);

    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    auto result = containerPattern->GetFloatingTitleVisible();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GetFloatingTitleVisible_Gone
 * @tc.desc: Test GetFloatingTitleVisible returns false when floating title is gone
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, GetFloatingTitleVisible_Gone, TestSize.Level1)
{
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto column = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    containerModalNode->AddChild(column);
    auto floatingTitleRow =
        FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 3, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    containerModalNode->AddChild(floatingTitleRow);
    floatingTitleRow->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);

    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    auto result = containerPattern->GetFloatingTitleVisible();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GetCustomTitleVisible_NullNode
 * @tc.desc: Test GetCustomTitleVisible returns false when node is null
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, GetCustomTitleVisible_NullNode, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    auto result = containerModalPatternEnhance->GetCustomTitleVisible();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GetCustomTitleVisible_Visible
 * @tc.desc: Test GetCustomTitleVisible returns true when custom title is visible
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, GetCustomTitleVisible_Visible, TestSize.Level1)
{
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto column = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    containerModalNode->AddChild(column);
    auto customTitleRow =
        FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 3, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    column->AddChild(customTitleRow);
    customTitleRow->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);

    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    auto result = containerPattern->GetCustomTitleVisible();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GetControlButtonVisible_NullNode
 * @tc.desc: Test GetControlButtonVisible returns false when node is null
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, GetControlButtonVisible_NullNode, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    auto result = containerModalPatternEnhance->GetControlButtonVisible();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GetControlButtonVisible_Visible
 * @tc.desc: Test GetControlButtonVisible returns true when control buttons are visible
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, GetControlButtonVisible_Visible, TestSize.Level1)
{
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto column = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    containerModalNode->AddChild(column);
    auto controlButtonRow =
        FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    containerModalNode->AddChild(controlButtonRow);
    controlButtonRow->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);

    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    auto result = containerPattern->GetControlButtonVisible();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ShowMaxMenu_NullTargetNode
 * @tc.desc: Test ShowMaxMenu returns null when target node is null
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ShowMaxMenu_NullTargetNode, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    auto result = containerModalPatternEnhance->ShowMaxMenu(nullptr);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: ShowMaxMenu_SplitDisabled
 * @tc.desc: Test ShowMaxMenu returns null when enableSplit_ is false
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ShowMaxMenu_SplitDisabled, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    containerModalPatternEnhance->enableSplit_ = false;

    auto targetNode =
        FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 1, AceType::MakeRefPtr<ButtonPattern>());
    auto result = containerModalPatternEnhance->ShowMaxMenu(targetNode);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: GetTitleItemByIndex_ValidIndex
 * @tc.desc: Test GetTitleItemByIndex returns child at given index
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, GetTitleItemByIndex_ValidIndex, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    auto controlButtonsNode =
        FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 1, AceType::MakeRefPtr<ButtonPattern>());
    auto child1 =
        FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, AceType::MakeRefPtr<TextPattern>());
    auto child2 =
        FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 3, AceType::MakeRefPtr<TextPattern>());
    controlButtonsNode->AddChild(child1);
    controlButtonsNode->AddChild(child2);

    auto result = containerModalPatternEnhance->GetTitleItemByIndex(controlButtonsNode, 1);
    EXPECT_EQ(result, child2);
}

/**
 * @tc.name: ChangeControlButtons_Focus
 * @tc.desc: Test ChangeControlButtons fires focused callback when isFocus is true
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ChangeControlButtons_Focus, TestSize.Level1)
{
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto column = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    containerModalNode->AddChild(column);
    auto controlButtonRow =
        FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    containerModalNode->AddChild(controlButtonRow);
    auto customButtonNode = CustomTitleNode::CreateCustomTitleNode(-1, "");
    controlButtonRow->AddChild(customButtonNode);

    bool isFocusCalled = false;
    customButtonNode->SetOnWindowFocusedCallback([&isFocusCalled]() { isFocusCalled = true; });

    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    containerPattern->ChangeControlButtons(true);
    EXPECT_TRUE(isFocusCalled);
}

/**
 * @tc.name: ChangeControlButtons_Unfocus
 * @tc.desc: Test ChangeControlButtons fires unfocused callback when isFocus is false
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ChangeControlButtons_Unfocus, TestSize.Level1)
{
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto column = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    containerModalNode->AddChild(column);
    auto controlButtonRow =
        FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    containerModalNode->AddChild(controlButtonRow);
    auto customButtonNode = CustomTitleNode::CreateCustomTitleNode(-1, "");
    controlButtonRow->AddChild(customButtonNode);

    bool isUnfocusCalled = false;
    customButtonNode->SetOnWindowUnfocusedCallback([&isUnfocusCalled]() { isUnfocusCalled = true; });

    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    containerPattern->ChangeControlButtons(false);
    EXPECT_TRUE(isUnfocusCalled);
}

/**
 * @tc.name: SetCloseButtonStatus_Enabled
 * @tc.desc: Test SetCloseButtonStatus fires callback with enabled=true
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, SetCloseButtonStatus_Enabled, TestSize.Level1)
{
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto column = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    containerModalNode->AddChild(column);
    auto controlButtonRow =
        FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    containerModalNode->AddChild(controlButtonRow);
    auto customButtonNode = CustomTitleNode::CreateCustomTitleNode(-1, "");
    controlButtonRow->AddChild(customButtonNode);

    std::string receivedEvent;
    std::string receivedParam;
    auto callback = [&receivedEvent, &receivedParam](const std::string& eventName, const std::string& param) {
        receivedEvent = eventName;
        receivedParam = param;
    };
    customButtonNode->SetCustomCallback(callback);

    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    containerPattern->SetCloseButtonStatus(true);
    EXPECT_EQ(receivedEvent, "arkui_close_status");
    EXPECT_EQ(receivedParam, "true");
}

/**
 * @tc.name: SetCloseButtonStatus_Disabled
 * @tc.desc: Test SetCloseButtonStatus fires callback with enabled=false
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, SetCloseButtonStatus_Disabled, TestSize.Level1)
{
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto column = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    containerModalNode->AddChild(column);
    auto controlButtonRow =
        FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    containerModalNode->AddChild(controlButtonRow);
    auto customButtonNode = CustomTitleNode::CreateCustomTitleNode(-1, "");
    controlButtonRow->AddChild(customButtonNode);

    std::string receivedParam;
    auto callback = [&receivedParam](const std::string& eventName, const std::string& param) {
        receivedParam = param;
    };
    customButtonNode->SetCustomCallback(callback);

    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    containerPattern->SetCloseButtonStatus(false);
    EXPECT_EQ(receivedParam, "false");
}

/**
 * @tc.name: SetMaximizeIconIsRecover_FullscreenMode
 * @tc.desc: Test SetMaximizeIconIsRecover fires callback with true when window is fullscreen
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, SetMaximizeIconIsRecover_FullscreenMode, TestSize.Level1)
{
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto column = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    containerModalNode->AddChild(column);
    auto controlButtonRow =
        FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    containerModalNode->AddChild(controlButtonRow);
    auto customButtonNode = CustomTitleNode::CreateCustomTitleNode(-1, "");
    controlButtonRow->AddChild(customButtonNode);

    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    auto windowMode = WindowMode::WINDOW_MODE_FULLSCREEN;
    windowManager->SetWindowGetModeCallBack([windowMode]() { return windowMode; });
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_ = windowManager;

    std::string receivedParam;
    auto callback = [&receivedParam](const std::string& eventName, const std::string& param) {
        receivedParam = param;
    };
    customButtonNode->SetCustomCallback(callback);

    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    containerPattern->SetMaximizeIconIsRecover();
    EXPECT_EQ(receivedParam, "true");
}

/**
 * @tc.name: SetMaximizeIconIsRecover_FloatingMode
 * @tc.desc: Test SetMaximizeIconIsRecover fires callback with false when window is floating
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, SetMaximizeIconIsRecover_FloatingMode, TestSize.Level1)
{
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto column = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    containerModalNode->AddChild(column);
    auto controlButtonRow =
        FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    containerModalNode->AddChild(controlButtonRow);
    auto customButtonNode = CustomTitleNode::CreateCustomTitleNode(-1, "");
    controlButtonRow->AddChild(customButtonNode);

    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    auto windowMode = WindowMode::WINDOW_MODE_FLOATING;
    windowManager->SetWindowGetModeCallBack([windowMode]() { return windowMode; });
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_ = windowManager;

    std::string receivedParam;
    auto callback = [&receivedParam](const std::string& eventName, const std::string& param) {
        receivedParam = param;
    };
    customButtonNode->SetCustomCallback(callback);

    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    containerPattern->SetMaximizeIconIsRecover();
    EXPECT_EQ(receivedParam, "false");
}

/**
 * @tc.name: AddButtonsRectChangeListener_ReturnsId
 * @tc.desc: Test AddButtonsRectChangeListener returns a non-zero listener id
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, AddButtonsRectChangeListener_ReturnsId, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    auto callback = [](const RectF&, const RectF&) {};
    auto id1 = containerModalPatternEnhance->AddButtonsRectChangeListener(std::move(callback));
    EXPECT_GT(id1, 0);

    auto id2 = containerModalPatternEnhance->AddButtonsRectChangeListener([](const RectF&, const RectF&) {});
    EXPECT_GT(id2, id1);
}

/**
 * @tc.name: RemoveButtonsRectChangeListener_ExistingId
 * @tc.desc: Test RemoveButtonsRectChangeListener removes existing listener
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, RemoveButtonsRectChangeListener_ExistingId, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    bool callbackTriggered = false;
    auto id = containerModalPatternEnhance->AddButtonsRectChangeListener(
        [&callbackTriggered](const RectF&, const RectF&) { callbackTriggered = true; });

    containerModalPatternEnhance->RemoveButtonsRectChangeListener(id);

    RectF r1, r2;
    containerModalPatternEnhance->NotifyButtonsRectChange(r1, r2);
    EXPECT_FALSE(callbackTriggered);
}

/**
 * @tc.name: RemoveButtonsRectChangeListener_NonExistingId
 * @tc.desc: Test RemoveButtonsRectChangeListener does not crash with non-existing id
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, RemoveButtonsRectChangeListener_NonExistingId, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    containerModalPatternEnhance->RemoveButtonsRectChangeListener(99999);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetColorConfigurationUpdate_LightMode
 * @tc.desc: Test SetColorConfigurationUpdate fires callback with light mode
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, SetColorConfigurationUpdate_LightMode, TestSize.Level1)
{
    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto column = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    containerModalNode->AddChild(column);
    auto controlButtonRow =
        FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    containerModalNode->AddChild(controlButtonRow);
    auto customButtonNode = CustomTitleNode::CreateCustomTitleNode(-1, "");
    controlButtonRow->AddChild(customButtonNode);

    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->colorMode_ = ColorMode::LIGHT;

    std::string receivedParam;
    auto callback = [&receivedParam](const std::string& eventName, const std::string& param) {
        receivedParam = param;
    };
    customButtonNode->SetCustomCallback(callback);

    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    containerPattern->SetColorConfigurationUpdate();
    EXPECT_EQ(receivedParam, "false");
}

/**
 * @tc.name: AddPointLight_NoOp
 * @tc.desc: Test AddPointLight does not crash
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, AddPointLight_NoOp, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    containerModalPatternEnhance->AddPointLight();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: InitButtonsLayoutProperty_NoOp
 * @tc.desc: Test InitButtonsLayoutProperty does not crash
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, InitButtonsLayoutProperty_NoOp, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    containerModalPatternEnhance->InitButtonsLayoutProperty();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ResetHoverTimer_ResetsState
 * @tc.desc: Test ResetHoverTimer sets isMenuPending_ to false
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ResetHoverTimer_ResetsState, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    containerModalPatternEnhance->isMenuPending_ = true;
    containerModalPatternEnhance->ResetHoverTimer();
    EXPECT_FALSE(containerModalPatternEnhance->isMenuPending_);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap_ReturnsFalse
 * @tc.desc: Test OnDirtyLayoutWrapperSwap returns false
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, OnDirtyLayoutWrapperSwap_ReturnsFalse, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    DirtySwapConfig config;
    auto result = containerModalPatternEnhance->OnDirtyLayoutWrapperSwap(nullptr, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnWindowForceUnfocused_WhenFocused
 * @tc.desc: Test OnWindowForceUnfocused does nothing when window is focused
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, OnWindowForceUnfocused_WhenFocused, TestSize.Level1)
{
    auto containerModalPatternEnhance = AceType::MakeRefPtr<ContainerModalPatternEnhance>();
    containerModalPatternEnhance->isFocus_ = true;
    containerModalPatternEnhance->isHoveredMenu_ = true;
    containerModalPatternEnhance->OnWindowForceUnfocused();
    EXPECT_TRUE(containerModalPatternEnhance->isHoveredMenu_);
}
} // namespace OHOS::Ace::NG