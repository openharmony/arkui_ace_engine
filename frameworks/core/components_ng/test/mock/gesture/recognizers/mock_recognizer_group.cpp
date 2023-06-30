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

#include "core/components_ng/gestures/recognizers/recognizer_group.h"

namespace OHOS::Ace::NG {
void RecognizerGroup::AddChildren(const std::list<RefPtr<NGGestureRecognizer>>& recognizers) {}

void RecognizerGroup::OnFlushTouchEventsBegin() {}

void RecognizerGroup::OnFlushTouchEventsEnd() {}

void RecognizerGroup::OnBeginGestureReferee(int32_t touchId, bool needUpdateChild) {}

void RecognizerGroup::OnFinishGestureReferee(int32_t touchId) {}

void RecognizerGroup::OnResetStatus() {}

const std::list<RefPtr<NGGestureRecognizer>>& RecognizerGroup::GetGroupRecognizer()
{
    std::list<RefPtr<NGGestureRecognizer>> groupRecognizer;
    return groupRecognizer;
}
} // namespace OHOS::Ace::NG
