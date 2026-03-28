/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

export enum A2UIMessageType {
  CREATE_SURFACE = 0,
  UPDATE_COMPONENTS = 1,
  UPDATE_DATA_MODEL = 2,
  DELETE_SURFACE = 3
}

export class A2UIMessage {
  version: string;
  surfaceId: string;
  type: A2UIMessageType;
  messageBody?: string;

  constructor(versionNum: string, surfaceId: string, type: A2UIMessageType, body: ESObject | string | undefined) {
    this.version = versionNum;
    this.surfaceId = surfaceId;
    this.type = type;
    this.messageBody = A2UIMessage.serializeMessageBody(body);
  }

  static fromDSL(dsl: string): A2UIMessage | null {
    let jsonObj: ESObject;
    try {
      jsonObj = JSON.parse(dsl);
    } catch (e) {
      console.error("[A2UIMessage] fromDSL JSON.parse FAIL" + e);
    }

    if (jsonObj === null || jsonObj === undefined) {
      console.error("[A2UIMessage] jsonObj is invaild");
      return null;
    }

    let version: string = jsonObj.version;
    if (version === undefined || version === null) {
      console.error("[A2UIMessage] version is invaild");
      return null;
    }
    return A2UIMessage.tryParseMessage(jsonObj, version, 'createSurface', A2UIMessageType.CREATE_SURFACE) ??
      A2UIMessage.tryParseMessage(jsonObj, version, 'updateComponents', A2UIMessageType.UPDATE_COMPONENTS) ??
      A2UIMessage.tryParseMessage(jsonObj, version, 'updateDataModel', A2UIMessageType.UPDATE_DATA_MODEL) ??
      A2UIMessage.tryParseMessage(jsonObj, version, 'deleteSurface', A2UIMessageType.DELETE_SURFACE) ??
      null;
  }

  private static tryParseMessage(
    jsonObj: ESObject,
    version: string,
    key: string,
    type: A2UIMessageType
  ): A2UIMessage | null {
    let body: ESObject = jsonObj[key];
    if (body === undefined) {
      return null;
    }
    let surfaceIdValue: string | number | boolean | Object | null | undefined = body.surfaceId;
    if (surfaceIdValue === undefined) {
      return null;
    }
    let surfaceId: string = String(surfaceIdValue);
    return new A2UIMessage(version, surfaceId, type, body);
  }

  private static serializeMessageBody(body: ESObject | string | undefined): string | undefined {
    if (body === undefined) {
      return undefined;
    }
    if (typeof body === 'string') {
      return body;
    }
    return JSON.stringify(body);
  }

}
