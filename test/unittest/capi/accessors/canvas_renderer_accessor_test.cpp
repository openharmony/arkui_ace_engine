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

#include "../stubs/stub_canvas_pattern.h"
#include "accessor_test_base.h"
#include "node_api.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"

#include "gmock/gmock.h"

#include "core/components_ng/pattern/canvas/canvas_paint_method.h"
#include "core/interfaces/arkoala/implementation/canvas_renderer_peer_impl.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {

class MockCanvasPattern : public CanvasPattern {
public:
    MockCanvasPattern() = default;
    ~MockCanvasPattern() override = default;
};

} // namespace

class CanvasRendererAccessorTest
    : public AccessorTestBase<GENERATED_ArkUICanvasRendererAccessor,
    &GENERATED_ArkUIAccessors::getCanvasRendererAccessor, CanvasRendererPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        mockPattern_ = new MockCanvasPattern();
        mockPatternKeeper_ = AceType::Claim(mockPattern_);
        ASSERT_NE(mockPatternKeeper_, nullptr);
        auto peerImpl = reinterpret_cast<GeneratedModifier::CanvasRendererPeerImpl*>(peer_);
        ASSERT_NE(peerImpl, nullptr);
        peerImpl->SetCanvasPattern(mockPatternKeeper_);
        ASSERT_NE(mockPattern_, nullptr);
    }

    void TearDown() override
    {
        AccessorTestBaseParent::TearDown();
        mockPatternKeeper_ = nullptr;
        mockPattern_ = nullptr;
    }

    MockCanvasPattern* mockPattern_ = nullptr;
    RefPtr<MockCanvasPattern> mockPatternKeeper_ = nullptr;
};

/**
 * @tc.name: beginPathTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, beginPathTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->beginPath, nullptr);

    accessor_->beginPath(peer_);
    accessor_->beginPath(peer_);
    accessor_->beginPath(peer_);

    EXPECT_EQ(holder->counter, 3);
    holder->TearDown();
}

/**
 * @tc.name: stroke0Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, stroke0Test, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->stroke0, nullptr);

    accessor_->stroke0(peer_);
    accessor_->stroke0(peer_);
    accessor_->stroke0(peer_);

    EXPECT_EQ(holder->counter, 3);
    holder->TearDown();
}

/**
 * @tc.name: restoreTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, restoreTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->restore, nullptr);

    accessor_->restore(peer_);
    accessor_->restore(peer_);
    accessor_->restore(peer_);

    EXPECT_EQ(holder->counter, 3);
    holder->TearDown();
}

/**
 * @tc.name: saveTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, saveTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->save, nullptr);

    accessor_->save(peer_);
    accessor_->save(peer_);
    accessor_->save(peer_);

    EXPECT_EQ(holder->counter, 3);
    holder->TearDown();
}

/**
 * @tc.name: resetTransformTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, resetTransformTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->resetTransform, nullptr);

    accessor_->resetTransform(peer_);
    accessor_->resetTransform(peer_);
    accessor_->resetTransform(peer_);

    EXPECT_EQ(holder->counter, 3);
    holder->TearDown();
}

/**
 * @tc.name: saveLayerTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, saveLayerTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->saveLayer, nullptr);

    accessor_->saveLayer(peer_);
    accessor_->saveLayer(peer_);
    accessor_->saveLayer(peer_);

    EXPECT_EQ(holder->counter, 3);
    holder->TearDown();
}

/**
 * @tc.name: restoreLayerTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, restoreLayerTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->restoreLayer, nullptr);

    accessor_->restoreLayer(peer_);
    accessor_->restoreLayer(peer_);
    accessor_->restoreLayer(peer_);

    EXPECT_EQ(holder->counter, 3);
    holder->TearDown();
}

/**
 * @tc.name: resetTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, resetTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->reset, nullptr);

    accessor_->reset(peer_);
    accessor_->reset(peer_);
    accessor_->reset(peer_);

    EXPECT_EQ(holder->counter, 3);
    holder->TearDown();
}

} // namespace OHOS::Ace::NG