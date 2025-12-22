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

import { AppStorageV2 } from '../storage/appStorageV2'
import { tsuite, tcase, test, eq, not_eq } from './lib/testFramework'

class ClassA {
    propA: string = "test";
}

class ClassB {
    propB: number = 500;
}

class ClassIB implements InfB {
    propB: number = 500;
}

interface InfB {
    propB: number;
}

export function run_app_storage_v2_simple(): Boolean {
    const ClassATypeValue = Type.of(new ClassA());
    const ClassBTypeValue = Type.of(new ClassB());
    const ClassIBTypeValue = Type.of(new ClassIB());
    const InfBType = Type.of({ propB: 8 } as InfB)

    const ttest = tsuite("AppStorageV2 API - simple") {
        tcase("connect, delete different ttypes") {
            let valA1 = AppStorageV2.connect<ClassA>(
                ClassATypeValue, "ca", () => { return new ClassA; })
            let valA2 = AppStorageV2.connect<ClassA>(
                ClassATypeValue, "ca", () => { return new ClassA; })
            let valA3 = AppStorageV2.connect<ClassA>(
                ClassATypeValue, "ca3", () => { return new ClassA; })

            test("ClassA type: has check", eq(valA1, valA2));
            test("ClassA propA: has check", eq(valA1?.propA, valA2?.propA));
            test("ClassA type: not eq", not_eq(valA1, valA3));

            AppStorageV2.remove("ca");
            AppStorageV2.remove("ca3");

            let detected = false;
            try {
                let valAD = AppStorageV2.connect<ClassA>(ClassATypeValue, "ca")
            } catch (e) {
                detected = true;
            } finally {
                test(`Connect to missing key - Exception detected`, detected);
            }

            // Access with the wrong type
            detected = false;
            try {
                let valAx = AppStorageV2.connect<ClassB>(ClassBTypeValue, "ca3")
            } catch (e) {
                detected = true;
            } finally {
                test(`Access with wrong type - Exception detected`, detected);
            }

            let valB1 = AppStorageV2.connect<ClassB>(
                ClassBTypeValue, "keyb", () => { return new ClassB; })
            let valB2 = AppStorageV2.connect<ClassB>(
                ClassBTypeValue, "keyb", () => { return new ClassB; })
            let valB3 = AppStorageV2.connect<ClassB>(
                ClassBTypeValue, "keyb3", () => { return new ClassB; })

            test("ClassA type: has check", eq(valB1, valB2));
            test("ClassA propA: has check", eq(valB1?.propB, valB2?.propB));
            test("ClassA type: not eq", not_eq(valB1, valB3));

            AppStorageV2.remove("keyb");
            AppStorageV2.remove("keyb3");
    
            // Check that we can get Class that implements interface
            // as an interface, not as a class
            let valCIB1 = AppStorageV2.connect<ClassIB>(
                ClassIBTypeValue, "keycib", () => { return new ClassIB; })

            // Access via interface
            // test below **fails**
            // Even tough ClassIB implements interface InfB
            // It looks that we have some dynamic type name generated
            // uipluginAppStorageV2.gensym%%_62
            // So InfBType in reality is type of interface instance
            detected = false;
            try {
                let valIB1 = AppStorageV2.connect<InfB>(InfBType, "keycib")
            } catch (e) {
                detected = true;
            } finally {
                test(`Access Access via interface - Exception detected`, detected);
            }

            let valInfB = AppStorageV2.connect<InfB>(
                InfBType, "keyinfb", () => {return { propB: 8 } as InfB;});
            test(`Access Access via interface InfB`, not_eq(valInfB, undefined));

            AppStorageV2.remove("keycib");
            AppStorageV2.remove("keyinfb");
        }
    }

    ttest();
    return true;
}
