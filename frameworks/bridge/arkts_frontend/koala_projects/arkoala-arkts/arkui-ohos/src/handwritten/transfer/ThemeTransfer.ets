/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { Colors, CustomTheme, Theme, CustomColors } from '@ohos/arkui/theme';
import { ResourceColor } from 'arkui/component/units';
import { ArkSystemColors, ArkSystemCustomColors } from 'arkui/theme/system/ArkSystemColors';
import { ResourceTransfer } from './ResourceTransfer';
import { Color } from 'arkui/component/enums';

export class ResourceColorTransfer {
    static transferStatic(input: Any): ResourceColor {
        let inputVal = ESValue.wrap(input);
        if (inputVal.isString()) {
            return inputVal.toString();
        }
        if (inputVal.isNumber()) {
            return inputVal.toNumber();
        }
        if (inputVal.isObject()) {
            return ResourceTransfer.transferStatic(input) as ResourceColor;
        }
        return '';
    }
    static transferDynamic(input: ResourceColor | undefined): ESValue {
        let inputVal = ESValue.wrap(input);
        if (input instanceof Color) {
            return ESValue.wrap(input.valueOf());
        }
        if (inputVal.isString()) {
            return inputVal;
        }
        if (inputVal.isNumber()) {
            return inputVal;
        }
        if (inputVal.isObject()) {
            return ESValue.wrap(ResourceTransfer.transferDynamic(input as Object));
        }
        return inputVal;
    }
}

