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

#include "base/geometry/size.h"
#include "base/utils/measure_util.h"

namespace {
    constexpr float TEXT_SIZE_WIDTH = 10.0f;
    constexpr float TEXT_SIZE_HEIGHT = 10.0f;
}

namespace OHOS::Ace {
Size MeasureUtil::MeasureTextSize(const MeasureContext& context)
{
    return Size(TEXT_SIZE_WIDTH, TEXT_SIZE_HEIGHT);
}
double MeasureUtil::MeasureText(const MeasureContext& context)
{
    return TEXT_SIZE_WIDTH;
}
double MeasureUtil::MeasureTextWidth(const TextStyle& textStyle, const std::string& text)
{
    return TEXT_SIZE_WIDTH;
}
Size MeasureUtil::MeasureTextSize(const TextStyle& textStyle, const std::string& text)
{
    return Size(TEXT_SIZE_WIDTH, TEXT_SIZE_HEIGHT);
}
} // namespace OHOS::Ace