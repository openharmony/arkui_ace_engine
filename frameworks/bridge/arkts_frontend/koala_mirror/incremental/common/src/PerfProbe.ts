/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

import { float64, int32, timeNow, numberToFixed } from "@koalaui/compat"

/**
 * A probe to measure performance.
 *
 * A probe can measure performance of any activity which has an entry and an exit points.
 * Such activity can be a method call, or a sequence of actions, possibly asynchronous.
 *
 * A probe which has been entered and exited is considered a performed probe (see {@link MainPerfProbe.probePerformed}).
 * A probe can be entered recursively. When all the recursive calls exits the probe becomes a performed probe.
 *
 * All performing probes form a hierarchy which is rooted at the main probe (see {@link enterMainPerfProbe}).
 * A last started probe (see {@link MainPerfProbe.enterProbe}) which has not yet performed becomes a parent
 * for the next started probe. It's the responsibility of the API caller to keep this parent-child relationship valid,
 * that is: a child probe should exit before its parent probe exits.
 *
 * Statistics gathered by a probe:
 * - call count
 * - recursive call count
 * - total time and percentage relative to the main (root) probe
 */
export interface PerfProbe {
    /**
     * The name of the probe.
     */
    readonly name: string

    /**
     * Whether this is a dummy probe which does not measure (a noop).
     *
     * @see MainPerfProbe.getProbe
     */
    readonly dummy: boolean

    /**
     * Exists the probe.
     *
     * @param log log the gathered statistics.
     * @see MainPerfProbe.enterProbe
     */
    exit(log: boolean|undefined): void

    /**
     * Cancels measuring the probe and its children probes.
     */
    cancel(b?: Boolean): void

    /**
     * User-defined data associated with the probe.
     */
    userData: string | undefined

    /**
     * Whether the probe was canceled.
     */
    readonly canceled: boolean
}

/**
 * The main (root) {@link PerfProbe}.
 *
 * This probe is used to enter the main activity.
 *
 * Calling {@link PerfProbe.cancel} removes the main probe and disposes all its resources.
 *
 * Calling {@link PerfProbe.exit} exits the main probe, cancels it and when the log option is provided
 * logs the gathered statistics.
 *
 * @see enterMainPerfProbe
 * @see getMainPerfProbe
 */
export interface MainPerfProbe extends PerfProbe {
    /**
     * Enters a child probe referenced by the {@link name} and measures it.
     * If the probe does not exist, returns a dummy instance.
     *
     * If the probe already performs a recursive call is counted.
     *
     * @see PerfProbe.exit
     * @see exitProbe
     */
    enterProbe(name: string): PerfProbe

    /**
     * Exits a child probe referenced by the {@link name}.
     * If the probe does not exist, returns a dummy instance.
     *
     * This is an equivalent of calling {@link getProbe} and then {@link PerfProbe.exit}.
     */
    exitProbe(name: string): PerfProbe

    /**
     * Returns the child probe referenced by the {@link name} if it exists,
     * otherwise a dummy instance.
     *
     * @see PerfProbe.dummy
     */
    getProbe(name: string): PerfProbe

    /**
     * Performs the {@link func} of a child probe referenced by the {@link name} and measures it.
     *
     * This is an equivalent of calling {@link enterProbe} and then {@link exitProbe}.
     *
     * If the probe already performs a recursive call is counted.
     */
    performProbe<T>(name: string, func: () => T): T

    /**
     * Returns true if the probe referenced by the {@link name} has been performed
     * (entered and exited all the recursive calls).
     */
    probePerformed(name: string): boolean
}

/**
 * Creates a {@link MainPerfProbe} instance with the {@link name} and enters its main probe.
 *
 * If a {@link MainPerfProbe} with this {@link name} already exists then it is canceled and the new one is created.
 *
 * Exit it with {@link MainPerfProbe.exit}.
 */
export function enterMainPerfProbe(name: string): MainPerfProbe {
    return new MainPerfProbeImpl(name)
}

/**
 * Returns {@link MainPerfProbe} instance with the {@link name} if it exists,
 * otherwise a dummy instance.
 *
 * @see MainPerfProbe.dummy
 */
