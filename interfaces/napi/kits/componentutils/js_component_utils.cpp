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


#include "interfaces/napi/kits/utils/napi_utils.h"

#include "frameworks/bridge/common/utils/engine_helper.h"

#include "napi/native_api.h"

namespace OHOS::Ace::Napi {
namespace {
constexpr size_t STR_BUFFER_SIZE = 1024;
}
static napi_value JSGetRectangleById(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, &argv, &thisVar, &data);
    NAPI_ASSERT(env, argc == 1, "requires 1 parameter");
    napi_valuetype type = napi_undefined;
    napi_typeof(env, argv, &type);
    NAPI_ASSERT(env, type == napi_string, "the type of arg is not string");
    char outBuffer[STR_BUFFER_SIZE] = { 0 };
    size_t outSize = 0;
    napi_get_value_string_utf8(env, argv, outBuffer, STR_BUFFER_SIZE, &outSize);
    std::string key = std::string(outBuffer);
    OHOS::Ace::NG::Rectangle rectangle;
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        NapiThrow(env, "UI execution context not found.", ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }
    delegate->GetRectangleById(key, rectangle);

    napi_value obj = nullptr;
    napi_value size = nullptr;
    napi_value localOffset = nullptr;
    napi_value windowOffset = nullptr;
    napi_value screenOffset = nullptr;
    napi_value translate = nullptr;
    napi_value scale = nullptr;
    napi_value rotate = nullptr;
    napi_value transform = nullptr;

    napi_value width = nullptr;
    napi_value height = nullptr;
    napi_value localOffsetX = nullptr;
    napi_value localOffsetY = nullptr;
    napi_value windowOffsetX = nullptr;
    napi_value windowOffsetY = nullptr;
    napi_value screenOffsetX = nullptr;
    napi_value screenOffsetY = nullptr;
    napi_value translateX = nullptr;
    napi_value translateY = nullptr;
    napi_value translateZ = nullptr;
    napi_value scaleX = nullptr;
    napi_value scaleY = nullptr;
    napi_value scaleZ = nullptr;
    napi_value scaleCenterX = nullptr;
    napi_value scaleCenterY = nullptr;
    napi_value rotateX = nullptr;
    napi_value rotateY = nullptr;
    napi_value rotateZ = nullptr;
    napi_value rotateAngle = nullptr;
    napi_value rotateCenterX = nullptr;
    napi_value rotateCenterY = nullptr;
    napi_value matrix4[16] = { nullptr };

    const int m00 = 0;
    const int m01 = 1;
    const int m02 = 2;
    const int m03 = 3;
    const int m10 = 4;
    const int m11 = 5;
    const int m12 = 6;
    const int m13 = 7;
    const int m20 = 8;
    const int m21 = 9;
    const int m22 = 10;
    const int m23 = 11;
    const int m30 = 12;
    const int m31 = 13;
    const int m32 = 14;
    const int m33 = 15;

    napi_create_array(env, &transform);

    napi_create_double(env, rectangle.size.Width(), &width);
    napi_create_double(env, rectangle.size.Height(), &height);
    napi_create_double(env, rectangle.localOffset.GetX(), &localOffsetX);
    napi_create_double(env, rectangle.localOffset.GetY(), &localOffsetY);
    napi_create_double(env, rectangle.windowOffset.GetX(), &windowOffsetX);
    napi_create_double(env, rectangle.windowOffset.GetY(), &windowOffsetY);
    napi_create_double(env, rectangle.windowOffset.GetX() + rectangle.screenRect.GetOffset().GetX(), &screenOffsetX);
    napi_create_double(env, rectangle.windowOffset.GetY() + rectangle.screenRect.GetOffset().GetY(), &screenOffsetY);
    napi_create_double(env, rectangle.translate.x, &translateX);
    napi_create_double(env, rectangle.translate.y, &translateY);
    napi_create_double(env, rectangle.translate.z, &translateZ);
    napi_create_double(env, rectangle.scale.x, &scaleX);
    napi_create_double(env, rectangle.scale.y, &scaleY);
    napi_create_double(env, rectangle.scale.z, &scaleZ);
    napi_create_double(env, rectangle.scale.centerX, &scaleCenterX);
    napi_create_double(env, rectangle.scale.centerY, &scaleCenterY);
    napi_create_double(env, rectangle.rotate.x, &rotateX);
    napi_create_double(env, rectangle.rotate.y, &rotateY);
    napi_create_double(env, rectangle.rotate.z, &rotateZ);
    napi_create_double(env, rectangle.rotate.angle, &rotateAngle);
    napi_create_double(env, rectangle.rotate.centerX, &rotateCenterX);
    napi_create_double(env, rectangle.rotate.centerY, &rotateCenterY);

