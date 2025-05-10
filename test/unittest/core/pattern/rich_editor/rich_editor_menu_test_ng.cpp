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
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/common/ai/data_detector_adapter.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string TEST_IMAGE_SOURCE = "src/image.png";
int32_t callBack1 = 0;
int32_t callBack2 = 0;
int32_t callBack3 = 0;
int32_t testNumber0 = 0;
int32_t testNumber5 = 5;

// include span string and position
struct AISpanTestInfo {
    std::variant<std::string, std::u16string> content;
    vector<Ace::AISpan> aiSpans;
};

const AISpanTestInfo U16_TEXT_FOR_AI_INFO =
                    { std::u16string(u"phone: 12345678900,url: www.baidu.com Hello World"),
                        { {7, 18, "12345678900", TextDataDetectType::PHONE_NUMBER},
                        {24, 37, "www.baidu.com", TextDataDetectType::URL} }
                    };

const AISpanTestInfo U16_TEXT_FOR_AI_INFO_2 =
                    { std::u16string(u"email: 1234@abc.com,date: 2025.09.12, "),
                        { {7, 19, "1234@abc.com", TextDataDetectType::EMAIL},
                        {26, 36, "2025.09.12", TextDataDetectType::DATE_TIME} }
                    };
} // namespace

class RichEditorMenuTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorMenuTestNg::SetUp()
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

void RichEditorMenuTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorMenuTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: TestRichEditorHandleOnShowMenu001
 * @tc.desc: test HandleOnShowMenu
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMenuTestNg, TestRichEditorHandleOnShowMenu001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto tempOffset = richEditorPattern->selectionMenuOffsetByMouse_;
    richEditorPattern->parentGlobalOffset_.x_ = 10.0f;
    richEditorPattern->parentGlobalOffset_.y_ = 20.0f;
    richEditorPattern->sourceType_ = SourceType::MOUSE;

    /**
     * @tc.steps: step2. add text and paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { -400.0, -400.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 6;
    richEditorPattern->contentRect_ = { -500.0, -500.0, 500.0, 500.0 };

    richEditorPattern->HandleOnShowMenu();
    ASSERT_NE(richEditorPattern->selectionMenuOffsetByMouse_, tempOffset);
}

/**
 * @tc.name: CopySelectionMenuParams001
 * @tc.desc: test CopySelectionMenuParams
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMenuTestNg, CopySelectionMenuParams001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SelectOverlayInfo selectInfo;
    richEditorPattern->selectedType_ = TextSpanType::TEXT;
    richEditorPattern->CopySelectionMenuParams(selectInfo, TextResponseType::LONG_PRESS);
    EXPECT_EQ(selectInfo.menuCallback.onDisappear, nullptr);

    richEditorPattern->selectedType_ = TextSpanType::IMAGE;
    richEditorPattern->CopySelectionMenuParams(selectInfo, TextResponseType::LONG_PRESS);
    EXPECT_EQ(selectInfo.menuCallback.onDisappear, nullptr);

    richEditorPattern->selectedType_ = TextSpanType::MIXED;
    richEditorPattern->CopySelectionMenuParams(selectInfo, TextResponseType::LONG_PRESS);
    EXPECT_EQ(selectInfo.menuCallback.onDisappear, nullptr);

    richEditorPattern->selectedType_ = TextSpanType(-1);
    richEditorPattern->CopySelectionMenuParams(selectInfo, TextResponseType::LONG_PRESS);
    EXPECT_EQ(selectInfo.menuCallback.onDisappear, nullptr);

    auto key = std::make_pair(TextSpanType::MIXED, TextResponseType::RIGHT_CLICK);
    callBack1 = 0;
    callBack2 = 0;
    callBack3 = 0;
    std::function<void()> buildFunc = []() {
        callBack1 = 1;
        return;
    };
    std::function<void(int32_t, int32_t)> onAppear = [](int32_t a, int32_t b) {
        callBack2 = 2;
        return;
    };
    std::function<void()> onDisappear = []() {
        callBack3 = 3;
        return;
    };
    std::shared_ptr<SelectionMenuParams> params1 = std::make_shared<SelectionMenuParams>(
        TextSpanType::MIXED, buildFunc, onAppear, onDisappear, TextResponseType::RIGHT_CLICK);
    richEditorPattern->selectionMenuMap_[key] = params1;
    selectInfo.isUsingMouse = true;
    richEditorPattern->selectedType_ = TextSpanType::MIXED;
    richEditorPattern->CopySelectionMenuParams(selectInfo, TextResponseType::RIGHT_CLICK);
    EXPECT_NE(selectInfo.menuCallback.onDisappear, nullptr);

    key = std::make_pair(TextSpanType::MIXED, TextResponseType::LONG_PRESS);
    std::shared_ptr<SelectionMenuParams> params2 = std::make_shared<SelectionMenuParams>(
        TextSpanType::MIXED, buildFunc, nullptr, nullptr, TextResponseType::RIGHT_CLICK);
    richEditorPattern->selectionMenuMap_[key] = params2;
    selectInfo.isUsingMouse = false;
    richEditorPattern->selectedType_ = TextSpanType::MIXED;
    richEditorPattern->CopySelectionMenuParams(selectInfo, TextResponseType::RIGHT_CLICK);
    EXPECT_NE(selectInfo.menuCallback.onDisappear, nullptr);
}

/**
 * @tc.name: BindSelectionMenu001
 * @tc.desc: test BindSelectionMenu
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMenuTestNg, BindSelectionMenu001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    callBack1 = 0;
    callBack2 = 0;
    callBack3 = 0;
    std::function<void()> buildFunc = []() {
        callBack1 = 1;
        return;
    };
    std::function<void(int32_t, int32_t)> onAppear = [](int32_t a, int32_t b) {
        callBack2 = 2;
        return;
    };
    std::function<void()> onDisappear = []() {
        callBack3 = 3;
        return;
    };

    auto key = std::make_pair(TextSpanType::MIXED, TextResponseType::RIGHT_CLICK);
    std::shared_ptr<SelectionMenuParams> params1 = std::make_shared<SelectionMenuParams>(
        TextSpanType::MIXED, buildFunc, onAppear, onDisappear, TextResponseType::RIGHT_CLICK);
    richEditorPattern->selectionMenuMap_[key] = params1;

    std::function<void()> nullFunc = nullptr;

    richEditorPattern->BindSelectionMenu(TextResponseType::RIGHT_CLICK, TextSpanType::MIXED, nullFunc,
        { .onAppear = onAppear, .onDisappear = onDisappear });
    EXPECT_TRUE(richEditorPattern->selectionMenuMap_.empty());

    richEditorPattern->selectionMenuMap_[key] = params1;
    richEditorPattern->BindSelectionMenu(TextResponseType::RIGHT_CLICK, TextSpanType::MIXED, buildFunc,
        { .onAppear = onAppear, .onDisappear = onDisappear });
    EXPECT_FALSE(richEditorPattern->selectionMenuMap_.empty());

    richEditorPattern->BindSelectionMenu(TextResponseType::RIGHT_CLICK, TextSpanType::IMAGE, buildFunc,
        { .onAppear = onAppear, .onDisappear = onDisappear });
    EXPECT_FALSE(richEditorPattern->selectionMenuMap_.empty());
}


/**
 * @tc.name: BindSelectionMenu001
 * @tc.desc: test BindSelectionMenu
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMenuTestNg, BindSelectionMenu002, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::function<void()> buildFunc = []() {
        callBack1 = 1;
        return;
    };
    TextSpanType textSpanType = TextSpanType::TEXT;
    TextResponseType textResponseType = TextResponseType::LONG_PRESS;
    SelectMenuParam menuParam { .onAppear = [](int32_t, int32_t) {}, .onDisappear = []() {} };
    richEditorModel.BindSelectionMenu(textSpanType, textResponseType, buildFunc, menuParam);
    EXPECT_TRUE(richEditorPattern->selectionMenuMap_.empty());
}

/**
 * @tc.name: OnMenuItemAction001
 * @tc.desc: test OnMenuItemAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMenuTestNg, OnMenuItemAction001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richeditor pattern and add text span
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
	
    /**
     * @tc.steps: step2. request focus
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();
	
    /**
     * @tc.step: step3. create a scene where the text menu has popped up
     */
    richEditorPattern->OnModifyDone();
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->textSelector_.Update(0, 2);

    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 2);
	
    /**
     * @tc.step: step4. test OnMenuItemAction
     */
    richEditorPattern->isMousePressed_ = true;
    richEditorPattern->caretUpdateType_ = CaretUpdateType::PRESSED;
    richEditorPattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::COPY, OptionMenuType::MOUSE_MENU);
    EXPECT_EQ(richEditorPattern->caretUpdateType_, CaretUpdateType::NONE);
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());
}

