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

#include <algorithm>
#include "accessor_test_base.h"
#include "accessor_test_utils.h"
#include "core/interfaces/native/implementation/image_data_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/unittest/capi/modifiers/generated/type_helpers.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
    constexpr int32_t WIDTH = 10;
    constexpr int32_t HEIGHT = 5;
    constexpr int32_t ARRAY_LENGTH = 4;
    uint8_t g_dataArray[] = { 1, 55, 0, 255 };
}

class ImageDataAccessorTest
    : public AccessorTestBaseParent<GENERATED_ArkUIImageDataAccessor,
        &GENERATED_ArkUIAccessors::getImageDataAccessor, ImageDataPeer> {
public:
    static void SetUpTestCase()
    {
        AccessorTestBaseParent::SetUpTestCase();
    }

    void FinalizePeer()
    {
        if (peer_) {
            ASSERT_NE(finalyzer_, nullptr);
            finalyzer_(peer_);
            peer_ = nullptr;
        }
    }
};

/**
 * @tc.name: CtorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageDataAccessorTest, CtorTest, TestSize.Level1)
{
    const Ark_Number arkWidth = Converter::ArkValue<Ark_Number>(WIDTH);
    const Ark_Number arkHeight = Converter::ArkValue<Ark_Number>(HEIGHT);
    InteropBuffer buffer = {
        .data = &g_dataArray,
        .length = ARRAY_LENGTH
    };
    auto bufferOpt = Converter::ArkValue<Opt_Buffer>(buffer);

    peer_ = reinterpret_cast<ImageDataPeer*>(accessor_->construct(&arkWidth, &arkHeight, &bufferOpt, nullptr));
    EXPECT_EQ(peer_->value.dirtyWidth, WIDTH);
    EXPECT_EQ(peer_->value.dirtyHeight, HEIGHT);
    ASSERT_EQ(peer_->value.data.size(), ARRAY_LENGTH / sizeof(uint32_t));
    for (int32_t idx = 0; idx < ARRAY_LENGTH; idx++) {
        EXPECT_EQ(reinterpret_cast<uint8_t*>(peer_->value.data.data())[idx], g_dataArray[idx]);
    }
}

/**
 * @tc.name: CtorInvalidValuesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageDataAccessorTest, CtorInvalidValuesTest, TestSize.Level1)
{
    const Ark_Number arkWidth = Converter::ArkValue<Ark_Number>(WIDTH);
    const Ark_Number arkHeight = Converter::ArkValue<Ark_Number>(HEIGHT);
    InteropBuffer buffer = {
        .data = &g_dataArray,
        .length = ARRAY_LENGTH
    };
    auto bufferOpt = Converter::ArkValue<Opt_Buffer>(buffer);

    peer_ = reinterpret_cast<ImageDataPeer*>(accessor_->construct(nullptr, &arkHeight, &bufferOpt, nullptr));
    EXPECT_EQ(peer_, nullptr);
    peer_ = reinterpret_cast<ImageDataPeer*>(accessor_->construct(&arkWidth, nullptr, &bufferOpt, nullptr));
    EXPECT_EQ(peer_, nullptr);
    peer_ = reinterpret_cast<ImageDataPeer*>(accessor_->construct(&arkWidth, &arkHeight, nullptr, nullptr));
    ASSERT_NE(peer_, nullptr);
    EXPECT_EQ(peer_->value.data.size(), 0);
}

/**
 * @tc.name: GetWidthTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageDataAccessorTest, GetWidthTest, TestSize.Level1)
{
    const Ark_Number arkWidth = Converter::ArkValue<Ark_Number>(WIDTH);
    const Ark_Number arkHeight = Converter::ArkValue<Ark_Number>(HEIGHT);

    peer_ = reinterpret_cast<ImageDataPeer*>(accessor_->construct(&arkWidth, &arkHeight, nullptr, nullptr));
    ASSERT_NE(peer_, nullptr);
    auto resultVal = Converter::Convert<int32_t>(accessor_->getWidth(peer_));
    EXPECT_EQ(resultVal, WIDTH);
}

/**
 * @tc.name: GetHeightTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageDataAccessorTest, GetHeightTest, TestSize.Level1)
{
    const Ark_Number arkWidth = Converter::ArkValue<Ark_Number>(WIDTH);
    const Ark_Number arkHeight = Converter::ArkValue<Ark_Number>(HEIGHT);

    peer_ = reinterpret_cast<ImageDataPeer*>(accessor_->construct(&arkWidth, &arkHeight, nullptr, nullptr));
    ASSERT_NE(peer_, nullptr);
    auto resultVal = Converter::Convert<int32_t>(accessor_->getHeight(peer_));
    EXPECT_EQ(resultVal, HEIGHT);
}

}
