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

#include "test/unittest/core/pattern/rich_editor/rich_editor_styled_string_common_test_ng.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_undo_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
enum class UndoRecordType {
    INSERT,
    DELETE,
    INTERNAL_DRAG,
    EXTERNAL_DRAG,
    PASTE_STR,
    PASTE_STYLED_STR,
    SET_STYLED_STR,
    SHORTCUT_BOLD,
    SHORTCUT_ITALIC,
    SHORTCUT_UNDERLINE
};

struct OperationRecord {
    UndoRecordType type;
    UndoRedoRecord recordStep1;
    UndoRedoRecord recordStep2;
};

std::vector<OperationRecord> testRecords;
const int32_t STEP_TWO = 2;
const std::vector<std::string> EXPECT_STRING_LIST = {
    "初始属性字符串",
    "初始属性插入",
    "属性插入初始",
    "属性插初始",
    "属性插初始",
    "属性Insert初始",
    "属性Insert初插入测试字符串始",
    "属性Insert初插入测试字符串",
    "属性Insert初",
    "初始属性字符串",
    "初始属性字符串插入测试字符串",
    "初始属性字符串插入测试字符串",
    "插入初始属性字符串插入测试字符串",
    "插入初始属性字符串你好插入测试字符串",
    "插入初始插入测试字符串属性字符串你好",
    "Hellow测试字符串属性字符串你好",
    "Hellow测试字符串属性字符串你好",
    "Hellow测试字符串插入你好",
    "初始属性字符串"
};
} // namespace

class RichEditorStyledStringExtendTestNg : public RichEditorStyledStringCommonTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static void InitFirstTenRecords();
    static void InitSecondTenRecords();
    void SetUp() override;
    void TearDown() override;
    void DoActionWithRecord(const OperationRecord& operationRecord);
    void DoTestActions(bool needUndo = false);
    void SetCaretOrSelectionWithRecord(const UndoRedoRecord& record);
    void CheckUndoRecord(const UndoRedoRecord& record);
    void InsertValueWithRecord(const UndoRedoRecord& record);
    void DeleteValueWithRecord(const UndoRedoRecord& record);
    void HandleDragWithRecord(const UndoRedoRecord& record);
    void HandleDragWithRecord(const UndoRedoRecord& recordStep1, const UndoRedoRecord& recordStep2);
    void HandlePasteStringWithRecord(const UndoRedoRecord& record);
    void HandlePasteStyledStringWithRecord(const UndoRedoRecord& record);
    void SetStyledStringWithRecord(const UndoRedoRecord& record);
    void HandleUpdateSelectStyleWithRecord(const UndoRedoRecord& record, KeyCode keyCode);
    std::string GetRecordString(const UndoRedoRecord& record);
};

void RichEditorStyledStringExtendTestNg::SetUpTestSuite()
{
    InitFirstTenRecords();
    InitSecondTenRecords();
}

void RichEditorStyledStringExtendTestNg::TearDownTestSuite()
{
    testRecords.clear();
}

