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
import { float32, int32 } from "@koalaui/common"
import { Access, ptrToBits, withFloat32Array, KFloat32ArrayPtr, Wrapper, pointer, bitsToPtr,
    KPointer, KInt, KFloat, wrapCallback,
    nullptr, Finalizable } from "@koalaui/interop"
import { ArkUINativeModule } from "./generated/ArkUINativeModule"
import { DataNode, IncrementalNode, contextNode } from "@koalaui/runtime"
import {
    AreaChangePeerEvent,
    CallbackPeerEvent,
    GesturePeerEvent,
    ImageCompletePeerEvent, ImageErrorPeerEvent,
    KeyPeerEvent,
    MousePeerEvent,
    PeerEvent,
    SinglePointerPeerEvent,
    XComponentLoadPeerEvent,
    PeerEnterKeyType,
    PeerSubmitEvent
} from "./PeerEvents"
import { NativePeerNode } from "./NativePeerNode"
import { WebLoadInterceptDataType } from "./WebResourceRequest"
import { ArkAlignment } from "./PeerLayout"

export function IntToFloatArray(array: Int32Array, offset: number = 0, length?: number): Float32Array {
    length = length ?? (array.length - offset)
    const data = new Float32Array(length)
    for (let i = 0; i < data.length; i++) {
        data[i] = array[i + offset]
    }
    return data
}

// This class doesn't manage its pointer, so not Finalizable.
export class PeerCanvas extends Wrapper {
    constructor(ptr: pointer) {
        super(ptr)
    }
    // Improve: commonize with Skoala!
    drawRect(left: float32, top: float32, right: float32, botton: float32, paint: PeerPaint) {
        console.log("drawRect: method not implemented")
    }
}


export class PeerPaint extends Finalizable {
    private constructor(ptr: pointer) {
        super(ptr, 0)
    }
    // Improve: commonize with Skoala!
    static make(): PeerPaint {
        console.log("make: method not implemented")
        return new PeerPaint(0)
    }
    setColor(color: int32) {
        console.log("setColor: method not implemented")
    }
    getColor(): int32 {
        console.log("getColor: method not implemented")
        return 0;
    }
}


export enum DirtyFlags {
    Geometry = 1, // 1 << 0,
    Visual = 2, // 1 << 1,
}

export interface CustomizableNode {
    onMeasure(args: Float32Array): int32
    onLayout(args: Float32Array): int32
    onDraw(canvas: PeerCanvas, args: Float32Array): int32

    firstChildNode(): CustomizableNode|undefined
    previousSiblingNode(): CustomizableNode|undefined
    nextSiblingNode(): CustomizableNode|undefined
    parentNode(): CustomizableNode|undefined

    markDirty(flags: int32): void
    getDirty(): int32
    clearDirty(flags: int32): void
}

export const PeerNodeType = 11
export const PartialPropertiesType = 13
export const GeneratedPartialPropertiesType = 14
export const LegacyNodeType = 17

function parentWithPeer(node?: IncrementalNode): PeerNode | undefined {
    node = node?.parent
    while (node) {
        if (node.isKind(PeerNodeType)) return node as PeerNode
        node = node.parent
    }
    return undefined
}

export interface Sized {
    size(): number
}

export class LazyRangeStartMarker {
    public onRangeUpdate: (startIndex: number, endIndex: number) => void
    public currentStart: () => number
    public currentEnd: () => number
    private sizedRange: Sized

    constructor(onRangeUpdate: (startIndex: number, endIndex: number) => void, sizedRange: Sized,
                currentStart: () => number, currentEnd: () => number) {
        this.sizedRange = sizedRange
        this.currentEnd = currentEnd
        this.currentStart = currentStart
        this.onRangeUpdate = onRangeUpdate
    }

    rangeSize(): number {
        return this.sizedRange.size()
    }
}

export class LazyRangeEndMarker {
    constructor() { }
}

