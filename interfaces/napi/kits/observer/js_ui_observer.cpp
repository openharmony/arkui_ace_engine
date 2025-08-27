/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "js_ui_observer.h"
#include "ui_observer.h"

#include "core/common/ace_engine.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/base/node_render_status_monitor.h"
#include "interfaces/napi/kits/observer/gesture/gesture_observer.h"
#include "interfaces/napi/kits/utils/napi_utils.h"


namespace OHOS::Ace::Napi {
namespace {
#define GET_PARAMS(env, info, max) \
    size_t argc = max;             \
    napi_value argv[max] = { 0 };  \
    napi_value thisVar = nullptr;  \
    void* data;                    \
    napi_get_cb_info(env, info, &argc, argv, &thisVar, &data)

static constexpr uint32_t PARAM_SIZE_ONE = 1;
static constexpr uint32_t PARAM_SIZE_TWO = 2;
static constexpr uint32_t PARAM_SIZE_THREE = 3;
static constexpr uint32_t PARAM_SIZE_FOUR = 4;

static constexpr size_t PARAM_INDEX_ZERO = 0;
static constexpr size_t PARAM_INDEX_ONE = 1;
static constexpr size_t PARAM_INDEX_TWO = 2;
static constexpr size_t PARAM_INDEX_THREE = 3;

static constexpr uint32_t ON_SHOWN = 0;
static constexpr uint32_t ON_HIDDEN = 1;
static constexpr uint32_t ON_APPEAR = 2;
static constexpr uint32_t ON_DISAPPEAR = 3;
static constexpr uint32_t ON_WILL_SHOW = 4;
static constexpr uint32_t ON_WILL_HIDE = 5;
static constexpr uint32_t ON_WILL_APPEAR = 6;
static constexpr uint32_t ON_WILL_DISAPPEAR = 7;
static constexpr uint32_t ON_ACTIVE = 8;
static constexpr uint32_t ON_INACTIVE = 9;
static constexpr uint32_t ON_BACKPRESS = 100;

static constexpr uint32_t SCROLL_START = 0;
static constexpr uint32_t SCROLL_STOP = 1;

static constexpr uint32_t ABOUT_TO_APPEAR = 0;
static constexpr uint32_t ABOUT_TO_DISAPPEAR = 1;
static constexpr uint32_t ON_PAGE_SHOW = 2;
static constexpr uint32_t ON_PAGE_HIDE = 3;
static constexpr uint32_t ON_BACK_PRESS = 4;

static constexpr uint32_t ON_SHOW = 0;
static constexpr uint32_t ON_HIDE = 1;

static constexpr uint32_t TAP_GESTURE = 0;
static constexpr uint32_t LONG_PRESS_GESTURE = 1;
static constexpr uint32_t PAN_GESTURE = 2;
static constexpr uint32_t PINCH_GESTURE = 3;
static constexpr uint32_t SWIPE_GESTURE = 4;
static constexpr uint32_t ROTATION_GESTURE = 5;
static constexpr uint32_t DRAG = 6;
static constexpr uint32_t CLICK = 7;

static constexpr uint32_t ABOUT_TO_RENDER_IN = 0;
static constexpr uint32_t ABOUT_TO_RENDER_OUT = 1;

static constexpr uint32_t READY = 0;
static constexpr uint32_t DETECTING = 1;
static constexpr uint32_t PENDING = 2;
static constexpr uint32_t BLOCKED = 3;
static constexpr uint32_t SUCCESSFUL = 4;
static constexpr uint32_t FAILED = 5;

constexpr char NAVDESTINATION_UPDATE[] = "navDestinationUpdate";
constexpr char NAVDESTINATION_UPDATE_BY_UNIQUEID[] = "navDestinationUpdateByUniqueId";
constexpr char ROUTERPAGE_UPDATE[] = "routerPageUpdate";
constexpr char SCROLL_EVENT[] = "scrollEvent";
constexpr char DENSITY_UPDATE[] = "densityUpdate";
constexpr char LAYOUT_DONE[] = "didLayout";
constexpr char DRAW_COMMAND_SEND[] = "willDraw";
constexpr char NAVDESTINATION_SWITCH[] = "navDestinationSwitch";
constexpr char WILLCLICK_UPDATE[] = "willClick";
constexpr char DIDCLICK_UPDATE[] = "didClick";
constexpr char TAB_CONTENT_STATE[] = "tabContentUpdate";
constexpr char BEFORE_PAN_START[] = "beforePanStart";
constexpr char BEFORE_PAN_END[] = "beforePanEnd";
constexpr char AFTER_PAN_START[] = "afterPanStart";
constexpr char AFTER_PAN_END[] = "afterPanEnd";
constexpr char NODE_RENDER_STATE[] = "nodeRenderState";
constexpr char NODE_RENDER_STATE_REGISTER_ERR_MSG[] =
    "The count of nodes monitoring render state is over the limitation";

bool IsUIAbilityContext(napi_env env, napi_value context)
{
    napi_value abilityInfo = nullptr;
    napi_get_named_property(env, context, "abilityInfo", &abilityInfo);
    if (!abilityInfo) {
        return false;
    }
    napi_value abilityInfoName = nullptr;
    napi_get_named_property(env, abilityInfo, "name", &abilityInfoName);
    if (abilityInfoName) {
        return true;
    }
    return false;
}

int32_t GetUIContextInstanceId(napi_env env, napi_value uiContext)
{
    int32_t result = 0;
    if (IsUIAbilityContext(env, uiContext)) {
        return result;
    }
    napi_value instanceId = nullptr;
    napi_get_named_property(env, uiContext, "instanceId_", &instanceId);
    napi_get_value_int32(env, instanceId, &result);
    return result;
}

bool MatchValueType(napi_env env, napi_value value, napi_valuetype targetType)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, value, &valueType);
    return valueType == targetType;
}

bool ParseStringFromNapi(napi_env env, napi_value val, std::string& str)
{
    napi_valuetype type;
    return GetNapiString(env, val, str, type);
}

bool ParseNavigationId(napi_env env, napi_value obj, std::string& navigationStr)
{
    napi_value navigationId = nullptr;
    napi_get_named_property(env, obj, "navigationId", &navigationId);
    return ParseStringFromNapi(env, navigationId, navigationStr);
}

bool ParseScrollId(napi_env env, napi_value obj, std::string& result)
{
    napi_value resultId = nullptr;
    napi_get_named_property(env, obj, "id", &resultId);
    if (!MatchValueType(env, resultId, napi_string)) {
        return false;
    }
    return ParseStringFromNapi(env, resultId, result);
}

bool IsNavDestSwitchOptions(napi_env env, napi_value obj, std::string& navigationId)
{
    if (!MatchValueType(env, obj, napi_object)) {
        return false;
    }
    napi_value navId = nullptr;
    napi_get_named_property(env, obj, "navigationId", &navId);
    return ParseStringFromNapi(env, navId, navigationId);
}

RefPtr<NG::FrameNode> ParseNodeRenderStateFrameNode(napi_env env, napi_value value)
{
    if (MatchValueType(env, value, napi_number)) {
        int32_t uniqueId = 0;
        napi_get_value_int32(env, value, &uniqueId);
        auto node = OHOS::Ace::ElementRegister::GetInstance()->GetUINodeById(uniqueId);
        CHECK_NULL_RETURN(node, nullptr);
        auto frameNode = AceType::DynamicCast<NG::FrameNode>(node);
        if (!frameNode) {
            TAG_LOGW(AceLogTag::ACE_OBSERVER, "node with id: %{public}d not exist.", uniqueId);
            return nullptr;
        }
        if (node->GetTag() == V2::ROOT_ETS_TAG || node->GetTag() == V2::STAGE_ETS_TAG ||
            node->GetTag() == V2::PAGE_ETS_TAG) {
            return nullptr;
        }
        return frameNode;
    }
    if (MatchValueType(env, value, napi_string)) {
        std::string inspectorId;
        if (!ParseStringFromNapi(env, value, inspectorId)) {
            return nullptr;
        }
        auto frameNode = NG::Inspector::GetFrameNodeByKey(inspectorId);
        if (!frameNode) {
            TAG_LOGW(AceLogTag::ACE_OBSERVER, "node with id: %{public}s not exist.", inspectorId.c_str());
        }
        return frameNode;
    }
    return nullptr;
}

struct NavDestinationSwitchParams {
    bool isUIContext = true;
    std::optional<std::string> navigationId;
    napi_value callback = nullptr;
    napi_value abilityUIContext = nullptr;
    int32_t uiContextInstanceId = 0;
};

