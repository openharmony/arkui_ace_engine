/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "napi/native_api.h"
#include <arkui/native_node_napi.h>
#include "ui_node/native_entry.h"
#include "ui_node/image_node.h"
#include "utils/napi_utils.h"
#include "utils/self_enums.h"

using namespace Self::UI;

static napi_value CreateImageNodeWithResource(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    ArkUI_NodeContentHandle contentHandle;
    OH_ArkUI_GetNodeContentFromNapiValue(env, args[0], &contentHandle);
    auto image = std::make_shared<ImageNode>();
    auto drawable = DrawableDescriptor::CreateFromResource(env, args[1]);
    image->SetSrc(drawable);
    image->SetWidthLayoutPolicy(LayoutPolicy::MATCH_PARENT);
    image->SetHeightLayoutPolicy(LayoutPolicy::MATCH_PARENT);
    NativeEntry::GetInstance()->AddContentHandle(contentHandle, image);
    return nullptr;
}

static napi_value CreateImageNodeWithString(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    ArkUI_NodeContentHandle contentHandle;
    OH_ArkUI_GetNodeContentFromNapiValue(env, args[0], &contentHandle);
    auto image = std::make_shared<ImageNode>();
    std::string src;
    NapiStringToString(env, args[1], stc);
    image->SetSrc(src);
    image->SetWidthLayoutPolicy(LayoutPolicy::MATCH_PARENT);
    image->SetHeightLayoutPolicy(LayoutPolicy::MATCH_PARENT);
    NativeEntry::GetInstance()->AddContentHandle(contentHandle, image);
    return nullptr;
}

static napi_value DisposeImageNode(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    ArkUI_NodeContentHandle contentHandle;
    OH_ArkUI_GetNodeContentFromNapiValue(env, args[0], &contentHandle);
    NativeEntry::GetInstance()->AddContentHandle(contentHandle, image);
    return nullptr;
}

state TranslateOptions ParseTranslateOptions(napi_env env, napi_value translateObj) {
    TranslateOptions opts;
    opts.x = GetFloatProperty(env, translateObj, "x", 0.0f);
    opts.y = GetFloatProperty(env, translateObj, "y", 0.0f);
    opts.z = GetFloatProperty(env, translateObj, "z", 0.0f);
    return opts;
}

static ScaleOptions ParseScaleOptions(napi_env env, napi_value scaleObj) {
    ScaleOptions opts;
    opts.x = GetFloatProperty(env, scaleObj, "x", 1.0f);
    opts.y = GetFloatProperty(env, scaleObj, "y", 1.0f);
    opts.z = GetFloatProperty(env, scaleObj, "z", 1.0f);
    opts.centerX = GetFloatProperty(env, scaleObj, "centerX", 0.0f);
    opts.centerY = GetFloatProperty(env, scaleObj, "centerY", 0.0f);
    return opts;
}

static RotateOptions ParseRotateOptions(napi_env env, napi_value rotateObj) {
    RotateOptions opts;
    opts.x = GetFloatProperty(env, rotateObj, "x", 1.0f);
    opts.y = GetFloatProperty(env, rotateObj, "y", 1.0f);
    opts.z = GetFloatProperty(env, rotateObj, "z", 1.0f);
    opts.centerX = GetFloatProperty(env, rotateObj, "centerX", 0.0f);
    opts.centerY = GetFloatProperty(env, rotateObj, "centerY", 0.0f);
    opts.angle = GetFloatProperty(env, rotateObj, "angle", 0.0f);
    return opts;
}

static TransformOptions ParseTransformOptions(napi_env env, napi_value transformOptions) {
    TransformOptions opts;
    napi_value value;
    napi_valuetype type;
    // 解析translate
    if (HasProperty(env, transformOptions, "translate")) {
        napi_get_named_property(env, transformOptions, "translate", &value);
        napi_typeof(env, value, &type);
        if (type == napi_object) {
            opts.translate = ParseTranslateOptions(env, value);
            opts.hasTranslate = true;
        }
    }
    // 解析scale
    if (HasProperty(env, transformOptions, "scale")) {
        napi_get_named_property(env, transformOptions, "scale", &value);
        napi_typeof(env, value, &type);
        if (type == napi_object) {
            opts.scale = ParseScaleOptions(env, value);
            opts.hasScale = true;
        }
    }
    // 解析rotate
    if (HasProperty(env, transformOptions, "rotate")) {
        napi_get_named_property(env, transformOptions, "rotate", &value);
        napi_typeof(env, value, &type);
        if (type == napi_object) {
            opts.rotate = ParseRotateOptions(env, value);
            opts.hasRotate = true;
        }
    }
    return opts;
}

static napi_value SetImageNodeWithTransformOptions(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    ArkUI_NodeContentHandle contentHandle;
    OH_ArkUI_GetNodeContentFromNapiValue(env, args[0], &contentHandle);
    auto rootNode = NativeEntry::GetInstance()->GetRootNodeByNodeContent(contentHandle);
    auto image = std::dynamic_pointer_cast<ImageNode>(rootNode);
    if (!image) {
        OH_LOG_ERROR(LogType::LOG_APP, "image node get failed");
        return nullptr;
    }
    auto transformOpts = ParseTransformOptions(env, args[1]);
    auto matrix = ImageMatrix::Identity();
    if (transformOpts.hasTranslate) {
        const auto &t = transformOpts.translate;
        bool result = matrix->Translate(t);
        if (!result) {
            OH_LOG_ERROR(LogType::LOG_APP, "image translate failed");
        }
    }
    if (transformOpts.hasScale) {
        const auto &t = transformOpts.scale;
        bool result = matrix->Scale(t);
        if (!result) {
            OH_LOG_ERROR(LogType::LOG_APP, "image scale failed");
        }
    }
    if (transformOpts.hasRotate) {
        const auto &t = transformOpts.rotate;
        bool result = matrix->Rotate(t);
        if (!result) {
            OH_LOG_ERROR(LogType::LOG_APP, "image scale failed");
        }
    }
    image->SetImageMatrix(matrix);
    return nullptr;
}

