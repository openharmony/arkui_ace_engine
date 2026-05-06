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

#include <ani.h>
#include <array>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "base/log/log_wrapper.h"
#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/common/event_manager.h"
#include "core/components_ng/manager/smart_gesture/smart_gesture_manager.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/base/error/error_code.h"
#include "frameworks/core/interfaces/native/ani/frame_node_peer_impl.h"

namespace OHOS::Ace::Ani {
using OHOS::Ace::FrameNodePeer;
using OHOS::Ace::NG::SmartGestureManager;
using OHOS::Ace::NG::SmartGestureProposal;

namespace {
constexpr char SMART_GESTURE_NAMESPACE[] = "@ohos.arkui.smartGestureController.smartGestureController";
constexpr char RAW_PROPOSAL_INNER_CLASS[] =
    "@ohos.arkui.smartGestureController.smartGestureController.SmartGestureProposalRawInner";
constexpr char SMART_GESTURE_ACTION_ENUM[] = "arkui.component.enums.SmartGestureAction";
constexpr char OPERATE_INTENTION_ENUM[] = "arkui.component.enums.OperateIntention";
constexpr char STS_INT_CLASS[] = "std.core.Int";
constexpr char STS_LONG_CLASS[] = "std.core.Long";
constexpr char STS_DOUBLE_CLASS[] = "std.core.Double";

constexpr char ACTION_KEY[] = "action";
constexpr char OPERATE_INTENTION_KEY[] = "operateIntention";
constexpr char NODE_PTR_KEY[] = "nodePtr";
constexpr char PAGE_COUNT_KEY[] = "pageCount";
constexpr char DISTANCE_KEY[] = "distance";
constexpr char IS_CONSUMED_KEY[] = "isConsumed";
constexpr char SELECTED_PROPOSAL_KEY[] = "selectedProposal";

constexpr char UI_CONTEXT_NOT_FOUND_MESSAGE[] = "UI execution context not found";
constexpr char MONITOR_STATE_CREATE_FAILED_MESSAGE[] = "Failed to create smart gesture monitor state.";
constexpr char MONITOR_CALLBACK_EXCEPTION_MESSAGE[] = "Smart gesture monitor callback threw an exception.";
constexpr char INVALID_MONITOR_RESULT_MESSAGE[] =
    "Smart gesture monitor must return a valid GestureHandlingResolution.";
constexpr char INVALID_SELECTED_PROPOSAL_MESSAGE[] = "Smart gesture monitor returned an invalid selectedProposal.";

enum class JsSmartGestureAction : int32_t {
    NONE = 0,
    PAGE_FORWARD = 1,
    SCROLL_FORWARD = 2,
    SELECT = 3,
    CLICK = 4,
    BACK_PRESS = 5,
};

enum class JsOperateIntention : int32_t {
    TAP = 0,
    SLIDE_FORWARD = 1,
    BACK_PRESS = 2,
};

enum class MonitorResolutionParseResult : uint32_t {
    SUCCESS = 0,
    INVALID_RESOLUTION,
    INVALID_SELECTED_PROPOSAL,
};

OHOS::Ace::NG::SmartGestureHandlingResolution CreateRejectedResolution()
{
    OHOS::Ace::NG::SmartGestureHandlingResolution resolution;
    resolution.isConsumed = false;
    return resolution;
}

OHOS::Ace::NG::SmartGestureHandlingResolution CreateAcceptedResolution()
{
    OHOS::Ace::NG::SmartGestureHandlingResolution resolution;
    resolution.isConsumed = true;
    return resolution;
}

std::string AniStringToStdString(ani_env* env, ani_string aniStr)
{
    CHECK_NULL_RETURN(env && aniStr, "");
    ani_size strSize = 0;
    if (ANI_OK != env->String_GetUTF8Size(aniStr, &strSize)) {
        return "";
    }
    std::vector<char> buffer(strSize + 1);
    ani_size written = 0;
    if (ANI_OK != env->String_GetUTF8(aniStr, buffer.data(), strSize + 1, &written)) {
        return "";
    }
    buffer[written] = '\0';
    return std::string(buffer.data());
}

ani_object WrapStsError(ani_env* env, const std::string& msg)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_class cls;
    ani_method ctor;
    ani_status status = ANI_OK;
    if ((status = env->FindClass("std.core.Error", &cls)) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_GESTURE, "FindClass std.core.Error failed, status=%{public}d", status);
        return nullptr;
    }
    if ((status = env->Class_FindMethod(cls, "<ctor>", "C{std.core.String}C{std.core.ErrorOptions}:", &ctor)) !=
        ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_GESTURE, "FindMethod Error ctor failed, status=%{public}d", status);
        return nullptr;
    }
    ani_string aniMsg = nullptr;
    if ((status = env->String_NewUTF8(msg.c_str(), msg.size(), &aniMsg)) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_GESTURE, "String_NewUTF8 failed, status=%{public}d", status);
        return nullptr;
    }
    ani_ref undefRef = nullptr;
    if ((status = env->GetUndefined(&undefRef)) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_GESTURE, "GetUndefined failed, status=%{public}d", status);
        return nullptr;
    }
    ani_object errObj = nullptr;
    if ((status = env->Object_New(cls, ctor, &errObj, aniMsg, undefRef)) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_GESTURE, "Object_New Error failed, status=%{public}d", status);
        return nullptr;
    }
    return errObj;
}

