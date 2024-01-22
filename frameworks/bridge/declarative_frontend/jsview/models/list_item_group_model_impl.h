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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_LIST_ITEM_GROUP_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_LIST_ITEM_GROUP_MODEL_IMPL_H

#include "core/components_ng/pattern/list/list_item_group_model.h"

namespace OHOS::Ace::Framework {

class ListItemGroupModelImpl : public ListItemGroupModel {
public:
    ListItemGroupModelImpl() = default;
    ~ListItemGroupModelImpl() override = default;

    void Create(V2::ListItemGroupStyle listItemGroupStyle) override;
    void SetSpace(const Dimension& space) override;
    void SetDivider(const V2::ItemDivider& divider) override;
    void SetHeader(std::function<void()>&& header) override;
    void SetFooter(std::function<void()>&& footer) override;
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_LIST_ITEM_MODEL_IMPL_H
