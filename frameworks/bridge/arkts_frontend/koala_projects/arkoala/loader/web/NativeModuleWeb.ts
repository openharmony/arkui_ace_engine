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
import {
    ComponentAsyncEventSubKind,
    NativeNodeFlags,
    PeerEventKind,
    parseLength,
    UndefinedDimensionUnit,
    align,
    ArkAlignment,
    CustomNodeOpType,
    toColor,
    ArkUINativeModuleEmpty
} from "@koalaui/arkoala"
import { decodeToString, KFloat, KFloat32ArrayPtr, KInt, KPointer, KStringPtr, callCallback } from "@koalaui/interop"
import { HEAP32, HEAP8 } from "./NativeHeap"
import { int32 } from "@koalaui/common"
import { ArkUINodeId } from "@koalaui/arkoala"
import { HTMLElement, HTMLDivElement, document, name } from "./index.web"

function getString(ptrValue: KStringPtr): string {
    let ptr = ptrValue as int32
    let len = HEAP32[ptr >> 2]
    let data = new Uint8Array(HEAP8.buffer, ptr + 4, len)
    return decodeToString(data)
}

function createElement(type: number, id: number): HTMLElement {
    const htmlTag = type === ArkUINodeId.Button ? "button" : "div"
    let node: HTMLElement = document.createElement(htmlTag)
    if (type == ArkUINodeId.Row) {
        node.style.display = "flex"
        node.style.alignItems = "flex-start"
        node.style.flexDirection = "column"
        node.style.overflowY = "scroll"
        node.style.maxHeight = "100vh"
        node.style.overflow = "hidden"
        node.style.gap = '10px'
    } else if (type == ArkUINodeId.Column) {
        node.style.display = "flex"
        node.style.alignItems = "flex-start"
        node.style.flexDirection = "row"
        node.style.overflowX = "scroll"
        node.style.maxWidth = "100vh"
        node.style.overflow = "hidden"
        node.style.gap = '10px'
    }
    node.className = "Arkoala_" + name
    return node
}

class Dimension {
    value: number = 0
    unit: KInt = UndefinedDimensionUnit
}

class TreeNodePointer {
    peer: HTMLElement
    callbackId: KInt
    flags: KInt
    width: KInt
    height: KInt
    x: KInt
    y: KInt
    measureResult: Float32Array
    layoutResult: Float32Array
    dimensionWidth: Dimension
    dimensionHeight: Dimension
    dimensionX: Dimension
    dimensionY: Dimension
    alignment: ArkAlignment
    children: Array<TreeNodePointer>
    parent?: TreeNodePointer

    constructor(peer: HTMLElement, flags: KInt) {
        this.peer = peer
        this.callbackId = 0
        this.flags = flags
        this.width = 0
        this.height = 0
        this.x = 0
        this.y = 0
        this.measureResult = new Float32Array(4)
        this.layoutResult = new Float32Array(4)
        this.dimensionWidth = new Dimension()
        this.dimensionHeight = new Dimension()
        this.dimensionX = new Dimension()
        this.dimensionY = new Dimension()
        this.alignment = ArkAlignment.Center
        this.children = []
    }

    asPointer(): KPointer {
        return this as unknown as KPointer
    }

    static fromPointer(ptr: KPointer) {
        return ptr as unknown as TreeNodePointer
    }


    add(child: TreeNodePointer) {
        child.parent = this
        this.children.push(child)
        this.peer.appendChild(child.peer)
    }

    remove(child: TreeNodePointer) {
        this.peer.removeChild(child.peer)
        const index = this.children.indexOf(child, 0);
        if (index > -1) {
            this.children.splice(index, 1);
        }
    }

    insert(child: TreeNodePointer, sibling: TreeNodePointer) {
        if (sibling) {
            const index = this.children.indexOf(sibling, 0);
            this.children.splice(index, 0, child)
            child.parent = this
            sibling.peer.after(child.peer)
        } else {
            this.add(child)
        }
    }
}