ani_ref CreateStsError(ani_env* env, ani_int code, const std::string& msg)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_class cls;
    ani_method ctor;
    ani_status status = ANI_OK;
    if ((status = env->FindClass("@ohos.base.BusinessError", &cls)) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_GESTURE, "FindClass BusinessError failed, status=%{public}d", status);
        return nullptr;
    }
    if ((status = env->Class_FindMethod(cls, "<ctor>", "iC{std.core.Error}:", &ctor)) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_GESTURE, "FindMethod BusinessError ctor failed, status=%{public}d", status);
        return nullptr;
    }
    ani_object error = WrapStsError(env, msg);
    CHECK_NULL_RETURN(error, nullptr);
    ani_object businessError = nullptr;
    if ((status = env->Object_New(cls, ctor, &businessError, code, error)) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_GESTURE, "Object_New BusinessError failed, status=%{public}d", status);
        return nullptr;
    }
    return reinterpret_cast<ani_ref>(businessError);
}

void AniThrow(ani_env* env, const std::string& msg, int32_t code)
{
    CHECK_NULL_VOID(env);
    auto errObj = CreateStsError(env, static_cast<ani_int>(code), msg);
    CHECK_NULL_VOID(errObj);
    if (ANI_OK != env->ThrowError(static_cast<ani_error>(errObj))) {
        TAG_LOGE(AceLogTag::ACE_GESTURE, "ThrowError failed");
    }
}

bool IsUndefinedOrNull(ani_env* env, ani_ref value)
{
    CHECK_NULL_RETURN(env, true);
    CHECK_NULL_RETURN(value, true);
    ani_boolean isUndefined = ANI_FALSE;
    if (ANI_OK == env->Reference_IsUndefined(value, &isUndefined) && isUndefined == ANI_TRUE) {
        return true;
    }
    ani_boolean isNull = ANI_FALSE;
    if (ANI_OK == env->Reference_IsNull(value, &isNull) && isNull == ANI_TRUE) {
        return true;
    }
    return false;
}

bool IsStrictlyEqual(ani_env* env, ani_ref left, ani_ref right)
{
    CHECK_NULL_RETURN(env && left && right, false);
    ani_boolean isEquals = ANI_FALSE;
    if (ANI_OK != env->Reference_StrictEquals(left, right, &isEquals)) {
        return false;
    }
    return isEquals == ANI_TRUE;
}

void ResetUnhandledErrorIfNeeded(ani_env* env)
{
    CHECK_NULL_VOID(env);
    ani_boolean hasUnhandledError = ANI_FALSE;
    if (ANI_OK != env->ExistUnhandledError(&hasUnhandledError) || hasUnhandledError != ANI_TRUE) {
        return;
    }
    env->ResetError();
}

void DescribeUnhandledErrorIfNeeded(ani_env* env)
{
    CHECK_NULL_VOID(env);
    ani_boolean hasUnhandledError = ANI_FALSE;
    if (ANI_OK != env->ExistUnhandledError(&hasUnhandledError) || hasUnhandledError != ANI_TRUE) {
        return;
    }
    env->DescribeError();
}

bool GetPropertyRef(ani_env* env, ani_object object, const char* key, ani_ref& outRef)
{
    CHECK_NULL_RETURN(env && object && key, false);
    return env->Object_GetPropertyByName_Ref(object, key, &outRef) == ANI_OK;
}

ani_object CreateIntObject(ani_env* env, int32_t value)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_class cls = nullptr;
    ani_method ctor = nullptr;
    ani_object result = nullptr;
    if (ANI_OK != env->FindClass(STS_INT_CLASS, &cls)) {
        return nullptr;
    }
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", "i:", &ctor)) {
        return nullptr;
    }
    if (ANI_OK != env->Object_New(cls, ctor, &result, static_cast<ani_int>(value))) {
        return nullptr;
    }
    return result;
}

ani_object CreateLongObject(ani_env* env, int64_t value)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_class cls = nullptr;
    ani_method ctor = nullptr;
    ani_object result = nullptr;
    if (ANI_OK != env->FindClass(STS_LONG_CLASS, &cls)) {
        return nullptr;
    }
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", "l:", &ctor)) {
        return nullptr;
    }
    if (ANI_OK != env->Object_New(cls, ctor, &result, static_cast<ani_long>(value))) {
        return nullptr;
    }
    return result;
}

ani_object CreateDoubleObject(ani_env* env, double value)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_class cls = nullptr;
    ani_method ctor = nullptr;
    ani_object result = nullptr;
    if (ANI_OK != env->FindClass(STS_DOUBLE_CLASS, &cls)) {
        return nullptr;
    }
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", "d:", &ctor)) {
        return nullptr;
    }
    if (ANI_OK != env->Object_New(cls, ctor, &result, static_cast<ani_double>(value))) {
        return nullptr;
    }
    return result;
}

bool SetIntPropertyByRef(ani_env* env, ani_object object, const char* key, int32_t value)
{
    CHECK_NULL_RETURN(env && object && key, false);
    auto boxedValue = CreateIntObject(env, value);
    CHECK_NULL_RETURN(boxedValue, false);
    return env->Object_SetPropertyByName_Ref(object, key, static_cast<ani_ref>(boxedValue)) == ANI_OK;
}

