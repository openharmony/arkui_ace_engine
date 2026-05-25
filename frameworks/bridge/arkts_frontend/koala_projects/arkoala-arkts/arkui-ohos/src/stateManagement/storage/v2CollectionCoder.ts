/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

import { StorageDefaultCreator } from './persistenceV2';
import { IObservedAnyProp } from '../decorator';
import { ObserveWrappedKeyedMeta } from '../base/observeWrappedBase';
import { StateMgmtTool } from '#stateMgmtTool';

export type CollectionCoderErrorCallback = (message: string) => void;

const CLASS_NAME_KEY: string = '__className__';
const BACKING_PREFIX: string = '__backing_';
const GETTER_PREFIX: string = '%%get-';
const SKIP_SENTINEL: Map<string, string> = new Map<string, string>();

const PRIMITIVE_TYPE_TO_TAG: Map<string, string> = new Map<string, string>([
    ['string', 'st'],
    ['byte', 'i08'],
    ['short', 'i16'],
    ['int', 'i32'],
    ['long', 'i64'],
    ['float', 'f32'],
    ['number', 'nu'],
    ['boolean', 'bo'],
    ['bigint', 'bi']
]);

function isNumericType(t: string): boolean {
    return t === 'byte' || t === 'short' || t === 'int' ||
        t === 'long' || t === 'float' || t === 'number';
}

function reportError(msg: string, onError?: CollectionCoderErrorCallback): void {
    if (onError) {
        onError(msg);
    } else {
        console.error(msg);
    }
}

function escapeString(str: string): string {
    const len: int = str.getLength();
    let result = new StringBuilder('');
    for (let i = 0; i < len; i++) {
        const code: int = str.charCodeAt(i);
        if (code === 0x5C) {
            result.append('\\\\');
        } else if (code === 0x22) {
            result.append('\\"');
        } else if (code === 0x0A) {
            result.append('\\n');
        } else if (code === 0x0D) {
            result.append('\\r');
        } else if (code === 0x09) {
            result.append('\\t');
        } else if (code === 0x08) {
            result.append('\\b');
        } else if (code === 0x0C) {
            result.append('\\f');
        } else if (code < 32) {
            result.append('\\u');
            result.append(code.toString(16).padStart(4, '0'));
        } else {
            result.append(str.charAt(i).toString());
        }
    }
    return result.toString();
}

function getClassName(val: Any): string | undefined {
    if (typeof val !== 'object' || val === null) {
        return undefined;
    }
    if (val instanceof Array || val instanceof Set ||
        (val instanceof Map && !(val instanceof Record)) || val instanceof Date) {
        return undefined;
    }
    try {
        return (val as Record<string, Any>)[CLASS_NAME_KEY] as string | undefined;
    } catch (e) {
        return undefined;
    }
}

function getElementType(val: Any): string {
    if (val === null || val === undefined) {
        return '';
    }
    if (typeof val === 'object') {
        const cn = getClassName(val);
        if (cn !== undefined && cn !== null) {
            return cn;
        }
        try {
            const unwrapped = StateMgmtTool.tryGetTarget(val as Object);
            const t = (unwrapped !== undefined && unwrapped !== null) ? unwrapped : val;
            return Class.of(t as Object).getName();
        } catch (e) {
            return '';
        }
    }
    try {
        const clazz = Class.ofAny(val);
        return clazz ? clazz.getName() : '';
    } catch (e) {
        return '';
    }
}

function serializePrimitive(value: Any): string | undefined {
    if (value === null) {
        return '{"_t":"nl"}';
    }
    if (value === undefined) {
        return '{"_t":"un"}';
    }
    const tag = PRIMITIVE_TYPE_TO_TAG.get(typeof value);
    if (tag !== undefined) {
        if (typeof value === 'string') {
            return '{"_t":"' + tag + '","_v":"' + escapeString(value as string) + '"}';
        }
        return '{"_t":"' + tag + '","_v":"' + (value as Object).toString() + '"}';
    }
    return undefined;
}

