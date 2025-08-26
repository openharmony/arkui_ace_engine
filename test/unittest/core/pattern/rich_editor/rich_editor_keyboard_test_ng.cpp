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

#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "test/mock/core/common/mock_udmf.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
 
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
int32_t testOnReadyEvent = 0;
int32_t testAboutToIMEInput = 0;
int32_t testOnIMEInputComplete = 0;
int32_t testAboutToDelete = 0;
int32_t testOnDeleteComplete = 0;
constexpr int32_t PERFORM_ACTION = 1;
} // namespace

class RichEditorKeyboardTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorKeyboardTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    richEditorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->InitScrollablePattern();
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->CreateNodePaintMethod();
    richEditorNode_->GetGeometryNode()->SetContentSize({});
}

void RichEditorKeyboardTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    testOnReadyEvent = 0;
    testAboutToIMEInput = 0;
    testOnIMEInputComplete = 0;
    testAboutToDelete = 0;
    testOnDeleteComplete = 0;
    MockParagraph::TearDown();
}

void RichEditorKeyboardTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}
 
/**
 * @tc.name: NeedSoftKeyboard001
 * @tc.desc: test NeedSoftKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardTestNg, NeedSoftKeyboard001, TestSize.Level1)
{
    /**
     * @tc.step: step1. Get frameNode and pattern.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.steps: step2. Test whether rich editor need soft keyboard.
     */
    EXPECT_TRUE(richEditorPattern->NeedSoftKeyboard());
}

/**
 * @tc.name: VirtualKeyboardAreaChanged001
 * @tc.desc: test OnVirtualKeyboardAreaChanged
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardTestNg, VirtualKeyboardAreaChanged001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    float height = 0.0f;
    auto x = richEditorPattern->CalcCursorOffsetByPosition(richEditorPattern->textSelector_.GetStart(), height).GetX();
    richEditorPattern->OnVirtualKeyboardAreaChanged();
    EXPECT_EQ(richEditorPattern->textSelector_.selectionBaseOffset.GetX(), x);
}

/**
 * @tc.name: VirtualKeyboardAreaChanged002
 * @tc.desc: test OnVirtualKeyboardAreaChanged
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardTestNg, VirtualKeyboardAreaChanged002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
    */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);

    richEditorPattern->OnModifyDone();
    richEditorPattern->textSelector_.Update(0, 1);
    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    richEditorPattern->OnVirtualKeyboardAreaChanged();
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());
}