export interface Properties {
    onClick: (event: SinglePointerPeerEvent) => void
    onSwiperChange: (value: number) => void
    onTabsChange: (value: number) => void
    onVisibleAreaChange: (isVisible: boolean, currentRatio: number) => void
    lazyRangeStart: LazyRangeStartMarker
    lazyRangeEnd: LazyRangeEndMarker
    onAppear: () => void
    onDisappear: () => void
    onScrollIndex: (first: number, last: number) => void
    onNavigatorClick: () => void
    onAction: (event: GesturePeerEvent) => void
    onActionStart: (event: GesturePeerEvent) => void
    onActionUpdate: (event: GesturePeerEvent) => void
    onActionEnd: (event: GesturePeerEvent) => void
    onActionCancel: () => void
    onTextInput: (text: string) => void
    onSwiperAnimationStart: (index: number, targetIndex: number, currentOffset: number, targetOffset: number, velocity: number) => void
    onSwiperAnimationEnd: (index: number, currentOffset: number, targetOffset: number, velocity: number) => void
    onSwiperGestureSwipe: (index: number, currentOffset: number, targetOffset: number, velocity: number) => void
    onAreaChange: (event: AreaChangePeerEvent) => void
    onBlur: () => void
    onCanvasReady: () => void
    onListScroll:(scrollOffset: number, scrollState: number) => void
    onListScrollIndex:(start: number, end: number, center: number) => void
    onListScrollStart:() => void
    onListScrollStop:() => void
    onWebLoadIntercept: (event: WebLoadInterceptDataType) => boolean
    onToggleChange: (isOn: boolean) => void
    onTextInputEditChange: (isEditing: boolean) => void
    onTextInputSubmit: (enterKey: PeerEnterKeyType, event: PeerSubmitEvent) => void
    onTextInputChange: (value: string) => void
    onSliderChange: (value: number, mode: number) => void
    onHover: (isHover: boolean) => void
    onKeyEvent: (event: KeyPeerEvent) => void
    onMouse: (event: MousePeerEvent) => void
    onImageComplete: (event: ImageCompletePeerEvent) => void
    onImageError: (event: ImageErrorPeerEvent) => void
    onRefreshStateChange: (state: number) => void
    onRefreshing:() => void
    onRadioChange: (isChecked: boolean) => void
    onGridScroll:(scrollOffset: number, scrollState: number) => void
    onGridScrollStart:() => void
    onGridScrollStop:() => void
    onSideBarChange:(value: boolean) => void
    onXComponentLoad: (event: XComponentLoadPeerEvent) => void
    onXComponentDestroy: () => void
    onNavBarStateChange: (isVisible: boolean) => void
    navDestination: (name: string, param: unknown) => void
}

/** @memo */
export function UseProperties(properties: Partial<Properties>) {
    const parent = contextNode<PeerNode>(PeerNodeType)
    DataNode.attach(PartialPropertiesType, properties, () => {
        parent.invalidateProperties()
    })
}

function findPeerNode(node: IncrementalNode): PeerNode | undefined {
    if (node.isKind(PeerNodeType)) return node as PeerNode
    for (let child = node.firstChild; child; child = child.nextSibling) {
        let peer = findPeerNode(child)
        if (peer) return peer
    }
    return undefined
}

let currentPostman = (node: PeerNode, peerEvent: PeerEvent, props: Partial<Properties>) => { }

export function setEventDeliverer(postman:
    (node: PeerNode, peerEvent: PeerEvent, props: Partial<Properties>) => void) {
    currentPostman = postman
}

function intersect(interval1: number[], interval2: number[]): number[] | undefined {
    let min = Math.max(interval1[0], interval2[0])
    let max = Math.min(interval1[1], interval2[1])
    return max < min ? undefined : [min, max]
}

export enum NativeNodeFlags {
    None = 0,
    CustomMeasure = 1, // 1 << 0,
    CustomLayout = 2, // 1 << 1,
    CustomDraw = 4, // 1 << 2,
}

export enum CustomNodeOpType {
    Measure = 1,
    Layout = 2,
    Draw = 3
}

export const UndefinedDimensionUnit = -1
const INITIAL_ID = 1000

