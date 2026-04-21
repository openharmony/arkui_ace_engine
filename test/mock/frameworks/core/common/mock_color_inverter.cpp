/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/common/color_inverter.h"

namespace OHOS::Ace {
ColorInverter::ColorInverter() = default;
ColorInverter::~ColorInverter() = default;
uint32_t ColorInverter::DefaultInverter(uint32_t color)
{
    return color;
}

Color ColorInverter::Invert(Color color, int32_t instanceId, const std::string& nodeTag)
{
    (void)instanceId;
    (void)nodeTag;
    return color;
}

template<>
ColorInverter& Singleton<ColorInverter>::GetInstance()
{
    static ColorInverter instance;
    return instance;
}
} // namespace OHOS::Ace
