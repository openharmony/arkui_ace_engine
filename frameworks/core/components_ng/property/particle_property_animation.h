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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PARTICLE_PROPERTY_ANIMATION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PARTICLE_PROPERTY_ANIMATION_H
#include <string>

#include "core/animation/curve.h"
#include "core/common/resource/resource_object.h"
namespace OHOS::Ace::NG {
template<typename T>
struct ParticlePropertyAnimation {
public:
    T GetFrom() const
    {
        return from_;
    }

    void SetFrom(T& from)
    {
        from_ = from;
    }

    T GetTo() const
    {
        return to_;
    }

    void SetTo(T& to)
    {
        to_ = to;
    }

    int32_t GetStartMills() const
    {
        return startMills_;
    }

    void SetStartMills(int32_t startMills)
    {
        startMills_ = startMills;
    }

    int32_t GetEndMills() const
    {
        return endMills_;
    }

    void SetEndMills(int32_t endMills)
    {
        endMills_ = endMills;
    }

    RefPtr<Curve> GetCurve() const
    {
        return curve_;
    }

    void SetCurve(RefPtr<Curve> curve)
    {
        curve_ = curve;
    }
    void AddResource(
        const std::string& key,
        const RefPtr<ResourceObject>& resObj,
        std::function<void(const RefPtr<ResourceObject>&, ParticlePropertyAnimation<T>&)>&& updateFunc)
    {
        if (resObj == nullptr || !updateFunc) {
            return;
        }
        particleColorResMap_[key] = { resObj, std::move(updateFunc) };
    }
 
    void ReloadResources()
    {
        for (const auto& [key, resourceUpdater] : particleColorResMap_) {
            resourceUpdater.updateFunc(resourceUpdater.obj, *this);
        }
    }

    void RemoveResource(const std::string& key)
    {
        auto iter = particleColorResMap_.find(key);
        if (iter != particleColorResMap_.end()) {
            particleColorResMap_.erase(iter);
        }
    }

    bool operator==(const ParticlePropertyAnimation<T>& other) const
    {
        bool isCurveEqual = (curve_ && curve_->IsEqual(other.GetCurve())) || (!curve_ && !other.GetCurve());
        return NearEqual(from_, other.GetFrom()) && NearEqual(to_, other.GetTo()) &&
               (startMills_ == other.GetStartMills()) && (endMills_ == other.GetEndMills()) &&
               isCurveEqual;
    }

    std::string ToString() const
    {
        std::string str;
        str.append("startMills: [").append(std::to_string(startMills_)).append("]");
        str.append("endMills: [").append(std::to_string(endMills_)).append("]");
        str.append("curve: [").append(curve_ ? curve_->ToString() : "NA").append("]");
        return str;
    }

private:
    struct ResourceUpdater {
        RefPtr<ResourceObject> obj;
        std::function<void(const RefPtr<ResourceObject>&, ParticlePropertyAnimation<T>&)> updateFunc;
    };
    std::unordered_map<std::string, ResourceUpdater> particleColorResMap_;
    T from_;
    T to_;
    int32_t startMills_ = 0;
    int32_t endMills_ = 0;
    RefPtr<Curve> curve_;
};
} // namespace OHOS::Ace::NG
#endif