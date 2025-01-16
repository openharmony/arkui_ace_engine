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

#include "text_base.h"

#include "core/components_ng/pattern/text/span_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
const std::string TEST_TEXT = "testText";
const std::string TEST_DESCRIPTION = "testDescription";
const std::string TEST_LEVEL = "testLevel";

void ConstructSpanItemOnClick(RefPtr<SpanItem>& spanItem)
{
    auto onClick = [](const BaseEventInfo* info) {};
    auto tmpClickFunc = [func = std::move(onClick)](GestureEvent& info) { func(&info); };
    spanItem->onClick = std::move(tmpClickFunc);
}
void ConstructImageSpanItemOnClick(const RefPtr<ImageSpanItem>& imageSpanItem)
{
    auto onClick = [](const BaseEventInfo* info) {};
    auto tmpClickFunc = [func = std::move(onClick)](GestureEvent& info) { func(&info); };
    imageSpanItem->onClick = std::move(tmpClickFunc);
}
void ConstructGestureStyle(GestureStyle& gestureInfo)
{
    auto onClick = [](const BaseEventInfo* info) {};
    auto tmpClickFunc = [func = std::move(onClick)](GestureEvent& info) { func(&info); };
    gestureInfo.onClick = std::move(tmpClickFunc);

    auto onLongPress = [](const BaseEventInfo* info) {};
    auto tmpLongPressFunc = [func = std::move(onLongPress)](GestureEvent& info) { func(&info); };
    gestureInfo.onLongPress = std::move(tmpLongPressFunc);
}
} // namespace

class SpanAccessibilityTestNg : public TextBases {
};

/**
 * @tc.name: GetSubComponentInfos001
 * @tc.desc: Test TextPattern GetSubComponentInfos
 * @tc.type: FUNC
 */
HWTEST_F(SpanAccessibilityTestNg, GetSubComponentInfos001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    /**
     * @tc.steps: step2. construct spanItemChildren
     */
    std::list<RefPtr<SpanItem>> spanItems;
    auto spanItem1 = AceType::MakeRefPtr<SpanItem>();
    spanItem1->content = u"test";
    ConstructSpanItemOnClick(spanItem1);
    spanItems.emplace_back(spanItem1);

    auto spanItem2 = AceType::MakeRefPtr<SpanItem>();
    spanItems.emplace_back(spanItem2);

    auto imageSpanNode1 = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ConstructImageSpanItemOnClick(imageSpanNode1->GetSpanItem());
    spanItems.emplace_back(imageSpanNode1->GetSpanItem());

    auto imageSpanNode2 = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    spanItems.emplace_back(imageSpanNode2->GetSpanItem());

    pattern->spans_ = spanItems;

    /**
     * @tc.steps: step3. test pattern GetSubComponentInfos
     */
    std::vector<SubComponentInfo> subComponentInfos;
    accessibilityProperty->GetSubComponentInfo(subComponentInfos);

    EXPECT_EQ(subComponentInfos.size(), 1);
}

/**
 * @tc.name: GetSubComponentInfos002
 * @tc.desc: Test TextPattern GetSubComponentInfos
 * @tc.type: FUNC
 */
HWTEST_F(SpanAccessibilityTestNg, GetSubComponentInfos002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    /**
     * @tc.steps: step2. construct spanItemChildren
     */
    GestureStyle gestureInfo;
    ConstructGestureStyle(gestureInfo);
    std::vector<RefPtr<SpanBase>> spanBases;
    spanBases.emplace_back(AceType::MakeRefPtr<GestureSpan>(gestureInfo, 0, 3));
    spanBases.emplace_back(AceType::MakeRefPtr<GestureSpan>(gestureInfo, 8, 11));
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"01234567891");
    spanString->BindWithSpans(spanBases);
    pattern->SetSpanItemChildren(spanString->GetSpanItems());

    /**
     * @tc.steps: step3. test pattern GetSubComponentInfos
     */
    std::vector<SubComponentInfo> subComponentInfos;
    accessibilityProperty->GetSubComponentInfo(subComponentInfos);

    EXPECT_EQ(subComponentInfos.size(), 2);
}

/**
 * @tc.name: GetSubComponentInfos003
 * @tc.desc: Test TextPattern GetSubComponentInfos
 * @tc.type: FUNC
 */
HWTEST_F(SpanAccessibilityTestNg, GetSubComponentInfos003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    /**
     * @tc.steps: step2. construct spanItemChildren
     */
    AISpan aiSpan1;
    aiSpan1.content = "13812345678";
    aiSpan1.start = 0;
    aiSpan1.end = aiSpan1.content.length();
    aiSpan1.type = TextDataDetectType::PHONE_NUMBER;
    pattern->dataDetectorAdapter_->aiSpanMap_.insert(std::make_pair(0, aiSpan1));

    /**
     * @tc.steps: step3. test pattern GetSubComponentInfos
     */
    std::vector<SubComponentInfo> subComponentInfos;
    accessibilityProperty->GetSubComponentInfo(subComponentInfos);

    EXPECT_EQ(subComponentInfos.size(), 1);
}