bool ParseNavDestSwitchRegisterParams(napi_env env, napi_callback_info info, NavDestinationSwitchParams& params)
{
    GET_PARAMS(env, info, PARAM_SIZE_FOUR);

    auto& secondArg = argv[PARAM_INDEX_ONE];
    auto& thirdArg = argv[PARAM_INDEX_TWO];
    auto& fourthArg = argv[PARAM_INDEX_THREE];
    std::string navigationId;
    if (argc == PARAM_SIZE_TWO && MatchValueType(env, secondArg, napi_function)) {
        // js code: UIObserver.on('navDestinationSwitch', callback)
        params.callback = secondArg;
    } else if (argc == PARAM_SIZE_THREE && MatchValueType(env, secondArg, napi_object) &&
        MatchValueType(env, thirdArg, napi_function)) {
        if (IsNavDestSwitchOptions(env, secondArg, navigationId)) {
            // js code: UIObserver.on('navDestinationSwitch', { navigationId: navId }, callback)
            params.navigationId = navigationId;
        } else if (IsUIAbilityContext(env, secondArg)) {
            // js code: observer.on('navDestinationSwitch', AbilityUIContext, callback)
            params.isUIContext = false;
            params.abilityUIContext = secondArg;
        } else {
            // js code: observer.on('navDestinationSwitch', UIContext, callback)
            params.uiContextInstanceId = GetUIContextInstanceId(env, secondArg);
        }
        params.callback = thirdArg;
    } else if (argc == PARAM_SIZE_FOUR && MatchValueType(env, secondArg, napi_object) &&
        IsNavDestSwitchOptions(env, thirdArg, navigationId) &&
        MatchValueType(env, fourthArg, napi_function)) {
        if (IsUIAbilityContext(env, secondArg)) {
            // js code: observer.on('navDestinationSwitch', AbilityUIContext, { navigationId: navId }, callback)
            params.isUIContext = false;
            params.abilityUIContext = secondArg;
        } else {
            // js code: observer.on('navDestinationSwitch', UIContext, { navigationId: navId }, callback)
            params.uiContextInstanceId = GetUIContextInstanceId(env, secondArg);
        }
        params.navigationId = navigationId;
        params.callback = fourthArg;
    } else {
        return false;
    }

    return true;
}

bool ParseNavDestSwitchUnRegisterParams(
    napi_env env, napi_value secondArg, NavDestinationSwitchParams& params)
{
    std::string navigationId;
    if (MatchValueType(env, secondArg, napi_function)) {
        // js code: UIObserver.off('navDestinationSwitch', callback)
        params.callback = secondArg;
    } else if (IsNavDestSwitchOptions(env, secondArg, navigationId)) {
        // js code: UIObserver.off('navDestinationSwitch', { navigationId: navId })
        params.navigationId = navigationId;
    } else if (MatchValueType(env, secondArg, napi_object)) {
        if (IsUIAbilityContext(env, secondArg)) {
            // js code: observer.off('navDestinationSwitch', AbilityUIContext)
            params.isUIContext = false;
            params.abilityUIContext = secondArg;
        } else {
            // js code: observer.off('navDestinationSwitch', UIContext)
            params.uiContextInstanceId = GetUIContextInstanceId(env, secondArg);
        }
    } else {
        return false;
    }

    return true;
}

bool ParseNavDestSwitchUnRegisterParams(
    napi_env env, napi_value secondArg, napi_value thirdArg, NavDestinationSwitchParams& params)
{
    std::string navigationId;
    if (MatchValueType(env, thirdArg, napi_function)) {
        params.callback = thirdArg;
        if (IsNavDestSwitchOptions(env, secondArg, navigationId)) {
            // js code: UIObserver.off('navDestinationSwitch', { navigationId: navId }, callback)
            params.navigationId = navigationId;
        } else if (MatchValueType(env, secondArg, napi_object)) {
            if (IsUIAbilityContext(env, secondArg)) {
                // js code: observer.off('navDestinationSwitch', AbilityUIContext, callback)
                params.isUIContext = false;
                params.abilityUIContext = secondArg;
            } else {
                // js code: observer.off('navDestinationSwitch', UIContext, callback)
                params.uiContextInstanceId = GetUIContextInstanceId(env, secondArg);
            }
        } else {
            return false;
        }
    } else if (MatchValueType(env, secondArg, napi_object) &&
        IsNavDestSwitchOptions(env, thirdArg, navigationId)) {
        if (IsUIAbilityContext(env, secondArg)) {
            // js code: observer.off('navDestinationSwitch', AbilityUIContext, { navigationId: navId })
            params.isUIContext = false;
            params.abilityUIContext = secondArg;
        } else {
            // js code: observer.off('navDestinationSwitch', UIContext, { navigationId: navId })
            params.uiContextInstanceId = GetUIContextInstanceId(env, secondArg);
        }
        params.navigationId = navigationId;
    } else {
        return false;
    }

    return true;
}

bool ParseNavDestSwitchUnRegisterParams(
    napi_env env, napi_value secondArg, napi_value thirdArg,
    napi_value fourthArg, NavDestinationSwitchParams& params)
{
    std::string navigationId;
    auto& context = secondArg;
    auto& options = thirdArg;
    auto& callback = fourthArg;
    if (MatchValueType(env, context, napi_object) &&
        IsNavDestSwitchOptions(env, options, navigationId) &&
        MatchValueType(env, callback, napi_function)) {
        if (IsUIAbilityContext(env, context)) {
            // js code: observer.off('navDestinationSwitch', AbilityUIContext, { navigationId: navId }, callback)
            params.isUIContext = false;
            params.abilityUIContext = context;
        } else {
            // js code: observer.off('navDestinationSwitch', UIContext, { navigationId: navId }, callback)
            params.uiContextInstanceId = GetUIContextInstanceId(env, context);
        }
        params.navigationId = navigationId;
        params.callback = callback;
        return true;
    }

    return false;
}

bool ParseNavDestSwitchUnRegisterParams(
    napi_env env, napi_callback_info info, NavDestinationSwitchParams& params)
{
    GET_PARAMS(env, info, PARAM_SIZE_FOUR);

    if (argc == PARAM_SIZE_TWO) {
        return ParseNavDestSwitchUnRegisterParams(env, argv[PARAM_INDEX_ONE], params);
    } else if (argc == PARAM_SIZE_THREE) {
        return ParseNavDestSwitchUnRegisterParams(env, argv[PARAM_INDEX_ONE], argv[PARAM_INDEX_TWO], params);
    } else if (argc == PARAM_SIZE_FOUR) {
        return ParseNavDestSwitchUnRegisterParams(
            env, argv[PARAM_INDEX_ONE], argv[PARAM_INDEX_TWO], argv[PARAM_INDEX_THREE], params);
    } else if (argc != PARAM_SIZE_ONE) {
        return false;
    }

    return true;
}
} // namespace

ObserverProcess::ObserverProcess()
{
    registerProcessMap_ = {
        { NAVDESTINATION_UPDATE, &ObserverProcess::ProcessNavigationRegister },
        { NAVDESTINATION_UPDATE_BY_UNIQUEID, &ObserverProcess::ProcessNavigationRegisterByUniqueId },
        { SCROLL_EVENT, &ObserverProcess::ProcessScrollEventRegister },
        { ROUTERPAGE_UPDATE, &ObserverProcess::ProcessRouterPageRegister },
        { DENSITY_UPDATE, &ObserverProcess::ProcessDensityRegister },
        { LAYOUT_DONE, &ObserverProcess::ProcessLayoutDoneRegister },
        { DRAW_COMMAND_SEND, &ObserverProcess::ProcessDrawCommandSendRegister },
        { NAVDESTINATION_SWITCH, &ObserverProcess::ProcessNavDestinationSwitchRegister },
        { WILLCLICK_UPDATE, &ObserverProcess::ProcessWillClickRegister },
        { DIDCLICK_UPDATE, &ObserverProcess::ProcessDidClickRegister },
        { TAB_CONTENT_STATE, &ObserverProcess::ProcessTabContentStateRegister },
        { BEFORE_PAN_START, &ObserverProcess::ProcessBeforePanStartRegister },
        { AFTER_PAN_START, &ObserverProcess::ProcessAfterPanStartRegister },
        { BEFORE_PAN_END, &ObserverProcess::ProcessBeforePanEndRegister },
        { AFTER_PAN_END, &ObserverProcess::ProcessAfterPanEndRegister },
        { NODE_RENDER_STATE, &ObserverProcess::ProcessNodeRenderStateRegister },
    };
    unregisterProcessMap_ = {
        { NAVDESTINATION_UPDATE, &ObserverProcess::ProcessNavigationUnRegister },
        { NAVDESTINATION_UPDATE_BY_UNIQUEID, &ObserverProcess::ProcessNavigationUnRegisterByUniqueId },
        { SCROLL_EVENT, &ObserverProcess::ProcessScrollEventUnRegister },
        { ROUTERPAGE_UPDATE, &ObserverProcess::ProcessRouterPageUnRegister },
        { DENSITY_UPDATE, &ObserverProcess::ProcessDensityUnRegister },
        { LAYOUT_DONE, &ObserverProcess::ProcessLayoutDoneUnRegister },
        { DRAW_COMMAND_SEND, &ObserverProcess::ProcessDrawCommandSendUnRegister},
        { NAVDESTINATION_SWITCH, &ObserverProcess::ProcessNavDestinationSwitchUnRegister },
        { WILLCLICK_UPDATE, &ObserverProcess::ProcessWillClickUnRegister },
        { DIDCLICK_UPDATE, &ObserverProcess::ProcessDidClickUnRegister },
        { TAB_CONTENT_STATE, &ObserverProcess::ProcessTabContentStateUnRegister },
        { BEFORE_PAN_START, &ObserverProcess::ProcessBeforePanStartUnRegister },
        { AFTER_PAN_START, &ObserverProcess::ProcessAfterPanStartUnRegister },
        { BEFORE_PAN_END, &ObserverProcess::ProcessBeforePanEndUnRegister },
        { AFTER_PAN_END, &ObserverProcess::ProcessAfterPanEndUnRegister },
        { NODE_RENDER_STATE, &ObserverProcess::ProcessNodeRenderStateUnRegister },
    };
}

