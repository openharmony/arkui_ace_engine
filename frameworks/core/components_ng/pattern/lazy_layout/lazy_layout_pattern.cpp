/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/lazy_layout/lazy_layout_pattern.h"

#include <string>

#include "base/log/dump_log.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

bool LazyLayoutPattern::SetNextStickyHeaderGap(const std::optional<float>& gap)
{
    const bool unchanged = nextStickyHeaderGap_.has_value() == gap.has_value() &&
                           (!gap.has_value() || NearEqual(nextStickyHeaderGap_.value(), gap.value()));
    if (unchanged) {
        return false;
    }
    nextStickyHeaderGap_ = gap;
    return true;
}

void LazyLayoutPattern::PublishNextStickyHeaderGap(const std::optional<float>& gap)
{
    if (!SetNextStickyHeaderGap(gap)) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    if (pipeline && pipeline->IsLayouting()) {
        pipeline->AddAfterLayoutTask([weakHost = WeakPtr<FrameNode>(host)]() {
            auto node = weakHost.Upgrade();
            CHECK_NULL_VOID(node);
            node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        });
        return;
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void LazyLayoutPattern::NotifyParentOnStickyHeaderChange()
{
    const bool hasStickyHeader = HasStickyHeader();
    if (!lastNotifiedHasStickyHeader_.has_value()) {
        lastNotifiedHasStickyHeader_ = hasStickyHeader;
        return;
    }
    if (lastNotifiedHasStickyHeader_.value() == hasStickyHeader) {
        return;
    }
    lastNotifiedHasStickyHeader_ = hasStickyHeader;

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto parent = host->GetAncestorNodeOfFrame(true);
    while (parent) {
        if (parent->GetPattern<LazyLayoutPattern>()) {
            parent->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
            return;
        }
        auto layoutProperty = parent->GetLayoutProperty();
        if (!layoutProperty || !layoutProperty->GetNeedLazyLayout()) {
            return;
        }
        parent = parent->GetAncestorNodeOfFrame(true);
    }
}

void LazyLayoutPattern::OnDetachFromMainTree()
{
    nextStickyHeaderGap_.reset();
    lastNotifiedHasStickyHeader_.reset();
    Pattern::OnDetachFromMainTree();
}

void LazyLayoutPattern::DumpStickyHeaderHandoffInfo() const
{
    const auto gap = nextStickyHeaderGap_.has_value() ? std::to_string(nextStickyHeaderGap_.value()) : "null";
    DumpLog::GetInstance().AddDesc("nextStickyHeaderGap:" + gap);
}

void LazyLayoutPattern::DumpStickyHeaderHandoffInfo(std::unique_ptr<JsonValue>& json) const
{
    CHECK_NULL_VOID(json);
    if (nextStickyHeaderGap_.has_value()) {
        json->Put("nextStickyHeaderGap", nextStickyHeaderGap_.value());
        return;
    }
    json->Put("nextStickyHeaderGap", "null");
}

} // namespace OHOS::Ace::NG
