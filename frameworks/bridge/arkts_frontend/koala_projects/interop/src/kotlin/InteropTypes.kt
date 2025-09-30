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

package koalaui.interop

public typealias KPointer = Long
public typealias pointer = KPointer
public typealias KByte = UByte
public typealias KBoolean = Byte
public typealias KShort = Short
public typealias KUShort = UShort
public typealias KInt = Int
public typealias KUInt = UInt
public typealias KLong = Long
public typealias KULong = ULong
public typealias KFloat = Float
public typealias KDouble = Double
public typealias KStringPtr = String
public typealias ArrayBuffer = UByteArray
public typealias KSerializerBuffer = KPointer
public typealias KUint8ArrayPtr = UByteArray
public val nullptr: Long = 0
public class KInteropReturnBuffer(val length: KInt, val data: KPointer) {}
