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

#include "core/common/font_manager.h"

#include "base/i18n/localization.h"
#include "core/components/text/render_text.h"
#include "core/components_ng/base/frame_node.h"
#ifdef ENABLE_ROSEN_BACKEND
#ifdef TEXGINE_SUPPORT_FOR_OHOS
#include "texgine/src/font_config.h"
#include "texgine/src/font_parser.h"
#endif
#endif
#ifdef USE_PLATFORM_FONT
#include "core/common/font/font_platform_proxy.h"
#endif

namespace OHOS::Ace {

std::string FontManager::appCustomFont_ = "";
float FontManager::fontWeightScale_ = 1.0f;
bool FontManager::isDefaultFontChanged_ = false;

void FontManager::RegisterFont(const std::string& familyName, const std::string& familySrc,
    const RefPtr<PipelineBase>& context, const std::string& bundleName, const std::string& moduleName)
{
    if (std::find(std::begin(fontNames_), std::end(fontNames_), familyName) == std::end(fontNames_)) {
        fontNames_.emplace_back(familyName);
    }

    for (auto iter = fontLoaders_.begin(); iter != fontLoaders_.end(); ++iter) {
        auto& fontLoader = *iter;
        if (fontLoader->GetFamilyName() == familyName) {
            return;
        }
    }
    RefPtr<FontLoader> fontLoader = FontLoader::Create(familyName, familySrc);
    fontLoaders_.emplace_back(fontLoader);
    TAG_LOGI(AceLogTag::ACE_FONT,
        "RegisterFont [familyName:%{public}s],[familySrc:%{public}s],[bundleName:%{public}s],[moduleName:%{public}s]",
        familyName.c_str(), familySrc.c_str(), bundleName.c_str(), moduleName.c_str());
    fontLoader->AddFont(context, bundleName, moduleName);

    fontLoader->SetVariationChanged([weak = WeakClaim(this), familyName]() {
        auto fontManager = weak.Upgrade();
        CHECK_NULL_VOID(fontManager);
        fontManager->VaryFontCollectionWithFontWeightScale();
    });
}

void FontManager::SetFontFamily(const char* familyName, const char* familySrc)
{
    RefPtr<FontLoader> fontLoader = FontLoader::Create(familyName, familySrc);
    fontLoader->SetDefaultFontFamily(familyName, familySrc);
}

bool FontManager::IsDefaultFontChanged()
{
    // For AutoUI Test，render Text with High precision
    if (SystemProperties::GetDebugAutoUIEnabled()) {
        isDefaultFontChanged_ = true;
    }
    return isDefaultFontChanged_;
}

bool FontManager::IsUseAppCustomFont() const
{
    return !appCustomFont_.empty();
}

void FontManager::SetAppCustomFont(const std::string& familyName)
{
    appCustomFont_ = familyName;
}

const std::string& FontManager::GetAppCustomFont() const
{
    return appCustomFont_;
}

void FontManager::GetSystemFontList(std::vector<std::string>& fontList)
{
#ifdef USE_PLATFORM_FONT
    auto fontPlatform = FontPlatformProxy::GetInstance().GetFontPlatform();
    if (fontPlatform) {
        fontPlatform->GetSystemFontList(fontList);
    }
#else
#ifdef ENABLE_ROSEN_BACKEND
#ifdef TEXGINE_SUPPORT_FOR_OHOS
    Rosen::TextEngine::FontParser fontParser;
    std::vector<Rosen::TextEngine::FontParser::FontDescriptor> systemFontList;
    auto locale = Localization::GetInstance()->GetFontLocale();
    systemFontList = fontParser.GetVisibilityFonts(locale);
    for (size_t i = 0; i < systemFontList.size(); ++i) {
        std::string fontName = systemFontList[i].fullName;
        fontList.emplace_back(fontName);
    }
#endif
#endif
#endif
}

void FontManager::GetUIFontConfig(FontConfigJsonInfo& info)
{
#ifdef ENABLE_ROSEN_BACKEND
#ifdef TEXGINE_SUPPORT_FOR_OHOS
    Rosen::TextEngine::FontConfigJson fontConfigJson;
    fontConfigJson.ParseFile();
    auto rosenInfo = fontConfigJson.GetFontConfigJsonInfo();
    // rosenInfo to FontConfigJsonInfo
    for (size_t i = 0; i < rosenInfo->fontDirSet.size(); ++i) {
        info.fontDirSet.emplace_back(rosenInfo->fontDirSet[i]);
    }
    for (size_t i = 0; i < rosenInfo->genericSet.size(); ++i) {
        FontGenericInfo genericInfo;
        genericInfo.familyName = rosenInfo->genericSet[i].familyName;
        for (size_t j = 0; j < rosenInfo->genericSet[i].aliasSet.size(); ++j) {
            AliasInfo aliasInfo;
            aliasInfo.familyName = rosenInfo->genericSet[i].aliasSet[j].familyName;
            aliasInfo.weight = rosenInfo->genericSet[i].aliasSet[j].weight;
            genericInfo.aliasSet.emplace_back(aliasInfo);
        }
        for (size_t j = 0; j < rosenInfo->genericSet[i].adjustSet.size(); ++j) {
            AdjustInfo adjustInfo;
            adjustInfo.origValue = rosenInfo->genericSet[i].adjustSet[j].origValue;
            adjustInfo.newValue = rosenInfo->genericSet[i].adjustSet[j].newValue;
            genericInfo.adjustSet.emplace_back(adjustInfo);
        }
        info.genericSet.emplace_back(genericInfo);
    }
    for (size_t i = 0; i < rosenInfo->fallbackGroupSet.size(); ++i) {
        FallbackGroup fallbackGroupInfo;
        fallbackGroupInfo.groupName = rosenInfo->fallbackGroupSet[i].groupName;
        for (size_t j = 0; j < rosenInfo->fallbackGroupSet[i].fallbackInfoSet.size(); ++j) {
            FallbackInfo fallbackInfo;
            fallbackInfo.familyName = rosenInfo->fallbackGroupSet[i].fallbackInfoSet[j].familyName;
            fallbackInfo.font = rosenInfo->fallbackGroupSet[i].fallbackInfoSet[j].font;
            fallbackGroupInfo.fallbackInfoSet.emplace_back(fallbackInfo);
        }
        info.fallbackGroupSet.emplace_back(fallbackGroupInfo);
    }
#endif
#endif
}

bool FontManager::GetSystemFont(const std::string& fontName, FontInfo& fontInfo)
{
    bool isGetFont = false;
#ifdef USE_PLATFORM_FONT
    auto fontPlatform = FontPlatformProxy::GetInstance().GetFontPlatform();
    if (fontPlatform) {
        isGetFont = fontPlatform->GetSystemFont(fontName, fontInfo);
    }
#else
#ifdef ENABLE_ROSEN_BACKEND
#ifdef TEXGINE_SUPPORT_FOR_OHOS
    Rosen::TextEngine::FontParser fontParser;
    std::unique_ptr<Rosen::TextEngine::FontParser::FontDescriptor> systemFontDesc;
    auto locale = Localization::GetInstance()->GetFontLocale();
    systemFontDesc = fontParser.GetVisibilityFontByName(fontName, locale);
    CHECK_NULL_RETURN(systemFontDesc, false);
    if (fontName == systemFontDesc->fullName) {
        fontInfo.path = systemFontDesc->path;
        fontInfo.postScriptName = systemFontDesc->postScriptName;
        fontInfo.fullName = systemFontDesc->fullName;
        fontInfo.family = systemFontDesc->fontFamily;
        fontInfo.subfamily = systemFontDesc->fontSubfamily;
        fontInfo.weight = static_cast<uint32_t>(systemFontDesc->weight);
        fontInfo.width = static_cast<uint32_t>(systemFontDesc->width);
        fontInfo.italic = systemFontDesc->italic;
        fontInfo.monoSpace = systemFontDesc->monoSpace;
        fontInfo.symbolic = systemFontDesc->symbolic;
        isGetFont = true;
    }
#endif
#endif
#endif
    return isGetFont;
}

bool FontManager::RegisterCallback(
    const WeakPtr<RenderNode>& node, const std::string& familyName, const std::function<void()>& callback)
{
    CHECK_NULL_RETURN(callback, false);
    for (auto& fontLoader : fontLoaders_) {
        if (fontLoader->GetFamilyName() == familyName) {
            fontLoader->SetOnLoaded(node, callback);
        }
    }
    return false;
}

const std::vector<std::string>& FontManager::GetFontNames() const
{
    return fontNames_;
}

void FontManager::AddFontNode(const WeakPtr<RenderNode>& node)
{
    if (fontNodes_.find(node) == fontNodes_.end()) {
        fontNodes_.emplace(node);
    }
}

void FontManager::RemoveFontNode(const WeakPtr<RenderNode>& node)
{
    fontNodes_.erase(node);
}

void FontManager::RebuildFontNode()
{
#ifndef NG_BUILD
    for (auto iter = fontNodes_.begin(); iter != fontNodes_.end();) {
        auto fontNode = iter->Upgrade();
        CHECK_NULL_VOID(fontNode);
        auto renderNode = DynamicCast<RenderNode>(fontNode);
        if (renderNode) {
            renderNode->MarkNeedLayout();
            ++iter;
        } else {
            iter = fontNodes_.erase(iter);
        }
    }
#else
    for (auto iter = fontNodesNG_.begin(); iter != fontNodesNG_.end();) {
        auto fontNode = iter->Upgrade();
        CHECK_NULL_VOID(fontNode);
        auto uiNode = DynamicCast<NG::UINode>(fontNode);
        if (uiNode) {
            uiNode->MarkDirtyNode(NG::PROPERTY_UPDATE_LAYOUT);
            ++iter;
        } else {
            iter = fontNodesNG_.erase(iter);
        }
    }
#endif
}

void FontManager::UnRegisterCallback(const WeakPtr<RenderNode>& node)
{
    for (auto& fontLoader : fontLoaders_) {
        fontLoader->RemoveCallback(node);
    }
}

void FontManager::RebuildFontNodeNG()
{
    for (auto iter = fontNodesNG_.begin(); iter != fontNodesNG_.end();) {
        auto fontNode = iter->Upgrade();
        CHECK_NULL_VOID(fontNode);
        auto uiNode = DynamicCast<NG::UINode>(fontNode);
        if (uiNode) {
            uiNode->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE);
            ++iter;
        } else {
            iter = fontNodesNG_.erase(iter);
        }
    }
    for (auto iter = observers_.begin(); iter != observers_.end();) {
        auto fontNode = iter->Upgrade();
        CHECK_NULL_VOID(fontNode);
        if (fontNode) {
            fontNode->OnFontChanged();
            ++iter;
        } else {
            iter = observers_.erase(iter);
        }
    }
}

