/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { ResourceColor } from 'arkui/component/units';
import { Colors, CustomColors } from '@ohos/arkui/theme';
import { _r } from 'arkui/component/resources';

export class ArkSystemColors implements Colors {
    public brand: ResourceColor;
    public warning: ResourceColor;
    public alert: ResourceColor;
    public confirm: ResourceColor;

    public fontPrimary: ResourceColor;
    public fontSecondary: ResourceColor;
    public fontTertiary: ResourceColor;
    public fontFourth: ResourceColor;
    public fontEmphasize: ResourceColor;

    public fontOnPrimary: ResourceColor;
    public fontOnSecondary: ResourceColor;
    public fontOnTertiary: ResourceColor;
    public fontOnFourth: ResourceColor;

    public iconPrimary: ResourceColor;
    public iconSecondary: ResourceColor;
    public iconTertiary: ResourceColor;
    public iconFourth: ResourceColor;
    public iconEmphasize: ResourceColor;
    public iconSubEmphasize: ResourceColor;

    public iconOnPrimary: ResourceColor;
    public iconOnSecondary: ResourceColor;
    public iconOnTertiary: ResourceColor;
    public iconOnFourth: ResourceColor;

    public backgroundPrimary: ResourceColor;
    public backgroundSecondary: ResourceColor;
    public backgroundTertiary: ResourceColor;
    public backgroundFourth: ResourceColor;
    public backgroundEmphasize: ResourceColor;

    public compForegroundPrimary: ResourceColor;
    public compBackgroundPrimary: ResourceColor;
    public compBackgroundPrimaryTran: ResourceColor;
    public compBackgroundPrimaryContrary: ResourceColor;
    public compBackgroundGray: ResourceColor;
    public compBackgroundSecondary: ResourceColor;
    public compBackgroundTertiary: ResourceColor;
    public compBackgroundEmphasize: ResourceColor;
    public compBackgroundNeutral: ResourceColor;
    public compEmphasizeSecondary: ResourceColor;
    public compEmphasizeTertiary: ResourceColor;
    public compDivider: ResourceColor;
    public compCommonContrary: ResourceColor;
    public compBackgroundFocus: ResourceColor;
    public compFocusedPrimary: ResourceColor;
    public compFocusedSecondary: ResourceColor;
    public compFocusedTertiary: ResourceColor;

    public interactiveHover: ResourceColor;
    public interactivePressed: ResourceColor;
    public interactiveFocus: ResourceColor;
    public interactiveActive: ResourceColor;
    public interactiveSelect: ResourceColor;
    public interactiveClick: ResourceColor;

