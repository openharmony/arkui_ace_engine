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

#include "gtest/gtest.h"

#include "interfaces/inner_api/xcomponent_controller/xcomponent_controller.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {
namespace {
    const std::string SURFACE_ID = "2430951489577";
} // namespace
class XComponentControllerTest : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: XComponentControllerTest001
 * @tc.desc: Test XComponentController::GetXComponentControllerFromNapiValue function.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentControllerTest, XComponentControllerTest001, TestSize.Level1)
{
    napi_env__* env = nullptr;
    napi_value__* value = nullptr;
    auto controller = XComponentController::GetXComponentControllerFromNapiValue(env, value);
    EXPECT_EQ(controller, nullptr);
}

/**
 * @tc.name: XComponentControllerTest002
 * @tc.desc: Test XComponentController::SetSurfaceCallbackMode function.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentControllerTest, XComponentControllerTest002, TestSize.Level1)
{
    napi_env__* env = nullptr;
    napi_value__* value = nullptr;
    SurfaceCallbackMode mode = SurfaceCallbackMode::DEFAULT;
    uint32_t code = XComponentController::SetSurfaceCallbackMode(env, value, mode);
    EXPECT_EQ(code, 1);
}

/**
 * @tc.name: SetRenderFitBySurfaceIdErrorCodeTest
 * @tc.desc: Test XComponentController::SetRenderFitBySurfaceId function with invalid input.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentControllerTest, SetRenderFitBySurfaceIdErrorCodeTest, TestSize.Level1)
{
    /**
     * @tc.step1: Test SetRenderFitBySurfaceId when renderFitNumber is less than zero.
     * @tc.expected: the error code indicates parameter invalid or load ace lib failed.
     */
    std::string surfaceId = SURFACE_ID;
    int32_t renderFitNumberInvalid = -1;
    auto code = XComponentController::SetRenderFitBySurfaceId(surfaceId, renderFitNumberInvalid, true);
    EXPECT_NE(code, 0);
    /**
     * @tc.step2: Test SetRenderFitBySurfaceId when renderFitNumber is larger than fifteen.
     * @tc.expected: the error code indicates parameter invalid or load ace lib failed.
     */
    renderFitNumberInvalid = 16;
    code = XComponentController::SetRenderFitBySurfaceId(surfaceId, renderFitNumberInvalid, true);
    EXPECT_NE(code, 0);
}

/**
 * @tc.name: GetRenderFitBySurfaceIdErrorCodeTest
 * @tc.desc: Test XComponentController::GetRenderFitBySurfaceId function with invalid input.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentControllerTest, GetRenderFitBySurfaceIdErrorCodeTest, TestSize.Level1)
{
    /**
     * @tc.step1: Test GetRenderFitBySurfaceId when surfaceId is invalid.
     * @tc.expected: the error code indicates parameter invalid or load ace lib failed.
     */
    std::string surfaceId = "";
    int32_t renderFitNumber = -1;
    bool isEnable = false;
    auto code = XComponentController::GetRenderFitBySurfaceId(surfaceId, renderFitNumber, isEnable);
    EXPECT_NE(code, 0);
}

/**
 * @tc.name: GetSurfaceRotationBySurfaceIdErrorCodeTest
 * @tc.desc: Test XComponentController::GetSurfaceRotationBySurfaceId function with invalid input.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentControllerTest, GetSurfaceRotationBySurfaceIdErrorCodeTest, TestSize.Level1)
{
    /**
     * @tc.step1: Test GetSurfaceRotationBySurfaceId when surfaceId is invalid.
     * @tc.expected: the error code indicates parameter invalid or load ace lib failed.
     */
    std::string surfaceId = "";
    bool isSurfaceLock = false;
    auto code = XComponentController::GetSurfaceRotationBySurfaceId(surfaceId, isSurfaceLock);
    EXPECT_NE(code, 0);
}

