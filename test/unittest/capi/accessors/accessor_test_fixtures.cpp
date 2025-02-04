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
}