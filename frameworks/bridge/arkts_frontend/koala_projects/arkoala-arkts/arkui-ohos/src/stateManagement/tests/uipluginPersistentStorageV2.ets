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

import { PersistenceV2, PersistenceV2Impl, IConnectOptions, StorageDefaultCreator, AreaMode } from 'production-path/storage/v2_persistence.ts'
import { tsuite, tcase, test, eq, not_eq } from 'stateManagement/utest/lib/testFramework'
import { IMutableStateMeta } from 'stateManagement/interface/iMutableStateMeta'
import { IObservedObject, RenderIdType } from 'stateManagement/interface/iObservedObject'
import { IWatchSubscriberRegister, ISubscribedWatches, WatchIdType, WatchFuncType } from 'stateManagement/interface/iWatch'
import { stateMgmtConsole } from 'stateManagement/tools/stateMgmtConsoleTrace'
import { StateMgmtFactory } from 'stateManagement/interface/iStateMgmtFactory'
import { Observe } from 'stateManagement/interface/iObserve'
import { PersistentStorageMocked } from 'stateManagement/mock/ani_storage_mock.ets'
import { ObserveSingleton } from 'stateManagement/base/observeSingleton.ets';
import { UIUtils } from '../../sdk/uiutils.ets';
import { TypeChecker } from 'stateManagement/tools/typeChecker.ets'

interface NumberInterface {
    prop: Double;
}

interface JsonSerializable {
    toJson(): jsonx.JsonElement;
}

interface JsonDeserializable {
    fromJson(json: jsonx.JsonElement): void;
}

class ConnectOptions<T extends object> implements IConnectOptions<T> {
    ttype: Type;
    key?: string;
    defaultCreator?: StorageDefaultCreator<T>;
    areaMode?: AreaMode;
    constructor(ttype: Type) {
        this.ttype = ttype;
    }
}

/*
@Observed class User {
    username: string;
}
*/
const UserTypeValue = Type.of(new User(""));
const NonObservedPersonType = Type.of(new NonObservedPerson());
const NumberInterfaceType = Type.of({ prop: 5 } as NumberInterface);

class User implements IObservedObject, IWatchSubscriberRegister, JsonSerializable, JsonDeserializable {

    constructor(propA: string) {
        stateMgmtConsole.log(`User CTOR: ${propA}`);
        this.__backing_username = propA;
    }

    private readonly subscribedWatches_: ISubscribedWatches = StateMgmtFactory.makeSubscribedWatches();

    public addWatchSubscriber(watchId: WatchIdType): void {
        this.subscribedWatches_.addWatchSubscriber(watchId);
    }
    public removeWatchSubscriber(watchId: WatchIdType): boolean {
        return this.subscribedWatches_.removeWatchSubscriber(watchId);
    }
    protected executeOnSubscribingWatches(changedPropName: string): void {
        this.subscribedWatches_.executeOnSubscribingWatches(changedPropName);
    }

    // IObservedObject interface
    // @JsonIgnore
    private ____V1RenderId: RenderIdType = 0;
    public setV1RenderId(renderId: RenderIdType): void {
        this.____V1RenderId = renderId;
    }

    protected conditionalAddRef(meta: IMutableStateMeta): void {
        if (Observe.shouldAddRef(this.____V1RenderId)) {
            meta.addRef();
        }
    }

    // @Track name : string;
    private __backing_username: string;

    // @JsonIgnore
    private readonly __meta_username: IMutableStateMeta
        = StateMgmtFactory.makeMutableStateMeta();

    public get username(): string {
        stateMgmtConsole.log(`User: get @Track username`);
        this.conditionalAddRef(this.__meta_username);
        return this.__backing_username
    }
    public set username(newValue: string) {
        if (this.__backing_username !== newValue) {
            stateMgmtConsole.log(`User: set @Track username`);
            this.__backing_username = newValue;
            this.__meta_username.fireChange();
            this.executeOnSubscribingWatches("username");
        }
    }

