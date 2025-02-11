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

RefPtr<FrameNode> ContainerModalViewEnhanceTestNg ::CreateContent()
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
    EXPECT_CALL(*subwindow, GetShown()).WillOnce(testing::Return(true));
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
 * @tc.desc: Test EnableContainerModalGesture
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ContainerModalPatternEnhanceTestNg, ContainerModalPatternEnhanceTest022, TestSize.Level1)
{
    CreateContainerModal();

    // EnableContainerModalGesture to false
    pattern_->EnableContainerModalGesture(false);

    // all events are null
    auto floatingTitleRow = GetFloatingTitleRow();
    EXPECT_NE(floatingTitleRow, nullptr);
    auto floatingTitleRowEventHub = floatingTitleRow->GetOrCreateGestureEventHub();
    EXPECT_NE(floatingTitleRowEventHub, nullptr);
    EXPECT_EQ(floatingTitleRowEventHub->IsGestureEmpty(), true);

    auto customTitleRow = GetCustomTitleRow();
    EXPECT_NE(customTitleRow, nullptr);
    auto customTitleRowEventHub = customTitleRow->GetOrCreateGestureEventHub();
    EXPECT_NE(customTitleRowEventHub, nullptr);
    EXPECT_EQ(customTitleRowEventHub->IsGestureEmpty(), true);
    EXPECT_EQ(customTitleRowEventHub->IsPanEventEmpty(), true);

    auto gestureRow = GetGestureRow();
    EXPECT_NE(gestureRow, nullptr);
    auto gestureRowEventHub = gestureRow->GetOrCreateGestureEventHub();
    EXPECT_NE(gestureRowEventHub, nullptr);
    EXPECT_EQ(gestureRowEventHub->IsGestureEmpty(), true);
    EXPECT_EQ(gestureRowEventHub->IsPanEventEmpty(), true);

    // EnableContainerModalGesture to true
    pattern_->EnableContainerModalGesture(true);

    // all events are not null
    auto floatingTitleRow = GetFloatingTitleRow();
    EXPECT_NE(floatingTitleRow, nullptr);
    auto floatingTitleRowEventHub = floatingTitleRow->GetOrCreateGestureEventHub();
    EXPECT_NE(floatingTitleRowEventHub, nullptr);
    EXPECT_EQ(floatingTitleRowEventHub->IsGestureEmpty(), false);

    auto customTitleRow = GetCustomTitleRow();
    EXPECT_NE(customTitleRow, nullptr);
    auto customTitleRowEventHub = customTitleRow->GetOrCreateGestureEventHub();
    EXPECT_NE(customTitleRowEventHub, nullptr);
    EXPECT_EQ(customTitleRowEventHub->IsGestureEmpty(), false);
    EXPECT_EQ(customTitleRowEventHub->IsPanEventEmpty(), false);

    auto gestureRow = GetGestureRow();
    EXPECT_NE(gestureRow, nullptr);
    auto gestureRowEventHub = gestureRow->GetOrCreateGestureEventHub();
    EXPECT_NE(gestureRowEventHub, nullptr);
    EXPECT_EQ(gestureRowEventHub->IsGestureEmpty(), false);
    EXPECT_EQ(gestureRowEventHub->IsPanEventEmpty(), false);
}
} // namespace OHOS::Ace::NG