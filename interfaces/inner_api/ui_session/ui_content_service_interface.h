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

#ifndef FOUNDATION_ACE_INTERFACE_UI_CONTENT_SERVICE_INTERFACE_H
#define FOUNDATION_ACE_INTERFACE_UI_CONTENT_SERVICE_INTERFACE_H

#include "iremote_broker.h"

#include "ui/base/macros.h"
#include "param_config.h"

namespace OHOS {
namespace Media {
class PixelMap;
class ImageSource;
} // namespace Media
} // namespace OHOS
namespace OHOS::Ace {
class ACE_FORCE_EXPORT IUiContentService : public OHOS::IRemoteBroker {
public:
    using EventCallback = std::function<void(std::string)>;
    DECLARE_INTERFACE_DESCRIPTOR(u"ohos.ace.UIContentService");
    IUiContentService() = default;
    ~IUiContentService() override = default;
    enum {
        UI_CONTENT_SERVICE_GET_TREE = 0,
        UI_CONTENT_CONNECT,
        REGISTER_CLICK_EVENT,
        REGISTER_SEARCH_EVENT,
        REGISTER_TEXT_CHANGE_EVENT,
        REGISTER_ROUTER_CHANGE_EVENT,
        REGISTER_COMPONENT_EVENT,
        REGISTER_WEB_UNFOCUS_EVENT,
        REGISTER_SCROLL_EVENT,
        REGISTER_LIFE_CYCLE_EVENT,
        REGISTER_SELECT_TEXT_EVENT,
        UNREGISTER_CLICK_EVENT,
        UNREGISTER_SEARCH_EVENT,
        UNREGISTER_TEXT_CHANGE_EVENT,
        UNREGISTER_ROUTER_CHANGE_EVENT,
        UNREGISTER_COMPONENT_EVENT,
        UNREGISTER_WEB_UNFOCUS_EVENT,
        UNREGISTER_SCROLL_EVENT,
        UNREGISTER_LIFE_CYCLE_EVENT,
        UNREGISTER_SELECT_TEXT_EVENT,
        RESET_ALL_TEXT,
        RESET_TEXT_BY_ID,
        GET_WEB_VIEW_LANGUAGE,
        GET_WEB_TRANSLATE_TEXT,
        CONTINUE_GET_WEB_TEXT,
        SEND_TRANSLATE_RESULT,
        SEND_TRANSLATE_RESULT_STR,
        END_WEB_TRANSLATE,
        GET_CURRENT_SHOWING_IMAGE,
        GET_CURRENT_PAGE_NAME,
        GET_VISIBLE_TREE,
        SENDCOMMAND_ASYNC_EVENT,
        SENDCOMMAND_EVENT,
        SEND_COMMAND,
        EXE_APP_AI_FUNCTION,
        GET_SPECIFIED_CONTENT_OFFSETS,
        HIGHLIGHT_SPECIFIED_CONTENT,
        REGISTER_CONTENT_CHANGE,
        UNREGISTER_CONTENT_CHANGE,
        GET_HIT_TEST_NODE_INFO_FOR_TOUCH,
        REQUEST_STATE_MGMT_INFO,
    };

    /**
     * @description: define get the current page inspector tree info interface
     * @return: result number
     */
    virtual int32_t GetInspectorTree(const std::function<void(std::string, int32_t, bool)>& eventCallback,
        ParamConfig config = ParamConfig()) = 0;
    virtual int32_t GetVisibleInspectorTree(const std::function<void(std::string, int32_t, bool)>& eventCallback,
        ParamConfig config = ParamConfig()) = 0;

    /**
     * @description: define get the node info for touch test interface
     * @return: result number
     */
    virtual int32_t GetLatestHitTestNodeInfosForTouch(
        const std::function<void(std::string, int32_t, bool)>& eventCallback,
        InteractionParamConfig config = InteractionParamConfig()) = 0;

    /**
     * @description: define SA process and current process connect interface
     * @return: result number
     */
    virtual int32_t Connect(const EventCallback& eventCallback) = 0;

