/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
declare enum IndexerAlign {
    Left,
    Right,
    START,
    END
}
interface AlphabetIndexerOptions {
    arrayValue: Array<string>;
    selected: number;
}
interface AlphabetIndexerInterface {
    (options: AlphabetIndexerOptions): AlphabetIndexerAttribute;
}
declare type OnAlphabetIndexerSelectCallback = (index: number) => void;
declare type OnAlphabetIndexerPopupSelectCallback = (index: number) => void;
declare type OnAlphabetIndexerRequestPopupDataCallback = (index: number) => Array<string>;
declare class AlphabetIndexerAttribute extends CommonMethod<AlphabetIndexerAttribute> {
    onSelected(callback: (index: number) => void): AlphabetIndexerAttribute;
    color(value: ResourceColor): AlphabetIndexerAttribute;
    selectedColor(value: ResourceColor): AlphabetIndexerAttribute;
    popupColor(value: ResourceColor): AlphabetIndexerAttribute;
    selectedBackgroundColor(value: ResourceColor): AlphabetIndexerAttribute;
    popupBackground(value: ResourceColor): AlphabetIndexerAttribute;
    popupSelectedColor(value: ResourceColor): AlphabetIndexerAttribute;
    popupUnselectedColor(value: ResourceColor): AlphabetIndexerAttribute;
    popupItemBackgroundColor(value: ResourceColor): AlphabetIndexerAttribute;
    usingPopup(value: boolean): AlphabetIndexerAttribute;
    selectedFont(value: Font): AlphabetIndexerAttribute;
    popupFont(value: Font): AlphabetIndexerAttribute;
    popupItemFont(value: Font): AlphabetIndexerAttribute;
    itemSize(value: string | number): AlphabetIndexerAttribute;
    font(value: Font): AlphabetIndexerAttribute;
    alignStyle(value: IndexerAlign, offset?: Length): AlphabetIndexerAttribute;
    onSelect(callback: OnAlphabetIndexerSelectCallback): AlphabetIndexerAttribute;
    onRequestPopupData(callback: OnAlphabetIndexerRequestPopupDataCallback): AlphabetIndexerAttribute;
    onPopupSelect(callback: OnAlphabetIndexerPopupSelectCallback): AlphabetIndexerAttribute;
    selected(index: number): AlphabetIndexerAttribute;
    popupPosition(value: Position): AlphabetIndexerAttribute;
    autoCollapse(value: boolean): AlphabetIndexerAttribute;
    popupItemBorderRadius(value: number): AlphabetIndexerAttribute;
    itemBorderRadius(value: number): AlphabetIndexerAttribute;
    popupBackgroundBlurStyle(value: BlurStyle): AlphabetIndexerAttribute;
    popupTitleBackground(value: ResourceColor): AlphabetIndexerAttribute;
    enableHapticFeedback(value: boolean): AlphabetIndexerAttribute;
}
declare const AlphabetIndexer: AlphabetIndexerInterface;
declare const AlphabetIndexerInstance: AlphabetIndexerAttribute;
