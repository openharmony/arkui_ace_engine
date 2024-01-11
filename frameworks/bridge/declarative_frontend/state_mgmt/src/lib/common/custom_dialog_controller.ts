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
class CustomDialogController extends NativeCustomDialogController {
  private builder_: () => void; // hold builder to kill root (builder) cycle dependency (view-->controller-->builder-->view)
  private cancel_?: () => void;
  private view_: ViewPU;

  constructor(arg: CustomDialogControllerConstructorArg, view: ViewPU) {
    super(arg, view);
    this.builder_ = arg.builder;
    this.cancel_ = arg.cancel;
    this.view_ = view;
  }
}
