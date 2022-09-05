/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_IMAGE_HELPER_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_IMAGE_HELPER_H

#include "core/components/image/image_component.h"
#include "core/components/image/image_event.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM)
#include "napi/native_api.h"
#include "native_engine/native_engine.h"
#endif

#include "core/components_ng/pattern/image/image_view.h"

#ifdef USE_QUICKJS_ENGINE
#ifdef __cplusplus
extern "C" {
#endif
#include "third_party/quickjs/quickjs.h"
#ifdef __cplusplus
}
#endif
#endif

namespace OHOS::Ace::Framework {

#define SET_PROP_FOR_NG(propName, propType, propValue)                      \
    do {                                                                    \
        if (Container::IsCurrentUseNewPipeline()) {                         \
            NG::ImageView::Set##propName(static_cast<propType>(propValue)); \
            return;                                                         \
        }                                                                   \
    } while (0);



// ImageModel is essentially the same class as ImageView
// there should be one left in the final implementation

class ImageModel {
public:
    static ImageModel* GetInstance();
    virtual ~ImageModel() {};

    virtual void SetAlt(std::string src) = 0;
    virtual void SetImageFit(int32_t value) = 0;
    virtual void SetMatchTextDirection(bool value) = 0;
    virtual void SetFitMaxSize(bool value) = 0;
    virtual void SetOnComplete(OHOS::Ace::NG::CompleteEvent&& callback) = 0;
    virtual void SetOnError(OHOS::Ace::NG::ErrorEvent&& callback) = 0;
    virtual void SetSvgAnimatorFinishEvent(const OHOS::Ace::EventMarker& callback) = 0;
    virtual void Create(std::string src, bool noPixMap) = 0;
    virtual void SetImageSourceSize(std::pair<Dimension, Dimension> size) = 0;
    virtual void SetImageFill(Color color) = 0;
    virtual void SetImageInterpolation(ImageInterpolation iterpolation) = 0;
    virtual void SetImageRepeat(ImageRepeat imageRepeat) = 0;
    virtual void SetImageRenderMode(ImageRenderMode imageRenderMode) = 0;
    virtual bool IsSrcSvgImage() = 0;
    virtual void SetAutoResize(bool autoResize) = 0;
    virtual void SetSyncMode(bool syncMode) = 0;
    virtual void SetColorFilterMatrix(const std::vector<float>& matrix) = 0;
    virtual void SetOnDragStartId(const OnDragFunc& onDragStartId) = 0;
    virtual void SetOnDragEnterId(const OnDropFunc&  onDragStartId) = 0;
    virtual void SetOnDragLeaveId(const OnDropFunc& onDragStartId) = 0;
    virtual void SetOnDragMoveId(const OnDropFunc& onDragMoveId) = 0;
    virtual void SetOnDropId(const OnDropFunc& onDropId) = 0;
    virtual void SetCopyOption(const CopyOptions& copyOption) = 0;

private:
    static thread_local std::unique_ptr<ImageModel> instance;
};

class ImageModelOG : public ImageModel{
public:
    void SetAlt(std::string src) override
    {
        auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        if (image) {
            image->SetAlt(src);
        }
    }

    void SetImageFit(int32_t value) override
    {
        //SET_PROP_FOR_NG(ObjectFit, ImageFit, value);
        auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        if (image) {
            image->SetImageFit(static_cast<ImageFit>(value));
        }
    }

    void SetMatchTextDirection(bool value) override
    {
        auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        if (image) {
            image->SetMatchTextDirection(value);
        }
    }

    void SetFitMaxSize(bool value) override
    {
        auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        if (image) {
            image->SetFitMaxSize(!value);
        }
    }

    void SetOnComplete(OHOS::Ace::NG::CompleteEvent&& callback) override
    {
        auto onCompleteEvent = EventMarker([func = std::move(callback)](const BaseEventInfo* info)
        {
            auto eventInfo = TypeInfoHelper::DynamicCast<LoadImageSuccessEvent>(info);
            func(*eventInfo);
        });
        auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        image->SetLoadSuccessEvent(onCompleteEvent);
    }

    void SetOnError(OHOS::Ace::NG::ErrorEvent&& callback) override
    {
        auto onErrorEvent = EventMarker([func = std::move(callback)](const BaseEventInfo* info)
        {
            auto eventInfo = TypeInfoHelper::DynamicCast<LoadImageFailEvent>(info);
            func(*eventInfo);
        });
        auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        image->SetLoadFailEvent(onErrorEvent);
    }

    void SetSvgAnimatorFinishEvent(const OHOS::Ace::EventMarker& callback) override
    {
        auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        image->SetSvgAnimatorFinishEvent(callback);
    }

    void Create(std::string src, bool noPixMap) override
    {
        RefPtr<ImageComponent> image = AceType::MakeRefPtr<OHOS::Ace::ImageComponent>(src);
        ViewStackProcessor::GetInstance()->ClaimElementId(image);
        image->SetUseSkiaSvg(false);
        ViewStackProcessor::GetInstance()->Push(image);
        JSInteractableView::SetFocusable(false);
        JSInteractableView::SetFocusNode(true);
        if (noPixMap) {
            return;
        }

    #if defined(IMAGE_SUPPORTED)
        //image->SetPixmap(CreatePixelMapFromNapiValue(info[0]));
    #endif
    }

