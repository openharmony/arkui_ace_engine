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

import { AttributeModifier } from './component/common';
import { AttributeUpdaterFlag, CommonMethodModifier } from './CommonMethodModifier';
import { ArkRefreshPeer, RefreshAttribute, RefreshStatus } from './component/refresh';

export class RefreshModifier extends CommonMethodModifier implements RefreshAttribute, AttributeModifier<RefreshAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId;
    }
    isUpdater: () => boolean = () => false;
    applyNormalAttribute(instance: RefreshAttribute): void {}
    applyPressedAttribute(instance: RefreshAttribute): void {}
    applyFocusedAttribute(instance: RefreshAttribute): void {}
    applyDisabledAttribute(instance: RefreshAttribute): void {}
    applySelectedAttribute(instance: RefreshAttribute): void {}
    _onStateChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _onStateChange_0_0value?: ((state: RefreshStatus) => void) | undefined;
    _onRefreshing_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _onRefreshing_0_0value?: (() => void) | undefined;
    _refreshOffset_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _refreshOffset_0_0value?: number | undefined;
    _pullToRefresh_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _pullToRefresh_0_0value?: boolean | undefined;
    _onOffsetChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _onOffsetChange_0_0value?: ((value0: number) => void) | undefined;
    _pullDownRatio_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _pullDownRatio_0_0value?: number | undefined;
    applyModifierPatch(peer: ArkRefreshPeer): void {
        super.applyModifierPatch(peer);
        if (this._onStateChange_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onStateChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onStateChangeAttribute(this._onStateChange_0_0value as ((state: RefreshStatus) => void) | undefined);
                    this._onStateChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onStateChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onStateChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onStateChangeAttribute(undefined as ((state: RefreshStatus) => void) | undefined);
                }
            }
        }
        if (this._onRefreshing_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onRefreshing_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onRefreshingAttribute(this._onRefreshing_0_0value as (() => void) | undefined);
                    this._onRefreshing_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onRefreshing_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onRefreshing_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onRefreshingAttribute(undefined as (() => void) | undefined);
                }
            }
        }
        if (this._refreshOffset_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._refreshOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.refreshOffsetAttribute(this._refreshOffset_0_0value as number | undefined);
                    this._refreshOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._refreshOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._refreshOffset_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.refreshOffsetAttribute(undefined as number | undefined);
                }
            }
        }
        if (this._pullToRefresh_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._pullToRefresh_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.pullToRefreshAttribute(this._pullToRefresh_0_0value as boolean | undefined);
                    this._pullToRefresh_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._pullToRefresh_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._pullToRefresh_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.pullToRefreshAttribute(undefined as boolean | undefined);
                }
            }
        }
        if (this._onOffsetChange_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onOffsetChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onOffsetChangeAttribute(this._onOffsetChange_0_0value as ((value0: number) => void) | undefined);
                    this._onOffsetChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onOffsetChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onOffsetChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onOffsetChangeAttribute(undefined as ((value0: number) => void) | undefined);
                }
            }
        }
        if (this._pullDownRatio_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._pullDownRatio_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.pullDownRatioAttribute(this._pullDownRatio_0_0value as number | undefined);
                    this._pullDownRatio_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._pullDownRatio_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._pullDownRatio_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.pullDownRatioAttribute(undefined as number | undefined);
                }
            }
        }
    }
    mergeModifier(modifier: RefreshModifier): void {
        super.mergeModifier(modifier);
        if (modifier._onStateChange_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onStateChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onStateChange(modifier._onStateChange_0_0value);
                    break;
                }
                default: {
                    this.onStateChange(undefined as ((state: RefreshStatus) => void) | undefined);
                }
            }
        }
        if (modifier._onRefreshing_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onRefreshing_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onRefreshing(modifier._onRefreshing_0_0value);
                    break;
                }
                default: {
                    this.onRefreshing(undefined as (() => void) | undefined);
                }
            }
        }
        if (modifier._refreshOffset_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._refreshOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.refreshOffset(modifier._refreshOffset_0_0value);
                    break;
                }
                default: {
                    this.refreshOffset(undefined as number | undefined);
                }
            }
        }
        if (modifier._pullToRefresh_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._pullToRefresh_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.pullToRefresh(modifier._pullToRefresh_0_0value);
                    break;
                }
                default: {
                    this.pullToRefresh(undefined as boolean | undefined);
                }
            }
        }
        if (modifier._onOffsetChange_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onOffsetChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onOffsetChange(modifier._onOffsetChange_0_0value);
                    break;
                }
                default: {
                    this.onOffsetChange(undefined as ((value0: number) => void) | undefined);
                }
            }
        }
        if (modifier._pullDownRatio_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._pullDownRatio_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.pullDownRatio(modifier._pullDownRatio_0_0value);
                    break;
                }
                default: {
                    this.pullDownRatio(undefined as number | undefined);
                }
            }
        }
    }
    onStateChange(value: ((state: RefreshStatus) => void) | undefined): this {
        if (this._onStateChange_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._onStateChange_0_flag = AttributeUpdaterFlag.UPDATE;
            this._onStateChange_0_0value = value;
        } else {
            this._onStateChange_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    onRefreshing(value: (() => void) | undefined): this {
        if (this._onRefreshing_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._onRefreshing_0_flag = AttributeUpdaterFlag.UPDATE;
            this._onRefreshing_0_0value = value;
        } else {
            this._onRefreshing_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    refreshOffset(value: number | undefined): this {
        if (this._refreshOffset_0_flag == AttributeUpdaterFlag.INITIAL || this._refreshOffset_0_0value !== value) {
            this._refreshOffset_0_flag = AttributeUpdaterFlag.UPDATE;
            this._refreshOffset_0_0value = value;
        } else {
            this._refreshOffset_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    pullToRefresh(value: boolean | undefined): this {
        if (this._pullToRefresh_0_flag == AttributeUpdaterFlag.INITIAL || this._pullToRefresh_0_0value !== value) {
            this._pullToRefresh_0_flag = AttributeUpdaterFlag.UPDATE;
            this._pullToRefresh_0_0value = value;
        } else {
            this._pullToRefresh_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    onOffsetChange(value: ((value0: number) => void) | undefined): this {
        if (this._onOffsetChange_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._onOffsetChange_0_flag = AttributeUpdaterFlag.UPDATE;
            this._onOffsetChange_0_0value = value;
        } else {
            this._onOffsetChange_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    pullDownRatio(value: number | undefined): this {
        if (this._pullDownRatio_0_flag == AttributeUpdaterFlag.INITIAL || this._pullDownRatio_0_0value !== value) {
            this._pullDownRatio_0_flag = AttributeUpdaterFlag.UPDATE;
            this._pullDownRatio_0_0value = value;
        } else {
            this._pullDownRatio_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
}
