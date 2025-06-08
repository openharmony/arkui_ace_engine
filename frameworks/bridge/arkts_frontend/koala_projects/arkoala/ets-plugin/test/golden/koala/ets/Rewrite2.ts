import { $r, $rawfile, AppStorage, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, CanvasRenderingContext2D, CustomDialogController, DataChangeListener, Environment, ForEach, GestureGroup, IDataSource, LocalStorage, LongPressGesture, PanGesture, PanGestureOptions, PersistentStorage, PinchGesture, RenderingContextSettings, RotationGesture, Scroller, StorageLinkState, SubscribedAbstractProperty, SwipeGesture, SwiperController, TabsController, TapGesture, TextAreaController, VideoController, animateTo, fp2px, getContext, getInspectorByKey, lpx2px, px2fp, px2lpx, px2vp, vp2px } from "@koalaui/arkui";
import { MutableState } from "@koalaui/runtime";
import { registerArkuiEntry } from "@koalaui/arkui/ohos.router";
import { observableProxy } from "@koalaui/common";
/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
export const storage = new LocalStorage();
/** @memo:stable */
class ArkLocalStorageLinkExampleComponent extends ArkStructBase<ArkLocalStorageLinkExampleComponent, LocalStorageLinkExampleOptions> {
    private _entry_local_storage_ = storage;
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: LocalStorageLinkExampleOptions): void {
        this.__backing_link = StorageLinkState<string>(this._entry_local_storage_, "storage", "Start");
    }
    private __backing_link?: MutableState<string>;
    private get link(): string {
        return this.__backing_link!.value;
    }
    private set link(value: string) {
        this.__backing_link!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: LocalStorageLinkExampleOptions) {
        ArkText(__builder, undefined, "LocalStorage entry = " + storage.get("storage"));
    }
}
/** @memo */
export function LocalStorageLinkExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: LocalStorageLinkExampleOptions): void {
    const updatedInitializers: LocalStorageLinkExampleOptions = {
        __backing_link: initializers?.__backing_link
    };
    ArkLocalStorageLinkExampleComponent._instantiate(style, () => new ArkLocalStorageLinkExampleComponent, content, updatedInitializers);
}
export interface LocalStorageLinkExampleOptions {
    __backing_link?: MutableState<string>;
    link?: string;
}
registerArkuiEntry(LocalStorageLinkExample, "Rewrite2");
export const __Entry = LocalStorageLinkExample;