/**
 * @tc.name: GetXComponentControllerFromAniValueTest
 * @tc.desc: Test XComponentController::GetXComponentControllerFromAniValue function with invalid input.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentControllerTest, GetXComponentControllerFromAniValueTest, TestSize.Level1)
{
    ani_env* env = nullptr;
    ani_object aniValue = nullptr;
    auto controller = XComponentController::GetXComponentControllerFromAniValue(env, aniValue);
    EXPECT_EQ(controller, nullptr);
}

/**
 * @tc.name: SetSurfaceCallbackModeFromAniValueTest
 * @tc.desc: Test XComponentController::SetSurfaceCallbackModeFromAniValue function with invalid input.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentControllerTest, SetSurfaceCallbackModeFromAniValueTest, TestSize.Level1)
{
    ani_env* env = nullptr;
    ani_object aniValue = nullptr;
    SurfaceCallbackMode mode = SurfaceCallbackMode::DEFAULT;
    uint32_t code = XComponentController::SetSurfaceCallbackModeFromAniValue(env, aniValue, mode);
    EXPECT_EQ(code, 1);
}

/**
 * @tc.name: SetSurfaceCallbackModeWithPipModeTest
 * @tc.desc: Test XComponentController::SetSurfaceCallbackMode with PIP mode and null env.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentControllerTest, SetSurfaceCallbackModeWithPipModeTest, TestSize.Level1)
{
    napi_env__* env = nullptr;
    napi_value__* value = nullptr;
    SurfaceCallbackMode mode = SurfaceCallbackMode::PIP;
    uint32_t code = XComponentController::SetSurfaceCallbackMode(env, value, mode);
    EXPECT_EQ(code, static_cast<uint32_t>(XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_BAD_PARAMETER));
}

/**
 * @tc.name: SetSurfaceCallbackModeFromAniValueWithPipModeTest
 * @tc.desc: Test XComponentController::SetSurfaceCallbackModeFromAniValue with PIP mode and null env.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentControllerTest, SetSurfaceCallbackModeFromAniValueWithPipModeTest, TestSize.Level1)
{
    ani_env* env = nullptr;
    ani_object aniValue = nullptr;
    SurfaceCallbackMode mode = SurfaceCallbackMode::PIP;
    uint32_t code = XComponentController::SetSurfaceCallbackModeFromAniValue(env, aniValue, mode);
    EXPECT_EQ(code, static_cast<uint32_t>(XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_BAD_PARAMETER));
}

/**
 * @tc.name: SetRenderFitBySurfaceIdBoundaryTest
 * @tc.desc: Test SetRenderFitBySurfaceId with boundary renderFitNumber values 0 and 15.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentControllerTest, SetRenderFitBySurfaceIdBoundaryTest, TestSize.Level1)
{
    /**
     * @tc.step1: Test SetRenderFitBySurfaceId when renderFitNumber is zero (minimum valid value).
     * @tc.expected: the error code indicates load ace lib failed since the symbol cannot be resolved
     *              in the test environment.
     */
    std::string surfaceId = SURFACE_ID;
    const int32_t RENDER_FIT_MIN = 0;
    auto code = XComponentController::SetRenderFitBySurfaceId(surfaceId, RENDER_FIT_MIN, true);
    EXPECT_NE(code, static_cast<uint32_t>(XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_NO_ERROR));
    /**
     * @tc.step2: Test SetRenderFitBySurfaceId when renderFitNumber is fifteen (maximum valid value).
     * @tc.expected: the error code indicates load ace lib failed.
     */
    const int32_t RENDER_FIT_MAX = 15;
    code = XComponentController::SetRenderFitBySurfaceId(surfaceId, RENDER_FIT_MAX, true);
    EXPECT_NE(code, static_cast<uint32_t>(XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_NO_ERROR));
}

/**
 * @tc.name: SetRenderFitBySurfaceIdNewVersionDisabledTest
 * @tc.desc: Test SetRenderFitBySurfaceId with isRenderFitNewVersionEnabled set to false.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentControllerTest, SetRenderFitBySurfaceIdNewVersionDisabledTest, TestSize.Level1)
{
    /**
     * @tc.step1: Test SetRenderFitBySurfaceId when new version is disabled.
     * @tc.expected: the error code indicates load ace lib failed in test environment.
     */
    std::string surfaceId = SURFACE_ID;
    const int32_t RENDER_FIT_DEFAULT = 0;
    auto code = XComponentController::SetRenderFitBySurfaceId(surfaceId, RENDER_FIT_DEFAULT, false);
    EXPECT_NE(code, static_cast<uint32_t>(XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_NO_ERROR));
}

/**
 * @tc.name: SetRenderFitBySurfaceIdEmptySurfaceIdTest
 * @tc.desc: Test SetRenderFitBySurfaceId with empty surfaceId.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentControllerTest, SetRenderFitBySurfaceIdEmptySurfaceIdTest, TestSize.Level1)
{
    /**
     * @tc.step1: Test SetRenderFitBySurfaceId when surfaceId is empty string.
     * @tc.expected: the error code indicates load ace lib failed or no error depending on impl.
     */
    std::string surfaceId = "";
    const int32_t RENDER_FIT_DEFAULT = 0;
    auto code = XComponentController::SetRenderFitBySurfaceId(surfaceId, RENDER_FIT_DEFAULT, true);
    EXPECT_NE(code, static_cast<uint32_t>(XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_NO_ERROR));
}

/**
 * @tc.name: GetRenderFitBySurfaceIdValidSurfaceIdTest
 * @tc.desc: Test GetRenderFitBySurfaceId with a valid surfaceId.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentControllerTest, GetRenderFitBySurfaceIdValidSurfaceIdTest, TestSize.Level1)
{
    /**
     * @tc.step1: Test GetRenderFitBySurfaceId when surfaceId is a valid string.
     * @tc.expected: the error code indicates load ace lib failed in test environment.
     */
    std::string surfaceId = SURFACE_ID;
    int32_t renderFitNumber = -1;
    bool isEnable = false;
    auto code = XComponentController::GetRenderFitBySurfaceId(surfaceId, renderFitNumber, isEnable);
    EXPECT_NE(code, static_cast<uint32_t>(XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_NO_ERROR));
}

/**
 * @tc.name: GetSurfaceRotationBySurfaceIdValidSurfaceIdTest
 * @tc.desc: Test GetSurfaceRotationBySurfaceId with a valid surfaceId.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentControllerTest, GetSurfaceRotationBySurfaceIdValidSurfaceIdTest, TestSize.Level1)
{
    /**
     * @tc.step1: Test GetSurfaceRotationBySurfaceId when surfaceId is a valid string.
     * @tc.expected: the error code indicates load ace lib failed in test environment.
     */
    std::string surfaceId = SURFACE_ID;
    bool isSurfaceLock = false;
    auto code = XComponentController::GetSurfaceRotationBySurfaceId(surfaceId, isSurfaceLock);
    EXPECT_NE(code, static_cast<uint32_t>(XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_NO_ERROR));
}
} // namespace OHOS::Ace
