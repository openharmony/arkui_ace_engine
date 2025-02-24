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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_relative_container_ffi.h"

#include "core/components_ng/pattern/relative_container/relative_container_model_ng.h"

using namespace OHOS::Ace;

namespace {
    constexpr int32_t LOCALIZED_BARRIER_DIRECTION_START = 4;
}

extern "C" {
    void FfiOHOSAceFrameworkRelativeContainerCreate()
    {
        RelativeContainerModel::GetInstance()->Create();
    }

    void FfiOHOSAceFrameworkReletiveContainerGuideLine(CGuideLineInfos guidelines)
    {
        std::vector<GuidelineInfo> guidelineInfos;
        if (guidelines.guideline == nullptr || guidelines.size == 0) {
            RelativeContainerModel::GetInstance()->SetGuideline(guidelineInfos);
            return;
        }
        
        for (int64_t i = 0; i < guidelines.size; i++) {
            GuidelineInfo guidelineInfoItem;
            CGuideLineStyle guideline = guidelines.guideline[i];
            guidelineInfoItem.id = std::string(guideline.id);
            guidelineInfoItem.direction = static_cast<LineDirection>(guideline.direction);
            // parse dimension
            if (guideline.position.start.unit > 0) {
                guidelineInfoItem.start = CalcDimension(guideline.position.start.value,
                    static_cast<DimensionUnit>(guideline.position.start.unit));
            }
            if (guideline.position.end.unit > 0) {
                guidelineInfoItem.end = CalcDimension(guideline.position.end.value,
                    static_cast<DimensionUnit>(guideline.position.end.unit));
            }
            guidelineInfos.emplace_back(guidelineInfoItem);
        }
        RelativeContainerModel::GetInstance()->SetGuideline(guidelineInfos);
    }

    void FfiOHOSAceFrameworkReletiveContainerBarrier(CBarrierInfos barriers)
    {
        std::vector<BarrierInfo> barrierInfos;
        if (barriers.barrier == nullptr || barriers.size == 0) {
            RelativeContainerModel::GetInstance()->SetBarrier(barrierInfos);
            return;
        }
        for (int64_t i = 0; i < barriers.size; i++) {
            BarrierInfo barrierInfoItem;
            CBarrierStyle barrier = barriers.barrier[i];
            barrierInfoItem.id = std::string(barrier.id);
            barrierInfoItem.direction = static_cast<BarrierDirection>(barrier.direction);
            for (int64_t j = 0; j < barrier.referencedId.size; j++) {
                if (barrier.referencedId.head[j] != nullptr) {
                    barrierInfoItem.referencedId.emplace_back(std::string(barrier.referencedId.head[j]));
                }
            }
            barrierInfos.emplace_back(barrierInfoItem);
        }
        RelativeContainerModel::GetInstance()->SetBarrier(barrierInfos);
    }

    void FfiOHOSAceFrameworkReletiveContainerLocalizedBarrier(CLocalizedBarrierInfos barriers)
    {
        std::vector<BarrierInfo> barrierInfos;
        if (barriers.localizedBarrier == nullptr || barriers.size == 0) {
            RelativeContainerModel::GetInstance()->SetBarrier(barrierInfos);
            return;
        }
        for (int64_t i = 0; i < barriers.size; i++) {
            BarrierInfo barrierInfoItem;
            CLocalizedBarrierStyle barrier = barriers.localizedBarrier[i];
            barrierInfoItem.id = std::string(barrier.id);
            
            if (barrier.localizedDirection > static_cast<int32_t>(BarrierDirection::RIGHT)) {
                barrierInfoItem.direction = static_cast<BarrierDirection>(barrier.localizedDirection);
            } else {
                barrierInfoItem.direction =
                    static_cast<BarrierDirection>(barrier.localizedDirection + LOCALIZED_BARRIER_DIRECTION_START);
            }

            for (int64_t j = 0; j < barrier.referencedId.size; j++) {
                if (barrier.referencedId.head[j] != nullptr) {
                    barrierInfoItem.referencedId.emplace_back(std::string(barrier.referencedId.head[j]));
                }
            }
            barrierInfos.emplace_back(barrierInfoItem);
        }
        RelativeContainerModel::GetInstance()->SetBarrier(barrierInfos);
    }
}
