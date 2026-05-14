/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

// Common UI-plugin-style mock classes shared by multiple test files.
// Each class mirrors the boilerplate the UI plugin would generate for the
// equivalent decorated class in source.

import {
    ILocalDecoratedVariable,
    IMutableStateMeta,
    IObservedAnyProp,
    IObservedObject,
    ISubscribedWatches,
    IWatchSubscriberRegister,
    RenderIdType,
    WatchIdType,
} from '../decorator';
import { STATE_MGMT_FACTORY } from '../decorator';
import { ExtendableComponent } from '../mock/extendableComponent';

const StateMgmtFactory = STATE_MGMT_FACTORY;

/*
    Source form (UI plugin would expand):

    class ClassWithDate {
        @Local dt: Date = new Date(2020, 0, 15);
    }
*/
export class ClassWithDate extends ExtendableComponent implements IObservedAnyProp {
    private _backing_dt: ILocalDecoratedVariable<Date>;

    // Per-property meta paired with the @Local backing. Fired on every dt
    // assignment in addition to the @Local backing's own meta, so wildcard
    // monitors that bind via addRefAnyProp pick up assignments.
    private readonly __meta_dt: IMutableStateMeta = StateMgmtFactory.makeMutableStateMeta();

    get dt(): Date {
        return this._backing_dt!.get() as Date;
    }
    set dt(newValue: Date) {
        this._backing_dt!.set(newValue);
        this.__meta_dt.fireChange();
    }

    // IObservedAnyProp — let wildcard monitors whose lambda returns `this`
    // bind to every observable surface on the class. addRef the per-property
    // meta directly so the binding is independent of how the @Local backing
    // chooses to expose its own meta.
    public addRefAnyProp(): void {
        this.__meta_dt.addRef();
    }

    constructor(parent: ExtendableComponent | null = null, initial?: Date) {
        super(parent);
        this._backing_dt = StateMgmtFactory.makeLocal<Date>(
            this,
            'dt',
            initial ?? new Date(2020, 0, 15)
        );
    }
}

/*
    Source form (UI plugin would expand):

    class ClassWithMapSet {
        @Local set: Set<number> = new Set<number>();
        @Local map: Map<string, number> = new Map<string, number>();
    }

    Implements the same interface set as ClassB_ObserveAnyProp
    (IObservedObject + IWatchSubscriberRegister + IObservedAnyProp) on top
    of ExtendableComponent so @Local works. Each @Local property is paired
    with an explicit __meta_<name> meta that the setter fires alongside
    the @Local backing's own meta — wildcard monitors that bind via
    addRefAnyProp pick up reassignments through that paired meta. Inner-
    container mutations (m.set, s.add, …) still fire the WrappedMap /
    WrappedSet keyed metas as usual; the wildcard's addRefAnyKey path
    binds to those when the lambda returns the wrapped container.
*/
export class ClassWithMapSet extends ExtendableComponent
    implements IObservedObject, IWatchSubscriberRegister, IObservedAnyProp
{
    // @Watch infrastructure
    private readonly subscribedWatches_: ISubscribedWatches = StateMgmtFactory.makeSubscribedWatches();
    public addWatchSubscriber(watchId: WatchIdType): void {
        this.subscribedWatches_.addWatchSubscriber(watchId);
    }
    public removeWatchSubscriber(watchId: WatchIdType): boolean {
        return this.subscribedWatches_.removeWatchSubscriber(watchId);
    }
    protected executeOnSubscribingWatches(changedPropName: string): void {
        this.subscribedWatches_.executeOnSubscribingWatches(changedPropName);
    }

    // IObservedObject
    private ____V1RenderId: RenderIdType = 0;
    public setV1RenderId(renderId: RenderIdType): void {
        this.____V1RenderId = renderId;
    }

    // @Local set: Set<number> = new Set<number>();
    private _backing_set: ILocalDecoratedVariable<Set<number>>;
    private readonly __meta_set: IMutableStateMeta = StateMgmtFactory.makeMutableStateMeta();
    get set(): Set<number> {
        return this._backing_set!.get();
    }
    set set(newValue: Set<number>) {
        this._backing_set!.set(newValue);
        this.__meta_set.fireChange();
        this.executeOnSubscribingWatches('set');
    }

    // @Local map: Map<string, number> = new Map<string, number>();
    private _backing_map: ILocalDecoratedVariable<Map<string, number>>;
    private readonly __meta_map: IMutableStateMeta = StateMgmtFactory.makeMutableStateMeta();
    get map(): Map<string, number> {
        return this._backing_map!.get();
    }
    set map(newValue: Map<string, number>) {
        this._backing_map!.set(newValue);
        this.__meta_map.fireChange();
        this.executeOnSubscribingWatches('map');
    }

    // IObservedAnyProp — wildcard monitors whose lambda returns `this`
    // bind to every observable surface on the class.
    public addRefAnyProp(): void {
        this.__meta_set.addRef();
        this.__meta_map.addRef();
    }

    constructor(
        parent: ExtendableComponent | null = null,
        initialSet?: Set<number>,
        initialMap?: Map<string, number>,
    ) {
        super(parent);
        this._backing_set = StateMgmtFactory.makeLocal<Set<number>>(
            this,
            'set',
            initialSet ?? new Set<number>(),
        );
        this._backing_map = StateMgmtFactory.makeLocal<Map<string, number>>(
            this,
            'map',
            initialMap ?? new Map<string, number>(),
        );
    }
}
