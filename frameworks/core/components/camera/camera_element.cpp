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

#include "core/components/camera/camera_element.h"

#include <sstream>

#include "core/components/camera/camera_component.h"
#include "core/components/video/render_texture.h"

namespace OHOS::Ace {
namespace {

const char CALLBACK_COMPLETE[] = "complete";
const char IS_SUCESS[] = "isSucceed";
const char PHOTO_PATH[] = "uri";
const char NULL_STRING[] = "";
const char ERROR_MSG[] = "errormsg";
const char ERROR_CODE[] = "errorcode";

inline std::string GetStringFromMap(const std::map<std::string, std::string>& map, std::string key)
{
    auto iter = map.find(key);
    if (iter != map.end()) {
        return iter->second;
    }
    return NULL_STRING;
}

} // namespace

CameraElement::~CameraElement()
{
    ReleasePlatformResource();
}

void CameraElement::ReleasePlatformResource()
{
    StopPreview();
    if (camera_) {
        camera_->Release();
        camera_.Reset();
    }
}

void CameraElement::Prepare(const WeakPtr<Element>& parent)
{
    auto themeManager = GetThemeManager();
    if (!themeManager) {
        return;
    }
    auto cameraComponent = AceType::DynamicCast<CameraComponent>(component_);
    theme_ = themeManager->GetTheme<CameraTheme>();
    if (cameraComponent) {
        InitEvent(cameraComponent);
        SetMethodCall(cameraComponent);
        CreatePlatformResource();
    }

    RenderElement::Prepare(parent);
    if (renderNode_) {
        auto renderTexture = AceType::DynamicCast<RenderTexture>(renderNode_);
        renderTexture->SetTextureSizeChange(
            [weak = WeakClaim(this)](int64_t textureId, int32_t textureWidth, int32_t textureHeight) {
                auto cameraElement = weak.Upgrade();
                if (cameraElement) {
                    cameraElement->OnTextureSize(textureId, textureWidth, textureHeight);
                }
            });
        renderTexture->SetHiddenChangeEvent(
            [weak = WeakClaim(this)](bool hidden) {
                auto cameraElement = weak.Upgrade();
                if (cameraElement) {
                    cameraElement->HiddenChange(hidden);
                }
            });
        renderTexture->SetTextureOffsetChange(
            [weak = WeakClaim(this)](int64_t textureId, int32_t x, int32_t y) {
                auto cameraElement = weak.Upgrade();
                if (cameraElement) {
                    cameraElement->OnTextureOffset(textureId, x, y);
                }
            });
    }
}

void CameraElement::HiddenChange(bool hidden)
{
    if (hidden) {
        ReleasePlatformResource();
    } else {
        CreatePlatformResource();
    }
}

void CameraElement::InitEvent(const RefPtr<CameraComponent>& cameraComponent)
{
    if (!cameraComponent->GetErrorEventId().IsEmpty()) {
        onError_ = AceAsyncEvent<void(const std::string&)>::Create(cameraComponent->GetErrorEventId(), context_);
    }
}

void CameraElement::OnTextureSize(int64_t textureId, int32_t textureWidth, int32_t textureHeight)
{
    LOGI("CameraElement::OnTextureSize");
    if (camera_) {
        LOGE("CameraElement:OnTextureSize  %{public}d %{public}d ", textureWidth, textureHeight);
        camera_->OnCameraSizeChange(textureWidth, textureHeight);
    }
}

void CameraElement::OnTextureOffset(int64_t textureId, int32_t x, int32_t y)
{
    LOGI("CameraElement::OnTextureOffset");
    if (camera_) {
        camera_->OnCameraOffsetChange(x, y);
        LOGE("Camera:OnTextureOffset %{public}d %{public}d", x, y);
        StartPreview();
    }
}

void CameraElement::CreatePlatformResource()
{
    ReleasePlatformResource();

    auto context = context_.Upgrade();
    if (!context) {
        LOGE("fail to get context");
        return;
    }

    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this)] {
            auto cameraElement = weak.Upgrade();
            if (cameraElement) {
                cameraElement->CreateCamera();
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void CameraElement::CreateCamera()
{
    LOGI("CameraElement::CreateCamera");
    camera_ = AceType::MakeRefPtr<Camera>(context_, eventHdlr_);
    camera_->Create(nullptr);
    InitListener();
}

void CameraElement::SetMethodCall(const RefPtr<CameraComponent>& cameraComponent)
{
    auto cameraController = cameraComponent->GetCameraController();
    if (cameraController) {
        auto context = context_.Upgrade();
        if (!context) {
            return;
        }
        auto uiTaskExecutor =
            SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        cameraController->SetTakePhotoImpl(
            [weak = WeakClaim(this), uiTaskExecutor](
                const TakePhotoParams& params) {
                    uiTaskExecutor.PostTask([weak, params] {
                        auto cameraElement = weak.Upgrade();
                        if (cameraElement) {
                            cameraElement->TakePhoto(params);
                        }
                    });
        });
        cameraController->SetStartRecordImpl(
            [weak = WeakClaim(this), uiTaskExecutor]() {
                    uiTaskExecutor.PostTask([weak] {
                        auto cameraElement = weak.Upgrade();
                        if (cameraElement) {
                            cameraElement->StartRecord();
                        }
                    });
        });

        cameraController->SetCloseRecorderImpl(
            [weak = WeakClaim(this), uiTaskExecutor](
                const std::string& params) {
                    uiTaskExecutor.PostTask([weak, params] {
                        auto cameraElement = weak.Upgrade();
                        if (cameraElement) {
                            cameraElement->CloseRecorder(params);
                        }
                    });
        });
    }
}

void CameraElement::InitListener()
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }

    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    auto takePhotoListener = [weak = WeakClaim(this), uiTaskExecutor](
        const std::map<std::string, std::string> result) {
            uiTaskExecutor.PostTask([&weak, result] {
                auto camera = weak.Upgrade();
                if (camera) {
                    camera->OnTakePhotoCallBack(result);
                }
            });
    };

    auto onError = [weak = WeakClaim(this), uiTaskExecutor](const std::string& errorcode, const std::string& errormsg) {
        uiTaskExecutor.PostTask([&weak, errorcode, errormsg] {
            auto camera = weak.Upgrade();
            if (camera) {
                camera->OnError(errorcode, errormsg);
            }
        });
    };

    auto recorderCallBack = [weak = WeakClaim(this), uiTaskExecutor](
        const std::map<std::string, std::string> result) {
            uiTaskExecutor.PostTask([&weak, result] {
                auto camera = weak.Upgrade();
                if (camera) {
                    camera->OnRecorderCallBack(result);
                }
            });
    };

    if (camera_) {
        camera_->AddTakePhotoListener(takePhotoListener);
        camera_->AddErrorListener(onError);
        camera_->AddRecordListener(recorderCallBack);
    }
}

