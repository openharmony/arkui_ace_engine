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
export interface InfoItem {
  name: string;
  isAnimated?: boolean;
  operation: number;
}

export enum InfoIndex{
  InterceptionWillFrom = 0,
  InterceptionWillTo = 1,
  InterceptionDidFrom = 2,
  InterceptionDidTo = 3
}

export class Recorder {
  static recorder: Recorder = new Recorder();
  infoArray: Array<InfoItem> = new Array<InfoItem>();

  static getInstance(): Recorder {
    return Recorder.recorder;
  }

  setInfo(info: NavDestinationContext | "navBar", index: number) {
    // if (typeof info === "string") {
    //   this.infoArray.splice(index, 0, {name: "navBar"})
    // } else {
    //   this.infoArray.splice(index, 0, )
    // }

  }
}