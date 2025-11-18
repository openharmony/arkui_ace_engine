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
'use static';
import hiTraceMeter from '@ohos.hiTraceMeter';
import { StateModel } from './StateModel';


export class TimeHelper {
  testCaseName: string = ''
  startTime: number = 0;

  constructor(testCaseName: string) {
    this.startTime = 0;
    this.testCaseName = testCaseName
  }

  printTime(isStart: boolean): boolean {
    let name: string = `testCaseName : ${this.testCaseName}`
    isStart ? hiTraceMeter.startTrace(name, 1024) : hiTraceMeter.finishTrace(name, 1024);
    return true;
  }

  printAttributeTime(isStart: boolean): boolean {
    let name: string = `testAttributeCaseName : ${this.testCaseName}`
    isStart ? hiTraceMeter.startTrace(name, 1024) : hiTraceMeter.finishTrace(name, 1024);
    return true;
  }

  printStateTime(isStart: boolean,stateModel: StateModel): boolean {
    let name: string =
      `testStateV1CaseName : ${this.testCaseName} & isBindUI: ${stateModel.isBindUI} & stateType: ${stateModel.getStateType}`;
    isStart ? hiTraceMeter.startTrace(name, 1024) : hiTraceMeter.finishTrace(name, 1024);
    return true;
  }
  printReuseTime(isStart: boolean): boolean {
    let name: string = `testComponentReuseName : ${this.testCaseName}`
    isStart ? hiTraceMeter.startTrace(name, 1024) : hiTraceMeter.finishTrace(name, 1024);
    return true;
  }
  printNodeTime(isStart: boolean): boolean {
    let name: string = `testNodeCaseName : ${this.testCaseName}`
    isStart ? console.time(name) : console.timeEnd(name);
    isStart ? hiTraceMeter.startTrace(name, 1024) : hiTraceMeter.finishTrace(name, 1024);
    return true;
  }
  printAttrTime(isStart: boolean): boolean {
    let name: string = `testNodeAttrCaseName : ${this.testCaseName}`
    isStart ? console.time(name) : console.timeEnd(name);
    isStart ? hiTraceMeter.startTrace(name, 1024) : hiTraceMeter.finishTrace(name, 1024);
    return true;
  }
}
