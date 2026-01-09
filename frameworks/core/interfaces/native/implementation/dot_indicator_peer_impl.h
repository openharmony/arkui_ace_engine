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

#ifndef FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPLEMENTATION_DOT_INDICATOR_PEER_IMPL_H
#define FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPLEMENTATION_DOT_INDICATOR_PEER_IMPL_H

#include "core/interfaces/native/implementation/indicator_peer_impl.h"
#include "core/components_ng/pattern/swiper/swiper_model_static.h"

struct DotIndicatorPeer : public IndicatorPeer {
public:
    DotIndicatorPeer() = default;
    void SetItemWidth(const std::optional<OHOS::Ace::Dimension>& value)
    {
        itemWidth_ = value;
    }

    void SetItemHeight(const std::optional<OHOS::Ace::Dimension>& value)
    {
        itemHeight_ = value;
    }

    void SetSelectedItemWidth(const std::optional<OHOS::Ace::Dimension>& value)
    {
        selectedItemWidth_ = value;
    }

    void SetSelectedItemHeight(const std::optional<OHOS::Ace::Dimension>& value)
    {
        selectedItemHeight_ = value;
    }

    void SetMask(const std::optional<bool>& value)
    {
        maskValue_ = value;
    }

    void SetColor(const std::optional<OHOS::Ace::Color>& value)
    {
        colorVal_ = value;
    }

    void SetSelectedColor(const std::optional<OHOS::Ace::Color>& value)
    {
        selectedColorVal_ = value;
    }

    void SetMaxDisplayCount(const std::optional<int32_t>& value)
    {
        maxDisplayCountVal_ = value;
    }

    void SetSpace(const std::optional<OHOS::Ace::Dimension>& value)
    {
        dimSpace_ = value;
    }

    OHOS::Ace::SwiperParameters GetDotParameters()
    {
        OHOS::Ace::SwiperParameters p;
        p.dimLeft = dimLeft_;
        p.dimTop = dimTop_;
        p.dimRight = dimRight_;
        p.dimBottom = dimBottom_;
        p.dimStart = dimStart_;
        p.dimEnd = dimEnd_;
        p.ignoreSizeValue = ignoreSize_;
        p.itemWidth = itemWidth_;
        p.itemHeight = itemHeight_;
        p.selectedItemWidth = selectedItemWidth_;
        p.selectedItemHeight = selectedItemHeight_;
        p.maskValue = maskValue_;
        p.colorVal = colorVal_;
        p.selectedColorVal = selectedColorVal_;
        p.maxDisplayCountVal = maxDisplayCountVal_;
        p.dimSpace = dimSpace_;
        return p;
    }
protected:
    std::optional<OHOS::Ace::Dimension> itemWidth_;
    std::optional<OHOS::Ace::Dimension> itemHeight_;
    std::optional<OHOS::Ace::Dimension> selectedItemWidth_;
    std::optional<OHOS::Ace::Dimension> selectedItemHeight_;
    std::optional<bool> maskValue_;
    std::optional<OHOS::Ace::Color> colorVal_;
    std::optional<OHOS::Ace::Color> selectedColorVal_;
    std::optional<int32_t> maxDisplayCountVal_;
    std::optional<OHOS::Ace::Dimension> dimSpace_;
};

#endif // FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPLEMENTATION_DOT_INDICATOR_PEER_IMPL_H