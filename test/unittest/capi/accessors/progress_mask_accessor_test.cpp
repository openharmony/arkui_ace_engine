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

#include "accessor_test_base.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "core/interfaces/native/implementation/progress_mask_peer.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class ProgressMaskAccessorTest : public AccessorTestCtorBase<GENERATED_ArkUIProgressMaskAccessor,
    &GENERATED_ArkUIAccessors::getProgressMaskAccessor, ProgressMaskPeer> {
public:
    void* CreatePeerInstance() override
    {
        const auto value = Converter::ArkValue<Ark_Number>(-1);
        const auto valueMax = Converter::ArkValue<Ark_Number>(-1);
        const auto color = Converter::ArkUnion<Ark_ResourceColor, Ark_String>("");
        return accessor_->construct(&value, &valueMax, &color);
    }

    ProgressMaskPeer* CreatePeerInstanceT()
    {
        return static_cast<ProgressMaskPeer*>(CreatePeerInstance());
    }
};

namespace {
constexpr auto DEFAULT_VALUE = 0.0f;
constexpr auto DEFAULT_MAX_VALUE = 100.0f;
constexpr auto DEFAULT_ENABLE_BREATHE = false;
constexpr auto DEFAULT_COLOR = Color(0x99182431);
} // namespace

/**
 * @tc.name: createDestroyPeerTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressMaskAccessorTest, createDestroyPeerTest, TestSize.Level1)
{
    auto peer1 = CreatePeerInstanceT();
    auto peer2 = CreatePeerInstanceT();
    auto peer3 = CreatePeerInstanceT();
    const auto property1 = peer1->GetProperty();
    const auto property2 = peer2->GetProperty();
    const auto property3 = peer3->GetProperty();
    ASSERT_NE(property1, nullptr);
    EXPECT_EQ(property1->RefCount(), 2);
    finalyzer_(peer1);
    EXPECT_EQ(property1->RefCount(), 1);
    EXPECT_EQ(property2->RefCount(), 2);
    EXPECT_EQ(property3->RefCount(), 2);
    finalyzer_(peer3);
    EXPECT_EQ(property1->RefCount(), 1);
    EXPECT_EQ(property2->RefCount(), 2);
    EXPECT_EQ(property3->RefCount(), 1);
    finalyzer_(peer2);
    EXPECT_EQ(property1->RefCount(), 1);
    EXPECT_EQ(property2->RefCount(), 1);
    EXPECT_EQ(property3->RefCount(), 1);
}

/**
 * @tc.name: ctorDefaultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressMaskAccessorTest, ctorDefaultTest, TestSize.Level1)
{
    ASSERT_NE(accessor_, nullptr);
    ASSERT_NE(peer_, nullptr);
    const auto property = peer_->GetProperty();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetValue(), DEFAULT_VALUE);
    EXPECT_EQ(property->GetMaxValue(), DEFAULT_MAX_VALUE);
    EXPECT_EQ(property->GetColor(), DEFAULT_COLOR);
    EXPECT_EQ(property->GetEnableBreathe(), DEFAULT_ENABLE_BREATHE);
}

/**
 * @tc.name: ctorValidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressMaskAccessorTest, ctorValidTest, TestSize.Level1)
{
    const std::vector<std::tuple<Ark_Number, float, Ark_Number, float, Ark_ResourceColor, Color>> validValues {
        {
            Converter::ArkValue<Ark_Number>(0), 0,
            Converter::ArkValue<Ark_Number>(100), 100,
            Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_RED), Color::RED
        },
        {
            Converter::ArkValue<Ark_Number>(20.5f), 20.5f,
            Converter::ArkValue<Ark_Number>(200.5f), 200.5f,
            Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0xff0000ff), Color(0xff0000ff)
        },
        {
            Converter::ArkValue<Ark_Number>(65535.0f), 65535.0f,
            Converter::ArkValue<Ark_Number>(32267.0f), 32267.0f,
            Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#123456"), Color::FromString("#123456")
        },
    };
    for (const auto& [inValue, outValue, inMax, outMax, inColor, outColor] : validValues) {
        auto peer = static_cast<ProgressMaskPeer*>(accessor_->construct(&inValue, &inMax, &inColor));
        const auto property = peer->GetProperty();
        ASSERT_NE(property, nullptr);
        EXPECT_EQ(property->GetValue(), outValue);
        EXPECT_EQ(property->GetMaxValue(), outMax);
        EXPECT_EQ(property->GetColor(), outColor);
        EXPECT_FALSE(property->GetEnableBreathe());
        finalyzer_(peer);
    }
}

/**
 * @tc.name: ctorInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressMaskAccessorTest, ctorInvalidTest, TestSize.Level1)
{
    const std::vector<std::tuple<Ark_Number, float, Ark_Number, float, Ark_ResourceColor, Color>> validValues {
        {
            Converter::ArkValue<Ark_Number>(-1), DEFAULT_VALUE,
            Converter::ArkValue<Ark_Number>(-1), DEFAULT_MAX_VALUE,
            Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(Ark_Color(-1)), DEFAULT_COLOR
        },
        {
            Converter::ArkValue<Ark_Number>(-100), DEFAULT_VALUE,
            Converter::ArkValue<Ark_Number>(10), 10,
            Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_RED), Color::RED
        },
        {
            Converter::ArkValue<Ark_Number>(10), 10,
            Converter::ArkValue<Ark_Number>(-200.5f), DEFAULT_MAX_VALUE,
            Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0xff0000ff), Color(0xff0000ff)
        },
        {
            Converter::ArkValue<Ark_Number>(200.5f), 200.5f,
            Converter::ArkValue<Ark_Number>(32267.0f), 32267.0f,
            Converter::ArkUnion<Ark_ResourceColor, Ark_String>(""), DEFAULT_COLOR
        },
    };
    for (const auto& [inValue, outValue, inMax, outMax, inColor, outColor] : validValues) {
        auto peer = static_cast<ProgressMaskPeer*>(accessor_->construct(&inValue, &inMax, &inColor));
        const auto property = peer->GetProperty();
        ASSERT_NE(property, nullptr);
        EXPECT_EQ(property->GetValue(), outValue);
        EXPECT_EQ(property->GetMaxValue(), outMax);
        EXPECT_EQ(property->GetColor(), outColor);
        EXPECT_FALSE(property->GetEnableBreathe());
        finalyzer_(peer);
    }
}

/**
 * @tc.name: updateProgressValidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressMaskAccessorTest, updateProgressValidTest, TestSize.Level1)
{
    const std::vector<std::tuple<Ark_Number, float>> validValues {
        {Converter::ArkValue<Ark_Number>(0), 0},
        {Converter::ArkValue<Ark_Number>(20.5f), 20.5f},
        {Converter::ArkValue<Ark_Number>(999.25f), 999.25f},
        {Converter::ArkValue<Ark_Number>(65535.0f), 65535.0f},
    };
    ASSERT_NE(accessor_, nullptr);
    ASSERT_NE(peer_, nullptr);
    for (const auto& [inValue, outValue] : validValues) {
        accessor_->updateProgress(peer_, &inValue);
        const auto property = peer_->GetProperty();
        ASSERT_NE(property, nullptr);
        EXPECT_EQ(property->GetValue(), outValue);
    }
}

/**
 * @tc.name: updateProgressInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressMaskAccessorTest, updateProgressInvalidTest, TestSize.Level1)
{
    const std::vector<Ark_Number> validValues {
        Converter::ArkValue<Ark_Number>(-1),
        Converter::ArkValue<Ark_Number>(-20.5f),
        Converter::ArkValue<Ark_Number>(-999.25f),
        Converter::ArkValue<Ark_Number>(-65535.0f),
    };
    ASSERT_NE(accessor_, nullptr);
    ASSERT_NE(peer_, nullptr);
    for (const auto& inValue : validValues) {
        accessor_->updateProgress(peer_, &inValue);
        const auto property = peer_->GetProperty();
        ASSERT_NE(property, nullptr);
        EXPECT_EQ(property->GetValue(), DEFAULT_VALUE);
    }
}

/**
 * @tc.name: updateColorValidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressMaskAccessorTest, updateColorValidTest, TestSize.Level1)
{
    const std::vector<std::tuple<Ark_ResourceColor, Color>> validValues {
        {Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_RED), Color::RED},
        {Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0xff0000ff), Color(0xff0000ff)},
        {Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#123456"), Color::FromString("#123456")},
    };
    ASSERT_NE(accessor_, nullptr);
    ASSERT_NE(peer_, nullptr);
    for (const auto& [inValue, outValue] : validValues) {
        accessor_->updateColor(peer_, &inValue);
        const auto property = peer_->GetProperty();
        ASSERT_NE(property, nullptr);
        EXPECT_EQ(property->GetColor(), outValue);
    }
}

/**
 * @tc.name: updateColorInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressMaskAccessorTest, updateColorInvalidTest, TestSize.Level1)
{
    const std::vector<Ark_ResourceColor> validValues {
        Converter::ArkUnion<Ark_ResourceColor, Ark_String>(""),
        Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(Ark_Color(-1)),
    };
    ASSERT_NE(accessor_, nullptr);
    ASSERT_NE(peer_, nullptr);
    for (const auto& inValue : validValues) {
        accessor_->updateColor(peer_, &inValue);
        const auto property = peer_->GetProperty();
        ASSERT_NE(property, nullptr);
        EXPECT_EQ(property->GetColor(), DEFAULT_COLOR);
    }
}

/**
 * @tc.name: enableBreathingAnimationValidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressMaskAccessorTest, enableBreathingAnimationValidTest, TestSize.Level1)
{
    const std::vector<std::tuple<Ark_Boolean, bool>> validValues {
        {Converter::ArkValue<Ark_Boolean>(false), false},
        {Converter::ArkValue<Ark_Boolean>(true), true},
        {Converter::ArkValue<Ark_Boolean>(false), false},
        {Converter::ArkValue<Ark_Boolean>(false), false},
        {Converter::ArkValue<Ark_Boolean>(true), true},
        {Converter::ArkValue<Ark_Boolean>(true), true},
    };
    ASSERT_NE(accessor_, nullptr);
    ASSERT_NE(peer_, nullptr);
    for (const auto& [inValue, outValue] : validValues) {
        accessor_->enableBreathingAnimation(peer_, inValue);
        const auto property = peer_->GetProperty();
        ASSERT_NE(property, nullptr);
        EXPECT_EQ(property->GetEnableBreathe(), outValue);
    }
}
} // namespace OHOS::Ace::NG