void RichEditorStyledStringExtendTestNg::InitFirstTenRecords()
{
    // step1 insert value with Selction "初始属性字符串"->"初始属性插入"
    UndoRedoRecord record = { .rangeBefore = TextRange{ 4, 7 }, .rangeAfter = TextRange{ 4, 6 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u"字符串"),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(INSERT_STRING_1), .selectionBefore = TextRange{ 4, 7 } };
    testRecords.push_back(OperationRecord{ .type = UndoRecordType::INSERT, .recordStep1 = record });

    // step2 internal drag "初始属性插入"->"属性插入初始"
    record = { .rangeBefore = TextRange{ 6, 6 }, .rangeAfter = TextRange{ 6, 8 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u""),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(u"初始"), .selectionBefore = TextRange{ 6, 6 } };
    UndoRedoRecord record2 = { .rangeBefore = TextRange{ 0, 2 }, .rangeAfter = TextRange{ 0, 0 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u"初始"),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(u""), .selectionBefore = TextRange{ 6, 6 } };
    testRecords.push_back(OperationRecord{ .type = UndoRecordType::INTERNAL_DRAG, .recordStep1 = record,
        .recordStep2 = record2});

    // step3 delete backward "属性插入初始"->"属性插初始"
    record = { .rangeBefore = TextRange{ 3, 4 }, .rangeAfter = TextRange{ 3, 3 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u"入"),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(u""), .selectionBefore = TextRange{ 4, 4 }, };
    testRecords.push_back(OperationRecord{ .type = UndoRecordType::DELETE, .recordStep1 = record });

    // step4 Ctrl + B "属性插初始"->"属性插初始"
    record = { .rangeBefore = TextRange{ 0, 2 }, .rangeAfter = TextRange{ 0, 2 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u"属性"),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(u"属性"),
        .selectionBefore = TextRange{ 0, 2 }, .isOnlyStyleChange = true, .updateSpanTypes = { SpanType::Font } };
    testRecords.push_back(OperationRecord{ .type = UndoRecordType::SHORTCUT_BOLD, .recordStep1 = record });

    // step5 paste styled string with selection "属性插初始"->"属性Insert初始"
    record = { .rangeBefore = TextRange{ 2, 3 }, .rangeAfter = TextRange{ 2, 8 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u"插"),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(INSERT_STRING_2), .selectionBefore = TextRange{ 2, 3 } };
    testRecords.push_back(OperationRecord{ .type = UndoRecordType::PASTE_STYLED_STR, .recordStep1 = record });

    // step6 insert value "属性Insert初始"->"属性Insert初插入测试字符串始"
    record = { .rangeBefore = TextRange{ 9, 9 }, .rangeAfter = TextRange{ 9, 16 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u""),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(INSERT_STRING_3), .selectionBefore = TextRange{ 9, 9 } };
    testRecords.push_back(OperationRecord{ .type = UndoRecordType::INSERT, .recordStep1 = record });

    // step7 delete forward "属性Insert初插入测试字符串始"->"属性Insert初插入测试字符串"
    record = { .rangeBefore = TextRange{ 16, 17 }, .rangeAfter = TextRange{ 16, 16 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u"始"),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(u""), .selectionBefore = TextRange{ 16, 16 } };
    testRecords.push_back(OperationRecord{ .type = UndoRecordType::DELETE, .recordStep1 = record });

    // step8 delete with selection "属性Insert初插入测试字符串"->"属性Insert初"
    record = { .rangeBefore = TextRange{ 9, 16 }, .rangeAfter = TextRange{ 9, 9 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u"插入测试字符串"),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(u""), .selectionBefore = TextRange{ 9, 16 } };
    testRecords.push_back(OperationRecord{ .type = UndoRecordType::DELETE, .recordStep1 = record });

    // step9 SetStyledString "属性Insert初"->"初始属性字符串"
    record = { .rangeBefore = TextRange{ 0, 9 }, .rangeAfter = TextRange{ 0, 7 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u"属性Insert初"),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(u"初始属性字符串"), .selectionBefore = TextRange{ 0, 0 } };
    testRecords.push_back(OperationRecord{ .type = UndoRecordType::SET_STYLED_STR, .recordStep1 = record });
}

