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

#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/components/text/render_text.h"
#include "core/pipeline/base/render_node.h"
#include "core/components_ng/base/frame_node.h"
#ifdef ENABLE_ROSEN_BACKEND
#ifdef TEXGINE_SUPPORT_FOR_OHOS
#include "foundation/graphic/graphic_2d/rosen/modules/texgine/src/font_parser.h"
#endif
#endif

namespace OHOS::Ace {

float FontManager::fontWeightScale_ = 1.0f;

void FontManager::RegisterFont(
    const std::string& familyName, const std::string& familySrc, const RefPtr<PipelineBase>& context)
{
    if (std::find(std::begin(fontNames_), std::end(fontNames_), familyName) == std::end(fontNames_)) {
        fontNames_.emplace_back(familyName);
    }

    for (auto iter = fontLoaders_.begin(); iter != fontLoaders_.end(); ++iter) {
        auto& fontLoader = *iter;
        if (fontLoader->GetFamilyName() == familyName) {
            LOGI("Font is already loaded!");
            return;
        }
    }
    RefPtr<FontLoader> fontLoader = FontLoader::Create(familyName, familySrc);
    fontLoaders_.emplace_back(fontLoader);
    fontLoader->AddFont(context);

    fontLoader->SetVariationChanged([weak = WeakClaim(this), familyName]() {
        auto fontManager = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(fontManager);
        fontManager->VaryFontCollectionWithFontWeightScale();
    });
}


void FontManager::GetSystemFontList(std::vector<std::string>& fontList)
{
#ifdef ENABLE_ROSEN_BACKEND
#ifdef TEXGINE_SUPPORT_FOR_OHOS
    Rosen::TextEngine::FontParser fontParser;
    std::vector<Rosen::TextEngine::FontParser::FontDescriptor> systemFontList;
    systemFontList = fontParser.GetVisibilityFonts();
    for (size_t i = 0; i < systemFontList.size(); ++i) {
        std::string fontName = systemFontList[i].fullName;
        fontList.emplace_back(fontName);
    }
#endif
#endif
}

bool FontManager::GetSystemFont(const std::string& fontName, FontInfo& fontInfo)
{
    bool isGetFont = false;
#ifdef ENABLE_ROSEN_BACKEND
#ifdef TEXGINE_SUPPORT_FOR_OHOS
    Rosen::TextEngine::FontParser fontParser;
    std::vector<Rosen::TextEngine::FontParser::FontDescriptor> systemFontList;
    systemFontList = fontParser.GetVisibilityFonts();
    for (size_t i = 0; i < systemFontList.size(); ++i) {
        if (fontName == systemFontList[i].fullName) {
            fontInfo.path = systemFontList[i].path;
            fontInfo.postScriptName = systemFontList[i].postScriptName;
            fontInfo.fullName = systemFontList[i].fullName;
            fontInfo.family = systemFontList[i].fontFamily;
            fontInfo.subfamily = systemFontList[i].fontSubfamily;
            fontInfo.weight = systemFontList[i].weight;
            fontInfo.width = systemFontList[i].width;
            fontInfo.italic = systemFontList[i].italic;
            fontInfo.monoSpace = systemFontList[i].monoSpace;
            fontInfo.symbolic = systemFontList[i].symbolic;
            isGetFont = true;
            break;
        }
    }
#endif
#endif
    return isGetFont;
}

bool FontManager::RegisterCallback(
    const WeakPtr<RenderNode>& node, const std::string& familyName, const std::function<void()>& callback)
{
    CHECK_NULL_RETURN(callback, false);
    bool isCustomFont = false;
    for (auto& fontLoader : fontLoaders_) {
        if (fontLoader->GetFamilyName() == familyName) {
            fontLoader->SetOnLoaded(node, callback);
            isCustomFont = true;
        }
    }
    return isCustomFont;
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
        auto uiNode = DynamicCast<UINode>(fontNode);
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
        auto frameNode = DynamicCast<FrameNode>(uiNode);
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
    bool isCustomFont = false;
    for (auto& fontLoader : fontLoaders_) {
        if (fontLoader->GetFamilyName() == familyName) {
            fontLoader->SetOnLoadedNG(node, callback);
            isCustomFont = true;
        }
    }
    return isCustomFont;
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

} // namespace OHOS::Ace
