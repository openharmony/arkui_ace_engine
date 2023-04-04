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
#include "unified_data.h"
#include "unified_types.h"

namespace OHOS::Ace {
void DragEvent::SetData(std::shared_ptr<UDMF::UnifiedData>& unifiedData)
{
    unifiedData_ = unifiedData;
}

std::shared_ptr<UDMF::UnifiedData>& DragEvent::GetData()
{
    return unifiedData_;
}

void DragEvent::SetSummary(std::shared_ptr<UDMF::Summary>& summary)
{
    summary_ = summary;
}

std::shared_ptr<UDMF::Summary>& DragEvent::GetSummary()
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

void DragEvent::SetDragInfo(std::shared_ptr<UDMF::UnifiedData>& dragInfo)
{
    dragInfo_ = dragInfo;
}

std::shared_ptr<UDMF::UnifiedData>& DragEvent::GetDragInfo()
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
} // namespace OHOS::Ace