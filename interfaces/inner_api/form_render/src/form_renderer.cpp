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

#include "form_renderer_hilog.h"

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
    HILOG_INFO("FormRenderer %{public}p created.", this);
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
    HILOG_INFO("InitUIContent width = %{public}f , height = %{public}f, borderWidth = %{public}f.",
        width_, height_, borderWidth_);
    SetAllowUpdate(allowUpdate_);
    uiContent_->SetFormWidth(width_ - borderWidth_ * DOUBLE);
    uiContent_->SetFormHeight(height_ - borderWidth_ * DOUBLE);
    lastBorderWidth_ = borderWidth_;
    uiContent_->SetFontScaleFollowSystem(fontScaleFollowSystem_);
    uiContent_->UpdateFormSharedImage(formJsInfo.imageDataMap);
    uiContent_->UpdateFormData(formJsInfo.formData);
    uiContent_->PreInitializeForm(nullptr, formJsInfo.formSrc, nullptr);
    backgroundColor_ = want.GetStringParam(OHOS::AppExecFwk::Constants::PARAM_FORM_TRANSPARENCY_KEY);
    if (!backgroundColor_.empty()) {
        uiContent_->SetFormBackgroundColor(backgroundColor_);
    }
}

void FormRenderer::RunFormPageInner(const OHOS::AAFwk::Want& want, const OHOS::AppExecFwk::FormJsInfo& formJsInfo)
{
    if (renderingMode_ == AppExecFwk::Constants::RenderingMode::SINGLE_COLOR) {
        uiContent_->SetFormRenderingMode(static_cast<int8_t>(renderingMode_));
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

    auto rsSurfaceNode = uiContent_->GetFormRootNode();
    if (rsSurfaceNode == nullptr) {
        return;
    }
    rsSurfaceNode->SetBounds(round(borderWidth_), round(borderWidth_), round(width_ - borderWidth_ * DOUBLE),
        round(height_ - borderWidth_ * DOUBLE));
    if (renderingMode_ == AppExecFwk::Constants::RenderingMode::SINGLE_COLOR) {
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
    proxy_ = want.GetRemoteObject(FORM_RENDERER_PROCESS_ON_ADD_SURFACE);
    renderingMode_ = (AppExecFwk::Constants::RenderingMode)want.GetIntParam(
        OHOS::AppExecFwk::Constants::PARAM_FORM_RENDERINGMODE_KEY, 0);
    borderWidth_ = want.GetFloatParam(OHOS::AppExecFwk::Constants::PARAM_FORM_BORDER_WIDTH_KEY, 0.0f);
    fontScaleFollowSystem_ = want.GetBoolParam(OHOS::AppExecFwk::Constants::PARAM_FONT_FOLLOW_SYSTEM_KEY, true);
    obscurationMode_ = want.GetBoolParam(OHOS::AppExecFwk::Constants::PARAM_FORM_OBSCURED_KEY, false);
}

void FormRenderer::AddForm(const OHOS::AAFwk::Want& want, const OHOS::AppExecFwk::FormJsInfo& formJsInfo)
{
    if (uiContent_ == nullptr) {
        HILOG_ERROR("uiContent is null!");
        return;
    }
    formRendererDispatcherImpl_ = new FormRendererDispatcherImpl(uiContent_, shared_from_this(), eventHandler_);
    ParseWant(want);
    InitUIContent(want, formJsInfo);
    SetRenderDelegate(proxy_);
    if (want.HasParameter(OHOS::AppExecFwk::Constants::FORM_STATUS_DATA)) {
        std::string statusData = want.GetStringParam(OHOS::AppExecFwk::Constants::FORM_STATUS_DATA);
        RecoverForm(statusData);
    }
    OnSurfaceCreate(formJsInfo, want.GetBoolParam(
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

void FormRenderer::RunFormPage(const OHOS::AAFwk::Want& want, const OHOS::AppExecFwk::FormJsInfo& formJsInfo)
{
    if (uiContent_ == nullptr) {
        HILOG_ERROR("uiContent is null!");
        return;
    }
    ParseWant(want);
    RunFormPageInner(want, formJsInfo);
    SetRenderDelegate(proxy_);
    if (want.HasParameter(OHOS::AppExecFwk::Constants::FORM_STATUS_DATA)) {
        std::string statusData = want.GetStringParam(OHOS::AppExecFwk::Constants::FORM_STATUS_DATA);
        RecoverForm(statusData);
    }
    OnSurfaceCreate(formJsInfo, want.GetBoolParam(
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
}

void FormRenderer::Destroy()
{
    HILOG_INFO("Destroy FormRenderer start.");
    if (formRendererDelegate_ != nullptr) {
        auto rsSurfaceNode = uiContent_->GetFormRootNode();
        if (rsSurfaceNode != nullptr) {
            HILOG_INFO("Form OnSurfaceRelease!");
            formRendererDelegate_->OnSurfaceRelease(rsSurfaceNode->GetId());
        }
    }

    if (formRendererDelegate_ != nullptr && formRendererDelegate_->AsObject() != nullptr) {
        formRendererDelegate_->AsObject()->RemoveDeathRecipient(renderDelegateDeathRecipient_);
    }
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

void FormRenderer::OnSurfaceCreate(const OHOS::AppExecFwk::FormJsInfo& formJsInfo,
    bool isRecoverFormToHandleClickEvent)
{
    if (!formRendererDispatcherImpl_) {
        HILOG_ERROR("form renderer dispatcher is null!");
        return;
    }
    if (!formRendererDelegate_) {
        HILOG_ERROR("form renderer delegate is null!");
        return;
    }
    OHOS::AAFwk::Want newWant;
    newWant.SetParam(FORM_RENDERER_DISPATCHER, formRendererDispatcherImpl_->AsObject());
    newWant.SetParam(OHOS::AppExecFwk::Constants::FORM_IS_RECOVER_FORM_TO_HANDLE_CLICK_EVENT,
        isRecoverFormToHandleClickEvent);
    auto rsSurfaceNode = uiContent_->GetFormRootNode();
    HILOG_INFO("Form OnSurfaceCreate!");
    formRendererDelegate_->OnSurfaceCreate(rsSurfaceNode, formJsInfo, newWant);
}

void FormRenderer::OnSurfaceReuse(const OHOS::AppExecFwk::FormJsInfo& formJsInfo)
{
    if (!formRendererDispatcherImpl_) {
        HILOG_ERROR("form renderer dispatcher is null!");
        return;
    }
    if (!formRendererDelegate_) {
        HILOG_ERROR("form renderer delegate is null!");
        return;
    }
    auto rsSurfaceNode = uiContent_->GetFormRootNode();
    if (rsSurfaceNode == nullptr) {
        HILOG_ERROR("form renderer rsSurfaceNode is null!");
        return;
    }
    OHOS::AAFwk::Want newWant;
    newWant.SetParam(FORM_RENDERER_DISPATCHER, formRendererDispatcherImpl_->AsObject());
    HILOG_INFO("Form OnSurfaceReuse.");
    formRendererDelegate_->OnSurfaceReuse(rsSurfaceNode->GetId(), formJsInfo, newWant);
    formRendererDelegate_->OnFormLinkInfoUpdate(cachedInfos_);
}

void FormRenderer::OnSurfaceDetach()
{
    if (!formRendererDelegate_) {
        HILOG_ERROR("form renderer delegate is null!");
        return;
    }
    auto rsSurfaceNode = uiContent_->GetFormRootNode();
    if (rsSurfaceNode == nullptr) {
        HILOG_ERROR("form renderer rsSurfaceNode is null!");
        return;
    }
    HILOG_INFO("Form OnSurfaceDetach.");
    formRendererDelegate_->OnSurfaceDetach(rsSurfaceNode->GetId());
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
    if (!formRendererDelegate_) {
        HILOG_ERROR("formRendererDelegate is null!");
        return;
    }

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

    formRendererDelegate_ = renderRemoteObj;

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
    HILOG_INFO("ResetRenderDelegate.");
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

void FormRenderer::AttachForm(const OHOS::AAFwk::Want& want, const OHOS::AppExecFwk::FormJsInfo& formJsInfo)
{
    if (uiContent_ == nullptr) {
        HILOG_ERROR("uiContent is null!");
        return;
    }
    ParseWant(want);
    OnSurfaceDetach();
    AttachUIContent(want, formJsInfo);
    SetRenderDelegate(proxy_);
    OnSurfaceReuse(formJsInfo);
}

void FormRenderer::AttachUIContent(const OHOS::AAFwk::Want& want, const OHOS::AppExecFwk::FormJsInfo& formJsInfo)
{
    HILOG_INFO("AttachUIContent width = %{public}f , height = %{public}f, borderWidth_ = %{public}f.",
        width_, height_, borderWidth_);
    SetAllowUpdate(allowUpdate_);
    auto rsSurfaceNode = uiContent_->GetFormRootNode();
    if (rsSurfaceNode == nullptr) {
        HILOG_ERROR("rsSurfaceNode is nullptr.");
        return;
    }
    float width = width_ - borderWidth_ * DOUBLE;
    float height = height_ - borderWidth_ * DOUBLE;
    if (!NearEqual(width, uiContent_->GetFormWidth()) || !NearEqual(height, uiContent_->GetFormHeight())
        || !NearEqual(borderWidth_, lastBorderWidth_)) {
        uiContent_->SetFormWidth(width);
        uiContent_->SetFormHeight(height);
        lastBorderWidth_ = borderWidth_;
        uiContent_->OnFormSurfaceChange(width, height);
        rsSurfaceNode->SetBounds(borderWidth_, borderWidth_, width, height);
    }
    auto backgroundColor = want.GetStringParam(OHOS::AppExecFwk::Constants::PARAM_FORM_TRANSPARENCY_KEY);
    if (backgroundColor_ != backgroundColor) {
        backgroundColor_ = backgroundColor;
        uiContent_->SetFormBackgroundColor(backgroundColor_);
    }
    if (renderingMode_ == AppExecFwk::Constants::RenderingMode::SINGLE_COLOR) {
        HILOG_INFO("AttachUIContent SetFormBackgroundColor #00FFFFFF");
        uiContent_->SetFormBackgroundColor(TRANSPARENT_COLOR);
    }

    uiContent_->Foreground();
}

void FormRenderer::GetRectRelativeToWindow(int32_t &top, int32_t &left) const
{
    if (!formRendererDelegate_) {
        HILOG_ERROR("form renderer delegate is null!");
        return;
    }
    formRendererDelegate_->OnGetRectRelativeToWindow(top, left);
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
} // namespace Ace
} // namespace OHOS
