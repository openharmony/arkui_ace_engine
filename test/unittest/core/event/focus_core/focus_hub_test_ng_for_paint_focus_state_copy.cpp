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
#include <cstdint>
#include "gtest/hwext/gtest-tag.h"
#include "test/unittest/core/event/focus_hub_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
struct HomeOrEndKeyInFocusGroupTestCase {
    int32_t curFocusHub;
    bool focusGroup1;
    bool focusGroup2;
    FocusIntension intension;
    int32_t expect;
};

const vector<HomeOrEndKeyInFocusGroupTestCase> HomeOrEndKeyInFocusGroupTestCase001 {
    { 1, false, false, FocusIntension::HOME, 11 },
    { 1, true, false, FocusIntension::HOME, 11 },
    { 1, false, true, FocusIntension::HOME, 14 },
    { 1, true, true, FocusIntension::HOME, 14 },
    { 1, false, false, FocusIntension::END, 11 },
    { 1, true, false, FocusIntension::END, 13 },
    { 1, false, true, FocusIntension::END, 15 },
    { 1, true, true, FocusIntension::END, 15 },
    { 3, false, false, FocusIntension::HOME, 13 },
    { 3, true, false, FocusIntension::HOME, 11 },
    { 3, false, true, FocusIntension::HOME, 14 },
    { 3, true, true, FocusIntension::HOME, 14 },
    { 3, false, false, FocusIntension::END, 13 },
    { 3, true, false, FocusIntension::END, 13 },
    { 3, false, true, FocusIntension::END, 15 },
    { 3, true, true, FocusIntension::END, 15 },
};

struct ButtonNodes {
    RefPtr<FrameNode> button1;
    RefPtr<FrameNode> button2;
    RefPtr<FrameNode> button3;
};

ButtonNodes CreateTestTreeWithDefaultFocus()
{
    /*--page
        --column1
            --column2
            --button4
             --column3
                --button1
                --button2
                --button3
            --button5
    */
    auto context = MockPipelineContext::GetCurrent();
    auto focusManager = context->GetOrCreateFocusManager();
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, pagePattern);
    pageNode->onMainTree_ = true;
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    context->rootNode_->AddChild(pageNode);
    auto column1 = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto column2 = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto column3 = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    column1->onMainTree_ = true;
    column2->onMainTree_ = true;
    column3->onMainTree_ = true;
    auto columnFocusHub1 = column1->GetOrCreateFocusHub();
    auto columnFocusHub2 = column2->GetOrCreateFocusHub();
    auto columnFocusHub3 = column3->GetOrCreateFocusHub();
    auto buttonNode1 = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 11, AceType::MakeRefPtr<ButtonPattern>());
    auto buttonNode2 = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 12, AceType::MakeRefPtr<ButtonPattern>());
    auto buttonNode3 = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 13, AceType::MakeRefPtr<ButtonPattern>());
    auto buttonNode4 = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 14, AceType::MakeRefPtr<ButtonPattern>());
    auto buttonNode5 = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 15, AceType::MakeRefPtr<ButtonPattern>());
    buttonNode1->onMainTree_ = true;
    buttonNode2->onMainTree_ = true;
    buttonNode3->onMainTree_ = true;
    buttonNode5->onMainTree_ = true;
    buttonNode4->onMainTree_ = true;
    pageNode->AddChild(column1);
    column1->AddChild(column2);
    column2->AddChild(buttonNode4);
    column2->AddChild(column3);
    column3->AddChild(buttonNode1);
    column3->AddChild(buttonNode2);
    column3->AddChild(buttonNode3);
    column2->AddChild(buttonNode5);
    pagePattern->FocusViewShow();
    context->FlushFocusView();
    return { buttonNode1, buttonNode2, buttonNode3 };
}

