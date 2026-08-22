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

#include "gtest/gtest.h"

#define private public
#define protected public

#include "core/common/visual_effect/component_material_interaction.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
// Duplicate the constants and struct from component_material_interaction.cpp
// since they are in an anonymous namespace and not accessible from tests.

// posZ
constexpr float LIGHT_POSITION_Z_NARROW_SHORT = 80.0f;
constexpr float LIGHT_POSITION_Z_MEDIUM_SHORT = 80.0f;
constexpr float LIGHT_POSITION_Z_LARGE_SHORT = 80.0f;
constexpr float LIGHT_POSITION_Z_NARROW_MID = 80.0f;
constexpr float LIGHT_POSITION_Z_MEDIUM_MID = 80.0f;
constexpr float LIGHT_POSITION_Z_LARGE_MID = 120.0f;
constexpr float LIGHT_POSITION_Z_NARROW_TALL = 80.0f;
constexpr float LIGHT_POSITION_Z_MEDIUM_TALL = 120.0f;
constexpr float LIGHT_POSITION_Z_LARGE_TALL = 160.0f;

// intensity
constexpr float LIGHT_INTENSITY_NARROW_SHORT = 2.0f;
constexpr float LIGHT_INTENSITY_NARROW_SHORT_DARK = 1.4f;
constexpr float LIGHT_INTENSITY_MEDIUM_SHORT = 2.4f;
constexpr float LIGHT_INTENSITY_LARGE_SHORT = 1.2f;
constexpr float LIGHT_INTENSITY_NARROW_MID = 2.4f;
constexpr float LIGHT_INTENSITY_MEDIUM_MID = 3.0f;
constexpr float LIGHT_INTENSITY_LARGE_MID = 1.8f;
constexpr float LIGHT_INTENSITY_NARROW_TALL = 1.4f;
constexpr float LIGHT_INTENSITY_MEDIUM_TALL = 1.8f;
constexpr float LIGHT_INTENSITY_LARGE_TALL = 0.8f;

// color
constexpr uint32_t COLOR_NARROW_SHORT_DARK = 0x99FFFFFF;
constexpr uint32_t COLOR_SHORT = 0xBFFFFFFF;
constexpr uint32_t COLOR_MID = 0x33FFFFFF;
constexpr uint32_t COLOR_TALL = 0xE5FFFFFF;
} // namespace

class ComponentMaterialInteractionTestNg : public testing::Test {
public:
    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();
        MockContainer::SetUp();
    }
    static void TearDownTestCase()
    {
        MockContainer::TearDown();
        MockPipelineContext::TearDown();
    }
};

/**
 * @tc.name: GetLightEffectParamsBySize001
 * @tc.desc: Branch 1: width>=480 && height>=780 -> LARGE_TALL
 * @tc.type: FUNC
 */
HWTEST_F(ComponentMaterialInteractionTestNg, GetLightEffectParamsBySize001, TestSize.Level1)
{
    auto params = ControlInteractionBase::GetLightEffectParamsBySize(500.0f, 800.0f, ColorMode::LIGHT);
    EXPECT_FLOAT_EQ(params.posZ, LIGHT_POSITION_Z_LARGE_TALL);
    EXPECT_FLOAT_EQ(params.intensity, LIGHT_INTENSITY_LARGE_TALL);
    EXPECT_EQ(params.color, Color(COLOR_TALL));
}

/**
 * @tc.name: GetLightEffectParamsBySize002
 * @tc.desc: Branch 2: height<48 && width<96, LIGHT -> NARROW_SHORT LIGHT
 * @tc.type: FUNC
 */
HWTEST_F(ComponentMaterialInteractionTestNg, GetLightEffectParamsBySize002, TestSize.Level1)
{
    auto params = ControlInteractionBase::GetLightEffectParamsBySize(80.0f, 40.0f, ColorMode::LIGHT);
    EXPECT_FLOAT_EQ(params.posZ, LIGHT_POSITION_Z_NARROW_SHORT);
    EXPECT_FLOAT_EQ(params.intensity, LIGHT_INTENSITY_NARROW_SHORT);
    EXPECT_EQ(params.color, Color(COLOR_TALL));
}

/**
 * @tc.name: GetLightEffectParamsBySize003
 * @tc.desc: Branch 3: height<48 && width<96, DARK -> NARROW_SHORT DARK
 * @tc.type: FUNC
 */
HWTEST_F(ComponentMaterialInteractionTestNg, GetLightEffectParamsBySize003, TestSize.Level1)
{
    auto params = ControlInteractionBase::GetLightEffectParamsBySize(80.0f, 40.0f, ColorMode::DARK);
    EXPECT_FLOAT_EQ(params.posZ, LIGHT_POSITION_Z_NARROW_SHORT);
    EXPECT_FLOAT_EQ(params.intensity, LIGHT_INTENSITY_NARROW_SHORT_DARK);
    EXPECT_EQ(params.color, Color(COLOR_NARROW_SHORT_DARK));
}

/**
 * @tc.name: GetLightEffectParamsBySize004
 * @tc.desc: Branch 4: height<48 && 96<=width<360 -> MEDIUM_SHORT
 * @tc.type: FUNC
 */