    constructor() {
        this.brand = _r(125830976, 10001, '', '');
        this.warning = _r(125830979, 10001, '', '');
        this.alert = _r(125830980, 10001, '', '');
        this.confirm = _r(125830981, 10001, '', '');

        this.fontPrimary = _r(125830982, 10001, '', '');
        this.fontSecondary = _r(125830983, 10001, '', '');
        this.fontTertiary = _r(125830984, 10001, '', '');
        this.fontFourth = _r(125830985, 10001, '', '');
        this.fontEmphasize = _r(125830986, 10001, '', '');

        this.fontOnPrimary = _r(125830987, 10001, '', '');
        this.fontOnSecondary = _r(125830988, 10001, '', '');
        this.fontOnTertiary = _r(125830989, 10001, '', '');
        this.fontOnFourth = _r(125830990, 10001, '', '');

        this.iconPrimary = _r(125830991, 10001, '', '');
        this.iconSecondary = _r(125830992, 10001, '', '');
        this.iconTertiary = _r(125830993, 10001, '', '');
        this.iconFourth = _r(125830994, 10001, '', '');
        this.iconEmphasize = _r(125830995, 10001, '', '');
        this.iconSubEmphasize = _r(125830996, 10001, '', '');

        this.iconOnPrimary = _r(125831057, 10001, '', '');
        this.iconOnSecondary = _r(125831058, 10001, '', '');
        this.iconOnTertiary = _r(125831059, 10001, '', '');
        this.iconOnFourth = _r(125831060, 10001, '', '');

        this.backgroundPrimary = _r(125831061, 10001, '', '');
        this.backgroundSecondary = _r(125831062, 10001, '', '');
        this.backgroundTertiary = _r(125831063, 10001, '', '');
        this.backgroundFourth = _r(125831064, 10001, '', '');
        this.backgroundEmphasize = _r(125831065, 10001, '', '');

        this.compForegroundPrimary = _r(125831003, 10001, '', '');
        this.compBackgroundPrimary = _r(125831004, 10001, '', '');
        this.compBackgroundPrimaryTran = _r('', '', 'sys.color.comp_background_primary_tran');
        this.compBackgroundPrimaryContrary = _r(125831005, 10001, '', '');
        this.compBackgroundGray = _r(125831006, 10001, '', '');
        this.compBackgroundSecondary = _r(125831007, 10001, '', '');
        this.compBackgroundTertiary = _r(125831008, 10001, '', '');
        this.compBackgroundEmphasize = _r(125831009, 10001, '', '');
        this.compBackgroundNeutral = _r(125831066, 10001, '', '');
        this.compEmphasizeSecondary = _r(125831011, 10001, '', '');
        this.compEmphasizeTertiary = _r(125831012, 10001, '', '');
        this.compDivider = _r(125831013, 10001, '', '');
        this.compCommonContrary = _r(125831014, 10001, '', '');
        this.compBackgroundFocus = _r(125831015, 10001, '', '');
        this.compFocusedPrimary = _r(125831016, 10001, '', '');
        this.compFocusedSecondary = _r(125831017, 10001, '', '');
        this.compFocusedTertiary = _r(125831018, 10001, '', '');

        this.interactiveHover = _r(125831019, 10001, '', '');
        this.interactivePressed = _r(125831020, 10001, '', '');
        this.interactiveFocus = _r(125831021, 10001, '', '');
        this.interactiveActive = _r(125831022, 10001, '', '');
        this.interactiveSelect = _r(125831023, 10001, '', '');
        this.interactiveClick = _r(125831024, 10001, '', '');
    }
}

export class ArkSystemCustomColors implements CustomColors {
    public brand?: ResourceColor;
    public warning?: ResourceColor;
    public alert?: ResourceColor;
    public confirm?: ResourceColor;

    public fontPrimary?: ResourceColor;
    public fontSecondary?: ResourceColor;
    public fontTertiary?: ResourceColor;
    public fontFourth?: ResourceColor;
    public fontEmphasize?: ResourceColor;

    public fontOnPrimary?: ResourceColor;
    public fontOnSecondary?: ResourceColor;
    public fontOnTertiary?: ResourceColor;
    public fontOnFourth?: ResourceColor;

    public iconPrimary?: ResourceColor;
    public iconSecondary?: ResourceColor;
    public iconTertiary?: ResourceColor;
    public iconFourth?: ResourceColor;
    public iconEmphasize?: ResourceColor;
    public iconSubEmphasize?: ResourceColor;

    public iconOnPrimary?: ResourceColor;
    public iconOnSecondary?: ResourceColor;
    public iconOnTertiary?: ResourceColor;
    public iconOnFourth?: ResourceColor;

    public backgroundPrimary?: ResourceColor;
    public backgroundSecondary?: ResourceColor;
    public backgroundTertiary?: ResourceColor;
    public backgroundFourth?: ResourceColor;
    public backgroundEmphasize?: ResourceColor;

    public compForegroundPrimary?: ResourceColor;
    public compBackgroundPrimary?: ResourceColor;
    public compBackgroundPrimaryTran?: ResourceColor;
    public compBackgroundPrimaryContrary?: ResourceColor;
    public compBackgroundGray?: ResourceColor;
    public compBackgroundSecondary?: ResourceColor;
    public compBackgroundTertiary?: ResourceColor;
    public compBackgroundEmphasize?: ResourceColor;
    public compBackgroundNeutral?: ResourceColor;
    public compEmphasizeSecondary?: ResourceColor;
    public compEmphasizeTertiary?: ResourceColor;
    public compDivider?: ResourceColor;
    public compCommonContrary?: ResourceColor;
    public compBackgroundFocus?: ResourceColor;
    public compFocusedPrimary?: ResourceColor;
    public compFocusedSecondary?: ResourceColor;
    public compFocusedTertiary?: ResourceColor;

    public interactiveHover?: ResourceColor;
    public interactivePressed?: ResourceColor;
    public interactiveFocus?: ResourceColor;
    public interactiveActive?: ResourceColor;
    public interactiveSelect?: ResourceColor;
    public interactiveClick?: ResourceColor;

    constructor() {}
}