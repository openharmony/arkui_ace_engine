/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import { FrameNode, NodeContent } from '@ohos.arkui.node';

type XComponentContextStatus = {
  hasDraw: boolean,
  hasChangeColor: boolean
};

export const createNativeNode: (content: NodeContent, tag: string) => void;

export const getStatus: (tag?: string) => XComponentContextStatus;

export const drawPattern: (tag?: string) => void;

export const bindNode: (id: string, node: FrameNode) => void;

export const unbindNode: (id: string) => void;

export const setFrameRate: (id: string, min: number, max: number, expected: number) => void;

export const setNeedSoftKeyboard: (id: string, needSoftKeyboard: boolean) => void;

export const initialize: (id: string) => void;

export const finalize: (id: string) => void;

export const drawStar: (id: string) => void;

export const getStatusForSurfaceHolder: (node: FrameNode) => XComponentContextStatus;

export const drawPatternForSurfaceHolder: (node: FrameNode) => void;
