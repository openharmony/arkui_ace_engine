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

#include "core/event/back_end_event_manager.h"

#include "core/event/key_event.h"
#include "core/event/mouse_raw_recognizer.h"
#include "core/event/rotation_event.h"
#include "core/components/scroll/scroll_position_controller.h"
#include "core/components_v2/grid/grid_event.h"
#include "core/components_v2/indexer/indexer_event_info.h"
#include "core/components_v2/pattern_lock/pattern_lock_component.h"
#include "core/gestures/click_info.h"
#include "core/gestures/drag_recognizer.h"
#include "core/gestures/long_press_recognizer.h"
#include "core/gestures/swipe_recognizer.h"
#include "ui/event/touch_event.h"
#include "ui/gestures/gesture_event.h"

namespace OHOS::Ace {
namespace {

std::atomic<uint64_t> g_currentId = 0;

} // namespace

#define BACKEND_EVENT_MANAGER_SINGLETON_IMPL(Signature)                \
template<>                                                             \
ACE_FORCE_EXPORT BackEndEventManager<Signature>&                       \
Singleton<BackEndEventManager<Signature>>::GetInstance()               \
{                                                                      \
    static BackEndEventManager<Signature> instance;                    \
    return instance;                                                   \
}


SINGLETON_INSTANCE_IMPL(BackEndEventIdManager);
BACKEND_EVENT_MANAGER_SINGLETON_IMPL(void());
BACKEND_EVENT_MANAGER_SINGLETON_IMPL(void(const std::string&));
BACKEND_EVENT_MANAGER_SINGLETON_IMPL(void(const std::string&, std::string&));
BACKEND_EVENT_MANAGER_SINGLETON_IMPL(void(const std::string&, uint32_t, bool));
BACKEND_EVENT_MANAGER_SINGLETON_IMPL(void(const TouchEventInfo&));
BACKEND_EVENT_MANAGER_SINGLETON_IMPL(void(const ClickInfo&));
BACKEND_EVENT_MANAGER_SINGLETON_IMPL(void(const LongPressInfo&));
BACKEND_EVENT_MANAGER_SINGLETON_IMPL(void(const DragStartInfo&));
BACKEND_EVENT_MANAGER_SINGLETON_IMPL(void(const DragUpdateInfo&));
BACKEND_EVENT_MANAGER_SINGLETON_IMPL(void(const DragEndInfo&));
BACKEND_EVENT_MANAGER_SINGLETON_IMPL(void(const RotationEvent&));
BACKEND_EVENT_MANAGER_SINGLETON_IMPL(void(const MouseEventInfo&));
BACKEND_EVENT_MANAGER_SINGLETON_IMPL(void(const GestureEvent&));
BACKEND_EVENT_MANAGER_SINGLETON_IMPL(void(const SwipeEventInfo&));
BACKEND_EVENT_MANAGER_SINGLETON_IMPL(void(const KeyEvent&, bool&));
BACKEND_EVENT_MANAGER_SINGLETON_IMPL(void(uint32_t));
BACKEND_EVENT_MANAGER_SINGLETON_IMPL(void(int32_t));
BACKEND_EVENT_MANAGER_SINGLETON_IMPL(void(std::string));
BACKEND_EVENT_MANAGER_SINGLETON_IMPL(void(const std::shared_ptr<BaseEventInfo>&));
BACKEND_EVENT_MANAGER_SINGLETON_IMPL(void(const std::shared_ptr<ClickInfo>&));
BACKEND_EVENT_MANAGER_SINGLETON_IMPL(void(const std::shared_ptr<KeyEventInfo>&));
BACKEND_EVENT_MANAGER_SINGLETON_IMPL(void(std::shared_ptr<ScrollEventInfo>&));
BACKEND_EVENT_MANAGER_SINGLETON_IMPL(void(const std::shared_ptr<TouchEventInfo>&));
BACKEND_EVENT_MANAGER_SINGLETON_IMPL(void(const std::shared_ptr<V2::GridEventInfo>&));
BACKEND_EVENT_MANAGER_SINGLETON_IMPL(void(const std::shared_ptr<V2::IndexerEventInfo>&));
BACKEND_EVENT_MANAGER_SINGLETON_IMPL(void(const std::shared_ptr<V2::PatternCompleteEvent>&));

BackEndEventIdManager::BackEndEventIdManager() = default;
BackEndEventIdManager::~BackEndEventIdManager() = default;

std::string BackEndEventIdManager::GetAvailableId()
{
    ACE_DCHECK(g_currentId.load() != UINT64_MAX);
    return std::to_string(++g_currentId);
}

} // namespace OHOS::Ace