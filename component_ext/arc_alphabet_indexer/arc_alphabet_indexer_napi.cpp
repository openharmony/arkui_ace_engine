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

#include "arc_alphabet_indexer_napi.h"
#include "ext_napi_utils.h"
#include "core/components_ng/pattern/indexer/indexer_model_ng.h"

extern const char _binary_arkui_arcalphabetindexer_abc_start[];

extern const char _binary_arkui_arcalphabetindexer_abc_end[];

namespace OHOS::Ace {
namespace {
static constexpr const size_t MAX_ARG_NUM = 10;
} // namespace

std::unique_ptr<IndexerModel> IndexerModel::instance_ = nullptr;
std::mutex IndexerModel::mutex_;

IndexerModel* IndexerModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
            instance_.reset(new NG::IndexerModelNG());
        }
    }
    return instance_.get();
}

napi_value JsCreate(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_ARG_NUM;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr));
    if (argc > 0 && ExtNapiUtils::CheckTypeForNapiValue(env, argv[0], napi_object)) {
        napi_value jsArrayValue = ExtNapiUtils::GetNamedProperty(env, argv[0], "arrayValue");
        if (!ExtNapiUtils::IsArray(env, jsArrayValue)) {
            return ExtNapiUtils::CreateNull(env);
        }
        uint32_t length = 0;
        std::vector<std::string> indexerArray;
        int32_t selectedVal = 0;
        napi_get_array_length(env, jsArrayValue, &length);
        for (uint32_t i = 0; i < length; i++) {
            napi_value elementValue;
            napi_get_element(env, jsArrayValue, i, &elementValue);
            std::string valueString = ExtNapiUtils::GetStringFromValueUtf8(env, elementValue);
            indexerArray.emplace_back(valueString);
        }
        napi_value jsSelected = ExtNapiUtils::GetNamedProperty(env, argv[0], "selected");
        if (ExtNapiUtils::CheckTypeForNapiValue(env, jsSelected, napi_number)) {
            selectedVal = ExtNapiUtils::GetCInt32(env, jsSelected);
        }
        selectedVal = selectedVal < 0 ? 0 : selectedVal;
        IndexerModel::GetInstance()->Create(indexerArray, selectedVal, true);
    }
    return ExtNapiUtils::CreateNull(env);
}

napi_value InitArcAlphabetIndexer(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        DECLARE_NAPI_FUNCTION("create", JsCreate),
    };
    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
    return exports;
}

napi_value ExportArcAlphabetIndexer(napi_env env, napi_value exports)
{
    InitArcAlphabetIndexer(env, exports);
    return exports;
}

} // namespace OHOS::Ace

// arkui_arcalphabetindexer JS register
extern "C" ACE_FORCE_EXPORT void NAPI_arkui_ArcAlphabetIndexer_GetABCCode(const char** buf,
    int* buflen)
{
    if (buf != nullptr) {
        *buf = _binary_arkui_arcalphabetindexer_abc_start;
    }
    if (buflen != nullptr) {
        *buflen = _binary_arkui_arcalphabetindexer_abc_end - _binary_arkui_arcalphabetindexer_abc_start;
    }
}

static napi_module arcAlphabetIndexerModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = OHOS::Ace::ExportArcAlphabetIndexer,
    .nm_modname = "arkui.ArcAlphabetIndexer",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterArcAlphabetIndexerModule()
{
    napi_module_register(&arcAlphabetIndexerModule);
}