ObserverProcess& ObserverProcess::GetInstance()
{
    static ObserverProcess instance;
    return instance;
}

napi_value ObserverProcess::ProcessRegister(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, PARAM_SIZE_THREE);
    NAPI_ASSERT(env, (argc >= PARAM_SIZE_TWO && thisVar != nullptr), "Invalid arguments");
    std::string type;
    if (!ParseStringFromNapi(env, argv[PARAM_INDEX_ZERO], type)) {
        return nullptr;
    }
    auto it = registerProcessMap_.find(type);
    if (it == registerProcessMap_.end()) {
        return nullptr;
    }
    return (this->*(it->second))(env, info);
}

napi_value ObserverProcess::ProcessUnRegister(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, PARAM_SIZE_THREE);
    NAPI_ASSERT(env, (argc >= PARAM_SIZE_ONE && thisVar != nullptr), "Invalid arguments");
    std::string type;
    if (!ParseStringFromNapi(env, argv[PARAM_INDEX_ZERO], type)) {
        return nullptr;
    }
    auto it = unregisterProcessMap_.find(type);
    if (it == unregisterProcessMap_.end()) {
        return nullptr;
    }
    return (this->*(it->second))(env, info);
}

napi_value ObserverProcess::ProcessNavigationRegister(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, PARAM_SIZE_THREE);

    if (!isNavigationHandleFuncSetted_) {
        NG::UIObserverHandler::GetInstance().SetHandleNavigationChangeFunc(&UIObserver::HandleNavigationStateChange);
        isNavigationHandleFuncSetted_ = true;
    }

    if (argc == PARAM_SIZE_TWO && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_function)) {
        auto listener = std::make_shared<UIObserverListener>(env, argv[PARAM_INDEX_ONE]);
        UIObserver::RegisterNavigationCallback(listener);
    }

    if (argc == PARAM_SIZE_THREE && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object) &&
        MatchValueType(env, argv[PARAM_INDEX_TWO], napi_function)) {
        std::string id;
        if (ParseNavigationId(env, argv[PARAM_INDEX_ONE], id)) {
            auto listener = std::make_shared<UIObserverListener>(env, argv[PARAM_INDEX_TWO]);
            UIObserver::RegisterNavigationCallback(id, listener);
        }
    }

    napi_value result = nullptr;
    return result;
}

napi_value ObserverProcess::ProcessNavigationRegisterByUniqueId(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, PARAM_SIZE_THREE);

    if (!isNavigationHandleFuncSetted_) {
        NG::UIObserverHandler::GetInstance().SetHandleNavigationChangeFunc(&UIObserver::HandleNavigationStateChange);
        isNavigationHandleFuncSetted_ = true;
    }

    if (argc == PARAM_SIZE_THREE && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_number) &&
        MatchValueType(env, argv[PARAM_INDEX_TWO], napi_function)) {
        int32_t navigationUniqueId;
        if (napi_get_value_int32(env, argv[PARAM_INDEX_ONE], &navigationUniqueId) == napi_ok) {
            auto listener = std::make_shared<UIObserverListener>(env, argv[PARAM_INDEX_TWO]);
            UIObserver::RegisterNavigationCallback(navigationUniqueId, listener);
        }
    }

    napi_value result = nullptr;
    return result;
}

napi_value ObserverProcess::ProcessNavigationUnRegister(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, PARAM_SIZE_THREE);

    if (argc == PARAM_SIZE_ONE) {
        UIObserver::UnRegisterNavigationCallback(nullptr);
    }

    if (argc == PARAM_SIZE_TWO && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_function)) {
        UIObserver::UnRegisterNavigationCallback(argv[PARAM_INDEX_ONE]);
    }

    if (argc == PARAM_SIZE_TWO && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object)) {
        std::string id;
        if (ParseNavigationId(env, argv[PARAM_INDEX_ONE], id)) {
            UIObserver::UnRegisterNavigationCallback(id, nullptr);
        }
    }

    if (argc == PARAM_SIZE_THREE && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object) &&
        MatchValueType(env, argv[PARAM_INDEX_TWO], napi_function)) {
        std::string id;
        if (ParseNavigationId(env, argv[PARAM_INDEX_ONE], id)) {
            UIObserver::UnRegisterNavigationCallback(id, argv[PARAM_INDEX_TWO]);
        }
    }

    napi_value result = nullptr;
    return result;
}

napi_value ObserverProcess::ProcessNavigationUnRegisterByUniqueId(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, PARAM_SIZE_THREE);
    
    if (argc == PARAM_SIZE_TWO && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_number)) {
        int32_t navigationUniqueId;
        if (napi_get_value_int32(env, argv[PARAM_INDEX_ONE], &navigationUniqueId) == napi_ok) {
            UIObserver::UnRegisterNavigationCallback(navigationUniqueId, nullptr);
        }
    }

    if (argc == PARAM_SIZE_THREE && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_number) &&
        MatchValueType(env, argv[PARAM_INDEX_TWO], napi_function)) {
        int32_t navigationUniqueId;
        if (napi_get_value_int32(env, argv[PARAM_INDEX_ONE], &navigationUniqueId) == napi_ok) {
            UIObserver::UnRegisterNavigationCallback(navigationUniqueId, argv[PARAM_INDEX_TWO]);
        }
    }

    napi_value result = nullptr;
    return result;
}

napi_value ObserverProcess::ProcessScrollEventRegister(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, PARAM_SIZE_THREE);

    if (!isScrollEventChangeFuncSetted_) {
        NG::UIObserverHandler::GetInstance().SetHandleScrollEventChangeFunc(&UIObserver::HandleScrollEventStateChange);
        isScrollEventChangeFuncSetted_ = true;
    }
    if (argc == PARAM_SIZE_TWO && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_function)) {
        auto listener = std::make_shared<UIObserverListener>(env, argv[PARAM_INDEX_ONE]);
        UIObserver::RegisterScrollEventCallback(listener);
    }

    if (argc == PARAM_SIZE_THREE && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object)
        && MatchValueType(env, argv[PARAM_INDEX_TWO], napi_function)) {
        std::string id;
        if (ParseScrollId(env, argv[PARAM_INDEX_ONE], id)) {
            auto listener = std::make_shared<UIObserverListener>(env, argv[PARAM_INDEX_TWO]);
            UIObserver::RegisterScrollEventCallback(id, listener);
        }
    }

    napi_value result = nullptr;
    return result;
}

napi_value ObserverProcess::ProcessScrollEventUnRegister(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, PARAM_SIZE_THREE);

    if (argc == PARAM_SIZE_ONE) {
        UIObserver::UnRegisterScrollEventCallback(nullptr);
    }

    if (argc == PARAM_SIZE_TWO && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_function)) {
        UIObserver::UnRegisterScrollEventCallback(argv[PARAM_INDEX_ONE]);
    }

    if (argc == PARAM_SIZE_TWO && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object)) {
        std::string id;
        if (ParseScrollId(env, argv[PARAM_INDEX_ONE], id)) {
            UIObserver::UnRegisterScrollEventCallback(id, nullptr);
        }
    }

    if (argc == PARAM_SIZE_THREE && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object)
        && MatchValueType(env, argv[PARAM_INDEX_TWO], napi_function)) {
        std::string id;
        if (ParseScrollId(env, argv[PARAM_INDEX_ONE], id)) {
            UIObserver::UnRegisterScrollEventCallback(id, argv[PARAM_INDEX_TWO]);
        }
    }

    napi_value result = nullptr;
    return result;
}