export class PeerNode extends IncrementalNode implements CustomizableNode {
    peer: NativePeerNode
    private id: number
    private insertMark: pointer = nullptr
    private insertDirection: int32 = 0

    setId(id: int32) {
        PeerNode.updatePeerNodeMap()
        PeerNode.peerNodeMap.delete(this.id)
        this.id = id
        PeerNode.peerNodeMap.set(this.id, this)
    }

    setInsertMark(mark: pointer, upDirection: boolean) {
        // console.log(`setInsertMark 0x${mark.toString(16)} ${upDirection ? "up" : "down"}`)
        this.insertMark = mark
        this.insertDirection = upDirection ? 0 : 1
    }

    getId(): number { return this.id }
    getPeerId(): number { return this.peer.id }
    getPeerPtr(): pointer { return this.peer.ptr }
    static nextId(): int32 { return PeerNode.currentId++ }

    private flags: int32
    getFlags(): int32 { return this.flags }

    alignment: int32 = ArkAlignment.Center
    measureResult: Float32Array = new Float32Array(4)
    layoutResult: Float32Array = new Float32Array(4)

    protected static currentId = INITIAL_ID
    private static peerNodeMap = new Map<number, PeerNode>()

    // peerNodeRawTail needs for perf optimizations. Insert into array much faster
    private static peerNodeRawTail = new Array<PeerNode>()

    private static updatePeerNodeMap() {
        if (PeerNode.peerNodeRawTail.length === 0)
            return

        PeerNode.peerNodeRawTail.forEach((peer: PeerNode) => {
            PeerNode.peerNodeMap.set(peer.id, peer)
        })

        PeerNode.peerNodeRawTail = []
    }

    static findPeerByNativeId(id: number): PeerNode | undefined {
        PeerNode.updatePeerNodeMap()
        return PeerNode.peerNodeMap.get(id)
    }

    static deliverEventFromPeer(event: PeerEvent) {
        let peer = PeerNode.findPeerByNativeId(event.nodeId)
        peer?.deliverEvent(event)
    }

    _name: string = "PeerNode"
    constructor(peerPtr: pointer, id: int32, name: string, flags: int32) {
        super(PeerNodeType)
        this.id = id
        this.peer = NativePeerNode.create(this, peerPtr, flags)

        this.flags = flags
        this._name = name
        PeerNode.peerNodeRawTail.push(this)
        this.onChildInserted = (child: IncrementalNode) => {
            let peer = findPeerNode(child)!
            if (peer) {
                let peerPtr = peer.getPeerPtr()
                if (this.insertMark != nullptr) {
                    if (this.insertDirection == 0) {
                        this.peer.insertChildBefore(peerPtr, this.insertMark)
                    } else {
                        this.peer.insertChildAfter(peerPtr, this.insertMark)
                    }
                    this.insertMark = peerPtr
                    return
                }

                // Find the closest peer node backward.
                // Improve: rework to avoid search
                let sibling: PeerNode | undefined = undefined
                for (let node = child.previousSibling; node; node = node.previousSibling) {
                    if (node.isKind(PeerNodeType)) {
                        sibling = node as PeerNode
                        break
                    }
                }
                this.peer.insertChildAfter(peerPtr, sibling?.getPeerPtr() ?? nullptr)
            }
        }
        this.onChildRemoved = (child: IncrementalNode) => {
            let peer = findPeerNode(child)
            if (peer) {
                this.peer.removeChild(peer.peer)
            }
        }
    }

    customizationCallback(args: Int32Array): int32 {
        switch (args[0]) {
            case CustomNodeOpType.Measure: {
                return this.onMeasure(IntToFloatArray(args, 1))
            }
            case CustomNodeOpType.Layout: {
                return this.onLayout(IntToFloatArray(args, 1))
            }
            case CustomNodeOpType.Draw: return this.onDraw(new PeerCanvas(bitsToPtr(args, 1)), IntToFloatArray(args, 3))
        }
        return 0
    }

