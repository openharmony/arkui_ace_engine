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
#include "test/unittest/core/event/focus_hub_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
/**
 * @tc.name: PaintFocusState0002
 * @tc.desc: Test the function SwitchFocus.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, PaintFocusState0002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
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
    context->isFocusActive_ = true;
    focusHub->focusType_ = FocusType::NODE;
    eventHub->AddSupportedState(NG::UI_STATE_FOCUSED);
    ASSERT_NE(eventHub->stateStyleMgr_, nullptr);
    EXPECT_TRUE(focusHub->PaintFocusState(false));
    EXPECT_TRUE(focusHub->PaintFocusState(true));

    eventHub->stateStyleMgr_ = nullptr;
    ASSERT_EQ(eventHub->stateStyleMgr_, nullptr);
    context->isFocusActive_ = true;
    FocusBoxStyle styledStyle;
    styledStyle.strokeColor = Color::RED;
    focusHub->box_.SetStyle(styledStyle);
    EXPECT_TRUE(focusHub->IsNeedPaintFocusState());
    focusHub->focusStyleType_ = FocusStyleType::NONE;
    EXPECT_FALSE(focusHub->HasFocusStateStyle());
    EXPECT_FALSE(focusHub->PaintFocusState(false));

    context->isFocusActive_ = true;
    EXPECT_TRUE(focusHub->IsNeedPaintFocusState());
    focusHub->focusStyleType_ = FocusStyleType::FORCE_NONE;
    EXPECT_FALSE(focusHub->HasFocusStateStyle());
    EXPECT_TRUE(focusHub->PaintFocusState(false));
}
} // namespace OHOS::Ace::NG