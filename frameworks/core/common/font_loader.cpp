/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/common/font_loader.h"

namespace OHOS::Ace {

FontLoader::FontLoader(const std::string& familyName, const std::string& familySrc)
    : familyName_(familyName), familySrc_(familySrc) {}
FontLoader::FontLoader(const std::string& familyName, const std::vector<std::string>& familySrcArray)
    : familyName_(familyName), familySrcArray_(familySrcArray) {}

const std::string& FontLoader::GetFamilyName() const
{
    return familyName_;
}

void FontLoader::SetOnLoaded(const WeakPtr<RenderNode>& node, const std::function<void()>& callback)
{
    CHECK_NULL_VOID(callback);
    if (isLoaded_) {
        callback();
    } else {
        callbacks_.emplace(node, callback);
    }
}

void FontLoader::RemoveCallback(const WeakPtr<RenderNode>& node)
{
    callbacks_.erase(node);
}

void FontLoader::SetVariationChanged(const std::function<void()>& variationChanged)
{
    variationChanged_ = variationChanged;
}

void FontLoader::RemoveCallbackNG(const WeakPtr<NG::UINode>& node)
{
    callbacksNG_.erase(node);
}

void FontLoader::SetOnLoadedNG(const WeakPtr<NG::UINode>& node, const std::function<void()>& callback)
{
    CHECK_NULL_VOID(callback);
    if (isLoaded_) {
        return;
    } else {
        callbacksNG_.emplace(node, callback);
    }
}

} // namespace OHOS::Ace
