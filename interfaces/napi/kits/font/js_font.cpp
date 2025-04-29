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


#include "interfaces/napi/kits/utils/napi_utils.h"

#include "bridge/common/utils/engine_helper.h"
#include "core/common/font_manager.h"

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

static bool ParseFamilyNameOrSrc(napi_env env, napi_value familyNameOrSrcNApi, std::string& familyNameOrSrc,
    napi_valuetype valueType, ResourceInfo& info)
{
    napi_typeof(env, familyNameOrSrcNApi, &valueType);
    if (valueType == napi_string) {
        size_t nameLen = 0;
        napi_get_value_string_utf8(env, familyNameOrSrcNApi, nullptr, 0, &nameLen);
        std::unique_ptr<char[]> name = std::make_unique<char[]>(nameLen + 1);
        napi_get_value_string_utf8(env, familyNameOrSrcNApi, name.get(), nameLen + 1, &nameLen);
        familyNameOrSrc = name.get();
    } else if (valueType == napi_object) {
        if (!ParseResourceParam(env, familyNameOrSrcNApi, info)) {
            return false;
        }
        if (!ParseString(info, familyNameOrSrc)) {
            return false;
        }
    } else {
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

    ResourceInfo resourceInfo;
    if (!ParseFamilyNameOrSrc(env, familyNameNApi, familyName, valueType, resourceInfo)) {
        return nullptr;
    }
    if (!ParseFamilyNameOrSrc(env, familySrcNApi, familySrc, valueType, resourceInfo)) {
        return nullptr;
    }

    std::string bundleName = resourceInfo.bundleName.has_value() ? resourceInfo.bundleName.value() : "";
    std::string moduleName = resourceInfo.moduleName.has_value() ? resourceInfo.moduleName.value() : "";
    auto container = Container::CurrentSafely();
    if (bundleName.empty() && container) {
        bundleName = container->GetBundleName();
    }
    if (moduleName.empty() && container) {
        moduleName = container->GetModuleName();
    }
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        return nullptr;
    }
    TAG_LOGI(AceLogTag::ACE_FONT, "begin to register font.");
    delegate->RegisterFont(familyName, familySrc, bundleName, moduleName);
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
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
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
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
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
    napi_get_boolean(env, fontInfo.italic, &resultArray[FONT_INFO_INDEX_ITALIC]);
    napi_get_boolean(env, fontInfo.monoSpace, &resultArray[FONT_INFO_INDEX_MONOSPACE]);
    napi_get_boolean(env, fontInfo.symbolic, &resultArray[FONT_INFO_INDEX_SYMBOLIC]);

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

static napi_value GetUIFontGenericInfo(napi_env env, const FontConfigJsonInfo& fontConfigJsonInfo)
{
    napi_value genericSetResult = nullptr;
    napi_create_array(env, &genericSetResult);
    int32_t index = 0;
    for (const FontGenericInfo& generic: fontConfigJsonInfo.genericSet) {
        napi_value genericResult = nullptr;
        napi_create_object(env, &genericResult);
        napi_value familyResult = nullptr;
        napi_create_string_utf8(env, generic.familyName.c_str(), generic.familyName.length(), &familyResult);
        napi_value aliasSetResult = nullptr;
        napi_create_array(env, &aliasSetResult);
        int32_t index2 = 0;
        for (const AliasInfo& alias: generic.aliasSet) {
            napi_value aliasResult = nullptr;
            napi_create_object(env, &aliasResult);
            napi_value familyNameResult = nullptr;
            napi_create_string_utf8(env, alias.familyName.c_str(), alias.familyName.length(), &familyNameResult);
            napi_value weightResult = nullptr;
            napi_create_int32(env, alias.weight, &weightResult);
            napi_set_named_property(env, aliasResult, "name", familyNameResult);
            napi_set_named_property(env, aliasResult, "weight", weightResult);
            napi_set_element(env, aliasSetResult, index2++, aliasResult);
        }
        index2 = 0;
        napi_value adjustSetResult = nullptr;
        napi_create_array(env, &adjustSetResult);
        for (const AdjustInfo& adjust: generic.adjustSet) {
            napi_value adjustResult = nullptr;
            napi_create_object(env, &adjustResult);
            napi_value weightResult = nullptr;
            napi_create_int32(env, adjust.origValue, &weightResult);
            napi_value toResult = nullptr;
            napi_create_int32(env, adjust.newValue, &toResult);
            napi_set_named_property(env, adjustResult, "weight", weightResult);
            napi_set_named_property(env, adjustResult, "to", toResult);
            napi_set_element(env, adjustSetResult, index2++, adjustResult);
        }
        napi_set_named_property(env, genericResult, "family", familyResult);
        napi_set_named_property(env, genericResult, "alias", aliasSetResult);
        napi_set_named_property(env, genericResult, "adjust", adjustSetResult);
        napi_set_element(env, genericSetResult, index++, genericResult);
    }
    return genericSetResult;
}

static napi_value GetUIFontFallbackInfo(napi_env env, const FontConfigJsonInfo& fontConfigJsonInfo)
{
    napi_value fallbackGroupSetResult = nullptr;
    napi_create_array(env, &fallbackGroupSetResult);
    int32_t index = 0;
    for (const FallbackGroup& fallbackGroup: fontConfigJsonInfo.fallbackGroupSet) {
        napi_value fallbackGroupResult = nullptr;
        napi_create_object(env, &fallbackGroupResult);
        napi_value fontSetNameResult = nullptr;
        napi_create_string_utf8(env, fallbackGroup.groupName.c_str(),
            fallbackGroup.groupName.length(), &fontSetNameResult);
        napi_value fallbackListResult = nullptr;
        napi_create_array(env, &fallbackListResult);
        int32_t index2 = 0;
        for (const FallbackInfo& fallback: fallbackGroup.fallbackInfoSet) {
            napi_value fallbackResult = nullptr;
            napi_create_object(env, &fallbackResult);
            napi_value familyResult = nullptr;
            napi_create_string_utf8(env, fallback.familyName.c_str(), fallback.familyName.length(), &familyResult);
            napi_value languageResult = nullptr;
            napi_create_string_utf8(env, fallback.font.c_str(), fallback.font.length(), &languageResult);

            napi_set_named_property(env, fallbackResult, "language", languageResult);
            napi_set_named_property(env, fallbackResult, "family", familyResult);
            napi_set_element(env, fallbackListResult, index2++, fallbackResult);
        }
        napi_set_named_property(env, fallbackGroupResult, "fontSetName", fontSetNameResult);
        napi_set_named_property(env, fallbackGroupResult, "fallback", fallbackListResult);
        napi_set_element(env, fallbackGroupSetResult, index++, fallbackGroupResult);
    }
    return fallbackGroupSetResult;
}

static napi_value JsGetUIFontConfig(napi_env env, napi_callback_info info)
{
    FontConfigJsonInfo fontConfigJsonInfo;
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        return nullptr;
    }
    delegate->GetUIFontConfig(fontConfigJsonInfo);
    napi_value result = nullptr;
    napi_create_object(env, &result);
    napi_value fontDirSetResult = nullptr;
    napi_create_array(env, &fontDirSetResult);
    int32_t index = 0;
    for (const std::string& fontDir : fontConfigJsonInfo.fontDirSet) {
        napi_value fontDirResult = nullptr;
        napi_create_string_utf8(env, fontDir.c_str(), fontDir.length(), &fontDirResult);
        napi_set_element(env, fontDirSetResult, index++, fontDirResult);
    }
    napi_value genericSetResult = GetUIFontGenericInfo(env, fontConfigJsonInfo);
    napi_value fallbackGroupSetResult = GetUIFontFallbackInfo(env, fontConfigJsonInfo);

    napi_set_named_property(env, result, "fontDir", fontDirSetResult);
    napi_set_named_property(env, result, "generic", genericSetResult);
    napi_set_named_property(env, result, "fallbackGroups", fallbackGroupSetResult);
    return result;
}

static napi_value FontExport(napi_env env, napi_value exports)
{
    napi_property_descriptor fontDesc[] = {
        DECLARE_NAPI_FUNCTION("registerFont", JSRegisterFont),
        DECLARE_NAPI_FUNCTION("getSystemFontList", JSgetSystemFontList),
        DECLARE_NAPI_FUNCTION("getFontByName", JSgetFontByName),
        DECLARE_NAPI_FUNCTION("getUIFontConfig", JsGetUIFontConfig)
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
