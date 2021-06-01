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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CAMERA_CAMERA_ELEMENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CAMERA_CAMERA_ELEMENT_H

#include "core/components/camera/camera.h"
#include "core/components/camera/camera_component.h"
#include "core/components/camera/camera_theme.h"
#include "core/focus/focus_node.h"
#include "core/pipeline/base/composed_element.h"
#include "core/pipeline/base/render_element.h"

namespace OHOS::Ace {

class CameraElement : public RenderElement, public FocusNode {
    DECLARE_ACE_TYPE(CameraElement, RenderElement, FocusNode);

public:
    using ErrorCallback = std::function<void(const std::string&, const std::string&)>;
    using EventCallback = std::function<void(const std::string&)>;

    CameraElement() = default;
    ~CameraElement() override;

    void Prepare(const WeakPtr<Element>& parent) override;
    void TakePhoto(const TakePhotoParams& params);

    void StartRecord();
    void CloseRecorder(const std::string& params);
    void StartPreview();
    void StopPreview();

private:
    void SetMethodCall(const RefPtr<CameraComponent>& cameraComponent);
    void OnTextureSize(int64_t textureId, int32_t textureWidth, int32_t textureHeight);
    void OnTextureOffset(int64_t textureId, int32_t x, int32_t y);
    void CreatePlatformResource();
    void ReleasePlatformResource();
    void CreateCamera();
    void InitListener();
    void OnTakePhotoCallBack(const std::map<std::string, std::string>& result);
    void ExecuteJsCallback(const std::string& callbackId, const std::string& result);
    void InitEvent(const RefPtr<CameraComponent>& cameraComponent);
    void OnError(const std::string& errorcode, const std::string& errormsg);
    void HiddenChange(bool hidden);

    void OnRecorderCallBack(const std::map<std::string, std::string>& result);
    void TakePhoto(const Size& size);
    void CloseRecorder();

    EventCallback onTakePhotoEvent_;
    EventCallback onError_;
    TakePhotoParams callbackIds_;
    RefPtr<CameraTheme> theme_;

    RefPtr<Camera> camera_;
    std::string recorderBackId_;
    bool isRecording_ = false;
    bool isPreViewing_ = false;
    Media::EventHandler eventHdlr_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CAMERA_CAMERA_ELEMENT_H