function serializeBoxed(value: Any): string | undefined {
    if (value instanceof Boolean) {
        return '{"_t":"bo","_v":"' + (value as Boolean).toString() + '"}';
    }
    if (value instanceof Byte) {
        return '{"_t":"i08","_v":"' + (value as Byte).toString() + '"}';
    }
    if (value instanceof Short) {
        return '{"_t":"i16","_v":"' + (value as Short).toString() + '"}';
    }
    if (value instanceof Int) {
        return '{"_t":"i32","_v":"' + (value as Int).toString() + '"}';
    }
    if (value instanceof Long) {
        return '{"_t":"i64","_v":"' + (value as Long).toString() + '"}';
    }
    if (value instanceof Float) {
        return '{"_t":"f32","_v":"' + (value as Float).toString() + '"}';
    }
    if (value instanceof Double) {
        return '{"_t":"nu","_v":"' + (value as Double).toString() + '"}';
    }
    if (value instanceof String) {
        return '{"_t":"st","_v":"' + escapeString((value as String).toString()) + '"}';
    }
    return undefined;
}

function serializeArray(value: Any, refId: string, visited: Map<Object, string>,
    onError?: CollectionCoderErrorCallback): string {
    let items = '';
    let first = true;
    (value as Any as Array<Any>).forEach((item: Any) => {
        if (!first) {
            items += ',';
        }
        first = false;
        items += serializeValue(item, visited, onError);
    });
    return '{"_t":"Ar","_r":"' + refId + '","_v":[' + items + ']}';
}

function serializeSet(value: Any, refId: string, visited: Map<Object, string>,
    onError?: CollectionCoderErrorCallback): string {
    let items = '';
    let first = true;
    (value as Any as Set<Any>).forEach((item: Any) => {
        if (!first) {
            items += ',';
        }
        first = false;
        items += serializeValue(item, visited, onError);
    });
    return '{"_t":"Se","_r":"' + refId + '","_v":[' + items + ']}';
}

function serializeMap(value: Any, refId: string, visited: Map<Object, string>,
    onError?: CollectionCoderErrorCallback): string {
    let keys = '';
    let vals = '';
    let first = true;
    let skipMap = false;
    (value as Any as Map<Any, Any>).forEach((v: Any, k: Any) => {
        if (skipMap) {
            return;
        }
        const kt = typeof k;
        if (kt !== 'string' && !isNumericType(kt)) {
            const msg = `PersistenceV2: Map key type '${kt}' is not supported. ` +
                `Only string and number types are allowed. Skipping map serialization.`;
            console.error(msg);
            if (onError) {
                onError(msg);
            }
            skipMap = true;
            return;
        }
        if (!first) {
            keys += ',';
            vals += ',';
        }
        first = false;
        keys += serializeValue(k, visited, onError);
        vals += serializeValue(v, visited, onError);
    });
    if (skipMap) {
        return '{"_t":"Ma","_r":"' + refId + '","_k":[],"_v":[]}';
    }
    return '{"_t":"Ma","_r":"' + refId + '","_k":[' + keys + '],"_v":[' + vals + ']}';
}

function serializePlainObject(value: Any, refId: string, visited: Map<Object, string>,
    onError?: CollectionCoderErrorCallback): string {
    let className = '';
    try {
        className = Class.of(value as Object).getName();
    } catch (e) {}
    let objKeys = '';
    let objVals = '';
    let first = true;
    const clazz = Class.of(value as Object);
    reflect.getInstanceFieldsRecursive(clazz).forEach((field: reflect.InstanceField) => {
        if (!first) {
            objKeys += ',';
            objVals += ',';
        }
        first = false;
        objKeys += '"' + escapeString(field.getName()) + '"';
        let fieldValue: Any = field.getValue(value as Object) as Any;
        const fieldName: string = field.getName();
        if (fieldName.startsWith(BACKING_PREFIX)) {
            const propName: string = fieldName.substring(BACKING_PREFIX.length);
            try {
                const method = clazz.getInstanceMethod(GETTER_PREFIX + propName);
                if (method !== undefined && method !== null) {
                    fieldValue = method.invoke(value as Object);
                }
            } catch (e) {}
        }
        objVals += serializeValue(fieldValue, visited, onError);
    });
    let result = '{"_t":"Ob","_r":"' + refId + '"';
    if (className.length > 0) {
        result += ',"_c":"' + escapeString(className) + '"';
    }
    result += ',"_k":[' + objKeys + '],"_v":[' + objVals + ']}';
    return result;
}

