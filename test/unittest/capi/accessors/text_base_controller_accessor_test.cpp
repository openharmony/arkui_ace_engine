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
#include "core/interfaces/native/implementation/text_base_controller_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
struct CheckSetSelection {
    int32_t selectionStart = 0;
    int32_t selectionEnd = 0;
    std::optional<OHOS::Ace::SelectionOptions> options = std::nullopt;
    bool isForward = true;
} g_checkSetSelection;

class MockTextBaseControllerPeer : public TextBaseControllerPeer {
public:
    MockTextBaseControllerPeer() = default;
    ~MockTextBaseControllerPeer() override = default;
    MOCK_METHOD(void, CloseSelectionMenu, ());
    MOCK_METHOD(OHOS::Ace::WeakPtr<OHOS::Ace::NG::LayoutInfoInterface>, GetLayoutInfoInterface, ());
    void SetSelection(int32_t selectionStart, int32_t selectionEnd,
        const std::optional<OHOS::Ace::SelectionOptions>& options = std::nullopt, bool isForward = false) override
    {
        g_checkSetSelection.selectionStart = selectionStart;
        g_checkSetSelection.selectionEnd = selectionEnd;
        g_checkSetSelection.options = options;
        g_checkSetSelection.isForward = isForward;
    }
};
} // namespace

class TextBaseControllerAccessorTest : public AccessorTestCtorBase<GENERATED_ArkUITextBaseControllerAccessor,
    &GENERATED_ArkUIAccessors::getTextBaseControllerAccessor, MockTextBaseControllerPeer> {
public:
    void* CreatePeerInstance() override
    {
        return new MockTextBaseControllerPeer();
    }
};

/**
 * @tc.name: CloseSelectionMenuTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextBaseControllerAccessorTest, CloseSelectionMenuTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->closeSelectionMenu, nullptr);
    EXPECT_CALL(*peer_, CloseSelectionMenu()).Times(1);
    accessor_->closeSelectionMenu(peer_);
}

/**
 * @tc.name: GetLayoutManagerTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextBaseControllerAccessorTest, GetLayoutManagerTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getLayoutManager, nullptr);
    auto layoutInfo = OHOS::Ace::NG::LayoutInfoInterface();
    EXPECT_CALL(*peer_, GetLayoutInfoInterface()).Times(1).WillOnce(Return(layoutInfo.GetLayoutInfoInterface()));
    Opt_LayoutManager layoutManager = accessor_->getLayoutManager(peer_);
    auto managerOpt = Converter::GetOpt(layoutManager);
    ASSERT_TRUE(managerOpt.has_value());
    auto manager = managerOpt.value();
    ASSERT_NE(manager, nullptr);
}

/**
 * @tc.name: SetSelectionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextBaseControllerAccessorTest, SetSelectionTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setSelection, nullptr);
    constexpr int32_t SELECTION_START = 1;
    constexpr int32_t SELECTION_END = 2;
    auto selectionStartArk = Converter::ArkValue<Ark_Number>(SELECTION_START);
    auto selectionEndArk = Converter::ArkValue<Ark_Number>(SELECTION_END);
    auto menuPolicyArkOpt =
        Converter::ArkValue<Opt_MenuPolicy>(Converter::ArkValue<Ark_MenuPolicy>(MenuPolicy::SHOW));
    Ark_SelectionOptions optionsArk = {.menuPolicy = menuPolicyArkOpt};
    const Opt_SelectionOptions optionsArkOpt = Converter::ArkValue<Opt_SelectionOptions>(optionsArk);

    accessor_->setSelection(peer_, &selectionStartArk, &selectionEndArk, &optionsArkOpt);
    EXPECT_EQ(g_checkSetSelection.selectionStart, SELECTION_START);
    EXPECT_EQ(g_checkSetSelection.selectionEnd, SELECTION_END);
    EXPECT_EQ(g_checkSetSelection.isForward, false);
    ASSERT_NE(g_checkSetSelection.options.has_value(), false);
    EXPECT_EQ(g_checkSetSelection.options.value().menuPolicy, MenuPolicy::SHOW);
}
} // namespace OHOS::Ace::NG
