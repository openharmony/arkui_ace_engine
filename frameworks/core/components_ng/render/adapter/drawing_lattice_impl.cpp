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

#include "core/components_ng/render/adapter/drawing_lattice_impl.h"

#include "base/utils/utils.h"

namespace OHOS::Ace {
RefPtr<DrawingLattice> DrawingLattice::CreateDrawingLatticeFromSptr(void* sptrAddr)
{
    CHECK_NULL_RETURN(sptrAddr, nullptr);
    auto* lattice = reinterpret_cast<std::shared_ptr<Rosen::Drawing::Lattice>*>(sptrAddr);
    return AceType::MakeRefPtr<DrawingLatticeImpl>(*lattice, 0);
}

RefPtr<DrawingLattice> DrawingLattice::CreateDrawingLatticeFromNative(void* addr)
{
    CHECK_NULL_RETURN(addr, nullptr);
    auto* lattice = reinterpret_cast<Rosen::Drawing::Lattice*>(addr);
    return AceType::MakeRefPtr<DrawingLatticeImpl>(lattice, 1);
}

Rosen::Drawing::Lattice* DrawingLatticeImpl::GetLattice()
{
    if (type_ == 0 && lattice_) {
        return lattice_.get();
    }
    if (type_ == 1 && latticeNative_) {
        return latticeNative_;
    }
    return nullptr;
}

std::string DrawingLatticeImpl::DumpToString()
{
    if (lattice_) {
        std::string drawingConfigStr;
        drawingConfigStr.append("fXCount = " + std::to_string(lattice_->fXCount));
        drawingConfigStr.append("fXDivs = [");
        for (int32_t idx = 0; idx < lattice_->fXCount; ++idx) {
            drawingConfigStr.append(std::to_string(lattice_->fXDivs[idx]) + " ");
        }
        drawingConfigStr.append("] ");
        drawingConfigStr.append("fYCount = " + std::to_string(lattice_->fYCount));
        drawingConfigStr.append("fYDivs = [");
        for (int32_t idx = 0; idx < lattice_->fYCount; ++idx) {
            drawingConfigStr.append(std::to_string(lattice_->fYDivs[idx]) + " ");
        }
        drawingConfigStr.append("] ");
        return drawingConfigStr;
    }
    return "Lattice is null";
}
} // namespace OHOS::Ace
