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

#include "test/mock/core/pattern/mock_canvas_pattern.h"
#include <gmock/gmock.h>

#include "core/components_ng/pattern/canvas/canvas_paint_method.h"
#include "core/components_ng/pattern/canvas/canvas_rendering_context_2d_model_ng.h"
#include "core/interfaces/native/implementation/image_bitmap_peer_impl.h"
#include "core/interfaces/native/implementation/offscreen_canvas_rendering_context2d_peer_impl.h"
#include "core/interfaces/native/implementation/rendering_context_settings_peer.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "accessor_test_base.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
const double DEFAULT_WIDTH = 12.34;
const double DEFAULT_HEIGHT = 56.73;
const double DEFAULT_DOUBLE_VALUE = 0.0;
const auto DEFAULT_UNIT = Ace::CanvasUnit::PX;
const Ark_Number ARK_DEFAULT_WIDTH = ArkValue<Ark_Number>(DEFAULT_WIDTH);
const Ark_Number ARK_DEFAULT_HEIGHT = ArkValue<Ark_Number>(DEFAULT_HEIGHT);
const Opt_RenderingContextSettings OPT_DEFAULT_SETTINGS =
    ArkValue<Opt_RenderingContextSettings>(RenderingContextSettingsPeer::Create(false));
const std::string IMAGE_PNG = "image/png";
const std::string IMAGE_JPEG = "image/jpeg";
const std::string IMAGE_WEBP = "image/webp";
const std::string EMPTY_STRING = "";
const auto DEFAULT_QUALITY = 0.92f;
const double FLT_PRECISION = 0.001;

const std::vector<std::pair<Opt_String, std::string>> optImageTypeTestPlan {
    { Converter::ArkValue<Opt_String>(IMAGE_PNG), IMAGE_PNG },
    { Converter::ArkValue<Opt_String>(IMAGE_JPEG), IMAGE_JPEG },
    { Converter::ArkValue<Opt_String>(IMAGE_WEBP), IMAGE_WEBP },
    { Converter::ArkValue<Opt_String>(EMPTY_STRING), EMPTY_STRING },
    { Converter::ArkValue<Opt_String>(Ark_Empty()), EMPTY_STRING },
};
const std::vector<std::pair<Opt_Float32, float>> optImageQualityTestPlan {
    { Converter::ArkValue<Opt_Float32>(-10.0f), -10.0f },
    { Converter::ArkValue<Opt_Float32>(0.0f), 0.0f },
    { Converter::ArkValue<Opt_Float32>(0.5f), 0.5f },
    { Converter::ArkValue<Opt_Float32>(1.0f), 1.0f },
    { Converter::ArkValue<Opt_Float32>(10.0f), 10.0f },
    { Converter::ArkValue<Opt_Float32>(Ark_Empty()), DEFAULT_QUALITY },
};
const std::vector<double> numberTestPlan = { 100, 0, -100, 12.34, -56.73 };
class MockCanvasRenderingContext2DModel : public NG::CanvasRenderingContext2DModelNG {
public:
    MockCanvasRenderingContext2DModel() = default;
    ~MockCanvasRenderingContext2DModel() override = default;

    MOCK_METHOD(std::string, ToDataURL, (const std::string&, double), (override));
    MOCK_METHOD(void, SetPattern, (RefPtr<AceType>), (override));
    MOCK_METHOD(void, SetShadowColor, (const Color&), (override));
    MOCK_METHOD(void, SetDensity, (double density), (override));
};
} // namespace

class OffScreenCanvasRenderingContext2DAccessorTest
    : public AccessorTestCtorBase<GENERATED_ArkUIOffscreenCanvasRenderingContext2DAccessor,
          &GENERATED_ArkUIAccessors::getOffscreenCanvasRenderingContext2DAccessor,
          OffscreenCanvasRenderingContext2DPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestCtorBase::SetUp();
        renderingModel_ = AceType::MakeRefPtr<NiceMock<MockCanvasRenderingContext2DModel>>();
        reinterpret_cast<GeneratedModifier::OffscreenCanvasRenderingContext2DPeerImpl*>(peer_)
            ->SetRenderingContext2DModel(renderingModel_);
    }

    void TearDown() override
    {
        AccessorTestCtorBase::TearDown();
        renderingModel_ = nullptr;
    }

    void* CreatePeerInstance() override
    {
        return accessor_->ctor(&ARK_DEFAULT_WIDTH, &ARK_DEFAULT_HEIGHT, &OPT_DEFAULT_SETTINGS);
    }

    RefPtr<MockCanvasRenderingContext2DModel> renderingModel_ = nullptr;
};

