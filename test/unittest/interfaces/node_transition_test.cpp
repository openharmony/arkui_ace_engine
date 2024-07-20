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

#include "animate_impl.h"
#include "event_converter.h"
#include "gtest/gtest.h"
#include "native_animate.h"
#include "native_interface.h"
#include "native_node.h"
#include "node_transition.h"

using namespace testing;
using namespace testing::ext;

class NodeTransitionTest : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: NodeTransitionTest001
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest001, TestSize.Level1)
{
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(option, nullptr);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest002
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest002, TestSize.Level1)
{
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(option, nullptr);
    ArkUI_TransitionEffect* combine = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(combine, nullptr);
    OH_ArkUI_TransitionEffect_Combine(option, combine);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    OH_ArkUI_TransitionEffect_Dispose(combine);
    combine = nullptr;
    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest003
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest003, TestSize.Level1)
{
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(option, nullptr);
    ArkUI_TransitionEffect* combine = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(combine, nullptr);
    OH_ArkUI_TransitionEffect_Combine(option, combine);

    ArkUI_AnimateOption* animation = OH_ArkUI_AnimateOption_Create();
    ASSERT_NE(animation, nullptr);
    OH_ArkUI_TransitionEffect_SetAnimation(option, animation);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    OH_ArkUI_AnimateOption_Dispose(animation);
    animation = nullptr;
    OH_ArkUI_TransitionEffect_Dispose(combine);
    combine = nullptr;
    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest004
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest004, TestSize.Level1)
{
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(option, nullptr);

    ArkUI_AnimateOption* animation = OH_ArkUI_AnimateOption_Create();
    ASSERT_NE(animation, nullptr);
    OH_ArkUI_TransitionEffect_SetAnimation(option, animation);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    OH_ArkUI_AnimateOption_Dispose(animation);
    animation = nullptr;
    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest005
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest005, TestSize.Level1)
{
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(option, nullptr);

    ArkUI_AnimateOption* animation = OH_ArkUI_AnimateOption_Create();
    ASSERT_NE(animation, nullptr);
    ArkUI_ExpectedFrameRateRange expectedFrameRateRange = {0, 0, 0};
    OH_ArkUI_AnimateOption_SetExpectedFrameRateRange(animation, &expectedFrameRateRange);

    OH_ArkUI_TransitionEffect_SetAnimation(option, animation);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    OH_ArkUI_AnimateOption_Dispose(animation);
    animation = nullptr;
    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest006
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest006, TestSize.Level1)
{
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(option, nullptr);
    ArkUI_TransitionEffect* combine = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(combine, nullptr);
    OH_ArkUI_TransitionEffect_Combine(option, combine);

    ArkUI_AnimateOption* animation = OH_ArkUI_AnimateOption_Create();
    ASSERT_NE(animation, nullptr);
    ArkUI_ExpectedFrameRateRange expectedFrameRateRange = {0, 0, 0};
    OH_ArkUI_AnimateOption_SetExpectedFrameRateRange(animation, &expectedFrameRateRange);

    OH_ArkUI_TransitionEffect_SetAnimation(option, animation);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    OH_ArkUI_AnimateOption_Dispose(animation);
    animation = nullptr;
    OH_ArkUI_TransitionEffect_Dispose(combine);
    combine = nullptr;
    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest007
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest007, TestSize.Level1)
{
    ArkUI_TranslationOptions translationOptions = {0.0f, 0.0f, 0.0f};
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateTranslationTransitionEffect(&translationOptions);
    ASSERT_NE(option, nullptr);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest008
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest008, TestSize.Level1)
{
    ArkUI_TranslationOptions translationOptions = {0.0f, 0.0f, 0.0f};
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateTranslationTransitionEffect(&translationOptions);
    ASSERT_NE(option, nullptr);
    ArkUI_TransitionEffect* combine = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(combine, nullptr);
    OH_ArkUI_TransitionEffect_Combine(option, combine);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    OH_ArkUI_TransitionEffect_Dispose(combine);
    combine = nullptr;
    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest009
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest009, TestSize.Level1)
{
    ArkUI_TranslationOptions translationOptions = {0.0f, 0.0f, 0.0f};
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateTranslationTransitionEffect(&translationOptions);
    ASSERT_NE(option, nullptr);
    ArkUI_TransitionEffect* combine = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(combine, nullptr);
    OH_ArkUI_TransitionEffect_Combine(option, combine);

    ArkUI_AnimateOption* animation = OH_ArkUI_AnimateOption_Create();
    ASSERT_NE(animation, nullptr);
    OH_ArkUI_TransitionEffect_SetAnimation(option, animation);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    OH_ArkUI_AnimateOption_Dispose(animation);
    animation = nullptr;
    OH_ArkUI_TransitionEffect_Dispose(combine);
    combine = nullptr;
    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest010
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest010, TestSize.Level1)
{
    ArkUI_TranslationOptions translationOptions = {0.0f, 0.0f, 0.0f};
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateTranslationTransitionEffect(&translationOptions);
    ASSERT_NE(option, nullptr);

    ArkUI_AnimateOption* animation = OH_ArkUI_AnimateOption_Create();
    ASSERT_NE(animation, nullptr);
    OH_ArkUI_TransitionEffect_SetAnimation(option, animation);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    OH_ArkUI_AnimateOption_Dispose(animation);
    animation = nullptr;
    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest011
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest011, TestSize.Level1)
{
    ArkUI_TranslationOptions translationOptions = {0.0f, 0.0f, 0.0f};
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateTranslationTransitionEffect(&translationOptions);
    ASSERT_NE(option, nullptr);

    ArkUI_AnimateOption* animation = OH_ArkUI_AnimateOption_Create();
    ASSERT_NE(animation, nullptr);
    ArkUI_ExpectedFrameRateRange expectedFrameRateRange = {0, 0, 0};
    OH_ArkUI_AnimateOption_SetExpectedFrameRateRange(animation, &expectedFrameRateRange);

    OH_ArkUI_TransitionEffect_SetAnimation(option, animation);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    OH_ArkUI_AnimateOption_Dispose(animation);
    animation = nullptr;
    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest012
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest012, TestSize.Level1)
{
    ArkUI_TranslationOptions translationOptions = {0.0f, 0.0f, 0.0f};
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateTranslationTransitionEffect(&translationOptions);
    ASSERT_NE(option, nullptr);
    ArkUI_TransitionEffect* combine = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(combine, nullptr);
    OH_ArkUI_TransitionEffect_Combine(option, combine);

    ArkUI_AnimateOption* animation = OH_ArkUI_AnimateOption_Create();
    ASSERT_NE(animation, nullptr);
    ArkUI_ExpectedFrameRateRange expectedFrameRateRange = {0, 0, 0};
    OH_ArkUI_AnimateOption_SetExpectedFrameRateRange(animation, &expectedFrameRateRange);

    OH_ArkUI_TransitionEffect_SetAnimation(option, animation);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    OH_ArkUI_AnimateOption_Dispose(animation);
    animation = nullptr;
    OH_ArkUI_TransitionEffect_Dispose(combine);
    combine = nullptr;
    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest013
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest013, TestSize.Level1)
{
    ArkUI_ScaleOptions scaleOptions = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateScaleTransitionEffect(&scaleOptions);
    ASSERT_NE(option, nullptr);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest014
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest014, TestSize.Level1)
{
    ArkUI_ScaleOptions scaleOptions = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateScaleTransitionEffect(&scaleOptions);
    ASSERT_NE(option, nullptr);
    ArkUI_TransitionEffect* combine = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(combine, nullptr);
    OH_ArkUI_TransitionEffect_Combine(option, combine);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    OH_ArkUI_TransitionEffect_Dispose(combine);
    combine = nullptr;
    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest015
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest015, TestSize.Level1)
{
    ArkUI_ScaleOptions scaleOptions = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateScaleTransitionEffect(&scaleOptions);
    ASSERT_NE(option, nullptr);
    ArkUI_TransitionEffect* combine = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(combine, nullptr);
    OH_ArkUI_TransitionEffect_Combine(option, combine);

    ArkUI_AnimateOption* animation = OH_ArkUI_AnimateOption_Create();
    ASSERT_NE(animation, nullptr);
    OH_ArkUI_TransitionEffect_SetAnimation(option, animation);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    OH_ArkUI_AnimateOption_Dispose(animation);
    animation = nullptr;
    OH_ArkUI_TransitionEffect_Dispose(combine);
    combine = nullptr;
    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest016
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest016, TestSize.Level1)
{
    ArkUI_ScaleOptions scaleOptions = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateScaleTransitionEffect(&scaleOptions);
    ASSERT_NE(option, nullptr);

    ArkUI_AnimateOption* animation = OH_ArkUI_AnimateOption_Create();
    ASSERT_NE(animation, nullptr);
    OH_ArkUI_TransitionEffect_SetAnimation(option, animation);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    OH_ArkUI_AnimateOption_Dispose(animation);
    animation = nullptr;
    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest017
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest017, TestSize.Level1)
{
    ArkUI_ScaleOptions scaleOptions = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateScaleTransitionEffect(&scaleOptions);
    ASSERT_NE(option, nullptr);

    ArkUI_AnimateOption* animation = OH_ArkUI_AnimateOption_Create();
    ASSERT_NE(animation, nullptr);
    ArkUI_ExpectedFrameRateRange expectedFrameRateRange = {0, 0, 0};
    OH_ArkUI_AnimateOption_SetExpectedFrameRateRange(animation, &expectedFrameRateRange);

    OH_ArkUI_TransitionEffect_SetAnimation(option, animation);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    OH_ArkUI_AnimateOption_Dispose(animation);
    animation = nullptr;
    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest018
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest018, TestSize.Level1)
{
    ArkUI_ScaleOptions scaleOptions = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateScaleTransitionEffect(&scaleOptions);
    ASSERT_NE(option, nullptr);
    ArkUI_TransitionEffect* combine = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(combine, nullptr);
    OH_ArkUI_TransitionEffect_Combine(option, combine);

    ArkUI_AnimateOption* animation = OH_ArkUI_AnimateOption_Create();
    ASSERT_NE(animation, nullptr);
    ArkUI_ExpectedFrameRateRange expectedFrameRateRange = {0, 0, 0};
    OH_ArkUI_AnimateOption_SetExpectedFrameRateRange(animation, &expectedFrameRateRange);

    OH_ArkUI_TransitionEffect_SetAnimation(option, animation);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    OH_ArkUI_AnimateOption_Dispose(animation);
    animation = nullptr;
    OH_ArkUI_TransitionEffect_Dispose(combine);
    combine = nullptr;
    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest019
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest019, TestSize.Level1)
{
    ArkUI_RotationOptions rotationOptions = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateRotationTransitionEffect(&rotationOptions);
    ASSERT_NE(option, nullptr);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest020
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest020, TestSize.Level1)
{
    ArkUI_RotationOptions rotationOptions = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateRotationTransitionEffect(&rotationOptions);
    ASSERT_NE(option, nullptr);
    ArkUI_TransitionEffect* combine = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(combine, nullptr);
    OH_ArkUI_TransitionEffect_Combine(option, combine);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    OH_ArkUI_TransitionEffect_Dispose(combine);
    combine = nullptr;
    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest021
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest021, TestSize.Level1)
{
    ArkUI_RotationOptions rotationOptions = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateRotationTransitionEffect(&rotationOptions);
    ASSERT_NE(option, nullptr);
    ArkUI_TransitionEffect* combine = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(combine, nullptr);
    OH_ArkUI_TransitionEffect_Combine(option, combine);

    ArkUI_AnimateOption* animation = OH_ArkUI_AnimateOption_Create();
    ASSERT_NE(animation, nullptr);
    OH_ArkUI_TransitionEffect_SetAnimation(option, animation);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    OH_ArkUI_AnimateOption_Dispose(animation);
    animation = nullptr;
    OH_ArkUI_TransitionEffect_Dispose(combine);
    combine = nullptr;
    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest022
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest022, TestSize.Level1)
{
    ArkUI_RotationOptions rotationOptions = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateRotationTransitionEffect(&rotationOptions);
    ASSERT_NE(option, nullptr);

    ArkUI_AnimateOption* animation = OH_ArkUI_AnimateOption_Create();
    ASSERT_NE(animation, nullptr);
    OH_ArkUI_TransitionEffect_SetAnimation(option, animation);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    OH_ArkUI_AnimateOption_Dispose(animation);
    animation = nullptr;
    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest023
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest023, TestSize.Level1)
{
    ArkUI_RotationOptions rotationOptions = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateRotationTransitionEffect(&rotationOptions);
    ASSERT_NE(option, nullptr);

    ArkUI_AnimateOption* animation = OH_ArkUI_AnimateOption_Create();
    ASSERT_NE(animation, nullptr);
    ArkUI_ExpectedFrameRateRange expectedFrameRateRange = {0, 0, 0};
    OH_ArkUI_AnimateOption_SetExpectedFrameRateRange(animation, &expectedFrameRateRange);

    OH_ArkUI_TransitionEffect_SetAnimation(option, animation);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    OH_ArkUI_AnimateOption_Dispose(animation);
    animation = nullptr;
    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest024
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest024, TestSize.Level1)
{
    ArkUI_RotationOptions rotationOptions = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateRotationTransitionEffect(&rotationOptions);
    ASSERT_NE(option, nullptr);
    ArkUI_TransitionEffect* combine = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(combine, nullptr);
    OH_ArkUI_TransitionEffect_Combine(option, combine);

    ArkUI_AnimateOption* animation = OH_ArkUI_AnimateOption_Create();
    ASSERT_NE(animation, nullptr);
    ArkUI_ExpectedFrameRateRange expectedFrameRateRange = {0, 0, 0};
    OH_ArkUI_AnimateOption_SetExpectedFrameRateRange(animation, &expectedFrameRateRange);

    OH_ArkUI_TransitionEffect_SetAnimation(option, animation);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    OH_ArkUI_AnimateOption_Dispose(animation);
    animation = nullptr;
    OH_ArkUI_TransitionEffect_Dispose(combine);
    combine = nullptr;
    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest025
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest025, TestSize.Level1)
{
    ArkUI_TransitionEffect* option =
        OH_ArkUI_CreateMovementTransitionEffect(ArkUI_TransitionEdge::ARKUI_TRANSITION_EDGE_START);
    ASSERT_NE(option, nullptr);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest026
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest026, TestSize.Level1)
{
    ArkUI_TransitionEffect* option =
        OH_ArkUI_CreateMovementTransitionEffect(ArkUI_TransitionEdge::ARKUI_TRANSITION_EDGE_START);
    ASSERT_NE(option, nullptr);
    ArkUI_TransitionEffect* combine = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(combine, nullptr);
    OH_ArkUI_TransitionEffect_Combine(option, combine);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    OH_ArkUI_TransitionEffect_Dispose(combine);
    combine = nullptr;
    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest027
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest027, TestSize.Level1)
{
    ArkUI_TransitionEffect* option =
        OH_ArkUI_CreateMovementTransitionEffect(ArkUI_TransitionEdge::ARKUI_TRANSITION_EDGE_START);
    ASSERT_NE(option, nullptr);
    ArkUI_TransitionEffect* combine = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(combine, nullptr);
    OH_ArkUI_TransitionEffect_Combine(option, combine);

    ArkUI_AnimateOption* animation = OH_ArkUI_AnimateOption_Create();
    ASSERT_NE(animation, nullptr);
    OH_ArkUI_TransitionEffect_SetAnimation(option, animation);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    OH_ArkUI_AnimateOption_Dispose(animation);
    animation = nullptr;
    OH_ArkUI_TransitionEffect_Dispose(combine);
    combine = nullptr;
    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest028
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest028, TestSize.Level1)
{
    ArkUI_TransitionEffect* option =
        OH_ArkUI_CreateMovementTransitionEffect(ArkUI_TransitionEdge::ARKUI_TRANSITION_EDGE_START);
    ASSERT_NE(option, nullptr);

    ArkUI_AnimateOption* animation = OH_ArkUI_AnimateOption_Create();
    ASSERT_NE(animation, nullptr);
    OH_ArkUI_TransitionEffect_SetAnimation(option, animation);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    OH_ArkUI_AnimateOption_Dispose(animation);
    animation = nullptr;
    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest029
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest029, TestSize.Level1)
{
    ArkUI_TransitionEffect* option =
        OH_ArkUI_CreateMovementTransitionEffect(ArkUI_TransitionEdge::ARKUI_TRANSITION_EDGE_START);
    ASSERT_NE(option, nullptr);

    ArkUI_AnimateOption* animation = OH_ArkUI_AnimateOption_Create();
    ASSERT_NE(animation, nullptr);
    ArkUI_ExpectedFrameRateRange expectedFrameRateRange = {0, 0, 0};
    OH_ArkUI_AnimateOption_SetExpectedFrameRateRange(animation, &expectedFrameRateRange);

    OH_ArkUI_TransitionEffect_SetAnimation(option, animation);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    OH_ArkUI_AnimateOption_Dispose(animation);
    animation = nullptr;
    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest030
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest030, TestSize.Level1)
{
    ArkUI_TransitionEffect* option =
        OH_ArkUI_CreateMovementTransitionEffect(ArkUI_TransitionEdge::ARKUI_TRANSITION_EDGE_START);
    ASSERT_NE(option, nullptr);
    ArkUI_TransitionEffect* combine = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(combine, nullptr);
    OH_ArkUI_TransitionEffect_Combine(option, combine);

    ArkUI_AnimateOption* animation = OH_ArkUI_AnimateOption_Create();
    ASSERT_NE(animation, nullptr);
    ArkUI_ExpectedFrameRateRange expectedFrameRateRange = {0, 0, 0};
    OH_ArkUI_AnimateOption_SetExpectedFrameRateRange(animation, &expectedFrameRateRange);

    OH_ArkUI_TransitionEffect_SetAnimation(option, animation);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    OH_ArkUI_AnimateOption_Dispose(animation);
    animation = nullptr;
    OH_ArkUI_TransitionEffect_Dispose(combine);
    combine = nullptr;
    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest031
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest031, TestSize.Level1)
{
    ArkUI_TransitionEffect* appear = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(appear, nullptr);
    ArkUI_TransitionEffect* disappear = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(disappear, nullptr);
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateAsymmetricTransitionEffect(appear, disappear);
    ASSERT_NE(option, nullptr);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
    OH_ArkUI_TransitionEffect_Dispose(appear);
    appear = nullptr;
    OH_ArkUI_TransitionEffect_Dispose(disappear);
    disappear = nullptr;
}

