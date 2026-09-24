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

#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"

#include "core/components_ng/pattern/rich_editor/rich_editor_model_static.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "test/mock/frameworks/core/components_ng/render/mock_paragraph.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/common/mock_resource_adapter_v2.h"
#include "test/unittest/core/pattern/test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float TEST_CARET_WIDTH = 5.0f;
constexpr float DEFAULT_CARET_WIDTH = 2.0f;
} // namespace

class RichEditorCapiModifierTestNg : public TestNG {};

/**
 * @tc.name: RichEditorCaretStyleTest
 * @tc.desc: Check the functionality of Set/Get/Reset RichEditorCaretStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCapiModifierTestNg, RichEditorCaretStyleTest, TestSize.Level1)
{
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);

    auto* rawNode = AceType::RawPtr(frameNode);
    RichEditorModelNG::SetRichEditorCaretStyle(rawNode, Dimension(TEST_CARET_WIDTH, DimensionUnit::VP));
    EXPECT_FLOAT_EQ(pattern->GetCustomCaretWidth().Value(), TEST_CARET_WIDTH);
    auto caretStyle = RichEditorModelNG::GetRichEditorCaretStyle(rawNode);
    EXPECT_FLOAT_EQ(caretStyle.GetNativeValue(DimensionUnit::VP), TEST_CARET_WIDTH);
    // Runtime: caret width takes effect as px-converted value consumed by paint/layout
    EXPECT_FLOAT_EQ(pattern->GetCaretWidth(), Dimension(TEST_CARET_WIDTH, DimensionUnit::VP).ConvertToPx());

    RichEditorModelNG::ResetRichEditorCaretStyle(rawNode);
    EXPECT_FLOAT_EQ(pattern->GetCustomCaretWidth().Value(), DEFAULT_CARET_WIDTH);
    // Runtime: reset restores default caret width in px
    EXPECT_FLOAT_EQ(pattern->GetCaretWidth(), Dimension(DEFAULT_CARET_WIDTH, DimensionUnit::VP).ConvertToPx());
}

/**
 * @tc.name: RichEditorSelectAllTest
 * @tc.desc: Check the functionality of Set/Get/Reset RichEditorSelectAll
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCapiModifierTestNg, RichEditorSelectAllTest, TestSize.Level1)
{
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);

    RichEditorModelNG::SetRichEditorSelectAll(AceType::RawPtr(frameNode), true);
    EXPECT_TRUE(pattern->GetSelectAll());
    EXPECT_TRUE(RichEditorModelNG::GetRichEditorSelectAll(AceType::RawPtr(frameNode)));
    // Runtime: seed non-empty content so ShouldSelectAllOnInit can reach the true branch
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->position = 5;
    pattern->spans_.push_back(spanItem);
    EXPECT_TRUE(pattern->ShouldSelectAllOnInit(FocusReason::DEFAULT));
    // Runtime: WINDOW_FOCUS suppresses select-all-on-init even when flag is on
    EXPECT_FALSE(pattern->ShouldSelectAllOnInit(FocusReason::WINDOW_FOCUS));

    RichEditorModelNG::ResetRichEditorSelectAll(AceType::RawPtr(frameNode));
    EXPECT_FALSE(pattern->GetSelectAll());
    // Runtime: reset disables select-all-on-init regardless of focus reason
    EXPECT_FALSE(pattern->ShouldSelectAllOnInit(FocusReason::DEFAULT));
}

/**
 * @tc.name: RichEditorBlurOnSubmitTest
 * @tc.desc: Check the functionality of Set/Get/Reset RichEditorBlurOnSubmit
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCapiModifierTestNg, RichEditorBlurOnSubmitTest, TestSize.Level1)
{
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);

    RichEditorModelNG::SetRichEditorBlurOnSubmit(AceType::RawPtr(frameNode), true);
    EXPECT_TRUE(pattern->GetBlurOnSubmit());
    EXPECT_TRUE(RichEditorModelNG::GetRichEditorBlurOnSubmit(AceType::RawPtr(frameNode)));
    // Runtime: blurOnSubmit=true skips InsertValue on NEW_LINE, content length unchanged
    pattern->isEditing_ = true;
    pattern->isSpanStringMode_ = false;
    pattern->caretPosition_ = 0;
    auto initSpan = AceType::MakeRefPtr<SpanItem>();
    initSpan->position = 3;
    pattern->spans_.push_back(initSpan);
    auto lengthBefore = pattern->GetTextContentLength();
    pattern->PerformAction(TextInputAction::NEW_LINE, false);
    EXPECT_EQ(pattern->GetTextContentLength(), lengthBefore);

    RichEditorModelNG::ResetRichEditorBlurOnSubmit(AceType::RawPtr(frameNode));
    EXPECT_FALSE(pattern->GetBlurOnSubmit());
    // Runtime: blurOnSubmit=false triggers InsertValue on NEW_LINE, content length changes
    pattern->isEditing_ = true;
    pattern->caretPosition_ = pattern->GetTextContentLength();
    pattern->PerformAction(TextInputAction::NEW_LINE, false);
    EXPECT_NE(pattern->GetTextContentLength(), lengthBefore);
}

/**
 * @tc.name: GetRichEditorContentRectTest
 * @tc.desc: Check the functionality of GetRichEditorContentRect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCapiModifierTestNg, GetRichEditorContentRectTest, TestSize.Level1)
{
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    ASSERT_NE(frameNode, nullptr);

    float values[4] = { -1.0f, -1.0f, -1.0f, -1.0f };
    RichEditorModelNG::GetRichEditorContentRect(AceType::RawPtr(frameNode), values, 4);
    // Runtime: default content rect (no layout yet) is all-zero, not the -1 sentinel
    EXPECT_FLOAT_EQ(values[0], 0.0f);
    EXPECT_FLOAT_EQ(values[1], 0.0f);
    EXPECT_FLOAT_EQ(values[2], 0.0f);
    EXPECT_FLOAT_EQ(values[3], 0.0f);
}

/**
 * @tc.name: RichEditorSelectionMenuHiddenTest
 * @tc.desc: Check the functionality of Set/Get/Reset RichEditorSelectionMenuHidden
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCapiModifierTestNg, RichEditorSelectionMenuHiddenTest, TestSize.Level1)
{
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);

    RichEditorModelNG::SetRichEditorSelectionMenuHidden(AceType::RawPtr(frameNode), true);
    EXPECT_TRUE(pattern->GetSelectionMenuHidden());
    EXPECT_TRUE(RichEditorModelNG::GetRichEditorSelectionMenuHidden(AceType::RawPtr(frameNode)));
    // Runtime: hidden=true forces menuIsShow=false in OnUpdateMenuInfo (IsShowMenu defaults true)
    SelectMenuInfo hiddenMenuInfo;
    pattern->selectOverlay_->OnUpdateMenuInfo(hiddenMenuInfo, DIRTY_ALL_MENU_ITEM);
    EXPECT_FALSE(hiddenMenuInfo.menuIsShow);

    RichEditorModelNG::ResetRichEditorSelectionMenuHidden(AceType::RawPtr(frameNode));
    EXPECT_FALSE(pattern->GetSelectionMenuHidden());
    // Runtime: hidden=false lets IsShowMenu() gate visibility (default true -> menu shown)
    SelectMenuInfo shownMenuInfo;
    pattern->selectOverlay_->OnUpdateMenuInfo(shownMenuInfo, DIRTY_ALL_MENU_ITEM);
    EXPECT_TRUE(shownMenuInfo.menuIsShow);
}

/**
 * @tc.name: RichEditorEnableSkipPreviewLongPressTest
 * @tc.desc: Check the functionality of Set/Get/Reset RichEditorEnableSkipPreviewLongPress
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCapiModifierTestNg, RichEditorEnableSkipPreviewLongPressTest, TestSize.Level1)
{
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);

    RichEditorModelNG::SetRichEditorEnableSkipPreviewLongPress(AceType::RawPtr(frameNode), true);
    EXPECT_TRUE(pattern->GetEnableSkipPreviewLongPress());
    EXPECT_TRUE(RichEditorModelNG::GetRichEditorEnableSkipPreviewLongPress(AceType::RawPtr(frameNode)));
    // Runtime: skip-preview branch — long press reset, enters editing directly when not editing
    pattern->isLongPress_ = true;
    pattern->isEditing_ = false;
    pattern->SetLongPressFlags();
    EXPECT_FALSE(pattern->isLongPress_);
    EXPECT_FALSE(pattern->previewLongPress_);
    EXPECT_TRUE(pattern->editingLongPress_);

    RichEditorModelNG::ResetRichEditorEnableSkipPreviewLongPress(AceType::RawPtr(frameNode));
    EXPECT_FALSE(pattern->GetEnableSkipPreviewLongPress());
    // Runtime: normal branch — keeps long press, flags mirror isEditing_ state
    pattern->isLongPress_ = true;
    pattern->isEditing_ = false;
    pattern->SetLongPressFlags();
    EXPECT_TRUE(pattern->isLongPress_);
    EXPECT_FALSE(pattern->editingLongPress_);
    EXPECT_TRUE(pattern->previewLongPress_);
}
} // namespace OHOS::Ace::NG
