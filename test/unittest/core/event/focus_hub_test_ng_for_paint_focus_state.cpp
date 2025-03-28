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
#include "test/unittest/core/event/focus_hub_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
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
    context->isFocusActive_ = true;

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
    context->isFocusActive_ = true;

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
    context->isFocusActive_ = true;
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
    context->isFocusActive_ = true;
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
} // namespace OHOS::Ace::NG