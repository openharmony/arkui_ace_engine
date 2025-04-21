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

class DrawableDescriptorAccessorTest
    : public AccessorTestBase<GENERATED_ArkUIDrawableDescriptorAccessor,
          &GENERATED_ArkUIAccessors::getDrawableDescriptorAccessor, DrawableDescriptorPeer> {
public:
    RefPtr<PixelMap> CreatePixelMap(std::string& src);
};

RefPtr<PixelMap> DrawableDescriptorAccessorTest::CreatePixelMap(std::string& src)
{
    void* ptr = reinterpret_cast<void*>(src.data());
    return PixelMap::CreatePixelMap(ptr);
}

/**
 * @tc.name: ctorTest
 * @tc.desc: Check the functionality of ctor
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorAccessorTest, ctorTest, TestSize.Level1)
{
    EXPECT_FALSE(peer_->HasPixelMap());
}

/**
 * @tc.name: getPixelMapTest
 * @tc.desc: Check the functionality of getPixelMap
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorAccessorTest, getPixelMapTest, TestSize.Level1)
{
    auto checkGetPixelMap = [](DrawableDescriptorPeer* peer, PixelMapPtr pixelMap, bool isEmpty) {
        auto pixelMapPeer = accessor_->getPixelMap(peer);
        ASSERT_TRUE(pixelMapPeer);
        if (isEmpty) {
            EXPECT_FALSE(pixelMapPeer->pixelMap);
        } else {
            ASSERT_TRUE(pixelMapPeer->pixelMap);
        }
    };

    // DrawableDescriptorPeer
    checkGetPixelMap(peer_, nullptr, true);

    // LayeredDrawablePeer
    std::string imagesSrc = "test";
    auto foregroundPixelMap = CreatePixelMap(imagesSrc);
    auto backgroundPixelMap = CreatePixelMap(imagesSrc);
    auto maskPixelMap = CreatePixelMap(imagesSrc);
    auto layeredPeer =
        PeerUtils::CreatePeer<LayeredDrawableDescriptorPeer>(foregroundPixelMap, backgroundPixelMap, maskPixelMap);
    checkGetPixelMap(layeredPeer, nullptr, true);
    PeerUtils::DestroyPeer(layeredPeer);

    // AnimatedDrawableDescriptorPeer
    const vector<RefPtr<PixelMap>> pixelMapArray = { foregroundPixelMap, backgroundPixelMap, maskPixelMap };
    auto animatedPeer =
        PeerUtils::CreatePeer<AnimatedDrawableDescriptorPeer>(pixelMapArray, std::nullopt, std::nullopt);
    checkGetPixelMap(animatedPeer, foregroundPixelMap, false);
    PeerUtils::DestroyPeer(animatedPeer);

    // PixelMapDrawableDescriptorPeer
    auto pixelMapPeer = PeerUtils::CreatePeer<PixelMapDrawableDescriptorPeer>();
    checkGetPixelMap(pixelMapPeer, nullptr, true);
    pixelMapPeer->SetPixelMap(foregroundPixelMap);
    checkGetPixelMap(pixelMapPeer, foregroundPixelMap, false);
    PeerUtils::DestroyPeer(pixelMapPeer);
}
} // namespace OHOS::Ace::NG
