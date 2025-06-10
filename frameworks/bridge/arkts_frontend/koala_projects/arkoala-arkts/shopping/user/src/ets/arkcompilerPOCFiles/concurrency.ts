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
import { InteropNativeModule as NativeModule } from '@koalaui/interop'
import { InformationModel } from '../data/homeData'

const LOG_TAG = "Shopping_2.0_Example "

function blockingSleep(ms: number): void {
  const start = Date.now();
  while (Date.now() - start < ms) {
  }
}

function getRandomString(length: number): string {
  const chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
  let result = "";
  for (let i = 0; i < length; i++) {
    result += chars.charAt(Math.floor(Math.random() * chars.length));
  }
  return result;
}

function getRandomTime(): string {
  const now = new Date();
  return now.toUTCString();
}


function simulateFetchAndParse(length: number): Array<InformationModel> {
  blockingSleep(1000);

  let res: Array<InformationModel> = new Array<InformationModel>();
  for (let i = 0; i < length; i++) {
    res.push(new InformationModel(
      `https://randomsite${i}.com/${getRandomString(10)}`,
      `Title ${getRandomString(5)}`,
      `Notice ${getRandomString(15)}`,
      getRandomTime()
    ));
  }
  return res;
}

export function fetch(): Array<InformationModel> {
  return simulateFetchAndParse(5);
}


export async function asyncFetch() : Promise<Array<InformationModel>> {
    NativeModule._NativeLog(LOG_TAG + "asyncFetch start");
    return simulateFetchAndParse(5);
}

export function callAsyncFetch() {
    NativeModule._NativeLog(LOG_TAG + "call asyncFetch");
    let p = asyncFetch();
    NativeModule._NativeLog(LOG_TAG + "before await res from asyncFetch");
    let first : Array<InformationModel> = await p;
    NativeModule._NativeLog(LOG_TAG + "asyncFetch done: " + first[0].title);
}

function coroutineFetchData() {
  NativeModule._NativeLog(LOG_TAG + "main thread request data from coroutine");

  let resCoroutine = launch fetch();
  let first : Array<InformationModel> = await resCoroutine;
  NativeModule._NativeLog(LOG_TAG + "Coroutine fetch data done: " + first[0].title);
}

export function callFetchWithCoroutine() {
  launch coroutineFetchData();
}

function fetchWithTaskPool() : Array<InformationModel> {
  NativeModule._NativeLog(LOG_TAG + `taskpool fetch data`)
  return fetch();
}

function taskPoolFetchData(){
  NativeModule._NativeLog(LOG_TAG + "main thread request data from taskpool")
  let resTaskPool = taskpool.execute(fetchWithTaskPool);
  let obj = (await resTaskPool) as Array<InformationModel>;
  NativeModule._NativeLog(LOG_TAG + "TaskPool fetch data done: " + obj[0].title);
}

export function callFetchWithTaskPool() {
  launch taskPoolFetchData();
}

let ea2coro : BlockingQueue<Array<InformationModel>> = new BlockingQueue<Array<InformationModel>>();
function eaTask() {
  NativeModule._NativeLog(LOG_TAG + "EACoroutine start to fetch data");
  ea2coro.push(fetch());
  NativeModule._NativeLog(LOG_TAG + "EACoroutine fetch data end");
}
let eaw:EAWorker;
let isEAInitialized = false;

function EACoroutineFetchData() {
  NativeModule._NativeLog(LOG_TAG + "request data from EACoroutine");
  if (!isEAInitialized) {
    isEAInitialized = true;
    eaw = new EAWorker(true);
  }
  eaw.run(()=>{
    return eaTask();
  })
  NativeModule._NativeLog(LOG_TAG + "Post eaTask done");
  let p = ea2coro.pop();
  NativeModule._NativeLog(LOG_TAG + "EACoroutine fetch data done: " + p[0].title);
}

export function callFetchWithEACoroutine() {
  launch EACoroutineFetchData();
}