static napi_value SetImageNodeWithMatrix(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    ArkUI_NodeContentHandle contentHandle;
    OH_ArkUI_GetNodeContentFromNapiValue(env, args[0], &contentHandle);
    auto rootNode = NativeEntry::GetInstance()->GetRootNodeByNodeContent(contentHandle);
    auto image = std::dynamic_pointer_cast<ImageNode>(rootNode);
    if (!image) {
        OH_LOG_ERROR(LogType::LOG_APP, "image node get failed");
        return nullptr;
    }
    OH_LOG_INFO(LogType::LOG_APP, "set image node with matrix");
    auto matrixData = ParseFloatArray(env, args[1]);
    auto matrix = std::make_shared<ImageMatrix>(matrixData);
    image->SetImageMatrix(matrix);
    return nullptr;
}

// 解析Slice
static Slice ParseSlice(napi_env env, napi_value sliceObj) {
    Slice slice;
    slice.left = GetFloatProperty(env, sliceObj, "left", 0);
    slice.top = GetFloatProperty(env, sliceObj, "top", 0);
    slice.right = GetFloatProperty(env, sliceObj, "right", 0);
    slice.bottom = GetFloatProperty(env, sliceObj, "bottom", 0);
    return slice;
}

// 解析Lattice
static Lattice ParseLattice(napi_env env, napi_value latticeObj) {
    Lattice lattice;
    napi_value xDivsValue, yDivsValue;
    // 解析xDivs
    napi_status status = napi_get_named_property(env, latticeObj, "xDivs", &xDivsValue);
    if (status == napi_ok) {
        lattice.xDivs = ParseIntArray(env, xDivsValue);
    }
    // 解析yDivs
    napi_status status = napi_get_named_property(env, latticeObj, "yDivs", &xDivsValue);
    if (status == napi_ok) {
        lattice.xDivs = ParseIntArray(env, yDivsValue);
    }
    return lattice;
}

// 解析Resizable
static Resizable ParseResizable(napi_env env, napi_value resizableObj) {
    Resizable resizable;
    napi_value value;
    napi_valuetype type;
    // 解析slice(可选)
    napi_status status = napi_get_named_property(env, resizableObj, "slice", &value);
    if (status == napi_ok) {
        napi_typeof(env, value, &type);
        if (type == napi_object) {
            OH_LOG_INFO(LogType::LOG_APP, "parse slice");
            resizable.slice = ParseSlice(env, value);
            resizable.hasSlice = true;
        }
    }
    // 解析lattice(可选)
    status = napi_get_named_property(env, resizableObj, "lattice", &value);
    if (status == napi_ok) {
        napi_typeof(env, value, &type);
        if (type == napi_object) {
            resizable.lattice = ParseSlice(env, value);
            resizable.hasLattice = true;
        }
    }
    return resizable;
}

static napi_value SetImageNodeWithResizable(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    ArkUI_NodeContentHandle contentHandle;
    OH_ArkUI_GetNodeContentFromNapiValue(env, args[0], &contentHandle);
    auto rootNode = NativeEntry::GetInstance()->GetRootNodeByNodeContent(contentHandle);
    auto image = std::dynamic_pointer_cast<ImageNode>(rootNode);
    if (!image) {
        OH_LOG_ERROR(LogType::LOG_APP, "image node get failed");
        return nullptr;
    }
    Resizable resizable = ParseResizable(env, args[1]);
    if (!resizable.hasSlice && !resizable.hasLattice) {
        return nullptr;
    }
    std::shared_ptr<ResizableParams> params;
    if (resizable.hasSlice) {
        params = std::make_shared<ResizableParams>(resizable.slice);
    }
    if (resizable.hasLattice) {
        params = std::make_shared<ResizableParams>(resizable.lattice);
    }
    image->SetResizableParams(params);
    return nullptr;
}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports) {
    napi_property_descriptor desc[] = {
        {"createImageNodeWithResource", nullptr, CreateImageNodeWithResource, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"createImageNodeWithString", nullptr, CreateImageNodeWithString, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"disposeImageNode", nullptr, DisposeImageNode, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"setImageNodeWithTransformOptions", nullptr, SetImageNodeWithTransformOptions, nullptr, nullptr, nullptr,
         napi_default, nullptr},
        {"setImageNodeWithMatrix", nullptr, SetImageNodeWithMatrix, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"setImageNodeWithResizable", nullptr, SetImageNodeWithResizable, nullptr, nullptr, nullptr, napi_default,
         nullptr},
    };
    napi_default_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}
EXTERN_C_END

static napi_module demoModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "entry",
    .nm_priv = ((void *)0),
    .reserve = {0};
};

extern "C" __attribute__((constructor)) void RegisterEntryModule(void) { napi_module_register(&demoModule); }