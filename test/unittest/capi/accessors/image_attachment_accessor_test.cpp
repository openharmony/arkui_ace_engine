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

#include "accessor_test_base.h"
#include "accessor_test_fixtures.h"
#include "gmock/gmock.h"
#include "node_api.h"

#include "core/interfaces/native/implementation/image_attachment_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace AccessorTestFixtures;
using namespace Converter;

namespace GeneratedModifier {
    const GENERATED_ArkUIPixelMapAccessor* GetPixelMapAccessor();
}
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
        return accessor_->ctor(nullptr);
    }
    RefPtr<PixelMap> CreatePixelMap(std::string& src);
};

RefPtr<PixelMap> ImageAttachmentAccessorTest::CreatePixelMap(std::string& src)
{
    void* ptr = reinterpret_cast<void*>(src.data());
    return PixelMap::CreatePixelMap(ptr);
}

/**
 * @tc.name: ctorTestPixelMap
 * @tc.desc: Check the functionality of ctor
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, ctorTestPixelMap, TestSize.Level1)
{
    std::string imagesSrc = "test";
    RefPtr<PixelMap> pixelMap = CreatePixelMap(imagesSrc);
    auto arkPixelMap = GeneratedModifier::GetPixelMapAccessor()->ctor();
    arkPixelMap->pixelMap = pixelMap;

    Ark_ImageAttachmentInterface value {
        .value = arkPixelMap,
    };
    auto peer = accessor_->ctor(&value);
    EXPECT_EQ(peer->imageSpan->GetImageSpanOptions().imagePixelMap, pixelMap);
    accessor_->destroyPeer(peer);
    GeneratedModifier::GetPixelMapAccessor()->destroyPeer(arkPixelMap);
}

/**
 * @tc.name: ctorTestSize
 * @tc.desc: Check the functionality of ctor
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, ctorTestSize, TestSize.Level1)
{
    for (auto& [input, test, expected] : testFixtureDimensionAnyValidValues) {
        Ark_SizeOptions size {
            .width = Converter::ArkValue<Opt_Length>(test),
            .height = Converter::ArkValue<Opt_Length>(test),
        };
        Ark_ImageAttachmentInterface value {
            .size = ArkValue<Opt_SizeOptions>(size),
        };
        auto peer = accessor_->ctor(&value);
        ASSERT_TRUE(peer->imageSpan->GetImageSpanOptions().imageAttribute);
        ASSERT_TRUE(peer->imageSpan->GetImageSpanOptions().imageAttribute->size);
        if (expected.IsNonNegative()) {
            ASSERT_TRUE(peer->imageSpan->GetImageSpanOptions().imageAttribute->size->width);
            ASSERT_TRUE(peer->imageSpan->GetImageSpanOptions().imageAttribute->size->height);
            EXPECT_EQ(
                peer->imageSpan->GetImageSpanOptions().imageAttribute->size->width->ToString(), expected.ToString());
            EXPECT_EQ(
                peer->imageSpan->GetImageSpanOptions().imageAttribute->size->height->ToString(), expected.ToString());
        } else {
            ASSERT_FALSE(peer->imageSpan->GetImageSpanOptions().imageAttribute->size->width);
            ASSERT_FALSE(peer->imageSpan->GetImageSpanOptions().imageAttribute->size->height);
        }
        accessor_->destroyPeer(peer);
    }
}

/**
 * @tc.name: ctorTestSizeResources
 * @tc.desc: Check the functionality of ctor
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, ctorTestSizeResources, TestSize.Level1)
{
    for (auto& [num_id, str_id, expected] : resourceInitTable) {
        auto expectPointer = std::get_if<Dimension>(&expected);
        ASSERT_TRUE(expectPointer);
        auto sizeResource = ArkValue<Ark_Length>(Ark_Length { .type = Ark_Tag::ARK_TAG_RESOURCE, .resource = num_id });
        Ark_SizeOptions size {
            .width = Converter::ArkValue<Opt_Length>(sizeResource),
            .height = Converter::ArkValue<Opt_Length>(sizeResource),
        };
        Ark_ImageAttachmentInterface value {
            .size = ArkValue<Opt_SizeOptions>(size),
        };
        auto peer = accessor_->ctor(&value);
        ASSERT_TRUE(peer->imageSpan->GetImageSpanOptions().imageAttribute);
        ASSERT_TRUE(peer->imageSpan->GetImageSpanOptions().imageAttribute->size);
        if (expectPointer->IsNonNegative()) {
            ASSERT_TRUE(peer->imageSpan->GetImageSpanOptions().imageAttribute->size->width);
            ASSERT_TRUE(peer->imageSpan->GetImageSpanOptions().imageAttribute->size->height);
            EXPECT_EQ(peer->imageSpan->GetImageSpanOptions().imageAttribute->size->width->ToString(),
                expectPointer->ToString());
            EXPECT_EQ(peer->imageSpan->GetImageSpanOptions().imageAttribute->size->height->ToString(),
                expectPointer->ToString());
        } else {
            ASSERT_FALSE(peer->imageSpan->GetImageSpanOptions().imageAttribute->size->width);
            ASSERT_FALSE(peer->imageSpan->GetImageSpanOptions().imageAttribute->size->height);
        }
        accessor_->destroyPeer(peer);
    }
}

/**
 * @tc.name: ctorTestVerticalAlignValidValues
 * @tc.desc: Check the functionality of ctor
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, ctorTestVerticalAlignValidValues, TestSize.Level1)
{
    for (auto& [input, test, expected] : testFixtureVerticalAlignValidValues) {
        Ark_ImageAttachmentInterface value {
            .verticalAlign = ArkValue<Opt_ImageSpanAlignment>(test),
        };
        auto peer = accessor_->ctor(&value);
        ASSERT_TRUE(peer->imageSpan->GetImageSpanOptions().imageAttribute);
        ASSERT_TRUE(peer->imageSpan->GetImageSpanOptions().imageAttribute->verticalAlign);
        EXPECT_EQ(peer->imageSpan->GetImageSpanOptions().imageAttribute->verticalAlign, expected);
        accessor_->destroyPeer(peer);
    }
}

/**
 * @tc.name: ctorTestVerticalAlignInvalidValues
 * @tc.desc: Check the functionality of ctor
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, ctorTestVerticalAlignInvalidValues, TestSize.Level1)
{
    for (auto& [input, test, expected] : testFixtureVerticalAlignInvalidValues) {
        Ark_ImageAttachmentInterface value {
            .verticalAlign = ArkValue<Opt_ImageSpanAlignment>(test),
        };
        auto peer = accessor_->ctor(&value);
        ASSERT_TRUE(peer->imageSpan->GetImageSpanOptions().imageAttribute);
        ASSERT_FALSE(peer->imageSpan->GetImageSpanOptions().imageAttribute->verticalAlign);
        accessor_->destroyPeer(peer);
    }
}

/**
 * @tc.name: ctorTestObjectFitValidValues
 * @tc.desc: Check the functionality of ctor
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, ctorTestObjectFitValidValues, TestSize.Level1)
{
    for (auto& [input, test, expected] : testFixtureObjectFitValidValues) {
        Ark_ImageAttachmentInterface value {
            .objectFit = ArkValue<Opt_ImageFit>(test),
        };
        auto peer = accessor_->ctor(&value);
        ASSERT_TRUE(peer->imageSpan->GetImageSpanOptions().imageAttribute);
        ASSERT_TRUE(peer->imageSpan->GetImageSpanOptions().imageAttribute->objectFit);
        EXPECT_EQ(peer->imageSpan->GetImageSpanOptions().imageAttribute->objectFit, expected);
        accessor_->destroyPeer(peer);
    }
}

/**
 * @tc.name: ctorTestObjectFitInvalidValues
 * @tc.desc: Check the functionality of ctor
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, ctorTestObjectFitInvalidValues, TestSize.Level1)
{
    for (auto& [input, test, expected] : testFixtureObjectFitInvalidValues) {
        Ark_ImageAttachmentInterface value {
            .objectFit = ArkValue<Opt_ImageFit>(test),
        };
        auto peer = accessor_->ctor(&value);
        ASSERT_TRUE(peer->imageSpan->GetImageSpanOptions().imageAttribute);
        ASSERT_FALSE(peer->imageSpan->GetImageSpanOptions().imageAttribute->objectFit);
        accessor_->destroyPeer(peer);
    }
}

/**
 * @tc.name: ctorTestImageStyleLengthMetrics
 * @tc.desc: Check the functionality of ctor
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, ctorTestImageStyleLengthMetrics, TestSize.Level1)
{
    const CalcLength length(123.0_vp);
    MarginProperty prop = {
        .left = length,
        .right = length,
        .top = length,
        .bottom = length
    };
    const Ark_LengthMetrics lengthMetrics = Converter::ArkValue<Ark_LengthMetrics>(length.GetDimension());
    const Ark_ImageAttachmentLayoutStyle imageLayoutStyle {
        .margin = Converter::ArkUnion<Opt_Union_LengthMetrics_Margin, Ark_LengthMetrics>(lengthMetrics),
        .padding = Converter::ArkUnion<Opt_Union_LengthMetrics_Padding, Ark_LengthMetrics>(lengthMetrics),
        .borderRadius = Converter::ArkUnion<Opt_Union_LengthMetrics_BorderRadiuses, Ark_LengthMetrics>(lengthMetrics),
    };
    Ark_ImageAttachmentInterface value {
        .layoutStyle = ArkValue<Opt_ImageAttachmentLayoutStyle>(imageLayoutStyle),
    };
    auto peer = accessor_->ctor(&value);
    ASSERT_TRUE(peer->imageSpan->GetImageSpanOptions().imageAttribute);
    ASSERT_TRUE(peer->imageSpan->GetImageSpanOptions().imageAttribute->marginProp);
    EXPECT_EQ(peer->imageSpan->GetImageSpanOptions().imageAttribute->marginProp, prop);
    accessor_->destroyPeer(peer);
};

/**
 * @tc.name: ctorTestImageStyleMargins
 * @tc.desc: Check the functionality of ctor
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, ctorTestImageStyleMargins, TestSize.Level1)
{
    const CalcLength length(123.0_vp);
    MarginProperty prop = {
        .left = length,
        .right = length,
        .top = length,
        .bottom = length
    };
    Ark_Padding arkPadding = {
        .left = ArkValue<Opt_Length>(length.GetDimension()),
        .top = ArkValue<Opt_Length>(length.GetDimension()),
        .right = ArkValue<Opt_Length>(length.GetDimension()),
        .bottom= ArkValue<Opt_Length>(length.GetDimension()),
    };
    Ark_BorderRadiuses arkBorderRadiuses = {
        .bottomLeft = ArkValue<Opt_Length>(length.GetDimension()),
        .bottomRight = ArkValue<Opt_Length>(length.GetDimension()),
        .topLeft = ArkValue<Opt_Length>(length.GetDimension()),
        .topRight = ArkValue<Opt_Length>(length.GetDimension())
    };
    const Ark_ImageAttachmentLayoutStyle imageLayoutStyle {
        .margin = ArkUnion<Opt_Union_LengthMetrics_Margin, Ark_Padding>(arkPadding),
        .padding = ArkUnion<Opt_Union_LengthMetrics_Padding, Ark_Padding>(arkPadding),
        .borderRadius = ArkUnion<Opt_Union_LengthMetrics_BorderRadiuses, Ark_BorderRadiuses>(arkBorderRadiuses),
    };
    Ark_ImageAttachmentInterface value {
        .layoutStyle = ArkValue<Opt_ImageAttachmentLayoutStyle>(imageLayoutStyle),
    };
    auto peer = accessor_->ctor(&value);
    ASSERT_TRUE(peer->imageSpan->GetImageSpanOptions().imageAttribute);
    ASSERT_TRUE(peer->imageSpan->GetImageSpanOptions().imageAttribute->marginProp);
    EXPECT_EQ(peer->imageSpan->GetImageSpanOptions().imageAttribute->marginProp, prop);
    accessor_->destroyPeer(peer);
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
    auto arkPixelMap = GeneratedModifier::GetPixelMapAccessor()->ctor();
    arkPixelMap->pixelMap = pixelMap;

    Ark_ImageAttachmentInterface value {
        .value = arkPixelMap,
    };
    auto peer = accessor_->ctor(&value);
    auto pixelMapPeerValue = accessor_->getValue(peer);
    ASSERT_TRUE(pixelMapPeerValue);
    EXPECT_EQ(pixelMapPeerValue->pixelMap, pixelMap);
    accessor_->destroyPeer(peer);
    GeneratedModifier::GetPixelMapAccessor()->destroyPeer(arkPixelMap);
}

/**
 * @tc.name: getVerticalAlignValidValues
 * @tc.desc: Check the functionality of getVerticalAlign
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, getVerticalAlignValidValues, TestSize.Level1)
{
    for (auto& [input, test, expected] : testFixtureVerticalAlignValidValues) {
        Ark_ImageAttachmentInterface value {
            .verticalAlign = ArkValue<Opt_ImageSpanAlignment>(test),
        };
        auto peer = accessor_->ctor(&value);
        EXPECT_EQ(accessor_->getVerticalAlign(peer), test);
        accessor_->destroyPeer(peer);
    }
}

/**
 * @tc.name: getVerticalAlignInvalidValues
 * @tc.desc: Check the functionality of getVerticalAlign
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, getVerticalAlignInvalidValues, TestSize.Level1)
{
    for (auto& [input, test, expected] : testFixtureVerticalAlignInvalidValues) {
        Ark_ImageAttachmentInterface value {
            .verticalAlign = ArkValue<Opt_ImageSpanAlignment>(test),
        };
        auto peer = accessor_->ctor(&value);
        EXPECT_EQ(accessor_->getVerticalAlign(peer), INVALID_ENUM_VAL<Ark_ImageSpanAlignment>);
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
        Ark_ImageAttachmentInterface value {
            .objectFit = ArkValue<Opt_ImageFit>(test),
        };
        auto peer = accessor_->ctor(&value);
        EXPECT_EQ(accessor_->getObjectFit(peer), test);
        accessor_->destroyPeer(peer);
    }
}

/**
 * @tc.name: getObjectFitInvalidValues
 * @tc.desc: Check the functionality of getObjectFit
 * @tc.type: FUNC
 */
HWTEST_F(ImageAttachmentAccessorTest, getObjectFitInvalidValues, TestSize.Level1)
{
    for (auto& [input, test, expected] : testFixtureObjectFitInvalidValues) {
        Ark_ImageAttachmentInterface value {
            .objectFit = ArkValue<Opt_ImageFit>(test),
        };
        auto peer = accessor_->ctor(&value);
        EXPECT_EQ(accessor_->getObjectFit(peer), INVALID_ENUM_VAL<Ark_ImageFit>);
        accessor_->destroyPeer(peer);
    }
}
} // namespace OHOS::Ace::NG