bool SetLongPropertyByRef(ani_env* env, ani_object object, const char* key, int64_t value)
{
    CHECK_NULL_RETURN(env && object && key, false);
    auto boxedValue = CreateLongObject(env, value);
    CHECK_NULL_RETURN(boxedValue, false);
    return env->Object_SetPropertyByName_Ref(object, key, static_cast<ani_ref>(boxedValue)) == ANI_OK;
}

bool SetDoublePropertyByRef(ani_env* env, ani_object object, const char* key, double value)
{
    CHECK_NULL_RETURN(env && object && key, false);
    auto boxedValue = CreateDoubleObject(env, value);
    CHECK_NULL_RETURN(boxedValue, false);
    return env->Object_SetPropertyByName_Ref(object, key, static_cast<ani_ref>(boxedValue)) == ANI_OK;
}

bool IsClassObject(ani_env* env, ani_object object, const char* classDescriptor)
{
    CHECK_NULL_RETURN(env && object && classDescriptor, false);
    ani_class objectClass = nullptr;
    if (ANI_OK != env->FindClass(classDescriptor, &objectClass)) {
        return false;
    }

    ani_boolean isInstance = ANI_FALSE;
    if (ANI_OK != env->Object_InstanceOf(object, objectClass, &isInstance)) {
        return false;
    }
    return isInstance == ANI_TRUE;
}

bool SetEnumPropertyByIndex(ani_env* env, ani_object object, const char* key, const char* enumName, ani_size index)
{
    CHECK_NULL_RETURN(env && object && key && enumName, false);
    ani_enum enumType = nullptr;
    if (ANI_OK != env->FindEnum(enumName, &enumType)) {
        return false;
    }
    ani_enum_item enumItem = nullptr;
    if (ANI_OK != env->Enum_GetEnumItemByIndex(enumType, index, &enumItem)) {
        return false;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Ref(object, key, enumItem)) {
        return false;
    }
    return true;
}

std::optional<int32_t> GetInt32FromRef(ani_env* env, ani_ref ref)
{
    CHECK_NULL_RETURN(env && ref, std::nullopt);
    if (IsUndefinedOrNull(env, ref)) {
        return std::nullopt;
    }

    auto object = static_cast<ani_object>(ref);
    if (IsClassObject(env, object, STS_INT_CLASS)) {
        ani_int value = 0;
        if (ANI_OK != env->Object_CallMethodByName_Int(object, "toInt", ":i", &value)) {
            return std::nullopt;
        }
        return static_cast<int32_t>(value);
    }

    ani_int value = 0;
    if (ANI_OK == env->EnumItem_GetValue_Int(static_cast<ani_enum_item>(ref), &value)) {
        return static_cast<int32_t>(value);
    }
    return std::nullopt;
}

std::optional<int64_t> GetInt64FromRef(ani_env* env, ani_ref ref)
{
    CHECK_NULL_RETURN(env && ref, std::nullopt);
    if (IsUndefinedOrNull(env, ref)) {
        return std::nullopt;
    }

    auto object = static_cast<ani_object>(ref);
    if (!IsClassObject(env, object, STS_LONG_CLASS)) {
        return std::nullopt;
    }

    ani_long value = 0;
    if (ANI_OK != env->Object_CallMethodByName_Long(object, "toLong", ":l", &value)) {
        return std::nullopt;
    }
    return static_cast<int64_t>(value);
}

std::optional<double> GetDoubleFromRef(ani_env* env, ani_ref ref)
{
    CHECK_NULL_RETURN(env && ref, std::nullopt);
    if (IsUndefinedOrNull(env, ref)) {
        return std::nullopt;
    }

    auto object = static_cast<ani_object>(ref);
    if (!IsClassObject(env, object, STS_DOUBLE_CLASS)) {
        return std::nullopt;
    }

    ani_double value = 0.0;
    if (ANI_OK != env->Object_CallMethodByName_Double(object, "toDouble", ":d", &value)) {
        return std::nullopt;
    }
    return static_cast<double>(value);
}

std::optional<int32_t> GetOptionalInt32PropertyByName(ani_env* env, ani_object object, const char* key)
{
    CHECK_NULL_RETURN(env && object && key, std::nullopt);
    ani_int value = 0;
    if (ANI_OK == env->Object_GetPropertyByName_Int(object, key, &value)) {
        return static_cast<int32_t>(value);
    }

    ani_ref ref = nullptr;
    if (!GetPropertyRef(env, object, key, ref) || IsUndefinedOrNull(env, ref)) {
        return std::nullopt;
    }

    return GetInt32FromRef(env, ref);
}

std::optional<int64_t> GetOptionalInt64PropertyByName(ani_env* env, ani_object object, const char* key)
{
    CHECK_NULL_RETURN(env && object && key, std::nullopt);
    ani_long value = 0;
    if (ANI_OK == env->Object_GetPropertyByName_Long(object, key, &value)) {
        return static_cast<int64_t>(value);
    }

    ani_ref ref = nullptr;
    if (!GetPropertyRef(env, object, key, ref) || IsUndefinedOrNull(env, ref)) {
        return std::nullopt;
    }

    return GetInt64FromRef(env, ref);
}

