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

#include "accessor_test_base.h"
#include "core/interfaces/native/implementation/x_component_controller_peer_impl.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "gmock/gmock.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class XComponentControllerNativeAccessorTest
    : public AccessorTestBase<GENERATED_ArkUIXComponentControllerNativeAccessor,
    &GENERATED_ArkUIAccessors::getXComponentControllerNativeAccessor, XComponentControllerNativePeer> {
};

/**
 * @tc.name: getXComponentSurfaceIdTest
 * @tc.desc: Verify getXComponentSurfaceId accessor function pointer is not null and call doesn't crash
 * @tc.type: FUNC
 */
HWTEST_F(XComponentControllerNativeAccessorTest, getXComponentSurfaceIdTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getXComponentSurfaceId, nullptr);
    auto result = accessor_->getXComponentSurfaceId(peer_);
    // The result is a valid Ark_String (may be empty but should not crash)
    ASSERT_NE(result.chars, nullptr);
}

/**
 * @tc.name: getXComponentSurfaceRectTest
 * @tc.desc: Verify getXComponentSurfaceRect accessor function pointer is not null and call doesn't crash
 * @tc.type: FUNC
 */
HWTEST_F(XComponentControllerNativeAccessorTest, getXComponentSurfaceRectTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getXComponentSurfaceRect, nullptr);
    auto result = accessor_->getXComponentSurfaceRect(peer_);
    // The result is a valid Ark_SurfaceRect with default values
    EXPECT_EQ(result.x, 0);
    EXPECT_EQ(result.y, 0);
    EXPECT_EQ(result.width, 0);
    EXPECT_EQ(result.height, 0);
}

} // namespace OHOS::Ace::NG
