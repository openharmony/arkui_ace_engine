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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_VIEW_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_VIEW_H

#include "ui/base/geometry/calc_dimension.h"
#include "ui/base/macros.h"
#include "ui/base/referenced.h"


namespace OHOS::Ace::Kit {

class FrameNode;

class ACE_FORCE_EXPORT View : public Referenced {
public:
    explicit View(const RefPtr<FrameNode>& node);
    ~View() override;
    const RefPtr<FrameNode>& GetNode() const;

    void SetWidth(const CalcDimension& width);
    void SetHeight(const CalcDimension& height);

protected:
    View();
    RefPtr<FrameNode> node_;
};

} // namespace OHOS::Ace::Kit
#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_VIEW_H