/**
 * @tc.name: KeyboardAppearance001
 * @tc.desc: test KeyboardAppearance
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardTestNg, KeyboardAppearance001, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    richEditorModel.SetKeyboardAppearance(KeyboardAppearance::IMMERSIVE);

    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ASSERT_EQ(richEditorPattern->GetKeyboardAppearance(), KeyboardAppearance::IMMERSIVE);
}

/**
 * @tc.name: RichEditorPatternTestRequestKeyboard001
 * @tc.desc: test RequestKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardTestNg, RichEditorPatternTestRequestKeyboard001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto textFieldManager = AceType::MakeRefPtr<TextFieldManagerNG>();
    MockPipelineContext::GetCurrent()->SetTextFieldManager(textFieldManager);
    auto func = [] {};

    auto customKeyboardBuilder = richEditorPattern->customKeyboardBuilder_;
    richEditorPattern->customKeyboardBuilder_ = func;
    ASSERT_EQ(richEditorPattern->RequestKeyboard(true, true, true), true);
    richEditorPattern->customKeyboardBuilder_ = customKeyboardBuilder;
}

/**
 * @tc.name: RichEditorPatternTestCloseCustomKeyboard001
 * @tc.desc: test CloseCustomKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardTestNg, RichEditorPatternTestCloseCustomKeyboard001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CloseCustomKeyboard();

    auto textFieldManager = AceType::MakeRefPtr<TextFieldManagerNG>();
    MockPipelineContext::GetCurrent()->SetTextFieldManager(textFieldManager);
    auto func = []() {};
    auto oldFunc = richEditorPattern->customKeyboardBuilder_;

    richEditorPattern->customKeyboardBuilder_ = func;

    EXPECT_EQ(richEditorPattern->isCustomKeyboardAttached_, false);
    EXPECT_EQ(richEditorPattern->RequestCustomKeyboard(), true);
    EXPECT_EQ(richEditorPattern->RequestCustomKeyboard(), true);
    EXPECT_EQ(richEditorPattern->isCustomKeyboardAttached_, true);
    EXPECT_NE(richEditorPattern->keyboardOverlay_, nullptr);
    ASSERT_EQ(richEditorPattern->CloseCustomKeyboard(), true);

    richEditorPattern->customKeyboardBuilder_ = oldFunc;
}

/**
 * @tc.name: RequestCustomKeyboard
 * @tc.desc: test RequestCustomKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardTestNg, RequestCustomKeyboard, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto textFieldManager = AceType::MakeRefPtr<TextFieldManagerNG>();
    MockPipelineContext::GetCurrent()->SetTextFieldManager(textFieldManager);
    int32_t apiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY));

    richEditorPattern->SetCustomKeyboardOption(true);
    auto func = []() {};
    richEditorPattern->customKeyboardBuilder_ = func;

    EXPECT_EQ(richEditorPattern->isCustomKeyboardAttached_, false);
    EXPECT_EQ(richEditorPattern->RequestCustomKeyboard(), true);
    EXPECT_EQ(textFieldManager->UsingCustomKeyboardAvoid(), true);
    EXPECT_EQ(richEditorPattern->isCustomKeyboardAttached_, true);

    richEditorPattern->SetCustomKeyboardOption(false);
    EXPECT_EQ(richEditorPattern->CloseCustomKeyboard(), true);
    EXPECT_EQ(textFieldManager->UsingCustomKeyboardAvoid(), false);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(apiVersion);
}

/**
 * @tc.name: RequestKeyboard001
 * @tc.desc: test RequestKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardTestNg, RequestKeyboard001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    bool res = richEditorPattern->RequestKeyboard(true, true, true);

    res = richEditorPattern->RequestKeyboard(true, true, false);

    richEditorPattern->customKeyboardBuilder_ = []() {};
    res = richEditorPattern->RequestKeyboard(true, true, true);

    richEditorPattern->customKeyboardBuilder_ = []() {};
    res = richEditorPattern->RequestKeyboard(true, true, false);
    ASSERT_NE(res, true);
}

/**
 * @tc.name: CloseKeyboard001
 * @tc.desc: test CloseKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardTestNg, CloseKeyboard001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->CloseKeyboard(false);
    EXPECT_EQ(richEditorPattern->HasConnection(), false);
}

/**
 * @tc.name: RequestKeyboardToEdit001
 * @tc.desc: test RequestKeyboardToEdit
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardTestNg, RequestKeyboardToEdit001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->previewLongPress_ = true;
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();
    richEditorPattern->isEditing_ = false;
    richEditorPattern->RequestKeyboardToEdit();
    EXPECT_FALSE(richEditorPattern->previewLongPress_);
}

/**
 * @tc.name: RequestKeyboardToEdit002
 * @tc.desc: test RequestKeyboardToEdit
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardTestNg, RequestKeyboardToEdit002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->RequestKeyboardToEdit();
}

/**
 * @tc.name: ResetKeyboardIfNeed001
 * @tc.desc: test ResetKeyboardIfNeed
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardTestNg, ResetKeyboardIfNeed001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    EXPECT_NE(focusHub, nullptr);

    focusHub->currentFocus_ = true;
    richEditorPattern->action_ = TextInputAction::UNSPECIFIED;
    richEditorPattern->ResetKeyboardIfNeed();
    EXPECT_NE(richEditorPattern->action_, TextInputAction::UNSPECIFIED);
}

/**
 * @tc.name: ResetKeyboardIfNeed002
 * @tc.desc: test ResetKeyboardIfNeed
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardTestNg, ResetKeyboardIfNeed002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    EXPECT_NE(focusHub, nullptr);

    richEditorPattern->imeShown_ = false;
    richEditorPattern->isCustomKeyboardAttached_ = true;
    focusHub->currentFocus_ = false;
    richEditorPattern->action_ = TextInputAction::SEARCH;
    richEditorPattern->ResetKeyboardIfNeed();
    EXPECT_NE(richEditorPattern->action_, TextInputAction::SEARCH);
}

/**
 * @tc.name: ResetKeyboardIfNeed003
 * @tc.desc: test ResetKeyboardIfNeed
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardTestNg, ResetKeyboardIfNeed003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    EXPECT_NE(focusHub, nullptr);

    richEditorPattern->imeShown_ = false;
    richEditorPattern->isCustomKeyboardAttached_ = false;
    focusHub->currentFocus_ = true;
    richEditorPattern->action_ = TextInputAction::SEARCH;
    richEditorPattern->ResetKeyboardIfNeed();
    EXPECT_NE(richEditorPattern->action_, TextInputAction::SEARCH);
}

/**
 * @tc.name: ResetKeyboardIfNeed004
 * @tc.desc: test ResetKeyboardIfNeed
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardTestNg, ResetKeyboardIfNeed004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
    */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    EXPECT_NE(focusHub, nullptr);

    richEditorPattern->imeShown_ = true;
    richEditorPattern->isCustomKeyboardAttached_ = true;
    focusHub->currentFocus_ = true;
    richEditorPattern->action_ = TextInputAction::SEARCH;
    richEditorPattern->ResetKeyboardIfNeed();
    EXPECT_NE(richEditorPattern->action_, TextInputAction::SEARCH);
}

