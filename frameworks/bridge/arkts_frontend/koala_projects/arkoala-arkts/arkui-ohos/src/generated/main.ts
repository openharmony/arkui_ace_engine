/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
import { ArkUINativeModule, TestNativeModule } from "#components"
import { wrapCallback, callCallback, wrapSystemCallback, registerNativeModuleLibraryName } from "@koalaui/interop"
import { deserializeAndCallCallback } from './peers/CallbackDeserializeCall.ts'
import { assertEquals, assertThrows } from "./test_utils"
import { ArkButtonPeer } from "@arkoala/arkui/peers/ArkButtonPeer"
import { ArkColumnPeer } from "@arkoala/arkui/peers/ArkColumnPeer"
import { ButtonType, LabelStyle } from '@arkoala/arkui/ArkButtonInterfaces'
import { BlurOptions, SheetTitleOptions, CustomBuilder } from "@arkoala/arkui/ArkCommonInterfaces"
import { ResourceStr,Font } from "@arkoala/arkui/ArkUnitsInterfaces"

import { Resource } from "global/resource";
import { Literal_Alignment_align } from './SyntheticDeclarations'

import { Alignment, TextOverflow, TextHeightAdaptivePolicy } from "@arkoala/arkui/ArkEnumsInterfaces"

import { Deserializer } from "@arkoala/arkui/peers/Deserializer"
import { Serializer } from "@arkoala/arkui/peers/Serializer"
import { CallbackKind } from "@arkoala/arkui/peers/CallbackKind"
import { ResourceId, InteropNativeModule } from "@koalaui/interop"
import { checkArkoalaCallbacks } from "@arkoala/arkui/peers/CallbacksChecker"


const testString1000 = "One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand words One Thousand";

/*
V8:
backdropBlur: 1456ms for 5000000 iteration, 291ms per 1M iterations
widthAttributeString: 1006ms for 5000000 iteration, 201ms per 1M iterations


PANDA:
"backdropBlur: 3518ms for 5000000 iteration, 704ms per 5000000 iterations"
"widthAttributeString: 1380ms for 5000000 iteration, 276ms per 5000000 iterations"

JVM:
backdropBlur: 284ms for 5000000 iteration, 57ms per 1M iterations
widthAttributeString: 502ms for 5000000 iteration, 100ms per 1M iterations

*/

function checkSerdeResult(name: string, value: object|string|number|undefined|null, expected: object|string|number|undefined|null) {
    if (value != expected) {
        console.log(`TEST ${name} FAILURE: ${value} != ${expected}`)
    } else {
        console.log(`TEST ${name} PASS`)
    }
}

function checkSerdeLength() {
    const ser = Serializer.hold()
    ser.writeLength("10px")
    ser.writeLength("11vp")
    ser.writeLength("12%")
    ser.writeLength("13lpx")
    ser.writeLength(14)
    const des = new Deserializer(ser.asBuffer(), ser.length())
    checkSerdeResult("Deserializer.readLength, unit px", des.readLength(), "10px")
    checkSerdeResult("Deserializer.readLength, unit vp", des.readLength(), "11vp")
    checkSerdeResult("Deserializer.readLength, unit %", des.readLength(), "12%")
    checkSerdeResult("Deserializer.readLength, unit lpx", des.readLength(), "13lpx")
    checkSerdeResult("Deserializer.readLength, number", des.readLength(), 14)
    ser.release()
}

function checkSerdeText() {
    const ser = Serializer.hold()
    const text = "test text serialization/deserialization"
    ser.writeString(text)
    const des = new Deserializer(ser.asBuffer(), ser.length())
    checkSerdeResult("Deserializer.readString", des.readString(), text)
    ser.release()
}

