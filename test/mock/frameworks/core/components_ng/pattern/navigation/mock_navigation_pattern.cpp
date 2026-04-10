/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/components_ng/pattern/navigation/navigation_pattern.h"

namespace OHOS::Ace::NG {
NavigationPattern::NavigationPattern() = default;

void NavigationPattern::OnAttachToFrameNode() {}

void NavigationPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    (void)frameNode;
}

void NavigationPattern::ContentChangeByDetaching(PipelineContext* pipeline)
{
    (void)pipeline;
}

void NavigationPattern::OnModifyDone() {}

void NavigationPattern::OnWindowHide() {}

bool NavigationPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    (void)dirty;
    (void)config;
    return false;
}

void NavigationPattern::BeforeSyncGeometryProperties(const DirtySwapConfig& config)
{
    (void)config;
}

void NavigationPattern::OnLanguageConfigurationUpdate() {}

void NavigationPattern::OnDpiConfigurationUpdate() {}

void NavigationPattern::SetNavigationStack(const RefPtr<NavigationStack>& navigationStack, bool needUpdateCallback)
{
    (void)needUpdateCallback;
    navigationStack_ = navigationStack;
}

void NavigationPattern::OnVisibleChange(bool isVisible)
{
    (void)isVisible;
}

void NavigationPattern::OnColorConfigurationUpdate() {}

bool NavigationPattern::OnThemeScopeUpdate(int32_t themeScopeId)
{
    (void)themeScopeId;
    return false;
}

void NavigationPattern::DumpInfo() {}

void NavigationPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    (void)json;
}

void NavigationPattern::OnAttachToMainTree() {}

void NavigationPattern::OnDetachFromMainTree() {}

void NavigationPattern::SetPageViewportConfig(const RefPtr<PageViewportConfig>& config)
{
    (void)config;
}

void NavigationPattern::OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type)
{
    (void)width;
    (void)height;
    (void)type;
}

void NavigationPattern::OnAvoidInfoChange(const ContainerModalAvoidInfo& info)
{
    (void)info;
}

void NavigationPattern::MarkAllNavDestinationDirtyIfNeeded(const RefPtr<FrameNode>& hostNode, bool skipCheck)
{
    (void)hostNode;
    (void)skipCheck;
}

bool NavigationPattern::CustomizeExpandSafeArea()
{
    return false;
}

void NavigationPattern::FireNavigationChange(const RefPtr<UINode>& node, bool isShow, bool isFirst, bool isFromWindow)
{
    (void)node;
    (void)isShow;
    (void)isFirst;
    (void)isFromWindow;
}
} // namespace OHOS::Ace::NG
