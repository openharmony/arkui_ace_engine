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

#include <algorithm>
#include <memory>
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "interfaces/napi/kits/utils/napi_utils.h"

#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/common/event_manager.h"
#include "core/common/frontend.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/manager/smart_gesture/smart_gesture_manager.h"
#include "core/pipeline_ng/pipeline_context.h"
extern const char _binary_smartgesturecontroller_js_start[];
extern const char _binary_smartgesturecontroller_abc_start[];
#if !defined(IOS_PLATFORM)
extern const char _binary_smartgesturecontroller_js_end[];
extern const char _binary_smartgesturecontroller_abc_end[];
#else
extern const char* _binary_smartgesturecontroller_js_end;
extern const char* _binary_smartgesturecontroller_abc_end;
#endif

namespace OHOS::Ace::Napi {
namespace {

constexpr size_t ARG_COUNT_ZERO = 0;
constexpr size_t ARG_COUNT_ONE = 1;

constexpr char ACTION_KEY[] = "action";
constexpr char OPERATE_INTENTION_KEY[] = "operateIntention";
constexpr char NODE_KEY[] = "node";
constexpr char PAGE_COUNT_KEY[] = "pageCount";
constexpr char DISTANCE_KEY[] = "distance";
constexpr char IS_CONSUMED_KEY[] = "isConsumed";
constexpr char SELECTED_PROPOSAL_KEY[] = "selectedProposal";
constexpr char NODE_PTR_KEY[] = "nodePtr_";
constexpr char ORIGINAL_MONITOR_CALLBACK_KEY[] = "__arkuiSmartGestureOriginalMonitorCallback__";

constexpr char INVALID_PARAM_COUNT_MESSAGE[] = "The number of parameters is incorrect.";
constexpr char INVALID_ENABLED_TYPE_MESSAGE[] = "The type of enabled is not boolean.";
constexpr char INVALID_MONITOR_CALLBACK_TYPE_MESSAGE[] = "The type of monitorCallback is not function.";
constexpr char INVALID_ID_TYPE_MESSAGE[] = "The type of id is not string.";
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

NG::SmartGestureHandlingResolution CreateRejectedResolution()
{
    NG::SmartGestureHandlingResolution resolution;
    resolution.isConsumed = false;
    return resolution;
}

NG::SmartGestureHandlingResolution CreateAcceptedResolution()
{
    NG::SmartGestureHandlingResolution resolution;
    resolution.isConsumed = true;
    return resolution;
}

std::string StringifyNapiValue(napi_env env, napi_value value)
{
    CHECK_NULL_RETURN(env != nullptr && value != nullptr, "");
    napi_value stringValue = nullptr;
    if (napi_coerce_to_string(env, value, &stringValue) != napi_ok) {
        return "";
    }
    std::string result;
    if (!NapiStringToString(env, stringValue, result)) {
        return "";
    }
    return result;
}

bool IsStrictlyEqual(napi_env env, napi_value left, napi_value right)
{
    CHECK_NULL_RETURN(env != nullptr && left != nullptr && right != nullptr, false);
    bool result = false;
    CHECK_NULL_RETURN(napi_strict_equals(env, left, right, &result) == napi_ok, false);
    return result;
}

napi_value GetOriginalMonitorCallback(napi_env env, napi_value wrapper)
{
    CHECK_NULL_RETURN(env != nullptr && wrapper != nullptr, nullptr);
    bool hasProperty = false;
    CHECK_NULL_RETURN(
        napi_has_named_property(env, wrapper, ORIGINAL_MONITOR_CALLBACK_KEY, &hasProperty) == napi_ok, nullptr);
    if (!hasProperty) {
        return nullptr;
    }
    napi_value originalCallback = nullptr;
    CHECK_NULL_RETURN(
        napi_get_named_property(env, wrapper, ORIGINAL_MONITOR_CALLBACK_KEY, &originalCallback) == napi_ok, nullptr);
    return originalCallback;
}

void LogMonitorFailure(const char* message, const std::string& detail = "")
{
    if (detail.empty()) {
        TAG_LOGW(AceLogTag::ACE_GESTURE, "%{public}s", message);
        return;
    }
    TAG_LOGW(AceLogTag::ACE_GESTURE, "%{public}s %{public}s", message, detail.c_str());
}

class ScopedHandleScope final {
public:
    explicit ScopedHandleScope(napi_env env) : env_(env)
    {
        if (env_ != nullptr && napi_open_handle_scope(env_, &scope_) != napi_ok) {
            scope_ = nullptr;
        }
    }

