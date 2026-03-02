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

// Using Object type to avoid circular dependency with ExtendableComponent
// This allows the class to be compiled and linked without circular reference issues
import { ReuseObject, CustomComponentV2 } from './customComponent';
import { RecordData } from '@ohos.base';
import { CustomComponentLifecycle, CustomComponentLifecycleState, CustomComponentLifecycleObserver, LifeCycleEvent } from './customComponent';

/**
 * State transition table defining valid lifecycle state changes
 */
const transitionTable: Map<
    CustomComponentLifecycleState,
    Map<LifeCycleEvent, CustomComponentLifecycleState>
> = new Map<
    CustomComponentLifecycleState,
    Map<LifeCycleEvent, CustomComponentLifecycleState>
>([
    [CustomComponentLifecycleState.INIT, new Map<LifeCycleEvent, CustomComponentLifecycleState>([
        [LifeCycleEvent.ON_APPEAR, CustomComponentLifecycleState.APPEARED],
        [LifeCycleEvent.ON_DISAPPEAR, CustomComponentLifecycleState.DISAPPEARED]
    ])],
    [CustomComponentLifecycleState.APPEARED, new Map<LifeCycleEvent, CustomComponentLifecycleState>([
        [LifeCycleEvent.ON_BUILD, CustomComponentLifecycleState.BUILT]
    ])],
    [CustomComponentLifecycleState.BUILT, new Map<LifeCycleEvent, CustomComponentLifecycleState>([
        [LifeCycleEvent.ON_RECYCLE, CustomComponentLifecycleState.RECYCLED],
        [LifeCycleEvent.ON_DISAPPEAR, CustomComponentLifecycleState.DISAPPEARED]
    ])],
    [CustomComponentLifecycleState.RECYCLED, new Map<LifeCycleEvent, CustomComponentLifecycleState>([
        [LifeCycleEvent.ON_REUSE, CustomComponentLifecycleState.BUILT],
        [LifeCycleEvent.ON_DISAPPEAR, CustomComponentLifecycleState.DISAPPEARED]
    ])],
    [CustomComponentLifecycleState.DISAPPEARED, new Map<LifeCycleEvent, CustomComponentLifecycleState>()]
]);

/**
 * Lifecycle class for managing component lifecycle
 */
export class __CustomComponentLifecycle__Internal implements CustomComponentLifecycle {
    private currentState_: CustomComponentLifecycleState = CustomComponentLifecycleState.INIT;
    private owningView_: Object = {};
    private observers_: Array<CustomComponentLifecycleObserver> = new Array<CustomComponentLifecycleObserver>();

    constructor(view: Object) {
        this.owningView_ = view;
    }

    public getCurrentState(): CustomComponentLifecycleState {
        return this.currentState_;
    }

    public handleEvent(event: LifeCycleEvent, params?: ReuseObject): boolean {
        const stateTransitions = transitionTable.get(this.currentState_);
        if (!stateTransitions) {
            console.error(`Lifecycle handleEvent error, event id = ${event}, current state:${this.currentState_}.`);
            return false;
        }
        const nextState = stateTransitions.get(event);
        if (!nextState) {
            console.error(`Lifecycle handleEvent error, event id = ${event}, current state:${this.currentState_}.`);
            return false;
        }
        console.debug(`Lifecycle handleEvent, current state:${this.currentState_}, event id:${event}, nextState:${nextState}.`);
        this.currentState_ = nextState;
        this.executeHandleEvent(event, params);
        return true;
    }

    public trigger(event: LifeCycleEvent, params?: ReuseObject): boolean {
        if (this.observers_.length === 0) {
            return false;
        }
        return this.handleEvent(event, params);
    }

    private executeHandleEvent(event: LifeCycleEvent, params?: ReuseObject): void {
        if (event === LifeCycleEvent.ON_APPEAR) {
            this.executeAboutToAppear();
        } else if (event === LifeCycleEvent.ON_BUILD) {
            this.executeOnDidBuild();
        } else if (event === LifeCycleEvent.ON_RECYCLE) {
            this.executeAboutToRecycle();
        } else if (event === LifeCycleEvent.ON_REUSE) {
            this.executeAboutToReuse(params);
        } else if (event === LifeCycleEvent.ON_DISAPPEAR) {
            this.executeAboutToDisappear();
        } else {
            console.error(`Lifecycle function cannot handle this event, event id:${event}.`);
        }
    }

    /**
     * Execute @ComponentAppear decorated methods
     */
    private executeAboutToAppear(): void {
        for (const observer of this.observers_) {
            observer.aboutToAppear();
        }
    }

    /**
     * Execute @ComponentBuilt decorated methods
     */
    private executeOnDidBuild(): void {
        for (const observer of this.observers_) {
            observer.onDidBuild();
        }
    }

    /**
     * Execute @ComponentRecycle decorated methods
     */
    private executeAboutToRecycle(): void {
        for (const observer of this.observers_) {
            observer.aboutToRecycle();
        }
    }

    private executeAboutToReuse(params?: ReuseObject): void {
        for (const observer of this.observers_) {
            if (this.owningView_ instanceof CustomComponentV2) {
                observer.aboutToReuse();
            } else {
                observer.aboutToReuse(params);
            }
        }
    }

    /**
     * Execute @ComponentDisappear decorated methods
     */
    private executeAboutToDisappear(): void {
        for (const observer of this.observers_) {
            observer.aboutToDisappear();
        }
        this.observers_ = [];
    }

    /**
     * Add lifecycle observer
     */
    public addObserver(target: CustomComponentLifecycleObserver): void {
        if (!this.observers_.includes(target)) {
            this.observers_.push(target);
        }
    }

    /**
     * Remove lifecycle observer
     */
    public removeObserver(target: CustomComponentLifecycleObserver): void {
        this.observers_ = this.observers_.filter(obs => obs !== target);
    }

    /**
     * Check if has observer
     */
    public hasObserver(): boolean {
        return this.observers_.length > 0;
    }


}