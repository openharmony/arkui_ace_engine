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

#include <memory>

#include "foundation/arkui/ace_engine/test/mock/core/render/mock_paragraph.h"
#include "gtest/gtest.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "text_base.h"
#include "ui/base/ace_type.h"
#include "ui/base/referenced.h"

namespace OHOS::Ace::NG {

class TextThirteenTestNg : public TextBases {};

/**
 * @tc.name: CollectTextSpanNodes_onLongPress
 * @tc.desc: Test TextPattern CollectTextSpanNodes
 * @tc.type: FUNC
 */
HWTEST_F(TextThirteenTestNg, CollectTextSpanNodes_onLongPress, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    auto pattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create a SpanNode and set its spanItem.
     * set the isSpanHasLongPress to false.
     */
    RefPtr<DataDetectorAdapter> dataDetectorAdapter = AceType::MakeRefPtr<DataDetectorAdapter>();
    pattern->dataDetectorAdapter_ = dataDetectorAdapter;
    RefPtr<SpanNode> spanNode = AceType::MakeRefPtr<SpanNode>(2);
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    spanNode->SetSpanItem(spanItem);
    std::u16string newContent = u"Hello World";
    spanNode->UpdateContent(newContent);
    auto onLongPress = [](GestureEvent& func) {};
    spanNode->UpdateOnLongPressEvent(std::move(onLongPress));
    bool isSpanHasClick = false;
    bool isSpanHasLongPress = false;

    /**
     * @tc.steps: step3. Calling the CollectTextSpanNodes function
     * @tc.expected: The isSpanHasLongPress from false to true.
     */
    pattern->CollectTextSpanNodes(spanNode, isSpanHasClick, isSpanHasLongPress);
    EXPECT_TRUE(isSpanHasLongPress);
}

/**
 * @tc.name: SetSpanItemEvent_clickCall
 * @tc.desc: Test TextPattern SetSpanItemEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextThirteenTestNg, SetSpanItemEvent_clickCall, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    auto pattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create a spanItem and focusHub.
     * set the spanItem->onClick from nullptr to a valid function.
     */
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->onClick = nullptr;
    auto focusHub = textNode->GetOrCreateFocusHub();
    auto onClickEventCallback = [](GestureEvent& func) {};
    focusHub->SetOnClickCallback(std::move(onClickEventCallback));

    /**
     * @tc.steps: step3. Calling the SetSpanItemEvent function
     * @tc.expected: The spanItem->onClick from nullptr to a valid function.
     */
    pattern->SetSpanItemEvent(spanItem, focusHub);
    EXPECT_NE(spanItem->onClick, nullptr);
}

/**
 * @tc.name: SetSpanItemEvent_longPressCallback
 * @tc.desc: Test TextPattern SetSpanItemEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextThirteenTestNg, SetSpanItemEvent_longPressCallback, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    auto pattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create a spanItem and focusHub.
     * set the onLongPress to nullptr.
     */
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->onLongPress = nullptr;
    auto focusHub = textNode->GetOrCreateFocusHub();
    auto onSpanLongPressEventCallback = [](GestureEvent& func) {};
    focusHub->SetOnLongPressCallback(std::move(onSpanLongPressEventCallback));

    /**
     * @tc.steps: step3. Calling the CollectTextSpanNodes function
     * @tc.expected: The spanItem->onLongPress from nullptr to a valid function.
     */
    pattern->SetSpanItemEvent(spanItem, focusHub);
    EXPECT_NE(spanItem->onLongPress, nullptr);
}

/**
 * @tc.name: DumpSimplifyInfo_001
 * @tc.desc: Test TextPattern DumpSimplifyInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextThirteenTestNg, DumpSimplifyInfo_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    RefPtr<TextLayoutProperty> layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    textNode->SetLayoutProperty(layoutProperty);
    auto pattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create a json.
     * and set IsSetObscured to return true.
     */
    auto json = JsonUtil::CreateSharedPtrJson(true);
    pattern->spans_.clear();
    std::vector<ObscuredReasons> obscured;
    obscured.emplace_back(ObscuredReasons::PLACEHOLDER);
    textNode->GetRenderContext()->UpdateObscured(obscured);

    /**
     * @tc.steps: step3. Calling the DumpSimplifyInfo function
     * @tc.expected: The "content" to "".
     */
    pattern->DumpSimplifyInfo(json);
    EXPECT_EQ(json->GetString("content"), "");
}

/**
 * @tc.name: DumpSimplifyInfo_002
 * @tc.desc: Test TextPattern DumpSimplifyInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextThirteenTestNg, DumpSimplifyInfo_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    RefPtr<TextLayoutProperty> layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    textNode->SetLayoutProperty(layoutProperty);
    auto pattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create a json.
     * Create a pManager
     */
    auto json = JsonUtil::CreateSharedPtrJson(true);
    pattern->spans_.clear();
    RefPtr<ParagraphManager> pManager = AceType::MakeRefPtr<ParagraphManager>();
    pattern->pManager_ = pManager;

    /**
     * @tc.steps: step3. Calling the DumpSimplifyInfo function
     * @tc.expected: The "content" to "".
     */
    pattern->DumpSimplifyInfo(json);
    EXPECT_EQ(json->GetString("content"), "");
}