/**
 * @tc.name: PerformAction001
 * @tc.desc: test PerformAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardTestNg, PerformAction001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    TextSpanOptions options2;
    options2.value = INIT_VALUE_1;
    richEditorController->AddTextSpan(options2);
    int count = 0;
    TextFieldCommonEvent event2;
    auto callback = [&count, &event2](int32_t key, NG::TextFieldCommonEvent& event) {
        event2 = event;
        if (count > 0) {
            event.SetKeepEditable(true);
        }
        count = count + 1;
    };
    eventHub->SetOnSubmit(std::move(callback));
    TextInputAction action2 = TextInputAction::SEARCH;
    bool forceCloseKeyboard = false;
    richEditorPattern->PerformAction(action2, forceCloseKeyboard);
    EXPECT_EQ(count, PERFORM_ACTION);
}

/**
 * @tc.name: GetCrossOverHeight001
 * @tc.desc: test GetCrossOverHeight
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardTestNg, GetCrossOverHeight001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->status_ = Status::DRAGGING;
    richEditorPattern->CreateHandles();
    richEditorPattern->contentChange_ = true;
    richEditorPattern->keyboardAvoidance_ = true;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
}

/**
 * @tc.name: GetCrossOverHeight002
 * @tc.desc: test GetCrossOverHeight
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardTestNg, GetCrossOverHeight002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->status_ = Status::DRAGGING;
    richEditorPattern->CreateHandles();
    richEditorPattern->contentChange_ = true;
    richEditorPattern->keyboardAvoidance_ = true;
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->rootHeight_ = 80.0;
    SafeAreaInsets::Inset insetBottom;
    insetBottom.start = 70;
    insetBottom.end = 80;
    pipeline->GetSafeAreaManager()->keyboardInset_ = SafeAreaInsets::Inset(insetBottom);
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
}

/**
 * @tc.name: GetCrossOverHeight003
 * @tc.desc: test GetCrossOverHeight
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardTestNg, GetCrossOverHeight003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->status_ = Status::DRAGGING;
    richEditorPattern->CreateHandles();
    richEditorPattern->contentChange_ = true;
    richEditorPattern->keyboardAvoidance_ = true;
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->rootHeight_ = 80.0;
    SafeAreaInsets::Inset insetBottom;
    insetBottom.start = 1;
    insetBottom.end = 86;
    pipeline->GetSafeAreaManager()->keyboardInset_ = SafeAreaInsets::Inset(insetBottom);
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 5.0f);
}

/**
 * @tc.name: GetCrossOverHeight004
 * @tc.desc: test GetCrossOverHeight
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardTestNg, GetCrossOverHeight004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->status_ = Status::DRAGGING;
    richEditorPattern->CreateHandles();
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    richEditorPattern->contentChange_ = true;
    richEditorPattern->keyboardAvoidance_ = true;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
    richEditorPattern->contentChange_ = false;
    richEditorPattern->keyboardAvoidance_ = true;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
    richEditorPattern->contentChange_ = false;
    richEditorPattern->keyboardAvoidance_ = false;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
    richEditorPattern->contentChange_ = true;
    richEditorPattern->keyboardAvoidance_ = false;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: GetCrossOverHeight005
 * @tc.desc: test GetCrossOverHeight
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardTestNg, GetCrossOverHeight005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->status_ = Status::DRAGGING;
    richEditorPattern->CreateHandles();
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN));
    richEditorPattern->contentChange_ = true;
    richEditorPattern->keyboardAvoidance_ = true;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
    richEditorPattern->contentChange_ = false;
    richEditorPattern->keyboardAvoidance_ = true;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
    richEditorPattern->contentChange_ = false;
    richEditorPattern->keyboardAvoidance_ = false;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
    richEditorPattern->contentChange_ = true;
    richEditorPattern->keyboardAvoidance_ = false;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: HandlePointWithTransform001
 * @tc.desc: test HandlePointWithTransform
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardTestNg, HandlePointWithTransform001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorNode_->tag_ = V2::WINDOW_SCENE_ETS_TAG;
    OffsetF point(0, 0);
    richEditorPattern->HandlePointWithTransform(point);
    EXPECT_EQ(point.GetX(), 0);
    EXPECT_EQ(point.GetY(), 0);
}

/**
 * @tc.name: HandlePointWithTransform002
 * @tc.desc: test HandlePointWithTransform
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardTestNg, HandlePointWithTransform002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorNode_->tag_ = V2::SCREEN_ETS_TAG;
    OffsetF point(0, 0);
    richEditorPattern->HandlePointWithTransform(point);
    EXPECT_EQ(point.GetX(), 0);
    EXPECT_EQ(point.GetY(), 0);
}

}