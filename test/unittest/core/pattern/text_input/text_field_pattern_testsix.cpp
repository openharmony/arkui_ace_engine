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

#include "text_input_base.h"

#include "test/mock/core/common/mock_container.h"

#include "core/components_ng/pattern/stage/page_pattern.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TextFieldPatternTestSix : public TextInputBases {
public:
};

/**
 * @tc.name: HandleOnDragStatusCallback001
 * @tc.desc: test testInput text HandleOnDragStatusCallback
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestSix, HandleOnDragStatusCallback001, TestSize.Level0)
{
    CreateTextField();
    auto notifyDragEvent = AceType::MakeRefPtr<NotifyDragEvent>();
    pattern_->isCaretTwinkling_ = true;
    pattern_->dragRecipientStatus_ = DragStatus::DRAGGING;
    pattern_->HandleOnDragStatusCallback(DragEventType::DROP, notifyDragEvent);
    ASSERT_FALSE(pattern_->isCaretTwinkling_);
    pattern_->isCaretTwinkling_ = true;
    pattern_->dragRecipientStatus_ = DragStatus::NONE;
    pattern_->HandleOnDragStatusCallback(DragEventType::DROP, notifyDragEvent);
    ASSERT_TRUE(pattern_->isCaretTwinkling_);
    pattern_->isCaretTwinkling_ = true;
    pattern_->HandleOnDragStatusCallback(DragEventType::ENTER, notifyDragEvent);
    ASSERT_TRUE(pattern_->isCaretTwinkling_);
}

/**
 * @tc.name: CheckMousePressedOverScrollBar001
 * @tc.desc: test testInput text CheckMousePressedOverScrollBar
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestSix, CheckMousePressedOverScrollBar001, TestSize.Level0)
{
    CreateTextField();
    GestureEvent info;
    ASSERT_FALSE(pattern_->CheckMousePressedOverScrollBar(info));
    info.localLocation_ = Offset(10, 30);
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
    scrollBar->isScrollable_ = true;
    scrollBar->barRect_ = Rect(0, 0, 12, 40);
    pattern_->scrollBar_ = scrollBar;
    ASSERT_FALSE(pattern_->CheckMousePressedOverScrollBar(info));
    pattern_->hasMousePressed_ = true;
    ASSERT_TRUE(pattern_->CheckMousePressedOverScrollBar(info));
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateDisplayMode(DisplayMode::OFF);
    ASSERT_FALSE(pattern_->CheckMousePressedOverScrollBar(info));
}

/**
 * @tc.name: FillTriggeredStateByType001
 * @tc.desc: test testInput text FillTriggeredStateByType
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestSix, FillTriggeredStateByType001, TestSize.Level0)
{
    CreateTextField();
    auto parentFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()); });
    frameNode_->SetParent(parentFrameNode);
    pattern_->firstAutoFillContainerNode_ = AceType::WeakClaim(AceType::RawPtr(parentFrameNode));
    pattern_->SetAutoFillTriggeredStateByType(AceAutoFillType::ACE_BANK_CARD_NUMBER);
    ASSERT_FALSE(pattern_->GetAutoFillTriggeredStateByType(AceAutoFillType::ACE_BANK_CARD_NUMBER));

    pattern_->SetAutoFillTriggeredStateByType(AceAutoFillType::ACE_PASSWORD);
    ASSERT_FALSE(pattern_->GetAutoFillTriggeredStateByType(AceAutoFillType::ACE_PASSWORD));

    pattern_->SetAutoFillTriggeredStateByType(AceAutoFillType::ACE_NEW_PASSWORD);
    ASSERT_FALSE(pattern_->GetAutoFillTriggeredStateByType(AceAutoFillType::ACE_NEW_PASSWORD));

    auto pipeline = frameNode_->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    CHECK_NULL_VOID(textFieldManager);
    auto passwordFrameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    passwordFrameNode->SetParent(parentFrameNode);
    auto passwordPattern = passwordFrameNode->GetPattern<TextFieldPattern>();
    std::unordered_map<int32_t, TextFieldInfo> nameAndPasswordInfoMap;
    TextFieldInfo textFieldInfo;
    textFieldInfo.nodeId = frameNode_->GetId();
    nameAndPasswordInfoMap[textFieldInfo.nodeId] = textFieldInfo;
    TextFieldInfo textFieldInfo2;
    textFieldInfo2.nodeId = passwordFrameNode->GetId();
    textFieldInfo2.inputType = TextInputType::NEW_PASSWORD;
    textFieldInfo2.enableAutoFill = true;
    nameAndPasswordInfoMap[passwordFrameNode->GetId()] = textFieldInfo2;
    std::unordered_map<int32_t, std::unordered_map<int32_t, TextFieldInfo>> textFieldInfoMap;
    textFieldInfoMap[parentFrameNode->GetId()] = nameAndPasswordInfoMap;
    textFieldManager->textFieldInfoMap_ = textFieldInfoMap;
    ASSERT_TRUE(textFieldManager->HasAutoFillPasswordNodeInContainer(parentFrameNode->GetId(), frameNode_->GetId()));
    pattern_->SetAutoFillTriggeredStateByType(AceAutoFillType::ACE_UNSPECIFIED);
    ASSERT_FALSE(pattern_->GetAutoFillTriggeredStateByType(AceAutoFillType::ACE_UNSPECIFIED));

    pattern_->SetAutoFillTriggeredStateByType(AceAutoFillType::ACE_USER_NAME);
    ASSERT_FALSE(pattern_->GetAutoFillTriggeredStateByType(AceAutoFillType::ACE_USER_NAME));
}

/**
 * @tc.name: GetAutoFillTypeAndMetaData001
 * @tc.desc: test testInput text GetAutoFillTypeAndMetaData
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestSix, GetAutoFillTypeAndMetaData001, TestSize.Level0)
{
    CreateTextField();
    auto hintToTypeWrap = pattern_->GetAutoFillTypeAndMetaData(false);
    ASSERT_EQ(hintToTypeWrap.autoFillType, AceAutoFillType::ACE_UNSPECIFIED);
    ASSERT_EQ(hintToTypeWrap.metadata, "{\"type\":\"InputType.Normal\"}");

    hintToTypeWrap = pattern_->GetAutoFillTypeAndMetaData(true);
    ASSERT_EQ(hintToTypeWrap.autoFillType, AceAutoFillType::ACE_UNSPECIFIED);

    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateTextInputType(TextInputType::VISIBLE_PASSWORD);
    hintToTypeWrap = pattern_->GetAutoFillTypeAndMetaData(false);
    ASSERT_EQ(hintToTypeWrap.autoFillType, AceAutoFillType::ACE_PASSWORD);

    layoutProperty->UpdateTextContentType(TextContentType::NEW_PASSWORD);
    hintToTypeWrap = pattern_->GetAutoFillTypeAndMetaData(false);
    ASSERT_EQ(hintToTypeWrap.autoFillType, AceAutoFillType::ACE_NEW_PASSWORD);

    auto pipeline = frameNode_->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    CHECK_NULL_VOID(textFieldManager);
    auto passwordFrameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    auto parentFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()); });
    frameNode_->SetParent(parentFrameNode);
    passwordFrameNode->SetParent(parentFrameNode);
    pattern_->firstAutoFillContainerNode_ = AceType::WeakClaim(AceType::RawPtr(parentFrameNode));
    auto passwordPattern = passwordFrameNode->GetPattern<TextFieldPattern>();
    std::unordered_map<int32_t, TextFieldInfo> nameAndPasswordInfoMap;
    TextFieldInfo textFieldInfo;
    textFieldInfo.nodeId = frameNode_->GetId();
    nameAndPasswordInfoMap[textFieldInfo.nodeId] = textFieldInfo;
    TextFieldInfo textFieldInfo2;
    textFieldInfo2.nodeId = passwordFrameNode->GetId();
    textFieldInfo2.inputType = TextInputType::NEW_PASSWORD;
    textFieldInfo2.enableAutoFill = true;
    nameAndPasswordInfoMap[passwordFrameNode->GetId()] = textFieldInfo2;
    std::unordered_map<int32_t, std::unordered_map<int32_t, TextFieldInfo>> textFieldInfoMap;
    textFieldInfoMap[parentFrameNode->GetId()] = nameAndPasswordInfoMap;
    textFieldManager->textFieldInfoMap_ = textFieldInfoMap;
    layoutProperty->UpdateTextInputType(TextInputType::UNSPECIFIED);
    layoutProperty->UpdateTextContentType(TextContentType::UNSPECIFIED);
    hintToTypeWrap = pattern_->GetAutoFillTypeAndMetaData(true);
    ASSERT_EQ(hintToTypeWrap.autoFillType, AceAutoFillType::ACE_UNSPECIFIED);
    ASSERT_EQ(hintToTypeWrap.metadata, "{\"type\":\"InputType.Normal\"}");
}

/**
 * @tc.name: ProcessAutoFillOnFocus001
 * @tc.desc: test TextFieldPattern ProcessAutoFillOnFocus
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestSix, ProcessAutoFillOnFocus001, TestSize.Level0)
{
    int32_t setApiVersion = 18;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    CreateTextField();
    pattern_->SetNeedToRequestKeyboardOnFocus(false);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->needToRequestKeyboardOnFocus_, false);
    pattern_->TextFieldRequestFocus(RequestFocusReason::DRAG_ENTER);
    EXPECT_EQ(pattern_->HasFocus(), true);
    pattern_->ProcessAutoFillOnFocus();
    EXPECT_EQ(pattern_->requestFocusReason_, RequestFocusReason::DRAG_ENTER);
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ProcessAutoFillOnFocus002
 * @tc.desc: test TextFieldPattern ProcessAutoFillOnFocus
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestSix, ProcessAutoFillOnFocus002, TestSize.Level0)
{
    int32_t setApiVersion = 18;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    CreateTextField();
    pattern_->TextFieldRequestFocus(RequestFocusReason::DRAG_ENTER);
    EXPECT_EQ(pattern_->HasFocus(), true);
    pattern_->ProcessAutoFillOnFocus();
    EXPECT_EQ(pattern_->requestFocusReason_, RequestFocusReason::DRAG_ENTER);
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ProcessAutoFillOnFocus003
 * @tc.desc: test TextFieldPattern ProcessAutoFillOnFocus
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestSix, ProcessAutoFillOnFocus003, TestSize.Level0)
{
    int32_t setApiVersion = 18;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    CreateTextField();
    pattern_->TextFieldRequestFocus(RequestFocusReason::LONG_PRESS);
    EXPECT_EQ(pattern_->HasFocus(), true);
    auto pageFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()); });
    ASSERT_NE(pageFrameNode, nullptr);
    frameNode_->SetParent(pageFrameNode);
    auto pagePattern = pageFrameNode->GetPattern<PagePattern>();
    ASSERT_NE(pagePattern, nullptr);
    pagePattern->SetIsModalCovered(true);
    pattern_->ProcessAutoFillOnFocus();
    EXPECT_EQ(pattern_->requestFocusReason_, RequestFocusReason::LONG_PRESS);
    auto stateHolder = pageFrameNode->GetPattern<AutoFillTriggerStateHolder>();
    ASSERT_NE(stateHolder, nullptr);
    EXPECT_EQ(stateHolder->IsAutoFillPasswordTriggered(), false);
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ProcessAutoFillOnFocus004
 * @tc.desc: test TextFieldPattern ProcessAutoFillOnFocus
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestSix, ProcessAutoFillOnFocus004, TestSize.Level0)
{
    int32_t setApiVersion = 18;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    CreateTextField();
    pattern_->TextFieldRequestFocus(RequestFocusReason::LONG_PRESS);
    EXPECT_EQ(pattern_->HasFocus(), true);
    auto pageFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()); });
    ASSERT_NE(pageFrameNode, nullptr);
    auto pagePattern = pageFrameNode->GetPattern<PagePattern>();
    ASSERT_NE(pagePattern, nullptr);
    pagePattern->SetIsModalCovered(false);
    frameNode_->SetParent(pageFrameNode);
    pattern_->firstAutoFillContainerNode_ = AceType::WeakClaim(AceType::RawPtr(pageFrameNode));
    auto pipeline = frameNode_->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    ASSERT_NE(textFieldManager, nullptr);
    std::unordered_map<int32_t, TextFieldInfo> nameAndPasswordInfoMap;
    TextFieldInfo textFieldInfo;
    textFieldInfo.nodeId = frameNode_->GetId();
    textFieldInfo.inputType = TextInputType::UNSPECIFIED;
    textFieldInfo.contentType = TextContentType::PHONE_NUMBER;
    nameAndPasswordInfoMap[textFieldInfo.nodeId] = textFieldInfo;
    std::unordered_map<int32_t, std::unordered_map<int32_t, TextFieldInfo>> textFieldInfoMap;
    textFieldInfoMap[pageFrameNode->GetId()] = nameAndPasswordInfoMap;
    textFieldManager->textFieldInfoMap_ = textFieldInfoMap;
    pattern_->ProcessAutoFillOnFocus();
    EXPECT_EQ(pattern_->requestFocusReason_, RequestFocusReason::LONG_PRESS);
    auto stateHolder = pageFrameNode->GetPattern<AutoFillTriggerStateHolder>();
    ASSERT_NE(stateHolder, nullptr);
    EXPECT_EQ(stateHolder->IsAutoFillPasswordTriggered(), false);
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ProcessAutoFillOnFocus005
 * @tc.desc: test TextFieldPattern ProcessAutoFillOnFocus
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestSix, ProcessAutoFillOnFocus005, TestSize.Level0)
{
    int32_t setApiVersion = 18;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    CreateTextField();
    pattern_->TextFieldRequestFocus(RequestFocusReason::UNKNOWN);
    EXPECT_EQ(pattern_->HasFocus(), true);
    auto pageFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()); });
    ASSERT_NE(pageFrameNode, nullptr);
    auto pagePattern = pageFrameNode->GetPattern<PagePattern>();
    ASSERT_NE(pagePattern, nullptr);
    pagePattern->SetIsModalCovered(false);
    frameNode_->SetParent(pageFrameNode);
    pattern_->firstAutoFillContainerNode_ = AceType::WeakClaim(AceType::RawPtr(pageFrameNode));
    auto passwordFrameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    passwordFrameNode->SetParent(pageFrameNode);
    auto pipeline = frameNode_->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    ASSERT_NE(textFieldManager, nullptr);
    std::unordered_map<int32_t, TextFieldInfo> nameAndPasswordInfoMap;
    TextFieldInfo textFieldInfo;
    textFieldInfo.nodeId = frameNode_->GetId();
    nameAndPasswordInfoMap[textFieldInfo.nodeId] = textFieldInfo;
    TextFieldInfo textFieldInfo2;
    textFieldInfo2.nodeId = passwordFrameNode->GetId();
    textFieldInfo2.inputType = TextInputType::VISIBLE_PASSWORD;
    textFieldInfo2.contentType = TextContentType::UNSPECIFIED;
    textFieldInfo2.enableAutoFill = true;
    textFieldInfo2.autoFillContainerNodeId = pageFrameNode->GetId();
    nameAndPasswordInfoMap[passwordFrameNode->GetId()] = textFieldInfo2;
    std::unordered_map<int32_t, std::unordered_map<int32_t, TextFieldInfo>> textFieldInfoMap;
    textFieldInfoMap[pageFrameNode->GetId()] = nameAndPasswordInfoMap;
    textFieldManager->textFieldInfoMap_ = textFieldInfoMap;
    pattern_->ProcessAutoFillOnFocus();
    EXPECT_EQ(pattern_->requestFocusReason_, RequestFocusReason::UNKNOWN);
    auto stateHolder = pageFrameNode->GetPattern<AutoFillTriggerStateHolder>();
    ASSERT_NE(stateHolder, nullptr);
    EXPECT_EQ(stateHolder->IsAutoFillPasswordTriggered(), true);
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}
} // namespace OHOS::Ace::NG