void FontManager::UpdateFontWeightScale()
{
    float fontWeightScale = SystemProperties::GetFontWeightScale();
    if (!NearEqual(fontWeightScale, fontWeightScale_)) {
        fontWeightScale_ = fontWeightScale;
        VaryFontCollectionWithFontWeightScale();
    }
}

void FontManager::AddVariationNode(const WeakPtr<RenderNode>& node)
{
    if (variationNodes_.find(node) == variationNodes_.end()) {
        variationNodes_.emplace(node);
    }
}

void FontManager::RemoveVariationNode(const WeakPtr<RenderNode>& node)
{
    variationNodes_.erase(node);
}

void FontManager::NotifyVariationNodes()
{
#ifndef NG_BUILD
    for (const auto& node : variationNodes_) {
        auto refNode = node.Upgrade();
        CHECK_NULL_VOID(refNode);
        auto renderNode = DynamicCast<RenderNode>(refNode);
        CHECK_NULL_VOID(renderNode);
        auto text = DynamicCast<RenderText>(renderNode);
        if (text) {
            text->MarkNeedMeasure();
        }
        renderNode->MarkNeedLayout();
    }
#else
    for (const auto& node : variationNodesNG_) {
        auto uiNode = node.Upgrade();
        CHECK_NULL_VOID(uiNode);
        auto frameNode = DynamicCast<NG::FrameNode>(uiNode);
        if (frameNode) {
            frameNode->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE);
        }
        uiNode->MarkDirtyNode(NG::PROPERTY_UPDATE_LAYOUT);
    }
