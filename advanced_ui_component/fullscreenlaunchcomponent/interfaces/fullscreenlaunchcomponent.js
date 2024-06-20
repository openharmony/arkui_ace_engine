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
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => {
    });
}
const hilog = requireNapi('hilog');
const abilityManager = requireNapi('app.ability.abilityManager');
const commonEventManager = requireNapi('commonEventManager');

export class FullScreenLaunchComponent extends ViewPU {
    constructor(v, w, x, y = -1, z = undefined, a1) {
        super(v, x, y, a1);
        if (typeof z === "function") {
            this.paramsGenerator_ = z;
        }
        this.content = this.doNothingBuilder;
        this.context = getContext(this);
        this.appId = "";
        this.options = undefined;
        this.__isShow = new ObservedPropertySimplePU(false, this, "isShow");
        this.subscriber = null;
        this.setInitiallyProvidedValue(w);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(u) {
        if (u.content !== undefined) {
            this.content = u.content;
        }
        if (u.context !== undefined) {
            this.context = u.context;
        }
        if (u.appId !== undefined) {
            this.appId = u.appId;
        }
        if (u.options !== undefined) {
            this.options = u.options;
        }
        if (u.isShow !== undefined) {
            this.isShow = u.isShow;
        }
        if (u.subscriber !== undefined) {
            this.subscriber = u.subscriber;
        }
    }

    updateStateVars(t) {
    }

    purgeVariableDependenciesOnElmtId(s) {
        this.__isShow.purgeDependencyOnElmtId(s);
    }

    aboutToBeDeleted() {
        this.__isShow.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get isShow() {
        return this.__isShow.get();
    }

    set isShow(r) {
        this.__isShow.set(r);
    }

    aboutToAppear() {
        let r = {
            events: [commonEventManager.Support.COMMON_EVENT_DISTRIBUTED_ACCOUNT_LOGOUT],
        };
        commonEventManager.createSubscriber(r, (t, u) => {
            if (t) {
                hilog.error(0x3900, 'FullScreenLaunchComponent', 'Failed to create subscriber, err: %{public}s.', JSON.stringify(t));
                return;
            }
            if (u == null || u == undefined) {
                hilog.error(0x3900, 'FullScreenLaunchComponent', 'Failed to create subscriber, data is null.');
                return;
            }
            this.subscriber = u;
            commonEventManager.subscribe(this.subscriber, (w, x) => {
                if (w) {
                    hilog.error(0x3900, 'FullScreenLaunchComponent', 'Failed to subscribe common event, err: %{public}s.', JSON.stringify(w));
                    return;
                }
                hilog.info(0x3900, 'FullScreenLaunchComponent', 'Received account logout event.');
                this.isShow = false;
            });
        });
    }

    aboutToDisappear() {
        if (this.subscriber !== null) {
            commonEventManager.unsubscribe(this.subscriber, (s) => {
                if (s) {
                    hilog.error(0x3900, 'FullScreenLaunchComponent', 'UnsubscribeCallBack, err: %{public}s.', JSON.stringify(s));
                }
                else {
                    hilog.info(0x3900, 'FullScreenLaunchComponent', 'Unsubscribe success.');
                    this.subscriber = null;
                }
            });
        }
    }

    doNothingBuilder(q = null) {
    }

    resetOptions() {
        if (this.options?.parameters) {
            this.options.parameters['ohos.extra.param.key.showMode'] = 1;
            this.options.parameters['ability.want.params.IsNotifyOccupiedAreaChange'] = true;
            this.options.parameters['ability.want.params.IsModal'] = true;
            hilog.info(0x3900, 'FullScreenLaunchComponent', 'replaced options is %{public}s !', JSON.stringify(this.options));
        }
        else {
            this.options = {
                parameters: {
                    'ohos.extra.param.key.showMode': 1,
                    'ability.want.params.IsNotifyOccupiedAreaChange': true,
                    'ability.want.params.IsModal': true
                }
            };
        }
    }

    async checkAbility() {
        this.resetOptions();
        try {
            const p = await abilityManager.isEmbeddedOpenAllowed(this.context, this.appId);
            if (p) {
                this.isShow = true;
                hilog.info(0x3900, 'FullScreenLaunchComponent', ' EmbeddedOpen is Allowed!');
            }
            else {
                this.popUp();
            }
        }
        catch (o) {
            hilog.error(0x3900, 'FullScreenLaunchComponent', 'isEmbeddedOpenAllowed called error!%{public}s', o.message);
        }
    }

    async popUp() {
        this.isShow = false;
        try {
            const n = await this.context.openAtomicService(this.appId, this.options);
            hilog.info(0x3900, 'FullScreenLaunchComponent', '%{public}s open service success!', n.want);
        }
        catch (m) {
            hilog.error(0x3900, 'FullScreenLaunchComponent', '%{public}s open service error!', m.message);
        }
    }

    initialRender() {
        this.observeComponentCreation2((i, j) => {
            Row.create();
            Row.justifyContent(FlexAlign.Center);
            Row.onClick(() => {
                this.checkAbility();
            });
            Row.bindContentCover({ value: this.isShow, changeEvent: l => {
                this.isShow = l;
            } }, { builder: () => {
                this.uiExtensionBuilder.call(this);
            } });
        }, Row);
        this.content.bind(this)();
        Row.pop();
    }

    uiExtensionBuilder(a = null) {
        this.observeComponentCreation2((c, d) => {
            UIExtensionComponent.create({
                bundleName: `com.atomicservice.${this.appId}`,
                flags: this.options?.flags,
                parameters: this.options?.parameters
            });
            UIExtensionComponent.height('100%');
            UIExtensionComponent.width('100%');
            UIExtensionComponent.onRelease(() => {
                this.isShow = false;
            });
            UIExtensionComponent.onError(g => {
                this.isShow = false;
                hilog.error(0x3900, 'FullScreenLaunchComponent', 'call up UIExtension error!%{public}s', g.message);
                this.getUIContext().showAlertDialog({
                    message: g.message
                });
            });
        }, UIExtensionComponent);
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export default { FullScreenLaunchComponent }