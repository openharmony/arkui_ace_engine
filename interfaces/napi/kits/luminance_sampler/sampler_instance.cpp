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

#include "base/utils/utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "core/components_ng/render/adapter/rosen_luminance_sampling_helper.h"
#include "interfaces/napi/kits/utils/napi_utils.h"
#include "sampler_instance.h"


namespace OHOS::Ace::Napi {
namespace {
static constexpr uint32_t MIN_INTERVAL_VALUE = 180;
static constexpr uint32_t MIN_LUMINANCE_VALUE = 0;
static constexpr uint32_t MAX_LUMINANCE_VALUE = 255;
} // namespace
#define GET_PARAMS(env, info, max) \
    size_t argc = max;             \
    napi_value argv[max] = { 0 };  \
    napi_value thisVar = nullptr;  \
    void* data;                    \
    napi_get_cb_info(env, info, &argc, argv, &thisVar, &data)

static constexpr uint32_t PARAM_SIZE_ZERO = 0;
static constexpr uint32_t PARAM_SIZE_ONE = 1;

static constexpr size_t PARAM_INDEX_ZERO = 0;

SamplerInstance::SamplerInstance()
{
    targetNode_ = nullptr;
    samplingOptions_ = SamplingOptions();
}

void SamplerInstance::Destroy(napi_env env)
{
    DecRefCount();
}
bool SamplerInstance::SetTargetNode(int32_t targetNodeID)
{
    auto targetNodeElement = ElementRegister::GetInstance()->GetNodeById(targetNodeID);
    CHECK_NULL_RETURN(targetNodeElement, false);
    auto targetNode = AceType::DynamicCast<NG::FrameNode>(targetNodeElement);
    CHECK_NULL_RETURN(targetNode, false);
    targetNode_ = targetNode;
    return true;
}
void SamplerInstance::SetBackgroundLuminanceSamplingOptions(napi_env& env, napi_callback_info& info)
{
    auto samplingOptions = ParseSamplingOptions(env, info);
    if (!ParamsRangeCheck(env, samplingOptions)) {
        return;
    }
    if (!samplingOptions) {
        return;
    } else {
        samplingOptions_ = samplingOptions;
    }
    CHECK_NULL_VOID(samplingOptions_);
    SetSamplingOptionsToGraphic();
}

void SamplerInstance::SetSamplingOptionsToGraphic()
{
    CHECK_NULL_VOID(samplingOptions_);
    auto& value = samplingOptions_.value();
    NG::LuminanceSamplingHelper::SetSamplingOptions(
        targetNode_, value.samplingInterval, value.brightThreshold, value.darkThreshold, value.region);
}

void SamplerInstance::SetCallBackToGraphic()
{
    auto func = [weak = AceType::WeakClaim(this), node = targetNode_](uint32_t luminance) {
        auto samplerInstance = weak.Upgrade();
        CHECK_NULL_VOID(samplerInstance);
        for (const auto& listener : samplerInstance->samplingListeners_) {
            listener->OnLuminanceChange(luminance);
        }
    };
    if (samplingListeners_.size() > 0) {
        SetSamplingOptionsToGraphic();
        NG::LuminanceSamplingHelper::RegisterSamplingCallback(targetNode_, func);
    } else {
        NG::LuminanceSamplingHelper::UnRegisterSamplingCallback(targetNode_);
    }
}

void SamplerInstance::RegisterSamplingCallback(std::shared_ptr<SamplingListener> listener)
{
    bool findSameListener = false;
    for (const auto& registedListener : samplingListeners_) {
        napi_value napiInCallback = listener->GetNapiCallback();
        if (registedListener->NapiEqual(napiInCallback)) {
            findSameListener = true;
            break;
        }
    }
    if (!findSameListener) {
        samplingListeners_.emplace_back(listener);
    }
    SetCallBackToGraphic();
}

void SamplerInstance::UnRegisterSamplingCallback(std::shared_ptr<SamplingListener> listener)
{
    if (!listener) {
        NG::LuminanceSamplingHelper::UnRegisterSamplingCallback(targetNode_);
        return;
    }
    napi_value napiInCallback = listener->GetNapiCallback();
    samplingListeners_.erase(
        std::remove_if(
            samplingListeners_.begin(),
            samplingListeners_.end(),
            [napiInCallback](const std::shared_ptr<SamplingListener>& registeredListener) {
                return registeredListener->NapiEqual(napiInCallback);
            }
        ),
        samplingListeners_.end()
    );
    SetCallBackToGraphic();
}

void SamplerInstance::OnBackgroundLuminanceChange(napi_env& env, napi_callback_info& info)
{
    CHECK_NULL_VOID(targetNode_.Upgrade());
    GET_PARAMS(env, info, PARAM_SIZE_ONE);

    if (argc == PARAM_SIZE_ONE && MatchValueTypeLuminance(env, argv[PARAM_INDEX_ZERO], napi_function)) {
        auto listener = std::make_shared<SamplingListener>(env, argv[PARAM_INDEX_ZERO]);
        RegisterSamplingCallback(listener);
    }
}

void SamplerInstance::OffBackgroundLuminanceChange(napi_env& env, napi_callback_info& info)
{
    CHECK_NULL_VOID(targetNode_.Upgrade());
    GET_PARAMS(env, info, PARAM_SIZE_ONE);

    if (argc == PARAM_SIZE_ZERO) {
        UnRegisterSamplingCallback(nullptr);
        samplingListeners_.clear();
    }

    if (argc == PARAM_SIZE_ONE && MatchValueTypeLuminance(env, argv[PARAM_INDEX_ZERO], napi_function)) {
        auto listener = std::make_shared<SamplingListener>(env, argv[PARAM_INDEX_ZERO]);
        UnRegisterSamplingCallback(listener);
    }
}

bool SamplerInstance::ParamsRangeCheck(napi_env& env, std::optional<SamplingOptions>& options)
{
    if (options->samplingInterval < MIN_INTERVAL_VALUE) {
        options->samplingInterval = MIN_INTERVAL_VALUE;
    }
    if (options->brightThreshold < MIN_LUMINANCE_VALUE || options->brightThreshold > MAX_LUMINANCE_VALUE) {
        NapiThrow(env, "Incorrect parameter values: Param brightThreshold not in [0, 255].", ERROR_CODE_INTERNAL_ERROR);
        return false;
    }
    if (options->darkThreshold < MIN_LUMINANCE_VALUE || options->darkThreshold > MAX_LUMINANCE_VALUE) {
        NapiThrow(env, "Incorrect parameter values: Param darkThreshold not in [0, 255].", ERROR_CODE_INTERNAL_ERROR);
        return false;
    }
    if (options->darkThreshold > options->brightThreshold) {
        NapiThrow(env, "Incorrect parameter values: Param darkThreshold greater than brightThreshold.",
            ERROR_CODE_INTERNAL_ERROR);
        return false;
    }
    return true;
}

std::optional<SamplingOptions> SamplerInstance::ParseSamplingOptions(napi_env& env, napi_callback_info& info)
{
    size_t argc = 1;
    napi_value argv[1] = { nullptr };
    napi_value thisVar = nullptr;
    napi_status status = napi_get_cb_info(env, info, &argc, argv, &thisVar, nullptr);
    std::optional<SamplingOptions> result = SamplingOptions();
    napi_value samplingInterval = nullptr;
    napi_value brightThreshold = nullptr;
    napi_value darkThreshold = nullptr;
    napi_value region = nullptr;

    if (MatchValueTypeLuminance(env, argv[PARAM_INDEX_ZERO], napi_object)) {
        status = napi_get_named_property(env, argv[PARAM_INDEX_ZERO], "samplingInterval", &samplingInterval);
        if (status != napi_ok) {
            NapiThrow(env, "Incorrect parameters types: Failed to get 'samplingInterval' property.",
                ERROR_CODE_INTERNAL_ERROR);
            return result;
        }

        status = napi_get_named_property(env, argv[PARAM_INDEX_ZERO], "brightThreshold", &brightThreshold);
        if (status != napi_ok) {
            NapiThrow(env, "Incorrect parameters types: Failed to get 'brightThreshold' property.",
                ERROR_CODE_INTERNAL_ERROR);
            return result;
        }

        status = napi_get_named_property(env, argv[PARAM_INDEX_ZERO], "darkThreshold", &darkThreshold);
        if (status != napi_ok) {
            NapiThrow(
                env, "Incorrect parameters types: Failed to get 'darkThreshold' property.", ERROR_CODE_INTERNAL_ERROR);
            return result;
        }

        status = napi_get_named_property(env, argv[PARAM_INDEX_ZERO], "region", &region);
        if (status != napi_ok) {
            NapiThrow(env, "Incorrect parameters types: Failed to get 'region' property.", ERROR_CODE_INTERNAL_ERROR);
            return result;
        }

        OHOS::Ace::Napi::ParseIntLuminance(env, samplingInterval, result->samplingInterval);
        OHOS::Ace::Napi::ParseIntLuminance(env, brightThreshold, result->brightThreshold);
        OHOS::Ace::Napi::ParseIntLuminance(env, darkThreshold, result->darkThreshold);
        auto regionResult = EdgesParam();
        bool parseStatus = OHOS::Ace::Napi::ParseEdgesLengthMetrics(env, region, regionResult);
        if (parseStatus) {
            result->region = regionResult;
        }
    } else if (!MatchValueTypeLuminance(env, argv[PARAM_INDEX_ZERO], napi_undefined) &&
               !MatchValueTypeLuminance(env, argv[PARAM_INDEX_ZERO], napi_null)) {
        NapiThrow(
            env, "Incorrect parameters types: The type of SamplingOptions is incorrect.", ERROR_CODE_INTERNAL_ERROR);
        return result;
    }

    return result;
}

} // namespace OHOS::Ace::Napi