export class ColorsTransfer {
    static transferStatic(input: Any): ArkSystemColors {
        let colors = new ArkSystemColors();
        let inputVal = ESValue.wrap(input);

        let brandVal = inputVal.getProperty('brand');
        if (!brandVal.isNull() && !brandVal.isUndefined()) {
            colors.brand = ResourceColorTransfer.transferStatic(brandVal.unwrap());
        }

        let warningVal = inputVal.getProperty('warning');
        if (!warningVal.isNull() && !warningVal.isUndefined()) {
            colors.warning = ResourceColorTransfer.transferStatic(warningVal.unwrap());
        }

        let alertVal = inputVal.getProperty('alert');
        if (!alertVal.isNull() && !alertVal.isUndefined()) {
            colors.alert = ResourceColorTransfer.transferStatic(alertVal.unwrap());
        }

        let confirmVal = inputVal.getProperty('confirm');
        if (!confirmVal.isNull() && !confirmVal.isUndefined()) {
            colors.confirm = ResourceColorTransfer.transferStatic(confirmVal.unwrap());
        }

        let fontPrimaryVal = inputVal.getProperty('fontPrimary');
        if (!fontPrimaryVal.isNull() && !fontPrimaryVal.isUndefined()) {
            colors.fontPrimary = ResourceColorTransfer.transferStatic(fontPrimaryVal.unwrap());
        }

        let fontSecondaryVal = inputVal.getProperty('fontSecondary');
        if (!fontSecondaryVal.isNull() && !fontSecondaryVal.isUndefined()) {
            colors.fontSecondary = ResourceColorTransfer.transferStatic(fontSecondaryVal.unwrap());
        }

        let fontTertiaryVal = inputVal.getProperty('fontTertiary');
        if (!fontTertiaryVal.isNull() && !fontTertiaryVal.isUndefined()) {
            colors.fontTertiary = ResourceColorTransfer.transferStatic(fontTertiaryVal.unwrap());
        }

        let fontFourthVal = inputVal.getProperty('fontFourth');
        if (!fontFourthVal.isNull() && !fontFourthVal.isUndefined()) {
            colors.fontFourth = ResourceColorTransfer.transferStatic(fontFourthVal.unwrap());
        }

        let fontEmphasizeVal = inputVal.getProperty('fontEmphasize');
        if (!fontEmphasizeVal.isNull() && !fontEmphasizeVal.isUndefined()) {
            colors.fontEmphasize = ResourceColorTransfer.transferStatic(fontEmphasizeVal.unwrap());
        }

        let fontOnPrimaryVal = inputVal.getProperty('fontOnPrimary');
        if (!fontOnPrimaryVal.isNull() && !fontOnPrimaryVal.isUndefined()) {
            colors.fontOnPrimary = ResourceColorTransfer.transferStatic(fontOnPrimaryVal.unwrap());
        }

        let fontOnSecondaryVal = inputVal.getProperty('fontOnSecondary');
        if (!fontOnSecondaryVal.isNull() && !fontOnSecondaryVal.isUndefined()) {
            colors.fontOnSecondary = ResourceColorTransfer.transferStatic(fontOnSecondaryVal.unwrap());
        }

        let fontOnTertiaryVal = inputVal.getProperty('fontOnTertiary');
        if (!fontOnTertiaryVal.isNull() && !fontOnTertiaryVal.isUndefined()) {
            colors.fontOnTertiary = ResourceColorTransfer.transferStatic(fontOnTertiaryVal.unwrap());
        }

        let fontOnFourthVal = inputVal.getProperty('fontOnFourth');
        if (!fontOnFourthVal.isNull() && !fontOnFourthVal.isUndefined()) {
            colors.fontOnFourth = ResourceColorTransfer.transferStatic(fontOnFourthVal.unwrap());
        }

        let iconPrimaryVal = inputVal.getProperty('iconPrimary');
        if (!iconPrimaryVal.isNull() && !iconPrimaryVal.isUndefined()) {
            colors.iconPrimary = ResourceColorTransfer.transferStatic(iconPrimaryVal.unwrap());
        }

        let iconSecondaryVal = inputVal.getProperty('iconSecondary');
        if (!iconSecondaryVal.isNull() && !iconSecondaryVal.isUndefined()) {
            colors.iconSecondary = ResourceColorTransfer.transferStatic(iconSecondaryVal.unwrap());
        }

        let iconTertiaryVal = inputVal.getProperty('iconTertiary');
        if (!iconTertiaryVal.isNull() && !iconTertiaryVal.isUndefined()) {
            colors.iconTertiary = ResourceColorTransfer.transferStatic(iconTertiaryVal.unwrap());
        }

        let iconFourthVal = inputVal.getProperty('iconFourth');
        if (!iconFourthVal.isNull() && !iconFourthVal.isUndefined()) {
            colors.iconFourth = ResourceColorTransfer.transferStatic(iconFourthVal.unwrap());
        }

        let iconEmphasizeVal = inputVal.getProperty('iconEmphasize');
        if (!iconEmphasizeVal.isNull() && !iconEmphasizeVal.isUndefined()) {
            colors.iconEmphasize = ResourceColorTransfer.transferStatic(iconEmphasizeVal.unwrap());
        }

        let iconSubEmphasizeVal = inputVal.getProperty('iconSubEmphasize');
        if (!iconSubEmphasizeVal.isNull() && !iconSubEmphasizeVal.isUndefined()) {
            colors.iconSubEmphasize = ResourceColorTransfer.transferStatic(iconSubEmphasizeVal.unwrap());
        }

        let iconOnPrimaryVal = inputVal.getProperty('iconOnPrimary');
        if (!iconOnPrimaryVal.isNull() && !iconOnPrimaryVal.isUndefined()) {
            colors.iconOnPrimary = ResourceColorTransfer.transferStatic(iconOnPrimaryVal.unwrap());
        }

        let iconOnSecondaryVal = inputVal.getProperty('iconOnSecondary');
        if (!iconOnSecondaryVal.isNull() && !iconOnSecondaryVal.isUndefined()) {
            colors.iconOnSecondary = ResourceColorTransfer.transferStatic(iconOnSecondaryVal.unwrap());
        }

        let iconOnTertiaryVal = inputVal.getProperty('iconOnTertiary');
        if (!iconOnTertiaryVal.isNull() && !iconOnTertiaryVal.isUndefined()) {
            colors.iconOnTertiary = ResourceColorTransfer.transferStatic(iconOnTertiaryVal.unwrap());
        }

        let iconOnFourthVal = inputVal.getProperty('iconOnFourth');
        if (!iconOnFourthVal.isNull() && !iconOnFourthVal.isUndefined()) {
            colors.iconOnFourth = ResourceColorTransfer.transferStatic(iconOnFourthVal.unwrap());
        }

        let backgroundPrimaryVal = inputVal.getProperty('backgroundPrimary');
        if (!backgroundPrimaryVal.isNull() && !backgroundPrimaryVal.isUndefined()) {
            colors.backgroundPrimary = ResourceColorTransfer.transferStatic(backgroundPrimaryVal.unwrap());
        }

        let backgroundSecondaryVal = inputVal.getProperty('backgroundSecondary');
        if (!backgroundSecondaryVal.isNull() && !backgroundSecondaryVal.isUndefined()) {
            colors.backgroundSecondary = ResourceColorTransfer.transferStatic(backgroundSecondaryVal.unwrap());
        }

        let backgroundTertiaryVal = inputVal.getProperty('backgroundTertiary');
        if (!backgroundTertiaryVal.isNull() && !backgroundTertiaryVal.isUndefined()) {
            colors.backgroundTertiary = ResourceColorTransfer.transferStatic(backgroundTertiaryVal.unwrap());
        }

        let backgroundFourthVal = inputVal.getProperty('backgroundFourth');
        if (!backgroundFourthVal.isNull() && !backgroundFourthVal.isUndefined()) {
            colors.backgroundFourth = ResourceColorTransfer.transferStatic(backgroundFourthVal.unwrap());
        }

        let backgroundEmphasizeVal = inputVal.getProperty('backgroundEmphasize');
        if (!backgroundEmphasizeVal.isNull() && !backgroundEmphasizeVal.isUndefined()) {
            colors.backgroundEmphasize = ResourceColorTransfer.transferStatic(backgroundEmphasizeVal.unwrap());
        }

        let compForegroundPrimaryVal = inputVal.getProperty('compForegroundPrimary');
        if (!compForegroundPrimaryVal.isNull() && !compForegroundPrimaryVal.isUndefined()) {
            colors.compForegroundPrimary = ResourceColorTransfer.transferStatic(compForegroundPrimaryVal.unwrap());
        }

        let compBackgroundPrimaryVal = inputVal.getProperty('compBackgroundPrimary');
        if (!compBackgroundPrimaryVal.isNull() && !compBackgroundPrimaryVal.isUndefined()) {
            colors.compBackgroundPrimary = ResourceColorTransfer.transferStatic(compBackgroundPrimaryVal.unwrap());
        }

        let compBackgroundPrimaryTranVal = inputVal.getProperty('compBackgroundPrimaryTran');
        if (!compBackgroundPrimaryTranVal.isNull() && !compBackgroundPrimaryTranVal.isUndefined()) {
            colors.compBackgroundPrimaryTran = ResourceColorTransfer.transferStatic(
                compBackgroundPrimaryTranVal.unwrap()
            );
        }

        let compBackgroundPrimaryContraryVal = inputVal.getProperty('compBackgroundPrimaryContrary');
        if (!compBackgroundPrimaryContraryVal.isNull() && !compBackgroundPrimaryContraryVal.isUndefined()) {
            colors.compBackgroundPrimaryContrary = ResourceColorTransfer.transferStatic(
                compBackgroundPrimaryContraryVal.unwrap()
            );
        }

        let compBackgroundGrayVal = inputVal.getProperty('compBackgroundGray');
        if (!compBackgroundGrayVal.isNull() && !compBackgroundGrayVal.isUndefined()) {
            colors.compBackgroundGray = ResourceColorTransfer.transferStatic(compBackgroundGrayVal.unwrap());
        }

        let compBackgroundSecondaryVal = inputVal.getProperty('compBackgroundSecondary');
        if (!compBackgroundSecondaryVal.isNull() && !compBackgroundSecondaryVal.isUndefined()) {
            colors.compBackgroundSecondary = ResourceColorTransfer.transferStatic(compBackgroundSecondaryVal.unwrap());
        }

        let compBackgroundTertiaryVal = inputVal.getProperty('compBackgroundTertiary');
        if (!compBackgroundTertiaryVal.isNull() && !compBackgroundTertiaryVal.isUndefined()) {
            colors.compBackgroundTertiary = ResourceColorTransfer.transferStatic(compBackgroundTertiaryVal.unwrap());
        }

        let compBackgroundEmphasizeVal = inputVal.getProperty('compBackgroundEmphasize');
        if (!compBackgroundEmphasizeVal.isNull() && !compBackgroundEmphasizeVal.isUndefined()) {
            colors.compBackgroundEmphasize = ResourceColorTransfer.transferStatic(compBackgroundEmphasizeVal.unwrap());
        }

        let compBackgroundNeutralVal = inputVal.getProperty('compBackgroundNeutral');
        if (!compBackgroundNeutralVal.isNull() && !compBackgroundNeutralVal.isUndefined()) {
            colors.compBackgroundNeutral = ResourceColorTransfer.transferStatic(compBackgroundNeutralVal.unwrap());
        }

        let compEmphasizeSecondaryVal = inputVal.getProperty('compEmphasizeSecondary');
        if (!compEmphasizeSecondaryVal.isNull() && !compEmphasizeSecondaryVal.isUndefined()) {
            colors.compEmphasizeSecondary = ResourceColorTransfer.transferStatic(compEmphasizeSecondaryVal.unwrap());
        }

        let compEmphasizeTertiaryVal = inputVal.getProperty('compEmphasizeTertiary');
        if (!compEmphasizeTertiaryVal.isNull() && !compEmphasizeTertiaryVal.isUndefined()) {
            colors.compEmphasizeTertiary = ResourceColorTransfer.transferStatic(compEmphasizeTertiaryVal.unwrap());
        }

        let compDividerVal = inputVal.getProperty('compDivider');
        if (!compDividerVal.isNull() && !compDividerVal.isUndefined()) {
            colors.compDivider = ResourceColorTransfer.transferStatic(compDividerVal.unwrap());
        }

        let compCommonContraryVal = inputVal.getProperty('compCommonContrary');
        if (!compCommonContraryVal.isNull() && !compCommonContraryVal.isUndefined()) {
            colors.compCommonContrary = ResourceColorTransfer.transferStatic(compCommonContraryVal.unwrap());
        }

        let compBackgroundFocusVal = inputVal.getProperty('compBackgroundFocus');
        if (!compBackgroundFocusVal.isNull() && !compBackgroundFocusVal.isUndefined()) {
            colors.compBackgroundFocus = ResourceColorTransfer.transferStatic(compBackgroundFocusVal.unwrap());
        }

        let compFocusedPrimaryVal = inputVal.getProperty('compFocusedPrimary');
        if (!compFocusedPrimaryVal.isNull() && !compFocusedPrimaryVal.isUndefined()) {
            colors.compFocusedPrimary = ResourceColorTransfer.transferStatic(compFocusedPrimaryVal.unwrap());
        }

        let compFocusedSecondaryVal = inputVal.getProperty('compFocusedSecondary');
        if (!compFocusedSecondaryVal.isNull() && !compFocusedSecondaryVal.isUndefined()) {
            colors.compFocusedSecondary = ResourceColorTransfer.transferStatic(compFocusedSecondaryVal.unwrap());
        }

        let compFocusedTertiaryVal = inputVal.getProperty('compFocusedTertiary');
        if (!compFocusedTertiaryVal.isNull() && !compFocusedTertiaryVal.isUndefined()) {
            colors.compFocusedTertiary = ResourceColorTransfer.transferStatic(compFocusedTertiaryVal.unwrap());
        }

        let interactiveHoverVal = inputVal.getProperty('interactiveHover');
        if (!interactiveHoverVal.isNull() && !interactiveHoverVal.isUndefined()) {
            colors.interactiveHover = ResourceColorTransfer.transferStatic(interactiveHoverVal.unwrap());
        }

        let interactivePressedVal = inputVal.getProperty('interactivePressed');
        if (!interactivePressedVal.isNull() && !interactivePressedVal.isUndefined()) {
            colors.interactivePressed = ResourceColorTransfer.transferStatic(interactivePressedVal.unwrap());
        }

        let interactiveFocusVal = inputVal.getProperty('interactiveFocus');
        if (!interactiveFocusVal.isNull() && !interactiveFocusVal.isUndefined()) {
            colors.interactiveFocus = ResourceColorTransfer.transferStatic(interactiveFocusVal.unwrap());
        }

        let interactiveActiveVal = inputVal.getProperty('interactiveActive');
        if (!interactiveActiveVal.isNull() && !interactiveActiveVal.isUndefined()) {
            colors.interactiveActive = ResourceColorTransfer.transferStatic(interactiveActiveVal.unwrap());
        }

        let interactiveSelectVal = inputVal.getProperty('interactiveSelect');
        if (!interactiveSelectVal.isNull() && !interactiveSelectVal.isUndefined()) {
            colors.interactiveSelect = ResourceColorTransfer.transferStatic(interactiveSelectVal.unwrap());
        }

        let interactiveClickVal = inputVal.getProperty('interactiveClick');
        if (!interactiveClickVal.isNull() && !interactiveClickVal.isUndefined()) {
            colors.interactiveClick = ResourceColorTransfer.transferStatic(interactiveClickVal.unwrap());
        }

        return colors;
    }