/**
 * @tc.name: DumpSimplifyInfo_003
 * @tc.desc: Test TextPattern DumpSimplifyInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextThirteenTestNg, DumpSimplifyInfo_003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    RefPtr<TextLayoutProperty> layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    textNode->SetLayoutProperty(layoutProperty);
    auto pattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create a json.
     * Create a paragraph of paragraphInfo
     */
    auto json = JsonUtil::CreateSharedPtrJson(true);
    pattern->spans_.clear();
    RefPtr<ParagraphManager> pManager = AceType::MakeRefPtr<ParagraphManager>();
    ParagraphManager::ParagraphInfo paragraphInfo;
    RefPtr<MockParagraph> paragraph = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*paragraph, GetParagraphText()).WillRepeatedly(testing::Return(u"hello"));
    paragraphInfo.paragraph = paragraph;
    std::vector<ParagraphManager::ParagraphInfo> paragraphs = { paragraphInfo };
    pManager->SetParagraphs(paragraphs);
    pattern->pManager_ = pManager;

    /**
     * @tc.steps: step3. Calling the DumpSimplifyInfo function
     * @tc.expected: The "content" to "hello".
     */
    pattern->DumpSimplifyInfo(json);
    EXPECT_EQ(json->GetString("content"), "hello");
}

/**
 * @tc.name: DumpSimplifyInfo_004
 * @tc.desc: Test TextPattern DumpSimplifyInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextThirteenTestNg, DumpSimplifyInfo_004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    RefPtr<TextLayoutProperty> layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    textNode->SetLayoutProperty(layoutProperty);
    auto pattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create a json.
     * Create a paragraphInfo of pManager
     */
    auto json = JsonUtil::CreateSharedPtrJson(true);
    pattern->spans_.clear();
    RefPtr<ParagraphManager> pManager = AceType::MakeRefPtr<ParagraphManager>();
    ParagraphManager::ParagraphInfo paragraphInfo;
    std::vector<ParagraphManager::ParagraphInfo> paragraphs = { paragraphInfo };
    pManager->SetParagraphs(paragraphs);
    pattern->pManager_ = pManager;

    /**
     * @tc.steps: step3. Calling the DumpSimplifyInfo function
     * @tc.expected: The "content" to "".
     */
    pattern->DumpSimplifyInfo(json);
    EXPECT_EQ(json->GetString("content"), "");
}

/**
 * @tc.name: CopyBindSelectionMenuParams_onAppear
 * @tc.desc: Test TextPattern CopyBindSelectionMenuParams
 * @tc.type: FUNC
 */
HWTEST_F(TextThirteenTestNg, CopyBindSelectionMenuParams_onAppear, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    auto pattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create a selectInfo and SelectionMenuParams
     * Set appear to false
     */
    SelectOverlayInfo selectInfo;
    auto buildUI = []() {};
    bool appear = false;
    auto handleAppear = [&appear](int32_t x, int32_t y) { appear = true; };
    auto handleDisappear = []() {};
    std::shared_ptr<SelectionMenuParams> menuParams = std::make_shared<SelectionMenuParams>(
        TextSpanType::TEXT, buildUI, handleAppear, handleDisappear, TextResponseType::SELECTED_BY_MOUSE);

    /**
     * @tc.steps: step3. Calling the CopyBindSelectionMenuParams function
     * @tc.expected: The appear return true
     */
    pattern->CopyBindSelectionMenuParams(selectInfo, menuParams);
    auto onAppear = selectInfo.menuCallback.onAppear;
    onAppear();
    EXPECT_TRUE(appear);
}

/**
 * @tc.name: CopyBindSelectionMenuParams_onMenuShow
 * @tc.desc: Test TextPattern CopyBindSelectionMenuParams
 * @tc.type: FUNC
 */
HWTEST_F(TextThirteenTestNg, CopyBindSelectionMenuParams_onMenuShow, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    auto pattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create a selectInfo and SelectionMenuParams
     * Set onCallback to false
     */
    SelectOverlayInfo selectInfo;
    auto buildUI = []() {};
    auto handleAppear = [](int32_t x, int32_t y) {};
    auto handleDisappear = []() {};
    std::shared_ptr<SelectionMenuParams> menuParams = std::make_shared<SelectionMenuParams>(
        TextSpanType::TEXT, buildUI, handleAppear, handleDisappear, TextResponseType::SELECTED_BY_MOUSE);
    bool callback = false;
    auto onCallback = [&callback](int32_t x, int32_t y) { callback = true; };
    menuParams->onMenuShow = onCallback;

    /**
     * @tc.steps: step3. Calling the CopyBindSelectionMenuParams function
     * @tc.expected: The onCallback return true
     */
    pattern->CopyBindSelectionMenuParams(selectInfo, menuParams);
    auto onMenuShow = selectInfo.menuCallback.onMenuShow;
    onMenuShow();
    EXPECT_TRUE(callback);
}