export function getMainPerfProbe(name: string): MainPerfProbe {
    const instance = MainPerfProbeImpl.mainProbes.get(name)
    return instance ? instance : MainPerfProbeImpl.DUMMY
}

class DummyPerfProbe implements MainPerfProbe {
    get name(): string { return "dummy" }
    get dummy(): boolean { return true }
    exit(log: boolean|undefined): void {}
    cancel(b?: Boolean) {}
    get canceled(): boolean { return false }
    enterProbe(name: string): PerfProbe { return PerfProbeImpl.DUMMY }
    exitProbe (name: string): PerfProbe { return PerfProbeImpl.DUMMY }
    getProbe(name: string): PerfProbe { return PerfProbeImpl.DUMMY }
    //performProbe: <T>(_: string, func: () => T) => func(),
    performProbe<T>(name: string, func: () => T): T { return func() }
    probePerformed(_: string): boolean { return false }

    get userData(): string | undefined {
        return undefined
    }
    set userData(_: string | undefined) {}
}

class PerfProbeImpl implements PerfProbe {
    constructor(
        name: string,
        main?: MainPerfProbeImpl,
        parent?: PerfProbeImpl,
        remainder: boolean = false
    ) {
        this._name = name
        this._main = main
        this.parent = parent
        this.remainder = remainder
    }

    private readonly _name: string
    private readonly _main: MainPerfProbeImpl|undefined
    public parent: PerfProbeImpl|undefined
    public readonly remainder: boolean

    children: Array<PerfProbeImpl> = new Array<PerfProbeImpl>()
    childrenSorted: boolean = false
    index: int32 = 0
    startTime: float64 = 0.0
    totalTime: float64 = 0.0
    callCount: int32 = 0
    currentRecursionDepth: int32 = 0
    recursiveCallCount: int32 = 0
    _canceled: boolean = false
    private _userData?: string

    get name(): string {
        return this._name
    }

    get dummy(): boolean {
        return false
    }

    get main(): MainPerfProbeImpl {
        return this._main!
    }

    get performing(): boolean {
        return this.startTime > 0
    }

    get userData(): string | undefined {
        return this._userData
    }

    set userData(value: string | undefined) {
        this._userData = value
    }

    exit(log?: boolean): void {
        if (this.canceled) return

        if (this.currentRecursionDepth == 0) {
            this.totalTime += timeNow() - this.startTime
            this.startTime = 0
        } else {
            this.currentRecursionDepth--
        }
        if (!this.performing) {
            this.main.pop(this)
        }
        if (log) this.log()
    }

    cancelWithChildren() {
        this.cancel()
        this.maybeCancelChildren()
    }

    cancel(b?: Boolean) {
        this._canceled = true
    }

    private maybeCancelChildren() {
        MainPerfProbeImpl.visit(this, false, (probe: PerfProbeImpl, depth: int32) => {
            if (probe.performing) probe.cancel()
        })
    }

    get canceled(): boolean {
        return this._canceled
    }

    toString(): string {
        if (this.canceled) {
            return `[${this.name}] canceled`
        }
        if (this.performing) {
            return `[${this.name}] still performing...`
        }
        const mainProbe = this.main.probes.get(this.main.name)!
        const percentage = mainProbe.totalTime > 0 ? Math.round((100 / mainProbe.totalTime) * this.totalTime) : 0

        let result = `[${this.name}] call count: ${this.callCount}`
            +  ` | recursive call count: ${this.recursiveCallCount}`
            +  ` | time: ${this.totalTime}ms ${percentage}%`

        if (this.userData) {
            result += ` | user data: ${this.userData}`
        }

        return result
    }

    protected log(prefix?: string) {
        console.log(prefix ? `${prefix}${this.toString()}` : this.toString())
    }

    static readonly DUMMY: PerfProbe = new DummyPerfProbe()
}

class MainPerfProbeImpl extends PerfProbeImpl implements MainPerfProbe {
    constructor(
        name: string
    ) {
        super(name)
        const prev = MainPerfProbeImpl.mainProbes.get(name)
        if (prev) prev.cancel()
        MainPerfProbeImpl.mainProbes.set(name, this)
        this.currentProbe = this.enterProbe(name)
    }