napi_value ObserverProcess::ProcessRouterPageRegister(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, PARAM_SIZE_THREE);

    if (!isRouterPageHandleFuncSetted_) {
        NG::UIObserverHandler::GetInstance().SetHandleRouterPageChangeFunc(&UIObserver::HandleRouterPageStateChange);
        isRouterPageHandleFuncSetted_ = true;
    }

    if (argc == PARAM_SIZE_TWO && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_function)) {
        auto listener = std::make_shared<UIObserverListener>(env, argv[PARAM_INDEX_ONE]);
        UIObserver::RegisterRouterPageCallback(0, listener);
    }

    if (argc == PARAM_SIZE_THREE && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object) &&
        MatchValueType(env, argv[PARAM_INDEX_TWO], napi_function)) {
        auto context = argv[PARAM_INDEX_ONE];
        if (context) {
            auto listener = std::make_shared<UIObserverListener>(env, argv[PARAM_INDEX_TWO]);
            if (IsUIAbilityContext(env, context)) {
                UIObserver::RegisterRouterPageCallback(env, context, listener);
            } else {
                auto uiContextInstanceId = GetUIContextInstanceId(env, context);
                UIObserver::RegisterRouterPageCallback(uiContextInstanceId, listener);
            }
        }
    }

    napi_value result = nullptr;
    return result;
}

napi_value ObserverProcess::ProcessRouterPageUnRegister(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, PARAM_SIZE_THREE);

    if (argc == PARAM_SIZE_ONE) {
        UIObserver::UnRegisterRouterPageCallback(0, nullptr);
    }

    if (argc == PARAM_SIZE_TWO && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_function)) {
        UIObserver::UnRegisterRouterPageCallback(0, argv[PARAM_INDEX_ONE]);
    }

    if (argc == PARAM_SIZE_TWO && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object)) {
        napi_value context = argv[PARAM_INDEX_ONE];
        if (context) {
            if (IsUIAbilityContext(env, context)) {
                UIObserver::UnRegisterRouterPageCallback(env, context, nullptr);
            } else {
                auto uiContextInstanceId = GetUIContextInstanceId(env, context);
                UIObserver::UnRegisterRouterPageCallback(uiContextInstanceId, nullptr);
            }
        }
    }

    if (argc == PARAM_SIZE_THREE && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object) &&
        MatchValueType(env, argv[PARAM_INDEX_TWO], napi_function)) {
        napi_value context = argv[PARAM_INDEX_ONE];
        if (context) {
            if (IsUIAbilityContext(env, context)) {
                UIObserver::UnRegisterRouterPageCallback(env, context, argv[PARAM_INDEX_TWO]);
            } else {
                auto uiContextInstanceId = GetUIContextInstanceId(env, context);
                UIObserver::UnRegisterRouterPageCallback(uiContextInstanceId, argv[PARAM_INDEX_TWO]);
            }
        }
    }

    napi_value result = nullptr;
    return result;
}

napi_value ObserverProcess::ProcessDensityRegister(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, PARAM_SIZE_THREE);

    if (!isDensityChangeSetted_) {
        NG::UIObserverHandler::GetInstance().SetHandleDensityChangeFunc(&UIObserver::HandleDensityChange);
        isDensityChangeSetted_ = true;
    }
    if (argc == PARAM_SIZE_TWO && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_function)) {
        auto listener = std::make_shared<UIObserverListener>(env, argv[PARAM_INDEX_ONE]);
        int32_t instanceId = ContainerScope::CurrentId();
        UIObserver::RegisterDensityCallback(instanceId, listener);
    }

    if (argc == PARAM_SIZE_THREE && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object) &&
        MatchValueType(env, argv[PARAM_INDEX_TWO], napi_function)) {
        auto context = argv[PARAM_INDEX_ONE];
        if (context) {
            auto listener = std::make_shared<UIObserverListener>(env, argv[PARAM_INDEX_TWO]);
            auto uiContextInstanceId = GetUIContextInstanceId(env, context);
            UIObserver::RegisterDensityCallback(uiContextInstanceId, listener);
        }
    }

    napi_value result = nullptr;
    return result;
}

napi_value ObserverProcess::ProcessDensityUnRegister(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, PARAM_SIZE_THREE);

    if (argc == PARAM_SIZE_ONE) {
        int32_t instanceId = ContainerScope::CurrentId();
        UIObserver::UnRegisterDensityCallback(instanceId, nullptr);
    }

    if (argc == PARAM_SIZE_TWO && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object)) {
        napi_value context = argv[PARAM_INDEX_ONE];
        if (context) {
            auto uiContextInstanceId = GetUIContextInstanceId(env, context);
            UIObserver::UnRegisterDensityCallback(uiContextInstanceId, nullptr);
        }
    }

    if (argc == PARAM_SIZE_TWO && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_function)) {
        int32_t instanceId = ContainerScope::CurrentId();
        UIObserver::UnRegisterDensityCallback(instanceId, argv[PARAM_INDEX_ONE]);
    }

    if (argc == PARAM_SIZE_THREE && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object) &&
        MatchValueType(env, argv[PARAM_INDEX_TWO], napi_function)) {
        napi_value context = argv[PARAM_INDEX_ONE];
        if (context) {
            auto uiContextInstanceId = GetUIContextInstanceId(env, context);
            UIObserver::UnRegisterDensityCallback(uiContextInstanceId, argv[PARAM_INDEX_TWO]);
        }
    }

    napi_value result = nullptr;
    return result;
}

napi_value ObserverProcess::ProcessDrawCommandSendRegister(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, 3); // 3: Param Size Three

    if (!isDrawCommandSendChangeSetted_) {
        NG::UIObserverHandler::GetInstance().SetDrawCommandSendHandleFunc(&UIObserver::HandDrawCommandSendChange);
        isDrawCommandSendChangeSetted_ = true;
    }

    if (argc == 2 && MatchValueType(env, argv[1], napi_function)) { // 2: Param Size Two
        auto listener = std::make_shared<UIObserverListener>(env, argv[1]);
        int32_t instanceId = ContainerScope::CurrentId();
        UIObserver::RegisterDrawCallback(instanceId, listener);
    }
    if (argc == 3 && MatchValueType(env, argv[1], napi_object) && // 3: Param Size Three
        MatchValueType(env, argv[2], napi_function)) { // 2: Param Index Two
        auto context = argv[1];
        if (context) {
            auto listener = std::make_shared<UIObserverListener>(env, argv[2]); // 2: Param Index Two
            auto uiContextInstanceId = GetUIContextInstanceId(env, context);
            UIObserver::RegisterDrawCallback(uiContextInstanceId, listener);
        }
    }
    napi_value result = nullptr;
    return result;
}

napi_value ObserverProcess::ProcessDrawCommandSendUnRegister(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, 3); // 3: Param Size Three

    if (argc == 1) {
        int32_t instanceId = ContainerScope::CurrentId();
        UIObserver::UnRegisterDrawCallback(instanceId, nullptr);
    }

    if (argc == 2 && MatchValueType(env, argv[1], napi_object)) { // 2: Param Size Two
        napi_value context = argv[1];
        if (context) {
            auto uiContextInstanceId = GetUIContextInstanceId(env, context);
            UIObserver::UnRegisterDrawCallback(uiContextInstanceId, nullptr);
        }
    }

    if (argc == 2 && MatchValueType(env, argv[1], napi_function)) { // 2: Param Size Two
        int32_t instanceId = ContainerScope::CurrentId();
        UIObserver::UnRegisterDrawCallback(instanceId, argv[1]);
    }

    if (argc == 3 && MatchValueType(env, argv[1], napi_object) && // 3: Param Size Three
        MatchValueType(env, argv[2], napi_function)) { // 2: Param Index Two
        napi_value context = argv[1];
        if (context) {
            auto uiContextInstanceId = GetUIContextInstanceId(env, context);
            UIObserver::UnRegisterDrawCallback(uiContextInstanceId, argv[2]); // 2: Param Index Two
        }
    }

    napi_value result = nullptr;
    return result;
}

napi_value ObserverProcess::ProcessLayoutDoneRegister(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, 3); // 3: Param Size Three

    if (!isLayoutDoneChangeSetted_) {
        NG::UIObserverHandler::GetInstance().SetLayoutDoneHandleFunc(&UIObserver::HandLayoutDoneChange);
        isLayoutDoneChangeSetted_ = true;
    }

    if (argc == 2 && MatchValueType(env, argv[1], napi_function)) { // 2: Param Size Two
        auto listener = std::make_shared<UIObserverListener>(env, argv[1]);
        int32_t instanceId = ContainerScope::CurrentId();
        UIObserver::RegisterLayoutCallback(instanceId, listener);
    }
    if (argc == 3 && MatchValueType(env, argv[1], napi_object) && // 3: Param Size Three
        MatchValueType(env, argv[2], napi_function)) { // 2: Param Index Two
        auto context = argv[1];
        if (context) {
            auto listener = std::make_shared<UIObserverListener>(env, argv[2]); // 2: Param Index Two
            auto uiContextInstanceId = GetUIContextInstanceId(env, context);
            UIObserver::RegisterLayoutCallback(uiContextInstanceId, listener);
        }
    }
    napi_value result = nullptr;
    return result;
}