    ~ScopedHandleScope()
    {
        if (scope_ != nullptr) {
            napi_close_handle_scope(env_, scope_);
        }
    }

    bool IsValid() const
    {
        return scope_ != nullptr;
    }

private:
    napi_env env_ = nullptr;
    napi_handle_scope scope_ = nullptr;
};

class SmartGestureCodec final {
public:
    static napi_value EncodeRawProposal(napi_env env, int32_t instanceId, const NG::SmartGestureProposal& proposal)
    {
        CHECK_NULL_RETURN(env, nullptr);
        napi_value object = nullptr;
        napi_create_object(env, &object);

        napi_value action = nullptr;
        napi_create_int32(env, static_cast<int32_t>(ToJsAction(proposal)), &action);
        napi_set_named_property(env, object, ACTION_KEY, action);

        napi_value intention = nullptr;
        napi_create_int32(env, static_cast<int32_t>(ToJsOperateIntention(proposal.operateIntention)), &intention);
        napi_set_named_property(env, object, OPERATE_INTENTION_KEY, intention);

        auto targetNode = proposal.GetTargetNode();
        if (targetNode) {
            auto nodeValue = CreateFrameNodeObject(env, instanceId, targetNode);
            if (nodeValue != nullptr) {
                napi_set_named_property(env, object, NODE_KEY, nodeValue);
            }
        }

        if (proposal.scrollingConfig.has_value()) {
            if (proposal.scrollingConfig->count.has_value()) {
                napi_value pageCount = nullptr;
                napi_create_int32(env, proposal.scrollingConfig->count.value(), &pageCount);
                napi_set_named_property(env, object, PAGE_COUNT_KEY, pageCount);
            }
            if (proposal.scrollingConfig->distance.has_value()) {
                napi_value distance = nullptr;
                napi_create_double(env, proposal.scrollingConfig->distance.value(), &distance);
                napi_set_named_property(env, object, DISTANCE_KEY, distance);
            }
        }
        return object;
    }

    static bool DecodeRawProposal(napi_env env, napi_value value, std::optional<NG::SmartGestureProposal>& outProposal)
    {
        CHECK_NULL_RETURN(GetValueType(env, value) == napi_object, false);

        auto action = ParseJsAction(env, value);
        CHECK_NULL_RETURN(action.has_value(), false);
        auto intention = ToNativeOperateIntention(GetOptionalInt32Property(env, value, OPERATE_INTENTION_KEY), *action);
        switch (*action) {
            case JsSmartGestureAction::NONE:
                outProposal = NG::SmartGestureProposal(NG::SmartGestureProposalType::NONE_ACTION, intention);
                return true;
            case JsSmartGestureAction::BACK_PRESS:
                outProposal = NG::SmartGestureProposal(NG::SmartGestureProposalType::BACK_PRESS, intention);
                return true;
            case JsSmartGestureAction::CLICK:
            case JsSmartGestureAction::SELECT:
            case JsSmartGestureAction::PAGE_FORWARD:
            case JsSmartGestureAction::SCROLL_FORWARD:
                break;
        }

        CHECK_NULL_RETURN(HasProperty(env, value, NODE_KEY), false);
        napi_value nodeValue = nullptr;
        NAPI_CALL_BASE(env, napi_get_named_property(env, value, NODE_KEY, &nodeValue), false);
        auto frameNode = ParseFrameNode(env, nodeValue);
        CHECK_NULL_RETURN(frameNode, false);

        if (*action == JsSmartGestureAction::CLICK) {
            outProposal = NG::SmartGestureProposal(NG::SmartGestureProposalType::CLICK, intention, frameNode);
            return true;
        }
        if (*action == JsSmartGestureAction::SELECT) {
            outProposal = NG::SmartGestureProposal(NG::SmartGestureProposalType::SELECT, intention, frameNode);
            return true;
        }

        NG::ScrollingConfig config;
        config.count = GetOptionalInt32Property(env, value, PAGE_COUNT_KEY);
        config.distance = GetOptionalDoubleProperty(env, value, DISTANCE_KEY);
        CHECK_NULL_RETURN(config.HasValue(), false);
        outProposal = NG::SmartGestureProposal(NG::SmartGestureProposalType::SCROLL, intention, frameNode, config);
        return true;
    }