/**
 * @tc.name: IsLeafFocusScope001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, IsLeafFocusScope001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    focusHub->tabStop_ = true;
    focusHub->isSwitchByEnter_ = true;
    focusHub->focusDepend_ = FocusDependence::SELF;
    auto ret = focusHub->IsLeafFocusScope();
    EXPECT_EQ(ret, false);

    focusHub->tabStop_ = true;
    focusHub->isSwitchByEnter_ = false;
    ret = focusHub->IsLeafFocusScope();
    EXPECT_EQ(ret, true);
}

/**
 * @tc.name: PaintAllFocusState001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, PaintAllFocusState001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    auto frameNode1 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto eventHub1 = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    eventHub1->AttachHost(frameNode1);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    auto focusHub1 = frameNode1->GetOrCreateFocusHub();
    OnPaintFocusStateFunc onPaintFocusCallback;
    std::function<bool()> lambdaFunction = []() {
        return false;
    };
    focusHub->onPaintFocusStateCallback_ = lambdaFunction;
    focusHub->isFocusActiveWhenFocused_ = true;
    EXPECT_FALSE(focusHub->PaintAllFocusState());

    focusHub1->focusStyleType_ = FocusStyleType::INNER_BORDER;
    focusHub1->isFocusActiveWhenFocused_ = true;
    EXPECT_FALSE(focusHub1->PaintAllFocusState());
}

/**
 * @tc.name: PaintAllFocusState074
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, PaintAllFocusState002, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<AppTheme>()));
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto focusManager = context->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);
    focusManager->isFocusActive_ = true;

    focusHub->focusStyleType_ = FocusStyleType::OUTER_BORDER;
    OnPaintFocusStateFunc onPaintFocusCallback;
    focusHub->onPaintFocusStateCallback_ = onPaintFocusCallback;
    FocusBoxStyle focusBoxStyle;
    CalcDimension strokeWidth(100);
    CalcDimension margin(100);
    Color color;

    focusBoxStyle.strokeColor = color;
    focusBoxStyle.strokeWidth = strokeWidth;
    focusBoxStyle.margin = margin;
    focusHub->box_.SetStyle(focusBoxStyle);
    auto ret = focusHub->PaintAllFocusState();
    EXPECT_TRUE(ret);

    FocusBoxStyle focusBoxStyle1;
    focusBoxStyle1.strokeColor = color;
    focusBoxStyle1.margin = margin;
    focusHub->box_.SetStyle(focusBoxStyle1);
    ret = focusHub->PaintAllFocusState();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: PaintAllFocusState003
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, PaintAllFocusState003, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<AppTheme>()));
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto focusManager = context->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);
    focusManager->isFocusActive_ = true;

    focusHub->focusStyleType_ = FocusStyleType::OUTER_BORDER;
    OnPaintFocusStateFunc onPaintFocusCallback;
    focusHub->onPaintFocusStateCallback_ = onPaintFocusCallback;
    FocusBoxStyle focusBoxStyle;
    CalcDimension strokeWidth(100);
    CalcDimension margin(100);
    Color color;

    FocusBoxStyle focusBoxStyle2;
    focusBoxStyle2.strokeColor = color;
    focusBoxStyle2.strokeWidth = strokeWidth;
    focusHub->box_.SetStyle(focusBoxStyle2);
    auto ret = focusHub->PaintAllFocusState();
    EXPECT_TRUE(ret);

    std::function<bool()> lambdaFunction = []() {
        return false;
    };
    focusHub->onPaintFocusStateCallback_ = lambdaFunction;
    FocusBoxStyle focusBoxStyle3;
    focusBoxStyle3.margin = margin;
    focusBoxStyle3.strokeWidth = strokeWidth;
    focusHub->box_.SetStyle(focusBoxStyle3);
    ret = focusHub->PaintAllFocusState();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: PaintInnerFocusState0048
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, PaintInnerFocusState001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<AppTheme>()));
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    auto child = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1,
        AceType::MakeRefPtr<ButtonPattern>());
    auto child2 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1,
        AceType::MakeRefPtr<ButtonPattern>());
    child->GetOrCreateFocusHub();
    child2->GetOrCreateFocusHub();
    frameNode->AddChild(child);
    frameNode->AddChild(child2);
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    FocusBoxStyle focusBoxStyle;
    CalcDimension strokeWidth(100);
    CalcDimension margin(100);
    Color color;
    focusBoxStyle.strokeColor = color;
    focusBoxStyle.strokeWidth = strokeWidth;
    focusBoxStyle.margin = margin;
    focusHub->box_.SetStyle(focusBoxStyle);
    RoundRect focusRectInner;
    auto focusManager = context->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);
    focusManager->isFocusActive_ = true;
    focusHub->focusType_ = FocusType::NODE;
    EXPECT_TRUE(focusHub->PaintInnerFocusState(focusRectInner));

    FocusBoxStyle focusBoxStyle1;
    focusBoxStyle1.strokeColor = color;
    focusBoxStyle1.margin = margin;
    focusHub->box_.SetStyle(focusBoxStyle1);
    EXPECT_TRUE(focusHub->PaintInnerFocusState(focusRectInner));

    FocusBoxStyle focusBoxStyle2;
    focusBoxStyle2.strokeColor = color;
    focusBoxStyle2.strokeWidth = strokeWidth;
    focusHub->box_.SetStyle(focusBoxStyle2);
    EXPECT_TRUE(focusHub->PaintInnerFocusState(focusRectInner));
}
 
/**
 * @tc.name: PaintInnerFocusState0048
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, PaintInnerFocusState002, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<AppTheme>()));
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    auto child = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1,
        AceType::MakeRefPtr<ButtonPattern>());
    auto child2 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1,
        AceType::MakeRefPtr<ButtonPattern>());
    child->GetOrCreateFocusHub();
    child2->GetOrCreateFocusHub();
    frameNode->AddChild(child);
    frameNode->AddChild(child2);
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    FocusBoxStyle focusBoxStyle;
    CalcDimension strokeWidth(100);
    CalcDimension strokeWidth1("100");
    CalcDimension margin(100);
    Color color;
    RoundRect focusRectInner;
    auto focusManager = context->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);
    focusManager->isFocusActive_ = true;
    focusHub->focusType_ = FocusType::NODE;

    FocusBoxStyle focusBoxStyle3;
    focusBoxStyle3.margin = margin;
    focusBoxStyle3.strokeWidth = strokeWidth;
    focusHub->box_.SetStyle(focusBoxStyle3);
    EXPECT_TRUE(focusHub->PaintInnerFocusState(focusRectInner));

    focusBoxStyle.strokeColor = color;
    focusBoxStyle.strokeWidth = strokeWidth1;
    focusBoxStyle.margin = margin;
    focusHub->box_.SetStyle(focusBoxStyle);
    EXPECT_TRUE(focusHub->PaintInnerFocusState(focusRectInner));
}

/**
 * @tc.name: ChangeFocusByHomeorEndTest001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, ChangeFocusByHomeorEndTest001, TestSize.Level1)
{
    ButtonNodes buttonNodes = CreateTestTreeWithDefaultFocus();
    RefPtr<FrameNode> button1 = buttonNodes.button1;
    RefPtr<FrameNode> button3 = buttonNodes.button3;
    EXPECT_NE(button1, nullptr);
    EXPECT_NE(button3, nullptr);
    NonPointerEvent nonPointerEvent;
    FocusEvent event { nonPointerEvent };
    auto buttonFocusHub1 = button1->GetOrCreateFocusHub();
    auto buttonFocusHub3 = button3->GetOrCreateFocusHub();
    auto parent = buttonFocusHub1->GetParentFocusHub();
    auto parent2 = parent->GetParentFocusHub();
    auto parent3 = parent2->GetParentFocusHub();
    auto page = parent3->GetParentFocusHub();
    auto context = MockPipelineContext::GetCurrent();
    auto focusManager = context->GetOrCreateFocusManager();
    focusManager->isFocusActive_ = true;
    for (auto& testcase : HomeOrEndKeyInFocusGroupTestCase001) {
        if (testcase.focusGroup1) {
            parent->SetFocusScopeId("2", true, true);
        }
        if (testcase.focusGroup2) {
            parent2->SetFocusScopeId("3", true, true);
        }
        buttonFocusHub1->RequestFocusImmediately();
        EXPECT_EQ(buttonFocusHub1->IsCurrentFocus(), true);
        context->eventManager_->isTabJustTriggerOnKeyEvent_ = false;
        event.intension = testcase.intension;
        if (testcase.curFocusHub == 3) {
            buttonFocusHub3->RequestFocusImmediately();
            EXPECT_EQ(buttonFocusHub3->IsCurrentFocus(), true);
        }
        page->OnFocusEventScope(event);
        auto currentFocusNode = focusManager->switchingFocus_;
        auto nodeId = currentFocusNode->GetFrameId();
        EXPECT_EQ(nodeId, testcase.expect);
        parent->SetFocusScopeId("", true, true);
        parent2->SetFocusScopeId("", true, true);
    }
}
} // namespace OHOS::Ace::NG