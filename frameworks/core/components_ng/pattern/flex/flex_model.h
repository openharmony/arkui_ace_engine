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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FLEX_FLEX_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FLEX_FLEX_MODEL_H

#include <memory>
#include <mutex>
#include <vector>

#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "frameworks/base/geometry/dimension.h"

namespace OHOS::Ace {

const std::vector<WrapAlignment> WRAP_TABLE = {
    WrapAlignment::START,
    WrapAlignment::START,
    WrapAlignment::CENTER,
    WrapAlignment::END,
    WrapAlignment::STRETCH,
    WrapAlignment::BASELINE,
    WrapAlignment::SPACE_BETWEEN,
    WrapAlignment::SPACE_AROUND,
    WrapAlignment::SPACE_EVENLY,
};

constexpr int32_t MAIN_ALIGN_MAX_VALUE = 8;
constexpr int32_t CROSS_ALIGN_MAX_VALUE = 5;
constexpr int32_t DIRECTION_MAX_VALUE = 3;

class ACE_FORCE_EXPORT FlexModel {
public:
    static FlexModel* GetInstance();
    virtual ~FlexModel() = default;

    virtual void CreateFlexRow() = 0;

    virtual void CreateWrap() = 0;

    virtual void SetDirection(FlexDirection direction) = 0;
    virtual void SetWrapDirection(WrapDirection direction) = 0;

    virtual void SetMainAxisAlign(FlexAlign flexAlign) = 0;
    virtual void SetWrapMainAlignment(WrapAlignment value) = 0;

    virtual void SetCrossAxisAlign(FlexAlign flexAlign) = 0;
    virtual void SetWrapCrossAlignment(WrapAlignment value) = 0;

    virtual void SetAlignItems(int32_t value) = 0;
    virtual void SetWrapAlignment(WrapAlignment value) = 0;

    virtual void SetHasHeight() = 0;
    virtual void SetHasWidth() = 0;
    virtual void SetFlexWidth() = 0;
    virtual void SetFlexHeight() = 0;

    virtual void SetJustifyContent(int32_t value) = 0;

    virtual void SetAlignContent(int32_t value) = 0;
    virtual void SetMainSpace(const std::optional<Dimension>& space) = 0;
    virtual void SetCrossSpace(const std::optional<Dimension>& space) = 0;
    virtual void SetWidthLayoutPolicy(uint8_t widthLayoutPolicy) = 0;
    virtual void SetHeightLayoutPolicy(uint8_t heightLayoutPolicy) = 0;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FLEX_FLEX_MODEL_H
