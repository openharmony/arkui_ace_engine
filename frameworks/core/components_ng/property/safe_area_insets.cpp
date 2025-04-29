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

#include "safe_area_insets.h"

namespace OHOS::Ace::NG {
SafeAreaInsets SafeAreaInsets::Combine(const SafeAreaInsets& other) const
{
    SafeAreaInsets res;
    res.left_ = left_.Combine(other.left_);
    res.top_ = top_.Combine(other.top_);
    res.right_ = right_.Combine(other.right_);
    res.bottom_ = bottom_.Combine(other.bottom_);
    return res;
}

using Inset = SafeAreaInsets::Inset;
Inset SafeAreaInsets::Inset::Combine(const Inset& other) const
{
    Inset res;
    if (other.IsValid() && this->IsValid()) {
        res = { .start = std::min(start, other.start), .end = std::max(end, other.end) };
    } else if (other.IsValid()) {
        res = other;
    } else {
        res = *this;
    }
    return res;
}

bool SafeAreaInsets::IsValid() const
{
    return top_.IsValid() || left_.IsValid() || right_.IsValid() || bottom_.IsValid();
}

std::string Inset::ToString() const
{
    using std::to_string;
    return "[start: " + to_string(start) + ", end: " + to_string(end) + "]";
}

std::string SafeAreaInsets::ToString() const
{
    return "SafeAreaInsets left_: " + left_.ToString() + ", top_: " + top_.ToString() +
           ", right_: " + right_.ToString() + ", bottom_: " + bottom_.ToString();
}

bool SafeAreaInsets::Inset::IsOverlapped(float pos) const
{
    return IsValid() && LessOrNearEqual(static_cast<float>(start), pos) &&
        LessOrNearEqual(pos, static_cast<float>(end));
}
} // namespace OHOS::Ace::NG
