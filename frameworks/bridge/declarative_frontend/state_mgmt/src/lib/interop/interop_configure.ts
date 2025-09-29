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

class InteropConfigureStateMgmt {
    private static interopInUse_: boolean = false;

    public static needsInterop(): boolean {
        return this.interopInUse_;
    }

    public static openInterop(): void {
        this.interopInUse_ = true;
    }
    
    public static closeInterop(): void {
        this.interopInUse_ = false;
    }
}

function openInterop(): void {
    InteropConfigureStateMgmt.openInterop();
}

function closeInterop(): void {
    InteropConfigureStateMgmt.closeInterop();
}