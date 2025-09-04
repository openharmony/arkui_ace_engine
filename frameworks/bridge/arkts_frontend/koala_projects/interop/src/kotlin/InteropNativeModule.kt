/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

@file:OptIn(ExperimentalForeignApi::class)

package koalaui.interop

import kotlinx.cinterop.*
import platform.posix.memcpy

import cinterop.interop_native_module.*

public class InteropNativeModule {
    companion object {
        public fun callCallbackFromNative(id: Int, args: KSerializerBuffer, length: Int): Int {
            // Improve:
            println("callCallbackFromNative: $id")
            return 0
        }
        public fun _GetGroupedLog(index: Int): KPointer {
            return kotlin_GetGroupedLog(index).toLong()
        }
        public fun _StartGroupedLog(index: Int): Unit {
            kotlin_StartGroupedLog(index)
        }
        public fun _StopGroupedLog(index: Int): Unit {
            kotlin_StopGroupedLog(index)
        }
        public fun _AppendGroupedLog(index: Int, message: String): Unit {
            kotlin_AppendGroupedLog(index, message)
        }
        public fun _PrintGroupedLog(index: Int): Unit {
            kotlin_PrintGroupedLog(index)
        }
        public fun _GetStringFinalizer(): KPointer {
            return kotlin_GetStringFinalizer().toLong()
        }
        public fun _InvokeFinalizer(ptr1: KPointer, ptr2: KPointer): Unit {
            kotlin_InvokeFinalizer(ptr1.toCPointer<CPointed>()!!, ptr2.toCPointer<CPointed>()!!)
        }
        public fun _IncrementNumber(value: Double): Double {
            return kotlin_IncrementNumber(value)
        }
        public fun _GetPtrVectorElement(ptr1: KPointer, arg: Int): KPointer {
            return kotlin_GetPtrVectorElement(ptr1.toCPointer<CPointed>()!!, arg).toLong()
        }
        public fun _StringLength(ptr1: KPointer): Int {
            return kotlin_StringLength(ptr1.toCPointer<CPointed>()!!)
        }
        public fun _StringData(ptr1: KPointer, array: KUint8ArrayPtr, arrayLength: Int): Unit {
            if (arrayLength <= 0) {
                return
            }
            array.usePinned {
                kotlin_StringData(ptr1.toCPointer<CPointed>()!!, it.addressOf(0), arrayLength)
            }
        }
        public fun _StringMake(str1: String): KPointer {
            return kotlin_StringMake(str1).toLong()
        }
        public fun _GetPtrVectorSize(ptr1: KPointer): Int {
            return kotlin_GetPtrVectorSize(ptr1.toCPointer<CPointed>()!!)
        }
        public fun _ManagedStringWrite(str1: String, array: KPointer, offset: Int): Int {
            val ptrWithOffset = (array + offset).toCPointer<CPointed>()!!
            val utf8Str = str1.cstr
            val byteCount = utf8Str.size
            memScoped {
                memcpy(ptrWithOffset, utf8Str.ptr, byteCount.convert())
            }
            return byteCount
        }
        public fun _NativeLog(str1: String): Unit {
            kotlin_NativeLog(str1)
        }
        public fun _Utf8ToString(data: KPointer, offset: Int, length: Int): String {
            val ptrWithOffset = (data + offset).toCPointer<ByteVar>()!!
            return ptrWithOffset.toKString()
        }
        public fun _StdStringToString(cstring: KPointer): String {
            return kotlin_StdStringToString(cstring.toCPointer<CPointed>()!!)?.toKString() ?: ""
        }
        public fun _CheckCallbackEvent(buffer: KSerializerBuffer, bufferLength: Int): Int {
            return kotlin_CheckCallbackEvent(buffer.toCPointer<CPointed>()!!, bufferLength)
        }
        public fun _HoldCallbackResource(resourceId: Int): Unit {
            kotlin_HoldCallbackResource(resourceId)
        }
        public fun _ReleaseCallbackResource(resourceId: Int): Unit {
            kotlin_ReleaseCallbackResource(resourceId)
        }
        public fun _CallCallback(apiKind: Int, callbackKind: Int, args: KSerializerBuffer, argsSize: Int): Unit {
            kotlin_CallCallback(apiKind, callbackKind, args.toCPointer<CPointed>()!!, argsSize)
        }
        public fun _CallCallbackSync(apiKind: Int, callbackKind: Int, args: KSerializerBuffer, argsSize: Int): Unit {
            kotlin_CallCallbackSync(apiKind, callbackKind, args.toCPointer<CPointed>()!!, argsSize)
        }
        public fun _CallCallbackResourceHolder(holder: KPointer, resourceId: Int): Unit {
            kotlin_CallCallbackResourceHolder(holder.toCPointer<CPointed>()!!, resourceId)
        }
        public fun _CallCallbackResourceReleaser(releaser: KPointer, resourceId: Int): Unit {
            kotlin_CallCallbackResourceReleaser(releaser.toCPointer<CPointed>()!!, resourceId)
        }
        public fun _LoadVirtualMachine(arg0: Int, arg1: String, arg2: String, arg3: String): Int {
            return kotlin_LoadVirtualMachine(arg0, arg1, arg2, arg3)
        }
        public fun _RunApplication(arg0: Int, arg1: Int): Boolean {
            return kotlin_RunApplication(arg0, arg1) != 0.toByte()
        }
        public fun _StartApplication(appUrl: String, appParams: String): KPointer {
            return kotlin_StartApplication(appUrl, appParams).toLong()
        }
        public fun _EmitEvent(eventType: Int, target: Int, arg0: Int, arg1: Int): String {
            return kotlin_EmitEvent(eventType, target, arg0, arg1)?.toKString() ?: ""
        }
        public fun _CallForeignVM(context: KPointer, callback: Int, data: KSerializerBuffer, length: Int): Int {
            return kotlin_CallForeignVM(context.toCPointer<CPointed>()!!, callback, data.toCPointer<CPointed>()!!, length)
        }
        public fun _SetForeignVMContext(context: KPointer): Unit {
            kotlin_SetForeignVMContext(context.toCPointer<CPointed>()!!)
        }
        public fun _RestartWith(page: String): Unit {
            kotlin_RestartWith(page)
        }
        public fun _ReadByte(data: KPointer, index: Long, length: Long): Int {
            if (index >= length) {
                error("ReadByte: index $index is equal or greater than length $length")
            }
            return data.toCPointer<UByteVar>()!!.get(index).convert()
        }
        public fun _WriteByte(data: KPointer, index: Long, length: Long, value: Int): Unit {
            if (index >= length) {
                error("WriteByte: index $index is equal or greater than length $length")
            }
            data.toCPointer<UByteVar>()!!.set(index, value.convert())
        }
        public fun _Malloc(length: Long): KPointer {
            return kotlin_Malloc(length.convert()).toLong()
        }
        public fun _GetMallocFinalizer(): KPointer {
            return kotlin_GetMallocFinalizer().toLong()
        }
        public fun _Free(data: KPointer): Unit {
            kotlin_Free(data.toCPointer<CPointed>()!!)
        }
        public fun _CopyArray(data: KPointer, length: Long, args: KUint8ArrayPtr): Unit {
            args.usePinned { pinned ->
                memcpy(data.toCPointer<CPointed>(), pinned.addressOf(0), length.convert())
            }
        }
        public fun _ReportMemLeaks(): Unit {
            kotlin_ReportMemLeaks()
        }
    }
}
