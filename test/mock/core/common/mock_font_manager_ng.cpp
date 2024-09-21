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

#include "test/mock/core/common/mock_font_manager.h"

#include "core/common/font_change_observer.h"
#include "core/common/font_manager.h"

namespace OHOS::Ace {

std::string FontManager::appCustomFont_ = "";
const std::vector<std::string>& FontManager::GetFontNames() const
{
    return {};
}

bool FontManager::RegisterCallbackNG(
    const WeakPtr<NG::UINode>& node, const std::string& familyName, const std::function<void()>& callback)
{
    return false;
}

bool FontManager::IsDefaultFontChanged()
{
    return false;
}

void FontManager::UnRegisterCallbackNG(const WeakPtr<NG::UINode>& node) {}

void FontManager::AddFontNodeNG(const WeakPtr<NG::UINode>& node)
{
    fontNodesNG_.emplace(node);
}

void FontManager::RemoveFontNodeNG(const WeakPtr<NG::UINode>& node)
{
    fontNodesNG_.erase(node);
}

void FontManager::AddVariationNodeNG(const WeakPtr<NG::UINode>& node) {}

void FontManager::RemoveVariationNodeNG(const WeakPtr<NG::UINode>& node) {}

void FontManager::RebuildFontNodeNG() {}

bool FontManager::IsUseAppCustomFont() const
{
    return false;
}

const std::string& FontManager::GetAppCustomFont() const
{
    return appCustomFont_;
}

void FontManager::AddFontObserver(WeakPtr<FontChangeObserver> node) {}

void FontManager::RemoveFontChangeObserver(WeakPtr<FontChangeObserver> node) {}
} // namespace OHOS::Ace