void RichEditorStyledStringExtendTestNg::InitSecondTenRecords()
{
    // step1 paste styled string "初始属性字符串"->"初始属性字符串插入测试字符串"
    UndoRedoRecord record = { .rangeBefore = TextRange{ 7, 7 }, .rangeAfter = TextRange{ 7, 14 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u""),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(INSERT_STRING_3), .selectionBefore = TextRange{ 7, 7 } };
    testRecords.push_back(OperationRecord{ .type = UndoRecordType::PASTE_STYLED_STR, .recordStep1 = record });

    // step2 Ctrl + I "初始属性字符串插入测试字符串"->"初始属性字符串插入测试字符串"
    record = { .rangeBefore = TextRange{ 2, 7 }, .rangeAfter = TextRange{ 2, 7 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u"属性字符串"),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(u"属性字符串"),
        .selectionBefore = TextRange{ 2, 7 }, .isOnlyStyleChange = true, .updateSpanTypes = { SpanType::Font } };
    testRecords.push_back(OperationRecord{ .type = UndoRecordType::SHORTCUT_ITALIC, .recordStep1 = record });

    // step3 external drag "初始属性字符串插入测试字符串"->"插入初始属性字符串插入测试字符串"
    record = { .rangeBefore = TextRange{ 0, 0 }, .rangeAfter = TextRange{ 0, 2 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u""),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(INSERT_STRING_1), .selectionBefore = TextRange{ 0, 0 } };
    testRecords.push_back(OperationRecord{ .type = UndoRecordType::EXTERNAL_DRAG, .recordStep1 = record });

    // step4 paste string "插入初始属性字符串插入测试字符串"->"插入初始属性字符串你好插入测试字符串"
    record = { .rangeBefore = TextRange{ 9, 9 }, .rangeAfter = TextRange{ 9, 11 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u""),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(u"你好"), .selectionBefore = TextRange{ 9, 9 } };
    testRecords.push_back(OperationRecord{ .type = UndoRecordType::PASTE_STR, .recordStep1 = record });
  
    // step5 internal drag "插入初始属性字符串你好插入测试字符串"->"插入初始插入测试字符串属性字符串你好"
    record = { .rangeBefore = TextRange{ 4, 4 }, .rangeAfter = TextRange{ 4, 11 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u""),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(u"插入测试字符串"), .selectionBefore = TextRange{ 4, 4 } };
    UndoRedoRecord record2 = { .rangeBefore = TextRange{ 18, 25 }, .rangeAfter = TextRange{ 18, 18 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u"插入测试字符串"),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(u""), .selectionBefore = TextRange{ 11, 11 } };
    testRecords.push_back(OperationRecord{ .type = UndoRecordType::INTERNAL_DRAG, .recordStep1 = record,
        .recordStep2 = record2});

    // step6 paste string with selection "插入初始插入测试字符串属性字符串你好"->"Hellow测试字符串属性字符串你好"
    record = { .rangeBefore = TextRange{ 0, 6 }, .rangeAfter = TextRange{ 0, 6 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u"插入初始插入"),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(u"Hellow"), .selectionBefore = TextRange{ 0, 6 } };
    testRecords.push_back(OperationRecord{ .type = UndoRecordType::PASTE_STR, .recordStep1 = record });

    // step7 Ctrl + U "Hellow测试字符串属性字符串你好"->"Hellow测试字符串属性字符串你好"
    record = { .rangeBefore = TextRange{ 6, 11 }, .rangeAfter = TextRange{ 6, 11 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u"测试字符串"),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(u"测试字符串"),
        .selectionBefore = TextRange{ 6, 11 }, .isOnlyStyleChange = true, .updateSpanTypes = { SpanType::Decoration } };
    testRecords.push_back(OperationRecord{ .type = UndoRecordType::SHORTCUT_UNDERLINE, .recordStep1 = record });

    // step8 insert value with Selction "Hellow测试字符串属性字符串你好"->"Hellow测试字符串插入你好"
    record = { .rangeBefore = TextRange{ 11, 16 }, .rangeAfter = TextRange{ 11, 13 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u"属性字符串"),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(INSERT_STRING_1), .selectionBefore = TextRange{ 11, 16 } };
    testRecords.push_back(OperationRecord{ .type = UndoRecordType::INSERT, .recordStep1 = record });

    // step9 SetStyledString "Hellow测试字符串插入你好"->"初始属性字符串"
    record = { .rangeBefore = TextRange{ 0, 15 }, .rangeAfter = TextRange{ 0, 7 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u"Hellow测试字符串插入你好"),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(u"初始属性字符串"), .selectionBefore = TextRange{ 0, 0 } };
    testRecords.push_back(OperationRecord{ .type = UndoRecordType::SET_STYLED_STR, .recordStep1 = record });
}

void RichEditorStyledStringExtendTestNg::SetUp()
{
    RichEditorStyledStringCommonTestNg::SetUp();
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    auto mutableStr = CreateTextStyledString(INIT_U16STRING_1);
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->SetStyledString(mutableStr);
    ASSERT_NE(richEditorPattern->undoManager_, nullptr);
    richEditorPattern->ClearOperationRecords();
}

