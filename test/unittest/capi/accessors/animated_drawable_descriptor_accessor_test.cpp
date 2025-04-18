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

namespace {
const auto DEFAULT_SIZE_TEST = 0;
const auto DEFAULT_DURATION_TEST = 0;
const auto DEFAULT_ITERATIONS_TEST = 1;
} // namespace

class AnimatedDrawableDescriptorAccessorTest
    : public AccessorTestCtorBase<GENERATED_ArkUIAnimatedDrawableDescriptorAccessor,
          &GENERATED_ArkUIAccessors::getAnimatedDrawableDescriptorAccessor, AnimatedDrawableDescriptorPeer> {
public:
    void* CreatePeerInstance() override
    {
        return accessor_->ctor(nullptr, nullptr);
    }
    RefPtr<PixelMap> CreatePixelMap(std::string& src);
};

RefPtr<PixelMap> AnimatedDrawableDescriptorAccessorTest::CreatePixelMap(std::string& src)
{
    void* ptr = reinterpret_cast<void*>(src.data());
    return PixelMap::CreatePixelMap(ptr);
}

/**
 * @tc.name: ctorTestDefault
 * @tc.desc: Check the functionality of ctor
 * @tc.type: FUNC
 */
HWTEST_F(AnimatedDrawableDescriptorAccessorTest, ctorTestDefault, TestSize.Level1)
{
    EXPECT_FALSE(peer_->GetPixelMap());
    EXPECT_EQ(peer_->GetPixelMapList().size(), DEFAULT_SIZE_TEST);
    EXPECT_EQ(peer_->GetDuration(), DEFAULT_DURATION_TEST);
    EXPECT_EQ(peer_->GetIterations(), DEFAULT_ITERATIONS_TEST);
}

/**
 * @tc.name: ctorTest
 * @tc.desc: Check the functionality of ctor
 * @tc.type: FUNC
 */
HWTEST_F(AnimatedDrawableDescriptorAccessorTest, ctorTest, TestSize.Level1)
{
    std::string imagesSrc = "test";
    auto duration = 100;
    auto iterations = 10;
    auto pixelMap1 = CreatePixelMap(imagesSrc);
    auto pixelMap2 = CreatePixelMap(imagesSrc);
    const vector<RefPtr<PixelMap>> pixelMapArray = { pixelMap1, pixelMap2 };
    auto array = ArkValue<Array_PixelMap>(pixelMapArray, Converter::FC);
    Ark_AnimationOptions animationOptions = {
        .duration = ArkValue<Opt_Number>(duration),
        .iterations = ArkValue<Opt_Number>(iterations),
    };
    auto optOptions = ArkValue<Opt_AnimationOptions>(animationOptions);
    auto animatedDrawableDescriptor = accessor_->ctor(&array, &optOptions);
    ASSERT_TRUE(animatedDrawableDescriptor);
    EXPECT_EQ(animatedDrawableDescriptor->GetDuration(), duration);
    EXPECT_EQ(animatedDrawableDescriptor->GetIterations(), iterations);
    EXPECT_EQ(animatedDrawableDescriptor->GetPixelMapList(), pixelMapArray);
}
} // namespace OHOS::Ace::NG
