/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
import JSON from "@ohos.util.json";
export declare class JsonUtils {
    static stringify(value: object, replacer?: JSON.Transformer, space?: string | number): string;
    static parse<T>(text: string, reviver?: JSON.Transformer, options?: JSON.ParseOptions): T | undefined;
}