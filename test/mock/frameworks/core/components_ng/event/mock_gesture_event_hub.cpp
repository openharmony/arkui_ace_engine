/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/event/gesture_event_hub.h"

namespace OHOS::Ace::NG {
void GestureEventHub::SetLongPressEvent(
    const RefPtr<LongPressEvent>& event, bool isForDrag, bool isDisableMouseLeft, int32_t duration)
{
    (void)event;
    (void)isForDrag;
    (void)isDisableMouseLeft;
    (void)duration;
}

bool GestureEventHub::ActClick(std::shared_ptr<JsonValue> secComphandle)
{
    (void)secComphandle;
    return true;
}

bool GestureEventHub::ActLongClick()
{
    return true;
}

void GestureEventHub::InitDragDropEvent()
{}

void GestureEventHub::RemoveDragEvent()
{}
void GestureEventHub::AddClickEvent(const RefPtr<ClickEvent>&) {}
void GestureEventHub::RemoveClickEvent(const RefPtr<ClickEvent>&) {}
} // namespace OHOS::Ace::NG
