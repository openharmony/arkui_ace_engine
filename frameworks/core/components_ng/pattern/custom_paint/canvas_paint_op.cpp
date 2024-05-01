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

#include "core/components_ng/pattern/custom_paint/canvas_paint_op.h"

#include "core/components_ng/pattern/custom_paint/canvas_paint_method.h"

namespace OHOS::Ace::NG {

#define X(T) T,
enum class Type : uint8_t {
#include "canvas_paint_ops.in"
};
#undef X

struct Op {
    uint32_t type : 8;
    uint32_t skip : 24;
};
static_assert(sizeof(Op) == 4, "size of canvas op shoule be 4");

struct SaveOp final : Op {
    static constexpr auto kType = Type::SaveOp;
    void Draw(CanvasPaintMethod* method, PaintWrapper*) const { method->Save(); }
};

struct RestoreOp final : Op {
    static constexpr auto kType = Type::RestoreOp;
    void Draw(CanvasPaintMethod* method, PaintWrapper*) const { method->Restore(); }
};

struct FillRectOp final : Op {
    static constexpr auto kType = Type::FillRectOp;
    explicit FillRectOp(const Rect& rect): rect(std::move(rect)) {}
    Rect rect;
    void Draw(CanvasPaintMethod* method, PaintWrapper*) const { method->Restore(); }
};

struct FillTextOp final : Op {
    static constexpr auto kType = Type::FillTextOp;
    FillTextOp(const std::string& text, double x, double y, std::optional<double> maxWidth)
        : text(std::move(text)), x(x), y(y), maxWidth(maxWidth) {}
    std::string text;
    double x, y;
    std::optional<double> maxWidth;
    void Draw(CanvasPaintMethod* method, PaintWrapper* paintWrapper) const
    {
        method->FillText(paintWrapper, text, x, y, maxWidth);
    }
};

struct BezierCurveToOp final : Op {
    static constexpr auto kType = Type::BezierCurveToOp;
    explicit BezierCurveToOp(const BezierCurveParam& param): param(param) {}
    BezierCurveParam param;
    void Draw(CanvasPaintMethod* method, PaintWrapper*) const { method->BezierCurveTo(param); }
};

typedef void (*DrawFn)(const void*, CanvasPaintMethod* method, PaintWrapper* paintWrapper);
typedef void (*VoidFn)(const void*);

#define X(T)                                                                                   \
    [](const void* op, CanvasPaintMethod* method, PaintWrapper* paintWrapper) {                \
        ((const T*)op)->Draw(method, paintWrapper);                                            \
    },
static const DrawFn DRAW_FNS[] = {
    #include "./canvas_paint_ops.in"
};
#undef X

#define X(T)                                                                                    \
    !std::is_trivially_destructible<T>::value ? [](const void* op) { ((const T*)op)->~T(); }    \
                                                : (VoidFn) nullptr,
static const VoidFn DTOR_FBS[] = {
    #include "./canvas_paint_ops.in"
};
#undef X

void CanvasPaintOp::Draw(CanvasPaintMethod* method, PaintWrapper* paintWrapper) const
{
    Map(DRAW_FNS, method, paintWrapper);
}

void CanvasPaintOp::Reset()
{
    Map(DTOR_FBS);
    fUsed = 0;
}

void CanvasPaintOp::Save()
{
    Push<SaveOp>(0);
}
void CanvasPaintOp::Restore()
{
    Push<RestoreOp>(0);
}

void CanvasPaintOp::FillText(const std::string& text, double x, double y, std::optional<double>& maxWidth)
{
    Push<FillTextOp>(0, text, x, y, maxWidth);
}

void CanvasPaintOp::FillRect(const Rect& rect)
{
    Push<FillRectOp>(0, rect);
}

void CanvasPaintOp::BezierCurveTo(const BezierCurveParam& param)
{
    Push<BezierCurveToOp>(0, param);
}

template <typename T, typename... Args>
void* CanvasPaintOp::Push(size_t pod, Args&&... args)
{
    size_t skip = AlignPtr(sizeof(T) + pod);
    ACE_DCHECK(skip < (1 << SKIPSIZE));
    if (fUsed + skip > fReserved) {
        static_assert(IsPow2(PAGESIZE), "This math needs updating for non-pow2.");
        fReserved = (fUsed + skip + PAGESIZE) & ~(PAGESIZE - 1);
        fBytes.realloc(fReserved);
        if (!fBytes.get()) {
            TAG_LOGE(AceLogTag::ACE_CANVAS_COMPONENT, "realloc failed");
        }
    }
    ACE_DCHECK(fUsed + skip <= fReserved);
    auto op = (T*)(fBytes.get() + fUsed);
    fUsed += skip;
    new (op) T{std::forward<Args>(args)...};
    op->type = (uint32_t)T::kType;
    op->skip = skip;
    return op + 1;
}

template <typename Fn, typename... Args>
inline void CanvasPaintOp::Map(const Fn fns[], Args... args) const
{
    auto end = fBytes.get() + fUsed;
    for (const uint8_t* ptr = fBytes.get(); ptr < end;) {
        auto op = (const Op*)ptr;
        auto type = op->type;
        auto skip = op->skip;
        if (auto fn = fns[type]) {
            fn(op, args...);
        }
        ptr += skip;
    }
}

} // namespace OHOS::Ace::NG
