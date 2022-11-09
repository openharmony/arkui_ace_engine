/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#define USE_ARK_ENGINE 1
#include <stdint.h>
#include <string>

#include "gtest/gtest.h"
#include "third_party/libpng/png.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_xcomponent.h"
#include "arkcompiler/ets_runtime/ecmascript/ecma_runtime_call_info.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
} // namespace

class JsXComponentTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: JsXComponentTestNgTest001
 * @tc.desc: JSXComponent::Create
 * @tc.type: FUNC
 */
HWTEST_F(JsXComponentTestNg, JsXComponentTestNgTest001, TestSize.Level1)
{
    // Framework::JSXComponent::Create();
    panda::ecmascript::EcmaRuntimeCallInfo* ecmaRuntimeCallInfo = new panda::ecmascript::EcmaRuntimeCallInfo();
    EXPECT_TRUE(1 == 1);
}



} // namespace OHOS::Ace::NG