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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_GESTURE_TYPES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_GESTURE_TYPES_H

#include <functional>
#include <list>
#include <optional>
#include <set>
#include <string>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/event/gesture_info.h"
#include "core/components_ng/gestures/base_gesture_event.h"
#include "core/event/ace_events.h"

namespace OHOS::Ace::NG {

class UINode;
class NGGestureRecognizer;

using GestureJudgeFunc = std::function<GestureJudgeResult(
    const RefPtr<GestureInfo>& gestureInfo, const std::shared_ptr<BaseGestureEvent>& info)>;

using GestureRecognizerJudgeFunc = std::function<GestureJudgeResult(const std::shared_ptr<BaseGestureEvent>& info,
    const RefPtr<NGGestureRecognizer>& current, const std::list<WeakPtr<NGGestureRecognizer>>& others)>;

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_GESTURE_TYPES_H
