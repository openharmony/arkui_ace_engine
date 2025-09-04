/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

package Interop

import std.collection.*

foreign {
        func Malloc(length: Int32): UInt64
        func Free(data: KPointer): Unit
        func ReadByte(data: KPointer, index: Int64, length: Int64): Int32
        func WriteByte(data: KPointer, index: Int64, length: Int64, value: Int32): Unit
        func ReleaseCallbackResource(resourceId: Int32): Unit

        func GetGroupedLog(index: Int32): UInt64
        func StartGroupedLog(index: Int32): Unit
        func StopGroupedLog(index: Int32): Unit
        func AppendGroupedLog(index: Int32, message: CString): Unit
        func PrintGroupedLog(index: Int32): Unit
        func GetStringFinalizer(): UInt64
        func InvokeFinalizer(ptr1: UInt64, ptr2: UInt64): Unit
        func GetPtrVectorElement(ptr1: UInt64, arg: Int32): UInt64
        func StringLength(ptr1: UInt64): Int32
        func StringData(ptr1: UInt64, array: CPointer<UInt8>, arrayLength: Int32): Unit
        func StringMake(str1: CString): UInt64
        func GetPtrVectorSize(ptr1: UInt64): Int32
        func ManagedStringWrite(str1: CString, array: pointer, arrayLength: Int32, arg: Int32): Int32
        func NativeLog(str1: CString): Unit
        func Utf8ToString(data: pointer, offset: Int32, length: Int32): CString
        func CheckCallbackEvent(buffer: KSerializerBuffer, bufferLength: Int32): Int32
        func StdStringToString(cstring: UInt64): CString
        func IncrementNumber(input: Float64): Float64
        func CallCallback(callbackKind: Int32, args: KSerializerBuffer, argsSize: Int32): Unit
        func CallCallbackSync(callbackKind: Int32, args: KSerializerBuffer, argsSize: Int32): Unit
        func CallCallbackResourceHolder(holder: UInt64, resourceId: Int32): Unit
        func CallCallbackResourceReleaser(releaser: UInt64, resourceId: Int32): Unit
        func CallForeignVM(foreignContext: UInt64, kind: Int32, data: CPointer<UInt8>, length: Int32): Int32
        func LoadVirtualMachine(arg0: Int32, arg1: CString, arg2: CString): Int32
        func RunApplication(arg0: Int32, arg1: Int32): Bool
        func StartApplication(appUrl: CString, appParams: CString): UInt64
        func EmitEvent(eventType: Int32, target: Int32, arg0: Int32, arg1: Int32): CString
        func RestartWith(page: CString): Unit
}