export class NativeModuleWeb extends ArkUINativeModuleEmpty {
    currentId = 0

    constructor(private root: HTMLElement) {
        super()
    }

    private asyncCallback(target: KInt, kind: KInt, args: Int32Array) {
        let array = new Int32Array(5 + args.length)
        array[0] = PeerEventKind.Callback
        array[1] = target
        array[2] = kind
        array[3] = args.length // count
        array[4] = 0 // continuation id
        array.set(args, 5)
        // todo: pending implementation
        // this.SendArkoalaEventInternal(array)
    }

    private crashShown = false
    override _ShowCrash(messagePtr: KStringPtr): void {
        if (this.crashShown) return
        this.crashShown = true
        let message = getString(messagePtr)
        message = message.replaceAll("\n", "<br/>&nbsp;&nbsp;&nbsp;&nbsp;")
        let popup: HTMLDivElement = document.createElement("div")
        popup.style.position = "absolute"
        popup.style.top = "10px"
        popup.style.left = "10px"
        popup.style.width = "800px"
        popup.style.height = "600px"
        popup.style.color = "#ffffff"
        popup.style.fontSize = "20px"
        popup.style.backgroundColor = "#0000ff"
        popup.innerHTML = message
        this.root.appendChild(popup)
    }

    override _CreateNode(type: KInt, id: KInt, flags: KInt): KPointer {
        let node = createElement(type, id)
        if (type === ArkUINodeId.Root) {
            node.style.color = "#000000ff"
            this.root.appendChild(node)
        }
        node.id = "akro_" + id
        return new TreeNodePointer(node, flags).asPointer()
    }

    override _DisposeNode(ptr: KPointer): void {
        TreeNodePointer.fromPointer(ptr).peer.remove()
    }

    _SetCustomCallbackId(node: KPointer, callbackId: KInt): void {
        TreeNodePointer.fromPointer(node).callbackId = callbackId
    }

    override _MeasureLayoutAndDraw(root: KPointer): KInt {
        // TODO: we must get this values from root node
        const rootMeasures = new Float32Array([600, 295, 600, 600])
        this._MeasureNode(root, rootMeasures)
        const rootLayouts = new Float32Array([0, 0, 600, 295])
        this._LayoutNode(root, rootLayouts)
        const rootDraw = new Float32Array([0, 0, 600, 295])
        this._DrawNode(root, rootDraw[0])

        return 0
    }

    override _MeasureNode(rootPtr: KPointer, data: KFloat32ArrayPtr): KInt {
        let root = TreeNodePointer.fromPointer(rootPtr)
        // TODO: rewrite!
        if (typeof(data) == "number") {
            this._SetMeasureWidth(rootPtr, root.dimensionWidth.value)
            this._SetMeasureHeight(rootPtr, root.dimensionHeight.value)
            return 0
        }

        const args = data as Float32Array
        if (root.flags & NativeNodeFlags.CustomMeasure) {
            const measureArray = new Int32Array(5)
            measureArray[0] = CustomNodeOpType.Measure
            measureArray.set(args, 1)
            callCallback(root.callbackId, new Uint8Array(measureArray.buffer), measureArray.byteLength)
            return 0
        }
        // default behavior
        const constraintWidth = args[0]
        const constraintHeight = args[1]

        root.width = parseLength(constraintWidth, root.dimensionWidth.value, root.dimensionWidth.unit)
        root.height = parseLength(constraintHeight, root.dimensionHeight.value, root.dimensionHeight.unit)

        const measureArray = new Float32Array(args)

        if (root.dimensionWidth.unit != UndefinedDimensionUnit) {
            measureArray[0] = root.width
        }
        if (root.dimensionHeight.unit != UndefinedDimensionUnit) {
            measureArray[1] = root.height
        }

        const isWidthWrapped = root.dimensionWidth.unit == UndefinedDimensionUnit
        const isHeightWrapped = root.dimensionHeight.unit == UndefinedDimensionUnit

        for (let index = 0; index < root.children.length; index++) {
            const child = root.children.at(index)!
            this._MeasureNode(child.asPointer(), measureArray)
            if (isWidthWrapped) {
                root.width = Math.max(root.width, measureArray[0])
            }
            if (isHeightWrapped) {
                root.height = Math.max(root.height, measureArray[1])
            }
        }

        measureArray[0] = root.width
        measureArray[1] = root.height
        root.measureResult.set(measureArray)

        return 0
    }

