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

#include "bridge/declarative_frontend/jsview/canvas/js_canvas_util.h"

namespace OHOS::Ace::Framework {
bool ExtractInfoToRadii(const JSRef<JSVal> value, std::vector<double>& radii)
{
    if (value->IsNull() || value->IsUndefined()) {
        radii.emplace_back(0.0);
        return true;
    }
    if (!value->IsNumber()) {
        return false;
    }
    double radiusValue = value->ToNumber<double>();
    if (LessNotEqual(radiusValue, 0.0)) {
        JSException::Throw(
            ERROR_CODE_CANVAS_PARAM_INVALID, "%s", "radii parameter error: The param radii contains negative value.");
        return false;
    }
    radii.emplace_back(radiusValue);
    return true;
}

bool ParseRadii(const JSCallbackInfo& info, std::vector<double>& radii)
{
    if (info[4]->IsArray()) {                                  // 4: The fifth param is array.
        JSRef<JSArray> array = JSRef<JSArray>::Cast(info[4]);  // 4: The fifth param of roundRect
        if ((array->Length() <= 0) || (array->Length() > 4)) { // The size of the fifth param > 4 or <= 0
            JSException::Throw(ERROR_CODE_CANVAS_PARAM_INVALID, "%s",
                "radii parameter error: The param radii is a list that has zero or more than four elements.");
            return false;
        }
        for (uint32_t i = 0; i < array->Length(); ++i) {
            JSRef<JSVal> value = array->GetValueAt(i);
            if (!ExtractInfoToRadii(value, radii)) {
                return false;
            }
        }
        return true;
    }
    return ExtractInfoToRadii(info[4], radii); // 4: Parse the fifth param of roundRect
}

bool ParseRoundRect(
    const JSCallbackInfo& info, Rect& rect, std::vector<double>& radii, double density, bool isJudgeSpecialValue)
{
    double x = 0.0;
    double y = 0.0;
    double width = 0.0;
    double height = 0.0;
    if (!((info.GetDoubleArg(0, x, isJudgeSpecialValue) || info[0]->IsNull()) &&         // 0: the 1st arg.
            (info.GetDoubleArg(1, y, isJudgeSpecialValue) || info[1]->IsNull()) &&       // 1: the 2nd arg.
            (info.GetDoubleArg(2, width, isJudgeSpecialValue) || info[2]->IsNull()) &&   // 2: the 3rd arg.
            (info.GetDoubleArg(3, height, isJudgeSpecialValue) || info[3]->IsNull()))) { // 3: the 4th arg.
        return false;
    }
    rect.SetRect(x, y, width, height);
    if ((info.Length() >= 5) && !ParseRadii(info, radii)) { // 5: roundRect has the fifth param.
        return false;
    }
    switch (radii.size()) {
        case 0:                                  // 0: The fifth param is not set.
            radii = std::vector<double>(4, 0.0); // 4: four corners are 0.0.
            break;
        case 1:                                                 // 1: The fifth param has 1 values.
            radii = std::vector<double>(4, radii[0] * density); // 4: four corners are radii[0].
            break;
        case 2: // 2: The fifth param has 2 values.
            radii = {
                radii[0] * density, radii[1] * density, // 0: top-left-and-bottom-right, 1: top-right-and-bottom-left.
                radii[0] * density, radii[1] * density  // 0: top-left-and-bottom-right, 1: top-right-and-bottom-left.
            };
            break;
        case 3: // 3: The fifth param has 3 values.
            radii = {
                radii[0] * density, radii[1] * density, // 0: top-left, 1: top-right-and-bottom-left.
                radii[2] * density, radii[1] * density  // 2: bottom-right, 1: top-right-and-bottom-left.
            };
            break;
        case 4: // 4: The fifth param has 4 values.
            radii = {
                radii[0] * density, radii[1] * density, // 0: top-left, 1: top-right.
                radii[2] * density, radii[3] * density  // 2: bottom-right, 3: bottom-left.
            };
            break;
        default:
            return false;
    }
    return true;
}
} // namespace OHOS::Ace::Framework