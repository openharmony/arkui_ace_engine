/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * 
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
 * 
 */

enum CustomComponentLifecycleState {
    INIT = 0,
    EXPANDING = 1,
    EXPANDED = 2,
    MOUNTED = 3,
    RECYCLED = 4,
    DELETED = 5
}

enum LifeCycleEvent {
    ON_EXPAND = 0,
    ON_EXPANDED = 1,
    ON_ATTACH = 2,
    ON_DETACH = 3,
    ON_RECYCLE = 4,
    ON_REUSE = 5,
    ON_DELETE = 6
}

// the state transition table of node lifecycle.
const transitionTable: { [key in CustomComponentLifecycleState]: { [key in LifeCycleEvent]?: CustomComponentLifecycleState } } = {
    [CustomComponentLifecycleState.INIT]: {
        [LifeCycleEvent.ON_EXPAND]: CustomComponentLifecycleState.EXPANDING,
        [LifeCycleEvent.ON_DELETE]: CustomComponentLifecycleState.DELETED  
    },
    [CustomComponentLifecycleState.EXPANDING]: {
        [LifeCycleEvent.ON_EXPANDED]: CustomComponentLifecycleState.EXPANDED
    },
    [CustomComponentLifecycleState.EXPANDED]: {
        [LifeCycleEvent.ON_ATTACH]: CustomComponentLifecycleState.MOUNTED,
        [LifeCycleEvent.ON_RECYCLE]: CustomComponentLifecycleState.RECYCLED,
        [LifeCycleEvent.ON_DELETE]: CustomComponentLifecycleState.DELETED
    },
    [CustomComponentLifecycleState.MOUNTED]: {
        [LifeCycleEvent.ON_DETACH]: CustomComponentLifecycleState.EXPANDED
    },
    [CustomComponentLifecycleState.RECYCLED]: {
        [LifeCycleEvent.ON_REUSE]: CustomComponentLifecycleState.EXPANDED,
        [LifeCycleEvent.ON_DELETE]: CustomComponentLifecycleState.DELETED
    },
    [CustomComponentLifecycleState.DELETED]: {
    }
}

// the lifecycle class of custom node.
class CustomComponentLifecycle {
    public __reusableUpdateParams__: Record<string, Object> = {};
    private currentState_: CustomComponentLifecycleState = CustomComponentLifecycleState.INIT;
    private owningView_: PUV2ViewBase;
    private observers_: Array<CustomComponentLifecycleObserver> = new Array<CustomComponentLifecycleObserver>();
    
    constructor(view: PUV2ViewBase) {
        this.owningView_ = view;
    }

    public getCurrentState(): CustomComponentLifecycleState {
        return this.currentState_;
    }

    public setParams(params: Record<string, Object>): void {
        this.__reusableUpdateParams__ = params;
    }

    public handleEvent(event: LifeCycleEvent): boolean {
        const nextState = transitionTable[this.currentState_][event];
        if (!nextState) {
            stateMgmtConsole.error(`Lifecycle handleEvent error, event id = ${event}, view id:${this.owningView_.id__()}, view name:${this.owningView_.constructor.name}, current state:${this.currentState_}.`);
            return false;
        }
        stateMgmtConsole.debug(`Lifecycle handleEvent, view id:${this.owningView_.id__()}, view name:${this.owningView_.constructor.name}, current state:${this.currentState_}, event id:${event}, nextState:${nextState}.`);
        this.executeHandleEvent(event);
        this.currentState_ = nextState;
        return true;
    }

    public executeAboutToExpand(): void {
        this.owningView_.aboutToExpand();
        for (const observer of this.observers_) {
            observer.aboutToExpand?.();
        }
    }

    public executeOnDidBuild(): void {
        for (const observer of this.observers_) {
            observer.onDidBuild?.();
        }
    }

    public executeAboutToAttach(): void {
        this.owningView_.aboutToAttach();
        for (const observer of this.observers_) {
            observer.aboutToAttach?.();
        }
    }

    public executeAboutToDetach(): void {
        this.owningView_.aboutToDetach();
        for (const observer of this.observers_) {
            observer.aboutToDetach?.();
        }
    }

    public executeAboutToReclaim(): void {
        this.owningView_.aboutToReclaim();
        for (const observer of this.observers_) {
            observer.aboutToReclaim?.();
        }
    }

    public executeAboutToRecover(): void {
        if (this.owningView_ instanceof ViewV2) {
            this.owningView_.aboutToRecover();
        } else {
            this.owningView_.aboutToRecover(this.__reusableUpdateParams__);
        }
        // aboutToRecover() is called elsewhere.
        for (const observer of this.observers_) {
            if (this.owningView_ instanceof ViewV2) {
                observer.aboutToRecover?.();
            } else {
                observer.aboutToRecover?.(this.__reusableUpdateParams__);
            }
        }
    }

    public executeAboutToDelete(): void {
        this.owningView_.aboutToDelete();
        for (const observer of this.observers_) {
            observer.aboutToDelete?.();
        }
        this.observers_.length = 0;
    }

    public executeHandleEvent(event: LifeCycleEvent): void {
        if (event === LifeCycleEvent.ON_EXPAND) {
            this.executeAboutToExpand();
        } else if (event === LifeCycleEvent.ON_EXPANDED) {
            this.executeOnDidBuild();
        }else if (event === LifeCycleEvent.ON_ATTACH) {
            this.executeAboutToAttach();
        } else if (event === LifeCycleEvent.ON_DETACH) {
            this.executeAboutToDetach();
        } else if (event === LifeCycleEvent.ON_RECYCLE) {
            this.executeAboutToReclaim();
        } else if (event === LifeCycleEvent.ON_REUSE) {
            this.executeAboutToRecover();
        } else if (event === LifeCycleEvent.ON_DELETE) {
            this.executeAboutToDelete();
        } else {
            stateMgmtConsole.error(`Lifecycle function cannot handle this event, event id:${event}.`);
        }
    }

    public addObserver(target: CustomComponentLifecycleObserver): void {
        if (!this.observers_.includes(target)) {
            this.observers_.push(target);
        }
    }

    public removeObserver(target: CustomComponentLifecycleObserver): void {
        this.observers_ = this.observers_.filter(obs => obs !== target);
    }
}

interface CustomComponentLifecycleObserver {
    aboutToExpand?(): void;

    onDidBuild?(): void;

    aboutToDelete?(): void;

    aboutToAttach?(): void;

    aboutToDetach?(): void;

    aboutToRecover?(params?: Record<string, Object>): void;

    aboutToReclaim?(): void;
}