/**
 * @tc.name: GetSubComponentInfos004
 * @tc.desc: Test TextPattern GetSubComponentInfos
 * @tc.type: FUNC
 */
HWTEST_F(SpanAccessibilityTestNg, GetSubComponentInfos004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    /**
     * @tc.steps: step2. test pattern GetSubComponentInfos
     */
    std::vector<SubComponentInfo> subComponentInfos;
    accessibilityProperty->GetSubComponentInfo(subComponentInfos);

    EXPECT_EQ(subComponentInfos.size(), 0);
}

/**
 * @tc.name: ExecSubComponent001
 * @tc.desc: Test TextPattern ExecSubComponent
 * @tc.type: FUNC
 */
HWTEST_F(SpanAccessibilityTestNg, ExecSubComponent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    /**
     * @tc.steps: step2. construct spanItemChildren
     */
    std::list<RefPtr<SpanItem>> spanItems;
    auto spanItem1 = AceType::MakeRefPtr<SpanItem>();
    spanItem1->content = u"test click";
    ConstructSpanItemOnClick(spanItem1);
    spanItems.emplace_back(spanItem1);

    auto spanItem2 = AceType::MakeRefPtr<SpanItem>();
    spanItems.emplace_back(spanItem2);

    auto imageSpanNode1 = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ConstructImageSpanItemOnClick(imageSpanNode1->GetSpanItem());
    spanItems.emplace_back(imageSpanNode1->GetSpanItem());

    auto imageSpanNode2 = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    spanItems.emplace_back(imageSpanNode2->GetSpanItem());

    pattern->spans_ = spanItems;

    std::vector<SubComponentInfo> subComponentInfos;
    accessibilityProperty->GetSubComponentInfo(subComponentInfos);
    EXPECT_EQ(subComponentInfos.size(), 1);

    /**
     * @tc.steps: step3. test pattern ExecSubComponent
     */
    EXPECT_EQ(accessibilityProperty->ActActionExecSubComponent(0), true);
    EXPECT_EQ(pattern->ExecSubComponent(0), true);
    EXPECT_EQ(accessibilityProperty->ActActionExecSubComponent(1), false);
    EXPECT_EQ(pattern->ExecSubComponent(1), false);
    EXPECT_EQ(accessibilityProperty->ActActionExecSubComponent(-1), false);
    EXPECT_EQ(pattern->ExecSubComponent(-1), false);
}

/**
 * @tc.name: ExecSubComponent002
 * @tc.desc: Test TextPattern ExecSubComponent
 * @tc.type: FUNC
 */
HWTEST_F(SpanAccessibilityTestNg, ExecSubComponent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    /**
     * @tc.steps: step2. construct spanItemChildren
     */
    AISpan aiSpan1;
    aiSpan1.content = "13812345678";
    aiSpan1.start = 0;
    aiSpan1.end = aiSpan1.content.length();
    aiSpan1.type = TextDataDetectType::PHONE_NUMBER;
    pattern->dataDetectorAdapter_->aiSpanMap_.insert(std::make_pair(0, aiSpan1));

    std::vector<SubComponentInfo> subComponentInfos;
    accessibilityProperty->GetSubComponentInfo(subComponentInfos);
    EXPECT_EQ(subComponentInfos.size(), 1);

    /**
     * @tc.steps: step3. test pattern ExecSubComponent
     */
    EXPECT_EQ(accessibilityProperty->ActActionExecSubComponent(0), true);
    EXPECT_EQ(pattern->ExecSubComponent(0), true);
    EXPECT_EQ(accessibilityProperty->ActActionExecSubComponent(1), false);
    EXPECT_EQ(pattern->ExecSubComponent(1), false);
    EXPECT_EQ(accessibilityProperty->ActActionExecSubComponent(-1), false);
    EXPECT_EQ(pattern->ExecSubComponent(-1), false);
}

/**
 * @tc.name: ExecSubComponent003
 * @tc.desc: Test TextPattern ExecSubComponent
 * @tc.type: FUNC
 */
HWTEST_F(SpanAccessibilityTestNg, ExecSubComponent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    /**
     * @tc.steps: step2. construct spanItemChildren
     */
    std::vector<SubComponentInfo> subComponentInfos;
    accessibilityProperty->GetSubComponentInfo(subComponentInfos);
    EXPECT_EQ(subComponentInfos.size(), 0);

    /**
     * @tc.steps: step3. test pattern ExecSubComponent
     */
    EXPECT_EQ(accessibilityProperty->ActActionExecSubComponent(0), false);
    EXPECT_EQ(pattern->ExecSubComponent(0), false);
    EXPECT_EQ(accessibilityProperty->ActActionExecSubComponent(1), false);
    EXPECT_EQ(pattern->ExecSubComponent(1), false);
    EXPECT_EQ(accessibilityProperty->ActActionExecSubComponent(-1), false);
    EXPECT_EQ(pattern->ExecSubComponent(-1), false);
}

/**
 * @tc.name: SetAccessibilityText001
 * @tc.desc: Test accessibilityText of span.
 * @tc.type: FUNC
 */