    static readonly mainProbes: Map<string, MainPerfProbeImpl> = new Map<string, MainPerfProbeImpl>()

    currentProbe: PerfProbeImpl
    probes: Map<string, PerfProbeImpl> = new Map<string, PerfProbeImpl>()

    private createProbe(name: string): PerfProbeImpl {
        const probes = name == this.name ? this : new PerfProbeImpl(name, this)
        this.push(probes)
        return probes
    }

    get main(): MainPerfProbeImpl {
        return this
    }

    push(probe: PerfProbeImpl) {
        probe.parent = this.currentProbe
        probe.index = probe.parent ? probe.parent!.children.length as int32 : 0
        if (probe.parent) probe.parent!.children.push(probe)
        this.currentProbe = probe
    }

    pop(probe: PerfProbeImpl) {
        if (probe.parent) {
            this.currentProbe = probe.parent!
        }
    }

    performProbe<T>(name: string, func: () => T): T {
        const probe = this.enterProbe(name)
        try {
            return func()
        } finally {
            probe.exit()
        }
    }

    enterProbe(name: string): PerfProbeImpl {
        let probe = this.probes.get(name)
        if (!probe) {
            probe = this.createProbe(name)
            this.probes.set(name, probe)
        }
        probe._canceled = false

        if (probe.performing) {
            probe.recursiveCallCount++
            probe.currentRecursionDepth++
        } else {
            probe.startTime = timeNow()
            probe.callCount++
        }
        return probe
    }

    exitProbe(name: string): PerfProbe {
        const probe = this.getProbe(name)
        probe.exit(undefined)
        return probe
    }

    getProbe(name: string): PerfProbe {
        const probe = this.probes.get(name)
        return probe !== undefined ? probe : PerfProbeImpl.DUMMY
    }

    probePerformed(name: string): boolean {
        const probe = this.probes.get(name)
        return probe != undefined && !probe!.performing && !probe!.canceled
    }

    exit(log?: boolean) {
        super.exit()
        if (log) this.log()
        this.cancel()
    }

    cancel(b?: Boolean) {
        MainPerfProbeImpl.mainProbes.delete(this.name)
    }

    static visit(root: PerfProbeImpl, logging: boolean, apply: (probe: PerfProbeImpl, depth: int32) => void) {
        let current: PerfProbeImpl = root
        let index = 0
        let depth = 0
        let visiting = true
        while (true) {
            if (visiting) {
            	current.index = 0
            	apply(current, depth)
            }
            if (index >= current.children.length) {
                if (!current.parent) {
                    break
                }
                current = current.parent!
                index = ++current.index
                depth--
                visiting = false
                continue
            }
            visiting = true
            if (logging && !current.childrenSorted) {
                current.childrenSorted = true
                current.children = current.children.sort((p1: PerfProbeImpl, p2: PerfProbeImpl):number => p2.totalTime - p1.totalTime)
                if (depth == 0) {
                    // a special probe to log the time remained
                    current.children.push(new PerfProbeImpl("<remainder>", root.main, current, true))
                }
            }
            current = current.children[index]
            index = 0
            depth++
        }
    }

    protected log(prefix?: string) {
        prefix = prefix !== undefined ? `${prefix}: ` : ""
        console.log(`${prefix}perf probes:`)

        MainPerfProbeImpl.visit(this.main, true, (probe, depth):void => {
            let indent = "\t"
            for (let i = 0; i < depth; i++) indent += "\t"
            if (probe.remainder) {
                const parentTime = probe.parent!.totalTime
                let childrenTime = 0
                probe.parent!.children.forEach((a: PerfProbeImpl):void => { childrenTime += a.totalTime })
                probe.totalTime = Math.max(0, parentTime - childrenTime) as int32
                const percentage = parentTime > 0 ? Math.round((100 / parentTime) * probe.totalTime) : 0
                console.log(`${prefix}${indent}[${probe.name}] time: ${numberToFixed(probe.totalTime, 2)}ms ${percentage}%`)
            } else {
                console.log(`${prefix}${indent}${probe.toString()}`)
            }
        })
    }

    static readonly DUMMY: MainPerfProbe = new DummyPerfProbe()
}
