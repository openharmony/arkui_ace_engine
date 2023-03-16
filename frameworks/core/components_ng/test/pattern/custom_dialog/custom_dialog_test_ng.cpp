/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include <optional>

#include "gtest/gtest.h"

#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#define private public
#define protected public
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#undef private
#undef protected
using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
class CustomDialogTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void CustomDialogTestNg::SetUpTestCase() {}

void CustomDialogTestNg::TearDownTestCase() {}

void CustomDialogTestNg::SetUp()
{
    MockPipelineBase::SetUp();
}

void CustomDialogTestNg::TearDown()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: CustomDialogTestNg001
 * @tc.desc: Verify function CreateDialogNode
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogTestNg, CustomDialogTestNg001, TestSize.Level1)
{
    DialogProperties param;
    param.maskColor = Color::BLACK;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<DialogTheme>()));
    auto result = DialogView::CreateDialogNode(param, nullptr);
    EXPECT_TRUE(result);
    if (result) {
        EXPECT_EQ(result->GetRenderContext()->GetBackgroundColorValue(Color::TRANSPARENT).GetValue(),
            Color::BLACK.GetValue());
    }
}

/**
 * @tc.name: CustomDialogTestNg002
 * @tc.desc: Verify function CreateDialogNode
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogTestNg, CustomDialogTestNg002, TestSize.Level1)
{
    DialogProperties param;
    param.maskColor = Color::BLACK;
    param.type = DialogType::ALERT_DIALOG;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<DialogTheme>()));
    auto result = DialogView::CreateDialogNode(param, nullptr);
    EXPECT_TRUE(result);
    if (result) {
        EXPECT_EQ(result->GetRenderContext()->GetBackgroundColorValue(Color::TRANSPARENT).GetValue(),
            Color::BLACK.GetValue());
    }
}

/**
 * @tc.name: CustomDialogTestNg003
 * @tc.desc: Verify function CreateDialogNode
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogTestNg, CustomDialogTestNg003, TestSize.Level1)
{
    DialogProperties param;
    param.maskColor = Color::BLACK;
    param.type = DialogType::ACTION_SHEET;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<DialogTheme>()));
    auto result = DialogView::CreateDialogNode(param, nullptr);
    EXPECT_TRUE(result);
    if (result) {
        EXPECT_EQ(result->GetRenderContext()->GetBackgroundColorValue(Color::TRANSPARENT).GetValue(),
            Color::BLACK.GetValue());
    }
}

/**
 * @tc.name: CustomDialogTestNg004
 * @tc.desc: Verify function GetCloseAnimation and GetOpenAnimation
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogTestNg, CustomDialogTestNg004, TestSize.Level1)
{
    DialogProperties param;
    AnimationOption animationOption;
    animationOption.SetDelay(10);
    param.openAnimation = animationOption;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<DialogTheme>()));
    auto result = DialogView::CreateDialogNode(param, nullptr);
    EXPECT_TRUE(result);
    if (!result) {
        return;
    }
    auto dialogPattern = result->GetPattern<DialogPattern>();
    EXPECT_TRUE(dialogPattern);
    if (!dialogPattern) {
        return;
    }
    if (dialogPattern->GetOpenAnimation().has_value()) {
        EXPECT_EQ(dialogPattern->GetOpenAnimation().value().GetDelay(), animationOption.GetDelay());
    }

    if (dialogPattern->GetCloseAnimation().has_value()) {
        EXPECT_EQ(dialogPattern->GetCloseAnimation().value().GetDelay(), animationOption.GetDelay());
    }
}

/**
 * @tc.name: CustomDialogTestNg005
 * @tc.desc: Verify function HandleClick
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogTestNg, CustomDialogTestNg005, TestSize.Level1)
{
    GestureEvent info;
    Offset globalLocation(10, 6);
    OffsetF translate(10, 5);
    DialogProperties param;
    param.autoCancel = false;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<DialogTheme>()));
    auto child = FrameNode::GetOrCreateFrameNode(
        V2::CUSTOM_DIALOG_COMPONENT_TAG, 0, []() { return AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr); });
    auto Dialog = DialogView::CreateDialogNode(param, child);
    EXPECT_TRUE(Dialog);
    ASSERT_NE(Dialog, nullptr);
    child->GetGeometryNode()->SetMarginFrameOffset(translate);
    EXPECT_EQ(Dialog->TotalChildCount(), 1);
    auto dialogPattern = Dialog->GetPattern<DialogPattern>();
    EXPECT_TRUE(dialogPattern);
    ASSERT_NE(dialogPattern, nullptr);
    info.SetGlobalLocation(globalLocation);
    dialogPattern->HandleClick(info);
}

/**
 * @tc.name: CustomDialogTestNg006
 * @tc.desc: Verify function HandleClick
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogTestNg, CustomDialogTestNg006, TestSize.Level1)
{
    GestureEvent info;
    Offset globalLocation(10, 6);
    OffsetF translate(10, 5);
    DialogProperties param;
    param.autoCancel = true;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<DialogTheme>()));
    auto child = FrameNode::GetOrCreateFrameNode(
        V2::CUSTOM_DIALOG_COMPONENT_TAG, 0, []() { return AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr); });
    auto Dialog = DialogView::CreateDialogNode(param, child);
    EXPECT_TRUE(Dialog);
    ASSERT_NE(Dialog, nullptr);
    child->GetGeometryNode()->SetMarginFrameOffset(translate);
    EXPECT_EQ(Dialog->TotalChildCount(), 1);
    auto dialogPattern = Dialog->GetPattern<DialogPattern>();
    EXPECT_TRUE(dialogPattern);
    ASSERT_NE(dialogPattern, nullptr);
    info.SetGlobalLocation(globalLocation);
    dialogPattern->HandleClick(info);
}
} // namespace OHOS::Ace::NG
