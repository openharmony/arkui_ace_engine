/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

/**
 * Class is used to keep built-in components whitelist for Theme application
 */
class ArkThemeWhiteList {
    // add to list only names of built-in components which support ArkTheme
    // strongly recommended to use alphabetical order
    private static whiteList: Array<string> = [
        'AlphabetIndexer',
        'Badge',
        'Button',
        'Checkbox',
        'CheckboxGroup',
        'Counter',
        'DataPanel',
        'DatePicker',
        'LoadingProgress',
        'Menu',
        'MenuItem',
        'PatternLock',
        'Progress',
        'QRCode',
        'Radio',
        'Scroll',
        'Search',
        'Select',
        'Slider',
        'Swiper',
        'Text',
        'TextClock',
        'TextInput',
        'TextPicker',
        'TimePicker',
        'Toggle',
    ];

    /**
     * Check whether component is in whitelist
     *
     * @param componentName original component name
     * @returns true if the component is in whitelist, otherwise false
     */
    static isInWhiteList(componentName: string): boolean {
        let start = 0;
        let end = ArkThemeWhiteList.whiteList.length - 1;
        while (start <= end) {
            let mid = (start + end) >> 1;
            if (ArkThemeWhiteList.whiteList[mid].localeCompare(componentName) === 0) {
                return true;
            }
            if (ArkThemeWhiteList.whiteList[mid].localeCompare(componentName) === 1) {
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        }
        return false;
    }
}

