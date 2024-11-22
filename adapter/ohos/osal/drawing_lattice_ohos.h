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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_OSAL_DRAWING_LATTICE_OHOS_H
#define FOUNDATION_ACE_ADAPTER_OHOS_OSAL_DRAWING_LATTICE_OHOS_H

#include <memory>
#include "draw/core_canvas.h"

#include "base/image/drawing_lattice.h"

namespace OHOS::Ace {

class DrawingLatticeOhos : public DrawingLattice {
public:
    explicit DrawingLatticeOhos(std::shared_ptr<Rosen::Drawing::Lattice> lattice)
        : lattice_(std::move(lattice)) {}
    ~DrawingLatticeOhos() override = default;
    void* GetDrawingLatticeSptrAddr() override;
    std::string DumpToString() override;

private:
    std::shared_ptr<Rosen::Drawing::Lattice> lattice_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_OHOS_OSAL_DRAWING_LATTICE_OHOS_H