/**
 * @tc.name: OnMenuItemAction002
 * @tc.desc: test OnMenuItemAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMenuTestNg, OnMenuItemAction002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richeditor pattern and add add text span
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 6);

    /**
     * @tc.steps: step2. request focus
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    focusHub->RequestFocusImmediately();
	
    /**
     * @tc.step: step3. create a scene where the text menu has popped up
     */
    richEditorPattern->OnModifyDone();
    richEditorPattern->textSelector_.Update(1, 2);
    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());
	
    /**
     * @tc.step: step4. test OnMenuItemAction
     */
    richEditorPattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::COPY, OptionMenuType::TOUCH_MENU);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 1);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 2);

    richEditorPattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::PASTE, OptionMenuType::NO_MENU);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 6);
	
    auto selectOverlayInfo = richEditorPattern->selectOverlay_->GetSelectOverlayInfo();
    auto selectInfoFirstHandle = selectOverlayInfo->firstHandle;
    EXPECT_FALSE(selectInfoFirstHandle.isShow);
    EXPECT_FALSE(richEditorPattern->SelectOverlayIsOn());
}

/**
 * @tc.name: OnMenuItemAction003
 * @tc.desc: test OnMenuItemAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMenuTestNg, OnMenuItemAction003, TestSize.Level1)
{
    /**
     * @tc.step: step1. get richeditor pattern and add text span.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 6);
	
    /**
     * @tc.step: step2. request focus
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    focusHub->RequestFocusImmediately();
    richEditorPattern->isEditing_ = true;

    /**
     * @tc.step: step3. call SetSelection
     */
    int32_t start = 0;
    int32_t end = 2;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    richEditorPattern->OnModifyDone();
    auto selectOverlay = richEditorPattern->selectOverlay_;
    richEditorPattern->SetSelection(start, end, options, false);

    EXPECT_FALSE(richEditorPattern->SelectOverlayIsOn());
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 2);

    /**
     * @tc.step: step4. test OnMenuItemAction
     */
    richEditorPattern->isMousePressed_ = true;
    selectOverlay->OnMenuItemAction(OptionMenuActionId::CUT, OptionMenuType::TOUCH_MENU);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 4);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), start);
    EXPECT_FALSE(richEditorPattern->SelectOverlayIsOn());
	
    /**
     * @tc.step: step5. call SetSelection again
     */
    richEditorPattern->SetSelection(1, 2, options, false);
    richEditorPattern->OnModifyDone();
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 1);
    EXPECT_FALSE(richEditorPattern->SelectOverlayIsOn());

    /**
     * @tc.step: step6. test OnMenuItemAction again
     */
    selectOverlay->OnMenuItemAction(OptionMenuActionId::SELECT_ALL, OptionMenuType::NO_MENU);
    auto selectOverlayInfo = selectOverlay->GetSelectOverlayInfo();
    auto selectInfoFirstHandle = selectOverlayInfo->firstHandle;
    EXPECT_FALSE(selectInfoFirstHandle.isShow);
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());
}

