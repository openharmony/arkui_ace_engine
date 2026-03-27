/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/components_ng/base/view_stack_processor.h"

namespace OHOS::Ace::NG {
thread_local std::unique_ptr<ViewStackProcessor> ViewStackProcessor::instance = nullptr;

ViewStackProcessor::ViewStackProcessor() = default;

ViewStackProcessor* ViewStackProcessor::GetInstance()
{
    if (!instance) {
        instance.reset(new ViewStackProcessor());
    }
    return instance.get();
}

RefPtr<UINode> ViewStackProcessor::Finish()
{
    if (elementsStack_.empty()) {
        return nullptr;
    }
    auto node = elementsStack_.top();
    elementsStack_.pop();
    return node;
}
} // namespace OHOS::Ace::NG
