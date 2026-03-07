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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHEET_IMAGE_GENERATOR_STYLE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHEET_IMAGE_GENERATOR_STYLE_H

namespace OHOS::Ace::NG {
struct SheetPositionInfo {
    SheetPositionInfo()
        : parentLeftConstraint(0), parentRightConstraint(0), parentTopConstraint(0), parentBottomConstraint(0),
          sheetOffset(0.0f, 0.0f), sheetWidth(0), sheetHeight(0)
    {}
    float parentLeftConstraint;
    float parentRightConstraint;
    float parentTopConstraint;
    float parentBottomConstraint;
    OffsetF sheetOffset;
    float sheetWidth;
    float sheetHeight;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHEET_IMAGE_GENERATOR_STYLE_H
