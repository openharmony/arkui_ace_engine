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

#include "core/components_ng/pattern/pattern.h"

#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/corner_mark/corner_mark.h"

namespace OHOS::Ace::NG {
void Pattern::OnColorModeChange(uint32_t colorMode)
{
    if (resourceMgr_) {
        resourceMgr_->ReloadResources();
    }
}

void Pattern::AddResObj(
    const std::string& key,
    const RefPtr<ResourceObject>& resObj,
    std::function<void(const RefPtr<ResourceObject>&)>&& updateFunc)
{
    if (resourceMgr_ == nullptr) {
        resourceMgr_ = MakeRefPtr<PatternResourceManager>();
    }
    resourceMgr_->AddResource(key, resObj, std::move(updateFunc));
}

void Pattern::AddResCache(const std::string& key, const std::string& value)
{
    if (resourceMgr_ == nullptr) {
        resourceMgr_ = MakeRefPtr<PatternResourceManager>();
    }
    resourceMgr_->AddResCache(key, value);
}

std::string Pattern::GetResCacheMapByKey(const std::string& key)
{
    if (resourceMgr_ == nullptr) {
        return "";
    }
    return resourceMgr_->GetResCacheMapByKey(key);
}

void Pattern::RemoveResObj(const std::string& key)
{
    if (resourceMgr_) {
        resourceMgr_->RemoveResource(key);
        if (resourceMgr_->Empty()) {
            resourceMgr_ = nullptr;
        }
    }
}

int32_t Pattern::OnRecvCommand(const std::string& command)
{
    auto json = JsonUtil::ParseJsonString(command);
    if (!json || !json->IsValid() || !json->IsObject()) {
        return RET_FAILED;
    }
    auto event = json->GetString("cmd");
    if (event.compare("click") == 0) {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, RET_FAILED);
        auto eventHub = host->GetEventHub<EventHub>();
        CHECK_NULL_RETURN(eventHub, RET_FAILED);
        if (!eventHub->IsEnabled()) {
            return RET_FAILED;
        }
        auto gestureHub = host->GetOrCreateGestureEventHub();
        CHECK_NULL_RETURN(gestureHub, RET_FAILED);
        auto clickEventFunc = gestureHub->GetClickEvent();
        CHECK_NULL_RETURN(clickEventFunc, RET_FAILED);
        GestureEvent info;
        clickEventFunc(info);
        return RET_SUCCESS;
    } else if (event.compare("ShowCornerMark") == 0) {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, RET_FAILED);
        auto cornerMark = AceType::MakeRefPtr<CornerMark>();
        CHECK_NULL_RETURN(cornerMark, RET_FAILED);
        return cornerMark->ResponseShowCornerMarkEvent(host, command);
    } else {
        return OnInjectionEvent(command);
    }
    return RET_FAILED;
}

void Pattern::UnRegisterResource(const std::string& key)
{
    RemoveResObj(key);
}

template<typename T>
void Pattern::RegisterResource(const std::string& key, const RefPtr<ResourceObject>& resObj, T value)
{
    auto&& updateFunc = [weakptr = AceType::WeakClaim(this), key](const RefPtr<ResourceObject>& resObj) {
        auto pattern = weakptr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->UpdateResource<T>(key, resObj);
    };
    AddResObj(key, resObj, std::move(updateFunc));
    UpdateProperty<T>(key, value, GetHost());
}

template void Pattern::RegisterResource<CalcDimension>(
    const std::string&, const RefPtr<ResourceObject>&, CalcDimension);
template void Pattern::RegisterResource<Dimension>(
    const std::string&, const RefPtr<ResourceObject>&, Dimension);
template void Pattern::RegisterResource<Color>(
    const std::string&, const RefPtr<ResourceObject>&, Color);
template void Pattern::RegisterResource<float>(
    const std::string&, const RefPtr<ResourceObject>&, float);
template void Pattern::RegisterResource<std::u16string>(
    const std::string&, const RefPtr<ResourceObject>&, std::u16string);
template void Pattern::RegisterResource<std::string>(
    const std::string&, const RefPtr<ResourceObject>&, std::string);
template void Pattern::RegisterResource<std::vector<std::string>>(
    const std::string&, const RefPtr<ResourceObject>&, std::vector<std::string>);
template<typename T>

void Pattern::UpdateResource(const std::string& key, const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    T value = ParseResObjToValue<T>(resObj);
    UpdateProperty<T>(key, value, frameNode);
}

template<typename T>
T Pattern::ParseResObjToValue(const RefPtr<ResourceObject>& resObj)
{
    T value{};
    CHECK_NULL_RETURN(resObj, value);
    if constexpr (std::is_same_v<T, std::string> || std::is_same_v<T, std::u16string>) {
        ResourceParseUtils::ParseResString(resObj, value);
    } else if constexpr(std::is_same_v<T, Color>) {
        ResourceParseUtils::ParseResColor(resObj, value);
    } else if constexpr(std::is_same_v<T, double>) {
        ResourceParseUtils::ParseResDouble(resObj, value);
    } else if constexpr(std::is_same_v<T, CalcDimension>) {
        ResourceParseUtils::ParseResDimensionFpNG(resObj, value, false);
    } else if constexpr(std::is_same_v<T, float>) {
        double tempValue;
        ResourceParseUtils::ParseResDouble(resObj, tempValue);
    } else if constexpr(std::is_same_v<T, std::vector<std::string>>) {
        ResourceParseUtils::ParseResFontFamilies(resObj, value);
    }
    return value;
}

template<typename T>
void Pattern::UpdateProperty(const std::string& key, T value, RefPtr<FrameNode> frameNode)
{
    UpdatePropertyImpl(key, AceType::MakeRefPtr<PropertyValue<T>>(value), frameNode);
}
} // namespace OHOS::Ace::NG