    static MonitorResolutionParseResult DecodeRawResolution(
        napi_env env, napi_value value, NG::SmartGestureHandlingResolution& resolution)
    {
        if (GetValueType(env, value) != napi_object) {
            return MonitorResolutionParseResult::INVALID_RESOLUTION;
        }

        auto consumed = GetOptionalBoolProperty(env, value, IS_CONSUMED_KEY);
        if (!consumed.has_value()) {
            return MonitorResolutionParseResult::INVALID_RESOLUTION;
        }
        resolution.isConsumed = consumed.value();

        if (!HasProperty(env, value, SELECTED_PROPOSAL_KEY)) {
            return MonitorResolutionParseResult::SUCCESS;
        }

        napi_value selectedProposal = nullptr;
        NAPI_CALL_BASE(env, napi_get_named_property(env, value, SELECTED_PROPOSAL_KEY, &selectedProposal),
            MonitorResolutionParseResult::INVALID_RESOLUTION);
        std::optional<NG::SmartGestureProposal> parsedProposal;
        if (!DecodeRawProposal(env, selectedProposal, parsedProposal)) {
            return MonitorResolutionParseResult::INVALID_SELECTED_PROPOSAL;
        }
        resolution.hasSelectedProposal = true;
        resolution.selectedProposal = parsedProposal;
        return MonitorResolutionParseResult::SUCCESS;
    }

private:
    static std::optional<int32_t> GetOptionalInt32Property(napi_env env, napi_value object, const char* key)
    {
        CHECK_NULL_RETURN(GetValueType(env, object) == napi_object, std::nullopt);
        if (!HasProperty(env, object, key)) {
            return std::nullopt;
        }

        napi_value value = nullptr;
        napi_get_named_property(env, object, key, &value);
        if (GetValueType(env, value) != napi_number) {
            return std::nullopt;
        }

        int32_t result = 0;
        napi_get_value_int32(env, value, &result);
        return result;
    }

    static std::optional<double> GetOptionalDoubleProperty(napi_env env, napi_value object, const char* key)
    {
        CHECK_NULL_RETURN(GetValueType(env, object) == napi_object, std::nullopt);
        if (!HasProperty(env, object, key)) {
            return std::nullopt;
        }

        napi_value value = nullptr;
        napi_get_named_property(env, object, key, &value);
        if (GetValueType(env, value) != napi_number) {
            return std::nullopt;
        }

        double result = 0.0;
        napi_get_value_double(env, value, &result);
        return result;
    }

    static std::optional<bool> GetOptionalBoolProperty(napi_env env, napi_value object, const char* key)
    {
        CHECK_NULL_RETURN(GetValueType(env, object) == napi_object, std::nullopt);
        if (!HasProperty(env, object, key)) {
            return std::nullopt;
        }

        napi_value value = nullptr;
        napi_get_named_property(env, object, key, &value);
        if (GetValueType(env, value) != napi_boolean) {
            return std::nullopt;
        }

        bool result = false;
        napi_get_value_bool(env, value, &result);
        return result;
    }

    static std::optional<JsSmartGestureAction> ParseJsAction(napi_env env, napi_value object)
    {
        auto actionValue = GetOptionalInt32Property(env, object, ACTION_KEY);
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
        return std::nullopt;
    }

    static RefPtr<NG::FrameNode> ParseFrameNode(napi_env env, napi_value object)
    {
        CHECK_NULL_RETURN(GetValueType(env, object) == napi_object, nullptr);
        CHECK_NULL_RETURN(HasProperty(env, object, NODE_PTR_KEY), nullptr);

        napi_value nodePtr = nullptr;
        NAPI_CALL_BASE(env, napi_get_named_property(env, object, NODE_PTR_KEY, &nodePtr), nullptr);
        CHECK_NULL_RETURN(GetValueType(env, nodePtr) == napi_external, nullptr);

        NG::UINode* uiNode = nullptr;
        NAPI_CALL_BASE(env, napi_get_value_external(env, nodePtr, reinterpret_cast<void**>(&uiNode)), nullptr);
        CHECK_NULL_RETURN(uiNode, nullptr);
        return AceType::DynamicCast<NG::FrameNode>(AceType::Claim(uiNode));
    }

