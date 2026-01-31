/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_PROPERTIES_NG_MEASURE_PROPERTY_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_PROPERTIES_NG_MEASURE_PROPERTY_H

#include <functional>
#include <optional>
#include <string>
#include <unordered_map>

#include "ui/base/geometry/ng/offset_t.h"
#include "ui/base/geometry/ng/size_t.h"
#include "ui/properties/ng/calc_length.h"
#include "ui/resource/resource_object.h"

namespace OHOS::Ace::NG {
static constexpr int32_t API_VERSION_SIXTEEN = 16;
const std::string BORDERZERO = "0.0";

template<typename T>
struct ACE_FORCE_EXPORT PaddingPropertyT {
    std::optional<T> left;
    std::optional<T> right;
    std::optional<T> top;
    std::optional<T> bottom;
    std::optional<T> start;
    std::optional<T> end;
    struct resourceUpdater {
        RefPtr<ResourceObject> resObj;
        std::function<void(const RefPtr<ResourceObject>&, PaddingPropertyT&)> updateFunc;
    };
    std::unordered_map<std::string, resourceUpdater> resMap_;

    ACE_FORCE_EXPORT void SetEdges(const T& padding);
    ACE_FORCE_EXPORT void SetEdges(const T& leftValue, const T& rightValue, const T& topValue, const T& bottomValue);
    ACE_FORCE_EXPORT bool operator==(const PaddingPropertyT& value) const;
    ACE_FORCE_EXPORT bool operator!=(const PaddingPropertyT& value) const;
    ACE_FORCE_EXPORT bool UpdateWithCheck(const PaddingPropertyT& value);
    ACE_FORCE_EXPORT bool UpdateLocalizedPadding(const PaddingPropertyT& value);
    ACE_FORCE_EXPORT void checkNeedReset(const PaddingPropertyT& value);
    ACE_FORCE_EXPORT std::string ToString() const;
    ACE_FORCE_EXPORT std::string ToJsonString() const;
    static PaddingPropertyT FromJsonString(const std::string& str);
    void AddResource(
        const std::string& key,
        const RefPtr<ResourceObject>& resObj,
        std::function<void(const RefPtr<ResourceObject>&, PaddingPropertyT&)>&& updateFunc);
    void ReloadResources();
};

struct ACE_FORCE_EXPORT PaddingPropertyF {
    std::optional<float> left;
    std::optional<float> right;
    std::optional<float> top;
    std::optional<float> bottom;

    bool operator==(const PaddingPropertyF& value) const;
    std::string ToString() const;
    std::string ToJsonString() const;
    float Width() const;
    float Height() const;
    SizeF Size() const;
    OffsetF Offset() const;
    OffsetF MirrorOffset() const;
    bool Empty();
    bool HasValue() const;
    PaddingPropertyF Plus(const PaddingPropertyF& another, bool skipNullOpt = true);
    PaddingPropertyF Minus(const PaddingPropertyF& another, bool skipNullOpt = true) const;
    bool AllSidesFilled(bool checkZero = false);
    bool OptionalValueCover(const PaddingPropertyF& another);
    void Reset();

private:
    PaddingPropertyF Calculate(const PaddingPropertyF& another, bool skipNullOpt, bool isAdd) const;
};

using PaddingProperty = PaddingPropertyT<CalcLength>;
using MarginProperty = PaddingProperty;
using MarginPropertyF = PaddingPropertyF;

} // namespace OHOS::Ace::NG

// Explicit template instantiation declarations
extern template struct OHOS::Ace::NG::PaddingPropertyT<OHOS::Ace::NG::CalcLength>;
extern template struct OHOS::Ace::NG::PaddingPropertyT<OHOS::Ace::Dimension>;

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_PROPERTIES_NG_MEASURE_PROPERTY_H
