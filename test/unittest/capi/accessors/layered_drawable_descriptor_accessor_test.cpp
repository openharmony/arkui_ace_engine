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

class LayeredDrawableDescriptorAccessorTest
    : public AccessorTestCtorBase<GENERATED_ArkUILayeredDrawableDescriptorAccessor,
          &GENERATED_ArkUIAccessors::getLayeredDrawableDescriptorAccessor, LayeredDrawableDescriptorPeer> {
public:
    void* CreatePeerInstance() override
    {
        return accessor_->ctor(nullptr, nullptr, nullptr);
    }
    RefPtr<PixelMap> CreatePixelMap(std::string& src);
};

RefPtr<PixelMap> LayeredDrawableDescriptorAccessorTest::CreatePixelMap(std::string& src)
{
    void* ptr = reinterpret_cast<void*>(src.data());
    return PixelMap::CreatePixelMap(ptr);
}

/**
 * @tc.name: ctorTestDefault
 * @tc.desc: Check the functionality of ctor
 * @tc.type: FUNC
 */
HWTEST_F(LayeredDrawableDescriptorAccessorTest, ctorTestDefault, TestSize.Level1)
{
    EXPECT_FALSE(peer_->GetPixelMap());
    auto foregroundPeer = peer_->GetForeground();
    ASSERT_TRUE(foregroundPeer);
    EXPECT_FALSE(foregroundPeer->GetPixelMap());
    auto backgroundPeer = peer_->GetBackground();
    ASSERT_TRUE(backgroundPeer);
    EXPECT_FALSE(backgroundPeer->GetPixelMap());
    auto maskPeer = peer_->GetMask();
    ASSERT_TRUE(maskPeer);
    EXPECT_FALSE(maskPeer->GetPixelMap());
}

/**
 * @tc.name: ctorTest
 * @tc.desc: Check the functionality of ctor
 * @tc.type: FUNC
 */
HWTEST_F(LayeredDrawableDescriptorAccessorTest, ctorTest, TestSize.Level1)
{
    std::string imagesSrc = "test";
    auto foregroundPixelMap = CreatePixelMap(imagesSrc);
    auto backgroundPixelMap = CreatePixelMap(imagesSrc);
    auto maskPixelMap = CreatePixelMap(imagesSrc);
    auto foregroundDesciptror = PeerUtils::CreatePeer<DrawableDescriptorPeer>(foregroundPixelMap);
    auto backgroundDesciptror = PeerUtils::CreatePeer<DrawableDescriptorPeer>(backgroundPixelMap);
    auto maskDesciptror = PeerUtils::CreatePeer<DrawableDescriptorPeer>(maskPixelMap);
    auto optForegroundDesciptror = ArkValue<Opt_DrawableDescriptor>(foregroundDesciptror);
    auto optBackgroundDesciptror = ArkValue<Opt_DrawableDescriptor>(backgroundDesciptror);
    auto optMaskDesciptror = ArkValue<Opt_DrawableDescriptor>(maskDesciptror);
    auto layeredDrawableDescriptor = accessor_->ctor(&optForegroundDesciptror,
        &optBackgroundDesciptror, &optMaskDesciptror);
    ASSERT_TRUE(layeredDrawableDescriptor);
    auto foregroundPeer = layeredDrawableDescriptor->GetForeground();
    ASSERT_TRUE(foregroundPeer);
    EXPECT_EQ(foregroundPeer->GetPixelMap(), foregroundDesciptror->GetPixelMap());
    auto backgroundPeer = layeredDrawableDescriptor->GetBackground();
    ASSERT_TRUE(backgroundPeer);
    EXPECT_EQ(backgroundPeer->GetPixelMap(), backgroundDesciptror->GetPixelMap());
    auto maskPeer = layeredDrawableDescriptor->GetMask();
    ASSERT_TRUE(maskPeer);
    EXPECT_EQ(maskPeer->GetPixelMap(), maskDesciptror->GetPixelMap());
    finalyzer_(layeredDrawableDescriptor);
    PeerUtils::DestroyPeer(foregroundDesciptror);
    PeerUtils::DestroyPeer(backgroundDesciptror);
    PeerUtils::DestroyPeer(maskDesciptror);
}

