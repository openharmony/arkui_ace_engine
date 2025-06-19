/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_OSAL_IMAGE_ANALYZER_MANAGER_H
#define FOUNDATION_ACE_ADAPTER_OHOS_OSAL_IMAGE_ANALYZER_MANAGER_H

#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/event/key_event.h"
#include "interfaces/inner_api/ace/ai/image_analyzer.h"

namespace OHOS::Ace {
class ImageAnalyzerAdapter;
}

struct ACE_FORCE_EXPORT MovingPhotoAnalyzerInfo {
    std::string uri = "";
    int64_t frameTimestamp = 0;
    float contentWidth = 0.0f;
    float contentHeight = 0.0f;
};

namespace OHOS::Ace {
class ACE_FORCE_EXPORT ImageAnalyzerManager : public AceType {
    DECLARE_ACE_TYPE(ImageAnalyzerManager, AceType);
public:
    ImageAnalyzerManager(const RefPtr<NG::FrameNode>& frameNode, ImageAnalyzerHolder holder);
    ~ImageAnalyzerManager()
    {
        ReleaseImageAnalyzer();
    }
    
    bool IsSupportImageAnalyzerFeature();
    void CreateAnalyzerOverlay(const RefPtr<OHOS::Ace::PixelMap>& pixelMap, const NG::OffsetF& offset = { 0.0f, 0.0f });
    void CreateMovingPhotoAnalyzerOverlay(const RefPtr<OHOS::Ace::PixelMap>& pixelMap, MovingPhotoAnalyzerInfo info);
    void UpdateAnalyzerOverlay(const RefPtr<OHOS::Ace::PixelMap>& pixelMap, const NG::OffsetF& offset = { 0.0f, 0.0f });
    void UpdateMovingPhotoAnalyzerOverlay(const RefPtr<OHOS::Ace::PixelMap>& pixelMap, MovingPhotoAnalyzerInfo info);
    void UpdateAnalyzerOverlayLayout();
    void UpdateAnalyzerUIConfig(const RefPtr<NG::GeometryNode>& geometryNode, const PixelMapInfo& info = {});
    void DestroyAnalyzerOverlay();
    void ReleaseImageAnalyzer();
    void SetImageAnalyzerConfig(void* config);
    void SetImageAnalyzerCallback(OnAnalyzedCallback& callback);
    void SetImageAIOptions(void* options);
    bool IsOverlayCreated();
    void UpdatePressOverlay(const RefPtr<OHOS::Ace::PixelMap>& pixelMap, int offsetX, int offsetY, int rectWidth,
        int rectHeight, int pointX, int pointY, OnTextSelectedCallback callback);
    void UpdateOverlayTouchInfo(int touchPointX, int touchPointY, TouchType touchType);
    void UpdateOverlayStatus(bool status, int offsetX, int offsetY, int rectWidth, int rectHeight);
    void UpdateAIButtonConfig(AIButtonConfig config);
    virtual void UpdateKeyEvent(KeyEvent keyEvent);
    void UpdateOverlayActiveStatus(bool status);
    void SetNotifySelectedCallback(OnNotifySelectedStatusCallback&& callback);
    void SetOnCanPlayCallback(OnCanPlayCallback&& callback);

private:
    bool UpdateVideoConfig(const PixelMapInfo& info);
    bool NeedUpdateOverlayOffset();

    WeakPtr<NG::FrameNode> frameNode_;
    ImageAnalyzerHolder holder_;
    ImageAnalyzerInnerConfig analyzerUIConfig_;
    std::shared_ptr<ImageAnalyzerAdapter> imageAnalyzerAdapter_;
    void* overlayData_ = nullptr;

    bool isAnalyzerOverlayBuild_ = false;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_ADAPTER_OHOS_OSAL_IMAGE_ANALYZER_MANAGER_H