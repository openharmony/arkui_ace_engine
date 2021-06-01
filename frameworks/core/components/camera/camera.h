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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CAMERA_CAMERA_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CAMERA_CAMERA_H

#include <list>
#include "core/components/camera/camera_component.h"
#include "core/components/common/layout/constants.h"

#include "camera_kit.h"
#include "recorder.h"
#include "window_manager.h"

namespace OHOS::Ace {

using TakePhotoListener = std::function<void(const std::map<std::string, std::string>&)>;
using ErrorListener = std::function<void(const std::string&, const std::string&)>;
using RecordListener = std::function<void(const std::map<std::string, std::string>&)>;

constexpr int32_t TEMPORARY_WINDOW_SIZE = 480;

enum State : int32_t {
    STATE_IDLE,
    STATE_RUNNING,
    STATE_BUTT
};

class FrameCallback final : public Media::FrameStateCallback {
public:
    ACE_DISALLOW_COPY_AND_MOVE(FrameCallback);
    FrameCallback() = default;
    ~FrameCallback() = default;

    void AddTakePhotoListener(TakePhotoListener&& listener);
    void SetCatchFilePath(std::string cacheFilePath);

protected:
    void OnFrameFinished(const Media::Camera &camera,
                        const Media::FrameConfig &frameConfig,
                        const Media::FrameResult &frameResult) override;
    void OnFrameError(const Media::Camera &camera,
                    const Media::FrameConfig &frameConfig,
                    int32_t errorCode,
                    const Media::FrameResult &frameResult) override;

private:
    void OnTakePhoto(bool isSucces, std::string info);
    TakePhotoListener takePhotoListener_;
    std::string cacheFilePath_;
};

class CameraCallback : public Media::CameraStateCallback {
public:
    ACE_DISALLOW_COPY_AND_MOVE(CameraCallback);

    explicit CameraCallback(Media::EventHandler &eventHdlr) : eventHandler_(eventHdlr)
    {}
    ~CameraCallback()
    {
        Stop(true);
    }

    const Media::Camera *GetCameraInstance()
    {
        return camera_;
    }

    Media::EventHandler& GetEventHandler()
    {
        return eventHandler_;
    }

    void SetPipelineContext(const WeakPtr<PipelineContext>& context)
    {
        context_ = context;
    }

    void Stop(bool isClosePreView);
    void Capture(Size photoSize);
    void StartPreview();
    void StartRecord();

    void AddTakePhotoListener(TakePhotoListener&& listener);
    void AddErrorListener(ErrorListener&& listener);
    void AddRecordListener(RecordListener&& listener);
    void SetCatchFilePath(std::string cacheFilePath);
    void OnCameraSizeChange(int32_t width, int32_t height);
    void OnCameraOffsetChange(int32_t x, int32_t y);

protected:
    void OnCreated(const Media::Camera &camera) override;
    void OnCreateFailed(const std::string cameraId, int32_t errorCode) override;
    void OnReleased(const Media::Camera &camera) override {}
    void CloseRecorder();

private:
    int PrepareRecorder();
    Media::Recorder *CreateRecorder();
    void onError();
    void onRecord(bool isSucces, std::string info);

    Media::Camera *camera_ = nullptr;
    Media::Recorder *recorder_ = nullptr;
    sptr<Surface> previewSurface_;
    Media::EventHandler& eventHandler_;

    ErrorListener onErrorListener_;
    RecordListener onRecordListener_;
    FrameCallback frameCallback_;
    int32_t recordFileId_ = -1;
    std::string recordPath_;
    std::string cacheFilePath_;

    std::unique_ptr<OHOS::SubWindow> subWindow_;
    WeakPtr<PipelineContext> context_;
    sptr<Surface> captureSurface_;
    Size windowSize_ = Size(TEMPORARY_WINDOW_SIZE, TEMPORARY_WINDOW_SIZE);
    Offset windowOffset_ = Offset(0, 0);

    bool isReady_ = false;
    bool hasCallPreView_ = false;

    State previewState_ = State::STATE_IDLE;
    State recordState_ = State::STATE_IDLE;
};

class SurfaceListener : public IBufferConsumerListener {
public:
    void OnBufferAvailable() override
    {
        LOGI("Camera SurfaceListener OnBufferAvailable");
    }
};

class Camera : public virtual AceType {
    DECLARE_ACE_TYPE(Camera, AceType);

public:
    Camera(const WeakPtr<PipelineContext> &context, Media::EventHandler &eventHdlr)
        : context_(context), cameraCallback_(eventHdlr) {}
    ~Camera() override = default;

    void Release();
    void Create(const std::function<void()>& onCreate);

    void Stop(bool isClosePreView);
    void TakePhoto(Size photoSize);
    void StartPreview();
    void StartRecord();

    void OnCameraSizeChange(int32_t width, int32_t height);
    void OnCameraOffsetChange(int32_t x, int32_t y);

    void AddTakePhotoListener(TakePhotoListener&& listener);
    void AddErrorListener(ErrorListener&& listener);
    void AddRecordListener(RecordListener&& listener);

private:
    void CreateCamera();
    WeakPtr<PipelineContext> context_;

    TakePhotoListener takePhotoListener_;
    ErrorListener onErrorListener_;
    RecordListener onRecordListener_;

    CameraCallback cameraCallback_;
    std::unique_ptr<OHOS::Window> window_;
    Media::CameraKit *cameraKit_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CAMERA_CAMERA_H
