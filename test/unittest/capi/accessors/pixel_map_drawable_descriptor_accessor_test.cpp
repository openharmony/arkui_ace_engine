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

#include <gmock/gmock.h>

#include "accessor_test_base.h"
#include "accessor_test_fixtures.h"

#include "core/interfaces/native/implementation/animated_drawable_descriptor_peer.h"
#include "core/interfaces/native/implementation/drawable_descriptor_peer.h"
#include "core/interfaces/native/implementation/layered_drawable_descriptor_peer.h"
#include "core/interfaces/native/implementation/pixel_map_drawable_descriptor_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace AccessorTestFixtures;
using namespace Converter;

class PixelMapDrawableDescriptorAccessorTest
    : public AccessorTestCtorBase<GENERATED_ArkUIPixelMapDrawableDescriptorAccessor,
          &GENERATED_ArkUIAccessors::getPixelMapDrawableDescriptorAccessor, PixelMapDrawableDescriptorPeer> {
public:
    void* CreatePeerInstance() override
    {
        return accessor_->ctor(nullptr);
    }
    RefPtr<PixelMap> CreatePixelMap(std::string& src);
};

RefPtr<PixelMap> PixelMapDrawableDescriptorAccessorTest::CreatePixelMap(std::string& src)
{
    void* ptr = reinterpret_cast<void*>(src.data());
    return PixelMap::CreatePixelMap(ptr);
}

/**
 * @tc.name: ctorTestDefault
 * @tc.desc: Check the functionality of ctor
 * @tc.type: FUNC
 */
HWTEST_F(PixelMapDrawableDescriptorAccessorTest, ctorTestDefault, TestSize.Level1)
{
    EXPECT_FALSE(peer_->GetPixelMap());
}

/**
 * @tc.name: ctorTest
 * @tc.desc: Check the functionality of ctor
 * @tc.type: FUNC
 */
HWTEST_F(PixelMapDrawableDescriptorAccessorTest, ctorTest, TestSize.Level1)
{
    std::string imagesSrc = "test";
    auto pixelMap = CreatePixelMap(imagesSrc);
    auto pixelMapPeer = PixelMapPeer::Create(pixelMap);
    auto optPixelMapPeer = ArkValue<Opt_PixelMap>(pixelMapPeer);
    auto pixelMapDrawableDescriptor = accessor_->ctor(&optPixelMapPeer);
    ASSERT_TRUE(pixelMapDrawableDescriptor);
    EXPECT_EQ(pixelMapDrawableDescriptor->GetPixelMap(), pixelMap);
}
} // namespace OHOS::Ace::NG
