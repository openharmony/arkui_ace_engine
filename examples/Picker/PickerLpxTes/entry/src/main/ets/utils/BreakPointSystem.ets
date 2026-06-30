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

import { deviceInfo } from "@kit.BasicServicesKit";

export class CommonConstants {
  static readonly XS: string = 'xs';

  static readonly SM: string = 'sm';

  static readonly MD: string = 'md';

  static readonly LG: string = 'lg';

  static readonly LIFE_FEED_INFO: string = 'LIFE_FEED_INFO';
}

export class BreakpointSystem {
  static curBreakpoint: string = CommonConstants.MD;

  static rate: number = 1;
}

export function isFirstUIBreakPoint(currentBreakPoint: string | undefined) {
  if (!currentBreakPoint) {
    currentBreakPoint = AppStorage.get<string>("currentBreakPoint");
  }

  if (underApiVersion(13)) {
    if (currentBreakPoint === 'xs' || currentBreakPoint === 'sm') {
      return true;
    }
  } else {
    if (currentBreakPoint === 'xs-sm' || currentBreakPoint === 'xs-md' || currentBreakPoint === 'xs-lg'
      || currentBreakPoint === 'sm-sm' || currentBreakPoint === 'sm-md' || currentBreakPoint === 'sm-lg') {
      return true;
    }
  }
  return false;
}

export function autoUILpxDim(currentBreakPoint: string | undefined, firstUIParamNumber: number | string,
  secondUIParamNumber: number | string): Dimension {
  if (!currentBreakPoint) {
    currentBreakPoint = AppStorage.get<string>("currentBreakPoint");
  }

  if (isFirstUIBreakPoint(currentBreakPoint)) {
    return lpxDim(firstUIParamNumber);
  } else {
    return lpxDim(secondUIParamNumber);
  }
}

export function lpxDim(pxValue: number | string): Dimension {
  try {
    let value = 0;
    if (typeof pxValue === 'string') {
      value = Number.parseInt(getContext().resourceManager.getStringByNameSync(pxValue));
    } else if (typeof pxValue === 'number') {
      value = pxValue;
    }

    if (isLargeBreakPoint(BreakpointSystem.curBreakpoint)) {
      let value1 = (value * BreakpointSystem.rate);
      return `${value1}lpx`;
    }

    return `${value}lpx`;
  } catch (e) {
    return '0lpx'
  }
}

export function autoUILpxN(currentBreakPoint: string | undefined, firstUIParamNumber: number,
  secondUIParamNumber: number): number {
  if (!currentBreakPoint) {
    currentBreakPoint = AppStorage.get<string>("currentBreakPoint");
  }

  if (isFirstUIBreakPoint(currentBreakPoint)) {
    return lpxN(firstUIParamNumber);
  } else {
    return lpxN(secondUIParamNumber);
  }
}

export function lpxN(pxValue: number | string): number {
  try {
    let value = 0;
    if (typeof pxValue === 'string') {
      value = Number.parseInt(getContext().resourceManager.getStringByNameSync(pxValue));
    } else if (typeof pxValue === 'number') {
      value = pxValue;
    }

    if (isLargeBreakPoint(BreakpointSystem.curBreakpoint)) {
      return (value * BreakpointSystem.rate);
    }

    return value;
  } catch (e) {
    return 0
  }
}

export function autoUILpx(currentBreakPoint: string | undefined, firstUIParamNumber: number | string,
  secondUIParamNumber: number | string): string {
  if (!currentBreakPoint) {
    currentBreakPoint = AppStorage.get<string>("currentBreakPoint");
  }

  if (isFirstUIBreakPoint(currentBreakPoint)) {
    return lpx(firstUIParamNumber);
  } else {
    return lpx(secondUIParamNumber);
  }
}

export function lpx(pxValue: number | string) {
  try {
    let value = 0;
    if (typeof pxValue === 'string') {
      value = Number.parseInt(getContext().resourceManager.getStringByNameSync(pxValue));
    } else if (typeof pxValue === 'number') {
      value = pxValue;
    }

    if (isLargeBreakPoint(BreakpointSystem.curBreakpoint)) {
      return (value * BreakpointSystem.rate) + 'lpx';
    }

    return value + 'lpx';
  } catch (e) {
    return '0lpx'
  }
}

export function isLargeBreakPoint(currentBreakPoint: string | undefined) {
  if (!currentBreakPoint) {
    currentBreakPoint = AppStorage.get<string>("currentBreakPoint");
  }

  if (underApiVersion(13)) {
    if (currentBreakPoint === 'lg') {
      return true;
    }
  } else {
    if (currentBreakPoint === 'lg-sm' || currentBreakPoint === 'lg-md' || currentBreakPoint === 'lg-lg'
      || currentBreakPoint === 'xl-sm' || currentBreakPoint === 'xl-md' || currentBreakPoint === 'xl-lg') {
      return true;
    }
  }
  return false;
}

function underApiVersion(apiVersion: number) {
  return deviceInfo.sdkApiVersion < apiVersion;
}