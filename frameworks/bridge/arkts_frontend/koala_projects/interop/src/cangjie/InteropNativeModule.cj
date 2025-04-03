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
        func CheckCallbackEvent(buffer: CPointer<UInt8>, bufferLength: Int32): Int32

        func GetGroupedLog(index: Int32): UInt64
        func StartGroupedLog(index: Int32): Unit
        func StopGroupedLog(index: Int32): Unit
        func AppendGroupedLog(index: Int32, message: CString): Unit
        func PrintGroupedLog(index: Int32): Unit
        func GetStringFinalizer(): UInt64
        func InvokeFinalizer(ptr1: UInt64, ptr2: UInt64): Unit
        func GetPtrVectorElement(ptr1: UInt64, arg: Int32): UInt64
        func StringLength(ptr1: UInt64): Int32
        func StringData(ptr1: UInt64, arr: CPointer<UInt8>, i: Int32): Unit
        func StringMake(str1: CString): UInt64
        func GetPtrVectorSize(ptr1: UInt64): Int32
        func ManagedStringWrite(str1: CString, arr: CPointer<UInt8>, arg: Int32): Int32
        func NativeLog(str1: CString): Unit
        func Utf8ToString(data: CPointer<UInt8>, offset: Int32, length: Int32): CString
        func StdStringToString(cstring: UInt64): CString
        func CallCallback(callbackKind: Int32, args: CPointer<UInt8>, argsSize: Int32): Unit
        func CallCallbackSync(callbackKind: Int32, args: CPointer<UInt8>, argsSize: Int32): Unit
        func CallCallbackResourceHolder(holder: UInt64, resourceId: Int32): Unit
        func CallCallbackResourceReleaser(releaser: UInt64, resourceId: Int32): Unit
        func LoadVirtualMachine(arg0: Int32, arg1: CString, arg2: CString): Int32
        func RunApplication(arg0: Int32, arg1: Int32): Bool
        func StartApplication(appUrl: CString, appParams: CString): UInt64
        func EmitEvent(eventType: Int32, target: Int32, arg0: Int32, arg1: Int32): Unit
}

public open class InteropNativeModule {
    public static func _CheckCallbackEvent(buffer: Array<UInt8>, bufferLength: Int32): Int32 {
        unsafe {
            let handle_0 = acquireArrayRawData(buffer)
            let result = CheckCallbackEvent(handle_0.pointer, bufferLength)
            releaseArrayRawData(handle_0);
            return result
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
    public static func _StringData(ptr1: UInt64, arr: ArrayList<UInt8>, i: Int32): Unit {
        unsafe {
            let handle_1 = acquireArrayRawData(arr.toArray())
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
    public static func _ManagedStringWrite(str1: String, arr: ArrayList<UInt8>, arg: Int32): Int32 {
        unsafe {
            let str1 =  LibC.mallocCString(str1)
            let handle_1 = acquireArrayRawData(arr.toArray())
            let result = ManagedStringWrite(str1, handle_1.pointer, arg)
            LibC.free(str1)
            releaseArrayRawData(handle_1)
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
    public static func _Utf8ToString(data: Array<UInt8>, offset: Int32, length: Int32): String {
        unsafe {
            let handle_0 = acquireArrayRawData(data)
            let result = Utf8ToString(handle_0.pointer, offset, length)
            releaseArrayRawData(handle_0)
            return result.toString()
        }
    }
    public static func _StdStringToString(cstring: UInt64): String {
        unsafe {
            let result = StdStringToString(cstring)
            return result.toString()
        }
    }
    public static func _CallCallback(callbackKind: Int32, args: ArrayList<UInt8>, argsSize: Int32): Unit {
        unsafe {
            let handle_1 = acquireArrayRawData(args.toArray())
            CallCallback(callbackKind, handle_1.pointer, argsSize)
            releaseArrayRawData(handle_1)
        }
    }
    public static func _CallCallbackSync(callbackKind: Int32, args: ArrayList<UInt8>, argsSize: Int32): Unit {
        unsafe {
            let handle_1 = acquireArrayRawData(args.toArray())
            CallCallbackSync(callbackKind, handle_1.pointer, argsSize)
            releaseArrayRawData(handle_1)
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
    public static func _LoadVirtualMachine(arg0: Int32, arg1: String, arg2: String): Int32 {
        unsafe {
            let arg1 =  LibC.mallocCString(arg1)
            let arg2 =  LibC.mallocCString(arg2)
            let result = LoadVirtualMachine(arg0, arg1, arg2)
            LibC.free(arg1)
            LibC.free(arg1)
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
            LibC.free(appUrl)
            return result
        }
    }
    public static func _EmitEvent(eventType: Int32, target: Int32, arg0: Int32, arg1: Int32): Unit {
        unsafe {
            EmitEvent(eventType, target, arg0, arg1)
        }
    }
    public static func _StringData(ptr: KPointer, data: Array<UInt8>, arg2: Int32): Unit {
        unsafe {
            let handle_1 = acquireArrayRawData(data)
            StringData(ptr, handle_1.pointer, arg2)
            releaseArrayRawData(handle_1)
        }
    }
}