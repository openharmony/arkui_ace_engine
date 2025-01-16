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

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/pattern/text/span/span_object.h"
#define private public
#include "core/components_ng/pattern/text_field/content_controller.h"
#undef private

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

class MyImageSpan : public ImageSpan {
public:
    explicit MyImageSpan(const ImageSpanOptions& options) : ImageSpan(options) {}
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

/**
 * @tc.name: ImageSpanIsAttributesEqual001
 * @tc.desc: test IsAttributesEqual
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ImageSpanIsAttributesEqual001, TestSize.Level1)
{
    ImageSpanOptions options;
    ImageSpanAttribute imageSpanAttribute;
    std::optional<ImageSpanAttribute> attribute;
    attribute.emplace(imageSpanAttribute);
    options.imageAttribute = attribute;
    ImageSpan imageSpan(options);
    auto spanBase = AceType::MakeRefPtr<MockSpanBase>();
    bool result = imageSpan.IsAttributesEqual(spanBase);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ImageSpanIsAttributesEqual002
 * @tc.desc: test IsAttributesEqual
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ImageSpanIsAttributesEqual002, TestSize.Level1)
{
    ImageSpanOptions options;
    ImageSpanAttribute imageSpanAttribute;
    std::optional<ImageSpanAttribute> attribute;
    attribute.emplace(imageSpanAttribute);
    options.imageAttribute = attribute;
    ImageSpan imageSpan(options);
    ImageSpanOptions myOptions;
    auto myImageSpan = AceType::MakeRefPtr<MyImageSpan>(myOptions);
    bool result = imageSpan.IsAttributesEqual(myImageSpan);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ImageSpanIsAttributesEqual003
 * @tc.desc: test IsAttributesEqual
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ImageSpanIsAttributesEqual003, TestSize.Level1)
{
    ImageSpanOptions options;
    ImageSpan imageSpan(options);
    ImageSpanOptions myOptions;
    ImageSpanAttribute imageSpanAttribute;
    std::optional<ImageSpanAttribute> attribute;
    attribute.emplace(imageSpanAttribute);
    myOptions.imageAttribute = attribute;
    auto myImageSpan = AceType::MakeRefPtr<MyImageSpan>(myOptions);
    bool result = imageSpan.IsAttributesEqual(myImageSpan);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CustomSpanGetSubSpan001
 * @tc.desc: test GetSubSpan
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, CustomSpanGetSubSpan001, TestSize.Level1)
{
    CustomSpan customSpan;
    auto result = customSpan.GetSubSpan(1, 4);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: BackgroundColorSpanApplyToSpanItem001
 * @tc.desc: test ApplyToSpanItem
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, BackgroundColorSpanApplyToSpanItem001, TestSize.Level1)
{
    Color color;
    std::optional<Color> backgroundColor;
    backgroundColor.emplace(color);
    TextBackgroundStyle textBackgroundStyle;
    textBackgroundStyle.backgroundColor = backgroundColor;
    std::optional<TextBackgroundStyle> backgroundStyle;
    backgroundStyle.emplace(textBackgroundStyle);
    BackgroundColorSpan backgroundColorSpan = BackgroundColorSpan(backgroundStyle);
    auto spanItem = AceType::MakeRefPtr<NG::SpanItem>();
    spanItem->backgroundStyle = backgroundStyle;
    backgroundColorSpan.ApplyToSpanItem(spanItem, SpanOperation::REMOVE);
    EXPECT_FALSE(spanItem->backgroundStyle.has_value());
}

/**
 * @tc.name: BackgroundColorSpanAddSpanStyle001
 * @tc.desc: test AddSpanStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, BackgroundColorSpanAddSpanStyle001, TestSize.Level1)
{
    std::optional<TextBackgroundStyle> backgroundStyle;
    BackgroundColorSpan backgroundColorSpan = BackgroundColorSpan(backgroundStyle);
    auto spanItem = AceType::MakeRefPtr<NG::SpanItem>();
    spanItem->backgroundStyle = backgroundStyle;
    backgroundColorSpan.AddSpanStyle(spanItem);
    EXPECT_FALSE(spanItem->backgroundStyle.has_value());
}

/**
 * @tc.name: BackgroundColorSpanRemoveSpanStyle001
 * @tc.desc: test RemoveSpanStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, BackgroundColorSpanRemoveSpanStyle001, TestSize.Level1)
{
    Color color;
    std::optional<Color> backgroundColor;
    backgroundColor.emplace(color);
    TextBackgroundStyle textBackgroundStyle;
    textBackgroundStyle.backgroundColor = backgroundColor;
    std::optional<TextBackgroundStyle> backgroundStyle;
    backgroundStyle.emplace(textBackgroundStyle);
    BackgroundColorSpan backgroundColorSpan = BackgroundColorSpan(backgroundStyle);
    auto spanItem = AceType::MakeRefPtr<NG::SpanItem>();
    spanItem->backgroundStyle = backgroundStyle;
    backgroundColorSpan.RemoveSpanStyle(spanItem);
    EXPECT_FALSE(spanItem->backgroundStyle.has_value());
}

/**
 * @tc.name: BackgroundColorSpanRemoveSpanStyle002
 * @tc.desc: test RemoveSpanStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, BackgroundColorSpanRemoveSpanStyle002, TestSize.Level1)
{
    std::optional<TextBackgroundStyle> backgroundStyle;
    BackgroundColorSpan backgroundColorSpan = BackgroundColorSpan(backgroundStyle);
    auto spanItem = AceType::MakeRefPtr<NG::SpanItem>();
    spanItem->backgroundStyle = backgroundStyle;
    backgroundColorSpan.RemoveSpanStyle(spanItem);
    EXPECT_FALSE(spanItem->backgroundStyle.has_value());
}

/**
 * @tc.name: TextShadowSpanAddSpanStyle001
 * @tc.desc: test AddSpanStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextShadowSpanAddSpanStyle001, TestSize.Level1)
{
    TextShadowSpan textShadowSpan;
    auto spanItem = AceType::MakeRefPtr<NG::SpanItem>();
    spanItem->fontStyle.reset();
    textShadowSpan.AddSpanStyle(spanItem);
    EXPECT_EQ(spanItem->fontStyle, nullptr);
}

/**
 * @tc.name: BaselineOffsetSpanAddBaselineOffsetStyle001
 * @tc.desc: test AddBaselineOffsetStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, BaselineOffsetSpanAddBaselineOffsetStyle001, TestSize.Level1)
{
    Dimension dimension(20.0);
    BaselineOffsetSpan baselineOffsetSpan(dimension);
    auto spanItem = AceType::MakeRefPtr<NG::SpanItem>();
    spanItem->textLineStyle.reset();
    baselineOffsetSpan.AddBaselineOffsetStyle(spanItem);
    EXPECT_NE(spanItem->textLineStyle, nullptr);
}

/**
 * @tc.name: BaselineOffsetSpanRemoveBaselineOffsetStyle001
 * @tc.desc: test RemoveBaselineOffsetStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, BaselineOffsetSpanRemoveBaselineOffsetStyle001, TestSize.Level1)
{
    Dimension dimension(20.0);
    BaselineOffsetSpan baselineOffsetSpan(dimension);
    auto spanItem = AceType::MakeRefPtr<NG::SpanItem>();
    spanItem->textLineStyle.reset();
    baselineOffsetSpan.RemoveBaselineOffsetStyle(spanItem);
    EXPECT_NE(spanItem->textLineStyle, nullptr);
}

/**
 * @tc.name: TLVUtilReadString001
 * @tc.desc: test ReadString
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TLVUtilReadString001, TestSize.Level1)
{
    TLVUtil util;
    std::vector<uint8_t> buffer;
    int32_t cursor = 0;
    TLVUtil::WriteUint8(buffer, TLV_DOUBLE_TAG);
    auto str = util.ReadString(buffer, cursor);
    EXPECT_TRUE(str.empty());
}

/**
 * @tc.name: TLVUtilReadString002
 * @tc.desc: test ReadString
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TLVUtilReadString002, TestSize.Level1)
{
    TLVUtil util;
    std::vector<uint8_t> buffer;
    int32_t cursor = 0;
    TLVUtil::WriteUint8(buffer, TLV_STRING_TAG);
    TLVUtil::WriteInt32(buffer, 1);
    TLVUtil::WriteUint8(buffer, 'A');
    auto str = util.ReadString(buffer, cursor);
    EXPECT_FALSE(str.empty());
}

/**
 * @tc.name: TLVUtilReadString003
 * @tc.desc: test ReadString
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TLVUtilReadString003, TestSize.Level1)
{
    TLVUtil util;
    std::vector<uint8_t> buffer;
    int32_t cursor = 0;
    TLVUtil::WriteUint8(buffer, TLV_STRING_TAG);
    TLVUtil::WriteInt32(buffer, 2);
    TLVUtil::WriteUint8(buffer, 'A');
    TLVUtil::WriteUint8(buffer, TLV_END);
    auto str = util.ReadString(buffer, cursor);
    EXPECT_TRUE(str.empty());
}

/**
 * @tc.name: TLVUtilReadDouble001
 * @tc.desc: test ReadDouble
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TLVUtilReadDouble001, TestSize.Level1)
{
    TLVUtil util;
    std::vector<uint8_t> buffer;
    int32_t cursor = 0;
    TLVUtil::WriteUint8(buffer, TLV_STRING_TAG);
    auto value = util.ReadDouble(buffer, cursor);
    EXPECT_EQ(value, 0.0);
}

/**
 * @tc.name: TLVUtilReadColor001
 * @tc.desc: test ReadColor
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TLVUtilReadColor001, TestSize.Level1)
{
    TLVUtil util;
    std::vector<uint8_t> buffer;
    int32_t cursor = 0;
    TLVUtil::WriteUint8(buffer, TLV_STRING_TAG);
    auto object = util.ReadColor(buffer, cursor);
    EXPECT_EQ(object.colorValue_.argb.blue, util.ReadUint8(buffer, cursor));
}

/**
 * @tc.name: TLVUtilReadDimension001
 * @tc.desc: test ReadDimension
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TLVUtilReadDimension001, TestSize.Level1)
{
    TLVUtil util;
    std::vector<uint8_t> buffer;
    int32_t cursor = 0;
    TLVUtil::WriteUint8(buffer, TLV_STRING_TAG);
    auto object = util.ReadDimension(buffer, cursor);
    EXPECT_EQ(object.value_, util.ReadDouble(buffer, cursor));
}

/**
 * @tc.name: TLVUtilReadPixelMap001
 * @tc.desc: test ReadPixelMap
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TLVUtilReadPixelMap001, TestSize.Level1)
{
    TLVUtil util;
    std::vector<uint8_t> buffer;
    int32_t cursor = 0;
    TLVUtil::WriteUint8(buffer, TLV_PIXEL_MAP_TAG);
    int32_t pixelMapLength = 10;
    buffer.insert(buffer.end(), reinterpret_cast<uint8_t*>(&pixelMapLength),
        reinterpret_cast<uint8_t*>(&pixelMapLength) + sizeof(pixelMapLength));
    auto result = util.ReadPixelMap(buffer, cursor);
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: TLVUtilWriteImageSpanSize001
 * @tc.desc: test WriteImageSpanSize
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TLVUtilWriteImageSpanSize001, TestSize.Level1)
{
    std::vector<uint8_t> buffer;
    ImageSpanSize imageSpanSize = {};
    TLVUtil::WriteImageSpanSize(buffer, imageSpanSize);
    std::vector<uint8_t> expectedBuffer = { TLV_IMAGESPANSIZE_TAG, TLV_IMAGESPANSIZE_END_TAG };
    EXPECT_EQ(buffer, expectedBuffer);
}
} // namespace OHOS::Ace::NG