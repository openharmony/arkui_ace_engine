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

#include "core/components/camera/camera.h"

#include <algorithm>
#include <cstring>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <securec.h>
#include <sstream>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "base/log/log.h"
#include "display_type.h"
#include "meta_data.h"

#include "core/image/image_cache.h"

namespace OHOS::Ace {
namespace {

const char SURFACE_BUFFER_SIZE[] = "surface_buffer_size";
const char IS_SUCESS[] = "isSucceed";
const char ERROR_CODE[] = "errorcode";
const char PHOTO_PATH[] = "uri";
const char NULL_STRING[] = "";
const char DEFAULT_CATCH_PATH[] = "data/data/";

const char SURFACE_STRIDE_ALIGNMENT[] = "surface_stride_Alignment";
const char SURFACE_WIDTH[] = "surface_width";
const char SURFACE_HEIGHT[] = "surface_height";
const char SURFACE_FORMAT[] = "surface_format";
const char SURFACE_USAGE[] = "surface_usage";
const char SURFACE_TIMEOUT[] = "surface_timeout";
const char SURFACE_SIZE[] = "surface_size";
const char REGION_POSITION_X[] = "region_position_x";
const char REGION_POSITION_Y[] = "region_position_y";
const char REGION_WIDTH[] = "region_width";
const char REGION_HEIGHT[] = "region_height";

constexpr int32_t DEFAULT_WIDTH = 1920;
constexpr int32_t DEFAULT_HEIGHT = 1080;
constexpr int32_t SURFACE_STRIDE_ALIGNMENT_VAL = 8;
constexpr int32_t PREVIEW_SURFACE_WIDTH = 720;
constexpr int32_t PREVIEW_SURFACE_HEIGHT = 480;
constexpr int32_t MAX_DURATION = 36000;
constexpr int32_t SAMPLE_RATE = 48000;
constexpr int32_t FRAME_RATE = 30;
constexpr int32_t RATE = 4096;
constexpr double FPS = 30;

inline void SaveFileData(const std::string& filePath, const char &buffer, uint32_t size, std::string& path)
{
    LOGI("Start saving picture");
    struct timeval tv = {};
    gettimeofday(&tv, nullptr);
    struct tm *ltm = localtime(&tv.tv_sec);
    if (ltm != nullptr) {
        std::ostringstream ss("Capture_");
        ss << "Capture" << ltm->tm_hour << "-" << ltm->tm_min << "-" << ltm->tm_sec << ".jpg";
        path = filePath + ss.str();
        std::ofstream pic(path, std::ofstream::out | std::ofstream::trunc);
        pic.write(&buffer, size);
        pic.close();
    }
}

inline int32_t GetRecordFile(const std::string filePath, std::string& path)
{
    LOGI("Camera GetRecordFile.");
    struct timeval tv = {};
    gettimeofday(&tv, nullptr);
    struct tm *ltm = localtime(&tv.tv_sec);
    int32_t fd = -1;
    if (ltm != nullptr) {
        std::ostringstream ss("Capture_");
        ss << "Record" << ltm->tm_hour << "-" << ltm->tm_min << "-" << ltm->tm_sec << ".mp4";
        path = filePath + ss.str();
        fd = open(path.c_str(), O_WRONLY | O_CREAT | O_CLOEXEC | O_TRUNC, S_IRUSR | S_IWUSR);
    }
    return fd;
}
}

void FrameCallback::OnFrameFinished(const Media::Camera &camera,
                                    const Media::FrameConfig &frameConfig,
                                    const Media::FrameResult &frameResult)
{
    if (((Media::FrameConfig &)frameConfig).GetFrameConfigType() != Media::FRAME_CONFIG_CAPTURE) {
        LOGI("FrameCallback: FrameConfigType is not FRAME_CONFIG_CAPTURE");
        return;
    }

    const auto surfaceList = ((Media::FrameConfig &)frameConfig).GetSurfaces();
    if (surfaceList.empty()) {
        return;
    }

    for (Surface *surface : surfaceList) {
        sptr<SurfaceBuffer> buffer;
        int32_t flushFence;
        int64_t timestamp;
        OHOS::Rect damage;
        SurfaceError ret = surface->AcquireBuffer(buffer, flushFence, timestamp, damage);
        if (ret == SURFACE_ERROR_OK) {
            char *virtAddr = static_cast<char *>(buffer->GetVirAddr());
            if (virtAddr != nullptr) {
                int32_t bufferSize = stoi(surface->GetUserData(SURFACE_BUFFER_SIZE));
                std::string path;
                SaveFileData(cacheFilePath_, *virtAddr, bufferSize, path);
                OnTakePhoto(true, path);
            }
            surface->ReleaseBuffer(buffer, -1);
        }
        delete surface;
    }
    delete &frameConfig;
}

void FrameCallback::OnFrameError(const Media::Camera &camera,
                                 const Media::FrameConfig &frameConfig,
                                 int32_t errorCode,
                                 const Media::FrameResult &frameResult)
{
    OnTakePhoto(false, NULL_STRING);
    delete &frameConfig;
    LOGI("Camera: OnFrameError errorCode is %{public}d", errorCode);
}

void FrameCallback::AddTakePhotoListener(TakePhotoListener&& listener)
{
    takePhotoListener_ = std::move(listener);
}

void FrameCallback::OnTakePhoto(bool isSucces, std::string info)
{
    LOGI("Camera:FrameCallback OnTakePhoto %{public}d  %{public}s--", isSucces, info.c_str());
    if (!takePhotoListener_) {
        return;
    }

    std::map<std::string, std::string> result;
    if (isSucces) {
        result[IS_SUCESS] = "1";
        result[PHOTO_PATH] = info;
    } else {
        result[IS_SUCESS] = "0";
        result[ERROR_CODE] = info;
    }
    takePhotoListener_(result);
    result.clear();
}

void FrameCallback::SetCatchFilePath(std::string cacheFilePath)
{
    cacheFilePath_ = cacheFilePath;
}

void CameraCallback::OnCreated(const Media::Camera &camera)
{
    LOGI("Camera OnCreated.");
    auto config = Media::CameraConfig::CreateCameraConfig();
    config->SetFrameStateCallback(frameCallback_, eventHandler_);

    ((Media::Camera &) camera).Configure(*config);
    camera_ = (Media::Camera *) &camera;
    isReady_ = true;
    if (hasCallPreView_) {
        StartPreview();
    }
}

void CameraCallback::OnCreateFailed(const std::string cameraId, int32_t errorCode)
{
    LOGE("CameraCallback: OnCreate Failed!");
}

Media::Recorder *CameraCallback::CreateRecorder()
{
    LOGI("Camera CreateRecorder start.");
    int ret = 0;
    int32_t channelCount = 1;
    AudioCodecFormat audioFormat = AAC_LC;
    AudioSourceType inputSource = AUDIO_MIC;
    int32_t audioEncodingBitRate = SAMPLE_RATE;
    Media::VideoSourceType source = Media::VIDEO_SOURCE_SURFACE_ES;
    int32_t sourceId = 0;
    int32_t audioSourceId = 0;
    int32_t width = DEFAULT_WIDTH;
    int32_t height = DEFAULT_HEIGHT;
    VideoCodecFormat encoder = HEVC;

    Media::Recorder *recorder = new Media::Recorder();
    if ((ret = recorder->SetVideoSource(source, sourceId)) != Media::SUCCESS) {
        LOGE("SetVideoSource failed. ret= %{private}d.", ret);
        delete recorder;
        return nullptr;
    }
    if ((ret = recorder->SetVideoEncoder(sourceId, encoder)) != Media::SUCCESS) {
        LOGE("SetVideoEncoder failed. ret= %{private}d.", ret);
        delete recorder;
        return nullptr;
    }
    if ((ret = recorder->SetOutputFormat(Media::FORMAT_MPEG_4)) != Media::SUCCESS) {
        LOGE("SetOutputFormat failed. ret= %{private}d.", ret);
        delete recorder;
        return nullptr;
    }
    if ((ret = recorder->SetVideoSize(sourceId, width, height)) != Media::SUCCESS) {
        LOGE("SetVideoSize failed. ret= %{private}d.", ret);
        delete recorder;
        return nullptr;
    }
    if ((ret = recorder->SetVideoFrameRate(sourceId, FRAME_RATE)) != Media::SUCCESS) {
        LOGE("SetVideoFrameRate failed. ret= %{private}d.", ret);
        delete recorder;
        return nullptr;
    }
    if ((ret = recorder->SetVideoEncodingBitRate(sourceId, RATE)) != Media::SUCCESS) {
        LOGE("SetVideoEncodingBitRate failed. ret= %{private}d.", ret);
        delete recorder;
        return nullptr;
    }
    if ((ret = recorder->SetCaptureRate(sourceId, FPS)) != Media::SUCCESS) {
        LOGE("SetCaptureRate failed. ret= %{private}d.", ret);
        delete recorder;
        return nullptr;
    }
    if ((ret = recorder->SetAudioSource(inputSource, audioSourceId)) != Media::SUCCESS) {
        LOGE("SetAudioSource failed. ret= %{private}d.", ret);
        delete recorder;
        return nullptr;
    }
    if ((ret = recorder->SetAudioEncoder(audioSourceId, audioFormat)) != Media::SUCCESS) {
        LOGE("SetAudioEncoder failed. ret= %{private}d.", ret);
        delete recorder;
        return nullptr;
    }
    if ((ret = recorder->SetAudioSampleRate(audioSourceId, SAMPLE_RATE)) != Media::SUCCESS) {
        LOGE("SetAudioSampleRate failed. ret= %{private}d.", ret);
        delete recorder;
        return nullptr;
    }
    if ((ret = recorder->SetAudioChannels(audioSourceId, channelCount)) != Media::SUCCESS) {
        LOGE("SetAudioChannels failed. ret= %{private}d.", ret);
        delete recorder;
        return nullptr;
    }
    if ((ret = recorder->SetAudioEncodingBitRate(audioSourceId, audioEncodingBitRate)) != Media::SUCCESS) {
        LOGE("SetAudioEncodingBitRate failed. ret= %{private}d.", ret);
        delete recorder;
        return nullptr;
    }
    if ((ret = recorder->SetMaxDuration(MAX_DURATION)) != Media::SUCCESS) { // 36000s=10h
        LOGE("SetAudioEncodingBitRate failed. ret= %{private}d.", ret);
        delete recorder;
        return nullptr;
    }
    LOGI("Camera CreateRecorder success.");
    return recorder;
}

int CameraCallback::PrepareRecorder()
{
    LOGI("Camera PrepareRecorder.");
    if (camera_ == nullptr) {
        LOGE("Camera is not ready.");
        return -1;
    }
    if (recorder_ == nullptr) {
        recorder_ = CreateRecorder();
    }
    if (recorder_ == nullptr) {
        LOGE("Camera: Recorder not available.");
        return -1;
    }
    if (recordFileId_ == -1) {
        recordFileId_ = GetRecordFile(cacheFilePath_, recordPath_);
    }
    if (recordFileId_ == -1) {
        LOGE("Camera: Create fd failed.");
        return -1;
    }
    return Media::SUCCESS;
}

void CameraCallback::CloseRecorder()
{
    if (recordState_ == State::STATE_RUNNING) {
        if (recorder_ != nullptr) {
            recorder_->Stop(true);
            delete recorder_;
            recorder_ = nullptr;
        }

        if (recordFileId_ != -1) {
            onRecord(true, recordPath_);
        }
        recordFileId_ = -1;
        recordState_ = State::STATE_IDLE;
    }
}

void CameraCallback::StartPreview()
{
    if (!isReady_) {
        LOGE("Not ready for StartPreview.");
        hasCallPreView_ = true;
        return;
    }

    LOGI("Camera StartPreview.");
    if (camera_ == nullptr) {
        LOGE("Camera is null.");
        return;
    }

    auto context = context_.Upgrade();
    if (!context) {
        LOGE("Camera:fail to get context to create Camera");
        return;
    }

    if (previewState_ == State::STATE_RUNNING) {
        LOGE("Camera is already previewing.");
        return;
    }

    if (!subWindow_) {
        OHOS::WindowConfig config;
        memset_s(&config, sizeof(OHOS::WindowConfig), 0, sizeof(OHOS::WindowConfig));
        config.height = windowSize_.Width();
        config.width = windowSize_.Height();
        config.format = PIXEL_FMT_RGBA_8888;
        config.pos_x = windowOffset_.GetX();
        config.pos_y = windowOffset_.GetY();
        config.subwindow = true;
        config.type = WINDOW_TYPE_VIDEO;

        subWindow_ = OHOS::WindowManager::GetInstance()->CreateSubWindow(context->GetWindowId(), &config);
        subWindow_->GetSurface()->SetQueueSize(10);
    }

    previewSurface_ = subWindow_->GetSurface();
    previewSurface_->SetUserData(SURFACE_STRIDE_ALIGNMENT, std::to_string(SURFACE_STRIDE_ALIGNMENT_VAL));
    previewSurface_->SetUserData(SURFACE_FORMAT, std::to_string(PIXEL_FMT_YCBCR_422_SP));
    previewSurface_->SetUserData(SURFACE_WIDTH, std::to_string(PREVIEW_SURFACE_WIDTH));
    previewSurface_->SetUserData(SURFACE_HEIGHT, std::to_string(PREVIEW_SURFACE_HEIGHT));
    previewSurface_->SetUserData(REGION_WIDTH, std::to_string(windowSize_.Width()));
    previewSurface_->SetUserData(REGION_HEIGHT, std::to_string(windowSize_.Height()));
    previewSurface_->SetUserData(REGION_POSITION_X, std::to_string(windowOffset_.GetX()));
    previewSurface_->SetUserData(REGION_POSITION_Y, std::to_string(windowOffset_.GetY()));

    Media::FrameConfig *preViewFrameConfig = new Media::FrameConfig(Media::FRAME_CONFIG_PREVIEW);
    preViewFrameConfig->AddSurface(*previewSurface_);
    int32_t ret = camera_->TriggerLoopingCapture(*preViewFrameConfig);
    if (ret != 0) {
        delete preViewFrameConfig;
        LOGE("Camera start preview failed. ret= %{private}d.", ret);
        return;
    }
    previewState_ = State::STATE_RUNNING;
    hasCallPreView_ = false;
    LOGI("Camera start preview succeed.");
}

void CameraCallback::StartRecord()
{
    LOGI("Camera Record start.");
    if (recordState_ == State::STATE_RUNNING) {
        LOGE("Camera is already recording.");
        return;
    }
    int ret = PrepareRecorder();
    if (ret != Media::SUCCESS) {
        LOGE("Camera PrepareRecorder failed.");
        CloseRecorder();
        onRecord(false, NULL_STRING);
        return;
    }
    ret = recorder_->SetOutputFile(recordFileId_);
    if (ret != Media::SUCCESS) {
        LOGE("Camera SetOutputPath failed. ret= %{private}d", ret);
        CloseRecorder();
        onRecord(false, NULL_STRING);
        return;
    }
    ret = recorder_->Prepare();
    if (ret != Media::SUCCESS) {
        LOGE("Prepare failed. ret= %{private}d", ret);
        CloseRecorder();
        onRecord(false, NULL_STRING);
        return;
    }
    ret = recorder_->Start();
    if (ret != Media::SUCCESS) {
        LOGE("recorder start failed. ret= %{private}d", ret);
        CloseRecorder();
        onRecord(false, NULL_STRING);
        return;
    }
    Surface *recorderSurface = (recorder_->GetSurface(0)).get();

    int queueSize = 10;
    int oneKilobytes = 1024;
    int surfaceSize = oneKilobytes * oneKilobytes;
    int usage = HBM_USE_CPU_READ | HBM_USE_CPU_WRITE | HBM_USE_MEM_DMA;
    recorderSurface->SetUserData(SURFACE_WIDTH, std::to_string(DEFAULT_WIDTH));
    recorderSurface->SetUserData(SURFACE_HEIGHT, std::to_string(DEFAULT_HEIGHT));
    recorderSurface->SetQueueSize(queueSize);
    recorderSurface->SetUserData(SURFACE_SIZE, std::to_string(surfaceSize));
    recorderSurface->SetUserData(SURFACE_STRIDE_ALIGNMENT, "8");
    recorderSurface->SetUserData(SURFACE_FORMAT, std::to_string(PIXEL_FMT_RGBA_8888));
    recorderSurface->SetUserData(SURFACE_USAGE, std::to_string(usage));
    recorderSurface->SetUserData(SURFACE_TIMEOUT, "0");

    Media::FrameConfig *recordFrameConfig = new Media::FrameConfig(Media::FRAME_CONFIG_RECORD);
    recordFrameConfig->AddSurface(*recorderSurface);
    ret = camera_->TriggerLoopingCapture(*recordFrameConfig);
    if (ret != 0) {
        delete recordFrameConfig;
        CloseRecorder();
        LOGE("Camera start recording failed. ret= %{private}d", ret);
        onRecord(false, NULL_STRING);
        return;
    }
    recordState_ = State::STATE_RUNNING;
    LOGI("Camera start recording succeed.");
}

void CameraCallback::Capture(Size photoSize)
{
    LOGI("Camera capture start.");
    if (camera_ == nullptr) {
        LOGE("Camera is not ready.");
        return;
    }
    captureSurface_ = Surface::CreateSurfaceAsConsumer();
    if (captureSurface_ == nullptr) {
        LOGE("Camera CreateSurface failed.");
        return;
    }

    auto refSurface = captureSurface_;
    sptr<IBufferConsumerListener> listener = new SurfaceListener();
    captureSurface_->RegisterConsumerListener(listener);

    int usage = HBM_USE_CPU_READ | HBM_USE_CPU_WRITE | HBM_USE_MEM_DMA;
    captureSurface_->SetUserData(SURFACE_WIDTH, std::to_string(DEFAULT_WIDTH));
    captureSurface_->SetUserData(SURFACE_HEIGHT, std::to_string(DEFAULT_HEIGHT));
    captureSurface_->SetUserData(SURFACE_STRIDE_ALIGNMENT, "8");
    captureSurface_->SetUserData(SURFACE_FORMAT, std::to_string(PIXEL_FMT_RGBA_8888));
    captureSurface_->SetUserData(SURFACE_USAGE, std::to_string(usage));
    captureSurface_->SetUserData(SURFACE_TIMEOUT, "0");

    Media::FrameConfig *captureFrameConfig = new Media::FrameConfig(Media::FRAME_CONFIG_CAPTURE);
    captureFrameConfig->AddSurface(*refSurface);
    int32_t ret = camera_->TriggerSingleCapture(*captureFrameConfig);
    if (MEDIA_OK != ret) {
        delete captureFrameConfig;
        LOGE("Camera: Capture faile. ret = %{private}d", ret);
        return;
    }
    LOGI("Camera capture end.");
}

void CameraCallback::Stop(bool isClosePreView)
{
    if (camera_ != nullptr) {
        camera_->StopLoopingCapture();
    }

    if (recordState_ == State::STATE_RUNNING) {
        CloseRecorder();
    }
    recordState_ = State::STATE_IDLE;
    previewState_ = State::STATE_IDLE;
    if (isClosePreView) {
        LOGI("CameraCallback: Destroy subWindow.");
        subWindow_.reset();
    }
}

void CameraCallback::AddTakePhotoListener(TakePhotoListener&& listener)
{
    frameCallback_.AddTakePhotoListener(std::move(listener));
}

void CameraCallback::AddErrorListener(ErrorListener&& listener)
{
    onErrorListener_ = std::move(listener);
}

void CameraCallback::AddRecordListener(RecordListener&& listener)
{
    onRecordListener_ = std::move(listener);
}

void CameraCallback::SetCatchFilePath(std::string cacheFilePath)
{
    cacheFilePath_ = cacheFilePath;
    frameCallback_.SetCatchFilePath(cacheFilePath_);
}

void CameraCallback::onError()
{
    if (onErrorListener_) {
        onErrorListener_(NULL_STRING, NULL_STRING);
    }
}

void CameraCallback::onRecord(bool isSucces, std::string info)
{
    LOGI("CameraCallback: onRecord callback.");
    if (!onRecordListener_) {
        return;
    }

    std::map<std::string, std::string> result;
    if (isSucces) {
        result[IS_SUCESS] = "1";
        result[PHOTO_PATH] = info;
    } else {
        result[IS_SUCESS] = "0";
        result[ERROR_CODE] = info;
    }
    onRecordListener_(result);
}

void CameraCallback::OnCameraSizeChange(int32_t width, int32_t height)
{
    LOGE("CameraCallback:OnCameraSizeChange  %{public}d %{public}d %{public}p-", width, height, subWindow_.get());
    if (subWindow_) {
        subWindow_->SetSubWindowSize(width, height);
    }
    windowSize_.SetWidth(width);
    windowSize_.SetWidth(height);
}

void CameraCallback::OnCameraOffsetChange(int32_t x, int32_t y)
{
    if (subWindow_) {
        subWindow_->Move(x, y);
    }
    windowOffset_.SetX(x);
    windowOffset_.SetX(y);
}

void Camera::Release()
{
    LOGI("Camera: Release!");
    Stop(true);
    Media::Camera *camera = const_cast<Media::Camera *>(cameraCallback_.GetCameraInstance());
    if (camera != nullptr) {
        camera->StopLoopingCapture();
        camera = nullptr;
    }
}

void Camera::CreateCamera()
{
    if (cameraKit_ == nullptr) {
        LOGE("Camera: post render failed due to null native object!");
        return;
    }

    std::list<std::string> camList = cameraKit_->GetCameraIds();
    if (camList.empty()) {
        LOGE("Camera: empty camera list!");
        return;
    }

    const std::string cameraId = camList.front();
    const Media::CameraAbility *ability = cameraKit_->GetCameraAbility(cameraId);
    if (ability == nullptr) {
        LOGE("Camera: get camera ability failed!");
        return;
    }

    cameraKit_->CreateCamera(cameraId, cameraCallback_, cameraCallback_.GetEventHandler());
}

void Camera::Create(const std::function<void()>& onCreate)
{
    LOGI("Camera: Create start");
    cameraKit_ = Media::CameraKit::GetInstance();
    LOGI("Camera:CameraKit Create");

    std::string cacheFilePath = ImageCache::GetImageCacheFilePath();
    if (cacheFilePath.empty()) {
        cacheFilePath = DEFAULT_CATCH_PATH;
    }
    cameraCallback_.SetCatchFilePath(cacheFilePath);
    cameraCallback_.SetPipelineContext(context_);

    CreateCamera();

    if (onCreate) {
        onCreate();
    }
    LOGI("Camera:Create end");
}

void Camera::Stop(bool isClosePreView)
{
    LOGI("Camera:Stop");
    cameraCallback_.Stop(isClosePreView);
}

void Camera::TakePhoto(Size photoSize)
{
    LOGI("Camera:TakePhoto");
    cameraCallback_.Capture(photoSize);
}

void Camera::StartPreview()
{
    LOGI("Camera:StartPreview");
    cameraCallback_.StartPreview();
}

void Camera::StartRecord()
{
    LOGI("Camera:StartRecord");
    cameraCallback_.StartRecord();
}

void Camera::AddTakePhotoListener(TakePhotoListener&& listener)
{
    cameraCallback_.AddTakePhotoListener(std::move(listener));
}

void Camera::AddErrorListener(ErrorListener&& listener)
{
    cameraCallback_.AddErrorListener(std::move(listener));
}

void Camera::AddRecordListener(RecordListener&& listener)
{
    cameraCallback_.AddRecordListener(std::move(listener));
}

void Camera::OnCameraSizeChange(int32_t width, int32_t height)
{
    cameraCallback_.OnCameraSizeChange(width, height);
}

void Camera::OnCameraOffsetChange(int32_t x, int32_t y)
{
    cameraCallback_.OnCameraOffsetChange(x, y);
}

} // namespace OHOS::Ace
