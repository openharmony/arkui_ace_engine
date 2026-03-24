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

enum __CustomComponentLifecycleState__Internal {
    INIT = 0,
    APPEARED = 1,
    BUILT = 2,
    RECYCLED = 3,
    DISAPPEARED = 4
}

enum LifeCycleEvent {
    ON_APPEAR = 0,
    ON_BUILD = 1,
    ON_RECYCLE = 2,
    ON_REUSE = 3,
    ON_DISAPPEAR = 4
}

// the state transition table of node lifecycle.
const transitionTable: { [key in __CustomComponentLifecycleState__Internal]: { [key in LifeCycleEvent]?: __CustomComponentLifecycleState__Internal } } = {
    [__CustomComponentLifecycleState__Internal.INIT]: {
        [LifeCycleEvent.ON_APPEAR]: __CustomComponentLifecycleState__Internal.APPEARED,
        [LifeCycleEvent.ON_DISAPPEAR]: __CustomComponentLifecycleState__Internal.DISAPPEARED
    },
    [__CustomComponentLifecycleState__Internal.APPEARED]: {
        [LifeCycleEvent.ON_BUILD]: __CustomComponentLifecycleState__Internal.BUILT
    },
    [__CustomComponentLifecycleState__Internal.BUILT]: {
        [LifeCycleEvent.ON_RECYCLE]: __CustomComponentLifecycleState__Internal.RECYCLED,
        [LifeCycleEvent.ON_DISAPPEAR]: __CustomComponentLifecycleState__Internal.DISAPPEARED
    },
    [__CustomComponentLifecycleState__Internal.RECYCLED]: {
        [LifeCycleEvent.ON_REUSE]: __CustomComponentLifecycleState__Internal.BUILT,
        [LifeCycleEvent.ON_DISAPPEAR]: __CustomComponentLifecycleState__Internal.DISAPPEARED
    },
    [__CustomComponentLifecycleState__Internal.DISAPPEARED]: {
    }
}

// the lifecycle class of custom node.
class CustomComponentLifecycle {
    public __reusableUpdateParams__: Record<string, Object> = {};
    private currentState_: __CustomComponentLifecycleState__Internal = __CustomComponentLifecycleState__Internal.INIT;
    private owningView_: PUV2ViewBase;
    private observers_: Array<CustomComponentLifecycleObserver> = new Array<CustomComponentLifecycleObserver>();

    private readonly observerFunctionMap_: Map<string, (observer: CustomComponentLifecycleObserver) => void> = new Map([
        ['ComponentAppear', (observer: CustomComponentLifecycleObserver): void => {
            if (typeof observer.aboutToAppear === 'function') {
                observer.aboutToAppear();
            }
        }],
        ['ComponentBuilt', (observer: CustomComponentLifecycleObserver): void => {
            if (typeof observer.onDidBuild === 'function') {
                observer.onDidBuild();
            }
        }],
        ['ComponentRecycle', (observer: CustomComponentLifecycleObserver): void => {
            if (typeof observer.aboutToRecycle === 'function') {
                observer.aboutToRecycle();
            }
        }],
        ['ComponentReuse', (observer: CustomComponentLifecycleObserver): void => {
            if (typeof observer.aboutToReuse !== 'function') {
                return;
            }
            if (this.owningView_ instanceof ViewV2) {
                observer.aboutToReuse();
            }
            if (this.owningView_ instanceof ViewPU) {
                observer.aboutToReuse(this.__reusableUpdateParams__);
            }
        }],
        ['ComponentDisappear', (observer: CustomComponentLifecycleObserver): void => {
            if (typeof observer.aboutToDisappear === 'function') {
                observer.aboutToDisappear();
            }
        }],
    ]);

    constructor(view: PUV2ViewBase) {
        this.owningView_ = view;
    }

    public getCurrentState(): __CustomComponentLifecycleState__Internal {
        return this.currentState_;
    }

    public setParams(params: Record<string, Object>): void {
        this.__reusableUpdateParams__ = params;
    }

    public handleEvent(event: LifeCycleEvent): boolean {
        const nextState = transitionTable[this.currentState_][event];
        if (!nextState) {
            stateMgmtConsole.frequentError(`Lifecycle handleEvent error, event id = ${event}, view id:${this.owningView_.id__()}, view name:${this.owningView_.constructor.name}, current state:${this.currentState_}.`);
            return false;
        }
        stateMgmtConsole.debug(`Lifecycle handleEvent, view id:${this.owningView_.id__()}, view name:${this.owningView_.constructor.name}, current state:${this.currentState_}, event id:${event}, nextState:${nextState}.`);
        this.currentState_ = nextState;
        this.executeHandleEvent(event);
        return true;
    }

    public executeAboutToAppear(): void {
        let watchProp = Symbol.for('APPEAR_INTERNAL_FUNCTION' + this.owningView_.constructor.name);
        const componentAppearFunctions = this.owningView_[watchProp];
        if (componentAppearFunctions instanceof Array) {
            this.executeInternalFunction(componentAppearFunctions, 'ComponentAppear');
        }
        this.handleObserverFunction('ComponentAppear');
    }

