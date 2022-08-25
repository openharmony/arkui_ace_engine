//
// Created by 陆泽辉 on 2022/8/8.
//

#ifndef ARKUI_ACE_ENGINE_FLEX_LAYOUT_STYLES_H
#define ARKUI_ACE_ENGINE_FLEX_LAYOUT_STYLES_H

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
struct FlexLayoutAttribute {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FlexDirection, FlexDirection);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(MainAxisAlign, FlexAlign);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(CrossAxisAlign, FlexAlign);
};
} // namespace OHOS::Ace::NG

#endif // ARKUI_ACE_ENGINE_FLEX_LAYOUT_STYLES_H
