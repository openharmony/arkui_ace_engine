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

#include <gmock/gmock.h>

#include "accessor_test_base.h"
#include "accessor_test_fixtures.h"

#include "core/interfaces/native/implementation/color_filter_peer.h"
#include "core/interfaces/native/implementation/image_attachment_peer.h"
#include "core/interfaces/native/implementation/pixel_map_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace AccessorTestFixtures;
using namespace Converter;

namespace GeneratedModifier {
const GENERATED_ArkUIColorFilterAccessor* GetColorFilterAccessor();
} // namespace GeneratedModifier
class ImageAttachmentAccessorTest : public AccessorTestCtorBase<GENERATED_ArkUIImageAttachmentAccessor,
        &GENERATED_ArkUIAccessors::getImageAttachmentAccessor, ImageAttachmentPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestCtorBase::SetUp();
        for (auto& [id, strid, res] : resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
    void* CreatePeerInstance() override
    {
        return accessor_->construct(nullptr);
    }
    RefPtr<PixelMap> CreatePixelMap(std::string& src);
};

RefPtr<PixelMap> ImageAttachmentAccessorTest::CreatePixelMap(std::string& src)
{
    void* ptr = reinterpret_cast<void*>(src.data());
    return PixelMap::CreatePixelMap(ptr);
}

