/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEB_DELEGATE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEB_DELEGATE_H

#include <list>
#include <map>

#include "ability_runtime/context/environment_callback.h"
#include "base/memory/referenced.h"
#include "core/components_ng/render/render_surface.h"
#include "core/pipeline/pipeline_base.h"
#if defined (OHOS_STANDARD_SYSTEM) && defined (ENABLE_ROSEN_BACKEND)
#include <ui/rs_surface_node.h>
#endif

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>
#include "base/image/pixel_map.h"
#include "core/common/recorder/event_recorder.h"
#include "core/common/container.h"
#include "core/components/common/layout/constants.h"
#include "core/components/web/resource/web_client_impl.h"
#include "core/components/web/resource/web_resource.h"
#include "core/components/web/web_component.h"
#include "core/components/web/web_event.h"
#include "core/components_ng/pattern/web/web_event_hub.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#include "nweb_accessibility_node_info.h"
#include "surface_delegate.h"
#ifdef OHOS_STANDARD_SYSTEM
#include "nweb_handler.h"
#include "nweb_helper.h"
#include "nweb_hit_testresult.h"
#include "app_mgr_client.h"
#ifdef ENABLE_ROSEN_BACKEND
#include "surface.h"
#include "core/components_ng/render/adapter/rosen_render_surface.h"
#endif
#include "wm/window.h"
#endif

namespace OHOS::Ace {

typedef struct WindowsSurfaceInfoTag {
    void* window;
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
} WindowsSurfaceInfo;

typedef NWeb::NativeArkWebOnJavaScriptProxyCallback NativeMethodCallback;

class WebMessagePortOhos : public WebMessagePort {
    DECLARE_ACE_TYPE(WebMessagePortOhos, WebMessagePort)

public:
    WebMessagePortOhos(WeakPtr<WebDelegate> webDelegate) : webDelegate_(webDelegate) {}
    WebMessagePortOhos() = default;
    ~WebMessagePortOhos() = default;

    void Close() override;
    void PostMessage(std::string& data) override;
    void SetWebMessageCallback(std::function<void(const std::string&)>&& callback) override;
    void SetPortHandle(std::string& handle) override;
    std::string GetPortHandle() override;

private:
    WeakPtr<WebDelegate> webDelegate_;
    std::string handle_;
};

class ConsoleLogOhos : public WebConsoleLog {
    DECLARE_ACE_TYPE(ConsoleLogOhos, WebConsoleLog)

public:
    explicit ConsoleLogOhos(std::shared_ptr<OHOS::NWeb::NWebConsoleLog> message) : message_(message) {}

    int GetLineNumber() override;

    std::string GetLog() override;

    int GetLogLevel() override;

    std::string GetSourceId() override;

private:
    std::shared_ptr<OHOS::NWeb::NWebConsoleLog> message_;
};

class ResultOhos : public Result {
    DECLARE_ACE_TYPE(ResultOhos, Result)

public:
    explicit ResultOhos(std::shared_ptr<OHOS::NWeb::NWebJSDialogResult> result) : result_(result) {}

    void Confirm() override;
    void Confirm(const std::string& message) override;
    void Cancel() override;

private:
    std::shared_ptr<OHOS::NWeb::NWebJSDialogResult> result_;
};

class FullScreenExitHandlerOhos : public FullScreenExitHandler {
    DECLARE_ACE_TYPE(FullScreenExitHandlerOhos, FullScreenExitHandler)

public:
    FullScreenExitHandlerOhos(std::shared_ptr<OHOS::NWeb::NWebFullScreenExitHandler> handler,
        WeakPtr<WebDelegate> webDelegate) : handler_(handler), webDelegate_(webDelegate) {}
    void ExitFullScreen() override;
private:
    std::shared_ptr<OHOS::NWeb::NWebFullScreenExitHandler> handler_;
    WeakPtr<WebDelegate> webDelegate_;
};

class WebCustomKeyboardHandlerOhos : public WebCustomKeyboardHandler {
    DECLARE_ACE_TYPE(WebCustomKeyboardHandlerOhos, WebCustomKeyboardHandler)

public:
    explicit WebCustomKeyboardHandlerOhos(std::shared_ptr<OHOS::NWeb::NWebCustomKeyboardHandler> keyboardHandler) :
    keyboardHandler_(keyboardHandler) {}

    void InsertText(const std::string &text) override
    {
        if (keyboardHandler_) {
            keyboardHandler_->InsertText(text);
        }
    }

    void DeleteForward(int32_t length) override
    {
        if (keyboardHandler_) {
            keyboardHandler_->DeleteForward(length);
        }
    }

    void DeleteBackward(int32_t length) override
    {
        if (keyboardHandler_) {
            keyboardHandler_->DeleteBackward(length);
        }
    }

    void SendFunctionKey(int32_t key) override
    {
        if (keyboardHandler_) {
            keyboardHandler_->SendFunctionKey(key);
        }
    }

    void Close() override
    {
        if (keyboardHandler_) {
            keyboardHandler_->Close();
        }
    }

private:
    std::shared_ptr<OHOS::NWeb::NWebCustomKeyboardHandler> keyboardHandler_;
};

class AuthResultOhos : public AuthResult {
    DECLARE_ACE_TYPE(AuthResultOhos, AuthResult)

public:
    explicit AuthResultOhos(std::shared_ptr<OHOS::NWeb::NWebJSHttpAuthResult> result) : result_(result) {}

    bool Confirm(std::string& userName, std::string& pwd) override;
    bool IsHttpAuthInfoSaved() override;
    void Cancel() override;

private:
    std::shared_ptr<OHOS::NWeb::NWebJSHttpAuthResult> result_;
};

class SslErrorResultOhos : public SslErrorResult {
    DECLARE_ACE_TYPE(SslErrorResultOhos, SslErrorResult)

public:
    explicit SslErrorResultOhos(std::shared_ptr<OHOS::NWeb::NWebJSSslErrorResult> result) : result_(result) {}

    void HandleConfirm() override;
    void HandleCancel() override;

private:
    std::shared_ptr<OHOS::NWeb::NWebJSSslErrorResult> result_;
};

class AllSslErrorResultOhos : public AllSslErrorResult {
    DECLARE_ACE_TYPE(AllSslErrorResultOhos, AllSslErrorResult)

public:
    explicit AllSslErrorResultOhos(std::shared_ptr<OHOS::NWeb::NWebJSAllSslErrorResult> result) : result_(result) {}

    void HandleConfirm() override;
    void HandleCancel(bool abortLoading) override;

private:
    std::shared_ptr<OHOS::NWeb::NWebJSAllSslErrorResult> result_;
};

class SslSelectCertResultOhos : public SslSelectCertResult {
    DECLARE_ACE_TYPE(SslSelectCertResultOhos, SslSelectCertResult)

public:
    explicit SslSelectCertResultOhos(std::shared_ptr<OHOS::NWeb::NWebJSSslSelectCertResult> result)
        : result_(result) {}

    void HandleConfirm(const std::string& privateKeyFile, const std::string& certChainFile) override;

    void HandleCancel() override;

    void HandleIgnore() override;
private:
    std::shared_ptr<OHOS::NWeb::NWebJSSslSelectCertResult> result_;
};

class FileSelectorParamOhos : public WebFileSelectorParam {
    DECLARE_ACE_TYPE(FileSelectorParamOhos, WebFileSelectorParam)

public:
    explicit FileSelectorParamOhos(std::shared_ptr<OHOS::NWeb::NWebFileSelectorParams> param) : param_(param) {}

    std::string GetTitle() override;
    int GetMode() override;
    std::string GetDefaultFileName() override;
    std::vector<std::string> GetAcceptType() override;
    bool IsCapture() override;
    std::vector<std::string> GetMimeType() override;

private:
    std::shared_ptr<OHOS::NWeb::NWebFileSelectorParams> param_;
};

class FileSelectorResultOhos : public FileSelectorResult {
    DECLARE_ACE_TYPE(FileSelectorResultOhos, FileSelectorResult)

public:
    FileSelectorResultOhos(
        std::shared_ptr<OHOS::NWeb::NWebStringVectorValueCallback> callback, const WeakPtr<WebDelegate>& delegate)
        : callback_(callback), delegate_(delegate)
    {}

