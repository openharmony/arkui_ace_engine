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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_PATTERN_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_PATTERN_H

#include "ui/base/ace_type.h"
#include "ui/base/referenced.h"
#include "ui/properties/dirty_flag.h"
#include "ui/properties/property.h"
#include "ui/view/draw/node_paint_method.h"
#include "ui/view/layout/layout_algorithm.h"

namespace OHOS::Ace::Kit {
class Pattern : public AceType {
    DECLARE_ACE_TYPE(Pattern, AceType);

public:
    virtual RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() = 0;
    virtual RefPtr<NodePaintMethod> CreateNodePaintMethod() = 0;
    virtual bool OnDirtyLayoutrSwap(const NG::DirtySwapConfig& config)
    {
        return false;
    }
    virtual void OnModifyDone() {}

    virtual RefPtr<Property> CreateProperty()
    {
        return AceType::MakeRefPtr<Property>();
    }

    void SetHost(const WeakPtr<FrameNode>& host)
    {
        host_ = host;
    }

    const WeakPtr<FrameNode>& GetHost() const
    {
        return host_;
    }

    virtual bool IsAtomicNode() const
    {
        return true;
    }

private:
    WeakPtr<FrameNode> host_;
};
} // namespace OHOS::Ace::Kit

#endif
