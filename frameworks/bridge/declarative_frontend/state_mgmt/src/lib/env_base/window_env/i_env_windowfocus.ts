/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES ORWARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * Indicates whether the window currently has input focus.
 * Input focus means the window receives keyboard and pointer events.
 */
interface UIEnvFocus {
  isFocused: boolean;
}

/**
 * Indicates whether the window is visually highlighted or active.
 * Visual highlight indicates the window is the top window in split screen or other multi-window scenarios.
 */
interface UIEnvHighlight {
  isHighlighted: boolean;
}

// WindowFocusedEnv decorated by @ObservedV2 used in Env.
// Provided by Platform Environment Provider.
declare class WindowFocusedEnv implements IEnvironmentValue<UIEnvFocus> {
  constructor(context: UIContext);
  value: UIEnvFocus;
  update(): void;
  destroy(): void;
}

// WindowHighlightedEnv decorated by @ObservedV2 used in Env.
// Provided by Platform Environment Provider.
declare class WindowHighlightedEnv implements IEnvironmentValue<UIEnvHighlight> {
  constructor(context: UIContext);
  value: UIEnvHighlight;
  update(): void;
  destroy(): void;
}