    static transferDynamic(input: Colors | undefined): Any {
        if (input === null) {
            throw Error('The Colors is null, convert fail.');
        }
        if (input === undefined) {
            throw Error('The Colors is undefined, convert fail.');
        }
        let staticValue = input as Colors;

        let dynamicValue = ESValue.instantiateEmptyObject();

        if (staticValue.brand !== undefined && staticValue.brand !== null) {
            const brand = ResourceColorTransfer.transferDynamic(staticValue.brand);
            dynamicValue.setProperty('brand', brand);
        }

        if (staticValue.warning !== undefined && staticValue.warning !== null) {
            const warning = ResourceColorTransfer.transferDynamic(staticValue.warning);
            dynamicValue.setProperty('warning', warning);
        }

        if (staticValue.alert !== undefined && staticValue.alert !== null) {
            const alert = ResourceColorTransfer.transferDynamic(staticValue.alert);
            dynamicValue.setProperty('alert', alert);
        }

        if (staticValue.confirm !== undefined && staticValue.confirm !== null) {
            const confirm = ResourceColorTransfer.transferDynamic(staticValue.confirm);
            dynamicValue.setProperty('confirm', confirm);
        }

        if (staticValue.fontPrimary !== undefined && staticValue.fontPrimary !== null) {
            const fontPrimary = ResourceColorTransfer.transferDynamic(staticValue.fontPrimary);
            dynamicValue.setProperty('fontPrimary', fontPrimary);
        }

        if (staticValue.fontSecondary !== undefined && staticValue.fontSecondary !== null) {
            const fontSecondary = ResourceColorTransfer.transferDynamic(staticValue.fontSecondary);
            dynamicValue.setProperty('fontSecondary', fontSecondary);
        }

        if (staticValue.fontTertiary !== undefined && staticValue.fontTertiary !== null) {
            const fontTertiary = ResourceColorTransfer.transferDynamic(staticValue.fontTertiary);
            dynamicValue.setProperty('fontTertiary', fontTertiary);
        }

        if (staticValue.fontFourth !== undefined && staticValue.fontFourth !== null) {
            const fontFourth = ResourceColorTransfer.transferDynamic(staticValue.fontFourth);
            dynamicValue.setProperty('fontFourth', fontFourth);
        }

        if (staticValue.fontEmphasize !== undefined && staticValue.fontEmphasize !== null) {
            const fontEmphasize = ResourceColorTransfer.transferDynamic(staticValue.fontEmphasize);
            dynamicValue.setProperty('fontEmphasize', fontEmphasize);
        }

        if (staticValue.fontOnPrimary !== undefined && staticValue.fontOnPrimary !== null) {
            const fontOnPrimary = ResourceColorTransfer.transferDynamic(staticValue.fontOnPrimary);
            dynamicValue.setProperty('fontOnPrimary', fontOnPrimary);
        }

        if (staticValue.fontOnSecondary !== undefined && staticValue.fontOnSecondary !== null) {
            const fontOnSecondary = ResourceColorTransfer.transferDynamic(staticValue.fontOnSecondary);
            dynamicValue.setProperty('fontOnSecondary', fontOnSecondary);
        }

        if (staticValue.fontOnTertiary !== undefined && staticValue.fontOnTertiary !== null) {
            const fontOnTertiary = ResourceColorTransfer.transferDynamic(staticValue.fontOnTertiary);
            dynamicValue.setProperty('fontOnTertiary', fontOnTertiary);
        }

        if (staticValue.fontOnFourth !== undefined && staticValue.fontOnFourth !== null) {
            const fontOnFourth = ResourceColorTransfer.transferDynamic(staticValue.fontOnFourth);
            dynamicValue.setProperty('fontOnFourth', fontOnFourth);
        }

        if (staticValue.iconPrimary !== undefined && staticValue.iconPrimary !== null) {
            const iconPrimary = ResourceColorTransfer.transferDynamic(staticValue.iconPrimary);
            dynamicValue.setProperty('iconPrimary', iconPrimary);
        }

        if (staticValue.iconSecondary !== undefined && staticValue.iconSecondary !== null) {
            const iconSecondary = ResourceColorTransfer.transferDynamic(staticValue.iconSecondary);
            dynamicValue.setProperty('iconSecondary', iconSecondary);
        }

        if (staticValue.iconTertiary !== undefined && staticValue.iconTertiary !== null) {
            const iconTertiary = ResourceColorTransfer.transferDynamic(staticValue.iconTertiary);
            dynamicValue.setProperty('iconTertiary', iconTertiary);
        }

        if (staticValue.iconFourth !== undefined && staticValue.iconFourth !== null) {
            const iconFourth = ResourceColorTransfer.transferDynamic(staticValue.iconFourth);
            dynamicValue.setProperty('iconFourth', iconFourth);
        }

        if (staticValue.iconEmphasize !== undefined && staticValue.iconEmphasize !== null) {
            const iconEmphasize = ResourceColorTransfer.transferDynamic(staticValue.iconEmphasize);
            dynamicValue.setProperty('iconEmphasize', iconEmphasize);
        }

        if (staticValue.iconSubEmphasize !== undefined && staticValue.iconSubEmphasize !== null) {
            const iconSubEmphasize = ResourceColorTransfer.transferDynamic(staticValue.iconSubEmphasize);
            dynamicValue.setProperty('iconSubEmphasize', iconSubEmphasize);
        }

        if (staticValue.iconOnPrimary !== undefined && staticValue.iconOnPrimary !== null) {
            const iconOnPrimary = ResourceColorTransfer.transferDynamic(staticValue.iconOnPrimary);
            dynamicValue.setProperty('iconOnPrimary', iconOnPrimary);
        }

        if (staticValue.iconOnSecondary !== undefined && staticValue.iconOnSecondary !== null) {
            const iconOnSecondary = ResourceColorTransfer.transferDynamic(staticValue.iconOnSecondary);
            dynamicValue.setProperty('iconOnSecondary', iconOnSecondary);
        }

        if (staticValue.iconOnTertiary !== undefined && staticValue.iconOnTertiary !== null) {
            const iconOnTertiary = ResourceColorTransfer.transferDynamic(staticValue.iconOnTertiary);
            dynamicValue.setProperty('iconOnTertiary', iconOnTertiary);
        }

        if (staticValue.iconOnFourth !== undefined && staticValue.iconOnFourth !== null) {
            const iconOnFourth = ResourceColorTransfer.transferDynamic(staticValue.iconOnFourth);
            dynamicValue.setProperty('iconOnFourth', iconOnFourth);
        }

        if (staticValue.backgroundPrimary !== undefined && staticValue.backgroundPrimary !== null) {
            const backgroundPrimary = ResourceColorTransfer.transferDynamic(staticValue.backgroundPrimary);
            dynamicValue.setProperty('backgroundPrimary', backgroundPrimary);
        }

        if (staticValue.backgroundSecondary !== undefined && staticValue.backgroundSecondary !== null) {
            const backgroundSecondary = ResourceColorTransfer.transferDynamic(staticValue.backgroundSecondary);
            dynamicValue.setProperty('backgroundSecondary', backgroundSecondary);
        }

        if (staticValue.backgroundTertiary !== undefined && staticValue.backgroundTertiary !== null) {
            const backgroundTertiary = ResourceColorTransfer.transferDynamic(staticValue.backgroundTertiary);
            dynamicValue.setProperty('backgroundTertiary', backgroundTertiary);
        }

        if (staticValue.backgroundFourth !== undefined && staticValue.backgroundFourth !== null) {
            const backgroundFourth = ResourceColorTransfer.transferDynamic(staticValue.backgroundFourth);
            dynamicValue.setProperty('backgroundFourth', backgroundFourth);
        }

        if (staticValue.backgroundEmphasize !== undefined && staticValue.backgroundEmphasize !== null) {
            const backgroundEmphasize = ResourceColorTransfer.transferDynamic(staticValue.backgroundEmphasize);
            dynamicValue.setProperty('backgroundEmphasize', backgroundEmphasize);
        }

        if (staticValue.compForegroundPrimary !== undefined && staticValue.compForegroundPrimary !== null) {
            const compForegroundPrimary = ResourceColorTransfer.transferDynamic(staticValue.compForegroundPrimary);
            dynamicValue.setProperty('compForegroundPrimary', compForegroundPrimary);
        }

        if (staticValue.compBackgroundPrimary !== undefined && staticValue.compBackgroundPrimary !== null) {
            const compBackgroundPrimary = ResourceColorTransfer.transferDynamic(staticValue.compBackgroundPrimary);
            dynamicValue.setProperty('compBackgroundPrimary', compBackgroundPrimary);
        }

        if (staticValue.compBackgroundPrimaryTran !== undefined && staticValue.compBackgroundPrimaryTran !== null) {
            const compBackgroundPrimaryTran = ResourceColorTransfer.transferDynamic(
                staticValue.compBackgroundPrimaryTran
            );
            dynamicValue.setProperty('compBackgroundPrimaryTran', compBackgroundPrimaryTran);
        }

        if (
            staticValue.compBackgroundPrimaryContrary !== undefined && 
            staticValue.compBackgroundPrimaryContrary !== null
        ) {
            const compBackgroundPrimaryContrary = ResourceColorTransfer.transferDynamic(
                staticValue.compBackgroundPrimaryContrary
            );
            dynamicValue.setProperty('compBackgroundPrimaryContrary', compBackgroundPrimaryContrary);
        }

        if (staticValue.compBackgroundGray !== undefined && staticValue.compBackgroundGray !== null) {
            const compBackgroundGray = ResourceColorTransfer.transferDynamic(staticValue.compBackgroundGray);
            dynamicValue.setProperty('compBackgroundGray', compBackgroundGray);
        }

        if (staticValue.compBackgroundSecondary !== undefined && staticValue.compBackgroundSecondary !== null) {
            const compBackgroundSecondary = ResourceColorTransfer.transferDynamic(staticValue.compBackgroundSecondary);
            dynamicValue.setProperty('compBackgroundSecondary', compBackgroundSecondary);
        }

        if (staticValue.compBackgroundTertiary !== undefined && staticValue.compBackgroundTertiary !== null) {
            const compBackgroundTertiary = ResourceColorTransfer.transferDynamic(staticValue.compBackgroundTertiary);
            dynamicValue.setProperty('compBackgroundTertiary', compBackgroundTertiary);
        }

        if (staticValue.compBackgroundEmphasize !== undefined && staticValue.compBackgroundEmphasize !== null) {
            const compBackgroundEmphasize = ResourceColorTransfer.transferDynamic(staticValue.compBackgroundEmphasize);
            dynamicValue.setProperty('compBackgroundEmphasize', compBackgroundEmphasize);
        }

        if (staticValue.compBackgroundNeutral !== undefined && staticValue.compBackgroundNeutral !== null) {
            const compBackgroundNeutral = ResourceColorTransfer.transferDynamic(staticValue.compBackgroundNeutral);
            dynamicValue.setProperty('compBackgroundNeutral', compBackgroundNeutral);
        }

        if (staticValue.compEmphasizeSecondary !== undefined && staticValue.compEmphasizeSecondary !== null) {
            const compEmphasizeSecondary = ResourceColorTransfer.transferDynamic(staticValue.compEmphasizeSecondary);
            dynamicValue.setProperty('compEmphasizeSecondary', compEmphasizeSecondary);
        }

        if (staticValue.compEmphasizeTertiary !== undefined && staticValue.compEmphasizeTertiary !== null) {
            const compEmphasizeTertiary = ResourceColorTransfer.transferDynamic(staticValue.compEmphasizeTertiary);
            dynamicValue.setProperty('compEmphasizeTertiary', compEmphasizeTertiary);
        }

        if (staticValue.compDivider !== undefined && staticValue.compDivider !== null) {
            const compDivider = ResourceColorTransfer.transferDynamic(staticValue.compDivider);
            dynamicValue.setProperty('compDivider', compDivider);
        }

        if (staticValue.compCommonContrary !== undefined && staticValue.compCommonContrary !== null) {
            const compCommonContrary = ResourceColorTransfer.transferDynamic(staticValue.compCommonContrary);
            dynamicValue.setProperty('compCommonContrary', compCommonContrary);
        }

        if (staticValue.compBackgroundFocus !== undefined && staticValue.compBackgroundFocus !== null) {
            const compBackgroundFocus = ResourceColorTransfer.transferDynamic(staticValue.compBackgroundFocus);
            dynamicValue.setProperty('compBackgroundFocus', compBackgroundFocus);
        }

        if (staticValue.compFocusedPrimary !== undefined && staticValue.compFocusedPrimary !== null) {
            const compFocusedPrimary = ResourceColorTransfer.transferDynamic(staticValue.compFocusedPrimary);
            dynamicValue.setProperty('compFocusedPrimary', compFocusedPrimary);
        }

        if (staticValue.compFocusedSecondary !== undefined && staticValue.compFocusedSecondary !== null) {
            const compFocusedSecondary = ResourceColorTransfer.transferDynamic(staticValue.compFocusedSecondary);
            dynamicValue.setProperty('compFocusedSecondary', compFocusedSecondary);
        }

        if (staticValue.compFocusedTertiary !== undefined && staticValue.compFocusedTertiary !== null) {
            const compFocusedTertiary = ResourceColorTransfer.transferDynamic(staticValue.compFocusedTertiary);
            dynamicValue.setProperty('compFocusedTertiary', compFocusedTertiary);
        }

        if (staticValue.interactiveHover !== undefined && staticValue.interactiveHover !== null) {
            const interactiveHover = ResourceColorTransfer.transferDynamic(staticValue.interactiveHover);
            dynamicValue.setProperty('interactiveHover', interactiveHover);
        }

        if (staticValue.interactivePressed !== undefined && staticValue.interactivePressed !== null) {
            const interactivePressed = ResourceColorTransfer.transferDynamic(staticValue.interactivePressed);
            dynamicValue.setProperty('interactivePressed', interactivePressed);
        }

        if (staticValue.interactiveFocus !== undefined && staticValue.interactiveFocus !== null) {
            const interactiveFocus = ResourceColorTransfer.transferDynamic(staticValue.interactiveFocus);
            dynamicValue.setProperty('interactiveFocus', interactiveFocus);
        }

        if (staticValue.interactiveActive !== undefined && staticValue.interactiveActive !== null) {
            const interactiveActive = ResourceColorTransfer.transferDynamic(staticValue.interactiveActive);
            dynamicValue.setProperty('interactiveActive', interactiveActive);
        }

        if (staticValue.interactiveSelect !== undefined && staticValue.interactiveSelect !== null) {
            const interactiveSelect = ResourceColorTransfer.transferDynamic(staticValue.interactiveSelect);
            dynamicValue.setProperty('interactiveSelect', interactiveSelect);
        }

        if (staticValue.interactiveClick !== undefined && staticValue.interactiveClick !== null) {
            const interactiveClick = ResourceColorTransfer.transferDynamic(staticValue.interactiveClick);
            dynamicValue.setProperty('interactiveClick', interactiveClick);
        }

        return dynamicValue.unwrap();
    }
}
export class CustomColorsTransfer {
    static transferStatic(input: Any): ArkSystemCustomColors {
        let colors = new ArkSystemCustomColors();
        let inputVal = ESValue.wrap(input);

        let brandVal = inputVal.getProperty('brand');
        if (!brandVal.isNull() && !brandVal.isUndefined()) {
            colors.brand = ResourceColorTransfer.transferStatic(brandVal.unwrap());
        }

        let warningVal = inputVal.getProperty('warning');
        if (!warningVal.isNull() && !warningVal.isUndefined()) {
            colors.warning = ResourceColorTransfer.transferStatic(warningVal.unwrap());
        }

        let alertVal = inputVal.getProperty('alert');
        if (!alertVal.isNull() && !alertVal.isUndefined()) {
            colors.alert = ResourceColorTransfer.transferStatic(alertVal.unwrap());
        }

        let confirmVal = inputVal.getProperty('confirm');
        if (!confirmVal.isNull() && !confirmVal.isUndefined()) {
            colors.confirm = ResourceColorTransfer.transferStatic(confirmVal.unwrap());
        }

        let fontPrimaryVal = inputVal.getProperty('fontPrimary');
        if (!fontPrimaryVal.isNull() && !fontPrimaryVal.isUndefined()) {
            colors.fontPrimary = ResourceColorTransfer.transferStatic(fontPrimaryVal.unwrap());
        }

        let fontSecondaryVal = inputVal.getProperty('fontSecondary');
        if (!fontSecondaryVal.isNull() && !fontSecondaryVal.isUndefined()) {
            colors.fontSecondary = ResourceColorTransfer.transferStatic(fontSecondaryVal.unwrap());
        }

        let fontTertiaryVal = inputVal.getProperty('fontTertiary');
        if (!fontTertiaryVal.isNull() && !fontTertiaryVal.isUndefined()) {
            colors.fontTertiary = ResourceColorTransfer.transferStatic(fontTertiaryVal.unwrap());
        }

        let fontFourthVal = inputVal.getProperty('fontFourth');
        if (!fontFourthVal.isNull() && !fontFourthVal.isUndefined()) {
            colors.fontFourth = ResourceColorTransfer.transferStatic(fontFourthVal.unwrap());
        }

        let fontEmphasizeVal = inputVal.getProperty('fontEmphasize');
        if (!fontEmphasizeVal.isNull() && !fontEmphasizeVal.isUndefined()) {
            colors.fontEmphasize = ResourceColorTransfer.transferStatic(fontEmphasizeVal.unwrap());
        }

        let fontOnPrimaryVal = inputVal.getProperty('fontOnPrimary');
        if (!fontOnPrimaryVal.isNull() && !fontOnPrimaryVal.isUndefined()) {
            colors.fontOnPrimary = ResourceColorTransfer.transferStatic(fontOnPrimaryVal.unwrap());
        }

        let fontOnSecondaryVal = inputVal.getProperty('fontOnSecondary');
        if (!fontOnSecondaryVal.isNull() && !fontOnSecondaryVal.isUndefined()) {
            colors.fontOnSecondary = ResourceColorTransfer.transferStatic(fontOnSecondaryVal.unwrap());
        }

        let fontOnTertiaryVal = inputVal.getProperty('fontOnTertiary');
        if (!fontOnTertiaryVal.isNull() && !fontOnTertiaryVal.isUndefined()) {
            colors.fontOnTertiary = ResourceColorTransfer.transferStatic(fontOnTertiaryVal.unwrap());
        }

        let fontOnFourthVal = inputVal.getProperty('fontOnFourth');
        if (!fontOnFourthVal.isNull() && !fontOnFourthVal.isUndefined()) {
            colors.fontOnFourth = ResourceColorTransfer.transferStatic(fontOnFourthVal.unwrap());
        }

        let iconPrimaryVal = inputVal.getProperty('iconPrimary');
        if (!iconPrimaryVal.isNull() && !iconPrimaryVal.isUndefined()) {
            colors.iconPrimary = ResourceColorTransfer.transferStatic(iconPrimaryVal.unwrap());
        }

        let iconSecondaryVal = inputVal.getProperty('iconSecondary');
        if (!iconSecondaryVal.isNull() && !iconSecondaryVal.isUndefined()) {
            colors.iconSecondary = ResourceColorTransfer.transferStatic(iconSecondaryVal.unwrap());
        }

        let iconTertiaryVal = inputVal.getProperty('iconTertiary');
        if (!iconTertiaryVal.isNull() && !iconTertiaryVal.isUndefined()) {
            colors.iconTertiary = ResourceColorTransfer.transferStatic(iconTertiaryVal.unwrap());
        }

        let iconFourthVal = inputVal.getProperty('iconFourth');
        if (!iconFourthVal.isNull() && !iconFourthVal.isUndefined()) {
            colors.iconFourth = ResourceColorTransfer.transferStatic(iconFourthVal.unwrap());
        }

        let iconEmphasizeVal = inputVal.getProperty('iconEmphasize');
        if (!iconEmphasizeVal.isNull() && !iconEmphasizeVal.isUndefined()) {
            colors.iconEmphasize = ResourceColorTransfer.transferStatic(iconEmphasizeVal.unwrap());
        }

        let iconSubEmphasizeVal = inputVal.getProperty('iconSubEmphasize');
        if (!iconSubEmphasizeVal.isNull() && !iconSubEmphasizeVal.isUndefined()) {
            colors.iconSubEmphasize = ResourceColorTransfer.transferStatic(iconSubEmphasizeVal.unwrap());
        }

        let iconOnPrimaryVal = inputVal.getProperty('iconOnPrimary');
        if (!iconOnPrimaryVal.isNull() && !iconOnPrimaryVal.isUndefined()) {
            colors.iconOnPrimary = ResourceColorTransfer.transferStatic(iconOnPrimaryVal.unwrap());
        }

        let iconOnSecondaryVal = inputVal.getProperty('iconOnSecondary');
        if (!iconOnSecondaryVal.isNull() && !iconOnSecondaryVal.isUndefined()) {
            colors.iconOnSecondary = ResourceColorTransfer.transferStatic(iconOnSecondaryVal.unwrap());
        }

        let iconOnTertiaryVal = inputVal.getProperty('iconOnTertiary');
        if (!iconOnTertiaryVal.isNull() && !iconOnTertiaryVal.isUndefined()) {
            colors.iconOnTertiary = ResourceColorTransfer.transferStatic(iconOnTertiaryVal.unwrap());
        }

        let iconOnFourthVal = inputVal.getProperty('iconOnFourth');
        if (!iconOnFourthVal.isNull() && !iconOnFourthVal.isUndefined()) {
            colors.iconOnFourth = ResourceColorTransfer.transferStatic(iconOnFourthVal.unwrap());
        }

        let backgroundPrimaryVal = inputVal.getProperty('backgroundPrimary');
        if (!backgroundPrimaryVal.isNull() && !backgroundPrimaryVal.isUndefined()) {
            colors.backgroundPrimary = ResourceColorTransfer.transferStatic(backgroundPrimaryVal.unwrap());
        }

        let backgroundSecondaryVal = inputVal.getProperty('backgroundSecondary');
        if (!backgroundSecondaryVal.isNull() && !backgroundSecondaryVal.isUndefined()) {
            colors.backgroundSecondary = ResourceColorTransfer.transferStatic(backgroundSecondaryVal.unwrap());
        }

        let backgroundTertiaryVal = inputVal.getProperty('backgroundTertiary');
        if (!backgroundTertiaryVal.isNull() && !backgroundTertiaryVal.isUndefined()) {
            colors.backgroundTertiary = ResourceColorTransfer.transferStatic(backgroundTertiaryVal.unwrap());
        }

        let backgroundFourthVal = inputVal.getProperty('backgroundFourth');
        if (!backgroundFourthVal.isNull() && !backgroundFourthVal.isUndefined()) {
            colors.backgroundFourth = ResourceColorTransfer.transferStatic(backgroundFourthVal.unwrap());
        }

        let backgroundEmphasizeVal = inputVal.getProperty('backgroundEmphasize');
        if (!backgroundEmphasizeVal.isNull() && !backgroundEmphasizeVal.isUndefined()) {
            colors.backgroundEmphasize = ResourceColorTransfer.transferStatic(backgroundEmphasizeVal.unwrap());
        }

        let compForegroundPrimaryVal = inputVal.getProperty('compForegroundPrimary');
        if (!compForegroundPrimaryVal.isNull() && !compForegroundPrimaryVal.isUndefined()) {
            colors.compForegroundPrimary = ResourceColorTransfer.transferStatic(compForegroundPrimaryVal.unwrap());
        }

        let compBackgroundPrimaryVal = inputVal.getProperty('compBackgroundPrimary');
        if (!compBackgroundPrimaryVal.isNull() && !compBackgroundPrimaryVal.isUndefined()) {
            colors.compBackgroundPrimary = ResourceColorTransfer.transferStatic(compBackgroundPrimaryVal.unwrap());
        }

        let compBackgroundPrimaryTranVal = inputVal.getProperty('compBackgroundPrimaryTran');
        if (!compBackgroundPrimaryTranVal.isNull() && !compBackgroundPrimaryTranVal.isUndefined()) {
            colors.compBackgroundPrimaryTran = ResourceColorTransfer.transferStatic(
                compBackgroundPrimaryTranVal.unwrap()
            );
        }

        let compBackgroundPrimaryContraryVal = inputVal.getProperty('compBackgroundPrimaryContrary');
        if (!compBackgroundPrimaryContraryVal.isNull() && !compBackgroundPrimaryContraryVal.isUndefined()) {
            colors.compBackgroundPrimaryContrary = ResourceColorTransfer.transferStatic(
                compBackgroundPrimaryContraryVal.unwrap()
            );
        }

        let compBackgroundGrayVal = inputVal.getProperty('compBackgroundGray');
        if (!compBackgroundGrayVal.isNull() && !compBackgroundGrayVal.isUndefined()) {
            colors.compBackgroundGray = ResourceColorTransfer.transferStatic(compBackgroundGrayVal.unwrap());
        }

        let compBackgroundSecondaryVal = inputVal.getProperty('compBackgroundSecondary');
        if (!compBackgroundSecondaryVal.isNull() && !compBackgroundSecondaryVal.isUndefined()) {
            colors.compBackgroundSecondary = ResourceColorTransfer.transferStatic(compBackgroundSecondaryVal.unwrap());
        }

        let compBackgroundTertiaryVal = inputVal.getProperty('compBackgroundTertiary');
        if (!compBackgroundTertiaryVal.isNull() && !compBackgroundTertiaryVal.isUndefined()) {
            colors.compBackgroundTertiary = ResourceColorTransfer.transferStatic(compBackgroundTertiaryVal.unwrap());
        }

        let compBackgroundEmphasizeVal = inputVal.getProperty('compBackgroundEmphasize');
        if (!compBackgroundEmphasizeVal.isNull() && !compBackgroundEmphasizeVal.isUndefined()) {
            colors.compBackgroundEmphasize = ResourceColorTransfer.transferStatic(compBackgroundEmphasizeVal.unwrap());
        }

        let compBackgroundNeutralVal = inputVal.getProperty('compBackgroundNeutral');
        if (!compBackgroundNeutralVal.isNull() && !compBackgroundNeutralVal.isUndefined()) {
            colors.compBackgroundNeutral = ResourceColorTransfer.transferStatic(compBackgroundNeutralVal.unwrap());
        }

        let compEmphasizeSecondaryVal = inputVal.getProperty('compEmphasizeSecondary');
        if (!compEmphasizeSecondaryVal.isNull() && !compEmphasizeSecondaryVal.isUndefined()) {
            colors.compEmphasizeSecondary = ResourceColorTransfer.transferStatic(compEmphasizeSecondaryVal.unwrap());
        }

        let compEmphasizeTertiaryVal = inputVal.getProperty('compEmphasizeTertiary');
        if (!compEmphasizeTertiaryVal.isNull() && !compEmphasizeTertiaryVal.isUndefined()) {
            colors.compEmphasizeTertiary = ResourceColorTransfer.transferStatic(compEmphasizeTertiaryVal.unwrap());
        }

        let compDividerVal = inputVal.getProperty('compDivider');
        if (!compDividerVal.isNull() && !compDividerVal.isUndefined()) {
            colors.compDivider = ResourceColorTransfer.transferStatic(compDividerVal.unwrap());
        }

        let compCommonContraryVal = inputVal.getProperty('compCommonContrary');
        if (!compCommonContraryVal.isNull() && !compCommonContraryVal.isUndefined()) {
            colors.compCommonContrary = ResourceColorTransfer.transferStatic(compCommonContraryVal.unwrap());
        }

        let compBackgroundFocusVal = inputVal.getProperty('compBackgroundFocus');
        if (!compBackgroundFocusVal.isNull() && !compBackgroundFocusVal.isUndefined()) {
            colors.compBackgroundFocus = ResourceColorTransfer.transferStatic(compBackgroundFocusVal.unwrap());
        }

        let compFocusedPrimaryVal = inputVal.getProperty('compFocusedPrimary');
        if (!compFocusedPrimaryVal.isNull() && !compFocusedPrimaryVal.isUndefined()) {
            colors.compFocusedPrimary = ResourceColorTransfer.transferStatic(compFocusedPrimaryVal.unwrap());
        }

        let compFocusedSecondaryVal = inputVal.getProperty('compFocusedSecondary');
        if (!compFocusedSecondaryVal.isNull() && !compFocusedSecondaryVal.isUndefined()) {
            colors.compFocusedSecondary = ResourceColorTransfer.transferStatic(compFocusedSecondaryVal.unwrap());
        }

        let compFocusedTertiaryVal = inputVal.getProperty('compFocusedTertiary');
        if (!compFocusedTertiaryVal.isNull() && !compFocusedTertiaryVal.isUndefined()) {
            colors.compFocusedTertiary = ResourceColorTransfer.transferStatic(compFocusedTertiaryVal.unwrap());
        }

        let interactiveHoverVal = inputVal.getProperty('interactiveHover');
        if (!interactiveHoverVal.isNull() && !interactiveHoverVal.isUndefined()) {
            colors.interactiveHover = ResourceColorTransfer.transferStatic(interactiveHoverVal.unwrap());
        }

        let interactivePressedVal = inputVal.getProperty('interactivePressed');
        if (!interactivePressedVal.isNull() && !interactivePressedVal.isUndefined()) {
            colors.interactivePressed = ResourceColorTransfer.transferStatic(interactivePressedVal.unwrap());
        }

        let interactiveFocusVal = inputVal.getProperty('interactiveFocus');
        if (!interactiveFocusVal.isNull() && !interactiveFocusVal.isUndefined()) {
            colors.interactiveFocus = ResourceColorTransfer.transferStatic(interactiveFocusVal.unwrap());
        }

        let interactiveActiveVal = inputVal.getProperty('interactiveActive');
        if (!interactiveActiveVal.isNull() && !interactiveActiveVal.isUndefined()) {
            colors.interactiveActive = ResourceColorTransfer.transferStatic(interactiveActiveVal.unwrap());
        }

        let interactiveSelectVal = inputVal.getProperty('interactiveSelect');
        if (!interactiveSelectVal.isNull() && !interactiveSelectVal.isUndefined()) {
            colors.interactiveSelect = ResourceColorTransfer.transferStatic(interactiveSelectVal.unwrap());
        }

        let interactiveClickVal = inputVal.getProperty('interactiveClick');
        if (!interactiveClickVal.isNull() && !interactiveClickVal.isUndefined()) {
            colors.interactiveClick = ResourceColorTransfer.transferStatic(interactiveClickVal.unwrap());
        }

        return colors;
    }

