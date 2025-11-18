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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_WINDOW_SIZE_BREAKPOINT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_WINDOW_SIZE_BREAKPOINT_H

namespace OHOS::Ace {

enum class WidthBreakpoint { WIDTH_XS, WIDTH_SM, WIDTH_MD, WIDTH_LG, WIDTH_XL, WIDTH_XXL, UNDEFINED };
enum class HeightBreakpoint { HEIGHT_SM, HEIGHT_MD, HEIGHT_LG };

struct WindowSizeBreakpoint {
    WidthBreakpoint widthBreakpoint = WidthBreakpoint::UNDEFINED;
    HeightBreakpoint heightBreakpoint = HeightBreakpoint::HEIGHT_SM;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_WINDOW_SIZE_BREAKPOINT_H