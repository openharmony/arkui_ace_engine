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

#include "frameworks/core/components/svg/parse/svg_clip_path.h"

#ifndef USE_ROSEN_DRAWING
#include "include/pathops/SkPathOps.h"
#endif

namespace OHOS::Ace {

RefPtr<SvgNode> SvgClipPath::Create()
{
    return AceType::MakeRefPtr<SvgClipPath>();
}

void SvgClipPath::AppendChild(const RefPtr<SvgNode>& child)
{
    children_.emplace_back(child);
}

#ifndef USE_ROSEN_DRAWING
SkPath SvgClipPath::AsPath(const Size& viewPort) const
{
    SkPath path;
    for (auto child : children_) {
        const SkPath childPath = child->AsPath(viewPort);
        Op(path, childPath, kUnion_SkPathOp, &path);
    }
    return path;
}
#else
RSPath SvgClipPath::AsPath(const Size& viewPort) const
{
    RSPath path;
    for (auto child : children_) {
        RSPath childPath = child->AsPath(viewPort);
        path.Op(path, childPath, RSPathOp::UNION);
    }
    return path;
}
#endif

} // namespace OHOS::Ace
