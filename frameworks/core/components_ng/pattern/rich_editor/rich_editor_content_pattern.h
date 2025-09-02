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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_CONTENT_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_CONTENT_PATTERN_H

#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"

namespace OHOS::Ace::NG {

class RichEditorContentLayoutAlgorithm : public BoxLayoutAlgorithm {
    void Measure(LayoutWrapper* layoutWrapper) override {
        CHECK_NULL_VOID(layoutWrapper);
        ACE_SCOPED_TRACE("RichEditorContentLayoutAlgorithm::Measure");
        auto contentNode = layoutWrapper->GetHostNode();
        if (!contentNode || contentNode->GetTag() != V2::RICH_EDITOR_CONTENT_ETS_TAG) {
            TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "Measure, GetContentHost error, node=%{public}s",
                contentNode ? contentNode->GetTag().c_str() : "nullptr");
                return;
        }
        auto richEditorNode = DynamicCast<FrameNode>(contentNode->GetParent());
        if (!richEditorNode || richEditorNode->GetTag() != V2::RICH_EDITOR_ETS_TAG) {
            TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "Measure, GetHost error, node=%{public}s",
                richEditorNode ? richEditorNode->GetTag().c_str() : "nullptr");
            return;
        }
        auto geometryNode = layoutWrapper->GetGeometryNode();
        auto parentGeometryNode = richEditorNode->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode && parentGeometryNode);
        geometryNode->SetFrameSize(parentGeometryNode->GetFrameSize());
    }

    void Layout(LayoutWrapper* layoutWrapper) override 
    {
        ACE_SCOPED_TRACE("RichEditorContentLayoutAlgorithm::Layout");
    }

    std::optional<SizeF> MeasureContent(const LayoutConstraintF& constraint, LayoutWrapper* layoutWrapper) override
    {
        ACE_SCOPED_TRACE("RichEditorContentLayoutAlgorithm::MeasureContent");
        return std::nullopt;
    }
};

class RichEditorContentPattern : public Pattern {
    DECLARE_ACE_TYPE(RichEditorContentPattern, Pattern);
public:
    explicit RichEditorContentPattern(const WeakPtr<RichEditorPattern>& pattern) : weakPattern_(pattern) {}
    ~RichEditorContentPattern() = default;

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        ACE_SCOPED_TRACE("RichEditorContentPattern::CreateNodePaintMethod");
        auto richEditorPattern = weakPattern_.Upgrade();
        CHECK_NULL_RETURN(richEditorPattern, nullptr);
        if (!contentMod_) {
            contentMod_ = MakeRefPtr<RichEditorContentModifier>(richEditorPattern->textStyle_,
                &(richEditorPattern->paragraphs_), WeakClaim(this));
        }
        richEditorPattern->CreateRichEditorOverlayModifier();
        if (richEditorPattern->GetIsCustomFont()) {
            contentMod_->SetIsCustomFont(true);
        }
        return MakeRefPtr<RichEditorPaintMethod>(WeakClaim(this), &(richEditorPattern->paragraphs_),
            richEditorPattern->baselineOffset_, contentMod_, richEditorPattern->GetOverlayModifier());
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        ACE_SCOPED_TRACE("RichEditorContentPattern::CreateLayoutAlgorithm");
        return MakeRefPtr<RichEditorContentLayoutAlgorithm>();
    }

    RectF GetTextContentRect(bool isActualText = false) const
    {
        auto richEditorPattern = weakPattern_.Upgrade();
        CHECK_NULL_RETURN(richEditorPattern, {});
        return richEditorPattern->GetTextContentRect(isActualText);
    }

    const RectF& GetTextRect()
    {
        auto richEditorPattern = weakPattern_.Upgrade();
        CHECK_NULL_RETURN(richEditorPattern, invalidRect);
        return richEditorPattern->GetTextRect();
    }

    const std::vector<RectF>& GetRectsForPlaceholders()
    {
        auto richEditorPattern = weakPattern_.Upgrade();
        CHECK_NULL_RETURN(richEditorPattern, invalidVecRectf);
        return richEditorPattern->GetRectsForPlaceholders();
    }

    std::vector<CustomSpanPlaceholderInfo> GetCustomSpanPlaceholderInfo()
    {
        auto richEditorPattern = weakPattern_.Upgrade();
        CHECK_NULL_RETURN(richEditorPattern, {});
        return richEditorPattern->GetCustomSpanPlaceholderInfo();
    }

    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override
    {
        ACE_SCOPED_TRACE("RichEditorContentPattern::OnDirtyLayoutWrapperSwap");
        return true;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<RichEditorLayoutProperty>();
    }

    void OnAttachToFrameNode() override
    {
        auto frameNode = GetHost();
        CHECK_NULL_VOID(frameNode);
        auto renderContext = frameNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->UpdateClipEdge(true);
        renderContext->SetClipToFrame(true);
        auto layoutProperty = GetLayoutProperty<LayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    }
    
    RefPtr<RichEditorPattern> GetParentPattern()
    {
        return weakPattern_.Upgrade();
    }

private:
    WeakPtr<RichEditorPattern> weakPattern_;
    RefPtr<TextContentModifier> contentMod_ = nullptr;
    const RectF invalidRect;
    const std::vector<RectF> invalidVecRectf;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_CONTENT_PATTERN_H