napi_value ObserverProcess::ProcessLayoutDoneUnRegister(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, 3); // 3: Param Size Three

    if (argc == 1) {
        int32_t instanceId = ContainerScope::CurrentId();
        UIObserver::UnRegisterLayoutCallback(instanceId, nullptr);
    }

    if (argc == 2 && MatchValueType(env, argv[1], napi_object)) { // 2: Param Size Two
        napi_value context = argv[1];
        if (context) {
            auto uiContextInstanceId = GetUIContextInstanceId(env, context);
            UIObserver::UnRegisterLayoutCallback(uiContextInstanceId, nullptr);
        }
    }

    if (argc == 2 && MatchValueType(env, argv[1], napi_function)) { // 2: Param Size Two
        int32_t instanceId = ContainerScope::CurrentId();
        UIObserver::UnRegisterLayoutCallback(instanceId, argv[1]);
    }

    if (argc == 3 && MatchValueType(env, argv[1], napi_object) && // 3: Param Size Three
        MatchValueType(env, argv[2], napi_function)) { // 2: Param Index Two
        napi_value context = argv[1];
        if (context) {
            auto uiContextInstanceId = GetUIContextInstanceId(env, context);
            UIObserver::UnRegisterLayoutCallback(uiContextInstanceId, argv[2]); // 2: Param Index Two
        }
    }

    napi_value result = nullptr;
    return result;
}

napi_value ObserverProcess::ProcessNavDestinationSwitchRegister(napi_env env, napi_callback_info info)
{
    NavDestinationSwitchParams params;
    if (!ParseNavDestSwitchRegisterParams(env, info, params)) {
        return nullptr;
    }

    if (!isDestinationSwitchHandleFuncSetted_) {
        NG::UIObserverHandler::GetInstance().SetHandleNavDestinationSwitchFunc(&UIObserver::HandleNavDestinationSwitch);
        isDestinationSwitchHandleFuncSetted_ = true;
    }

    auto listener = std::make_shared<UIObserverListener>(env, params.callback);
    if (params.isUIContext) {
        UIObserver::RegisterNavDestinationSwitchCallback(params.uiContextInstanceId, params.navigationId, listener);
    } else {
        UIObserver::RegisterNavDestinationSwitchCallback(env, params.abilityUIContext, params.navigationId, listener);
    }

    return nullptr;
}

napi_value ObserverProcess::ProcessNavDestinationSwitchUnRegister(napi_env env, napi_callback_info info)
{
    NavDestinationSwitchParams params;
    if (!ParseNavDestSwitchUnRegisterParams(env, info, params)) {
        return nullptr;
    }

    if (params.isUIContext) {
        UIObserver::UnRegisterNavDestinationSwitchCallback(
            params.uiContextInstanceId, params.navigationId, params.callback);
    } else {
        UIObserver::UnRegisterNavDestinationSwitchCallback(
            env, params.abilityUIContext, params.navigationId, params.callback);
    }

    return nullptr;
}

napi_value ObserverProcess::ProcessWillClickRegister(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, PARAM_SIZE_THREE);

    if (!isWillClickFuncSetted_) {
        NG::UIObserverHandler::GetInstance().SetWillClickFunc(&UIObserver::HandleWillClick);
        isWillClickFuncSetted_ = true;
    }

    if (argc == PARAM_SIZE_TWO && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_function)) {
        auto listener = std::make_shared<UIObserverListener>(env, argv[PARAM_INDEX_ONE]);
        UIObserver::RegisterWillClickCallback(0, listener);
    }

    if (argc == PARAM_SIZE_THREE && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object) &&
        MatchValueType(env, argv[PARAM_INDEX_TWO], napi_function)) {
        auto context = argv[PARAM_INDEX_ONE];
        if (context) {
            auto listener = std::make_shared<UIObserverListener>(env, argv[PARAM_INDEX_TWO]);
            if (IsUIAbilityContext(env, context)) {
                UIObserver::RegisterWillClickCallback(env, context, listener);
            } else {
                auto uiContextInstanceId = GetUIContextInstanceId(env, context);
                UIObserver::RegisterWillClickCallback(uiContextInstanceId, listener);
            }
        }
    }

    return nullptr;
}

napi_value ObserverProcess::ProcessWillClickUnRegister(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, PARAM_SIZE_THREE);

    if (argc == PARAM_SIZE_ONE) {
        UIObserver::UnRegisterWillClickCallback(0, nullptr);
    }

    if (argc == PARAM_SIZE_TWO) {
        if (MatchValueType(env, argv[PARAM_INDEX_ONE], napi_function)) {
            UIObserver::UnRegisterWillClickCallback(0, argv[PARAM_INDEX_ONE]);
        } else if (MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object)) {
            napi_value context = argv[PARAM_INDEX_ONE];
            if (!context) {
                return nullptr;
            }
            if (IsUIAbilityContext(env, context)) {
                UIObserver::UnRegisterWillClickCallback(env, context, nullptr);
            } else {
                auto uiContextInstanceId = GetUIContextInstanceId(env, context);
                UIObserver::UnRegisterWillClickCallback(uiContextInstanceId, nullptr);
            }
        }
    }

    if (argc == PARAM_SIZE_THREE && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object) &&
        MatchValueType(env, argv[PARAM_INDEX_TWO], napi_function)) {
        napi_value context = argv[PARAM_INDEX_ONE];
        if (context) {
            if (IsUIAbilityContext(env, context)) {
                UIObserver::UnRegisterWillClickCallback(env, context, argv[PARAM_INDEX_TWO]);
            } else {
                auto uiContextInstanceId = GetUIContextInstanceId(env, context);
                UIObserver::UnRegisterWillClickCallback(uiContextInstanceId, argv[PARAM_INDEX_TWO]);
            }
        }
    }

    return nullptr;
}

napi_value ObserverProcess::ProcessDidClickRegister(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, PARAM_SIZE_THREE);

    if (!isDidClickFuncSetted_) {
        NG::UIObserverHandler::GetInstance().SetDidClickFunc(&UIObserver::HandleDidClick);
        isDidClickFuncSetted_ = true;
    }

    if (argc == PARAM_SIZE_TWO && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_function)) {
        auto listener = std::make_shared<UIObserverListener>(env, argv[PARAM_INDEX_ONE]);
        UIObserver::RegisterDidClickCallback(0, listener);
    }

    if (argc == PARAM_SIZE_THREE && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object) &&
        MatchValueType(env, argv[PARAM_INDEX_TWO], napi_function)) {
        auto context = argv[PARAM_INDEX_ONE];
        if (context) {
            auto listener = std::make_shared<UIObserverListener>(env, argv[PARAM_INDEX_TWO]);
            if (IsUIAbilityContext(env, context)) {
                UIObserver::RegisterDidClickCallback(env, context, listener);
            } else {
                auto uiContextInstanceId = GetUIContextInstanceId(env, context);
                UIObserver::RegisterDidClickCallback(uiContextInstanceId, listener);
            }
        }
    }

    return nullptr;
}

napi_value ObserverProcess::ProcessDidClickUnRegister(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, PARAM_SIZE_THREE);

    if (argc == PARAM_SIZE_ONE) {
        UIObserver::UnRegisterDidClickCallback(0, nullptr);
    }

    if (argc == PARAM_SIZE_TWO) {
        if (MatchValueType(env, argv[PARAM_INDEX_ONE], napi_function)) {
            UIObserver::UnRegisterDidClickCallback(0, argv[PARAM_INDEX_ONE]);
        } else if (MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object)) {
            napi_value context = argv[PARAM_INDEX_ONE];
            if (!context) {
                return nullptr;
            }
            if (IsUIAbilityContext(env, context)) {
                UIObserver::UnRegisterDidClickCallback(env, context, nullptr);
            } else {
                auto uiContextInstanceId = GetUIContextInstanceId(env, context);
                UIObserver::UnRegisterDidClickCallback(uiContextInstanceId, nullptr);
            }
        }
    }

    if (argc == PARAM_SIZE_THREE && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object) &&
        MatchValueType(env, argv[PARAM_INDEX_TWO], napi_function)) {
        napi_value context = argv[PARAM_INDEX_ONE];
        if (context) {
            if (IsUIAbilityContext(env, context)) {
                UIObserver::UnRegisterDidClickCallback(env, context, argv[PARAM_INDEX_TWO]);
            } else {
                auto uiContextInstanceId = GetUIContextInstanceId(env, context);
                UIObserver::UnRegisterDidClickCallback(uiContextInstanceId, argv[PARAM_INDEX_TWO]);
            }
        }
    }

    return nullptr;
}

