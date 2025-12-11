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

#include <gmock/gmock.h>

#include "core/components_ng/pattern/canvas/canvas_paint_method.h"
#include "core/components_ng/pattern/canvas/canvas_rendering_context_2d_model_ng.h"
#include "core/interfaces/native/implementation/canvas_rendering_context2d_peer_impl.h"
#include "core/interfaces/native/implementation/rendering_context_settings_peer.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/mock/core/pattern/mock_canvas_pattern.h"

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
    ARK_IMAGE_ANALYZER_TYPE_TEXT,
    ARK_IMAGE_ANALYZER_TYPE_SUBJECT,
    static_cast<Ark_ImageAnalyzerType>(100),
    static_cast<Ark_ImageAnalyzerType>(-100)
};

const std::vector<std::pair<Opt_String, std::string>> OPT_IMAGE_TYPE_TEST_PLAN {
    { Converter::ArkValue<Opt_String>(IMAGE_PNG),  IMAGE_PNG},
    { Converter::ArkValue<Opt_String>(IMAGE_JPEG),  IMAGE_JPEG},
    { Converter::ArkValue<Opt_String>(IMAGE_WEBP),  IMAGE_WEBP},
    { Converter::ArkValue<Opt_String>(EMPTY_STRING),  IMAGE_PNG},
    { Converter::ArkValue<Opt_String>(Ark_Empty()),  IMAGE_PNG},
};
using QualityType = Opt_Number;
const std::vector<std::pair<QualityType, float>> OPT_IMAGE_QUALITY_TEST_PLAN {
    { Converter::ArkValue<QualityType>(-10.0f), IMAGE_QUALITY_DEFAULT },
    { Converter::ArkValue<QualityType>(-1.0f), IMAGE_QUALITY_DEFAULT },
    { Converter::ArkValue<QualityType>(-0.75f), IMAGE_QUALITY_DEFAULT },
    { Converter::ArkValue<QualityType>(0.0f), 0.0f },
    { Converter::ArkValue<QualityType>(0.5f), 0.5f },
    { Converter::ArkValue<QualityType>(0.92f), 0.92f },
    { Converter::ArkValue<QualityType>(1.0f), 1.0f },
    { Converter::ArkValue<QualityType>(1.25f), IMAGE_QUALITY_DEFAULT },
    { Converter::ArkValue<QualityType>(10.0f), IMAGE_QUALITY_DEFAULT },
    { Converter::ArkValue<QualityType>(Ark_Empty()), IMAGE_QUALITY_DEFAULT },
};
} // namespace

class CanvasRenderingContext2DAccessorTest
    : public AccessorTestBaseParent<GENERATED_ArkUICanvasRenderingContext2DAccessor,
    &GENERATED_ArkUIAccessors::getCanvasRenderingContext2DAccessor, CanvasRenderingContext2DPeer> {
public:
    void SetUp(void) override
    {
        ASSERT_NE(accessor_->construct, nullptr);
        peer_ = reinterpret_cast<CanvasRenderingContext2DPeer*>(accessor_->construct(&DEFAULT_SETTINGS, nullptr));
        ASSERT_NE(peer_, nullptr);

        AccessorTestBaseParent::SetUp();
        mockPattern_ = new MockCanvasPattern();
        mockPatternKeeper_ = AceType::Claim(mockPattern_);
        ASSERT_NE(mockPatternKeeper_, nullptr);
        auto peerImpl = reinterpret_cast<GeneratedModifier::CanvasRenderingContext2DPeerImpl*>(peer_);
        ASSERT_NE(peerImpl, nullptr);
        peerImpl->SetCanvasPattern(mockPatternKeeper_);
        ASSERT_NE(mockPattern_, nullptr);
    }

    void TearDown() override
    {
        AccessorTestBaseParent::TearDown();
        mockPatternKeeper_ = nullptr;
        mockPattern_ = nullptr;
    }

    MockCanvasPattern* mockPattern_ = nullptr;
    RefPtr<MockCanvasPattern> mockPatternKeeper_ = nullptr;
    Ark_VMContext vmContext_ = nullptr;
    Ark_AsyncWorkerPtr asyncWorker_ = nullptr;
};

