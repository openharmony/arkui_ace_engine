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

#include "interfaces/inner_api/drawable_descriptor/drawable_descriptor.h"
#include "interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.h"
#include "node_extened.h"
#include "native_drawable_descriptor.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Napi;

namespace OHOS::Ace {

class JsDrawableDescriptorTest : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: JsDrawableDescriptorTest001
 * @tc.desc: test Export function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest001, TestSize.Level1)
{
    napi_env env = nullptr;
    napi_value exports = nullptr;
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.Export(env, exports);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorTest002
 * @tc.desc: test ToNapi function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest002, TestSize.Level1)
{
    napi_env env = nullptr;
    DrawableDescriptor* drawable = nullptr;
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.ToNapi(env, drawable, DrawableDescriptor::DrawableType::PIXELMAP);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorTest003
 * @tc.desc: test ToNapi function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest003, TestSize.Level1)
{
    napi_env env = nullptr;
    DrawableDescriptor drawable;
    JsDrawableDescriptor jsDrawableDescriptor;
    JsDrawableDescriptor::baseConstructor_ = (napi_ref)malloc(1000);
    napi_value result = jsDrawableDescriptor.ToNapi(env, &drawable, DrawableDescriptor::DrawableType::ANIMATED);
    EXPECT_EQ(result, nullptr);
    free(JsDrawableDescriptor::baseConstructor_);
}

/**
 * @tc.name: JsDrawableDescriptorTest004
 * @tc.desc: test ToNapi function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest004, TestSize.Level1)
{
    napi_env env = nullptr;
    DrawableDescriptor drawable;
    JsDrawableDescriptor jsDrawableDescriptor;
    JsDrawableDescriptor::layeredConstructor_ = (napi_ref)malloc(1000);
    napi_value result = jsDrawableDescriptor.ToNapi(env, &drawable, DrawableDescriptor::DrawableType::BASE);
    EXPECT_EQ(result, nullptr);
    free(JsDrawableDescriptor::layeredConstructor_);
}

/**
 * @tc.name: JsDrawableDescriptorTest005
 * @tc.desc: test ToNapi function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest005, TestSize.Level1)
{
    napi_env env = nullptr;
    DrawableDescriptor drawable;
    JsDrawableDescriptor jsDrawableDescriptor;
    JsDrawableDescriptor::animatedConstructor_ = (napi_ref)malloc(1000);
    napi_value result = jsDrawableDescriptor.ToNapi(env, &drawable, DrawableDescriptor::DrawableType::LAYERED);
    EXPECT_EQ(result, nullptr);
    free(JsDrawableDescriptor::animatedConstructor_);
}

/**
 * @tc.name: JsDrawableDescriptorTest006
 * @tc.desc: test ToNapi function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest006, TestSize.Level1)
{
    napi_env env = nullptr;
    DrawableDescriptor drawable;
    JsDrawableDescriptor jsDrawableDescriptor;
    JsDrawableDescriptor::pixelMapConstructor_ = (napi_ref)malloc(1000);
    napi_value result = jsDrawableDescriptor.ToNapi(env, &drawable, DrawableDescriptor::DrawableType::PIXELMAP);
    EXPECT_EQ(result, nullptr);
    free(JsDrawableDescriptor::pixelMapConstructor_);
}
} // namespace OHOS::Ace