    /**
     * @description: define register a callback on click event occur to execute interface
     * @return: result number
     */
    virtual int32_t RegisterClickEventCallback(const EventCallback& eventCallback) = 0;

    /**
     * @description: define register a callback on switch event occur to execute interface
     * @return: result number
     */
    virtual int32_t RegisterRouterChangeEventCallback(const EventCallback& eventCallback) = 0;

    /**
     * @description: define register a callback on search event occur to execute interface
     * @return: result number
     */
    virtual int32_t RegisterSearchEventCallback(const EventCallback& eventCallback) = 0;

    /**
     * @description: define register a callback on search event occur to execute interface
     * @return: result number
     */
    virtual int32_t RegisterTextChangeEventCallback(const EventCallback& eventCallback) = 0;

    /**
     * @description: define register a callback on component event occur to execute interface
     * @return: result number
     */
    virtual int32_t RegisterComponentChangeEventCallback(const EventCallback& eventCallback) = 0;

    /**
     * @description: define register a callback on web unfocus event occur to execute interface
     * @return: result number
     */
    virtual int32_t RegisterWebUnfocusEventCallback(
        const std::function<void(int64_t accessibilityId, const std::string& data)>& eventCallback) = 0;

    /**
     * @description: define register a callback on scroll event occur to execute interface
     * @return: result number
     */
    virtual int32_t RegisterScrollEventCallback(const EventCallback& eventCallback) = 0;

    /**
     * @description: define register a callback on life cycle event occur to execute interface
     * @return: result number
     */
    virtual int32_t RegisterLifeCycleEventCallback(const EventCallback& eventCallback) = 0;

    /**
     * @description: define register a callback on select text event occur to execute interface
     * @return: result number
     */
    virtual int32_t RegisterSelectTextEventCallback(const EventCallback& eventCallback) = 0;

    /**
     * @description: define register a callback get select offsets
     * @return: result number
     */
    virtual int32_t GetSpecifiedContentOffsets(int32_t id, const std::string& content,
        const std::function<void(std::vector<std::pair<float, float>>)>& eventCallback) = 0;

    /**
     * @description: define register a callback highlight content text
     * @return: result number
     */
    virtual int32_t HighlightSpecifiedContent(int32_t id, const std::string& content,
        const std::vector<std::string>& nodeIds, const std::string& configs) = 0;

    /**
     * @description: define register a callback on SendCommand event occur to execute interface
     * @return: result number
     *          0: Node execution is successful.
     */
    virtual int32_t SendCommand(int32_t id, const std::string& command) = 0;

    /**
     * @description: define register a callback on SendCommand Async event occur to execute interface
     * @return: result number
     *          0: Node execution is successful.
     *          10: SendCommand Pipeline context is null.
     *          11: SendCommand Task executor is null.
     *          12: Error occurred during self handling of SendCommand.
     *          13: Failure due to no nodes.
     */
    virtual int32_t SendCommandAsync(int32_t id, const std::string& command) = 0;

    /**
     * @description: define register a callback on Send keycode command occur to execute interface
     * @return: result number
     */
    virtual int32_t SendCommand(const std::string command) = 0;

    /**
     * @description: define unregister the click event occur callback last register interface
     * @return: result number
     */
    virtual int32_t UnregisterClickEventCallback() = 0;

    /**
     * @description: define unregister the search event occur callback last register interface
     * @return: result number
     */
    virtual int32_t UnregisterSearchEventCallback() = 0;

    /**
     * @description: define unregister the search event occur callback last register interface
     * @return: result number
     */
    virtual int32_t UnregisterTextChangeEventCallback() = 0;

    /**
     * @description: define unregister the switch event occur callback last register interface
     * @return: result number
     */
    virtual int32_t UnregisterRouterChangeEventCallback() = 0;

    /**
     * @description: define unregister the component event occur callback last register interface
     * @return: result number
     */
    virtual int32_t UnregisterComponentChangeEventCallback() = 0;

