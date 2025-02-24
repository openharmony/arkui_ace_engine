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
const auto ANTIALIAS_DEFAULT_VALUE = Converter::ArkValue<Opt_Boolean>(false);
} // namespace

class RenderingContextSettingsAccessorTest
    : public AccessorTestBaseParent<GENERATED_ArkUIRenderingContextSettingsAccessor,
        &GENERATED_ArkUIAccessors::getRenderingContextSettingsAccessor, RenderingContextSettingsPeer> {
public:
    void SetUp(void) override
    {
        ASSERT_NE(accessor_->ctor, nullptr);
        peer_ = accessor_->ctor(&ANTIALIAS_DEFAULT_VALUE);
        ASSERT_NE(peer_, nullptr);
        AccessorTestBaseParent::SetUp();
    }

    void TearDown() override
    {
        AccessorTestBaseParent::TearDown();
    }
};

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
        std::printf("renderSettings: actual: %d result: %d == %d\n",
            value, Converter::Convert<bool>(result), Converter::Convert<bool>(expected)
        );
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
         std::printf( "renderSettings: actual: %d result: %d == %d\n", Converter::Convert<bool>(value), result, expected);
         EXPECT_EQ(result, expected) <<
            "Input value is: " << input << ", method: SetRepeat";
     }
}
}