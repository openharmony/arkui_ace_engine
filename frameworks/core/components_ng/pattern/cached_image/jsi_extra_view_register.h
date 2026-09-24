/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2023-2023. All rights reserved.
 */

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_JSI_ADVANCE_VIEW_REGISTER_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_JSI_ADVANCE_VIEW_REGISTER_H

#include "bridge/declarative_frontend/engine/bindings_defines.h"

namespace OHOS::Ace::Framework {

void RegisterExtraViews(BindingTarget globalObj);

void RegisterExtraViewByName(BindingTarget globalObj, const std::string& moduleName);

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_JSI_ADVANCE_VIEW_REGISTER_H