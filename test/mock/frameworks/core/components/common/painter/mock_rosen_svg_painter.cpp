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

#include <sstream>
#include <string>

#include "test/mock/frameworks/core/rosen/testing_canvas.h"
#include "test/mock/frameworks/core/rosen/testing_matrix.h"
#include "test/mock/frameworks/core/rosen/testing_point.h"

#include "core/components/common/painter/rosen_svg_painter.h"

namespace OHOS::Ace {
void RosenSvgPainter::SetMask(RSCanvas* canvas) {}
RSMatrix RosenSvgPainter::ToDrawingMatrix(const Matrix4& matrix4)
{
    RSMatrix matrix;
    return matrix;
}

void RosenSvgPainter::StringToPoints(const char str[], std::vector<Testing::TestingPoint>& points)
{
    // parse space-separated "x,y" pairs into points
    if (!str || strlen(str) == 0) {
        return;
    }
    std::string s(str);
    std::istringstream stream(s);
    std::string token;
    while (stream >> token) {
        auto comma = token.find(',');
        if (comma != std::string::npos) {
            Testing::TestingPoint pt;
            pt.SetX(std::stof(token.substr(0, comma)));
            pt.SetY(std::stof(token.substr(comma + 1)));
            points.push_back(pt);
        }
    }
}
} // namespace OHOS::Ace