    napi_create_double(env, rectangle.matrix4[m00], &matrix4[m00]);
    napi_create_double(env, rectangle.matrix4[m01], &matrix4[m10]);
    napi_create_double(env, rectangle.matrix4[m02], &matrix4[m20]);
    napi_create_double(env, rectangle.matrix4[m03], &matrix4[m30]);
    napi_create_double(env, rectangle.matrix4[m10], &matrix4[m01]);
    napi_create_double(env, rectangle.matrix4[m11], &matrix4[m11]);
    napi_create_double(env, rectangle.matrix4[m12], &matrix4[m21]);
    napi_create_double(env, rectangle.matrix4[m13], &matrix4[m31]);
    napi_create_double(env, rectangle.matrix4[m20], &matrix4[m02]);
    napi_create_double(env, rectangle.matrix4[m21], &matrix4[m12]);
    napi_create_double(env, rectangle.matrix4[m22], &matrix4[m22]);
    napi_create_double(env, rectangle.matrix4[m23], &matrix4[m32]);
    napi_create_double(env, rectangle.matrix4[m30], &matrix4[m03]);
    napi_create_double(env, rectangle.matrix4[m31], &matrix4[m13]);
    napi_create_double(env, rectangle.matrix4[m32], &matrix4[m23]);
    napi_create_double(env, rectangle.matrix4[m33], &matrix4[m33]);

    napi_set_element(env, transform, m00, matrix4[m00]);
    napi_set_element(env, transform, m01, matrix4[m10]);
    napi_set_element(env, transform, m02, matrix4[m20]);
    napi_set_element(env, transform, m03, matrix4[m30]);
    napi_set_element(env, transform, m10, matrix4[m01]);
    napi_set_element(env, transform, m11, matrix4[m11]);
    napi_set_element(env, transform, m12, matrix4[m21]);
    napi_set_element(env, transform, m13, matrix4[m31]);
    napi_set_element(env, transform, m20, matrix4[m02]);
    napi_set_element(env, transform, m21, matrix4[m12]);
    napi_set_element(env, transform, m22, matrix4[m22]);
    napi_set_element(env, transform, m23, matrix4[m32]);
    napi_set_element(env, transform, m30, matrix4[m03]);
    napi_set_element(env, transform, m31, matrix4[m13]);
    napi_set_element(env, transform, m32, matrix4[m23]);
    napi_set_element(env, transform, m33, matrix4[m33]);

    constexpr size_t kTwoPropties = 2;
    std::array<const char*, kTwoPropties> sizePropKey = { "width", "height" };
    std::array<napi_value, kTwoPropties> sizePropValue = { width, height };
    napi_create_object_with_named_properties(env, &size, kTwoPropties, sizePropKey.data(), sizePropValue.data());

    std::array<const char*, kTwoPropties> localOffsetPropKey = { "x", "y" };
    std::array<napi_value, kTwoPropties> localOffsetPropValue = { localOffsetX, localOffsetY };
    napi_create_object_with_named_properties(env, &localOffset, kTwoPropties,
                                             localOffsetPropKey.data(), localOffsetPropValue.data());

    // same key with local offset { "x", "y" }
    std::array<napi_value, kTwoPropties> windowOffsetPropValue = { windowOffsetX, windowOffsetY };
    napi_create_object_with_named_properties(env, &windowOffset, kTwoPropties,
                                             localOffsetPropKey.data(), windowOffsetPropValue.data());

    // same key with local offset { "x", "y" }
    std::array<napi_value, kTwoPropties> screenOffsetPropValue = { screenOffsetX, screenOffsetY };
    napi_create_object_with_named_properties(env, &screenOffset, kTwoPropties,
                                             localOffsetPropKey.data(), screenOffsetPropValue.data());

    constexpr size_t kThreePropties = 3;
    std::array<const char*, kThreePropties> translatePropKey = { "x", "y", "z" };
    std::array<napi_value, kThreePropties> translatePropValue = { translateX, translateY, translateZ };
    napi_create_object_with_named_properties(env, &translate, kThreePropties,
                                             translatePropKey.data(), translatePropValue.data());

    constexpr size_t kFivePropties = 5;
    std::array<const char*, kFivePropties> scalePropKey = { "x", "y", "z", "centerX", "centerY" };
    std::array<napi_value, kFivePropties> scalePropValue = { scaleX, scaleY, scaleZ, scaleCenterX, scaleCenterY };
    napi_create_object_with_named_properties(env, &scale, kFivePropties, scalePropKey.data(), scalePropValue.data());

    constexpr size_t kSixPropties = 6;
    std::array<const char*, kSixPropties> rotatePropKey = { "x", "y", "z", "angle", "centerX", "centerY" };
    std::array<napi_value, kSixPropties> rotatePropValue = { rotateX, rotateY, rotateZ, rotateAngle,
                                                             rotateCenterX, rotateCenterY };
    napi_create_object_with_named_properties(env, &rotate, kSixPropties, rotatePropKey.data(), rotatePropValue.data());

    constexpr size_t kEightPropties = 8;
    std::array<const char*, kEightPropties> objPropKey = { "size", "localOffset", "windowOffset", "screenOffset",
                                                           "translate", "scale", "rotate", "transform" };
    std::array<napi_value, kEightPropties> objPropValue = { size, localOffset, windowOffset, screenOffset,
                                                            translate, scale, rotate, transform };
    napi_create_object_with_named_properties(env, &obj, kEightPropties, objPropKey.data(), objPropValue.data());

    return obj;
}

static napi_value registerFunc(napi_env env, napi_value exports)
{
    napi_property_descriptor animatorDesc[] = {
        DECLARE_NAPI_FUNCTION("getRectangleById", JSGetRectangleById),
    };
    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(animatorDesc) / sizeof(animatorDesc[0]), animatorDesc));
    return exports;
}

static napi_module componentUtilsModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = registerFunc,
    .nm_modname = "arkui.componentUtils",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void ComponentUtilsRegister()
{
    napi_module_register(&componentUtilsModule);
}
} // namespace OHOS::Ace::Napi