function checkSerdePrimitive() {
    const ser = Serializer.hold()
    ser.writeNumber(10)
    ser.writeNumber(10.5)
    ser.writeNumber(undefined)
    const des = new Deserializer(ser.asBuffer(), ser.length())
    checkSerdeResult("Deserializer.readNumber, int", des.readNumber(), 10)
    checkSerdeResult("Deserializer.readNumber, float", des.readNumber(), 10.5)
    checkSerdeResult("Deserializer.readNumber, undefined", des.readNumber(), undefined)
    ser.release()
}

function checkSerdeCustomObject() {
    const ser = Serializer.hold()
    const date = new Date(2024, 11, 28)
    ser.writeCustomObject("Date", date)
    const des = new Deserializer(ser.asBuffer(), ser.length())
    checkSerdeResult("Deserializer.readCustomObject, Date",
        JSON.stringify(date),
        JSON.stringify(des.readCustomObject("Date") as Date))
    ser.release()
}

let hasTestErrors = false

export function getNativeLog(): string {
    let ptr = InteropNativeModule._GetGroupedLog(1)
    let length = InteropNativeModule._StringLength(ptr)
    let data = new byte[length]
    InteropNativeModule._StringData(ptr, data, length)
    InteropNativeModule._InvokeFinalizer(ptr, InteropNativeModule._GetStringFinalizer())
    // TODO: better string decoding.
    let result = new StringBuilder()
    for (let i = 0; i < length; i++) {
        result.append(String.fromCharCode(data[i] as number))
    }
    return result.toString()
}

export function checkResult(name: string, test: () => void, expected: string) {
    InteropNativeModule._StartGroupedLog(1)
    test()
    InteropNativeModule._StopGroupedLog(1)
    const actual = getNativeLog()
        .replaceAll(" \n", "")
    if (actual != expected) {
        console.log(`TEST ${name} FAIL:\n  EXPECTED "${expected}"\n  ACTUAL   "${actual}"`)
        hasTestErrors = true
    } else {
        console.log(`TEST ${name} PASS`)
    }
}

class LabelStyleImpl implements LabelStyle {
    _textOverflow: TextOverflow | undefined
    _maxLines: number | undefined
    _minFontSize: number | ResourceStr | undefined
    _maxFontSize: number | ResourceStr | undefined
    _heightAdaptivePolicy: TextHeightAdaptivePolicy | undefined
    _font: Font | undefined

    constructor(maxLines?: number) {
        this._maxLines = maxLines
    }

    get overflow(): TextOverflow | undefined {
        return this._textOverflow
    }
    set overflow(arg: TextOverflow | undefined) {
        this._textOverflow = arg
    }

    get maxLines(): number | undefined {
        return this._maxLines
    }
    set maxLines(arg: number | undefined) {
        this._maxLines = arg
    }

    get minFontSize(): number | ResourceStr | undefined {
        return this._minFontSize
    }
    set minFontSize(arg: number | ResourceStr | undefined) {
        this._minFontSize = arg
    }

    get maxFontSize(): number | ResourceStr | undefined {
        return this._maxFontSize
    }
    set maxFontSize(arg: number | ResourceStr | undefined) {
        this._maxFontSize = arg
    }

    get heightAdaptivePolicy(): TextHeightAdaptivePolicy | undefined {
        return this._heightAdaptivePolicy
    }
    set heightAdaptivePolicy(arg: TextHeightAdaptivePolicy | undefined) {
        this._heightAdaptivePolicy = arg
    }

    get font(): Font | undefined {
        return this._font
    }
    set font(arg: Font | undefined) {
        this._font = arg
    }
}

class SheetTitleOptionsImpl implements SheetTitleOptions {
    _title: ResourceStr
    _subtitle: ResourceStr | undefined

    constructor(title: ResourceStr) {
        this._title = title
    }

    get title(): ResourceStr {
        return this._title
    }
    set title(arg: ResourceStr) {
        this._title = arg
    }

    get subtitle(): ResourceStr | undefined {
        return this._subtitle
    }
    set subtitle(arg: ResourceStr | undefined) {
        this._subtitle = arg
    }
}

