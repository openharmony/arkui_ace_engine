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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_DRAWING_LATTICE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_DRAWING_LATTICE_H

#include <memory>

#include "draw/core_canvas.h"

#include "base/image/drawing_lattice.h"

namespace OHOS::Ace {

class DrawingLatticeImpl : public DrawingLattice {
    DECLARE_ACE_TYPE(DrawingLatticeImpl, DrawingLattice);
    
public:
    DrawingLatticeImpl(std::shared_ptr<Rosen::Drawing::Lattice> lattice, int32_t type)
        : type_(type), lattice_(std::move(lattice))
    {}
    DrawingLatticeImpl(Rosen::Drawing::Lattice* lattice, int32_t type) : type_(type), latticeNative_(lattice) {}
    ~DrawingLatticeImpl() override = default;

    Rosen::Drawing::Lattice* GetLattice();
    std::string DumpToString() override;

private:
    DrawingLatticeImpl() = default;

    int32_t type_ = 0;
    Rosen::Drawing::Lattice* latticeNative_;
    std::shared_ptr<Rosen::Drawing::Lattice> lattice_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_DRAWING_LATTICE_H
