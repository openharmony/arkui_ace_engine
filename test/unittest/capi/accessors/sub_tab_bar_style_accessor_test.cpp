/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "test/unittest/capi/accessors/accessor_test_fixtures.h"

#include "core/gestures/gesture_event.h"
#include "core/interfaces/native/implementation/sub_tab_bar_style_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
namespace {
}

using namespace testing;
using namespace testing::ext;

class SubTabBarStyleAccessorTest : public AccessorTestBase<GENERATED_ArkUISubTabBarStyleAccessor,
                                  &GENERATED_ArkUIAccessors::getSubTabBarStyleAccessor, SubTabBarStylePeer> {};


using StyledIndUnionTest = Ark_Union_SubTabBarIndicatorStyle_DrawableTabBarIndicator;
;
/**
 * @tc.name: indicator1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SubTabBarStyleAccessorTest, indicator1Test, TestSize.Level1)
{
    constexpr double height = 100;
    ASSERT_NE(accessor_->Indicator1, nullptr);

    Ark_DrawableTabBarIndicator drawInd;
    drawInd.width = Converter::ArkValue<Opt_Length>(height);
    drawInd.height = Converter::ArkValue<Opt_Length>(height);
    drawInd.borderRadius = Converter::ArkValue<Opt_Length>(height);
    drawInd.marginTop = Converter::ArkValue<Opt_Length>(height);

    drawInd.drawable = Converter::ArkValue<Opt_DrawableDescriptor>(Ark_Empty());

    StyledIndUnionTest style = = Converter::ArkUnion<StyledIndUnionTest,
        Ark_DrawableTabBarIndicator>(drawInd);
    auto stylePeer = PeerUtils::CreatePeer<SubTabBarStylePeer>();
    EXPECT_EQ(stylePeer->imageInfoConfig, nullptr);

    accessor_->Indicator1(stylePeer, &style);
    EXPECT_EQ(stylePeer->imageInfoConfig, nullptr);
}
}