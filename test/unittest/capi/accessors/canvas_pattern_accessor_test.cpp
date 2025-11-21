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
#include "test/mock/core/pattern/mock_canvas_pattern.h"
#include "accessor_test_base.h"
#include "gmock/gmock.h"

#include "frameworks/base/utils/utils.h"

#include "core/interfaces/native/implementation/matrix2d_peer_impl.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/canvas_pattern_peer.h"

#include "core/components_ng/pattern/canvas/canvas_paint_method.h"
#include "core/components_ng/pattern/canvas/canvas_pattern.h"
#include "core/interfaces/native/implementation/canvas_renderer_peer_impl.h"
#include "core/interfaces/native/implementation/canvas_gradient_peer.h"
#include "core/interfaces/native/implementation/image_bitmap_peer_impl.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
const double DEFAULT_DOUBLE_VALUE = 10.0;
const double SCALE_VALUE = 3.0;

class MockCanvasPattern : public CanvasPattern {
public:
    MockCanvasPattern() = default;
    ~MockCanvasPattern() override = default;
};

class CanvasPatternAccessorTest : public AccessorTestBase<GENERATED_ArkUICanvasPatternAccessor,
    &GENERATED_ArkUIAccessors::getCanvasPatternAccessor, CanvasPatternPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        mockPattern_ = new MockCanvasPattern();
        mockPatternKeeper_ = AceType::Claim(mockPattern_);
        ASSERT_NE(mockPatternKeeper_, nullptr);
        rendererKeeper_ = Referenced::MakeRefPtr<GeneratedModifier::CanvasRendererPeerImpl>();
        ASSERT_NE(rendererKeeper_, nullptr);
        rendererKeeper_->SetCanvasPattern(mockPatternKeeper_);
        auto peerImpl = reinterpret_cast<CanvasPatternPeer*>(peer_);
        ASSERT_NE(peerImpl, nullptr);
        peerImpl->SetCanvasRenderer(rendererKeeper_);
        ASSERT_NE(mockPattern_, nullptr);
    }

    void TearDown() override
    {
        AccessorTestBaseParent::TearDown();
        mockPatternKeeper_ = nullptr;
        rendererKeeper_ = nullptr;
        mockPattern_ = nullptr;
    }

    MockCanvasPattern* mockPattern_ = nullptr;
    RefPtr<MockCanvasPattern> mockPatternKeeper_ = nullptr;
    RefPtr<GeneratedModifier::CanvasRendererPeerImpl> rendererKeeper_ = nullptr;
};

/**
 * @tc.name: asetTransformTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPatternAccessorTest, DISABLED_setTransformTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setTransform, nullptr);

    auto peer = PeerUtils::CreatePeer<Matrix2DPeer>();
    auto optMatrix = Converter::ArkValue<Opt_Matrix2D>(peer);
    peer->SetScaleX(SCALE_VALUE);
    peer->SetScaleY(SCALE_VALUE);
    peer->SetRotateX(DEFAULT_DOUBLE_VALUE);
    peer->SetRotateY(DEFAULT_DOUBLE_VALUE);
    peer->SetTranslateX(DEFAULT_DOUBLE_VALUE);
    peer->SetTranslateY(DEFAULT_DOUBLE_VALUE);
    accessor_->setTransform(peer_, &optMatrix);
    EXPECT_TRUE(holder->isCalled);
    EXPECT_TRUE(LessOrEqualCustomPrecision(holder->scaleX, SCALE_VALUE));
    EXPECT_TRUE(LessOrEqualCustomPrecision(holder->scaleY, SCALE_VALUE));

    holder->TearDown();
}
} // namespace OHOS::Ace::NG
