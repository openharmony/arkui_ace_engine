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

import { ExtendableComponent } from 'stateManagement/base/extendableComponent'
import { IObservedObject, RenderIdType } from 'stateManagement/interface/iObservedObject'
import { Observe } from 'stateManagement/interface/iObserve'
import { IWatchSubscriberRegister, ISubscribedWatches, WatchIdType, WatchFuncType } from 'stateManagement/interface/iWatch'
import { IMutableStateMeta } from 'stateManagement/interface/iMutableStateMeta'
import { stateMgmtConsole } from 'stateManagement/tools/stateMgmtConsoleTrace';
import { StateMgmtFactory } from 'stateManagement/interface/iStateMgmtFactory'
import { IStateDecoratedVariable, ILinkDecoratedVariable, IObjectLinkDecoratedVariable, LinkSourcesType } from 'stateManagement/interface/iDecorators'
import { IProvideDecoratedVariable, IConsumeDecoratedVariable } from 'stateManagement/interface/iDecorators'
import { ClassA, ParentComponent_init_update_struct, ParentComponent, LinkChildComponent_init_update_struct, LinkChildComponent, linkChildComp } from 'stateManagement/utest/uiPlugin/uipluginLink1.ets'

// unit testing
import { tsuite, tcase, test, eq } from 'stateManagement/utest/lib/testFramework'

const NumberTypeValue = Type.of(1 as Number);
const BooleanTypeValue = Type.of(true as Boolean);
const StringTypeValue = Type.of("hello" as String);

export function run_link2(): Boolean {

    const tests = tsuite("@Link tests #2", () => {
        const parent = new ParentComponent(null, {});
        parent.build();

        if (!linkChildComp) {
            throw new Error("LinkChildComponent not initialized");
        }

        tcase('Test 1: LinkA assignment and verify @Link, @ObjectLink and state sync', () => {
            // reset counters
            parent.watchFuncRunCtrA = 0;
            linkChildComp!.watchFuncRunLinkA = 0

            // assign new Object first
            linkChildComp!.linkA = new ClassA('name1', 9);

            test(`@Link set parent @state correctly: parent.stateA.propB`, eq(parent.stateA.propB, 9));
            test(`on property change: parent @watch func watchFuncRunCtrA executed`, eq(parent.watchFuncRunCtrA, 1));

            test(`on property change: Child @Link @Watch func executed once`, eq(linkChildComp!.watchFuncRunLinkA, 1));
        });

        tcase('Test 2: State / Link source object property change, test @Watch', () => {
            // reset counters
            parent.watchFuncRunCtrA = 0;
            linkChildComp!.watchFuncRunLinkA = 0

            parent.stateA.propA = "state / link source changed value";
            test(`@Link value changed: of linkChildComp!.linkA.propA value changed`, eq(linkChildComp?.linkA.propA, "state / link source changed value"));
            test(`@Link source, i.e. parent.stateA.propA, value change by link`, eq(parent.stateA.propA, "state / link source changed value"));

            test(`@Observe obj property changed in source: parent @watch func watchFuncRunCtrA executed once`, eq(parent.watchFuncRunCtrA, 1));
            test(`@Observe obj property change in source: Child @Link @Watch func executed once`, eq(linkChildComp!.watchFuncRunLinkA, 1));
        });


        tcase('Test 3: LinkA object property change, test @Watch', () => {
            // reset counters
            parent.watchFuncRunCtrA = 0;
            linkChildComp!.watchFuncRunLinkA = 0

            linkChildComp!.linkA.propA = "link changed value";
            test(`childComp1!.linkA.propA value changed`, eq(linkChildComp?.linkA.propA, "link changed value"));
            test(`@Link source, i.e. parent.stateA.propA, value change by link`, eq(parent.stateA.propA, "link changed value"));
            test(`@Observe obj property change in link: parent @watch func watchFuncRunCtrA executed once`, eq(parent.watchFuncRunCtrA, 1));
            test(`@Observe obj property change: Child @Link @Watch func executed once`, eq(linkChildComp!.watchFuncRunLinkA, 1));
        });
    });

    tests();
    return true;

}
