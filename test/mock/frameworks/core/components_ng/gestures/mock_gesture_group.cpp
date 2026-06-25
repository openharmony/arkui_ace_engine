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

#include "core/components_ng/gestures/gesture_group.h"

namespace OHOS::Ace::NG {
int32_t GestureGroup::SizeofMe()
{
    return 0;
}

int32_t GestureGroup::Serialize(char* buff)
{
    (void)buff;
    return 0;
}

RefPtr<Gesture> GestureGroup::MakeGesture(GestureType type)
{
    (void)type;
    return nullptr;
}

int32_t GestureGroup::Deserialize(const char* buff)
{
    (void)buff;
    return 0;
}

RefPtr<NGGestureRecognizer> GestureGroup::CreateRecognizer()
{
    return nullptr;
}

void GestureGroup::RemoveChildrenByTag(const std::string& gestureTag, bool& needRecollect)
{
    (void)gestureTag;
    (void)needRecollect;
}

void GestureGroup::RemoveGesture(RefPtr<Gesture> gesture)
{
    (void)gesture;
}
} // namespace OHOS::Ace::NG
