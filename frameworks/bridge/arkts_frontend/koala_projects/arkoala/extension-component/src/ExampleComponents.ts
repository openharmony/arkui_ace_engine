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

import { align, DirtyFlags, NativeNodeFlags, PeerCanvas, PeerNode, PeerPaint, } from "@koalaui/arkoala"
import { NodeAttach, remember, } from "@koalaui/runtime"
import { Access, KFloat32ArrayPtr, KPointer, withFloat32Array } from "@koalaui/interop"
import { ArkCommonMethodPeer, ArkButtonAttributes, ArkButtonPeer, Attach, ArkUINodeType, ComponentBase, ArkCommonMethodComponent, ArkUIGeneratedNativeModule } from "@koalaui/arkoala-arkui"
import { int32 } from "@koalaui/common"

class ExampleNode extends ArkCommonMethodPeer {
    protected _color: int32 = 0xff0000ff
    protected _paint?: PeerPaint
    protected _width: int32 = 0
    protected _height: int32 = 0
    protected _x: int32 = 0
    protected _y: int32 = 0

    public static create(component?: ComponentBase, flags: int32 = 0): ExampleNode {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIGeneratedNativeModule._Stack_construct(peerId, flags)
        const _peer = new ExampleNode(_peerPtr, peerId, "Example")
        component?.setPeer(_peer)
        return _peer
    }

    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, 0);
        this.markDirty(DirtyFlags.Geometry | DirtyFlags.Visual)
    }

    onMeasure(args: Float32Array): int32 {
        if ((this.getFlags() & NativeNodeFlags.CustomMeasure) == 0) {
            // This node doesn't have managed measure, call native instead.
            let result = 0
            withFloat32Array(args, Access.READ | Access.WRITE, (argsPtr: KFloat32ArrayPtr) => {
                // Call native measure
                result = this.measureNode(this.peer.ptr, argsPtr)
            })
            return result
        }

        // Box layout implementation
        // TODO: consider parent padding and current margin
        // args[0] - constraint width
        // args[1] - constraint height
        if ((this.getDirty() & DirtyFlags.Geometry) == 0) return 0

        const measureArray = new Float32Array(args)
        measureArray[0] = this._width
        measureArray[1] = this._height

        const isWidthWrapped = false
        const isHeightWrapped = false

        for (let child = this.firstChildNode(); child != undefined; child = child.nextSiblingNode()) {
            let childPeer = child as PeerNode
            childPeer.onMeasure(measureArray)
            if (isWidthWrapped) {
                this.width = Math.max(this._width, measureArray[0])
            }
            if (isHeightWrapped) {
                this.height = Math.max(this._height, measureArray[1])
            }
        }

        // record constraints
        args[0] = this._width
        args[1] = this._height

        this.measureResult.set(args)
        this.setMeasureWidth(this.peer.ptr, this._width)
        this.setMeasureHeight(this.peer.ptr, this._height)
        this.widthAttribute(this._width)
        this.widthAttribute(this._height)

        return this._dirtyFlags
    }

    onLayout(args: Float32Array): int32 {
        if ((this.getFlags() & NativeNodeFlags.CustomLayout) == 0) {
            // This node doesn't have managed layout, call native instead.
            let result = 0
            withFloat32Array(args, Access.READ | Access.WRITE, (argsPtr: KFloat32ArrayPtr) => {
                // Call native layout.
                result = this.layoutNode(this.peer.ptr, argsPtr)
            })
            return result
        }

        // Box layout implementation
        if ((this.getDirty() & DirtyFlags.Geometry) == 0) return 0

        this.x = args[0]
        this.y = args[1]

        for (let child = this.firstChildNode(); child != undefined; child = child.nextSiblingNode()) {
            let layoutArray = new Float32Array(args)
            let childPeer = child as PeerNode
            align(
                childPeer.alignment,
                this._width,
                this._height,
                this.getMeasureWidth(childPeer.peer.ptr),
                this.getMeasureHeight(childPeer.peer.ptr),
                layoutArray
            )
            childPeer.onLayout(layoutArray)
        }

        this.layoutResult.set(args)
        let dirty = this._dirtyFlags
        this.clearDirty(DirtyFlags.Geometry)

        return dirty
    }

    onDraw(canvas: PeerCanvas, args: Float32Array): int32 {
        if ((this.getFlags() & NativeNodeFlags.CustomDraw) == 0) {
            // This node doesn't have managed layout, call native instead.
            let result = 0
            withFloat32Array(args, Access.READ | Access.WRITE, (argsPtr: KFloat32ArrayPtr) => {
                // Call native draw.
                result = this.drawNode(this.peer.ptr, argsPtr)
            })
            return result
        }

        canvas.drawRect(this._x, this._y, this._x + this._width, this._y + this._height, this._paint!)

        // default behavior
        let drawArray = new Float32Array(args)
        for (let child = this.firstChildNode(); child != undefined; child = child.nextSiblingNode()) {
            let childPeer = child as PeerNode
            childPeer.onDraw(canvas, drawArray)
        }

        return this._dirtyFlags
    }

    set color(color: int32) {
        if (color != this._color || !this._paint) {
            if (!this._paint) this._paint = PeerPaint.make()
            this._paint.setColor(color)
            this._color = color
            this.markDirty(DirtyFlags.Visual)
            this.backgroundColorAttribute(0xFF000000 + this._color);
        }
    }

    set width(width: int32) {
        if (width != this._width) {
            this._width = width
            this.markDirty(DirtyFlags.Geometry)
        }
    }

    set height(height: int32) {
        if (height != this.height) {
            this._height = height
            this.markDirty(DirtyFlags.Geometry)
        }
    }

    set x(value: int32) {
        if (value != this._x) {
            this._x = value
            this.markDirty(DirtyFlags.Geometry)
        }
    }

    set y(value: int32) {
        if (value != this._y) {
            this._y = value
            this.markDirty(DirtyFlags.Geometry)
        }
    }
}