    void HandleFileList(std::vector<std::string>& result) override;

private:
    std::shared_ptr<OHOS::NWeb::NWebStringVectorValueCallback> callback_;
    WeakPtr<WebDelegate> delegate_;
};

class ContextMenuParamOhos : public WebContextMenuParam {
    DECLARE_ACE_TYPE(ContextMenuParamOhos, WebContextMenuParam)

public:
    explicit ContextMenuParamOhos(std::shared_ptr<OHOS::NWeb::NWebContextMenuParams> param) : param_(param) {}

    int32_t GetXCoord() const override;
    int32_t GetYCoord() const override;
    std::string GetLinkUrl() const override;
    std::string GetUnfilteredLinkUrl() const override;
    std::string GetSourceUrl() const override;
    bool HasImageContents() const override;
    bool IsEditable() const override;
    int GetEditStateFlags() const override;
    int GetSourceType() const override;
    int GetMediaType() const override;
    int GetInputFieldType() const override;
    std::string GetSelectionText() const override;
    void GetImageRect(int32_t& x, int32_t& y, int32_t& width, int32_t& height) const override;
    bool IsAILink() const override;

private:
    std::shared_ptr<OHOS::NWeb::NWebContextMenuParams> param_;
};

class ContextMenuResultOhos : public ContextMenuResult {
    DECLARE_ACE_TYPE(ContextMenuResultOhos, ContextMenuResult)

public:
    explicit ContextMenuResultOhos(std::shared_ptr<OHOS::NWeb::NWebContextMenuCallback> callback)
        : callback_(callback) {}

    void Cancel() const override;
    void CopyImage() const override;
    void Copy() const override;
    void Paste() const override;
    void Cut() const override;
    void SelectAll() const override;
    void Undo() const override;
    void Redo() const override;
    void PasteAndMatchStyle() const override;

private:
    std::shared_ptr<OHOS::NWeb::NWebContextMenuCallback> callback_;
};

class WebGeolocationOhos : public WebGeolocation {
    DECLARE_ACE_TYPE(WebGeolocationOhos, WebGeolocation)

public:
    WebGeolocationOhos(
        const std::shared_ptr<OHOS::NWeb::NWebGeolocationCallbackInterface>&
            callback, bool incognito)
        : geolocationCallback_(callback), incognito_(incognito) {}

    void Invoke(const std::string& origin, const bool& allow, const bool& retain) override;

private:
    std::shared_ptr<OHOS::NWeb::NWebGeolocationCallbackInterface> geolocationCallback_;
    bool incognito_ = false;
};

class WebPermissionRequestOhos : public WebPermissionRequest {
    DECLARE_ACE_TYPE(WebPermissionRequestOhos, WebPermissionRequest)

public:
    explicit WebPermissionRequestOhos(const std::shared_ptr<OHOS::NWeb::NWebAccessRequest>& request)
        : request_(request) {}

    void Deny() const override;

    std::string GetOrigin() const override;

    std::vector<std::string> GetResources() const override;

    void Grant(std::vector<std::string>& resources) const override;

private:
    std::shared_ptr<OHOS::NWeb::NWebAccessRequest> request_;
};

class NWebScreenCaptureConfigImpl : public OHOS::NWeb::NWebScreenCaptureConfig {
public:
    NWebScreenCaptureConfigImpl() = default;
    ~NWebScreenCaptureConfigImpl() = default;

    int32_t GetMode() override
    {
        return mode_;
    }

    void SetMode(int32_t mode)
    {
        mode_ = mode;
    }

    int32_t GetSourceId() override
    {
        return source_id_;
    }

    void SetSourceId(int32_t source_id)
    {
        source_id_ = source_id;
    }

private:
    int32_t mode_ = 0;
    int32_t source_id_ = -1;
};

class WebScreenCaptureRequestOhos : public WebScreenCaptureRequest {
    DECLARE_ACE_TYPE(WebScreenCaptureRequestOhos, WebScreenCaptureRequest)

public:
    explicit WebScreenCaptureRequestOhos(const std::shared_ptr<OHOS::NWeb::NWebScreenCaptureAccessRequest>& request)
        : request_(request) {
        config_ = std::make_shared<NWebScreenCaptureConfigImpl>();
    }

    void Deny() const override;

    std::string GetOrigin() const override;

    void SetCaptureMode(int32_t mode) override;

    void SetSourceId(int32_t sourceId) override;

    void Grant() const override;

private:
    std::shared_ptr<OHOS::NWeb::NWebScreenCaptureAccessRequest> request_;

    std::shared_ptr<NWebScreenCaptureConfigImpl> config_;
};

class WebWindowNewHandlerOhos : public WebWindowNewHandler {
    DECLARE_ACE_TYPE(WebWindowNewHandlerOhos, WebWindowNewHandler)

public:
    WebWindowNewHandlerOhos(const std::shared_ptr<OHOS::NWeb::NWebControllerHandler>& handler, int32_t parentNWebId)
        : handler_(handler), parentNWebId_(parentNWebId) {}

    void SetWebController(int32_t id) override;

    bool IsFrist() const override;

    int32_t GetId() const override;

    int32_t GetParentNWebId() const override;

private:
    std::shared_ptr<OHOS::NWeb::NWebControllerHandler> handler_;
    int32_t parentNWebId_ = -1;
};

class WebAppLinkCallbackOhos : public WebAppLinkCallback {
    DECLARE_ACE_TYPE(WebAppLinkCallbackOhos, WebAppLinkCallback)
public:
    explicit WebAppLinkCallbackOhos(const std::shared_ptr<OHOS::NWeb::NWebAppLinkCallback>& callback)
        : callback_(callback) {}

    void ContinueLoad() override
    {
        if (callback_) {
            callback_->ContinueLoad();
        }
    }

    void CancelLoad() override
    {
        if (callback_) {
            callback_->CancelLoad();
        }
    }

private:
    std::shared_ptr<OHOS::NWeb::NWebAppLinkCallback> callback_;
};

class DataResubmittedOhos : public DataResubmitted {
    DECLARE_ACE_TYPE(DataResubmittedOhos, DataResubmitted)

public:
    explicit DataResubmittedOhos(std::shared_ptr<OHOS::NWeb::NWebDataResubmissionCallback> handler)
        : handler_(handler) {}
    void Resend() override;
    void Cancel() override;

private:
    std::shared_ptr<OHOS::NWeb::NWebDataResubmissionCallback> handler_;
};

class FaviconReceivedOhos : public WebFaviconReceived {
    DECLARE_ACE_TYPE(FaviconReceivedOhos, WebFaviconReceived)

public:
    FaviconReceivedOhos(
        const void* data,
        size_t width,
        size_t height,
        OHOS::NWeb::ImageColorType colorType,
        OHOS::NWeb::ImageAlphaType alphaType)
        : data_(data), width_(width), height_(height), colorType_(colorType), alphaType_(alphaType)  {}
    const void* GetData() override;
    size_t GetWidth() override;
    size_t GetHeight() override;
    int GetColorType() override;
    int GetAlphaType() override;

private:
    const void* data_ = nullptr;
    size_t width_ = 0;
    size_t height_ = 0;
    OHOS::NWeb::ImageColorType colorType_ = OHOS::NWeb::ImageColorType::COLOR_TYPE_UNKNOWN;
    OHOS::NWeb::ImageAlphaType alphaType_ = OHOS::NWeb::ImageAlphaType::ALPHA_TYPE_UNKNOWN;
};

class WebSurfaceCallback : public OHOS::SurfaceDelegate::ISurfaceCallback {
public:
    explicit WebSurfaceCallback(const WeakPtr<WebDelegate>& delegate) : delegate_(delegate) {}
    ~WebSurfaceCallback() = default;