    public executeOnDidBuild(): void {
        let watchProp = Symbol.for('BUILT_INTERNAL_FUNCTION' + this.owningView_.constructor.name);
        const componentBuiltFunctions = this.owningView_[watchProp];
        if (componentBuiltFunctions instanceof Array) {
            this.executeInternalFunction(componentBuiltFunctions, 'ComponentBuilt');
        }
        this.handleObserverFunction('ComponentBuilt');
    }

    public executeAboutToRecycle(): void {
        let watchProp = Symbol.for('RECYCLE_INTERNAL_FUNCTION' + this.owningView_.constructor.name);
        const componentRecycleFunctions = this.owningView_[watchProp];
        if (componentRecycleFunctions instanceof Array) {
            this.executeInternalFunction(componentRecycleFunctions, 'ComponentRecycle');
        }
        this.handleObserverFunction('ComponentRecycle');
    }

    public executeAboutToReuse(): void {
        let watchProp = Symbol.for('REUSE_INTERNAL_FUNCTION' + this.owningView_.constructor.name);
        const componentReuseFunctions = this.owningView_[watchProp];
        if (componentReuseFunctions instanceof Array) {
            this.executeReuseFunction(componentReuseFunctions, 'ComponentReuse');
        }
        this.handleObserverFunction('ComponentReuse');
    }

    public executeAboutToDisappear(): void {
        let watchProp = Symbol.for('DISAPPEAR_INTERNAL_FUNCTION' + this.owningView_.constructor.name);
        const componentDisappearFunctions = this.owningView_[watchProp];
        if (componentDisappearFunctions instanceof Array) {
            this.executeInternalFunction(componentDisappearFunctions, 'ComponentDisappear');
        }
        this.handleObserverFunction('ComponentDisappear');
        this.observers_.length = 0;
    }

    public executeHandleEvent(event: LifeCycleEvent): void {
        if (event === LifeCycleEvent.ON_APPEAR) {
            this.executeAboutToAppear();
        } else if (event === LifeCycleEvent.ON_BUILD) {
            this.executeOnDidBuild();
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
        if (!this.checkValidObserver(target)) {
            stateMgmtConsole.frequentApplicationError(`addObserver: invalid CustomComponentLifecycleObserver, ${this.owningView_.debugInfo__()}.`);
            return;
        }
        this.owningView_['__newLifecycleNeedWork__Internal'] = true;
        if (!this.observers_.includes(target)) {
            this.observers_.push(target);
        }
    }

    public removeObserver(target: CustomComponentLifecycleObserver): void {
        if (!this.checkValidObserver(target)) {
            stateMgmtConsole.frequentApplicationError(`removeObserver: invalid CustomComponentLifecycleObserver, ${this.owningView_.debugInfo__()}.`);
            return;
        }
        this.observers_ = this.observers_.filter(obs => obs !== target);
    }

    private checkValidObserver(target: CustomComponentLifecycleObserver): boolean {
        if (!target || typeof target !== 'object') {
            return false;
        }
        if (typeof target.aboutToAppear === 'function' ||
            typeof target.onDidBuild === 'function' ||
            typeof target.aboutToDisappear === 'function' ||
            typeof target.aboutToReuse === 'function' ||
            typeof target.aboutToRecycle === 'function') {
            return true;
        }
        return false;
    }

    private executeInternalFunction(componentFunctions: Array<Function>, executeName: string): void {
        try {
            componentFunctions.forEach((componentFunction) => {
                componentFunction.call(this.owningView_);
            });
        } catch (e) {
            stateMgmtConsole.frequentApplicationError(`Lifecycle ${executeName} error, ${this.owningView_.debugInfo__()}, ${e.message} ${e.stack}`);
            throw e;
        }
    }

    private executeReuseFunction(componentFunctions: Array<Function>, executeName: string): void {
        try {
            componentFunctions.forEach((componentFunction) => {
                if (this.owningView_ instanceof ViewV2) {
                    componentFunction.call(this.owningView_);
                }
                if (this.owningView_ instanceof ViewPU) {
                    componentFunction.call(this.owningView_, this.__reusableUpdateParams__);
                }
            });
        } catch (e) {
            stateMgmtConsole.frequentApplicationError(`Lifecycle ${executeName} error, ${this.owningView_.debugInfo__()}, ${e.message} ${e.stack}`);
            throw e;
        }
    }

    private handleObserverFunction(executeName: string): void {
        try {
            for (const observer of this.observers_) {
                this.executeObserverFunction(observer, executeName);
            }
        } catch (e) {
            stateMgmtConsole.frequentApplicationError(`CustomComponentLifecycleObserver error, ${this.owningView_.debugInfo__()}, ${e.message} ${e.stack}`);
            throw e;
        }
    }

    private executeObserverFunction(observer: CustomComponentLifecycleObserver, executeName: string): void {
        const func = this.observerFunctionMap_.get(executeName);
        if (typeof func === 'function') {
            func(observer);
        }
    }

    public toJSON(): Object {
        return {};
    }
}

interface CustomComponentLifecycleObserver {
    aboutToAppear?(): void;

