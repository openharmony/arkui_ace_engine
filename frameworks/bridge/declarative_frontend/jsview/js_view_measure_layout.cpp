/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_view_measure_layout.h"

#include <iterator>

namespace OHOS::Ace::Framework {

thread_local std::list<RefPtr<NG::LayoutWrapper>> measureChildren_ = std::list<RefPtr<NG::LayoutWrapper>>();
thread_local std::list<RefPtr<NG::LayoutWrapper>>::iterator iterMeasureChildren_;
thread_local std::list<RefPtr<NG::LayoutWrapper>> layoutChildren_ = std::list<RefPtr<NG::LayoutWrapper>>();
thread_local std::list<RefPtr<NG::LayoutWrapper>>::iterator iterLayoutChildren_;
thread_local NG::LayoutConstraintF measureDefaultConstraint_ = NG::LayoutConstraintF();
thread_local NG::OffsetF parentGlobalOffset = NG::OffsetF(0, 0);
thread_local int measureIndex_ = 0;

} // namespace OHOS::Ace::Framework