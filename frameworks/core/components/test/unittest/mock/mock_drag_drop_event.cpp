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


#include "core/components/box/drag_drop_event.h"

namespace OHOS::Ace {
void DragDropEvent::CreateDragDropRecognizer(const WeakPtr<PipelineContext>& pipelineContext)
{
    if (dragDropGesture_) {
        return;
    }
}

void DragDropEvent::LongPressOnAction(const GestureEvent& info)
{
    startPoint_ = Point();
}

RefPtr<DragDropEvent> DragDropEvent::FindDragDropNode(const RefPtr<PipelineContext>& context, const GestureEvent& info)
{
    return nullptr;
}

void DragDropEvent::AddDataToClipboard(const RefPtr<PipelineContext>& context, const std::string& extraInfo,
    const std::string& selectedText, const std::string& imageSrc)
{
}

void DragDropEvent::MergeClipboardData(const RefPtr<PipelineContext>& context, const std::string& newData)
{
}

void DragDropEvent::RestoreCilpboardData(const RefPtr<PipelineContext>& context)
{
    clipboard_ = nullptr;
    deleteDataCallback_ = nullptr;
}
} // namespace OHOS::Ace