public open class InteropNativeModule {
    public static func _Malloc(length: Int32) {
        unsafe {
            return Malloc(length)
        }
    }
    public static func _Free(data: KPointer): Unit {
        unsafe {
            Free(data)
        }
    }
    public static func _ReadByte(data: KPointer, index: Int64, length: Int64): Int32 {
        unsafe {
            return ReadByte(data, index, length)
        }
    }
    public static func _WriteByte(data: KPointer, index: Int64, length: Int64, value: Int32) {
        unsafe {
            WriteByte(data, index, length, value)
        }
    }
    public static func _ReleaseCallbackResource(resourceId: Int32): Unit {
        unsafe {
            ReleaseCallbackResource(resourceId)
        }
    }
    public static func _GetGroupedLog(index: Int32): UInt64 {
        unsafe {
            let result = GetGroupedLog(index)
            return result
        }
    }
    public static func _StartGroupedLog(index: Int32): Unit {
        unsafe {
            StartGroupedLog(index)
        }
    }
    public static func _StopGroupedLog(index: Int32): Unit {
        unsafe {
            StopGroupedLog(index)
        }
    }
    public static func _AppendGroupedLog(index: Int32, message: String): Unit {
        unsafe {
            let message =  LibC.mallocCString(message)
            AppendGroupedLog(index, message)
            LibC.free(message)
        }
    }
    public static func _PrintGroupedLog(index: Int32): Unit {
        unsafe {
            PrintGroupedLog(index)
        }
    }
    public static func _GetStringFinalizer(): UInt64 {
        unsafe {
            let result = GetStringFinalizer()
            return result
        }
    }
    public static func _InvokeFinalizer(ptr1: UInt64, ptr2: UInt64): Unit {
        unsafe {
            InvokeFinalizer(ptr1, ptr2)
        }
    }
    public static func _GetPtrVectorElement(ptr1: UInt64, arg: Int32): UInt64 {
        unsafe {
            let result = GetPtrVectorElement(ptr1, arg)
            return result
        }
    }
    public static func _StringLength(ptr1: UInt64): Int32 {
        unsafe {
            let result = StringLength(ptr1)
            return result
        }
    }
    public static func _StringData(ptr1: UInt64, array: Array<UInt8>, arrayLength: Int32): Unit {
        unsafe {
            let handle_1 = acquireArrayRawData(arr)
            StringData(ptr1, handle_1.pointer, i)
            releaseArrayRawData(handle_1)
        }
    }
    public static func _StringMake(str1: String): UInt64 {
        unsafe {
            let str1 =  LibC.mallocCString(str1)
            let result = StringMake(str1)
            LibC.free(str1)
            return result
        }
    }
    public static func _GetPtrVectorSize(ptr1: UInt64): Int32 {
        unsafe {
            let result = GetPtrVectorSize(ptr1)
            return result
        }
    }
    public static func _ManagedStringWrite(str1: String, array: pointer, arrayLength: Int32, arg: Int32): Int32 {
        unsafe {
            let str1 =  LibC.mallocCString(str1)
            let result = ManagedStringWrite(str1, arr, arrLength, arg)
            LibC.free(str1)
            return result
        }
    }
    public static func _NativeLog(str1: String): Unit {
        unsafe {
            let str1 =  LibC.mallocCString(str1)
            NativeLog(str1)
            LibC.free(str1)
        }
    }
    public static func _Utf8ToString(data: pointer, offset: Int32, length: Int32): String {
        unsafe {
            let result = Utf8ToString(data, offset, length)
            return result.toString()
        }
    }
    public static func _CheckCallbackEvent(buffer: KSerializerBuffer, bufferLength: Int32): Int32 {
        unsafe {
            return CheckCallbackEvent(buffer, bufferLength)
        }
    }
    public static func _StdStringToString(cstring: UInt64): String {
        unsafe {
            let result = StdStringToString(cstring)
            return result.toString()
        }
    }
    public static func _IncrementNumber(input: Float64): Float64 {
        unsafe {
            let result = IncrementNumber(input)
            return result
        }
    }
    public static func _CallCallback(callbackKind: Int32, args: KSerializerBuffer, argsSize: Int32): Unit {
        unsafe {
            CallCallback(callbackKind, args, argsSize)
        }
    }
    public static func _CallCallbackSync(callbackKind: Int32, args: KSerializerBuffer, argsSize: Int32): Unit {
        unsafe {
            CallCallbackSync(callbackKind, args, argsSize)
        }
    }
    public static func _CallCallbackResourceHolder(holder: UInt64, resourceId: Int32): Unit {
        unsafe {
            CallCallbackResourceHolder(holder, resourceId)
        }
    }
    public static func _CallCallbackResourceReleaser(releaser: UInt64, resourceId: Int32): Unit {
        unsafe {
            CallCallbackResourceReleaser(releaser, resourceId)
        }
    }
    public static func _CallForeignVM(foreignContext: UInt64, kind: Int32, data: ArrayList<UInt8>, length: Int32): Int32 {
        unsafe {
            let handle_2 = acquireArrayRawData(data.toArray())
            let result = CallForeignVM(foreignContext, kind, handle_2.pointer, length)
            releaseArrayRawData(handle_2)
            return result
        }
    }
    public static func _LoadVirtualMachine(arg0: Int32, arg1: String, arg2: String): Int32 {
        unsafe {
            let arg1 =  LibC.mallocCString(arg1)
            let arg2 =  LibC.mallocCString(arg2)
            let result = LoadVirtualMachine(arg0, arg1, arg2)
            LibC.free(arg1)
            LibC.free(arg2)
            return result
        }
    }
    public static func _RunApplication(arg0: Int32, arg1: Int32): Bool {
        unsafe {
            let result = RunApplication(arg0, arg1)
            return result
        }
    }
    public static func _StartApplication(appUrl: String, appParams: String): UInt64 {
        unsafe {
            let appUrl =  LibC.mallocCString(appUrl)
            let appParams =  LibC.mallocCString(appParams)
            let result = StartApplication(appUrl, appParams)
            LibC.free(appUrl)
            LibC.free(appParams)
            return result
        }
    }
    public static func _EmitEvent(eventType: Int32, target: Int32, arg0: Int32, arg1: Int32): String {
        unsafe {
            let result = EmitEvent(eventType, target, arg0, arg1)
            return result.toString()
        }
    }
    public static func _RestartWith(page: String): Unit {
        unsafe {
            let page =  LibC.mallocCString(page)
            RestartWith(page)
            LibC.free(page)
        }
    }
}