    static transferDynamic(input: CustomColors | undefined): Any {
        if (input === null) {
            throw Error('The Colors is null, convert fail.');
        }
        if (input === undefined) {
            throw Error('The Colors is undefined, convert fail.');
        }
        let staticValue = input as CustomColors;

        let dynamicValue = ESValue.instantiateEmptyObject();

        if (staticValue.brand !== undefined && staticValue.brand !== null) {
            const brand = ResourceColorTransfer.transferDynamic(staticValue.brand);
            dynamicValue.setProperty('brand', brand);
        }

        if (staticValue.warning !== undefined && staticValue.warning !== null) {
            const warning = ResourceColorTransfer.transferDynamic(staticValue.warning);
            dynamicValue.setProperty('warning', warning);
        }

        if (staticValue.alert !== undefined && staticValue.alert !== null) {
            const alert = ResourceColorTransfer.transferDynamic(staticValue.alert);
            dynamicValue.setProperty('alert', alert);
        }

        if (staticValue.confirm !== undefined && staticValue.confirm !== null) {
            const confirm = ResourceColorTransfer.transferDynamic(staticValue.confirm);
            dynamicValue.setProperty('confirm', confirm);
        }

        if (staticValue.fontPrimary !== undefined && staticValue.fontPrimary !== null) {
            const fontPrimary = ResourceColorTransfer.transferDynamic(staticValue.fontPrimary);
            dynamicValue.setProperty('fontPrimary', fontPrimary);
        }

        if (staticValue.fontSecondary !== undefined && staticValue.fontSecondary !== null) {
            const fontSecondary = ResourceColorTransfer.transferDynamic(staticValue.fontSecondary);
            dynamicValue.setProperty('fontSecondary', fontSecondary);
        }

        if (staticValue.fontTertiary !== undefined && staticValue.fontTertiary !== null) {
            const fontTertiary = ResourceColorTransfer.transferDynamic(staticValue.fontTertiary);
            dynamicValue.setProperty('fontTertiary', fontTertiary);
        }

        if (staticValue.fontFourth !== undefined && staticValue.fontFourth !== null) {
            const fontFourth = ResourceColorTransfer.transferDynamic(staticValue.fontFourth);
            dynamicValue.setProperty('fontFourth', fontFourth);
        }

        if (staticValue.fontEmphasize !== undefined && staticValue.fontEmphasize !== null) {
            const fontEmphasize = ResourceColorTransfer.transferDynamic(staticValue.fontEmphasize);
            dynamicValue.setProperty('fontEmphasize', fontEmphasize);
        }

        if (staticValue.fontOnPrimary !== undefined && staticValue.fontOnPrimary !== null) {
            const fontOnPrimary = ResourceColorTransfer.transferDynamic(staticValue.fontOnPrimary);
            dynamicValue.setProperty('fontOnPrimary', fontOnPrimary);
        }

        if (staticValue.fontOnSecondary !== undefined && staticValue.fontOnSecondary !== null) {
            const fontOnSecondary = ResourceColorTransfer.transferDynamic(staticValue.fontOnSecondary);
            dynamicValue.setProperty('fontOnSecondary', fontOnSecondary);
        }

        if (staticValue.fontOnTertiary !== undefined && staticValue.fontOnTertiary !== null) {
            const fontOnTertiary = ResourceColorTransfer.transferDynamic(staticValue.fontOnTertiary);
            dynamicValue.setProperty('fontOnTertiary', fontOnTertiary);
        }

        if (staticValue.fontOnFourth !== undefined && staticValue.fontOnFourth !== null) {
            const fontOnFourth = ResourceColorTransfer.transferDynamic(staticValue.fontOnFourth);
            dynamicValue.setProperty('fontOnFourth', fontOnFourth);
        }

        if (staticValue.iconPrimary !== undefined && staticValue.iconPrimary !== null) {
            const iconPrimary = ResourceColorTransfer.transferDynamic(staticValue.iconPrimary);
            dynamicValue.setProperty('iconPrimary', iconPrimary);
        }

        if (staticValue.iconSecondary !== undefined && staticValue.iconSecondary !== null) {
            const iconSecondary = ResourceColorTransfer.transferDynamic(staticValue.iconSecondary);
            dynamicValue.setProperty('iconSecondary', iconSecondary);
        }

        if (staticValue.iconTertiary !== undefined && staticValue.iconTertiary !== null) {
            const iconTertiary = ResourceColorTransfer.transferDynamic(staticValue.iconTertiary);
            dynamicValue.setProperty('iconTertiary', iconTertiary);
        }

        if (staticValue.iconFourth !== undefined && staticValue.iconFourth !== null) {
            const iconFourth = ResourceColorTransfer.transferDynamic(staticValue.iconFourth);
            dynamicValue.setProperty('iconFourth', iconFourth);
        }

        if (staticValue.iconEmphasize !== undefined && staticValue.iconEmphasize !== null) {
            const iconEmphasize = ResourceColorTransfer.transferDynamic(staticValue.iconEmphasize);
            dynamicValue.setProperty('iconEmphasize', iconEmphasize);
        }

        if (staticValue.iconSubEmphasize !== undefined && staticValue.iconSubEmphasize !== null) {
            const iconSubEmphasize = ResourceColorTransfer.transferDynamic(staticValue.iconSubEmphasize);
            dynamicValue.setProperty('iconSubEmphasize', iconSubEmphasize);
        }

        if (staticValue.iconOnPrimary !== undefined && staticValue.iconOnPrimary !== null) {
            const iconOnPrimary = ResourceColorTransfer.transferDynamic(staticValue.iconOnPrimary);
            dynamicValue.setProperty('iconOnPrimary', iconOnPrimary);
        }

        if (staticValue.iconOnSecondary !== undefined && staticValue.iconOnSecondary !== null) {
            const iconOnSecondary = ResourceColorTransfer.transferDynamic(staticValue.iconOnSecondary);
            dynamicValue.setProperty('iconOnSecondary', iconOnSecondary);
        }

        if (staticValue.iconOnTertiary !== undefined && staticValue.iconOnTertiary !== null) {
            const iconOnTertiary = ResourceColorTransfer.transferDynamic(staticValue.iconOnTertiary);
            dynamicValue.setProperty('iconOnTertiary', iconOnTertiary);
        }

        if (staticValue.iconOnFourth !== undefined && staticValue.iconOnFourth !== null) {
            const iconOnFourth = ResourceColorTransfer.transferDynamic(staticValue.iconOnFourth);
            dynamicValue.setProperty('iconOnFourth', iconOnFourth);
        }

        if (staticValue.backgroundPrimary !== undefined && staticValue.backgroundPrimary !== null) {
            const backgroundPrimary = ResourceColorTransfer.transferDynamic(staticValue.backgroundPrimary);
            dynamicValue.setProperty('backgroundPrimary', backgroundPrimary);
        }

        if (staticValue.backgroundSecondary !== undefined && staticValue.backgroundSecondary !== null) {
            const backgroundSecondary = ResourceColorTransfer.transferDynamic(staticValue.backgroundSecondary);
            dynamicValue.setProperty('backgroundSecondary', backgroundSecondary);
        }

        if (staticValue.backgroundTertiary !== undefined && staticValue.backgroundTertiary !== null) {
            const backgroundTertiary = ResourceColorTransfer.transferDynamic(staticValue.backgroundTertiary);
            dynamicValue.setProperty('backgroundTertiary', backgroundTertiary);
        }

        if (staticValue.backgroundFourth !== undefined && staticValue.backgroundFourth !== null) {
            const backgroundFourth = ResourceColorTransfer.transferDynamic(staticValue.backgroundFourth);
            dynamicValue.setProperty('backgroundFourth', backgroundFourth);
        }

        if (staticValue.backgroundEmphasize !== undefined && staticValue.backgroundEmphasize !== null) {
            const backgroundEmphasize = ResourceColorTransfer.transferDynamic(staticValue.backgroundEmphasize);
            dynamicValue.setProperty('backgroundEmphasize', backgroundEmphasize);
        }

        if (staticValue.compForegroundPrimary !== undefined && staticValue.compForegroundPrimary !== null) {
            const compForegroundPrimary = ResourceColorTransfer.transferDynamic(staticValue.compForegroundPrimary);
            dynamicValue.setProperty('compForegroundPrimary', compForegroundPrimary);
        }

        if (staticValue.compBackgroundPrimary !== undefined && staticValue.compBackgroundPrimary !== null) {
            const compBackgroundPrimary = ResourceColorTransfer.transferDynamic(staticValue.compBackgroundPrimary);
            dynamicValue.setProperty('compBackgroundPrimary', compBackgroundPrimary);
        }

        if (staticValue.compBackgroundPrimaryTran !== undefined && staticValue.compBackgroundPrimaryTran !== null) {
            const compBackgroundPrimaryTran = ResourceColorTransfer.transferDynamic(
                staticValue.compBackgroundPrimaryTran
            );
            dynamicValue.setProperty('compBackgroundPrimaryTran', compBackgroundPrimaryTran);
        }

        if (staticValue.compBackgroundPrimaryContrary !== undefined 
            && staticValue.compBackgroundPrimaryContrary !== null
        ) {
            const compBackgroundPrimaryContrary = ResourceColorTransfer.transferDynamic(
                staticValue.compBackgroundPrimaryContrary
            );
            dynamicValue.setProperty('compBackgroundPrimaryContrary', compBackgroundPrimaryContrary);
        }

        if (staticValue.compBackgroundGray !== undefined && staticValue.compBackgroundGray !== null) {
            const compBackgroundGray = ResourceColorTransfer.transferDynamic(staticValue.compBackgroundGray);
            dynamicValue.setProperty('compBackgroundGray', compBackgroundGray);
        }

        if (staticValue.compBackgroundSecondary !== undefined && staticValue.compBackgroundSecondary !== null) {
            const compBackgroundSecondary = ResourceColorTransfer.transferDynamic(staticValue.compBackgroundSecondary);
            dynamicValue.setProperty('compBackgroundSecondary', compBackgroundSecondary);
        }

        if (staticValue.compBackgroundTertiary !== undefined && staticValue.compBackgroundTertiary !== null) {
            const compBackgroundTertiary = ResourceColorTransfer.transferDynamic(staticValue.compBackgroundTertiary);
            dynamicValue.setProperty('compBackgroundTertiary', compBackgroundTertiary);
        }

        if (staticValue.compBackgroundEmphasize !== undefined && staticValue.compBackgroundEmphasize !== null) {
            const compBackgroundEmphasize = ResourceColorTransfer.transferDynamic(staticValue.compBackgroundEmphasize);
            dynamicValue.setProperty('compBackgroundEmphasize', compBackgroundEmphasize);
        }

        if (staticValue.compBackgroundNeutral !== undefined && staticValue.compBackgroundNeutral !== null) {
            const compBackgroundNeutral = ResourceColorTransfer.transferDynamic(staticValue.compBackgroundNeutral);
            dynamicValue.setProperty('compBackgroundNeutral', compBackgroundNeutral);
        }

        if (staticValue.compEmphasizeSecondary !== undefined && staticValue.compEmphasizeSecondary !== null) {
            const compEmphasizeSecondary = ResourceColorTransfer.transferDynamic(staticValue.compEmphasizeSecondary);
            dynamicValue.setProperty('compEmphasizeSecondary', compEmphasizeSecondary);
        }

        if (staticValue.compEmphasizeTertiary !== undefined && staticValue.compEmphasizeTertiary !== null) {
            const compEmphasizeTertiary = ResourceColorTransfer.transferDynamic(staticValue.compEmphasizeTertiary);
            dynamicValue.setProperty('compEmphasizeTertiary', compEmphasizeTertiary);
        }

        if (staticValue.compDivider !== undefined && staticValue.compDivider !== null) {
            const compDivider = ResourceColorTransfer.transferDynamic(staticValue.compDivider);
            dynamicValue.setProperty('compDivider', compDivider);
        }

        if (staticValue.compCommonContrary !== undefined && staticValue.compCommonContrary !== null) {
            const compCommonContrary = ResourceColorTransfer.transferDynamic(staticValue.compCommonContrary);
            dynamicValue.setProperty('compCommonContrary', compCommonContrary);
        }

        if (staticValue.compBackgroundFocus !== undefined && staticValue.compBackgroundFocus !== null) {
            const compBackgroundFocus = ResourceColorTransfer.transferDynamic(staticValue.compBackgroundFocus);
            dynamicValue.setProperty('compBackgroundFocus', compBackgroundFocus);
        }

        if (staticValue.compFocusedPrimary !== undefined && staticValue.compFocusedPrimary !== null) {
            const compFocusedPrimary = ResourceColorTransfer.transferDynamic(staticValue.compFocusedPrimary);
            dynamicValue.setProperty('compFocusedPrimary', compFocusedPrimary);
        }

        if (staticValue.compFocusedSecondary !== undefined && staticValue.compFocusedSecondary !== null) {
            const compFocusedSecondary = ResourceColorTransfer.transferDynamic(staticValue.compFocusedSecondary);
            dynamicValue.setProperty('compFocusedSecondary', compFocusedSecondary);
        }

        if (staticValue.compFocusedTertiary !== undefined && staticValue.compFocusedTertiary !== null) {
            const compFocusedTertiary = ResourceColorTransfer.transferDynamic(staticValue.compFocusedTertiary);
            dynamicValue.setProperty('compFocusedTertiary', compFocusedTertiary);
        }

        if (staticValue.interactiveHover !== undefined && staticValue.interactiveHover !== null) {
            const interactiveHover = ResourceColorTransfer.transferDynamic(staticValue.interactiveHover);
            dynamicValue.setProperty('interactiveHover', interactiveHover);
        }

        if (staticValue.interactivePressed !== undefined && staticValue.interactivePressed !== null) {
            const interactivePressed = ResourceColorTransfer.transferDynamic(staticValue.interactivePressed);
            dynamicValue.setProperty('interactivePressed', interactivePressed);
        }

        if (staticValue.interactiveFocus !== undefined && staticValue.interactiveFocus !== null) {
            const interactiveFocus = ResourceColorTransfer.transferDynamic(staticValue.interactiveFocus);
            dynamicValue.setProperty('interactiveFocus', interactiveFocus);
        }

        if (staticValue.interactiveActive !== undefined && staticValue.interactiveActive !== null) {
            const interactiveActive = ResourceColorTransfer.transferDynamic(staticValue.interactiveActive);
            dynamicValue.setProperty('interactiveActive', interactiveActive);
        }

        if (staticValue.interactiveSelect !== undefined && staticValue.interactiveSelect !== null) {
            const interactiveSelect = ResourceColorTransfer.transferDynamic(staticValue.interactiveSelect);
            dynamicValue.setProperty('interactiveSelect', interactiveSelect);
        }

        if (staticValue.interactiveClick !== undefined && staticValue.interactiveClick !== null) {
            const interactiveClick = ResourceColorTransfer.transferDynamic(staticValue.interactiveClick);
            dynamicValue.setProperty('interactiveClick', interactiveClick);
        }

        return dynamicValue.unwrap();
    }
}

