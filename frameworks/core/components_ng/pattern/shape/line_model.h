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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINE_LINE_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINE_LINE_MODEL_H

#include <memory>
#include <mutex>

#include "core/components/shape/shape_component.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT LineModel {
public:
    static LineModel* GetInstance();
    virtual ~LineModel() = default;

    virtual void Create();
    virtual void StartPoint(const ShapePoint& value);
    virtual void StartPoint(const ShapePoint& value, const std::vector<RefPtr<ResourceObject>>& resObjArray) {};
    virtual void EndPoint(const ShapePoint& value);
    virtual void EndPoint(const ShapePoint& value, const std::vector<RefPtr<ResourceObject>>& resObjArray) {};
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINE_LINE_MODEL_H
