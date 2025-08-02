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

#include "drag_event.h"

#if defined(ACE_STATIC)
#include "frameworks/core/components_ng/event/gesture_event_hub.h"
#endif

namespace OHOS::Ace {
void DragEvent::SetData(const RefPtr<UnifiedData>& unifiedData)
{
    unifiedData_ = unifiedData;
}

RefPtr<UnifiedData>& DragEvent::GetData()
{
    return unifiedData_;
}

void DragEvent::SetDragInfo(const RefPtr<UnifiedData>& dragInfo)
{
    dragInfo_ = dragInfo;
}

RefPtr<UnifiedData>& DragEvent::GetDragInfo()
{
    return dragInfo_;
}

#if defined(ACE_STATIC)
RefPtr<PixelMap> DragEvent::GetDragDropInfoPixelMap() const
{
    return dragDropInfoPixelMap_;
}

void* DragEvent::GetDragDropInfoCustomNode() const
{
    return dragDropInfoCustomNode_;
}

std::string DragEvent::GetDragDropInfoExtraInfo() const
{
    return dragDropInfoExtraInfo_;
}

void DragEvent::SetDragDropInfoPixelMap(RefPtr<PixelMap> pixelMap)
{
    dragDropInfoPixelMap_ = pixelMap;
}

void DragEvent::SetDragDropInfoExtraInfo(std::string& extraInfo)
{
    dragDropInfoExtraInfo_ = extraInfo;
}

void DragEvent::SetDragDropInfoCustomNode(void* customNode)
{
    dragDropInfoCustomNode_ = customNode;
}
#endif

} // namespace OHOS::Ace