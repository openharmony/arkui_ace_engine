/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/pipeline/base/constants.h"
#include "core/components/common/properties/alignment.h"

namespace OHOS::Ace {
const double ACE_PI = 3.14159265358979323846;
const double ACE_E = 2.71828182845904523536;

const Alignment Alignment::TOP_LEFT = Alignment(-1.0, -1.0);
const Alignment Alignment::TOP_CENTER = Alignment(0.0, -1.0);
const Alignment Alignment::TOP_RIGHT = Alignment(1.0, -1.0);
const Alignment Alignment::CENTER_LEFT = Alignment(-1.0, 0.0);
const Alignment Alignment::CENTER = Alignment(0.0, 0.0);
const Alignment Alignment::CENTER_RIGHT = Alignment(1.0, 0.0);
const Alignment Alignment::BOTTOM_LEFT = Alignment(-1.0, 1.0);
const Alignment Alignment::BOTTOM_CENTER = Alignment(0.0, 1.0);
const Alignment Alignment::BOTTOM_RIGHT = Alignment(1.0, 1.0);
} // namespace OHOS::Ace
