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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LINEAR_LAYOUT_COLUMN_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LINEAR_LAYOUT_COLUMN_MODEL_H

#include <memory>
#include <mutex>
#include <optional>
#include <string>

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/common/resource/resource_object.h"
#include "core/components/common/layout/align_declaration.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace {

class ACE_FORCE_EXPORT ColumnModel {
public:
    static ColumnModel* GetInstance();
    virtual ~ColumnModel() = default;

    virtual void Create(
        const std::optional<Dimension>& space, AlignDeclaration* declaration, const std::string& tag) = 0;
    virtual void Create(
        const RefPtr<ResourceObject>& spaceResObj, AlignDeclaration* declaration, const std::string& tag) {}
    virtual void CreateWithWrap() = 0;
    virtual void SetAlignItems(FlexAlign flexAlign) = 0;
    virtual void SetJustifyContent(FlexAlign flexAlign) = 0;
    virtual void SetIsReverse(bool isReverse) = 0;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LINEAR_LAYOUT_COLUMN_MODEL_H