    static napi_value CreateFrameNodeObject(napi_env env, int32_t instanceId, const RefPtr<NG::FrameNode>& frameNode)
    {
        CHECK_NULL_RETURN(env, nullptr);
        CHECK_NULL_RETURN(frameNode, nullptr);
        ContainerScope scope(instanceId);
        auto container = AceEngine::Get().GetContainer(instanceId);
        CHECK_NULL_RETURN(container, nullptr);
        auto frontend = container->GetFrontend();
        CHECK_NULL_RETURN(frontend, nullptr);
        return frontend->GetFrameNodeValueByNodeId(frameNode->GetId());
    }

    static JsOperateIntention ToJsOperateIntention(NG::SmartGestureOperateIntention intention)
    {
        switch (intention) {
            case NG::SmartGestureOperateIntention::TAP:
                return JsOperateIntention::TAP;
            case NG::SmartGestureOperateIntention::SLIDE_FORWARD:
                return JsOperateIntention::SLIDE_FORWARD;
            case NG::SmartGestureOperateIntention::BACK_PRESS:
                return JsOperateIntention::BACK_PRESS;
        }
        return JsOperateIntention::TAP;
    }

    static NG::SmartGestureOperateIntention ToNativeOperateIntention(
        std::optional<int32_t> intention, JsSmartGestureAction action)
    {
        if (intention.has_value()) {
            switch (static_cast<JsOperateIntention>(intention.value())) {
                case JsOperateIntention::TAP:
                    return NG::SmartGestureOperateIntention::TAP;
                case JsOperateIntention::SLIDE_FORWARD:
                    return NG::SmartGestureOperateIntention::SLIDE_FORWARD;
                case JsOperateIntention::BACK_PRESS:
                    return NG::SmartGestureOperateIntention::BACK_PRESS;
            }
        }

        switch (action) {
            case JsSmartGestureAction::BACK_PRESS:
                return NG::SmartGestureOperateIntention::BACK_PRESS;
            case JsSmartGestureAction::PAGE_FORWARD:
            case JsSmartGestureAction::SCROLL_FORWARD:
                return NG::SmartGestureOperateIntention::SLIDE_FORWARD;
            case JsSmartGestureAction::NONE:
            case JsSmartGestureAction::SELECT:
            case JsSmartGestureAction::CLICK:
                return NG::SmartGestureOperateIntention::TAP;
        }
        return NG::SmartGestureOperateIntention::TAP;
    }

    static JsSmartGestureAction ToJsAction(const NG::SmartGestureProposal& proposal)
    {
        switch (proposal.type) {
            case NG::SmartGestureProposalType::NONE_ACTION:
                return JsSmartGestureAction::NONE;
            case NG::SmartGestureProposalType::CLICK:
                return JsSmartGestureAction::CLICK;
            case NG::SmartGestureProposalType::SELECT:
                return JsSmartGestureAction::SELECT;
            case NG::SmartGestureProposalType::BACK_PRESS:
                return JsSmartGestureAction::BACK_PRESS;
            case NG::SmartGestureProposalType::SCROLL:
                if (proposal.scrollingConfig.has_value() && proposal.scrollingConfig->count.has_value() &&
                    !proposal.scrollingConfig->distance.has_value()) {
                    return JsSmartGestureAction::PAGE_FORWARD;
                }
                return JsSmartGestureAction::SCROLL_FORWARD;
        }
        return JsSmartGestureAction::NONE;
    }
};

class SmartGestureMonitorState final {
public:
    static std::shared_ptr<SmartGestureMonitorState> Create(napi_env env, int32_t instanceId, napi_value callback)
    {
        auto state = std::make_shared<SmartGestureMonitorState>(env, instanceId);
        CHECK_NULL_RETURN(state && state->SetMonitorRef(callback), nullptr);
        return state;
    }

    SmartGestureMonitorState(napi_env env, int32_t instanceId) : env_(env), instanceId_(instanceId) {}

    ~SmartGestureMonitorState()
    {
        ResetMonitorRef();
    }

