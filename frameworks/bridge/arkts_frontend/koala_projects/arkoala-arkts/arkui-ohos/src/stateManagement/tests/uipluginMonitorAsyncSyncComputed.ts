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

// Monitor-on-@Computed coverage parameterized by `isSync`. Two scenarios:
//   1. ChainedComputedComponent: @Computed kelvin reads @Computed fahrenheit
//      reads @Local celcius. A monitor on `kelvin` should fire when celcius
//      changes.
//   2. ClassPerson: a monitor on `person.fullName` (itself a @Computed of
//      firstName + lastName). Source writes propagate through the @Computed
//      to the monitor.
//
// NOTE on SyncMonitors and @Computed:
//
// A sync monitor's callback fires inside fireChange ONLY for direct deps it
// has bound during a previous lambda evaluation. When the lambda reads a
// @Computed (e.g. `() => person.fullName`), the sync monitor binds to the
// @Computed's meta — NOT to the @Computed's own source deps (firstName,
// lastName, celcius). A direct write to a source therefore does not fire
// the sync monitor inside fireChange; the @Computed has to be recomputed
// first to forward the dirty signal to the @Computed's meta.
//
// Recomputation happens during ObserveSingleton.instance.updateDirty(), so
// these tests call updateDirty() after every mutation — even in sync mode.
// In sync mode the monitor callback then fires inside the @Computed's
// recomputation cycle (still synchronously, but staged after the drain
// rather than inside the source's fireChange).

import { tsuite, tcase, test, eq } from './lib/testFramework'
import {
    IComputedDecoratedVariable,
    ILocalDecoratedVariable,
    IMonitor,
    IMonitorDecoratedVariable,
    IMonitorPathInfo,
    IMutableStateMeta,
    IObservedObject,
    ISubscribedWatches,
    IWatchSubscriberRegister,
    MonitorCallback,
    RenderIdType,
    WatchIdType,
} from '../decorator'
import { ExtendableComponent } from '../mock/extendableComponent';
import { ObserveSingleton } from '../base/observeSingleton';
import { STATE_MGMT_FACTORY } from '../decorator'

const StateMgmtFactory = STATE_MGMT_FACTORY;
const stateMgmtConsole = console;

// === Test infra ============================================================

const testMonitors_: Array<IMonitorDecoratedVariable> = new Array<IMonitorDecoratedVariable>();

function makeMonitorByMode(
    isSync: boolean,
    pathInfos: IMonitorPathInfo[],
    onChanged: MonitorCallback,
): IMonitorDecoratedVariable {
    const m = isSync
        ? STATE_MGMT_FACTORY.makeSyncMonitor(pathInfos, onChanged, undefined)
        : STATE_MGMT_FACTORY.makeMonitor(pathInfos, onChanged);
    testMonitors_.push(m);
    return m;
}

// === ChainedComputedComponent =============================================

interface ChainedComputedComponent_init_update_struct {
    celcius?: number;
}

// Component with: @Local celcius → @Computed fahrenheit → @Computed kelvin.
// The monitor is wired in the constructor; isSync chooses the factory.
class ChainedComputedComponent extends ExtendableComponent {
    private _backing_celcius: ILocalDecoratedVariable<number>;
    private _computed_fahrenheit: IComputedDecoratedVariable<number>;
    private _computed_kelvin: IComputedDecoratedVariable<number>;

    public monitorFunctionRunCount: number = 0;
    private _monitor: IMonitorDecoratedVariable | undefined = undefined;
    public _monitorFunction?: (m: IMonitor) => void;

    get celcius(): number { return this._backing_celcius!.get(); }
    set celcius(newValue: number) { this._backing_celcius!.set(newValue); }
    get kelvin(): number { return this._computed_kelvin.get(); }
    get fahrenheit(): number { return this._computed_fahrenheit.get(); }