/**
 * @tc.name: ctorDefaultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(OffScreenCanvasRenderingContext2DAccessorTest, ctorDefaultTest, TestSize.Level1)
{
    ASSERT_NE(peer_, nullptr);
    auto peer = reinterpret_cast<GeneratedModifier::OffscreenCanvasRenderingContext2DPeerImpl*>(peer_);
    ASSERT_NE(peer, nullptr);

    EXPECT_NEAR(peer->GetWidth(), DEFAULT_DOUBLE_VALUE, FLT_PRECISION);
    EXPECT_NEAR(peer->GetHeight(), DEFAULT_DOUBLE_VALUE, FLT_PRECISION);
    EXPECT_FALSE(peer->GetAnti());
}

/**
 * @tc.name: ctorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(OffScreenCanvasRenderingContext2DAccessorTest, ctorTest, TestSize.Level1)
{
    auto peer = reinterpret_cast<GeneratedModifier::OffscreenCanvasRenderingContext2DPeerImpl*>(
        accessor_->ctor(&ARK_DEFAULT_WIDTH, &ARK_DEFAULT_HEIGHT, &OPT_DEFAULT_SETTINGS));
    ASSERT_NE(peer, nullptr);

    EXPECT_NEAR(peer->GetWidth(), DEFAULT_DOUBLE_VALUE, FLT_PRECISION);
    EXPECT_NEAR(peer->GetHeight(), DEFAULT_DOUBLE_VALUE, FLT_PRECISION);
    EXPECT_FALSE(peer->GetAnti());

    // opt testing
    peer = reinterpret_cast<GeneratedModifier::OffscreenCanvasRenderingContext2DPeerImpl*>(
        accessor_->ctor(&ARK_DEFAULT_WIDTH, &ARK_DEFAULT_HEIGHT, nullptr));
    ASSERT_NE(peer, nullptr);
    EXPECT_FALSE(peer->GetAnti());
}

/**
 * @tc.name: toDataURLTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(OffScreenCanvasRenderingContext2DAccessorTest, toDataURLTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->toDataURL, nullptr);

    for (auto& [actualType, expectedType] : optImageTypeTestPlan) {
        for (auto& [actualQuality, expectedQuality] : optImageQualityTestPlan) {
            auto expectedURL = expectedType + std::to_string(expectedQuality);
            std::string target;
            double targetQuality;
            EXPECT_CALL(*renderingModel_, ToDataURL(_, _))
                .WillOnce(DoAll(SaveArg<0>(&target), SaveArg<1>(&targetQuality), Return(expectedURL)));
            auto result = accessor_->toDataURL(peer_, &actualType, &actualQuality);

            auto actualURL = Converter::Convert<std::string>(result);
            EXPECT_EQ(target, expectedType);
            EXPECT_NEAR(targetQuality, expectedQuality, FLT_PRECISION);
            EXPECT_EQ(actualURL, expectedURL);
        }
    }

    // opt testing
    std::string target;
    double targetQuality;
    EXPECT_CALL(*renderingModel_, ToDataURL(_, _))
        .WillOnce(DoAll(SaveArg<0>(&target), SaveArg<1>(&targetQuality), Return(EMPTY_STRING)));
    accessor_->toDataURL(peer_, nullptr, nullptr);
    EXPECT_EQ(target, EMPTY_STRING);
    EXPECT_NEAR(targetQuality, DEFAULT_QUALITY, FLT_PRECISION);
}

/**
 * @tc.name: transferToImageBitmapTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(OffScreenCanvasRenderingContext2DAccessorTest, transferToImageBitmapTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->transferToImageBitmap, nullptr);
    auto peer = reinterpret_cast<GeneratedModifier::OffscreenCanvasRenderingContext2DPeerImpl*>(peer_);
    ASSERT_NE(peer, nullptr);

    int32_t counter = 0;
    peer->SetUnit(DEFAULT_UNIT);
    for (auto& actualW : numberTestPlan) {
        for (auto& actualH : numberTestPlan) {
            peer->SetWidth(actualW);
            peer->SetHeight(actualH);
            auto expectedW = static_cast<int32_t>(actualW);
            auto expectedH = static_cast<int32_t>(actualH);
            auto expectedPattern = AceType::MakeRefPtr<NG::OffscreenCanvasPattern>(actualW, actualH);
            peer->AddOffscreenCanvasPattern(expectedPattern);

            Ark_ImageBitmap bitmap = accessor_->transferToImageBitmap(peer_);
            ASSERT_NE(bitmap, nullptr);
            ASSERT_NE(bitmap->GetImageData(), nullptr);
            EXPECT_NEAR(bitmap->GetWidth(), actualW, FLT_PRECISION);
            EXPECT_NEAR(bitmap->GetHeight(), actualH, FLT_PRECISION);
            EXPECT_EQ(bitmap->GetImageData()->dirtyWidth, abs(expectedW));
            EXPECT_EQ(bitmap->GetImageData()->dirtyHeight, abs(expectedH));
            EXPECT_EQ(bitmap->GetUnit(), DEFAULT_UNIT);

            auto actualPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(peer->GetOffscreenPattern(counter));
            ASSERT_NE(actualPattern, nullptr);
            EXPECT_EQ(Referenced::RawPtr(actualPattern), Referenced::RawPtr(expectedPattern));
            EXPECT_EQ(actualPattern->GetWidth(), expectedW > 0 ? expectedW : 0);
            EXPECT_EQ(actualPattern->GetHeight(), expectedH > 0 ? expectedH : 0);
            counter++;
        }
    }
}
} // namespace OHOS::Ace::NG