    /**
     * @description: define unregister the web focus event occur callback last register interface
     * @return: result number
     */
    virtual int32_t UnregisterWebUnfocusEventCallback() = 0;

    /**
     * @description: define unregister the scroll event occur callback last register interface
     * @return: result number
     */
    virtual int32_t UnregisterScrollEventCallback() = 0;

    /**
     * @description: define unregister the life cycle event occur callback last register interface
     * @return: result number
     */
    virtual int32_t UnregisterLifeCycleEventCallback() = 0;

    /**
     * @description: define unregister the select text event occur callback last register interface
     * @return: result number
     */
    virtual int32_t UnregisterSelectTextEventCallback() = 0;

    /**
     * @description:get web need translate text
     * @return: result number
     */
    virtual int32_t GetWebViewTranslateText(
        const std::string& data, const std::function<void(int32_t, std::string)>& eventCallback) = 0;

    /**
     * @description:send translate result by cloud service
     * @return: result number
     */
    virtual int32_t SendTranslateResult(int32_t nodeId, std::vector<std::string> results, std::vector<int32_t> ids) = 0;

    /**
     * @description:send translate result by cloud service
     * @return: result number
     */
    virtual int32_t SendTranslateResult(int32_t nodeId, std::string result) = 0;

    /**
     * @description:start continuity translate
     * @return: result number
     */
    virtual int32_t StartWebViewTranslate(
        const std::string& data, const std::function<void(int32_t, std::string)>& eventCallback) = 0;

    /**
     * @description:end continuity translate
     * @return: result number
     */
    virtual int32_t EndWebViewTranslate() = 0;

    /**
     * @description:reset all components with translate
     * @return: result number
     */
    virtual int32_t ResetTranslateTextAll() = 0;

    /**
     * @description:reset one component with translate by id
     * @return: result number
     */
    virtual int32_t ResetTranslateText(int32_t nodeId) = 0;

    /**
     * @description:get web component current language
     * @return: result number
     */
    virtual int32_t GetWebViewCurrentLanguage(const EventCallback& eventCallback) = 0;

    /**
     * @description:get web component current page name
     * @return: result number
     */
    virtual int32_t GetCurrentPageName(const std::function<void(std::string)>& finishCallback) = 0;

    /**
     * @description:get all image with use imageComponents
     * @return: result number
     */
    virtual int32_t GetCurrentImagesShowing(
        const std::function<void(std::vector<std::pair<int32_t, std::shared_ptr<Media::PixelMap>>>)>&
            finishCallback) = 0;

    /* Not Used Ipc Interface*/
    /**
     * AI to judge if connect
     */
    virtual bool IsConnect() = 0;

    /**
     * @description: execute application AI function
     * @return: result number
     */
    virtual int32_t ExeAppAIFunction(const std::string& funcName, const std::string& params,
        const std::function<void(uint32_t)>& finishCallback) = 0;

    /**
     * @description: define register a callback on content change occur to execute interface
     * @return: result number
     */
    virtual int32_t RegisterContentChangeCallback(const ContentChangeConfig& config,
        const std::function<void(ChangeType type, const std::string& simpleTree)> callback) = 0;

    /**
     * @description: define unregister the content change occur callback last register interface
     * @return: result number
     */
    virtual int32_t UnregisterContentChangeCallback() = 0;

