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
#include "core/interfaces/native/implementation/rendering_context_settings_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/unittest/capi/accessors/accessor_test_fixtures.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
const auto ANTIALIAS_DEFAULT_VALUE = false;
} // namespace

class RenderingContextSettingsAccessorTest
    : public AccessorTestCtorBase<GENERATED_ArkUIRenderingContextSettingsAccessor,
        &GENERATED_ArkUIAccessors::getRenderingContextSettingsAccessor, RenderingContextSettingsPeer> {
public:
    RenderingContextSettingsPeer* CreatePeerInstanceT(const Opt_Boolean* value)
    {
        return accessor_->construct(value);
    }
    void* CreatePeerInstance() override
    {
        auto optValue = Converter::ArkValue<Opt_Boolean>(ANTIALIAS_DEFAULT_VALUE);
        return CreatePeerInstanceT(&optValue);
    }
};

/**
 * @tc.name: ctorRenderingContextSettingsPeerTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderingContextSettingsAccessorTest, ctorRenderingContextSettingsPeerTest, TestSize.Level1)
{
    for (const auto& [input, value, expected] : AccessorTestFixtures::testFixtureBooleanValues) {
        auto optValue = Converter::ArkValue<Opt_Boolean>(value);
        auto peer = CreatePeerInstanceT(&optValue);
        auto result = peer->antialias;
        finalyzer_(peer);
        ASSERT_NE(result, std::nullopt);
        EXPECT_EQ(result.value(), expected) <<
            "Input value is: " << input << ", method: GetRepeat";
    }

    auto optValue = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    auto peer = CreatePeerInstanceT(&optValue);
    auto result = peer->antialias;
    finalyzer_(peer);
    EXPECT_EQ(result, std::nullopt) <<
        "Input value is: empty, method: GetRepeat";

    peer = CreatePeerInstanceT(nullptr);
    result = peer->antialias;
    finalyzer_(peer);
    EXPECT_EQ(result, std::nullopt) <<
        "Input value is: nullptr, method: GetRepeat";
}

/**
 * @tc.name: getAntialiasTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderingContextSettingsAccessorTest, getAntialiasTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getAntialias, nullptr);
    for (const auto& [input, expected, value] : AccessorTestFixtures::testFixtureBooleanValues) {
        peer_->antialias = value;
        auto result = Converter::GetOpt(accessor_->getAntialias(peer_));
        EXPECT_EQ(result, expected) <<
            "Input value is: " << input << ", method: GetRepeat";
    }
}

/**
 * @tc.name: setAntialiasTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderingContextSettingsAccessorTest, setAntialiasTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setAntialias, nullptr);
    for (const auto& [input, value, expected] : AccessorTestFixtures::testFixtureBooleanValues) {
        auto inputValue = Converter::ArkValue<Opt_Boolean>(value);
        accessor_->setAntialias(peer_, &inputValue);
        auto result = peer_->antialias;
        ASSERT_NE(result, std::nullopt);
        EXPECT_EQ(result.value(), expected) <<
            "Input value is: " << input << ", method: SetRepeat";
    }
}
}
