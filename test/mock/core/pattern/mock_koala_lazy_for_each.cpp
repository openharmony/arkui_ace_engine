/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "mock_koala_lazy_for_each.h"

#include <gtest/gtest.h>

#include "core/components_ng/base/scroll_window_adapter.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
void MockKoalaLazyForEach::Register()
{
    auto adapter = parent_->GetPattern()->GetOrCreateScrollWindowAdapter();
    adapter->RegisterUpdater([this](int32_t s, void* pointer) {
        // frontend
        Update(s, pointer);
    });
    adapter->SetTotalCount(totalCnt_);
}

void MockKoalaLazyForEach::NormalModeUpdate(int32_t s, void* pointer)
{
    if (s < range_.first) { // to mock detachChildScopes
        for (auto& item : itemCache_) {
            if (item.first <= range_.first) {
                parent_->RemoveChild(item.second);
            }
        }
        itemCache_.clear();
    }
    bool insertInFront = false;
    auto* insertRef = (FrameNode*)pointer;
    VisibleRange visibleRange(parent_, s, s);
    int32_t index = s;

    parent_->GetScrollWindowAdapter()->Prepare(0);
    while (true) {
        if (index < 0 || index >= totalCnt_) {
            break;
        }

        auto item = CreateItem(index);
        if (!insertRef) {
            parent_->AddChild(item);
        } else if (insertInFront) {
            parent_->AddChildBefore(item, AceType::Claim(insertRef));
        } else {
            parent_->AddChildAfter(item, AceType::Claim(insertRef));
        }

        bool moreUp = visibleRange.NeedFillUp();
        if (moreUp && visibleRange.indexUp_ > 0) {
            index = --visibleRange.indexUp_;
        } else if (visibleRange.NeedFillDown()) {
            index = ++visibleRange.indexDown_;
        } else {
            index = -1;
        }
        insertInFront = moreUp;
        insertRef = moreUp ? visibleRange.markUp_ : visibleRange.markDown_;
    }

    range_ = { visibleRange.indexUp_, visibleRange.indexDown_ };
    // remove unused items
    for (auto it = itemCache_.begin(); it != itemCache_.end();) {
        if (it->first < visibleRange.indexUp_ || it->first > visibleRange.indexDown_) {
            parent_->RemoveChild(it->second);
            it = itemCache_.erase(it);
        } else {
            ++it;
        }
    }
}

void MockKoalaLazyForEach::RangeModeUpdate(int32_t s, int32_t e)
{
    while (!parent_->GetChildren().empty()) {
        parent_->RemoveChildAtIndex(0);
    }
    // range mode
    for (int i = s; i <= e; ++i) {
        auto item = CreateItem(i);
        parent_->AddChild(item);
    }
    range_ = { s, e };
    parent_->GetScrollWindowAdapter()->Prepare(0);
}

void MockKoalaLazyForEach::Update(int32_t s, void* pointer)
{
    taskQ_.push([=]() { NormalModeUpdate(s, pointer); });
}

RefPtr<FrameNode> MockKoalaLazyForEach::CreateItem(int32_t idx)
{
    auto it = itemCache_.find(idx);
    if (it != itemCache_.end()) {
        return it->second;
    }
    auto node = itemCreator_(idx);
    itemCache_[idx] = node;
    return node;
}

void MockKoalaLazyForEach::Increment(int32_t lineNumber)
{
    ASSERT_FALSE(taskQ_.empty()) << "Failure on line " << lineNumber;
    taskQ_.back()();
    while (!taskQ_.empty()) {
        taskQ_.pop();
    }
}

bool VisibleRange::NeedFillUp()
{
    auto more = parent_->GetScrollWindowAdapter()->NeedMoreElements(markUp_, FillDirection::START);
    if (more == nullptr)
        return false;
    markUp_ = more;
    return true;
}

bool VisibleRange::NeedFillDown()
{
    auto more = parent_->GetScrollWindowAdapter()->NeedMoreElements(markDown_, FillDirection::END);
    if (more == nullptr)
        return false;
    markDown_ = more;
    return true;
}
} // namespace OHOS::Ace::NG