    NG::SmartGestureHandlingResolution Invoke(const NG::SmartGestureProposal& defaultProposal) const
    {
        auto resolution = CreateRejectedResolution();
        CHECK_NULL_RETURN(env_, resolution);

        ContainerScope scope(instanceId_);
        ScopedHandleScope handleScope(env_);
        CHECK_NULL_RETURN(handleScope.IsValid(), resolution);

        auto callback = GetCallback();
        CHECK_NULL_RETURN(callback != nullptr, resolution);

        auto proposalValue = SmartGestureCodec::EncodeRawProposal(env_, instanceId_, defaultProposal);
        CHECK_NULL_RETURN(proposalValue != nullptr, resolution);

        napi_value result = nullptr;
        if (napi_call_function(env_, nullptr, callback, ARG_COUNT_ONE, &proposalValue, &result) != napi_ok) {
            napi_value exception = nullptr;
            napi_get_and_clear_last_exception(env_, &exception);
            LogMonitorFailure(MONITOR_CALLBACK_EXCEPTION_MESSAGE, StringifyNapiValue(env_, exception));
            return resolution;
        }

        NG::SmartGestureHandlingResolution decodedResolution;
        auto parseResult = SmartGestureCodec::DecodeRawResolution(env_, result, decodedResolution);
        if (parseResult != MonitorResolutionParseResult::SUCCESS) {
            auto detail = parseResult == MonitorResolutionParseResult::INVALID_SELECTED_PROPOSAL
                              ? INVALID_SELECTED_PROPOSAL_MESSAGE
                              : INVALID_MONITOR_RESULT_MESSAGE;
            LogMonitorFailure(detail);
            return resolution;
        }
        return decodedResolution;
    }

    napi_env GetEnv() const
    {
        return env_;
    }

    bool MatchesCallback(napi_env env, napi_value callback) const
    {
        CHECK_NULL_RETURN(env_ != nullptr, false);
        CHECK_NULL_RETURN(env == env_, false);
        auto currentCallback = GetCallback();
        CHECK_NULL_RETURN(currentCallback != nullptr, false);
        if (IsStrictlyEqual(env_, currentCallback, callback)) {
            return true;
        }
        auto originalCallback = GetOriginalMonitorCallback(env_, currentCallback);
        if (originalCallback == nullptr) {
            return false;
        }
        return IsStrictlyEqual(env_, originalCallback, callback);
    }

    int32_t GetInstanceId() const
    {
        return instanceId_;
    }

    void Detach()
    {
        ResetMonitorRef();
        env_ = nullptr;
        instanceId_ = -1;
    }

private:
    bool SetMonitorRef(napi_value callback)
    {
        CHECK_NULL_RETURN(env_ != nullptr, false);
        NAPI_CALL_BASE(env_, napi_create_reference(env_, callback, 1, &monitorRef_), false);
        return true;
    }

    void ResetMonitorRef()
    {
        if (env_ != nullptr && monitorRef_ != nullptr) {
            napi_delete_reference(env_, monitorRef_);
        }
        monitorRef_ = nullptr;
    }

    napi_value GetCallback() const
    {
        CHECK_NULL_RETURN(env_, nullptr);
        CHECK_NULL_RETURN(monitorRef_ != nullptr, nullptr);
        napi_value callback = nullptr;
        CHECK_NULL_RETURN(napi_get_reference_value(env_, monitorRef_, &callback) == napi_ok, nullptr);
        return callback;
    }

    napi_env env_ = nullptr;
    int32_t instanceId_ = -1;
    napi_ref monitorRef_ = nullptr;
};

class SmartGestureMonitorRegistry final {
public:
    static bool Register(napi_env env, int32_t instanceId, napi_value callback)
    {
        auto state = SmartGestureMonitorState::Create(env, instanceId, callback);
        if (!state) {
            return false;
        }
        if (!AcquireEnvCleanupHook(env)) {
            return false;
        }
        states_[instanceId].emplace_back(std::move(state));
        return true;
    }