void CameraElement::OnTakePhotoCallBack(const std::map<std::string, std::string>& result)
{
    std::string callbackId;
    if (GetStringFromMap(result, IS_SUCESS) == "1" && !callbackIds_.success.empty()) {
        std::string param = std::string("{\"")
                                .append(PHOTO_PATH)
                                .append("\":\"file://")
                                .append(GetStringFromMap(result, PHOTO_PATH))
                                .append("\"}");
        ExecuteJsCallback(callbackIds_.success, param);
    } else if (GetStringFromMap(result, IS_SUCESS) != "1" && !callbackIds_.fail.empty()) {
        std::string param = std::string("{\"")
                                .append(ERROR_MSG)
                                .append("\":\"")
                                .append(GetStringFromMap(result, ERROR_MSG))
                                .append("\", \"")
                                .append(ERROR_CODE)
                                .append("\":\"")
                                .append(GetStringFromMap(result, ERROR_CODE))
                                .append("\"}");
        ExecuteJsCallback(callbackIds_.fail, param);
    }
    if (!callbackIds_.complete.empty()) {
        std::string param = std::string("{\"").append(CALLBACK_COMPLETE).append("\":\"\"}");
        ExecuteJsCallback(callbackIds_.complete, param);
    }
}

void CameraElement::OnError(const std::string& errorcode, const std::string& errormsg)
{
    if (onError_) {
        std::string param = std::string("\"error\",{\"")
                                .append(ERROR_MSG)
                                .append("\":\"")
                                .append(errormsg)
                                .append("\", \"")
                                .append(ERROR_CODE)
                                .append("\":\"")
                                .append(errorcode)
                                .append("\"}");
        onError_(param);
    }
}

