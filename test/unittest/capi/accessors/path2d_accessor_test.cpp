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
std::vector<double> NUMBER_TEST_PLAN = {
    100, 10.25, 2.35, 5.42, 12.34, 56.73
};

class MockCanvasPath : public CanvasPath2D {
public:
    MockCanvasPath() = default;
    ~MockCanvasPath() override = default;
    MOCK_METHOD(void, AddPath, (const RefPtr<CanvasPath2D>&));
    MOCK_METHOD(void, SetTransform, (double, double, double, double, double, double));
};
} // namespace

class Path2DAccessorTest
    : public AccessorTestBase<GENERATED_ArkUIPath2DAccessor,
        &GENERATED_ArkUIAccessors::getPath2DAccessor, Path2DPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        mockPath_ = new MockCanvasPath();
        mockPathKeeper_ = AceType::Claim(mockPath_);
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
    MockCanvasPath* mockPath_ = nullptr;
    RefPtr<MockCanvasPath> mockPathKeeper_ = nullptr;
};

/**
 * @tc.name: addPathTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Path2DAccessorTest, addPathTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->addPath, nullptr);
    Ark_Path2D arkPath;
    auto peerPathImpl = Referenced::MakeRefPtr<GeneratedModifier::Path2DPeerImpl>();
    arkPath.ptr = reinterpret_cast<Path2DPeer*>(Referenced::RawPtr(peerPathImpl));
    peerPathImpl->path = AceType::MakeRefPtr<MockCanvasPath>();
    Ark_Matrix2D arkMatrix;
    auto peerMatrix = new Matrix2DPeer();
    arkMatrix.ptr = peerMatrix;
    auto optMatrix = Converter::ArkValue<Opt_Matrix2D>(arkMatrix);
    peerMatrix->transform.scaleX = NUMBER_TEST_PLAN[0];
    peerMatrix->transform.scaleY = NUMBER_TEST_PLAN[1];
    peerMatrix->transform.skewX = NUMBER_TEST_PLAN[2];
    peerMatrix->transform.skewY = NUMBER_TEST_PLAN[3];
    peerMatrix->transform.translateX = NUMBER_TEST_PLAN[4];
    peerMatrix->transform.translateY = NUMBER_TEST_PLAN[5];
    auto tr = peerMatrix->transform;
    EXPECT_CALL(*mockPath_, AddPath(peerPathImpl->path)).Times(3);
    EXPECT_CALL(*mockPath_, SetTransform(tr.scaleX, tr.skewX, tr.skewY, tr.scaleY, tr.translateX, tr.translateY))
        .Times(3);
    accessor_->addPath(peer_, &arkPath, &optMatrix);
    accessor_->addPath(peer_, &arkPath, &optMatrix);
    accessor_->addPath(peer_, &arkPath, &optMatrix);
}
} // namespace OHOS::Ace::NG