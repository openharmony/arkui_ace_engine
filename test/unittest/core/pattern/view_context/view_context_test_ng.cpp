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
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/subwindow/subwindow_manager.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/view_context/view_context_model_ng.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
class ViewContextTestNG : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void ViewContextTestNG::SetUpTestCase()
{
    MockContainer::SetUp();
    MockPipelineContext::SetUp();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockSubwindow::SetUp();
}

void ViewContextTestNG::TearDownTestCase()
{
    MockContainer::TearDown();
    MockPipelineContext::TearDown();
    // Note that MockSubwindow cannot be held by SubwindowManager and needs to be released
    SubwindowManager::GetInstance()->subwindowMap_.clear();
    SubwindowManager::GetInstance()->instanceSubwindowMap_.clear();
    MockSubwindow::TearDown();
}

/**
 * @tc.name: closeAnimation001
 * @tc.desc: Test function closeAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextTestNG, closeAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create viewContext.
     */
    ViewContextModelNG viewContext;
    RefPtr<FrameNode> node = FrameNode::CreateCommonNode("node", 1, true, AceType::MakeRefPtr<Pattern>());
    auto funcVoid = []() -> void {};
    auto funcFloat = [](const float) -> void {};
    auto onWillDismiss = [](int32_t info) -> void {};
    NG::SheetStyle sheetStyle;
    sheetStyle.isTitleBuilder = false;

    /**
     * @tc.steps: step2. call the function closeAnimation.
     */
    int32_t ret = viewContext.OpenBindSheet(node, funcVoid, sheetStyle, funcVoid, funcVoid, funcVoid, onWillDismiss,
        funcVoid, funcVoid, funcFloat, funcFloat, funcFloat, funcFloat, funcVoid, 1, 1);
    EXPECT_EQ(ret, 0);
    AnimationOption option = AnimationOption();
    option.SetDuration(10); // 10 is ths duration of animation.
    viewContext.closeAnimation(option, true);
    EXPECT_EQ(NG::ViewStackProcessor::GetInstance()->GetImplicitAnimationOption().GetDuration(), 10);
}

/**
 * @tc.name: closeAnimation002
 * @tc.desc: Test function closeAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextTestNG, closeAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create viewContext.
     */
    ViewContextModelNG viewContext;
    RefPtr<FrameNode> node = FrameNode::CreateCommonNode("node", 1, true, AceType::MakeRefPtr<Pattern>());
    NG::SheetStyle sheetStyle;
    sheetStyle.isTitleBuilder = false;
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, 1,
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", nullptr));
    ASSERT_NE(sheetNode, nullptr);
    auto scroll = FrameNode::CreateFrameNode(
        V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scroll, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(sheetStyle);
    scroll->MountToParent(sheetNode);
    node->MountToParent(scroll);
    /**
     * @tc.steps: step2. call the function closeAnimation.
     */
    int32_t ret = viewContext.UpdateBindSheet(node, sheetStyle, true, 1);
    EXPECT_EQ(ret, 0);
    AnimationOption option = AnimationOption();
    option.SetDuration(10); // 10 is ths duration of animation.
    viewContext.closeAnimation(option, false);
    EXPECT_EQ(NG::ViewStackProcessor::GetInstance()->GetImplicitAnimationOption().GetDuration(), 10);
}

/**
 * @tc.name: openAnimation001
 * @tc.desc: Test function openAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextTestNG, openAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create viewContext.
     */
    ViewContextModelNG viewContext;
    RefPtr<FrameNode> node = FrameNode::CreateCommonNode("node", 1, true, AceType::MakeRefPtr<Pattern>());
    NG::SheetStyle sheetStyle;
    sheetStyle.isTitleBuilder = false;
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, 1,
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", nullptr));
    ASSERT_NE(sheetNode, nullptr);
    auto scroll = FrameNode::CreateFrameNode(
        V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scroll, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(sheetStyle);
    scroll->MountToParent(sheetNode);
    node->MountToParent(scroll);
    /**
     * @tc.steps: step2. call the function closeAnimation.
     */
    int32_t ret = viewContext.CloseBindSheet(node, 1);
    EXPECT_EQ(ret, 0);
    AnimationOption option = AnimationOption();
    option.SetDuration(10); // 10 is ths duration of animation.
    viewContext.openAnimation(option);
    EXPECT_EQ(NG::ViewStackProcessor::GetInstance()->GetImplicitAnimationOption().GetDuration(), 10);
}

/**
 * @tc.name: BindSheet
 * @tc.desc: Test function BindSheet when showInSubwindow is true.
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextTestNG, BindSheet, TestSize.Level1)
{
    auto subwindow = MockSubwindow::GetSubwindow();
    ASSERT_NE(subwindow, nullptr);
    EXPECT_CALL(*subwindow, CheckHostWindowStatus()).WillRepeatedly(Return(true));
    EXPECT_CALL(*subwindow, InitContainer()).Times(AtLeast(1));
    subwindow->isRosenWindowCreate_ = true;
    /**
     * @tc.steps: step1. create viewContext.
     */
    ViewContextModelNG viewContext;
    RefPtr<FrameNode> node = FrameNode::CreateCommonNode("node", 1, true, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(node, nullptr);
    auto funcVoid = []() -> void {};
    auto funcFloat = [](const float) -> void {};
    auto onWillDismiss = [](int32_t info) -> void {};
    NG::SheetStyle sheetStyle;
    sheetStyle.isTitleBuilder = false;
    sheetStyle.showInSubWindow = true;
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, 1,
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", nullptr));
    ASSERT_NE(sheetNode, nullptr);
    auto scroll = FrameNode::CreateFrameNode(
        V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scroll, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(sheetStyle);
    scroll->MountToParent(sheetNode);
    node->MountToParent(scroll);
    /**
     * @tc.steps: step2. call the function BindSheet when subwindow is null.
     */
    int32_t ret01 = viewContext.UpdateBindSheet(node, sheetStyle, true, 1);
    EXPECT_EQ(ret01, ERROR_CODE_BIND_SHEET_CONTENT_NOT_FOUND);
    int32_t ret02 = viewContext.CloseBindSheet(node, 1);
    EXPECT_EQ(ret02, ERROR_CODE_BIND_SHEET_CONTENT_NOT_FOUND);
    /**
     * @tc.steps: step3. call the function OpenBindSheet.
     */
    int32_t ret11 = viewContext.OpenBindSheet(node, funcVoid, sheetStyle, funcVoid, funcVoid, funcVoid, onWillDismiss,
        funcVoid, funcVoid, funcFloat, funcFloat, funcFloat, funcFloat, funcVoid, 1, 1);
    EXPECT_EQ(ret11, 0);
    /**
     * @tc.steps: step4. call the function UpdateBindSheet.
     */
    NG::SheetStyle newSheetStyle;
    newSheetStyle.enableFloatingDragBar = true;
    int32_t ret12 = viewContext.UpdateBindSheet(node, newSheetStyle, true, 1);
    EXPECT_EQ(ret12, 0);
    /**
     * @tc.steps: step5. call the function CloseBindSheet.
     */
    int32_t ret13 = viewContext.CloseBindSheet(node, 1);
    EXPECT_EQ(ret13, 0);
}
} // namespace OHOS::Ace::NG
