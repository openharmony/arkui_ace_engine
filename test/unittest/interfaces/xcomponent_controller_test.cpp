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
    EXPECT_TRUE(code != 0);
    /**
     * @tc.step2: Test SetRenderFitBySurfaceId when renderFitNumber is larger than fifteen.
     * @tc.expected: the error code indicates parameter invalid or load ace lib failed.
     */
    renderFitNumberInvalid = 16;
    code = XComponentController::SetRenderFitBySurfaceId(surfaceId, renderFitNumberInvalid, true);
    EXPECT_TRUE(code != 0);
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
    EXPECT_TRUE(code != 0);
}
} // namespace OHOS::Ace