/**
 * @tc.name: OnMenuItemAction004
 * @tc.desc: test OnMenuItemAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMenuTestNg, OnMenuItemAction004, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_EQ(richEditorPattern->OnBackPressed(), false);
    auto offsetF = OffsetF(5.0f, 30.0f);
    RectF rect(testNumber0, testNumber0, testNumber5, testNumber5);
    richEditorPattern->CreateHandles();
    richEditorPattern->textSelector_.Update(0, testNumber5);
    richEditorPattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::DISAPPEAR, OptionMenuType::MOUSE_MENU);
}

/**
 * @tc.name: OnMenuItemAction005
 * @tc.desc: test OnMenuItemAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMenuTestNg, OnMenuItemAction005, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_EQ(richEditorPattern->OnBackPressed(), false);
    auto offsetF = OffsetF(5.0f, 30.0f);
    RectF rect(testNumber0, testNumber0, testNumber5, testNumber5);
    richEditorPattern->CreateHandles();
    richEditorPattern->textSelector_.Update(0, testNumber5);
    richEditorPattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::APPEAR, OptionMenuType::MOUSE_MENU);
}

/**
 * @tc.name: OnMenuItemAction006
 * @tc.desc: test OnMenuItemAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMenuTestNg, OnMenuItemAction006, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_EQ(richEditorPattern->OnBackPressed(), false);
    auto offsetF = OffsetF(5.0f, 30.0f);
    RectF rect(testNumber0, testNumber0, testNumber5, testNumber5);
    richEditorPattern->CreateHandles();
    richEditorPattern->textSelector_.Update(0, testNumber5);
    richEditorPattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::CAMERA_INPUT, OptionMenuType::MOUSE_MENU);
}

/**
 * @tc.name: OnMenuItemAction007
 * @tc.desc: test OnMenuItemAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMenuTestNg, OnMenuItemAction007, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::AI_WRITE, OptionMenuType::MOUSE_MENU);
    EXPECT_NE(richEditorPattern->aiWriteAdapter_, nullptr);
}

/**
 * @tc.name: SelectionMenuOptionsTest001
 * @tc.desc: test SelectionMenuOptions
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMenuTestNg, SelectionMenuOptionsTest001, TestSize.Level1)
{
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::vector<NG::MenuOptionsParam> menuOptionsItems;
    NG::MenuOptionsParam menuOptionsParam1;
    menuOptionsParam1.content = "按钮1";
    menuOptionsParam1.icon = TEST_IMAGE_SOURCE;
    menuOptionsItems.push_back(menuOptionsParam1);

    NG::MenuOptionsParam menuOptionsParam2;
    menuOptionsParam2.content = "按钮2";
    menuOptionsParam2.icon = TEST_IMAGE_SOURCE;
    menuOptionsItems.push_back(menuOptionsParam2);

    NG::MenuOptionsParam menuOptionsParam3;
    menuOptionsParam3.content = "按钮3";
    menuOptionsParam3.icon = TEST_IMAGE_SOURCE;
    menuOptionsItems.push_back(menuOptionsParam3);
    OnCreateMenuCallback onCreateMenuCallback;
    OnMenuItemClickCallback onMenuItemClick;
    richEditorPattern->OnSelectionMenuOptionsUpdate(std::move(onCreateMenuCallback), std::move(onMenuItemClick));
}

/**
 * @tc.name: SelectionMenuOptionsTest002
 * @tc.desc: test SelectionMenuOptions
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMenuTestNg, SelectionMenuOptionsTest002, TestSize.Level1)
{
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::vector<NG::MenuOptionsParam> menuOptionsItems;
    NG::MenuOptionsParam menuOptionsParam1;
    menuOptionsParam1.content = "按钮1";
    menuOptionsItems.push_back(menuOptionsParam1);

    NG::MenuOptionsParam menuOptionsParam2;
    menuOptionsParam2.content = "按钮2";
    menuOptionsItems.push_back(menuOptionsParam2);

    NG::MenuOptionsParam menuOptionsParam3;
    menuOptionsParam3.content = "按钮3";
    menuOptionsItems.push_back(menuOptionsParam3);
    OnCreateMenuCallback onCreateMenuCallback;
    OnMenuItemClickCallback onMenuItemClick;
    richEditorPattern->OnSelectionMenuOptionsUpdate(std::move(onCreateMenuCallback), std::move(onMenuItemClick));
}

/**
 * @tc.name: BuilderSpanBindSelectionMenu001
 * @tc.desc: Test bind selection menu on BuilderSpan.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMenuTestNg, BuilderSpanBindSelectionMenu001, TestSize.Level1)
{
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ResultObject objText;
    objText.type = SelectSpanType::TYPESPAN;
    ResultObject objImage;
    objImage.type = SelectSpanType::TYPEIMAGE;
    objImage.valueString = u" ";
    objImage.valuePixelMap = PixelMap::CreatePixelMap(nullptr);
    ResultObject objBuilder;
    objBuilder.type = SelectSpanType::TYPEIMAGE;
    objBuilder.valueString = u" ";
    objBuilder.valuePixelMap = nullptr;
    SelectionInfo originalSelection;
    SelectionInfo adjustedSelection;

    // 0: Select BuilderSpan
    originalSelection.selection_.resultObjects.push_front(objBuilder);
    adjustedSelection = richEditorPattern->GetAdjustedSelectionInfo(originalSelection);
    richEditorPattern->UpdateSelectionType(adjustedSelection);
    EXPECT_EQ(richEditorPattern->selectedType_.value(), TextSpanType::BUILDER);

    // 1: Select BuilderSpan and TextSpan
    originalSelection.selection_.resultObjects.push_front(objText);
    adjustedSelection = richEditorPattern->GetAdjustedSelectionInfo(originalSelection);
    richEditorPattern->UpdateSelectionType(adjustedSelection);
    EXPECT_EQ(richEditorPattern->selectedType_.value(), TextSpanType::MIXED);

    // 2: Select BuilderSpan、TextSpan and ImageSpan
    originalSelection.selection_.resultObjects.push_front(objImage);
    adjustedSelection = richEditorPattern->GetAdjustedSelectionInfo(originalSelection);
    richEditorPattern->UpdateSelectionType(adjustedSelection);
    EXPECT_EQ(richEditorPattern->selectedType_.value(), TextSpanType::MIXED);
}

/**
 * @tc.name: SelectionMenuInteraction001
 * @tc.desc: Test the interaction between selection menu and click event.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMenuTestNg, SelectionMenuInteraction001, TestSize.Level1)
{
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::vector<RectF> rects { RectF(0.0, 0.0, 200.0, 200.0) };
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    richEditorPattern->paragraphs_.AddParagraph({ .paragraph = paragraph, .start = 0, .end = 10 });
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<THIRD_PARAM>(rects));
    
    // 0: Show selectOverlay
    richEditorPattern->textSelector_.Update(0, 1);
    ASSERT_NE(richEditorPattern->selectOverlay_, nullptr);
    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    ASSERT_TRUE(richEditorPattern->SelectOverlayIsOn());

    // 1: Toggle the menu when the selection area is clicked
    GestureEvent info;
    info.deviceType_ = SourceType::TOUCH;
    info.localLocation_ = Offset(50, 50);
    info.globalLocation_ = Offset(50, 50);
    auto manager = richEditorPattern->selectOverlay_->GetManager<SelectContentOverlayManager>();
    ASSERT_NE(manager, nullptr);
    manager->ShowOptionMenu();
    richEditorPattern->HandleClickSelection(info);
    EXPECT_FALSE(richEditorPattern->selectOverlay_->GetSelectOverlayInfo()->menuInfo.menuIsShow);
    richEditorPattern->HandleClickSelection(info);
    EXPECT_TRUE(richEditorPattern->selectOverlay_->GetSelectOverlayInfo()->menuInfo.menuIsShow);
}

/**
 * @tc.name: CloseSystemMenu001
 * @tc.desc: test CloseSystemMenu
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMenuTestNg, CloseSystemMenu001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->selectOverlay_->bindManager_.Reset();
    richEditorPattern->CloseSystemMenu();
    EXPECT_FALSE(richEditorPattern->SelectOverlayIsOn());
}

/**
 * @tc.name: CloseSystemMenu002
 * @tc.desc: test CloseSystemMenu
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMenuTestNg, CloseSystemMenu002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.steps: step1. get richeditor pattern and add add text span
     */
    AddSpan("hello1");
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 6);

    /**
     * @tc.steps: step2. request focus
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    focusHub->RequestFocusImmediately();

    auto eventHub = richEditorPattern->GetOrCreateEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);

    bool enabledCache = eventHub->IsEnabled();
    EXPECT_EQ(enabledCache, true);

    /**
     * @tc.step: step3. create a scene where the text menu has popped up
     */
    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->enabled_ = true;
    richEditorPattern->OnModifyDone();

    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->enabled_ = false;
    richEditorPattern->OnModifyDone();

    richEditorPattern->textDetectEnable_ = false;
    richEditorPattern->enabled_ = true;
    richEditorPattern->OnModifyDone();

    richEditorPattern->textDetectEnable_ = false;
    richEditorPattern->enabled_ = false;
    richEditorPattern->OnModifyDone();

    richEditorPattern->textSelector_.Update(1, 2);
    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);

    richEditorPattern->CloseSystemMenu();

    EXPECT_EQ(richEditorPattern->SelectOverlayIsOn(), false);
}

