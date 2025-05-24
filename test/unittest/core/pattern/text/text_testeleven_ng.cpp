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

void UrlCallback()
{
    std::cout << "urlOnRelease" << std::endl;
}

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
 * @tc.name: FontSpanAddSpanStyle001
 * @tc.desc: test AddSpanStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, FontSpanSpanAddSpanStyle001, TestSize.Level1)
{
    FontSpan fontSpan;
    auto spanItem = AceType::MakeRefPtr<NG::SpanItem>();
    spanItem->fontStyle.reset();
    fontSpan.AddSpanStyle(spanItem);
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

/**
 * @tc.name: TLVUtilReadImageSpanSize001
 * @tc.desc: test ReadImageSpanSize
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TLVUtilReadImageSpanSize001, TestSize.Level1)
{
    std::vector<uint8_t> buffer;
    int32_t cursor = 0;
    TLVUtil::WriteUint8(buffer, TLV_IMAGESPANSIZE_TAG);
    TLVUtil::WriteUint8(buffer, TLV_ELLIPSISMODE_TAG);
    TLVUtil::WriteUint8(buffer, TLV_IMAGESPANSIZE_END_TAG);
    auto result = TLVUtil::ReadImageSpanSize(buffer, cursor);
    EXPECT_FALSE(result.width.has_value());
    EXPECT_FALSE(result.height.has_value());
}

/**
 * @tc.name: TLVUtilReadPaddingProperty001
 * @tc.desc: test ReadPaddingProperty
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TLVUtilReadPaddingProperty001, TestSize.Level1)
{
    std::vector<uint8_t> buffer;
    int32_t cursor = 0;
    TLVUtil::WriteUint8(buffer, TLV_PADDINGPROPERTY_TAG);
    TLVUtil::WriteUint8(buffer, TLV_ELLIPSISMODE_TAG);
    TLVUtil::WriteUint8(buffer, TLV_PADDINGPROPERTY_END_TAG);
    auto result = TLVUtil::ReadPaddingProperty(buffer, cursor);
    EXPECT_FALSE(result.left.has_value());
    EXPECT_FALSE(result.top.has_value());
    EXPECT_FALSE(result.bottom.has_value());
    EXPECT_FALSE(result.right.has_value());
}

/**
 * @tc.name: ContentControllerRemoveErrorTextFromValue001
 * @tc.desc: test RemoveErrorTextFromValue
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ContentControllerRemoveErrorTextFromValue001, TestSize.Level1)
{
    auto result = ContentController::RemoveErrorTextFromValue(u"b", u"a");
    EXPECT_EQ(result, u"b");
}

/**
 * @tc.name: ContentControllerFilterWithAscii001
 * @tc.desc: test FilterWithAscii
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ContentControllerFilterWithAscii001, TestSize.Level1)
{
    std::u16string str = u"";
    auto result = ContentController::FilterWithAscii(str);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SpanStringGetDefaultSpan001
 * @tc.desc: test GetDefaultSpan
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SpanStringGetDefaultSpan001, TestSize.Level1)
{
    auto span = SpanString::GetDefaultSpan(SpanType::Decoration);
    EXPECT_NE(span, nullptr);
    auto decorationSpan = AceType::DynamicCast<DecorationSpan>(span);
    EXPECT_NE(decorationSpan, nullptr);
}

/**
 * @tc.name: SpanStringGetDefaultSpan002
 * @tc.desc: test GetDefaultSpan
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SpanStringGetDefaultSpan002, TestSize.Level1)
{
    auto span = SpanString::GetDefaultSpan(SpanType::ExtSpan);
    EXPECT_NE(span, nullptr);
    auto extSpan = AceType::DynamicCast<ExtSpan>(span);
    EXPECT_NE(extSpan, nullptr);
}

/**
 * @tc.name: SpanStringGetDefaultSpan003
 * @tc.desc: test GetDefaultSpan
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SpanStringGetDefaultSpan003, TestSize.Level1)
{
    auto span = SpanString::GetDefaultSpan(SpanType::BackgroundColor);
    EXPECT_NE(span, nullptr);
    auto backgroundColorSpan = AceType::DynamicCast<BackgroundColorSpan>(span);
    EXPECT_NE(backgroundColorSpan, nullptr);
}

/**
 * @tc.name: SpanStringGetDefaultSpan004
 * @tc.desc: test GetDefaultSpan
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SpanStringGetDefaultSpan004, TestSize.Level1)
{
    auto span = SpanString::GetDefaultSpan(SpanType::Url);
    EXPECT_NE(span, nullptr);
    auto urlSpan = AceType::DynamicCast<UrlSpan>(span);
    EXPECT_NE(urlSpan, nullptr);
}

/**
 * @tc.name: SpanStringGetDefaultSpan005
 * @tc.desc: test GetDefaultSpan
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SpanStringGetDefaultSpan005, TestSize.Level1)
{
    auto span = SpanString::GetDefaultSpan(SpanType::CustomSpan);
    EXPECT_EQ(span, nullptr);
}

/**
 * @tc.name: SpanStringCheckRange001
 * @tc.desc: test CheckRange
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SpanStringCheckRange001, TestSize.Level1)
{
    SpanString spanString(u"text");
    RefPtr<SpanBase> span = AceType::MakeRefPtr<ExtSpan>(5, 3);
    auto result = spanString.CheckRange(span);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SpanStringCheckRange002
 * @tc.desc: test CheckRange
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SpanStringCheckRange002, TestSize.Level1)
{
    SpanString spanString(u"text");
    RefPtr<SpanBase> span = AceType::MakeRefPtr<ExtSpan>(1, 2);
    auto result = spanString.CheckRange(span);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SpanString_CheckRange001
 * @tc.desc: test CheckRange
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SpanString_CheckRange001, TestSize.Level1)
{
    SpanString spanString(u"text");
    auto result = spanString.CheckRange(1, 1, true);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SpanString_CheckRange002
 * @tc.desc: test CheckRange
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SpanString_CheckRange002, TestSize.Level1)
{
    SpanString spanString(u"text");
    auto result = spanString.CheckRange(0, 2, false);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SpanStringGetSubSpanList001
 * @tc.desc: test GetSubSpanList
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SpanStringGetSubSpanList001, TestSize.Level1)
{
    SpanString spanString(u"text");
    RefPtr<SpanBase> spanBase = AceType::MakeRefPtr<ExtSpan>(6, 1);
    std::list<RefPtr<SpanBase>> spans;
    spans.emplace_back(spanBase);
    auto result = spanString.GetSubSpanList(2, 3, spans);
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: SpanStringGetSubSpanList002
 * @tc.desc: test GetSubSpanList
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SpanStringGetSubSpanList002, TestSize.Level1)
{
    SpanString spanString(u"text");
    RefPtr<SpanBase> spanBase = AceType::MakeRefPtr<ExtSpan>(2, 2);
    std::list<RefPtr<SpanBase>> spans;
    spans.emplace_back(spanBase);
    auto result = spanString.GetSubSpanList(0, 5, spans);
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: SpanStringGetSpan001
 * @tc.desc: test GetSpan
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SpanStringGetSpan001, TestSize.Level1)
{
    SpanString spanString(u"string");
    RefPtr<SpanBase> spanBase = AceType::MakeRefPtr<ExtSpan>(2, 2);
    std::list<RefPtr<SpanBase>> spans;
    spans.emplace_back(spanBase);
    spanString.spansMap_.emplace(SpanType::ExtSpan, spans);
    auto result = spanString.GetSpan(0, 5, SpanType::ExtSpan);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: SpanStringOperator001
 * @tc.desc: test operator==
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SpanStringOperator001, TestSize.Level1)
{
    SpanString spanString(u"string");
    SpanString spanStringOne(u"string");
    GestureStyle gestureInfo;
    RefPtr<SpanBase> spanBase = AceType::MakeRefPtr<GestureSpan>(gestureInfo, 2, 2);
    std::list<RefPtr<SpanBase>> spans;
    spans.emplace_back(spanBase);
    spanString.spansMap_.emplace(SpanType::Gesture, spans);
    GestureStyle gesture;
    RefPtr<SpanBase> spanBaseOne = AceType::MakeRefPtr<GestureSpan>(gesture, 1, 2);
    std::list<RefPtr<SpanBase>> spanList;
    spanList.emplace_back(spanBaseOne);
    spanStringOne.spansMap_.emplace(SpanType::Gesture, spanList);
    auto result = spanString.operator==(spanStringOne);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SpanStringOperator002
 * @tc.desc: test operator==
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SpanStringOperator002, TestSize.Level1)
{
    SpanString spanString(u"string");
    SpanString spanStringOne(u"string");
    RefPtr<SpanBase> spanBase = AceType::MakeRefPtr<ExtSpan>(2, 2);
    std::list<RefPtr<SpanBase>> spans;
    spans.emplace_back(spanBase);
    spanString.spansMap_.emplace(SpanType::ExtSpan, spans);
    Font font;
    RefPtr<SpanBase> spanBaseOne = AceType::MakeRefPtr<FontSpan>(font, 1, 2);
    std::list<RefPtr<SpanBase>> spanList;
    spanList.emplace_back(spanBaseOne);
    spanStringOne.spansMap_.emplace(SpanType::Font, spanList);
    auto result = spanString.operator==(spanStringOne);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SpanStringOperator003
 * @tc.desc: test operator==
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SpanStringOperator003, TestSize.Level1)
{
    SpanString spanString(u"string");
    SpanString spanStringOne(u"string");
    RefPtr<SpanBase> spanBase = AceType::MakeRefPtr<ExtSpan>(2, 2);
    std::list<RefPtr<SpanBase>> spans;
    spans.emplace_back(spanBase);
    spanString.spansMap_.emplace(SpanType::ExtSpan, spans);
    RefPtr<SpanBase> spanBaseOne = AceType::MakeRefPtr<ExtSpan>(2, 2);
    Font font;
    RefPtr<SpanBase> spanBaseTwo = AceType::MakeRefPtr<FontSpan>(font, 1, 2);
    std::list<RefPtr<SpanBase>> spanList;
    spanList.emplace_back(spanBaseOne);
    spanList.emplace_back(spanBaseTwo);
    spanStringOne.spansMap_.emplace(SpanType::ExtSpan, spanList);
    auto result = spanString.operator==(spanStringOne);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SpanStringOperator004
 * @tc.desc: test operator==
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SpanStringOperator004, TestSize.Level1)
{
    SpanString spanString(u"string");
    SpanString spanStringOne(u"string");
    Dimension dimension(20.0);
    Color color(20, 10);
    Font font;
    font.fontWeight.emplace(FontWeight::BOLDER);
    font.fontSize.emplace(dimension);
    font.fontStyle = std::nullopt;
    font.fontColor.emplace(color);
    font.enableVariableFontWeight.emplace(true);
    RefPtr<SpanBase> spanBase = AceType::MakeRefPtr<FontSpan>(font, 1, 2);
    std::list<RefPtr<SpanBase>> spans;
    spans.emplace_back(spanBase);
    spanString.spansMap_.emplace(SpanType::Font, spans);
    Font fontOne;
    fontOne.fontWeight.emplace(FontWeight::BOLDER);
    fontOne.fontSize.emplace(dimension);
    fontOne.fontStyle = std::nullopt;
    fontOne.fontColor.emplace(color);
    fontOne.enableVariableFontWeight.emplace(true);
    RefPtr<SpanBase> spanBaseOne = AceType::MakeRefPtr<FontSpan>(fontOne, 1, 2);
    std::list<RefPtr<SpanBase>> spanList;
    spanList.emplace_back(spanBaseOne);
    spanStringOne.spansMap_.emplace(SpanType::Font, spanList);
    auto result = spanString.operator==(spanStringOne);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SpanStringGetSpecialTypesVector001
 * @tc.desc: test GetSpecialTypesVector
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SpanStringGetSpecialTypesVector001, TestSize.Level1)
{
    SpanString spanString(u"string");
    RefPtr<SpanBase> spanBase = AceType::MakeRefPtr<ExtSpan>(6, 1);
    std::list<RefPtr<SpanBase>> spans;
    spans.emplace_back(spanBase);
    spanString.spansMap_.emplace(SpanType::Image, spans);
    spanString.spansMap_.emplace(SpanType::CustomSpan, spans);
    std::list<int32_t> indexList;
    indexList.emplace_back(1);
    indexList.emplace_back(2);
    spanString.GetSpecialTypesVector(indexList, 2, 3);
    auto iter = std::find(indexList.begin(), indexList.end(), 6);
    auto iters = indexList.end();
    EXPECT_EQ(iter, iters);
}

/**
 * @tc.name: SpanStringGetSpecialTypesVector002
 * @tc.desc: test GetSpecialTypesVector
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SpanStringGetSpecialTypesVector002, TestSize.Level1)
{
    SpanString spanString(u"string");
    RefPtr<SpanBase> spanBase = AceType::MakeRefPtr<ExtSpan>(2, 2);
    std::list<RefPtr<SpanBase>> spans;
    spans.emplace_back(spanBase);
    spanString.spansMap_.emplace(SpanType::Image, spans);
    spanString.spansMap_.emplace(SpanType::CustomSpan, spans);
    std::list<int32_t> indexList;
    indexList.emplace_back(1);
    indexList.emplace_back(2);
    spanString.GetSpecialTypesVector(indexList, 0, 5);
    auto iter = std::find(indexList.begin(), indexList.end(), 6);
    auto iters = indexList.end();
    EXPECT_EQ(iter, iters);
}

/**
 * @tc.name: UrlSpanApplyToSpanItem001
 * @tc.desc: test ApplyToSpanItem
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, UrlSpanApplyToSpanItem001, TestSize.Level1)
{
    UrlSpan urlSpan("test");
    auto spanItem = AceType::MakeRefPtr<NG::SpanItem>();
    spanItem->urlOnRelease = UrlCallback;
    urlSpan.ApplyToSpanItem(spanItem, SpanOperation::REMOVE);
    EXPECT_EQ(spanItem->urlOnRelease, nullptr);
}
} // namespace OHOS::Ace::NG