    static bool Unregister(napi_env env, int32_t instanceId, napi_value callback)
    {
        std::shared_ptr<SmartGestureMonitorState> stateToDetach;
        auto iter = states_.find(instanceId);
        if (iter == states_.end() || iter->second.empty()) {
            return false;
        }
        auto& stateStack = iter->second;
        for (auto reverseIter = stateStack.rbegin(); reverseIter != stateStack.rend(); ++reverseIter) {
            auto state = *reverseIter;
            if (!state || !state->MatchesCallback(env, callback)) {
                continue;
            }
            stateToDetach = state;
            stateStack.erase(std::next(reverseIter).base());
            break;
        }
        if (stateStack.empty()) {
            states_.erase(iter);
        }
        if (stateToDetach) {
            stateToDetach->Detach();
        }
        return stateToDetach != nullptr;
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

    static NG::SmartGestureHandlingResolution Invoke(
        int32_t instanceId, const NG::SmartGestureProposal& defaultProposal)
    {
        std::vector<std::shared_ptr<SmartGestureMonitorState>> states;
        auto iter = states_.find(instanceId);
        if (iter == states_.end() || iter->second.empty()) {
            return CreateAcceptedResolution();
        }
        states = iter->second;
        for (auto iter = states.rbegin(); iter != states.rend(); ++iter) {
            auto state = *iter;
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

        return CreateAcceptedResolution();
    }

private:
    static void HandleEnvCleanup(void* data)
    {
        auto env = static_cast<napi_env>(data);
        std::vector<std::shared_ptr<SmartGestureMonitorState>> statesToDetach;
        for (auto iter = states_.begin(); iter != states_.end();) {
            auto& stateStack = iter->second;
            auto removeIter = std::remove_if(stateStack.begin(), stateStack.end(),
                [&statesToDetach, env](const std::shared_ptr<SmartGestureMonitorState>& state) {
                    if (!state || state->GetEnv() != env) {
                        return false;
                    }
                    statesToDetach.emplace_back(state);
                    return true;
                });
            stateStack.erase(removeIter, stateStack.end());
            if (!stateStack.empty()) {
                ++iter;
                continue;
            }
            iter = states_.erase(iter);
        }
        cleanupHookEnvs_.erase(env);
        for (const auto& state : statesToDetach) {
            if (state) {
                state->Detach();
            }
        }
    }

    static bool AcquireEnvCleanupHook(napi_env env)
    {
        if (env == nullptr) {
            return false;
        }
        if (cleanupHookEnvs_.find(env) != cleanupHookEnvs_.end()) {
            return true;
        }
        if (napi_add_env_cleanup_hook(env, HandleEnvCleanup, env) != napi_ok) {
            return false;
        }
        cleanupHookEnvs_.insert(env);
        return true;
    }

    static std::unordered_map<int32_t, std::vector<std::shared_ptr<SmartGestureMonitorState>>> states_;
    static std::unordered_set<napi_env> cleanupHookEnvs_;
};

// 一个instanceId下允许注册多个monitor回调，按注册顺序保存，触发时按后进先出执行。
std::unordered_map<int32_t, std::vector<std::shared_ptr<SmartGestureMonitorState>>>
    SmartGestureMonitorRegistry::states_;
// 一个env只注册一次cleanup hook，env销毁时统一清理其名下的monitor回调。
std::unordered_set<napi_env> SmartGestureMonitorRegistry::cleanupHookEnvs_;

RefPtr<NG::SmartGestureManager> GetManagerByInstanceId(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN(container, nullptr);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipeline);
    CHECK_NULL_RETURN(context, nullptr);
    auto eventManager = context->GetEventManager();
    CHECK_NULL_RETURN(eventManager, nullptr);
    return eventManager->GetOrCreateSmartGestureManager();
}

bool TryGetCurrentInstanceId(napi_env env, int32_t& instanceId)
{
    instanceId = Container::CurrentIdSafely();
    if (instanceId >= 0) {
        return true;
    }
    return false;
}

RefPtr<NG::SmartGestureManager> GetRequiredManager(napi_env env, int32_t instanceId)
{
    auto manager = GetManagerByInstanceId(instanceId);
    if (!manager) {
        NapiThrow(env, UI_CONTEXT_NOT_FOUND_MESSAGE, ERROR_CODE_INTERNAL_ERROR);
    }
    return manager;
}

void InstallRegistryBackedMonitor(const RefPtr<NG::SmartGestureManager>& manager, int32_t instanceId)
{
    CHECK_NULL_VOID(manager);
    if (!SmartGestureMonitorRegistry::HasMonitor(instanceId)) {
        manager->SetMonitor(NG::SmartGestureManager::SmartGestureMonitor());
        return;
    }
    manager->SetMonitor(
        [instanceId](const NG::SmartGestureProposal& defaultProposal) -> NG::SmartGestureHandlingResolution {
            return SmartGestureMonitorRegistry::Invoke(instanceId, defaultProposal);
        });
}

bool GetRequiredBooleanArgument(napi_env env, napi_callback_info info, bool& value)
{
    napi_value arg = nullptr;
    napi_valuetype valueType = napi_undefined;
    if (!GetSingleParam(env, info, &arg, valueType)) {
        NapiThrow(env, INVALID_PARAM_COUNT_MESSAGE, ERROR_CODE_PARAM_INVALID);
        return false;
    }
    if (valueType != napi_boolean) {
        NapiThrow(env, INVALID_ENABLED_TYPE_MESSAGE, ERROR_CODE_PARAM_INVALID);
        return false;
    }
    return napi_get_value_bool(env, arg, &value) == napi_ok;
}

bool GetRequiredFunctionArgument(napi_env env, napi_callback_info info, napi_value& callback)
{
    napi_valuetype valueType = napi_undefined;
    if (!GetSingleParam(env, info, &callback, valueType)) {
        NapiThrow(env, INVALID_PARAM_COUNT_MESSAGE, ERROR_CODE_PARAM_INVALID);
        return false;
    }
    if (valueType != napi_function) {
        NapiThrow(env, INVALID_MONITOR_CALLBACK_TYPE_MESSAGE, ERROR_CODE_PARAM_INVALID);
        return false;
    }
    return true;
}

bool GetRequiredStringArgument(napi_env env, napi_callback_info info, std::string& value)
{
    napi_value arg = nullptr;
    napi_valuetype valueType = napi_undefined;
    if (!GetSingleParam(env, info, &arg, valueType)) {
        NapiThrow(env, INVALID_PARAM_COUNT_MESSAGE, ERROR_CODE_PARAM_INVALID);
        return false;
    }
    if (valueType != napi_string) {
        NapiThrow(env, INVALID_ID_TYPE_MESSAGE, ERROR_CODE_PARAM_INVALID);
        return false;
    }
    return NapiStringToString(env, arg, value);
}

napi_value JSEnableSmartTapAndSlideGestures(napi_env env, napi_callback_info info)
{
    bool enabled = false;
    if (!GetRequiredBooleanArgument(env, info, enabled)) {
        return nullptr;
    }

    int32_t instanceId = -1;
    if (!TryGetCurrentInstanceId(env, instanceId)) {
        return nullptr;
    }

    ContainerScope scope(instanceId);
    auto manager = GetRequiredManager(env, instanceId);
    CHECK_NULL_RETURN(manager, nullptr);
    manager->SetSmartTapAndSlideGesturesEnabled(enabled);
    return nullptr;
}

napi_value JSRegisterMonitor(napi_env env, napi_callback_info info)
{
    napi_value callback = nullptr;
    if (!GetRequiredFunctionArgument(env, info, callback)) {
        return nullptr;
    }

    int32_t instanceId = -1;
    if (!TryGetCurrentInstanceId(env, instanceId)) {
        return nullptr;
    }

    ContainerScope scope(instanceId);
    auto manager = GetRequiredManager(env, instanceId);
    CHECK_NULL_RETURN(manager, nullptr);

    if (!SmartGestureMonitorRegistry::Register(env, instanceId, callback)) {
        NapiThrow(env, MONITOR_STATE_CREATE_FAILED_MESSAGE, ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }

    InstallRegistryBackedMonitor(manager, instanceId);
    return nullptr;
}

napi_value JSUnregisterMonitor(napi_env env, napi_callback_info info)
{
    napi_value callback = nullptr;
    if (!GetRequiredFunctionArgument(env, info, callback)) {
        return nullptr;
    }

    int32_t instanceId = -1;
    if (!TryGetCurrentInstanceId(env, instanceId)) {
        return nullptr;
    }

    ContainerScope scope(instanceId);
    auto manager = GetRequiredManager(env, instanceId);
    CHECK_NULL_RETURN(manager, nullptr);
    SmartGestureMonitorRegistry::Unregister(env, instanceId, callback);
    InstallRegistryBackedMonitor(manager, instanceId);
    return nullptr;
}

napi_value JSClearMonitors(napi_env env, napi_callback_info info)
{
    size_t argc = ARG_COUNT_ZERO;
    napi_get_cb_info(env, info, &argc, nullptr, nullptr, nullptr);

    int32_t instanceId = -1;
    if (!TryGetCurrentInstanceId(env, instanceId)) {
        return nullptr;
    }

    ContainerScope scope(instanceId);
    auto manager = GetRequiredManager(env, instanceId);
    CHECK_NULL_RETURN(manager, nullptr);
    SmartGestureMonitorRegistry::Clear(instanceId);
    InstallRegistryBackedMonitor(manager, instanceId);
    return nullptr;
}

napi_value JSRequestSelected(napi_env env, napi_callback_info info)
{
    std::string inspectorId;
    if (!GetRequiredStringArgument(env, info, inspectorId)) {
        return nullptr;
    }

    int32_t instanceId = -1;
    if (!TryGetCurrentInstanceId(env, instanceId)) {
        return nullptr;
    }

    ContainerScope scope(instanceId);
    auto manager = GetRequiredManager(env, instanceId);
    CHECK_NULL_RETURN(manager, nullptr);
    manager->RequestSelected(inspectorId);
    return nullptr;
}

napi_value JSClearSelected(napi_env env, napi_callback_info info)
{
    size_t argc = ARG_COUNT_ZERO;
    napi_get_cb_info(env, info, &argc, nullptr, nullptr, nullptr);

    int32_t instanceId = -1;
    if (!TryGetCurrentInstanceId(env, instanceId)) {
        return nullptr;
    }

    ContainerScope scope(instanceId);
    auto manager = GetRequiredManager(env, instanceId);
    CHECK_NULL_RETURN(manager, nullptr);
    manager->ClearSelected();
    return nullptr;
}

napi_value SmartGestureControllerExport(napi_env env, napi_value exports)
{
    napi_property_descriptor descriptors[] = {
        DECLARE_NAPI_FUNCTION("enableSmartTapAndSlideGestures", JSEnableSmartTapAndSlideGestures),
        DECLARE_NAPI_FUNCTION("registerMonitor", JSRegisterMonitor),
        DECLARE_NAPI_FUNCTION("unregisterMonitor", JSUnregisterMonitor),
        DECLARE_NAPI_FUNCTION("clearMonitors", JSClearMonitors),
        DECLARE_NAPI_FUNCTION("requestSelected", JSRequestSelected),
        DECLARE_NAPI_FUNCTION("clearSelected", JSClearSelected),
    };
    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(descriptors) / sizeof(descriptors[0]), descriptors));
    return exports;
}

extern "C" __attribute__((visibility("default"))) void NAPI_smartgesturecontroller_GetJSCode(
    const char** buf, int* bufLen)
{
    if (buf != nullptr) {
        *buf = _binary_smartgesturecontroller_js_start;
    }
    if (bufLen != nullptr) {
        *bufLen = _binary_smartgesturecontroller_js_end - _binary_smartgesturecontroller_js_start;
    }
}

extern "C" __attribute__((visibility("default"))) void NAPI_smartgesturecontroller_GetABCCode(
    const char** buf, int* bufLen)
{
    if (buf != nullptr) {
        *buf = _binary_smartgesturecontroller_abc_start;
    }
    if (bufLen != nullptr) {
        *bufLen = _binary_smartgesturecontroller_abc_end - _binary_smartgesturecontroller_abc_start;
    }
}

static napi_module_with_js smartGestureControllerModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = SmartGestureControllerExport,
    .nm_modname = "arkui.smartGestureController",
    .nm_priv = ((void*)0),
    .nm_get_abc_code = NAPI_smartgesturecontroller_GetABCCode,
    .nm_get_js_code = NAPI_smartgesturecontroller_GetJSCode,
};

extern "C" __attribute__((constructor)) void SmartGestureControllerRegister()
{
    napi_module_with_js_register(&smartGestureControllerModule);
}

} // namespace
} // namespace OHOS::Ace::Napi
