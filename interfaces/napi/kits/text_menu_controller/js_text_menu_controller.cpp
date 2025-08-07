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

#include "interfaces/napi/kits/utils/napi_utils.h"

#include "frameworks/core/common/ace_application_info.h"
#include "frameworks/core/components_ng/pattern/select_overlay/select_overlay_property.h"

namespace OHOS::Ace::Napi {

static NG::SystemServiceMenuDisableFlag GetDisableFlag(const std::string& id)
{
    static std::unordered_map<std::string, NG::SystemServiceMenuDisableFlag> disalbeFlagsMap = {
        { NG::OH_DEFAULT_TRANSLATE, NG::DISABLE_TRANSLATE_FLAG },
        { NG::OH_DEFAULT_SEARCH, NG::DISABLE_SEARCH_FLAG },
        { NG::OH_DEFAULT_SHARE, NG::DISABLE_SHARE_FLAG },
        { NG::OH_DEFAULT_CAMERA_INPUT, NG::DISABLE_CAMERA_INPUT_FLAG },
        { NG::OH_DEFAULT_AI_WRITE, NG::DISABLE_AI_WRITER_FLAG },
        { NG::OH_DEFAULT_COLLABORATION_SERVICE, NG::DISABLE_COLLABORATION_SERVICE_FLAG },
        { NG::OH_DEFAULT_AI_MENU_URL, NG::DISABLE_AI_MENU_URL_FLAG },
        { NG::OH_DEFAULT_AI_MENU_PHONE, NG::DISABLE_AI_MENU_PHONE_FLAG },
        { NG::OH_DEFAULT_AI_MENU_EMAIL, NG::DISABLE_AI_MENU_EMAIL_FLAG },
        { NG::OH_DEFAULT_AI_MENU_ADDRESS, NG::DISABLE_AI_MENU_ADDRESS_FLAG },
        { NG::OH_DEFAULT_AI_MENU_DATETIME, NG::DISABLE_AI_MENU_DATETIME_FLAG },
        { NG::OH_DEFAULT_ASK_CELIA, NG::DISABLE_ASK_CELIA_FLAG },
    };
    return disalbeFlagsMap.find(id) == disalbeFlagsMap.end() ? NG::DISABLE_NORMAL_FLAG : disalbeFlagsMap[id];
}

static void DisableSystemServiceMenuItems(bool disableAll)
{
    auto textMenuInfo = AceApplicationInfo::GetInstance().GetTextMenuInfo();
    auto isPrevDisableAll = (textMenuInfo.disableFlags & NG::DISABLE_ALL_FLAG) == NG::DISABLE_ALL_FLAG;
    if (disableAll) {
        AceApplicationInfo::GetInstance().AddTextMenuDisableFlag(NG::DISABLE_ALL_FLAG);
    } else {
        AceApplicationInfo::GetInstance().SetTextMenuDisableFlags(~NG::DISABLE_ALL_FLAG);
    }
    if (isPrevDisableAll != disableAll && textMenuInfo.menuOnChangeCallback) {
        if (!textMenuInfo.menuOnChangeCallback()) {
            AceApplicationInfo::GetInstance().SetTextMenuOnChangeCallback(nullptr);
        }
    }
}

static void DisableTextMenuSystemItems(const std::vector<std::string>& menuItems)
{
    auto textMenuInfo = AceApplicationInfo::GetInstance().GetTextMenuInfo();
    auto oldFlags = textMenuInfo.disableFlags;
    AceApplicationInfo::GetInstance().SetTextMenuDisableFlags(NG::DISABLE_ALL_FLAG);
    for (const auto& item : menuItems) {
        AceApplicationInfo::GetInstance().AddTextMenuDisableFlag(GetDisableFlag(item));
    }
    if (oldFlags != AceApplicationInfo::GetInstance().GetTextMenuInfo().disableFlags &&
        textMenuInfo.menuOnChangeCallback) {
        if (!textMenuInfo.menuOnChangeCallback()) {
            AceApplicationInfo::GetInstance().SetTextMenuOnChangeCallback(nullptr);
        }
    }
}

static napi_value JSDisableSystemServiceMenuItems(napi_env env, napi_callback_info info)
{
    napi_handle_scope scope = nullptr;
    napi_open_handle_scope(env, &scope);
    CHECK_NULL_RETURN(scope, nullptr);
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value thisvar = nullptr;
    void* data = nullptr;
    status = napi_get_cb_info(env, info, &argc, argv, &thisvar, &data);
    if (status != napi_ok || argc < 1) {
        TAG_LOGE(AceLogTag::ACE_SELECT_OVERLAY, "Invalid arguments.");
        napi_close_handle_scope(env, scope);
        return nullptr;
    }
    napi_valuetype valueType = napi_undefined;
    status = napi_typeof(env, argv[0], &valueType);
    if (status != napi_ok || valueType != napi_boolean) {
        TAG_LOGE(AceLogTag::ACE_SELECT_OVERLAY, "Expected boolean.");
        DisableSystemServiceMenuItems(false);
        napi_close_handle_scope(env, scope);
        return nullptr;
    }
    bool disableAll = false;
    status = napi_get_value_bool(env, argv[0], &disableAll);
    if (status == napi_ok) {
        DisableSystemServiceMenuItems(disableAll);
    } else {
        TAG_LOGE(AceLogTag::ACE_SELECT_OVERLAY, "Failed to get boolean value.");
    }
    napi_close_handle_scope(env, scope);
    return nullptr;
}

static size_t GetStringLength(napi_env env, napi_value str)
{
    size_t buffSize = 0;
    napi_status status = napi_get_value_string_utf8(env, str, nullptr, 0, &buffSize);
    if (status != napi_ok || buffSize == 0) {
        return 0;
    }
    return buffSize;
}

static void ParseTextMenuItems(std::vector<std::string>& items, napi_env env, napi_value value, uint32_t length)
{
    napi_status status;
    for (uint32_t i = 0; i < length; i++) {
        napi_value element;
        status = napi_get_element(env, value, i, &element);
        if (status != napi_ok) {
            continue;
        }
        napi_valuetype valueType = napi_undefined;
        status = napi_typeof(env, element, &valueType);
        if (status != napi_ok || valueType != napi_object) {
            continue;
        }
        napi_value idValue;
        status = napi_get_named_property(env, element, "id_", &idValue);
        if (status != napi_ok) {
            continue;
        }
        status = napi_typeof(env, idValue, &valueType);
        if (status != napi_ok || valueType != napi_string) {
            continue;
        }
        size_t strLen = GetStringLength(env, idValue) + 1;
        std::unique_ptr<char[]> idString = std::make_unique<char[]>(strLen);
        size_t resultLen;
        napi_get_value_string_utf8(env, idValue, idString.get(), strLen, &resultLen);
        items.emplace_back(idString.get());
    }
}

static napi_value JSDisableMenuItems(napi_env env, napi_callback_info info)
{
    napi_handle_scope scope = nullptr;
    napi_open_handle_scope(env, &scope);
    CHECK_NULL_RETURN(scope, nullptr);
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value thisvar = nullptr;
    void* data = nullptr;
    status = napi_get_cb_info(env, info, &argc, argv, &thisvar, &data);
    if (status != napi_ok || argc < 1) {
        TAG_LOGE(AceLogTag::ACE_SELECT_OVERLAY, "Invalid arguments.");
        napi_close_handle_scope(env, scope);
        return nullptr;
    }
    bool isArray = false;
    status = napi_is_array(env, argv[0], &isArray);
    if (status != napi_ok || !isArray) {
        TAG_LOGE(AceLogTag::ACE_SELECT_OVERLAY, "Invalid argument type.");
        DisableTextMenuSystemItems({});
        napi_close_handle_scope(env, scope);
        return nullptr;
    }
    uint32_t length = 0;
    status = napi_get_array_length(env, argv[0], &length);
    if (status != napi_ok) {
        TAG_LOGE(AceLogTag::ACE_SELECT_OVERLAY, "Failed to get array length.");
        napi_close_handle_scope(env, scope);
        return nullptr;
    }
    std::vector<std::string> menuItems;
    ParseTextMenuItems(menuItems, env, argv[0], length);
    DisableTextMenuSystemItems(menuItems);
    napi_close_handle_scope(env, scope);
    return nullptr;
}

static napi_value textMenuControllerExport(napi_env env, napi_value exports)
{
    napi_property_descriptor textMenuControllerDesc[] = {
        DECLARE_NAPI_FUNCTION("disableSystemServiceMenuItems", JSDisableSystemServiceMenuItems),
        DECLARE_NAPI_FUNCTION("disableMenuItems", JSDisableMenuItems),
    };
    NAPI_CALL(env, napi_define_properties(env, exports,
                       sizeof(textMenuControllerDesc) / sizeof(textMenuControllerDesc[0]), textMenuControllerDesc));

    return exports;
}

static napi_module textMenuControllerModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = textMenuControllerExport,
    .nm_modname = "arkui.textMenuController",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void TextMenuControllerRegister()
{
    napi_module_register(&textMenuControllerModule);
}
} // namespace OHOS::Ace::Napi
