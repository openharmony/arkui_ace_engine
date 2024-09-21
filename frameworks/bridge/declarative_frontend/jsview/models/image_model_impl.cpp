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

#include "bridge/declarative_frontend/jsview/models/image_model_impl.h"

#include "bridge/declarative_frontend/jsview/models/view_abstract_model_impl.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/image/image_component.h"
#include "core/components/image/image_event.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_utils.h"

namespace OHOS::Ace::Framework {

void ImageModelImpl::SetAlt(const ImageSourceInfo& src)
{
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (image) {
        image->SetAlt(src.GetSrc());
    }
}

void ImageModelImpl::SetBorder(const Border& border)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto decoration = box->GetFrontDecoration();
    if (!decoration) {
        decoration = AceType::MakeRefPtr<Decoration>();
        box->SetFrontDecoration(decoration);
    }
    decoration->SetBorder(border);
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (image) {
        image->SetBorder(border);
    }
}

void ImageModelImpl::SetBackBorder()
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto decoration = box->GetBackDecoration();
    if (!decoration) {
        decoration = AceType::MakeRefPtr<Decoration>();
        box->SetBackDecoration(decoration);
    }
    SetBorder(decoration->GetBorder());
}

void ImageModelImpl::SetBlur(double blur)
{
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (image) {
        image->SetBlur(blur);
    }
}

void ImageModelImpl::SetImageFit(ImageFit value)
{
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (image) {
        image->SetImageFit(value);
    }
}

void ImageModelImpl::SetMatchTextDirection(bool value)
{
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (image) {
        image->SetMatchTextDirection(value);
    }
}

void ImageModelImpl::SetFitOriginSize(bool value)
{
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (image) {
        image->SetFitMaxSize(!value);
    }
}

void ImageModelImpl::SetOnComplete(std::function<void(const LoadImageSuccessEvent& info)>&& callback)
{
    auto onCompleteEvent = EventMarker([func = std::move(callback)](const BaseEventInfo* info) {
        auto eventInfo = TypeInfoHelper::DynamicCast<LoadImageSuccessEvent>(info);
        func(*eventInfo);
    });
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    image->SetLoadSuccessEvent(onCompleteEvent);
}

void ImageModelImpl::SetOnError(std::function<void(const LoadImageFailEvent& info)>&& callback)
{
    auto onErrorEvent = EventMarker([func = std::move(callback)](const BaseEventInfo* info) {
        auto eventInfo = TypeInfoHelper::DynamicCast<LoadImageFailEvent>(info);
        func(*eventInfo);
    });
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    image->SetLoadFailEvent(onErrorEvent);
}

void ImageModelImpl::SetSvgAnimatorFinishEvent(std::function<void()>&& callback)
{
    auto onFinishEvent = EventMarker([func = std::move(callback)]() { func(); });
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    image->SetSvgAnimatorFinishEvent(onFinishEvent);
}

void ImageModelImpl::Create(const ImageInfoConfig& imageInfoConfig, RefPtr<PixelMap>& pixmap)
{
    RefPtr<ImageComponent> image =
        AceType::MakeRefPtr<OHOS::Ace::ImageComponent>(imageInfoConfig.src ? *imageInfoConfig.src : "");
    image->SetBundleInfo(imageInfoConfig.bundleName, imageInfoConfig.moduleName);
    ViewStackProcessor::GetInstance()->ClaimElementId(image);
    image->SetUseSkiaSvg(false);
    ViewStackProcessor::GetInstance()->Push(image);
    JSInteractableView::SetFocusable(false);
    JSInteractableView::SetFocusNode(true);
    if (!pixmap) {
        return;
    }

#if defined(PIXEL_MAP_SUPPORTED)
    image->SetPixmap(pixmap);
#endif
}

void ImageModelImpl::SetImageSourceSize(const std::pair<Dimension, Dimension>& size)
{
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    image->SetImageSourceSize(size);
}

void ImageModelImpl::SetImageFill(const Color& color)
{
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    image->SetImageFill(color);
}

void ImageModelImpl::SetImageInterpolation(ImageInterpolation iterpolation)
{
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    image->SetImageInterpolation(iterpolation);
}

void ImageModelImpl::SetImageRepeat(ImageRepeat imageRepeat)
{
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    image->SetImageRepeat(imageRepeat);
}

void ImageModelImpl::SetImageRenderMode(ImageRenderMode imageRenderMode)
{
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    image->SetImageRenderMode(imageRenderMode);
}

bool ImageModelImpl::IsSrcSvgImage()
{
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    return image && image->IsSrcSvgImage();
}

void ImageModelImpl::SetAutoResize(bool autoResize)
{
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (image) {
        image->SetAutoResize(autoResize);
    }
}

void ImageModelImpl::SetSyncMode(bool syncMode)
{
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (image) {
        image->SetSyncMode(syncMode);
    }
}

void ImageModelImpl::SetColorFilterMatrix(const std::vector<float>& matrix)
{
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (image) {
        image->SetColorFilterMatrix(matrix);
    }
}

void ImageModelImpl::SetOnDragStart(NG::OnDragStartFunc&& onDragStart)
{
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (image) {
        image->SetOnDragStartId(ViewAbstractModelImpl::ToDragFunc(std::move(onDragStart)));
    }
}

void ImageModelImpl::SetOnDragEnter(NG::OnDragDropFunc&& onDragStartId)
{
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (image) {
        image->SetOnDragEnterId(std::move(onDragStartId));
    }
}

void ImageModelImpl::SetOnDragLeave(NG::OnDragDropFunc&& onDragStartId)
{
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (image) {
        image->SetOnDragLeaveId(std::move(onDragStartId));
    }
}

void ImageModelImpl::SetOnDragMove(NG::OnDragDropFunc&& onDragMoveId)
{
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (image) {
        image->SetOnDragMoveId(std::move(onDragMoveId));
    }
}

void ImageModelImpl::SetOnDrop(NG::OnDragDropFunc&& onDropId)
{
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (image) {
        image->SetOnDropId(std::move(onDropId));
    }
}

void ImageModelImpl::SetCopyOption(const CopyOptions& copyOption)
{
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (image) {
        image->SetCopyOption(copyOption);
    }
}

bool ImageModelImpl::UpdateDragItemInfo(DragItemInfo& itemInfo)
{
    auto component = ViewStackProcessor::GetInstance()->Finish();
    if (!component) {
        LOGE("Custom component is null.");
        return false;
    }
    itemInfo.customComponent = component;
    return true;
}

bool ImageModelImpl::GetIsAnimation()
{
    return false;
}

} // namespace OHOS::Ace::Framework
