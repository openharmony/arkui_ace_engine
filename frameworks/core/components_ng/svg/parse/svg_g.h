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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_G_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_G_H

#include "frameworks/core/components_ng/svg/parse/svg_group.h"

namespace OHOS::Ace::NG {

class SvgG : public SvgGroup {
    DECLARE_ACE_TYPE(SvgG, SvgGroup);

public:
    SvgG();
    ~SvgG() override = default;
    static RefPtr<SvgNode> Create();

#ifndef USE_ROSEN_DRAWING
    SkPath AsPath(const Size& viewPort) const override;
#else
    RSRecordingPath AsPath(const Size& viewPort) const override;
#endif
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_G_H