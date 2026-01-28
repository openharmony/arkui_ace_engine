/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { memo, memo_skip } from 'arkui.stateManagement.runtime'
import { WithThemeAttribute, ArkWithThemeComponent, ArkWithThemePeer, ThemeColorMode } from '#generated'
import { ArkThemeScopeManager } from '#arktheme'
import { NodeAttach, remember } from '@koalaui/runtime'
import { GlobalStateManager } from '@koalaui/runtime';

@memo
export function WithThemeImpl(
    @memo @memo_skip
    style: ((attributes: WithThemeAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkWithThemeComponent>((): ArkWithThemeComponent => {
        return new ArkWithThemeComponent()
    })
    NodeAttach<ArkWithThemePeer>((): ArkWithThemePeer => ArkWithThemePeer.create(receiver), (peer: ArkWithThemePeer): void => {
        receiver.setPeer(peer)

        const withThemeId = receiver.getPeer()?.getId() ?? 0;
        ArkThemeScopeManager.getInstance().onComponentCreateEnter("WithTheme", receiver.getPeer()?.getId(), receiver.isFirstRender)
        style?.(receiver)
        ArkThemeScopeManager.getInstance().onComponentCreateExit(receiver.getPeer()?.getId())
        receiver.setPeer(undefined)

        GlobalStateManager.instance.namedState<int32>("themeScopeId", () => withThemeId);
        const themeOptions = ArkThemeScopeManager.getInstance().getThemeOptionsById(withThemeId);
        ArkThemeScopeManager.getInstance().updateColorMode(themeOptions?.colorMode ?? ThemeColorMode.SYSTEM);

        content_?.()

        ArkThemeScopeManager.getInstance().restoreColorMode();
        ArkThemeScopeManager.getInstance().onScopeExit();

        receiver.isFirstRender = false;
    })
}