/**
 * @tc.name: CloseSystemMenu003
 * @tc.desc: test CloseSystemMenu
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMenuTestNg, CloseSystemMenu003, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CloseSystemMenu();
    EXPECT_FALSE(richEditorPattern->SelectOverlayIsOn());

    auto selectOverlayInfo = richEditorPattern->selectOverlay_->GetSelectOverlayInfo();
    selectOverlayInfo->menuInfo.menuBuilder = []() { return; };
    EXPECT_TRUE(selectOverlayInfo->menuInfo.menuBuilder);
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    ASSERT_TRUE(richEditorPattern->SelectOverlayIsOn());
    richEditorPattern->CloseSystemMenu();
    EXPECT_FALSE(richEditorPattern->SelectOverlayIsOn());
}

/**
 * @tc.name: HandleMenuCallbackOnSelectAll001
 * @tc.desc: test HandleMenuCallbackOnSelectAll
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMenuTestNg, HandleMenuCallbackOnSelectAll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richeditor pattern and add add text span
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 6);

    /**
     * @tc.steps: step2. request focus
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    focusHub->RequestFocusImmediately();

    /**
     * @tc.step: step3. create a scene where the text menu has popped up
     */
    richEditorPattern->OnModifyDone();
    richEditorPattern->textSelector_.Update(1, 2);
    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());

    /**
     * @tc.step: step4. test OnMenuItemAction
     */
    richEditorPattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::COPY, OptionMenuType::TOUCH_MENU);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 1);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 2);

    richEditorPattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::PASTE, OptionMenuType::NO_MENU);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 6);

    auto selectOverlayInfo = richEditorPattern->selectOverlay_->GetSelectOverlayInfo();
    richEditorPattern->selectOverlay_->isUsingMouse_ = true;
    EXPECT_EQ(richEditorPattern->selectOverlay_->IsUsingMouse(), true);
    richEditorPattern->HandleMenuCallbackOnSelectAll();
    ASSERT_EQ(richEditorPattern->IsUsingMouse(), false);
}

