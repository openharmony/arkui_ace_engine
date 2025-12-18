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
    APPEARED = 1,
    BUILT = 2,
    MOUNTED = 3,
    RECYCLED = 4,
    DISAPPEARED = 5
}

enum LifeCycleEvent {
    ON_APPEAR = 0,
    ON_BUILD = 1,
    ON_ATTACH = 2,
    ON_DETACH = 3,
    ON_RECYCLE = 4,
    ON_REUSE = 5,
    ON_DISAPPEAR = 6
}

// the state transition table of node lifecycle.
const transitionTable: { [key in CustomComponentLifecycleState]: { [key in LifeCycleEvent]?: CustomComponentLifecycleState } } = {
    [CustomComponentLifecycleState.INIT]: {
        [LifeCycleEvent.ON_APPEAR]: CustomComponentLifecycleState.APPEARED,
        [LifeCycleEvent.ON_DISAPPEAR]: CustomComponentLifecycleState.DISAPPEARED  
    },
    [CustomComponentLifecycleState.APPEARED]: {
        [LifeCycleEvent.ON_BUILD]: CustomComponentLifecycleState.BUILT
    },
    [CustomComponentLifecycleState.BUILT]: {
        [LifeCycleEvent.ON_ATTACH]: CustomComponentLifecycleState.MOUNTED,
        [LifeCycleEvent.ON_RECYCLE]: CustomComponentLifecycleState.RECYCLED,
        [LifeCycleEvent.ON_DISAPPEAR]: CustomComponentLifecycleState.DISAPPEARED
    },
    [CustomComponentLifecycleState.MOUNTED]: {
        [LifeCycleEvent.ON_DETACH]: CustomComponentLifecycleState.BUILT
    },
    [CustomComponentLifecycleState.RECYCLED]: {
        [LifeCycleEvent.ON_REUSE]: CustomComponentLifecycleState.BUILT,
        [LifeCycleEvent.ON_DISAPPEAR]: CustomComponentLifecycleState.DISAPPEARED
    },
    [CustomComponentLifecycleState.DISAPPEARED]: {
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

    public executeAboutToAppear(): void {
        let watchProp = Symbol.for('APPEAR_INTERNAL_FUNCTION' + this.owningView_.constructor.name);
        const componentAppearFunctions = this.owningView_[watchProp];
        if (componentAppearFunctions instanceof Array) {
            componentAppearFunctions.forEach((componentAppearFunction) => {
                componentAppearFunction.call(this.owningView_);
            })
        }
        for (const observer of this.observers_) {
            observer.aboutToAppear?.();
        }
    }

    public executeOnDidBuild(): void {
        let watchProp = Symbol.for('BUILT_INTERNAL_FUNCTION' + this.owningView_.constructor.name);
        const componentBuiltFunctions = this.owningView_[watchProp];
        if (componentBuiltFunctions instanceof Array) {
            componentBuiltFunctions.forEach((componentBuiltFunction) => {
                componentBuiltFunction.call(this.owningView_);
            })
        }
        for (const observer of this.observers_) {
            observer.onDidBuild?.();
        }
    }

    public executeAboutToAttach(): void {
        let watchProp = Symbol.for('ATTACH_INTERNAL_FUNCTION' + this.owningView_.constructor.name);
        const componentAttachFunctions = this.owningView_[watchProp];
        if (componentAttachFunctions instanceof Array) {
            componentAttachFunctions.forEach((componentAttachFunction) => {
                componentAttachFunction.call(this.owningView_);
            })
        }
        for (const observer of this.observers_) {
            observer.aboutToAttach?.();
        }
    }

    public executeAboutToDetach(): void {
        let watchProp = Symbol.for('DETACH_INTERNAL_FUNCTION' + this.owningView_.constructor.name);
        const componentDetachFunctions = this.owningView_[watchProp];
        if (componentDetachFunctions instanceof Array) {
            componentDetachFunctions.forEach((componentDetachFunction) => {
                componentDetachFunction.call(this.owningView_);
            })
        }
        for (const observer of this.observers_) {
            observer.aboutToDetach?.();
        }
    }

    public executeAboutToRecycle(): void {
        let watchProp = Symbol.for('RECYCLE_INTERNAL_FUNCTION' + this.owningView_.constructor.name);
        const componentRecycleFunctions = this.owningView_[watchProp];
        if (componentRecycleFunctions instanceof Array) {
            componentRecycleFunctions.forEach((componentRecycleFunction) => {
                componentRecycleFunction.call(this.owningView_);
            })
        }
        for (const observer of this.observers_) {
            observer.aboutToRecycle?.();
        }
    }

    public executeAboutToReuse(): void {
        let watchProp = Symbol.for('REUSE_INTERNAL_FUNCTION' + this.owningView_.constructor.name);
        const componentReuseFunctions = this.owningView_[watchProp];
        if (componentReuseFunctions instanceof Array) {
            componentReuseFunctions.forEach((componentReuseFunction) => {
                if (this.owningView_ instanceof ViewV2) {
                    componentReuseFunction.call(this.owningView_);
                } else {
                    componentReuseFunction.call(this.owningView_, this.__reusableUpdateParams__);
                }
            })
        }
        for (const observer of this.observers_) {
            if (this.owningView_ instanceof ViewV2) {
                observer.aboutToReuse?.();
            } else {
                observer.aboutToReuse?.(this.__reusableUpdateParams__);
            }
        }
    }

    public executeAboutToDisappear(): void {
        let watchProp = Symbol.for('DISAPPEAR_INTERNAL_FUNCTION' + this.owningView_.constructor.name);
        const componentDisappearFunctions = this.owningView_[watchProp];
        if (componentDisappearFunctions instanceof Array) {
            componentDisappearFunctions.forEach((componentDisappearFunction) => {
                componentDisappearFunction.call(this.owningView_);
            })
        }
        for (const observer of this.observers_) {
            observer.aboutToDisappear?.();
        }
        this.observers_.length = 0;
    }

    public executeHandleEvent(event: LifeCycleEvent): void {
        if (event === LifeCycleEvent.ON_APPEAR) {
            this.executeAboutToAppear();
        } else if (event === LifeCycleEvent.ON_BUILD) {
            this.executeOnDidBuild();
        }else if (event === LifeCycleEvent.ON_ATTACH) {
            this.executeAboutToAttach();
        } else if (event === LifeCycleEvent.ON_DETACH) {
            this.executeAboutToDetach();
        } else if (event === LifeCycleEvent.ON_RECYCLE) {
            this.executeAboutToRecycle();
        } else if (event === LifeCycleEvent.ON_REUSE) {
            this.executeAboutToReuse();
        } else if (event === LifeCycleEvent.ON_DISAPPEAR) {
            this.executeAboutToDisappear();
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
    aboutToAppear?(): void;

    onDidBuild?(): void;

    aboutToDisappear?(): void;

    aboutToAttach?(): void;

    aboutToDetach?(): void;

    aboutToReuse?(params?: Record<string, Object>): void;

    aboutToRecycle?(): void;
}