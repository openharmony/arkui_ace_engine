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

import { StateMgmtFactory, IMonitorPathInfo, IMonitorable } from '../base/stateMgmtFactory';
import { StateMgmtConsole } from '../tools/stateMgmtDFX';

class TestMakeMonitorOptions implements IMonitorable {
    private _counter: number = 0;
    private _monitorDecorator?: IMonitorable;
    private _monitorFunctionRunCount: number = 0;

    constructor() {
        this._monitorDecorator = StateMgmtFactory.makeMonitor(
            new Array<IMonitorPathInfo>(
                StateMgmtFactory.makeMonitorPath('counter', () => {
                    return this._counter;
                })
            ),
            (m: IMonitor) => {
                this._monitorFunctionRunCount++;
                StateMgmtConsole.log(`Monitor function run count: ${this._monitorFunctionRunCount}`);
            },
            {
                owner: this,
                functionName: 'testMonitor'
            }
        );
    }

    get counter(): number {
        return this._counter;
    }

    set counter(value: number) {
        this._counter = value;
    }
}

export { TestMakeMonitorOptions };
