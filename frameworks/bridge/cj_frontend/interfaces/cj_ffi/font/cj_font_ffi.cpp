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

#include "cj_font_ffi.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

extern "C" {
void FfiFontManagerRegisterFont(const char* familyName, const char* familySrc)
{
    auto container = Container::Current();
    if (container && container->GetPipelineContext()) {
        auto pipelineContext = container->GetPipelineContext();
        pipelineContext->RegisterFont(familyName, familySrc, "", "");
    } else {
        LOGE("Can not get pipelineContext.");
        return;
    }
}

VectorStringHandle FfiFontManagerGetSystemFontList()
{
    auto fontList = new std::vector<std::string>;
    auto container = Container::Current();
    if (container && container->GetPipelineContext()) {
        auto pipelineContext = container->GetPipelineContext();
        pipelineContext->GetSystemFontList(*fontList);
        return fontList;
    } else {
        LOGE("Can not get pipelineContext.");
        return fontList;
    }
}

NativeFontInfo4Font* FfiFontManagerGetFontByName(const char* fontName)
{
    auto container = Container::Current();
    if (!container || !container->GetPipelineContext()) {
        LOGE("Can not get pipelineContext.");
        return nullptr;
    }
    auto pipelineContext = container->GetPipelineContext();
    FontInfo fontInfo;
    if (!pipelineContext->GetSystemFont(fontName, fontInfo)) {
        LOGE("Can not get system font.");
        return nullptr;
    }
    return new NativeFontInfo4Font { .path = Utils::MallocCString(fontInfo.path),
        .postScriptName = Utils::MallocCString(fontInfo.postScriptName),
        .fullName = Utils::MallocCString(fontInfo.fullName),
        .family = Utils::MallocCString(fontInfo.family),
        .subfamily = Utils::MallocCString(fontInfo.subfamily),
        .weight = fontInfo.weight,
        .width = fontInfo.width,
        .italic = fontInfo.italic,
        .monoSpace = fontInfo.monoSpace,
        .symbolic = fontInfo.symbolic };
}

void parseGenericList(FontConfigJsonInfo fontConfigJsonInfo, std::vector<NativeUIFontGenericInfo>* genericList)
{
    for (auto generic : fontConfigJsonInfo.genericSet) {
        NativeUIFontGenericInfo nativeGeneric = NativeUIFontGenericInfo();
        nativeGeneric.family = Utils::MallocCString(generic.familyName);
        std::vector<NativeUIFontAliasInfo>* aliasInfoList = new std::vector<NativeUIFontAliasInfo>();
        if (aliasInfoList == nullptr) {
            LOGE("Can not get NativeUIFontAliasInfo vector ptr.");
            return;
        }
        for (auto alias : generic.aliasSet) {
            NativeUIFontAliasInfo nativeAlias = NativeUIFontAliasInfo { .name = Utils::MallocCString(alias.familyName),
                .weight = static_cast<uint32_t>(alias.weight) };
            aliasInfoList->push_back(nativeAlias);
        }
        nativeGeneric.alias = aliasInfoList;
        std::vector<NativeUIFontAdjustInfo>* adjustInfoList = new std::vector<NativeUIFontAdjustInfo>();
        if (adjustInfoList == nullptr) {
            LOGE("Can not get NativeUIFontAdjustInfo vector ptr.");
            return;
        }
        for (auto adjust : generic.adjustSet) {
            NativeUIFontAdjustInfo nativeAdjust =
                NativeUIFontAdjustInfo { .weight = static_cast<uint32_t>(adjust.origValue),
                    .to = static_cast<uint32_t>(adjust.newValue) };
            adjustInfoList->push_back(nativeAdjust);
        }
        nativeGeneric.adjust = adjustInfoList;
        genericList->push_back(nativeGeneric);
    }
}

void parseFallbackGroupList(
    FontConfigJsonInfo fontConfigJsonInfo, std::vector<NativeUIFontFallbackGroupInfo>* fallbackGroupList)
{
    for (auto fallbackGroup : fontConfigJsonInfo.fallbackGroupSet) {
        NativeUIFontFallbackGroupInfo nativeFallbackGroup = NativeUIFontFallbackGroupInfo();
        nativeFallbackGroup.fontSetName = Utils::MallocCString(fallbackGroup.groupName);
        std::vector<NativeUIFontFallbackInfo>* fallbackList = new std::vector<NativeUIFontFallbackInfo>();
        if (fallbackList == nullptr) {
            LOGE("Can not get NativeUIFontFallbackInfo vector ptr.");
            return;
        }
        for (auto fallbackInfo : fallbackGroup.fallbackInfoSet) {
            NativeUIFontFallbackInfo nativeFallbackInfo =
                NativeUIFontFallbackInfo { .language = Utils::MallocCString(fallbackInfo.font),
                    .family = Utils::MallocCString(fallbackInfo.familyName) };
            fallbackList->push_back(nativeFallbackInfo);
        }
        nativeFallbackGroup.fallback = fallbackList;
        fallbackGroupList->push_back(nativeFallbackGroup);
    }
}

NativeUIFontConfig FfiFontManagerGetUIFontConfig()
{
    auto container = Container::Current();
    if (!container || !container->GetPipelineContext()) {
        LOGE("Can not get pipelineContext.");
        return NativeUIFontConfig { .fontDir = new std::vector<std::string>(),
            .generic = new std::vector<NativeUIFontGenericInfo>(),
            .fallbackGroups = new std::vector<NativeUIFontFallbackGroupInfo>() };
    }
    auto pipelineContext = container->GetPipelineContext();
    FontConfigJsonInfo fontConfigJsonInfo;
    pipelineContext->GetUIFontConfig(fontConfigJsonInfo);
    auto genericList = new std::vector<NativeUIFontGenericInfo>();
    parseGenericList(fontConfigJsonInfo, genericList);
    auto fallbackGroupList = new std::vector<NativeUIFontFallbackGroupInfo>();
    parseFallbackGroupList(fontConfigJsonInfo, fallbackGroupList);
    auto fontDirList = new std::vector<std::string>();
    for (auto dir : fontConfigJsonInfo.fontDirSet) {
        std::string fontDir = dir.c_str();
        fontDirList->push_back(fontDir);
    }
    return NativeUIFontConfig { .fontDir = fontDirList, .generic = genericList, .fallbackGroups = fallbackGroupList };
}
}