function serializeValue(value: Any, visited: Map<Object, string>,
    onError?: CollectionCoderErrorCallback): string {
    const primResult = serializePrimitive(value);
    if (primResult !== undefined) {
        return primResult;
    }

    if (value instanceof ObserveWrappedKeyedMeta) {
        (value as ObserveWrappedKeyedMeta).addRefAnyKey();
    } else if (value instanceof IObservedAnyProp) {
        (value as IObservedAnyProp).addRefAnyProp();
    }

    const boxedResult = serializeBoxed(value);
    if (boxedResult !== undefined) {
        return boxedResult;
    }

    let refId = visited.get(value as Object);
    if (refId !== undefined) {
        return '{"_t":"re","_r":"' + refId + '"}';
    }

    const size: int = visited.size;
    refId = size.toString(32).padStart(4, '0');
    visited.set(value as Object, refId);

    if (value instanceof Date) {
        return '{"_t":"Da","_r":"' + refId + '","_v":"' + (value as Date).toISOString() + '"}';
    }
    if (value instanceof Array) {
        return serializeArray(value, refId, visited, onError);
    }
    if (value instanceof Set) {
        return serializeSet(value, refId, visited, onError);
    }
    if (value instanceof Map && !(value instanceof Record)) {
        return serializeMap(value, refId, visited, onError);
    }
    return serializePlainObject(value, refId, visited, onError);
}

function readPrimitiveValue(type: string, element: jsonx.JsonElement): Any | undefined {
    if (type === 'nl') {
        return null;
    }
    if (type === 'un') {
        return undefined;
    }
    if (type === 'st') {
        return element.getElement('_v').asString();
    }
    if (type === 'i08') {
        return Double.toByte(Number(element.getElement('_v').asString()));
    }
    if (type === 'i16') {
        return Double.toShort(Number(element.getElement('_v').asString()));
    }
    if (type === 'i32') {
        return Double.toInt(Number(element.getElement('_v').asString()));
    }
    if (type === 'i64') {
        return Long.parseInt(element.getElement('_v').asString(), 10);
    }
    if (type === 'f32') {
        return Double.toFloat(Number(element.getElement('_v').asString()));
    }
    if (type === 'nu') {
        return Number(element.getElement('_v').asString());
    }
    if (type === 'bo') {
        return element.getElement('_v').asString() === 'true';
    }
    if (type === 'bi') {
        return BigInt(element.getElement('_v').asString());
    }
    return undefined;
}

function readReferenceValue(type: string, refId: string, element: jsonx.JsonElement,
    objects: Map<string, Object>): Any | undefined {
    if (type === 're') {
        const resolved = objects.get(refId);
        if (resolved === undefined) {
            console.error(`PersistenceV2: Unresolved circular reference '${refId}'.`);
        }
        return resolved;
    }
    if (type === 'Da') {
        const result = new Date(element.getElement('_v').asString());
        objects.set(refId, result as Object);
        return result;
    }
    if (type === 'Ar') {
        return readArrayValue(element, refId, objects);
    }
    if (type === 'Se') {
        return readSetValue(element, refId, objects);
    }
    if (type === 'Ma') {
        return readMapValue(element, refId, objects);
    }
    if (type === 'Ob') {
        return readObjectValue(element, refId, objects);
    }
    return undefined;
}

function readArrayValue(element: jsonx.JsonElement, refId: string,
    objects: Map<string, Object>): Array<Any> {
    const arr = element.getElement('_v').asArray();
    const result: Array<Any> = [];
    objects.set(refId, result as Object);
    for (let i = 0; i < arr.length; i++) {
        result.push(readValue(arr[i], objects));
    }
    return result;
}

function readSetValue(element: jsonx.JsonElement, refId: string,
    objects: Map<string, Object>): Set<Any> {
    const arr = element.getElement('_v').asArray();
    const result = new Set<Any>();
    objects.set(refId, result as Object);
    for (let i = 0; i < arr.length; i++) {
        result.add(readValue(arr[i], objects));
    }
    return result;
}

function readMapValue(element: jsonx.JsonElement, refId: string,
    objects: Map<string, Object>): Map<Any, Any> {
    const keysArr = element.getElement('_k').asArray();
    const valsArr = element.getElement('_v').asArray();
    const result = new Map<Any, Any>();
    objects.set(refId, result as Object);
    for (let i = 0; i < keysArr.length; i++) {
        const k = readValue(keysArr[i], objects);
        const v = readValue(valsArr[i], objects);
        result.set(k, v);
    }
    return result;
}

