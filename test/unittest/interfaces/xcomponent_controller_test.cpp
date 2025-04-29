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
} // namespace OHOS::Ace
