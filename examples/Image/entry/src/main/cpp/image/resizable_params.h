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

#ifndef CAPI_RESIZABLE_PARAMS_H
#define CAPI_RESIZABLE_PARAMS_H

#include "native_drawing/drawing_types.h"
#include "native_drawing/drawing_lattice.h"
#include <hilog/log.h>
#include <vector>
#include <string>

namespace Self::UI {
    enum class ResizableType { LATTICE = 0, SLICE = 1, NONE = 2 };
    // Slice结构体
    struct Slice {
        float left = 0;
        float top = 0;
        float right = 0;
        float bottom = 0;
        std::string ToString() {
            std::string result;
            result.append("[");
            result.append(std::to_string(left));
            result.append(" ");
            result.append(std::to_string(top));
            result.append(" ");
            result.append(std::to_string(right));
            result.append(" ");
            result.append(std::to_string(bottom));
            result.append("]");
            return result;
        }
    };

    // Lattice结构体
    struct Lattice {
        std::vector<int> xDivs;
        std::vector<int> yDivs;
        std::string ToString() {
            std::string result;
            result.append("{xDivs:[");
            for (size_t i = 0; i < xDivs.size(); i++) {
                result.append(std::to_string(xDivs[i]));
                if (i == xDivs.size() - 1) {
                    break;
                } else {
                    result.append(" ");
                }
            }
            result.append("]");
            result.append(", yDivs:[");
            for (size_t i = 0; i < yDivs.size(); i++) {
                result.append(std::to_string(yDivs[i]));
                if (i == yDivs.size() - 1) {
                    break;
                } else {
                    result.append(" ");
                }
            }
            result.append("]");
            result.append("}");
            return result;
        }
    };

    // Resizable结构体
    struct Resizable {
        Slice slice;
        Lattice lattice;
        bool hasSlice = false;
        bool hasLattice = false;
    };
    class  ResizableParams {
    public:
        // 输入的时候传px
        ResizableParams(const Slice &slice) : type_(ResizableType::SLICE), slice_(slice) {}

        ResizableParams(const Lattice &lattice) {
            auto code = OH_Drawing_LatticeCreate(lattice.xDivs.data(), lattice.yDivs.data(), lattice.xDivs.size(), 
                                                lattice.yDivs.size(), nullptr, nullptr, 0, 0, 0, &lattice_);
            if (code != OH_Drawing_ErrorCode::OH_DRAWING_SUCCESS) {
                OH_LOG_ERROR(LogType::LOG_APP, "create drawing lattice filed");
            }
            latticeV_ = lattice;
            type_ = ResizableType::LATTICE;
        }

        Slice GetSlice() { return slice_; }

        Lattice GetLatticeV() { return latticeV_; }

        OH_Drawing_Lattice *GetLattice() { return lattice_; }
        
        ResizableType GetType() { return type_; }

    private:
        ResizableParams() = default;

        ResizableType type_ = ResizableType::NONE;
        Lattice latticeV_;
        Slice slice_;
        OH_Drawing_Lattice *lattice_;
    };
} // namespace Self::UI

#endif // CAPI_RESIZABLE_PARAMS_H