void CameraElement::TakePhoto(const TakePhotoParams& params)
{
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("fail to get context");
        return;
    }

    callbackIds_.clear();
    callbackIds_ = params;
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this)] {
            auto cameraElement = weak.Upgrade();
            if (cameraElement) {
                cameraElement->TakePhoto(Size());
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void CameraElement::OnRecorderCallBack(const std::map<std::string, std::string>& result)
{
    if (recorderBackId_.empty()) {
        return;
    }

    std::string param = std::string("{\"arguments\":[");
    if (GetStringFromMap(result, IS_SUCESS) == "1") {
        param.append("{\"")
            .append(PHOTO_PATH)
            .append("\":\"file://")
            .append(GetStringFromMap(result, PHOTO_PATH))
            .append("\"}],\"method\":\"success\"}");
        ExecuteJsCallback(recorderBackId_, param);
    } else if (GetStringFromMap(result, IS_SUCESS) != "1") {
        param.append("{\"")
            .append(ERROR_MSG)
            .append("\":\"")
            .append(GetStringFromMap(result, ERROR_MSG))
            .append("\", \"")
            .append(ERROR_CODE)
            .append("\":\"")
            .append(GetStringFromMap(result, ERROR_CODE))
            .append("\"}],\"method\":\"fail\"}");
        ExecuteJsCallback(recorderBackId_, param);
    }

    std::string complete = std::string("{\"arguments\":[{\"")
        .append(CALLBACK_COMPLETE)
        .append("\":\"\"}],\"method\":\"complete\"}");
    ExecuteJsCallback(recorderBackId_, complete);
}

void CameraElement::StartPreview()
{
    if (camera_ && !isPreViewing_) {
        camera_->StartPreview();
        isPreViewing_ = true;
    }
}

void CameraElement::StopPreview()
{
    if (camera_ && isPreViewing_) {
        camera_->Stop(true);
        isPreViewing_ = true;
    }
}

void CameraElement::TakePhoto(const Size& size)
{
    if (camera_) {
        camera_->TakePhoto(size);
    }
}

void CameraElement::StartRecord()
{
    if (camera_ && !isRecording_) {
        camera_->StartRecord();
        isRecording_ = true;
    }
}

void CameraElement::CloseRecorder(const std::string& params)
{
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("fail to get context");
        return;
    }

    if (camera_ && isRecording_) {
        recorderBackId_ = params;

        context->GetTaskExecutor()->PostTask(
            [weak = WeakClaim(this)] {
                auto cameraElement = weak.Upgrade();
                if (cameraElement) {
                    cameraElement->CloseRecorder();
                }
            },
            TaskExecutor::TaskType::PLATFORM);
        isRecording_ = false;
    }
}

void CameraElement::CloseRecorder()
{
    if (camera_) {
        LOGI("CameraElement:CloseRecorder Task");
        camera_->Stop(false);
    }
}

void CameraElement::ExecuteJsCallback(const std::string& callbackId, const std::string& result)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->SendCallbackMessageToFrontend(callbackId, result);
    LOGI("CameraElement: ExecuteJsCallback %{public}s %{public}s", callbackId.c_str(), result.c_str());
}

} // namespace OHOS::Ace