/**
 * @tc.name: HandleMenuCallbackOnSelectAll002
 * @tc.desc: test RichEditorPattern HandleMenuCallbackOnSelectAll
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMenuTestNg, HandleMenuCallbackOnSelectAll002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.steps: step1. get richeditor pattern and add add text span
     */
    AddSpan("hello1");
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 6);

    /**
     * @tc.steps: step2. request focus
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    focusHub->RequestFocusImmediately();

    auto eventHub = richEditorPattern->GetOrCreateEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);

    bool enabledCache = eventHub->IsEnabled();
    EXPECT_EQ(enabledCache, true);

    /**
     * @tc.step: step3. create a scene where the text menu has popped up
     */
    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->enabled_ = true;
    richEditorPattern->OnModifyDone();

    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->enabled_ = false;
    richEditorPattern->OnModifyDone();

    richEditorPattern->textDetectEnable_ = false;
    richEditorPattern->enabled_ = true;
    richEditorPattern->OnModifyDone();

    richEditorPattern->textDetectEnable_ = false;
    richEditorPattern->enabled_ = false;
    richEditorPattern->OnModifyDone();

    richEditorPattern->textSelector_.Update(1, 2);
    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());

    /**
     * @tc.step: step4. test OnMenuItemAction
     */
    richEditorPattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::COPY, OptionMenuType::TOUCH_MENU);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 1);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 2);

    richEditorPattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::PASTE, OptionMenuType::NO_MENU);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 6);

    richEditorPattern->selectOverlay_->isUsingMouse_ = true;
    richEditorPattern->HandleMenuCallbackOnSelectAll();
    ASSERT_EQ(richEditorPattern->IsUsingMouse(), false);
}

