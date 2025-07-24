import { $r, $rawfile, AppStorage, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, CanvasRenderingContext2D, CustomDialogController, DataChangeListener, Environment, ForEach, GestureGroup, IDataSource, LocalStorage, LongPressGesture, PanGesture, PanGestureOptions, PersistentStorage, PinchGesture, RenderingContextSettings, RotationGesture, Scroller, SubscribedAbstractProperty, SwipeGesture, SwiperController, TabsController, TapGesture, TextAreaController, VideoController, animateTo, fp2px, getContext, getInspectorByKey, lpx2px, px2fp, px2lpx, px2vp, stateOf, vp2px } from "@koalaui/arkui";
import { MutableState } from "@koalaui/runtime";
import { observableProxy } from "@koalaui/common";
/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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
class Parent {
    private __backing_initialized: MutableState<number> = stateOf<number>(4);
    get initialized(): number {
        return this.__backing_initialized.value;
    }
    set initialized(value: number) {
        this.__backing_initialized.value = observableProxy(value);
    }
    private __backing_lazy?: MutableState<string>;
    get lazy(): string {
        return this.__backing_lazy!.value;
    }
    set lazy(value: string) {
        if (this.__backing_lazy)
            this.__backing_lazy!.value = observableProxy(value);
        else
            this.__backing_lazy = stateOf<string>(value);
    }
    constructor() {
        this.lazy = "set in constructor";
    }
}
class Example<T> extends Parent {
    private __backing_parent: MutableState<Parent> = stateOf<Parent>(new Parent());
    private get parent(): Parent {
        return this.__backing_parent.value;
    }
    private set parent(value: Parent) {
        this.__backing_parent.value = observableProxy(value);
    }
}
