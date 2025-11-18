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

#include "test/unittest/core/pattern/rich_editor/rich_editor_styled_string_common_test_ng.h"
#include "test/mock/core/common/mock_udmf.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_undo_manager.h"
#include "core/components_ng/pattern/rich_editor/style_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class RichEditorStyledStringOneTestNg : public RichEditorStyledStringCommonTestNg {};

/**
 * @tc.name: InsertValueInStyledString002
 * @tc.desc: test InsertValueInStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringOneTestNg, InsertValueInStyledString002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(INIT_VALUE_3);
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->undoManager_ =
        std::make_unique<StyledStringUndoManager>(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->InsertValueInStyledString(PREVIEW_TEXT_VALUE1);
    EXPECT_FALSE(richEditorPattern->textSelector_.IsValid());
}

/**
 * @tc.name: InsertValueInStyledString003
 * @tc.desc: test RichEditorPattern InsertValueInStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringOneTestNg, InsertValueInStyledString003, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto host = richEditorPattern->GetHost();
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    TextSpanOptions options2;
    options2.value = INIT_VALUE_1;
    richEditorController->AddTextSpan(options2);
    focusHub->RequestFocusImmediately();
    richEditorPattern->FireOnSelectionChange(-1, 0);
    richEditorPattern->FireOnSelectionChange(0, -1);
    richEditorPattern->FireOnSelectionChange(-1, -1);
    ASSERT_EQ(richEditorPattern->HasFocus(), true);
}

/**
 * @tc.name: CreatePasteCallback001
 * @tc.desc: test CreatePasteCallback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringOneTestNg, CreatePasteCallback001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipeline = MockPipelineContext::GetCurrent();
    auto clipboard = ClipboardProxy::GetInstance()->GetClipboard(pipeline->GetTaskExecutor());
    richEditorPattern->clipboard_ = clipboard;
    /**
     * @tc.steps: step1. CreatePasteCallback
     */
    auto pasteCallback = richEditorPattern->CreatePasteCallback();
    /**
     * @tc.steps: step2. value from clipBoard
     */
    auto mutableTextStr = CreateTextStyledString(INIT_U16STRING_1);
    auto mutableImageStr = CreateImageStyledString();
    std::vector<uint8_t> data1;
    std::vector<uint8_t> data2;
    mutableTextStr->EncodeTlv(data1);
    mutableImageStr->EncodeTlv(data2);
    std::vector<std::vector<uint8_t>> arrs = { std::move(data1), std::move(data2) };
    string text = UtfUtils::Str16ToStr8(INIT_U16STRING_1);
    bool isMulitiTypeRecord = true;
    /**
     * @tc.steps: step3. test spanStringMode
     */
    richEditorPattern->spans_.clear();
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"");
    richEditorPattern->styledString_->SetSpanWatcher(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    pasteCallback(arrs, text, isMulitiTypeRecord);
    EXPECT_EQ(2, richEditorPattern->spans_.size());
}

/**
 * @tc.name: ProcessStyledString001
 * @tc.desc: test ProcessStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringOneTestNg, ProcessStyledString001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->spans_.push_front(AceType::MakeRefPtr<SpanItem>());

    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->dataDetectorAdapter_->aiDetectInitialized_ = true;
    richEditorPattern->ProcessStyledString();

    richEditorPattern->dataDetectorAdapter_->aiDetectInitialized_ = false;
    richEditorPattern->ProcessStyledString();

    ASSERT_EQ(richEditorPattern->spans_.empty(), true);
}

/**
 * @tc.name: ProcessStyledString002
 * @tc.desc: test ProcessStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringOneTestNg, ProcessStyledString002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->textDetectEnable_ = true;
    bool ret = false;
    ret = richEditorPattern->CanStartAITask();
    EXPECT_TRUE(ret);

    richEditorPattern->textForDisplay_ = INIT_VALUE_1;
    richEditorPattern->dataDetectorAdapter_->aiDetectInitialized_ = true;
    richEditorPattern->ProcessStyledString();

    EXPECT_FALSE(richEditorPattern->spans_.empty());
}

/**
 * @tc.name: ProcessStyledString003
 * @tc.desc: test ProcessStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringOneTestNg, ProcessStyledString003, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->textDetectEnable_ = true;
    bool ret = false;
    ret = richEditorPattern->CanStartAITask();
    EXPECT_TRUE(ret);

    richEditorPattern->dataDetectorAdapter_->aiDetectInitialized_ = false;
    richEditorPattern->ProcessStyledString();

    EXPECT_FALSE(richEditorPattern->spans_.empty());
}

/**
 * @tc.name: ProcessStyledString003
 * @tc.desc: test ProcessStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringOneTestNg, StyledStringCreateTest, TestSize.Level0)
{
    RefPtr<RichEditorPattern> pattern;
    bool isStyledStringMode;

    isStyledStringMode = false;
    pattern = AceType::MakeRefPtr<RichEditorPattern>(isStyledStringMode);
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->isSpanStringMode_, false);
    EXPECT_EQ(pattern->styledString_, nullptr);

    isStyledStringMode = true;
    pattern = AceType::MakeRefPtr<RichEditorPattern>(isStyledStringMode);
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->isSpanStringMode_, true);
    EXPECT_NE(pattern->styledString_, nullptr);
}

} // namespace OHOS::Ace::NG
