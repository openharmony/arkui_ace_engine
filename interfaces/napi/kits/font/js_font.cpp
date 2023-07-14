/*
 * Copyright (c) 2022 Shenzhen Kaihong Digital Industry Development Co., Ltd.
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

#include <string>

#include "interfaces/napi/kits/utils/napi_utils.h"
#include "napi/native_api.h"
#include "napi/native_engine/native_value.h"
#include "napi/native_node_api.h"

#include "bridge/common/utils/engine_helper.h"
#include "bridge/js_frontend/engine/common/js_engine.h"

namespace OHOS::Ace::Napi {
namespace {
constexpr size_t STR_BUFFER_SIZE = 1024;
constexpr int32_t FONT_INFO_INDEX_PATH = 0;
constexpr int32_t FONT_INFO_INDEX_POST_SCRIPT_NAME = 1;
constexpr int32_t FONT_INFO_INDEX_FULL_NAME = 2;
constexpr int32_t FONT_INFO_INDEX_FAMILY = 3;
constexpr int32_t FONT_INFO_INDEX_SUB_FAMILY = 4;
constexpr int32_t FONT_INFO_INDEX_WEIGHT = 5;
constexpr int32_t FONT_INFO_INDEX_WIDTH = 6;
constexpr int32_t FONT_INFO_INDEX_ITALIC = 7;
constexpr int32_t FONT_INFO_INDEX_MONOSPACE = 8;
constexpr int32_t FONT_INFO_INDEX_SYMBOLIC = 9;
constexpr int32_t FONT_INFO_INDEX_MAX = 10;
}

static bool ParseFamilyNameOrSrc(
    napi_env env, napi_value familyNameOrSrcNApi, std::string& familyNameOrSrc, napi_valuetype valueType)
{
    napi_typeof(env, familyNameOrSrcNApi, &valueType);
    if (valueType == napi_string) {
        size_t nameLen = 0;
        napi_get_value_string_utf8(env, familyNameOrSrcNApi, nullptr, 0, &nameLen);
        std::unique_ptr<char[]> name = std::make_unique<char[]>(nameLen + 1);
        napi_get_value_string_utf8(env, familyNameOrSrcNApi, name.get(), nameLen + 1, &nameLen);
        familyNameOrSrc = name.get();
    } else if (valueType == napi_object) {
        int32_t id = 0;
        int32_t type = 0;
        std::vector<std::string> params;
        if (!ParseResourceParam(env, familyNameOrSrcNApi, id, type, params)) {
            LOGE("can not parse resource info from input params.");
            return false;
        }
        if (!ParseString(id, type, params, familyNameOrSrc)) {
            LOGE("can not get family name or src from resource manager.");
            return false;
        }
    } else {
        LOGE("The parameter type of family name or src is incorrect.");
        return false;
    }
    return true;
}

static napi_value JSRegisterFont(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, &argv, &thisVar, &data);

    napi_value familyNameNApi = nullptr;
    napi_value familySrcNApi = nullptr;
    std::string familyName;
    std::string familySrc;

    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv, &valueType);
    if (valueType == napi_object) {
        napi_get_named_property(env, argv, "familyName", &familyNameNApi);
        napi_get_named_property(env, argv, "familySrc", &familySrcNApi);
    } else {
        return nullptr;
    }
    
    if (!ParseFamilyNameOrSrc(env, familyNameNApi, familyName, valueType)) {
        return nullptr;
    }

    if (!ParseFamilyNameOrSrc(env, familySrcNApi, familySrc, valueType)) {
        return nullptr;
    }

    auto delegate = EngineHelper::GetCurrentDelegate();
    if (!delegate) {
        LOGE("can not get delegate.");
        return nullptr;
    }
    delegate->RegisterFont(familyName, familySrc);
    return nullptr;
}

static napi_value JSgetSystemFontList(napi_env env, napi_callback_info info)
{
    napi_value arrayResult = nullptr;
    napi_create_array(env, &arrayResult);
    bool isArray = false;
    if (napi_is_array(env, arrayResult, &isArray) != napi_ok || !isArray) {
        return arrayResult;
    }
    std::vector<std::string> fontList;
    auto delegate = EngineHelper::GetCurrentDelegate();
    if (!delegate) {
        return nullptr;
    }
    delegate->GetSystemFontList(fontList);

    int32_t index = 0;
    for (const std::string& font : fontList) {
        napi_value result = nullptr;
        napi_create_string_utf8(env, font.c_str(), font.length(), &result);
        napi_set_element(env, arrayResult, index++, result);
    }
    return arrayResult;
}

static napi_value JSgetFontByName(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    void* data = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, &argv, &thisVar, &data));
    NAPI_ASSERT(env, argc == 1, "requires 1 parameter");

    napi_valuetype type;
    NAPI_CALL(env, napi_typeof(env, argv, &type));
    NAPI_ASSERT(env, type == napi_string, "type mismatch");
    char fontName[STR_BUFFER_SIZE] = { 0 };
    size_t len = 0;
    napi_get_value_string_utf8(env, argv, fontName, STR_BUFFER_SIZE, &len);
    NAPI_ASSERT(env, len < STR_BUFFER_SIZE, "condition string too long");
    std::string fontNameStr(fontName, len);

    FontInfo fontInfo;
    auto delegate = EngineHelper::GetCurrentDelegate();
    if (!delegate) {
        return nullptr;
    }
    if (!delegate->GetSystemFont(fontNameStr, fontInfo)) {
        return nullptr;
    }

    napi_value resultArray[FONT_INFO_INDEX_MAX] = { 0 };
    napi_create_string_utf8(env, fontInfo.path.c_str(), NAPI_AUTO_LENGTH, &resultArray[FONT_INFO_INDEX_PATH]);
    napi_create_string_utf8(env, fontInfo.postScriptName.c_str(), NAPI_AUTO_LENGTH,
        &resultArray[FONT_INFO_INDEX_POST_SCRIPT_NAME]);
    napi_create_string_utf8(env, fontInfo.fullName.c_str(), NAPI_AUTO_LENGTH, &resultArray[FONT_INFO_INDEX_FULL_NAME]);
    napi_create_string_utf8(env, fontInfo.family.c_str(), NAPI_AUTO_LENGTH, &resultArray[FONT_INFO_INDEX_FAMILY]);
    napi_create_string_utf8(env, fontInfo.subfamily.c_str(), NAPI_AUTO_LENGTH,
        &resultArray[FONT_INFO_INDEX_SUB_FAMILY]);
    napi_create_int32(env, fontInfo.weight, &resultArray[FONT_INFO_INDEX_WEIGHT]);
    napi_create_int32(env, fontInfo.width, &resultArray[FONT_INFO_INDEX_WIDTH]);
    napi_create_int32(env, fontInfo.italic, &resultArray[FONT_INFO_INDEX_ITALIC]);
    napi_create_int32(env, fontInfo.monoSpace, &resultArray[FONT_INFO_INDEX_MONOSPACE]);
    napi_create_int32(env, fontInfo.symbolic, &resultArray[FONT_INFO_INDEX_SYMBOLIC]);

    napi_value result = nullptr;
    napi_create_object(env, &result);
    napi_set_named_property(env, result, "path", resultArray[FONT_INFO_INDEX_PATH]);
    napi_set_named_property(env, result, "postScriptName", resultArray[FONT_INFO_INDEX_POST_SCRIPT_NAME]);
    napi_set_named_property(env, result, "fullName", resultArray[FONT_INFO_INDEX_FULL_NAME]);
    napi_set_named_property(env, result, "family", resultArray[FONT_INFO_INDEX_FAMILY]);
    napi_set_named_property(env, result, "subfamily", resultArray[FONT_INFO_INDEX_SUB_FAMILY]);
    napi_set_named_property(env, result, "weight", resultArray[FONT_INFO_INDEX_WEIGHT]);
    napi_set_named_property(env, result, "width", resultArray[FONT_INFO_INDEX_WIDTH]);
    napi_set_named_property(env, result, "italic", resultArray[FONT_INFO_INDEX_ITALIC]);
    napi_set_named_property(env, result, "monoSpace", resultArray[FONT_INFO_INDEX_MONOSPACE]);
    napi_set_named_property(env, result, "symbolic", resultArray[FONT_INFO_INDEX_SYMBOLIC]);

    return result;
}

static napi_value FontExport(napi_env env, napi_value exports)
{
    napi_property_descriptor fontDesc[] = {
        DECLARE_NAPI_FUNCTION("registerFont", JSRegisterFont),
        DECLARE_NAPI_FUNCTION("getSystemFontList", JSgetSystemFontList),
        DECLARE_NAPI_FUNCTION("getFontByName", JSgetFontByName)
    };
    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(fontDesc) / sizeof(fontDesc[0]), fontDesc));
    return exports;
}

static napi_module fontModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = FontExport,
    .nm_modname = "font",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void FontRegister()
{
    napi_module_register(&fontModule);
}
} // namespace OHOS::Ace::Napi
