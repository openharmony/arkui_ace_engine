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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CANVAS_PAINT_OP_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CANVAS_PAINT_OP_H

#include <optional>

#include "core/components_ng/pattern/custom_paint/canvas_paint_mem.h"

namespace OHOS::Ace {
struct BezierCurveParam;
class Rect;
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
class CanvasPaintMethod;
class PaintWrapper;

class CanvasPaintOp final {
public:
    CanvasPaintOp() : mHasText(false) {}
    ~CanvasPaintOp() { Reset(); }

    void Draw(CanvasPaintMethod* method, PaintWrapper* paintWrapper) const;
    void Reset();
    bool Empty() const {return fUsed == 0; }

    bool HasText() const { return mHasText; }
    size_t UsedSize() const { return fUsed; }
    size_t AllocatedSize() const { return fReserved; }

    void Save();
    void Restore();
    void FillText(const std::string& text, double x, double y, std::optional<double>& maxWidth);
    void FillRect(const Rect& rect);
    void BezierCurveTo(const BezierCurveParam& param);

private:
    template <typename T, typename... Args>
    void* Push(size_t, Args&&...);

    template <typename Fn, typename... Args>
    void Map(const Fn[], Args...) const;

    template <typename T> static constexpr inline T Align2(T x) { return (x + 1) >> 1 << 1; }
    template <typename T> static constexpr inline T Align4(T x) { return (x + 3) >> 2 << 2; }
    template <typename T> static constexpr inline T Align8(T x) { return (x + 7) >> 3 << 3; }

    template <typename T> static constexpr inline bool IsAlign2(T x) { return (x & 1) == 0; }
    template <typename T> static constexpr inline bool IsAlign4(T x) { return (x & 3) == 0; }
    template <typename T> static constexpr inline bool IsAlign8(T x) { return (x & 7) == 0; }
    template <typename T> static constexpr inline bool IsPow2(T value)
    {
        return (value & (value - 1)) == 0;
    }
    template <typename T> static constexpr inline T AlignPtr(T x)
    {
        return sizeof(void*) == POINTSIZE8 ? Align8(x) : Align4(x);
    }
    template <typename T> static constexpr inline bool IsAlignPtr(T x)
    {
        return sizeof(void*) == POINTSIZE8 ? IsAlign8(x) : IsAlign4(x);
    }

    AutoTMalloc<uint8_t> fBytes;
    size_t fUsed = 0;
    size_t fReserved = 0;

    bool mHasText : 1;
    static constexpr uint8_t SKIPSIZE = 24;
    static constexpr uint8_t POINTSIZE8 = 8;
    static constexpr uint16_t PAGESIZE = 4096;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CANVAS_PAINT_OP_H
