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

#include "accessor_test_base.h"
#include "node_api.h"
#include "core/interfaces/native/implementation/path2d_accessor_peer_impl.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/converter.h"
#include "gmock/gmock.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
const auto TRANSFORM_UNITY_VALUE = 1.00;
const auto TRANSFORM_ZERO_VALUE = 0.00;

std::vector<std::vector<double>>
    ARRAY_NUMBER_TEST_PLAN = {
        { 100, 10.25, 2.35, 5.42, 12.34, 56.73 },
        { 100, 10.25, 0, 5.42, 12.34, 56.73 },
        { 100, -10.25, 0, -5.42, 12.34, -56.73 },
        { 0, 0, 0, 0, 0, 0 },
        { -100, -10.25, -2.35, -5.42, -12.34, -56.73 },
    };
std::vector<double> NUMBER_TEST_PLAN = {
    100, 0, -100, 12.34, -56.73,
};

std::vector<int32_t> INT32_TEST_PLAN = {
    100, 0, -100, 12, -56,
};

class StubCanvasPath : public CanvasPath2D {
public:
    StubCanvasPath() = default;
    ~StubCanvasPath() override = default;
    virtual void CanvasPath2D::AddPath(const RefPtr<CanvasPath2D>& path) {
          std::printf("path: stub exec\n")  
    }
};
class MockCanvasPath : public StubCanvasPath {
public:
    MockCanvasPath() = default;
    ~MockCanvasPath() override = default;
    MOCK_METHOD(void, AddPath, (const RefPtr<CanvasPath2D>&));
};
} // namespace

class Path2DAccessorTest
    : public AccessorTestBase<GENERATED_ArkUIPath2DAccessor,
        &GENERATED_ArkUIAccessors::getCanvasPathAccessor, Path2DPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        mockPath_ = new MockCanvasPath();
        mockPathKeeper_ = AceType::Claim(mockPattern_);
        ASSERT_NE(mockPathKeeper_, nullptr);
        auto peerImpl = reinterpret_cast<GeneratedModifier::Path2DPeerImpl*>(peer_);
        ASSERT_NE(peerImpl, nullptr);
        peerImpl->path = mockPathKeeper_;
        ASSERT_NE(mockPath_, nullptr);
    }

    void TearDown() override
    {
        AccessorTestBaseParent::TearDown();
        mockPathKeeper_ = nullptr;
        mockPath_ = nullptr;
    }

    MockCanvasPath* mockPattern_ = nullptr;
    RefPtr<MockCanvasPath> mockPatternKeeper_ = nullptr;
};

/**
 * @tc.name: addPathTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Path2DAccessorTest, addPathTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->addPath, nullptr);

    auto path = new StubCanvasPath();

    Ark_Path2D arkPath;
    auto peerPathImpl = Referenced::MakeRefPtr<GeneratedModifier::Path2DPeerImpl>();
    arkPath.ptr = reinterpret_cast<Path2DPeer*>(Referenced::RawPtr(peerPathImpl));
    peerPathImpl->path = AceType::MakeRefPtr<StubCanvasPath>();

    Ark_Matrix2D arkMatrix;
    auto peerMatrix = new Matrix2DPeer();
    arkMatrix.ptr = peerMatrix;
    auto optMatrix = Converter::ArkValue<Opt_Matrix2D>(arkMatrix);



    // auto x = Converter::ArkValue<Ark_Number>(FIRST_X_VALUE);
    // auto y = Converter::ArkValue<Ark_Number>(FIRST_Y_VALUE);
    // auto radius = Converter::ArkValue<Ark_Number>(static_cast<float>(DEFAULT_DOUBLE_VALUE));
    // auto startAngle = Converter::ArkValue<Ark_Number>(DEFAULT_START_VALUE);
    // auto endAngle = Converter::ArkValue<Ark_Number>(TWO_PI_VALUE);
    // auto clockwise = Converter::ArkValue<Opt_Boolean>(DEFAULT_BOOL_VALUE);

    // EXPECT_CALL(*mockPath_, AddPath(_, _, _, _, _, _)).Times(EXPECTED_NUMBER_OF_CALLS);
    // accessor_->addPath(peer_, &x, &y, &radius, &startAngle, &endAngle, &clockwise);
    
}
} // namespace OHOS::Ace::NG