std::optional<double> GetOptionalDoublePropertyByName(ani_env* env, ani_object object, const char* key)
{
    CHECK_NULL_RETURN(env && object && key, std::nullopt);
    ani_double value = 0.0;
    if (ANI_OK == env->Object_GetPropertyByName_Double(object, key, &value)) {
        return static_cast<double>(value);
    }

    ani_ref ref = nullptr;
    if (!GetPropertyRef(env, object, key, ref) || IsUndefinedOrNull(env, ref)) {
        return std::nullopt;
    }

    return GetDoubleFromRef(env, ref);
}

std::optional<bool> GetOptionalBoolPropertyByName(ani_env* env, ani_object object, const char* key)
{
    CHECK_NULL_RETURN(env && object && key, std::nullopt);
    ani_boolean value = ANI_FALSE;
    if (ANI_OK != env->Object_GetPropertyByName_Boolean(object, key, &value)) {
        return std::nullopt;
    }
    return value == ANI_TRUE;
}

std::optional<bool> HasOwnProperty(ani_env* env, ani_object object, const char* key)
{
    CHECK_NULL_RETURN(env && object && key, std::nullopt);
    ani_string aniKey = nullptr;
    if (ANI_OK != env->String_NewUTF8(key, std::strlen(key), &aniKey)) {
        return std::nullopt;
    }

    ani_boolean hasOwn = ANI_FALSE;
    if (ANI_OK !=
        env->Object_CallMethodByName_Boolean(object, "hasOwnProperty", "C{std.core.String}:z", &hasOwn, aniKey)) {
        return std::nullopt;
    }
    return hasOwn == ANI_TRUE;
}

RefPtr<SmartGestureManager> GetManagerByInstanceId(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN(container, nullptr);
    auto pipeline = AceType::DynamicCast<OHOS::Ace::NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto eventManager = pipeline->GetEventManager();
    CHECK_NULL_RETURN(eventManager, nullptr);
    return eventManager->GetOrCreateSmartGestureManager();
}

bool TryGetCurrentInstanceId(int32_t& instanceId)
{
    instanceId = Container::CurrentIdSafely();
    return instanceId >= 0;
}

RefPtr<SmartGestureManager> GetRequiredManager(ani_env* env, int32_t instanceId)
{
    auto manager = GetManagerByInstanceId(instanceId);
    if (!manager) {
        AniThrow(env, UI_CONTEXT_NOT_FOUND_MESSAGE, OHOS::Ace::ERROR_CODE_INTERNAL_ERROR);
    }
    return manager;
}

class SmartGestureCodec final {
public:
    static ani_object EncodeRawProposal(ani_env* env, int32_t instanceId, const SmartGestureProposal& proposal)
    {
        CHECK_NULL_RETURN(env, nullptr);
        auto object = CreateRawProposalObject(env);
        CHECK_NULL_RETURN(object, nullptr);

        CHECK_NULL_RETURN(SetEnumPropertyByIndex(env, object, ACTION_KEY, SMART_GESTURE_ACTION_ENUM,
            static_cast<ani_size>(ToJsAction(proposal))), nullptr);
        CHECK_NULL_RETURN(SetEnumPropertyByIndex(env, object, OPERATE_INTENTION_KEY, OPERATE_INTENTION_ENUM,
            static_cast<ani_size>(ToJsOperateIntention(proposal.operateIntention))), nullptr);

        auto targetNode = proposal.GetTargetNode();
        if (targetNode) {
            ContainerScope scope(instanceId);
            auto peer = FrameNodePeer::Create(targetNode);
            if (peer) {
                auto nodePtr = static_cast<int64_t>(reinterpret_cast<intptr_t>(peer));
                SetLongPropertyByRef(env, object, NODE_PTR_KEY, nodePtr);
            }
        }

        if (proposal.scrollingConfig.has_value()) {
            if (proposal.scrollingConfig->count.has_value()) {
                SetIntPropertyByRef(env, object, PAGE_COUNT_KEY, proposal.scrollingConfig->count.value());
            }
            if (proposal.scrollingConfig->distance.has_value()) {
                SetDoublePropertyByRef(env, object, DISTANCE_KEY, proposal.scrollingConfig->distance.value());
            }
        }

        return object;
    }