/**
 * @tc.name: startImageAnalyzerTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderingContext2DAccessorTest, DISABLED_startImageAnalyzerTest, TestSize.Level1)
{
    // check config
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    std::vector<Ark_ImageAnalyzerType> src = ARK_IMAGE_TYPE_TEST_PLAN;
    Ark_ImageAnalyzerConfig arkConfig = {
        .types.array = reinterpret_cast<Ark_ImageAnalyzerType*>(src.data()),
        .types.length = static_cast<Ark_Int32>(src.size()),
    };

    ASSERT_NE(accessor_->startImageAnalyzer, nullptr);
    Callback_Opt_Array_String_Void cont{};
    accessor_->startImageAnalyzer(vmContext_, asyncWorker_, peer_, &arkConfig, &cont);

    ImageAnalyzerConfig* configPtr = reinterpret_cast<ImageAnalyzerConfig*>(holder->config);
    ASSERT_NE(configPtr, nullptr);
    ImageAnalyzerConfig config = *configPtr;
    auto length = IMAGE_TYPE_TEST_PLAN.size();
    EXPECT_EQ(config.types.size(), length);
    for (int i = 0; i < length; i++) {
        ImageAnalyzerType expected = IMAGE_TYPE_TEST_PLAN[i];
        EXPECT_TRUE(config.types.count(expected));
    }
    OnAnalyzedCallback onAnalyzed = holder->onAnalyzed;

    // check callback
    holder->SetUp();
    accessor_->startImageAnalyzer(vmContext_, asyncWorker_, peer_, &arkConfig, &cont);
    EXPECT_FALSE(holder->isCalled);

    EXPECT_EQ(holder->config, nullptr);
    EXPECT_EQ(holder->onAnalyzed, nullptr);
    EXPECT_NE(onAnalyzed, nullptr);

    holder->SetUp();
    (onAnalyzed.value())(ImageAnalyzerState::FINISHED);
    accessor_->startImageAnalyzer(vmContext_, asyncWorker_, peer_, &arkConfig, &cont);
    EXPECT_TRUE(holder->isCalled);
    EXPECT_NE(holder->config, nullptr);
    EXPECT_NE(holder->onAnalyzed, nullptr);

    holder->TearDown();
}

/**
 * @tc.name: stopImageAnalyzerTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderingContext2DAccessorTest, DISABLED_stopImageAnalyzerTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->stopImageAnalyzer, nullptr);

    accessor_->stopImageAnalyzer(peer_);
    accessor_->stopImageAnalyzer(peer_);
    accessor_->stopImageAnalyzer(peer_);

    EXPECT_EQ(holder->counter, 3);
    holder->TearDown();
}

/**
 * @tc.name: getHeightTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderingContext2DAccessorTest, DISABLED_getHeightTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->getHeight, nullptr);

    for (auto& [actual, expected] : DOUBLE_VALUE_TEST_PLAN) {
        holder->height = actual;
        auto result = Convert<double>(accessor_->getHeight(peer_));
        EXPECT_FLOAT_EQ(result, expected);
    }
    EXPECT_EQ(holder->counter, DOUBLE_VALUE_TEST_PLAN.size());
    holder->TearDown();
}

/**
 * @tc.name: getWidthTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderingContext2DAccessorTest, DISABLED_getWidthTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->getWidth, nullptr);

    for (auto& [actual, expected] : DOUBLE_VALUE_TEST_PLAN) {
        holder->width = actual;
        auto result = Convert<double>(accessor_->getWidth(peer_));
        EXPECT_FLOAT_EQ(result, expected);
    }
    EXPECT_EQ(holder->counter, DOUBLE_VALUE_TEST_PLAN.size());
    holder->TearDown();
}

/**
 * @tc.name: onAttachTest
 * @tc.desc: check add callbacks using onAttach
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderingContext2DAccessorTest, DISABLED_onAttachTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();
    ASSERT_TRUE(mockPatternKeeper_);
    ASSERT_NE(accessor_->onAttach, nullptr);
    struct CheckEvent {
        int32_t resourceId;
    };
    static size_t eventsSize = 10;
    using TestCallback = std::pair<VoidCallback, std::optional<CheckEvent>>;
    static std::vector<TestCallback> checkEvents;
    for (size_t i = 0; i < eventsSize; ++i) {
        auto callback = [](const Ark_Int32 resourceId) {
            checkEvents[resourceId].second = {
                .resourceId = resourceId,
            };
        };
        checkEvents.emplace_back(std::make_pair(ArkValue<VoidCallback>(callback, i), std::nullopt));
    }
    int arkCounter = 0;
    for (size_t i = 0; i < eventsSize; ++i) {
        accessor_->onAttach(peer_, &checkEvents[i].first);
        EXPECT_FALSE(checkEvents[i].second);
        for (size_t j = 0; j <= i; ++j) {
            mockPatternKeeper_->AttachRenderContext();
            ++arkCounter;
            EXPECT_TRUE(checkEvents[j].second);
            EXPECT_EQ(holder->counter, arkCounter);
            EXPECT_EQ(checkEvents[j].second->resourceId, j);
        }
    }
    holder->TearDown();
}

/**
 * @tc.name: onDetachTest
 * @tc.desc: check add callbacks using onDetach
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderingContext2DAccessorTest, DISABLED_onDetachTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();
    ASSERT_TRUE(mockPatternKeeper_);
    ASSERT_NE(accessor_->onAttach, nullptr);
    struct CheckEvent {
        int32_t resourceId;
    };
    static size_t eventsSize = 10;
    using TestCallback = std::pair<VoidCallback, std::optional<CheckEvent>>;
    static std::vector<TestCallback> checkEvents;
    for (size_t i = 0; i < eventsSize; ++i) {
        auto callback = [](const Ark_Int32 resourceId) {
            checkEvents[resourceId].second = {
                .resourceId = resourceId,
            };
        };
        checkEvents.emplace_back(std::make_pair(ArkValue<VoidCallback>(callback, i), std::nullopt));
    }
    int arkCounter = 0;
    for (size_t i = 0; i < eventsSize; ++i) {
        accessor_->onDetach(peer_, &checkEvents[i].first);
        EXPECT_FALSE(checkEvents[i].second);
        for (size_t j = 0; j <= i; ++j) {
            mockPatternKeeper_->DetachRenderContext();
            ++arkCounter;
            EXPECT_TRUE(checkEvents[j].second);
            EXPECT_EQ(holder->counter, arkCounter);
            EXPECT_EQ(checkEvents[j].second->resourceId, j);
        }
    }
    holder->TearDown();
}

/**
 * @tc.name: offAttachTest
 * @tc.desc: check remove single callback using offAttach
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderingContext2DAccessorTest, DISABLED_offAttachTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();
    ASSERT_TRUE(mockPatternKeeper_);
    ASSERT_NE(accessor_->onAttach, nullptr);
    struct CheckEvent {
        int32_t resourceId;
    };
    static size_t eventsSize = 10;
    using TestCallback = std::pair<Opt_VoidCallback, std::optional<CheckEvent>>;
    static std::vector<TestCallback> checkEvents;
    for (size_t i = 0; i < eventsSize; ++i) {
        auto callback = [](const Ark_Int32 resourceId) {
            checkEvents[resourceId].second = {
                .resourceId = resourceId,
            };
        };
        auto arkCallback = ArkValue<VoidCallback>(callback, i);
        checkEvents.emplace_back(std::make_pair(ArkValue<Opt_VoidCallback>(arkCallback), std::nullopt));
        accessor_->onAttach(peer_, &arkCallback);
    }
    int arkCounter = 0;
    for (size_t i = 0; i < eventsSize; ++i) {
        accessor_->offAttach(peer_, &checkEvents[i].first);
        checkEvents[i].second = std::nullopt;
        for (size_t j = 0; j < eventsSize; ++j) {
            mockPatternKeeper_->AttachRenderContext();
            ++arkCounter;
            if (j > i) {
                EXPECT_TRUE(checkEvents[j].second);
                EXPECT_EQ(checkEvents[j].second->resourceId, j);
            } else {
                EXPECT_FALSE(checkEvents[j].second);
            }
            EXPECT_EQ(holder->counter, arkCounter);
        }
    }
    holder->TearDown();
}

/**
 * @tc.name: offAttachTestAll
 * @tc.desc: check remove all callbacks using offAttachTest
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderingContext2DAccessorTest, DISABLED_offAttachTestAll, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();
    ASSERT_TRUE(mockPatternKeeper_);
    ASSERT_NE(accessor_->onAttach, nullptr);
    struct CheckEvent {
        int32_t resourceId;
    };
    static size_t eventsSize = 10;
    using TestCallback = std::pair<Opt_VoidCallback, std::optional<CheckEvent>>;
    static std::vector<TestCallback> checkEvents;
    for (size_t i = 0; i < eventsSize; ++i) {
        auto callback = [](const Ark_Int32 resourceId) {
            checkEvents[resourceId].second = {
                .resourceId = resourceId,
            };
        };
        auto arkCallback = ArkValue<VoidCallback>(callback, i);
        checkEvents.emplace_back(std::make_pair(ArkValue<Opt_VoidCallback>(arkCallback), std::nullopt));
        accessor_->onAttach(peer_, &arkCallback);
    }
    auto optCallback = ArkValue<Opt_VoidCallback>();
    accessor_->offAttach(peer_, &optCallback);
    mockPatternKeeper_->AttachRenderContext();
    for (size_t j = 0; j < eventsSize; ++j) {
        EXPECT_FALSE(checkEvents[j].second);
    }
    EXPECT_EQ(holder->counter, 1);
    holder->TearDown();
}

/**
 * @tc.name: offDetachTest
 * @tc.desc: check remove single callback using offDetach
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderingContext2DAccessorTest, DISABLED_offDetachTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();
    ASSERT_TRUE(mockPatternKeeper_);
    ASSERT_NE(accessor_, nullptr);
    ASSERT_NE(accessor_->onAttach, nullptr);
    struct CheckEvent {
        int32_t resourceId;
    };
    static size_t eventsSize = 10;
    using TestCallback = std::pair<Opt_VoidCallback, std::optional<CheckEvent>>;
    static std::vector<TestCallback> checkEvents;
    for (size_t i = 0; i < eventsSize; ++i) {
        auto callback = [](const Ark_Int32 resourceId) {
            checkEvents[resourceId].second = {
                .resourceId = resourceId,
            };
        };
        auto arkCallback = ArkValue<VoidCallback>(callback, i);
        checkEvents.emplace_back(std::make_pair(ArkValue<Opt_VoidCallback>(arkCallback), std::nullopt));
        accessor_->onDetach(peer_, &arkCallback);
    }
    int arkCounter = 0;
    for (size_t i = 0; i < eventsSize; ++i) {
        accessor_->offDetach(peer_, &checkEvents[i].first);
        checkEvents[i].second = std::nullopt;
        for (size_t j = 0; j < eventsSize; ++j) {
            mockPatternKeeper_->DetachRenderContext();
            ++arkCounter;
            if (j > i) {
                EXPECT_TRUE(checkEvents[j].second);
                EXPECT_EQ(checkEvents[j].second->resourceId, j);
            } else {
                EXPECT_FALSE(checkEvents[j].second);
            }
            EXPECT_EQ(holder->counter, arkCounter);
        }
    }
    holder->TearDown();
}

/**
 * @tc.name: offDetachTestAll
 * @tc.desc: check remove all callbacks using offDetach
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderingContext2DAccessorTest, DISABLED_offDetachTestAll, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();
    ASSERT_TRUE(mockPatternKeeper_);
    ASSERT_NE(accessor_->onAttach, nullptr);
    struct CheckEvent {
        int32_t resourceId;
    };
    static size_t eventsSize = 10;
    using TestCallback = std::pair<Opt_VoidCallback, std::optional<CheckEvent>>;
    static std::vector<TestCallback> checkEvents;
    for (size_t i = 0; i < eventsSize; ++i) {
        auto callback = [](const Ark_Int32 resourceId) {
            checkEvents[resourceId].second = {
                .resourceId = resourceId,
            };
        };
        auto arkCallback = ArkValue<VoidCallback>(callback, i);
        checkEvents.emplace_back(std::make_pair(ArkValue<Opt_VoidCallback>(arkCallback), std::nullopt));
        accessor_->onDetach(peer_, &arkCallback);
    }
    auto optCallback = ArkValue<Opt_VoidCallback>();
    accessor_->offDetach(peer_, &optCallback);
    mockPatternKeeper_->DetachRenderContext();
    for (size_t j = 0; j < eventsSize; ++j) {
        EXPECT_FALSE(checkEvents[j].second);
    }
    EXPECT_EQ(holder->counter, 1);
    holder->TearDown();
}

/**
 * @tc.name: toDataURLTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderingContext2DAccessorTest, DISABLED_toDataURLTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->toDataURL, nullptr);

    for (auto& [actualType, expectedType] : OPT_IMAGE_TYPE_TEST_PLAN) {
        for (auto& [actualQuality, expectedQuality] : OPT_IMAGE_QUALITY_TEST_PLAN) {
            holder->SetUp();
            EXPECT_FALSE(holder->type.has_value());
            EXPECT_FALSE(holder->quality.has_value());
            accessor_->toDataURL(peer_, &actualType, &actualQuality);

            EXPECT_EQ(holder->type.value(), expectedType);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->quality.value(), expectedQuality));
            EXPECT_TRUE(holder->isCalled);
            holder->TearDown();
        }
    }
}
} // namespace OHOS::Ace::NG
