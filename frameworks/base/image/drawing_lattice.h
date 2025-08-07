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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_ACE_DRAWING_LATTICE_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_ACE_DRAWING_LATTICE_H

#include "base/memory/ace_type.h"

namespace OHOS {
namespace Ace {
class ACE_EXPORT DrawingLattice : public AceType {
    DECLARE_ACE_TYPE(DrawingLattice, AceType)

public:
    static RefPtr<DrawingLattice> CreateDrawingLattice(void* sptrAddr);
    static RefPtr<DrawingLattice> CreateDrawingLatticeFromNative(void* sptrAddr);
#if defined(ACE_STATIC)
    /**
     * @description: Create ace lattice by drawing lattice ani
     * @param aniAddr ani lattice of drawing lattice
     * @return  ace lattice object
     *
     * only for arkts 1.2
     */
    static RefPtr<DrawingLattice> CreateDrawingLatticeFromAni(void* aniAddr);
#endif
    virtual void* GetDrawingLatticeSptrAddr() = 0; //define the return value as void is for tdd compilation
    virtual std::string DumpToString() = 0;
};

} // namespace Ace
} // namespace OHOS

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_ACE_DRAWING_LATTICE_H