/**
 * @tc.name: IsMenuItemShow001
 * @tc.desc: test IsMenuItemShow
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMenuTestNg, IsMenuItemShow001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;
    auto theme = AceType::MakeRefPtr<RichEditorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));
    theme->searchIsSupport_ = true;
    theme->translateIsSupport_ = true;

    auto showSearch = richEditorPattern->IsShowSearch();
    EXPECT_TRUE(showSearch);
    auto showTranslate = richEditorPattern->IsShowTranslate();
    EXPECT_TRUE(showTranslate);
}

/**
 * @tc.name: IsMenuItemShow002
 * @tc.desc: test menu search and translate item
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMenuTestNg, IsMenuItemShow002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step1. searchIsSupport_ set to true.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;
    auto theme = AceType::MakeRefPtr<RichEditorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));
    theme->searchIsSupport_ = true;
    auto showSearch = richEditorPattern->IsShowSearch();
    EXPECT_TRUE(showSearch);
    theme->translateIsSupport_ = true;
    auto showTranslate = richEditorPattern->IsShowTranslate();
    EXPECT_TRUE(showTranslate);

    auto selectOverlay = richEditorPattern->selectOverlay_;
    ASSERT_NE(selectOverlay, nullptr);

    /**
     * @tc.steps: step2. add text\image\symbol.
     */
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    richEditorController->AddTextSpan(options);
    AddImageSpan();
    richEditorPattern->AddSymbolSpan(SYMBOL_SPAN_OPTIONS_1);

    /**
     * @tc.steps: step3. select text.
     */
    richEditorPattern->textSelector_.Update(0, 6);
    richEditorPattern->copyOption_ = CopyOptions::Local;
    SelectMenuInfo menuInfo;
    selectOverlay->OnUpdateMenuInfo(menuInfo, DIRTY_ALL_MENU_ITEM);
    ASSERT_EQ(menuInfo.showSearch, true);
    ASSERT_EQ(menuInfo.showTranslate, true);

    /**
     * @tc.steps: step4. select image.
     */
    richEditorPattern->textSelector_.Update(6, 7);
    selectOverlay->OnUpdateMenuInfo(menuInfo, DIRTY_ALL_MENU_ITEM);
    ASSERT_EQ(menuInfo.showSearch, false);
    ASSERT_EQ(menuInfo.showTranslate, false);

    /**
     * @tc.steps: step5. select symbol.
     */
    richEditorPattern->textSelector_.Update(7, 8);
    selectOverlay->OnUpdateMenuInfo(menuInfo, DIRTY_ALL_MENU_ITEM);
    ASSERT_EQ(menuInfo.showSearch, false);
    ASSERT_EQ(menuInfo.showTranslate, false);

    /**
     * @tc.steps: step6. mixed selection.
     */
    richEditorPattern->textSelector_.Update(0, 8);
    selectOverlay->OnUpdateMenuInfo(menuInfo, DIRTY_ALL_MENU_ITEM);
    ASSERT_EQ(menuInfo.showSearch, true);
    ASSERT_EQ(menuInfo.showTranslate, true);
}

/**
 * @tc.name: SetPreviewMenuParam001
 * @tc.desc: test SetPreviewMenuParam
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMenuTestNg, SetPreviewMenuParam001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TextSpanType spanType = TextSpanType::IMAGE;
    std::function<void()> builder;
    SelectMenuParam menuParam;
    richEditorPattern->SetPreviewMenuParam(spanType, builder, menuParam);

    richEditorPattern->SetPreviewMenuParam(spanType, builder, menuParam);
    EXPECT_TRUE(richEditorPattern->oneStepDragController_);
}

/**
 * @tc.name: OnSelectionMenuOptionsUpdate001
 * @tc.desc: test OnSelectionMenuOptionsUpdate
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMenuTestNg, OnSelectionMenuOptionsUpdate001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    OnCreateMenuCallback onCreateMenuCallback;
    OnMenuItemClickCallback onMenuItemClick;
    richEditorPattern->OnSelectionMenuOptionsUpdate(std::move(onCreateMenuCallback), std::move(onMenuItemClick));
}

/**
 * @tc.name: HandleOnShowMenu001
 * @tc.desc: test HandleOnShowMenu
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMenuTestNg, HandleOnShowMenu001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->overlayMod_ = nullptr;
    richEditorPattern->HandleOnShowMenu();
    EXPECT_EQ(richEditorPattern->overlayMod_, nullptr);
}

/**
 * @tc.name: HideMenu001
 * @tc.desc: test HideMenu
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMenuTestNg, HideMenu001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->HideMenu();
    EXPECT_NE(richEditorPattern->selectOverlay_, nullptr);
}

/**
 * @tc.name: UpdateAIMenuOptions
 * @tc.desc: test UpdateAIMenuOptions function with valid textSelector
 *           check single ai entity in selection range
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMenuTestNg, UpdateAIMenuOptions001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();

    /**
     * @tc.steps: step1. preset conditions
     */
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->content = std::get<std::u16string>(U16_TEXT_FOR_AI_INFO.content);
    spanItem->position = spanItem->content.length();
    pattern->spans_.emplace_back(spanItem);

    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 20, 20) };
    EXPECT_CALL(*mockParagraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));
    pattern->pManager_->AddParagraph({ .paragraph = mockParagraph, .start = 0, .end = 100 });

    pattern->SetTextDetectEnable(true);
    pattern->copyOption_ = CopyOptions::Local;

    auto aiSpan1 = U16_TEXT_FOR_AI_INFO.aiSpans[0];
    auto aiSpan2 = U16_TEXT_FOR_AI_INFO.aiSpans[1];
    std::map<int32_t, Ace::AISpan> aiSpanMap;
    aiSpanMap[aiSpan1.start] = aiSpan1;
    aiSpanMap[aiSpan2.start] = aiSpan2;
    pattern->dataDetectorAdapter_->aiSpanMap_ = aiSpanMap;

    /**
     * @tc.steps: step2. call UpdateAIMenuOptions function.
     */
    pattern->textSelector_.Update(0, 22);
    pattern->UpdateAIMenuOptions();
    pattern->HandleAIMenuOption();
    EXPECT_EQ(pattern->GetAIItemOption().size(), 1);
    auto aiSpan = pattern->GetAIItemOption().begin()->second;
    EXPECT_EQ(aiSpan.type, TextDataDetectType::PHONE_NUMBER);
    EXPECT_EQ(pattern->IsShowAIMenuOption(), true);

    pattern->textSelector_.Update(20, 37);
    pattern->UpdateAIMenuOptions();
    EXPECT_EQ(pattern->GetAIItemOption().size(), 1);
    aiSpan = pattern->GetAIItemOption().begin()->second;
    EXPECT_EQ(aiSpan.type, TextDataDetectType::URL);
    EXPECT_EQ(pattern->IsShowAIMenuOption(), true);
}

