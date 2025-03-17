/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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
#include "core/components/multimodal/rosen_render_multimodal.h"

#include "rosen_text/typography_create.h"
#include "rosen_text/typography_style.h"

#ifndef USE_ROSEN_DRAWING
#include "third_party/skia/include/core/SkPaint.h"
#include "third_party/skia/include/core/SkPoint.h"
#include "third_party/skia/include/core/SkRRect.h"
#endif

#include "base/i18n/localization.h"
#include "core/components/calendar/rosen_render_calendar.h"
#include "core/components/font/constants_converter.h"
#include "core/components/font/rosen_font_collection.h"
#include "core/pipeline/base/rosen_render_context.h"

namespace OHOS::Ace {
namespace {
constexpr double DEFAULT_SIZE = 20.0;
constexpr double LIMIT_WIDTH = 18.0;
constexpr double CORNER_RADIUS = 8.0;
constexpr double FONT_SIZE = 14;
const char ELLIPSIS[] = "...";
} // namespace

void RosenRenderMultimodal::Paint(RenderContext& context, const Offset& offset)
{
    RenderNode::Paint(context, offset);

    if (!isSubscriptShow_) {
        return;
    }

    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (canvas == nullptr) {
        LOGE("Paint canvas is null");
        return;
    }

    auto width = NormalizeToPx(Dimension(DEFAULT_SIZE, DimensionUnit::VP));
    auto height = NormalizeToPx(Dimension(DEFAULT_SIZE, DimensionUnit::VP));
    auto corner = NormalizeToPx(Dimension(CORNER_RADIUS, DimensionUnit::VP));

#ifndef USE_ROSEN_DRAWING
    SkPaint paint;
    paint.setAntiAlias(true);
    paint.setColor(Color::FromARGB(230, 0, 0, 0).GetValue());
#else
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(Color::FromARGB(230, 0, 0, 0).GetValue());
#endif

    UpdateParagraph(offset, subscript_.GetVoiceContent());
    paragraph_->Layout(GetLayoutSize().Width());
    if (paragraph_->GetActualWidth() > NormalizeToPx(Dimension(LIMIT_WIDTH, DimensionUnit::VP))) {
        width = height + (paragraph_->GetActualWidth() - NormalizeToPx(Dimension(LIMIT_WIDTH, DimensionUnit::VP)));
    }
#ifndef USE_ROSEN_DRAWING
    SkVector radii[] = { { corner, corner }, { 0, 0 }, { corner, corner }, { 0, 0 } };
    SkRRect rrect;
    rrect.setRectRadii(SkRect::MakeXYWH(offset.GetX(), offset.GetY(), width, height), radii);
    canvas->drawRRect(rrect, paint);
#else
    std::vector<RSPoint> radii = { { corner, corner }, { 0, 0 }, { corner, corner }, { 0, 0 } };
    RSRoundRect rrect(RSRect(offset.GetX(), offset.GetY(), offset.GetX() + width, offset.GetY() + height), radii);
    canvas->AttachBrush(brush);
    canvas->DrawRoundRect(rrect);
    canvas->DetachBrush();
#endif

    auto leftOffset = paragraph_->GetActualWidth() / 2;
    auto centerX = offset.GetX() + width / 2;
    auto centerY = offset.GetY() + height / 2;
    paragraph_->Paint(canvas, centerX - leftOffset, centerY - paragraph_->GetHeight() / 2);
}

void RosenRenderMultimodal::UpdateParagraph(const Offset& offset, const std::string& text)
{
    using namespace Constants;
    Rosen::TypographyStyle style;
    style.maxLines = 1;
    style.ellipsis = StringUtils::Str8ToStr16(ELLIPSIS);

    auto fontCollection = RosenFontCollection::GetInstance().GetFontCollection();
    if (!fontCollection) {
        LOGW("UpdateParagraph: fontCollection is null");
        return;
    }
    std::unique_ptr<Rosen::TypographyCreate> builder = Rosen::TypographyCreate::Create(style, fontCollection);
    Rosen::TextStyle txtStyle;
    txtStyle.fontSize = NormalizeToPx(Dimension(FONT_SIZE, DimensionUnit::FP));
    txtStyle.color = Color::FromARGB(255, 255, 255, 255).GetValue();
    txtStyle.locale = Localization::GetInstance()->GetFontLocale();
    builder->PushStyle(txtStyle);
    builder->AppendText(StringUtils::Str8ToStr16(text));
    paragraph_ = builder->CreateTypography();
}
} // namespace OHOS::Ace