    public toJson(): jsonx.JsonElement {
        //let elem: jsonx.JsonElement = new jsonx.JsonElement();
        let se = jsonx.JsonElement.createString(this.username);
        //console.error("user.tJson... setElement")
        //elem.setElement("username", se);
        return se;
    }

    public fromJson(json: jsonx.JsonElement): void {
        //this.username = json.getElement("username").asString();
        this.username = json.asString();
    }

    public getId(): string {
        return this.username;
    }
}

class NonObservedPerson implements JsonSerializable, JsonDeserializable {
    public personname: string = "John Malkovich";

    public toJson(): jsonx.JsonElement {
        //let elem: jsonx.JsonElement = new jsonx.JsonElement();
        let se = jsonx.JsonElement.createString(this.personname);
        //console.error("user.tJson... setElement")
        //elem.setElement("username", se);
        return se;
    }
    public fromJson(json: jsonx.JsonElement): void {
        //this.username = json.getElement("username").asString();
        this.personname = json.asString();
    }
}


export function run_persistent_storage_v2(): Boolean {
    let storageBackend = new PersistentStorageMocked();

    const toJsonUser = (user: User) => {
        stateMgmtConsole.log("user1 toJson, username:" + user.getId());
        return user.toJson();
    };

    const fromJsonUser = (json: jsonx.JsonElement): User => {
        stateMgmtConsole.log("user1 fromJson, JSON: " + JSON.stringifyJsonElement(json));
        let user = new User("default");
        user.fromJson(json);
        return user;
    };

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

    const toJsonNumberInterface = (objLit: NumberInterface) => {
        stateMgmtConsole.log("Accesing objLit.prop, observed: " + TypeChecker.isObservedInterface(objLit));
        return jsonx.JsonElement.createDouble(objLit.prop);
    };

    const fromJsonNumberInterface = (json: jsonx.JsonElement): NumberInterface => {
        let objLit = { prop: 0 } as NumberInterface;
        objLit.prop = json.asDouble();
        return objLit;
    };

    const ttest = tsuite("PersistenceV2Impl API ") {

        PersistenceV2.configureBackend(storageBackend);

    tcase("Persistence regular - create an entry, remove an entry") {
        let userFromStorage1 = PersistenceV2.connect<User>(
            UserTypeValue,
            "userKey",
            toJsonUser,
            fromJsonUser,
            () => { return new User("defaultByCreator"); })

        let userFromStorage2 = PersistenceV2.connect<User>(
            UserTypeValue,
            "userKey",
            toJsonUser,
            fromJsonUser,
            () => { return new User("defaultCreator"); })

        let userFromStorageKey2 = PersistenceV2.connect<User>(
            UserTypeValue,
            "userKey2",
            toJsonUser,
            fromJsonUser,
            () => { return new User("defaultCreator"); })

        // Trigger writing to the back store before the start deleting
        ObserveSingleton.instance.updateDirty2();

        test("Users the same ", eq(userFromStorage1, userFromStorage2));
        test("User name  the same ", eq(userFromStorage1!.username, userFromStorage2!.username));

        let keys = PersistenceV2.keys();
        test("keys[0] 'userKey'", eq(keys[0], "userKey"));

        keys = PersistenceV2.keys();
        PersistenceV2.remove("userKey");
        keys = PersistenceV2.keys();
        test("keys size one", eq(keys.length, 1));
        PersistenceV2.remove("userKey2");
        keys = PersistenceV2.keys();
        test("keys size zero", eq(keys.length, 0));
        //test("Users is undefined ", eq( userFromStorage3 , undefined));
        //ObserveSingleton.instance.updateDirty2()
        // Cleanup
        PersistenceV2.remove("userKey");
    }

    tcase("Create persist of update") {
        let userFromStorage1 = PersistenceV2.connect<User>(
            UserTypeValue,
            "userKey",
            toJsonUser,
            fromJsonUser,
            () => { return new User("defaultByCreator"); })

        // Trigger writing to the back store
        ObserveSingleton.instance.updateDirty2();

        userFromStorage1!.username = "newName";
        PersistenceV2Impl.backendUpdateCountForTesting = 0;
        // Trigger writing to the backend
        ObserveSingleton.instance.updateDirty2();
        test("backendUpdateCount", eq(PersistenceV2Impl.backendUpdateCountForTesting, 1));
        PersistenceV2.remove("userKey");
    }

    tcase("Persist Map not supported") {
        const toJson = (user: Map<string, string>) => {
            return jsonx.JsonElement.createString("");
        };

        const fromJson = (json: jsonx.JsonElement): Map<string, string> => {
            return new Map<string, string>();
        };

        let errorTriggered = false;
        try {
            let userFromStorage1 = PersistenceV2.connect<Map<string, string>>(
                Type.of(new Map<string, string>()),
                "userKey",
                toJson,
                fromJson,
                () => { return new Map<string, string>(); })
        } catch (e) {
            errorTriggered = true;
        }
        test("Map rejected", eq(errorTriggered, true));
    }

    tcase("Persist Set not supported") {
        const toJson = (user: Set<Number>) => {
            return jsonx.JsonElement.createString("");
        };
        const fromJson = (json: jsonx.JsonElement): Set<Number> => {
            return new Set<Number>();
        };

        let errorTriggered = false;
        try {
            let userFromStorage1 = PersistenceV2.connect<Set<Number>>(
                Type.of(new Set<Number>()),
                "userKey",
                toJson,
                fromJson,
                () => { return new Set<Number>() })
        } catch (e) {
            errorTriggered = true;
        }
        test("Set rejected", eq(errorTriggered, true));
    }

    tcase("Persist with wrong key") {
        let userFromStorage = PersistenceV2.connect<User>(
            UserTypeValue,
            "userKey-",
            toJsonUser,
            fromJsonUser,
            () => { return new User("defaultByCreator"); })
        // Wrong key generates error message only
        test("Invalid key", not_eq(userFromStorage, undefined));
        // Trigger writing to the back store
        ObserveSingleton.instance.updateDirty2();
        PersistenceV2.remove("userKey-");
    }

    tcase("Persist with empty key") {
        let userFromStorage = PersistenceV2.connect<User>(
            UserTypeValue,
            "",
            toJsonUser,
            fromJsonUser,
            () => { return new User("defaultByCreator"); })
        test("Empty key", eq(userFromStorage, undefined));
    }

    tcase("Persistence Global - create an entry, remove an entry") {
        let options = new ConnectOptions<User>(UserTypeValue);
        options.key = "userKey";
        options.defaultCreator = () => { return new User("defaultByCreator") };

        let userFromStorage1 = PersistenceV2.globalConnect<User>(
            options,
            toJsonUser,
            fromJsonUser
        )

        let userFromStorage2 = PersistenceV2.globalConnect<User>(
            options,
            toJsonUser,
            fromJsonUser
        )

        options.key = "userKey2"
        let userFromStorageKey2 = PersistenceV2.globalConnect<User>(
            options,
            toJsonUser,
            fromJsonUser,
        )

        test("Users the same ", eq(userFromStorage1, userFromStorage2));
        test("User name  the same ", eq(userFromStorage1!.username, userFromStorage2!.username));

        // Trigger writing to the back store
        ObserveSingleton.instance.updateDirty2();

        let keys = PersistenceV2.keys();
        test("keys[0] 'userKey'", eq(keys[0], "userKey"));

        keys = PersistenceV2.keys();
        PersistenceV2.remove("userKey");
        keys = PersistenceV2.keys();

        test("keys size one", eq(keys.length, 1));

        PersistenceV2.remove("userKey2");
        keys = PersistenceV2.keys();

        test("keys size zero", eq(keys.length, 0));
    }

    tcase("Create/delete in Global mode in different areas.") {
        // Create new objects
        const userKeyEL1 = "userKeyEL1";
        const userKeyEL5 = "userKeyEL5";
        let options = new ConnectOptions<User>(UserTypeValue);
        options.key = userKeyEL1
        options.areaMode = AreaMode.EL1;
        options.defaultCreator = () => { return new User("defaultByCreator") };
        let userEL1 = PersistenceV2.globalConnect<User>(
            options,
            toJsonUser,
            fromJsonUser
        )

        options.key = userKeyEL5;
        options.areaMode = AreaMode.EL5;
        let userEL5 = PersistenceV2.globalConnect<User>(
            options,
            toJsonUser,
            fromJsonUser
        )
        test("Object created", not_eq(userEL1, undefined));
        test("Object created ", not_eq(userEL5, undefined));

        // Get exiting from store
        options.key = userKeyEL1
        options.areaMode = AreaMode.EL1;
        options.defaultCreator = undefined;
        let userEL1A = PersistenceV2.globalConnect<User>(
            options,
            toJsonUser,
            fromJsonUser
        )

        options.key = userKeyEL5;
        options.areaMode = AreaMode.EL5;
        options.defaultCreator = undefined;
        let userEL5A = PersistenceV2.globalConnect<User>(
            options,
            toJsonUser,
            fromJsonUser
        )

        test("Object found", not_eq(userEL1A, undefined));
        test("Object found ", not_eq(userEL5A, undefined));

        // That will actually write to the backend
        ObserveSingleton.instance.updateDirty2();
        test("Key in correct backend", eq(storageBackend.has(userKeyEL1, AreaMode.EL1), true));
        test("Key in correct backend", eq(storageBackend.has(userKeyEL1, AreaMode.EL2), false));
        test("Key in correct backend", eq(storageBackend.has(userKeyEL5, AreaMode.EL5), true));
        test("Key in correct backend", eq(storageBackend.has(userKeyEL5, AreaMode.EL1), false));

        let keys = PersistenceV2.keys();
        test("keys count is 2", eq(keys.length, 2));

        // Trigger writing to the back store
        ObserveSingleton.instance.updateDirty2();

        // Cleanup
        PersistenceV2.remove(userKeyEL1);
        PersistenceV2.remove(userKeyEL5);
        keys = PersistenceV2.keys();
        test("keys size zero", eq(keys.length, 0));
    }

    tcase("Get existing objects from Persist storage on disk") {
        // Initialize backend and then recreate PersistenceV2Impl instance.
        // **** Initialize backend ****
        // Create new objects
        const userKeyEL1 = "userKeyEL1";
        const userKeyEL5 = "userKeyEL5";
        let options = new ConnectOptions<User>(UserTypeValue);
        options.key = userKeyEL1
        options.areaMode = AreaMode.EL1;
        options.defaultCreator = () => { return new User("defaultByCreator") };
        let userEL1 = PersistenceV2.globalConnect<User>(
            options,
            toJsonUser,
            fromJsonUser
        )

        options.key = userKeyEL5;
        options.areaMode = AreaMode.EL5;
        let userEL5 = PersistenceV2.globalConnect<User>(
            options,
            toJsonUser,
            fromJsonUser
        )
        test("Object created", not_eq(userEL1, undefined));
        test("Object created ", not_eq(userEL5, undefined));

        // Trigger writing to the back store
        ObserveSingleton.instance.updateDirty2();

        // **** reset backend ****

        test("PersistenceV2Impl.instanceExists() - true", eq(PersistenceV2Impl.instanceExists(), true));
        PersistenceV2Impl.instanceReset();
        test("PersistenceV2Impl.instanceExists() - false", eq(PersistenceV2Impl.instanceExists(), false));
        PersistenceV2.configureBackend(storageBackend);

        // Get objects from the storage
        options.key = userKeyEL1
        options.areaMode = AreaMode.EL1;
        options.defaultCreator = undefined;

        let userEL1A = PersistenceV2.globalConnect<User>(
            options,
            toJsonUser,
            fromJsonUser
        )

        options.key = userKeyEL5;
        options.areaMode = AreaMode.EL5;
        options.defaultCreator = undefined;
        let userEL5A = PersistenceV2.globalConnect<User>(
            options,
            toJsonUser,
            fromJsonUser
        )
        test("Object read ", not_eq(userEL1A, undefined));
        test("Object read ", not_eq(userEL5A, undefined));
        PersistenceV2.remove(userKeyEL1);
        PersistenceV2.remove(userKeyEL5);
        let keys = PersistenceV2.keys();
        test("keys size zero", eq(keys.length, 0));
    }

    tcase("Keys clash between local and global storage") {
        PersistenceV2Impl.instanceReset();
        PersistenceV2.configureBackend(storageBackend);
        let keys = PersistenceV2.keys();
        test("keys.length'", eq(keys.length, 0));

        let userKey = "userKey"
        let options = new ConnectOptions<User>(UserTypeValue);
        options.key = userKey;
        options.defaultCreator = () => { return new User("defaultByCreator") };

        let userGlobal = PersistenceV2.globalConnect<User>(
            options,
            toJsonUser,
            fromJsonUser
        );

        let errorTriggered = false;
        try {
            let userRegular = PersistenceV2.connect<User>(
                UserTypeValue,
                userKey,
                toJsonUser,
                fromJsonUser,
                () => { return new User("defaultByCreator") }
            );
        } catch (e) {
            errorTriggered = true;
        }

        test("userGlobal created ", not_eq(userGlobal, undefined));
        test("userRegular failed", eq(errorTriggered, true));

        keys = PersistenceV2.keys();
        test("keys.length'", eq(keys.length, 1));

        PersistenceV2.remove(userKey);
        keys = PersistenceV2.keys();
        test("keys size zero", eq(keys.length, 0));
    }

    tcase("Saving non observed object to persistent storage") {
        //TODO: call save as well
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

        ObserveSingleton.instance.updateDirty2();
        test("backendUpdateCount", eq(PersistenceV2Impl.backendUpdateCountForTesting, 1));

        test("person created", not_eq(person, undefined));
        person!.personname = "newName";

        // Trigger writing to the backend
        ObserveSingleton.instance.updateDirty2();
        // Nothing was actually processed
        test("backendUpdateCount", eq(PersistenceV2Impl.backendUpdateCountForTesting, 1));

        PersistenceV2.remove(key);
    }

    tcase("Reading back non observed object from persistent storage") {
        //TODO: call save as well
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

        ObserveSingleton.instance.updateDirty2();
        test("backendUpdateCount", eq(PersistenceV2Impl.backendUpdateCountForTesting, 1));

        test("person created", not_eq(person, undefined));
        person!.personname = "newName";

        // Trigger writing to the backend
        ObserveSingleton.instance.updateDirty2();
        // Nothing was actually processed
        test("backendUpdateCount", eq(PersistenceV2Impl.backendUpdateCountForTesting, 1));

        // Reset Persistent Storage
        PersistenceV2Impl.instanceReset();
        test("PersistenceV2Impl.instanceExists() - false", eq(PersistenceV2Impl.instanceExists(), false));
        PersistenceV2.configureBackend(storageBackend);
        test("PersistenceV2Impl.instanceExists() - true", eq(PersistenceV2Impl.instanceExists(), true));

        PersistenceV2Impl.backendUpdateCountForTesting = 0;
        // Load existing
        let personB = PersistenceV2.connect<NonObservedPerson>(
            NonObservedPersonType,
            key,
            toJsonPerson,
            fromJsonPerson,
        )
        test("backendUpdateCount - 0", eq(PersistenceV2Impl.backendUpdateCountForTesting, 0));

        // Will not trigger writing to the backend
        ObserveSingleton.instance.updateDirty2();
        test("backendUpdateCount - 0", eq(PersistenceV2Impl.backendUpdateCountForTesting, 0));

        test("person created", not_eq(personB, undefined));
        test("person created", eq(personB!.personname, "John Malkovich"));
        personB!.personname = "newName";

        // Will not trigger writing to the backend
        ObserveSingleton.instance.updateDirty2();
        // Nothing was actually processed
        test("backendUpdateCount - 0", eq(PersistenceV2Impl.backendUpdateCountForTesting, 0));
        PersistenceV2.save(key)
        test("backendUpdateCount - 1", eq(PersistenceV2Impl.backendUpdateCountForTesting, 1));
        PersistenceV2.remove(key);
    }

    tcase("Connect to global data with the wrong type") {
        let keys = PersistenceV2.keys();
        test("keys.length'", eq(keys.length, 0));

        let userKey = "userKey"
        let options = new ConnectOptions<User>(UserTypeValue);
        options.key = userKey;
        options.defaultCreator = () => { return new User("defaultByCreator") };
        let userGlobal = PersistenceV2.globalConnect<User>(
            options,
            toJsonUser,
            fromJsonUser
        );

        test("userGlobal created ", not_eq(userGlobal, undefined));

        let optionsPerson = new ConnectOptions<User>(NonObservedPersonType);
        optionsPerson.key = userKey;
        optionsPerson.defaultCreator = undefined;
        let errorTriggered = false;
        try {
            let userGlobalBadType = PersistenceV2.globalConnect<User>(
                optionsPerson,
                toJsonUser,
                fromJsonUser
            );
        } catch (e) {
            errorTriggered = true;
        }

        test("Type mismatch triggered ", eq(errorTriggered, true));

        keys = PersistenceV2.keys();
        test("keys.length'", eq(keys.length, 1));

        // Trigger writing to the back store
        ObserveSingleton.instance.updateDirty2();

        PersistenceV2.remove(userKey);
        keys = PersistenceV2.keys();
        test("keys size zero", eq(keys.length, 0));
    }

    tcase("Connect to local data with the wrong type") {
        let keys = PersistenceV2.keys();
        test("keys.length'", eq(keys.length, 0));

        let userKey = "userKey"
        let userLocal = PersistenceV2.connect<User>(
            UserTypeValue,
            userKey,
            toJsonUser,
            fromJsonUser,
            () => new User("defaultByCreator")
        );

        test("local created ", not_eq(userLocal, undefined));

        let errorTriggered = false;
        try {
            let userLocalBadType = PersistenceV2.connect<NonObservedPerson>(
                NonObservedPersonType,
                userKey,
                toJsonPerson,
                fromJsonPerson
            );
        } catch (e) {
            errorTriggered = true;
        }

        test("Type mismatch triggered ", eq(errorTriggered, true));

        keys = PersistenceV2.keys();
        test("keys.length'", eq(keys.length, 1));

        // Trigger writing to the back store
        ObserveSingleton.instance.updateDirty2();

        PersistenceV2.remove(userKey);
        keys = PersistenceV2.keys();
        test("keys size zero", eq(keys.length, 0));

        let personLocalBadType = PersistenceV2.connect<NonObservedPerson>(
            NonObservedPersonType,
            userKey,
            toJsonPerson,
            fromJsonPerson,
            () => new NonObservedPerson()
        );

        // Trigger writing to the back store
        ObserveSingleton.instance.updateDirty2();

        test("local personLocalBadType created ", not_eq(personLocalBadType, undefined));
        PersistenceV2.remove(userKey);
        keys = PersistenceV2.keys();
        test("keys size is zero", eq(keys.length, 0));
    }

    tcase("Delayed write to Persist storage after connect") {
        PersistenceV2Impl.backendUpdateCountForTesting = 0;
        let userFromStorage1 = PersistenceV2.connect<User>(
            UserTypeValue,
            "userKey",
            toJsonUser,
            fromJsonUser,
            () => { return new User("defaultByCreator"); })

        test("backendUpdateCount 0 after connect", eq(PersistenceV2Impl.backendUpdateCountForTesting, 0));
        ObserveSingleton.instance.updateDirty2();
        test("backendUpdateCount 1 after update", eq(PersistenceV2Impl.backendUpdateCountForTesting, 1));

        userFromStorage1!.username = "newName";

        // Trigger writing to the backend
        ObserveSingleton.instance.updateDirty2();
        test("backendUpdateCount 2 after update", eq(PersistenceV2Impl.backendUpdateCountForTesting, 2));
        PersistenceV2.remove("userKey");
    }

    tcase("Persists non observed object literal and trigger saving on change") {

        // Test case not valid anymore, we make object literals observable
        // Ignoring
        return;

        // TODO: sort out if that is needed
        PersistenceV2Impl.backendUpdateCountForTesting = 0;
        const key = "MyInterfacePropObject";
        let obj = PersistenceV2.connect<NumberInterface>(
            NumberInterfaceType,
            key,
            toJsonNumberInterface,
            fromJsonNumberInterface,
            () => { return { prop: 100. } as NumberInterface; })
        test("obj created", not_eq(obj, undefined));
        test("backendUpdateCount 0 after update", eq(PersistenceV2Impl.backendUpdateCountForTesting, 0));

        // Trigger writing to the backend
        ObserveSingleton.instance.updateDirty2();
        test("backendUpdateCount 1 after update", eq(PersistenceV2Impl.backendUpdateCountForTesting, 1));

        // Object not observed, so nothing will be written to backend
        obj!.prop = 1000.;
        ObserveSingleton.instance.updateDirty2();
        test("backendUpdateCount still 1 after update", eq(PersistenceV2Impl.backendUpdateCountForTesting, 1));

        PersistenceV2.save(key);
        test("backendUpdateCount 2 after save", eq(PersistenceV2Impl.backendUpdateCountForTesting, 2));

        PersistenceV2.remove(key);
    }

    tcase("Persists *observed* object literal and trigger saving on change") {
        PersistenceV2Impl.backendUpdateCountForTesting = 0;

        // Initializing backstore
        const key = "MyInterfacePropObject";
        let obj = PersistenceV2.connect<NumberInterface>(
            NumberInterfaceType,
            key,
            toJsonNumberInterface,
            fromJsonNumberInterface,
            () => { return UIUtils.makeObserved({ prop: 100. } as NumberInterface); }
        )

        test("obj created", not_eq(obj, undefined));

        // Check fails!
        test("obj created prop 100", eq(obj!.prop, 100.));
        test("backendUpdateCount 0 after update", eq(PersistenceV2Impl.backendUpdateCountForTesting, 0));

        // Trigger writing to the backend
        ObserveSingleton.instance.updateDirty2();
        test("backendUpdateCount 1 after update", eq(PersistenceV2Impl.backendUpdateCountForTesting, 1));

        // Object observed, write will be triggered
        obj!.prop = 1000.;
        ObserveSingleton.instance.updateDirty2();
        test("obj prop updated to 1000.", eq(obj!.prop, 1000.));
        test("backendUpdateCount 2 after update", eq(PersistenceV2Impl.backendUpdateCountForTesting, 2));

        PersistenceV2.save(key);
        test("backendUpdateCount 3 after save", eq(PersistenceV2Impl.backendUpdateCountForTesting, 3));

        PersistenceV2.remove(key);
    }

    tcase("Reading persisted *observed* object literal and trigger saving on change") {
        PersistenceV2Impl.backendUpdateCountForTesting = 0;
        const key = "MyInterfacePropObject";
        let obj = PersistenceV2.connect<NumberInterface>(
            NumberInterfaceType,
            key,
            toJsonNumberInterface,
            fromJsonNumberInterface,
            () => ({ prop: 100.1 } as NumberInterface)
        )

        test("obj created", not_eq(obj, undefined));
        test("obj created prop 100.1", eq(obj!.prop, 100.1));
        // Trigger writing to the backend
        ObserveSingleton.instance.updateDirty2();
        test("backendUpdateCount 1 after update", eq(PersistenceV2Impl.backendUpdateCountForTesting, 1));
        obj!.prop = 100.2;
        ObserveSingleton.instance.updateDirty2();
        test("backendUpdateCount 2 after update", eq(PersistenceV2Impl.backendUpdateCountForTesting, 2));

        // Reset Persistent Storage
        PersistenceV2Impl.instanceReset();
        test("PersistenceV2Impl.instanceExists() - false", eq(PersistenceV2Impl.instanceExists(), false));
        PersistenceV2.configureBackend(storageBackend);
        test("PersistenceV2Impl.instanceExists() - true", eq(PersistenceV2Impl.instanceExists(), true));

        let objFromDisk = PersistenceV2.connect<NumberInterface>(
            NumberInterfaceType,
            key,
            toJsonNumberInterface,
            fromJsonNumberInterface
        )

        PersistenceV2Impl.backendUpdateCountForTesting = 0;
        test("objFromDisk restored created", not_eq(objFromDisk, undefined));
        test("objFromDisk prop 100.2", eq(objFromDisk!.prop, 100.2));
        // Object observed, write will be triggered
        objFromDisk!.prop = 1000.1;
        ObserveSingleton.instance.updateDirty2();
        test("objFromDisk prop updated to 1000.1", eq(objFromDisk!.prop, 1000.1));
        test("backendUpdateCount 1 after update", eq(PersistenceV2Impl.backendUpdateCountForTesting, 1));

        PersistenceV2.save(key);
        test("backendUpdateCount 2 after save", eq(PersistenceV2Impl.backendUpdateCountForTesting, 2));

        PersistenceV2.remove(key);
    }

    tcase("Report type clash when object read from disk with the wrong type given to connect") {
        let keys = PersistenceV2.keys();
        test("Keys size is zero", eq(keys.length, 0));
        // Initialize backend and then recreate PersistenceV2Impl instance.
        // **** Initialize backend ****
        // Create new objects
        const userKeyEL1 = "userKeyEL1";
        let options = new ConnectOptions<User>(UserTypeValue);
        options.key = userKeyEL1
        options.areaMode = AreaMode.EL1;
        options.defaultCreator = () => new User("defaultByCreator");
        let userEL1 = PersistenceV2.globalConnect<User>(
            options,
            toJsonUser,
            fromJsonUser
        )

        test("Object created", not_eq(userEL1, undefined));

        // Trigger writing to the back store
        ObserveSingleton.instance.updateDirty2();

        // **** reset backend ****
        test("PersistenceV2Impl.instanceExists() - true", eq(PersistenceV2Impl.instanceExists(), true));

        PersistenceV2Impl.instanceReset();
        test("PersistenceV2Impl.instanceExists() - false", eq(PersistenceV2Impl.instanceExists(), false));
        PersistenceV2.configureBackend(storageBackend);

        // Get stored objects from the storage
        let errorTriggered = false;
        try {
            let optionsPerson = new ConnectOptions<NonObservedPerson>(NonObservedPersonType);
            optionsPerson.key = options.key;
            optionsPerson.areaMode = options.areaMode;
            optionsPerson.defaultCreator = undefined;
            let userEL1A = PersistenceV2.globalConnect<NonObservedPerson>(
                optionsPerson,
                toJsonPerson,
                fromJsonPerson
            )
        }
        catch (e) {
            errorTriggered = true;
        }

        test("Object NOT read with the wrong type", eq(errorTriggered, true));

        // Trigger writing to the back store
        ObserveSingleton.instance.updateDirty2();
        PersistenceV2.remove(userKeyEL1);
        keys = PersistenceV2.keys();
        test("keys size zero", eq(keys.length, 0));
    }
    }

    ttest();
    return true;
}