void RichEditorStyledStringExtendTestNg::TearDown()
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->ClearOperationRecords();
    RichEditorStyledStringCommonTestNg::TearDown();
}

void RichEditorStyledStringExtendTestNg::DoActionWithRecord(const OperationRecord& operationRecord)
{
    switch (operationRecord.type) {
        case UndoRecordType::INSERT:
            InsertValueWithRecord(operationRecord.recordStep1);
            break;
        case UndoRecordType::DELETE:
            DeleteValueWithRecord(operationRecord.recordStep1);
            break;
        case UndoRecordType::INTERNAL_DRAG:
            HandleDragWithRecord(operationRecord.recordStep1, operationRecord.recordStep2);
            break;
        case UndoRecordType::EXTERNAL_DRAG:
            HandleDragWithRecord(operationRecord.recordStep1);
            break;
        case UndoRecordType::PASTE_STR:
            HandlePasteStringWithRecord(operationRecord.recordStep1);
            break;
        case UndoRecordType::PASTE_STYLED_STR:
            HandlePasteStyledStringWithRecord(operationRecord.recordStep1);
            break;
        case UndoRecordType::SET_STYLED_STR:
            SetStyledStringWithRecord(operationRecord.recordStep1);
            break;
        case UndoRecordType::SHORTCUT_BOLD:
            HandleUpdateSelectStyleWithRecord(operationRecord.recordStep1, KeyCode::KEY_B);
            break;
        case UndoRecordType::SHORTCUT_ITALIC:
            HandleUpdateSelectStyleWithRecord(operationRecord.recordStep1, KeyCode::KEY_I);
            break;
        case UndoRecordType::SHORTCUT_UNDERLINE:
            HandleUpdateSelectStyleWithRecord(operationRecord.recordStep1, KeyCode::KEY_U);
            break;
        default:
            break;
    }
}

void RichEditorStyledStringExtendTestNg::DoTestActions(bool needUndo)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    for (const auto& record : testRecords) {
        DoActionWithRecord(record);
    }
    CHECK_NULL_VOID(needUndo);
    auto& undoRecords = richEditorPattern->undoManager_->undoRecords_;
    while (!undoRecords.empty()) {
        richEditorPattern->HandleOnUndoAction();
    }
}

void RichEditorStyledStringExtendTestNg::SetCaretOrSelectionWithRecord(const UndoRedoRecord& record)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->ResetSelection();
    richEditorPattern->SetCaretPosition(record.selectionBefore.end);
    if (record.selectionBefore.GetLength() > 0) {
        richEditorPattern->textSelector_.Update(record.selectionBefore.start, record.selectionBefore.end);
    }
}

void RichEditorStyledStringExtendTestNg::CheckUndoRecord(const UndoRedoRecord& record)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ASSERT_NE(richEditorPattern->undoManager_, nullptr);
    auto& undoRecords = richEditorPattern->undoManager_->undoRecords_;
    EXPECT_GE(undoRecords.size(), 1);
    EXPECT_EQ(GetRecordString(undoRecords.back()), GetRecordString(record));
}

void RichEditorStyledStringExtendTestNg::InsertValueWithRecord(const UndoRedoRecord& record)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SetCaretOrSelectionWithRecord(record);
    richEditorPattern->InsertValueInStyledString(record.styledStringAfter->GetU16string(), true);
    CheckUndoRecord(record);
}

void RichEditorStyledStringExtendTestNg::DeleteValueWithRecord(const UndoRedoRecord& record)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SetCaretOrSelectionWithRecord(record);
    richEditorPattern->DeleteValueInStyledString(record.rangeBefore.start, record.rangeBefore.GetLength());
    CheckUndoRecord(record);
}

void RichEditorStyledStringExtendTestNg::HandleDragWithRecord(const UndoRedoRecord& record)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isDragSponsor_ = false;
    richEditorPattern->SetCaretPosition(record.selectionBefore.end);
    richEditorPattern->HandleOnDragInsertStyledString(record.styledStringAfter);
    CheckUndoRecord(record);
}

