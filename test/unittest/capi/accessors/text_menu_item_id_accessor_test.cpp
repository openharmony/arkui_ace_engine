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
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "core/interfaces/native/implementation/text_menu_item_id_peer.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class TextMenuItemIdAccessorTest : public AccessorTestBase<GENERATED_ArkUITextMenuItemIdAccessor,
    &GENERATED_ArkUIAccessors::getTextMenuItemIdAccessor, TextMenuItemIdPeer> {
};

/**
 * @tc.name: createTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextMenuItemIdAccessorTest, createTest, TestSize.Level1)
{
    EXPECT_EQ(peer_->id, std::nullopt);
    const std::vector<std::string> validValues {"Create1", "2", "My ID", ""};
    for (const auto& value : validValues) {
        auto arkString = Converter::ArkValue<Ark_String>(value);
        auto arkValue = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(arkString);
        auto peer = reinterpret_cast<TextMenuItemIdPeer*>(accessor_->of(&arkValue));
        EXPECT_EQ(peer->id.value(), value);
        finalyzer_(peer);
    }
}

/**
 * @tc.name: compareTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextMenuItemIdAccessorTest, compareTest, TestSize.Level1)
{
    EXPECT_EQ(peer_->id, std::nullopt);
    const Ark_TextMenuItemId obj { .ptr = peer_ };
    auto peer = static_cast<TextMenuItemIdPeer *>(accessor_->ctor());
    auto result = Converter::Convert<bool>(accessor_->equals(peer, &obj));
    EXPECT_FALSE(result);
    finalyzer_(peer);

    const std::vector<std::tuple<std::string, std::string, bool>> validValues {
        {"Test 1", "Test 1", true},
        {"Compare2", "Compare22", false},
        {"ID", "Id", false},
        {"1234567890", "1234567890", true},
        {"", " ", false}
    };
    for (auto [value1, value2, expected] : validValues) {
        auto arkString = Converter::ArkValue<Ark_String>(value1);
        auto arkValue = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(arkString);
        peer = reinterpret_cast<TextMenuItemIdPeer*>(accessor_->of(&arkValue));
        peer_->id = value2;
        result = Converter::Convert<bool>(accessor_->equals(peer, &obj));
        EXPECT_EQ(result, expected);
        finalyzer_(peer);
    }
}
} // namespace OHOS::Ace::NG
