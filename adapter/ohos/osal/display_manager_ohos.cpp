/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "display_manager_ohos.h"

#include <mutex>
#include <unordered_map>
#include <vector>

#include "dm/display_manager.h"

#include "base/log/log.h"

namespace OHOS::Ace {

namespace {
std::unordered_map<uint64_t, RefPtr<BaseDisplayInfo>> g_cachedDisplayInfoMap;
std::mutex g_cachedDisplayInfoMutex;

std::unordered_map<uint64_t, DisplayManager::DisplaySizeChangeCallback> g_displaySizeChangeCallbacks;
std::mutex g_callbackMutex;
uint64_t g_nextCallbackId = 1;

constexpr int32_t MAX_REGISTER_RETRY = 3;
std::mutex g_registerMutex;
bool g_displayRegistered = false;
int32_t g_displayAttemptCount = 0;

sptr<Rosen::DisplayManager::IDisplayListener> g_displayListener;
sptr<Rosen::DisplayManager::IDisplayAttributeListener> g_attributeListener;
bool g_displayListenerRegistered = false;
bool g_attributeListenerRegistered = false;

// Lightweight query: 1 IPC (GetDisplayById), then local member access.
// Only fetches displayId/width/height/rotation — does NOT call GetIsFoldable/GetFoldStatus/etc.
// Falls back to GetDefaultDisplay if GetDisplayById fails (at most 2 IPC in fallback path).
RefPtr<BaseDisplayInfo> FetchBaseDisplayInfo(uint64_t requestedDisplayId)
{
    auto display =
        Rosen::DisplayManager::GetInstance().GetDisplayById(static_cast<int32_t>(requestedDisplayId));
    if (!display) {
        TAG_LOGW(AceLogTag::ACE_DEFAULT_DOMAIN,
            "GetDisplayById failed for displayId=%{public}" PRIu64 ", trying GetDefaultDisplay", requestedDisplayId);
        display = Rosen::DisplayManager::GetInstance().GetDefaultDisplay();
    }
    if (!display) {
        TAG_LOGE(AceLogTag::ACE_DEFAULT_DOMAIN,
            "GetDefaultDisplay also failed for displayId=%{public}" PRIu64, requestedDisplayId);
        return nullptr;
    }
    auto dmDisplayInfo = display->GetDisplayInfo();
    if (!dmDisplayInfo) {
        return nullptr;
    }
    uint64_t actualDisplayId = dmDisplayInfo->GetDisplayId();
    if (actualDisplayId != requestedDisplayId) {
        TAG_LOGW(AceLogTag::ACE_DEFAULT_DOMAIN,
            "DisplayId mismatch: requested=%{public}" PRIu64 ", actual=%{public}" PRIu64,
            requestedDisplayId, actualDisplayId);
    }
    auto info = AceType::MakeRefPtr<BaseDisplayInfo>();
    info->SetDisplayId(actualDisplayId);
    info->SetWidth(dmDisplayInfo->GetWidth());
    info->SetHeight(dmDisplayInfo->GetHeight());
    info->SetRotation(static_cast<Rotation>(static_cast<uint32_t>(dmDisplayInfo->GetRotation())));
    return info;
}

class DisplayListenerImpl : public Rosen::DisplayManager::IDisplayListener {
public:
    void OnCreate(Rosen::DisplayId displayId) override
    {
        TAG_LOGI(AceLogTag::ACE_DEFAULT_DOMAIN, "OnCreate displayId=%{public}" PRIu64, static_cast<uint64_t>(displayId));
        uint64_t castDisplayId = static_cast<uint64_t>(displayId);
        auto cachedInfo = FetchBaseDisplayInfo(castDisplayId);
        if (!cachedInfo) {
            TAG_LOGE(AceLogTag::ACE_DEFAULT_DOMAIN, "OnCreate: FetchBaseDisplayInfo failed for displayId=%{public}" PRIu64,
                castDisplayId);
            return;
        }
        uint64_t actualId = cachedInfo->GetDisplayId();
        {
            std::lock_guard<std::mutex> lock(g_cachedDisplayInfoMutex);
            g_cachedDisplayInfoMap[actualId] = cachedInfo;
        }
    }

    void OnDestroy(Rosen::DisplayId displayId) override
    {
        TAG_LOGI(AceLogTag::ACE_DEFAULT_DOMAIN, "OnDestroy displayId=%{public}" PRIu64, static_cast<uint64_t>(displayId));
        uint64_t castDisplayId = static_cast<uint64_t>(displayId);
        {
            std::lock_guard<std::mutex> lock(g_cachedDisplayInfoMutex);
            g_cachedDisplayInfoMap.erase(castDisplayId);
        }
    }

