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


export interface ExpectedFrameRateRange {
  min: number,
  max: number,
  expected: number,
}

export class IntervalInfo {
    timestamp: long;
    targetTimestamp: long;

    constructor(timestamp: long, targetTimestamp: long) {
        this.timestamp = timestamp;
        this.targetTimestamp = targetTimestamp;
    }
}

export default class DisplaySync {
    static { loadLibrary("display_sync_ani") }
    static native create(): DisplaySyncResult;
}

export interface DisplaySyncResult {
    setExpectedFrameRateRange(rateRange: ExpectedFrameRateRange) : void;
    on(callbackType: string, callback: (intervalInfo: IntervalInfo) => void): void;
    off(callbackType: string, callback?: (intervalInfo: IntervalInfo) => void): void;
    start(): void;
    stop(): void;
}

class DisplaySyncResultInner implements DisplaySyncResult {
    displaySync: long = 0
    constructor(result: long) {
        if (this.displaySync == 0) {
            this.displaySync = result;
        }
    }

    public native setExpectedFrameRateRange(rateRange: ExpectedFrameRateRange) : void;
    public native on(callbackType: string, callback: (intervalInfo: IntervalInfo) => void): void;
    public native off(callbackType: string, callback?: (intervalInfo: IntervalInfo) => void): void;
    public native start(): void;
    public native stop(): void;
}