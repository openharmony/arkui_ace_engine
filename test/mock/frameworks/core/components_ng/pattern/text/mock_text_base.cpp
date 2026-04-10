/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/components_ng/pattern/text/text_base.h"

namespace OHOS::Ace::NG {
VectorF TextBase::GetHostScale(const RefPtr<FrameNode>& host) const
{
    (void)host;
    return VectorF(1.0f, 1.0f);
}
} // namespace OHOS::Ace::NG
