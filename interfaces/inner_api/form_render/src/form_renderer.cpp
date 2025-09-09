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

#include "form_renderer.h"

#include "form_mgr_errors.h"
#include "form_renderer_hilog.h"
#include "form_event_report.h"
#include "base/utils/utils.h"

namespace OHOS {
namespace Ace {
namespace {
constexpr char FORM_RENDERER_ALLOW_UPDATE[] = "allowUpdate";
constexpr char FORM_RENDERER_DISPATCHER[] = "ohos.extra.param.key.process_on_form_renderer_dispatcher";
constexpr char FORM_RENDERER_PROCESS_ON_ADD_SURFACE[] = "ohos.extra.param.key.process_on_add_surface";
constexpr char TRANSPARENT_COLOR[] = "#00FFFFFF";
constexpr int32_t DOUBLE = 2;
} // namespace

using EventHandler = OHOS::AppExecFwk::EventHandler;

FormRenderer::FormRenderer(const std::shared_ptr<OHOS::AbilityRuntime::Context> context,
    const std::shared_ptr<OHOS::AbilityRuntime::Runtime> runtime,
    std::weak_ptr<OHOS::AppExecFwk::EventHandler> eventHandler)
    : context_(context), runtime_(runtime), eventHandler_(eventHandler)
{
    HILOG_INFO("FormRenderer created.");
    if (!context_ || !runtime_) {
        return;
    }
    auto& nativeEngine = (static_cast<AbilityRuntime::JsRuntime&>(*runtime_.get())).GetNativeEngine();
    uiContent_ = UIContent::Create(context_.get(), &nativeEngine, true);
}

FormRenderer::~FormRenderer()
{
    HILOG_DEBUG("called");
}

void FormRenderer::PreInitUIContent(const OHOS::AAFwk::Want& want, const OHOS::AppExecFwk::FormJsInfo& formJsInfo)
{
    HILOG_INFO("InitUIContent width = %{public}f , height = %{public}f, borderWidth = %{public}f,"
        " layoutWidth =  %{public}f, layoutHeight = %{public}f. formJsInfo.formData.size = %{public}zu."
        " formJsInfo.imageDataMap.size = %{public}zu.", width_, height_, borderWidth_, layoutWidth_, layoutHeight_,
        formJsInfo.formData.size(), formJsInfo.imageDataMap.size());
    SetAllowUpdate(allowUpdate_);
    float uiWidth = width_ - borderWidth_ * DOUBLE;
    float uiHeight = height_ - borderWidth_ * DOUBLE;
    uiContent_->SetFormWidth(uiWidth);
    uiContent_->SetFormHeight(uiHeight);
    lastBorderWidth_ = borderWidth_;
    uiContent_->SetFontScaleFollowSystem(fontScaleFollowSystem_);
    uiContent_->UpdateFormSharedImage(formJsInfo.imageDataMap);
    uiContent_->UpdateFormData(formJsInfo.formData);
    uiContent_->PreInitializeForm(nullptr, formJsInfo.formSrc, nullptr);
    backgroundColor_ = want.GetStringParam(OHOS::AppExecFwk::Constants::PARAM_FORM_TRANSPARENCY_KEY);
    if (!backgroundColor_.empty()) {
        uiContent_->SetFormBackgroundColor(backgroundColor_);
    }
    if (!uiContent_->GetFormRootNode()) {
        HILOG_ERROR("PreInitUIContent failed to PreInitializeForm, rsSurfaceNode is null");
        AppExecFwk::FormEventReport::SendFormFailedEvent(AppExecFwk::FormEventName::FORM_NODE_ERROR,
            formJsInfo.formId,
            formJsInfo.bundleName,
            formJsInfo.formName,
            static_cast<int32_t>(AppExecFwk::AddFormFailedErrorType::UI_CONTENT_INIT_FAILED),
            0);
    }
    uiContent_->SetFormViewScale(uiWidth, uiHeight, layoutWidth_, layoutHeight_);
}

void FormRenderer::RunFormPageInner(const OHOS::AAFwk::Want& want, const OHOS::AppExecFwk::FormJsInfo& formJsInfo)
{
    if (renderingMode_ == AppExecFwk::Constants::RenderingMode::SINGLE_COLOR) {
        uiContent_->SetFormRenderingMode(static_cast<int8_t>(renderingMode_));
    }
    if (enableBlurBackground_) {
        uiContent_->SetFormEnableBlurBackground(enableBlurBackground_);
    }
    uiContent_->RunFormPage();
    backgroundColor_ = want.GetStringParam(OHOS::AppExecFwk::Constants::PARAM_FORM_TRANSPARENCY_KEY);
    if (!backgroundColor_.empty()) {
        uiContent_->SetFormBackgroundColor(backgroundColor_);
    }

    auto actionEventHandler = [weak = weak_from_this()](const std::string& action) {
        auto formRenderer = weak.lock();
        if (formRenderer) {
            formRenderer->OnActionEvent(action);
        }
    };
    uiContent_->SetActionEventHandler(actionEventHandler);

    auto errorEventHandler = [weak = weak_from_this()](const std::string& code, const std::string& msg) {
        auto formRenderer = weak.lock();
        if (formRenderer) {
            formRenderer->OnError(code, msg);
        }
    };
    uiContent_->SetErrorEventHandler(errorEventHandler);

    if (!formJsInfo.isDynamic) {
        auto formLinkInfoUpdateHandler = [weak = weak_from_this()](const std::vector<std::string>& formLinkInfos) {
            auto formRenderer = weak.lock();
            if (formRenderer) {
                formRenderer->OnFormLinkInfoUpdate(formLinkInfos);
            }
        };
        uiContent_->SetFormLinkInfoUpdateHandler(formLinkInfoUpdateHandler);
    }

    auto surfaceNode = GetSurfaceNode();
    if (!surfaceNode) {
        HILOG_ERROR("rsSurfaceNode is nullptr.");
        return;
    }
    if (renderingMode_ == AppExecFwk::Constants::RenderingMode::SINGLE_COLOR || enableBlurBackground_) {
        HILOG_INFO("InitUIContent SetFormBackgroundColor #00FFFFFF");
        uiContent_->SetFormBackgroundColor(TRANSPARENT_COLOR);
    }
    HILOG_INFO("ChangeSensitiveNodes: %{public}s", obscurationMode_ ? "true" : "false");
    uiContent_->ChangeSensitiveNodes(obscurationMode_);
    uiContent_->Foreground();
}

void FormRenderer::InitUIContent(const OHOS::AAFwk::Want& want, const OHOS::AppExecFwk::FormJsInfo& formJsInfo)
{
    PreInitUIContent(want, formJsInfo);
    RunFormPageInner(want, formJsInfo);
}

void FormRenderer::ParseWant(const OHOS::AAFwk::Want& want)
{
    allowUpdate_ = want.GetBoolParam(FORM_RENDERER_ALLOW_UPDATE, true);
    width_ = want.GetDoubleParam(OHOS::AppExecFwk::Constants::PARAM_FORM_WIDTH_KEY, 0.0f);
    height_ = want.GetDoubleParam(OHOS::AppExecFwk::Constants::PARAM_FORM_HEIGHT_KEY, 0.0f);
    layoutWidth_ = want.GetDoubleParam(OHOS::AppExecFwk::Constants::PARAM_LAYOUT_WIDTH_KEY, width_);
    layoutHeight_ = want.GetDoubleParam(OHOS::AppExecFwk::Constants::PARAM_LAYOUT_HEIGHT_KEY, height_);
    proxy_ = want.GetRemoteObject(FORM_RENDERER_PROCESS_ON_ADD_SURFACE);
    renderingMode_ = (AppExecFwk::Constants::RenderingMode)want.GetIntParam(
        OHOS::AppExecFwk::Constants::PARAM_FORM_RENDERINGMODE_KEY, 0);
    enableBlurBackground_ = want.GetBoolParam(OHOS::AppExecFwk::Constants::PARAM_FORM_ENABLE_BLUR_BACKGROUND_KEY,
        false);
    borderWidth_ = want.GetFloatParam(OHOS::AppExecFwk::Constants::PARAM_FORM_BORDER_WIDTH_KEY, 0.0f);
    fontScaleFollowSystem_ = want.GetBoolParam(OHOS::AppExecFwk::Constants::PARAM_FONT_FOLLOW_SYSTEM_KEY, true);
    obscurationMode_ = want.GetBoolParam(OHOS::AppExecFwk::Constants::PARAM_FORM_OBSCURED_KEY, false);
}

int32_t FormRenderer::AddForm(const OHOS::AAFwk::Want& want, const OHOS::AppExecFwk::FormJsInfo& formJsInfo)
{
    if (uiContent_ == nullptr) {
        HILOG_ERROR("uiContent is null!");
        return ERR_APPEXECFWK_FORM_FORM_NODE_RELEASED;
    }
    formRendererDispatcherImpl_ = new FormRendererDispatcherImpl(uiContent_, shared_from_this(), eventHandler_);
    ParseWant(want);
    InitUIContent(want, formJsInfo);
    SetRenderDelegate(proxy_);
    if (want.HasParameter(OHOS::AppExecFwk::Constants::FORM_STATUS_DATA)) {
        std::string statusData = want.GetStringParam(OHOS::AppExecFwk::Constants::FORM_STATUS_DATA);
        RecoverForm(statusData);
    }
    return OnSurfaceCreate(formJsInfo, want.GetBoolParam(
        OHOS::AppExecFwk::Constants::FORM_IS_RECOVER_FORM_TO_HANDLE_CLICK_EVENT, false));
}

void FormRenderer::PreInitAddForm(const OHOS::AAFwk::Want& want, const OHOS::AppExecFwk::FormJsInfo& formJsInfo)
{
    if (uiContent_ == nullptr) {
        HILOG_ERROR("uiContent is null!");
        return;
    }
    formRendererDispatcherImpl_ = new FormRendererDispatcherImpl(uiContent_, shared_from_this(), eventHandler_);
    ParseWant(want);
    PreInitUIContent(want, formJsInfo);
}

int32_t FormRenderer::RunFormPage(const OHOS::AAFwk::Want& want, const OHOS::AppExecFwk::FormJsInfo& formJsInfo)
{
    if (uiContent_ == nullptr) {
        HILOG_ERROR("uiContent is null!");
        return ERR_APPEXECFWK_FORM_FORM_NODE_RELEASED;
    }
    ParseWant(want);
    RunFormPageInner(want, formJsInfo);
    SetRenderDelegate(proxy_);
    if (want.HasParameter(OHOS::AppExecFwk::Constants::FORM_STATUS_DATA)) {
        std::string statusData = want.GetStringParam(OHOS::AppExecFwk::Constants::FORM_STATUS_DATA);
        RecoverForm(statusData);
    }
    return OnSurfaceCreate(formJsInfo, want.GetBoolParam(
        OHOS::AppExecFwk::Constants::FORM_IS_RECOVER_FORM_TO_HANDLE_CLICK_EVENT, false));
}

void FormRenderer::ReloadForm(const std::string& url)
{
    if (!uiContent_) {
        HILOG_ERROR("uiContent_ is null");
        return;
    }
    uiContent_->ReloadForm(url);
}

bool FormRenderer::IsAllowUpdate()
{
    if (formRendererDispatcherImpl_ == nullptr) {
        HILOG_ERROR("formRendererDispatcherImpl is null");
        return true;
    }

    return formRendererDispatcherImpl_->IsAllowUpdate();
}

void FormRenderer::SetAllowUpdate(bool allowUpdate)
{
    if (formRendererDispatcherImpl_ == nullptr) {
        HILOG_ERROR("formRendererDispatcherImpl is null");
        return;
    }

    formRendererDispatcherImpl_->SetAllowUpdate(allowUpdate);
}

void FormRenderer::UpdateForm(const OHOS::AppExecFwk::FormJsInfo& formJsInfo)
{
    HILOG_INFO("FormRender UpdateForm start.");
    if (!IsAllowUpdate()) {
        HILOG_ERROR("Not allow update");
        return;
    }
    if (!uiContent_) {
        HILOG_ERROR("uiContent_ is null");
        return;
    }
    uiContent_->SetFontScaleFollowSystem(fontScaleFollowSystem_);
    uiContent_->UpdateFormSharedImage(formJsInfo.imageDataMap);
    uiContent_->UpdateFormData(formJsInfo.formData);
    HILOG_INFO("FormRender UpdateForm end. formJsInfo.formData.size = %{public}zu. \
        formJsInfo.imageDataMap.size = %{public}zu.",
        formJsInfo.formData.size(),
        formJsInfo.imageDataMap.size());
    if (!formRendererDelegate_) {
        HILOG_ERROR("form renderer delegate is null!");
        return;
    }
    formRendererDelegate_->OnUpdateFormDone(formJsInfo.formId);
}

void FormRenderer::RemoveFormDeathRecipient()
{
    if (!formRendererDelegate_) {
        return;
    }
    auto renderDelegate = formRendererDelegate_->AsObject();
    if (renderDelegate != nullptr) {
        renderDelegate->RemoveDeathRecipient(renderDelegateDeathRecipient_);
    }
}

void FormRenderer::Destroy()
{
    HILOG_INFO("Destroy FormRenderer start.");
    if (formRendererDelegate_ != nullptr) {
        auto surfaceNode = GetSurfaceNode();
        if (surfaceNode) {
            HILOG_INFO("Form OnSurfaceRelease, id: %{public}" PRIu64, surfaceNode->GetId());
            formRendererDelegate_->OnSurfaceRelease(surfaceNode->GetId());
        }
    }

    RemoveFormDeathRecipient();
    renderDelegateDeathRecipient_ = nullptr;
    formRendererDelegate_ = nullptr;
    formRendererDispatcherImpl_ = nullptr;
    if (uiContent_) {
        uiContent_->Destroy();
        uiContent_ = nullptr;
    }
    context_ = nullptr;
    runtime_ = nullptr;
    HILOG_INFO("Destroy FormRenderer finish.");
}

void FormRenderer::UpdateFormSize(float width, float height, float borderWidth)
{
    if (!uiContent_) {
        HILOG_ERROR("uiContent_ is null");
        return;
    }
    float resizedWidth = width - borderWidth * DOUBLE;
    float resizedHeight = height - borderWidth * DOUBLE;
    if (!NearEqual(width, width_) || !NearEqual(height, height_) || !NearEqual(borderWidth, lastBorderWidth_)) {
        width_ = width;
        height_ = height;
        borderWidth_ = borderWidth;
        uiContent_->SetFormWidth(resizedWidth);
        uiContent_->SetFormHeight(resizedHeight);
        uiContent_->SetFormViewScale(resizedWidth, resizedHeight, layoutWidth_, layoutHeight_);
        lastBorderWidth_ = borderWidth_;
        std::shared_ptr<EventHandler> eventHandler = eventHandler_.lock();
        HILOG_INFO("UpdateFormSize after set uiContent, width: %{public}f, height: %{public}f", width, height);
        if (!eventHandler) {
            HILOG_ERROR("eventHandler is null");
            return;
        }
        eventHandler->PostTask([uiContent = uiContent_, resizedWidth, resizedHeight]() {
            if (!uiContent) {
                HILOG_ERROR("uiContent is null");
                return;
            }
            uiContent->OnFormSurfaceChange(resizedWidth, resizedHeight);
        });
    }
}

void FormRenderer::OnSurfaceChange(float width, float height, float borderWidth)
{
    if (!formRendererDelegate_) {
        HILOG_ERROR("form renderer delegate is null!");
        return;
    }
    HILOG_INFO("Form OnSurfaceChange!");
    formRendererDelegate_->OnSurfaceChange(width, height, borderWidth);
    width_ = width;
    height_ = height;
    borderWidth_ = borderWidth;
}

int32_t FormRenderer::OnSurfaceCreate(const OHOS::AppExecFwk::FormJsInfo& formJsInfo,
    bool isRecoverFormToHandleClickEvent)
{
    if (!formRendererDispatcherImpl_) {
        HILOG_ERROR("form renderer dispatcher is null!");
        return ERR_APPEXECFWK_FORM_FORM_NODE_RELEASED;
    }
    if (!formRendererDelegate_) {
        HILOG_ERROR("form renderer delegate is null!");
        return ERR_APPEXECFWK_FORM_FORM_NODE_RELEASED;
    }
    OHOS::AAFwk::Want newWant;
    newWant.SetParam(FORM_RENDERER_DISPATCHER, formRendererDispatcherImpl_->AsObject());
    newWant.SetParam(OHOS::AppExecFwk::Constants::FORM_IS_RECOVER_FORM_TO_HANDLE_CLICK_EVENT,
        isRecoverFormToHandleClickEvent);

    auto rsSurfaceNode = GetSurfaceNode();
    if (!rsSurfaceNode) {
        HILOG_ERROR("OnSurfaceCreate rsSurfaceNode is nullptr.");
        return ERR_APPEXECFWK_FORM_FORM_NODE_RELEASED;
    }
    HILOG_INFO("Form OnSurfaceCreate, id: %{public}" PRIu64, rsSurfaceNode->GetId());

    int32_t ret = ERR_OK;
    if (formJsInfo.uiSyntax == OHOS::AppExecFwk::FormType::ETS) {
        OHOS::AppExecFwk::FormJsInfo newFormJsInfo = formJsInfo.CopyFormJsInfoWithoutFormData();
        ret = formRendererDelegate_->OnSurfaceCreate(rsSurfaceNode, newFormJsInfo, newWant);
    } else {
        ret = formRendererDelegate_->OnSurfaceCreate(rsSurfaceNode, formJsInfo, newWant);
    }
    if (ret != ERR_OK) {
        HILOG_ERROR("Form OnSurfaceCreate failed, code:%{public}d", ret);
    }
    return ret;
}

int32_t FormRenderer::OnSurfaceReuse(const OHOS::AppExecFwk::FormJsInfo& formJsInfo)
{
    if (!formRendererDispatcherImpl_) {
        HILOG_ERROR("Form OnSurfaceReuse, dispatcher is null!");
        return ERR_APPEXECFWK_FORM_FORM_NODE_RELEASED;
    }
    if (!formRendererDelegate_) {
        HILOG_ERROR("Form OnSurfaceReuse, delegate is null!");
        return ERR_APPEXECFWK_FORM_FORM_NODE_RELEASED;
    }
    auto rsSurfaceNode = GetSurfaceNode();
    if (!rsSurfaceNode) {
        HILOG_ERROR("Form OnSurfaceReuse, rsSurfaceNode is null!");
        return ERR_APPEXECFWK_FORM_FORM_NODE_RELEASED;
    }
    OHOS::AAFwk::Want newWant;
    newWant.SetParam(FORM_RENDERER_DISPATCHER, formRendererDispatcherImpl_->AsObject());
    HILOG_INFO("Form OnSurfaceReuse, id: %{public}" PRIu64, rsSurfaceNode->GetId());
    OHOS::AppExecFwk::FormJsInfo newFormJsInfo = formJsInfo;
    if (formJsInfo.uiSyntax == OHOS::AppExecFwk::FormType::ETS) {
        newFormJsInfo = formJsInfo.CopyFormJsInfoWithoutFormData();
    }
    int32_t ret = formRendererDelegate_->OnSurfaceReuse(rsSurfaceNode->GetId(), newFormJsInfo, newWant);
    if (ret != ERR_OK) {
        HILOG_ERROR("Form OnSurfaceReuse failed, code:%{public}d", ret);
    }
    if (ret == ERR_APPEXECFWK_FORM_SURFACE_NODE_NOT_FOUND) {
        int32_t result = formRendererDelegate_->OnSurfaceCreate(rsSurfaceNode, newFormJsInfo, newWant);
        if (result != ERR_OK) {
            HILOG_ERROR("Form OnSurfaceCreate failed, code:%{public}d", result);
        }
    }
    formRendererDelegate_->OnFormLinkInfoUpdate(cachedInfos_);
    return ret;
}

void FormRenderer::OnSurfaceDetach()
{
    if (!formRendererDelegate_) {
        HILOG_ERROR("Form OnSurfaceDetach, delegate is null!");
        return;
    }
    auto surfaceNode = GetSurfaceNode();
    if (!surfaceNode) {
        HILOG_ERROR("Form OnSurfaceDetach, rsSurfaceNode is null!");
        return;
    }
    HILOG_INFO("Form OnSurfaceDetach, id: %{public}" PRIu64, surfaceNode->GetId());
    int32_t ret = formRendererDelegate_->OnSurfaceDetach(surfaceNode->GetId());
    if (ret != ERR_OK) {
        HILOG_ERROR("Form OnSurfaceDetach failed, code:%{public}d", ret);
    }
}

void FormRenderer::OnActionEvent(const std::string& action)
{
    if (!formRendererDelegate_) {
        HILOG_ERROR("formRendererDelegate is null!");
        return;
    }

    formRendererDelegate_->OnActionEvent(action);
}

void FormRenderer::OnError(const std::string& code, const std::string& msg)
{
    auto rsSurfaceNode = GetSurfaceNode();
    if (rsSurfaceNode) {
        HILOG_INFO("Form OnError, id: %{public}" PRIu64, rsSurfaceNode->GetId());
    } else {
        HILOG_ERROR("Form OnError, rsSurfaceNode is null");
    }
    if (!formRendererDelegate_) {
        HILOG_ERROR("formRendererDelegate is null!");
        return;
    }
    HILOG_INFO("Form OnError, code: %{public}s, msg: %{public}s", code.c_str(), msg.c_str());
    formRendererDelegate_->OnError(code, msg);
}

void FormRenderer::OnFormLinkInfoUpdate(const std::vector<std::string>& formLinkInfos)
{
    if (!formRendererDelegate_) {
        HILOG_ERROR("formRendererDelegate is null!");
        return;
    }
    cachedInfos_ = formLinkInfos;
    formRendererDelegate_->OnFormLinkInfoUpdate(formLinkInfos);
}

void FormRenderer::SetRenderDelegate(const sptr<IRemoteObject>& remoteObj)
{
    HILOG_INFO("Get renderRemoteObj, add death recipient.");
    auto renderRemoteObj = iface_cast<IFormRendererDelegate>(remoteObj);
    if (renderRemoteObj == nullptr) {
        HILOG_ERROR("renderRemoteObj is nullptr.");
        return;
    }

    if (!formRendererDelegate_) {
        formRendererDelegate_ = renderRemoteObj;
    } else {
        RemoveFormDeathRecipient();
        auto formRendererDelegate = renderRemoteObj;
        bool checkFlag = true;
        formRendererDelegate->OnCheckManagerDelegate(checkFlag);
        if (checkFlag) {
            formRendererDelegate_ = renderRemoteObj;
        } else {
            HILOG_ERROR("EventHandle - SetRenderDelegate error checkFlag is false");
        }
    }

    if (renderDelegateDeathRecipient_ == nullptr) {
        renderDelegateDeathRecipient_ = new FormRenderDelegateRecipient(
            [eventHandler = eventHandler_, renderer = weak_from_this()]() {
                auto handler = eventHandler.lock();
                if (!handler) {
                    HILOG_ERROR("eventHandler is nullptr");
                    return;
                }

                handler->PostTask([weak = renderer]() {
                    auto formRender = weak.lock();
                    if (!formRender) {
                        HILOG_ERROR("formRender is nullptr");
                        return;
                    }
                    formRender->ResetRenderDelegate();
                });
            });
    }
    auto renderDelegate = formRendererDelegate_->AsObject();
    if (renderDelegate == nullptr) {
        HILOG_ERROR("renderDelegate is nullptr, can not get obj from renderRemoteObj.");
        return;
    }
    renderDelegate->AddDeathRecipient(renderDelegateDeathRecipient_);
}

void FormRenderer::ResetRenderDelegate()
{
    if (formRendererDelegate_ && !formRendererDelegate_->AsObject()->IsObjectDead()) {
        HILOG_WARN("ResetRenderDelegate formRendererDelegate_ has been replaced.");
        return;
    }
    HILOG_INFO("ResetRenderDelegate.");
    RemoveFormDeathRecipient();
    renderDelegateDeathRecipient_ = nullptr;
    formRendererDelegate_ = nullptr;
}

void FormRenderer::UpdateConfiguration(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config)
{
    if (!uiContent_) {
        HILOG_ERROR("uiContent_ is null");
        return;
    }

    uiContent_->UpdateConfiguration(config);
}

void FormRenderDelegateRecipient::OnRemoteDied(const wptr<IRemoteObject>& remote)
{
    HILOG_ERROR("Recv FormRenderDelegate death notice");
    if (remote == nullptr) {
        HILOG_ERROR("weak remote is null");
        return;
    }
    if (handler_) {
        handler_();
    }
}

int32_t FormRenderer::AttachForm(const OHOS::AAFwk::Want& want, const OHOS::AppExecFwk::FormJsInfo& formJsInfo)
{
    if (uiContent_ == nullptr) {
        HILOG_ERROR("uiContent is null!");
        return ERR_APPEXECFWK_FORM_FORM_NODE_RELEASED;
    }
    ParseWant(want);
    OnSurfaceDetach();
    AttachUIContent(want, formJsInfo);
    SetRenderDelegate(proxy_);
    return OnSurfaceReuse(formJsInfo);
}

void FormRenderer::AttachUIContent(const OHOS::AAFwk::Want& want, const OHOS::AppExecFwk::FormJsInfo& formJsInfo)
{
    HILOG_INFO("AttachUIContent width = %{public}f , height = %{public}f, borderWidth_ = %{public}f,"
        " layoutWidth_ = %{public}f, layoutHeight_ = %{public}f.", width_, height_, borderWidth_,
        layoutWidth_, layoutHeight_);
    SetAllowUpdate(allowUpdate_);
    float width = width_ - borderWidth_ * DOUBLE;
    float height = height_ - borderWidth_ * DOUBLE;
    if (!NearEqual(width, uiContent_->GetFormWidth()) || !NearEqual(height, uiContent_->GetFormHeight())
        || !NearEqual(borderWidth_, lastBorderWidth_)) {
        uiContent_->SetFormWidth(width);
        uiContent_->SetFormHeight(height);
        uiContent_->SetFormViewScale(width, height, layoutWidth_, layoutHeight_);
        lastBorderWidth_ = borderWidth_;
        uiContent_->OnFormSurfaceChange(width, height);
        HILOG_INFO("AttachUIContent after set uiContent, width: %{public}f, height: %{public}f", width, height);
    }
    auto backgroundColor = want.GetStringParam(OHOS::AppExecFwk::Constants::PARAM_FORM_TRANSPARENCY_KEY);
    if (backgroundColor_ != backgroundColor) {
        backgroundColor_ = backgroundColor;
        uiContent_->SetFormBackgroundColor(backgroundColor_);
    }
    if (renderingMode_ == AppExecFwk::Constants::RenderingMode::SINGLE_COLOR || enableBlurBackground_) {
        HILOG_INFO("AttachUIContent SetFormBackgroundColor #00FFFFFF");
        uiContent_->SetFormBackgroundColor(TRANSPARENT_COLOR);
    }

    uiContent_->Foreground();
}

void FormRenderer::GetRectRelativeToWindow(AccessibilityParentRectInfo& parentRectInfo) const
{
    if (!formRendererDelegate_) {
        HILOG_ERROR("form renderer delegate is null!");
        return;
    }
    formRendererDelegate_->OnGetRectRelativeToWindow(parentRectInfo);
}

void FormRenderer::RecycleForm(std::string& statusData)
{
    if (uiContent_ == nullptr) {
        HILOG_ERROR("RecycleForm, uiContent_ is null!");
        return;
    }
    statusData = uiContent_->RecycleForm();
}

void FormRenderer::RecoverForm(const std::string& statusData)
{
    if (uiContent_ == nullptr) {
        HILOG_ERROR("RecoverForm, uiContent_ is null!");
        return;
    }
    uiContent_->RecoverForm(statusData);
}

void FormRenderer::SetVisibleChange(bool isVisible)
{
    if (formRendererDispatcherImpl_ != nullptr) {
        formRendererDispatcherImpl_->SetVisible(isVisible);
    } else {
        HILOG_WARN("formRendererDispatcherImpl_ is null!");
    }

    if (uiContent_ == nullptr) {
        HILOG_ERROR("SetVisibleChange error, uiContent_ is null!");
        return;
    }
    uiContent_->ProcessFormVisibleChange(isVisible);
}

bool FormRenderer::IsManagerDelegateValid(const OHOS::AAFwk::Want& want)
{
    sptr<IRemoteObject> hostRemoteObj = want.GetRemoteObject(FORM_RENDERER_PROCESS_ON_ADD_SURFACE);
    auto renderRemoteObj = iface_cast<IFormRendererDelegate>(hostRemoteObj);
    if (renderRemoteObj == nullptr) {
        return true;
    }
    bool checkFlag = true;
    renderRemoteObj->OnCheckManagerDelegate(checkFlag);
    HILOG_INFO("checkFlag:%{public}d", checkFlag);
    return checkFlag;
}

std::shared_ptr<Rosen::RSSurfaceNode> FormRenderer::GetSurfaceNode()
{
    if (!uiContent_) {
        HILOG_ERROR("uiContent_ is null");
        return nullptr;
    }
    return uiContent_->GetFormRootNode();
}
} // namespace Ace
} // namespace OHOS
