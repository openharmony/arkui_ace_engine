/*
* Copyright (C) 2026 Huawei Device Co., Ltd.
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

// 引用测试用例文件
import { UipluginStateTest } from "./uipluginState.test.ets";
import { StateDecoratedVariableTest } from "./stateDecoratedVariable.test.ets";

export default function testsuite() {
    UipluginStateTest();
    StateDecoratedVariableTest();
}