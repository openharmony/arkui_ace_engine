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

#include "core/common/container_consts.h"
#include "core/pipeline/base/element_register.h"
#include "frameworks/base/utils/string_utils.h"
#include "interfaces/inner_api/ace_kit/include/ui/base/ace_type.h"
#include "interfaces/napi/kits/utils/napi_utils.h"
#include "interfaces/napi/kits/luminance_sampler/js_luminance_sampler.h"

namespace OHOS::Ace::Napi {
static const TargetInfo INVALID_TARGET_INFO = TargetInfo();
static constexpr uint32_t PARAM_SIZE_TWO = 2;

LuminanceSampler::LuminanceSampler() {}

LuminanceSampler& LuminanceSampler::GetInstance()
{
    static LuminanceSampler instance;
    return instance;
}

bool LuminanceSampler::GetFrameNodeTargetID(TargetInfo& info, int32_t& result)
{
    result = -1;
    if (info == INVALID_TARGET_INFO) {
        return false;
    }
    if (info.idIsNumber) {
        result = StringUtils::StringToInt(info.id);
    } else {
        std::string targetIdString = info.id;
        auto componentId = info.componentId;
        if (componentId != -1) {
            auto targetComponentIdNode =
                ElementRegister::GetInstance()->GetSpecificItemById<NG::UINode>(componentId);
            CHECK_NULL_RETURN(targetComponentIdNode, false);
            auto targetNode = NG::FrameNode::FindChildByNameUINode(targetComponentIdNode, targetIdString);
            CHECK_NULL_RETURN(targetNode, false);
            result = targetNode->GetId();
        } else {
            auto targetNode =
                ElementRegister::GetInstance()->GetAttachedFrameNodeById(targetIdString, false, Container::CurrentId());
            if (!targetNode) {
                targetNode = ElementRegister::GetInstance()->GetAttachedFrameNodeById(targetIdString);
            }
            CHECK_NULL_RETURN(targetNode, false);
            result = targetNode->GetId();
        }
    }
    if (result < 0) {
        return false;
    }
    return true;
}

TargetInfo LuminanceSampler::ParseTargetInfo(napi_env& env, napi_callback_info& info)
{
    size_t argc = 2;
    napi_value argv[2] = { nullptr };
    napi_value thisVar = nullptr;
    napi_status status = napi_get_cb_info(env, info, &argc, argv, &thisVar, nullptr);

    TargetInfo result;
    napi_value targetInfoId = nullptr;
    napi_value targetInfoComponentId = nullptr;
    napi_valuetype valueType = napi_undefined;

    if (argc < PARAM_SIZE_TWO) {
        return result;
    }

    status = napi_typeof(env, argv[0], &valueType);

    status = napi_typeof(env, argv[1], &valueType);
    if (status != napi_ok) {
        NapiThrow(env, "Incorrect parameters types: Failed to get argument type.", ERROR_CODE_INTERNAL_ERROR);
        return result;
    }

    if (valueType == napi_object) {
        status = napi_get_named_property(env, argv[1], "id", &targetInfoId);
        if (status != napi_ok) {
            NapiThrow(env, "Incorrect parameters types: Failed to get 'id' property.", ERROR_CODE_INTERNAL_ERROR);
            return result;
        }

        status = napi_get_named_property(env, argv[1], "componentId", &targetInfoComponentId);
        if (status != napi_ok) {
            NapiThrow(
                env, "Incorrect parameters types: Failed to get 'componentId' property.", ERROR_CODE_INTERNAL_ERROR);
            return result;
        }

        napi_valuetype idType;
        status = napi_typeof(env, targetInfoId, &idType);
        if (status != napi_ok) {
            NapiThrow(env, "Incorrect parameters types: Failed to get 'id' type.", ERROR_CODE_INTERNAL_ERROR);
            return result;
        }

        if (idType == napi_string) {
            size_t idLength = 0;
            status = napi_get_value_string_utf8(env, targetInfoId, nullptr, 0, &idLength);
            std::unique_ptr<char[]> idValue = std::make_unique<char[]>(idLength + 1);
            napi_get_value_string_utf8(env, targetInfoId, idValue.get(), idLength + 1, &idLength);
            if (status != napi_ok) {
                NapiThrow(
                    env, "Incorrect parameters types: Failed to get 'id' value as string.", ERROR_CODE_INTERNAL_ERROR);
                return result;
            }
            result.id = std::string(idValue.get(), idLength);
            result.idIsNumber = false;
        } else if (idType == napi_number) {
            int32_t idValue;
            status = napi_get_value_int32(env, targetInfoId, &idValue);
            if (status != napi_ok) {
                NapiThrow(
                    env, "Incorrect parameters types: Failed to get 'id' value as number.", ERROR_CODE_INTERNAL_ERROR);
                return result;
            }
            result.id = std::to_string(idValue);
            result.idIsNumber = true;
        } else {
            NapiThrow(env, "Incorrect parameters types: The type of 'id' is incorrect.", ERROR_CODE_INTERNAL_ERROR);
            return result;
        }

        if (targetInfoComponentId != nullptr) {
            napi_valuetype componentIdType;
            status = napi_typeof(env, targetInfoComponentId, &componentIdType);
            if (status != napi_ok) {
                NapiThrow(
                    env, "Incorrect parameters types: Failed to get 'componentId' type.", ERROR_CODE_INTERNAL_ERROR);
                return result;
            }

            if (componentIdType == napi_number) {
                int32_t componentIdValue;
                status = napi_get_value_int32(env, targetInfoComponentId, &componentIdValue);
                if (status != napi_ok) {
                    NapiThrow(env, "Incorrect parameters types: Failed to get 'componentId' value as number.",
                        ERROR_CODE_INTERNAL_ERROR);
                    return result;
                }
                result.componentId = componentIdValue;
            } else if (componentIdType != napi_undefined && componentIdType != napi_null) {
                NapiThrow(env, "Incorrect parameters types: The type of 'componentId' is incorrect.",
                    ERROR_CODE_INTERNAL_ERROR);
                return result;
            }
        }
    } else if (valueType != napi_undefined && valueType != napi_null) {
        NapiThrow(env, "Incorrect parameters types: The type of parameters is incorrect.", ERROR_CODE_INTERNAL_ERROR);
        return result;
    }

    return result;
}

SamplerInstance* LuminanceSampler::GetSamplerInstance(napi_env env, napi_callback_info info)
{
    SamplerInstance* samplerInstance = nullptr;
    napi_value thisVar;
    napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr);
    napi_unwrap(env, thisVar, reinterpret_cast<void**>(&samplerInstance));
    return samplerInstance;
}

