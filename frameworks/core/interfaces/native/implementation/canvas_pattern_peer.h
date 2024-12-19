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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CANVAS_PATTERN_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CANVAS_PATTERN_PEER_IMPL_H

#include "core/components/common/properties/decoration.h"
#include "core/components_ng/pattern/canvas/canvas_pattern.h"

struct CanvasPatternPeer {
public:
    CanvasPatternPeer() = default;
    virtual ~CanvasPatternPeer() = default;
    const OHOS::Ace::RefPtr<OHOS::Ace::NG::CanvasPattern>& GetPattern() const
    {
        return pattern_;
    }
    void SetPattern(const OHOS::Ace::RefPtr<OHOS::Ace::NG::CanvasPattern>& pattern)
    {
        pattern_ = pattern;
    }
    virtual void SetTransform(const OHOS::Ace::TransformParam& param)
    {
        if (!pattern_) {
        LOGE("ARKOALA CanvasPatternPeer::SetTransform pattern "
             "not bound to component.");
        return;
        }
        pattern_->SetTransform(param);
    }
private:
    OHOS::Ace::RefPtr<OHOS::Ace::NG::CanvasPattern> pattern_ = nullptr;
};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CANVAS_PATTERN_PEER_IMPL_H
