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

/// <reference path="../types/index.d.ts" />

const JSCallbackInfoType = { STRING: 0, NUMBER: 1, OBJECT: 2, BOOLEAN: 3, FUNCTION: 4 };
type basicType = string | number | bigint | boolean | symbol | undefined | object | null;
const isString = (val: basicType): boolean => typeof val === 'string';
const isNumber = (val: basicType): boolean => typeof val === 'number';
const isBigint = (val: basicType): boolean => typeof val === 'bigint';
const isBoolean = (val: basicType): boolean => typeof val === 'boolean';
const isSymbol = (val: basicType): boolean => typeof val === 'symbol';
const isUndefined = (val: basicType): boolean => typeof val === 'undefined';
const isObject = (val: basicType): boolean => typeof val === 'object';
const isFunction = (val: basicType): boolean => typeof val === 'function';
const isLengthType = (val: any): boolean => typeof val === 'string' || typeof val === 'number';
const isNull = (val: any) => typeof val === 'object' && val === null;
const isArray = (val: any) => Array.isArray(val);
const isDate = (val: any) => val instanceof Date;
const isRegExp = (val: any) => val instanceof RegExp;
const isError = (val: any) => val instanceof Error;
const isFloat = (val: any) => Number.isFinite(val) && !Number.isInteger(val);
const isInteger = (val: any) => Number.isInteger(val);
const isNonEmptyMap = (val: any) => val instanceof Map && val.size > 0;
const isTruthyString = (val: any) => typeof val === 'string' && val.trim() !== '';

function isResource(variable: any): variable is Resource {
  return (variable as Resource)?.bundleName !== undefined;
}

function isBaseOrResourceEqual(stageValue: any, value: any): boolean {
  if (!isResource(stageValue) && !isResource(value)) {
    return (stageValue === value);
  }
  return false;
}

function deepCompareArrays(arr1: Array<any>, arr2: Array<any>): boolean {
  return (
    Array.isArray(arr1) &&
    Array.isArray(arr2) &&
    arr1.length === arr2.length &&
    arr1.every((value, index) => {
      if (Array.isArray(value) && Array.isArray(arr2[index])) {
        return deepCompareArrays(value, arr2[index]);
      } else {
        return value === arr2[index];
      }
    })
  );
}