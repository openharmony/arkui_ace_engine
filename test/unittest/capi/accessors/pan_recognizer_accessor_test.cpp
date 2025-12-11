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
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/implementation/pan_recognizer_peer.h"
#include "core/interfaces/native/implementation/pan_gesture_options_peer.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class PanRecognizerAccessorTest : public AccessorTestBase<GENERATED_ArkUIPanRecognizerAccessor,
                                      &GENERATED_ArkUIAccessors::getPanRecognizerAccessor, PanRecognizerPeer> {};

/**
 * @tc.name: getPanGestureOptionsTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerAccessorTest, getPanGestureOptionsTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getPanGestureOptions, nullptr);

    const std::vector<std::tuple<int32_t, double, PanDirection>> testPlan = {
        { 1, 1.0f, { PanDirection::LEFT } },
        { 1, 4.0f, { PanDirection::VERTICAL } },
        { 2, 0.0f, { PanDirection::LEFT } },
        { 3, 4.0f, { PanDirection::NONE } },
        { 5, 10.0f, { PanDirection::RIGHT } },
    };

    for (auto [fingers, distance, direction] : testPlan) {
        auto mockGestureRecognizer_ = AceType::MakeRefPtr<NG::PanRecognizer>(fingers, direction, distance);
        peer_->Update(mockGestureRecognizer_);
        Ark_PanGestureOptions result = accessor_->getPanGestureOptions(peer_);
        ASSERT_NE(result, nullptr);
        ASSERT_NE(result->handler, nullptr);
        EXPECT_EQ(result->handler->GetFingers(), fingers);
        EXPECT_NEAR(result->handler->GetDistance(), distance, FLT_EPSILON);
        EXPECT_EQ(result->handler->GetDirection().type, direction.type);
    }
}

} // namespace OHOS::Ace::NG