    static bool DecodeRawProposal(ani_env* env, ani_object value, std::optional<SmartGestureProposal>& outProposal)
    {
        CHECK_NULL_RETURN(env && value, false);

        auto action = ParseJsAction(env, value);
        CHECK_NULL_RETURN(action.has_value(), false);

        auto rawIntention = GetOptionalInt32PropertyByName(env, value, OPERATE_INTENTION_KEY);
        auto intention = ToNativeOperateIntention(rawIntention, *action);
        switch (*action) {
            case JsSmartGestureAction::NONE:
                outProposal = SmartGestureProposal(OHOS::Ace::NG::SmartGestureProposalType::NONE_ACTION, intention);
                return true;
            case JsSmartGestureAction::BACK_PRESS:
                outProposal = SmartGestureProposal(OHOS::Ace::NG::SmartGestureProposalType::BACK_PRESS, intention);
                return true;
            case JsSmartGestureAction::CLICK:
            case JsSmartGestureAction::SELECT:
            case JsSmartGestureAction::PAGE_FORWARD:
            case JsSmartGestureAction::SCROLL_FORWARD:
                break;
        }

        auto frameNode = ParseFrameNode(env, value);
        CHECK_NULL_RETURN(frameNode, false);

        if (*action == JsSmartGestureAction::CLICK) {
            outProposal = SmartGestureProposal(OHOS::Ace::NG::SmartGestureProposalType::CLICK, intention, frameNode);
            return true;
        }
        if (*action == JsSmartGestureAction::SELECT) {
            outProposal = SmartGestureProposal(OHOS::Ace::NG::SmartGestureProposalType::SELECT, intention, frameNode);
            return true;
        }

        OHOS::Ace::NG::ScrollingConfig config;
        config.count = GetOptionalInt32PropertyByName(env, value, PAGE_COUNT_KEY);
        config.distance = GetOptionalDoublePropertyByName(env, value, DISTANCE_KEY);
        CHECK_NULL_RETURN(config.HasValue(), false);
        outProposal =
            SmartGestureProposal(OHOS::Ace::NG::SmartGestureProposalType::SCROLL, intention, frameNode, config);
        return true;
    }

    static MonitorResolutionParseResult DecodeRawResolution(
        ani_env* env, ani_object value, OHOS::Ace::NG::SmartGestureHandlingResolution& resolution)
    {
        if (!env || !value) {
            return MonitorResolutionParseResult::INVALID_RESOLUTION;
        }

        auto consumed = GetOptionalBoolPropertyByName(env, value, IS_CONSUMED_KEY);
        if (!consumed.has_value()) {
            return MonitorResolutionParseResult::INVALID_RESOLUTION;
        }
        resolution.isConsumed = consumed.value();

        ani_ref selectedProposalRef = nullptr;
        if (!GetPropertyRef(env, value, SELECTED_PROPOSAL_KEY, selectedProposalRef)) {
            return MonitorResolutionParseResult::SUCCESS;
        }
        if (IsUndefinedOrNull(env, selectedProposalRef)) {
            auto hasOwnSelectedProposal = HasOwnProperty(env, value, SELECTED_PROPOSAL_KEY);
            if (hasOwnSelectedProposal.has_value() && hasOwnSelectedProposal.value()) {
                return MonitorResolutionParseResult::INVALID_SELECTED_PROPOSAL;
            }
            return MonitorResolutionParseResult::SUCCESS;
        }

        std::optional<SmartGestureProposal> parsedProposal;
        if (!DecodeRawProposal(env, static_cast<ani_object>(selectedProposalRef), parsedProposal)) {
            return MonitorResolutionParseResult::INVALID_SELECTED_PROPOSAL;
        }
        resolution.hasSelectedProposal = true;
        resolution.selectedProposal = parsedProposal;
        return MonitorResolutionParseResult::SUCCESS;
    }

private:
    static ani_object CreateRawProposalObject(ani_env* env)
    {
        CHECK_NULL_RETURN(env, nullptr);
        ani_class cls;
        ani_method ctor;
        ani_object object = nullptr;
        if (ANI_OK != env->FindClass(RAW_PROPOSAL_INNER_CLASS, &cls)) {
            return nullptr;
        }
        if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", ":", &ctor)) {
            return nullptr;
        }
        if (ANI_OK != env->Object_New(cls, ctor, &object)) {
            return nullptr;
        }
        return object;
    }

    static std::optional<JsSmartGestureAction> ParseJsAction(ani_env* env, ani_object object)
    {
        auto actionValue = GetOptionalInt32PropertyByName(env, object, ACTION_KEY);
        CHECK_NULL_RETURN(actionValue.has_value(), std::nullopt);

        switch (static_cast<JsSmartGestureAction>(actionValue.value())) {
            case JsSmartGestureAction::NONE:
            case JsSmartGestureAction::PAGE_FORWARD:
            case JsSmartGestureAction::SCROLL_FORWARD:
            case JsSmartGestureAction::SELECT:
            case JsSmartGestureAction::CLICK:
            case JsSmartGestureAction::BACK_PRESS:
                return static_cast<JsSmartGestureAction>(actionValue.value());
            default:
                return std::nullopt;
        }
    }

    static OHOS::Ace::RefPtr<OHOS::Ace::NG::FrameNode> ParseFrameNode(ani_env* env, ani_object object)
    {
        auto nodePtr = GetOptionalInt64PropertyByName(env, object, NODE_PTR_KEY);
        CHECK_NULL_RETURN(nodePtr.has_value(), nullptr);
        auto peer = reinterpret_cast<FrameNodePeer*>(static_cast<intptr_t>(nodePtr.value()));
        return FrameNodePeer::GetFrameNodeByPeer(peer);
    }

    static JsSmartGestureAction ToJsAction(const SmartGestureProposal& proposal)
    {
        switch (proposal.type) {
            case OHOS::Ace::NG::SmartGestureProposalType::NONE_ACTION:
                return JsSmartGestureAction::NONE;
            case OHOS::Ace::NG::SmartGestureProposalType::CLICK:
                return JsSmartGestureAction::CLICK;
            case OHOS::Ace::NG::SmartGestureProposalType::SELECT:
                return JsSmartGestureAction::SELECT;
            case OHOS::Ace::NG::SmartGestureProposalType::BACK_PRESS:
                return JsSmartGestureAction::BACK_PRESS;
            case OHOS::Ace::NG::SmartGestureProposalType::SCROLL:
                if (proposal.scrollingConfig.has_value() && proposal.scrollingConfig->count.has_value() &&
                    !proposal.scrollingConfig->distance.has_value()) {
                    return JsSmartGestureAction::PAGE_FORWARD;
                }
                return JsSmartGestureAction::SCROLL_FORWARD;
        }
        return JsSmartGestureAction::NONE;
    }

    static JsOperateIntention ToJsOperateIntention(OHOS::Ace::NG::SmartGestureOperateIntention intention)
    {
        switch (intention) {
            case OHOS::Ace::NG::SmartGestureOperateIntention::TAP:
                return JsOperateIntention::TAP;
            case OHOS::Ace::NG::SmartGestureOperateIntention::SLIDE_FORWARD:
                return JsOperateIntention::SLIDE_FORWARD;
            case OHOS::Ace::NG::SmartGestureOperateIntention::BACK_PRESS:
                return JsOperateIntention::BACK_PRESS;
        }
        return JsOperateIntention::TAP;
    }

    static OHOS::Ace::NG::SmartGestureOperateIntention ToNativeOperateIntention(
        std::optional<int32_t> intention, JsSmartGestureAction action)
    {
        if (intention.has_value()) {
            switch (static_cast<JsOperateIntention>(intention.value())) {
                case JsOperateIntention::TAP:
                    return OHOS::Ace::NG::SmartGestureOperateIntention::TAP;
                case JsOperateIntention::SLIDE_FORWARD:
                    return OHOS::Ace::NG::SmartGestureOperateIntention::SLIDE_FORWARD;
                case JsOperateIntention::BACK_PRESS:
                    return OHOS::Ace::NG::SmartGestureOperateIntention::BACK_PRESS;
            }
        }

        switch (action) {
            case JsSmartGestureAction::BACK_PRESS:
                return OHOS::Ace::NG::SmartGestureOperateIntention::BACK_PRESS;
            case JsSmartGestureAction::PAGE_FORWARD:
            case JsSmartGestureAction::SCROLL_FORWARD:
                return OHOS::Ace::NG::SmartGestureOperateIntention::SLIDE_FORWARD;
            case JsSmartGestureAction::NONE:
            case JsSmartGestureAction::SELECT:
            case JsSmartGestureAction::CLICK:
                return OHOS::Ace::NG::SmartGestureOperateIntention::TAP;
        }
        return OHOS::Ace::NG::SmartGestureOperateIntention::TAP;
    }
};

