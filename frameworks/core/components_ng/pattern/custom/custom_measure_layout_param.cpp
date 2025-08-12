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

#include "core/components_ng/pattern/custom/custom_measure_layout_param.h"

#include "core/components_ng/layout/layout_property.h"
namespace OHOS::Ace::NG {
RefPtr<LayoutWrapper> MeasureLayoutChild::GetChild() const
{
    return parent_->GetChildByIndex(index_);
}
RefPtr<LayoutWrapper> MeasureLayoutChild::GetOrCreateChild() const
{
    return parent_->GetOrCreateChildByIndex(index_);
}
LayoutConstraintF MeasureLayoutChild::CreateChildConstraint() const
{
    return parent_->CreateChildConstraint();
}
void MeasureLayoutChild::UpdateSize(const SizeF& size)
{
    parent_->UpdateSize(index_, size);
}

MeasureLayoutParam::MeasureLayoutParam(LayoutWrapper* layoutWrapper) : layoutWrapper_(layoutWrapper)
{
    count_ = layoutWrapper->GetTotalChildCount();
    children_.resize(count_);
    for (int32_t i = 0; i < count_; i++) {
        children_[i].Init(this, i);
    }
}

MeasureLayoutParam::~MeasureLayoutParam()
{
}

RefPtr<LayoutWrapper> MeasureLayoutParam::GetChildByIndex(int32_t index)
{
    return layoutWrapper_->GetChildByIndex(index);
}

RefPtr<LayoutWrapper> MeasureLayoutParam::GetOrCreateChildByIndex(int32_t index)
{
    return layoutWrapper_->GetOrCreateChildByIndex(index);
}

LayoutConstraintF MeasureLayoutParam::CreateChildConstraint() const
{
    const auto& layoutProperty = layoutWrapper_->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, LayoutConstraintF());
    return layoutProperty->CreateChildConstraint();
}

void MeasureLayoutParam::Update(LayoutWrapper* layoutWrapper)
{
    layoutWrapper_ = layoutWrapper;
    int32_t newCount = layoutWrapper->GetTotalChildCount();
    if (count_ == newCount) {
        return;
    }
    children_.resize(newCount);
    if (count_ < newCount) {
        for (int32_t i = count_; i < newCount; i++) {
            children_[i].Init(this, i);
        }
    }
    count_ = newCount;
}
} // namespace OHOS::Ace::NG
