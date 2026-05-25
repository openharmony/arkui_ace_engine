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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTY_PARTICLE_ENUM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTY_PARTICLE_ENUM_H

#include <cstdint>

namespace OHOS::Ace::NG {

enum ACE_EXPORT UpdaterType { NONE_UPDATER = 0, RANDOM, CURVE };

enum ACE_EXPORT ParticleType { POINT = 0, IMAGE };

enum ACE_EXPORT ParticleEmitterShape { RECTANGLE = 0, CIRCLE, ELLIPSE, ANNULUS };

enum ACE_EXPORT DistributionType { UNIFORM = 0, GAUSSIAN };

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTY_PARTICLE_ENUM_H