export class ThemeTransfer {
    static transferStatic(input: Any): Theme {
        let theme = {} as Theme;
        let inputVal = ESValue.wrap(input);

        let colorsVal = inputVal.getProperty('colors');
        if (!colorsVal.isNull() && !colorsVal.isUndefined()) {
            theme.colors = ColorsTransfer.transferStatic(colorsVal.unwrap()) as ArkSystemColors;
        }

        return theme;
    }

    static transferDynamic(input: Object): Any {
        if (input === null) {
            throw Error('The Theme is null, convert fail.');
        }
        if (input === undefined) {
            throw Error('The Theme is undefined, convert fail.');
        }
        let staticValue = input as Theme;

        let dynamicValue = ESValue.instantiateEmptyObject();

        if (staticValue.colors !== undefined && staticValue.colors !== null) {
            dynamicValue.setProperty('colors', ESValue.wrap(ColorsTransfer.transferDynamic(staticValue.colors)));
        }

        return dynamicValue.unwrap();
    }
}

export class CustomThemeTransfer {
    static transferStatic(input: Any): CustomTheme {
        let theme = {} as CustomTheme;
        let inputVal = ESValue.wrap(input);

        let colorsVal = inputVal.getProperty('colors');
        if (!colorsVal.isNull() && !colorsVal.isUndefined()) {
            theme.colors = CustomColorsTransfer.transferStatic(colorsVal.unwrap()) as ArkSystemCustomColors;
        }

        return theme;
    }

    static transferDynamic(input: Object): Any {
        if (input === null) {
            throw Error('The Theme is null, convert fail.');
        }
        if (input === undefined) {
            throw Error('The Theme is undefined, convert fail.');
        }
        let staticValue = input as CustomTheme;

        let dynamicValue = ESValue.instantiateEmptyObject();

        if (staticValue.colors !== undefined && staticValue.colors !== null) {
            dynamicValue.setProperty('colors', ESValue.wrap(CustomColorsTransfer.transferDynamic(staticValue.colors)));
        }

        return dynamicValue.unwrap();
    }
}