napi_value ObserverProcess::ProcessTabContentStateRegister(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, PARAM_SIZE_THREE);

    if (!isTabContentStateUpdateFuncSetted_) {
        NG::UIObserverHandler::GetInstance().SetHandleTabContentStateUpdateFunc(
            &UIObserver::HandleTabContentStateChange);
        isTabContentStateUpdateFuncSetted_ = true;
    }

    if (argc == PARAM_SIZE_TWO && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_function)) {
        auto listener = std::make_shared<UIObserverListener>(env, argv[PARAM_INDEX_ONE]);
        UIObserver::RegisterTabContentStateCallback(listener);
    }

    if (argc == PARAM_SIZE_THREE && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object)
        && MatchValueType(env, argv[PARAM_INDEX_TWO], napi_function)) {
        std::string id;
        if (ParseScrollId(env, argv[PARAM_INDEX_ONE], id)) {
            auto listener = std::make_shared<UIObserverListener>(env, argv[PARAM_INDEX_TWO]);
            UIObserver::RegisterTabContentStateCallback(id, listener);
        }
    }

    napi_value result = nullptr;
    return result;
}

napi_value ObserverProcess::ProcessTabContentStateUnRegister(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, PARAM_SIZE_THREE);

    if (argc == PARAM_SIZE_ONE) {
        UIObserver::UnRegisterTabContentStateCallback(nullptr);
    }

    if (argc == PARAM_SIZE_TWO && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_function)) {
        UIObserver::UnRegisterTabContentStateCallback(argv[PARAM_INDEX_ONE]);
    }

    if (argc == PARAM_SIZE_TWO && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object)) {
        std::string id;
        if (ParseScrollId(env, argv[PARAM_INDEX_ONE], id)) {
            UIObserver::UnRegisterTabContentStateCallback(id, nullptr);
        }
    }

    if (argc == PARAM_SIZE_THREE && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object)
        && MatchValueType(env, argv[PARAM_INDEX_TWO], napi_function)) {
        std::string id;
        if (ParseScrollId(env, argv[PARAM_INDEX_ONE], id)) {
            UIObserver::UnRegisterTabContentStateCallback(id, argv[PARAM_INDEX_TWO]);
        }
    }

    napi_value result = nullptr;
    return result;
}

napi_value ObserverProcess::ProcessBeforePanStartRegister(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, PARAM_SIZE_THREE);

    if (!isPanGestureHandleFuncSetted_) {
        NG::UIObserverHandler::GetInstance().SetPanGestureHandleFunc(&UIObserver::HandlePanGestureAccept);
        isPanGestureHandleFuncSetted_ = true;
    }

    if (argc == PARAM_SIZE_TWO && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_function)) {
        auto listener = std::make_shared<UIObserverListener>(env, argv[PARAM_INDEX_ONE]);
        UIObserver::RegisterBeforePanStartCallback(0, listener);
    }

    if (argc == PARAM_SIZE_THREE && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object) &&
        MatchValueType(env, argv[PARAM_INDEX_TWO], napi_function)) {
        auto context = argv[PARAM_INDEX_ONE];
        if (context) {
            auto listener = std::make_shared<UIObserverListener>(env, argv[PARAM_INDEX_TWO]);
            if (IsUIAbilityContext(env, context)) {
                UIObserver::RegisterBeforePanStartCallback(env, context, listener);
            } else {
                auto uiContextInstanceId = GetUIContextInstanceId(env, context);
                UIObserver::RegisterBeforePanStartCallback(uiContextInstanceId, listener);
            }
        }
    }

    return nullptr;
}

napi_value ObserverProcess::ProcessBeforePanStartUnRegister(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, PARAM_SIZE_THREE);

    if (argc == PARAM_SIZE_ONE) {
        UIObserver::UnRegisterBeforePanStartCallback(0, nullptr);
    }

    if (argc == PARAM_SIZE_TWO) {
        if (MatchValueType(env, argv[PARAM_INDEX_ONE], napi_function)) {
            UIObserver::UnRegisterBeforePanStartCallback(0, argv[PARAM_INDEX_ONE]);
        } else if (MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object)) {
            napi_value context = argv[PARAM_INDEX_ONE];
            if (!context) {
                return nullptr;
            }
            if (IsUIAbilityContext(env, context)) {
                UIObserver::UnRegisterBeforePanStartCallback(env, context, nullptr);
            } else {
                auto uiContextInstanceId = GetUIContextInstanceId(env, context);
                UIObserver::UnRegisterBeforePanStartCallback(uiContextInstanceId, nullptr);
            }
        }
    }

    if (argc == PARAM_SIZE_THREE && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object) &&
        MatchValueType(env, argv[PARAM_INDEX_TWO], napi_function)) {
        napi_value context = argv[PARAM_INDEX_ONE];
        if (context) {
            if (IsUIAbilityContext(env, context)) {
                UIObserver::UnRegisterBeforePanStartCallback(env, context, argv[PARAM_INDEX_TWO]);
            } else {
                auto uiContextInstanceId = GetUIContextInstanceId(env, context);
                UIObserver::UnRegisterBeforePanStartCallback(uiContextInstanceId, argv[PARAM_INDEX_TWO]);
            }
        }
    }

    return nullptr;
}

napi_value ObserverProcess::ProcessBeforePanEndRegister(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, PARAM_SIZE_THREE);

    if (!isPanGestureHandleFuncSetted_) {
        NG::UIObserverHandler::GetInstance().SetPanGestureHandleFunc(&UIObserver::HandlePanGestureAccept);
        isPanGestureHandleFuncSetted_ = true;
    }

    if (argc == PARAM_SIZE_TWO && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_function)) {
        auto listener = std::make_shared<UIObserverListener>(env, argv[PARAM_INDEX_ONE]);
        UIObserver::RegisterBeforePanEndCallback(0, listener);
    }

    if (argc == PARAM_SIZE_THREE && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object) &&
        MatchValueType(env, argv[PARAM_INDEX_TWO], napi_function)) {
        auto context = argv[PARAM_INDEX_ONE];
        if (context) {
            auto listener = std::make_shared<UIObserverListener>(env, argv[PARAM_INDEX_TWO]);
            if (IsUIAbilityContext(env, context)) {
                UIObserver::RegisterBeforePanEndCallback(env, context, listener);
            } else {
                auto uiContextInstanceId = GetUIContextInstanceId(env, context);
                UIObserver::RegisterBeforePanEndCallback(uiContextInstanceId, listener);
            }
        }
    }

    return nullptr;
}

napi_value ObserverProcess::ProcessBeforePanEndUnRegister(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, PARAM_SIZE_THREE);

    if (argc == PARAM_SIZE_ONE) {
        UIObserver::UnRegisterBeforePanEndCallback(0, nullptr);
    }

    if (argc == PARAM_SIZE_TWO) {
        if (MatchValueType(env, argv[PARAM_INDEX_ONE], napi_function)) {
            UIObserver::UnRegisterBeforePanEndCallback(0, argv[PARAM_INDEX_ONE]);
        } else if (MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object)) {
            napi_value context = argv[PARAM_INDEX_ONE];
            if (!context) {
                return nullptr;
            }
            if (IsUIAbilityContext(env, context)) {
                UIObserver::UnRegisterBeforePanEndCallback(env, context, nullptr);
            } else {
                auto uiContextInstanceId = GetUIContextInstanceId(env, context);
                UIObserver::UnRegisterBeforePanEndCallback(uiContextInstanceId, nullptr);
            }
        }
    }

    if (argc == PARAM_SIZE_THREE && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object) &&
        MatchValueType(env, argv[PARAM_INDEX_TWO], napi_function)) {
        napi_value context = argv[PARAM_INDEX_ONE];
        if (context) {
            if (IsUIAbilityContext(env, context)) {
                UIObserver::UnRegisterBeforePanEndCallback(env, context, argv[PARAM_INDEX_TWO]);
            } else {
                auto uiContextInstanceId = GetUIContextInstanceId(env, context);
                UIObserver::UnRegisterBeforePanEndCallback(uiContextInstanceId, argv[PARAM_INDEX_TWO]);
            }
        }
    }

    return nullptr;
}