export interface ExampleNodeAttribute {
    color: number
    width: number
    height: number
    alignment: number
}

/** @memo:stable */
export class ExampleComponent_Component extends ArkCommonMethodComponent {
    getPeer(): ExampleNode {
        return (this.peer as ExampleNode)
    }
}

/** @memo */
export function ExampleComponent(style: Partial<ExampleNodeAttribute>) {
    const receiver = remember(() => {
        return new ExampleComponent_Component()
    })
    NodeAttach(() => ExampleNode.create(receiver), (node: ExampleNode) => {
        if (style.width !== undefined) node.width = style.width
        if (style.height !== undefined) node.height = style.height
        if (style.color !== undefined) node.color = style.color
        if (style.alignment !== undefined) node.alignment = style.alignment
    })
}

class BoxNode extends ExampleNode {
    private _gap: int32 = 1

    public static create(component?: ComponentBase, flags: int32 = 0): BoxNode {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIGeneratedNativeModule._Stack_construct(peerId, flags)
        const _peer = new BoxNode(_peerPtr, peerId, "BoxNode")
        component?.setPeer(_peer)
        return _peer
    }

    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, 0);
        this.markDirty(DirtyFlags.Geometry | DirtyFlags.Visual)
    }

    set gap(gap: int32) {
        if (gap != this._gap) {
            this._gap = gap
            this.markDirty(DirtyFlags.Geometry)
        }
    }

    onLayout(args: Float32Array): int32 {
        if ((this.getFlags() & NativeNodeFlags.CustomLayout) == 0) {
            // This node doesn't have managed layout, call native instead.
            let result = 0
            withFloat32Array(args, Access.READ | Access.WRITE, (argsPtr: KFloat32ArrayPtr) => {
                // Call native layout.
                result = this.layoutNode(this.peer.ptr, argsPtr)
            })
            return result
        }

        // Box layout implementation
        if ((this.getDirty() & DirtyFlags.Geometry) == 0) return 0

        this.x = args[0]
        this.y = args[1]

        for (let child = this.firstChildNode(); child != undefined; child = child.nextSiblingNode()) {
            let layoutArray = new Float32Array(args)
            let childPeer = child as ArkCommonMethodPeer
            align(
                this.getAlignment(childPeer.peer.ptr),
                this._width,
                this._height,
                this.getMeasureWidth(childPeer.peer.ptr),
                this.getMeasureHeight(childPeer.peer.ptr),
                layoutArray
            )

            // Here we need to set position in native module
            this.setX(childPeer.peer.ptr, layoutArray[0]);
            this.setY(childPeer.peer.ptr, layoutArray[1]);
            const position: Position = {
                x: layoutArray[0],
                y: layoutArray[1]
            }
            childPeer.positionAttribute(position);

            childPeer.onLayout(layoutArray)
        }

        this.layoutResult.set(args)
        let dirty = this._dirtyFlags
        this.clearDirty(DirtyFlags.Geometry)

        return dirty
    }

    set color(color: int32) {
        if (color != this._color) {
            this._color = color
            this.backgroundColorAttribute(0xFF000000 + this._color);
        }
    }
}

export interface BoxAttribute extends ExampleNodeAttribute {
    gap: number
}

/** @memo:stable */
export class BoxNode_Component extends ArkCommonMethodComponent {
    getPeer(): BoxNode {
        return (this.peer as BoxNode)
    }
}

/** @memo */
export function Box(
    style: Partial<BoxAttribute>,
    /** @memo */
    content?: () => void
) {
    const receiver = remember(() => {
        return new BoxNode_Component()
    })
    NodeAttach(() => BoxNode.create(receiver), (node: BoxNode) => {
        if (style.width !== undefined) node.width = style.width
        if (style.height !== undefined) node.height = style.height
        if (style.color !== undefined) node.color = style.color
        if (style.alignment !== undefined) node.alignment = style.alignment
        content?.()
    })
}


interface OutlinedButtonAttributes extends ArkButtonAttributes {
    label?: string,
    outlineOptions?: { thickness: number, color: Color }
    onOutlineChange?: (thickness: number, color: Color) => void
}

class OutlinedButtonPeer extends ArkButtonPeer {
    // example of override common method
    widthAttribute(value: Length): void {
        super.widthAttribute(value)
        console.log("width:", value);
    }

    private _outlineValue?: { thickness: number, color: Color }
    outlineOptions(value: { thickness: number, color: Color }) {
        this._outlineValue = {
            thickness: value.thickness,
            color: value.color
        }
        this._callback?.(
            this._outlineValue.thickness,
            this._outlineValue.color
        )
    }

    label(value: string) {
        this.setButtonOptions2Attribute(value)
    }

    private _callback?: (thickness: number, color: Color) => void
    onOutlineChange(event: (thickness: number, color: Color) => void) {
        this._callback = event
    }

    applyAttributes<T extends OutlinedButtonAttributes>(attributes: T): void {
        super.applyAttributes(attributes)
    }
}

/** @memo */
export function OutlinedButton(
    options?: any,
    /** @memo */
    content?: () => void,
) {
    Attach(() => OutlinedButtonPeer.create(), options, content)
}
