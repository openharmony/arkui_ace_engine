/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CANVAS_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CANVAS_PAINT_METHOD_H

#include <memory>

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/canvas/custom_paint_paint_method.h"
#include "core/components_ng/pattern/canvas/offscreen_canvas_pattern.h"

namespace OHOS::Ace::NG {
class CanvasPaintMethod;
using TaskFunc = std::function<void(CanvasPaintMethod&)>;
using OnModifierUpdateFunc = std::function<void(void)>;
class CanvasPaintMethod : public CustomPaintPaintMethod {
    DECLARE_ACE_TYPE(CanvasPaintMethod, CustomPaintPaintMethod);
public:
    CanvasPaintMethod() = default;
    CanvasPaintMethod(RefPtr<CanvasModifier> contentModifier, const RefPtr<FrameNode>& frameNode);
    ~CanvasPaintMethod() override = default;

    void GetFastTaskPool();
    void UpdateContentModifier(PaintWrapper* paintWrapper) override;
    void UpdateRecordingCanvas(float width, float height);

    void SetCustomTextType();
    void PushTask(const TaskFunc& task);
    bool HasTask() const;
    void FlushTask();

    void FlushUITasks()
    {
        CHECK_EQUAL_VOID(HasTask(), false);
        auto context = context_.Upgrade();
        if (context) {
            context->FlushUITasks();
        }
    }

    double GetWidth()
    {
        return lastLayoutSize_.Width();
    }

    double GetHeight()
    {
        return lastLayoutSize_.Height();
    }

    void SetOnModifierUpdateFunc(OnModifierUpdateFunc&& func)
    {
        onModifierUpdate_ = std::move(func);
    }

    void FireOnModifierUpdateFunc()
    {
        CHECK_NULL_VOID(onModifierUpdate_);
        onModifierUpdate_();
    }

    void SetRSCanvasCallback(std::function<void(RSCanvas*, double, double)>& callback)
    {
        canvasCallback_ = callback;
    }
    void FireRSCanvasCallback(double width, double height)
    {
        CHECK_NULL_VOID(canvasCallback_);
        canvasCallback_(rsCanvas_.get(), width, height);
    }

    void CloseImageBitmap(const std::string& src);
    void DrawPixelMap(RefPtr<PixelMap> pixelMap, const Ace::CanvasImage& canvasImage);
    void DrawPixelMapInternal(RefPtr<PixelMap> pixelMap, const Ace::CanvasImage& canvasImage);
    void CalculatePixelMapRect(
        const Ace::CanvasImage& canvasImage, int32_t width, int32_t height, RSRect& srcRect, RSRect& dstRect);

    std::unique_ptr<Ace::ImageData> GetImageData(double left, double top, double width, double height);
    void GetImageData(const std::shared_ptr<Ace::ImageData>& imageData);
#ifdef PIXEL_MAP_SUPPORTED
    void TransferFromImageBitmap(const RefPtr<PixelMap>& pixelMap);
#endif
    std::string ToDataURL(const std::string& type, const double quality);
    bool DrawBitmap(RefPtr<RenderContext> renderContext, RSBitmap& currentBitmap);
    std::string GetJsonData(const std::string& path);

    void Reset();
    TextDirection GetSystemDirection() override;
    std::string GetDumpInfo();
    void SetHostCustomNodeName();
    void GetSimplifyDumpInfo(std::unique_ptr<JsonValue>& json);
private:
    int32_t GetId() const;
#ifndef ACE_UNITTEST
    void ConvertTxtStyle(const TextStyle& textStyle, Rosen::TextStyle& txtStyle) override;
#endif
    std::list<TaskFunc> tasks_;

#ifndef ACE_UNITTEST
    RefPtr<Ace::ImageObject> imageObj_ = nullptr;
#endif
    OnModifierUpdateFunc onModifierUpdate_;
    std::function<void(RSCanvas*, double, double)> canvasCallback_ = nullptr;
    WeakPtr<FrameNode> frameNode_;
    bool needMarkDirty_ = true;
    // To record the host custom component name of the current canvas.
    std::string customNodeName_;

    ACE_DISALLOW_COPY_AND_MOVE(CanvasPaintMethod);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CANVAS_PAINT_METHOD_H
