/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/syntax/lazy_layout_wrapper_builder.h"

namespace OHOS::Ace::NG {

LazyLayoutWrapperBuilder::LazyLayoutWrapperBuilder(
    const RefPtr<LazyForEachBuilder>& builder, const WeakPtr<LazyForEachNode>& host)
    : builder_(builder), host_(host)
{}

void LazyLayoutWrapperBuilder::SwapDirtyAndUpdateBuildCache() {}

void LazyLayoutWrapperBuilder::AdjustGridOffset()
{
    for (const auto& wrapper : childWrappers_) {
        auto frameNode = wrapper->GetHostNode();
        CHECK_NULL_VOID(frameNode);
        frameNode->AdjustGridOffset();
    }
}

int32_t LazyLayoutWrapperBuilder::OnGetTotalCount()
{
    CHECK_NULL_RETURN(builder_, 0);
    return builder_->GetTotalCount();
}

RefPtr<LayoutWrapper> LazyLayoutWrapperBuilder::OnGetOrCreateWrapperByIndex(int32_t index)
{
    auto totalCount = GetTotalCount();
    if ((index < 0) || (index >= totalCount)) {
        LOGE("index is illegal: %{public}d", index);
        return nullptr;
    }
    // check if the index needs to be converted to virtual index.
    if (lazySwiper_ &&
        ((startIndex_ && index < startIndex_.value() - 1) || (endIndex_ && index > endIndex_.value() + 1))) {
        if (index > startIndex_.value()) {
            index -= totalCount;
        } else {
            index += totalCount;
        }
    }
    return OnGetOrCreateWrapperByIndexLegacy(index);
}

std::pair<RefPtr<UINode>, std::string> LazyLayoutWrapperBuilder::GetOrCreateFrameNode(int32_t index, int32_t totalCount)
{
    RefPtr<UINode> uiNode;
    std::string id;
    // get frame node from previous cached.
    if ((index >= preStartIndex_) && (index <= preEndIndex_)) {
        auto iter = preNodeIds_.begin();
        std::advance(iter, index - preStartIndex_);
        if ((iter != preNodeIds_.end()) && (iter->has_value())) {
            id = iter->value();
            uiNode = builder_->GetChildByKey(id);
        }
    }
    if (!uiNode) {
        // convert index to real index.
        int32_t realIndex = index;
        if (lazySwiper_) {
            if (index >= totalCount) {
                realIndex -= totalCount;
            } else if (index < 0) {
                realIndex += totalCount;
            }
        }
        // create frame node.
        auto itemInfo = builder_->GetChildByIndex(realIndex, true);
        id = itemInfo.first;
        uiNode = itemInfo.second;
    }
    return std::pair(uiNode, id);
}

RefPtr<LayoutWrapper> LazyLayoutWrapperBuilder::OnGetOrCreateWrapperByIndexLegacy(int32_t index)
{
    int32_t totalCount = GetTotalCount();
    // The first time get the item, do not do the range check, and the subsequent get the item
    // needs to check whether it is in the upper and lower bounds (-1, +1) of the existing index.
    if (!startIndex_) {
        startIndex_ = index;
        endIndex_ = index;
    } else {
        if ((index >= startIndex_.value()) && (index <= endIndex_.value())) {
            auto iter = childWrappers_.begin();
            std::advance(iter, index - startIndex_.value());
            return *iter;
        }
        if ((index < (startIndex_.value() - 1)) || (index > (endIndex_.value() + 1))) {
            LOGE("need to obtain the item node in order and by step one: %{public}d", index);
            return nullptr;
        }
    }

    CHECK_NULL_RETURN(builder_, nullptr);
    const std::pair<RefPtr<UINode>, std::string>& pair = GetOrCreateFrameNode(index, totalCount);
    RefPtr<UINode> uiNode = pair.first;
    std::string id = pair.second;
    CHECK_NULL_RETURN(uiNode, nullptr);
    RefPtr<LayoutWrapper> wrapper;
    auto frameNode = DynamicCast<FrameNode>(uiNode);
    if (frameNode) {
        wrapper = frameNode->CreateLayoutWrapper(forceMeasure_, forceLayout_);
    } else {
        wrapper = uiNode->CreateLayoutWrapper(forceMeasure_, forceLayout_);
    }
    CHECK_NULL_RETURN(wrapper, nullptr);
    if (index == (startIndex_.value() - 1)) {
        // insert at begin.
        startIndex_ = index;
        childWrappers_.emplace_front(wrapper);
        nodeIds_.emplace_front(id);
        return wrapper;
    }
    // insert at end.
    endIndex_ = index;
    childWrappers_.emplace_back(wrapper);
    nodeIds_.emplace_back(id);
    return wrapper;
}

const std::list<RefPtr<LayoutWrapper>>& LazyLayoutWrapperBuilder::GetCachedChildLayoutWrapper()
{
    return childWrappers_;
}

const std::list<RefPtr<LayoutWrapper>>& LazyLayoutWrapperBuilder::OnExpandChildLayoutWrapper()
{
    auto total = GetTotalCount();
    if (!childWrappers_.empty()) {
        if (static_cast<int32_t>(childWrappers_.size()) == total) {
            return childWrappers_;
        }
        LOGE("can not mix lazy get and full get method!");
        childWrappers_.clear();
        return childWrappers_;
    }

    CHECK_NULL_RETURN(builder_, childWrappers_);
    for (int32_t index = 0; index < total; ++index) {
        auto itemInfo = builder_->GetChildByIndex(index, true);
        RefPtr<LayoutWrapper> wrapper;
        auto frameNode = DynamicCast<FrameNode>(itemInfo.second);
        auto uiNode = itemInfo.second;
        if (frameNode) {
            wrapper = frameNode->CreateLayoutWrapper(forceMeasure_, forceLayout_);
        } else if (uiNode) {
            wrapper = uiNode->CreateLayoutWrapper(forceMeasure_, forceLayout_);
        }
        if (!wrapper) {
            LOGE("fail to create wrapper");
            childWrappers_.clear();
            return childWrappers_;
        }
        nodeIds_.emplace_back(itemInfo.first);
        childWrappers_.emplace_back(wrapper);
    }
    startIndex_ = 0;
    endIndex_ = total - 1;
    return childWrappers_;
}

std::optional<std::string> LazyLayoutWrapperBuilder::GetKeyByIndexFromPreNodes(int32_t index)
{
    if ((index >= preStartIndex_) && (index <= preEndIndex_)) {
        auto iter = preNodeIds_.begin();
        std::advance(iter, index - preStartIndex_);
        if ((iter != preNodeIds_.end()) && (iter->has_value())) {
            return iter->value();
        }
    }
    return std::nullopt;
}

} // namespace OHOS::Ace::NG
