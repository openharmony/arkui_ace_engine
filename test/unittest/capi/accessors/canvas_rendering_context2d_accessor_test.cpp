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

#include "test/mock/core/pattern/mock_canvas_pattern.h"
#include <gmock/gmock.h>

#include "core/components_ng/pattern/canvas/canvas_paint_method.h"
#include "core/components_ng/pattern/canvas/canvas_rendering_context_2d_model_ng.h"
#include "core/interfaces/native/implementation/canvas_rendering_context2d_peer_impl.h"
#include "core/interfaces/native/implementation/rendering_context_settings_peer.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "accessor_test_base.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
const Opt_RenderingContextSettings DEFAULT_SETTINGS =
    ArkValue<Opt_RenderingContextSettings>(RenderingContextSettingsPeer::Create(false));

class MockCanvasPattern : public CanvasPattern {
public:
    MockCanvasPattern() = default;
    ~MockCanvasPattern() override = default;
};

const std::string IMAGE_PNG = "image/png";
const std::string IMAGE_JPEG = "image/jpeg";
const std::string IMAGE_WEBP = "image/webp";
const std::string EMPTY_STRING = "";
const auto IMAGE_QUALITY_DEFAULT = 0.92f;
const double FLT_PRECISION = 0.001;
const auto EXPECTED_NUMBER_OF_CALLS = 3;
const double DENSITY_1_25 = 1.25;
const double DENSITY_2_50 = 2.50;
const double DEFAULT_DENSITY = 1.0;

// test plans
typedef std::pair<double, double> DoubleValueTestStep;
const std::vector<DoubleValueTestStep> DOUBLE_VALUE_TEST_PLAN = {
    { 0, 0 },
    { 1.25, 1.25 },
    { 100.15, 100.15 },
    { -2.35, -2.35 },
};

const std::vector<ImageAnalyzerType> IMAGE_TYPE_TEST_PLAN {
    ImageAnalyzerType::TEXT,
    ImageAnalyzerType::SUBJECT,
};

const std::vector<Ark_ImageAnalyzerType> ARK_IMAGE_TYPE_TEST_PLAN {
    Ark_ImageAnalyzerType::ARK_IMAGE_ANALYZER_TYPE_TEXT,
    Ark_ImageAnalyzerType::ARK_IMAGE_ANALYZER_TYPE_SUBJECT,
    static_cast<Ark_ImageAnalyzerType>(100),
    static_cast<Ark_ImageAnalyzerType>(-100)
};

const std::vector<std::pair<Opt_String, std::string>> OPT_IMAGE_TYPE_TEST_PLAN {
    { Converter::ArkValue<Opt_String>(IMAGE_PNG),  IMAGE_PNG},
    { Converter::ArkValue<Opt_String>(IMAGE_JPEG),  IMAGE_JPEG},
    { Converter::ArkValue<Opt_String>(IMAGE_WEBP),  IMAGE_WEBP},
    { Converter::ArkValue<Opt_String>(EMPTY_STRING),  EMPTY_STRING},
    { Converter::ArkValue<Opt_String>(Ark_Empty()),  EMPTY_STRING},
};
const std::vector<std::pair<Opt_Float32, float>> OPT_IMAGE_QUALITY_TEST_PLAN {
    { Converter::ArkValue<Opt_Float32>(-10.0f), -10.0f },
    { Converter::ArkValue<Opt_Float32>(0.0f), 0.0f },
    { Converter::ArkValue<Opt_Float32>(0.5f), 0.5f },
    { Converter::ArkValue<Opt_Float32>(1.0f), 1.0f },
    { Converter::ArkValue<Opt_Float32>(10.0f), 10.0f },
    { Converter::ArkValue<Opt_Float32>(Ark_Empty()), IMAGE_QUALITY_DEFAULT },
};

class MockCanvasRenderingContext2DModel : public NG::CanvasRenderingContext2DModelNG {
public:
    MockCanvasRenderingContext2DModel() = default;
    ~MockCanvasRenderingContext2DModel() override = default;

    MOCK_METHOD(std::string, ToDataURL, (const std::string&, double), (override));
    MOCK_METHOD(void, StartImageAnalyzer, (void*, OnAnalyzedCallback&), (override));
    MOCK_METHOD(void, StopImageAnalyzer, (), (override));
    MOCK_METHOD(void, GetHeight, (double&), (override));
    MOCK_METHOD(void, GetWidth, (double&), (override));

    MOCK_METHOD(void, SetOnAttach, (std::function<void()>&&), (override));
    MOCK_METHOD(void, SetOnDetach, (std::function<void()>&&), (override));
};
} // namespace

