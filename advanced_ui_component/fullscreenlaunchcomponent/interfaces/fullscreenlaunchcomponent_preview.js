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
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
const hilog = requireNapi('hilog');
const abilityManager = requireNapi('app.ability.abilityManager');

export class FullScreenLaunchComponent extends ViewPU {
    constructor(j, k, l, m = -1, n = undefined, o) {
        super(j, l, m, o);
        if (typeof n === "function") {
            this.paramsGenerator_ = n;
        }
        this.content = this.doNothingBuilder;
        this.context = getContext(this);
        this.appId = "";
        this.options = undefined;
        this.__isShow = new ObservedPropertySimplePU(false, this, "isShow");
        this.setInitiallyProvidedValue(k);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(i) {
        if (i.content !== undefined) {
            this.content = i.content;
        }
        if (i.context !== undefined) {
            this.context = i.context;
        }
        if (i.appId !== undefined) {
            this.appId = i.appId;
        }
        if (i.options !== undefined) {
            this.options = i.options;
        }
        if (i.isShow !== undefined) {
            this.isShow = i.isShow;
        }
    }
    updateStateVars(h) {
    }
    purgeVariableDependenciesOnElmtId(g) {
        this.__isShow.purgeDependencyOnElmtId(g);
    }
    aboutToBeDeleted() {
        this.__isShow.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get isShow() {
        return this.__isShow.get();
    }
    set isShow(f) {
        this.__isShow.set(f);
    }
    doNothingBuilder(e = null) {
    }
    initialRender() {
        this.observeComponentCreation2((b, c) => {
            Row.create();
            Row.justifyContent(FlexAlign.Center);
            Row.onClick(() => {
                hilog.warn(0x3900, 'FullScreenLaunchComponent', 'Embedded components do not support preview.');
            });
        }, Row);
        this.content.bind(this)();
        Row.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}

export default { FullScreenLaunchComponent }