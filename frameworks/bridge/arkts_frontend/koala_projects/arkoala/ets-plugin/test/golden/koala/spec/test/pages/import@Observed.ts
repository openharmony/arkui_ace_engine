import { $r, $rawfile, AppStorage, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, CanvasRenderingContext2D, CustomDialogController, DataChangeListener, Environment, ForEach, GestureGroup, IDataSource, LocalStorage, LongPressGesture, PanGesture, PanGestureOptions, PersistentStorage, PinchGesture, RenderingContextSettings, RotationGesture, Scroller, SubscribedAbstractProperty, SwipeGesture, SwiperController, TabsController, TapGesture, TextAreaController, VideoController, animateTo, fp2px, getContext, getInspectorByKey, lpx2px, px2fp, px2lpx, px2vp, stateOf, vp2px } from "@koalaui/arkui";
import { MutableState } from "@koalaui/runtime";
import { observableProxy } from "@koalaui/common";
/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
var nextID: number = 0;
export class ClassB {
    private __backing_name?: MutableState<string>;
    public get name(): string {
        return this.__backing_name!.value;
    }
    public set name(value: string) {
        if (this.__backing_name)
            this.__backing_name!.value = observableProxy(value);
        else
            this.__backing_name = stateOf<string>(value);
    }
    private __backing_c?: MutableState<number>;
    public get c(): number {
        return this.__backing_c!.value;
    }
    public set c(value: number) {
        if (this.__backing_c)
            this.__backing_c!.value = observableProxy(value);
        else
            this.__backing_c = stateOf<number>(value);
    }
    private __backing_id?: MutableState<number>;
    public get id(): number {
        return this.__backing_id!.value;
    }
    public set id(value: number) {
        if (this.__backing_id)
            this.__backing_id!.value = observableProxy(value);
        else
            this.__backing_id = stateOf<number>(value);
    }
    constructor(c: number, name: string = 'OK') {
        this.name = name;
        this.c = c;
        this.id = nextID++;
    }
}
export {};