napi_value LuminanceSampler::JSSetBackgroundLuminanceSamplingOptions(napi_env env, napi_callback_info info)
{
    auto samplerInstance = GetSamplerInstance(env, info);
    if (!samplerInstance) {
        return nullptr;
    }
    samplerInstance->SetBackgroundLuminanceSamplingOptions(env, info);
    return nullptr;
}

napi_value LuminanceSampler::JSOnBackgroundLuminanceChange(napi_env env, napi_callback_info info)
{
    auto samplerInstance = GetSamplerInstance(env, info);
    if (!samplerInstance) {
        return nullptr;
    }
    samplerInstance->OnBackgroundLuminanceChange(env, info);
    return nullptr;
}

napi_value LuminanceSampler::JSOffBackgroundLuminanceChange(napi_env env, napi_callback_info info)
{
    auto samplerInstance = GetSamplerInstance(env, info);
    if (!samplerInstance) {
        return nullptr;
    }
    samplerInstance->OffBackgroundLuminanceChange(env, info);
    return nullptr;
}

napi_value LuminanceSampler::CreateJSSamplerInstance(napi_env env, SamplerInstance* samplerInstance)
{
    napi_value jsSampler = nullptr;
    napi_create_object(env, &jsSampler);
    napi_wrap(
        env, jsSampler, samplerInstance,
        [](napi_env env, void* data, void* hint) {
            SamplerInstance* samplerInstance = (SamplerInstance*)data;
            // release four references(onFunc) before releasing samplerInstance
            samplerInstance->Destroy(env);
        },
        nullptr, nullptr);
    napi_property_descriptor resultFuncs[] = {
        DECLARE_NAPI_FUNCTION("setBackgroundLuminanceSamplingConfigs", JSSetBackgroundLuminanceSamplingOptions),
        DECLARE_NAPI_FUNCTION("onBackgroundLuminanceChange", JSOnBackgroundLuminanceChange),
        DECLARE_NAPI_FUNCTION("offBackgroundLuminanceChange", JSOffBackgroundLuminanceChange)
    };

    NAPI_CALL(env, napi_define_properties(env, jsSampler, sizeof(resultFuncs) / sizeof(resultFuncs[0]), resultFuncs));
    return jsSampler;
}