function readObjectValue(element: jsonx.JsonElement, refId: string,
    objects: Map<string, Object>): Record<string, Any> {
    const keysArr = element.getElement('_k').asArray();
    const valsArr = element.getElement('_v').asArray();
    const result: Record<string, Any> = {} as Record<string, Any>;
    objects.set(refId, result as Object);
    try {
        const cElement = element.getElement('_c');
        if (cElement !== undefined && cElement !== null) {
            result[CLASS_NAME_KEY] = cElement.asString();
        }
    } catch (e) {}
    for (let i = 0; i < keysArr.length; i++) {
        const key = keysArr[i].asString();
        result[key] = readValue(valsArr[i], objects);
    }
    return result;
}

function readValue(element: jsonx.JsonElement, objects: Map<string, Object>): Any {
    const type: string = element.getElement('_t').asString();

    const primResult = readPrimitiveValue(type, element);
    if (primResult !== undefined || type === 'nl' || type === 'un') {
        return primResult;
    }

    const refId: string = element.getElement('_r').asString();

    const refResult = readReferenceValue(type, refId, element, objects);
    if (refResult !== undefined) {
        return refResult;
    }

    console.error(`PersistenceV2: Unknown type tag '${type}' during deserialization.`);
    return undefined;
}

function convertByteToNumeric(srcVal: Any, tgtType: string): Any {
    if (tgtType === 'short') {
        return Byte.toShort(srcVal as byte);
    }
    if (tgtType === 'int') {
        return Byte.toInt(srcVal as byte);
    }
    if (tgtType === 'long') {
        return Byte.toLong(srcVal as byte);
    }
    if (tgtType === 'float') {
        return Byte.toFloat(srcVal as byte);
    }
    if (tgtType === 'number') {
        return Byte.toDouble(srcVal as byte);
    }
    return srcVal;
}

function convertShortToNumeric(srcVal: Any, tgtType: string): Any {
    if (tgtType === 'byte') {
        return Short.toByte(srcVal as short);
    }
    if (tgtType === 'int') {
        return Short.toInt(srcVal as short);
    }
    if (tgtType === 'long') {
        return Short.toLong(srcVal as short);
    }
    if (tgtType === 'float') {
        return Short.toFloat(srcVal as short);
    }
    if (tgtType === 'number') {
        return Short.toDouble(srcVal as short);
    }
    return srcVal;
}

function convertIntToNumeric(srcVal: Any, tgtType: string): Any {
    if (tgtType === 'byte') {
        return Int.toByte(srcVal as int);
    }
    if (tgtType === 'short') {
        return Int.toShort(srcVal as int);
    }
    if (tgtType === 'long') {
        return Int.toLong(srcVal as int);
    }
    if (tgtType === 'float') {
        return Int.toFloat(srcVal as int);
    }
    if (tgtType === 'number') {
        return Int.toDouble(srcVal as int);
    }
    return srcVal;
}

function convertLongToNumeric(srcVal: Any, tgtType: string): Any {
    if (tgtType === 'byte') {
        return Long.toByte(srcVal as long);
    }
    if (tgtType === 'short') {
        return Long.toShort(srcVal as long);
    }
    if (tgtType === 'int') {
        return Long.toInt(srcVal as long);
    }
    if (tgtType === 'float') {
        return Long.toFloat(srcVal as long);
    }
    if (tgtType === 'number') {
        return Long.toDouble(srcVal as long);
    }
    return srcVal;
}

function convertFloatToNumeric(srcVal: Any, tgtType: string): Any {
    if (tgtType === 'byte') {
        return Float.toByte(srcVal as float);
    }
    if (tgtType === 'short') {
        return Float.toShort(srcVal as float);
    }
    if (tgtType === 'int') {
        return Float.toInt(srcVal as float);
    }
    if (tgtType === 'long') {
        return Float.toLong(srcVal as float);
    }
    if (tgtType === 'number') {
        return Float.toDouble(srcVal as float);
    }
    return srcVal;
}

function convertDoubleToNumeric(srcVal: Any, tgtType: string): Any {
    if (tgtType === 'byte') {
        return Double.toByte(srcVal as double);
    }
    if (tgtType === 'short') {
        return Double.toShort(srcVal as double);
    }
    if (tgtType === 'int') {
        return Double.toInt(srcVal as double);
    }
    if (tgtType === 'long') {
        return Double.toLong(srcVal as double);
    }
    if (tgtType === 'float') {
        return Double.toFloat(srcVal as double);
    }
    return srcVal;
}

