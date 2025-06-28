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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_INDICATOR_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_INDICATOR_MODEL_NG_H
 
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT IndicatorModelNG : public OHOS::Ace::IndicatorModel {
public:
    RefPtr<IndicatorController> Create() override;
    void SetCount(uint32_t count) override;
    void SetInitialIndex(uint32_t index) override;
    void SetLoop(bool loop) override;
    void SetDirection(Axis axis) override;
    void SetIndicatorType(SwiperIndicatorType indicatorType) override;
    void SetIndicatorStyle(const SwiperParameters& swiperParameters) override;

    void SetDotIndicatorStyle(const SwiperParameters& swiperParameters) override;
    void SetDigitIndicatorStyle(const SwiperDigitalParameters& swiperDigitalParameters) override;
    void SetOnChange(std::function<void(const BaseEventInfo* info)>&& onChange) override;
    void SetShowIndicator(bool showIndicator) override;
    void SetIsIndicatorCustomSize(bool isCustomSize) override;
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetOnChange(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& onChange);
    static void SetDigitIndicatorStyle(FrameNode* frameNode, const SwiperDigitalParameters& swiperDigitalParameters);
    static void SetDotIndicatorStyle(FrameNode* frameNode, const SwiperParameters& swiperParameters);
    static void SetIndicatorType(FrameNode* frameNode, SwiperIndicatorType indicatorType);

    static bool GetLoop(FrameNode* frameNode);
    static void SetInitialIndex(FrameNode* frameNode, uint32_t index);
    static void SetCount(FrameNode* frameNode, uint32_t count);
    static void SetLoop(FrameNode* frameNode, bool loop);
    static void SetDirection(FrameNode* frameNode, Axis axis);
    static void SetIsIndicatorCustomSize(FrameNode* frameNode, bool isCustomSize);
    static void SetShowIndicator(FrameNode* frameNode, bool showIndicator);
    static int32_t GetCount(FrameNode* frameNode);
    static void ProcessDotSizeWithResourceObj(FrameNode* frameNode, const std::string& name,
        const RefPtr<ResourceObject>& resObj);
    static void ProcessDotColorWithResourceObj(FrameNode* frameNode, const std::string& name,
        const RefPtr<ResourceObject>& resObj);
    static void ProcessDigitalFontSizeWithResourceObj(FrameNode* frameNode, const std::string& name,
        const RefPtr<ResourceObject>& resObj);
    static void ProcessDigitalColorWithResourceObj(FrameNode* frameNode, const std::string& name,
        const RefPtr<ResourceObject>& resObj);
    static void CreateDotWithResourceObj(FrameNode*  frameNode, const SwiperParameters& swiperParameters);
    static void CreateDigitWithResourceObj(FrameNode*  frameNode,
        const SwiperDigitalParameters& swiperDigitalParameters);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_INDICATOR_MODEL_NG_H