    override _LayoutNode(rootPtr: KPointer, data: KFloat32ArrayPtr): KInt {
        // TODO: rewrite!
        let root = TreeNodePointer.fromPointer(rootPtr)
        if (typeof(data) == "number") {
            const parent = root.parent
            if (parent) {
                const layoutArray = new Float32Array(2)
                const rect = parent.peer.getBoundingClientRect()
                layoutArray[0] = rect.left
                layoutArray[1] = rect.top
                align(
                    root.alignment,
                    parent.measureResult[0],
                    parent.measureResult[1],
                    root.measureResult[0],
                    root.measureResult[1],
                    layoutArray
                )
                this._SetX(rootPtr, layoutArray[0])
                this._SetY(rootPtr, layoutArray[1])
            }
            return 0
        }

        const args = data as Float32Array
        if (root.flags & NativeNodeFlags.CustomLayout) {
            const layoutArray = new Int32Array(5)
            layoutArray[0] = CustomNodeOpType.Layout
            layoutArray.set(args, 1)

            callCallback(root.callbackId, new Uint8Array(layoutArray.buffer), layoutArray.byteLength)
            return 0
        }

        // Box layout implementation
        root.x = args[0]
        root.y = args[1]

        for (let index = 0; index < root.children.length; index++) {
            const child = root.children.at(index)!
            const layoutArray = new Float32Array(args)
            const rect = child.peer.getBoundingClientRect()
            layoutArray[0] = rect.left
            layoutArray[1] = rect.top
            this._LayoutNode(child.asPointer(), layoutArray)
        }

        // root.layoutResult.set(data)
        return 0
    }

    override _DrawNode(rootPtr: KPointer, data: KFloat32ArrayPtr): KInt {
        // TODO: rewrite!
        let root = TreeNodePointer.fromPointer(rootPtr)
        if (root.flags & NativeNodeFlags.CustomDraw) {
            const drawArray = new Int32Array(7)
            drawArray[0] = CustomNodeOpType.Draw
            drawArray.set(data as Float32Array, 1)

            callCallback(root.callbackId, new Uint8Array(drawArray.buffer), drawArray.byteLength)
            return 0
        }
        for (let index = 0; index < root.children.length; index++) {
            const child = root.children.at(index)!
            this._DrawNode(child.asPointer(), data)
        }
        return 0
    }

    _SetBackgroundColor(ptr: KPointer, value: KInt) {
        TreeNodePointer.fromPointer(ptr).peer.style.background = toColor(value)
    }

    override _SetMeasureWidth(root: KPointer, value: number): void {
        TreeNodePointer.fromPointer(root).measureResult[0] = value
    }
    override _GetMeasureWidth(root: KPointer): number {
        const result = TreeNodePointer.fromPointer(root).measureResult[0]
        if (result == 0) {
            const rect = TreeNodePointer.fromPointer(root).peer.getBoundingClientRect()
            TreeNodePointer.fromPointer(root).measureResult[0] = rect.width
            return rect.width
        }
        return result
    }
    override _SetMeasureHeight(root: KPointer, value: number): void {
        TreeNodePointer.fromPointer(root).measureResult[1] = value
    }
    override _GetMeasureHeight(root: KPointer): number {
        const result = TreeNodePointer.fromPointer(root).measureResult[1]
        if (result == 0) {
            const rect = TreeNodePointer.fromPointer(root).peer.getBoundingClientRect()
            TreeNodePointer.fromPointer(root).measureResult[1] = rect.height
            return rect.height
        }
        return result
    }
    override _SetX(root: KPointer, value: KFloat): void {
        let peer = TreeNodePointer.fromPointer(root).peer
        peer.style.position = "absolute"
        peer.style.left = value + "px"
    }
    override _SetY(root: KPointer, value: KFloat): void {
        let peer = TreeNodePointer.fromPointer(root).peer
        peer.style.position = "absolute"
        peer.style.top = value + "px"
    }

