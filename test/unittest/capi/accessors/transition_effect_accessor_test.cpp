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

#include "gmock/gmock.h"

#include "accessor_test_base.h"
#include "node_api.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "core/interfaces/native/implementation/transition_effect_peer_impl.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
const std::string g_message = "message";

} // namespace

class TransitionEffectAccessorTest : public AccessorTestCtorBase<GENERATED_ArkUITransitionEffectAccessor,
    &GENERATED_ArkUIAccessors::getTransitionEffectAccessor, TransitionEffectPeer> {
public:
    TransitionEffectPeer* CreatePeerInstance() override
    {
        Ark_String arkType = Converter::ArkValue<Ark_String>(g_message);
        Ark_TransitionEffects* arkEffects = new(Ark_TransitionEffects);
        return accessor_->ctor(&arkType, arkEffects);
    }
};

/**
 * @tc.name: getRotateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TransitionEffectAccessorTest, DISABLED_getRotateTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->rotate, nullptr);

    Ark_RotateOptions value;
    value.x = Converter::ArkValue<Opt_Number>(2);
    value.y = Converter::ArkValue<Opt_Number>(3);
    value.z = Converter::ArkValue<Opt_Number>(4);
    value.centerX = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(3);
    value.centerY = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(3);
    value.centerZ = Converter::ArkValue<Opt_Number>(3);
    value.perspective = Converter::ArkValue<Opt_Number>(6);
    value.angle = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(45);
    auto peer = accessor_->rotate(&value);
    ASSERT_NE(peer, nullptr);
    peer = accessor_->rotate(nullptr);
    ASSERT_EQ(peer, nullptr);
}

/**
 * @tc.name: getTranslateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TransitionEffectAccessorTest, DISABLED_getTranslateTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->translate, nullptr);
    Ark_TranslateOptions value;
    value.x = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(2);
    value.y = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(3);
    value.z = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(4);
    auto peer = accessor_->translate(&value);
    ASSERT_NE(peer, nullptr);
    peer = accessor_->translate(nullptr);
    ASSERT_EQ(peer, nullptr);
}

/**
 * @tc.name: getScaleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TransitionEffectAccessorTest, DISABLED_getScaleTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->scale, nullptr);
    Ark_ScaleOptions value;
    value.x = Converter::ArkValue<Opt_Number>(2);
    value.y = Converter::ArkValue<Opt_Number>(3);
    value.z = Converter::ArkValue<Opt_Number>(4);
    value.centerX = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(3);
    value.centerY = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(3);
    auto peer = accessor_->scale(&value);
    ASSERT_NE(peer, nullptr);
    peer = accessor_->scale(nullptr);
    ASSERT_EQ(peer, nullptr);
}

/**
 * @tc.name: getOpacityTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TransitionEffectAccessorTest, getOpacityTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->opacity, nullptr);
    Ark_Number value = Converter::ArkValue<Ark_Number>(33);
    auto peer = accessor_->opacity(&value);
    ASSERT_NE(peer, nullptr);
    peer = accessor_->opacity(nullptr);
    ASSERT_EQ(peer, nullptr);
}

/**
 * @tc.name: getMoveTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TransitionEffectAccessorTest, getMoveTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->move, nullptr);
<<<<<<< HEAD
    Ark_TransitionEdge value = Converter::ArkValue<Ark_TransitionEdge>(NG::TransitionEdge::END);
    auto peer = accessor_->move(value);
    ASSERT_NE(peer, nullptr);
=======
    Ark_TransitionEdge value = Converter::ArkValue<Ark_TransitionEdge>(NG::TransitionEdge::END);    
    // should return value
    accessor_->move(value);
>>>>>>> 80927900318 (transition effects accessors)
}

/**
 * @tc.name: getAsymmetricTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TransitionEffectAccessorTest, DISABLED_getAsymmetricTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->asymmetric, nullptr);
}

/**
 * @tc.name: getAnimationTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TransitionEffectAccessorTest, DISABLED_getAnimationTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->animation, nullptr);
}

/**
 * @tc.name: getCombineTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TransitionEffectAccessorTest, DISABLED_getCombineTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->combine, nullptr);
}

} // namespace OHOS::Ace::NG