    void OnSurfaceCreated(const OHOS::sptr<OHOS::Surface>& surface) override;
    void OnSurfaceChanged(const OHOS::sptr<OHOS::Surface>& surface, int32_t width, int32_t height) override;
    void OnSurfaceDestroyed() override;
private:
    WeakPtr<WebDelegate> delegate_;

};

enum class DragAction {
    DRAG_START = 0,
    DRAG_ENTER,
    DRAG_LEAVE,
    DRAG_OVER,
    DRAG_DROP,
    DRAG_END,
    DRAG_CANCEL,
};

namespace NG {
class WebPattern;
}; // namespace NG

class RenderWeb;

class NWebDragEventImpl : public OHOS::NWeb::NWebDragEvent {
public:
    NWebDragEventImpl(double x, double y, NWeb::DragAction action) : x_(x), y_(y), action_(action) {}
    ~NWebDragEventImpl() = default;

    double GetX() override
    {
        return x_;
    }

    double GetY() override
    {
        return y_;
    }

    NWeb::DragAction GetAction() override
    {
        return action_;
    }

private:
    double x_ = 0.0;
    double y_ = 0.0;
    NWeb::DragAction action_ = NWeb::DragAction::DRAG_START;
};

class NWebTouchPointInfoImpl : public OHOS::NWeb::NWebTouchPointInfo {
public:
    NWebTouchPointInfoImpl(int id, double x, double y) : id_(id), x_(x), y_(y) {}
    ~NWebTouchPointInfoImpl() = default;

    int GetId() override
    {
        return id_;
    }

    double GetX() override
    {
        return x_;
    }

    double GetY() override
    {
        return y_;
    }

private:
    int id_ = 0;
    double x_ = 0;
    double y_ = 0;
};

class NWebScreenLockCallbackImpl : public OHOS::NWeb::NWebScreenLockCallback {
public:
    explicit NWebScreenLockCallbackImpl(const WeakPtr<PipelineBase>& context);
    ~NWebScreenLockCallbackImpl() = default;

    void Handle(bool key) override;

private:
    WeakPtr<PipelineBase> context_ = nullptr;
};

class WebDelegateObserver : public virtual AceType {
DECLARE_ACE_TYPE(WebDelegateObserver, AceType);
public:
    WebDelegateObserver(const RefPtr<WebDelegate>& delegate, WeakPtr<PipelineBase> context)
        : delegate_(delegate), context_(context)
    {}
    ~WebDelegateObserver();
    void NotifyDestory();
    void OnAttachContext(const RefPtr<NG::PipelineContext> &context);
    void OnDetachContext();

private:
    RefPtr<WebDelegate> delegate_;
    WeakPtr<PipelineBase> context_;
};

class GestureEventResultOhos : public GestureEventResult {
    DECLARE_ACE_TYPE(GestureEventResultOhos, GestureEventResult);

public:
    explicit GestureEventResultOhos(std::shared_ptr<OHOS::NWeb::NWebGestureEventResult> result)
        : result_(result) {}

    void SetGestureEventResult(bool result) override;
    void SetGestureEventResult(bool result, bool stopPropagation) override;
    bool HasSendTask() { return sendTask_; }
    void SetSendTask() { sendTask_ = true; }
    bool GetEventResult() { return eventResult_; }

private:
    std::shared_ptr<OHOS::NWeb::NWebGestureEventResult> result_;
    bool sendTask_ = false;
    bool eventResult_ = false;
};

class WebAvoidAreaChangedListener : public OHOS::Rosen::IAvoidAreaChangedListener {
public:
    explicit WebAvoidAreaChangedListener(WeakPtr<WebDelegate> webDelegate, WeakPtr<PipelineBase> context)
        : webDelegate_(webDelegate), context_(context) {}
    ~WebAvoidAreaChangedListener() = default;

    void OnAvoidAreaChanged(const OHOS::Rosen::AvoidArea avoidArea, OHOS::Rosen::AvoidAreaType type,
        const sptr<OHOS::Rosen::OccupiedAreaChangeInfo>& info) override;
private:
    WeakPtr<WebDelegate> webDelegate_;
    WeakPtr<PipelineBase> context_;
};

class WebWindowFocusChangedListener : public Rosen::IWindowLifeCycle {
public:
    explicit WebWindowFocusChangedListener(WeakPtr<WebDelegate> webDelegate) : webDelegate_(webDelegate) {}
    ~WebWindowFocusChangedListener() = default;

    void AfterFocused() override;;
private:
    WeakPtr<WebDelegate> webDelegate_;
};

enum class ScriptItemType {
    DOCUMENT_START = 0,
    DOCUMENT_END = 1,
    DOCUMENT_HEAD_READY
};

class NWebSystemConfigurationImpl : public OHOS::NWeb::NWebSystemConfiguration {
public:
    explicit NWebSystemConfigurationImpl(uint8_t flags) : theme_flags_(flags) {}
    ~NWebSystemConfigurationImpl() = default;

    uint8_t GetThemeFlags() override
    {
        return theme_flags_;
    }

private:
    uint8_t theme_flags_ = static_cast<uint8_t>(NWeb::SystemThemeFlags::NONE);
};

class NWebKeyboardEventImpl : public OHOS::NWeb::NWebKeyboardEvent {
public:
    NWebKeyboardEventImpl(
        int32_t keyCode, int32_t action, int32_t unicode, bool enableCapsLock,
        std::vector<int32_t> pressedCodes)
        : keyCode_(keyCode), action_(action), unicode_(unicode), enableCapsLock_(enableCapsLock),
        pressedCodes_(pressedCodes) {}
    ~NWebKeyboardEventImpl() = default;

    int32_t GetKeyCode() override
    {
        return keyCode_;
    }

    int32_t GetAction() override
    {
        return action_;
    }

    int32_t GetUnicode() override
    {
        return unicode_;
    }

    bool IsEnableCapsLock() override
    {
        return enableCapsLock_;
    }

    std::vector<int32_t> GetPressKeyCodes() override
    {
        return pressedCodes_;
    }

private:
    int32_t keyCode_ = 0;
    int32_t action_ = 0;
    uint32_t unicode_ = 0;
    bool enableCapsLock_ = false;
    std::vector<int32_t> pressedCodes_ {};
};

class NWebMouseEventImpl : public OHOS::NWeb::NWebMouseEvent {
public:
    NWebMouseEventImpl(int32_t x, int32_t y, int32_t rawX, int32_t rawY,
        int32_t buttton, int32_t action,
        int32_t clickNum, std::vector<int32_t> pressedCodes)
        : x_(x), y_(y), buttton_(buttton), action_(action),
        clickNum_(clickNum), pressedCodes_(pressedCodes) {}
    ~NWebMouseEventImpl() = default;

    int32_t GetX() override
    {
        return x_;
    }

    int32_t GetY() override
    {
        return y_;
    }

    int32_t GetButton() override
    {
        return buttton_;
    }

    int32_t GetAction() override
    {
        return action_;
    }

    int32_t GetClickNum() override
    {
        return clickNum_;
    }

    std::vector<int32_t> GetPressKeyCodes() override
    {
        return pressedCodes_;
    }

    int32_t GetRawX() override
    {
        return raw_x_;
    }

    int32_t GetRawY() override
    {
        return raw_y_;
    }

private:
    int32_t x_ = 0;
    int32_t y_ = 0;
    int32_t raw_x_ = 0;
    int32_t raw_y_ = 0;
    int32_t buttton_ = 0;
    int32_t action_ = 0;
    int32_t clickNum_ = 0;
    std::vector<int32_t> pressedCodes_ {};
};

class WebDelegate : public WebResource {
    DECLARE_ACE_TYPE(WebDelegate, WebResource);

public:
    using CreatedCallback = std::function<void()>;
    using ReleasedCallback = std::function<void(bool)>;
    using EventCallback = std::function<void(const std::string&)>;
    using EventCallbackV2 = std::function<void(const std::shared_ptr<BaseEventInfo>&)>;
    enum class State : char {
        WAITINGFORSIZE,
        CREATING,
        CREATED,
        CREATEFAILED,
        RELEASED,
    };

    // for webcontoller, the enum is same as web_webview and core side
    enum class JavaScriptObjIdErrorCode : int32_t { WEBCONTROLLERERROR = -2, WEBVIEWCONTROLLERERROR = -1, END = 0 };

