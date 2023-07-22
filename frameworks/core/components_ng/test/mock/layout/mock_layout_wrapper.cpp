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

#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"

namespace OHOS::Ace::NG {
void LayoutWrapper::Update(
    WeakPtr<FrameNode> hostNode, RefPtr<GeometryNode> geometryNode, RefPtr<LayoutProperty> layoutProperty)
{}

LayoutWrapper::LayoutWrapper(
    WeakPtr<FrameNode> hostNode, RefPtr<GeometryNode> geometryNode, RefPtr<LayoutProperty> layoutProperty)
    : hostNode_(std::move(hostNode)), geometryNode_(std::move(geometryNode)), layoutProperty_(std::move(layoutProperty))
{}

RefPtr<LayoutWrapper> LayoutWrapper::GetOrCreateChildByIndex(int32_t index, bool addToRenderTree)
{
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    return layoutWrapper;
}

void LayoutWrapper::SetCacheCount(int32_t cacheCount, const std::optional<LayoutConstraintF>& itemConstraint) {}

const std::list<RefPtr<LayoutWrapper>>& LayoutWrapper::GetAllChildrenWithBuild(bool addToRenderTree)
{
    return {};
}

void LayoutWrapper::RemoveChildInRenderTree(const RefPtr<LayoutWrapper>& wrapper) {}

void LayoutWrapper::RemoveChildInRenderTree(int32_t index) {}

void LayoutWrapper::RemoveAllChildInRenderTree() {}

void LayoutWrapper::ResetHostNode() {}

RefPtr<FrameNode> LayoutWrapper::GetHostNode() const
{
    return {};
}

WeakPtr<FrameNode> LayoutWrapper::GetWeakHostNode() const
{
    return {};
}

std::string LayoutWrapper::GetHostTag() const
{
    return V2::SWIPER_ETS_TAG;
}

int32_t LayoutWrapper::GetHostDepth() const
{
    return {};
}

void LayoutWrapper::CreateRootConstraint() {}

void LayoutWrapper::ApplyConstraint(LayoutConstraintF constraint) {}

void LayoutWrapper::ApplySafeArea(const SafeAreaInsets& insets, LayoutConstraintF& constraint) {}

// This will call child and self measure process.
void LayoutWrapper::Measure(const std::optional<LayoutConstraintF>& parentConstraint) {}

// Called to perform layout children.
void LayoutWrapper::Layout() {}

void LayoutWrapper::RestoreGeoState() {}

void LayoutWrapper::AvoidKeyboard() {}

void LayoutWrapper::ExpandSafeArea() {}

void LayoutWrapper::SaveGeoState() {}
void LayoutWrapper::ExpandSafeAreaInner() {}

void LayoutWrapper::ExpandIntoKeyboard() {}

bool LayoutWrapper::SkipMeasureContent() const
{
    return false;
}

bool LayoutWrapper::CheckNeedForceMeasureAndLayout()
{
    return false;
}

bool LayoutWrapper::CheckChildNeedForceMeasureAndLayout()
{
    return false;
}

void LayoutWrapper::MountToHostOnMainThread() {}

void LayoutWrapper::SwapDirtyLayoutWrapperOnMainThread() {}

void LayoutWrapper::BuildLazyItem() {}

std::pair<int32_t, int32_t> LayoutWrapper::GetLazyBuildRange()
{
    return {};
}

void LayoutWrapper::AddNodeFlexLayouts() {}

void LayoutWrapper::AddNodeLayoutTime(int64_t time) {}

void LayoutWrapper::AppendChild(const RefPtr<LayoutWrapper>& child, bool isOverlayNode) {}
} // namespace OHOS::Ace::NG
