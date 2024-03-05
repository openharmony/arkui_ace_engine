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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LOADING_PROGRESS_LOADING_PROGRESS_UTILLL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LOADING_PROGRESS_LOADING_PROGRESS_UTILLL_H

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_base.h"
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_INDEX = 3;
constexpr uint32_t SIZE = 6;
const Dimension RING_STROKE_WIDTH[] = { 1.12_vp, 1.5_vp, 1.76_vp, 1.9_vp, 2.16_vp, 2.28_vp };
const Dimension COMET_RADIUS[] = { 1.2_vp, 1.8_vp, 2.4_vp, 3.0_vp, 3.36_vp, 4.18_vp };
const Dimension DIAMETER[] = { 16.0_vp, 24.0_vp, 32.0_vp, 40.0_vp, 48.0_vp, 76.0_vp};
const float RING_DARK_RADIUS_16VP = 0.5f;
const float RING_DARK_RADIUS_40VP = 0.2f;
const float RING_DARK_RADIUS_76VP = 0.1f;
const float RING_DARK_BACKGROUND_WIDTH_40VP = 3.0f;
const float RING_DARK_BACKGROUND_WIDTH_76VP = 2.0f;
const float RING_DARK_BACKGROUND_RADIUS = 2.0f;
const Dimension MODE_16 = 16.0_vp;
const Dimension MODE_24 = 24.0_vp;
const Dimension MODE_32 = 32.0_vp;
const Dimension MODE_40 = 40.0_vp;
const Dimension MODE_48 = 48.0_vp;
const Dimension MODE_76 = 76.0_vp;

constexpr Dimension RING_RADIUS_BASE40 = 10.5_vp;
constexpr Dimension ORBIT_RADIUS_BASE40 = 17.0_vp;
} // namespace
class LoadingProgressUtill {
public:
    LoadingProgressUtill() = default;
    ~LoadingProgressUtill() = default;

    static float GetRingRadius(float diameter)
    {
        return RING_RADIUS_BASE40.ConvertToPx() * diameter / MODE_40.ConvertToPx();
    }

    static float GetOrbitRadius(float diameter)
    {
        return ORBIT_RADIUS_BASE40.ConvertToPx() * diameter / MODE_40.ConvertToPx();
    }

    static float GetRingStrokeWidth(float diameter)
    {
        if (LessOrEqual(diameter, MODE_16.ConvertToPx())) {
            return diameter / MODE_16.ConvertToPx() * RING_STROKE_WIDTH[0].ConvertToPx();
        } else if (GreatOrEqual(diameter, MODE_76.ConvertToPx())) {
            return GetMostStrokeWidth(diameter);
        } else {
            for (uint32_t index = 1; index < SIZE; index++) {
                if (LessOrEqual(diameter, DIAMETER[index].ConvertToPx())) {
                    return CalculateValue(diameter, DIAMETER[index - 1].ConvertToPx(), DIAMETER[index].ConvertToPx(),
                        RING_STROKE_WIDTH[index - 1].ConvertToPx(), RING_STROKE_WIDTH[index].ConvertToPx());
                }
            }
        }
        return RING_STROKE_WIDTH[DEFAULT_INDEX].ConvertToPx();
    }

    static float GetRingDarkRadius(float diameter)
    {
        if (LessOrEqual(diameter, MODE_16.ConvertToPx())) {
            return Dimension(RING_DARK_RADIUS_16VP * (diameter / MODE_40.ConvertToPx()), DimensionUnit::VP)
                .ConvertToPx();
        } else if (GreatOrEqual(diameter, MODE_76.ConvertToPx())) {
            return Dimension(RING_DARK_RADIUS_76VP * (diameter / MODE_40.ConvertToPx()), DimensionUnit::VP)
                .ConvertToPx();
        } else {
            return Dimension(RING_DARK_RADIUS_40VP * (diameter / MODE_40.ConvertToPx()), DimensionUnit::VP)
                .ConvertToPx();
        }
    }

    static float GetRingDarkBackgroundWidth(float diameter)
    {
        if (LessOrEqual(diameter, MODE_40.ConvertToPx())) {
            return Dimension(RING_DARK_BACKGROUND_WIDTH_40VP * (diameter / MODE_40.ConvertToPx()), DimensionUnit::VP)
                .ConvertToPx();
        } else {
            return Dimension(RING_DARK_BACKGROUND_WIDTH_76VP * (diameter / MODE_40.ConvertToPx()), DimensionUnit::VP)
                .ConvertToPx();
        }
    }

    static float GetRingDarkBackgroundRadius(float diameter)
    {
        return Dimension(RING_DARK_BACKGROUND_RADIUS * (diameter / MODE_40.ConvertToPx()), DimensionUnit::VP)
            .ConvertToPx();
    }

    static float GetCometRadius(float diameter)
    {
        if (LessOrEqual(diameter, MODE_16.ConvertToPx())) {
            return diameter / MODE_16.ConvertToPx() * COMET_RADIUS[0].ConvertToPx();
        } else if (GreatOrEqual(diameter, MODE_76.ConvertToPx())) {
            return GetMostCometRadius(diameter);
        } else {
            for (uint32_t index = 1; index < SIZE; index++) {
                if (LessOrEqual(diameter, DIAMETER[index].ConvertToPx())) {
                    return CalculateValue(diameter, DIAMETER[index - 1].ConvertToPx(), DIAMETER[index].ConvertToPx(),
                        COMET_RADIUS[index - 1].ConvertToPx(), COMET_RADIUS[index].ConvertToPx());
                }
            }
        }
        return COMET_RADIUS[DEFAULT_INDEX].ConvertToPx();
    }

    static float GetMostStrokeWidth(float diameter)
    {
        auto index_76 = static_cast<uint32_t>(LoadingProgressBase::BASE76);
        auto strokeWidth_76 =
            RING_STROKE_WIDTH[index_76].ConvertToPx() / (MODE_76.ConvertToPx() / MODE_40.ConvertToPx());
        return strokeWidth_76 * (diameter / MODE_40.ConvertToPx());
    }

    static float GetMostCometRadius(float diameter)
    {
        auto index_76 = static_cast<uint32_t>(LoadingProgressBase::BASE76);
        auto cometRadius_76 = COMET_RADIUS[index_76].ConvertToPx() / (MODE_76.ConvertToPx() / MODE_40.ConvertToPx());
        return cometRadius_76 * (diameter / MODE_40.ConvertToPx());
    }

private:
    static float CalculateValue(float inputValue, float minInput, float maxInput, float minOutPut, float maxOutput)
    {
        auto inputScale = (inputValue - minInput) / (maxInput - minInput);
        return (maxOutput - minOutPut) * inputScale + minOutPut;
    }
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LOADING_PROGRESS_LOADING_PROGRESS_UTILLL_H