    WebDelegate() = delete;
    ~WebDelegate() override;
    WebDelegate(const WeakPtr<PipelineBase>& context, ErrorCallback&& onError, const std::string& type)
        : WebResource(type, context, std::move(onError)), instanceId_(Container::CurrentId())
    {}
    WebDelegate(const WeakPtr<PipelineBase>& context, ErrorCallback&& onError, const std::string& type, int32_t id)
        : WebResource(type, context, std::move(onError)), instanceId_(id)
    {}

    void UnRegisterScreenLockFunction();

    void SetObserver(const RefPtr<WebDelegateObserver>& observer)
    {
        observer_ = observer;
    };
    void SetRenderWeb(const WeakPtr<RenderWeb>& renderWeb);

    void CreatePlatformResource(const Size& size, const Offset& position, const WeakPtr<PipelineContext>& context);
    void CreatePluginResource(const Size& size, const Offset& position, const WeakPtr<PipelineContext>& context);
    void AddCreatedCallback(const CreatedCallback& createdCallback);
    void RemoveCreatedCallback();
    void AddReleasedCallback(const ReleasedCallback& releasedCallback);
    void SetComponent(const RefPtr<WebComponent>& component);
    void RemoveReleasedCallback();
    void Reload();
    void UpdateUrl(const std::string& url);
#ifdef OHOS_STANDARD_SYSTEM
    void InitOHOSWeb(const RefPtr<PipelineBase>& context, const RefPtr<NG::RenderSurface>& surface);
    void InitOHOSWeb(const WeakPtr<PipelineBase>& context);
    bool PrepareInitOHOSWeb(const WeakPtr<PipelineBase>& context);
    void InitWebViewWithWindow();
    void ShowWebView();
    void HideWebView();
    void OnRenderToBackground();
    void OnRenderToForeground();
    void SetSurfaceDensity(const double& density);
    void Resize(const double& width, const double& height, bool isKeyboard = false);
    int32_t GetRosenWindowId()
    {
        return rosenWindowId_;
    }
    void SetKeepScreenOn(bool key);
    void UpdateUserAgent(const std::string& userAgent);
    void UpdateBackgroundColor(const int backgroundColor);
    void UpdateInitialScale(float scale);
    void UpdateLayoutMode(WebLayoutMode mode);
    void UpdateJavaScriptEnabled(const bool& isJsEnabled);
    void UpdateAllowFileAccess(const bool& isFileAccessEnabled);
    void UpdateBlockNetworkImage(const bool& onLineImageAccessEnabled);
    void UpdateLoadsImagesAutomatically(const bool& isImageAccessEnabled);
    void UpdateMixedContentMode(const MixedModeContent& mixedMode);
    void UpdateSupportZoom(const bool& isZoomAccessEnabled);
    void UpdateDomStorageEnabled(const bool& isDomStorageAccessEnabled);
    void UpdateGeolocationEnabled(const bool& isGeolocationAccessEnabled);
    void UpdateCacheMode(const WebCacheMode& mode);
    std::shared_ptr<OHOS::NWeb::NWeb> GetNweb();
    bool GetForceDarkMode();
    void OnConfigurationUpdated(const OHOS::AppExecFwk::Configuration& configuration);
    void UpdateDarkMode(const WebDarkMode& mode);
    void UpdateDarkModeAuto(RefPtr<WebDelegate> delegate, std::shared_ptr<OHOS::NWeb::NWebPreference> setting);
    void UpdateForceDarkAccess(const bool& access);
    void UpdateAudioResumeInterval(const int32_t& resumeInterval);
    void UpdateAudioExclusive(const bool& audioExclusive);
    void UpdateAudioSessionType(const WebAudioSessionType& audioSessionType);
    void UpdateOverviewModeEnabled(const bool& isOverviewModeAccessEnabled);
    void UpdateFileFromUrlEnabled(const bool& isFileFromUrlAccessEnabled);
    void UpdateDatabaseEnabled(const bool& isDatabaseAccessEnabled);
    void UpdateTextZoomRatio(const int32_t& textZoomRatioNum);
    void UpdateWebDebuggingAccess(bool isWebDebuggingAccessEnabled);
    void UpdateWebDebuggingAccessAndPort(bool enabled, int32_t port);
    void UpdatePinchSmoothModeEnabled(bool isPinchSmoothModeEnabled);
    void UpdateMediaPlayGestureAccess(bool isNeedGestureAccess);
    void UpdateMultiWindowAccess(bool isMultiWindowAccessEnabled);
    void UpdateAllowWindowOpenMethod(bool isAllowWindowOpenMethod);
    void UpdateWebCursiveFont(const std::string& cursiveFontFamily);
    void UpdateWebFantasyFont(const std::string& fantasyFontFamily);
    void UpdateWebFixedFont(const std::string& fixedFontFamily);
    void UpdateWebSansSerifFont(const std::string& sansSerifFontFamily);
    void UpdateWebSerifFont(const std::string& serifFontFamily);
    void UpdateWebStandardFont(const std::string& standardFontFamily);
    void UpdateDefaultFixedFontSize(int32_t size);
    void UpdateDefaultFontSize(int32_t defaultFontSize);
    void UpdateDefaultTextEncodingFormat(const std::string& textEncodingFormat);
    void UpdateMinFontSize(int32_t minFontSize);
    void UpdateMinLogicalFontSize(int32_t minLogicalFontSize);
    void UpdateBlockNetwork(bool isNetworkBlocked);
    void UpdateHorizontalScrollBarAccess(bool isHorizontalScrollBarAccessEnabled);
    void UpdateVerticalScrollBarAccess(bool isVerticalScrollBarAccessEnabled);
    void UpdateOverlayScrollbarEnabled(bool isEnabled);
    void UpdateScrollBarColor(const std::string& colorValue);
    void UpdateOverScrollMode(const int32_t overscrollModeValue);
    void UpdateBlurOnKeyboardHideMode(const int32_t isBlurOnKeyboardHideEnable);
    void UpdateNativeEmbedModeEnabled(bool isEmbedModeEnabled);
    void UpdateIntrinsicSizeEnabled(bool isIntrinsicSizeEnabled);
    void UpdateCssDisplayChangeEnabled(bool isCssDisplayChangeEnabled);
    void UpdateBypassVsyncCondition(const WebBypassVsyncCondition& condition);
    void UpdateGestureFocusMode(const GestureFocusMode& mode);
    void UpdateNativeEmbedRuleTag(const std::string& tag);
    void UpdateNativeEmbedRuleType(const std::string& type);
    void UpdateCopyOptionMode(const int32_t copyOptionModeValue);
    void UpdateTextAutosizing(bool isTextAutosizing);
    void UpdateMetaViewport(bool isMetaViewportEnabled);
    void UpdateNativeVideoPlayerConfig(bool enable, bool shouldOverlay);
    void UpdateEnableFollowSystemFontWeight(bool enableFollowSystemFontWeight);
    void LoadUrl();
    void CreateWebMessagePorts(std::vector<RefPtr<WebMessagePort>>& ports);
    void PostWebMessage(std::string& message, std::vector<RefPtr<WebMessagePort>>& ports, std::string& uri);
    void ClosePort(std::string& handle);
    void PostPortMessage(std::string& handle, std::string& data);
    void SetPortMessageCallback(std::string& handle, std::function<void(const std::string&)>&& callback);
    void HandleTouchDown(const int32_t& id, const double& x, const double& y, bool from_overlay = false);
    void HandleTouchUp(const int32_t& id, const double& x, const double& y, bool from_overlay = false);
    void HandleTouchMove(const int32_t& id, const double& x, const double& y, bool from_overlay = false);
    void HandleTouchMove(const std::vector<std::shared_ptr<OHOS::NWeb::NWebTouchPointInfo>> &touch_point_infos,
                         bool fromOverlay = false);
    void HandleTouchCancel();
    void HandleTouchpadFlingEvent(const double& x, const double& y, const double& vx, const double& vy);
    void WebHandleTouchpadFlingEvent(const double& x, const double& y,
        const double& vx, const double& vy, const std::vector<int32_t>& pressedCodes);
    void HandleAxisEvent(const double& x, const double& y, const double& deltaX, const double& deltaY);
    void WebHandleAxisEvent(const double& x, const double& y,
        const double& deltaX, const double& deltaY, const std::vector<int32_t>& pressedCodes, const int32_t source);
    bool OnKeyEvent(int32_t keyCode, int32_t keyAction);
    bool WebOnKeyEvent(int32_t keyCode, int32_t keyAction, const std::vector<int32_t>& pressedCodes);
    bool SendKeyboardEvent(const std::shared_ptr<OHOS::NWeb::NWebKeyboardEvent>& keyboardEvent);
    void OnMouseEvent(int32_t x, int32_t y, const MouseButton button, const MouseAction action, int count);
    void WebOnMouseEvent(const std::shared_ptr<OHOS::NWeb::NWebMouseEvent>& mouseEvent);
    void OnFocus(const OHOS::NWeb::FocusReason& reason = OHOS::NWeb::FocusReason::EVENT_REQUEST);
    bool NeedSoftKeyboard();
    void OnBlur();
    void OnPermissionRequestPrompt(const std::shared_ptr<OHOS::NWeb::NWebAccessRequest>& request);
    void OnScreenCaptureRequest(const std::shared_ptr<OHOS::NWeb::NWebScreenCaptureAccessRequest>& request);
    void UpdateClippedSelectionBounds(int32_t x, int32_t y, int32_t w, int32_t h);
    bool RunQuickMenu(std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params,
        std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback);
    void OnQuickMenuDismissed();
    void HideHandleAndQuickMenuIfNecessary(bool hide);
    void ChangeVisibilityOfQuickMenu();
    bool ChangeVisibilityOfQuickMenuV2();
    void OnTouchSelectionChanged(std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertHandle,
        std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> startSelectionHandle,
        std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endSelectionHandle);
    void HandleDragEvent(int32_t x, int32_t y, const DragAction& dragAction);
    RefPtr<PixelMap> GetDragPixelMap();
    std::string GetUrl();
    void UpdateLocale();
    void SetDrawRect(int32_t x, int32_t y, int32_t width, int32_t height);
    void ReleaseResizeHold();
    bool GetPendingSizeStatus();
    void OnInactive();
    void OnActive();
    void GestureBackBlur();
    void OnWebviewHide();
    void OnWebviewShow();
    bool OnCursorChange(const OHOS::NWeb::CursorType& type, std::shared_ptr<OHOS::NWeb::NWebCursorInfo> info);
    void OnSelectPopupMenu(
        std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuParam> params,
        std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuCallback> callback);
    void SetShouldFrameSubmissionBeforeDraw(bool should);
    void SetBackgroundColor(int32_t backgroundColor)
    {
        backgroundColor_ = backgroundColor;
    }
    void NotifyMemoryLevel(int32_t level);
    void SetAudioMuted(bool muted);
    void SetRichtextIdentifier(std::optional<std::string>& richtextData)
    {
        richtextData_ = richtextData;
    }
    void HandleAccessibilityHoverEvent(
        const NG::PointF& point, SourceType source, NG::AccessibilityHoverEventType eventType, TimeStamp time);
    void NotifyAutoFillViewData(const std::string& jsonStr);
    void AutofillCancel(const std::string& fillContent);
    bool HandleAutoFillEvent(const std::shared_ptr<OHOS::NWeb::NWebMessage>& viewDataJson);
    void UpdateOptimizeParserBudgetEnabled(const bool enable);
#endif
    void OnErrorReceive(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request,
        std::shared_ptr<OHOS::NWeb::NWebUrlResourceError> error);
    void OnHttpErrorReceive(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request,
        std::shared_ptr<OHOS::NWeb::NWebUrlResourceResponse> response);
    RefPtr<WebResponse> OnInterceptRequest(const std::shared_ptr<BaseEventInfo>& info);
    bool IsEmptyOnInterceptRequest();
    void ReportDynamicFrameLossEvent(const std::string& sceneId, bool isStart);
    void RecordWebEvent(Recorder::EventType eventType, const std::string& param) const;
    void OnPageStarted(const std::string& param);
    void OnPageFinished(const std::string& param);
    void OnProgressChanged(int param);
    void OnReceivedTitle(const std::string& title, bool isRealTitle = false);
    void ExitFullScreen();
    void OnFullScreenExit();
    void OnGeolocationPermissionsHidePrompt();
    void OnGeolocationPermissionsShowPrompt(
        const std::string& origin, const std::shared_ptr<OHOS::NWeb::NWebGeolocationCallbackInterface>& callback);
    void OnCompleteSwapWithNewSize();
    void OnResizeNotWork();
    void OnDateTimeChooserPopup(
        std::shared_ptr<OHOS::NWeb::NWebDateTimeChooser> chooser,
        const std::vector<std::shared_ptr<OHOS::NWeb::NWebDateTimeSuggestion>>& suggestions,
        std::shared_ptr<OHOS::NWeb::NWebDateTimeChooserCallback> callback);
    void OnDateTimeChooserClose();
    void OnRequestFocus();
    bool OnCommonDialog(const std::shared_ptr<BaseEventInfo>& info, DialogEventType dialogEventType);
    bool OnHttpAuthRequest(const std::shared_ptr<BaseEventInfo>& info);
    bool OnSslErrorRequest(const std::shared_ptr<BaseEventInfo>& info);
    bool OnAllSslErrorRequest(const std::shared_ptr<BaseEventInfo>& info);
    bool OnSslSelectCertRequest(const std::shared_ptr<BaseEventInfo>& info);
    void OnDownloadStart(const std::string& url, const std::string& userAgent, const std::string& contentDisposition,
        const std::string& mimetype, long contentLength);
    void OnAccessibilityEvent(int64_t accessibilityId, AccessibilityEventType eventType, const std::string& argument);
    void OnPageError(const std::string& param);
    void OnMessage(const std::string& param);
    void OnFullScreenEnter(std::shared_ptr<OHOS::NWeb::NWebFullScreenExitHandler> handler, int videoNaturalWidth,
        int videoNaturalHeight);
    bool OnConsoleLog(std::shared_ptr<OHOS::NWeb::NWebConsoleLog> message);
    void OnRouterPush(const std::string& param);
    void OnRenderExited(OHOS::NWeb::RenderExitReason reason);
    void OnRefreshAccessedHistory(const std::string& url, bool isRefreshed);
    bool OnFileSelectorShow(const std::shared_ptr<BaseEventInfo>& info);
    bool OnContextMenuShow(const std::shared_ptr<BaseEventInfo>& info);
    void OnContextMenuHide(const std::string& info);
    bool OnHandleInterceptUrlLoading(const std::string& url);
    bool OnHandleInterceptLoading(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request);
    void OnResourceLoad(const std::string& url);
    void OnScaleChange(float oldScaleFactor, float newScaleFactor);
    void OnScroll(double xOffset, double yOffset);
    bool LoadDataWithRichText();
    void OnSearchResultReceive(int activeMatchOrdinal, int numberOfMatches, bool isDoneCounting);
    bool OnDragAndDropData(const void* data, size_t len, int width, int height);
    bool OnDragAndDropDataUdmf(std::shared_ptr<OHOS::NWeb::NWebDragData> dragData);
    void OnTooltip(const std::string& tooltip);
    void OnPopupSize(int32_t x, int32_t y, int32_t width, int32_t height);
    void OnPopupShow(bool show);
    void OnShowAutofillPopup(const float offsetX, const float offsetY, const std::vector<std::string>& menu_items);
    void OnShowAutofillPopupV2(const float offsetX, const float offsetY, const float height, const float width,
        const std::vector<std::string>& menu_items);
    void SuggestionSelected(int32_t index);
    void OnHideAutofillPopup();
    std::shared_ptr<OHOS::NWeb::NWebDragData> GetOrCreateDragData();
    bool IsDragging();
    bool IsImageDrag();
    std::shared_ptr<OHOS::NWeb::NWebDragData> dragData_ = nullptr;
    std::string tempDir_;
    void UpdateDragCursor(NWeb::NWebDragData::DragOperation op)
    {
        op_ = op;
    }
    NWeb::NWebDragData::DragOperation GetDragAcceptableStatus()
    {
        return op_;
    }
    NWeb::NWebDragData::DragOperation op_ = NWeb::NWebDragData::DragOperation::DRAG_OPERATION_NONE;
    void OnWindowNew(const std::string& targetUrl, bool isAlert, bool isUserTrigger,
        const std::shared_ptr<OHOS::NWeb::NWebControllerHandler>& handler);
    void OnActivateContent();
    void OnWindowExit();
    void OnPageVisible(const std::string& url);
    void OnDataResubmitted(std::shared_ptr<OHOS::NWeb::NWebDataResubmissionCallback> handler);
    void OnNavigationEntryCommitted(std::shared_ptr<OHOS::NWeb::NWebLoadCommittedDetails> details);
    void OnFaviconReceived(const void* data, size_t width, size_t height, OHOS::NWeb::ImageColorType colorType,
        OHOS::NWeb::ImageAlphaType alphaType);
    void OnTouchIconUrl(const std::string& iconUrl, bool precomposed);
    void OnAudioStateChanged(bool audible);
    void OnFirstContentfulPaint(int64_t navigationStartTick, int64_t firstContentfulPaintMs);
    void OnFirstMeaningfulPaint(std::shared_ptr<OHOS::NWeb::NWebFirstMeaningfulPaintDetails> details);
    void OnLargestContentfulPaint(std::shared_ptr<OHOS::NWeb::NWebLargestContentfulPaintDetails> details);
    void OnSafeBrowsingCheckResult(int threat_type);
    void OnGetTouchHandleHotZone(std::shared_ptr<OHOS::NWeb::NWebTouchHandleHotZone> hotZone);
    void OnOverScroll(float xOffset, float yOffset);
    void OnOverScrollFlingVelocity(float xVelocity, float yVelocity, bool isFling);
    void OnScrollState(bool scrollState);
    void OnScrollStart(const float x, const float y);
    void EnableSecurityLayer(bool isNeedSecurityLayer);
    void OnRootLayerChanged(int width, int height);
    bool FilterScrollEvent(const float x, const float y, const float xVelocity, const float yVelocity);
    void OnNativeEmbedAllDestory();
    std::string GetSurfaceIdByHtmlElementId(const std::string& htmlElementId);
    std::string GetHtmlElementIdBySurfaceId(const std::string& surfaceId);
    int64_t GetWebAccessibilityIdBySurfaceId(const std::string& surfaceId);
    void OnNativeEmbedLifecycleChange(std::shared_ptr<NWeb::NWebNativeEmbedDataInfo> dataInfo);
    void OnNativeEmbedVisibilityChange(const std::string& embedId, bool visibility);
    void OnNativeEmbedGestureEvent(std::shared_ptr<NWeb::NWebNativeEmbedTouchEvent> event);
    void SetNGWebPattern(const RefPtr<NG::WebPattern>& webPattern);
    bool RequestFocus(OHOS::NWeb::NWebFocusSource source = OHOS::NWeb::NWebFocusSource::FOCUS_SOURCE_DEFAULT);
    bool IsCurrentFocus();
    void SetDrawSize(const Size& drawSize);
    void SetEnhanceSurfaceFlag(const bool& isEnhanceSurface);
    EGLConfig GLGetConfig(int version, EGLDisplay eglDisplay);
    void GLContextInit(void* window);
    sptr<OHOS::SurfaceDelegate> GetSurfaceDelegateClient();
    void SetBoundsOrResize(const Size& drawSize, const Offset& offset, bool isKeyboard = false);
    void ResizeVisibleViewport(const Size& visibleSize, bool isKeyboard = false);
    Offset GetWebRenderGlobalPos();
    bool InitWebSurfaceDelegate(const WeakPtr<PipelineBase>& context);
    int GetWebId();
    void JavaScriptOnDocumentStart();
    void JavaScriptOnDocumentEnd();
    void SetJavaScriptItems(const ScriptItems& scriptItems, const ScriptItemType& type);
    void JavaScriptOnDocumentStartByOrder();
    void JavaScriptOnDocumentEndByOrder();
    void JavaScriptOnHeadReadyByOrder();
    void SetJavaScriptItemsByOrder(const ScriptItems& scriptItems, const ScriptItemType& type,
        const ScriptItemsByOrder& scriptItemsByOrder);
    void SetTouchEventInfo(std::shared_ptr<OHOS::NWeb::NWebNativeEmbedTouchEvent> touchEvent,
        TouchEventInfo& touchEventInfo);
    bool GetIsSmoothDragResizeEnabled();
    void DragResize(const double& width, const double& height, const double& pre_height, const double& pre_width);
    void SetDragResizeStartFlag(bool isDragResizeStart);
    void SetDragResizePreSize(const double& pre_height, const double& pre_width);
    std::string SpanstringConvertHtml(const std::vector<uint8_t> &content);
    bool CloseImageOverlaySelection();
    void GetVisibleRectToWeb(int& visibleX, int& visibleY, int& visibleWidth, int& visibleHeight);
    void RestoreRenderFit();
    bool OnNestedScroll(float& x, float& y, float& xVelocity, float& yVelocity, bool& isAvailable);
#if defined(ENABLE_ROSEN_BACKEND)
    void SetSurface(const sptr<Surface>& surface);
    void SetPopupSurface(const RefPtr<NG::RenderSurface>& popupSurface);
    sptr<Surface> surface_ = nullptr;
    sptr<Surface> popupSurface_ = nullptr;
    RefPtr<NG::RosenRenderSurface> renderSurface_ = nullptr;
    RefPtr<NG::RosenRenderSurface> popupRenderSurface_ = nullptr;
#endif
#ifdef OHOS_STANDARD_SYSTEM
    void SetWebRendeGlobalPos(const Offset& pos)
    {
        offset_ = pos;
    }
    void SetBlurReason(const OHOS::NWeb::BlurReason& blurReason)
    {
        blurReason_ = blurReason;
    }
    void SetPopup(bool popup)
    {
        isPopup_ = popup;
    }
    void SetParentNWebId(int32_t parentNWebId)
    {
        parentNWebId_ = parentNWebId;
    }
#endif
    void SetToken();
    void SetRenderMode(RenderMode renderMode);
    void SetFitContentMode(WebLayoutMode layoutMode);
    void SetVirtualKeyBoardArg(int32_t width, int32_t height, double keyboard);
    bool ShouldVirtualKeyboardOverlay();
    void ScrollBy(float deltaX, float deltaY);
    void ScrollByRefScreen(float deltaX, float deltaY, float vx = 0, float vy = 0);
    bool ExecuteAction(int64_t accessibilityId, AceAction action,
        const std::map<std::string, std::string>& actionArguments);
    bool GetAccessibilityNodeRectById(
        int64_t accessibilityId, int32_t* width, int32_t* height, int32_t* offsetX, int32_t* offsetY);
    std::shared_ptr<OHOS::NWeb::NWebAccessibilityNodeInfo> GetFocusedAccessibilityNodeInfo(
        int64_t accessibilityId, bool isAccessibilityFocus);
    std::shared_ptr<OHOS::NWeb::NWebAccessibilityNodeInfo> GetAccessibilityNodeInfoById(int64_t accessibilityId);
    std::shared_ptr<OHOS::NWeb::NWebAccessibilityNodeInfo> GetAccessibilityNodeInfoByFocusMove(
        int64_t accessibilityId, int32_t direction);
    void SetAccessibilityState(bool state, bool isDelayed);
    void UpdateAccessibilityState(bool state);
    OHOS::NWeb::NWebPreference::CopyOptionMode GetCopyOptionMode() const;
    void OnIntelligentTrackingPreventionResult(
        const std::string& websiteHost, const std::string& trackerHost);
    bool OnHandleOverrideLoading(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request);
    void ScaleGestureChange(double scale, double centerX, double centerY);
    void ScaleGestureChangeV2(int type, double scale, double originScale, double centerX, double centerY);
    std::vector<int8_t> GetWordSelection(const std::string& text, int8_t offset);
    // Backward
    void Backward();
    bool AccessBackward();
    bool OnOpenAppLink(const std::string& url, std::shared_ptr<OHOS::NWeb::NWebAppLinkCallback> callback);

