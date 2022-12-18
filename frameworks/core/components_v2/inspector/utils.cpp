/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::V2 {

std::string GetTextStyleInJson(const TextStyle& textStyle)
{
    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("size", textStyle.GetFontSize().ToString().c_str());
    auto weight = textStyle.GetFontWeight();
    if (weight == FontWeight::W100) {
        jsonValue->Put("weight", "100");
    } else if (weight == FontWeight::W200) {
        jsonValue->Put("weight", "200");
    } else if (weight == FontWeight::W300) {
        jsonValue->Put("weight", "300");
    } else if (weight == FontWeight::W400) {
        jsonValue->Put("weight", "400");
    } else if (weight == FontWeight::W500) {
        jsonValue->Put("weight", "500");
    } else if (weight == FontWeight::W600) {
        jsonValue->Put("weight", "600");
    } else if (weight == FontWeight::W700) {
        jsonValue->Put("weight", "700");
    } else if (weight == FontWeight::W800) {
        jsonValue->Put("weight", "800");
    } else if (weight == FontWeight::W900) {
        jsonValue->Put("weight", "900");
    } else {
        jsonValue->Put("weight", ConvertWrapFontWeightToStirng(weight).c_str());
    }
    std::string jsonFamily = ConvertFontFamily(textStyle.GetFontFamilies());
    jsonValue->Put("family", jsonFamily.c_str());
    auto fontStyle = textStyle.GetFontStyle();
    jsonValue->Put("style", ConvertWrapFontStyleToStirng(fontStyle).c_str());
    return jsonValue->ToString();
}

} // namespace OHOS::Ace::V2
