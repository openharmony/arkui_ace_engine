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

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "text_base.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TextTestNg : public TextBases {
public:
};

class MockSpanBase : public SpanBase {
public:
    MockSpanBase() = default;
    MockSpanBase(int32_t start, int32_t end) : SpanBase(start, end) {}
    MOCK_CONST_METHOD1(IsAttributesEqual, bool(const RefPtr<SpanBase>& other));
    MOCK_METHOD2(GetSubSpan, RefPtr<SpanBase>(int32_t start, int32_t end));
    MOCK_CONST_METHOD0(GetSpanType, SpanType());
    MOCK_CONST_METHOD2(ApplyToSpanItem, void(const RefPtr<NG::SpanItem>& spanItem, SpanOperation operation));
    MOCK_CONST_METHOD0(ToString, std::string());
};

/**
 * @tc.name: SpanStringContainSpecialNode001
 * @tc.desc: test ContainSpecialNode
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SpanStringContainSpecialNode001, TestSize.Level1)
{
    SpanString spanString = SpanString(u"text");
    std::list<RefPtr<SpanBase>> base;
    auto spanBase = AceType::MakeRefPtr<MockSpanBase>();
    spanBase->start_ = 5;
    spanBase->end_ = 15;
    base.emplace_back(spanBase);
    spanString.spansMap_[SpanType::Image] = base;
    bool result = spanString.ContainSpecialNode(10, 5);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SpanStringContainSpecialNode002
 * @tc.desc: test ContainSpecialNode
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SpanStringContainSpecialNode002, TestSize.Level1)
{
    SpanString spanString = SpanString(u"text");
    std::list<RefPtr<SpanBase>> base;
    auto spanBase = AceType::MakeRefPtr<MockSpanBase>();
    spanBase->start_ = 20;
    spanBase->end_ = 30;
    base.emplace_back(spanBase);
    spanString.spansMap_[SpanType::Image] = base;
    bool result = spanString.ContainSpecialNode(5, 10);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SpanStringContainSpecialNode003
 * @tc.desc: test ContainSpecialNode
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SpanStringContainSpecialNode003, TestSize.Level1)
{
    SpanString spanString = SpanString(u"text");
    auto mockSpanBase = std::make_shared<MockSpanBase>();
    mockSpanBase->start_ = 5;
    mockSpanBase->end_ = 15;
    bool result = spanString.ContainSpecialNode(10, 5);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: MutableSpanStringIsSpeicalNode001
 * @tc.desc: test IsSpeicalNode
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, MutableSpanStringIsSpeicalNode001, TestSize.Level1)
{
    MutableSpanString mutableSpanString = MutableSpanString(u"text");
    std::list<RefPtr<SpanBase>> base;
    auto spanBase = AceType::MakeRefPtr<MockSpanBase>();
    spanBase->start_ = 5;
    spanBase->end_ = 15;
    base.emplace_back(spanBase);
    mutableSpanString.spansMap_.emplace(SpanType::TextShadow, base);
    mutableSpanString.spansMap_.emplace(SpanType::LineHeight, base);
    mutableSpanString.spansMap_.emplace(SpanType::BackgroundColor, base);
    bool result = mutableSpanString.IsSpeicalNode(10, SpanType::Image);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: MutableSpanStringIsSpeicalNode002
 * @tc.desc: test IsSpeicalNode
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, MutableSpanStringIsSpeicalNode002, TestSize.Level1)
{
    MutableSpanString mutableSpanString = MutableSpanString(u"text");
    std::list<RefPtr<SpanBase>> base;
    auto spanBase = AceType::MakeRefPtr<MockSpanBase>();
    spanBase->start_ = 5;
    spanBase->end_ = 15;
    base.emplace_back(spanBase);
    mutableSpanString.spansMap_.emplace(SpanType::TextShadow, base);
    mutableSpanString.spansMap_.emplace(SpanType::LineHeight, base);
    mutableSpanString.spansMap_.emplace(SpanType::BackgroundColor, base);
    bool result = mutableSpanString.IsSpeicalNode(10, SpanType::TextShadow);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: MutableSpanStringIsSpeicalNode003
 * @tc.desc: test IsSpeicalNode
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, MutableSpanStringIsSpeicalNode003, TestSize.Level1)
{
    MutableSpanString mutableSpanString = MutableSpanString(u"text");
    std::list<RefPtr<SpanBase>> base;
    auto spanBase = AceType::MakeRefPtr<MockSpanBase>();
    spanBase->start_ = 4;
    spanBase->end_ = 15;
    base.emplace_back(spanBase);
    mutableSpanString.spansMap_.emplace(SpanType::TextShadow, base);
    mutableSpanString.spansMap_.emplace(SpanType::LineHeight, base);
    mutableSpanString.spansMap_.emplace(SpanType::BackgroundColor, base);
    bool result = mutableSpanString.IsSpeicalNode(4, SpanType::TextShadow);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: MutableSpanStringIsSpeicalNode004
 * @tc.desc: test IsSpeicalNode
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, MutableSpanStringIsSpeicalNode004, TestSize.Level1)
{
    MutableSpanString mutableSpanString = MutableSpanString(u"text");
    std::list<RefPtr<SpanBase>> base;
    auto spanBase = AceType::MakeRefPtr<MockSpanBase>();
    spanBase->start_ = 15;
    spanBase->end_ = 30;
    base.emplace_back(spanBase);
    mutableSpanString.spansMap_.emplace(SpanType::TextShadow, base);
    mutableSpanString.spansMap_.emplace(SpanType::LineHeight, base);
    mutableSpanString.spansMap_.emplace(SpanType::BackgroundColor, base);
    bool result = mutableSpanString.IsSpeicalNode(10, SpanType::TextShadow);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: BackgroundColorSpanIsAttributesEqual001
 * @tc.desc: test IsAttributesEqual
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, BackgroundColorSpanIsAttributesEqual001, TestSize.Level1)
{
    TextBackgroundStyle textBackgroundStyle;
    std::optional<TextBackgroundStyle> textBackgroundStyle_;
    textBackgroundStyle_.emplace(textBackgroundStyle);
    BackgroundColorSpan backgroundColorSpan = BackgroundColorSpan(textBackgroundStyle_);
    auto spanBase = AceType::MakeRefPtr<MockSpanBase>();
    bool result = backgroundColorSpan.IsAttributesEqual(spanBase);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: UrlSpanIsAttributesEqual001
 * @tc.desc: test IsAttributesEqual
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, UrlSpanIsAttributesEqual001, TestSize.Level1)
{
    UrlSpan urlSpan = UrlSpan("test");
    auto spanBase = AceType::MakeRefPtr<MockSpanBase>();
    bool result = urlSpan.IsAttributesEqual(spanBase);
    EXPECT_FALSE(result);
}
} // namespace OHOS::Ace::NG