/**
 * @tc.name: getForegroundTest
 * @tc.desc: Check the functionality of getForeground
 * @tc.type: FUNC
 */
HWTEST_F(LayeredDrawableDescriptorAccessorTest, getForegroundTest, TestSize.Level1)
{
    ASSERT_TRUE(accessor_->getForeground);
    std::string imagesSrc = "test";
    auto foregroundPixelMap = CreatePixelMap(imagesSrc);
    auto empty = ArkValue<Opt_DrawableDescriptor>();
    auto foregroundDesciptor = PeerUtils::CreatePeer<DrawableDescriptorPeer>(foregroundPixelMap);
    auto optForegroundDesciptor = ArkValue<Opt_DrawableDescriptor>(foregroundDesciptor);
    auto layeredDrawableDescriptor = accessor_->ctor(&optForegroundDesciptor, &empty, &empty);
    ASSERT_TRUE(layeredDrawableDescriptor);
    auto foregroundPeer = accessor_->getForeground(layeredDrawableDescriptor);
    ASSERT_TRUE(foregroundPeer);
    EXPECT_EQ(foregroundPeer->GetPixelMap(), foregroundDesciptor->GetPixelMap());
    finalyzer_(layeredDrawableDescriptor);
    PeerUtils::DestroyPeer(foregroundDesciptor);
}

/**
 * @tc.name: getBackgroundTest
 * @tc.desc: Check the functionality of getBackground
 * @tc.type: FUNC
 */
HWTEST_F(LayeredDrawableDescriptorAccessorTest, getBackgroundTest, TestSize.Level1)
{
    ASSERT_TRUE(accessor_->getBackground);
    std::string imagesSrc = "test";
    auto backgroundPixelMap = CreatePixelMap(imagesSrc);
    auto empty = ArkValue<Opt_DrawableDescriptor>();
    auto backgroundDesciptor = PeerUtils::CreatePeer<DrawableDescriptorPeer>(backgroundPixelMap);
    auto optBackgroundDesciptror = ArkValue<Opt_DrawableDescriptor>(backgroundDesciptor);
    auto layeredDrawableDescriptor = accessor_->ctor(&empty, &optBackgroundDesciptror, &empty);
    ASSERT_TRUE(layeredDrawableDescriptor);
    auto backgroundPeer = accessor_->getBackground(layeredDrawableDescriptor);
    ASSERT_TRUE(backgroundPeer);
    EXPECT_EQ(backgroundPeer->GetPixelMap(), backgroundDesciptor->GetPixelMap());
    finalyzer_(layeredDrawableDescriptor);
    PeerUtils::DestroyPeer(backgroundDesciptor);
}

/**
 * @tc.name: getMaskTest
 * @tc.desc: Check the functionality of getMask
 * @tc.type: FUNC
 */
HWTEST_F(LayeredDrawableDescriptorAccessorTest, getMaskTest, TestSize.Level1)
{
    ASSERT_TRUE(accessor_->getMask);
    std::string imagesSrc = "test";
    auto maskPixelMap = CreatePixelMap(imagesSrc);
    auto empty = ArkValue<Opt_DrawableDescriptor>();
    auto maskDescriptor = PeerUtils::CreatePeer<DrawableDescriptorPeer>(maskPixelMap);
    auto optMaskDescriptor = ArkValue<Opt_DrawableDescriptor>(maskDescriptor);
    auto layeredDrawableDescriptor = accessor_->ctor(&empty, &empty, &optMaskDescriptor);
    ASSERT_TRUE(layeredDrawableDescriptor);
    auto maskPeer = accessor_->getMask(layeredDrawableDescriptor);
    ASSERT_TRUE(maskPeer);
    EXPECT_EQ(maskPeer->GetPixelMap(), maskDescriptor->GetPixelMap());
    finalyzer_(layeredDrawableDescriptor);
    PeerUtils::DestroyPeer(maskDescriptor);
}

/**
 * @tc.name: getMaskClipPathTest
 * @tc.desc: Check the functionality of getMaskClipPath
 * @tc.type: FUNC
 */
HWTEST_F(LayeredDrawableDescriptorAccessorTest, DISABLED_getMaskClipPathTest, TestSize.Level1)
{
    // not implemented yet
}
} // namespace OHOS::Ace::NG