HWTEST_F(SpanAccessibilityTestNg, SetAccessibilityText001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create span node
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);

    /**
     * @tc.steps: step2. get span node
     */
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    ASSERT_NE(spanItem->accessibilityProperty, nullptr);

    /**
     * @tc.steps: step3. test accessibilityText
     */
    spanModelNG.SetAccessibilityText("");
    EXPECT_EQ(spanItem->accessibilityProperty->GetAccessibilityText(), "");

    spanModelNG.SetAccessibilityText(TEST_TEXT);
    EXPECT_EQ(spanItem->accessibilityProperty->GetAccessibilityText(), TEST_TEXT);

    spanModelNG.SetAccessibilityText("");
    EXPECT_EQ(spanItem->accessibilityProperty->GetAccessibilityText(), "");

    spanModelNG.SetAccessibilityText(TEST_TEXT);
    EXPECT_EQ(spanItem->accessibilityProperty->GetAccessibilityText(), TEST_TEXT);
}

/**
 * @tc.name: SetAccessibilityDescription001
 * @tc.desc: Test accessibilityDescription of span.
 * @tc.type: FUNC
 */
HWTEST_F(SpanAccessibilityTestNg, SetAccessibilityDescription001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create span node
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);

    /**
     * @tc.steps: step2. get span node
     */
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    ASSERT_NE(spanItem->accessibilityProperty, nullptr);

    /**
     * @tc.steps: step3. test accessibilityDescription
     */
    spanModelNG.SetAccessibilityDescription("");
    EXPECT_EQ(spanItem->accessibilityProperty->GetAccessibilityDescription(), "");

    spanModelNG.SetAccessibilityDescription(TEST_DESCRIPTION);
    EXPECT_EQ(spanItem->accessibilityProperty->GetAccessibilityDescription(), TEST_DESCRIPTION);

    spanModelNG.SetAccessibilityDescription("");
    EXPECT_EQ(spanItem->accessibilityProperty->GetAccessibilityDescription(), "");

    spanModelNG.SetAccessibilityDescription(TEST_DESCRIPTION);
    EXPECT_EQ(spanItem->accessibilityProperty->GetAccessibilityDescription(), TEST_DESCRIPTION);
}

/**
 * @tc.name: SetAccessibilityLevel001
 * @tc.desc: Test accessibilityLevel of span.
 * @tc.type: FUNC
 */
HWTEST_F(SpanAccessibilityTestNg, SetAccessibilityLevel001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create span node
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);

    /**
     * @tc.steps: step2. get span node
     */
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    ASSERT_NE(spanItem->accessibilityProperty, nullptr);

    /**
     * @tc.steps: step3. test accessibilityLevel
     */
    spanModelNG.SetAccessibilityImportance("");
    EXPECT_EQ(spanItem->accessibilityProperty->GetAccessibilityLevel(), AccessibilityProperty::Level::AUTO);

    spanModelNG.SetAccessibilityImportance(AccessibilityProperty::Level::YES_STR);
    EXPECT_EQ(spanItem->accessibilityProperty->GetAccessibilityLevel(), AccessibilityProperty::Level::YES_STR);

    spanModelNG.SetAccessibilityImportance(AccessibilityProperty::Level::NO_STR);
    EXPECT_EQ(spanItem->accessibilityProperty->GetAccessibilityLevel(), AccessibilityProperty::Level::NO_STR);

    spanModelNG.SetAccessibilityImportance(AccessibilityProperty::Level::NO_HIDE_DESCENDANTS);
    EXPECT_EQ(spanItem->accessibilityProperty->GetAccessibilityLevel(),
        AccessibilityProperty::Level::NO_HIDE_DESCENDANTS);

    spanModelNG.SetAccessibilityImportance(AccessibilityProperty::Level::AUTO);
    EXPECT_EQ(spanItem->accessibilityProperty->GetAccessibilityLevel(), AccessibilityProperty::Level::AUTO);

    spanModelNG.SetAccessibilityImportance(AccessibilityProperty::Level::YES_STR);
    EXPECT_EQ(spanItem->accessibilityProperty->GetAccessibilityLevel(), AccessibilityProperty::Level::YES_STR);

    spanModelNG.SetAccessibilityImportance(TEST_LEVEL);
    EXPECT_EQ(spanItem->accessibilityProperty->GetAccessibilityLevel(), AccessibilityProperty::Level::AUTO);

    spanModelNG.SetAccessibilityImportance(AccessibilityProperty::Level::YES_STR);
    EXPECT_EQ(spanItem->accessibilityProperty->GetAccessibilityLevel(), AccessibilityProperty::Level::YES_STR);

    spanModelNG.SetAccessibilityImportance("");
    EXPECT_EQ(spanItem->accessibilityProperty->GetAccessibilityLevel(), AccessibilityProperty::Level::AUTO);

    spanModelNG.SetAccessibilityImportance(AccessibilityProperty::Level::YES_STR);
    EXPECT_EQ(spanItem->accessibilityProperty->GetAccessibilityLevel(), AccessibilityProperty::Level::YES_STR);
}
} // namespace OHOS::Ace::NG