class BlurOptionsImpl implements BlurOptions {
    _grayscale: [number, number]

    constructor(grayscale: [number, number]) {
        this._grayscale = grayscale
    }

    get grayscale(): [number, number] {
        return this._grayscale
    }
    set grayscale(arg: [number, number]) {
        this._grayscale = arg
    }
}

function checkPerf3(count: number) {
    let peer = ArkButtonPeer.create()
    let start = Date.now()
    for (let i = 0; i < count; i++) {
        peer.widthAttribute(testString1000)
    }
    let passed = Date.now() - start
    console.log(`widthAttributeString: ${Math.round(passed)}ms for ${count} iteration, ${Math.round(passed / count * 1_000_000)}ms per 1M iterations`)
}

function checkButton() {
    let peer = ArkButtonPeer.create()

    checkResult("width", () => peer.widthAttribute("42%"),
        "width({.type=2, .value=42, .unit=3, .resource=0})")
    const resource: Resource = { id: 43, bundleName: "MyApp", moduleName: "MyApp" }
    checkResult("height", () => peer.heightAttribute(resource),
        "height({.type=3, .value=0, .unit=1, .resource=43})")
    checkResult("height", () => peer.heightAttribute(44),
        "height({.type=1, .value=44, .unit=1, .resource=0})")
    const builder: CustomBuilder = (): void => { }
    const options: Literal_Alignment_align = { align: Alignment.Center }
    checkResult("background", () => peer.backgroundAttribute(builder, options),
        "background({.resource={.resourceId=104, .hold=0, .release=0}, .call=0}, {.tag=INTEROP_TAG_OBJECT, .value={.align={.tag=INTEROP_TAG_OBJECT, .value=Ark_Alignment(4)}}})")
    checkResult("type", () => peer.typeAttribute(ButtonType.Circle), "type(Ark_ButtonType(1))")
    checkResult("labelStyle", () => peer.labelStyleAttribute(new LabelStyleImpl(3)),
        "labelStyle({.overflow={.tag=INTEROP_TAG_UNDEFINED, .value={}}, .maxLines={.tag=INTEROP_TAG_OBJECT, .value={.tag=102, .i32=3}}, .minFontSize={.tag=INTEROP_TAG_UNDEFINED, .value={}}, .maxFontSize={.tag=INTEROP_TAG_UNDEFINED, .value={}}, .heightAdaptivePolicy={.tag=INTEROP_TAG_UNDEFINED, .value={}}, .font={.tag=INTEROP_TAG_UNDEFINED, .value={}}})")
    checkResult("labelStyle2", () => peer.labelStyleAttribute(new LabelStyleImpl()),
        "labelStyle({.overflow={.tag=INTEROP_TAG_UNDEFINED, .value={}}, .maxLines={.tag=INTEROP_TAG_UNDEFINED, .value={}}, .minFontSize={.tag=INTEROP_TAG_UNDEFINED, .value={}}, .maxFontSize={.tag=INTEROP_TAG_UNDEFINED, .value={}}, .heightAdaptivePolicy={.tag=INTEROP_TAG_UNDEFINED, .value={}}, .font={.tag=INTEROP_TAG_UNDEFINED, .value={}}})")
}

function checkCallback() {
    const id1 = wrapCallback((args: byte[], length: int) => 2024)
    const id2 = wrapCallback((args: byte[], length: int) => 2025)

    assertEquals("Call callback 1", 2024, callCallback(id1, [], 0))
    assertEquals("Call callback 2", 2025, callCallback(id2, [], 0))
    assertThrows("Call disposed callback 1", () => { callCallback(id1, [], 0) })
    assertThrows("Call callback 0", () => { callCallback(0, [2, 4, 6, 8], 4) })
}

