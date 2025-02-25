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
const auto ANTIALIAS_DEFAULT_VALUE = Converter::ArkValue<Ark_Boolean>(false);
} // namespace

class RenderingContextSettingsAccessorTest
    : public AccessorTestBaseParent<GENERATED_ArkUIRenderingContextSettingsAccessor,
        &GENERATED_ArkUIAccessors::getRenderingContextSettingsAccessor, RenderingContextSettingsPeer> {
public:
    void SetUp(void) override
    {
        ASSERT_NE(accessor_->ctor, nullptr);
        auto optValue = Converter::ArkValue<Opt_Boolean>(ANTIALIAS_DEFAULT_VALUE);
        peer_ = accessor_->ctor(&optValue);
        ASSERT_NE(peer_, nullptr);
        AccessorTestBaseParent::SetUp();
    }

    void TearDown() override
    {
        AccessorTestBaseParent::TearDown();
        RenderingContextSettingsPeer::Destroy(peer_);
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
        RenderingContextSettingsPeer::Destroy(peer_);
        auto optValue = Converter::ArkValue<Opt_Boolean>(value);
        peer_ = accessor_->ctor(&optValue);
        ASSERT_NE(peer_, nullptr);
        auto result = accessor_->getAntialias(peer_);
        EXPECT_EQ(result, expected) << "Input value is: "
            << input << ", method: GetRepeat";
    }
    RenderingContextSettingsPeer::Destroy(peer_);
    auto optValue = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    peer_ = accessor_->ctor(&optValue);
    auto result = accessor_->getAntialias(peer_);
    EXPECT_EQ(result, ANTIALIAS_DEFAULT_VALUE)
        << "Input value is: empty, method: GetRepeat";
    RenderingContextSettingsPeer::Destroy(peer_);
    peer_ = accessor_->ctor(nullptr);
    result = accessor_->getAntialias(peer_);
    EXPECT_EQ(result, ANTIALIAS_DEFAULT_VALUE)
        << "Input value is: nullptr, method: GetRepeat";
}

/**
 * @tc.name: getAntialiasTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderingContextSettingsAccessorTest, getAntialiasTest, TestSize.Level1)
{
    for (const auto& [input, expected, value] : AccessorTestFixtures::testFixtureBooleanValues) {
        peer_->antialias = value;
        auto result = accessor_->getAntialias(peer_);
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
    for (const auto& [input, value, expected] : AccessorTestFixtures::testFixtureBooleanValues) {
        accessor_->setAntialias(peer_, value);
        auto result = peer_->antialias.value();
        EXPECT_EQ(result, expected) <<
            "Input value is: " << input << ", method: SetRepeat";
    }
}
}