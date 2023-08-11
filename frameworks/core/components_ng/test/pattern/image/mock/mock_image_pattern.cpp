/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_paint_method.h"
#include "core/components_ng/pattern/image/image_pattern.h"

namespace OHOS::Ace::NG {
RefPtr<NodePaintMethod> ImagePattern::CreateNodePaintMethod()
{
    if (image_) {
        return MakeRefPtr<ImagePaintMethod>(image_, false);
    }
    if (altImage_ && altDstRect_ && altSrcRect_) {
        return MakeRefPtr<ImagePaintMethod>(altImage_, false);
    }
    return nullptr;
}

bool ImagePattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    return image_;
}
bool ImagePattern::BetweenSelectedPosition(const Offset& globalOffset)
{
    return false;
}
void ImagePattern::OnModifyDone() {}
void ImagePattern::OnAttachToFrameNode() {}

void ImagePattern::OnDetachFromFrameNode(FrameNode* frameNode) {}
void ImagePattern::BeforeCreatePaintWrapper() {}

void ImagePattern::OnNotifyMemoryLevel(int32_t level) {}
void ImagePattern::OnWindowHide() {}
void ImagePattern::OnWindowShow() {}
void ImagePattern::OnVisibleChange(bool isVisible) {}

void ImagePattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const {}
void ImagePattern::DumpInfo() {}
void ImagePattern::OnLanguageConfigurationUpdate() {}
} // namespace OHOS::Ace::NG
