/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_PLACEMENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_PLACEMENT_H

namespace OHOS::Ace {

enum class Placement : int32_t {
    LEFT = 0,
    RIGHT,
    TOP,
    BOTTOM,
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT,
    LEFT_TOP,
    LEFT_BOTTOM,
    RIGHT_TOP,
    RIGHT_BOTTOM,
    NONE,
};

class PlacementUtils {
public:
    static std::string ConvertPlacementToString(Placement placement)
    {
        std::string placementStr;
        switch (placement) {
            case Placement::LEFT:
                placementStr = "Placement.LEFT";
                break;
            case Placement::RIGHT:
                placementStr = "Placement.RIGHT";
                break;
            case Placement::TOP:
                placementStr = "Placement.TOP";
                break;
            case Placement::BOTTOM:
                placementStr = "Placement.BOTTOM";
                break;
            case Placement::TOP_LEFT:
                placementStr = "Placement.TOP_LEFT";
                break;
            case Placement::TOP_RIGHT:
                placementStr = "Placement.TOP_RIGHT";
                break;
            case Placement::BOTTOM_LEFT:
                placementStr = "Placement.BOTTOM_LEFT";
                break;
            case Placement::BOTTOM_RIGHT:
                placementStr = "Placement.BOTTOM_RIGHT";
                break;
            case Placement::LEFT_TOP:
                placementStr = "Placement.LEFT_TOP";
                break;
            case Placement::LEFT_BOTTOM:
                placementStr = "Placement.LEFT_BOTTOM";
                break;
            case Placement::RIGHT_TOP:
                placementStr = "Placement.RIGHT_TOP";
                break;
            case Placement::RIGHT_BOTTOM:
                placementStr = "Placement.RIGHT_BOTTOM";
                break;
            case Placement::NONE:
                placementStr = "Placement.NONE";
                break;
            default:
                placementStr = "Placement.DEFAULT";
        }
        return placementStr;
    }
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_PLACEMENT_H
