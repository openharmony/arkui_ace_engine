/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef GENERATED_FOUNDATION_ACE_CAPI_TEST_FIXTURES_ENUMS_H
#define GENERATED_FOUNDATION_ACE_CAPI_TEST_FIXTURES_ENUMS_H

#include <string>
#include <tuple>
#include <vector>

#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::Fixtures {
extern std::vector<std::tuple<std::string, Ark_Axis, std::string>> testFixtureEnumAxisValidValues;
extern std::vector<std::tuple<std::string, Ark_Axis>> testFixtureEnumAxisInvalidValues;
extern std::vector<std::tuple<std::string, Ark_RadioIndicatorType, std::string>>
    testFixtureEnumRadioIndicatorTypeValidValues;
extern std::vector<std::tuple<std::string, Ark_RadioIndicatorType>> testFixtureEnumRadioIndicatorTypeInvalidValues;
extern std::vector<std::tuple<std::string, Ark_SliderBlockType, std::string>> testFixtureEnumSliderBlockTypeValidValues;
extern std::vector<std::tuple<std::string, Ark_SliderBlockType>> testFixtureEnumSliderBlockTypeInvalidValues;
extern std::vector<std::tuple<std::string, Ark_SliderInteraction, std::string>>
    testFixtureEnumSliderInteractionValidValues;
extern std::vector<std::tuple<std::string, Ark_SliderInteraction>> testFixtureEnumSliderInteractionInvalidValues;
extern std::vector<std::tuple<std::string, Ark_SliderStyle, std::string>> testFixtureEnumSliderStyleValidValues;
extern std::vector<std::tuple<std::string, Ark_SliderStyle>> testFixtureEnumSliderStyleInvalidValues;
} // namespace OHOS::Ace::NG::Fixtures
#endif // GENERATED_FOUNDATION_ACE_CAPI_TEST_FIXTURES_H
