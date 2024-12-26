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
    using CanvasPatternPtr = OHOS::Ace::RefPtr<OHOS::Ace::NG::CanvasPattern>;
    using TransformParamCls = OHOS::Ace::TransformParam;

    CanvasPatternPeer() = default;
    virtual ~CanvasPatternPeer() = default;
    const CanvasPatternPtr& GetPattern() const
    {
        return pattern_;
    }
    void SetPattern(const CanvasPatternPtr& pattern)
    {
        pattern_ = pattern;
    }
    virtual void SetTransform(const TransformParamCls& param)
    {
        if (!pattern_) {
        LOGE("ARKOALA CanvasPatternPeer::SetTransform pattern "
             "not bound to component.");
        return;
        }
        pattern_->SetTransform(param);
    }
    void SetId(int32_t id)
    {
        id_ = id;
    }

    int32_t GetId() const
    {
        return id_;
    }

    void SetUnit(CanvasUnit unit)
    {
        unit_ = unit;
    }

    CanvasUnit GetUnit()
    {
        return unit_;
    }

public:
    std::shared_ptr<OHOS::Ace::Pattern> pattern = nullptr;    
private:
    int32_t id_ = 0;
    CanvasUnit unit_ = CanvasUnit::DEFAULT;   
    CanvasPatternPtr pattern_ = nullptr;
    std::shared_ptr<OHOS::Ace::Pattern> pattern = nullptr; 
};

#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CANVAS_PATTERN_PEER_IMPL_H
