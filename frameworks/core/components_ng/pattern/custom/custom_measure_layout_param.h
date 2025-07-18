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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_CUSTOM_MEASURE_LAYOUT_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_CUSTOM_MEASURE_LAYOUT_NODE_H

#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/property/layout_constraint.h"

namespace OHOS::Ace::NG {
class MeasureLayoutParam;

#ifdef ACE_STATIC
class ACE_FORCE_EXPORT MeasureLayoutChild {
#else
class MeasureLayoutChild {
#endif
public:
    inline void Init(MeasureLayoutParam* parent, int32_t index)
    {
        parent_ = parent;
        index_ = index;
    }
    RefPtr<LayoutWrapper> GetChild() const;
    RefPtr<LayoutWrapper> GetOrCreateChild() const;
    LayoutConstraintF CreateChildConstraint() const;
    void UpdateSize(const SizeF& size);
private:
    MeasureLayoutParam* parent_;
    int32_t index_ = 0;
};

#ifdef ACE_STATIC
class ACE_FORCE_EXPORT MeasureLayoutParam : public AceType {
#else
class MeasureLayoutParam : public AceType {
#endif
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

    bool ChildIndexInRange(int32_t index)
    {
        return index >= 0 && index < static_cast<int32_t>(children_.size());
    }

    LayoutWrapper* GetLayoutWrapper()
    {
        return layoutWrapper_;
    }
    virtual void Init() {}
    virtual void UpdateSize(int32_t index, const SizeF& size) {}
    virtual void Update(LayoutWrapper* layoutWrapper);
private:
    LayoutWrapper* layoutWrapper_;
    std::vector<MeasureLayoutChild> children_;
    int32_t count_ = 0;
};
} // namespace OHOS::Ace::NG
#endif
