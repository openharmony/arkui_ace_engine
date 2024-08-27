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

#include "bridge/cj_frontend/frontend/cj_frontend_abstract.h"

#include "base/i18n/localization.h"
#include "base/subwindow/subwindow_manager.h"
#include "bridge/cj_frontend/frontend/cj_frontend_loader.h"
#include "bridge/cj_frontend/runtime/cj_runtime_delegate.h"
#include "bridge/common/accessibility/accessibility_node_manager.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/common/font_manager.h"

using namespace OHOS::Ace::NG;
using namespace OHOS::Ace;

namespace OHOS::Ace {
namespace {
std::string FA_DEFAULT_APP_LIB_PATH = "/data/storage/el1/bundle/libs/arm64/libohos_app_cangjie_default.so";
constexpr int32_t TOAST_TIME_MAX = 10000;    // ms
constexpr int32_t TOAST_TIME_DEFAULT = 1500; // ms
constexpr int32_t CALLBACK_ERRORCODE_CANCEL = 1;
constexpr int32_t CALLBACK_DATACODE_ZERO = 0;

// helper function to run OverlayManager task
// ensures that the task runs in subwindow instead of main Window
void MainWindowOverlay(std::function<void(RefPtr<NG::OverlayManager>)>&& task, const std::string& name)
{
    auto currentId = Container::CurrentId();
    ContainerScope scope(currentId);
    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    context->GetTaskExecutor()->PostTask(
        [task = std::move(task), weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            task(overlayManager);
        },
        TaskExecutor::TaskType::UI, name);
}
} // namespace

namespace Framework {
void FrontendLoader::SetCJBinPath(const std::string& src)
{
    FA_DEFAULT_APP_LIB_PATH = src;
}
}

#if defined(PREVIEW)
void CJFrontendAbstract::TransferJsResponseDataPreview(int32_t callbackId, int32_t code,
    ResponseData responseData) const
{}
#endif

CJFrontendAbstract::~CJFrontendAbstract()
{
    LOGD("CJFrontendAbstract destroyed.");
}

bool CJFrontendAbstract::Initialize(FrontendType type, const RefPtr<OHOS::Ace::TaskExecutor>& taskExecutor)
{
    if (type != FrontendType::DECLARATIVE_CJ) {
        LOGE("CJFrontendAbstract Initialize failed, FrontendType only accept DECLARATIVE_CJ");
        return false;
    }
    LOGD("CJFrontendAbstract initialize begin.");
    taskExecutor_ = taskExecutor;
    manifestParser_ = AceType::MakeRefPtr<Framework::ManifestParser>();
    accessibilityManager_ = Framework::AccessibilityNodeManager::Create();

    type_ = type;
    InternalInitialize();
    if (!pageRouterManager_) {
        LOGE("InternalInitialize must initialize pageRouterManager_");
        return false;
    }
    return true;
}

void CJFrontendAbstract::FlushReload()
{
    if (!Container::IsCurrentUseNewPipeline()) {
        LOGW("not support old pipeline");
        return;
    }
    pageRouterManager_->FlushReload();
}

void CJFrontendAbstract::RebuildAllPages()
{
    CHECK_NULL_VOID(pageRouterManager_);
    auto url = pageRouterManager_->GetCurrentPageUrl();
    pageRouterManager_->Clear();
    pageRouterManager_->RunPage(url, "");
}

void CJFrontendAbstract::NavigatePage(uint8_t type, const PageTarget& target, const std::string& params)
{
    switch (static_cast<NavigatorType>(type)) {
        case NavigatorType::PUSH:
            PushPage(target.url, params);
            break;
        case NavigatorType::REPLACE:
            ReplacePage(target.url, params);
            break;
        case NavigatorType::BACK:
            Back(target.url, params);
            break;
        default:
            LOGE("Navigator type is invalid!");
            Back(target.url, params);
    }
}

bool CJFrontendAbstract::OnBackPressed()
{
    return pageRouterManager_->PopWithExitCheck();
}

void CJFrontendAbstract::OnShow()
{
    foregroundFrontend_ = true;
    pageRouterManager_->OnShowCurrent();
}

void CJFrontendAbstract::OnHide()
{
    foregroundFrontend_ = false;
    pageRouterManager_->OnHideCurrent();
}

void CJFrontendAbstract::Destroy()
{
    LOGD("CJFrontendAbstract Destroy begin.");
}

bool CJFrontendAbstract::LoadAppLibrary()
{
    return Framework::CJRuntimeDelegate::GetInstance()->LoadCJLibrary(
        FA_DEFAULT_APP_LIB_PATH.c_str());
}

void CJFrontendAbstract::AttachPipelineContext(const RefPtr<PipelineBase>& context)
{
    pipelineContextHolder_.Attach(context);
    auto jsAccessibility = AceType::DynamicCast<Framework::AccessibilityNodeManager>(accessibilityManager_);
    jsAccessibility->SetPipelineContext(context);
    jsAccessibility->InitializeCallback();
}

void CJFrontendAbstract::SetAssetManager(const RefPtr<AssetManager>& assetManager)
{
    assetManager_ = assetManager;
}

UIContentErrorCode CJFrontendAbstract::RunPage(const std::string& url, const std::string& params)
{
    LOGI("CJFrontendAbstract::RunPage start: %{public}s", url.c_str());
    if (!isStageModel_) {
        if (!LoadAppLibrary()) {
            TAG_LOGW(AceLogTag::ACE_FORM, "fail to run page due to path url is empty");
            return UIContentErrorCode::NULL_URL;
        }
    }
    InternalRunPage(url, params);
    return UIContentErrorCode::NO_ERRORS;
}

void CJFrontendAbstract::ReplacePage(const std::string& url, const std::string& params)
{
    pageRouterManager_->Replace({ url }, params);
}

void CJFrontendAbstract::PushPage(const std::string& url, const std::string& params)
{
    pageRouterManager_->Push({ url }, params);
}

void CJFrontendAbstract::Back(const std::string& uri, const std::string& params)
{
    pageRouterManager_->BackWithTarget({ uri }, params);
}

void CJFrontendAbstract::CallRouterBack()
{
    pageRouterManager_->Pop();
}

void CJFrontendAbstract::InternalRunPage(const std::string& url, const std::string& params)
{
    LOGI("InternalRunPage %{public}s", url.c_str());
    pageRouterManager_->RunPage(url, params);
}

double CJFrontendAbstract::MeasureText(const MeasureContext& context)
{
    return MeasureUtil::MeasureText(context);
}

Size CJFrontendAbstract::MeasureTextSize(const MeasureContext& context)
{
    LOGI("CJFrontendAbstract::MeasureTextSize start");
    return MeasureUtil::MeasureTextSize(context);
}

void CJFrontendAbstract::ShowToast(
    const std::string& message, int32_t duration, const std::string& bottom, const NG::ToastShowMode& showMode)
{
    int32_t durationTime = std::clamp(duration, TOAST_TIME_DEFAULT, TOAST_TIME_MAX);
    bool isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
    auto task = [durationTime, message, bottom, isRightToLeft, showMode, containerId = Container::CurrentId()](
                    const RefPtr<NG::OverlayManager>& overlayManager) {
        CHECK_NULL_VOID(overlayManager);
        ContainerScope scope(containerId);
        auto toastInfo = NG::ToastInfo { .message = message,
            .duration = durationTime,
            .bottom = bottom,
            .isRightToLeft = isRightToLeft,
            .showMode = showMode,
            .alignment = -1,
            .offset = std::nullopt };
        overlayManager->ShowToast(toastInfo, nullptr);
    };
    MainWindowOverlay(std::move(task), "ArkUIOverlayShowToast");
}

void CJFrontendAbstract::ShowDialog(const std::string& title, const std::string& message,
    const std::vector<ButtonInfo>& buttons, std::function<void(int32_t, int32_t)>&& callback,
    const std::set<std::string>& callbacks)
{
    DialogProperties dialogProperties = { .title = title, .content = message, .buttons = buttons };
    ShowDialogInner(dialogProperties, std::move(callback), callbacks);
}

void CJFrontendAbstract::ShowDialogInner(DialogProperties& dialogProperties,
    std::function<void(int32_t, int32_t)>&& callback, const std::set<std::string>& callbacks)
{
    auto pipelineContext = pipelineContextHolder_.Get();
    LOGI("Dialog IsCurrentUseNewPipeline.");
    dialogProperties.onCancel = [callback, taskExecutor = taskExecutor_] {
        taskExecutor->PostTask(
            [callback]() { callback(CALLBACK_ERRORCODE_CANCEL, CALLBACK_DATACODE_ZERO); }, TaskExecutor::TaskType::JS,
            "CJFroentendShowDialogInner");
    };
    dialogProperties.onSuccess = std::move(callback);
    auto task = [dialogProperties](const RefPtr<NG::OverlayManager>& overlayManager) {
        CHECK_NULL_VOID(overlayManager);
        RefPtr<NG::FrameNode> dialog;
        LOGI("Begin to show dialog ");
        if (dialogProperties.isShowInSubWindow) {
            dialog = SubwindowManager::GetInstance()->ShowDialogNG(dialogProperties, nullptr);
            CHECK_NULL_VOID(dialog);
            if (dialogProperties.isModal) {
                DialogProperties maskarg;
                maskarg.isMask = true;
                maskarg.autoCancel = dialogProperties.autoCancel;
                auto mask = overlayManager->ShowDialog(maskarg, nullptr, false);
                CHECK_NULL_VOID(mask);
                overlayManager->SetMaskNodeId(dialog->GetId(), mask->GetId());
            }
        } else {
            dialog = overlayManager->ShowDialog(
                dialogProperties, nullptr, AceApplicationInfo::GetInstance().IsRightToLeft());
            CHECK_NULL_VOID(dialog);
        }
    };
    MainWindowOverlay(std::move(task), "ArkUIShowDialogInner");
}

void CJFrontendAbstract::ShowActionMenu(const std::string& title, const std::vector<ButtonInfo>& button,
    std::function<void(int32_t, int32_t)>&& callback)
{
    DialogProperties dialogProperties = {
        .title = title,
        .autoCancel = true,
        .isMenu = true,
        .buttons = button,
    };
    ShowActionMenuInner(dialogProperties, button, std::move(callback));
}

void CJFrontendAbstract::ShowActionMenuInner(DialogProperties& dialogProperties, const std::vector<ButtonInfo>& button,
    std::function<void(int32_t, int32_t)>&& callback)
{
    ButtonInfo buttonInfo = { .text = Localization::GetInstance()->GetEntryLetters("common.cancel"), .textColor = "" };
    dialogProperties.buttons.emplace_back(buttonInfo);
    dialogProperties.onCancel = [callback, taskExecutor = taskExecutor_] {
        taskExecutor->PostTask([callback]() { callback(CALLBACK_ERRORCODE_CANCEL, CALLBACK_DATACODE_ZERO); },
            TaskExecutor::TaskType::JS, "CJFroentendShowActionMenuInnerOnCancel");
    };
    dialogProperties.onSuccess = std::move(callback);
    auto context = DynamicCast<NG::PipelineContext>(pipelineContextHolder_.Get());
    auto overlayManager = context ? context->GetOverlayManager() : nullptr;
    taskExecutor_->PostTask(
        [dialogProperties, weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            RefPtr<NG::FrameNode> dialog;
            if (dialogProperties.isShowInSubWindow) {
                dialog = SubwindowManager::GetInstance()->ShowDialogNG(dialogProperties, nullptr);
                CHECK_NULL_VOID(dialog);
                if (dialogProperties.isModal) {
                    DialogProperties maskarg;
                    maskarg.autoCancel = dialogProperties.autoCancel;
                    maskarg.isMask = true;
                    auto mask = overlayManager->ShowDialog(maskarg, nullptr, false);
                    CHECK_NULL_VOID(mask);
                    overlayManager->SetMaskNodeId(dialog->GetId(), mask->GetId());
                }
            } else {
                dialog = overlayManager->ShowDialog(
                    dialogProperties, nullptr, AceApplicationInfo::GetInstance().IsRightToLeft());
                CHECK_NULL_VOID(dialog);
            }
        },
        TaskExecutor::TaskType::UI, "CJFroentendShowActionMenuInner");
}

void CJFrontendAbstract::OpenCustomDialog(const PromptDialogAttr &dialogAttr,
    std::function<void(int32_t)> &&callback)
{
    DialogProperties dialogProperties = {
        .onWillDismiss = dialogAttr.customOnWillDismiss,
        .isShowInSubWindow = dialogAttr.showInSubWindow,
        .isModal = dialogAttr.isModal,
        .isSysBlurStyle = false,
        .customBuilder = dialogAttr.customBuilder,
        .maskRect = dialogAttr.maskRect
    };
#if defined(PREVIEW)
    if (dialogProperties.isShowInSubWindow) {
        LOGW("[Engine Log] Unable to use the SubWindow in the Previewer. Perform this operation on the "
             "emulator or a real device instead.");
        dialogProperties.isShowInSubWindow = false;
    }
#endif
    if (dialogAttr.alignment.has_value()) {
        dialogProperties.alignment = dialogAttr.alignment.value();
    }
    if (dialogAttr.offset.has_value()) {
        dialogProperties.offset = dialogAttr.offset.value();
    }
    if (!Container::IsCurrentUseNewPipeline()) {
        LOGW("not support old pipeline");
        return;
    }
    LOGI("Dialog IsCurrentUseNewPipeline.");
    auto task = [dialogAttr, dialogProperties, callback](const RefPtr<NG::OverlayManager>& overlayManager) mutable {
        CHECK_NULL_VOID(overlayManager);
        LOGI("Begin to open custom dialog ");
        if (dialogProperties.isShowInSubWindow) {
            SubwindowManager::GetInstance()->OpenCustomDialogNG(dialogProperties, std::move(callback));
            if (dialogProperties.isModal) {
                LOGW("temporary not support isShowInSubWindow and isModal");
            }
        } else {
            overlayManager->OpenCustomDialog(dialogProperties, std::move(callback));
        }
    };
    MainWindowOverlay(std::move(task), "ArkUIOpenCustomDialog");
    return;
}

void CJFrontendAbstract::CloseCustomDialog(int32_t id)
{
    auto task = [id](const RefPtr<NG::OverlayManager>& overlayManager) {
        CHECK_NULL_VOID(overlayManager);
        LOGI("begin to close custom dialog.");
        overlayManager->CloseCustomDialog(id);
        SubwindowManager::GetInstance()->CloseCustomDialogNG(id);
    };
    MainWindowOverlay(std::move(task), "ArkUICloseCustomDialog");
    return;
}

void CJFrontendAbstract::RegisterFont(const std::string& familyName, const std::string& familySrc,
    const std::string& bundleName, const std::string& moduleName)
{
    pipelineContextHolder_.Get()->RegisterFont(familyName, familySrc, bundleName, moduleName);
}

VectorStringHandle CJFrontendAbstract::GetSystemFontList()
{
    auto fontList = new std::vector<std::string>;
    pipelineContextHolder_.Get()->GetSystemFontList(*fontList);
    return fontList;
}

NativeOptionFontInfo CJFrontendAbstract::GetSystemFont(const std::string& fontName)
{
    FontInfo fontInfo;
    if (!pipelineContextHolder_.Get()->GetSystemFont(fontName, fontInfo)) {
        return NativeOptionFontInfo {
            .hasValue = false,
            .info = nullptr
        };
    }
    return NativeOptionFontInfo {
        .hasValue = true,
        .info = new NativeFontInfo {
            .path = fontInfo.path.c_str(),
            .postScriptName = fontInfo.postScriptName.c_str(),
            .fullName = fontInfo.fullName.c_str(),
            .family = fontInfo.family.c_str(),
            .subfamily = fontInfo.subfamily.c_str(),
            .weight = fontInfo.weight,
            .width = fontInfo.width,
            .italic = fontInfo.italic,
            .monoSpace = fontInfo.monoSpace,
            .symbolic =  fontInfo.symbolic
        }
    };
}
} // namespace OHOS::Ace
