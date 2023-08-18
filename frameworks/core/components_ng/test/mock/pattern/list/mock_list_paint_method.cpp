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

#include "core/components_ng/pattern/list/list_paint_method.h"

namespace OHOS::Ace::NG {
CanvasDrawFunction ListPaintMethod::GetForegroundDrawFunction(PaintWrapper* /* paintWrapper */)
{
    // just use the private value
    vertical_ = false;
    lanes_ = 1;
    space_ = 0.0f;
    return nullptr;
}

void ListPaintMethod::UpdateContentModifier(PaintWrapper* paintWrapper) {}

void ListPaintMethod::UpdateOverlayModifier(PaintWrapper* paintWrapper) {}
} // namespace OHOS::Ace::NG
