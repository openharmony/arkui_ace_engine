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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_DISPLAY_INFO_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_DISPLAY_INFO_H

#include "base/geometry/rect.h"
#include "base/memory/ace_type.h"

namespace OHOS::Ace {
/**
 * souce is Rosen::FoldDisplayMode
 */
enum class FoldDisplayMode: uint32_t {
    UNKNOWN = 0,
    FULL = 1,   // EXPAND
    MAIN = 2,   // FOLDED
    SUB = 3,
    COORDINATION = 4,
};

/**
 * souce is Rosen::FoldStatus
 */
enum class FoldStatus : uint32_t {
    UNKNOWN = 0,
    EXPAND = 1,
    FOLDED = 2,
    HALF_FOLD = 3,
};

/**
 * souce is Rosen::Rotation
 */
enum class Rotation : uint32_t {
    ROTATION_0,
    ROTATION_90,
    ROTATION_180,
    ROTATION_270,
};

/**
* source is Rosen::DisplayOrientation
*/
enum class DisplayOrientation : uint32_t {
    PORTRAIT = 0,
    LANDSCAPE,
    PORTRAIT_INVERTED,
    LANDSCAPE_INVERTED,
};

inline bool IsValidDisplayOrientation(DisplayOrientation ori)
{
    return static_cast<int32_t>(DisplayOrientation::PORTRAIT) <= static_cast<int32_t>(ori) &&
        static_cast<int32_t>(DisplayOrientation::LANDSCAPE_INVERTED) >= static_cast<int32_t>(ori);
}

/**
 * souce is Rosen::WindowStatus
 */
enum class WindowStatus : uint32_t {
    WINDOW_STATUS_UNDEFINED = 0,
    WINDOW_STATUS_FULLSCREEN = 1,
    WINDOW_STATUS_MAXMIZE,
    WINDOW_STATUS_MINIMIZE,
    WINDOW_STATUS_FLOATING,
    WINDOW_STATUS_SPLITSCREEN
};

class ACE_EXPORT DisplayInfo : public AceType {
    DECLARE_ACE_TYPE(DisplayInfo, AceType);

public:
    DisplayInfo() = default;
    ~DisplayInfo() override = default;

    bool GetIsFoldable()
    {
        return isFoldable_;
    }

    void SetIsFoldable(bool isFoldable)
    {
        isFoldable_ = isFoldable;
    }

    FoldStatus GetFoldStatus()
    {
        return foldStatus_;
    }

    void SetFoldStatus(FoldStatus foldStatus)
    {
        foldStatus_ = foldStatus;
    }

    Rotation GetRotation()
    {
        return rotation_;
    }

    void SetRotation(Rotation rotation)
    {
        rotation_ = rotation;
    }

    std::vector<Rect> GetCurrentFoldCreaseRegion()
    {
        return currentFoldCreaseRegion_;
    }

    void SetCurrentFoldCreaseRegion(std::vector<Rect> currentFoldCreaseRegion)
    {
        currentFoldCreaseRegion_ = currentFoldCreaseRegion;
    }

    uint64_t GetDisplayId() const
    {
        return displayId_;
    }

    void SetDisplayId(uint64_t displayId)
    {
        displayId_ = displayId;
    }

    int32_t GetWidth() const
    {
        return width_;
    }

    void SetWidth(int32_t width)
    {
        width_ = width;
    }

    int32_t GetHeight() const
    {
        return height_;
    }

    void SetHeight(int32_t height)
    {
        height_ = height;
    }

private:
    FoldStatus foldStatus_ = FoldStatus::UNKNOWN;
    bool isFoldable_ = false;
    Rotation rotation_ = Rotation::ROTATION_0;
    std::vector<Rect> currentFoldCreaseRegion_;
    uint64_t displayId_ = 0;
    int32_t width_ = 0;
    int32_t height_ = 0;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_DISPLAY_INFO_H
