/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/render/adapter/txt_font_collection.h"

#ifndef PREVIEW
#include "rosen_text/font_collection_mgr.h"
#include "bridge/common/utils/engine_helper.h"
#endif

namespace OHOS::Ace::NG {
namespace {
void OnLoadFontFinished(const Rosen::FontCollection* collection, const Rosen::FontEventInfo& info)
{
#ifndef PREVIEW
    uint64_t runtimeId = Rosen::FontCollectionMgr::GetInstance().GetEnvByFontCollection(collection);
#else
    uint64_t runtimeId = 0;
#endif
    if (runtimeId == 0) {
        auto txtFontCollection = AceType::DynamicCast<TxtFontCollection>(FontCollection::Current());
        if (!txtFontCollection || txtFontCollection->GetRawFontCollection().get() != collection) {
            return;
        }
    }
    auto loadFinishCallback = FontCollection::Current()->GetLoadFontFinishCallback();
    for (const auto& callback : loadFinishCallback) {
        if (callback) {
            callback(info.familyName, runtimeId);
        }
    }
}

void OnUnLoadFontFinished(const Rosen::FontCollection* collection, const Rosen::FontEventInfo& info)
{
#ifndef PREVIEW
    uint64_t runtimeId = Rosen::FontCollectionMgr::GetInstance().GetEnvByFontCollection(collection);
#else
    uint64_t runtimeId = 0;
#endif
    if (runtimeId == 0) {
        auto txtFontCollection = AceType::DynamicCast<TxtFontCollection>(FontCollection::Current());
        if (!txtFontCollection || txtFontCollection->GetRawFontCollection().get() != collection) {
            return;
        }
    }
    auto unLoadFinishCallback = FontCollection::Current()->GetUnloadFontFinishCallback();
    for (const auto& callback : unLoadFinishCallback) {
        if (callback) {
            callback(info.familyName, runtimeId);
        }
    }
}
}

RefPtr<FontCollection> TxtFontCollection::GetInstance()
{
    static RefPtr<TxtFontCollection> instance = AceType::MakeRefPtr<TxtFontCollection>();
    return instance;
}

RefPtr<FontCollection> FontCollection::Current()
{
    auto localFontCollection = TxtFontCollection::GetFormLocalInstance();
    if (localFontCollection) {
        return localFontCollection;
    }
    return TxtFontCollection::GetInstance();
}

RefPtr<FontCollection> TxtFontCollection::GetFormLocalInstance()
{
#ifndef PREVIEW
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, nullptr);
    if (!pipeline->IsFormRender()) {
        return nullptr;
    }
    auto engine = EngineHelper::GetCurrentEngine();
    if (!engine) {
        return nullptr;
    }
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    if (nativeEngine == nullptr) {
        return nullptr;
    }
    uint64_t envId = static_cast<uint64_t>(reinterpret_cast<uintptr_t>(nativeEngine));
    std::shared_ptr<Rosen::FontCollection> rosenFontCollection =
        Rosen::FontCollectionMgr::GetInstance().GetLocalInstance(envId);
    if (rosenFontCollection) {
        // register global font callback.
        TxtFontCollection::GetInstance();
        return AceType::MakeRefPtr<TxtFontCollection>(rosenFontCollection);
    }
#endif
    return nullptr;
}

TxtFontCollection::TxtFontCollection()
{
    collection_ = Rosen::FontCollection::Create();
    /* texgine not support
    dynamicFontManager_ = RosenFontCollection::GetInstance().GetDynamicFontManager();
    if (collection_) {
        std::string emptyLocale;
        // 0x4e2d is unicode for '中'.
        collection_->MatchFallbackFont(0x4e2d, emptyLocale);
        collection_->GetMinikinFontCollectionForFamilies({ "sans-serif" }, emptyLocale);
    }
    */
    Rosen::FontCollection::RegisterLoadFontFinishCallback(OnLoadFontFinished);
    Rosen::FontCollection::RegisterUnloadFontFinishCallback(OnUnLoadFontFinished);
}

TxtFontCollection::TxtFontCollection(const std::shared_ptr<Rosen::FontCollection>& fontCollection)
    : collection_(fontCollection)
{}
} // namespace OHOS::Ace::NG
