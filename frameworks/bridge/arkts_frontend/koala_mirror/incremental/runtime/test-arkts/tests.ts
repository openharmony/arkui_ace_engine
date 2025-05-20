/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

import { suite } from "@koalaui/harness"
import { __ARKTEST__ as Easing } from "./animation/Easing.test"
import { __ARKTEST__ as MarkableQueue } from "./common/MarkableQueue.test"
import { __ARKTEST__ as bind } from "./memo/bind.test"
import { __ARKTEST__ as changeListener } from "./memo/changeListener.test"
import { __ARKTEST__ as contextLocal } from "./memo/contextLocal.test"
import { __ARKTEST__ as remember } from "./memo/remember.test"
import { __ARKTEST__ as repeat } from "./memo/repeat.test"
import { __ARKTEST__ as Journal } from "./states/Journal.test"
import { __ARKTEST__ as state_basics } from "./states/state_basics.test"
import { __ARKTEST__ as State } from "./states/State.test"
import { __ARKTEST__ as TreeNode } from "./tree/TreeNode.test"
import { __ARKTEST__ as TreePath } from "./tree/TreePath.test"

suite("runtime", () => {
    Array.of<string>(Easing, MarkableQueue, bind, changeListener, contextLocal, remember, repeat, Journal, /* state_basics,  */State, TreeNode, TreePath)
})