void RichEditorStyledStringExtendTestNg::HandleDragWithRecord(const UndoRedoRecord& recordStep1,
    const UndoRedoRecord& recordStep2)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isDragSponsor_ = true;
    richEditorPattern->dragRange_ = { recordStep2.rangeBefore.start, recordStep2.rangeBefore.end};
    if (recordStep2.rangeBefore.start > recordStep1.selectionBefore.end) {
        richEditorPattern->dragRange_.first -= recordStep1.rangeAfter.GetLength();
        richEditorPattern->dragRange_.second -= recordStep1.rangeAfter.GetLength();
    }
    richEditorPattern->SetCaretPosition(recordStep1.selectionBefore.end);
    richEditorPattern->HandleOnDragInsertStyledString(recordStep1.styledStringAfter);
    ASSERT_NE(richEditorPattern->undoManager_, nullptr);
    auto& undoRecords = richEditorPattern->undoManager_->undoRecords_;
    EXPECT_GE(undoRecords.size(), STEP_TWO);
    auto undoRecord = undoRecords.back();
    EXPECT_EQ(GetRecordString(undoRecord), GetRecordString(recordStep2));
    undoRecord = undoRecords.at(undoRecords.size() - STEP_TWO);
    EXPECT_EQ(GetRecordString(undoRecord), GetRecordString(recordStep1));
}

void RichEditorStyledStringExtendTestNg::HandlePasteStringWithRecord(const UndoRedoRecord& record)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SetCaretOrSelectionWithRecord(record);
    richEditorPattern->InsertValueByPaste(record.styledStringAfter->GetU16string());
    CheckUndoRecord(record);
}

void RichEditorStyledStringExtendTestNg::HandlePasteStyledStringWithRecord(const UndoRedoRecord& record)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SetCaretOrSelectionWithRecord(record);
    richEditorPattern->InsertStyledStringByPaste(record.styledStringAfter);
    CheckUndoRecord(record);
}

void RichEditorStyledStringExtendTestNg::SetStyledStringWithRecord(const UndoRedoRecord& record)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SetCaretOrSelectionWithRecord(record);
    richEditorPattern->SetStyledString(record.styledStringAfter);
    CheckUndoRecord(record);
}

void RichEditorStyledStringExtendTestNg::HandleUpdateSelectStyleWithRecord(const UndoRedoRecord& record,
    KeyCode keyCode)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SetCaretOrSelectionWithRecord(record);
    richEditorPattern->HandleSelectFontStyle(keyCode);
    CheckUndoRecord(record);
}

std::string RichEditorStyledStringExtendTestNg::GetRecordString(const UndoRedoRecord& record)
{
    std::stringstream ss;
    CHECK_NULL_RETURN(record.IsValid(), "");
    ss<< "rangeBefore:" << record.rangeBefore.ToString() << ", ";
    ss<< "stringBefore:" << record.styledStringBefore->GetString() << ", ";
    ss<< "rangeAfter:" << record.rangeAfter.ToString() << ", ";
    ss<< "stringAfter:" << record.styledStringAfter->GetString() << ", ";
    ss<< "isOnlyStyleChange:" << record.isOnlyStyleChange << ", ";
    auto spanTypesArray = JsonUtil::CreateArray();
    for (const auto& type : record.updateSpanTypes) {
        spanTypesArray->Put("", static_cast<int>(type));
    }
    ss<< "updateSpanTypes:" << spanTypesArray->ToString();
    return ss.str();
}