class CanvasRenderingContext2DAccessorTest
    : public AccessorTestCtorBase<GENERATED_ArkUICanvasRenderingContext2DAccessor,
    &GENERATED_ArkUIAccessors::getCanvasRenderingContext2DAccessor, CanvasRenderingContext2DPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestCtorBase::SetUp();
        renderingModel_ = AceType::MakeRefPtr<NiceMock<MockCanvasRenderingContext2DModel>>();
        reinterpret_cast<GeneratedModifier::CanvasRenderingContext2DPeerImpl*>(peer_)->SetRenderingContext2DModel(
            renderingModel_);
    }

    void TearDown() override
    {
        AccessorTestCtorBase::TearDown();
        auto pipelineContext =
            AceType::DynamicCast<NG::MockPipelineContext>(NG::MockPipelineContext::GetCurrentContext());
        pipelineContext->SetDensity(DEFAULT_DENSITY);
    }

    void* CreatePeerInstance() override
    {
        return accessor_->ctor(&DEFAULT_SETTINGS);
    }

    void ChangeDensity(const double density)
    {
        auto pipelineContext =
            AceType::DynamicCast<NG::MockPipelineContext>(NG::MockPipelineContext::GetCurrentContext());
        pipelineContext->SetDensity(density);
        // Re-create peer for density to have effect
        finalyzer_(peer_);
        peer_ = static_cast<CanvasRenderingContext2DPeer*>(CreatePeerInstance());
        reinterpret_cast<GeneratedModifier::CanvasRendererPeerImpl*>(peer_)->SetRenderingContext2DModel(
            renderingModel_);
    }

    RefPtr<MockCanvasRenderingContext2DModel> renderingModel_ = nullptr;
    Ark_VMContext vmContext_ = nullptr;
    Ark_AsyncWorkerPtr asyncWorker_ = nullptr;
};

