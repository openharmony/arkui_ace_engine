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

interface CustomDialogControllerConstructorArg {
  builder: () => void; // arg MUST contain a builder function
  cancel?: () => void; // arg MAY contain a cancel function
}

/**
 * NativeCustomDialogController aka JSNativeCustomDialogController C++ class exposed to JS
 * 
 *  all definitions in this file are framework internal
 */
declare class NativeCustomDialogController {
  constructor(arg: CustomDialogControllerConstructorArg, view: ViewPU);
  open(): void;
  close(): void;
}