function convertNumericToNumeric(srcVal: Any, srcType: string, tgtType: string): Any {
    if (srcType === 'byte') {
        return convertByteToNumeric(srcVal, tgtType);
    }
    if (srcType === 'short') {
        return convertShortToNumeric(srcVal, tgtType);
    }
    if (srcType === 'int') {
        return convertIntToNumeric(srcVal, tgtType);
    }
    if (srcType === 'long') {
        return convertLongToNumeric(srcVal, tgtType);
    }
    if (srcType === 'float') {
        return convertFloatToNumeric(srcVal, tgtType);
    }
    return convertDoubleToNumeric(srcVal, tgtType);
}

function convertStringToNumeric(srcVal: string, tgtType: string): Any | undefined {
    const num = Number(srcVal);
    if (isNaN(num)) {
        return undefined;
    }
    if (tgtType === 'byte') {
        return Double.toByte(num);
    }
    if (tgtType === 'short') {
        return Double.toShort(num);
    }
    if (tgtType === 'int') {
        return Double.toInt(num);
    }
    if (tgtType === 'long') {
        return Long.parseInt(srcVal, 10);
    }
    if (tgtType === 'float') {
        return Double.toFloat(num);
    }
    return num;
}

function coercePrimitive(srcVal: Any, tgtVal: Any, fieldName: string,
    onError?: CollectionCoderErrorCallback): Any {
    const tgtType = typeof tgtVal;
    const srcType = typeof srcVal;

    if (isNumericType(tgtType)) {
        if (isNumericType(srcType)) {
            console.error(`PersistenceV2: Type mismatch for field '${fieldName}': ` +
                `source '${srcType}' converted to target '${tgtType}'.`);
            return convertNumericToNumeric(srcVal, srcType, tgtType);
        }
        if (srcType === 'string') {
            const result = convertStringToNumeric(srcVal as string, tgtType);
            if (result !== undefined) {
                console.error(`PersistenceV2: Type mismatch for field '${fieldName}': ` +
                    `source '${srcType}' parsed and converted to target '${tgtType}'.`);
                return result;
            }
        }
    }

    if (tgtType === 'string' && isNumericType(srcType)) {
        console.error(`PersistenceV2: Type mismatch for field '${fieldName}': ` +
            `source '${srcType}' converted to target 'string'.`);
        return (srcVal as Object).toString();
    }

    const msg = `PersistenceV2: Type mismatch for field '${fieldName}': ` +
        `source '${srcType}' cannot convert to '${tgtType}'. Keeping default value.`;
    reportError(msg, onError);
    return undefined;
}

function getFirstElement(collection: Any): Any {
    let first: Any = undefined;
    let found = false;
    if (collection instanceof Map && !(collection instanceof Record)) {
        (collection as Any as Map<Any, Any>).forEach((v: Any) => {
            if (!found) {
                first = v;
                found = true;
            }
        });
    } else if (collection instanceof Set) {
        (collection as Any as Set<Any>).forEach((item: Any) => {
            if (!found) {
                first = item;
                found = true;
            }
        });
    } else if (Array.isArray(collection)) {
        if ((collection as Array<Any>).length > 0) {
            first = (collection as Array<Any>)[0];
        }
    }
    return first;
}

function checkElementTypeMismatch(srcFirst: Any, tgtFirst: Any, collectionLabel: string,
    skipLabel: string, onError?: CollectionCoderErrorCallback): string | undefined {
    const srcName = getElementType(srcFirst);
    const tgtName = getElementType(tgtFirst);
    if (srcName !== '' && tgtName !== '' && srcName !== tgtName) {
        const msg = `PersistenceV2: ${collectionLabel} type mismatch (source: ${srcName}, target: ${tgtName}). Skipping ${skipLabel} restoration.`;
        reportError(msg, onError);
        return msg;
    }
    return undefined;
}

function checkUnregisteredSubCreator(srcFirst: Any, collectionLabel: string,
    skipLabel: string, classNameToCreator: Map<string, StorageDefaultCreator<object>> | undefined,
    onError?: CollectionCoderErrorCallback): string | undefined {
    if (typeof srcFirst !== 'object' || srcFirst === null) {
        return undefined;
    }
    const srcName = getClassName(srcFirst);
    if (srcName !== undefined && srcName !== '' &&
        classNameToCreator !== undefined && !classNameToCreator.has(srcName)) {
        const msg = `PersistenceV2: ${collectionLabel} type '${srcName}' not found in defaultSubCreators. Skipping ${skipLabel} restoration.`;
        reportError(msg, onError);
        return msg;
    }
    return undefined;
}

