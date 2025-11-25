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
#include "test/unittest/capi/accessors/accessor_test_fixtures.h"

#include "core/gestures/gesture_event.h"
#include "core/interfaces/native/implementation/symbol_glyph_modifier_peer.h"
#include "core/interfaces/native/implementation/tab_bar_symbol_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
namespace {
}

using namespace testing;
using namespace testing::ext;

class TabBarSymbolAccessorTest : public AccessorTestBase<GENERATED_ArkUITabBarSymbolAccessor,
                                  &GENERATED_ArkUIAccessors::getTabBarSymbolAccessor, TabBarSymbolPeer> {};

/**
 * @tc.name: setNormalTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TabBarSymbolAccessorTest, setNormalTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setNormal, nullptr);

    auto tabPeer = PeerUtils::CreatePeer<TabBarSymbolPeer>();
    auto symbolPeer = PeerUtils::CreatePeer<SymbolGlyphModifierPeer>();

    auto normal = tabPeer->GetNormal().Upgrade();
    EXPECT_EQ(normal, nullptr);

    accessor_->setNormal(tabPeer, symbolPeer);
    normal = tabPeer->GetNormal().Upgrade();
    EXPECT_NE(normal, nullptr);
}

/**
 * @tc.name: getNormalTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TabBarSymbolAccessorTest, getNormalTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getNormal, nullptr);

    auto tabPeer = PeerUtils::CreatePeer<TabBarSymbolPeer>();
    auto symbolPeer = PeerUtils::CreatePeer<SymbolGlyphModifierPeer>();

    auto normal = tabPeer->GetNormal().Upgrade();
    auto normal1 = accessor_->getNormal(tabPeer);
    EXPECT_EQ(normal, nullptr);
    EXPECT_EQ(normal1, nullptr);

    accessor_->setNormal(tabPeer, symbolPeer);
    normal = tabPeer->GetNormal().Upgrade();
    normal1 = accessor_->getNormal(tabPeer);
    EXPECT_NE(normal, nullptr);
    EXPECT_NE(normal1, nullptr);
    EXPECT_EQ(normal, normal1);
}

/**
 * @tc.name: setSelectedTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TabBarSymbolAccessorTest, setSelectedTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setSelected, nullptr);

    auto tabPeer = PeerUtils::CreatePeer<TabBarSymbolPeer>();
    auto symbolPeer = PeerUtils::CreatePeer<SymbolGlyphModifierPeer>();
    auto symbolPeerOpt = Converter::ArkValue<Opt_SymbolGlyphModifier>(symbolPeer);

    auto selected = tabPeer->GetSelected().Upgrade();
    EXPECT_EQ(selected, nullptr);

    accessor_->setSelected(tabPeer, &symbolPeerOpt);
    selected = tabPeer->GetSelected().Upgrade();
    EXPECT_NE(selected, nullptr);
}

/**
 * @tc.name: getSelectedTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TabBarSymbolAccessorTest, getSelectedTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setSelected, nullptr);

    auto tabPeer = PeerUtils::CreatePeer<TabBarSymbolPeer>();
    auto symbolPeer = PeerUtils::CreatePeer<SymbolGlyphModifierPeer>();
    auto symbolPeerOpt = Converter::ArkValue<Opt_SymbolGlyphModifier>(symbolPeer);

    auto selected = tabPeer->GetSelected().Upgrade();
    auto selectedOpt = Converter::OptConvert<Ark_SymbolGlyphModifier>(accessor_->getSelected(tabPeer));
    EXPECT_EQ(selected, nullptr);
    EXPECT_EQ(selectedOpt, std::nullopt);

    accessor_->setSelected(tabPeer, &symbolPeerOpt);
    selected = tabPeer->GetSelected().Upgrade();
    selectedOpt = Converter::OptConvert<Ark_SymbolGlyphModifier>(accessor_->getSelected(tabPeer));
    EXPECT_NE(selected, nullptr);
    EXPECT_NE(selectedOpt, std::nullopt);
    EXPECT_EQ(selected, selectedOpt);
}
}