    void OnRenderProcessNotResponding(
        const std::string& jsStack, int pid, OHOS::NWeb::RenderProcessNotRespondingReason reason);
    void OnRenderProcessResponding();
    std::string GetSelectInfo() const;
    Offset GetPosition(const std::string& embedId);

    void OnOnlineRenderToForeground();
    void NotifyForNextTouchEvent();

    void OnViewportFitChange(OHOS::NWeb::ViewportFit viewportFit);
    void OnAreaChange(const OHOS::Ace::Rect& area);
    void OnAvoidAreaChanged(const OHOS::Rosen::AvoidArea avoidArea, OHOS::Rosen::AvoidAreaType type);
    std::string GetWebInfoType();
    void OnInterceptKeyboardAttach(
        const std::shared_ptr<OHOS::NWeb::NWebCustomKeyboardHandler> keyboardHandler,
        const std::map<std::string, std::string> &attributes, bool &useSystemKeyboard, int32_t &enterKeyType);

    void OnCustomKeyboardAttach();

    void OnCustomKeyboardClose();

    void CreateOverlay(void* data, size_t len, int width, int height, int offsetX, int offsetY, int rectWidth,
        int rectHeight, int pointX, int pointY);

    void OnOverlayStateChanged(int offsetX, int offsetY, int rectWidth, int rectHeight);

