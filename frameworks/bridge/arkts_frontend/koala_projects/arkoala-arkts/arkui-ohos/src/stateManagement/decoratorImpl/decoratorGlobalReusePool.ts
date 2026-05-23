/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { int32 } from '@koalaui/common';
import { IGlobalReusePoolVariable, ReusePoolOwnership, IVariableOwner } from '../decorator';
import { GlobalReusePool, GlobalReusePoolRegistry } from '../tools/globalReusePool';
import { DecoratedVariableBase } from './decoratorBase';
import { ExtendableComponent } from '../../component/extendableComponent';
import { WrappedBuilder, CustomBuilder } from '../../component/builder';
import { IReusableInfo } from '../utils';
/**
 * Backing variable for the framework-emitted `__backing_reusePool` field on
 * a @Component/@ComponentV2 with `reusePool` and `poolAccepts` parameters.
 *
 * Delegates every IReusePool / IGlobalReusePoolVariable call to the singleton
 * GlobalReusePool instance owned by the GlobalReusePoolRegistry. The
 * decorated-variable wrapper exists so the framework can register/unregister
 * pool ownership on the component's lifecycle.
 */
export class GlobalReusePoolDecoratedVariable extends DecoratedVariableBase implements IGlobalReusePoolVariable {
    private readonly globalPool: GlobalReusePool;
    public readonly owner: IVariableOwner;
    public readonly ownership: ReusePoolOwnership;
    public readonly acceptedClasses: Array<string>;

    constructor(ownership: ReusePoolOwnership, acceptedClasses: Array<string>, owner: IVariableOwner) {
        super('GlobalReusePool', owner as IVariableOwner | undefined, '__backing_reusePool');
        this.owner = owner;
        this.ownership = ownership;
        this.acceptedClasses = acceptedClasses;

        this.globalPool = GlobalReusePoolRegistry.create(ownership, acceptedClasses, owner);

        const ownerComp = owner as ExtendableComponent;
        ownerComp.___reusePool = this.globalPool;
        this.globalPool.addOwner(ownerComp);
    }

    // ── IGlobalReusePoolVariable ─────────────────────────────────────────────

    pop(classKey: string, reuseId?: string): Object | undefined {
        return this.globalPool.pop(classKey, reuseId);
    }

    push(classKey: string, instance: Object, reuseId?: string): boolean {
        return this.globalPool.push(classKey, instance, reuseId);
    }

    peek(classKey: string, reuseId?: string): Object | undefined {
      return this.globalPool.peek(classKey, reuseId);
    }

    acceptsComponent(classKey: string): boolean {
        return this.globalPool.acceptsComponent(classKey);
    }

    isActive(): boolean {
        return this.globalPool.isActive();
    }

    // ── IReusePool ───────────────────────────────────────────────────────

    getReusableInfo(reusableComp: Class, reuseId?: string): IReusableInfo[] | IReusableInfo | undefined {
        return this.globalPool.getReusableInfo(reusableComp, reuseId);
    }

    preRender(builder: WrappedBuilder<CustomBuilder>, n: int32): Promise<void> {
        return this.globalPool.preRender(builder, n);
    }

    // ── DecoratedVariableBase ────────────────────────────────────────────

    override aboutToBeDeletedInternal(): void {
        const ownerComp = this.owner as ExtendableComponent;
        this.globalPool.removeOwner(ownerComp);
        super.aboutToBeDeletedInternal();
    }
}