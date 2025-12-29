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

import { PersistenceV2, PersistenceV2Impl, ConnectOptions, StorageDefaultCreator } from '../storage/persistenceV2'
import { tsuite, tcase, test, eq, not_eq } from './lib/testFramework'
import { StateMgmtConsole } from '../tools/stateMgmtDFX';
import { PersistentStorageMocked } from '../mock/ani_storage_mock'
import { ObserveSingleton } from '../base/observeSingleton';
import contextConstant from '@ohos.app.ability.contextConstant';

type stateMgmtConsole=StateMgmtConsole;

interface NumberInterface {
    prop: Double;
}

interface JsonSerializable {
    toJson(): jsonx.JsonElement;
}

interface JsonDeserializable {
    fromJson(json: jsonx.JsonElement): void;
}

class ConnectOptionsInst<T extends object> implements ConnectOptions<T> {
    type: Type;
    key?: string;
    defaultCreator?: StorageDefaultCreator<T>;
    areaMode?: contextConstant.AreaMode;
    constructor(ttype: Type) {
        this.type = ttype;
    }
}

const NonObservedPersonType = Type.of(new NonObservedPerson());
const NumberInterfaceType = Type.of({ prop: 5 } as NumberInterface);

class NonObservedPerson //implements JsonSerializable, JsonDeserializable
{
    public personname: string = "John Malkovich";

    public toJson(): jsonx.JsonElement {
        let se = jsonx.JsonElement.createString(this.personname);
        return se;
    }
    public fromJson(json: jsonx.JsonElement): void {
        //this.username = json.getElement("username").asString();
        this.personname = json.asString();
    }
}

export function run_persistent_storage_v2_simple(): Boolean {
    let storageBackend = new PersistentStorageMocked();

    const toJsonPerson = (person: NonObservedPerson) => {
        stateMgmtConsole.log("user1 toJson, username: " + person.personname);
        return person.toJson();
    };

    const fromJsonPerson = (json: jsonx.JsonElement): NonObservedPerson => {
        stateMgmtConsole.log("user1 fromJson, JSON: " + JSON.stringifyJsonElement(json));
        let person = new NonObservedPerson();
        person.fromJson(json);
        return person;
    };



    const ttest = tsuite("PersistenceV2Impl API ") {

    tcase("Saving non observed object to persistent storage") {
        PersistenceV2Impl.backendUpdateCountForTesting = 0;
        let key = "PersonKey";
        let person = PersistenceV2.connect<NonObservedPerson>(
            NonObservedPersonType,
            key,
            toJsonPerson,
            fromJsonPerson,
            () => new NonObservedPerson()
        )
        test("backendUpdateCount", eq(PersistenceV2Impl.backendUpdateCountForTesting, 0));
        test("Key Count 1", eq(PersistenceV2.keys().length, 1));
        ObserveSingleton.instance.updateDirty();
        PersistenceV2.remove(key);
        ObserveSingleton.instance.updateDirty();
        test("Key Count 0", eq(PersistenceV2.keys().length, 0));

        ObserveSingleton.instance.updateDirty();
        test("backendUpdateCount", eq(PersistenceV2Impl.backendUpdateCountForTesting, 1));

        test("person created", not_eq(person, undefined));
        person!.personname = "newName";

        // Trigger writing to the backend
        ObserveSingleton.instance.updateDirty();
        // Nothing was actually processed
        test("backendUpdateCount", eq(PersistenceV2Impl.backendUpdateCountForTesting, 1));

        PersistenceV2.remove(key);
    }

    }

    ttest();
    return true;
}