    constructor(
        parent: ExtendableComponent | null,
        param: ChainedComputedComponent_init_update_struct,
        isSync: boolean,
    ) {
        super(parent);
        this._backing_celcius = StateMgmtFactory.makeLocal<number>(
            this, 'celcius', param.celcius !== undefined ? param.celcius! : 3
        );
        this._computed_fahrenheit = StateMgmtFactory.makeComputed<number>(
            (): number => {
                stateMgmtConsole.log('computing fahrenheit');
                return this.celcius * 9 / 5 + 32;
            },
            'fahrenheit',
        );
        this._computed_kelvin = StateMgmtFactory.makeComputed<number>(
            (): number => {
                stateMgmtConsole.log('computing kelvin');
                return (this.fahrenheit - 32) * 5 / 9 + 273.15;
            },
            'Kelvin',
        );

        this._monitor = makeMonitorByMode(
            isSync,
            [{
                path: 'kelvin',
                valueCallback: () => this.kelvin,
                enableWildcard: false } as IMonitorPathInfo
            ] as IMonitorPathInfo[],
            (m: IMonitor): void => {
                if (this._monitorFunction) {
                    this.monitorFunctionRunCount++;
                    this._monitorFunction!(m);
                }
            },
        );
    }
}

// === ClassPerson ==========================================================

class ClassPerson implements IObservedObject, IWatchSubscriberRegister {
    private readonly subscribedWatches_: ISubscribedWatches;

    constructor(firstName: string, lastName: string) {
        this.__backing_firstName = firstName;
        this.__backing_lastName = lastName;
        this.subscribedWatches_ = StateMgmtFactory.makeSubscribedWatches();

        this.__computed_fullName = StateMgmtFactory.makeComputed<string>(
            (): string => {
                stateMgmtConsole.log('computing fullName');
                return this.firstName + ' ' + this.lastName;
            },
            'fullName',
        );
    }

    public addWatchSubscriber(watchId: WatchIdType): void {
        this.subscribedWatches_!.addWatchSubscriber(watchId);
    }
    public removeWatchSubscriber(watchId: WatchIdType): boolean {
        return this.subscribedWatches_!.removeWatchSubscriber(watchId);
    }
    protected executeOnSubscribingWatches(changedPropName: string): void {
        this.subscribedWatches_!.executeOnSubscribingWatches(changedPropName);
    }

    private ____V1RenderId: RenderIdType = 0;
    public setV1RenderId(renderId: RenderIdType): void {
        this.____V1RenderId = renderId;
    }
    protected conditionalAddRef(meta: IMutableStateMeta): void {
        if (ObserveSingleton.instance.shouldAddRef(this.____V1RenderId)) {
            meta.addRef();
        }
    }

    private __backing_firstName: string;
    private readonly __meta_firstName: IMutableStateMeta = StateMgmtFactory.makeMutableStateMeta();
    public get firstName(): string {
        this.conditionalAddRef(this.__meta_firstName);
        return this.__backing_firstName;
    }
    public set firstName(newValue: string) {
        if (this.__backing_firstName !== newValue) {
            this.__backing_firstName = newValue;
            this.__meta_firstName.fireChange();
            this.executeOnSubscribingWatches('firstName');
        }
    }

    private __backing_lastName: string;
    private readonly __meta_lastName: IMutableStateMeta = StateMgmtFactory.makeMutableStateMeta();
    public get lastName(): string {
        this.conditionalAddRef(this.__meta_lastName);
        return this.__backing_lastName;
    }
    public set lastName(newValue: string) {
        if (this.__backing_lastName !== newValue) {
            this.__backing_lastName = newValue;
            this.__meta_lastName.fireChange();
            this.executeOnSubscribingWatches('lastName');
        }
    }

    private __computed_fullName: IComputedDecoratedVariable<string>;
    public get fullName(): string {
        return this.__computed_fullName.get();
    }
}

// === Test bodies ===========================================================

