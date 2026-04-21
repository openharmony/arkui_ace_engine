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

/**
 * @tc.name: JsDrawableDescriptorTest007
 * @tc.desc: test CreatDrawable function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest007, TestSize.Level1)
{
    napi_env env = nullptr;
    void* native = nullptr;
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.CreatDrawable(env, native);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorTest008
 * @tc.desc: test CreatDrawable function with valid native pointer but null env;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest008, TestSize.Level1)
{
    napi_env env = nullptr;
    void* native = malloc(100);
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.CreatDrawable(env, native);
    EXPECT_EQ(result, nullptr);
    free(native);
}

/**
 * @tc.name: JsDrawableDescriptorTest009
 * @tc.desc: test CreatLayeredDrawable function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest009, TestSize.Level1)
{
    napi_env env = nullptr;
    void* native = nullptr;
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.CreatLayeredDrawable(env, native);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorTest010
 * @tc.desc: test CreatLayeredDrawable function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest010, TestSize.Level1)
{
    napi_env env = nullptr;
    void* native = malloc(100);
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.CreatLayeredDrawable(env, native);
    EXPECT_EQ(result, nullptr);
    free(native);
}

/**
 * @tc.name: JsDrawableDescriptorTest011
 * @tc.desc: test CreatPixelMapDrawable function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest011, TestSize.Level1)
{
    napi_env env = nullptr;
    void* native = nullptr;
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.CreatPixelMapDrawable(env, native);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorTest012
 * @tc.desc: test CreatPixelMapDrawable function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest012, TestSize.Level1)
{
    napi_env env = nullptr;
    void* native = malloc(100);
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.CreatPixelMapDrawable(env, native);
    EXPECT_EQ(result, nullptr);
    free(native);
}

/**
 * @tc.name: JsDrawableDescriptorTest013
 * @tc.desc: test CreateDrawableDescriptorTransfer function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest013, TestSize.Level1)
{
    napi_env env = nullptr;
    napi_callback_info info = nullptr;
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.CreateDrawableDescriptorTransfer(env, info);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorTest014
 * @tc.desc: test GetForeground function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest014, TestSize.Level1)
{
    napi_env env = nullptr;
    napi_callback_info info = nullptr;
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.GetForeground(env, info);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorTest015
 * @tc.desc: test GetBackground function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest015, TestSize.Level1)
{
    napi_env env = nullptr;
    napi_callback_info info = nullptr;
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.GetBackground(env, info);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorTest016
 * @tc.desc: test GetMask function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest016, TestSize.Level1)
{
    napi_env env = nullptr;
    napi_callback_info info = nullptr;
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.GetMask(env, info);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorTest017
 * @tc.desc: test GetMaskClipPath function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest017, TestSize.Level1)
{
    napi_env env = nullptr;
    napi_callback_info info = nullptr;
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.GetMaskClipPath(env, info);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorTest018
 * @tc.desc: test SetBlendMode function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest018, TestSize.Level1)
{
    napi_env env = nullptr;
    napi_callback_info info = nullptr;
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.SetBlendMode(env, info);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorTest019
 * @tc.desc: test GetPixelMap function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest019, TestSize.Level1)
{
    napi_env env = nullptr;
    napi_callback_info info = nullptr;
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.GetPixelMap(env, info);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorTest020
 * @tc.desc: test CreateLoadResult function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest020, TestSize.Level1)
{
    napi_env env = nullptr;
    int32_t width = 100;
    int32_t height = 200;
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.CreateLoadResult(env, width, height);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorTest021
 * @tc.desc: test LoadComplete function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest021, TestSize.Level1)
{
    napi_env env = nullptr;
    napi_status status = napi_ok;
    void* data = nullptr;
    JsDrawableDescriptor jsDrawableDescriptor;
    jsDrawableDescriptor.LoadComplete(env, status, data);
    // Void function, just verify it doesn't crash
}

/**
 * @tc.name: JsDrawableDescriptorTest022
 * @tc.desc: test Load function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest022, TestSize.Level1)
{
    napi_env env = nullptr;
    napi_callback_info info = nullptr;
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.Load(env, info);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorTest023
 * @tc.desc: test LoadSync function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest023, TestSize.Level1)
{
    napi_env env = nullptr;
    napi_callback_info info = nullptr;
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.LoadSync(env, info);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorTest024
 * @tc.desc: test GetAnimationController function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest024, TestSize.Level1)
{
    napi_env env = nullptr;
    napi_callback_info info = nullptr;
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.GetAnimationController(env, info);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorTest025
 * @tc.desc: test Start function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest025, TestSize.Level1)
{
    napi_env env = nullptr;
    napi_callback_info info = nullptr;
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.Start(env, info);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorTest026
 * @tc.desc: test Stop function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest026, TestSize.Level1)
{
    napi_env env = nullptr;
    napi_callback_info info = nullptr;
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.Stop(env, info);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorTest027
 * @tc.desc: test Pause function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest027, TestSize.Level1)
{
    napi_env env = nullptr;
    napi_callback_info info = nullptr;
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.Pause(env, info);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorTest028
 * @tc.desc: test Resume function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest028, TestSize.Level1)
{
    napi_env env = nullptr;
    napi_callback_info info = nullptr;
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.Resume(env, info);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorTest029
 * @tc.desc: test GetStatus function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest029, TestSize.Level1)
{
    napi_env env = nullptr;
    napi_callback_info info = nullptr;
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.GetStatus(env, info);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorTest030
 * @tc.desc: test AnimatedConstructor function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest030, TestSize.Level1)
{
    napi_env env = nullptr;
    napi_callback_info info = nullptr;
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.AnimatedConstructor(env, info);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorTest031
 * @tc.desc: test LayeredConstructor function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest031, TestSize.Level1)
{
    napi_env env = nullptr;
    napi_callback_info info = nullptr;
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.LayeredConstructor(env, info);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorTest032
 * @tc.desc: test DrawableConstructor function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest032, TestSize.Level1)
{
    napi_env env = nullptr;
    napi_callback_info info = nullptr;
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.DrawableConstructor(env, info);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorTest033
 * @tc.desc: test PixelMapConstructor function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest033, TestSize.Level1)
{
    napi_env env = nullptr;
    napi_callback_info info = nullptr;
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.PixelMapConstructor(env, info);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorTest034
 * @tc.desc: test InitDrawable function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest034, TestSize.Level1)
{
    napi_env env = nullptr;
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.InitDrawable(env);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorTest035
 * @tc.desc: test InitPixelMapDrawable function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest035, TestSize.Level1)
{
    napi_env env = nullptr;
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.InitPixelMapDrawable(env);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorTest036
 * @tc.desc: test InitLayeredDrawable function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest036, TestSize.Level1)
{
    napi_env env = nullptr;
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.InitLayeredDrawable(env);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorTest037
 * @tc.desc: test InitAnimatedDrawable function;
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorTest, JsDrawableDescriptorTest037, TestSize.Level1)
{
    napi_env env = nullptr;
    JsDrawableDescriptor jsDrawableDescriptor;
    napi_value result = jsDrawableDescriptor.InitAnimatedDrawable(env);
    EXPECT_EQ(result, nullptr);
}
} // namespace OHOS::Ace
