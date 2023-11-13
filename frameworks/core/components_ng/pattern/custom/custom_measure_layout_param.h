/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_CUSTOM_MEASURE_LAYOUT_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_CUSTOM_MEASURE_LAYOUT_NODE_H

#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/property/layout_constraint.h"

namespace OHOS::Ace::NG {
class MeasureLayoutParam;

class MeasureLayoutChild {
public:
    inline void Init(MeasureLayoutParam* parent, int32_t index)
    {
        parent_ = parent;
        index_ = index;
    }
    RefPtr<LayoutWrapper> GetChildByIndex() const;
    RefPtr<LayoutWrapper> GetOrCreateChildByIndex() const;
    LayoutConstraintF CreateChildConstraint() const;
    void MarkLayouted();
    void UpdateSize(const SizeF& size);
private:
    MeasureLayoutParam* parent_;
    int32_t index_;
};

class MeasureLayoutParam : public AceType {
    DECLARE_ACE_TYPE(MeasureLayoutParam, AceType)
public:
    MeasureLayoutParam(LayoutWrapper* layoutWrapper);
    ~MeasureLayoutParam();

    RefPtr<LayoutWrapper> GetChildByIndex(int32_t index);
    RefPtr<LayoutWrapper> GetOrCreateChildByIndex(int32_t index);
    LayoutConstraintF CreateChildConstraint() const;
    int32_t GetTotalChildCount() const
    {
        return count_;
    }
    MeasureLayoutChild& Get(int32_t index)
    {
        return children_[index];
    }
    LayoutWrapper* GetLayoutWrapper()
    {
        return layoutWrapper_;
    }
    void AddLayouted(int32_t index)
    {
        layoutedList_.emplace(index);
    }
    void ResetLayouted()
    {
        layoutedList_.clear();
    }
    const std::set<int32_t>& GetLayoutedList() const
    {
        return layoutedList_;
    }
    virtual void UpdateSize(int32_t index, const SizeF& size) {}
    virtual void Update(LayoutWrapper* layoutWrapper);
private:
    LayoutWrapper* layoutWrapper_;
    std::vector<MeasureLayoutChild> children_;
    std::set<int32_t> layoutedList_;
    int32_t count_;
};
} // namespace OHOS::Ace::NG
#endif