    void OnTextSelected();
    void OnDestroyImageAnalyzerOverlay();

    void OnAttachContext(const RefPtr<NG::PipelineContext> &context);
    void OnDetachContext();

    int32_t GetInstanceId() const
    {
        return instanceId_;
    }

    void OnAdsBlocked(const std::string& url, const std::vector<std::string>& adsBlocked);
    void SetSurfaceId(const std::string& surfaceId);

    void KeyboardReDispatch(const std::shared_ptr<OHOS::NWeb::NWebKeyEvent>& event, bool isUsed);

    void OnCursorUpdate(double x, double y, double width, double height);

    void CloseCustomKeyboard()
    {
        if (keyboardHandler_) {
            keyboardHandler_->Close();
        }
    }

    bool SetFocusByPosition(float x, float y);

    void StartVibraFeedback(const std::string& vibratorType);

    RefPtr<TaskExecutor> GetTaskExecutor() const
    {
        return taskExecutor_;
    }

    bool GetAccessibilityVisible(int64_t accessibilityId);

    void SetTransformHint(uint32_t rotation);

    void MaximizeResize();

    void ExecuteTypeScript(const std::string& jscode, const std::function<void(std::string)>&& callback);

    void RegisterNativeArkJSFunction(const std::string& objName,
        const std::vector<std::pair<std::string, NativeMethodCallback>>& methodList, bool isNeedRefresh);

