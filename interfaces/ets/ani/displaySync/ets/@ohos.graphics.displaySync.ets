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

import { ExpectedFrameRateRange } from './arkui.component.common'

export namespace displaySync {
  loadLibrary("display_sync_ani")

  export class IntervalInfo {
    _timestamp: number;
    _targetTimestamp: number;

    public get timestamp(): number {
      return this._timestamp;
    }

    public get targetTimestamp(): number {
      return this._targetTimestamp;
    }

    public set timestamp(value: number) {
      this._timestamp = value;
    }

    public set targetTimestamp(value: number) {
      this._targetTimestamp = value;
    }

    constructor(timestamp: number, targetTimestamp: number) {
        this._timestamp = timestamp;
        this._targetTimestamp = targetTimestamp;
    }
  }

  export native function create(): DisplaySync;

  class Cleaner {
    private ptr: long = 0;
    constructor(ptr: long) {
        this.ptr = ptr;
    }
    native clean(): void;
  }

  export function callback(cleaner: Cleaner): void {
      cleaner.clean()
  }

  let destroyRegister = new FinalizationRegistry<Cleaner>(callback)
  let unregisterToken = new object()

  class DisplaySync {
    displaySync: long = 0;
    private cleaner: Cleaner | null = null;
    constructor(result: long) {
        if (this.displaySync == 0) {
            this.displaySync = result;
        }
        this.registerCleaner(this.displaySync)
    }

    registerCleaner(ptr: long): void {
        this.cleaner = new Cleaner(ptr)
        destroyRegister.register(this, this.cleaner!, unregisterToken);
    }
    unregisterCleaner(): void {
        destroyRegister.unregister(unregisterToken);
    }

    public native setExpectedFrameRateRange(rateRange: ExpectedFrameRateRange) : void;
    public native on(callbackType: string, callback: (intervalInfo: IntervalInfo) => void): void;
    public native off(callbackType: string, callback?: (intervalInfo: IntervalInfo) => void): void;
    public native start(): void;
    public native stop(): void;
    public native clean(): void;
  }
}