/**
 * @tc.name: UpdateAIMenuOptions
 * @tc.desc: test UpdateAIMenuOptions function with valid textSelector
 *           check multi ai entity in selection range
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMenuTestNg, UpdateAIMenuOptions002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();

    /**
     * @tc.steps: step1. prepare spanItem with at least 2 ai entity
     */
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->content = std::get<std::u16string>(U16_TEXT_FOR_AI_INFO_2.content);
    spanItem->position = spanItem->content.length();
    pattern->spans_.emplace_back(spanItem);

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> selectedRects { RectF(0, 0, 20, 20), RectF(30, 30, 20, 20), RectF(60, 60, 20, 20) };
    EXPECT_CALL(*paragraph, GetRectsForPlaceholders(_)).WillRepeatedly(SetArgReferee<0>(selectedRects));
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });

    pattern->SetTextDetectEnable(true);
    pattern->copyOption_ = CopyOptions::Local;

    auto aiSpan1 = U16_TEXT_FOR_AI_INFO_2.aiSpans[0];
    auto aiSpan2 = U16_TEXT_FOR_AI_INFO_2.aiSpans[1];
    std::map<int32_t, Ace::AISpan> aiSpanMap;
    aiSpanMap[aiSpan1.start] = aiSpan1;
    aiSpanMap[aiSpan2.start] = aiSpan2;
    pattern->dataDetectorAdapter_->aiSpanMap_ = aiSpanMap;

    /**
     * @tc.steps: step2. call UpdateAIMenuOptions function.
     * @tc.expected: isShowAIMenuOption is false.
     */
    pattern->textSelector_.Update(0, 40);
    pattern->UpdateAIMenuOptions();
    EXPECT_EQ(pattern->GetAIItemOption().size(), 1);
    auto aiSpan = pattern->GetAIItemOption().begin()->second;
    EXPECT_EQ(aiSpan.type, TextDataDetectType::EMAIL);
    EXPECT_EQ(pattern->IsShowAIMenuOption(), false);

    pattern->textSelector_.Update(7, 19);
    pattern->SetTextDetectEnable(false);
    pattern->UpdateAIMenuOptions();
    EXPECT_EQ(pattern->IsShowAIMenuOption(), false);

    pattern->SetTextDetectEnable(true);
    pattern->copyOption_ = CopyOptions::InApp;
    pattern->UpdateAIMenuOptions();
    EXPECT_EQ(pattern->IsShowAIMenuOption(), false);
}
}