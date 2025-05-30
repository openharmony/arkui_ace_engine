/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_EVENT_REPORT_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_EVENT_REPORT_H

#include <string>
#include <vector>

#include "base/perfmonitor/perf_monitor.h"
#include "base/utils/macros.h"
#include "core/components_ng/pattern/scrollable/scrollable.h"
#include "core/components_ng/base/frame_scene_status.h"

namespace OHOS::Ace {

const std::string EXCEPTION_FRAMEWORK_APP_START = "FRAMEWORK_APP_START_EXCEPTION";
const std::string EXCEPTION_FRAMEWORK_PAGE_ROUTER = "FRAMEWORK_PAGE_ROUTER_EXCEPTION";
const std::string EXCEPTION_COMPONENT = "COMPONENT_EXCEPTION";
const std::string EXCEPTION_API_CHANNEL = "API_CHANNEL_EXCEPTION";
const std::string EXCEPTION_RENDER = "RENDER_EXCEPTION";
const std::string EXCEPTION_JS = "JS_EXCEPTION";
const std::string EXCEPTION_ANIMATION = "ANIMATION_EXCEPTION";
const std::string EXCEPTION_EVENT = "EVENT_EXCEPTION";
const std::string EXCEPTION_INTERNATIONALIZATION = "INTERNATIONALIZATION_EXCEPTION";
const std::string EXCEPTION_ACCESSIBILITY = "ACCESSIBILITY_EXCEPTION";
const std::string EXCEPTION_FORM = "FORM_EXCEPTION";

// EXCEPTION_FRAMEWORK_APP_START
enum class AppStartExcepType {
    CREATE_CONTAINER_ERR = 1,
    SET_VIEW_ERR,
    VIEW_TYPE_ERR,
    GET_PACKAGE_PATH_ERR,
    JNI_CLASS_ERR,
    JNI_INIT_ERR = 10,
    FRONTEND_TYPE_ERR,
    PIPELINE_CONTEXT_ERR,
    VIEW_STATE_ERR,
    RESOURCE_REGISTER_INIT_ERR,
    JS_ENGINE_CREATE_ERR,
    JAVA_EVENT_CALLBACK_INIT_ERR,
};

// EXCEPTION_FRAMEWORK_PAGE_ROUTER
enum class PageRouterExcepType {
    ROUTE_PARSE_ERR = 0,
    PAGE_STACK_OVERFLOW_ERR,
    RUN_PAGE_ERR,
    UPDATE_PAGE_ERR,
    LOAD_PAGE_ERR,
    REPLACE_PAGE_ERR,
};

// EXCEPTION_COMPONENT
enum class ComponentExcepType {
    TEXT_INPUT_CONNECTION_CLOSE_ERR = 0,
    GET_THEME_ERR,
    BUTTON_COMPONENT_ERR,
    DIALOG_EVENT_ERR,
    DOM_NODE_NOT_FOUND,
    SET_ROOT_DOM_NODE_ERR,
    IMAGE_ANIMATOR_ERR,
    LIST_COMPONENT_ERR,
    LIST_ITEM_ERR,
    MARQUEE_ERR,
    NAVIGATION_BAR_ERR,
};

// EXCEPTION_API_CHANNEL
enum class APIChannelExcepType {
    JS_BRIDGE_INIT_ERR = 0,
    SET_FUNCTION_ERR,
};

// EXCEPTION_RENDER
enum class RenderExcepType {
    VIEW_SCALE_ERR = 0,
    RENDER_ANIMATION_ERR,
    RENDER_COMPONENT_ERR,
    CLIP_ERR,
    UI_THREAD_STUCK,
};

// EXCEPTION_JS
enum class JsExcepType {
    GET_NODE_ERR = 0,
    CREATE_NODE_ERR,
    CREATE_DOM_BODY_ERR,
    REMOVE_DOM_ELEMENT_ERR,
    UPDATE_DOM_ELEMENT_ERR,
    JS_ENGINE_INIT_ERR,
    JS_RUNTIME_OBJ_ERR,
    JS_CONTEXT_INIT_ERR,
    JS_THREAD_STUCK,
};

// EXCEPTION_ANIMATION
enum class AnimationExcepType {
    ANIMATION_BRIDGE_ERR = 0,
    ANIMATION_PAGE_ERR,
};

// EXCEPTION_EVENT
enum class EventExcepType {
    FIRE_EVENT_ERR = 1,
};

// EXCEPTION_INTERNATIONALIZATION
enum class InternalExcepType {
    CHANGE_LOCALE_ERR = 0,
};

// EXCEPTION_ACCESSIBILITY
enum class AccessibilityExcepType {
    CREATE_ACCESSIBILITY_NODE_ERR = 0,
    GET_NODE_ERR,
};

// EXCEPTION_FORM
enum class FormExcepType {
    RUN_PAGE_ERR = 0,
    LOAD_PAGE_ERR,
    CREATE_NODE_ERR,
    UPDATE_PAGE_ERR,
    FIRE_FORM_EVENT_ERR,
    ACTION_EVENT_CALLBACK_ERR,
};

#ifdef VSYNC_TIMEOUT_CHECK
enum class VsyncExcepType {
    UI_VSYNC_TIMEOUT
};
#endif

enum class RawEventType { WARNING, FREEZE, RECOVER };

enum class ScrollableErrorType {
    GET_CHILD_FAILED = 0,
    INTERNAL_ERROR,
    GESTURE_MISMATCH,
    CONTROLLER_NOT_BIND,
    STOP_ANIMATION_TIMEOUT,
};

struct EventInfo {
    std::string eventType;
    int32_t errorType = 0;
    std::string pageUrl;
};

struct DragInfo {
    int32_t isCrossing = -1;
    int32_t result = -1;
    int32_t summaryNum = -1;
    std::string dragBehavior;
    std::string pNameId;
    std::string pVersionId;
    std::string hostName;
    std::string summaryType;
    std::string allowDropType;
};

enum class RichEditorErrorType {
    DELETE_BACKWARD = 0,
    DELETE_FORWARD,
    INSERT_VALUE,
    DELETE_NODE,
};

struct RichEditorInfo {
    RichEditorErrorType errorType;
    int32_t spanLength = -1;
    int32_t textLength = -1;
    int32_t spanIndex = -1;
};

struct FRCSceneFpsInfo {
    int64_t duration_120 = 0;
    int64_t duration_90 = 0;
    int64_t duration_72 = 0;
    int64_t duration_60 = 0;
};

class ACE_FORCE_EXPORT EventReport {
public:
    static void SendEvent(const EventInfo& eventInfo);
    static void SendJsCardRenderTimeEvent(
        const std::string& sessionID,
        const std::string& timeType,
        uint64_t timeDelay);