function isCreatorMismatch(actualName: string, className: string,
    onError?: CollectionCoderErrorCallback): boolean {
    if (actualName === className) {
        return false;
    }
    const msg = `PersistenceV2: defaultSubCreator type mismatch: expected '${className}' but got '${actualName}'. Skipping.`;
    console.error(msg);
    if (onError) {
        onError(msg);
    }
    return true;
}

function cloneOrCopyValue(val: Any, classNameToCreator: Map<string, StorageDefaultCreator<object>> | undefined,
    visitedTargets: Set<Object>, visitedSources: Map<Object, Object>,
    onError?: CollectionCoderErrorCallback): Any {
    if (typeof val !== 'object' || val === null) {
        return val;
    }
    if (visitedSources.has(val as Object)) {
        return visitedSources.get(val as Object);
    }
    if (val instanceof Date) {
        const cloned = new Date((val as Date).getTime());
        visitedSources.set(val as Object, cloned as Object);
        return cloned;
    }
    const className = getClassName(val);
    if (className !== undefined && classNameToCreator !== undefined) {
        const creator = classNameToCreator.get(className);
        if (creator !== undefined) {
            const newInstance = creator();
            try {
                const actualName = Class.of(newInstance as Object).getName();
                if (isCreatorMismatch(actualName, className, onError)) {
                    return SKIP_SENTINEL;
                }
            } catch (e) {}
            visitedSources.set(val as Object, newInstance as Object);
            restoreObject(newInstance, val, classNameToCreator, visitedTargets, visitedSources, onError);
            return newInstance;
        }
    }
    visitedSources.set(val as Object, val as Object);
    return val;
}

function restoreArray(target: Any, source: Any, classNameToCreator: Map<string, StorageDefaultCreator<object>> | undefined,
    visitedTargets: Set<Object>, visitedSources: Map<Object, Object>,
    onError?: CollectionCoderErrorCallback): void {
    if (!Array.isArray(target)) {
        const msg = `PersistenceV2: Type mismatch: source is Array but target is ${typeof target}. Skipping.`;
        reportError(msg, onError);
        return;
    }
    const srcArr = source as Array<Any>;
    const tgtArr = target as Array<Any>;
    if (srcArr.length > 0 && tgtArr.length > 0) {
        const err = checkElementTypeMismatch(srcArr[0], tgtArr[0], 'Array element', 'array', onError);
        if (err !== undefined) {
            return;
        }
    } else if (srcArr.length > 0 && tgtArr.length === 0) {
        const err = checkUnregisteredSubCreator(srcArr[0], 'Array element', 'array', classNameToCreator, onError);
        if (err !== undefined) {
            return;
        }
    }
    tgtArr.length = 0;
    srcArr.forEach((item: Any) => {
        const cloned = cloneOrCopyValue(item, classNameToCreator, visitedTargets, visitedSources, onError);
        if (cloned !== SKIP_SENTINEL) {
            tgtArr.push(cloned);
        }
    });
}

function restoreMap(target: Any, source: Any, classNameToCreator: Map<string, StorageDefaultCreator<object>> | undefined,
    visitedTargets: Set<Object>, visitedSources: Map<Object, Object>,
    onError?: CollectionCoderErrorCallback): void {
    if (!(target instanceof Map) || target instanceof Record) {
        const msg = `PersistenceV2: Type mismatch: source is Map but target is ${typeof target}. Skipping.`;
        reportError(msg, onError);
        return;
    }
    const srcMap = source as Any as Map<Any, Any>;
    const tgtMap = target as Any as Map<Any, Any>;
    const srcHasVal = srcMap.size > 0;
    const tgtHasVal = tgtMap.size > 0;
    const srcFirstVal = srcHasVal ? getFirstElement(srcMap) : undefined;
    const tgtFirstVal = tgtHasVal ? getFirstElement(tgtMap) : undefined;
    if (srcHasVal && tgtHasVal) {
        const err = checkElementTypeMismatch(srcFirstVal, tgtFirstVal, 'Map value', 'map', onError);
        if (err !== undefined) {
            return;
        }
    } else if (srcHasVal && !tgtHasVal) {
        const err = checkUnregisteredSubCreator(srcFirstVal, 'Map value', 'map', classNameToCreator, onError);
        if (err !== undefined) {
            return;
        }
    }
    tgtMap.clear();
    srcMap.forEach((val: Any, key: Any) => {
        const cloned = cloneOrCopyValue(val, classNameToCreator, visitedTargets, visitedSources, onError);
        if (cloned !== SKIP_SENTINEL) {
            tgtMap.set(key, cloned);
        }
    });
}