    /**
     * @description: define get the values of state variables that meets specified conditions
     * @return: result number
     */
    virtual int32_t GetStateMgmtInfo(const std::string& componentName, const std::string& propertyName,
        const std::string& jsonPath, const std::function<void(std::vector<std::string>)>& eventCallback) = 0;
};
class ACE_FORCE_EXPORT ReportService : public OHOS::IRemoteBroker {
public:
    using EventCallback = std::function<void(std::string)>;
    DECLARE_INTERFACE_DESCRIPTOR(u"ohos.ace.ReportService");
    ReportService() = default;
    ~ReportService() override = default;
    enum {
        REPORT_CLICK_EVENT,
        REPORT_SWITCH_EVENT,
        REPORT_COMPONENT_EVENT,
        REPORT_SEARCH_EVENT,
        REPORT_TEXT_CHANGE_EVENT,
        REPORT_INSPECTOR_VALUE,
        REPORT_WEB_UNFOCUS_EVENT,
        REPORT_SCROLL_EVENT,
        REPORT_LIFE_CYCLE_EVENT,
        REPORT_SELECT_TEXT_EVENT,
        SEND_BASE_INFO,
        SEND_CURRENT_LANGUAGE,
        SEND_TEXT,
        SEND_IMAGES,
        SEND_CURRENT_PAGE_NAME,
        SEND_EXE_APP_AI_FUNCTION_RESULT,
        SEND_SPECIFIED_CONTENT_OFFSETS,
        SEND_CONTENT_CHANGE,
        REPORT_HIT_TEST_NODE_INFOS,
        REPORT_STATE_MGMT_INFO,
    };

    /**
     * @description: define reports the click event to the proxy interface
     */
    virtual void ReportClickEvent(const std::string& data) = 0;

    /**
     * @description: define reports the switch event to the proxy interface
     */
    virtual void ReportRouterChangeEvent(const std::string& data) = 0;

    /**
     * @description: define reports the component change event to the proxy interface
     */
    virtual void ReportComponentChangeEvent(const std::string& data) = 0;

    /**
     * @description: define reports the search event to the proxy interface
     */
    virtual void ReportSearchEvent(const std::string& data) = 0;

    /**
     * @description: define reports the text change event to the proxy interface
     */
    virtual void ReportTextChangeEvent(const std::string& data) = 0;

    /**
     * @description: define reports inspector value to the proxy interface
     */
    virtual void ReportInspectorTreeValue(const std::string& data, int32_t partNum, bool isLastPart) = 0;

    /**
     * @description: define reports the information of hit test node to the proxy interface
     */
    virtual void ReportHitTestNodeInfos(const std::string& data, int32_t partNum, bool isLastPart) = 0;

    /**
     * @description: define reports web unfocus value to the proxy interface
     */
    virtual void ReportWebUnfocusEvent(int64_t accessibilityId, const std::string& data) = 0;

    /**
     * @description: define reports the scroll event to the proxy interface
     */
    virtual void ReportScrollEvent(const std::string& data) = 0;

    /**
     * @description: define reports the life cycle event to the proxy interface
     */
    virtual void ReportLifeCycleEvent(const std::string& data) = 0;

    /**
     * @description: define reports the select text event to the proxy interface
     */
    virtual void ReportSelectTextEvent(const std::string& data) = 0;

    /**
     * @description: define reports the select content offsets to the proxy interface
     */
    virtual void SendSpecifiedContentOffsets(const std::vector<std::pair<float, float>>& offsets) = 0;

    /**
     * @description: define send base info value to the proxy interface
     */
    virtual void SendBaseInfo(const std::string& data) = 0;

    /**
     * @description: define ui send text for cloud service interface
     */
    virtual void SendWebText(int32_t nodeId, std::string res) = 0;

    /**
     * @description: define ui send web component language for cloud service interface
     */
    virtual void SendCurrentLanguage(const std::string& data) = 0;

    /**
     * @description: define ui collect all pixelMap for sa service
     */
    virtual void SendShowingImage(std::vector<std::pair<int32_t, std::shared_ptr<Media::PixelMap>>> maps) = 0;

    /**
     * @description: define ui send page name for sa service
     */
    virtual void SendCurrentPageName(const std::string& data) = 0;

    /**
     * @description: define ui send execute application AI function result for sa service
     */
    virtual void SendExeAppAIFunctionResult(uint32_t result) = 0;

    /**
     * @description: define send the content change to the proxy interface
     */
    virtual void SendContentChange(ChangeType type, const std::string& simpleTree) = 0;

    /**
     * @description: define send the state management info to the proxy interface
     */
    virtual void ReportGetStateMgmtInfo(std::vector<std::string> results) = 0;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_UI_CONTENT_SERVICE_INTERFACE_H
