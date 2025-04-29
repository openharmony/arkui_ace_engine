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

#include "drawing_lattice_preview.h"

#include "draw/core_canvas.h"
#include "lattice_napi/js_lattice.h"

#include "base/image/drawing_lattice.h"
#include "base/utils/utils.h"

namespace OHOS::Ace {
RefPtr<DrawingLattice> DrawingLattice::CreateDrawingLattice(void* sptrAddr)
{
    CHECK_NULL_RETURN(sptrAddr, nullptr);
    auto* jsLattice = reinterpret_cast<OHOS::Rosen::Drawing::JsLattice*>(sptrAddr);
    return AceType::MakeRefPtr<DrawingLatticePreview>(jsLattice->GetLattice());
}

RefPtr<DrawingLattice> DrawingLattice::CreateDrawingLatticeFromNative(void* sptrAddr)
{
    CHECK_NULL_RETURN(sptrAddr, nullptr);
    auto* lattice = reinterpret_cast<std::shared_ptr<OHOS::Rosen::Drawing::Lattice>*>(sptrAddr);
    return AceType::MakeRefPtr<DrawingLatticePreview>(*lattice);
}

void* DrawingLatticePreview::GetDrawingLatticeSptrAddr()
{
    return static_cast<void*>(&lattice_);
}

std::string DrawingLatticePreview::DumpToString()
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
