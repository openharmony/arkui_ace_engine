/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

var __decorate = (this && this.__decorate) || function (h15, i15, j15, k15) {
    var l15 = arguments.length, m15 = l15 < 3 ? i15 : k15 === null ? k15 = Object.getOwnPropertyDescriptor(i15, j15) : k15, n15;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        m15 = Reflect.decorate(h15, i15, j15, k15);
    else
        for (var o15 = h15.length - 1; o15 >= 0; o15--)
            if (n15 = h15[o15])
                m15 = (l15 < 3 ? n15(m15) : l15 > 3 ? n15(i15, j15, m15) : n15(i15, j15)) || m15;
    return l15 > 3 && m15 && Object.defineProperty(i15, j15, m15), m15;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
import matrix4 from '@ohos.matrix4';
let PI = 3.14159265359;
export function calcAABB(t13, u13, v13) {
    let w13 = 0;
    let x13 = 0;
    let y13 = 0;
    let z13 = 0;
    let a14 = [];
    for (let q14 = 0; q14 < t13.length; q14++) {
        const r14 = t13[q14];
        let s14 = r14.rect?.left ?? 0;
        let t14 = r14.rect?.top ?? 0;
        let u14 = (r14.rect?.right ?? 0) - s14;
        let v14 = (r14.rect?.bottom ?? 0) - t14;
        let w14 = r14.rotation?.centerX ?? 0.5 * u14;
        let x14 = r14.rotation?.centerY ?? 0.5 * v14;
        let y14 = r14.rotation?.angle ?? 0;
        let z14 = [
            1, 0, 0,
            -w14,
            0, 1, 0,
            -x14,
            0, 0, 1, 0,
            0, 0, 0, 1
        ];
        let a15 = [
            Math.cos(y14), -Math.sin(y14),
            0, 0,
            Math.sin(y14), Math.cos(y14),
            0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        ];
        let b15 = [
            1, 0, 0,
            s14 + w14,
            0, 1, 0,
            t14 + x14,
            0, 0, 1, 0,
            0, 0, 0, 1
        ];
        let c15 = combine(combine(z14, a15), b15);
        a14.push(c15);
        let d15 = { x: (0) * c15[0] + (0) * c15[1] + c15[3], y: (0) * c15[4] + (0) * c15[5] + c15[7] };
        let e15 = { x: (0 + u14) * c15[0] + (0) * c15[1] + c15[3], y: (0 + u14) * c15[4] + (0) * c15[5] + c15[7] };
        let f15 = { x: (0) * c15[0] + (0 + v14) * c15[1] + c15[3], y: (0) * c15[4] + (0 + v14) * c15[5] + c15[7] };
        let g15 = { x: (0 + u14) * c15[0] + (0 + v14) * c15[1] + c15[3], y: (0 + u14) * c15[4] + (0 + v14) * c15[5] + c15[7] };
        if (q14 == 0) {
            w13 = Math.min(d15.x, e15.x, f15.x, g15.x);
            y13 = Math.min(d15.y, e15.y, f15.y, g15.y);
            x13 = Math.max(d15.x, e15.x, f15.x, g15.x);
            z13 = Math.max(d15.y, e15.y, f15.y, g15.y);
        }
        else {
            w13 = Math.min(w13, d15.x, e15.x, f15.x, g15.x);
            y13 = Math.min(y13, d15.y, e15.y, f15.y, g15.y);
            x13 = Math.max(x13, d15.x, e15.x, f15.x, g15.x);
            z13 = Math.max(z13, d15.y, e15.y, f15.y, g15.y);
        }
    }
    let b14 = x13 - w13;
    let c14 = z13 - y13;
    let d14 = Math.abs(v13 / c14) > Math.abs(u13 / b14) ? (u13 / b14) : (v13 / c14);
    let e14 = [];
    for (let f14 = 0; f14 < t13.length; f14++) {
        const g14 = t13[f14];
        let h14 = g14.rect?.left ?? 0;
        let i14 = g14.rect?.top ?? 0;
        let j14 = (g14.rect?.right ?? 0) - h14;
        let k14 = (g14.rect?.bottom ?? 0) - i14;
        let l14 = g14.rotation?.angle ?? 0;
        let m14 = [
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        ];
        m14 = combine(m14, [
            Math.cos(l14), -Math.sin(l14),
            0, 0,
            Math.sin(l14), Math.cos(l14),
            0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        ]);
        m14 = combine(m14, [
            d14,
            0, 0, 0,
            0,
            d14,
            0, 0,
            0, 0,
            d14,
            0,
            0, 0, 0, 1
        ]);
        let n14 = a14[f14];
        let o14 = { x: (0) * n14[0] + (0) * n14[1] + n14[3], y: (0) * n14[4] + (0) * n14[5] + n14[7] };
        let p14 = { x: (-0.5 * j14) * m14[0] + (-0.5 * k14) * m14[1] + m14[3], y: (-0.5 * j14) * m14[4] + (-0.5 * k14) * m14[5] + m14[7] };
        m14 = combine(m14, [
            1, 0, 0,
            (o14.x - w13) * d14 - 0.5 * j14 - p14.x,
            0, 1, 0,
            (o14.y - y13) * d14 - 0.5 * k14 - p14.y,
            0, 0, 1, 0,
            0, 0, 0, 1
        ]);
        e14.push(m14);
    }
    return e14;
}
export function mat4toImageItem(l13, m13, n13) {
    let o13 = l13[10];
    let p13 = combine([
        1, 0, 0,
        vp2px(-0.5 * m13),
        0, 1, 0,
        vp2px(-0.5 * n13),
        0, 0, 1, 0,
        0, 0, 0, 1
    ], l13);
    p13 = combine(p13, [
        1, 0, 0,
        vp2px(0.5 * m13),
        0, 1, 0,
        vp2px(0.5 * n13),
        0, 0, 1, 0,
        0, 0, 0, 1
    ]);
    let q13 = { x: (0) * p13[0] + (0) * p13[1] + p13[3], y: (0) * p13[4] + (0) * p13[5] + p13[7] };
    p13 = combine(p13, [
        1, 0, 0,
        -q13.x,
        0, 1, 0,
        -q13.y,
        0, 0, 1, 0,
        0, 0, 0, 1
    ]);
    p13 = combine(p13, [
        1 / o13,
        0, 0, 0,
        0,
        1 / o13,
        0, 0,
        0, 0,
        1 / o13,
        0,
        0, 0, 0, 1
    ]);
    let r13 = 0;
    if (p13[0] >= 0) {
        r13 = Math.asin(p13[4]);
    }
    else if (p13[0] < 0 && p13[4] >= 0) {
        r13 = Math.acos(p13[0]);
    }
    else {
        r13 = -Math.acos(p13[0]);
    }
    let s13 = {
        rect: {
            left: q13.x,
            right: q13.x + vp2px(m13) * o13,
            top: q13.y,
            bottom: q13.y + vp2px(n13) * o13
        },
        rotation: {
            centerX: 0,
            centerY: 0,
            angle: r13
        }
    };
    return s13;
}
function length(k13) {
    return Math.sqrt(Math.pow(k13.x, 2) + Math.pow(k13.y, 2));
}
function vec4Multiple(i13, j13) {
    return [i13[0] * j13[0], i13[1] * j13[1], i13[2] * j13[2], i13[3] * j13[3]];
}
function vec4Add(g13, h13) {
    return [g13[0] + h13[0], g13[1] + h13[1], g13[2] + h13[2], g13[3] + h13[3]];
}
function vec4Sub(e13, f13) {
    return [e13[0] - f13[0], e13[1] - f13[1], e13[2] - f13[2], e13[3] - f13[3]];
}
function toMatrix(d13) {
    return matrix4.init([
        d13[0], d13[4], d13[8], d13[12],
        d13[1], d13[5], d13[9], d13[13],
        d13[2], d13[6], d13[10], d13[14],
        d13[3], d13[7], d13[11], d13[15],
    ]);
}
function combine(b13, c13) {
    return [
        c13[0] * b13[0] + c13[1] * b13[4] + c13[2] * b13[8] + c13[3] * b13[12],
        c13[0] * b13[1] + c13[1] * b13[5] + c13[2] * b13[9] + c13[3] * b13[13],
        c13[0] * b13[2] + c13[1] * b13[6] + c13[2] * b13[10] + c13[3] * b13[14],
        c13[0] * b13[3] + c13[1] * b13[7] + c13[2] * b13[11] + c13[3] * b13[15],
        c13[4] * b13[0] + c13[5] * b13[4] + c13[6] * b13[8] + c13[7] * b13[12],
        c13[4] * b13[1] + c13[5] * b13[5] + c13[6] * b13[9] + c13[7] * b13[13],
        c13[4] * b13[2] + c13[5] * b13[6] + c13[6] * b13[10] + c13[7] * b13[14],
        c13[4] * b13[3] + c13[5] * b13[7] + c13[6] * b13[11] + c13[7] * b13[15],
        c13[8] * b13[0] + c13[9] * b13[4] + c13[10] * b13[8] + c13[11] * b13[12],
        c13[8] * b13[1] + c13[9] * b13[5] + c13[10] * b13[9] + c13[11] * b13[13],
        c13[8] * b13[2] + c13[9] * b13[6] + c13[10] * b13[10] + c13[11] * b13[14],
        c13[8] * b13[3] + c13[9] * b13[7] + c13[10] * b13[11] + c13[11] * b13[15],
        c13[12] * b13[0] + c13[13] * b13[4] + c13[14] * b13[8] + c13[15] * b13[12],
        c13[12] * b13[1] + c13[13] * b13[5] + c13[14] * b13[9] + c13[15] * b13[13],
        c13[12] * b13[2] + c13[13] * b13[6] + c13[14] * b13[10] + c13[15] * b13[14],
        c13[12] * b13[3] + c13[13] * b13[7] + c13[14] * b13[11] + c13[15] * b13[15],
    ];
}
function mat4Inverse(n11) {
    let o11 = n11[2 + 4 * 2] * n11[3 + 4 * 3] - n11[3 + 4 * 2] * n11[2 + 4 * 3];
    let p11 = n11[1 + 4 * 2] * n11[3 + 4 * 3] - n11[3 + 4 * 2] * n11[1 + 4 * 3];
    let q11 = n11[1 + 4 * 2] * n11[2 + 4 * 3] - n11[2 + 4 * 2] * n11[1 + 4 * 3];
    let r11 = n11[2 + 4 * 1] * n11[3 + 4 * 3] - n11[3 + 4 * 1] * n11[2 + 4 * 3];
    let s11 = n11[1 + 4 * 1] * n11[3 + 4 * 3] - n11[3 + 4 * 1] * n11[1 + 4 * 3];
    let t11 = n11[1 + 4 * 1] * n11[2 + 4 * 3] - n11[2 + 4 * 1] * n11[1 + 4 * 3];
    let u11 = n11[2 + 4 * 1] * n11[3 + 4 * 2] - n11[3 + 4 * 1] * n11[2 + 4 * 2];
    let v11 = n11[1 + 4 * 1] * n11[3 + 4 * 2] - n11[3 + 4 * 1] * n11[1 + 4 * 2];
    let w11 = n11[1 + 4 * 1] * n11[2 + 4 * 2] - n11[2 + 4 * 1] * n11[1 + 4 * 2];
    let x11 = n11[2 + 4 * 0] * n11[3 + 4 * 3] - n11[3 + 4 * 0] * n11[2 + 4 * 3];
    let y11 = n11[1 + 4 * 0] * n11[3 + 4 * 3] - n11[3 + 4 * 0] * n11[1 + 4 * 3];
    let z11 = n11[1 + 4 * 0] * n11[2 + 4 * 3] - n11[2 + 4 * 0] * n11[1 + 4 * 3];
    let a12 = n11[2 + 4 * 0] * n11[3 + 4 * 2] - n11[3 + 4 * 0] * n11[2 + 4 * 2];
    let b12 = n11[1 + 4 * 0] * n11[3 + 4 * 2] - n11[3 + 4 * 0] * n11[1 + 4 * 2];
    let c12 = n11[1 + 4 * 0] * n11[2 + 4 * 2] - n11[2 + 4 * 0] * n11[1 + 4 * 2];
    let d12 = n11[2 + 4 * 0] * n11[3 + 4 * 1] - n11[3 + 4 * 0] * n11[2 + 4 * 1];
    let e12 = n11[1 + 4 * 0] * n11[3 + 4 * 1] - n11[3 + 4 * 0] * n11[1 + 4 * 1];
    let f12 = n11[1 + 4 * 0] * n11[2 + 4 * 1] - n11[2 + 4 * 0] * n11[1 + 4 * 1];
    let g12 = [o11, o11, p11, q11];
    let h12 = [r11, r11, s11, t11];
    let i12 = [u11, u11, v11, w11];
    let j12 = [x11, x11, y11, z11];
    let k12 = [a12, a12, b12, c12];
    let l12 = [d12, d12, e12, f12];
    let m12 = [n11[1 + 4 * 0], n11[0 + 4 * 0], n11[0 + 4 * 0], n11[0 + 4 * 0]];
    let n12 = [n11[1 + 4 * 1], n11[0 + 4 * 1], n11[0 + 4 * 1], n11[0 + 4 * 1]];
    let o12 = [n11[1 + 4 * 2], n11[0 + 4 * 2], n11[0 + 4 * 2], n11[0 + 4 * 2]];
    let p12 = [n11[1 + 4 * 3], n11[0 + 4 * 3], n11[0 + 4 * 3], n11[0 + 4 * 3]];
    let q12 = vec4Add(vec4Sub(vec4Multiple(n12, g12), vec4Multiple(o12, h12)), vec4Multiple(p12, i12));
    let r12 = vec4Add(vec4Sub(vec4Multiple(m12, g12), vec4Multiple(o12, j12)), vec4Multiple(p12, k12));
    let s12 = vec4Add(vec4Sub(vec4Multiple(m12, h12), vec4Multiple(n12, j12)), vec4Multiple(p12, l12));
    let t12 = vec4Add(vec4Sub(vec4Multiple(m12, i12), vec4Multiple(n12, k12)), vec4Multiple(o12, l12));
    let u12 = [+1, -1, +1, -1];
    let v12 = [-1, +1, -1, +1];
    let w12 = [
        q12[0] * u12[0], r12[0] * v12[0], s12[0] * u12[0], t12[0] * v12[0],
        q12[1] * u12[1], r12[1] * v12[1], s12[1] * u12[1], t12[1] * v12[1],
        q12[2] * u12[2], r12[2] * v12[2], s12[2] * u12[2], t12[2] * v12[2],
        q12[3] * u12[3], r12[3] * v12[3], s12[3] * u12[3], t12[3] * v12[3]
    ];
    let x12 = [w12[0 + 4 * 0], w12[1 + 4 * 0], w12[2 + 4 * 0], w12[3 + 4 * 0]];
    let y12 = [n11[0] * x12[0], n11[0] * x12[1], n11[0] * x12[2], n11[0] * x12[3]];
    let z12 = (y12[0] + y12[1]) + (y12[2] + y12[3]);
    let a13 = 1 / z12;
    return [
        a13 * w12[0], a13 * w12[1], a13 * w12[2], a13 * w12[3],
        a13 * w12[4], a13 * w12[5], a13 * w12[6], a13 * w12[7],
        a13 * w12[8], a13 * w12[9], a13 * w12[10], a13 * w12[11],
        a13 * w12[12], a13 * w12[13], a13 * w12[14], a13 * w12[15]
    ];
}
class delegate {
    constructor() {
        this.functions = [];
    }
    add(k11) {
        if (k11 instanceof Function) {
            this.functions.push(k11);
        }
        else if (k11 instanceof delegate) {
            for (let l11 = 0; l11 < k11.functions.length; l11++) {
                const m11 = k11.functions[l11];
                this.functions.push(m11);
            }
        }
    }
    invoke(...h11) {
        for (let i11 = 0; i11 < this.functions.length; i11++) {
            const j11 = this.functions[i11];
            j11(...h11);
        }
    }
}
class ImageOperateGlobalThis {
    constructor() {
        this.imageOperatorClickDelegate = new delegate();
    }
    static getInstance() {
        return ImageOperateGlobalThis.instance;
    }
    getImageOperatorClickDelegate() {
        return this.imageOperatorClickDelegate;
    }
}
ImageOperateGlobalThis.instance = new ImageOperateGlobalThis();
export class ImageOperate extends ViewV2 {
    constructor(b11, c11, d11, e11 = -1, f11, g11) {
        super(b11, e11, g11);
        this.initParam("pixelMap", (c11 && "pixelMap" in c11) ? c11.pixelMap : undefined);
        this.initParam("preTransform", (c11 && "preTransform" in c11) ? c11.preTransform : [
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        ]);
        this.initParam("imageWidth", (c11 && "imageWidth" in c11) ? c11.imageWidth : '100%');
        this.initParam("imageAspectRito", (c11 && "imageAspectRito" in c11) ? c11.imageAspectRito : undefined);
        this.imageClick = false;
        this.to00 = { x: 0, y: 0 };
        this.ImageW = 0;
        this.ImageH = 0;
        this.lockRotate = false;
        this.storeTouchPos = { x: 0, y: 0 };
        this.blockFatherTouch = false;
        this.matrix = [
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        ];
        this.initParam("setMatrixCallback", (c11 && "setMatrixCallback" in c11) ? c11.setMatrixCallback : undefined);
        this.storeMatrix = [
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        ];
        this.toWindowPos = { x: 0, y: 0 };
        this.traceId0 = -1;
        this.traceId1 = -1;
        this.store0Pos = { x: 0, y: 0 };
        this.store1Pos = { x: 0, y: 0 };
        this.touches = new Map();
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(a11) {
        this.resetParam("pixelMap", (a11 && "pixelMap" in a11) ? a11.pixelMap : undefined);
        this.resetParam("preTransform", (a11 && "preTransform" in a11) ? a11.preTransform : [
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        ]);
        this.resetParam("imageWidth", (a11 && "imageWidth" in a11) ? a11.imageWidth : '100%');
        this.resetParam("imageAspectRito", (a11 && "imageAspectRito" in a11) ? a11.imageAspectRito : undefined);
        this.imageClick = false;
        this.to00 = { x: 0, y: 0 };
        this.matrix = [
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        ];
        this.resetParam("setMatrixCallback", (a11 && "setMatrixCallback" in a11) ? a11.setMatrixCallback : undefined);
        this.storeMatrix = [
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        ];
        this.resetMonitorsOnReuse();
    }
    onMatrixChanged() {
        if (this.setMatrixCallback !== undefined) {
            this.setMatrixCallback(this.matrix);
        }
    }
    aboutToAppear() {
        this.matrix = this.preTransform;
        ImageOperateGlobalThis.getInstance().getImageOperatorClickDelegate().add(() => {
            this.imageClick = false;
        });
    }
    calcMatrix() {
        if (this.traceId0 == -1 && this.traceId1 == -1) {
            return;
        }
        else if (this.traceId0 == -1) {
            this.matrix = combine(this.storeMatrix, [
                1, 0, 0, vp2px(this.touches.get(this.traceId1).x - this.store1Pos.x),
                0, 1, 0, vp2px(this.touches.get(this.traceId1).y - this.store1Pos.y),
                0, 0, 1, 0,
                0, 0, 0, 1
            ]);
        }
        else if (this.traceId1 == -1) {
            this.matrix = combine(this.storeMatrix, [
                1, 0, 0, vp2px(this.touches.get(this.traceId0).x - this.store0Pos.x),
                0, 1, 0, vp2px(this.touches.get(this.traceId0).y - this.store0Pos.y),
                0, 0, 1, 0,
                0, 0, 0, 1
            ]);
        }
        else {
            let q10 = { x: this.store1Pos.x - this.store0Pos.x, y: this.store1Pos.y - this.store0Pos.y };
            let r10 = { x: this.touches.get(this.traceId1).x - this.touches.get(this.traceId0).x, y: this.touches.get(this.traceId1).y - this.touches.get(this.traceId0).y };
            let s10 = { x: this.to00.x - this.store0Pos.x, y: this.to00.y - this.store0Pos.y };
            let t10 = length(r10) / length(q10);
            let u10 = length(r10) / length(q10);
            let v10 = length(r10) / length(q10);
            let w10 = Math.atan(q10.y / q10.x) * 180 / PI + (q10.x < 0 ? 180 : 0);
            let x10 = Math.atan(r10.y / r10.x) * 180 / PI + (r10.x < 0 ? 180 : 0);
            let y10 = x10 - w10;
            if (this.lockRotate) {
                t10 = r10.x / q10.x;
                u10 = r10.y / q10.y;
                v10 = Math.max(0.05 / this.storeMatrix[10], Math.min(t10, u10));
                t10 = v10;
                u10 = v10;
                y10 = 0;
            }
            let z10 = { x: this.touches.get(this.traceId0).x - this.to00.x, y: this.touches.get(this.traceId0).y - this.to00.y };
            this.matrix = combine(combine(combine(combine(this.storeMatrix, [
                1, 0, 0,
                vp2px(s10.x),
                0, 1, 0,
                vp2px(s10.y),
                0, 0, 1, 0,
                0, 0, 0, 1
            ]), [
                t10,
                0, 0, 0,
                0,
                u10,
                0, 0,
                0, 0,
                v10,
                0,
                0, 0, 0, 1
            ]), [
                Math.cos(y10 / 180 * PI), -Math.sin(y10 / 180 * PI),
                0, 0,
                Math.sin(y10 / 180 * PI), Math.cos(y10 / 180 * PI),
                0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            ]), [
                1, 0, 0,
                vp2px(z10.x),
                0, 1, 0,
                vp2px(z10.y),
                0, 0, 1, 0,
                0, 0, 0, 1
            ]);
        }
    }
    handleTouchOpt(l10, m10, n10) {
        this.touches.set(l10, n10);
        if (m10 == TouchType.Down) {
            if (this.traceId0 == -1) {
                this.traceId0 = l10;
                this.store0Pos = n10;
                this.storeMatrix = this.matrix;
                if (this.touches.has(this.traceId1)) {
                    this.store1Pos = this.touches.get(this.traceId1);
                }
            }
            else if (this.traceId1 == -1) {
                this.traceId1 = l10;
                this.store1Pos = n10;
                this.storeMatrix = this.matrix;
                if (this.touches.has(this.traceId0)) {
                    this.store0Pos = this.touches.get(this.traceId0);
                }
            }
            return;
        }
        else if (m10 == TouchType.Move) {
            this.calcMatrix();
        }
        else if (m10 == TouchType.Up) {
            this.touches.delete(l10);
            if (l10 == this.traceId0) {
                if (this.touches.size >= 2) {
                    for (let p10 of this.touches) {
                        if (p10[0] != this.traceId1) {
                            this.traceId0 = p10[0];
                            this.storeMatrix = this.matrix;
                            this.store0Pos = this.touches.get(this.traceId0);
                            this.store1Pos = this.touches.get(this.traceId1);
                            return;
                        }
                    }
                }
                else {
                    this.traceId0 = -1;
                    this.storeMatrix = this.matrix;
                    this.store1Pos = this.touches.get(this.traceId1);
                }
            }
            else if (l10 == this.traceId1) {
                if (this.touches.size >= 2) {
                    for (let o10 of this.touches) {
                        if (o10[0] != this.traceId0) {
                            this.traceId1 = o10[0];
                            this.storeMatrix = this.matrix;
                            this.store0Pos = this.touches.get(this.traceId0);
                            this.store1Pos = this.touches.get(this.traceId1);
                            return;
                        }
                    }
                }
                else {
                    this.traceId1 = -1;
                    this.storeMatrix = this.matrix;
                    this.store0Pos = this.touches.get(this.traceId0);
                }
            }
            else {
                return;
            }
        }
    }
    calcPointPos(e10) {
        let f10 = [vp2px(e10.x), vp2px(e10.y), 1, 1];
        let g10 = [
            1, 0, 0, -vp2px(this.to00.x),
            0, 1, 0, -vp2px(this.to00.y),
            0, 0, 1, 0,
            0, 0, 0, 1
        ];
        let h10 = this.storeMatrix;
        let i10 = [
            1, 0, 0, vp2px(this.to00.x),
            0, 1, 0, vp2px(this.to00.y),
            0, 0, 1, 0,
            0, 0, 0, 1
        ];
        let j10 = combine(g10, h10);
        j10 = combine(j10, i10);
        let k10 = [
            f10[0] * j10[0] + f10[1] * j10[1] + f10[2] * j10[2] + f10[3] * j10[3],
            f10[0] * j10[4] + f10[1] * j10[5] + f10[2] * j10[6] + f10[3] * j10[7],
            f10[0] * j10[8] + f10[1] * j10[9] + f10[2] * j10[10] + f10[3] * j10[11],
            f10[0] * j10[12] + f10[1] * j10[13] + f10[2] * j10[14] + f10[3] * j10[15]
        ];
        return { x: px2vp(k10[0] / k10[3]), y: px2vp(k10[1] / k10[3]) };
    }
    initialRender() {
        this.observeComponentCreation2((c10, d10) => {
            Stack.create();
        }, Stack);
        this.observeComponentCreation2((u9, v9) => {
            RelativeContainer.create();
            RelativeContainer.position({ x: 0, y: 0 });
            RelativeContainer.width(this.imageWidth);
            RelativeContainer.aspectRatio(this.imageAspectRito);
            RelativeContainer.transform3D(toMatrix(this.matrix));
            RelativeContainer.onAreaChange((y9, z9) => {
                let a10 = z9.width;
                let b10 = z9.height;
                this.to00 = { x: 0.5 * a10, y: 0.5 * b10 };
                this.toWindowPos = { x: z9.globalPosition.x ?? 0, y: z9.globalPosition.y ?? 0 };
            });
            RelativeContainer.onClick(() => {
                ImageOperateGlobalThis.getInstance().getImageOperatorClickDelegate().invoke();
                this.imageClick = !this.imageClick;
            });
            RelativeContainer.onTouch((w9) => {
                w9.stopPropagation();
                if (this.blockFatherTouch) {
                    return;
                }
                for (let x9 = 0; x9 < w9.touches.length; x9++) {
                    this.handleTouchOpt(w9.touches[x9].id, w9.touches[x9].type, { x: w9.touches[x9].displayX - this.toWindowPos.x, y: w9.touches[x9].displayY - this.toWindowPos.y });
                }
            });
            RelativeContainer.hitTestBehavior(HitTestMode.BLOCK_HIERARCHY);
            RelativeContainer.borderColor(Color.Red);
        }, RelativeContainer);
        this.observeComponentCreation2((s9, t9) => {
            Image.create(this.pixelMap);
            Image.syncLoad(true);
            Image.width('100%');
            Image.height('100%');
            Image.alignRules({
                left: { anchor: "__container__", align: HorizontalAlign.Start },
                top: { anchor: "__container__", align: VerticalAlign.Top }
            });
            Image.objectFit(ImageFit.Fill);
            Image.draggable(false);
            Image.syncLoad(true);
        }, Image);
        this.observeComponentCreation2((a9, b9) => {
            If.create();
            if (this.imageClick) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((o9, p9) => {
                        Circle.create();
                        Circle.stroke(Color.Blue);
                        Circle.strokeWidth(1 / this.matrix[10]);
                        Circle.fillOpacity(0);
                        Circle.width(15 / this.matrix[10]);
                        Circle.height(15 / this.matrix[10]);
                        Circle.alignRules({
                            middle: { anchor: "__container__", align: HorizontalAlign.Start },
                            center: { anchor: "__container__", align: VerticalAlign.Top }
                        });
                        Circle.onTouch((q9) => {
                            q9.stopPropagation();
                            if (q9.touches.length == 1) {
                                let r9 = this.calcPointPos(this.to00);
                                if (q9.touches[0].type == TouchType.Down) {
                                    this.lockRotate = true;
                                    this.blockFatherTouch = true;
                                    this.storeTouchPos = { x: q9.touches[0].windowX - this.toWindowPos.x, y: q9.touches[0].windowY - this.toWindowPos.y };
                                    this.handleTouchOpt(q9.touches[0].id + 1, TouchType.Down, r9);
                                    this.handleTouchOpt(q9.touches[0].id, TouchType.Down, this.storeTouchPos);
                                }
                                else if (q9.touches[0].type == TouchType.Move) {
                                    this.handleTouchOpt(q9.touches[0].id, TouchType.Move, { x: q9.touches[0].windowX - this.toWindowPos.x, y: q9.touches[0].windowY - this.toWindowPos.y });
                                }
                                else {
                                    this.handleTouchOpt(q9.touches[0].id + 1, TouchType.Up, r9);
                                    this.handleTouchOpt(q9.touches[0].id, TouchType.Up, { x: q9.touches[0].windowX - this.toWindowPos.x, y: q9.touches[0].windowY - this.toWindowPos.y });
                                    this.lockRotate = false;
                                    this.blockFatherTouch = false;
                                }
                            }
                        });
                    }, Circle);
                    this.observeComponentCreation2((k9, l9) => {
                        Circle.create();
                        Circle.stroke(Color.Blue);
                        Circle.strokeWidth(1 / this.matrix[10]);
                        Circle.fillOpacity(0);
                        Circle.width(15 / this.matrix[10]);
                        Circle.height(15 / this.matrix[10]);
                        Circle.alignRules({
                            middle: { anchor: "__container__", align: HorizontalAlign.End },
                            center: { anchor: "__container__", align: VerticalAlign.Top }
                        });
                        Circle.onTouch((m9) => {
                            m9.stopPropagation();
                            if (m9.touches.length == 1) {
                                let n9 = this.calcPointPos(this.to00);
                                if (m9.touches[0].type == TouchType.Down) {
                                    this.lockRotate = true;
                                    this.blockFatherTouch = true;
                                    this.storeTouchPos = { x: m9.touches[0].windowX - this.toWindowPos.x, y: m9.touches[0].windowY - this.toWindowPos.y };
                                    this.handleTouchOpt(m9.touches[0].id + 1, TouchType.Down, n9);
                                    this.handleTouchOpt(m9.touches[0].id, TouchType.Down, this.storeTouchPos);
                                }
                                else if (m9.touches[0].type == TouchType.Move) {
                                    this.handleTouchOpt(m9.touches[0].id, TouchType.Move, { x: m9.touches[0].windowX - this.toWindowPos.x, y: m9.touches[0].windowY - this.toWindowPos.y });
                                }
                                else {
                                    this.handleTouchOpt(m9.touches[0].id + 1, TouchType.Up, n9);
                                    this.handleTouchOpt(m9.touches[0].id, TouchType.Up, { x: m9.touches[0].windowX - this.toWindowPos.x, y: m9.touches[0].windowY - this.toWindowPos.y });
                                    this.lockRotate = false;
                                    this.blockFatherTouch = false;
                                }
                            }
                        });
                    }, Circle);
                    this.observeComponentCreation2((g9, h9) => {
                        Circle.create();
                        Circle.stroke(Color.Blue);
                        Circle.strokeWidth(1 / this.matrix[10]);
                        Circle.fillOpacity(0);
                        Circle.width(15 / this.matrix[10]);
                        Circle.height(15 / this.matrix[10]);
                        Circle.alignRules({
                            middle: { anchor: "__container__", align: HorizontalAlign.Start },
                            center: { anchor: "__container__", align: VerticalAlign.Bottom }
                        });
                        Circle.onTouch((i9) => {
                            i9.stopPropagation();
                            if (i9.touches.length == 1) {
                                let j9 = this.calcPointPos(this.to00);
                                if (i9.touches[0].type == TouchType.Down) {
                                    this.lockRotate = true;
                                    this.blockFatherTouch = true;
                                    this.storeTouchPos = { x: i9.touches[0].windowX - this.toWindowPos.x, y: i9.touches[0].windowY - this.toWindowPos.y };
                                    this.handleTouchOpt(i9.touches[0].id + 1, TouchType.Down, j9);
                                    this.handleTouchOpt(i9.touches[0].id, TouchType.Down, this.storeTouchPos);
                                }
                                else if (i9.touches[0].type == TouchType.Move) {
                                    this.handleTouchOpt(i9.touches[0].id, TouchType.Move, { x: i9.touches[0].windowX - this.toWindowPos.x, y: i9.touches[0].windowY - this.toWindowPos.y });
                                }
                                else {
                                    this.handleTouchOpt(i9.touches[0].id + 1, TouchType.Up, j9);
                                    this.handleTouchOpt(i9.touches[0].id, TouchType.Up, { x: i9.touches[0].windowX - this.toWindowPos.x, y: i9.touches[0].windowY - this.toWindowPos.y });
                                    this.lockRotate = false;
                                    this.blockFatherTouch = false;
                                }
                            }
                        });
                    }, Circle);
                    this.observeComponentCreation2((c9, d9) => {
                        Circle.create();
                        Circle.stroke(Color.Blue);
                        Circle.strokeWidth(1 / this.matrix[10]);
                        Circle.fillOpacity(0);
                        Circle.width(15 / this.matrix[10]);
                        Circle.height(15 / this.matrix[10]);
                        Circle.alignRules({
                            middle: { anchor: "__container__", align: HorizontalAlign.End },
                            center: { anchor: "__container__", align: VerticalAlign.Bottom }
                        });
                        Circle.onTouch((e9) => {
                            e9.stopPropagation();
                            if (e9.touches.length == 1) {
                                let f9 = this.calcPointPos(this.to00);
                                if (e9.touches[0].type == TouchType.Down) {
                                    this.lockRotate = true;
                                    this.blockFatherTouch = true;
                                    this.storeTouchPos = { x: e9.touches[0].windowX - this.toWindowPos.x, y: e9.touches[0].windowY - this.toWindowPos.y };
                                    this.handleTouchOpt(e9.touches[0].id + 1, TouchType.Down, f9);
                                    this.handleTouchOpt(e9.touches[0].id, TouchType.Down, this.storeTouchPos);
                                }
                                else if (e9.touches[0].type == TouchType.Move) {
                                    this.handleTouchOpt(e9.touches[0].id, TouchType.Move, { x: e9.touches[0].windowX - this.toWindowPos.x, y: e9.touches[0].windowY - this.toWindowPos.y });
                                }
                                else {
                                    this.handleTouchOpt(e9.touches[0].id + 1, TouchType.Up, f9);
                                    this.handleTouchOpt(e9.touches[0].id, TouchType.Up, { x: e9.touches[0].windowX - this.toWindowPos.x, y: e9.touches[0].windowY - this.toWindowPos.y });
                                    this.lockRotate = false;
                                    this.blockFatherTouch = false;
                                }
                            }
                        });
                    }, Circle);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        RelativeContainer.pop();
        Stack.pop();
    }
    updateStateVars(z8) {
        if (z8 === undefined) {
            return;
        }
        if ("pixelMap" in z8) {
            this.updateParam("pixelMap", z8.pixelMap);
        }
        if ("preTransform" in z8) {
            this.updateParam("preTransform", z8.preTransform);
        }
        if ("imageWidth" in z8) {
            this.updateParam("imageWidth", z8.imageWidth);
        }
        if ("imageAspectRito" in z8) {
            this.updateParam("imageAspectRito", z8.imageAspectRito);
        }
        if ("setMatrixCallback" in z8) {
            this.updateParam("setMatrixCallback", z8.setMatrixCallback);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], ImageOperate.prototype, "pixelMap", void 0);
__decorate([
    Param
], ImageOperate.prototype, "preTransform", void 0);
__decorate([
    Param
], ImageOperate.prototype, "imageWidth", void 0);
__decorate([
    Param
], ImageOperate.prototype, "imageAspectRito", void 0);
__decorate([
    Local
], ImageOperate.prototype, "imageClick", void 0);
__decorate([
    Local
], ImageOperate.prototype, "to00", void 0);
__decorate([
    Local
], ImageOperate.prototype, "matrix", void 0);
__decorate([
    Param
], ImageOperate.prototype, "setMatrixCallback", void 0);
__decorate([
    Monitor('matrix')
], ImageOperate.prototype, "onMatrixChanged", null);
__decorate([
    Local
], ImageOperate.prototype, "storeMatrix", void 0);
