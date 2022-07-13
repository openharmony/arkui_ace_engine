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

#include "core/components_ng/pattern/image/image_layout_algorithm.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

std::optional<SizeF> ImageLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    if (imageObject_) {
        LOGD("already has image object");
        return ProcessContentSize(contentConstraint, imageObject_);
    }
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, contentConstraint.selfIdealSize);
    auto imageLayoutProperty = DynamicCast<ImageLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(imageLayoutProperty, contentConstraint.selfIdealSize);
    auto imageInfo = imageLayoutProperty->GetImageSourceInfo();
    if (!imageInfo) {
        LOGE("fail to get image info");
        return contentConstraint.selfIdealSize;
    }
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_RETURN(pipeline, contentConstraint.selfIdealSize);
    // TODO: add adapter for flutter.
    auto* currentDartState = flutter::UIDartState::Current();
    CHECK_NULL_RETURN(currentDartState, contentConstraint.selfIdealSize);
    auto renderTaskHolder = MakeRefPtr<FlutterRenderTaskHolder>(currentDartState->GetSkiaUnrefQueue(),
        currentDartState->GetIOManager(), currentDartState->GetTaskRunners().GetIOTaskRunner());
    ImageProvider::FetchImageObject(imageInfo.value(), successCallback_, uploadSuccessCallback_, failedCallback_,
        pipeline, false, false, false, renderTaskHolder, onBackgroundTaskPostCallback_);
    return contentConstraint.selfIdealSize;
}

SizeF ImageLayoutAlgorithm::ProcessContentSize(
    const LayoutConstraintF& contentConstraint, const RefPtr<ImageObject>& imageObject)
{
    if (contentConstraint.selfIdealSize) {
        return contentConstraint.selfIdealSize.value();
    }
    auto imageSize = imageObject->GetImageSize();
    SizeF size = SizeF(static_cast<float>(imageSize.Width()), static_cast<float>(imageSize.Height()));
    size.Constrain(contentConstraint.minSize, contentConstraint.maxSize);
    return size;
}

} // namespace OHOS::Ace::NG