/**
 * @tc.name: CopyBindSelectionMenuParams_onMenuHide
 * @tc.desc: Test TextPattern CopyBindSelectionMenuParams
 * @tc.type: FUNC
 */
HWTEST_F(TextThirteenTestNg, CopyBindSelectionMenuParams_onMenuHide, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    auto pattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create a selectInfo and SelectionMenuParams
     * Set onCallback to false
     */
    SelectOverlayInfo selectInfo;
    auto buildUI = []() {};
    auto handleAppear = [](int32_t x, int32_t y) {};
    auto handleDisappear = []() {};
    std::shared_ptr<SelectionMenuParams> menuParams = std::make_shared<SelectionMenuParams>(
        TextSpanType::TEXT, buildUI, handleAppear, handleDisappear, TextResponseType::SELECTED_BY_MOUSE);
    menuParams->onMenuShow = [](int32_t x, int32_t y) {};
    bool callback = false;
    auto onCallback = [&callback](int32_t x, int32_t y) { callback = true; };
    menuParams->onMenuHide = onCallback;

    /**
     * @tc.steps: step3. Calling the CopyBindSelectionMenuParams function
     * @tc.expected: The callback return true
     */
    pattern->CopyBindSelectionMenuParams(selectInfo, menuParams);
    auto onMenuHide = selectInfo.menuCallback.onMenuHide;
    onMenuHide();
    EXPECT_TRUE(callback);
}

/**
 * @tc.name: RegisterFormVisibleChangeCallback_formCallback
 * @tc.desc: Test TextPattern RegisterFormVisibleChangeCallback
 * @tc.type: FUNC
 */
HWTEST_F(TextThirteenTestNg, RegisterFormVisibleChangeCallback_formCallback, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    textNode->SetLayoutProperty(textLayoutProperty);
    auto pattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set hasRegisterFormVisibleCallback_ to false
     * set TextOverflow to MARQUEE
     */
    pattern->hasRegisterFormVisibleCallback_ = false;
    auto layoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    layoutProperty->UpdateTextOverflow(TextOverflow::MARQUEE);
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    context->SetIsFormRender(true);
    textNode->context_ = AceType::RawPtr(context);

    /**
     * @tc.steps: step3. Calling the RegisterFormVisibleChangeCallback and formCallback function
     * @tc.expected: The hasRegisterFormVisibleCallback_ return true
     */
    pattern->RegisterFormVisibleChangeCallback();
    auto formCallback = textNode->context_->GetFormVisibleManager()->onFormVisibleChangeEvents_[0];
    formCallback(true);
    textNode->context_ = nullptr;
    EXPECT_TRUE(pattern->hasRegisterFormVisibleCallback_);
}

/**
 * @tc.name: IsLocationInFrameRegion
 * @tc.desc: Test TextPattern IsLocationInFrameRegion
 * @tc.type: FUNC
 */
HWTEST_F(TextThirteenTestNg, IsLocationInFrameRegion, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    auto pattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set localOffset and size
     */
    Offset localOffset(2.0, 4.0);
    SizeF size(8.0f, 10.0f);
    textNode->GetGeometryNode()->SetFrameSize(size);

    /**
     * @tc.steps: step3. Calling the IsLocationInFrameRegion function
     * @tc.expected: The result return true
     */
    auto result = pattern->IsLocationInFrameRegion(localOffset);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: RegisterVisibleAreaChangeCallback_else
 * @tc.desc: Test TextPattern RegisterVisibleAreaChangeCallback
 * @tc.type: FUNC
 */
HWTEST_F(TextThirteenTestNg, RegisterVisibleAreaChangeCallback_else, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto textNode = FrameNode::CreateFrameNode(V2::SYMBOL_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    textNode->SetLayoutProperty(textLayoutProperty);
    auto pattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set isRegisteredAreaCallback_ to true
     * create the context
     */
    auto layoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    layoutProperty->SetIsLoopAnimation(false);
    pattern->isRegisteredAreaCallback_ = true;
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    context->SetIsFormRender(true);
    textNode->context_ = AceType::RawPtr(context);

    /**
     * @tc.steps: step3. Calling the RegisterVisibleAreaChangeCallback function
     * @tc.expected: The isRegisteredAreaCallback_ return false
     */
    pattern->RegisterVisibleAreaChangeCallback();
    textNode->context_ = nullptr;
    EXPECT_FALSE(pattern->isRegisteredAreaCallback_);
}
} // namespace OHOS::Ace::NG