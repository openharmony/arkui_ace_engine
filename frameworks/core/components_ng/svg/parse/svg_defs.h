/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_DEFS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_DEFS_H

#include "include/pathops/SkPathOps.h"

namespace OHOS::Ace::NG {

class SvgDefs : public SvgNode {
    DECLARE_ACE_TYPE(SvgDefs, SvgNode);

public:
    SvgDefs()
    {
        InitNoneFlag();
    }

    ~SvgDefs() override = default;

    static RefPtr<SvgNode> Create()
    {
        return AceType::MakeRefPtr<SvgDefs>();
    }

#ifndef USE_ROSEN_DRAWING
    SkPath AsPath(const Size& viewPort) const override
    {
        SkPath path;
        for (auto child : children_) {
            const SkPath childPath = child->AsPath(viewPort);
            Op(path, childPath, kUnion_SkPathOp, &path);
        }
        return path;
    }
#else
    RSRecordingPath AsPath(const Size& viewPort) const override
    {
        RSRecordingPath path;
        for (auto child : children_) {
            auto childPath = child->AsPath(viewPort);
            path.Op(path, childPath, RSPathOp::UNION);
        }
        return path;
    }
#endif
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_SVG_DEFS_H