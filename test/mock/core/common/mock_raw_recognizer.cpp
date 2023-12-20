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

#include "core/gestures/raw_recognizer.h"

namespace OHOS::Ace {
void RawRecognizer::HandleRawEvent(const TouchEvent &point, uint32_t stage)
{
}

bool RawRecognizer::DispatchEvent(const TouchEvent &point)
{
    return true;
}

bool RawRecognizer::HandleEvent(const TouchEvent &point)
{
    return true;
};

TouchEventInfo RawRecognizer::CreateTouchEventInfo(
    const std::string &type, const TouchEvent &point, bool ignoreCurrent) const
{
    TouchEventInfo info(type);
    return info;
}

} // namespace OHOS::Ace
