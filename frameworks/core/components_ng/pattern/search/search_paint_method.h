/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_SEARCH_SEARCH_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_SEARCH_SEARCH_PAINT_METHOD_H

#include <utility>

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {

class SearchPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(SearchPaintMethod, NodePaintMethod)

public:
    SearchPaintMethod(const SizeF& buttonSize, const std::string& searchButton, bool isEnabled)
        : buttonSize_(buttonSize), searchButton_(searchButton), isSearchButtonEnabled_(isEnabled) {};
    ~SearchPaintMethod() override = default;

    CanvasDrawFunction GetContentDrawFunction(PaintWrapper* paintWrapper) override;

private:
    void PaintSearch(RSCanvas& canvas, PaintWrapper* paintWrapper) const;

    SizeF buttonSize_;
    std::string searchButton_;
    bool isSearchButtonEnabled_ = false;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_SEARCH_SEARCH_PAINT_METHOD_H
