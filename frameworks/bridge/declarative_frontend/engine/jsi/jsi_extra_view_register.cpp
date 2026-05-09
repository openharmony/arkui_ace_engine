/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/engine/jsi/jsi_extra_view_register.h"
#include "bridge/declarative_frontend/jsview/js_cached_image.h"

namespace OHOS::Ace::Framework {

static const std::unordered_map<std::string, std::function<void(BindingTarget)>> extraBindFuncs = {
    /*
     * Binding function map sample:
      { "XXX", JSXXX::JSBind },
     */
    { "CachedImage", JSCachedImage::JSBind },
    { "MediaCachedImage", JSCachedImage::JSBindMediaCachedImage },
};

void RegisterExtraViews(BindingTarget globalObj)
{
    for (const auto& iter : extraBindFuncs) {
        iter.second(globalObj);
    }
}

bool RegisterExtraViewByName(BindingTarget globalObj, const std::string& moduleName)
{
    auto func = extraBindFuncs.find(moduleName);
    if (func == extraBindFuncs.end()) {
        LOGW("JS module not exist in extra, name: %{public}s", moduleName.c_str());
        return false;
    }
    (*func).second(globalObj);
    return true;
}

} // namespace OHOS::Ace::Framework
