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

#ifndef FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPLEMENTATION_INDICATOR_PEER_IMPL_H
#define FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPLEMENTATION_INDICATOR_PEER_IMPL_H

struct IndicatorPeer {
public:
    IndicatorPeer() = default;
    void SetLeft(const std::optional<OHOS::Ace::Dimension>& value)
    {
        dimLeft_ = value;
    }

    void SetTop(const std::optional<OHOS::Ace::Dimension>& value)
    {
        dimTop_ = value;
    }

    void SetRight(const std::optional<OHOS::Ace::Dimension>& value)
    {
        dimRight_ = value;
    }

    void SetBottom(const std::optional<OHOS::Ace::Dimension>& value)
    {
        dimBottom_ = value;
    }

    void SetBottomIgnoreSize(const std::optional<bool>& value)
    {
        ignoreSize_ = value;
    }

    void SetStart(const std::optional<OHOS::Ace::Dimension>& value)
    {
        dimStart_ = value;
    }

    void SetEnd(const std::optional<OHOS::Ace::Dimension>& value)
    {
        dimEnd_ = value;
    }
protected:
    std::optional<OHOS::Ace::Dimension> dimLeft_;
    std::optional<OHOS::Ace::Dimension> dimTop_;
    std::optional<OHOS::Ace::Dimension> dimRight_;
    std::optional<OHOS::Ace::Dimension> dimBottom_;
    std::optional<OHOS::Ace::Dimension> dimStart_;
    std::optional<OHOS::Ace::Dimension> dimEnd_;
    std::optional<bool> ignoreSize_;
};

#endif // FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPLEMENTATION_INDICATOR_PEER_IMPL_H