napi_value ObserverProcess::ProcessAfterPanStartRegister(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, PARAM_SIZE_THREE);

    if (!isPanGestureHandleFuncSetted_) {
        NG::UIObserverHandler::GetInstance().SetPanGestureHandleFunc(&UIObserver::HandlePanGestureAccept);
        isPanGestureHandleFuncSetted_ = true;
    }

    if (argc == PARAM_SIZE_TWO && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_function)) {
        auto listener = std::make_shared<UIObserverListener>(env, argv[PARAM_INDEX_ONE]);
        UIObserver::RegisterAfterPanStartCallback(0, listener);
    }

    if (argc == PARAM_SIZE_THREE && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object) &&
        MatchValueType(env, argv[PARAM_INDEX_TWO], napi_function)) {
        auto context = argv[PARAM_INDEX_ONE];
        if (context) {
            auto listener = std::make_shared<UIObserverListener>(env, argv[PARAM_INDEX_TWO]);
            if (IsUIAbilityContext(env, context)) {
                UIObserver::RegisterAfterPanStartCallback(env, context, listener);
            } else {
                auto uiContextInstanceId = GetUIContextInstanceId(env, context);
                UIObserver::RegisterAfterPanStartCallback(uiContextInstanceId, listener);
            }
        }
    }

    return nullptr;
}

napi_value ObserverProcess::ProcessAfterPanStartUnRegister(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, PARAM_SIZE_THREE);

    if (argc == PARAM_SIZE_ONE) {
        UIObserver::UnRegisterAfterPanStartCallback(0, nullptr);
    }

    if (argc == PARAM_SIZE_TWO) {
        if (MatchValueType(env, argv[PARAM_INDEX_ONE], napi_function)) {
            UIObserver::UnRegisterAfterPanStartCallback(0, argv[PARAM_INDEX_ONE]);
        } else if (MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object)) {
            napi_value context = argv[PARAM_INDEX_ONE];
            if (!context) {
                return nullptr;
            }
            if (IsUIAbilityContext(env, context)) {
                UIObserver::UnRegisterAfterPanStartCallback(env, context, nullptr);
            } else {
                auto uiContextInstanceId = GetUIContextInstanceId(env, context);
                UIObserver::UnRegisterAfterPanStartCallback(uiContextInstanceId, nullptr);
            }
        }
    }

    if (argc == PARAM_SIZE_THREE && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object) &&
        MatchValueType(env, argv[PARAM_INDEX_TWO], napi_function)) {
        napi_value context = argv[PARAM_INDEX_ONE];
        if (context) {
            if (IsUIAbilityContext(env, context)) {
                UIObserver::UnRegisterAfterPanStartCallback(env, context, argv[PARAM_INDEX_TWO]);
            } else {
                auto uiContextInstanceId = GetUIContextInstanceId(env, context);
                UIObserver::UnRegisterAfterPanStartCallback(uiContextInstanceId, argv[PARAM_INDEX_TWO]);
            }
        }
    }

    return nullptr;
}

napi_value ObserverProcess::ProcessAfterPanEndRegister(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, PARAM_SIZE_THREE);

    if (!isPanGestureHandleFuncSetted_) {
        NG::UIObserverHandler::GetInstance().SetPanGestureHandleFunc(&UIObserver::HandlePanGestureAccept);
        isPanGestureHandleFuncSetted_ = true;
    }

    if (argc == PARAM_SIZE_TWO && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_function)) {
        auto listener = std::make_shared<UIObserverListener>(env, argv[PARAM_INDEX_ONE]);
        UIObserver::RegisterAfterPanEndCallback(0, listener);
    }

    if (argc == PARAM_SIZE_THREE && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object) &&
        MatchValueType(env, argv[PARAM_INDEX_TWO], napi_function)) {
        auto context = argv[PARAM_INDEX_ONE];
        if (context) {
            auto listener = std::make_shared<UIObserverListener>(env, argv[PARAM_INDEX_TWO]);
            if (IsUIAbilityContext(env, context)) {
                UIObserver::RegisterAfterPanEndCallback(env, context, listener);
            } else {
                auto uiContextInstanceId = GetUIContextInstanceId(env, context);
                UIObserver::RegisterAfterPanEndCallback(uiContextInstanceId, listener);
            }
        }
    }

    return nullptr;
}

napi_value ObserverProcess::ProcessAfterPanEndUnRegister(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, PARAM_SIZE_THREE);

    if (argc == PARAM_SIZE_ONE) {
        UIObserver::UnRegisterAfterPanEndCallback(0, nullptr);
    }

    if (argc == PARAM_SIZE_TWO) {
        if (MatchValueType(env, argv[PARAM_INDEX_ONE], napi_function)) {
            UIObserver::UnRegisterAfterPanEndCallback(0, argv[PARAM_INDEX_ONE]);
        } else if (MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object)) {
            napi_value context = argv[PARAM_INDEX_ONE];
            if (!context) {
                return nullptr;
            }
            if (IsUIAbilityContext(env, context)) {
                UIObserver::UnRegisterAfterPanEndCallback(env, context, nullptr);
            } else {
                auto uiContextInstanceId = GetUIContextInstanceId(env, context);
                UIObserver::UnRegisterAfterPanEndCallback(uiContextInstanceId, nullptr);
            }
        }
    }

    if (argc == PARAM_SIZE_THREE && MatchValueType(env, argv[PARAM_INDEX_ONE], napi_object) &&
        MatchValueType(env, argv[PARAM_INDEX_TWO], napi_function)) {
        napi_value context = argv[PARAM_INDEX_ONE];
        if (context) {
            if (IsUIAbilityContext(env, context)) {
                UIObserver::UnRegisterAfterPanEndCallback(env, context, argv[PARAM_INDEX_TWO]);
            } else {
                auto uiContextInstanceId = GetUIContextInstanceId(env, context);
                UIObserver::UnRegisterAfterPanEndCallback(uiContextInstanceId, argv[PARAM_INDEX_TWO]);
            }
        }
    }

    return nullptr;
}

napi_value ObserverProcess::ProcessNodeRenderStateRegister(napi_env env, napi_callback_info info)
{
    auto container = AceEngine::Get().GetContainer(Container::CurrentIdSafely());
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(pipeline);
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto monitor = pipelineContext->GetNodeRenderStatusMonitor();
    if (monitor->IsRegisterNodeRenderStateChangeCallbackExceedLimit()) {
        TAG_LOGE(AceLogTag::ACE_OBSERVER, "register node render state change callback exceed limit.");
        NapiThrow(env, NODE_RENDER_STATE_REGISTER_ERR_MSG, NODE_RENDER_STATE_REGISTER_ERR_CODE);
        return nullptr;
    }
    GET_PARAMS(env, info, PARAM_SIZE_THREE);

    if (argc == PARAM_SIZE_THREE && MatchValueType(env, argv[PARAM_INDEX_TWO], napi_function)) {
        auto frameNode = ParseNodeRenderStateFrameNode(env, argv[PARAM_INDEX_ONE]);
        auto listener = std::make_shared<UIObserverListener>(env, argv[PARAM_INDEX_TWO]);
        UIObserver::RegisterNodeRenderStateChangeCallback(frameNode, listener, monitor);
    }

    return nullptr;
}

napi_value ObserverProcess::ProcessNodeRenderStateUnRegister(napi_env env, napi_callback_info info)
{
    auto container = AceEngine::Get().GetContainer(Container::CurrentIdSafely());
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(pipeline);
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto monitor = pipelineContext->GetNodeRenderStatusMonitor();
    GET_PARAMS(env, info, PARAM_SIZE_THREE);

    RefPtr<NG::FrameNode> frameNode = nullptr;
    napi_value callback = nullptr;
    if (argc == PARAM_SIZE_TWO) {
        frameNode = ParseNodeRenderStateFrameNode(env, argv[PARAM_INDEX_ONE]);
    }

    if (argc == PARAM_SIZE_THREE && MatchValueType(env, argv[PARAM_INDEX_TWO], napi_function)) {
        frameNode = ParseNodeRenderStateFrameNode(env, argv[PARAM_INDEX_ONE]);
        callback = argv[PARAM_INDEX_TWO];
    }
    UIObserver::UnRegisterNodeRenderStateChangeCallback(frameNode, callback, monitor);
    return nullptr;
}

napi_value ObserverOn(napi_env env, napi_callback_info info)
{
    return ObserverProcess::GetInstance().ProcessRegister(env, info);
}

napi_value ObserverOff(napi_env env, napi_callback_info info)
{
    return ObserverProcess::GetInstance().ProcessUnRegister(env, info);
}

napi_value AddToScrollEventType(napi_env env)
{
    napi_value scrollEventType = nullptr;
    napi_value prop = nullptr;
    napi_create_object(env, &scrollEventType);
    napi_create_uint32(env, SCROLL_START, &prop);
    napi_set_named_property(env, scrollEventType, "SCROLL_START", prop);
    napi_create_uint32(env, SCROLL_STOP, &prop);
    napi_set_named_property(env, scrollEventType, "SCROLL_STOP", prop);
    return scrollEventType;
}