RefPtr<NG::FrameNode> LuminanceSampler::GetTargetFrameNode(int32_t targetNodeID)
{
    auto targetNodeElement = ElementRegister::GetInstance()->GetNodeById(targetNodeID);
    CHECK_NULL_RETURN(targetNodeElement, nullptr);
    auto targetNode = AceType::DynamicCast<NG::FrameNode>(targetNodeElement);
    return targetNode;
}

napi_value LuminanceSampler::JSGetOrCreateLuminanceSampler(napi_env& env, napi_callback_info& info)
{
    auto targetInfo = ParseTargetInfo(env, info);

    int32_t targetInfoId = -1;
    if (!GetFrameNodeTargetID(targetInfo, targetInfoId)) {
        return nullptr;
    }
    auto targetNodePtr = GetTargetFrameNode(targetInfoId);
    CHECK_NULL_RETURN(targetNodePtr, nullptr);
    auto registedInstance = targetNodePtr->GetSamplerManager();
    TAG_LOGD(AceLogTag::ACE_VISUAL_EFFECT,
        "LuminanceSampling | {id:%{public}d,tag:%{public}s,inspectorId:%{public}s} | registedInstance: %{public}d",
        targetNodePtr->GetId(), targetNodePtr->GetTag().c_str(), targetNodePtr->GetInspectorId().value_or("").c_str(),
        registedInstance ? 1 : 0);
    if (!registedInstance) {
        SamplerInstance* samplerInstance = new SamplerInstance();
        samplerInstance->IncRefCount();
        if (!samplerInstance->SetTargetNode(targetInfoId)) {
            samplerInstance->DecRefCount();
            return nullptr;
        }
        auto newSamplerInstance = CreateJSSamplerInstance(env, samplerInstance);
        RefPtr<NG::SamplerManager> newSamplerInstanceRef =
            AceType::MakeRefPtr<SamplerManagerImpl>(env, newSamplerInstance);
        targetNodePtr->SetSamplerManager(newSamplerInstanceRef);
        return newSamplerInstance;
    }
    auto registedInstanceImpl = AceType::DynamicCast<SamplerManagerImpl>(registedInstance);
    CHECK_NULL_RETURN(registedInstanceImpl, nullptr);
    auto jsInstance = registedInstanceImpl->GetJSInstance();
    return jsInstance;
}

napi_value GetOrCreateLuminanceSampler(napi_env env, napi_callback_info info)
{
    return LuminanceSampler::GetInstance().JSGetOrCreateLuminanceSampler(env, info);
}

static napi_value LuminanceSamplerExport(napi_env env, napi_value exports)
{
    napi_property_descriptor properties[] = {
        DECLARE_NAPI_FUNCTION("getOrCreateLuminanceSampler", GetOrCreateLuminanceSampler),
    };
    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(properties) / sizeof(properties[0]), properties));
    return exports;
}

static napi_module luminance_sampler_module = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = LuminanceSamplerExport,
    .nm_modname = "luminancesampler",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterLuminanceSampler()
{
    napi_module_register(&luminance_sampler_module);
}
} // namespace OHOS::Ace::Napi
