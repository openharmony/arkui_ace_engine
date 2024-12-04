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
#include "drawing_rendering_context_accessor_test.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "core/interfaces/native/implementation/drawing_rendering_context_peer_impl.h"
#include "core/components_ng/pattern/canvas/canvas_paint_method.h"
#include "gmock/gmock.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {

const Ark_String ARK_STRING = Converter::ArkValue<Ark_String>("PX");
const Opt_CustomObject DEFAULT_SETTING_UNITS = Converter::ArkValue<Opt_CustomObject>(ARK_STRING);

class MockCanvasPattern : public CanvasPattern {
public:
    MockCanvasPattern() = default;
    ~MockCanvasPattern() override = default;
};

} // namespace

class DrawingRenderingContextAccessorTest
    : public AccessorTestBaseParent<GENERATED_ArkUIDrawingRenderingContextAccessor,
    &GENERATED_ArkUIAccessors::getDrawingRenderingContextAccessor, DrawingRenderingContextPeer> {
public:
    void SetUp(void) override
    {
        ASSERT_NE(accessor_->ctor, nullptr);
        peer_ = reinterpret_cast<DrawingRenderingContextPeer*>(accessor_->ctor(&DEFAULT_SETTING_UNITS));
        ASSERT_NE(peer_, nullptr);

        mockPattern_ = new MockCanvasPattern();
        mockPatternKeeper_ = AceType::Claim(mockPattern_);
        ASSERT_NE(mockPatternKeeper_, nullptr);
        auto peerImpl = reinterpret_cast<GeneratedModifier::DrawingRenderingContextPeerImpl*>(peer_);
        ASSERT_NE(peerImpl, nullptr);
        peerImpl->SetCanvasPattern(mockPatternKeeper_);
        ASSERT_NE(mockPattern_, nullptr);

        LOGE("ARKOALA DrawingRenderingContextAccessorTest::SetUp Opt_CustomObject not implemented.");
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
 * @tc.name: invalidateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DrawingRenderingContextAccessorTest, DISABLED_invalidateTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->invalidate, nullptr);

    accessor_->invalidate(peer_);
    accessor_->invalidate(peer_);
    accessor_->invalidate(peer_);

    EXPECT_EQ(holder->counter, 3);

    holder->TearDown();
}

} // namespace OHOS::Ace::NG
