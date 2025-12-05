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
#include "core/interfaces/native/implementation/image_bitmap_peer_impl.h"

#include "accessor_test_base.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "gmock/gmock.h"

namespace OHOS::Ace::NG {

using testing::Return;
using namespace testing;
using namespace testing::ext;

const std::string DEFAULT_STRING_VALUE = "text";
const int DEFAULT_INT_VALUE = 100;
const Ark_Int32 DEFAULT_HEIGHT_VALUE = 0;
const Ark_Int32 DEFAULT_WIDTH_VALUE = 0;
const auto DEFAULT_RESOURCE = Converter::ArkUnion<Ark_Union_image_PixelMap_String, Ark_String>(DEFAULT_STRING_VALUE);
const auto DEFAULT_METRICS = Converter::ArkValue<Opt_LengthMetricsUnit>(Ace::CanvasUnit::PX);

std::vector<std::tuple<Ark_Number, double>> arkNumberTestPlan = {
    { Converter::ArkValue<Ark_Number>(100), 100 },
    { Converter::ArkValue<Ark_Number>(0), 0 },
    { Converter::ArkValue<Ark_Number>(-100), -100 },
    { Converter::ArkValue<Ark_Number>(12.34), 12.34 },
    { Converter::ArkValue<Ark_Number>(-56.73), -56.73 },
};

namespace {
struct MockImageBitmapPeer : public ImageBitmapPeer {
public:
    MockImageBitmapPeer() = default;
    ~MockImageBitmapPeer() override = default;
    using ImageBitmapPeer::SetHeight;
    using ImageBitmapPeer::SetWidth;
    using ImageBitmapPeer::SetCloseCallback;
};
}

class ImageBitmapAccessorTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        ASSERT_NE(accessor_, nullptr);
        ASSERT_NE(accessor_->construct, nullptr);
        finalyzer_ = reinterpret_cast<void (*)(MockImageBitmapPeer *)>(accessor_->getFinalizer());
        ASSERT_NE(accessor_->getFinalizer, nullptr);
    }

    virtual void SetUp()
    {
        ASSERT_NE(finalyzer_, nullptr);
    }

    virtual void TearDown()
    {
        FinalizePeer();
    }

    void FinalizePeer()
    {
        if (peer_) {
            ASSERT_NE(finalyzer_, nullptr);
            finalyzer_(peer_);
            peer_ = nullptr;
        }
    }

private:
    inline static const GENERATED_ArkUIFullNodeAPI *fullAPI_
        = reinterpret_cast<const GENERATED_ArkUIFullNodeAPI *>(
            GENERATED_GetArkAnyAPI(GENERATED_Ark_APIVariantKind::GENERATED_FULL, GENERATED_ARKUI_FULL_API_VERSION)
        );

public:
    inline static const GENERATED_ArkUIImageBitmapAccessor *accessor_ =
        fullAPI_->getAccessors()->getImageBitmapAccessor();
    inline static void (*finalyzer_)(MockImageBitmapPeer *) = nullptr;
    MockImageBitmapPeer *peer_ = nullptr;
};

/**
 * @tc.name: close_success
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageBitmapAccessorTest, close_success, TestSize.Level1)
{
    Converter::ConvContext ctx;
    auto imageResource = Converter::ArkUnion<Ark_Union_image_PixelMap_String, Ark_String>(DEFAULT_STRING_VALUE, &ctx);
    auto unit = Converter::ArkValue<Opt_LengthMetricsUnit>();
    peer_ = reinterpret_cast<MockImageBitmapPeer *>(accessor_->construct(&imageResource, &unit));
    bool result = false;
    auto clouseFunc = [&result]() {
        result = true;
    };
    peer_->SetCloseCallback(clouseFunc);
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(accessor_->close, nullptr);

    accessor_->close(peer_);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: getHeight
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageBitmapAccessorTest, getHeight, TestSize.Level1)
{
    Converter::ConvContext ctx;
    auto imageResource = Converter::ArkUnion<Ark_Union_image_PixelMap_String, Ark_String>(DEFAULT_STRING_VALUE, &ctx);
    auto unit = Converter::ArkValue<Opt_LengthMetricsUnit>();
    peer_ = reinterpret_cast<MockImageBitmapPeer *>(accessor_->construct(&imageResource, &unit));
    ASSERT_NE(peer_, nullptr);
    peer_->SetHeight(DEFAULT_INT_VALUE);
    ASSERT_NE(accessor_->getHeight, nullptr);
    auto custValue = Converter::ArkValue<Ark_Int32>(DEFAULT_INT_VALUE);

    auto result = Converter::Convert<int32_t>(accessor_->getHeight(peer_));
    EXPECT_EQ(result, custValue);
}

/**
 * @tc.name: getWidth
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageBitmapAccessorTest, getWidth, TestSize.Level1)
{
    Converter::ConvContext ctx;
    auto imageResource = Converter::ArkUnion<Ark_Union_image_PixelMap_String, Ark_String>(DEFAULT_STRING_VALUE, &ctx);
    auto unit = Converter::ArkValue<Opt_LengthMetricsUnit>();
    peer_ = reinterpret_cast<MockImageBitmapPeer *>(accessor_->construct(&imageResource, &unit));
    ASSERT_NE(peer_, nullptr);
    peer_->SetWidth(DEFAULT_INT_VALUE);
    ASSERT_NE(accessor_->getHeight, nullptr);
    auto custValue = Converter::ArkValue<Ark_Int32>(DEFAULT_INT_VALUE);

    auto result = Converter::Convert<int32_t>(accessor_->getWidth(peer_));
    EXPECT_EQ(result, custValue);
}

/**
 * @tc.name: closeImpl_NullPointer
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageBitmapAccessorTest, closeImpl_NullPointer, TestSize.Level1)
{
    ASSERT_NE(accessor_->close, nullptr);

    accessor_->close(nullptr);
}

/**
 * @tc.name: getHeightImpl_NullPointer
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageBitmapAccessorTest, getHeightImpl_NullPointer, TestSize.Level1)
{
    ASSERT_NE(accessor_->getHeight, nullptr);

    auto result = Converter::Convert<int32_t>(accessor_->getHeight(nullptr));
    EXPECT_EQ(result, DEFAULT_HEIGHT_VALUE);
}

/**
 * @tc.name: getWidthImpl_NullPointer
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageBitmapAccessorTest, getWidthImpl_NullPointer, TestSize.Level1)
{
    ASSERT_NE(accessor_->getWidth, nullptr);

    auto result = Converter::Convert<int32_t>(accessor_->getWidth(nullptr));
    EXPECT_EQ(result, DEFAULT_WIDTH_VALUE);
}
} // namespace OHOS::Ace::NG