/**
 * @tc.name: NodeTransitionTest032
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest032, TestSize.Level1)
{
    ArkUI_TransitionEffect* appear = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(appear, nullptr);
    ArkUI_TransitionEffect* disappear = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(disappear, nullptr);
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateAsymmetricTransitionEffect(appear, disappear);
    ASSERT_NE(option, nullptr);
    ArkUI_TransitionEffect* combine = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(combine, nullptr);
    OH_ArkUI_TransitionEffect_Combine(option, combine);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    OH_ArkUI_TransitionEffect_Dispose(combine);
    combine = nullptr;
    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
    OH_ArkUI_TransitionEffect_Dispose(appear);
    appear = nullptr;
    OH_ArkUI_TransitionEffect_Dispose(disappear);
    disappear = nullptr;
}

/**
 * @tc.name: NodeTransitionTest033
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest033, TestSize.Level1)
{
    ArkUI_TransitionEffect* appear = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(appear, nullptr);
    ArkUI_TransitionEffect* disappear = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(disappear, nullptr);
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateAsymmetricTransitionEffect(appear, disappear);
    ASSERT_NE(option, nullptr);
    ArkUI_TransitionEffect* combine = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(combine, nullptr);
    OH_ArkUI_TransitionEffect_Combine(option, combine);

    ArkUI_AnimateOption* animation = OH_ArkUI_AnimateOption_Create();
    ASSERT_NE(animation, nullptr);
    OH_ArkUI_TransitionEffect_SetAnimation(option, animation);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    OH_ArkUI_AnimateOption_Dispose(animation);
    animation = nullptr;
    OH_ArkUI_TransitionEffect_Dispose(combine);
    combine = nullptr;
    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
    OH_ArkUI_TransitionEffect_Dispose(appear);
    appear = nullptr;
    OH_ArkUI_TransitionEffect_Dispose(disappear);
    disappear = nullptr;
}

/**
 * @tc.name: NodeTransitionTest034
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest034, TestSize.Level1)
{
    ArkUI_TransitionEffect* appear = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(appear, nullptr);
    ArkUI_TransitionEffect* disappear = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(disappear, nullptr);
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateAsymmetricTransitionEffect(appear, disappear);
    ASSERT_NE(option, nullptr);

    ArkUI_AnimateOption* animation = OH_ArkUI_AnimateOption_Create();
    ASSERT_NE(animation, nullptr);
    OH_ArkUI_TransitionEffect_SetAnimation(option, animation);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    OH_ArkUI_AnimateOption_Dispose(animation);
    animation = nullptr;
    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
    OH_ArkUI_TransitionEffect_Dispose(appear);
    appear = nullptr;
    OH_ArkUI_TransitionEffect_Dispose(disappear);
    disappear = nullptr;
}

/**
 * @tc.name: NodeTransitionTest035
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest035, TestSize.Level1)
{
    ArkUI_TransitionEffect* appear = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(appear, nullptr);
    ArkUI_TransitionEffect* disappear = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(disappear, nullptr);
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateAsymmetricTransitionEffect(appear, disappear);
    ASSERT_NE(option, nullptr);

    ArkUI_AnimateOption* animation = OH_ArkUI_AnimateOption_Create();
    ASSERT_NE(animation, nullptr);
    ArkUI_ExpectedFrameRateRange expectedFrameRateRange = {0, 0, 0};
    OH_ArkUI_AnimateOption_SetExpectedFrameRateRange(animation, &expectedFrameRateRange);

    OH_ArkUI_TransitionEffect_SetAnimation(option, animation);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    OH_ArkUI_AnimateOption_Dispose(animation);
    animation = nullptr;
    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
    OH_ArkUI_TransitionEffect_Dispose(appear);
    appear = nullptr;
    OH_ArkUI_TransitionEffect_Dispose(disappear);
    disappear = nullptr;
}

/**
 * @tc.name: NodeTransitionTest036
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest036, TestSize.Level1)
{
    ArkUI_TransitionEffect* appear = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(appear, nullptr);
    ArkUI_TransitionEffect* disappear = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(disappear, nullptr);
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateAsymmetricTransitionEffect(appear, disappear);
    ASSERT_NE(option, nullptr);
    ArkUI_TransitionEffect* combine = OH_ArkUI_CreateOpacityTransitionEffect(0.0f);
    ASSERT_NE(combine, nullptr);
    OH_ArkUI_TransitionEffect_Combine(option, combine);

    ArkUI_AnimateOption* animation = OH_ArkUI_AnimateOption_Create();
    ASSERT_NE(animation, nullptr);
    ArkUI_ExpectedFrameRateRange expectedFrameRateRange = {0, 0, 0};
    OH_ArkUI_AnimateOption_SetExpectedFrameRateRange(animation, &expectedFrameRateRange);

    OH_ArkUI_TransitionEffect_SetAnimation(option, animation);
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_NE(toEffectOption, nullptr);

    OH_ArkUI_AnimateOption_Dispose(animation);
    animation = nullptr;
    OH_ArkUI_TransitionEffect_Dispose(combine);
    combine = nullptr;
    option->toEffectOption = toEffectOption;
    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
    OH_ArkUI_TransitionEffect_Dispose(appear);
    appear = nullptr;
    OH_ArkUI_TransitionEffect_Dispose(disappear);
    disappear = nullptr;
}

/**
 * @tc.name: NodeTransitionTest037
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest037, TestSize.Level1)
{
    ArkUI_TranslationOptions translationOptions = {0.0f, 0.0f, 0.0f};
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateTranslationTransitionEffect(&translationOptions);
    ASSERT_NE(option, nullptr);
    option->translate = nullptr;
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_EQ(toEffectOption, nullptr);

    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest038
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest038, TestSize.Level1)
{
    ArkUI_ScaleOptions scaleOptions = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateScaleTransitionEffect(&scaleOptions);
    ASSERT_NE(option, nullptr);
    option->scale = nullptr;
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_EQ(toEffectOption, nullptr);

    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}

/**
 * @tc.name: NodeTransitionTest039
 * @tc.desc: Test ConvertToEffectOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeTransitionTest, NodeTransitionTest039, TestSize.Level1)
{
    ArkUI_RotationOptions rotationOptions = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    ArkUI_TransitionEffect* option = OH_ArkUI_CreateRotationTransitionEffect(&rotationOptions);
    ASSERT_NE(option, nullptr);
    option->rotate = nullptr;
    ArkUITransitionEffectOption* toEffectOption = OHOS::Ace::TransitionModel::ConvertToEffectOption(option);
    ASSERT_EQ(toEffectOption, nullptr);

    OH_ArkUI_TransitionEffect_Dispose(option);
    option = nullptr;
}