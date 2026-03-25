/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "test/mock/frameworks/core/common/mock_font_manager.h"
#include "core/common/font_change_observer.h"
#include "core/common/font_manager.h"

namespace OHOS::Ace {
std::string FontManager::appCustomFont_ = "";
bool FontManager::isDefaultFontChanged_ = false;
RefPtr<FontManager> FontManager::Create()
{
    return AceType::MakeRefPtr<MockFontManager>();
}

const std::vector<std::string>& FontManager::GetFontNames() const
{
    return {};
}

bool FontManager::IsDefaultFontChanged()
{
    return isDefaultFontChanged_;
}
void FontManager::UnRegisterCallbackNG(const WeakPtr<NG::UINode>& node) {}
bool FontManager::RegisterCallbackNG(
    const WeakPtr<NG::UINode>& node, const std::string& familyName, const std::function<void()>& callback)
{
    return false;
}

void FontManager::RebuildFontNodeNG() {}

void FontManager::AddFontObserver(WeakPtr<FontChangeObserver> node)
{
    (void)node;
}

void FontManager::RemoveFontChangeObserver(WeakPtr<FontChangeObserver> node) {}

void FontManager::AddFontNodeNG(const WeakPtr<NG::UINode>& node)
{
    if (fontNodesNG_.find(node) == fontNodesNG_.end()) {
        fontNodesNG_.emplace(node);
    }
}

void FontManager::RemoveFontNodeNG(const WeakPtr<NG::UINode>& node)
{
    fontNodesNG_.erase(node);
}

void FontManager::UpdateFontWeightScale() {}

void FontManager::RegisterFont(const std::string& familyName, const std::string& familySrc,
    const RefPtr<PipelineBase>& context, const std::string& bundleName, const std::string& moduleName)
{
    (void)familyName;
    (void)familySrc;
    (void)context;
    (void)bundleName;
    (void)moduleName;
}

void FontManager::GetSystemFontList(std::vector<std::string>& fontList)
{
    fontList = fontNames_;
}

bool FontManager::GetSystemFont(const std::string& fontName, FontInfo& fontInfo)
{
    (void)fontName;
    (void)fontInfo;
    return false;
}

void FontManager::GetUIFontConfig(FontConfigJsonInfo& info)
{
    info.fontDirSet.clear();
    info.genericSet.clear();
    info.fallbackGroupSet.clear();
}

void FontManager::AddVariationNodeNG(const WeakPtr<NG::UINode>& node) {}

void FontManager::RemoveVariationNodeNG(const WeakPtr<NG::UINode>& node) {}

bool FontManager::IsUseAppCustomFont() const
{
    return false;
}

const std::string& FontManager::GetAppCustomFont() const
{
    return appCustomFont_;
}

void FontManager::AddHybridRenderNode(const WeakPtr<NG::UINode>& node) {}
void FontManager::RemoveHybridRenderNode(const WeakPtr<NG::UINode>& node) {}
void FontManager::UpdateHybridRenderNodes() {}
void FontManager::StartAbilityOnInstallAppInStore(const std::string& appName) const {}
void FontManager::OnPreviewMenuOptionClick(TextDataDetectType type, const std::string& content) {}
void FontManager::StartAbilityOnCalendar(const std::map<std::string, std::string>& params) const {}
} // namespace OHOS::Ace
