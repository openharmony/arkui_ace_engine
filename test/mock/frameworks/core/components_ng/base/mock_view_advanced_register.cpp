/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/components_ng/base/view_advanced_register.h"

namespace OHOS::Ace::NG {
thread_local std::shared_ptr<ViewAdvancedRegister> ViewAdvancedRegister::instance_ = nullptr;

std::shared_ptr<ViewAdvancedRegister> ViewAdvancedRegister::GetInstance()
{
    if (!instance_) {
        instance_ = std::make_shared<ViewAdvancedRegister>();
    }
    return instance_;
}

RefPtr<PagePattern> ViewAdvancedRegister::CreatePagePattern(const RefPtr<PageInfo>& pageInfo)
{
    (void)pageInfo;
    return nullptr;
}

RefPtr<Pattern> ViewAdvancedRegister::GeneratePattern(const std::string& patternName)
{
    (void)patternName;
    return nullptr;
}

RefPtr<StageManager> ViewAdvancedRegister::GenerateStageManager(const RefPtr<FrameNode>& stage)
{
    (void)stage;
    return nullptr;
}
} // namespace OHOS::Ace::NG
