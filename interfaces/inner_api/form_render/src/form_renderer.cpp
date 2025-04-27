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
constexpr int64_t DEFAULT_TIMESTAMP = -1;
constexpr int64_t DELAY_SET_DEFAULT_TIMESTAMP_TASK = 50; //ms
constexpr int64_t DELAY_RESIZE_FORM_AGAIN_TASK = 100; //ms
constexpr int32_t RSSURFACENODE_PROPERTIES_WIDTH_INDEX = 2;
constexpr int32_t RSSURFACENODE_PROPERTIES_HEIGHT_INDEX = 3;
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
    HILOG_INFO("InitUIContent width = %{public}f , height = %{public}f, borderWidth = %{public}f. \
        formJsInfo.formData.size = %{public}zu. formJsInfo.imageDataMap.size = %{public}zu.",
        width_, height_, borderWidth_,
        formJsInfo.formData.size(),
        formJsInfo.imageDataMap.size());
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

    auto rsSurfaceNode = uiContent_->GetFormRootNode();
    if (rsSurfaceNode == nullptr) {
        return;
    }
    HandleTimeStampAndSetBounds(rsSurfaceNode);
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
    proxy_ = want.GetRemoteObject(FORM_RENDERER_PROCESS_ON_ADD_SURFACE);
    renderingMode_ = (AppExecFwk::Constants::RenderingMode)want.GetIntParam(
        OHOS::AppExecFwk::Constants::PARAM_FORM_RENDERINGMODE_KEY, 0);
    enableBlurBackground_ = want.GetBoolParam(OHOS::AppExecFwk::Constants::PARAM_FORM_ENABLE_BLUR_BACKGROUND_KEY,
        false);
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
    if (formRendererDelegate_ != nullptr && uiContent_ != nullptr) {
        auto rsSurfaceNode = uiContent_->GetFormRootNode();
        if (rsSurfaceNode != nullptr) {
            HILOG_INFO("Form OnSurfaceRelease!");
            formRendererDelegate_->OnSurfaceRelease(rsSurfaceNode->GetId());
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
    auto rsSurfaceNode = uiContent_->GetFormRootNode();
    if (rsSurfaceNode == nullptr) {
        HILOG_ERROR("rsSurfaceNode is nullptr.");
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
        lastBorderWidth_ = borderWidth_;
        std::shared_ptr<EventHandler> eventHandler = eventHandler_.lock();
        rsSurfaceNode->SetBounds(borderWidth_, borderWidth_, resizedWidth, resizedHeight);
        HILOG_INFO(
            "UpdateFormSize after setbounds, rsSurfaceNode width: %{public}f, height: %{public}f",
            rsSurfaceNode->GetStagingProperties().GetBounds().data_[RSSURFACENODE_PROPERTIES_WIDTH_INDEX],
            rsSurfaceNode->GetStagingProperties().GetBounds().data_[RSSURFACENODE_PROPERTIES_HEIGHT_INDEX]);
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
    } else {
        CheckWhetherNeedResizeFormAgain(borderWidth, resizedWidth, resizedHeight);
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
            HILOG_ERROR("EventHandle - SetRenderDelegate error  checkFlag is false");
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
        HILOG_INFO(
            "AttachUIContent after setbounds, rsSurfaceNode width: %{public}f, height: %{public}f",
            rsSurfaceNode->GetStagingProperties().GetBounds().data_[RSSURFACENODE_PROPERTIES_WIDTH_INDEX],
            rsSurfaceNode->GetStagingProperties().GetBounds().data_[RSSURFACENODE_PROPERTIES_HEIGHT_INDEX]);
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

void FormRenderer::HandleTimeStampAndSetBounds(std::shared_ptr<Rosen::RSSurfaceNode> rsSurfaceNode)
{
    int64_t timeStamp = static_cast<int64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count());
    std::shared_ptr<EventHandler> eventHandler = eventHandler_.lock();
    SetRunFormPageInnerTimeStamp(timeStamp);

    if (eventHandler) {
        auto task = [weak = weak_from_this()]() {
            auto formRenderer = weak.lock();
            if (formRenderer) {
                formRenderer->SetRunFormPageInnerTimeStamp(DEFAULT_TIMESTAMP);
            } else {
                HILOG_WARN("HandleTimeStampAndSetBounds, formRenderer is nullptr");
            }
        };
        eventHandler->PostTask(task, DELAY_SET_DEFAULT_TIMESTAMP_TASK);
    }

    rsSurfaceNode->SetBounds(round(borderWidth_), round(borderWidth_), round(width_ - borderWidth_ * DOUBLE),
        round(height_ - borderWidth_ * DOUBLE));
    HILOG_INFO(
        "HandleTimeStampAndSetBounds after setbounds, rsSurfaceNode width: %{public}f, height: %{public}f",
        rsSurfaceNode->GetStagingProperties().GetBounds().data_[RSSURFACENODE_PROPERTIES_WIDTH_INDEX],
        rsSurfaceNode->GetStagingProperties().GetBounds().data_[RSSURFACENODE_PROPERTIES_HEIGHT_INDEX]);
}

void FormRenderer::CheckWhetherNeedResizeFormAgain(float borderWidth, float width, float height)
{
    int64_t timeStamp = static_cast<int64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count());
    int64_t runFormPageInnerTimeStamp = GetRunFormPageInnerTimeStamp();
    SetRunFormPageInnerTimeStamp(DEFAULT_TIMESTAMP);
    if (timeStamp - runFormPageInnerTimeStamp > DELAY_SET_DEFAULT_TIMESTAMP_TASK) {
        return;
    }
    std::shared_ptr<EventHandler> eventHandler = eventHandler_.lock();
    if (eventHandler == nullptr) {
        HILOG_ERROR("CheckWhetherNeedResizeFormAgain, eventHandler is nullptr!");
        return;
    }
    auto task = [weak = weak_from_this(), borderWidth, resizedWidth = width, resizedHeight = height]() {
        auto formRenderer = weak.lock();
        if (formRenderer == nullptr) {
            HILOG_WARN("CheckWhetherNeedResizeFormAgain, formRenderer is nullptr");
            return;
        }
        formRenderer->ResizeFormAgain(borderWidth, resizedWidth, resizedHeight);
    };
    eventHandler->PostTask(task, DELAY_RESIZE_FORM_AGAIN_TASK);
}

void FormRenderer::ResizeFormAgain(float borderWidth, float width, float height)
{
    if (uiContent_ == nullptr) {
        HILOG_ERROR("uiContent_ is null");
        return;
    }
    auto rsSurfaceNode = uiContent_->GetFormRootNode();
    if (rsSurfaceNode == nullptr) {
        HILOG_ERROR("rsSurfaceNode is nullptr.");
        return;
    }
    uiContent_->SetFormWidth(width);
    uiContent_->SetFormHeight(height);
    uiContent_->OnFormSurfaceChange(width, height);
    rsSurfaceNode->SetBounds(borderWidth, borderWidth, width, height);
    HILOG_INFO(
        "ResizeFormAgain after setbounds, rsSurfaceNode width: %{public}f, height: %{public}f",
        rsSurfaceNode->GetStagingProperties().GetBounds().data_[RSSURFACENODE_PROPERTIES_WIDTH_INDEX],
        rsSurfaceNode->GetStagingProperties().GetBounds().data_[RSSURFACENODE_PROPERTIES_HEIGHT_INDEX]);
}

int64_t FormRenderer::GetRunFormPageInnerTimeStamp()
{
    return runFormPageInnerTimeStamp_;
}

void FormRenderer::SetRunFormPageInnerTimeStamp(int64_t timeStamp)
{
    runFormPageInnerTimeStamp_ = timeStamp;
}
} // namespace Ace
} // namespace OHOS
