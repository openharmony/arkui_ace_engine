/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPLEMENTATION_DIGIT_INDICATOR_PEER_IMPL_H
#define FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPLEMENTATION_DIGIT_INDICATOR_PEER_IMPL_H

#include "core/interfaces/native/implementation/indicator_peer_impl.h"
#include "core/components_ng/pattern/swiper/swiper_model_static.h"

struct DigitIndicatorPeer : public IndicatorPeer {
public:
    DigitIndicatorPeer() = default;
    void SetFontColor(const std::optional<OHOS::Ace::Color>& value)
    {
        fontColor_ = value;
    }

    void SetSelectedFontColor(const std::optional<OHOS::Ace::Color>& value)
    {
        selectedFontColor_ = value;
    }

    void SetFontSize(const std::optional<OHOS::Ace::Dimension>& value)
    {
        fontSize_ = value;
    }

    void SetFontWeight(const std::optional<OHOS::Ace::FontWeight>& value)
    {
        fontWeight_ = value;
    }

    void SetSelectedFontSize(const std::optional<OHOS::Ace::Dimension>& value)
    {
        selectedFontSize_ = value;
    }

    void SetSelectedFontWeight(const std::optional<OHOS::Ace::FontWeight>& value)
    {
        selectedFontWeight_ = value;
    }

    OHOS::Ace::SwiperDigitalParameters GetDigitParameters()
    {
        OHOS::Ace::SwiperDigitalParameters p;
        p.dimLeft = dimLeft_;
        p.dimTop = dimTop_;
        p.dimRight = dimRight_;
        p.dimBottom = dimBottom_;
        p.dimStart = dimStart_;
        p.dimEnd = dimEnd_;
        p.ignoreSizeValue = ignoreSize_;
        p.fontColor = fontColor_;
        p.selectedFontColor = selectedFontColor_;
        p.fontSize = fontSize_;
        p.fontWeight = fontWeight_;
        p.selectedFontSize = selectedFontSize_;
        p.selectedFontWeight = selectedFontWeight_;
        return p;
    }
protected:
    std::optional<OHOS::Ace::Color> fontColor_;
    std::optional<OHOS::Ace::Color> selectedFontColor_;
    std::optional<OHOS::Ace::Dimension> fontSize_;
    std::optional<OHOS::Ace::Dimension> selectedFontSize_;
    std::optional<OHOS::Ace::FontWeight> fontWeight_;
    std::optional<OHOS::Ace::FontWeight> selectedFontWeight_;
};

#endif // FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPLEMENTATION_DIGIT_INDICATOR_PEER_IMPL_H