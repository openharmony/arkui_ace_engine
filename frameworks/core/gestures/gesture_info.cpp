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

#include "gesture_info.h"

namespace OHOS::Ace {
#ifdef ENABLE_DRAG_FRAMEWORK
void DragEvent::SetData(const RefPtr<UnifiedData>& unifiedData)
{
    unifiedData_ = unifiedData;
}

RefPtr<UnifiedData>& DragEvent::GetData()
{
    return unifiedData_;
}

void DragEvent::SetSummary(std::map<std::string, int64_t>& summary)
{
    summary_ = summary;
}

std::map<std::string, int64_t>& DragEvent::GetSummary()
{
    return summary_;
}

void DragEvent::SetResult(DragRet dragRet)
{
    dragRet_ = dragRet;
}

DragRet DragEvent::GetResult()
{
    return dragRet_;
}

Rect DragEvent::GetPreviewRect()
{
    return previewRect_;
}

void DragEvent::SetPreviewRect(Rect previewRect)
{
    previewRect_ = previewRect;
}

void DragEvent::UseCustomAnimation(bool useCustomAnimation)
{
    useCustomAnimation_ = useCustomAnimation;
}

bool DragEvent::IsUseCustomAnimation()
{
    return useCustomAnimation_;
}

void DragEvent::SetDragInfo(const RefPtr<UnifiedData>& dragInfo)
{
    dragInfo_ = dragInfo;
}

RefPtr<UnifiedData>& DragEvent::GetDragInfo()
{
    return dragInfo_;
}

void DragEvent::SetCopy(bool copy)
{
    copy_ = copy;
}

bool DragEvent::IsCopy()
{
    return copy_;
}
#endif // ENABLE_DRAG_FRAMEWORK
} // namespace OHOS::Ace