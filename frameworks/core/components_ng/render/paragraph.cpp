/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/render/paragraph.h"

#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::NG {
std::string ParagraphStyle::ToString() const
{
    std::string result = "TextAlign: ";
    result += V2::ConvertWrapTextAlignToString(align);
    result += ", TextVerticalAlign: ";
    result += V2::ConvertWrapTextVerticalAlignToString(verticalAlign);
    result += ", maxLines: ";
    result += std::to_string(maxLines);
    result += ", wordBreak: ";
    result += V2::ConvertWrapWordBreakToString(wordBreak);
    result += ", textOverflow: ";
    result += V2::ConvertWrapTextOverflowToString(textOverflow);
    result += ", leadingMargin: ";
    result += leadingMargin.has_value() ? leadingMargin.value().ToString().c_str() : "nullptr";
    result += ", fontSize: ";
    result += std::to_string(fontSize);
    result += ", indent: ";
    result += ", paragraphSpacing: ";
    result += paragraphSpacing.ToString();
    result += indent.ToString();
    result += ", enableAutoSpacing: ";
    result += enableAutoSpacing;
    result += ", orphanCharOptimization: ";
    result += orphanCharOptimization;
    result += ", compressLeadingPunctuation: ";
    result += compressLeadingPunctuation;
    result += ", punctuationOverflow: ";
    result += punctuationOverflow;
    result += ", includeFontPadding: ";
    result += includeFontPadding;
    result += ", fallbackLineSpacing: ";
    result += fallbackLineSpacing;
    result += ", gradient: ";
    if (propGradient) {
        result += propGradient->GetGradient().has_value() ? propGradient->GetGradient().value().ToString().c_str()
            : "nullptr";
    } else {
        result += "nullptr";
    }
    result += ", colorShaderStyle: ";
    result += colorShaderStyle.has_value() ? colorShaderStyle.value().ToString().c_str() : "nullptr";
    return result;
}
} // namespace OHOS::Ace::NG