class SmartGestureMonitorState final {
public:
    SmartGestureMonitorState(ani_env* env, int32_t instanceId) : env_(env), instanceId_(instanceId) {}

    static std::shared_ptr<SmartGestureMonitorState> Create(ani_env* env, int32_t instanceId, ani_fn_object callback)
    {
        auto state = std::make_shared<SmartGestureMonitorState>(env, instanceId);
        CHECK_NULL_RETURN(state && state->SetMonitorRef(callback), nullptr);
        return state;
    }

    ~SmartGestureMonitorState()
    {
        ResetMonitorRef();
    }

    OHOS::Ace::NG::SmartGestureHandlingResolution Invoke(const SmartGestureProposal& defaultProposal) const
    {
        auto resolution = CreateRejectedResolution();
        CHECK_NULL_RETURN(env_, resolution);

        ContainerScope scope(instanceId_);
        ani_size nrRefs = 16;
        if (ANI_OK != env_->CreateLocalScope(nrRefs) || !nrRefs) {
            TAG_LOGW(AceLogTag::ACE_GESTURE, "CreateLocalScope failed when invoking smart gesture monitor");
            return resolution;
        }
        auto callback = GetCallback();
        if (!callback) {
            env_->DestroyLocalScope();
            return resolution;
        }

        ani_object proposalValue = SmartGestureCodec::EncodeRawProposal(env_, instanceId_, defaultProposal);
        if (!proposalValue) {
            env_->DestroyLocalScope();
            return resolution;
        }

        std::array<ani_ref, 1> args = { proposalValue };
        ani_ref fnReturnVal = nullptr;
        if (ANI_OK != env_->FunctionalObject_Call(callback, args.size(), args.data(), &fnReturnVal)) {
            DescribeUnhandledErrorIfNeeded(env_);
            ResetUnhandledErrorIfNeeded(env_);
            TAG_LOGW(AceLogTag::ACE_GESTURE, "%{public}s", MONITOR_CALLBACK_EXCEPTION_MESSAGE);
            env_->DestroyLocalScope();
            return resolution;
        }
        if (IsUndefinedOrNull(env_, fnReturnVal)) {
            TAG_LOGW(AceLogTag::ACE_GESTURE, "%{public}s", INVALID_MONITOR_RESULT_MESSAGE);
            env_->DestroyLocalScope();
            return resolution;
        }

        OHOS::Ace::NG::SmartGestureHandlingResolution decodedResolution;
        auto parseResult =
            SmartGestureCodec::DecodeRawResolution(env_, static_cast<ani_object>(fnReturnVal), decodedResolution);
        if (parseResult != MonitorResolutionParseResult::SUCCESS) {
            auto detail = parseResult == MonitorResolutionParseResult::INVALID_SELECTED_PROPOSAL
                              ? INVALID_SELECTED_PROPOSAL_MESSAGE
                              : INVALID_MONITOR_RESULT_MESSAGE;
            TAG_LOGW(AceLogTag::ACE_GESTURE, "%{public}s", detail);
            env_->DestroyLocalScope();
            return resolution;
        }
        env_->DestroyLocalScope();
        return decodedResolution;
    }

