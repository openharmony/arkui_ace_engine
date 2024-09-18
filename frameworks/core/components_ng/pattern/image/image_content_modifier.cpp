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

#include "core/components_ng/pattern/image/image_content_modifier.h"
#include "core/components_ng/render/image_painter.h"
#include "core/common/ace_application_info.h"

namespace OHOS::Ace::NG {
ImageContentModifier::ImageContentModifier()
{
    sensitive_ = AceType::MakeRefPtr<PropertyBool>(false);
    AttachProperty(sensitive_);
    size_ = AceType::MakeRefPtr<PropertySizeF>(SizeF());
    AttachProperty(size_);
    canvasImageWrapper_ = AceType::MakeRefPtr<PropertyCanvasImageModifierWrapper>(CanvasImageModifierWrapper());
    AttachProperty(canvasImageWrapper_);
}

void ImageContentModifier::onDraw(DrawingContext& drawingContext)
{
    CHECK_NULL_VOID(canvasImageWrapper_);
    auto canvasImage = canvasImageWrapper_->Get().GetCanvasImage();
    CHECK_NULL_VOID(canvasImage);
    ImagePainter imagePainter(canvasImage);
    if (!sensitive_->Get()) {
        imagePainter.DrawImage(drawingContext.canvas, {}, size_->Get());
    }
}
} // namespace OHOS::Ace::NG
