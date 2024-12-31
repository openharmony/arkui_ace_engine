/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "compatible/components/component_loader.h"

#include <functional>
#include <string>
#include <unordered_map>

#include "compatible/components/badge/badge_loader.h"
#include "compatible/components/canvas/canvas_loader.h"
#include "compatible/components/marquee/marquee_loader.h"

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_Compatible_GetLoader(const char* name)
{
    return OHOS::Ace::ComponentLoader::GetLoaderByName(name);
}

namespace OHOS::Ace {

ComponentLoader* ComponentLoader::GetLoaderByName(const char* name)
{
    std::string nameStr(name);
    static std::unordered_map<std::string, std::function<ComponentLoader*()>> sLoaderMap = {
        { "badge", []() -> ComponentLoader* { return new BadgeLoader(); } },
        { "canvas", []() -> ComponentLoader* { return new CanvasLoader(); } },
        { "marquee", []() -> ComponentLoader* { return new MarqueeLoader(); } }
    };
    auto loaderIter = sLoaderMap.find(nameStr);
    if (loaderIter != sLoaderMap.end()) {
        return loaderIter->second();
    }

    return nullptr;
}

} // namespace OHOS::Ace