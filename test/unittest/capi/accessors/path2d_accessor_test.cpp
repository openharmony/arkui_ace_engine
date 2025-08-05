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

#include "accessor_test_base.h"
#include "core/interfaces/native/implementation/matrix2d_peer_impl.h"
#include "core/interfaces/native/implementation/path2d_peer_impl.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
const std::string EXTENDED_PATH = "M0 0 L600 0";
const std::string DEFAULT_STRING_PATH = "";
const auto DEFAULT_UNIT = Ace::CanvasUnit::DEFAULT;
const auto DEFAULT_ARK_UNIT = Ark_LengthMetricsUnit::ARK_LENGTH_METRICS_UNIT_DEFAULT;
const std::string EXP_PATH = "CMDS:M0 0 L600 0";
const std::string EXP_TRANSFORM = "TRANSFORM:100.000000,2.350000,5.420000,10.250000,12.340000,56.730000";

std::vector<double> numberTestPlan = { 100, 10.25, 2.35, 5.42, 12.34, 56.73 };
std::vector<std ::string> addPathTestPlan = {
    EXP_PATH + " " + EXP_TRANSFORM + " ",
    EXP_PATH + " " + EXP_TRANSFORM + " " + EXP_PATH + " " + EXP_TRANSFORM + " ",
    EXP_PATH + " " + EXP_TRANSFORM + " " + EXP_PATH + " " + EXP_TRANSFORM + " " + EXP_PATH + " " + EXP_TRANSFORM + " ",
};
std::vector<std::tuple<std::string, std::string>> pathTestPlan = {
    { "M0 0 L600 0", "CMDS:M0 0 L600 0 " },
    { "M0 0 L100 0", "CMDS:M0 0 L100 0 " },
    { "", "CMDS: " },
};
std::vector<std::tuple<Ark_LengthMetricsUnit, Ace::CanvasUnit>> unitTestPlan = {
    { ARK_LENGTH_METRICS_UNIT_DEFAULT, Ace::CanvasUnit::DEFAULT },
    { ARK_LENGTH_METRICS_UNIT_PX, Ace::CanvasUnit::PX },
    { static_cast<Ark_LengthMetricsUnit>(-1), Ace::CanvasUnit::DEFAULT },
};
std::vector<std::tuple<Ark_String, std::string>> pathStringTestPlan = {
    { Converter::ArkValue<Ark_String>("M0 0 L600 0 "), "CMDS:M0 0 L600 0  " },
    { Converter::ArkValue<Ark_String>("M0 0 L100 0 "), "CMDS:M0 0 L100 0  " },
    { Converter::ArkValue<Ark_String>(""), "" },
};
} // namespace

class Path2DAccessorTest
    : public AccessorTestBase0<GENERATED_ArkUIPath2DAccessor,
        &GENERATED_ArkUIAccessors::getPath2DAccessor, Path2DPeer> {
public:
    void SetUp(void) override
    {
        ASSERT_NO_FATAL_FAILURE(AccessorTestBase0::SetUp());
        mockPathKeeper_ = AceType::MakeRefPtr<CanvasPath2D>();
        ASSERT_NE(mockPathKeeper_, nullptr);
        peer_->SetCanvasPath2d(mockPathKeeper_);
    }

    void TearDown() override
    {
        AccessorTestBase0::TearDown();
        mockPathKeeper_ = nullptr;
    }
    RefPtr<CanvasPath2D> mockPathKeeper_ = nullptr;
};