    bool MatchesCallback(ani_env* env, ani_fn_object callback) const
    {
        CHECK_NULL_RETURN(env_ != nullptr, false);
        CHECK_NULL_RETURN(env == env_, false);
        auto currentCallback = reinterpret_cast<ani_ref>(GetCallback());
        CHECK_NULL_RETURN(currentCallback != nullptr, false);
        return IsStrictlyEqual(env_, currentCallback, reinterpret_cast<ani_ref>(callback));
    }

    ani_env* GetEnv() const
    {
        return env_;
    }

    void Detach()
    {
        ResetMonitorRef();
        env_ = nullptr;
        instanceId_ = -1;
    }

private:
    bool SetMonitorRef(ani_fn_object callback)
    {
        CHECK_NULL_RETURN(env_ != nullptr && callback != nullptr, false);
        return env_->GlobalReference_Create(reinterpret_cast<ani_ref>(callback), &monitorRef_) == ANI_OK;
    }

    void ResetMonitorRef()
    {
        if (env_ != nullptr && monitorRef_ != nullptr) {
            env_->GlobalReference_Delete(monitorRef_);
        }
        monitorRef_ = nullptr;
    }

    ani_fn_object GetCallback() const
    {
        return reinterpret_cast<ani_fn_object>(monitorRef_);
    }

    ani_env* env_ = nullptr;
    int32_t instanceId_ = -1;
    ani_ref monitorRef_ = nullptr;
};

class SmartGestureMonitorRegistry final {
public:
    static bool Register(ani_env* env, int32_t instanceId, ani_fn_object callback)
    {
        auto state = SmartGestureMonitorState::Create(env, instanceId, callback);
        CHECK_NULL_RETURN(state, false);
        states_[instanceId].emplace_back(std::move(state));
        return true;
    }

    static bool Unregister(ani_env* env, int32_t instanceId, ani_fn_object callback)
    {
        std::vector<std::shared_ptr<SmartGestureMonitorState>> statesToDetach;
        auto iter = states_.find(instanceId);
        if (iter == states_.end() || iter->second.empty()) {
            return false;
        }
        auto& stateStack = iter->second;
        auto removeIter = std::remove_if(stateStack.begin(), stateStack.end(),
            [&statesToDetach, env, callback](const std::shared_ptr<SmartGestureMonitorState>& state) {
                if (!state || !state->MatchesCallback(env, callback)) {
                    return false;
                }
                statesToDetach.emplace_back(state);
                return true;
            });
        stateStack.erase(removeIter, stateStack.end());
        if (stateStack.empty()) {
            states_.erase(iter);
        }
        for (const auto& state : statesToDetach) {
            if (state) {
                state->Detach();
            }
        }
        return !statesToDetach.empty();
    }

    static bool Clear(int32_t instanceId)
    {
        std::vector<std::shared_ptr<SmartGestureMonitorState>> statesToDetach;
        auto iter = states_.find(instanceId);
        if (iter == states_.end() || iter->second.empty()) {
            return false;
        }
        statesToDetach = std::move(iter->second);
        states_.erase(iter);

        for (const auto& state : statesToDetach) {
            if (state) {
                state->Detach();
            }
        }
        return true;
    }

    static bool HasMonitor(int32_t instanceId)
    {
        auto iter = states_.find(instanceId);
        return iter != states_.end() && !iter->second.empty();
    }

    static OHOS::Ace::NG::SmartGestureHandlingResolution Invoke(
        int32_t instanceId, const SmartGestureProposal& defaultProposal)
    {
        auto iter = states_.find(instanceId);
        if (iter == states_.end() || iter->second.empty()) {
            return CreateAcceptedResolution();
        }
        auto states = iter->second;

        for (auto stateIter = states.rbegin(); stateIter != states.rend(); ++stateIter) {
            auto state = *stateIter;
            CHECK_NULL_CONTINUE(state);
            auto resolution = state->Invoke(defaultProposal);
            if (!resolution.isConsumed) {
                continue;
            }
            if (resolution.hasSelectedProposal) {
                return resolution;
            }
            return resolution;
        }
        return CreateRejectedResolution();
    }

private:
    static std::unordered_map<int32_t, std::vector<std::shared_ptr<SmartGestureMonitorState>>> states_;
};

std::unordered_map<int32_t, std::vector<std::shared_ptr<SmartGestureMonitorState>>>
    SmartGestureMonitorRegistry::states_;

