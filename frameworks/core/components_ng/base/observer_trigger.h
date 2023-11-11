#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_OBSERVER_HANDLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_OBSERVER_HANDLER_H

#include <string>

#include "base/memory/referenced.h"

namespace OHOS::Ace::NG {
class NavDestinationPattern;
enum class NavDestinationState {
    ON_SHOW = 0,
    ON_HIDDEN = 1,
};

class UIObserverHandler {
public:
    static void NotifyNavigationStateChange(const RefPtr<NavDestinationPattern>& pattern, NavDestinationState state);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_OBSERVER_HANDLER_H
