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
#include "accessor_test_utils.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "core/interfaces/native/implementation/text_menu_item_id_peer.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class TextMenuItemIdAccessorTest : public AccessorTestBase<GENERATED_ArkUITextMenuItemIdAccessor,
    &GENERATED_ArkUIAccessors::getTextMenuItemIdAccessor, TextMenuItemIdPeer> {
public:
    template<typename ResourceValue>
    Ark_ResourceStr CreateResourceStr(const ResourceValue& value,
        ResourceType type = ResourceType::STRING)
    {
        AddResource(++resCounter_, value);
        IntResourceId id {resCounter_, type};
        return CreateResourceUnion<Ark_ResourceStr>(id);
    }

private:
    uint32_t resCounter_ = 0;
};

/**
 * @tc.name: ofTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextMenuItemIdAccessorTest, ofTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->of, nullptr);
    EXPECT_EQ(peer_->id, std::nullopt); // default value
    const std::string string1("TextMenuItemIdAccessorTest ofTest");
    const Ark_ResourceStr resource1 = CreateResourceStr(string1);
    const std::string string2("2");
    const Ark_ResourceStr resource2 = CreateResourceStr(string2);
    const std::string string3("Test");
    const Ark_ResourceStr resource3 = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(string3);
    const std::string string4("");
    const Ark_ResourceStr resource4 = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(string4);
    const Ark_ResourceStr resource5 = CreateResourceStr(Color::BLACK, ResourceType::COLOR);
    const std::vector<std::tuple<const Ark_ResourceStr*, std::optional<std::string>>> testPlan {
        {&resource1, string1},
        {&resource2, string2},
        {&resource3, string3},
        {&resource4, string4},
        {&resource5, std::nullopt},
        {nullptr, std::nullopt},
    };
    for (auto [value, expected] : testPlan) {
        Ark_TextMenuItemId peer = accessor_->of(value);
        EXPECT_EQ(peer->id, expected);
        finalyzer_(peer);
    }
}

/**
 * @tc.name: equalsTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextMenuItemIdAccessorTest, equalsTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->equals, nullptr);
    auto peer1 = PeerUtils::CreatePeer<TextMenuItemIdPeer>("Test 1");
    auto peer2 = PeerUtils::CreatePeer<TextMenuItemIdPeer>("Test 1");
    auto peer3 = PeerUtils::CreatePeer<TextMenuItemIdPeer>("Compare2");
    auto peer4 = PeerUtils::CreatePeer<TextMenuItemIdPeer>("Compare22");
    auto peer5 = PeerUtils::CreatePeer<TextMenuItemIdPeer>("ID");
    auto peer6 = PeerUtils::CreatePeer<TextMenuItemIdPeer>("Id");
    auto peer7 = PeerUtils::CreatePeer<TextMenuItemIdPeer>("1234567890");
    auto peer8 = PeerUtils::CreatePeer<TextMenuItemIdPeer>("1234567890");
    auto peer9 = PeerUtils::CreatePeer<TextMenuItemIdPeer>("");
    auto peer10 = PeerUtils::CreatePeer<TextMenuItemIdPeer>(" ");
    auto peer11 = PeerUtils::CreatePeer<TextMenuItemIdPeer>(std::nullopt);
    auto peer12 = PeerUtils::CreatePeer<TextMenuItemIdPeer>(std::nullopt);
    const std::vector<std::tuple<Ark_TextMenuItemId, Ark_TextMenuItemId, bool>> testPlan {
        {peer1, peer2, true},
        {peer3, peer4, false},
        {peer5, peer6, false},
        {peer7, peer8, true},
        {peer9, peer10, false},
        {peer11, peer12, false},
        {peer11, peer1, false},
        {peer1, peer1, true},
        {peer1, nullptr, false},
        {nullptr, peer2, false},
        {nullptr, nullptr, false},
    };
    for (auto [value1, value2, expected] : testPlan) {
        const bool result = Converter::Convert<bool>(accessor_->equals(value1, value2));
        EXPECT_EQ(result, expected);
    }

    PeerUtils::DestroyPeer(peer1);
    PeerUtils::DestroyPeer(peer2);
    PeerUtils::DestroyPeer(peer3);
    PeerUtils::DestroyPeer(peer4);
    PeerUtils::DestroyPeer(peer5);
    PeerUtils::DestroyPeer(peer6);
    PeerUtils::DestroyPeer(peer7);
    PeerUtils::DestroyPeer(peer8);
    PeerUtils::DestroyPeer(peer9);
    PeerUtils::DestroyPeer(peer10);
    PeerUtils::DestroyPeer(peer11);
    PeerUtils::DestroyPeer(peer12);
}

/**
 * @tc.name: getCUT_Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextMenuItemIdAccessorTest, getCUT_Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->getCUT, nullptr);
    Ark_TextMenuItemId peer = accessor_->getCUT();
    EXPECT_EQ(peer->id, "OH_DEFAULT_CUT");
    finalyzer_(peer);
}

/**
 * @tc.name: getCOPY_Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextMenuItemIdAccessorTest, getCOPY_Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->getCOPY, nullptr);
    Ark_TextMenuItemId peer = accessor_->getCOPY();
    EXPECT_EQ(peer->id, "OH_DEFAULT_COPY");
    finalyzer_(peer);
}

/**
 * @tc.name: getPASTE_Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextMenuItemIdAccessorTest, getPASTE_Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->getPASTE, nullptr);
    Ark_TextMenuItemId peer = accessor_->getPASTE();
    EXPECT_EQ(peer->id, "OH_DEFAULT_PASTE");
    finalyzer_(peer);
}

/**
 * @tc.name: getSELECT_ALL_Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextMenuItemIdAccessorTest, getSELECT_ALL_Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->getSELECT_ALL, nullptr);
    Ark_TextMenuItemId peer = accessor_->getSELECT_ALL();
    EXPECT_EQ(peer->id, "OH_DEFAULT_SELECT_ALL");
    finalyzer_(peer);
}

/**
 * @tc.name: getCOLLABORATION_SERVICE_Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextMenuItemIdAccessorTest, getCOLLABORATION_SERVICE_Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->getCOLLABORATION_SERVICE, nullptr);
    Ark_TextMenuItemId peer = accessor_->getCOLLABORATION_SERVICE();
    EXPECT_EQ(peer->id, "OH_DEFAULT_COLLABORATION_SERVICE");
    finalyzer_(peer);
}

/**
 * @tc.name: getCAMERA_INPUT_Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextMenuItemIdAccessorTest, getCAMERA_INPUT_Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->getCAMERA_INPUT, nullptr);
    Ark_TextMenuItemId peer = accessor_->getCAMERA_INPUT();
    EXPECT_EQ(peer->id, "OH_DEFAULT_CAMERA_INPUT");
    finalyzer_(peer);
}

/**
 * @tc.name: getAI_WRITER_Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextMenuItemIdAccessorTest, getAI_WRITER_Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->getAI_WRITER, nullptr);
    Ark_TextMenuItemId peer = accessor_->getAI_WRITER();
    EXPECT_EQ(peer->id, "OH_DEFAULT_AI_WRITE");
    finalyzer_(peer);
}

/**
 * @tc.name: getTRANSLATE_Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextMenuItemIdAccessorTest, getTRANSLATE_Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->getTRANSLATE, nullptr);
    Ark_TextMenuItemId peer = accessor_->getTRANSLATE();
    EXPECT_EQ(peer->id, "OH_DEFAULT_TRANSLATE");
    finalyzer_(peer);
}

/**
 * @tc.name: getSEARCH_Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextMenuItemIdAccessorTest, getSEARCH_Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->getSEARCH, nullptr);
    Ark_TextMenuItemId peer = accessor_->getSEARCH();
    EXPECT_EQ(peer->id, "OH_DEFAULT_SEARCH");
    finalyzer_(peer);
}

/**
 * @tc.name: getSHARE_Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextMenuItemIdAccessorTest, getSHARE_Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->getSHARE, nullptr);
    Ark_TextMenuItemId peer = accessor_->getSHARE();
    EXPECT_EQ(peer->id, "OH_DEFAULT_SHARE");
    finalyzer_(peer);
}
} // namespace OHOS::Ace::NG
