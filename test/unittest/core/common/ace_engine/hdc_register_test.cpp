/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include <csignal>
#include <dlfcn.h>
#include <memory>
#include <unistd.h>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/common/ace_application_info.h"
#include "core/common/hdc_register.h"
#include "core/common/platform_window.h"
#include "core/common/watch_dog.h"
#include "core/common/window.h"
#include "core/pipeline/pipeline_context.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
using ::testing::_;

namespace OHOS::Ace {
namespace {
using StartRegister = void (*)(const std::string& pkgName);
using StopRegister = void (*)();
} // namespace

class HdcRegisterTest : public testing::Test {};

/**
 * @tc.name: HdcRegisterTest
 * @tc.desc: Verify the StartHdcRegister.
 * @tc.type: FUNC
 */
HWTEST_F(HdcRegisterTest, HdcRegisterTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call LoadRegisterSo.
     * @tc.expect: registerHandler_ is not null
     */
    AceApplicationInfo::GetInstance().isDebugVersion_ = true;
    HdcRegister::Get().LoadRegisterSo();
    EXPECT_NE(HdcRegister::Get().registerHandler_, nullptr);

    /**
     * @tc.steps: step2. Call StartHdcRegister with instanceId > 0.
     */
    HdcRegister::Get().StartHdcRegister(1);

    /**
     * @tc.steps: step3. Call StartHdcRegister with instanceId = 0.
     */
    HdcRegister::Get().StartHdcRegister(0);
}

/**
 * @tc.name: HdcRegisterTest002
 * @tc.desc: Verify the StopHdcRegister.
 * @tc.type: FUNC
 */
HWTEST_F(HdcRegisterTest, HdcRegisterTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call LoadRegisterSo.
     * @tc.expect: registerHandler_ is not null
     */
    AceApplicationInfo::GetInstance().isDebugVersion_ = true;
    HdcRegister::Get().LoadRegisterSo();
    EXPECT_NE(HdcRegister::Get().registerHandler_, nullptr);

    /**
     * @tc.steps: step2. Call StopHdcRegister with instanceId > 0.
     * @tc.expect: registerHandler_ is not null
     */
    HdcRegister::Get().StopHdcRegister(1);
    EXPECT_NE(HdcRegister::Get().registerHandler_, nullptr);

    /**
     * @tc.steps: step3. Call StopHdcRegister with instanceId = 0.
     * @tc.expect: registerHandler_ is not null
     */
    HdcRegister::Get().StopHdcRegister(0);
    EXPECT_TRUE(AceApplicationInfo::GetInstance().IsDebugVersion());
    EXPECT_EQ(HdcRegister::Get().registerHandler_, nullptr);
}
} // namespace OHOS::Ace