    void UnRegisterNativeArkJSFunction(const std::string& objName);

    bool IsActivePolicyDisable();

    void UpdateWebMediaAVSessionEnabled(bool isEnabled);

    std::string GetCurrentLanguage();
    void RegisterNativeJavaScriptProxy(const std::string& obj, const std::vector<std::string>& method,
        std::vector<std::function<void(const std::vector<std::string>&)>> callbackImpl,
        bool isAync, const std::string& permission, bool isNeedRefresh);

    void RegisterWebWindowFocusChangedListener();

    void UnRegisterWebWindowFocusChangedListener();
    
    void OnDragAttach();

    bool IsNWebEx();

    void SetNativeInnerWeb(bool isInnerWeb);

    void ResetStateOfDataDetectorJS();
    void RunDataDetectorJS();
    void SetDataDetectorEnable(bool enable);
    void OnDataDetectorSelectText();
    void OnDataDetectorCopy(const std::vector<std::string>& recordMix);
    int GetLastHitTestResult();
    int GetHitTestResult();

    void RemoveSnapshotFrameNode(int removeDelayTime);

    void OnPip(int status, int delegate_id, int child_id, int frame_routing_id,  int width, int height);
    void SetPipNativeWindow(int delegate_id, int child_id, int frame_routing_id, void* window);
    void SendPipEvent(int delegate_id, int child_id, int frame_routing_id, int event);
    void SetIsFileSelectorShow(bool isFileSelectorShow) { isFileSelectorShow_ = isFileSelectorShow; }
    bool IsFileSelectorShow() { return isFileSelectorShow_; }


    bool ShowMagnifier();
    bool HideMagnifier();
    void UpdateSingleHandleVisible(bool isVisible);
    void SetTouchHandleExistState(bool touchHandleExist);
private:
    void InitWebEvent();
    void RegisterWebEvent();
    void ReleasePlatformResource();
    void Stop();
    void UnregisterEvent();
    std::string GetUrlStringParam(const std::string& param, const std::string& name) const;
    void CallWebRouterBack();
    void CallPopPageSuccessPageUrl(const std::string& url);
    void CallIsPagePathInvalid(const bool& isPageInvalid);

    void BindRouterBackMethod();
    void BindPopPageSuccessMethod();
    void BindIsPagePathInvalidMethod();
    void TextBlurReportByFocusEvent(int64_t accessibilityId);
    void WebComponentClickReport(int64_t accessibilityId);
    void TextBlurReportByBlurEvent(int64_t accessibilityId);
    void AccessibilityReleasePageEvent();
    void AccessibilitySendPageChange();

#ifdef OHOS_STANDARD_SYSTEM
    sptr<OHOS::Rosen::Window> CreateWindow();
    void LoadUrl(const std::string& url, const std::map<std::string, std::string>& httpHeaders);
    void LoadDataWithBaseUrl(const std::string& baseUrl, const std::string& data, const std::string& mimeType,
        const std::string& encoding, const std::string& historyUrl);
    void Refresh();
    void StopLoading();
    void AddJavascriptInterface(const std::string& objectName, const std::vector<std::string>& methodList);
    void RemoveJavascriptInterface(const std::string& objectName, const std::vector<std::string>& methodList);
    void SetWebViewJavaScriptResultCallBack(const WebController::JavaScriptCallBackImpl&& javaScriptCallBackImpl);
    void Zoom(float factor);
    bool ZoomIn();
    bool ZoomOut();
    int ConverToWebHitTestType(int hitType);
    void GetHitTestValue(HitTestResult& result);
    int GetProgress();
    int GetPageHeight();
    std::string GetTitle();
    std::string GetDefaultUserAgent();
    bool SaveCookieSync();
    bool SetCookie(const std::string& url,
                   const std::string& value,
                   bool incognito_mode);
    std::string GetCookie(const std::string& url, bool incognito_mode) const;
    void DeleteEntirelyCookie(bool incognito_mode);
    void RegisterOHOSWebEventAndMethord();
    void SetWebCallBack();
    void RunSetWebIdAndHapPathCallback();
    void RunJsProxyCallback();
    void RegisterConfigObserver();
    void UnRegisterConfigObserver();

    // forward
    void Forward();
    void ClearHistory();
    void ClearSslCache();
    void ClearClientAuthenticationCache();
    bool AccessStep(int32_t step);
    void BackOrForward(int32_t step);
    bool AccessForward();

    void SearchAllAsync(const std::string& searchStr);
    void ClearMatches();
    void SearchNext(bool forward);

    void UpdateSettting(bool useNewPipe = false);

    std::string GetCustomScheme();
    void InitWebViewWithSurface();
    Size GetEnhanceSurfaceSize(const Size& drawSize);
    void UpdateScreenOffSet(double& offsetX, double& offsetY);
    void RegisterSurfacePositionChangedCallback();
    void UnregisterSurfacePositionChangedCallback();

    void NotifyPopupWindowResult(bool result);

    EventCallbackV2 GetAudioStateChangedCallback(bool useNewPipe, const RefPtr<NG::WebEventHub>& eventHub);
    void SurfaceOcclusionCallback(float visibleRatio);
    void RegisterSurfaceOcclusionChangeFun();
    void SetPartitionPoints(std::vector<float>& partition);
    void ratioStrToFloat(const std::string& str);
    void ratioStrToFloatV2(const std::string& str);
    // Return canonical encoding name according to the encoding alias name.
    std::string GetCanonicalEncodingName(const std::string& alias_name) const;
    void RegisterAvoidAreaChangeListener(int32_t instanceId);
    void UnregisterAvoidAreaChangeListener(int32_t instanceId);
    NG::SafeAreaInsets GetCombinedSafeArea();
    void OnSafeInsetsChange();
    void EnableHardware();
#endif