HWTEST_F(ComponentMaterialInteractionTestNg, GetLightEffectParamsBySize004, TestSize.Level1)
{
    auto params = ControlInteractionBase::GetLightEffectParamsBySize(200.0f, 40.0f, ColorMode::LIGHT);
    EXPECT_FLOAT_EQ(params.posZ, LIGHT_POSITION_Z_MEDIUM_SHORT);
    EXPECT_FLOAT_EQ(params.intensity, LIGHT_INTENSITY_MEDIUM_SHORT);
    EXPECT_EQ(params.color, Color(COLOR_SHORT));
}

/**
 * @tc.name: GetLightEffectParamsBySize005
 * @tc.desc: Branch 5: height<48 && width>=360 -> LARGE_SHORT
 * @tc.type: FUNC
 */
HWTEST_F(ComponentMaterialInteractionTestNg, GetLightEffectParamsBySize005, TestSize.Level1)
{
    auto params = ControlInteractionBase::GetLightEffectParamsBySize(400.0f, 40.0f, ColorMode::LIGHT);
    EXPECT_FLOAT_EQ(params.posZ, LIGHT_POSITION_Z_LARGE_SHORT);
    EXPECT_FLOAT_EQ(params.intensity, LIGHT_INTENSITY_LARGE_SHORT);
    EXPECT_EQ(params.color, Color(COLOR_SHORT));
}

/**
 * @tc.name: GetLightEffectParamsBySize006
 * @tc.desc: Branch 6: 48<=height<56 && width<96 -> NARROW_MID
 * @tc.type: FUNC
 */
HWTEST_F(ComponentMaterialInteractionTestNg, GetLightEffectParamsBySize006, TestSize.Level1)
{
    auto params = ControlInteractionBase::GetLightEffectParamsBySize(80.0f, 52.0f, ColorMode::LIGHT);
    EXPECT_FLOAT_EQ(params.posZ, LIGHT_POSITION_Z_NARROW_MID);
    EXPECT_FLOAT_EQ(params.intensity, LIGHT_INTENSITY_NARROW_MID);
    EXPECT_EQ(params.color, Color(COLOR_MID));
}

/**
 * @tc.name: GetLightEffectParamsBySize007
 * @tc.desc: Branch 7: 48<=height<56 && 96<=width<360 -> MEDIUM_MID
 * @tc.type: FUNC
 */
HWTEST_F(ComponentMaterialInteractionTestNg, GetLightEffectParamsBySize007, TestSize.Level1)
{
    auto params = ControlInteractionBase::GetLightEffectParamsBySize(200.0f, 52.0f, ColorMode::LIGHT);
    EXPECT_FLOAT_EQ(params.posZ, LIGHT_POSITION_Z_MEDIUM_MID);
    EXPECT_FLOAT_EQ(params.intensity, LIGHT_INTENSITY_MEDIUM_MID);
    EXPECT_EQ(params.color, Color(COLOR_MID));
}

/**
 * @tc.name: GetLightEffectParamsBySize008
 * @tc.desc: Branch 8: 48<=height<56 && width>=360 -> LARGE_MID
 * @tc.type: FUNC
 */
HWTEST_F(ComponentMaterialInteractionTestNg, GetLightEffectParamsBySize008, TestSize.Level1)
{
    auto params = ControlInteractionBase::GetLightEffectParamsBySize(400.0f, 52.0f, ColorMode::LIGHT);
    EXPECT_FLOAT_EQ(params.posZ, LIGHT_POSITION_Z_LARGE_MID);
    EXPECT_FLOAT_EQ(params.intensity, LIGHT_INTENSITY_LARGE_MID);
    EXPECT_EQ(params.color, Color(COLOR_MID));
}

/**
 * @tc.name: GetLightEffectParamsBySize009
 * @tc.desc: Branch 9: height>=56 (not LARGE_TALL) && width<96 -> NARROW_TALL
 * @tc.type: FUNC
 */
HWTEST_F(ComponentMaterialInteractionTestNg, GetLightEffectParamsBySize009, TestSize.Level1)
{
    auto params = ControlInteractionBase::GetLightEffectParamsBySize(80.0f, 100.0f, ColorMode::LIGHT);
    EXPECT_FLOAT_EQ(params.posZ, LIGHT_POSITION_Z_NARROW_TALL);
    EXPECT_FLOAT_EQ(params.intensity, LIGHT_INTENSITY_NARROW_TALL);
    EXPECT_EQ(params.color, Color(COLOR_MID));
}

/**
 * @tc.name: GetLightEffectParamsBySize010
 * @tc.desc: Branch 10: height>=56 (not LARGE_TALL) && 96<=width<360 -> MEDIUM_TALL
 * @tc.type: FUNC
 */
HWTEST_F(ComponentMaterialInteractionTestNg, GetLightEffectParamsBySize010, TestSize.Level1)
{
    auto params = ControlInteractionBase::GetLightEffectParamsBySize(200.0f, 100.0f, ColorMode::LIGHT);
    EXPECT_FLOAT_EQ(params.posZ, LIGHT_POSITION_Z_MEDIUM_TALL);
    EXPECT_FLOAT_EQ(params.intensity, LIGHT_INTENSITY_MEDIUM_TALL);
    EXPECT_EQ(params.color, Color(COLOR_TALL));
}

} // namespace OHOS::Ace::NG
