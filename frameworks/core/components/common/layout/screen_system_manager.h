/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_LAYOUT_SCREEN_SYSTEM_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_LAYOUT_SCREEN_SYSTEM_MANAGER_H

#include <array>
#include <map>
#include <string>

#include "base/geometry/dimension.h"
#include "base/log/log.h"
#include "base/utils/noncopyable.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace {
enum class ScreenSizeType {
    UNDEFINED = 0,
    XS,
    SM,
    MD,
    LG,
    XL,
};

constexpr size_t SCREEN_SIZE_COUNT = static_cast<size_t>(ScreenSizeType::XL) + 1;
const inline std::map<ScreenSizeType, std::string> SCREEN_SIZE_VALUES = {
    {ScreenSizeType::XS, "xs"},
    {ScreenSizeType::SM, "sm"},
    {ScreenSizeType::MD, "md"},
    {ScreenSizeType::LG, "lg"},
    {ScreenSizeType::XL, "xl"},
};

inline bool IsValid(ScreenSizeType val)
{
    return static_cast<size_t>(val) < SCREEN_SIZE_COUNT;
}

class ScreenSystemManager final {
public:
    static ScreenSystemManager& GetInstance();

    void SetWindowInfo(double screenWidth, double density, double dipScale)
    {
        std::lock_guard<std::mutex> guard(lock);
        screenWidth_ = screenWidth;
        density_ = density;
        dipScale_ = dipScale;
        viewScale_ = density / dipScale;
    }

    void SetWindowInfo(double density, double dipScale)
    {
        std::lock_guard<std::mutex> guard(lock);
        density_ = density;
        dipScale_ = dipScale;
        viewScale_ = density / dipScale;
    }

    void OnSurfaceChanged(double width);

    double GetScreenWidth(const RefPtr<PipelineBase>& pipeline = nullptr) const
    {
        std::lock_guard<std::mutex> guard(lock);
        if (pipeline) {
            return pipeline->GetRootWidth();
        }
        return screenWidth_;
    }

    double GetDipScale() const
    {
        std::lock_guard<std::mutex> guard(lock);
        return dipScale_;
    }

    ScreenSizeType GetSize(double width) const;

    ScreenSizeType GetCurrentSize() const
    {
        std::lock_guard<std::mutex> guard(lock);
        return currentSize_;
    }

    double GetDensity() const
    {
        std::lock_guard<std::mutex> guard(lock);
        return density_;
    }

private:
    double screenWidth_ = 0.0;
    double density_ = 1.0;
    double dipScale_ = 1.0;
    double viewScale_ = 1.0;
    ScreenSizeType currentSize_ = ScreenSizeType::UNDEFINED;

private:
    ScreenSystemManager() = default;
    ~ScreenSystemManager() = default;
    static std::mutex lock;
    ACE_DISALLOW_COPY_AND_MOVE(ScreenSystemManager);
};

inline ScreenSystemManager& ScreenSystemManager::GetInstance()
{
    static ScreenSystemManager instance;
    return instance;
}

template<typename T>
class ArrayByScreenType final {
public:
    ArrayByScreenType() = default;
    ArrayByScreenType(const T& defValue)
    {
        std::fill(values_.begin(), values_.end(), defValue);
    }

    ~ArrayByScreenType() = default;

    const T& operator [](ScreenSizeType idx) const
    {
        return values_[static_cast<size_t>(idx)];
    }

    T& operator [](ScreenSizeType idx)
    {
        return values_[static_cast<size_t>(idx)];
    }

    const T& GetCurrentValue() const
    {
        auto idx = ScreenSystemManager::GetInstance().GetCurrentSize();
        return values_[static_cast<size_t>(idx)];
    }

    T& GetCurrentValue()
    {
        auto idx = ScreenSystemManager::GetInstance().GetCurrentSize();
        return values_[static_cast<size_t>(idx)];
    }
private:
    std::array<T, SCREEN_SIZE_COUNT> values_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_LAYOUT_SCREEN_SYSTEM_MANAGER_H