    void OnChange(Rosen::DisplayId displayId) override
    {
        // No-op: Rosen adapter fires both OnChange AND OnAttributeChange.
        // We only handle OnAttributeChange (server-side filtered for width/height/rotation).
    }
};

class AttributeListenerImpl : public Rosen::DisplayManager::IDisplayAttributeListener {
public:
    void OnAttributeChange(Rosen::DisplayId displayId, const std::vector<std::string>& attributes) override
    {
        uint64_t castDisplayId = static_cast<uint64_t>(displayId);

        // OPT-3: No consumers -> invalidate cache entry + skip IPC entirely.
        bool hasConsumers = false;
        {
            std::lock_guard<std::mutex> lock(g_callbackMutex);
            hasConsumers = !g_displaySizeChangeCallbacks.empty();
        }
        if (!hasConsumers) {
            std::lock_guard<std::mutex> lock(g_cachedDisplayInfoMutex);
            g_cachedDisplayInfoMap.erase(castDisplayId);
            TAG_LOGD(AceLogTag::ACE_DEFAULT_DOMAIN,
                "OnAttributeChange skip (no consumers), invalidated displayId=%{public}" PRIu64, castDisplayId);
            return;
        }

        auto freshInfo = FetchBaseDisplayInfo(castDisplayId);
        if (!freshInfo) {
            TAG_LOGE(AceLogTag::ACE_DEFAULT_DOMAIN, "OnAttributeChange: FetchBaseDisplayInfo failed for displayId=%{public}" PRIu64,
                castDisplayId);
            return;
        }
        uint64_t actualId = freshInfo->GetDisplayId();
        int32_t newWidth = freshInfo->GetWidth();
        int32_t newHeight = freshInfo->GetHeight();
        Rotation newRotation = freshInfo->GetRotation();

        // Diff detection as race-condition guard (server-side already filters).
        bool changed = false;
        {
            std::lock_guard<std::mutex> lock(g_cachedDisplayInfoMutex);
            auto it = g_cachedDisplayInfoMap.find(actualId);
            if (it != g_cachedDisplayInfoMap.end()) {
                changed = (it->second->GetWidth() != newWidth || it->second->GetHeight() != newHeight ||
                           it->second->GetRotation() != newRotation);
                if (changed) {
                    it->second->SetWidth(newWidth);
                    it->second->SetHeight(newHeight);
                    it->second->SetRotation(newRotation);
                }
            } else {
                g_cachedDisplayInfoMap[actualId] = freshInfo;
                changed = true;
            }
        }
        if (!changed) {
            TAG_LOGD(AceLogTag::ACE_DEFAULT_DOMAIN,
                "OnAttributeChange no change detected displayId=%{public}" PRIu64, actualId);
            return;
        }
        TAG_LOGD(AceLogTag::ACE_DEFAULT_DOMAIN,
            "OnAttributeChange updated displayId=%{public}" PRIu64 " w=%{public}d h=%{public}d rot=%{public}u",
            actualId, newWidth, newHeight, static_cast<uint32_t>(newRotation));

        // Copy callbacks under lock, dispatch outside lock.
        std::vector<DisplayManager::DisplaySizeChangeCallback> callbacksCopy;
        {
            std::lock_guard<std::mutex> lock(g_callbackMutex);
            callbacksCopy.reserve(g_displaySizeChangeCallbacks.size());
            for (const auto& [id, callback] : g_displaySizeChangeCallbacks) {
                callbacksCopy.push_back(callback);
            }
        }
        for (const auto& callback : callbacksCopy) {
            callback(newWidth, newHeight, newRotation, actualId);
        }
        TAG_LOGD(AceLogTag::ACE_DEFAULT_DOMAIN,
            "OnAttributeChange dispatched %{public}zu callback(s) displayId=%{public}" PRIu64,
            callbacksCopy.size(), actualId);
    }
};

bool EnsureListenersRegistered()
{
    std::lock_guard<std::mutex> lock(g_registerMutex);
    if (g_displayRegistered || g_displayAttemptCount >= MAX_REGISTER_RETRY) {
        return g_displayRegistered;
    }
    g_displayAttemptCount++;

    if (!g_displayListener) {
        g_displayListener = sptr<DisplayListenerImpl>::MakeSptr();
    }
    if (!g_attributeListener) {
        g_attributeListener = sptr<AttributeListenerImpl>::MakeSptr();
    }

    // Register IDisplayListener (OnCreate/OnDestroy active, OnChange no-op).
    auto retListener = Rosen::DisplayManager::GetInstance().RegisterDisplayListener(g_displayListener);
    if (retListener == Rosen::DMError::DM_OK) {
        g_displayListenerRegistered = true;
    } else {
        TAG_LOGE(AceLogTag::ACE_DEFAULT_DOMAIN, "RegisterDisplayListener failed: %{public}d (attempt %{public}d/%{public}d)",
            static_cast<int32_t>(retListener), g_displayAttemptCount, MAX_REGISTER_RETRY);
    }

    // Register IDisplayAttributeListener (server-side filtered for width/height/rotation).
    std::vector<std::string> listenAttributes = {"width", "height", "rotation"};
    auto retAttr = Rosen::DisplayManager::GetInstance().RegisterDisplayAttributeListener(
        listenAttributes, g_attributeListener);
    if (retAttr == Rosen::DMError::DM_OK) {
        g_attributeListenerRegistered = true;
        TAG_LOGI(AceLogTag::ACE_DEFAULT_DOMAIN, "AttributeListener registered (attempt %{public}d/%{public}d)",
            g_displayAttemptCount, MAX_REGISTER_RETRY);
    } else {
        TAG_LOGE(AceLogTag::ACE_DEFAULT_DOMAIN, "RegisterAttributeListener failed: %{public}d (attempt %{public}d/%{public}d)",
            static_cast<int32_t>(retAttr), g_displayAttemptCount, MAX_REGISTER_RETRY);
    }

    // Core functionality depends on AttributeListener.
    g_displayRegistered = g_attributeListenerRegistered;
    return g_displayRegistered;
}
} // namespace

DisplayManager& DisplayManager::GetInstance()
{
    static DisplayManagerOhos instance;
    return instance;
}

DisplayManagerOhos::DisplayManagerOhos()
{
    TAG_LOGI(AceLogTag::ACE_DEFAULT_DOMAIN, "DisplayManagerOhos created");
}

DisplayManagerOhos::~DisplayManagerOhos()
{
    TAG_LOGI(AceLogTag::ACE_DEFAULT_DOMAIN, "DisplayManagerOhos destroying, unregistering listeners");
    if (g_displayListener) {
        Rosen::DisplayManager::GetInstance().UnregisterDisplayListener(g_displayListener);
        g_displayListener = nullptr;
    }
    if (g_attributeListener) {
        Rosen::DisplayManager::GetInstance().UnRegisterDisplayAttributeListener(g_attributeListener);
        g_attributeListener = nullptr;
    }
}

bool DisplayManagerOhos::ConvertScreenIdToRsScreenId(uint64_t screenId, uint64_t& rsScreenId)
{
    return Rosen::DisplayManager::GetInstance().ConvertScreenIdToRsScreenId(screenId, rsScreenId);
}

FoldDisplayMode DisplayManagerOhos::GetFoldDisplayMode()
{
    return static_cast<FoldDisplayMode>(static_cast<uint32_t>(
        Rosen::DisplayManager::GetInstance().GetFoldDisplayMode()));
}

RefPtr<BaseDisplayInfo> DisplayManagerOhos::GetCachedDisplayInfo(uint64_t displayId)
{
    {
        std::lock_guard<std::mutex> lock(g_cachedDisplayInfoMutex);
        auto it = g_cachedDisplayInfoMap.find(displayId);
        if (it != g_cachedDisplayInfoMap.end()) {
            return it->second;
        }
    }
    TAG_LOGD(AceLogTag::ACE_DEFAULT_DOMAIN,
        "GetCachedDisplayInfo cache miss displayId=%{public}" PRIu64, displayId);
    EnsureListenersRegistered();
    auto cachedInfo = FetchBaseDisplayInfo(displayId);
    if (!cachedInfo) {
        TAG_LOGE(AceLogTag::ACE_DEFAULT_DOMAIN,
            "GetCachedDisplayInfo: FetchBaseDisplayInfo failed for displayId=%{public}" PRIu64, displayId);
        return nullptr;
    }
    {
        std::lock_guard<std::mutex> lock(g_cachedDisplayInfoMutex);
        g_cachedDisplayInfoMap[cachedInfo->GetDisplayId()] = cachedInfo;
    }
    return cachedInfo;
}

uint64_t DisplayManagerOhos::RegisterDisplaySizeChangeCallback(DisplaySizeChangeCallback callback)
{
    CHECK_NULL_RETURN(callback, 0);
    if (!EnsureListenersRegistered()) {
        TAG_LOGE(AceLogTag::ACE_DEFAULT_DOMAIN, "RegisterDisplaySizeChangeCallback: listener registration not available");
        return 0;
    }
    uint64_t callbackId = 0;
    {
        std::lock_guard<std::mutex> lock(g_callbackMutex);
        callbackId = g_nextCallbackId++;
        g_displaySizeChangeCallbacks[callbackId] = std::move(callback);
    }
    TAG_LOGD(AceLogTag::ACE_DEFAULT_DOMAIN,
        "RegisterDisplaySizeChangeCallback id=%{public}" PRIu64, callbackId);
    return callbackId;
}

void DisplayManagerOhos::UnregisterDisplaySizeChangeCallback(uint64_t callbackId)
{
    if (callbackId == 0) {
        return;
    }
    {
        std::lock_guard<std::mutex> lock(g_callbackMutex);
        g_displaySizeChangeCallbacks.erase(callbackId);
    }
    TAG_LOGD(AceLogTag::ACE_DEFAULT_DOMAIN,
        "UnregisterDisplaySizeChangeCallback id=%{public}" PRIu64, callbackId);
}
} // namespace OHOS::Ace