    onMeasure(args: Float32Array): int32 {
        if ((this.flags & NativeNodeFlags.CustomMeasure) == 0) {
            // This node doesn't have managed measure, call native instead.
            let result = 0
            withFloat32Array(args, Access.READ | Access.WRITE, (argsPtr: KFloat32ArrayPtr) => {
                // Call native measure
                result = ArkUINativeModule._MeasureNode(this.peer.ptr, argsPtr)
            })
            return result
        }
        if ((this.getDirty() & DirtyFlags.Geometry) == 0) return 0
        // default behavior
        const measureArray = new Float32Array(args)
        for (let child = this.firstChildNode(); child != undefined; child = child.nextSiblingNode()) {
            let childPeer = child as PeerNode
            childPeer.onMeasure(measureArray)
        }
        this.measureResult.set(args)
        ArkUINativeModule._SetMeasureWidth(this.peer.ptr, this.measureResult[0])
        ArkUINativeModule._SetMeasureHeight(this.peer.ptr, this.measureResult[1])
        return this._dirtyFlags
    }

    onLayout(args: Float32Array): int32 {
        if ((this.flags & NativeNodeFlags.CustomLayout) == 0) {
            // This node doesn't have managed layout, call native instead.
            let result = 0
            withFloat32Array(args, Access.READ | Access.WRITE, (argsPtr: KFloat32ArrayPtr) => {
                // Call native layout.
                result = ArkUINativeModule._LayoutNode(this.peer.ptr, argsPtr)
            })
            return result
        }
        if ((this.getDirty() & DirtyFlags.Geometry) == 0) return 0
        // default behavior
        let layoutArray = new Float32Array(args)
        for (let child = this.firstChildNode(); child != undefined; child = child.nextSiblingNode()) {
            let childPeer = child as PeerNode
            childPeer.onLayout(layoutArray)
        }
        this.layoutResult.set(args)
        let dirty = this._dirtyFlags
        this.clearDirty(DirtyFlags.Geometry)
        return dirty
    }

    onDraw(canvas: PeerCanvas, args: Float32Array): int32 {
        if ((this.flags & NativeNodeFlags.CustomDraw) == 0) {
            // This node doesn't have managed layout, call native instead.
            let result = 0
            withFloat32Array(args, Access.READ | Access.WRITE, (argsPtr: KFloat32ArrayPtr) => {
                // Call native draw.
                result = ArkUINativeModule._DrawNode(this.peer.ptr, argsPtr)
            })
            return result
        }
        // default behavior
        let drawArray = new Float32Array(4)
        for (let child = this.firstChildNode(); child != undefined; child = child.nextSiblingNode()) {
            let childPeer = child as PeerNode
            drawArray.set(args)
            childPeer.onDraw(canvas, drawArray)
        }
        return this._dirtyFlags
    }


    protected _dirtyFlags: int32 = 0
    markDirty(flags: int32) {
        this._dirtyFlags |= flags
        let node: PeerNode = this
        while (node != undefined) {
            node._dirtyFlags |= flags
            node = node.parent as PeerNode
        }
    }
    getDirty(): int32 {
        return this._dirtyFlags
    }
    clearDirty(flags: int32): void {
        this._dirtyFlags &= ~(flags as number)
    }
    firstChildNode(): CustomizableNode|undefined {
        let child = this.firstChild
        if (child?.isKind(PeerNodeType))
            return child as Object as CustomizableNode
        else
            return undefined
    }
    previousSiblingNode(): CustomizableNode|undefined {
        let sibling = this.previousSibling
        if (sibling?.isKind(PeerNodeType))
            return sibling as Object as CustomizableNode
        else
            return undefined

    }
    nextSiblingNode(): CustomizableNode|undefined {
        let sibling = this.nextSibling
        if (sibling?.isKind(PeerNodeType))
            return sibling as Object as CustomizableNode
        else
            return undefined
    }
    parentNode(): CustomizableNode|undefined {
        return this.parent as Object as CustomizableNode
    }

