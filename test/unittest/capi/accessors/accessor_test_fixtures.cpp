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

#include "accessor_test_fixtures.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::AccessorTestFixtures {
using namespace Converter;
// Fixture 'Boolean' for type 'Ark_Boolean'
const std::vector<std::tuple<std::string, Ark_Boolean, bool>> testFixtureBooleanValues = {
    { "true", ArkValue<Ark_Boolean>(true), true },
    { "false", ArkValue<Ark_Boolean>(false), false },
};

const std::vector<std::tuple<std::string, Ark_Int32, int32_t>> testFixtureInt32WithNegativeValues = {
    { "0", ArkValue<Ark_Int32>(0), 0 },
    { "INT32_MIN", ArkValue<Ark_Int32>(INT32_MIN), INT32_MIN },
    { "32", ArkValue<Ark_Int32>(32), 32 },
    { "-1", ArkValue<Ark_Int32>(-1), -1 },
    { "INT32_MAX", ArkValue<Ark_Int32>(INT32_MAX), INT32_MAX },
};

const std::vector<std::tuple<std::string, Ark_Number, int32_t>> testFixtureNumberInt32Values = {
    { "0", ArkValue<Ark_Number>(0), 0 },
    { "INT32_MIN", ArkValue<Ark_Number>(INT32_MIN), INT32_MIN },
    { "32", ArkValue<Ark_Number>(32), 32 },
    { "-1", ArkValue<Ark_Number>(-1), -1 },
    { "INT32_MAX", ArkValue<Ark_Number>(INT32_MAX), INT32_MAX },
};

const std::vector<std::tuple<std::string, Ark_Number, double>> testFixtureNumberValues = {
    { "1.24", ArkValue<Ark_Number>(1.24), 1.24 },
    { "0", ArkValue<Ark_Number>(0), 0 },
    { "100", ArkValue<Ark_Number>(100), 100 },
    { "-20.65", ArkValue<Ark_Number>(-20.65), -20.65 },
};

const std::vector<std::tuple<std::string, Ark_Number, double>> testFixtureNumber_2x_Values = {
    { "1.24", ArkValue<Ark_Number>(1.24), 2.48 },
    { "0", ArkValue<Ark_Number>(0), 0 },
    { "100", ArkValue<Ark_Number>(100), 200 },
    { "-20.65", ArkValue<Ark_Number>(-20.65), -41.30 },
};

const std::vector<std::tuple<std::string, double, Ark_Int32>> testFixtureDoubleArkInt32Values = {
    { "1.24", 1.24, ArkValue<Ark_Int32>(1) },
    { "0", 0, ArkValue<Ark_Int32>(0) },
    { "100", 100, ArkValue<Ark_Int32>(100) },
    { "-20.65", -20.65, ArkValue<Ark_Int32>(-20) },
};

const std::vector<std::tuple<std::string, double, Ark_Int32>> testFixtureDoubleArkInt32_half_Values = {
    { "4.4", 4.4, ArkValue<Ark_Int32>(2) },
    { "0", 0, ArkValue<Ark_Int32>(0) },
    { "100", 100, ArkValue<Ark_Int32>(50) },
    { "-20.65", -20.65, ArkValue<Ark_Int32>(-10) },
};

const std::vector<std::tuple<std::string, double, double, Ark_Int32>> testFixtureVelocity_half_Values = {
    { "[30., 40.]", 30., 40., ArkValue<Ark_Int32>(25) },
    { "[-30., 0.]", 30., 0., ArkValue<Ark_Int32>(15) },
    { "[0., 40.]", 0., 40., ArkValue<Ark_Int32>(20) },
    { "[0., 0.]", 0., 0., ArkValue<Ark_Int32>(0) },
};
} // namespace OHOS::Ace::NG::AccessorTestFixtures
