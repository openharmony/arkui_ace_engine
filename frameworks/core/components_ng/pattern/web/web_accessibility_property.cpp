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

#include "core/components_ng/pattern/web/web_accessibility_property.h"

#if !defined(ANDROID_PLATFORM) && !defined(IOS_PLATFORM)
#include "core/components_ng/pattern/web/web_pattern.h"
#else
#include "core/components_ng/pattern/web/cross_platform/web_pattern.h"
#endif

namespace OHOS::Ace::NG {
std::string WebAccessibilityProperty::GetText() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, "");
    auto webPattern = frameNode->GetPattern<WebPattern>();
    CHECK_NULL_RETURN(webPattern, "");
    auto webPaintProperty = AceType::DynamicCast<WebPaintProperty>(webPattern->CreatePaintProperty());
    CHECK_NULL_RETURN(webPaintProperty, "");
    return webPaintProperty->GetWebPaintData();
}
} // namespace OHOS::Ace::NG