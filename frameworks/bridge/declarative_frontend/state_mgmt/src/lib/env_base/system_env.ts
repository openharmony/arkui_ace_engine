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

declare enum Direction {}

class SystemEnvKey {
    keyId: string;
    constructor(keyId: string) {
        this.keyId = keyId;
    }
}

class WritableSystemEnvKey<T> extends SystemEnvKey {
    constructor(keyId: string) {
        super(keyId);
    }
}

class ReadonlySystemEnvKey<T> extends SystemEnvKey {
    constructor(keyId: string) {
        super(keyId);
    }
}

class WritableEnvKey {
    static readonly DIRECTION: WritableSystemEnvKey<Direction> = new WritableSystemEnvKey<Direction>('system.arkui.layout.direction');
    static readonly FONT_SCALE: WritableSystemEnvKey<number> = new WritableSystemEnvKey<number>('system.arkui.fontScale');
}

class ReadonlyEnvKey {
  static readonly WINDOW_AVOID_AREA: ReadonlySystemEnvKey<UIEnvAvoidArea> = new ReadonlySystemEnvKey<UIEnvAvoidArea>('system.window.avoidarea');
  static readonly WINDOW_AVOID_AREA_PX: ReadonlySystemEnvKey<UIEnvAvoidArea> = new ReadonlySystemEnvKey<UIEnvAvoidArea>('system.window.avoidarea.px');
  static readonly WINDOW_SIZE: ReadonlySystemEnvKey<SizeInVp> = new ReadonlySystemEnvKey<SizeInVp>('system.window.size');
  static readonly WINDOW_SIZE_PX: ReadonlySystemEnvKey<Size> = new ReadonlySystemEnvKey<Size>('system.window.size.px');
  static readonly WINDOW_DISPLAY_ID: ReadonlySystemEnvKey<number> = new ReadonlySystemEnvKey<number>('system.window.displayid');
  static readonly WINDOW_SYSTEM_DENSITY: ReadonlySystemEnvKey<number> = new ReadonlySystemEnvKey<number>('system.window.density.system');
  static readonly WINDOW_IS_FOCUSED: ReadonlySystemEnvKey<boolean> = new ReadonlySystemEnvKey<boolean>('system.window.focused');
  static readonly WINDOW_IS_HIGHLIGHTED: ReadonlySystemEnvKey<boolean> = new ReadonlySystemEnvKey<boolean>('system.window.highlighted');
}