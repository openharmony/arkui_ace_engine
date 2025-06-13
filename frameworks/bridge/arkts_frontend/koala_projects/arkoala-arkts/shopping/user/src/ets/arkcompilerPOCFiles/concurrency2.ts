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

import { GiteeHelper } from './GiteeHelper'
import { PRs } from './GiteeHelperData'

const TABLE_NAME = "pr_table"
export const CREATE_TABLE = "CREATE TABLE " + TABLE_NAME + " (" +
  "id INTEGER PRIMARY KEY AUTOINCREMENT," +
  "url TEXT," +
  "number TEXT, " +
  "created_at TEXT, " +
  "updated_at TEXT, " +
  "closed_at TEXT, " +
  "merged_at TEXT, " +
  "user_name TEXT, " +
  "title TEXT, " +
  "body TEXT);";
export const DROP_TABLE = "DROP TABLE " + TABLE_NAME;

let bg2fg: BlockingQueue<Promise<number>> = new BlockingQueue<Promise<number>>();

export function callRDBWithNativeEACoroutine() {
  console.log("callRDBWithNativeEACoroutine is not implemented yet")
}

function DtoS(x?: Date): string {
  if (x != undefined) {
    return x.toString()
  }
  return 'undefined'
}

function CreateDataQuery(prs: PRs): string {
  let query: string = "INSERT INTO " + TABLE_NAME + " " +
    "( url, number, created_at, updated_at, closed_at, merged_at, user_name, title, body ) VALUES "
  try {
  let values = prs.values!;
  for (let idx = 0; idx < values.length; idx++) {
    const pr = values[idx]
    const user = pr.user!
    query += "('" + pr.url + "', '" + pr.number + "', '" + DtoS(pr.created_at) + "',  '" + DtoS(pr.updated_at) + "',  '" +
                   DtoS(pr.closed_at) + "',  '" + DtoS(pr.merged_at) + "',  '" + user.name + "',  '" + pr.title + "',  '" + pr.body + "')"
    if (idx != values.length - 1) query += ", "
  }
  query += "; "
  console.log("query: " + query)
  } catch (e) {
    console.log("Error: " + e)
  }
  return query
}

export function GetAll(cb: (ret: number) => void) {
  let dataRdb = JSRuntime.loadModule('@ohos.data.relationalStore')
  const query = "select * from " + TABLE_NAME;
  const storeConfig = {} as JSValue;
  JSRuntime.setPropertyString(storeConfig, 'name', TABLE_NAME);
  JSRuntime.setPropertyJSValue(storeConfig, 'securityLevel', dataRdb.SecurityLevel.S1);
  let ctx = GetCtx();

  let gstore: JSValue = {} as JSValue;
  let p: Promise<JSValue> = dataRdb.getRdbStore(ctx, storeConfig).then((store: JSValue) => {
    store.querySql(query).then((res: JSValue) => {
      res.goToFirstRow();
      const rowCount = res.rowCount as number;
      const columnCount = res.columnCount as number;
      console.log(`inserted rows count: ${rowCount}`)
      cb(rowCount);
    })
  }).catch((e: JSValue) => {
    console.log(`GetAll QuerySql catch ${e}`)
  });
}


function GetCtx(): JSValue {
  let ctx: JSValue = {} as JSValue;

  JSRuntime.setPropertyBoolean(ctx, 'stageMode', true)
  JSRuntime.setPropertyString(ctx, 'databaseDir', '/data/storage/el2/database/entry')
  JSRuntime.setPropertyDouble(ctx, 'area', 1)
  const currentHapModuleInfo = {} as JSValue;
  JSRuntime.setPropertyString(currentHapModuleInfo, 'name', 'entry');
  JSRuntime.setPropertyJSValue(ctx, 'currentHapModuleInfo', currentHapModuleInfo)
  const applicationInfo = {} as JSValue;
  JSRuntime.setPropertyString(applicationInfo, 'name', 'com.arkoala.app');
  JSRuntime.setPropertyBoolean(applicationInfo, 'systemApp', false);
  JSRuntime.setPropertyJSValue(ctx, 'applicationInfo', applicationInfo)
  return ctx
}

function DoFetchAndPush(prs: PRs): Promise<number> {
  let hilog = JSRuntime.loadModule('@ohos.hilog');
  let dataRdb = JSRuntime.loadModule('@ohos.data.relationalStore')

  console.log("DoFetchAndPush START");
  hilog.error(0x0000, "koalaShopping", "%{public}s", "I AM INTEROP FROM EACOROUTINE");

  const storeConfig = {} as JSValue;
  JSRuntime.setPropertyString(storeConfig, 'name', TABLE_NAME);
  JSRuntime.setPropertyJSValue(storeConfig, 'securityLevel', dataRdb.SecurityLevel.S1);
  let ctx = GetCtx();

  console.log("DoFetchAndPush before getRdbStore");
  let RDBstore: JSValue = {};
  let promise: Promise<JSValue> = dataRdb.getRdbStore(ctx, storeConfig).then((store: JSValue) => {
    RDBstore = store
    return {} as JSValue;
  }).then((x: JSValue)=>{
    let promise: JSValue = {} as JSValue;
    promise = RDBstore.executeSql(CREATE_TABLE);
    return promise;
  }).catch((e: JSValue) => {
    console.log(`DoFetchAndPush CATCH 1 ${e}`)
  }).then((x: JSValue)=>{
    let promise: JSValue = {} as JSValue;
    const query = CreateDataQuery(prs);
    promise = RDBstore.executeSql(query);
    return promise;
  }).catch((e: JSValue) => {
    console.log(`DoFetchAndPush CATCH 2 ${e}`)
  });

  console.log("DoFetchAndPush END ");
  return promise;
}

export function InsertInDBFromParam(prs: PRs): int
{
  console.log("InsertInDBFromParam START");
  bg2fg.push(DoFetchAndPush(prs));
  console.log("InsertInDBFromParam END");
  return 42;
}

let EAW: EAWorker;
let isEAworkerInitialized = false
export function callRDBWithManagedEACoroutine(cb: () => void) {
  if (!isEAworkerInitialized) {
    isEAworkerInitialized = true;
    EAW = new EAWorker(true)
  }
  console.log("callRDBWithManagedEACoroutine start")
  GiteeHelper.FetchMockData(0, 200, (prs: PRs) => {
    EAW.run(() => {
      return InsertInDBFromParam(prs);
    });
  })
  console.log("callRDBWithManagedEACoroutine end")

  let p = bg2fg.pop();
  p.then((x: JSValue): number => {
    console.log("callRDBWithManagedEACoroutine p.then before CB call");
    cb();
    console.log("callRDBWithManagedEACoroutine p.then after CB call");
    return 322;
  });
  return p;
}
