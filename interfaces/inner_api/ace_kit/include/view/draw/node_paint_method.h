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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_DRAW_NODE_PAINT_METHOD_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_DRAW_NODE_PAINT_METHOD_H

#include "interfaces/inner_api/ace_kit/include/base/ace_type.h"
#include "interfaces/inner_api/ace_kit/include/view/draw/modifier.h"

namespace OHOS::AceKit {
class NodePaintMethod : public Ace::AceType {
    DECLARE_ACE_TYPE(NodePaintMethod, Ace::AceType);

public:
    virtual Ace::RefPtr<Modifier> GetContentModifier() = 0;
};
} // namespace OHOS::AceKit

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_DRAW_NODE_PAINT_METHOD_H