    onDidBuild?(): void;

    aboutToDisappear?(): void;

    aboutToReuse?(params?: Record<string, Object>): void;

    aboutToRecycle?(): void;
}

function __componentInit__Internal(target: PUV2ViewBase, propertyName: string, descriptor: PropertyDescriptor): void {
  target['__newLifecycleNeedWork__Internal'] = true;
  const watchProp = Symbol.for('INIT_INTERNAL_FUNCTION' + target.constructor.name);
  const componentInitFunction = descriptor.value;
  if (componentInitFunction && typeof componentInitFunction === 'function') {
    if (!target[watchProp]) {
      const componentInitFunctionArray: Array<Function> = new Array<Function>();
      componentInitFunctionArray.push(componentInitFunction as Function);
      target[watchProp] = componentInitFunctionArray;
    } else {
      target[watchProp].push(componentInitFunction as Function);
    }
  }
}

function __componentAppear__Internal(target: PUV2ViewBase, propertyName: string, descriptor: PropertyDescriptor): void {
  target['__newLifecycleNeedWork__Internal'] = true;
  const watchProp = Symbol.for('APPEAR_INTERNAL_FUNCTION' + target.constructor.name);
  const componentAppearFunction = descriptor.value;
  if (componentAppearFunction && typeof componentAppearFunction === 'function') {
    if (!target[watchProp]) {
      const componentAppearFunctionArray: Array<Function> = new Array<Function>();
      componentAppearFunctionArray.push(componentAppearFunction as Function);
      target[watchProp] = componentAppearFunctionArray;
    } else {
      target[watchProp].push(componentAppearFunction as Function);
    }
  }
}

function __componentBuilt__Internal(target: PUV2ViewBase, propertyName: string, descriptor: PropertyDescriptor): void {
  target['__newLifecycleNeedWork__Internal'] = true;
  const watchProp = Symbol.for('BUILT_INTERNAL_FUNCTION' + target.constructor.name);
  const componentBuiltFunction = descriptor.value;
  if (componentBuiltFunction && typeof componentBuiltFunction === 'function') {
    if (!target[watchProp]) {
      const componentBuiltFunctionArray: Array<Function> = new Array<Function>();
      componentBuiltFunctionArray.push(componentBuiltFunction as Function);
      target[watchProp] = componentBuiltFunctionArray;
    } else {
      target[watchProp].push(componentBuiltFunction as Function);
    }
  }
}

function __componentReuse__Internal(target: PUV2ViewBase, propertyName: string, descriptor: PropertyDescriptor): void {
  target['__newLifecycleNeedWork__Internal'] = true;
  const watchProp = Symbol.for('REUSE_INTERNAL_FUNCTION' + target.constructor.name);
  const componentReuseFunction = descriptor.value;
  if (componentReuseFunction && typeof componentReuseFunction === 'function') {
    if (!target[watchProp]) {
      const componentReuseFunctionArray: Array<Function> = new Array<Function>();
      componentReuseFunctionArray.push(componentReuseFunction as Function);
      target[watchProp] = componentReuseFunctionArray;
    } else {
      target[watchProp].push(componentReuseFunction as Function);
    }
  }
}

function __componentRecycle__Internal(target: PUV2ViewBase, propertyName: string, descriptor: PropertyDescriptor): void {
  target['__newLifecycleNeedWork__Internal'] = true;
  const watchProp = Symbol.for('RECYCLE_INTERNAL_FUNCTION' + target.constructor.name);
  const componentRecycleFunction = descriptor.value;
  if (componentRecycleFunction && typeof componentRecycleFunction === 'function') {
    if (!target[watchProp]) {
      const componentRecycleFunctionArray: Array<Function> = new Array<Function>();
      componentRecycleFunctionArray.push(componentRecycleFunction as Function);
      target[watchProp] = componentRecycleFunctionArray;
    } else {
      target[watchProp].push(componentRecycleFunction as Function);
    }
  }
}

function __componentDisappear__Internal(target: PUV2ViewBase, propertyName: string, descriptor: PropertyDescriptor): void {
  target['__newLifecycleNeedWork__Internal'] = true;
  const watchProp = Symbol.for('DISAPPEAR_INTERNAL_FUNCTION' + target.constructor.name);
  const componentDisappearFunction = descriptor.value;
  if (componentDisappearFunction && typeof componentDisappearFunction === 'function') {
    if (!target[watchProp]) {
      const componentDisappearFunctionArray: Array<Function> = new Array<Function>();
      componentDisappearFunctionArray.push(componentDisappearFunction as Function);
      target[watchProp] = componentDisappearFunctionArray;
    } else {
      target[watchProp].push(componentDisappearFunction as Function);
    }
  }
}