function restoreSet(target: Any, source: Any, classNameToCreator: Map<string, StorageDefaultCreator<object>> | undefined,
    visitedTargets: Set<Object>, visitedSources: Map<Object, Object>,
    onError?: CollectionCoderErrorCallback): void {
    if (!(target instanceof Set)) {
        const msg = `PersistenceV2: Type mismatch: source is Set but target is ${typeof target}. Skipping.`;
        reportError(msg, onError);
        return;
    }
    const srcSet = source as Any as Set<Any>;
    const tgtSet = target as Any as Set<Any>;
    const srcHasItem = srcSet.size > 0;
    const tgtHasItem = tgtSet.size > 0;
    const srcFirstItem = srcHasItem ? getFirstElement(srcSet) : undefined;
    const tgtFirstItem = tgtHasItem ? getFirstElement(tgtSet) : undefined;
    if (srcHasItem && tgtHasItem) {
        const err = checkElementTypeMismatch(srcFirstItem, tgtFirstItem, 'Set element', 'set', onError);
        if (err !== undefined) {
            return;
        }
    } else if (srcHasItem && !tgtHasItem) {
        const err = checkUnregisteredSubCreator(srcFirstItem, 'Set element', 'set', classNameToCreator, onError);
        if (err !== undefined) {
            return;
        }
    }
    tgtSet.clear();
    srcSet.forEach((item: Any) => {
        const cloned = cloneOrCopyValue(item, classNameToCreator, visitedTargets, visitedSources, onError);
        if (cloned !== SKIP_SENTINEL) {
            tgtSet.add(cloned);
        }
    });
}

function restorePrimitiveField(field: reflect.InstanceField, realTarget: Any, srcVal: Any,
    key: string, onError?: CollectionCoderErrorCallback): void {
    if (srcVal === undefined) {
        return;
    }
    try {
        field.setValue(realTarget as Object, srcVal);
    } catch (e) {
        const tgtVal = field.getValue(realTarget as Object) as Any;
        const coerced = coercePrimitive(srcVal, tgtVal, key, onError);
        if (coerced !== undefined) {
            field.setValue(realTarget as Object, coerced);
        }
    }
}

function restoreCircularRefField(field: reflect.InstanceField, realTarget: Any,
    srcVal: Any, tgtVal: Any, visitedSources: Map<Object, Object>): void {
    const mappedVal = visitedSources.get(srcVal as Object);
    if (srcVal instanceof Date && tgtVal !== undefined && tgtVal !== null && tgtVal instanceof Date) {
        (tgtVal as Date).setTime((mappedVal as Date).getTime());
    } else {
        field.setValue(realTarget as Object, mappedVal);
    }
}

function restoreDateField(field: reflect.InstanceField, realTarget: Any,
    srcVal: Any, tgtVal: Any): void {
    if (tgtVal !== undefined && tgtVal !== null && tgtVal instanceof Date) {
        (tgtVal as Date).setTime((srcVal as Date).getTime());
    } else {
        field.setValue(realTarget as Object, srcVal);
    }
}

function restoreNestedField(field: reflect.InstanceField, realTarget: Any,
    srcVal: Any, tgtVal: Any, classNameToCreator: Map<string, StorageDefaultCreator<object>> | undefined,
    visitedTargets: Set<Object>, visitedSources: Map<Object, Object>,
    onError?: CollectionCoderErrorCallback): void {
    if (tgtVal !== undefined && tgtVal !== null) {
        restoreObject(tgtVal, srcVal, classNameToCreator, visitedTargets, visitedSources, onError);
        return;
    }
    const className = getClassName(srcVal);
    if (className !== undefined && classNameToCreator !== undefined) {
        const creator = classNameToCreator.get(className);
        if (creator !== undefined) {
            const newInstance = creator();
            try {
                const actualName = Class.of(newInstance as Object).getName();
                if (isCreatorMismatch(actualName, className, onError)) {
                    return;
                }
            } catch (e) {}
            field.setValue(realTarget as Object, newInstance);
            restoreObject(newInstance, srcVal, classNameToCreator, visitedTargets, visitedSources, onError);
            return;
        }
    }
    field.setValue(realTarget as Object, srcVal);
}

