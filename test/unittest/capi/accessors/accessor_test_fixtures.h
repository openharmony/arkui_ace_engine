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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_TEST_UNITTEST_CAPI_ACCESSOR_TEST_FEATURES_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_TEST_UNITTEST_CAPI_ACCESSOR_TEST_FEATURES_H

#include <string>
#include <vector>

// sorted part of the code
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#include "frameworks/core/gestures/drag_event.h"

namespace OHOS::Ace::NG::AccessorTestFixtures {
// Fixture 'Boolean' for type 'Ark_Boolean'
extern const std::vector<std::tuple<std::string, Ark_Boolean, bool>> testFixtureBooleanValues;
extern const std::vector<std::tuple<std::string, Ark_Int32, int32_t>> testFixtureInt32WithNegativeValues;
extern const std::vector<std::tuple<std::string, Ark_Number, int32_t>> testFixtureNumberInt32Values;
extern const std::vector<std::tuple<std::string, Ark_Number, double>> testFixtureNumberValues;
extern const std::vector<std::tuple<std::string, Ark_Number, double>> testFixtureNumber_2x_Values;
extern const std::vector<std::tuple<std::string, double, Ark_Int32>> testFixtureDoubleArkInt32Values;
extern const std::vector<std::tuple<std::string, double, Ark_Int32>> testFixtureDoubleArkInt32_half_Values;
extern const std::vector<std::tuple<std::string, double, double, Ark_Int32>> testFixtureVelocity_half_Values;
extern const std::vector<std::tuple<std::string, double, Ark_Number>> testFixtureNumberFloatAnythingValidValues;
extern const std::vector<std::tuple<std::string, double, Ark_Number>> testFixtureVelocityValues;
extern const std::vector<std::tuple<std::string, Ark_DragBehavior, OHOS::Ace::DragBehavior>>
    testFixtureEnumDragBehaviorValues;
} // namespace OHOS::Ace::NG::AccessorTestFixtures
#endif