napi_value AddToRouterPageState(napi_env env)
{
    napi_value routerPageState = nullptr;
    napi_value prop = nullptr;
    napi_create_object(env, &routerPageState);
    napi_create_uint32(env, ABOUT_TO_APPEAR, &prop);
    napi_set_named_property(env, routerPageState, "ABOUT_TO_APPEAR", prop);
    napi_create_uint32(env, ABOUT_TO_DISAPPEAR, &prop);
    napi_set_named_property(env, routerPageState, "ABOUT_TO_DISAPPEAR", prop);
    napi_create_uint32(env, ON_PAGE_SHOW, &prop);
    napi_set_named_property(env, routerPageState, "ON_PAGE_SHOW", prop);
    napi_create_uint32(env, ON_PAGE_HIDE, &prop);
    napi_set_named_property(env, routerPageState, "ON_PAGE_HIDE", prop);
    napi_create_uint32(env, ON_BACK_PRESS, &prop);
    napi_set_named_property(env, routerPageState, "ON_BACK_PRESS", prop);
    return routerPageState;
}

napi_value CreateNavDestinationState(napi_env env)
{
    napi_value navDestinationState = nullptr;
    napi_create_object(env, &navDestinationState);
    napi_value prop = nullptr;
    napi_create_uint32(env, ON_SHOWN, &prop);
    napi_set_named_property(env, navDestinationState, "ON_SHOWN", prop);
    napi_create_uint32(env, ON_HIDDEN, &prop);
    napi_set_named_property(env, navDestinationState, "ON_HIDDEN", prop);
    napi_create_uint32(env, ON_APPEAR, &prop);
    napi_set_named_property(env, navDestinationState, "ON_APPEAR", prop);
    napi_create_uint32(env, ON_DISAPPEAR, &prop);
    napi_set_named_property(env, navDestinationState, "ON_DISAPPEAR", prop);
    napi_create_uint32(env, ON_WILL_SHOW, &prop);
    napi_set_named_property(env, navDestinationState, "ON_WILL_SHOW", prop);
    napi_create_uint32(env, ON_WILL_HIDE, &prop);
    napi_set_named_property(env, navDestinationState, "ON_WILL_HIDE", prop);
    napi_create_uint32(env, ON_WILL_APPEAR, &prop);
    napi_set_named_property(env, navDestinationState, "ON_WILL_APPEAR", prop);
    napi_create_uint32(env, ON_WILL_DISAPPEAR, &prop);
    napi_set_named_property(env, navDestinationState, "ON_WILL_DISAPPEAR", prop);
    napi_create_uint32(env, ON_BACKPRESS, &prop);
    napi_set_named_property(env, navDestinationState, "ON_BACKPRESS", prop);
    napi_create_uint32(env, ON_ACTIVE, &prop);
    napi_set_named_property(env, navDestinationState, "ON_ACTIVE", prop);
    napi_create_uint32(env, ON_INACTIVE, &prop);
    napi_set_named_property(env, navDestinationState, "ON_INACTIVE", prop);
    return navDestinationState;
}

napi_value AddToNodeRenderStateType(napi_env env)
{
    napi_value nodeRenderStateType = nullptr;
    napi_value prop = nullptr;
    napi_create_object(env, &nodeRenderStateType);
    napi_create_uint32(env, ABOUT_TO_RENDER_IN, &prop);
    napi_set_named_property(env, nodeRenderStateType, "ABOUT_TO_RENDER_IN", prop);
    napi_create_uint32(env, ABOUT_TO_RENDER_OUT, &prop);
    napi_set_named_property(env, nodeRenderStateType, "ABOUT_TO_RENDER_OUT", prop);
    return nodeRenderStateType;
}

napi_value AddToTabContentState(napi_env env)
{
    napi_value tabContentState = nullptr;
    napi_value prop = nullptr;
    napi_create_object(env, &tabContentState);
    napi_create_uint32(env, ON_SHOW, &prop);
    napi_set_named_property(env, tabContentState, "ON_SHOW", prop);
    napi_create_uint32(env, ON_HIDE, &prop);
    napi_set_named_property(env, tabContentState, "ON_HIDE", prop);
    return tabContentState;
}

napi_value AddToGestureType(napi_env env)
{
    napi_value gestureType = nullptr;
    napi_value prop = nullptr;
    napi_create_object(env, &gestureType);
    napi_create_uint32(env, TAP_GESTURE, &prop);
    napi_set_named_property(env, gestureType, "TAP_GESTURE", prop);
    napi_create_uint32(env, LONG_PRESS_GESTURE, &prop);
    napi_set_named_property(env, gestureType, "LONG_PRESS_GESTURE", prop);
    napi_create_uint32(env, PAN_GESTURE, &prop);
    napi_set_named_property(env, gestureType, "PAN_GESTURE", prop);
    napi_create_uint32(env, PINCH_GESTURE, &prop);
    napi_set_named_property(env, gestureType, "PINCH_GESTURE", prop);
    napi_create_uint32(env, SWIPE_GESTURE, &prop);
    napi_set_named_property(env, gestureType, "SWIPE_GESTURE", prop);
    napi_create_uint32(env, ROTATION_GESTURE, &prop);
    napi_set_named_property(env, gestureType, "ROTATION_GESTURE", prop);
    napi_create_uint32(env, DRAG, &prop);
    napi_set_named_property(env, gestureType, "DRAG", prop);
    napi_create_uint32(env, CLICK, &prop);
    napi_set_named_property(env, gestureType, "CLICK", prop);
    return gestureType;
}

napi_value AddToGestureRecognizerState(napi_env env)
{
    napi_value gestureRecognizerState = nullptr;
    napi_value prop = nullptr;
    napi_create_object(env, &gestureRecognizerState);
    napi_create_uint32(env, READY, &prop);
    napi_set_named_property(env, gestureRecognizerState, "READY", prop);
    napi_create_uint32(env, DETECTING, &prop);
    napi_set_named_property(env, gestureRecognizerState, "DETECTING", prop);
    napi_create_uint32(env, PENDING, &prop);
    napi_set_named_property(env, gestureRecognizerState, "PENDING", prop);
    napi_create_uint32(env, BLOCKED, &prop);
    napi_set_named_property(env, gestureRecognizerState, "BLOCKED", prop);
    napi_create_uint32(env, SUCCESSFUL, &prop);
    napi_set_named_property(env, gestureRecognizerState, "SUCCESSFUL", prop);
    napi_create_uint32(env, FAILED, &prop);
    napi_set_named_property(env, gestureRecognizerState, "FAILED", prop);
    return gestureRecognizerState;
}

static napi_value UIObserverExport(napi_env env, napi_value exports)
{
    napi_value navDestinationState = CreateNavDestinationState(env);

    napi_value scrollEventType = nullptr;
    scrollEventType = AddToScrollEventType(env);

    napi_value routerPageState = nullptr;
    routerPageState = AddToRouterPageState(env);

    napi_value tabContentState = nullptr;
    tabContentState = AddToTabContentState(env);

    napi_value gestureType = nullptr;
    gestureType = AddToGestureType(env);

    napi_value gestureRecognizerState = nullptr;
    gestureRecognizerState = AddToGestureRecognizerState(env);

    napi_value nodeRenderStateType = nullptr;
    nodeRenderStateType = AddToNodeRenderStateType(env);

    napi_property_descriptor uiObserverDesc[] = {
        DECLARE_NAPI_FUNCTION("on", ObserverOn),
        DECLARE_NAPI_FUNCTION("off", ObserverOff),
        DECLARE_NAPI_PROPERTY("NavDestinationState", navDestinationState),
        DECLARE_NAPI_PROPERTY("ScrollEventType", scrollEventType),
        DECLARE_NAPI_PROPERTY("RouterPageState", routerPageState),
        DECLARE_NAPI_PROPERTY("TabContentState", tabContentState),
        DECLARE_NAPI_PROPERTY("GestureType", gestureType),
        DECLARE_NAPI_PROPERTY("GestureRecognizerState", gestureRecognizerState),
        DECLARE_NAPI_PROPERTY("NodeRenderState", nodeRenderStateType),
    };
    NAPI_CALL(
        env, napi_define_properties(env, exports, sizeof(uiObserverDesc) / sizeof(uiObserverDesc[0]), uiObserverDesc));
    NAPI_CALL(env, GestureObserver::DefineGestureObserver(env, exports));
    return exports;
}

static napi_module uiObserverModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = UIObserverExport,
    .nm_modname = "arkui.observer",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void ObserverRegister()
{
    napi_module_register(&uiObserverModule);
}
} // namespace OHOS::Ace::Napi