function restoreField(field: reflect.InstanceField, realTarget: Any, source: Any,
    classNameToCreator: Map<string, StorageDefaultCreator<object>> | undefined,
    visitedTargets: Set<Object>, visitedSources: Map<Object, Object>,
    onError?: CollectionCoderErrorCallback): void {
    const key: string = field.getName();
    const srcVal: Any = (source as Record<string, Any>)[key];
    const tgtVal: Any = field.getValue(realTarget as Object) as Any;

    if (typeof srcVal !== 'object' || srcVal === null) {
        restorePrimitiveField(field, realTarget, srcVal, key, onError);
        return;
    }

    if (visitedSources.has(srcVal as Object)) {
        restoreCircularRefField(field, realTarget, srcVal, tgtVal, visitedSources);
        return;
    }

    if (srcVal instanceof Date) {
        restoreDateField(field, realTarget, srcVal, tgtVal);
        return;
    }

    if ((srcVal instanceof Map && !(srcVal instanceof Record)) || srcVal instanceof Set || Array.isArray(srcVal)) {
        if (tgtVal !== undefined && tgtVal !== null) {
            restoreObject(tgtVal, srcVal, classNameToCreator, visitedTargets, visitedSources, onError);
        } else {
            field.setValue(realTarget as Object, srcVal);
        }
        return;
    }

    restoreNestedField(field, realTarget, srcVal, tgtVal, classNameToCreator, visitedTargets, visitedSources, onError);
}

function restorePlainObject(target: Any, source: Any, classNameToCreator: Map<string, StorageDefaultCreator<object>> | undefined,
    visitedTargets: Set<Object>, visitedSources: Map<Object, Object>,
    onError?: CollectionCoderErrorCallback): void {
    let realTarget: Any = target;
    try {
        const unwrapped = StateMgmtTool.tryGetTarget(target as Object);
        if (unwrapped !== undefined && unwrapped !== null) {
            realTarget = unwrapped as Any;
        }
    } catch (e) {}

    reflect.getInstanceFieldsRecursive(Class.of(realTarget as Object)).forEach((field: reflect.InstanceField) => {
        restoreField(field, realTarget, source, classNameToCreator, visitedTargets, visitedSources, onError);
    });
}

function restoreObject(target: Any, source: Any,
    classNameToCreator: Map<string, StorageDefaultCreator<object>> | undefined,
    visitedTargets: Set<Object>, visitedSources: Map<Object, Object>,
    onError?: CollectionCoderErrorCallback): void {
    if (target === null || target === undefined) {
        return;
    }
    if (source === null || source === undefined) {
        return;
    }
    if (visitedTargets.has(target as Object)) {
        return;
    }
    visitedTargets.add(target as Object);

    if (typeof source === 'object' && !visitedSources.has(source as Object)) {
        visitedSources.set(source as Object, target as Object);
    }

    if (source instanceof Date) {
        if (target instanceof Date) {
            (target as Date).setTime((source as Date).getTime());
        }
        return;
    }

    if (Array.isArray(source)) {
        restoreArray(target, source, classNameToCreator, visitedTargets, visitedSources, onError);
        return;
    }

    if (source instanceof Map && !(source instanceof Record)) {
        restoreMap(target, source, classNameToCreator, visitedTargets, visitedSources, onError);
        return;
    }

    if (source instanceof Set) {
        restoreSet(target, source, classNameToCreator, visitedTargets, visitedSources, onError);
        return;
    }

    if (typeof source === 'object') {
        restorePlainObject(target, source, classNameToCreator, visitedTargets, visitedSources, onError);
    }
}

export class V2CollectionCoder {

    public static stringify<T>(value: T, onError?: CollectionCoderErrorCallback): string {
        const visited = new Map<Object, string>();
        return '{"$":' + serializeValue(value, visited, onError) + '}';
    }

    public static parse(text: string): Any {
        const objects = new Map<string, Object>();
        const root = JSON.parseJsonElement(text);
        const rootValue = root.getElement('$');
        return readValue(rootValue, objects);
    }

    public static restoreTo<T extends object>(
        target: T, source: Any,
        classNameToCreator?: Map<string, StorageDefaultCreator<object>>,
        onError?: CollectionCoderErrorCallback
    ): T {
        const visitedTargets = new Set<Object>();
        const visitedSources = new Map<Object, Object>();
        restoreObject(target, source, classNameToCreator, visitedTargets, visitedSources, onError);
        return target;
    }

    public static isNewFormat(payload: string): boolean {
        return payload.startsWith('{"$":');
    }
}
