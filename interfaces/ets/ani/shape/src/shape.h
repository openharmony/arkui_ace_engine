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

#ifndef OHOS_ANI_ACE_SHAPE_H
#define OHOS_ANI_ACE_SHAPE_H

#include <ani.h>
#include <iostream>
#include <array>
#include <algorithm>
#include <chrono>
#include <future>
#include <thread>
#include <map>
#include <string>
#include <memory>
#include <vector>
#include "base/memory/referenced.h"
#include "base/log/log_wrapper.h"
#include "base/geometry/shape.h"
#include "base/memory/ace_type.h"
#include "base/geometry/dimension.h"
#include "base/geometry/calc_dimension.h"
#include "shapeUtil.h"


namespace OHOS::Ace {
class ACE_FORCE_EXPORT CircleShape final {
public:
    static ani_status BindCircleShape(ani_env *env);
};

class ACE_FORCE_EXPORT EllipseShape final {
public:
    static ani_status BindEllipseShape(ani_env *env);
};

class ACE_FORCE_EXPORT PathShape final {
public:
    static ani_status BindPathShape(ani_env *env);
};

class ACE_FORCE_EXPORT RectShape final {
public:
    static ani_status BindRectShape(ani_env *env);
};

} // namespace OHOS::Ace
#endif // OHOS_ANI_ACE_SHAPE_H