void InstallRegistryBackedMonitor(const RefPtr<SmartGestureManager>& manager, int32_t instanceId)
{
    CHECK_NULL_VOID(manager);
    if (!SmartGestureMonitorRegistry::HasMonitor(instanceId)) {
        manager->SetMonitor(SmartGestureManager::SmartGestureMonitor());
        return;
    }
    manager->SetMonitor(
        [instanceId](const SmartGestureProposal& defaultProposal) -> OHOS::Ace::NG::SmartGestureHandlingResolution {
            return SmartGestureMonitorRegistry::Invoke(instanceId, defaultProposal);
        });
}

void EnableSmartTapAndSlideGestures(ani_env* env, ani_boolean enabled)
{
    int32_t instanceId = -1;
    if (!TryGetCurrentInstanceId(instanceId)) {
        return;
    }
    ContainerScope scope(instanceId);
    auto manager = GetRequiredManager(env, instanceId);
    CHECK_NULL_VOID(manager);
    manager->SetSmartTapAndSlideGesturesEnabled(enabled == ANI_TRUE);
}

void RegisterMonitor(ani_env* env, ani_fn_object callback)
{
    CHECK_NULL_VOID(env);
    if (callback == nullptr) {
        AniThrow(env, MONITOR_STATE_CREATE_FAILED_MESSAGE, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
        return;
    }
    int32_t instanceId = -1;
    if (!TryGetCurrentInstanceId(instanceId)) {
        return;
    }
    ContainerScope scope(instanceId);
    auto manager = GetRequiredManager(env, instanceId);
    CHECK_NULL_VOID(manager);

    if (!SmartGestureMonitorRegistry::Register(env, instanceId, callback)) {
        AniThrow(env, MONITOR_STATE_CREATE_FAILED_MESSAGE, OHOS::Ace::ERROR_CODE_INTERNAL_ERROR);
        return;
    }
    InstallRegistryBackedMonitor(manager, instanceId);
}

void UnregisterMonitor(ani_env* env, ani_fn_object callback)
{
    CHECK_NULL_VOID(env);
    if (callback == nullptr) {
        return;
    }
    int32_t instanceId = -1;
    if (!TryGetCurrentInstanceId(instanceId)) {
        return;
    }
    ContainerScope scope(instanceId);
    auto manager = GetRequiredManager(env, instanceId);
    CHECK_NULL_VOID(manager);

    SmartGestureMonitorRegistry::Unregister(env, instanceId, callback);
    InstallRegistryBackedMonitor(manager, instanceId);
}

void ClearMonitors(ani_env* env)
{
    CHECK_NULL_VOID(env);
    int32_t instanceId = -1;
    if (!TryGetCurrentInstanceId(instanceId)) {
        return;
    }
    ContainerScope scope(instanceId);
    auto manager = GetRequiredManager(env, instanceId);
    CHECK_NULL_VOID(manager);

    SmartGestureMonitorRegistry::Clear(instanceId);
    InstallRegistryBackedMonitor(manager, instanceId);
}

void RequestSelected(ani_env* env, ani_string id)
{
    CHECK_NULL_VOID(env);
    CHECK_NULL_VOID(id);
    auto inspectorId = AniStringToStdString(env, id);
    int32_t instanceId = -1;
    if (!TryGetCurrentInstanceId(instanceId)) {
        return;
    }
    ContainerScope scope(instanceId);
    auto manager = GetRequiredManager(env, instanceId);
    CHECK_NULL_VOID(manager);
    manager->RequestSelected(inspectorId);
}

void ClearSelected(ani_env* env)
{
    CHECK_NULL_VOID(env);
    int32_t instanceId = -1;
    if (!TryGetCurrentInstanceId(instanceId)) {
        return;
    }
    ContainerScope scope(instanceId);
    auto manager = GetRequiredManager(env, instanceId);
    CHECK_NULL_VOID(manager);
    manager->ClearSelected();
}
} // namespace

ani_status SmartGestureAniConstructor(ani_vm* vm, uint32_t* result)
{
    if (vm == nullptr || result == nullptr) {
        return ANI_ERROR;
    }
    ani_env* env = nullptr;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        return ANI_ERROR;
    }

    ani_namespace ns = nullptr;
    if (ANI_OK != env->FindNamespace(SMART_GESTURE_NAMESPACE, &ns)) {
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function {
            "enableSmartTapAndSlideGestures", nullptr, reinterpret_cast<void*>(EnableSmartTapAndSlideGestures) },
        ani_native_function { "registerMonitor", nullptr, reinterpret_cast<void*>(RegisterMonitor) },
        ani_native_function { "unregisterMonitor", nullptr, reinterpret_cast<void*>(UnregisterMonitor) },
        ani_native_function { "clearMonitors", nullptr, reinterpret_cast<void*>(ClearMonitors) },
        ani_native_function { "requestSelected", nullptr, reinterpret_cast<void*>(RequestSelected) },
        ani_native_function { "clearSelected", nullptr, reinterpret_cast<void*>(ClearSelected) },
    };
    if (ANI_OK != env->Namespace_BindNativeFunctions(ns, methods.data(), methods.size())) {
        return ANI_ERROR;
    }

    *result = ANI_VERSION_1;
    return ANI_OK;
}
} // namespace OHOS::Ace::Ani

ANI_EXPORT ani_status ANI_Constructor(ani_vm* vm, uint32_t* result)
{
    return OHOS::Ace::Ani::SmartGestureAniConstructor(vm, result);
}
