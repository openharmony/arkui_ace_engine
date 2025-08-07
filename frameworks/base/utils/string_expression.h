/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_STRING_EXPRESSION_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_STRING_EXPRESSION_H

#include <functional>
#include <map>
#include <string>
#include <vector>

#include "base/geometry/dimension.h"

namespace OHOS::Ace::StringExpression {

void InitMapping(std::map<std::string, int>& mapping);

bool CheckCalcIsValid(const std::string& formula);

void ReplaceSignNumber(std::string& formula);

void ConvertDal2Rpn(std::string formula, std::vector<std::string> &result);

double CalculateExp(const std::string& expression, const std::function<double(const Dimension&)>& calcFunc,
    const std::vector<std::string>& lengthString = std::vector<std::string>());

#ifdef ACE_UNITTEST
bool PushOpStack(const std::string& formula, std::string& curNum, std::vector<std::string>& result,
    std::vector<std::string>& opStack);

bool CalculateFourOperationsExp(const std::string& exp, const Dimension& num1, const Dimension& num2,
    const std::function<double(const Dimension&)>& calcFunc, double& opRes);
bool CalculateExpImpl(const std::vector<std::string>& rpnexp, const std::function<double(const Dimension&)>& calcFunc,
    std::vector<Dimension>& result, double& opRes);
#endif
} // namespace OHOS::Ace::StringExpression

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_STRING_EXPRESSION_H
