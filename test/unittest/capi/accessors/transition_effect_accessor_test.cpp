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
    void *CreatePeerInstance() override
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
HWTEST_F(TransitionEffectAccessorTest, getRotateTest, TestSize.Level1)
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

    auto ptr = accessor_->rotate(&value);
    auto peer = reinterpret_cast<TransitionEffectPeer*>(ptr);
    ASSERT_NE(peer, nullptr);

    auto effect = AceType::DynamicCast<ChainedRotateEffect>(peer->handler);
    CHECK_NULL_VOID(effect);
    ASSERT_EQ(effect->GetEffect().xDirection, 2);
    ASSERT_EQ(effect->GetEffect().yDirection, 3);
    ASSERT_EQ(effect->GetEffect().zDirection, 4);
    ASSERT_EQ(effect->GetEffect().centerX.ToString(), "3.00vp");
    ASSERT_EQ(effect->GetEffect().centerY.ToString(), "3.00vp");
    ASSERT_EQ(effect->GetEffect().centerZ.ToString(), "3.00vp");
    ASSERT_EQ(effect->GetEffect().perspective, 6);
    ASSERT_EQ(effect->GetEffect().angle, 45);

    ptr = accessor_->rotate(nullptr);
    peer = reinterpret_cast<TransitionEffectPeer*>(ptr);
    ASSERT_EQ(peer, nullptr);
}