namespace {
const CalcLength TEST_CALC_LENGTH(123.0_vp);
const auto TEST_DIMENSION = "123vp";

inline const std::vector<float> EMPTY_VECTOR = {};
inline std::vector<float> INVALID_MATRIX_LESS = { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 };
inline const std::vector<float> INVALID_MATRIX_MORE = { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1,
    0 };
inline const std::vector<float> VALID_MATRIX = { 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0 };
inline const std::vector<float> VALID_MATRIX_0 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
inline const std::vector<float> VALID_MATRIX_1 = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

inline ArkArrayHolder<Array_Float64> EMPTY_HOLDER(EMPTY_VECTOR);
inline ArkArrayHolder<Array_Float64> INVALID_HOLDER_0(INVALID_MATRIX_LESS);
inline ArkArrayHolder<Array_Float64> INVALID_HOLDER_1(INVALID_MATRIX_MORE);
inline ArkArrayHolder<Array_Float64> VALID_HOLDER_0(VALID_MATRIX_0);
inline ArkArrayHolder<Array_Float64> VALID_HOLDER_1(VALID_MATRIX_1);
inline ArkArrayHolder<Array_Float64> VALID_HOLDER_2(VALID_MATRIX);
inline ArkArrayHolder<Array_Float64> DEFAULT_VALUE_MATRIX(INVALID_MATRIX_MORE);

const std::vector<std::tuple<std::string, Array_Float64, std::optional<std::vector<float>>>> floatMatrixTest {
    { "EMPTY_VECTOR", ArkValue<Array_Float64>(EMPTY_HOLDER.ArkValue()), std::nullopt },
    { "VALID_HOLDER_0", ArkValue<Array_Float64>(VALID_HOLDER_0.ArkValue()), VALID_MATRIX_0 },
    { "INVALID_HOLDER_0", ArkValue<Array_Float64>(INVALID_HOLDER_0.ArkValue()), std::nullopt },
    { "VALID_HOLDER_1", ArkValue<Array_Float64>(VALID_HOLDER_1.ArkValue()), VALID_MATRIX_1 },
    { "INVALID_HOLDER_1", ArkValue<Array_Float64>(INVALID_HOLDER_1.ArkValue()), std::nullopt },
    { "VALID_HOLDER_2", ArkValue<Array_Float64>(VALID_HOLDER_2.ArkValue()), VALID_MATRIX }
};

const MarginProperty MARGIN_PADDING_PROPERTY = { .left = TEST_CALC_LENGTH,
    .right = TEST_CALC_LENGTH,
    .top = TEST_CALC_LENGTH,
    .bottom = TEST_CALC_LENGTH };
const BorderRadiusProperty BORDER_RADIUES_PROPERTY(Dimension::FromString(TEST_DIMENSION));

Opt_ImageAttachmentLayoutStyle getImageLayoutStyleFilled()
{
    const Ark_Padding arkPadding = {
        .left = ArkValue<Opt_Length>(TEST_DIMENSION),
        .top = ArkValue<Opt_Length>(TEST_DIMENSION),
        .right = ArkValue<Opt_Length>(TEST_DIMENSION),
        .bottom = ArkValue<Opt_Length>(TEST_DIMENSION),
    };
    const Ark_BorderRadiuses arkBorderRadiuses = {
        .bottomLeft = ArkValue<Opt_Length>(TEST_DIMENSION),
        .bottomRight = ArkValue<Opt_Length>(TEST_DIMENSION),
        .topLeft = ArkValue<Opt_Length>(TEST_DIMENSION),
        .topRight = ArkValue<Opt_Length>(TEST_DIMENSION)
    };
    const Ark_ImageAttachmentLayoutStyle imageLayoutStyle {
        .margin = ArkUnion<Opt_Union_LengthMetrics_Margin, Ark_Padding>(arkPadding),
        .padding = ArkUnion<Opt_Union_LengthMetrics_Padding, Ark_Padding>(arkPadding),
        .borderRadius = ArkUnion<Opt_Union_LengthMetrics_BorderRadiuses, Ark_BorderRadiuses>(arkBorderRadiuses),
    };
    return ArkValue<Opt_ImageAttachmentLayoutStyle>(imageLayoutStyle);
}
Opt_ImageAttachmentLayoutStyle getImageLayoutStyleLengthMetrics()
{
    const Ark_LengthMetrics lengthMetrics = ArkValue<Ark_LengthMetrics>(Dimension::FromString(TEST_DIMENSION));
    const Ark_ImageAttachmentLayoutStyle imageLayoutStyle {
        .margin = ArkUnion<Opt_Union_LengthMetrics_Margin, Ark_LengthMetrics>(lengthMetrics),
        .padding = ArkUnion<Opt_Union_LengthMetrics_Padding, Ark_LengthMetrics>(lengthMetrics),
        .borderRadius = ArkUnion<Opt_Union_LengthMetrics_BorderRadiuses, Ark_LengthMetrics>(lengthMetrics),
    };
    return ArkValue<Opt_ImageAttachmentLayoutStyle>(imageLayoutStyle);
};

Opt_ImageAttachmentLayoutStyle getImageLayoutStyleOptional()
{
    Ark_ImageAttachmentLayoutStyle imageLayoutStyle = {
        .margin = ArkUnion<Opt_Union_LengthMetrics_Margin>(Ark_Empty()),
        .padding = ArkUnion<Opt_Union_LengthMetrics_Padding>(Ark_Empty()),
        .borderRadius = ArkUnion<Opt_Union_LengthMetrics_BorderRadiuses>(Ark_Empty()),
    };
    return ArkValue<Opt_ImageAttachmentLayoutStyle>(imageLayoutStyle);
};

MATCHER_P(CompareArkColorFilterType, expected, "Compare ColorFilter and DrawingColorFilter in union") {
    auto expectedTest = expected;
    auto result = false;
    VisitUnion(
        arg,
        [&expectedTest, &result](const Ark_ColorFilter& filter) {
            if (filter) {
                result = filter->GetColorFilterMatrix() == expectedTest;
            } else if (expectedTest->size() == 0) {
                result = true;
            }
            GeneratedModifier::GetColorFilterAccessor()->destroyPeer(filter);
        },
        [](const Ark_drawing_ColorFilter& colorStrategy) {
            LOGE("Arkoala: ImageAttachmentAccessor convert from DrawinColorFilter doesn't supported");
        },
        [&expectedTest, &result]() {
            result = !expectedTest.has_value();
        });
    return result;
}
} // namespace
/**
 * @tc.name: ctorTestPixelMap
 * @tc.desc: Check the functionality of construct
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, ctorTestPixelMap, TestSize.Level1)
{
    std::string imagesSrc = "test";
    RefPtr<PixelMap> pixelMap = CreatePixelMap(imagesSrc);
    auto arkPixelMap = PeerUtils::CreatePeer<image_PixelMapPeer>();
    arkPixelMap->pixelMap = pixelMap;

    Ark_ImageAttachmentInterface content {
        .value = arkPixelMap,
    };
    auto inputValue = Converter::ArkUnion<Opt_AttachmentType,
        Ark_ImageAttachmentInterface>(content);
    auto peer = accessor_->construct(&inputValue);
    EXPECT_EQ(peer->span->GetImageSpanOptions().imagePixelMap, pixelMap);
    accessor_->destroyPeer(peer);
}

/**
 * @tc.name: ctorTestSize
 * @tc.desc: Check the functionality of construct
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, ctorTestSize, TestSize.Level1)
{
    for (auto& [input, test, expected] : testFixtureDimensionAnyValidValues) {
        Ark_SizeOptions size {
            .width = ArkValue<Opt_Length>(test),
            .height = ArkValue<Opt_Length>(test),
        };
        Ark_ImageAttachmentInterface content {
            .size = ArkValue<Opt_SizeOptions>(size),
        };
        auto inputValue = Converter::ArkUnion<Opt_AttachmentType,
            Ark_ImageAttachmentInterface>(content);
        auto peer = accessor_->construct(&inputValue);
        ASSERT_TRUE(peer->span->GetImageAttribute());
        ASSERT_TRUE(peer->span->GetImageAttribute()->size);
        if (expected.IsNonNegative()) {
            ASSERT_TRUE(peer->span->GetImageAttribute()->size->width);
            ASSERT_TRUE(peer->span->GetImageAttribute()->size->height);
            EXPECT_EQ(peer->span->GetImageAttribute()->size->width->ToString(), expected.ToString())
                << "Input value: " << input;
            EXPECT_EQ(peer->span->GetImageAttribute()->size->height->ToString(), expected.ToString())
                << "Input value: " << input;
        } else {
            ASSERT_FALSE(peer->span->GetImageAttribute()->size->width)
                << "Input value: " << input;
            ASSERT_FALSE(peer->span->GetImageAttribute()->size->height)
                << "Input value: " << input;
        }
        accessor_->destroyPeer(peer);
    }
}

/**
 * @tc.name: ctorTestSizeResources
 * @tc.desc: Check the functionality of construct
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, ctorTestSizeResources, TestSize.Level1)
{
    for (auto& [num_id, str_id, expected] : resourceInitTable) {
        auto expectPointer = std::get_if<Dimension>(&expected);
        ASSERT_TRUE(expectPointer);
        auto sizeResource = ArkValue<Opt_Length>(num_id);
        Ark_SizeOptions size {
            .width = sizeResource,
            .height = sizeResource,
        };
        Ark_ImageAttachmentInterface content {
            .size = ArkValue<Opt_SizeOptions>(size),
        };
        auto inputValue = Converter::ArkUnion<Opt_AttachmentType,
            Ark_ImageAttachmentInterface>(content);
        auto peer = accessor_->construct(&inputValue);
        ASSERT_TRUE(peer->span->GetImageAttribute());
        ASSERT_TRUE(peer->span->GetImageAttribute()->size);
        if (expectPointer->IsNonNegative()) {
            ASSERT_TRUE(peer->span->GetImageAttribute()->size->width);
            ASSERT_TRUE(peer->span->GetImageAttribute()->size->height);
            EXPECT_EQ(peer->span->GetImageAttribute()->size->width->ToString(), expectPointer->ToString());
            EXPECT_EQ(peer->span->GetImageAttribute()->size->height->ToString(), expectPointer->ToString());
        } else {
            ASSERT_FALSE(peer->span->GetImageAttribute()->size->width);
            ASSERT_FALSE(peer->span->GetImageAttribute()->size->height);
        }
        accessor_->destroyPeer(peer);
    }
}

/**
 * @tc.name: ctorTestVerticalAlignValidValues
 * @tc.desc: Check the functionality of construct
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, ctorTestVerticalAlignValidValues, TestSize.Level1)
{
    for (auto& [input, test, expected] : testFixtureVerticalAlignValidValues) {
        Ark_ImageAttachmentInterface content {
            .verticalAlign = ArkValue<Opt_ImageSpanAlignment>(test),
        };
        auto inputValue = Converter::ArkUnion<Opt_AttachmentType,
            Ark_ImageAttachmentInterface>(content);
        auto peer = accessor_->construct(&inputValue);
        ASSERT_TRUE(peer->span->GetImageAttribute());
        ASSERT_TRUE(peer->span->GetImageAttribute()->verticalAlign);
        EXPECT_EQ(peer->span->GetImageAttribute()->verticalAlign, expected);
        accessor_->destroyPeer(peer);
    }
}

/**
 * @tc.name: ctorTestVerticalAlignInvalidValues
 * @tc.desc: Check the functionality of construct
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, ctorTestVerticalAlignInvalidValues, TestSize.Level1)
{
    for (auto& [input, test, expected] : testFixtureVerticalAlignInvalidValues) {
        Ark_ImageAttachmentInterface content {
            .verticalAlign = ArkValue<Opt_ImageSpanAlignment>(test),
        };
        auto inputValue = Converter::ArkUnion<Opt_AttachmentType,
            Ark_ImageAttachmentInterface>(content);
        auto peer = accessor_->construct(&inputValue);
        ASSERT_TRUE(peer->span->GetImageAttribute());
        ASSERT_TRUE(peer->span->GetImageAttribute()->verticalAlign);
        accessor_->destroyPeer(peer);
    }
}

/**
 * @tc.name: ctorTestObjectFitValidValues
 * @tc.desc: Check the functionality of construct
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, ctorTestObjectFitValidValues, TestSize.Level1)
{
    for (auto& [input, test, expected] : testFixtureObjectFitValidValues) {
        Ark_ImageAttachmentInterface content {
            .objectFit = ArkValue<Opt_ImageFit>(test),
        };
        auto inputValue = Converter::ArkUnion<Opt_AttachmentType,
            Ark_ImageAttachmentInterface>(content);
        auto peer = accessor_->construct(&inputValue);
        ASSERT_TRUE(peer->span->GetImageAttribute());
        ASSERT_TRUE(peer->span->GetImageAttribute()->objectFit);
        EXPECT_EQ(peer->span->GetImageAttribute()->objectFit, expected);
        accessor_->destroyPeer(peer);
    }
}

/**
 * @tc.name: ctorTestObjectFitInvalidValues
 * @tc.desc: Check the functionality of construct
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, ctorTestObjectFitInvalidValues, TestSize.Level1)
{
    for (auto& [input, test, expected] : testFixtureObjectFitInvalidValues) {
        Ark_ImageAttachmentInterface content {
            .objectFit = ArkValue<Opt_ImageFit>(test),
        };
        auto inputValue = Converter::ArkUnion<Opt_AttachmentType,
            Ark_ImageAttachmentInterface>(content);
        auto peer = accessor_->construct(&inputValue);
        ASSERT_TRUE(peer->span->GetImageAttribute());
        ASSERT_TRUE(peer->span->GetImageAttribute()->objectFit);
        accessor_->destroyPeer(peer);
    }
}

/**
 * @tc.name: ctorTestImageStyleMargins
 * @tc.desc: Check the functionality of construct
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, ctorTestImageStyleOptional, TestSize.Level1)
{
    const Ark_ImageAttachmentInterface content {
        .layoutStyle = getImageLayoutStyleOptional(),
    };
    auto inputValue = Converter::ArkUnion<Opt_AttachmentType,
        Ark_ImageAttachmentInterface>(content);
    auto peer = accessor_->construct(&inputValue);
    ASSERT_TRUE(peer->span->GetImageAttribute());
    ASSERT_FALSE(peer->span->GetImageAttribute()->marginProp);
    ASSERT_FALSE(peer->span->GetImageAttribute()->paddingProp);
    ASSERT_FALSE(peer->span->GetImageAttribute()->borderRadius);
    accessor_->destroyPeer(peer);
};

/**
 * @tc.name: ctorTestImageStyleLengthMetrics
 * @tc.desc: Check the functionality of construct
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, ctorTestImageStyleLengthMetrics, TestSize.Level1)
{
    Ark_ImageAttachmentInterface content {
        .layoutStyle = getImageLayoutStyleLengthMetrics(),
    };
    auto inputValue = Converter::ArkUnion<Opt_AttachmentType,
        Ark_ImageAttachmentInterface>(content);
    auto peer = accessor_->construct(&inputValue);
    ASSERT_TRUE(peer->span->GetImageAttribute());
    ASSERT_TRUE(peer->span->GetImageAttribute()->marginProp);
    EXPECT_EQ(peer->span->GetImageAttribute()->marginProp, MARGIN_PADDING_PROPERTY);
    ASSERT_TRUE(peer->span->GetImageAttribute()->paddingProp);
    EXPECT_EQ(peer->span->GetImageAttribute()->paddingProp, MARGIN_PADDING_PROPERTY);
    ASSERT_TRUE(peer->span->GetImageAttribute()->borderRadius);
    EXPECT_EQ(peer->span->GetImageAttribute()->borderRadius, BORDER_RADIUES_PROPERTY);
    accessor_->destroyPeer(peer);
};

/**
 * @tc.name: ctorTestImageStyleMargins
 * @tc.desc: Check the functionality of construct
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, ctorTestImageStyleFilled, TestSize.Level1)
{
    const Ark_ImageAttachmentInterface content {
        .layoutStyle = getImageLayoutStyleFilled(),
    };
    auto inputValue = Converter::ArkUnion<Opt_AttachmentType,
        Ark_ImageAttachmentInterface>(content);
    auto peer = accessor_->construct(&inputValue);
    ASSERT_TRUE(peer->span->GetImageAttribute());
    ASSERT_TRUE(peer->span->GetImageAttribute()->marginProp);
    EXPECT_EQ(peer->span->GetImageAttribute()->marginProp, MARGIN_PADDING_PROPERTY);
    ASSERT_TRUE(peer->span->GetImageAttribute()->paddingProp);
    EXPECT_EQ(peer->span->GetImageAttribute()->paddingProp, MARGIN_PADDING_PROPERTY);
    ASSERT_TRUE(peer->span->GetImageAttribute()->borderRadius);
    EXPECT_EQ(peer->span->GetImageAttribute()->borderRadius, BORDER_RADIUES_PROPERTY);
    accessor_->destroyPeer(peer);
};

/**
 * @tc.name: ctorTestImageStyleMargins
 * @tc.desc: Check the functionality of construct
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, ctorTestColorFilter, TestSize.Level1)
{
    auto accessor = GeneratedModifier::GetColorFilterAccessor();
    ASSERT_TRUE(accessor);
    for (auto& [name, filter, expected] : floatMatrixTest) {
        auto peerFilter = accessor->construct(&filter);
        ASSERT_TRUE(peerFilter);
        auto unionValue = Converter::ArkUnion<Opt_ColorFilterType, Ark_ColorFilter>(peerFilter);
        const Ark_ImageAttachmentInterface content {
            .colorFilter = unionValue,
        };
        auto inputValue = Converter::ArkUnion<Opt_AttachmentType,
            Ark_ImageAttachmentInterface>(content);
        auto peer = accessor_->construct(&inputValue);
        ASSERT_TRUE(peer->span->GetImageAttribute());
        if (expected) {
            ASSERT_TRUE(peer->span->GetImageAttribute()->colorFilterMatrix);
            EXPECT_EQ(peer->span->GetImageAttribute()->colorFilterMatrix, expected);
        } else {
            ASSERT_FALSE(peer->span->GetImageAttribute()->colorFilterMatrix);
        }
        ASSERT_FALSE(peer->span->GetImageAttribute()->drawingColorFilter);
        accessor_->destroyPeer(peer);
    }
};

/**
 * @tc.name: ctorTestImageStyleMargins
 * @tc.desc: Check the functionality of construct
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, DISABLED_ctorTestDrawingColorFilter, TestSize.Level1)
{
    // DrawingColorFilter is not supperted yet
};

/**
 * @tc.name: getValueTest
 * @tc.desc: Check the functionality of getValue
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, getValueTest, TestSize.Level1)
{
    std::string imagesSrc = "test";
    RefPtr<PixelMap> pixelMap = CreatePixelMap(imagesSrc);
    auto arkPixelMap = PeerUtils::CreatePeer<image_PixelMapPeer>();
    arkPixelMap->pixelMap = pixelMap;

    Ark_ImageAttachmentInterface content {
        .value = arkPixelMap,
    };
    auto inputValue = Converter::ArkUnion<Opt_AttachmentType,
        Ark_ImageAttachmentInterface>(content);
    auto peer = accessor_->construct(&inputValue);
    auto pixelMapPeerValue = accessor_->getValue(peer);
    ASSERT_TRUE(pixelMapPeerValue);
    EXPECT_EQ(pixelMapPeerValue->pixelMap, pixelMap);
    accessor_->destroyPeer(peer);
}

/**
 * @tc.name: ctorTestSize
 * @tc.desc: Check the functionality of construct
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, getSizeTest, TestSize.Level1)
{
    for (auto& [input, test, expected] : testFixtureDimensionAnyValidValues) {
        Ark_SizeOptions size {
            .width = ArkValue<Opt_Length>(test),
            .height = ArkValue<Opt_Length>(test),
        };
        Ark_ImageAttachmentInterface content {
            .size = ArkValue<Opt_SizeOptions>(size),
        };
        auto inputValue = Converter::ArkUnion<Opt_AttachmentType,
            Ark_ImageAttachmentInterface>(content);
        auto peer = accessor_->construct(&inputValue);
        if (expected.IsNonNegative()) {
            EXPECT_THAT(accessor_->getSize(peer), CompareArkSize(size)) << "Passed value is: " << input;
        } else {
            Ark_SizeOptions emptySize {
                .width = ArkValue<Opt_Length>(test),
                .height = ArkValue<Opt_Length>(test),
            };
            EXPECT_THAT(accessor_->getSize(peer), CompareArkSize(emptySize)) << "Passed value is: " << input;
            ;
        }
        accessor_->destroyPeer(peer);
    }
}

/**
 * @tc.name: getVerticalAlignValidValues
 * @tc.desc: Check the functionality of getVerticalAlign
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, getVerticalAlignTestValidValues, TestSize.Level1)
{
    for (auto& [input, test, expected] : testFixtureVerticalAlignValidValues) {
        Ark_ImageAttachmentInterface content {
            .verticalAlign = ArkValue<Opt_ImageSpanAlignment>(test),
        };
        auto inputValue = Converter::ArkUnion<Opt_AttachmentType,
            Ark_ImageAttachmentInterface>(content);
        auto peer = accessor_->construct(&inputValue);
        EXPECT_EQ(Converter::GetOpt(accessor_->getVerticalAlign(peer)), test);
        accessor_->destroyPeer(peer);
    }
}

/**
 * @tc.name: getVerticalAlignInvalidValues
 * @tc.desc: Check the functionality of getVerticalAlign
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, getVerticalAlignTestInvalidValues, TestSize.Level1)
{
    for (auto& [input, test, expected] : testFixtureVerticalAlignInvalidValues) {
        Ark_ImageAttachmentInterface content {
            .verticalAlign = ArkValue<Opt_ImageSpanAlignment>(test),
        };
        auto inputValue = Converter::ArkUnion<Opt_AttachmentType,
            Ark_ImageAttachmentInterface>(content);
        auto peer = accessor_->construct(&inputValue);
        EXPECT_EQ(Converter::GetOpt(accessor_->getVerticalAlign(peer)), 1);
        accessor_->destroyPeer(peer);
    }
}

/**
 * @tc.name: getObjectFitTestValidValues
 * @tc.desc: Check the functionality of getObjectFit
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, getObjectFitTestValidValues, TestSize.Level1)
{
    for (auto& [input, test, expected] : testFixtureObjectFitValidValues) {
        Ark_ImageAttachmentInterface content {
            .objectFit = ArkValue<Opt_ImageFit>(test),
        };
        auto inputValue = Converter::ArkUnion<Opt_AttachmentType,
            Ark_ImageAttachmentInterface>(content);
        auto peer = accessor_->construct(&inputValue);
        EXPECT_EQ(Converter::GetOpt(accessor_->getObjectFit(peer)), test);
        accessor_->destroyPeer(peer);
    }
}

/**
 * @tc.name: getObjectFitInvalidValues
 * @tc.desc: Check the functionality of getObjectFit
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, getObjectFitTestInvalidValues, TestSize.Level1)
{
    for (auto& [input, test, expected] : testFixtureObjectFitInvalidValues) {
        Ark_ImageAttachmentInterface content {
            .objectFit = ArkValue<Opt_ImageFit>(test),
        };
        auto inputValue = Converter::ArkUnion<Opt_AttachmentType,
            Ark_ImageAttachmentInterface>(content);
        auto peer = accessor_->construct(&inputValue);
        EXPECT_EQ(Converter::GetOpt(accessor_->getObjectFit(peer)), 1);
        accessor_->destroyPeer(peer);
    }
}

/**
 * @tc.name: getObjectFitInvalidValues
 * @tc.desc: Check the functionality of getObjectFit
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, getLayoutStyleTestOptional, TestSize.Level1)
{
    auto expected = OptConvert<Ark_ImageAttachmentLayoutStyle>(getImageLayoutStyleOptional());
    const Ark_ImageAttachmentInterface content {
        .layoutStyle = getImageLayoutStyleOptional(),
    };
    auto inputValue = Converter::ArkUnion<Opt_AttachmentType,
        Ark_ImageAttachmentInterface>(content);
    auto peer = accessor_->construct(&inputValue);
    auto optGetValue = Converter::GetOpt(accessor_->getLayoutStyle(peer));
    ASSERT_TRUE(expected);
    ASSERT_TRUE(optGetValue);
    auto arkGetValue = *optGetValue;
    EXPECT_THAT(arkGetValue.margin, CompareOptMarginsPaddings(expected->margin));
    EXPECT_THAT(arkGetValue.padding, CompareOptMarginsPaddings(expected->padding));
    EXPECT_THAT(arkGetValue.borderRadius, CompareOptBorderRadius(expected->borderRadius));
    accessor_->destroyPeer(peer);
}

/**
 * @tc.name: getObjectFitInvalidValues
 * @tc.desc: Check the functionality of getObjectFit
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, getLayoutStyleTestFilled, TestSize.Level1)
{
    auto expected = OptConvert<Ark_ImageAttachmentLayoutStyle>(getImageLayoutStyleFilled());
    const Ark_ImageAttachmentInterface content {
        .layoutStyle = getImageLayoutStyleFilled(),
    };
    auto inputValue = Converter::ArkUnion<Opt_AttachmentType,
        Ark_ImageAttachmentInterface>(content);
    auto peer = accessor_->construct(&inputValue);
    auto optGetValue = Converter::GetOpt(accessor_->getLayoutStyle(peer));
    ASSERT_TRUE(expected);
    ASSERT_TRUE(optGetValue);
    auto arkGetValue = *optGetValue;
    EXPECT_THAT(arkGetValue.margin, CompareOptMarginsPaddings(expected->margin));
    EXPECT_THAT(arkGetValue.padding, CompareOptMarginsPaddings(expected->padding));
    EXPECT_THAT(arkGetValue.borderRadius, CompareOptBorderRadius(expected->borderRadius));
    accessor_->destroyPeer(peer);
}

/**
 * @tc.name: ctorTestImageStyleMargins
 * @tc.desc: Check the functionality of construct
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, getColorFilterTestColorFilter, TestSize.Level1)
{
    auto accessor = GeneratedModifier::GetColorFilterAccessor();
    ASSERT_TRUE(accessor);
    for (auto& [name, filter, expected] : floatMatrixTest) {
        auto peerFilter = accessor->construct(&filter);
        ASSERT_TRUE(peerFilter);
        auto unionValue = ArkUnion<Opt_ColorFilterType, Ark_ColorFilter>(peerFilter);
        const Ark_ImageAttachmentInterface content {
            .colorFilter = unionValue,
        };
        auto inputValue = Converter::ArkUnion<Opt_AttachmentType,
            Ark_ImageAttachmentInterface>(content);
        auto peer = accessor_->construct(&inputValue);
        ASSERT_TRUE(peer);
        EXPECT_THAT(accessor_->getColorFilter(peer), CompareArkColorFilterType(expected))
            << "ColorFilter is " << name;
        accessor_->destroyPeer(peer);
    }
};

/**
 * @tc.name: ctorTestImageStyleMargins
 * @tc.desc: Check the functionality of construct
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, DISABLED_getColorFilterTestDrawingColorFilter, TestSize.Level1)
{
    // DrawingColorFilter is not supperted yet
};
} // namespace OHOS::Ace::NG