    override _SetAlignment(root: KPointer, value: KInt): void {
        TreeNodePointer.fromPointer(root).alignment = value
    }
    override _GetAlignment(root: KPointer): KInt {
        return TreeNodePointer.fromPointer(root).alignment
    }

    _SetAlign(root: KPointer, value: number): void {
        TreeNodePointer.fromPointer(root).alignment = value
    }

    _SetTextLabel(ptr: KPointer, value: KStringPtr) {
        TreeNodePointer.fromPointer(ptr).peer.textContent = getString(value)
    }

    _SetButtonLabel(ptr: KPointer, value: KStringPtr): void {
        TreeNodePointer.fromPointer(ptr).peer.textContent = getString(value)
    }

    override _AddChild(parent: KPointer, child: KPointer): number {
        TreeNodePointer.fromPointer(parent).add(TreeNodePointer.fromPointer(child))
        return 0 // todo: return proper value
    }
    override _RemoveChild(parent: KPointer, child: KPointer): void {
        if (child) {
            TreeNodePointer.fromPointer(parent).remove(TreeNodePointer.fromPointer(child))
        }
    }
    override _InsertChildAfter(parent: KPointer, child: KPointer, sibling: KPointer): number {
        TreeNodePointer.fromPointer(parent).insert(
            TreeNodePointer.fromPointer(child),
            TreeNodePointer.fromPointer(sibling)
        )
        return 0 // todo: return proper value
    }
    _SetWidth(nodePtr: KPointer, value: number, unit: number): void {
        let ptr = TreeNodePointer.fromPointer(nodePtr)
        ptr.peer.style.width = value + "px"
        ptr.dimensionWidth.value = value
        ptr.dimensionWidth.unit = 1
    }
    _SetHeight(ptr: KPointer, value: number, unit: number): void {
        let node = TreeNodePointer.fromPointer(ptr)
        node.peer.style.height = value + "px"
        node.dimensionHeight.value = value
        node.dimensionHeight.unit = 1
    }
    _SetTextFontColor(ptr: KPointer, value: number): void {
        TreeNodePointer.fromPointer(ptr).peer.style.color = toColor(value)
    }
    _SetTextMinFontSize(ptr: KPointer, value: number, unit: number): void {
        TreeNodePointer.fromPointer(ptr).peer.style.fontSize = value + 'px'
    }
    _SetTextMaxFontSize(ptr: KPointer, value: number, unit: number): void {
        TreeNodePointer.fromPointer(ptr).peer.style.fontSize = value + 'px'
    }

    _NotifyComponentAsyncEvent(ptr: KPointer, kind: number): void {
        switch (kind) {
            case ComponentAsyncEventSubKind.OnClick: {
                let peer = TreeNodePointer.fromPointer(ptr).peer
                peer.onclick = (event: MouseEvent) => {
                    let array = new Int32Array(5)
                    array[0] = PeerEventKind.SinglePointerInput
                    array[1] = parseInt(peer.id.substring(5))
                    array[2] = event.x
                    array[3] = event.y
                    array[4] = 1
                    // todo: pending implementation
                    // this.SendArkoalaEventInternal(array)
                };
            }
        }
    }
}