/**
 * @tc.name: getTranslateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TransitionEffectAccessorTest, getTranslateTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->translate, nullptr);
    Ark_TranslateOptions value;
    value.x = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(2);
    value.y = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(3);
    value.z = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(4);
    auto ptr = accessor_->translate(&value);
    auto peer = reinterpret_cast<TransitionEffectPeer*>(ptr);
    ASSERT_NE(peer, nullptr);

    auto effect = AceType::DynamicCast<ChainedTranslateEffect>(peer->handler);
    CHECK_NULL_VOID(effect);
    ASSERT_EQ(effect->GetEffect().x.ToString(), "2.00vp");
    ASSERT_EQ(effect->GetEffect().y.ToString(), "3.00vp");
    ASSERT_EQ(effect->GetEffect().z.ToString(), "4.00vp");

    ptr = accessor_->translate(nullptr);
    peer = reinterpret_cast<TransitionEffectPeer*>(ptr);
    ASSERT_EQ(peer, nullptr);
}

/**
 * @tc.name: getScaleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TransitionEffectAccessorTest, getScaleTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->scale, nullptr);
    Ark_ScaleOptions value;
    value.x = Converter::ArkValue<Opt_Number>(2);
    value.y = Converter::ArkValue<Opt_Number>(3);
    value.z = Converter::ArkValue<Opt_Number>(4);
    value.centerX = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(3);
    value.centerY = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(3);
    auto ptr = accessor_->scale(&value);
    auto peer = reinterpret_cast<TransitionEffectPeer*>(ptr);
    ASSERT_NE(peer, nullptr);

    auto effect = AceType::DynamicCast<ChainedScaleEffect>(peer->handler);
    CHECK_NULL_VOID(effect);
    ASSERT_EQ(effect->GetEffect().xScale, 2);
    ASSERT_EQ(effect->GetEffect().yScale, 3);
    ASSERT_EQ(effect->GetEffect().zScale, 4);
    ASSERT_EQ(effect->GetEffect().centerX.ToString(), "3.00vp");
    ASSERT_EQ(effect->GetEffect().centerY.ToString(), "3.00vp");

    ptr = accessor_->scale(nullptr);
    peer = reinterpret_cast<TransitionEffectPeer*>(ptr);
    ASSERT_EQ(peer, nullptr);
}

/**
 * @tc.name: getOpacityTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TransitionEffectAccessorTest, getOpacityTest, TestSize.Level1)
{
    const int TEST_VALUE = 330;
    ASSERT_NE(accessor_->opacity, nullptr);
    Ark_Number value = Converter::ArkValue<Ark_Number>(TEST_VALUE);

    auto ptr = accessor_->opacity(&value);
    auto peer = reinterpret_cast<TransitionEffectPeer*>(ptr);
    ASSERT_NE(peer, nullptr);

    auto effect = AceType::DynamicCast<ChainedOpacityEffect>(peer->handler);
    CHECK_NULL_VOID(effect);
    ASSERT_EQ(effect->GetEffect(), TEST_VALUE);

    ptr = accessor_->opacity(nullptr);
    peer = reinterpret_cast<TransitionEffectPeer*>(ptr);
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
    Ark_TransitionEdge value = Converter::ArkValue<Ark_TransitionEdge>(NG::TransitionEdge::END);

    auto ptr = accessor_->move(value);
    auto peer = reinterpret_cast<TransitionEffectPeer*>(ptr);
    ASSERT_NE(peer, nullptr);

    auto effect = AceType::DynamicCast<ChainedMoveEffect>(peer->handler);
    CHECK_NULL_VOID(effect);
    ASSERT_EQ(effect->GetEffect(), NG::TransitionEdge::END);
}

/**
 * @tc.name: getAsymmetricTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TransitionEffectAccessorTest, getAsymmetricTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->asymmetric, nullptr);
    auto app = new(Ark_TransitionEffect);
    auto appPeer = new(TransitionEffectPeer);
    app->ptr = appPeer;
    auto disapp = new(Ark_TransitionEffect);
    auto disappPeer = new(TransitionEffectPeer);
    disapp->ptr = disappPeer;
    auto peer = accessor_->asymmetric(app, disapp);
    ASSERT_NE(peer, nullptr);
    delete disappPeer;
    delete disapp;
    delete appPeer;
    delete app;
}

/**
 * @tc.name: getAnimationTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TransitionEffectAccessorTest, getAnimationTest, TestSize.Level1)
{
    const int TEST_VALUE = 333;
    ASSERT_NE(accessor_->animation, nullptr);
    Ark_AnimateParam animParam;
    animParam.duration = Converter::ArkValue<Opt_Number>(TEST_VALUE);
    animParam.tempo =  Converter::ArkValue<Opt_Number>(0.5);
    TransitionEffectPeer peer;
    peer.handler = AceType::MakeRefPtr<ChainedOpacityEffect>(33);

    auto ptr = accessor_->animation(reinterpret_cast<TransitionEffectPeer*>(&peer), &animParam);
    auto peer2 = reinterpret_cast<TransitionEffectPeer*>(ptr);
    ASSERT_NE(peer2, nullptr);
    ASSERT_EQ(peer2->handler->GetAnimationOption()->GetDuration(), TEST_VALUE);
}

/**
 * @tc.name: getCombineTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TransitionEffectAccessorTest, getCombineTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->combine, nullptr);
    auto opacity1 = 444;
    auto opacity2 = 555;

    TransitionEffectPeer peer1;
    peer1.handler = AceType::MakeRefPtr<ChainedOpacityEffect>(opacity1);

    TransitionEffectPeer peer2;
    peer2.handler = AceType::MakeRefPtr<ChainedOpacityEffect>(opacity2);

    const Ark_TransitionEffect effect { .ptr = &peer2 };

    auto ptr = accessor_->combine(reinterpret_cast<TransitionEffectPeer*>(&peer1), &effect);
    auto ret_peer1 = reinterpret_cast<TransitionEffectPeer*>(ptr);
    ASSERT_NE(ret_peer1, nullptr);
    auto effect1 = AceType::DynamicCast<ChainedOpacityEffect>(ret_peer1->handler);
    ASSERT_EQ(effect1->GetEffect(), opacity1);

    auto effect2 = AceType::DynamicCast<ChainedOpacityEffect>(ret_peer1->handler->GetNext());
    ASSERT_EQ(effect2->GetEffect(), opacity2);

}

} // namespace OHOS::Ace::NG