    void SetImageSourceSize(std::pair<Dimension, Dimension> size) override
    {
        auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        image->SetImageSourceSize(size);
    }

    void SetImageFill(Color color) override
    {
        auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        image->SetImageFill(color);
    }

    void SetImageInterpolation(ImageInterpolation iterpolation) override
    {
        auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        image->SetImageInterpolation(iterpolation);
    }

    void SetImageRepeat(ImageRepeat imageRepeat) override
    {
        auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        image->SetImageRepeat(imageRepeat);
    }

    void SetImageRenderMode(ImageRenderMode imageRenderMode) override
    {
        auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        image->SetImageRenderMode(imageRenderMode);
    }

    bool IsSrcSvgImage() override
    {
        auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        return image && image->IsSrcSvgImage();
    }

    void SetAutoResize(bool autoResize) override
    {
        auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        if (image) {
            image->SetAutoResize(autoResize);
        }
    }

    void SetSyncMode(bool syncMode) override
    {
        auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        if (image) {
            image->SetSyncMode(syncMode);
        }
    }

    void SetColorFilterMatrix(const std::vector<float>& matrix) override
    {
        auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        if (image) {
            image->SetColorFilterMatrix(matrix);
        }
    }

    void SetOnDragStartId(const OnDragFunc& onDragStartId) override
    {
        auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        if (image) {
            image->SetOnDragStartId(onDragStartId);
        }
    }

    void SetOnDragEnterId(const OnDropFunc&  onDragStartId) override
    {
        auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        if (image) {
            image->SetOnDragEnterId(onDragStartId);
        }
    }

    void SetOnDragLeaveId(const OnDropFunc& onDragStartId) override
    {
        auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        if (image) {
            image->SetOnDragLeaveId(onDragStartId);
        }
    }

    void SetOnDragMoveId(const OnDropFunc& onDragMoveId) override
    {
        auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        if (image) {
            image->SetOnDragMoveId(onDragMoveId);
        }
    }

    void SetOnDropId(const OnDropFunc& onDropId) override
    {
        auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        if (image) {
            image->SetOnDropId(onDropId);
        }
    }

    void SetCopyOption(const CopyOptions& copyOption) override
    {
        auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        if (image) {
            image->SetCopyOption(copyOption);
        }
    }
};

class ImageModelNG : public ImageModel{
public:
    void SetAlt(std::string src) override
    {
    }

    void SetImageFit(int32_t value) override
    {
        SET_PROP_FOR_NG(ObjectFit, ImageFit, value);
    }

    void SetMatchTextDirection(bool value) override
    {
    }

    void SetFitMaxSize(bool value) override
    {
    }

    void SetOnComplete(OHOS::Ace::NG::CompleteEvent&& callback) override
    {
        NG::ImageView::SetOnComplete(std::move(callback));
    }

    void SetOnError(OHOS::Ace::NG::ErrorEvent&& callback) override
    {
        NG::ImageView::SetOnError(std::move(callback));
    }

    void SetSvgAnimatorFinishEvent(const OHOS::Ace::EventMarker& callback) override
    {
    }

    void Create(std::string src, bool noPixMap) override
    {
        NG::ImageView::Create(src);
    }

    void SetImageSourceSize(std::pair<Dimension, Dimension> size) override
    {
        NG::ImageView::SetImageSourceSize(size);
    }

    void SetImageFill(Color color) override
    {
    }

    void SetImageInterpolation(ImageInterpolation iterpolation) override
    {
        SET_PROP_FOR_NG(ImageInterpolation, ImageInterpolation, iterpolation);
    }

    void SetImageRepeat(ImageRepeat imageRepeat) override
    {
        SET_PROP_FOR_NG(ImageRepeat, ImageRepeat, imageRepeat);
    }

    void SetImageRenderMode(ImageRenderMode imageRenderMode) override
    {
        SET_PROP_FOR_NG(ImageRenderMode, ImageRenderMode, imageRenderMode);
    }

    bool IsSrcSvgImage() override
    {
        return false;
    }

    void SetAutoResize(bool autoResize) override
    {
        SET_PROP_FOR_NG(AutoResize, bool, autoResize);
    }

    void SetSyncMode(bool syncMode) override
    {
    }

    void SetColorFilterMatrix(const std::vector<float>& matrix) override
    {
    }

    void SetOnDragStartId(const OnDragFunc& onDragStartId) override
    {
    }

    void SetOnDragEnterId(const OnDropFunc&  onDragStartId) override
    {
    }

    void SetOnDragLeaveId(const OnDropFunc& onDragStartId) override
    {
    }

    void SetOnDragMoveId(const OnDropFunc& onDragMoveId) override
    {
    }

    void SetOnDropId(const OnDropFunc& onDropId) override
    {
    }

    void SetCopyOption(const CopyOptions& copyOption) override
    {
    }
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_IMAGE_HELPER_H
