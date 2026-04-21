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

#include "interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Napi;

namespace OHOS::Ace {

class JsDrawableDescriptorExtendedTest : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: JsDrawableDescriptorExtendedTest001
 * @tc.desc: test GetPixelMapFromNapi with null napiValue
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorExtendedTest, JsDrawableDescriptorExtendedTest001, TestSize.Level1)
{
    JsDrawableDescriptor jsDrawable;
    napi_env env = nullptr;
    napi_value napiValue = nullptr;

    auto result = jsDrawable.GetPixelMapFromNapi(env, napiValue);

    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorExtendedTest002
 * @tc.desc: test GetPixelMapFromDrawableNapi with null drawable
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorExtendedTest, JsDrawableDescriptorExtendedTest002, TestSize.Level1)
{
    JsDrawableDescriptor jsDrawable;
    napi_env env = nullptr;
    napi_value napiValue = nullptr;

    auto result = jsDrawable.GetPixelMapFromDrawableNapi(env, napiValue);

    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorExtendedTest003
 * @tc.desc: test ToNapi with null drawable
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorExtendedTest, JsDrawableDescriptorExtendedTest003, TestSize.Level1)
{
    JsDrawableDescriptor jsDrawable;
    napi_env env = nullptr;
    DrawableDescriptor* drawable = nullptr;

    auto result = jsDrawable.ToNapi(env, drawable, DrawableDescriptor::DrawableType::BASE);

    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorExtendedTest004
 * @tc.desc: test ToNapi with valid drawable but null env
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorExtendedTest, JsDrawableDescriptorExtendedTest004, TestSize.Level1)
{
    JsDrawableDescriptor jsDrawable;
    napi_env env = nullptr;
    DrawableDescriptor drawable;

    auto result = jsDrawable.ToNapi(env, &drawable, DrawableDescriptor::DrawableType::BASE);

    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorExtendedTest005
 * @tc.desc: test ToNapi with invalid DrawableType
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorExtendedTest, JsDrawableDescriptorExtendedTest005, TestSize.Level1)
{
    JsDrawableDescriptor jsDrawable;
    napi_env env = nullptr;
    DrawableDescriptor drawable;

    auto result = jsDrawable.ToNapi(env, &drawable, static_cast<DrawableDescriptor::DrawableType>(999));

    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorExtendedTest006
 * @tc.desc: test ToNapi with ANIMATED type
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorExtendedTest, JsDrawableDescriptorExtendedTest006, TestSize.Level1)
{
    JsDrawableDescriptor jsDrawable;
    napi_env env = nullptr;
    DrawableDescriptor drawable;

    auto result = jsDrawable.ToNapi(env, &drawable, DrawableDescriptor::DrawableType::ANIMATED);

    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorExtendedTest007
 * @tc.desc: test ToNapi with LAYERED type
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorExtendedTest, JsDrawableDescriptorExtendedTest007, TestSize.Level1)
{
    JsDrawableDescriptor jsDrawable;
    napi_env env = nullptr;
    DrawableDescriptor drawable;

    auto result = jsDrawable.ToNapi(env, &drawable, DrawableDescriptor::DrawableType::LAYERED);

    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorExtendedTest008
 * @tc.desc: test ToNapi with PIXELMAP type
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorExtendedTest, JsDrawableDescriptorExtendedTest008, TestSize.Level1)
{
    JsDrawableDescriptor jsDescriptor;
    napi_env env = nullptr;
    DrawableDescriptor drawable;

    auto result = jsDescriptor.ToNapi(env, &drawable, DrawableDescriptor::DrawableType::PIXELMAP);

    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorExtendedTest009
 * @tc.desc: test Export with null env
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorExtendedTest, JsDrawableDescriptorExtendedTest009, TestSize.Level1)
{
    JsDrawableDescriptor jsDescriptor;
    napi_env env = nullptr;
    napi_value exports = nullptr;

    auto result = jsDescriptor.Export(env, exports);

    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorExtendedTest010
 * @tc.desc: test GetPixelMap with null env
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorExtendedTest, JsDrawableDescriptorExtendedTest010, TestSize.Level1)
{
    napi_env env = nullptr;
    napi_callback_info info = nullptr;

    auto result = JsDrawableDescriptor::GetPixelMap(env, info);

    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorExtendedTest011
 * @tc.desc: test GetForeground with null env
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorExtendedTest, JsDrawableDescriptorExtendedTest011, TestSize.Level1)
{
    napi_env env = nullptr;
    napi_callback_info info = nullptr;

    auto result = JsDrawableDescriptor::GetForeground(env, info);

    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorExtendedTest012
 * @tc.desc: test GetBackground with null env
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorExtendedTest, JsDrawableDescriptorExtendedTest012, TestSize.Level1)
{
    napi_env env = nullptr;
    napi_callback_info info = nullptr;

    auto result = JsDrawableDescriptor::GetBackground(env, info);

    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorExtendedTest013
 * @tc.desc: test GetMask with null env
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorExtendedTest, JsDrawableDescriptorExtendedTest013, TestSize.Level1)
{
    napi_env env = nullptr;
    napi_callback_info info = nullptr;

    auto result = JsDrawableDescriptor::GetMask(env, info);

    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorExtendedTest014
 * @tc.desc: test GetMaskClipPath static method
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorExtendedTest, JsDrawableDescriptorExtendedTest014, TestSize.Level1)
{
    napi_env env = nullptr;
    napi_callback_info info = nullptr;

    auto result = JsDrawableDescriptor::GetMaskClipPath(env, info);

    // Static method, should return a string result even with null env
}

/**
 * @tc.name: JsDrawableDescriptorExtendedTest015
 * @tc.desc: test InitDrawable with null env
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorExtendedTest, JsDrawableDescriptorExtendedTest015, TestSize.Level1)
{
    napi_env env = nullptr;

    auto result = JsDrawableDescriptor::InitDrawable(env);

    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorExtendedTest016
 * @tc.desc: test InitLayeredDrawable with null env
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorExtendedTest, JsDrawableDescriptorExtendedTest016, TestSize.Level1)
{
    napi_env env = nullptr;

    auto result = JsDrawableDescriptor::InitLayeredDrawable(env);

    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorExtendedTest017
 * @tc.desc: test InitAnimatedDrawable with null env
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorExtendedTest, JsDrawableDescriptorExtendedTest017, TestSize.Level1)
{
    napi_env env = nullptr;

    auto result = JsDrawableDescriptor::InitAnimatedDrawable(env);

    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsDrawableDescriptorExtendedTest018
 * @tc.desc: test InitPixelMapDrawable with null env
 * @tc.type: FUNC
 */
HWTEST_F(JsDrawableDescriptorExtendedTest, JsDrawableDescriptorExtendedTest018, TestSize.Level1)
{
    napi_env env = nullptr;

    auto result = JsDrawableDescriptor::InitPixelMapDrawable(env);

    EXPECT_EQ(result, nullptr);
}

} // namespace OHOS::Ace