/**
 * @tc.name: startImageAnalyzerTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderingContext2DAccessorTest, startImageAnalyzerTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->startImageAnalyzer, nullptr);

    std::vector<Ark_ImageAnalyzerType> src = ARK_IMAGE_TYPE_TEST_PLAN;
    Ark_ImageAnalyzerConfig arkConfig = {
        .types.array = reinterpret_cast<Ark_ImageAnalyzerType*>(src.data()),
        .types.length = static_cast<Ark_Int32>(src.size()),
    };
    Callback_Opt_Array_String_Void cont {};

    void* target;
    Ace::OnAnalyzedCallback onAnalyzed;
    EXPECT_CALL(*renderingModel_, StartImageAnalyzer(_, _))
        .WillOnce(DoAll(SaveArg<0>(&target), SaveArg<1>(&onAnalyzed)));
    accessor_->startImageAnalyzer(vmContext_, asyncWorker_, peer_, &arkConfig, &cont);

    ImageAnalyzerConfig* configPtr = reinterpret_cast<ImageAnalyzerConfig*>(target);
    ASSERT_NE(configPtr, nullptr);
    ImageAnalyzerConfig config = *configPtr;
    auto length = IMAGE_TYPE_TEST_PLAN.size();
    EXPECT_EQ(config.types.size(), length);
    for (int i = 0; i < length; i++) {
        ImageAnalyzerType expected = IMAGE_TYPE_TEST_PLAN[i];
        EXPECT_TRUE(config.types.count(expected));
    }

    EXPECT_CALL(*renderingModel_, StartImageAnalyzer(_, _)).Times(0);
    accessor_->startImageAnalyzer(vmContext_, asyncWorker_, peer_, &arkConfig, &cont);

    (onAnalyzed.value())(ImageAnalyzerState::FINISHED);
    EXPECT_CALL(*renderingModel_, StartImageAnalyzer(_, _)).Times(1);
    accessor_->startImageAnalyzer(vmContext_, asyncWorker_, peer_, &arkConfig, &cont);
}

/**
 * @tc.name: stopImageAnalyzerTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderingContext2DAccessorTest, stopImageAnalyzerTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->stopImageAnalyzer, nullptr);

    EXPECT_CALL(*renderingModel_, StopImageAnalyzer()).Times(EXPECTED_NUMBER_OF_CALLS);
    accessor_->stopImageAnalyzer(peer_);
    accessor_->stopImageAnalyzer(peer_);
    accessor_->stopImageAnalyzer(peer_);
}

/**
 * @tc.name: getHeightTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderingContext2DAccessorTest, getHeightTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getHeight, nullptr);

    for (auto& [actual, expected] : DOUBLE_VALUE_TEST_PLAN) {
        EXPECT_CALL(*renderingModel_, GetHeight(_)).WillOnce(DoAll(SetArgReferee<0>(actual)));
        auto result = Convert<double>(accessor_->getHeight(peer_));
        EXPECT_NEAR(result, expected, FLT_PRECISION);
    }
    // with density
    double density = DENSITY_1_25;
    ChangeDensity(density);
    for (auto& [actual, expected] : DOUBLE_VALUE_TEST_PLAN) {
        EXPECT_CALL(*renderingModel_, GetHeight(_)).WillOnce(DoAll(SetArgReferee<0>(actual)));
        auto result = Convert<double>(accessor_->getHeight(peer_));
        EXPECT_NEAR(result, expected / density, FLT_PRECISION);
    }
}

/**
 * @tc.name: getWidthTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderingContext2DAccessorTest, getWidthTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getWidth, nullptr);
    for (auto& [actual, expected] : DOUBLE_VALUE_TEST_PLAN) {
        EXPECT_CALL(*renderingModel_, GetWidth(_)).WillOnce(DoAll(SetArgReferee<0>(actual)));
        auto result = Convert<double>(accessor_->getWidth(peer_));
        EXPECT_NEAR(result, expected, FLT_PRECISION);
    }
    // with density
    double density = DENSITY_2_50;
    ChangeDensity(density);
    for (auto& [actual, expected] : DOUBLE_VALUE_TEST_PLAN) {
        EXPECT_CALL(*renderingModel_, GetWidth(_)).WillOnce(DoAll(SetArgReferee<0>(actual)));
        auto result = Convert<double>(accessor_->getWidth(peer_));
        EXPECT_NEAR(result, expected / density, FLT_PRECISION);
    }
}

/**
 * @tc.name: onOnAttachTest
 * @tc.desc: check add callbacks using onOnAttach
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderingContext2DAccessorTest, onOnAttachTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->onOnAttach, nullptr);

    struct CheckEvent {
        int32_t resourceId;
    };
    auto onAttach = [this]() {
        CHECK_NULL_VOID(this->peer_);
        reinterpret_cast<GeneratedModifier::CanvasRenderingContext2DPeerImpl*>(this->peer_)->OnAttachToCanvas();
    };
    static size_t eventsSize = 10;
    static size_t counter = 0;
    int arkCounter = 0;
    using TestCallback = std::pair<Callback_Void, std::optional<CheckEvent>>;
    static std::vector<TestCallback> checkEvents;
    for (size_t i = 0; i < eventsSize; ++i) {
        auto callback = [](const Ark_Int32 resourceId) {
            checkEvents[resourceId].second = {
                .resourceId = resourceId,
            };
            counter++;
        };
        checkEvents.emplace_back(std::make_pair(ArkValue<Callback_Void>(callback, i), std::nullopt));
    }
    for (size_t i = 0; i < eventsSize; ++i) {
        arkCounter++;
        accessor_->onOnAttach(vmContext_, peer_, &checkEvents[i].first);
        EXPECT_FALSE(checkEvents[i].second);

        std::function<void()> target;
        EXPECT_CALL(*renderingModel_, SetOnAttach(_)).WillOnce(DoAll(SaveArg<0>(&target)));
        renderingModel_->SetOnAttach(onAttach);
        counter = 0;
        target();
        EXPECT_EQ(counter, arkCounter);
        ASSERT_TRUE(checkEvents[i].second);
        EXPECT_EQ(checkEvents[i].second->resourceId, i);
    }
}

/**
 * @tc.name: onOnDetachTest
 * @tc.desc: check add callbacks using onOnDetach
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderingContext2DAccessorTest, onOnDetachTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->onOnDetach, nullptr);

    struct CheckEvent {
        int32_t resourceId;
    };
    auto onDetach = [this]() {
        CHECK_NULL_VOID(this->peer_);
        reinterpret_cast<GeneratedModifier::CanvasRenderingContext2DPeerImpl*>(this->peer_)->OnDetachFromCanvas();
    };
    static size_t eventsSize = 10;
    static size_t counter = 0;
    int arkCounter = 0;
    using TestCallback = std::pair<Callback_Void, std::optional<CheckEvent>>;
    static std::vector<TestCallback> checkEvents;
    for (size_t i = 0; i < eventsSize; ++i) {
        auto callback = [](const Ark_Int32 resourceId) {
            checkEvents[resourceId].second = {
                .resourceId = resourceId,
            };
            counter++;
        };
        checkEvents.emplace_back(std::make_pair(ArkValue<Callback_Void>(callback, i), std::nullopt));
    }
    for (size_t i = 0; i < eventsSize; ++i) {
        arkCounter++;
        accessor_->onOnDetach(vmContext_, peer_, &checkEvents[i].first);
        EXPECT_FALSE(checkEvents[i].second);

        std::function<void()> target;
        EXPECT_CALL(*renderingModel_, SetOnDetach(_)).WillOnce(DoAll(SaveArg<0>(&target)));
        renderingModel_->SetOnDetach(onDetach);
        counter = 0;
        target();
        EXPECT_EQ(counter, arkCounter);
        ASSERT_TRUE(checkEvents[i].second);
        EXPECT_EQ(checkEvents[i].second->resourceId, i);
    }
}

/**
 * @tc.name: offOnAttachTest
 * @tc.desc: check remove single callback using offOnAttach
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderingContext2DAccessorTest, offOnAttachTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->onOnAttach, nullptr);
    ASSERT_NE(accessor_->offOnAttach, nullptr);

    struct CheckEvent {
        int32_t resourceId;
    };
    auto onAttach = [this]() {
        CHECK_NULL_VOID(this->peer_);
        reinterpret_cast<GeneratedModifier::CanvasRenderingContext2DPeerImpl*>(this->peer_)->OnAttachToCanvas();
    };
    static size_t eventsSize = 10;
    static size_t counter = 0;
    int arkCounter = 0;
    using TestCallback = std::pair<Opt_Callback_Void, std::optional<CheckEvent>>;
    static std::vector<TestCallback> checkEvents;
    for (size_t i = 0; i < eventsSize; ++i) {
        auto callback = [](const Ark_Int32 resourceId) {
            checkEvents[resourceId].second = {
                .resourceId = resourceId,
            };
            counter++;
        };
        auto arkCallback = ArkValue<Callback_Void>(callback, i);
        checkEvents.emplace_back(std::make_pair(ArkValue<Opt_Callback_Void>(arkCallback), std::nullopt));
        accessor_->onOnAttach(vmContext_, peer_, &arkCallback);
    }
    for (size_t i = 0; i < eventsSize; ++i) {
        ++arkCounter;
        accessor_->offOnAttach(vmContext_, peer_, &checkEvents[i].first);
        checkEvents[i].second = std::nullopt;
        for (size_t j = 0; j < eventsSize; ++j) {
            std::function<void()> target;
            EXPECT_CALL(*renderingModel_, SetOnAttach(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            renderingModel_->SetOnAttach(onAttach);
            counter = 0;
            target();
            if (j > i) {
                ASSERT_TRUE(checkEvents[j].second);
                EXPECT_EQ(checkEvents[j].second->resourceId, j);
            } else {
                EXPECT_FALSE(checkEvents[j].second);
            }
            EXPECT_EQ(counter, eventsSize - arkCounter);
        }
    }
}

/**
 * @tc.name: offOnAttachTestAll
 * @tc.desc: check remove all callbacks using offOnAttachTest
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderingContext2DAccessorTest, offOnAttachTestAll, TestSize.Level1)
{
    ASSERT_NE(accessor_->onOnAttach, nullptr);
    ASSERT_NE(accessor_->offOnAttach, nullptr);

    struct CheckEvent {
        int32_t resourceId;
    };
    auto onAttach = [this]() {
        CHECK_NULL_VOID(this->peer_);
        reinterpret_cast<GeneratedModifier::CanvasRenderingContext2DPeerImpl*>(this->peer_)->OnAttachToCanvas();
    };
    static size_t eventsSize = 10;
    using TestCallback = std::pair<Opt_Callback_Void, std::optional<CheckEvent>>;
    static std::vector<TestCallback> checkEvents;
    for (size_t i = 0; i < eventsSize; ++i) {
        auto callback = [](const Ark_Int32 resourceId) {
            checkEvents[resourceId].second = {
                .resourceId = resourceId,
            };
        };
        auto arkCallback = ArkValue<Callback_Void>(callback, i);
        checkEvents.emplace_back(std::make_pair(ArkValue<Opt_Callback_Void>(arkCallback), std::nullopt));
        accessor_->onOnAttach(vmContext_, peer_, &arkCallback);
    }
    auto optCallback = ArkValue<Opt_Callback_Void>();
    accessor_->offOnAttach(vmContext_, peer_, &optCallback);

    std::function<void()> target;
    EXPECT_CALL(*renderingModel_, SetOnAttach(_)).WillOnce(DoAll(SaveArg<0>(&target)));
    renderingModel_->SetOnAttach(onAttach);
    target();
    for (size_t j = 0; j < eventsSize; ++j) {
        EXPECT_FALSE(checkEvents[j].second);
    }
}

/**
 * @tc.name: offOnDetachTest
 * @tc.desc: check remove single callback using offOnDetach
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderingContext2DAccessorTest, offOnDetachTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->onOnAttach, nullptr);
    ASSERT_NE(accessor_->offOnAttach, nullptr);

    struct CheckEvent {
        int32_t resourceId;
    };
    auto onDetach = [this]() {
        CHECK_NULL_VOID(this->peer_);
        reinterpret_cast<GeneratedModifier::CanvasRenderingContext2DPeerImpl*>(this->peer_)->OnDetachFromCanvas();
    };
    static size_t eventsSize = 10;
    static size_t counter = 0;
    int arkCounter = 0;
    using TestCallback = std::pair<Opt_Callback_Void, std::optional<CheckEvent>>;
    static std::vector<TestCallback> checkEvents;
    for (size_t i = 0; i < eventsSize; ++i) {
        auto callback = [](const Ark_Int32 resourceId) {
            checkEvents[resourceId].second = {
                .resourceId = resourceId,
            };
            counter++;
        };
        auto arkCallback = ArkValue<Callback_Void>(callback, i);
        checkEvents.emplace_back(std::make_pair(ArkValue<Opt_Callback_Void>(arkCallback), std::nullopt));
        accessor_->onOnDetach(vmContext_, peer_, &arkCallback);
    }
    for (size_t i = 0; i < eventsSize; ++i) {
        arkCounter++;
        accessor_->offOnDetach(vmContext_, peer_, &checkEvents[i].first);
        checkEvents[i].second = std::nullopt;
        for (size_t j = 0; j < eventsSize; ++j) {
            std::function<void()> target;
            EXPECT_CALL(*renderingModel_, SetOnDetach(_)).WillOnce(DoAll(SaveArg<0>(&target)));
            renderingModel_->SetOnDetach(onDetach);
            counter = 0;
            target();
            if (j > i) {
                ASSERT_TRUE(checkEvents[j].second);
                EXPECT_EQ(checkEvents[j].second->resourceId, j);
            } else {
                EXPECT_FALSE(checkEvents[j].second);
            }
            EXPECT_EQ(counter, eventsSize - arkCounter);
        }
    }
}

/**
 * @tc.name: offOnDetachTestAll
 * @tc.desc: check remove all callbacks using offOnDetach
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderingContext2DAccessorTest, offOnDetachTestAll, TestSize.Level1)
{
    ASSERT_NE(accessor_->onOnDetach, nullptr);
    ASSERT_NE(accessor_->offOnDetach, nullptr);

    struct CheckEvent {
        int32_t resourceId;
    };
    auto onDetach = [this]() {
        CHECK_NULL_VOID(this->peer_);
        reinterpret_cast<GeneratedModifier::CanvasRenderingContext2DPeerImpl*>(this->peer_)->OnDetachFromCanvas();
    };
    static size_t eventsSize = 10;
    using TestCallback = std::pair<Opt_Callback_Void, std::optional<CheckEvent>>;
    static std::vector<TestCallback> checkEvents;
    for (size_t i = 0; i < eventsSize; ++i) {
        auto callback = [](const Ark_Int32 resourceId) {
            checkEvents[resourceId].second = {
                .resourceId = resourceId,
            };
        };
        auto arkCallback = ArkValue<Callback_Void>(callback, i);
        checkEvents.emplace_back(std::make_pair(ArkValue<Opt_Callback_Void>(arkCallback), std::nullopt));
        accessor_->onOnDetach(vmContext_, peer_, &arkCallback);
    }
    auto optCallback = ArkValue<Opt_Callback_Void>();
    accessor_->offOnDetach(vmContext_, peer_, &optCallback);

    std::function<void()> target;
    EXPECT_CALL(*renderingModel_, SetOnDetach(_)).WillOnce(DoAll(SaveArg<0>(&target)));
    renderingModel_->SetOnDetach(onDetach);
    target();
    for (size_t j = 0; j < eventsSize; ++j) {
        EXPECT_FALSE(checkEvents[j].second);
    }
}

/**
 * @tc.name: toDataURLTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderingContext2DAccessorTest, toDataURLTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->toDataURL, nullptr);

    for (auto& [actualType, expectedType] : OPT_IMAGE_TYPE_TEST_PLAN) {
        for (auto& [actualQuality, expectedQuality] : OPT_IMAGE_QUALITY_TEST_PLAN) {
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
}
} // namespace OHOS::Ace::NG