function createDefaultWriteCallback(kind: CallbackKind, callback: object) {
    return (serializer: Serializer) => {
        return serializer.holdAndWriteCallback(callback,
            TestNativeModule._TestGetManagedHolder(),
            TestNativeModule._TestGetManagedReleaser(),
            TestNativeModule._TestGetManagedCaller(kind.valueOf()),
            TestNativeModule._TestGetManagedCallerSync(kind.valueOf()),
        )
    }
}

function enqueueCallback(
    writeCallback: (serializer: Serializer) => ResourceId,
    readAndCallCallback: (deserializer: Deserializer) => void,
) {
    const serializer = Serializer.hold()
    const resourceId = writeCallback(serializer)
    /* imitate libace holding resource */
    InteropNativeModule._HoldCallbackResource(resourceId)
    /* libace stored resource somewhere */
    const buffer = new byte[serializer.length()]
    for (let i = 0; i < buffer.length; i++) {
        buffer[i] = serializer.getByte(i)
    }
    serializer.release()

    /* libace calls stored callback */
    const deserializer = new Deserializer(buffer, buffer.length)
    readAndCallCallback(deserializer)
    /* libace released resource */
    InteropNativeModule._ReleaseCallbackResource(resourceId)
}

function checkTwoSidesCallback() {
    let callResult1 = "NOT_CALLED"
    let callResult2 = 0
    const call2Count = 100

    enqueueCallback(
        createDefaultWriteCallback(CallbackKind.Kind_Callback_Number_Void, (value: number): void => {
            callResult1 = `CALLED, value=${value}`
        }),
        (deserializer) => {
            const callback = deserializer.readCallback_Number_Void()
            callback(194)
        },
    )
    for (let i = 0; i < call2Count; i++) {
        enqueueCallback(
            createDefaultWriteCallback(CallbackKind.Kind_Callback_Void, (): void => {
                callResult2++
            }),
            (deserializer) => {
                const callback = deserializer.readCallback_Void()
                callback()
            },
        )
    }

    assertEquals("Callback 1 enqueued", "NOT_CALLED", callResult1)
    assertEquals(`Callback 2 enqueued ${call2Count} times`, 0, callResult2)
    checkArkoalaCallbacks()
    assertEquals("Callback 1 read&called", "CALLED, value=194", callResult1)
    assertEquals(`Callback 2 read&called ${call2Count} times`, call2Count, callResult2)
}

function checkTwoSidesCallbackSync() {
    wrapSystemCallback(1, (buff: byte[], len: int32) => { deserializeAndCallCallback(new Deserializer(buff, len)); return 0 })

    let callResult1 = "NOT_CALLED"
    enqueueCallback(
        createDefaultWriteCallback(CallbackKind.Kind_Callback_Number_Void, (value: number): void => {
            callResult1 = `CALLED, value=${value}`
        }),
        (deserializer) => {
            const callback = deserializer.readCallback_Number_Void(true)
            callback(194)
        },
    )

    assertEquals("Sync Callback 1 read&called immediately", "CALLED, value=194", callResult1)
}

function checkNumberIncrement() {
    assertEquals("Native increment", 40, InteropNativeModule._IncrementNumber(39))
}

function checkCallbackWithReturn() {
    wrapSystemCallback(1, (buff:byte[], len:int) => { deserializeAndCallCallback(new Deserializer(buff, len)); return 0 })

    let callResult1 = "NOT_CALLED"

    enqueueCallback(
        createDefaultWriteCallback(CallbackKind.Kind_Callback_Number_Boolean, (x:number): boolean => {
            return x > 10
        }),
        (deserializer) => {
            const callback = deserializer.readCallback_Number_Boolean(true)
            const result1 = callback(42)
            const result2 = callback(0)
            callResult1 = `CALLED, value1=${result1} value2=${result2}`
        },
    )

    assertEquals("Sync Callback 1 with return type read&called immediately", "CALLED, value1=true value2=false", callResult1)
}

