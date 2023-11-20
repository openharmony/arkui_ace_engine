#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_OBSERVER_HANDLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_OBSERVER_HANDLER_H

#include <string>
#include <utility>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"

namespace OHOS::Ace::NG {
enum class NavDestinationState {
    ON_SHOW = 0,
    ON_HIDDEN = 1,
};

struct NavDestinationInfo {
    std::string navigationId;
    std::string name;
    NavDestinationState state;

    NavDestinationInfo(std::string id, std::string name, NavDestinationState state)
        : navigationId(std::move(id)), name(std::move(name)), state(state)
    {}
};

class UIObserverHandler {
public:
    static void NotifyNavigationStateChange(const WeakPtr<AceType>& weakPattern, NavDestinationState state);
    static std::shared_ptr<NavDestinationInfo> GetNavigationState(const RefPtr<AceType>& node);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_OBSERVER_HANDLER_H
