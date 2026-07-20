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

// entry/src/main/cpp/types/libentry/Index.d.ts

export const createNativeRoot: (content: Object) => void;
export const destroyNativeRoot: () => void;
export const createNativeNode: (content: Object) => void;
export const createNativeNodeForGesture: (content: Object) => void;
export const createNativeNodeForLongPressAndSwipe: (content: Object) => void;
export const createNativeNodeForLongPressAndFlick: (content: Object) => void;
export const createNativeNodeForSwipeAndPinchExclusive: (content: Object) => void;