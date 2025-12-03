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

#include "test/unittest/core/layout/vertical_overflow_handler_test_ng.h"
#include "frameworks/core/components_ng/layout/vertical_overflow_handler.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

/**
 * @tc.name: VerticalOverflowHandlerIsOverflowTest
 * @tc.desc: Test IsOverflow method for horizontal overflow detection
 * @tc.type: FUNC
 */
HWTEST_F(OverflowTestNg, VerticalOverflowHandlerIsOverflowTest, TestSize.Level0)
{
    VerticalOverflowHandler handler;
    
    // Set content and child rects that don't overflow
    handler.SetContentRect(RectF(0.f, 0.f, 200.f, 100.f));
    handler.SetTotalChildFrameRect(RectF(0.f, 0.f, 150.f, 100.f));
    
    // Should not be overflow since child is within content
    EXPECT_FALSE(handler.IsOverflow());
    
    // Set content and child rects that do overflow horizontally
    handler.SetContentRect(RectF(0.f, 0.f, 100.f, 100.f));  // 100 width
    handler.SetTotalChildFrameRect(RectF(0.f, 0.f, 150.f, 100.f));  // 150 width
    
    // Should be overflow since child extends beyond content
    EXPECT_TRUE(handler.IsOverflow());
    
    // Test with offset content (left boundary exceeded)
    handler.SetContentRect(RectF(20.f, 0.f, 120.f, 100.f));  // starts at x=20
    handler.SetTotalChildFrameRect(RectF(0.f, 0.f, 150.f, 100.f));  // starts at x=0
    
    EXPECT_TRUE(handler.IsOverflow());  // Left boundary exceeded
}

/**
 * @tc.name: VerticalOverflowHandlerOverflowDisabledFlagTest
 * @tc.desc: Test the new overflow disabled flag getter
 * @tc.type: FUNC
 */
HWTEST_F(OverflowTestNg, VerticalOverflowHandlerOverflowDisabledFlagTest, TestSize.Level0)
{
    VerticalOverflowHandler handler;
    
    // Initially should not be disabled
    EXPECT_FALSE(handler.IsOverflowDisabled());
    
    // Set disabled flag
    handler.SetOverflowDisabledFlag(true);
    EXPECT_TRUE(handler.IsOverflowDisabled());
    
    // Set enabled flag
    handler.SetOverflowDisabledFlag(false);
    EXPECT_FALSE(handler.IsOverflowDisabled());
}
} // namespace OHOS::Ace::NG