    get childrenCountOfPeer(): number {
        // Improve: add some cache for it.
        let totalCount = 0
        let inLazyRange = false
        for (let child = this.firstChild; child; child = child.nextSibling) {
            if (child.isKind(PeerNodeType)) {
                if (!inLazyRange) {
                    ++totalCount
                }
                continue
            }
            const properties = DataNode.extract<Partial<Properties>>(PartialPropertiesType, child)
            if (properties) {
                const lazyRangeStart = properties.lazyRangeStart
                if (lazyRangeStart != undefined) {
                    inLazyRange = true
                    totalCount = totalCount + lazyRangeStart.rangeSize()
                    continue
                }
                if (properties.lazyRangeEnd) {
                    inLazyRange = false
                }
            }
        }
        return totalCount
    }

    // We only need that for container nodes where LazyForEach can appear.
    private hasRangeUpdater = false
    setRangeUpdater(needed: boolean) {
        if (!needed && this.hasRangeUpdater) {
            ArkUINativeModule._SetRangeUpdater(this.peer.ptr, 0)
            this.hasRangeUpdater = false
            return
        }
        if (needed && !this.hasRangeUpdater) {
            this.hasRangeUpdater = true
            ArkUINativeModule._SetLazyItemIndexer(this.peer.ptr, wrapCallback((args1: Uint8Array, length: int32) => {
                const args = new Int32Array(args1.buffer)
                let requestedIndex = args[0]
                let logicalIndex = 0
                let currentRangeStart = 0, currentRangeEnd = 0, currentRangeSize = 0
                for (let child = this.firstChild; child; child = child.nextSibling) {
                    if (child.isKind(PeerNodeType)) {
                        if (logicalIndex == requestedIndex) {
                            let bits = ptrToBits((child as PeerNode).peer.ptr)!
                            args[1] = bits[0]
                            args[2] = bits[1]
                            return 1
                        }
                        logicalIndex++
                        continue
                    }
                    const properties = DataNode.extract<Partial<Properties>>(PartialPropertiesType, child)
                    if (properties) {
                        const lazyRangeStart = properties.lazyRangeStart
                        if (lazyRangeStart != undefined) {
                            currentRangeSize = lazyRangeStart.rangeSize()
                            currentRangeStart = lazyRangeStart.currentStart()
                            currentRangeEnd = lazyRangeStart.currentEnd()
                            logicalIndex += currentRangeStart
                        }
                        if (properties.lazyRangeEnd) {
                            logicalIndex += currentRangeSize - (currentRangeEnd - currentRangeStart)
                            currentRangeStart = 0
                            currentRangeEnd = 0
                            currentRangeSize = 0
                        }
                    }
                }
                return 0
            }, false))
            /**
             * Theory of operations.
             *
             * Native side can send us range update request for essentially range of items it wants to materialize,
             * we call it `nativeStartIndex` and `nativeEndIndex`.
             * When there's LazyForEach we insert two markers: `start` and `end` into the tree.
             * `start` contains a reference to data source, so it knows the presumable span generatable by this lazy list.
             * We walk through the children of container node, and compute the actual native index for every node.
             * We compute intersection between lazy range span and requested range, and update LazyForEach range accordingly.
             * It adds or remove elements as needed.
             */
            ArkUINativeModule._SetRangeUpdater(this.peer.ptr, CallbackPeerEvent.wrap((args: Int32Array) => {
                let nativeStartIndex = args[0]
                let nativeEndIndex = args[1]
                let inLazyRange = false
                let currentNativeIndex = 0
                // Improve: we may want some caching here.
                for (let child = this.firstChild; child; child = child.nextSibling) {
                    if (child.isKind(PeerNodeType)) {
                        if (!inLazyRange) currentNativeIndex++
                    }
                    const properties = DataNode.extract<Partial<Properties>>(PartialPropertiesType, child)
                    if (properties) {
                        const lazyRangeStart = properties.lazyRangeStart
                        if (lazyRangeStart != undefined) {
                            inLazyRange = true
                            let rangeSize = lazyRangeStart.rangeSize()
                            // We need to intersect `[currentNativeIndex, currentNativeIndex + rangeSize]` with `[nativeStartIndex, nativeEndIndex]`
                            // produce `[intersectionStart, intersectionEnd]` and use `intersectionStart - currentNativeIndex` as base of new range.
                            let intersection = intersect(
                                [currentNativeIndex, currentNativeIndex + rangeSize],
                                [nativeStartIndex, nativeEndIndex])
                            if (intersection != undefined) {
                                lazyRangeStart.onRangeUpdate(intersection[0] - currentNativeIndex, intersection[1] - currentNativeIndex)
                            }
                            currentNativeIndex += rangeSize
                        }
                        if (properties.lazyRangeEnd) {
                            inLazyRange = false
                        }
                    }
                    // Nothing else to update.
                    if (currentNativeIndex > nativeEndIndex) break
                }
            }, false))
        }
    }