function checkNativeCallback() {
    const id1 = wrapCallback((args: byte[], length: int): int => {
        return 123456
    })
    assertEquals("NativeCallback without args", 123456, TestNativeModule._TestCallIntNoArgs(id1))
    assertThrows("NativeCallback without args called again", () => { callCallback(id1, [], 0) })
    assertThrows("NativeCallback without args called again from native", () => { TestNativeModule._TestCallIntNoArgs(id1) })

    const id2 = wrapCallback((args: byte[], length: int): int => {
        const buf = new ArrayBuffer(length)
        const view = new DataView(buf)
        const args32 = new Int32Array(buf)
        for (let i = 0; i < length; i++) {
            view.setUint8(i, args[i]);
        }
        let sum: int = 0
        for (let i = 0; i < args32.length; i++) {
            sum += args32[i]
        }
        return sum
    })
    const arr2: int[] = [100, 200, 300, -1000]
    assertEquals("NativeCallback Int32Array sum", -400, TestNativeModule._TestCallIntIntArraySum(id2, arr2, arr2.length))

    const id3 = wrapCallback((args: byte[], length: int): int => {
        const buf = new ArrayBuffer(length)
        const view = new DataView(buf)
        const args32 = new Int32Array(buf)
        for (let i = 0; i < length; i++) {
            view.setUint8(i, args[i]);
        }
        for (let i = 1; i < args32.length; i++) {
            args32[i] += args32[i - 1]
        }
        for (let i = 0; i < length; i++) {
            args[i] = view.getUint8(i) as byte
        }
        return 0
    })
    const arr3: int[] = [100, 200, 300, -1000]
    TestNativeModule._TestCallVoidIntArrayPrefixSum(id3, arr3, arr3.length)
    assertEquals("NativeCallback Int32Array PrefixSum [0]", 100, arr3[0])
    assertEquals("NativeCallback Int32Array PrefixSum [1]", 300, arr3[1])
    assertEquals("NativeCallback Int32Array PrefixSum [2]", 600, arr3[2])
    assertEquals("NativeCallback Int32Array PrefixSum [3]", -400, arr3[3])

    const start = Date.now()
    const id4 = wrapCallback((args: byte[], length: int): int => {
        const buf = new ArrayBuffer(length)
        const view = new DataView(buf)
        const args32 = new Int32Array(buf)
        for (let i = 0; i < length; i++) {
            view.setUint8(i, args[i]);
        }
        args32[1]++
        for (let i = 0; i < length; i++) {
            args[i] = view.getUint8(i) as byte
        }
        if (args32[0] + args32[1] < args32[2]) {
            return TestNativeModule._TestCallIntRecursiveCallback(id3 + 1, args, args.length)
        }
        return 1
    }, false)
    assertEquals("NativeCallback prepare recursive callback test", id4, id3 + 1)
    const depth = 500
    const count = 100
    for (let i = 0; i < count; i++) {
        const length = 12
        const args = new byte[length]
        const buf = new ArrayBuffer(length)
        const view = new DataView(buf)
        const args32 = new Int32Array(buf)
        args32[2] = depth
        for (let i = 0; i < length; i++) {
            args[i] = view.getUint8(i) as byte
        }
        TestNativeModule._TestCallIntRecursiveCallback(id4, args, args.length)
        for (let i = 0; i < length; i++) {
            view.setUint8(i, args[i]);
        }
        if (i == 0) {
            assertEquals("NativeCallback Recursive [0]", Math.ceil(depth / 2), args32[0])
            assertEquals("NativeCallback Recursive [1]", Math.floor(depth / 2), args32[1])
        }
    }
    const passed = Date.now() - start
    console.log(`recursive native callback: ${Math.round(passed)}ms for ${depth * count} callbacks, ${Math.round(passed / (depth * count) * 1000000)}ms per 1M callbacks`)

    const id5 = wrapCallback((args: byte[], length: int): int => {
        let sum: int = 0
        for (let i = 0; i < args.length; i++) {
            sum += args[i]
        }
        return sum
    }, false)
    TestNativeModule._TestCallIntMemory(id5, 1000)
}

