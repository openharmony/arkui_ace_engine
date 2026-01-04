/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node.h"
#ifdef FORM_SUPPORTED
#include "core/components_ng/pattern/form/form_model_ng.h"
#include "core/components_ng/pattern/form/form_model_static_ng.h"
#endif
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "arkoala_api_generated.h"
#include "core/components/common/layout/constants.h"
#include "core/components/form/resource/form_request_data.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_static.h"
#include "core/components_ng/pattern/counter/counter_model_ng.h"
#include "core/components_ng/pattern/counter/counter_node.h"
#include "core/interfaces/native/utility/validators.h"
namespace OHOS::Ace::NG {
struct OptRequestFormInfo {
    std::optional<int64_t> id = std::nullopt;
    std::string name;
    std::string bundle;
    std::string ability;
    std::string module;
    std::optional<int32_t> dimension = std::nullopt;
    std::optional<bool> temporary = std::nullopt;
    RefPtr<WantWrap> want = nullptr;
    std::optional<int32_t> renderingMode = std::nullopt;
    std::optional<int32_t> shape = std::nullopt;
    std::optional<bool> exemptAppLock = std::nullopt;
};
struct LiteralDimension {
    Dimension width;
    Dimension height;
};
namespace {
const auto FORM_SHAPE_RECT = 1;
const auto FORM_SHAPE_CIRCLE = 2;
const auto FORM_RENDERING_MODE_FULL_COLOR = 0;
const auto FORM_RENDERING_MODE_SINGLE_COLOR = 1;
const auto FORM_DIMENSION_DIMENSION_1_2 = 1;
const auto FORM_DIMENSION_DIMENSION_2_2 = 2;
const auto FORM_DIMENSION_DIMENSION_2_4 = 3;
const auto FORM_DIMENSION_DIMENSION_4_4 = 4;
const auto FORM_DIMENSION_DIMENSION_1_1 = 6;
const auto FORM_DIMENSION_DIMENSION_6_4 = 7;
const auto FORM_DIMENSION_DIMENSION_2_3 = 8;
const auto FORM_DIMENSION_DIMENSION_3_3 = 9;
const auto FORM_COMPONENT_ID_KEY = "id";
const auto FORM_COMPONENT_ID_STRING_KEY = "idString";
const auto FORM_COMPONENT_IS_LOCKED_KEY = "isLocked";
const uint32_t FORM_ON_ACQUIRED_ID_INVALID = -1;
const std::string FORM_ON_ACQUIRED_ID_STRING_INVALID = "-1";
const uint32_t MIN_UNSIGNED_NUMBER_OF_ARK = 0;
const uint32_t MAX_UNSIGNED_NUMBER_OF_ARK = UINT_MAX;
const auto FORM_ON_ERROR_CODE_KEY = "errcode";
const auto FORM_ON_ERROR_MSG_KEY = "msg";
const auto ROUTER_CODE_ACTION_KEY = "action";
const auto ROUTER_CODE_BUNDLE_NAME_KEY = "bundleName";
const auto ROUTER_CODE_MODULE_NAME_KEY = "moduleName";
const auto ROUTER_CODE_ABILITY_NAME_KEY = "abilityName";
const auto ROUTER_CODE_PARAMS_KEY = "params";
const int32_t FORM_ON_ERROR_CODE_INVALID = -1;
const std::string FORM_EMPTY_STRING = "";
const int32_t MIN_SIGNED_NUMBER_OF_ARK = INT_MIN;
const int32_t MAX_SIGNED_NUMBER_OF_ARK = INT_MAX;
const int32_t TYPE_INT = 0;
} // namespace
namespace Converter {
template<>
OptRequestFormInfo Convert(const Ark_FormInfo& src)
{
    OptRequestFormInfo dst;
    if (src.id.selector == TYPE_INT) {
        dst.id = Converter::OptConvert<int64_t>(src.id.value0);
    } else {
        dst.id = StringUtils::StringToLongInt(Converter::OptConvert<std::string>(src.id.value1).value_or("-1"), -1);
    }
    dst.name = Converter::Convert<std::string>(src.name);
    dst.bundle = Converter::Convert<std::string>(src.bundle);
    dst.ability = Converter::Convert<std::string>(src.ability);
    dst.module = Converter::Convert<std::string>(src.module);
    dst.dimension = Converter::OptConvert<int32_t>(src.dimension);
    dst.temporary = Converter::OptConvert<bool>(src.temporary);
    dst.renderingMode = Converter::OptConvert<int32_t>(src.renderingMode);
    dst.shape = Converter::OptConvert<int32_t>(src.shape);
    dst.exemptAppLock = Converter::OptConvert<bool>(src.exemptAppLock);
    return dst;
}
template<>
void AssignCast(std::optional<int32_t>& dst, const Ark_FormShape& src)
{
    switch (src) {
        case ARK_FORM_SHAPE_RECT: dst = FORM_SHAPE_RECT; break;
        case ARK_FORM_SHAPE_CIRCLE: dst = FORM_SHAPE_CIRCLE; break;
        default: LOGE("Unexpected enum value in Ark_FormRenderingMode: %{public}d", src);
    }
}
template<>
void AssignCast(std::optional<int32_t>& dst, const Ark_FormRenderingMode& src)
{
    switch (src) {
        case ARK_FORM_RENDERING_MODE_FULL_COLOR: dst = FORM_RENDERING_MODE_FULL_COLOR; break;
        case ARK_FORM_RENDERING_MODE_SINGLE_COLOR: dst = FORM_RENDERING_MODE_SINGLE_COLOR; break;
        default: LOGE("Unexpected enum value in Ark_FormRenderingMode: %{public}d", src);
    }
}
template<>
LiteralDimension Convert(const Ark_FormSize& src)
{
    return LiteralDimension {
        .width = Dimension(Converter::Convert<double>(src.width)),
        .height = Dimension(Converter::Convert<double>(src.height)),
    };
}
template<>
void AssignCast(std::optional<int32_t>& dst, const Ark_FormDimension& src)
{
    switch (src) {
        case ARK_FORM_DIMENSION_DIMENSION_1_2: dst = FORM_DIMENSION_DIMENSION_1_2; break;
        case ARK_FORM_DIMENSION_DIMENSION_2_2: dst = FORM_DIMENSION_DIMENSION_2_2; break;
        case ARK_FORM_DIMENSION_DIMENSION_2_4: dst = FORM_DIMENSION_DIMENSION_2_4; break;
        case ARK_FORM_DIMENSION_DIMENSION_4_4: dst = FORM_DIMENSION_DIMENSION_4_4; break;
        case ARK_FORM_DIMENSION_DIMENSION_1_1: dst = FORM_DIMENSION_DIMENSION_1_1; break;
        case ARK_FORM_DIMENSION_DIMENSION_6_4: dst = FORM_DIMENSION_DIMENSION_6_4; break;
        case ARK_FORM_DIMENSION_DIMENSION_2_3: dst = FORM_DIMENSION_DIMENSION_2_3; break;
        case ARK_FORM_DIMENSION_DIMENSION_3_3: dst = FORM_DIMENSION_DIMENSION_3_3; break;
        default: LOGE("Unexpected enum value in Ark_FormDimension: %{public}d", src);
    }
}
} // namespace OHOS::Ace::NG::Converter
} // namespace OHOS::Ace::NG
namespace OHOS::Ace::NG::GeneratedModifier {
namespace FormComponentModifier {
const bool DEFAULT_ALLOW_UPDATE = true;
const int32_t DEFAULT_DIMENSION = -1;
const std::string DEFAULT_MODULE_NAME;

Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
#ifdef FORM_SUPPORTED
    auto frameNode = FormModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
#else
    return {};
#endif
}
} // FormComponentModifier
namespace FormComponentInterfaceModifier {
void SetFormComponentOptionsImpl(Ark_NativePointer node,
                                 const Ark_FormInfo* value)
{
#ifdef FORM_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optRequestFormInfo = Converter::Convert<OptRequestFormInfo>(*value);
    RequestFormInfo formInfo;
    if (optRequestFormInfo.id) {
        formInfo.id = optRequestFormInfo.id.value();
    }
    formInfo.cardName = optRequestFormInfo.name;
    formInfo.bundleName = optRequestFormInfo.bundle;
    formInfo.abilityName = optRequestFormInfo.ability;
    formInfo.moduleName = optRequestFormInfo.module;
    formInfo.wantWrap = WantWrap::CreateWantWrap(formInfo.bundleName, formInfo.abilityName);
    if (optRequestFormInfo.dimension) {
        formInfo.dimension = optRequestFormInfo.dimension.value();
    }
    if (optRequestFormInfo.temporary) {
        formInfo.temporary = optRequestFormInfo.temporary.value();
    }
    if (optRequestFormInfo.renderingMode) {
        formInfo.renderingMode = optRequestFormInfo.renderingMode.value();
    }
    if (optRequestFormInfo.shape) {
        formInfo.shape = optRequestFormInfo.shape.value();
    }
    if (optRequestFormInfo.exemptAppLock) {
        formInfo.exemptAppLock = optRequestFormInfo.exemptAppLock.value();
    }
    FormModelStatic::UpdateProperty(formInfo);
    FormModelStatic::SetModuleName(frameNode, formInfo.moduleName);
#endif // FORM_SUPPORTED
}
} // FormComponentInterfaceModifier
namespace FormComponentAttributeModifier {
void SetWidthInternal(FrameNode *frameNode, std::optional<Dimension> value)
{
    Validator::ValidateNonNegative(value);
    if (!value) {
        LOGE("width value is null.");
        ViewAbstract::ClearWidthOrHeight(frameNode, true);
        return;
    }
    ViewAbstractModelStatic::SetWidth(frameNode, *value);
}
void SetHeightInternal(FrameNode *frameNode, std::optional<Dimension> value)
{
    Validator::ValidateNonNegative(value);
    if (!value) {
        LOGE("height value is null.");
        ViewAbstract::ClearWidthOrHeight(frameNode, false);
        return;
    }
    ViewAbstractModelStatic::SetHeight(frameNode, *value);
}
void SetSizeImpl(Ark_NativePointer node,
                 const Opt_FormSize* value)
{
#ifdef FORM_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        LOGE("optValue value is null.");
        return;
    }
    auto width = Dimension(Converter::Convert<double>(optValue->width));
    auto height = Dimension(Converter::Convert<double>(optValue->height));
    SetWidthInternal(frameNode, width);
    SetHeightInternal(frameNode, height);
#endif // FORM_SUPPORTED
}
void SetModuleNameImpl(Ark_NativePointer node,
                       const Opt_String* value)
{
#ifdef FORM_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<std::string>(value).value_or(FormComponentModifier::DEFAULT_MODULE_NAME);
    FormModelStatic::SetModuleName(frameNode, convValue);
#endif // FORM_SUPPORTED
}
void SetDimensionImpl(Ark_NativePointer node,
                      const Opt_FormDimension* value)
{
#ifdef FORM_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<int32_t>(value).value_or(FormComponentModifier::DEFAULT_DIMENSION);
    FormModelStatic::SetDimension(frameNode, convValue);
#endif // FORM_SUPPORTED
}
void SetAllowUpdateImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
#ifdef FORM_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value).value_or(FormComponentModifier::DEFAULT_ALLOW_UPDATE);
    FormModelStatic::AllowUpdate(frameNode, convValue);
