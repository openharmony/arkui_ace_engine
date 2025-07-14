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

public open class Tag {
    public static var UNDEFINED: Tag = Tag(101)
    public static var INT32: Tag = Tag(102)
    public static var FLOAT32: Tag = Tag(103)
    public static var STRING: Tag = Tag(104)
    public static var LENGTH: Tag = Tag(105)
    public static var RESOURCE: Tag = Tag(106)
    public static var OBJECT: Tag = Tag(107)
    public var value: Int8
    Tag (arg0: Int8) {
        value = arg0
    }
}
