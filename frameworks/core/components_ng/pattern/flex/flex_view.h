//
// Created by 陆泽辉 on 2022/8/4.
//

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LINEAR_LAYOUT_FLEX_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LINEAR_LAYOUT_FLEX_VIEW_H

#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT FlexView {
public:
    static void Create(FlexDirection direction, FlexAlign mainAxisAlign, FlexAlign crossAxisAlign);
    static void Direction(const FlexDirection& value);
    static void MainAxisAlign(const FlexAlign& value);
    static void CrossAxisAlign(const FlexAlign& value);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LINEAR_LAYOUT_FLEX_VIEW_H
