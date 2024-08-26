/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "drawing_lattice_ohos.h"

#include "base/utils/utils.h"
#include "lattice_napi/js_lattice.h"

namespace OHOS::Ace {
RefPtr<DrawingLattice> DrawingLattice::CreateDrawingLattice(void* sptrAddr)
{
    CHECK_NULL_RETURN(sptrAddr, nullptr);
    auto* jsLattice = reinterpret_cast<OHOS::Rosen::Drawing::JsLattice*>(sptrAddr);
    return AceType::MakeRefPtr<DrawingLatticeOhos>(jsLattice->GetLattice());
}

RefPtr<DrawingLattice> DrawingLattice::CreateDrawingLatticeFromNative(void* sptrAddr)
{
    CHECK_NULL_RETURN(sptrAddr, nullptr);
    auto* lattice = reinterpret_cast<std::shared_ptr<OHOS::Rosen::Drawing::Lattice>*>(sptrAddr);
    return AceType::MakeRefPtr<DrawingLatticeOhos>(*lattice);
}

void* DrawingLatticeOhos::GetDrawingLatticeSptrAddr()
{
    return static_cast<void*>(&lattice_);
}
} // namespace OHOS::Ace