function checkNodeAPI() {
    console.log("TreeNode tests")

    const root = ArkColumnPeer.create()
    const child1 = ArkButtonPeer.create()
    const child2 = ArkButtonPeer.create()
    const child3 = ArkButtonPeer.create()
    const child4 = ArkButtonPeer.create()
    const child5 = ArkButtonPeer.create()

    checkResult("BasicNodeAPI addChild", () => root.peer.addChild(child1.peer.ptr),
        `addChild(0x${root.peer.ptr}, 0x${child1.peer.ptr})markDirty(0x${root.peer.ptr}, 32)`)
    checkResult("BasicNodeAPI insertChildAfter", () => root.peer.insertChildAfter(child4.peer.ptr, child1.peer.ptr),
        `insertChildAfter(0x${root.peer.ptr}, 0x${child4.peer.ptr}, 0x${child1.peer.ptr})markDirty(0x${root.peer.ptr}, 32)`)
    checkResult("BasicNodeAPI insertChildBefore", () => root.peer.insertChildBefore(child3.peer.ptr, child4.peer.ptr),
        `insertChildBefore(0x${root.peer.ptr}, 0x${child3.peer.ptr}, 0x${child4.peer.ptr})markDirty(0x${root.peer.ptr}, 32)`)
    checkResult("BasicNodeAPI insertChildAt", () => root.peer.insertChildAt(child2.peer.ptr, 1),
        `insertChildAt(0x${root.peer.ptr}, 0x${child2.peer.ptr}, 1)markDirty(0x${root.peer.ptr}, 32)`)
    checkResult("BasicNodeAPI insertChildAfter (empty tree case)", () => child4.peer.insertChildAfter(child5.peer.ptr, 0),
        `insertChildAfter(0x${child4.peer.ptr}, 0x${child5.peer.ptr}, 0x0)markDirty(0x${child4.peer.ptr}, 32)`)
    checkResult("BasicNodeAPI removeChild", () => root.peer.removeChild(child2.peer.ptr),
        `removeChild(0x${root.peer.ptr}, 0x${child2.peer.ptr})markDirty(0x${root.peer.ptr}, 32)`)
    checkResult("BasicNodeAPI dumpTree", () => root.peer.dumpTree(),
        `dumpTreeNode(0x${root.peer.ptr})`)
    checkResult("BasicNodeAPI measureLayoutAndDraw", () => ArkUINativeModule._MeasureLayoutAndDraw(root.peer.ptr),
        `measureLayoutAndDraw(0x${root.peer.ptr})`)
}

export function main(): void {
    registerNativeModuleLibraryName("InteropNativeModule", "ArkoalaNative_ark")
    registerNativeModuleLibraryName("TestNativeModule", "ArkoalaNative_ark")
    registerNativeModuleLibraryName("ArkUINativeModule", "ArkoalaNative_ark")
    registerNativeModuleLibraryName("ArkUIGeneratedNativeModule", "ArkoalaNative_ark")

    checkNumberIncrement()
    checkCallbackWithReturn()
    checkTwoSidesCallbackSync()

    checkSerdeLength()
    checkSerdeText()
    checkSerdePrimitive()
    checkSerdeCustomObject()

    // TODO: enable tests after fixing issues with arm64 panda
	// https://rnd-gitlab-msc.huawei.com/rus-os-team/virtual-machines-and-tools/panda/-/issues/20899
	// https://rnd-gitlab-msc.huawei.com/rus-os-team/virtual-machines-and-tools/panda/-/issues/20908
    // checkPerf2(5 * 1000 * 1000)
    checkPerf3(5 * 1000 * 1000)

    checkButton()

    checkCallback()
    checkNativeCallback()

    checkNodeAPI()
    checkTwoSidesCallback()

    if (hasTestErrors) {
        throw new Error("Tests failed!")
    }
}
