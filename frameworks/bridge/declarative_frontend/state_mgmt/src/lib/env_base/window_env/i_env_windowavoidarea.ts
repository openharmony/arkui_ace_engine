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

interface Rect {
  left: number;
  top: number;
  width: number;
  height: number;
}

interface AvoidArea {
  visible: boolean;
  leftRect: Rect;
  topRect: Rect;
  rightRect: Rect;
  bottomRect: Rect;
}

interface UIEnvAvoidArea {
  statusBar: AvoidArea;
  cutout: AvoidArea;
  keyboard: AvoidArea;
  navigationIndicator: AvoidArea;
}

// WindowAvoidAreaPxEnv decorated by @ObservedV2 used in Env.
// Provided by Platform Environment Provider.
declare class WindowAvoidAreaPxEnv implements IEnvironmentValue<UIEnvAvoidArea> {
  constructor(context: UIContext);
  statusBar: AvoidArea;
  cutout: AvoidArea;
  keyboard: AvoidArea;
  navigationIndicator: AvoidArea;

  value: UIEnvAvoidArea;
  update(): void;
  destroy(): void;
}

// WindowAvoidAreaVpEnv decorated by @ObservedV2 used in Env.
// Provided by Platform Environment Provider.
declare class WindowAvoidAreaVpEnv implements IEnvironmentValue<UIEnvAvoidArea> {
  constructor(context: UIContext);
  statusBar: AvoidArea;
  cutout: AvoidArea;
  keyboard: AvoidArea;
  navigationIndicator: AvoidArea;

  value: UIEnvAvoidArea;
  update(): void;
  destroy(): void;
}