/**
 * @tc.name: construct0Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Path2DAccessorTest, construct0Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->construct1, nullptr);
    peer_ = accessor_->construct0();
    ASSERT_NE(peer_, nullptr);
    auto canvasPath = peer_->GetCanvasPath2d();
    auto unit = peer_->GetUnit();
    ASSERT_NE(canvasPath, nullptr);
    EXPECT_EQ(canvasPath->ToString(), DEFAULT_STRING_PATH);
    EXPECT_EQ(unit, DEFAULT_UNIT);
}

/**
 * @tc.name: construct1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Path2DAccessorTest, construct1Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->construct2, nullptr);
    for (const auto& [actual, expected] : unitTestPlan) {
        peer_ = accessor_->construct1(actual);
        ASSERT_NE(peer_, nullptr);
        auto canvasPath = peer_->GetCanvasPath2d();
        auto unit = peer_->GetUnit();
        ASSERT_NE(canvasPath, nullptr);
        EXPECT_EQ(canvasPath->ToString(), DEFAULT_STRING_PATH);
        EXPECT_EQ(unit, expected);
    }
}

/**
 * @tc.name: construct2Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Path2DAccessorTest, construct2Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->construct1, nullptr);
    for (const auto& [actual, expected] : pathTestPlan) {
        auto path = Referenced::MakeRefPtr<CanvasPath2D>(actual);
        auto peer = Referenced::MakeRefPtr<Path2DPeer>();
        ASSERT_NE(peer, nullptr);
        peer->SetCanvasPath2d(path);
        auto arkPeer = Referenced::RawPtr(peer);
        ASSERT_NE(arkPeer, nullptr);
        peer_ = accessor_->construct2(arkPeer);
        ASSERT_NE(peer_, nullptr);
        auto canvasPath = peer_->GetCanvasPath2d();
        auto unit = peer_->GetUnit();
        ASSERT_NE(canvasPath, nullptr);
        EXPECT_EQ(canvasPath->ToString(), expected);
        EXPECT_EQ(unit, DEFAULT_UNIT);
    }
}

/**
 * @tc.name: construct3UnitTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Path2DAccessorTest, construct3UnitTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->construct3, nullptr);
    for (const auto& [actual, expected] : unitTestPlan) {
        peer_ = accessor_->construct3(nullptr, actual);
        ASSERT_NE(peer_, nullptr);
        auto canvasPath = peer_->GetCanvasPath2d();
        auto unit = peer_->GetUnit();
        ASSERT_NE(canvasPath, nullptr);
        EXPECT_EQ(canvasPath->ToString(), DEFAULT_STRING_PATH);
        EXPECT_EQ(unit, expected);
    }
}

/**
 * @tc.name: construct3PathTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Path2DAccessorTest, construct3PathTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->construct3, nullptr);
    for (const auto& [actual, expected] : pathTestPlan) {
        auto path = Referenced::MakeRefPtr<CanvasPath2D>(actual);
        auto peer = Referenced::MakeRefPtr<Path2DPeer>();
        ASSERT_NE(peer, nullptr);
        peer->SetCanvasPath2d(path);
        auto arkPeer = Referenced::RawPtr(peer);
        ASSERT_NE(arkPeer, nullptr);
        peer_ = accessor_->construct3(arkPeer, DEFAULT_ARK_UNIT);
        ASSERT_NE(peer_, nullptr);
        auto canvasPath = peer_->GetCanvasPath2d();
        auto unit = peer_->GetUnit();
        ASSERT_NE(canvasPath, nullptr);
        EXPECT_EQ(canvasPath->ToString(), expected);
        EXPECT_EQ(unit, DEFAULT_UNIT);
    }
}

/**
 * @tc.name: construct4Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Path2DAccessorTest, construct4Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->construct4, nullptr);
    for (const auto& [actual, expected] : pathStringTestPlan) {
        peer_ = accessor_->construct4(&actual);
        ASSERT_NE(peer_, nullptr);
        auto canvasPath = peer_->GetCanvasPath2d();
        auto unit = peer_->GetUnit();
        ASSERT_NE(canvasPath, nullptr);
        EXPECT_EQ(canvasPath->ToString(), expected);
        EXPECT_EQ(unit, DEFAULT_UNIT);
    }
}

/**
 * @tc.name: construct5UnitTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Path2DAccessorTest, construct5UnitTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->construct5, nullptr);
    for (const auto& [actual, expected] : unitTestPlan) {
        peer_ = accessor_->construct5(nullptr, actual);
        ASSERT_NE(peer_, nullptr);
        auto canvasPath = peer_->GetCanvasPath2d();
        auto unit = peer_->GetUnit();
        ASSERT_NE(canvasPath, nullptr);
        EXPECT_EQ(canvasPath->ToString(), DEFAULT_STRING_PATH);
        EXPECT_EQ(unit, expected);
    }
}

/**
 * @tc.name: construct5DescriptionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Path2DAccessorTest, construct5DescriptionTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->construct5, nullptr);
    for (const auto& [actual, expected] : pathStringTestPlan) {
        peer_ = accessor_->construct5(&actual, DEFAULT_ARK_UNIT);
        ASSERT_NE(peer_, nullptr);
        auto canvasPath = peer_->GetCanvasPath2d();
        auto unit = peer_->GetUnit();
        ASSERT_NE(canvasPath, nullptr);
        EXPECT_EQ(canvasPath->ToString(), expected);
        EXPECT_EQ(unit, DEFAULT_UNIT);
    }
}

/**
 * @tc.name: addPathTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Path2DAccessorTest, addPathTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->addPath, nullptr);
    auto path = Referenced::MakeRefPtr<CanvasPath2D>(EXTENDED_PATH);
    auto peerPathImpl = Referenced::MakeRefPtr<Path2DPeer>();
    peerPathImpl->SetCanvasPath2d(path);
    auto arkPath = Referenced::RawPtr(peerPathImpl);
    auto peerMatrix = PeerUtils::CreatePeer<Matrix2DPeer>();
    auto optMatrix = Converter::ArkValue<Opt_Matrix2D>(peerMatrix);
    peerMatrix->SetScaleX(numberTestPlan[0]);
    peerMatrix->SetScaleY(numberTestPlan[1]);
    peerMatrix->SetRotateX(numberTestPlan[2]);
    peerMatrix->SetRotateY(numberTestPlan[3]);
    peerMatrix->SetTranslateX(numberTestPlan[4]);
    peerMatrix->SetTranslateY(numberTestPlan[5]);
    accessor_->addPath(peer_, arkPath, &optMatrix);
    EXPECT_EQ(mockPathKeeper_->ToString(), addPathTestPlan[0]);
    accessor_->addPath(peer_, arkPath, &optMatrix);
    EXPECT_EQ(mockPathKeeper_->ToString(), addPathTestPlan[1]);
    accessor_->addPath(peer_, arkPath, &optMatrix);
    EXPECT_EQ(mockPathKeeper_->ToString(), addPathTestPlan[2]);
}
} // namespace OHOS::Ace::NG