#endif // FORM_SUPPORTED
}
void SetVisibilityImpl(Ark_NativePointer node,
                       const Opt_Visibility* value)
{
#ifdef FORM_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto opt = Converter::OptConvertPtr<VisibleType>(value);
    CHECK_NULL_VOID(opt);
    FormModelStatic::SetVisibility(frameNode, *opt);
#endif // FORM_SUPPORTED
}
void SetOnAcquiredImpl(Ark_NativePointer node,
                       const Opt_Callback_FormCallbackInfo_Void* value)
{
#ifdef FORM_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    auto arkCallback = optValue ? CallbackHelper(*optValue) : CallbackHelper<Callback_FormCallbackInfo_Void>();
    auto onAcquired = [arkCallback](const std::string& param) {
        int64_t id = FORM_ON_ACQUIRED_ID_INVALID;
        std::string idString = FORM_ON_ACQUIRED_ID_STRING_INVALID;
        bool isLocked = false;
        auto sourceJson = JsonUtil::ParseJsonString(param);
        if (sourceJson && !sourceJson->IsNull()) {
            char* endptr = nullptr;
            auto jsonId = sourceJson->GetString(FORM_COMPONENT_ID_KEY, FORM_ON_ACQUIRED_ID_STRING_INVALID);
            idString = sourceJson->GetString(FORM_COMPONENT_ID_STRING_KEY, FORM_ON_ACQUIRED_ID_STRING_INVALID);
            isLocked = sourceJson->GetBool(FORM_COMPONENT_IS_LOCKED_KEY, false);
            int64_t result = std::strtoll(jsonId.c_str(), &endptr, 10);
            if (endptr && *endptr == '\0') {
                id = result;
            }
        }
        Ark_FormCallbackInfo parameter = {
            .id = Converter::ArkValue<Ark_Int64>(id),
            .idString = Converter::ArkValue<Ark_String>(idString),
            .isLocked = Converter::ArkValue<Ark_Boolean>(isLocked)
        };
        arkCallback.InvokeSync(parameter);
    };
    FormModelStatic::SetOnAcquired(frameNode, onAcquired);
#endif // FORM_SUPPORTED
}
void SetOnErrorImpl(Ark_NativePointer node,
                    const Opt_Callback_ErrorInformation_Void* value)
{
#ifdef FORM_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    auto arkCallback = optValue ? CallbackHelper(*optValue) : CallbackHelper<Callback_ErrorInformation_Void>();
    auto onError = [arkCallback](const std::string& param) {
        int32_t code = FORM_ON_ERROR_CODE_INVALID;
        std::string msg = FORM_EMPTY_STRING;
        auto sourceJson = JsonUtil::ParseJsonString(param);
        if (sourceJson && !sourceJson->IsNull()) {
            char* endptr = nullptr;
            auto jsonCode = sourceJson->GetString(FORM_ON_ERROR_CODE_KEY, FORM_EMPTY_STRING);
            msg = sourceJson->GetString(FORM_ON_ERROR_MSG_KEY, FORM_EMPTY_STRING);
            int32_t result = std::strtol(jsonCode.c_str(), &endptr, 10);
            if (endptr && *endptr == '\0' && result >= MIN_SIGNED_NUMBER_OF_ARK
                && result <= MAX_SIGNED_NUMBER_OF_ARK) {
                code = result;
            }
        }
        Ark_ErrorInformation parameter = { .errcode = Converter::ArkValue<Ark_Int32>(code),
            .msg = Converter::ArkValue<Ark_String>(msg) };
        arkCallback.InvokeSync(parameter);
    };
    FormModelStatic::SetOnError(frameNode, onError);
#endif // FORM_SUPPORTED
}
void SetOnRouterImpl(Ark_NativePointer node,
                     const Opt_Callback_RouterCallbackInfo_Void* value)
{
#ifdef FORM_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    auto arkCallback = optValue ? CallbackHelper(*optValue) : CallbackHelper<Callback_RouterCallbackInfo_Void>();
    auto onRouter = [arkCallback](const std::string& param) {
        std::string action = FORM_EMPTY_STRING;
        std::string bundleName = FORM_EMPTY_STRING;
        std::string moduleName = FORM_EMPTY_STRING;
        std::string abilityName = FORM_EMPTY_STRING;
        std::string params = FORM_EMPTY_STRING;
        auto sourceJson = JsonUtil::ParseJsonString(param);
        do {
            if (!sourceJson || sourceJson->IsNull()) {
                break;
            }
            auto actionInfo = sourceJson->GetValue(ROUTER_CODE_ACTION_KEY);
            if (!actionInfo || actionInfo->IsNull()) {
                break;
            }
            action = actionInfo->GetString(ROUTER_CODE_ACTION_KEY, FORM_EMPTY_STRING);
            bundleName = actionInfo->GetString(ROUTER_CODE_BUNDLE_NAME_KEY, FORM_EMPTY_STRING);
            moduleName = actionInfo->GetString(ROUTER_CODE_MODULE_NAME_KEY, FORM_EMPTY_STRING);
            abilityName = actionInfo->GetString(ROUTER_CODE_ABILITY_NAME_KEY, FORM_EMPTY_STRING);
            auto paramsValue = actionInfo->GetValue(ROUTER_CODE_PARAMS_KEY);
            if (!paramsValue || paramsValue->IsNull()) {
                break;
            }
            params = paramsValue->ToString();
        } while (false);
        Ark_RouterCallbackInfo parameter = {
            .action = Converter::ArkValue<Ark_String>(action),
            .bundleName = Converter::ArkValue<Ark_String>(bundleName),
            .moduleName = Converter::ArkValue<Ark_String>(moduleName),
            .abilityName = Converter::ArkValue<Ark_String>(abilityName),
            .params = Converter::ArkValue<Ark_String>(params)
        };
        arkCallback.InvokeSync(parameter);
    };
    FormModelStatic::SetOnRouter(frameNode, onRouter);
#endif // FORM_SUPPORTED
}
void SetOnUninstallImpl(Ark_NativePointer node,
                        const Opt_Callback_FormCallbackInfo_Void* value)
{
#ifdef FORM_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    auto arkCallback = optValue ? CallbackHelper(*optValue) : CallbackHelper<Callback_FormCallbackInfo_Void>();
    auto onUninstall = [arkCallback](const std::string& param) {
        int64_t id = FORM_ON_ACQUIRED_ID_INVALID;
        std::string idString = FORM_ON_ACQUIRED_ID_STRING_INVALID;
        bool isLocked = false;
        auto sourceJson = JsonUtil::ParseJsonString(param);
        if (sourceJson && !sourceJson->IsNull()) {
            char* endptr = nullptr;
            auto jsonId = sourceJson->GetString(FORM_COMPONENT_ID_KEY, FORM_ON_ACQUIRED_ID_STRING_INVALID);
            idString = sourceJson->GetString(FORM_COMPONENT_ID_STRING_KEY, FORM_ON_ACQUIRED_ID_STRING_INVALID);
            isLocked = sourceJson->GetBool(FORM_COMPONENT_IS_LOCKED_KEY, false);
            int64_t result = std::strtoll(jsonId.c_str(), &endptr, 10);
            if (endptr && *endptr == '\0') {
                id = result;
            }
        }
        Ark_FormCallbackInfo parameter = {
            .id = Converter::ArkValue<Ark_Int64>(id),
            .idString = Converter::ArkValue<Ark_String>(idString),
            .isLocked = Converter::ArkValue<Ark_Boolean>(isLocked)
        };
        arkCallback.InvokeSync(parameter);
    };
    FormModelStatic::SetOnUninstall(frameNode, onUninstall);
#endif // FORM_SUPPORTED
}
void SetOnLoadImpl(Ark_NativePointer node,
                   const Opt_VoidCallback* value)
{
#ifdef FORM_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    auto arkCallback = optValue ? CallbackHelper(*optValue) : CallbackHelper<VoidCallback>();
    auto onLoad = [arkCallback](const std::string& param) {
        arkCallback.Invoke();
    };
    FormModelStatic::SetOnLoad(frameNode, std::move(onLoad));
#endif // FORM_SUPPORTED
}
void SetOnUpdateImpl(Ark_NativePointer node,
                     const Opt_Callback_FormCallbackInfo_Void* value)
{
#ifdef FORM_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    auto arkCallback = optValue ? CallbackHelper(*optValue) : CallbackHelper<Callback_FormCallbackInfo_Void>();
    auto onUpdate = [arkCallback](const std::string& param) {
        int64_t id = FORM_ON_ACQUIRED_ID_INVALID;
        std::string idString = FORM_ON_ACQUIRED_ID_STRING_INVALID;
        auto sourceJson = JsonUtil::ParseJsonString(param);
        if (sourceJson && !sourceJson->IsNull()) {
            char* endptr = nullptr;
            auto jsonId = sourceJson->GetString(FORM_COMPONENT_ID_KEY, FORM_ON_ACQUIRED_ID_STRING_INVALID);
            idString = sourceJson->GetString(FORM_COMPONENT_ID_STRING_KEY, FORM_ON_ACQUIRED_ID_STRING_INVALID);
            int64_t result = std::strtoll(jsonId.c_str(), &endptr, 10);
            if (endptr && *endptr == '\0') {
                id = result;
            }
        }
        Ark_FormCallbackInfo parameter = { .id = Converter::ArkValue<Ark_Int64>(id),
            .idString = Converter::ArkValue<Ark_String>(idString) };
        arkCallback.InvokeSync(parameter);
    };
    FormModelStatic::SetOnUpdate(frameNode, onUpdate);
#endif // FORM_SUPPORTED
}
} // FormComponentAttributeModifier
const GENERATED_ArkUIFormComponentModifier* GetFormComponentModifier()
{
    static const GENERATED_ArkUIFormComponentModifier ArkUIFormComponentModifierImpl {
        FormComponentModifier::ConstructImpl,
        FormComponentInterfaceModifier::SetFormComponentOptionsImpl,
        FormComponentAttributeModifier::SetSizeImpl,
        FormComponentAttributeModifier::SetModuleNameImpl,
        FormComponentAttributeModifier::SetDimensionImpl,
        FormComponentAttributeModifier::SetAllowUpdateImpl,
        FormComponentAttributeModifier::SetVisibilityImpl,
        FormComponentAttributeModifier::SetOnAcquiredImpl,
        FormComponentAttributeModifier::SetOnErrorImpl,
        FormComponentAttributeModifier::SetOnRouterImpl,
        FormComponentAttributeModifier::SetOnUninstallImpl,
        FormComponentAttributeModifier::SetOnLoadImpl,
        FormComponentAttributeModifier::SetOnUpdateImpl,
    };
    return &ArkUIFormComponentModifierImpl;
}

}