#endif
}

bool FontManager::RegisterCallbackNG(
    const WeakPtr<NG::UINode>& node, const std::string& familyName, const std::function<void()>& callback)
{
    CHECK_NULL_RETURN(callback, false);
    for (auto& fontLoader : fontLoaders_) {
        if (fontLoader->GetFamilyName() == familyName) {
            fontLoader->SetOnLoadedNG(node, callback);
        }
    }
    return false;
}

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

void FontManager::UnRegisterCallbackNG(const WeakPtr<NG::UINode>& node)
{
    for (auto& fontLoader : fontLoaders_) {
        fontLoader->RemoveCallbackNG(node);
    }
}

void FontManager::AddVariationNodeNG(const WeakPtr<NG::UINode>& node)
{
    if (variationNodesNG_.find(node) == variationNodesNG_.end()) {
        variationNodesNG_.emplace(node);
    }
}

void FontManager::RemoveVariationNodeNG(const WeakPtr<NG::UINode>& node)
{
    variationNodesNG_.erase(node);
}

void FontManager::AddFontObserver(WeakPtr<FontChangeObserver> node)
{
    if (observers_.find(node) == observers_.end()) {
        observers_.emplace(node);
    }
}

void FontManager::RemoveFontChangeObserver(WeakPtr<FontChangeObserver> node)
{
    observers_.erase(node);
}

} // namespace OHOS::Ace
