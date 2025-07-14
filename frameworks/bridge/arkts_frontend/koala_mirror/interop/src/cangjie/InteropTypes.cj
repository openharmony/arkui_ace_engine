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
package Interop

import std.collection.*

public type KPointer = UInt64
public type KFloat = Float32
public type pointer = KPointer
public type KInt = Int32
public type KLong = Int64
public type KStringPtr = String
public type ArrayBuffer = ArrayList<UInt8>
public type KSerializerBuffer = pointer
public const nullptr: UInt64 = 0
@C
public struct KInteropReturnBuffer {
  public var length: Int32
  public var data: CPointer<UInt8>
  public var dispose: CPointer<CFunc<(CPointer<Unit>, Int32) -> Unit>>
  init (length: Int32, data: CPointer<UInt8>, dispose: CPointer<CFunc<(CPointer<Unit>, Int32) -> Unit>>) {
    this.length = length
    this.data = data
    this.dispose = dispose
  }
}