/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_LAYOUT_BREAK_POINT_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_LAYOUT_BREAK_POINT_H

#include <vector>

namespace OHOS::Ace {

/**
 * @brief Width layout breakpoint configuration
 *
 * Defines the width breakpoints for responsive layout:
 * - XS: Extra Small (< 320vp)
 * - SM: Small (320vp - 600vp)
 * - MD: Medium (600vp - 840vp)
 * - LG: Large (840vp - 1440vp)
 * - XL: Extra Large (> 1440vp)
 * - XXL: Extra Extra Large (if configured)
 */
struct WidthLayoutBreakPoint {
    double widthVPXS_ = 320.0;
    double widthVPSM_ = 600.0;
    double widthVPMD_ = 840.0;
    double widthVPLG_ = 1440.0;
    double widthVPXL_ = -1.0;  // Default disabled

    WidthLayoutBreakPoint() = default;

    WidthLayoutBreakPoint(
        double widthVPXS, double widthVPSM, double widthVPMD, double widthVPLG, double widthVPXL = -1.0)
        : widthVPXS_(widthVPXS), widthVPSM_(widthVPSM), widthVPMD_(widthVPMD), widthVPLG_(widthVPLG),
          widthVPXL_(widthVPXL)
    {}

    WidthLayoutBreakPoint(std::vector<double> breakPoints)
        : widthVPXS_(breakPoints.size() > 0 ? breakPoints[0] : -1.0),
          widthVPSM_(breakPoints.size() > 1 ? breakPoints[1] : -1.0),
          widthVPMD_(breakPoints.size() > 2 ? breakPoints[2] : -1.0),
          widthVPLG_(breakPoints.size() > 3 ? breakPoints[3] : -1.0),
          widthVPXL_(breakPoints.size() > 4 ? breakPoints[4] : -1.0)
    {}

    bool operator==(WidthLayoutBreakPoint& v)
    {
        return widthVPXS_ == v.widthVPXS_ && widthVPSM_ == v.widthVPSM_ && widthVPMD_ == v.widthVPMD_ &&
               widthVPLG_ == v.widthVPLG_ && widthVPXL_ == v.widthVPXL_;
    }

    bool operator==(const WidthLayoutBreakPoint& v)
    {
        return widthVPXS_ == v.widthVPXS_ && widthVPSM_ == v.widthVPSM_ && widthVPMD_ == v.widthVPMD_ &&
               widthVPLG_ == v.widthVPLG_ && widthVPXL_ == v.widthVPXL_;
    }

    bool operator!=(WidthLayoutBreakPoint& v)
    {
        return widthVPXS_ != v.widthVPXS_ || widthVPSM_ != v.widthVPSM_ || widthVPMD_ != v.widthVPMD_ ||
               widthVPLG_ != v.widthVPLG_ || widthVPXL_ != v.widthVPXL_;
    }

    bool operator!=(const WidthLayoutBreakPoint& v)
    {
        return widthVPXS_ != v.widthVPXS_ || widthVPSM_ != v.widthVPSM_ || widthVPMD_ != v.widthVPMD_ ||
               widthVPLG_ != v.widthVPLG_ || widthVPXL_ != v.widthVPXL_;
    }
};

/**
 * @brief Height layout breakpoint configuration
 *
 * Defines the height breakpoints for responsive layout:
 * - SM: Small (< 0.8)
 * - MD: Medium (0.8 - 1.2)
 */
struct HeightLayoutBreakPoint {
    double heightVPRATIOSM_ = 0.8;
    double heightVPRATIOMD_ = 1.2;

    HeightLayoutBreakPoint() = default;

    HeightLayoutBreakPoint(double heightVPRATIOSM, double heightVPRATIOMD)
        : heightVPRATIOSM_(heightVPRATIOSM), heightVPRATIOMD_(heightVPRATIOMD) {}
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_LAYOUT_BREAK_POINT_H
