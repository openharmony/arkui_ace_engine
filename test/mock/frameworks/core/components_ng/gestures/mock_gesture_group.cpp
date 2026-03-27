/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/components_ng/gestures/gesture_group.h"

namespace OHOS::Ace::NG {
int32_t GestureGroup::SizeofMe()
{
    return 0;
}

int32_t GestureGroup::Serialize(char* buff)
{
    (void)buff;
    return 0;
}

RefPtr<Gesture> GestureGroup::MakeGesture(GestureType type)
{
    (void)type;
    return nullptr;
}

int32_t GestureGroup::Deserialize(const char* buff)
{
    (void)buff;
    return 0;
}

RefPtr<NGGestureRecognizer> GestureGroup::CreateRecognizer()
{
    return nullptr;
}

void GestureGroup::RemoveChildrenByTag(const std::string& gestureTag, bool& needRecollect)
{
    (void)gestureTag;
    (void)needRecollect;
}

void GestureGroup::RemoveGesture(RefPtr<Gesture> gesture)
{
    (void)gesture;
}
} // namespace OHOS::Ace::NG