// Monitor over a chained @Computed. Updating celcius re-runs both
// fahrenheit and kelvin; the monitor on `kelvin` should fire.
// updateDirty() is called even in sync mode — see file header for why
// SyncMonitors on @Computed still need an explicit drain.
function doMonitorOnChainedComputedKelvin(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    const c = new ChainedComputedComponent(null, { celcius: 10 }, isSync);
    ObserveSingleton.instance.updateDirty();
    test(`[${tag}] chained: fahrenheit === 50`, eq(c.fahrenheit, 50));
    test(`[${tag}] chained: kelvin === 283.15`, eq(c.kelvin, 283.15));

    c._monitorFunction = (_m: IMonitor) => {
        stateMgmtConsole.log(`KELVIN monitor[${tag}] fired, kelvin=${c.kelvin}`);
    };

    c.celcius = 20;
    ObserveSingleton.instance.updateDirty();
    test(`[${tag}] chained: fahrenheit === 68`, eq(c.fahrenheit, 68));
    test(`[${tag}] chained: kelvin === 293.15`, eq(c.kelvin, 293.15));
    test(`[${tag}] chained: monitor count === 1`, eq(c.monitorFunctionRunCount, 1));
}

// Monitor over a @Computed (fullName = firstName + ' ' + lastName).
// Mutating either source must re-run the @Computed and fire the monitor.
// updateDirty() is required after each source write in BOTH modes — see
// file header for the SyncMonitor + @Computed staging note.
function doMonitorOnComputedFullName(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    const person = new ClassPerson('Jack', 'Ripper');
    let monitorCallCount: int = 0;

    const _monitor = makeMonitorByMode(
        isSync,
        [{
            path: 'person.fullName',
            valueCallback: (): string => person.fullName,
            enableWildcard: false } as IMonitorPathInfo
        ] as IMonitorPathInfo[],
        (m: IMonitor): void => {
            monitorCallCount++;
            stateMgmtConsole.log(`Monitor[${tag}] 'person.fullName' triggered`);
        },
    );

    person.firstName = 'John';
    ObserveSingleton.instance.updateDirty();
    test(`[${tag}] fullName: monitorCallCount === 1 after firstName write`, eq(monitorCallCount, 1));
    test(`[${tag}] fullName: person.fullName === 'John Ripper'`, eq(person.fullName, 'John Ripper'));

    person.lastName = 'Doe';
    ObserveSingleton.instance.updateDirty();
    test(`[${tag}] fullName: monitorCallCount === 2 after lastName write`, eq(monitorCallCount, 2));
    test(`[${tag}] fullName: person.fullName === 'John Doe'`, eq(person.fullName, 'John Doe'));

    // No-op assignment: setter short-circuits, no fire, fullName unchanged.
    person.firstName = 'John';
    ObserveSingleton.instance.updateDirty();
    test(`[${tag}] fullName: no-op firstName write does not fire: monitorCallCount === 2`, eq(monitorCallCount, 2));
    test(`[${tag}] fullName: person.fullName === 'John Doe'`, eq(person.fullName, 'John Doe'));
}

// === Suite wiring ==========================================================

function runComputedSuite(isSync: boolean): void {
    const factoryName = isSync ? 'makeSyncMonitor' : 'makeMonitor';

    tcase(`### ${factoryName} on chained @Computed kelvin: monitor fires when celcius changes`)
    {
        doMonitorOnChainedComputedKelvin(isSync);
    }

    tcase(`### ${factoryName} on @Computed fullName (ClassPerson): firstName / lastName writes fire the monitor`)
    {
        doMonitorOnComputedFullName(isSync);
    }
}

export function run_monitor_computed(): boolean {
    const ttest = tsuite('@Monitor on @Computed') {
        runComputedSuite(/* isSync */ false);
    }
    ttest();
    return true;
}

export function run_syncmonitor_computed(): boolean {
    const ttest = tsuite('@SyncMonitor on @Computed') {
        runComputedSuite(/* isSync */ true);
    }
    ttest();
    return true;
}
