/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_PROPERTIES_NG_CALC_LENGTH_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_PROPERTIES_NG_CALC_LENGTH_H

#include <vector>
#include "ui/base/geometry/dimension.h"
#include "ui/base/utils/utils.h"

namespace OHOS::Ace::NG {

class CalcLength {
public:
    CalcLength() = default;
    explicit CalcLength(const std::string& value) : calcValue_(value)
    {
        dimension_.SetUnit(DimensionUnit::CALC);
    }
    ~CalcLength() = default;

    explicit CalcLength(double value, DimensionUnit unit = DimensionUnit::PX) : dimension_(value, unit) {};
    explicit CalcLength(const Dimension& dimension) : dimension_(dimension) {};

    void Reset()
    {
        calcValue_ = "";
        dimension_.Reset();
    }

    const std::string& CalcValue() const
    {
        return calcValue_;
    }

    void SetCalcValue(const std::string& value)
    {
        calcValue_ = value;
    }

    bool NormalizeToPx(double vpScale, double fpScale, double lpxScale, double parentLength, double& result,
        const std::vector<std::string>& rpnexp = std::vector<std::string>()) const;

    bool IsValid() const
    {
        if (calcValue_.empty()) {
            return dimension_.IsNonNegative();
        }
        return true;
    }

    bool operator==(const CalcLength& length) const
    {
        if (calcValue_.empty() && length.calcValue_.empty()) {
            return dimension_ == length.dimension_;
        }
        return calcValue_ == length.calcValue_;
    }

    bool operator!=(const CalcLength& length) const
    {
        return !(*this == length);
    }

    std::string ToString() const
    {
        if (calcValue_.empty()) {
            return dimension_.ToString();
        }
        return calcValue_;
    }

    static CalcLength FromString(const std::string& str)
    {
        return CalcLength(Dimension::FromString(str));
    }

    Dimension GetDimension() const
    {
        if (!IsValid()) {
            return Dimension();
        }
        return dimension_;
    }

    Dimension GetDimensionContainsNegative() const
    {
        return dimension_;
    }

private:
    std::string calcValue_;
    Dimension dimension_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_PROPERTIES_NG_CALC_LENGTH_H
