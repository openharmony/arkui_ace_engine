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

#include "gmock/gmock.h"
#include "accessor_test_base.h"
#include "accessor_test_utils.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/implementation/path_shape_peer.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_theme_style.h"


namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace Converter {
    template<>
    void AssignArkValue(Ark_PathShapeOptions& dst, const PathShapeOptions& src, ConvContext *ctx)
    {
        auto commands = Converter::ArkValue<Opt_String>(src.commands.value_or(""), ctx);
        dst.commands = commands;
    }
}

class PathShapeAccessorTest : public AccessorTestCtorBase<GENERATED_ArkUIPathShapeAccessor,
    &GENERATED_ArkUIAccessors::getPathShapeAccessor, PathShapePeer> {
public:
    void *CreatePeerInstance() override
    {
        PathShapeOptions pathShapeOptions{};
        auto options = Converter::ArkValue<Opt_PathShapeOptions>(pathShapeOptions);
        return accessor_->construct(&options);
    }
};

/**
 * @tc.name: OffsetTest
 * @tc.desc:
 * @tc.type: FUNC
*/
HWTEST_F(PathShapeAccessorTest, OffsetTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->offset, nullptr);
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(peer_->shape, nullptr);

    using OffsetTestStep = std::pair<int32_t, int32_t>;
    const std::vector<OffsetTestStep> OFFSET_TEST_PLAN = {{2, 4}, {6, 8}, {10, 12}};
    Opt_Length optX, optY;
    Ark_Position arkOffset{};
    DimensionOffset peerOffset;
    Converter::ConvContext ctx;

    for (const auto &[x, y]: OFFSET_TEST_PLAN) {
        optX = Converter::ArkValue<Opt_Length>(Dimension(x), &ctx);
        optY = Converter::ArkValue<Opt_Length>(Dimension(y), &ctx);
        arkOffset = {optX, optY};

        accessor_->offset(peer_, &arkOffset);
        peerOffset = peer_->shape->GetOffset();
        EXPECT_EQ(peerOffset.GetX().ToString(), Dimension(x).ToString());
        EXPECT_EQ(peerOffset.GetY().ToString(), Dimension(y).ToString());
    }
}

/**
 * @tc.name: PositionTest
 * @tc.desc:
 * @tc.type: FUNC
*/
HWTEST_F(PathShapeAccessorTest, PositionTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->position, nullptr);
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(peer_->shape, nullptr);

    using OffsetTestStep = std::pair<int32_t, int32_t>;
    const std::vector<OffsetTestStep> POSITION_TEST_PLAN = {{2, 4}, {6, 8}, {10, 12}};
    Opt_Length optX, optY;
    Ark_Position arkPosition{};
    DimensionOffset peerPosition;
    Converter::ConvContext ctx;

    for (const auto &[x, y]: POSITION_TEST_PLAN) {
        optX = Converter::ArkValue<Opt_Length>(Dimension(x), &ctx);
        optY = Converter::ArkValue<Opt_Length>(Dimension(y), &ctx);
        arkPosition = {optX, optY};

        accessor_->position(peer_, &arkPosition);
        peerPosition = peer_->shape->GetPosition();
        EXPECT_EQ(peerPosition.GetX().ToString(), Dimension(x).ToString());
        EXPECT_EQ(peerPosition.GetY().ToString(), Dimension(y).ToString());
    }
}

/**
 * @tc.name: fillTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PathShapeAccessorTest, fillTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->fill, nullptr);
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(peer_->shape, nullptr);

    using FillTestStep = std::pair<Ark_ResourceColor, Color>;
    const std::vector<FillTestStep> FILL_TEST_PLAN = {
        // Ark_Color
        {Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(Ark_Color::ARK_COLOR_RED),
            Converter::OptConvert<Color>(Ark_Color::ARK_COLOR_RED).value_or(Color())},
        {Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(Ark_Color::ARK_COLOR_GREEN),
            Converter::OptConvert<Color>(Ark_Color::ARK_COLOR_GREEN).value_or(Color())},
        {Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(Ark_Color::ARK_COLOR_BLUE),
            Converter::OptConvert<Color>(Ark_Color::ARK_COLOR_BLUE).value_or(Color())},
        // Ark_Number
        {Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(Converter::ArkValue<Ark_Float64>(0x11223344)),
            Color(0x11223344)},
        {Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(Converter::ArkValue<Ark_Float64>(0xAABBCCDD)),
            Color(0xAABBCCDD)},
        // Ark_String
        {Converter::ArkUnion<Ark_ResourceColor, Ark_String>(Converter::ArkValue<Ark_String>("#11223344")),
            Color(0x11223344)},
        {Converter::ArkUnion<Ark_ResourceColor, Ark_String>(Converter::ArkValue<Ark_String>("#AABBCCDD")),
            Color(0xAABBCCDD)},
        // Ark_Resource in next test
    };
    Color peerColor;

    for (const auto &[inputColor, expectedColor]: FILL_TEST_PLAN) {
        accessor_->fill(peer_, &inputColor);
        peerColor = peer_->shape->GetColor();
        EXPECT_EQ(peerColor.GetValue(), expectedColor.GetValue());
    }
}

/**
 * @tc.name: fillFromResourceTest
 * @tc.desc: Color from Resource
 * @tc.type: FUNC
 */
HWTEST_F(PathShapeAccessorTest, fillFromResourceTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->fill, nullptr);
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(peer_->shape, nullptr);
    const auto RES_NAME_ID = NamedResourceId { "fill_color_resource_name", ResourceType::COLOR };
    const auto EXPECTED_COLOR = Color(0xAABBCCDD);

    auto arkResource = CreateResource(RES_NAME_ID);
    auto arkResourceColor = Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(arkResource);
    AddResource(RES_NAME_ID, EXPECTED_COLOR);

    accessor_->fill(peer_, &arkResourceColor);
    auto peerColor = peer_->shape->GetColor();

    EXPECT_EQ(peerColor.GetValue(), EXPECTED_COLOR.GetValue());
}

/**
 * @tc.name: commandsTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PathShapeAccessorTest, commandsTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->commands, nullptr);
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(peer_->shape, nullptr);

    using CommandsTestStep = std::pair<Ark_String, std::string>;
    const std::vector<CommandsTestStep> COMMANDS_TEST_PLAN = {
        {Converter::ArkValue<Ark_String>("command1"), "command1"},
        {Converter::ArkValue<Ark_String>("command1, command2"), "command1, command2"},
    };
    std::string peerCommands;

    for (const auto &[arkInput, expected]: COMMANDS_TEST_PLAN) {
        accessor_->commands(peer_, &arkInput);
        peerCommands = peer_->shape->GetValue();
        EXPECT_EQ(peerCommands, expected);
    }
}
} // namespace OHOS::Ace::NG