    WeakPtr<WebComponent> webComponent_;
    WeakPtr<RenderWeb> renderWeb_;

    WeakPtr<NG::WebPattern> webPattern_;

    std::list<CreatedCallback> createdCallbacks_;
    std::list<ReleasedCallback> releasedCallbacks_;
    EventCallback onPageStarted_;
    EventCallback onPageFinished_;
    EventCallback onPageError_;
    EventCallback onMessage_;
    Method reloadMethod_;
    Method updateUrlMethod_;
    Method routerBackMethod_;
    Method changePageUrlMethod_;
    Method isPagePathInvalidMethod_;
    State state_ { State::WAITINGFORSIZE };
#ifdef OHOS_STANDARD_SYSTEM
    std::shared_ptr<OHOS::NWeb::NWeb> nweb_;
    std::shared_ptr<OHOS::NWeb::NWebCookieManager> cookieManager_ = nullptr;
    sptr<Rosen::Window> window_;
    bool isCreateWebView_ = false;
    int32_t callbackId_ = 0;

    EventCallbackV2 onPageFinishedV2_;
    EventCallbackV2 onPageStartedV2_;
    EventCallbackV2 onProgressChangeV2_;
    EventCallbackV2 onTitleReceiveV2_;
    EventCallbackV2 onFullScreenExitV2_;
    EventCallbackV2 onGeolocationHideV2_;
    EventCallbackV2 onGeolocationShowV2_;
    EventCallbackV2 onRequestFocusV2_;
    EventCallbackV2 onErrorReceiveV2_;
    EventCallbackV2 onHttpErrorReceiveV2_;
    EventCallbackV2 onDownloadStartV2_;
    EventCallbackV2 onRefreshAccessedHistoryV2_;
    EventCallbackV2 onRenderExitedV2_;
    EventCallbackV2 onResourceLoadV2_;
    EventCallbackV2 onScaleChangeV2_;
    EventCallbackV2 onScrollV2_;
    EventCallbackV2 onPermissionRequestV2_;
    EventCallbackV2 onSearchResultReceiveV2_;
    EventCallbackV2 onActivateContentV2_;
    EventCallbackV2 onWindowExitV2_;
    EventCallbackV2 onPageVisibleV2_;
    EventCallbackV2 onTouchIconUrlV2_;
    EventCallbackV2 onAudioStateChangedV2_;
    EventCallbackV2 onFirstContentfulPaintV2_;
    EventCallbackV2 OnFirstMeaningfulPaintV2_;
    EventCallbackV2 OnLargestContentfulPaintV2_;
    EventCallbackV2 onOverScrollV2_;
    EventCallbackV2 onScreenCaptureRequestV2_;
    EventCallbackV2 onNavigationEntryCommittedV2_;
    EventCallbackV2 onSafeBrowsingCheckResultV2_;
    EventCallbackV2 OnNativeEmbedAllDestoryV2_;
    EventCallbackV2 OnNativeEmbedLifecycleChangeV2_;
    EventCallbackV2 OnNativeEmbedVisibilityChangeV2_;
    EventCallbackV2 OnNativeEmbedGestureEventV2_;
    EventCallbackV2 onIntelligentTrackingPreventionResultV2_;
    EventCallbackV2 onRenderProcessNotRespondingV2_;
    EventCallbackV2 onRenderProcessRespondingV2_;
    EventCallbackV2 onViewportFitChangedV2_;
    std::function<WebKeyboardOption(const std::shared_ptr<BaseEventInfo>&)> onInterceptKeyboardAttachV2_;
    EventCallbackV2 onAdsBlockedV2_;

    int32_t renderMode_ = -1;
    int32_t layoutMode_ = -1;
    std::string bundlePath_;
    std::string bundleDataPath_;
    std::string hapPath_;
    RefPtr<PixelMap> pixelMap_ = nullptr;
    bool isRefreshPixelMap_ = false;
    Size drawSize_;
    Offset offset_;
    bool isEnhanceSurface_ = false;
    sptr<WebSurfaceCallback> surfaceCallback_;
    sptr<OHOS::SurfaceDelegate> surfaceDelegate_;
    EGLNativeWindowType mEglWindow = nullptr;
    EGLDisplay mEGLDisplay = EGL_NO_DISPLAY;
    EGLConfig mEGLConfig = nullptr;
    EGLContext mEGLContext = EGL_NO_CONTEXT;
    EGLContext mSharedEGLContext = EGL_NO_CONTEXT;
    EGLSurface mEGLSurface = nullptr;
    WindowsSurfaceInfo surfaceInfo_ = { nullptr, EGL_NO_DISPLAY, nullptr, EGL_NO_CONTEXT };
    bool forceDarkMode_ = false;
    WebDarkMode current_dark_mode_ = WebDarkMode::Auto;
    std::shared_ptr<OHOS::AbilityRuntime::EnvironmentCallback> configChangeObserver_ = nullptr;
    OHOS::NWeb::BlurReason blurReason_ = OHOS::NWeb::BlurReason::FOCUS_SWITCH;
    bool isPopup_ = false;
    int32_t parentNWebId_ = -1;
    bool needResizeAtFirst_ = false;
    int32_t backgroundColor_ = 0xffffffff;
    uint32_t rosenWindowId_ = 0;
    RefPtr<WebDelegateObserver> observer_;
    std::shared_ptr<Rosen::RSNode> rsNode_;
    std::shared_ptr<Rosen::RSNode> surfaceRsNode_;
    Rosen::NodeId surfaceNodeId_ = 0;
    float visibleRatio_ = 1.0;
    uint32_t delayTime_ = 500;
    float lowerFrameRateVisibleRatio_ = 0.1;
    float halfFrameRateVisibleRatio_ = 0.3;
    bool isHalfFrame_ = false;
    std::optional<ScriptItems> onDocumentStartScriptItems_;
    std::optional<ScriptItems> onDocumentEndScriptItems_;
    std::optional<ScriptItems> onHeadReadyScriptItems_;
    std::optional<ScriptItemsByOrder> onDocumentStartScriptItemsByOrder_;
    std::optional<ScriptItemsByOrder> onDocumentEndScriptItemsByOrder_;
    std::optional<ScriptItemsByOrder> onHeadReadyScriptItemsByOrder_;
    bool accessibilityState_ = false;
    std::optional<std::string> richtextData_;
    bool incognitoMode_ = false;
    bool isEmbedModeEnabled_ = false;
    std::shared_mutex embedDataInfoMutex_;
    std::map<std::string, std::shared_ptr<OHOS::NWeb::NWebNativeEmbedDataInfo>> embedDataInfo_;
    std::string tag_;
    std::string tag_type_;
    double resizeWidth_ = 0.0;
    double resizeHeight_ = 0.0;
    double resizeVisibleWidth_ = -1.0;
    double resizeVisibleHeight_ = -1.0;
    OHOS::Ace::Rect currentArea_;
    NG::SafeAreaInsets systemSafeArea_;
    NG::SafeAreaInsets cutoutSafeArea_;
    NG::SafeAreaInsets navigationIndicatorSafeArea_;
    sptr<Rosen::IAvoidAreaChangedListener> avoidAreaChangedListener_ = nullptr;
    int32_t instanceId_;
    std::shared_ptr<OHOS::NWeb::NWebCustomKeyboardHandler> keyboardHandler_ = nullptr;
    sptr<WebWindowFocusChangedListener> webWindowFocusChangedListener_ = nullptr;
    std::string sharedRenderProcessToken_;
    int64_t lastFocusInputId_ = 0;
    int64_t lastFocusReportId_ = 0;
    RefPtr<TaskExecutor> taskExecutor_;
    bool isEnableHardwareComposition_ = false;
    bool isDragResizeStart_ = false;
    double dragResize_preHight_ = 0.0;
    double dragResize_preWidth_ = 0.0;
    bool enableFollowSystemFontWeight_ = false;

    // data detector js state
    bool initDataDetectorJS_ = false;
    bool isFileSelectorShow_ = false;

#endif
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEB_DELEGATE_H
