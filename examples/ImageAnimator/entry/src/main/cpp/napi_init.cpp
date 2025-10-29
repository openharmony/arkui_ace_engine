/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#define NAPI_VERSION 8

#include <arkui/native_node_napi.h>
#include <napi/native_api.h>

#include "arkui_column_node.h"
#include "arkui_image_node.h"
#include "native_entry.h"
#include "native_module.h"

namespace NativeModule {
napi_value CreateNativeRoot(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[2] = { nullptr, nullptr };
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    // 获取NodeContent
    ArkUI_NodeContentHandle contentHandle;
    OH_ArkUI_GetNodeContentFromNapiValue(env, args[0], &contentHandle);
    NativeEntry::GetInstance()->SetContentHandle(contentHandle);
    std::string src = "file:///data/storage/el2/base/haps/entry/files";
    auto imageSource = ImageSource::Create(src + "/img2.gif");
    auto drawable1 = DrawableDescriptor::CreateFromNapiValue(env, args[1]);
    DecodingOptions options;
    options.SetPixelFormat(PixelMapFormat::RGBA_8888);
    auto pixelMaps = imageSource->CreatePixelMapList(options);
    auto drawable2 = DrawableDescriptor::CreateFromPixelMapArray(pixelMaps, { .duration = 2000, .iteration = -1 });
    auto columnNode = std::make_shared<ArkUIColumnNode>();
    auto image1 = std::make_shared<ArkUIImageNode>();
    image1->SetDrawableDescriptor(drawable1);
    image1->SetWidth(200);
    image1->SetHeight(200);
    image1->SetBorderWidth(1);
    image1->SetBorderColor(0XFF1A1234);
    auto image2 = std::make_shared<ArkUIImageNode>();
    image2->SetDrawableDescriptor(drawable2);
    image2->SetWidth(200);
    image2->SetHeight(200);
    image2->SetBorderWidth(1);
    image2->SetBorderColor(0XFF1A1234);
    columnNode->InsertChild(image1, 0);
    columnNode->InsertChild(image2, 0);
    NativeEntry::GetInstance()->SetRootNode(columnNode);
    return nullptr;
}

napi_value CreateNativeImage(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1] = { nullptr };
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    ArkUI_NodeContentHandle contentHandle;
    OH_ArkUI_GetNodeContentFromNapiValue(env, args[0], &contentHandle);
    NativeEntry::GetInstance()->SetContentHandle(contentHandle);
    std::string src1 = "resources/base/media/1.jpg";
    auto columnNode = std::make_shared<ArkUIColumnNode>();
    auto image1 = std::make_shared<ArkUIImageNode>();
    image1->SetSrc(src1);
    image1->SetWidth(100);
    image1->SetHeight(100);
    image1->SetBorderWidth(1);
    image1->SetBorderColor(0XFF1A1234);
    columnNode->InsertChild(image1, 0);
    NativeEntry::GetInstance()->SetRootNode(columnNode);
    return nullptr;
}

napi_value DestroyNativeRoot(napi_env env, napi_callback_info info)
{
    // 从管理类中释放Native侧对象。
    NativeEntry::GetInstance()->DisposeRootNode();
    return nullptr;
}
} // namespace NativeModule

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        { "createNativeRoot", nullptr, NativeModule::CreateNativeRoot, nullptr, nullptr, nullptr, napi_default,
            nullptr },
        { "createNativeImage", nullptr, NativeModule::CreateNativeImage, nullptr, nullptr, nullptr, napi_default,
            nullptr },
        { "destroyNativeRoot", nullptr, NativeModule::DestroyNativeRoot, nullptr, nullptr, nullptr, napi_default,
            nullptr },
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}
EXTERN_C_END

static napi_module demoModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "entry",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterEntryModule(void)
{
    napi_module_register(&demoModule);
}