/**
 * @tc.name: HandleSelectFontStyle
 * @tc.desc: Test HandleSelectFontStyle.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringExtendTestNg, HandleSelectFontStyle, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ASSERT_NE(richEditorPattern->styledString_, nullptr);
    auto keyCode = KeyCode::KEY_B;
    richEditorPattern->textSelector_.Update(2, 4);
    richEditorPattern->HandleSelectFontStyle(keyCode);
    auto fontSpan = AceType::DynamicCast<FontSpan>(richEditorPattern->styledString_->GetSpan(2, 2, SpanType::Font));
    ASSERT_NE(fontSpan, nullptr);
    EXPECT_EQ(fontSpan->GetFont().fontWeight, FontWeight::NORMAL);
    richEditorPattern->textSelector_.Update(2, 6);
    richEditorPattern->HandleSelectFontStyle(keyCode);
    fontSpan = AceType::DynamicCast<FontSpan>(richEditorPattern->styledString_->GetSpan(2, 4, SpanType::Font));
    ASSERT_NE(fontSpan, nullptr);
    EXPECT_EQ(fontSpan->GetFont().fontWeight, FontWeight::BOLD);

    keyCode = KeyCode::KEY_I;
    richEditorPattern->textSelector_.Update(2, 4);
    richEditorPattern->HandleSelectFontStyle(keyCode);
    fontSpan = AceType::DynamicCast<FontSpan>(richEditorPattern->styledString_->GetSpan(2, 2, SpanType::Font));
    ASSERT_NE(fontSpan, nullptr);
    EXPECT_EQ(fontSpan->GetFont().fontStyle, OHOS::Ace::FontStyle::NORMAL);
    richEditorPattern->textSelector_.Update(2, 6);
    richEditorPattern->HandleSelectFontStyle(keyCode);
    fontSpan = AceType::DynamicCast<FontSpan>(richEditorPattern->styledString_->GetSpan(2, 4, SpanType::Font));
    ASSERT_NE(fontSpan, nullptr);
    EXPECT_EQ(fontSpan->GetFont().fontStyle, OHOS::Ace::FontStyle::ITALIC);

    keyCode = KeyCode::KEY_U;
    richEditorPattern->textSelector_.Update(2, 4);
    richEditorPattern->HandleSelectFontStyle(keyCode);
    auto decorationSpan =
        AceType::DynamicCast<DecorationSpan>(richEditorPattern->styledString_->GetSpan(2, 2, SpanType::Decoration));
    ASSERT_NE(decorationSpan, nullptr);
    EXPECT_EQ(decorationSpan->GetTextDecorationFirst(), TextDecoration::UNDERLINE);
    richEditorPattern->textSelector_.Update(2, 6);
    richEditorPattern->HandleSelectFontStyle(keyCode);
    decorationSpan =
        AceType::DynamicCast<DecorationSpan>(richEditorPattern->styledString_->GetSpan(2, 4, SpanType::Decoration));
    ASSERT_NE(decorationSpan, nullptr);
    bool ret = V2::HasTextDecoration(decorationSpan->GetTextDecorationTypes(), TextDecoration::UNDERLINE);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: RecordOperation001
 * @tc.desc: Test RecordOperation by insert or delete.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringExtendTestNg, RecordOperation001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ASSERT_NE(richEditorPattern->styledString_, nullptr);
    // step1 insert value
    UndoRedoRecord record = { .rangeBefore = TextRange{ 4, 4 }, .rangeAfter = TextRange{ 4, 6 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u""),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(INSERT_STRING_1),
        .selectionBefore = TextRange{ 4, 4 } };
    InsertValueWithRecord(record);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 1);

    // step2 insert value with selection
    record = { .rangeBefore = TextRange{ 0, 2 }, .rangeAfter = TextRange{ 0, 6 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u"初始"),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(INSERT_STRING_2),
        .selectionBefore = TextRange{ 0, 2 } };
    InsertValueWithRecord(record);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 2);

    // step3 delete forward
    record = { .rangeBefore = TextRange{ 11, 12 }, .rangeAfter = TextRange{ 11, 11 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u"符"),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(u""),
        .selectionBefore = TextRange{ 11, 11 } };
    DeleteValueWithRecord(record);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 3);

    // step4 delete backward
    record = { .rangeBefore = TextRange{ 10, 11 }, .rangeAfter = TextRange{ 10, 10 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u"字"),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(u""),
        .selectionBefore = TextRange{ 11, 11 } };
    DeleteValueWithRecord(record);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 4);

    // step5 delete with selection
    record = { .rangeBefore = TextRange{ 6, 8 }, .rangeAfter = TextRange{ 6, 6 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u"属性"),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(u""),
        .selectionBefore = TextRange{ 6, 8 } };
    DeleteValueWithRecord(record);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 5);
}

/**
 * @tc.name: RecordOperation002
 * @tc.desc: Test RecordOperation by paste or drag.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringExtendTestNg, RecordOperation002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ASSERT_NE(richEditorPattern->styledString_, nullptr);

    // step1 paste string
    UndoRedoRecord record = { .rangeBefore = TextRange{ 2, 2 }, .rangeAfter = TextRange{ 2, 4 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u""),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(INSERT_STRING_1),
        .selectionBefore = TextRange{ 2, 2 } };
    HandlePasteStringWithRecord(record);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 1);

    // step2 paste string with selection
    record = { .rangeBefore = TextRange{ 4, 6 }, .rangeAfter = TextRange{ 4, 10 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u"属性"),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(INSERT_STRING_2),
        .selectionBefore = TextRange{ 4, 6 } };
    HandlePasteStringWithRecord(record);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 2);

    // step3 paste styled string
    record = { .rangeBefore = TextRange{ 12, 12 }, .rangeAfter = TextRange{ 12, 14 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u""),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(INSERT_STRING_1),
        .selectionBefore = TextRange{ 12, 12 } };
    HandlePasteStringWithRecord(record);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 3);

    // step4 paste styled string with selection
    record = { .rangeBefore = TextRange{ 0, 4 }, .rangeAfter = TextRange{ 0, 6 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u"初始插入"),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(INSERT_STRING_2),
        .selectionBefore = TextRange{ 0, 4 } };
    HandlePasteStyledStringWithRecord(record);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 4);

    // step5 internal drag
    record = { .rangeBefore = TextRange{ 16, 16 }, .rangeAfter = TextRange{ 16, 18 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u""),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(u"字符"),
        .selectionBefore = TextRange{ 16, 16 } };
    UndoRedoRecord record2 = { .rangeBefore = TextRange{ 12, 14 }, .rangeAfter = TextRange{ 12, 12 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u"字符"),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(u""),
        .selectionBefore = TextRange{ 16, 16 } };
    HandleDragWithRecord(record, record2);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 6);

    // step6 external drag
    record = { .rangeBefore = TextRange{ 6, 6 }, .rangeAfter = TextRange{ 6, 8 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u""),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(INSERT_STRING_1),
        .selectionBefore = TextRange{ 6, 6 } };
    HandleDragWithRecord(record);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 7);
}

/**
 * @tc.name: RecordOperation003
 * @tc.desc: Test RecordOperation by SetStyledString or HandleSelectFontStyle.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringExtendTestNg, RecordOperation003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ASSERT_NE(richEditorPattern->styledString_, nullptr);

    // step1 SetStyledString
    auto mutableStr = CreateCustomSpanStyledString();
    auto mutableTextStr = CreateTextStyledString(INIT_U16STRING_1);
    auto mutableImageStr = CreateImageStyledString();
    mutableStr->AppendSpanString(mutableTextStr);
    mutableStr->InsertSpanString(3, mutableImageStr);
    UndoRedoRecord record = { .rangeBefore = TextRange{ 0, 7 }, .rangeAfter = TextRange{ 0, 9 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(INIT_U16STRING_1), .styledStringAfter = mutableStr,
        .selectionBefore = TextRange{ 2, 2 } };
    SetStyledStringWithRecord(record);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 1);

    // step2 Ctrl + B
    record = { .rangeBefore = TextRange{ 4, 9 }, .rangeAfter = TextRange{ 4, 9 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u"属性字符串"),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(u"属性字符串"),
        .selectionBefore = TextRange{ 4, 9 }, .isOnlyStyleChange = true, .updateSpanTypes = { SpanType::Font }};
    HandleUpdateSelectStyleWithRecord(record, KeyCode::KEY_B);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 2);

    // step3 Ctrl + I
    record = { .rangeBefore = TextRange{ 0, 5 }, .rangeAfter = TextRange{ 0, 5 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u" 初始 属"),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(u" 初始 属"),
        .selectionBefore = TextRange{ 0, 5 }, .isOnlyStyleChange = true, .updateSpanTypes = { SpanType::Font }};
    HandleUpdateSelectStyleWithRecord(record, KeyCode::KEY_I);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 3);

    // step4 Ctrl + U
    record = { .rangeBefore = TextRange{ 2, 7 }, .rangeAfter = TextRange{ 2, 7 },
        .styledStringBefore = AceType::MakeRefPtr<SpanString>(u"始 属性字"),
        .styledStringAfter = AceType::MakeRefPtr<SpanString>(u"始 属性字"),
        .selectionBefore = TextRange{ 2, 7 }, .isOnlyStyleChange = true, .updateSpanTypes = { SpanType::Decoration }};
    HandleUpdateSelectStyleWithRecord(record, KeyCode::KEY_U);
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 4);
}

/**
 * @tc.name: HandleUndoAction001
 * @tc.desc: Test HandleUndoAction.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringExtendTestNg, HandleUndoAction001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ASSERT_NE(richEditorPattern->styledString_, nullptr);
    DoTestActions();
    EXPECT_EQ(richEditorPattern->undoManager_->undoRecords_.size(), 20);
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[18]);
    richEditorPattern->HandleOnUndoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[17]);
    richEditorPattern->HandleOnUndoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[16]);
    richEditorPattern->HandleOnUndoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[15]);
    richEditorPattern->HandleOnUndoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[14]);
    richEditorPattern->HandleOnUndoAction();
    richEditorPattern->HandleOnUndoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[13]);
    richEditorPattern->HandleOnUndoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[12]);
    richEditorPattern->HandleOnUndoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[11]);
    richEditorPattern->HandleOnUndoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[10]);
    richEditorPattern->HandleOnUndoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[9]);
    richEditorPattern->HandleOnUndoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[8]);
    richEditorPattern->HandleOnUndoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[7]);
    richEditorPattern->HandleOnUndoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[6]);
    richEditorPattern->HandleOnUndoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[5]);
    richEditorPattern->HandleOnUndoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[4]);
    richEditorPattern->HandleOnUndoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[3]);
    richEditorPattern->HandleOnUndoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[2]);
    richEditorPattern->HandleOnUndoAction();
    richEditorPattern->HandleOnUndoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[1]);
    richEditorPattern->HandleOnUndoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[0]);
}

/**
 * @tc.name: HandleRedoAction001
 * @tc.desc: Test HandleRedoAction.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringExtendTestNg, HandleRedoAction001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ASSERT_NE(richEditorPattern->styledString_, nullptr);
    DoTestActions(true);
    EXPECT_EQ(richEditorPattern->undoManager_->redoRecords_.size(), 20);
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[0]);
    richEditorPattern->HandleOnRedoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[1]);
    richEditorPattern->HandleOnRedoAction();
    richEditorPattern->HandleOnRedoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[2]);
    richEditorPattern->HandleOnRedoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[3]);
    richEditorPattern->HandleOnRedoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[4]);
    richEditorPattern->HandleOnRedoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[5]);
    richEditorPattern->HandleOnRedoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[6]);
    richEditorPattern->HandleOnRedoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[7]);
    richEditorPattern->HandleOnRedoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[8]);
    richEditorPattern->HandleOnRedoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[9]);
    richEditorPattern->HandleOnRedoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[10]);
    richEditorPattern->HandleOnRedoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[11]);
    richEditorPattern->HandleOnRedoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[12]);
    richEditorPattern->HandleOnRedoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[13]);
    richEditorPattern->HandleOnRedoAction();
    richEditorPattern->HandleOnRedoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[14]);
    richEditorPattern->HandleOnRedoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[15]);
    richEditorPattern->HandleOnRedoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[16]);
    richEditorPattern->HandleOnRedoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[17]);
    richEditorPattern->HandleOnRedoAction();
    EXPECT_EQ(richEditorPattern->styledString_->GetString(), EXPECT_STRING_LIST[18]);
}

} // namespace OHOS::Ace::NG