    static void SendAppStartException(AppStartExcepType type);
    static void SendPageRouterException(PageRouterExcepType type, const std::string& pageUrl = "");
    static void SendComponentException(ComponentExcepType type);
    static void SendAPIChannelException(APIChannelExcepType type);
    static void SendRenderException(RenderExcepType type);
    static void SendJsException(JsExcepType type);
    static void SendAnimationException(AnimationExcepType type);
    static void SendEventException(EventExcepType type);
    static void SendInternalException(InternalExcepType type);
    static void SendAccessibilityException(AccessibilityExcepType type);
    static void ReportAccessibilityFailEvent(const std::string& actionName);
    static void SendFormException(FormExcepType type);
#ifdef VSYNC_TIMEOUT_CHECK
    static void SendVsyncException(VsyncExcepType type, uint32_t windowId, int32_t instanceId, uint64_t timeStamp);
#endif

    static void JsEventReport(int32_t eventType, const std::string& jsonStr);
    static void JsErrReport(
        const std::string& packageName, const std::string& reason, const std::string& summary);
    static void ANRRawReport(RawEventType type, int32_t uid, const std::string& packageName,
        const std::string& processName, const std::string& msg = " ");
    static void ANRShowDialog(int32_t uid, const std::string& packageName,
        const std::string& processName, const std::string& msg = "");
    static void JankFrameReport(int64_t startTime, int64_t duration, const std::vector<uint16_t>& jank,
        const std::string& pageUrl, uint32_t jankStatusVersion = 1);
    static void ReportDoubleClickTitle(int32_t stateChange);
    static void ReportClickTitleMaximizeMenu(int32_t maxMenuItem, int32_t stateChange);
    static void ReportPageNodeOverflow(const std::string& pageUrl, int32_t nodeCount, int32_t threshold);
    static void ReportPageDepthOverflow(const std::string& pageUrl, int32_t depth, int32_t threshold);
    static void ReportFunctionTimeout(const std::string& functionName, int64_t time, int32_t threshold);
    static void ReportHoverStatusChange(int32_t foldStatus, int32_t time, bool isHoverMode,
        int32_t appRotation, int32_t windowMode);
    static void ReportNonManualPostCardActionInfo(const std::string& formName, const std::string& bundleName,
        const std::string& abilityName, const std::string& moduleName, int32_t dimension);
    static void ReportUiExtensionTransparentEvent(const std::string& pageUrl, const std::string& bundleName,
        const std::string& moduleName);
    static void ReportDragInfo(const DragInfo& dragInfo);
    static void ReportRichEditorInfo(const RichEditorInfo& richEditorInfo);
    static void ReportScrollableErrorEvent(
        const std::string& nodeType, ScrollableErrorType errorType, const std::string& subErrorType);
    static void ReportTextFieldErrorEvent(int32_t frameNodeId, int32_t depth, const std::string& errorType);
    static void ReportClipboardFailEvent(const std::string& errorType);
    static void ReportReusedNodeSkipMeasureApp();
    static void ReportPageSlidInfo(NG::SlidInfo &slidInfo);
    static void SendDiffFrameRatesDuring(const std::string& scene, const FRCSceneFpsInfo& curFRCSceneFpsInfo_);
    static void FrameRateDurationsStatistics(int32_t expectedRate, const std::string& scene, NG::SceneStatus status);
    static void AddFrameRateDuration(int32_t frameRate, int64_t duration);

private:
    static void SendEventInner(const EventInfo& eventInfo);
    static FRCSceneFpsInfo curFRCSceneFpsInfo_;
    static int64_t calTime_;
    static int32_t calFrameRate_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_EVENT_REPORT_H