    invalidateProperties() {
        // This is probably a bit heavyweight - we iterate over all partial properties and if there
        // is lazy iterators - install range updater.
        let needed = false
        for (let child = this.firstChild; child; child = child.nextSibling) {
            const properties = DataNode.extract<Partial<Properties>>(PartialPropertiesType, child)
            if (properties?.lazyRangeStart != undefined) {
                needed = true
                break
            }
        }
        // can be replaced with the following code when lambda processing will be fast enough:
        // const needed = DataNode.findFirst<Partial<Properties>>(PartialPropertiesType, this.children, properties => properties.lazyRangeStart != undefined) != undefined
        this.setRangeUpdater(needed)
    }

    deliverEvent(event: PeerEvent) {
        for (let child = this.firstChild; child; child = child.nextSibling) {
            const properties = DataNode.extract<Partial<Properties>>(PartialPropertiesType, child)
            if (properties) currentPostman(this, event, properties)
        }
        // can be replaced with the following code when lambda processing will be fast enough:
        // DataNode.forEach<Partial<Properties>>(PartialPropertiesType, this.children, properties => currentPostman(this, event, properties))
    }

    get name(): string {
        return this.peer.getAttribute("name")
    }

    set name(value: string) {
        this.peer.setAttribute("name", value)
    }

    dispose(): void {
        let parent = parentWithPeer(this)
        parent?.peer?.removeChild(this.peer)
        this.peer.dispose()
        PeerNode.updatePeerNodeMap()
        PeerNode.peerNodeMap.delete(this.id)
        super.dispose()
    }

    toString(): string {
        return `${this.constructor.name}: peer=[${this.peer}], size=[${this.getMeasureWidth(this.peer.ptr)}x${this.getMeasureHeight(this.peer.ptr)}], id=${this.getId()}`
    }

    // access to NativeModule
    protected measureNode(node: KPointer, data: KFloat32ArrayPtr): KInt {
        return ArkUINativeModule._MeasureNode(node, data)
    }
    protected layoutNode(node: KPointer, data: KFloat32ArrayPtr): KInt {
        return ArkUINativeModule._LayoutNode(node, data)
    }
    protected drawNode(node: KPointer, data: KFloat32ArrayPtr): KInt {
        return ArkUINativeModule._DrawNode(node, data)
    }
    protected setMeasureWidth(node: KPointer, value: int32) {
        ArkUINativeModule._SetMeasureWidth(node, value)
    }
    protected getMeasureWidth(node: KPointer): KFloat {
        return ArkUINativeModule._GetMeasureWidth(node)
    }
    protected setMeasureHeight(node: KPointer, value: KFloat) {
        ArkUINativeModule._SetMeasureHeight(node, value)
    }
    protected getMeasureHeight(node: KPointer): KFloat {
        return ArkUINativeModule._GetMeasureHeight(node)
    }
    protected setX(node: KPointer, value: int32) {
        ArkUINativeModule._SetX(node, value)
    }
    protected setY(node: KPointer, value: int32) {
        ArkUINativeModule._SetY(node, value)
    }
    protected getAlignment(node: KPointer): KInt {
        return ArkUINativeModule._GetAlignment(node)
    }

    applyAttributes(attributes: object): void {}
}