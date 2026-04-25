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

export type CompatibleStateChangeCallback<T> = (value: T) => void;

export function isDynamicObject<T>(value: T): boolean {
    return false;
}

export function getObservedObject<T>(value: T, deep?: boolean): T {
    return value;
}

export function getV2ObservedObject<T>(value: T): T {
    return value;
}

export function staticStateBindObservedObject<T>(
    value: T,
    onPropertyChange?: () => void,
    onTrackPropertyRead?: (readPropName: string, isTracked: boolean) => void,
    onTrackPropertyChange?: (readPropName: string) => void
): T {
    return value;
}

export function enableCompatibleObservedV2ForStaticMeta<T>(value: T): T {
    return value;
}
