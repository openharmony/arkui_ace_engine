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

import { info } from "@ohos.hilog";

import {
  Fruits,
  Person,
  arr,
  numbers,
  man,
  myMap,
  jsonVal,
  calculator,
  globalVar,
  err,
  call,
  anonymousFunction,
  arrowFunction,
  Order,
  MethodCallTestClass,
  jsNull,
  jsUndefined,
  jsBoolean,
  jsNumber,
  jsBigint,
  jsString,
  jsSymbol,
  jsInst,
  funcReturnTypeNull,
  funcReturnTypeUndefined,
  funcReturnTypeBoolean,
  funcReturnTypeNumber,
  funcReturnTypeBigint,
  funcReturnTypeString,
  funcArgType,
  subtract,
  multiply,
  funcError,
  funcUserDefinedError,
  MyError
} from "@bundle:com.arkoala.app/entry/ets/jsFiles/pure";

function Log(msg: String) {
  info(0, "[LOG]", msg);
}

export function TestOperators(): void {
  Log('Panda Test[S2D]: ============ test operators return type begin ============');

  const newConstructor = new Fruits('apple', 10);
  if (newConstructor.kinds as string == "apple" && newConstructor.weight as number == 10) {
    Log('Panda Test[S2D]: Passed the test for funcNewConstructor!');
  } else {
    Log('Panda Test[S2D]: Failed the test for funcNewConstructor!');
  }

  const newClassInstance = new Person('Alice', 30);
  if (newClassInstance.name as string == "Alice" && newClassInstance.age as number == 30) {
    Log('Panda Test[S2D]: Passed the test for funcNewClassInstance!');
  } else {
    Log('Panda Test[S2D]: Failed the test for funcNewClassInstance!');
  }

  if (arr.length as number == 3) {
    Log('Panda Test[S2D]: Passed the test for funcNewBuiltIn!');
  } else {
    Log('Panda Test[S2D]: Failed the test for funcNewBuiltIn!');
  }

  if (numbers[0] as number == 10) {
    Log('Panda Test[S2D]: Passed the test for funcAccessArrElement!');
  } else {
    Log('Panda Test[S2D]: Failed the test for funcAccessArrElement!');
  }

//  if (man["name"] as string == "John") { compile error
//    Log('Panda Test[S2D]: Passed the test for funcAccessObjValByKey!');
//  } else {
//    Log('Panda Test[S2D]: Failed the test for funcAccessObjValByKey!');
//  }

//  if (myMap[name] as string == "Alice") { compile error
//    Log('Panda Test[S2D]: Passed the test for funcAccessMapValByKey!');
//  } else {
//    Log('Panda Test[S2D]: Failed the test for funcAccessMapValByKey!');
//  }

  let p = new Person('Doe', 30);
  if (p.name as string == "Doe") {
    Log('Panda Test[S2D]: Passed the test for funcAccessClassInstanceAttr!');
  } else {
    Log('Panda Test[S2D]: Failed the test for funcAccessClassInstanceAttr!');
  }

  if (jsonVal as number == 30) {
    Log('Panda Test[S2D]: Passed the test for funcAccessJsonValByKey!');
  } else {
    Log('Panda Test[S2D]: Failed the test for funcAccessJsonValByKey!');
  }
  
  if (calculator.add(1, 2) as number == 3) {
    Log('Panda Test[S2D]: Passed the test for funcObjMethod!');
  } else {
    Log('Panda Test[S2D]: Failed the test for funcObjMethod!');
  }

  let p1 = new Person('Doe', 30);
  if (p1.add(1, 2) as number == 3) {
    Log('Panda Test[S2D]: Passed the test for funcClassInstanceMethod!');
  } else {
    Log('Panda Test[S2D]: Failed the test for funcClassInstanceMethod!');
  }

  if (Person.staticProp as string == "static prop") {
    Log('Panda Test[S2D]: Passed the test for funcClassInstanceStaticProp!');
  } else {
    Log('Panda Test[S2D]: Failed the test for funcClassInstanceStaticProp!');
  }

  if (Person.staticMethod() as string == "static method") {
    Log('Panda Test[S2D]: Passed the test for funcClassInstanceStaticMethod!');
  } else {
    Log('Panda Test[S2D]: Failed the test for funcClassInstanceStaticMethod!');
  }

  if (globalVar as string == "global variable") {
    Log('Panda Test[S2D]: Passed the test for funcGlobalObjProp!');
  } else {
    Log('Panda Test[S2D]: Failed the test for funcGlobalObjProp!');
  }

  if (err.message as string == "Something went wrong!") {
    Log('Panda Test[S2D]: Passed the test for funcErrorProp!');
  } else {
    Log('Panda Test[S2D]: Failed the test for funcErrorProp!');
  }

  if (call() as string == "call") {
    Log('Panda Test[S2D]: Passed the test for funcCall!');
  } else {
    Log('Panda Test[S2D]: Failed the test for funcCall!');
  }

  if (p1.add(3, 3) as number == 6) {
    Log('Panda Test[S2D]: Passed the test for funcClassCall!');
  } else {
    Log('Panda Test[S2D]: Failed the test for funcClassCall!');
  }

  if (anonymousFunction() as string == "anonymous") {
    Log('Panda Test[S2D]: Passed the test for funcAnonymousCall!');
  } else {
    Log('Panda Test[S2D]: Failed the test for funcAnonymousCall!');
  }

  if (arrowFunction() as string == "arrow") {
    Log('Panda Test[S2D]: Passed the test for funcArrowCall!');
  } else {
    Log('Panda Test[S2D]: Failed the test for funcArrowCall!');
  }

  let order = new Order(101,10);
  if (order.id as number == 101) {
    Log('Panda Test[S2D]: Passed the test for funcConstructorCall!');
  } else {
    Log('Panda Test[S2D]: Failed the test for funcConstructorCall!');
  }
}

const PI: double = 3.14;

const jsonString: string = '{"name": "John", "age": 30, "city": "New York"}';

// export function TestNewConstructor(age: number) :void {
//   this.age = age;
// }

export class TestOperatorClass {
  name: string;
  arr: number[] = [1, 2, 3];
  // map: Map<string, number>;
  jsonStr: string = jsonString;
  static pi: double = PI;
  arrow = (): string => {
    return "arrow return";
  };
  constructor(name: string) {
    this.name = name
    // this.map = new Map();
    // this.map["aaa"] = 2;
  }
  myMethod(): number {
    return 10;
  }
  static getPI(): double {
    return PI;
  }
  // myAnonymous() {
  //   let a = function(arg) {
  //     return arg
  //   }
  //   return a;
  // }
}

enum Color {
  Green = 'green',
  Red = 'red'
}
const etsInt = 1;

export class ConversionsClass {
  name: string;
  stsNumber: number = 1;
  stsByte: byte = 1;
  stsShort: short = 0;
  stsInt: int = 0;
  stsLong: long = 0;
  stsFloat: float = 0.0;
  stsDouble: double = 0.0;
  stsChar: char = 3;
  stsBoolean: boolean = true;
  stsString: string = "hello";
  stsBigint: bigint = 10n;
  // stsEnum: enum = Color.Green;
  // stsLiteral: literal = etsInt;
  stsUndefined: undefined = undefined;
  stsNull: null = null;
  constructor(name: string) {
    this.name = name;
  };
}

export function ErrorFunc(): number {
  throw new Error('Panda: throw new error in sts!');
  // return 2;
}

export class CustomError extends Error {
  code: number;
  constructor(message: string, code: number) {
    super(message);
    this.name = "CustomError";
    this.code = code;
  }
}

export function CustomErrorFunc(): number {
  throw new CustomError("Panda: Something went wrong!", 1001);
  // return 3;
}

export function nullArgFunc(arg: null): null {
  return arg;
}
export function undefinedArgFunc(arg: undefined): undefined {
  return arg;
}
export function booleanArgFunc(arg: boolean): boolean {
  return arg;
}
export function numberArgFunc(arg: number): number {
  return arg;
}
export function bigintArgFunc(arg: bigint): bigint {
  return arg;
}
export function stringArgFunc(arg: string): string {
  return arg;
}
export function classInstArgFunc(arg: number): number {
  return arg;
}
export function numberRetValFunc(): number {
  return 1;
}
export function byteRetValFunc(): byte {
  return 1;
}
export function shortRetValFunc(): short {
  return 0;
}
export function intRetValFunc(): int {
  return 1;
}
export function longRetValFunc(): long {
  return 0;
}
export function floatRetValFunc(): float {
  return 0.0;
}
export function doubleRetValFunc(): double {
  return 0.0;
}
export function charRetValFunc(): char {
  return 3;
}
export function booleanRetValFunc(): boolean {
  return false;
}
export function stringRetValFunc(): string {
  return "hi";
}
export function bigintRetValFunc(): bigint {
  return 0n;
}
export function nullRetValFunc(): null {
  return null;
}
export function undefinedRetValFunc(): undefined {
  return undefined;
}

export class TestMyClass {
  name: string;
  constructor(name: string) {
    this.name = name;
  }
  nullArgMethod(arg: null): null {
    return arg;
  }
  undefinedArgMethod(arg: undefined): undefined {
    return arg;
  }
  booleanArgMethod(arg: boolean): boolean {
    return arg;
  }
  numberArgMethod(arg: number): number {
    return arg;
  }
  bigintArgMethod(arg: bigint): bigint {
    return arg;
  }
  stringArgMethod(arg: string): string {
    return arg;
  }
  classInstArgMethod(arg: number): number {
    return arg;
  }
  numberRetValMethod(): number {
    return 1;
  }
  byteRetValMethod(): byte {
    return 1;
  }
  shortRetValMethod(): short {
    return 0;
  }
  intRetValMethod(): int {
    return 1;
  }
  longRetValMethod(): long {
    return 0;
  }
  floatRetValMethod(): float {
    return 0.0;
  }
  doubleRetValMethod(): double {
    return 0.0;
  }
  charRetValMethod(): char {
    return 3;
  }
  booleanRetValMethod(): boolean {
    return false;
  }
  stringRetValMethod(): string {
    return "hi";
  }
  bigintRetValMethod(): bigint {
    return 0n;
  }
  // enumRetValMethod(): enum {
  //   return Color.Green;
  // }
  // literalRetValMethod(): literal {
  //   const etsInt = 1;
  //   return etsInt;
  // }
  nullRetValMethod(): null {
    return null;
  }
  undefinedRetValMethod(): undefined {
    return undefined;
  }
}

export function TestMethodCallReturnType(): void {
  Log('Panda Test[S2D]: ================== test method call return type begin ==================');
  let inst = new MethodCallTestClass();

  if (inst.nullRetValMethod() as null == null) {
    Log('Panda Test[S2D]: Passed the test for method call with return type null!');
  } else {
    Log('Panda Test[S2D]: Failed the test for method call with return type null!');
  }

  if (inst.undefinedRetValMethod() as undefined == undefined) {
    Log('Panda Test[S2D]: Passed the test for method call with return type undefined!');
  } else {
    Log('Panda Test[S2D]: Failed the test for method call with return type undefined!');
  }

  if (inst.booleanRetValMethod() as boolean == true) {
    Log('Panda Test[S2D]: Passed the test for method call with return type boolean!');
  } else {
    Log('Panda Test[S2D]: Failed the test for method call with return type boolean!');
  }

  if (inst.numberRetValMethod() as number == 1) {
    Log('Panda Test[S2D]: Passed the test for method call with return type number!');
  } else {
    Log('Panda Test[S2D]: Failed the test for method call with return type number!');
  }

  if (inst.bigintRetValMethod() as bigint == 0n) {
    Log('Panda Test[S2D]: Passed the test for method call with return type bigint!');
  } else {
    Log('Panda Test[S2D]: Failed the test for method call with return type bigint!');
  }

  if (inst.stringRetValMethod() as string == "hi") {
    Log('Panda Test[S2D]: Passed the test for method call with return type string!');
  } else {
    Log('Panda Test[S2D]: Failed the test for method call with return type string!');
  }

  // if (inst.symbolRetValMethod() as ESObject == "id") { TODO
  //   Log('Panda Test[S2D]: Passed the test for method call with return type symbol!');
  // } else {
  //   Log('Panda Test[S2D]: Failed the test for method call with return type symbol!');
  // }

  // compile error -> cannot find type 'ESObject'
  // let jsInst: ESObject = inst.classInstRetValMethod() as ESObject;
  // if (jsInst.num as number == 123) {
  //   Log('Panda Test[S2D]: Passed the test for method call with return type class instance!');
  // } else {
  //   Log('Panda Test[S2D]: Failed the test for method call with return type class instance!');
  // }

  // let obj: ESObject = inst.objRetValMethod() as ESObject;
  // if (obj.a as string == '123') {
  //   Log('Panda Test[S2D]: Passed the test for method call with return type array!');
  // } else {
  //   Log('Panda Test[S2D]: Failed the test for method call with return type array!');
  // }

  // let arr: ESObject = inst.funcReturnTypeArr() as ESObject;
  // if (arr[0] as number == 1) {
  //   Log('Panda Test[S2D]: Passed the test for method call with return type array!');
  // } else {
  //   Log('Panda Test[S2D]: Failed the test for method call with return type array!');
  // }
}

export function TestMethodCallArg(): void {
  Log('Panda Test[S2D]: ================== test method call arg type begin ==================');
  let inst = new MethodCallTestClass();

  let arg0: number = 1;
  if (inst.argTypeMethod(arg0) as number == 1) {
    Log('Panda Test[S2D]: Passed the test for method call with parameter type number!');
  } else {
    Log('Panda Test[S2D]: Failed the test for method call with parameter type number!');
  }

  let arg1: byte = 1;
  if (inst.argTypeMethod(arg1) as byte == 1) {
    Log('Panda Test[S2D]: Passed the test for method call with parameter type byte!');
  } else {
    Log('Panda Test[S2D]: Failed the test for method call with parameter type byte!');
  }

  let arg2: short = 0;
  if (inst.argTypeMethod(arg2) as short == 0) {
    Log('Panda Test[S2D]: Passed the test for method call with parameter type short!');
  } else {
    Log('Panda Test[S2D]: Failed the test for method call with parameter type short!');
  }

  let arg3: int = 1;
  if (inst.argTypeMethod(arg3) as int == 1) {
    Log('Panda Test[S2D]: Passed the test for method call with parameter type int!');
  } else {
    Log('Panda Test[S2D]: Failed the test for method call with parameter type int!');
  }

  let arg4: long = 0;
  if (inst.argTypeMethod(arg4) as long == 0) {
    Log('Panda Test[S2D]: Passed the test for method call with parameter type long!');
  } else {
    Log('Panda Test[S2D]: Failed the test for method call with parameter type long!');
  }

  let arg5: float = 0.0;
  if (inst.argTypeMethod(arg5) as float == 0.0) {
    Log('Panda Test[S2D]: Passed the test for method call with parameter type float!');
  } else {
    Log('Panda Test[S2D]: Failed the test for method call with parameter type float!');
  }

  let arg6: double = 0.0;
  if (inst.argTypeMethod(arg6) as double == 0.0) {
    Log('Panda Test[S2D]: Passed the test for method call with parameter type double!');
  } else {
    Log('Panda Test[S2D]: Failed the test for method call with parameter type double!');
  }

  let arg7: char = 3;
  if (inst.argTypeMethod(arg7) as char == 3) {
    Log('Panda Test[S2D]: Passed the test for method call with parameter type char!');
  } else {
    Log('Panda Test[S2D]: Failed the test for method call with parameter type char!');
  }

  let arg8: boolean = true;
  if (inst.argTypeMethod(arg8) as boolean == true) {
    Log('Panda Test[S2D]: Passed the test for method call with parameter type boolean!');
  } else {
    Log('Panda Test[S2D]: Failed the test for method call with parameter type boolean!');
  }

  let arg9: string = "hello";
  if (inst.argTypeMethod(arg9) as string == "hello") {
    Log('Panda Test[S2D]: Passed the test for method call with parameter type string!');
  } else {
    Log('Panda Test[S2D]: Failed the test for method call with parameter type string!');
  }

  let arg10: bigint = 0n;
  if (inst.argTypeMethod(arg10) as bigint == 0n) {
    Log('Panda Test[S2D]: Passed the test for method call with parameter type bigint!');
  } else {
    Log('Panda Test[S2D]: Failed the test for method call with parameter type bigint!');
  }

  // enum Color { runtime error
  //   Green = 'green',
  //   Red = 'red'
  // }
  // if (inst.argTypeMethod(Color.Green) as string == "green") {
  //   Log('Panda Test[S2D]: Passed the test for method call with parameter type enum!');
  // } else {
  //   Log('Panda Test[S2D]: Failed the test for method call with parameter type enum!');
  // }

  // const etsInt = 1; compile error -> cannot find type 'literal'
  // let arg12: literal = etsInt;
  // if (inst.argTypeMethod(arg12) as literal == etsInt) {
  //   Log('Panda Test[S2D]: Passed the test for method call with parameter type literal!');
  // } else {
  //   Log('Panda Test[S2D]: Failed the test for method call with parameter type literal!');
  // }

  let arg13: undefined = undefined;
  if (inst.argTypeMethod(arg13) as undefined == undefined) {
    Log('Panda Test[S2D]: Passed the test for method call with parameter type undefined!');
  } else {
    Log('Panda Test[S2D]: Failed the test for method call with parameter type undefined!');
  }

  let arg14: null = null;
  if (inst.argTypeMethod(arg14) as null == null) {
    Log('Panda Test[S2D]: Passed the test for method call with parameter type null!');
  } else {
    Log('Panda Test[S2D]: Failed the test for method call with parameter type null!');
  }
}

export function TestConversion(): void {
  Log('Panda Test[S2D]: ================== test conversion begin ==================');

  // test-conversions-null compile error
  // let stsNull: null = jsNull;
  // if (typeof stsNull == 'object') { // null?
  //   Log('Panda Test[S2D]: Passed the test to convert jsNull to stsNull!');
  // } else {
  //   Log('Panda Test[S2D]: Failed the test to convert jsNull to stsNull!');
  // }

  // test-conversions-undefined compile error
  // let stsUndefined: undefined = jsUndefined;
  // if (typeof stsUndefined == 'undefined') {
  //   Log('Panda Test[S2D]: Passed the test to convert jsUndefined to stsUndefined!');
  // } else {
  //   Log('Panda Test[S2D]: Failed the test to convert jsUndefined to stsUndefined!');
  // }

  // test-conversions-boolean
  let stsBoolean: boolean = jsBoolean;
  if (typeof stsBoolean == 'boolean') {
    Log('Panda Test[S2D]: Passed the test to convert jsBoolean to stsBoolean!');
  } else {
    Log('Panda Test[S2D]: Failed the test to convert jsBoolean to stsBoolean!');
  }

  // test-conversions-number
  let stsNumber: number = jsNumber;
  if (typeof stsNumber == 'number') {
    Log('Panda Test[S2D]: Passed the test to convert jsNumber to stsNumber!');
  } else {
    Log('Panda Test[S2D]: Failed the test to convert jsNumber to stsNumber!');
  }

  // test-conversions-bigint
  let stsBigint: bigint = jsBigint;
  if (typeof stsBigint == 'bigint') {
    Log('Panda Test[S2D]: Passed the test to convert jsBigint to stsBigint!');
  } else {
    Log('Panda Test[S2D]: Failed the test to convert jsBigint to stsBigint!');
  }

  // test-conversions-string
  let stsString: string = jsString;
  if (typeof stsString == 'string') {
    Log('Panda Test[S2D]: Passed the test to convert jsString to stsString!');
  } else {
    Log('Panda Test[S2D]: Failed the test to convert jsString to stsString!');
  }

  // test-conversions-symbol
  // let stsSymbol: ESObejct = jsSymbol; TODO
  // if (typeof stsSymbol == 'ESObejct') {
  //   Log('Panda Test[S2D]: Passed the test to convert jsSymbol to stsSymbol!');
  // } else {
  //   Log('Panda Test[S2D]: Failed the test to convert jsSymbol to stsSymbol!');
  // }

  // test-conversions: a.v
  try {
    let stsNum = jsInst.num;
    Log('Panda Test[S2D]: Get num from js class instance: expected 123 actually ' + stsNum);
  } catch(e) {
    Log('Panda Test[S2D]: Get num from js class instance throw error');
  }
  // test-conversions: a[index]
  try {
    jsInst[0];
    Log('Panda Test[S2D]: jsInst[0] expected RT error actually no error');
  } catch(e) {
    Log('Panda Test[S2D]: jsInst[0] expected RT error actually throw error');
  }
  // test-conversions: a()
  try {
    jsInst();
    Log('Panda Test[S2D]: jsInst() expected RT error actually no error');
  } catch(e) {
    Log('Panda Test[S2D]: jsInst() expected RT error actually throw error');
  }
  // test-conversions: new a()
  try {
    new jsInst();
    Log('Panda Test[S2D]: new jsInst() expected no error actually no error');
  } catch(e) {
    Log('Panda Test[S2D]: new jsInst() expected no error actually throw error');
  }
}

export function TestFuncCallReturnType(): void {
  Log('Panda Test[S2D]: ================== test function call return type begin ==================');
  if (funcReturnTypeNull() as null == null) {
    Log('Panda Test[S2D]: Passed the test for function call with return type null!');
  } else {
    Log('Panda Test[S2D]: Failed the test for function call with return type null!');
  }

  if (funcReturnTypeUndefined() as undefined == undefined) {
    Log('Panda Test[S2D]: Passed the test for function call with return type undefined!');
  } else {
    Log('Panda Test[S2D]: Failed the test for function call with return type undefined!');
  }

  if (funcReturnTypeBoolean() as boolean == true) {
    Log('Panda Test[S2D]: Passed the test for function call with return type boolean!');
  } else {
    Log('Panda Test[S2D]: Failed the test for function call with return type boolean!');
  }

  if (funcReturnTypeNumber() as number == 1) {
    Log('Panda Test[S2D]: Passed the test for function call with return type number!');
  } else {
    Log('Panda Test[S2D]: Failed the test for function call with return type number!');
  }

  if (funcReturnTypeBigint() as bigint == 0n) {
    Log('Panda Test[S2D]: Passed the test for function call with return type bigint!');
  } else {
    Log('Panda Test[S2D]: Failed the test for function call with return type bigint!');
  }

  if (funcReturnTypeString() as string == "hello") {
    Log('Panda Test[S2D]: Passed the test for function call with return type string!');
  } else {
    Log('Panda Test[S2D]: Failed the test for function call with return type string!');
  }

  // if (funcReturnTypeSymbol() as ESObject == "hello") { TODO
  //   Log('Panda Test[S2D]: Passed the test for function call with return type symbol!');
  // } else {
  //   Log('Panda Test[S2D]: Failed the test for function call with return type symbol!');
  // }

  // compile error -> cannot find type 'ESObject'
  // let inst: ESObject = funcReturnTypeClassInst() as ESObject;
  // if (inst.num as number == 123) {
  //   Log('Panda Test[S2D]: Passed the test for function call with return type class instance!');
  // } else {
  //   Log('Panda Test[S2D]: Failed the test for function call with return type class instance!');
  // }

  // let arr: ESObject = funcReturnTypeArr() as ESObject;
  // if (arr[0] as number == 1) {
  //   Log('Panda Test[S2D]: Passed the test for function call with return type array!');
  // } else {
  //   Log('Panda Test[S2D]: Failed the test for function call with return type array!');
  // }
}

export function TestFuncCallArg(): void {
  Log('Panda Test[S2D]: ================== test function call arg type begin ==================');
  let arg0: number = 1;
  if (funcArgType(arg0) as number == 1) {
    Log('Panda Test[S2D]: Passed the test for function call with parameter type number!');
  } else {
    Log('Panda Test[S2D]: Failed the test for function call with parameter type number!');
  }

  let arg1: byte = 1;
  if (funcArgType(arg1) as byte == 1) {
    Log('Panda Test[S2D]: Passed the test for function call with parameter type byte!');
  } else {
    Log('Panda Test[S2D]: Failed the test for function call with parameter type byte!');
  }

  let arg2: short = 0;
  if (funcArgType(arg2) as short == 0) {
    Log('Panda Test[S2D]: Passed the test for function call with parameter type short!');
  } else {
    Log('Panda Test[S2D]: Failed the test for function call with parameter type short!');
  }

  let arg3: int = 1;
  if (funcArgType(arg3) as int == 1) {
    Log('Panda Test[S2D]: Passed the test for function call with parameter type int!');
  } else {
    Log('Panda Test[S2D]: Failed the test for function call with parameter type int!');
  }

  let arg4: long = 0;
  if (funcArgType(arg4) as long == 0) {
    Log('Panda Test[S2D]: Passed the test for function call with parameter type long!');
  } else {
    Log('Panda Test[S2D]: Failed the test for function call with parameter type long!');
  }

  let arg5: float = 0.0;
  if (funcArgType(arg5) as float == 0.0) {
    Log('Panda Test[S2D]: Passed the test for function call with parameter type float!');
  } else {
    Log('Panda Test[S2D]: Failed the test for function call with parameter type float!');
  }

  let arg6: double = 0.0;
  if (funcArgType(arg6) as double == 0.0) {
    Log('Panda Test[S2D]: Passed the test for function call with parameter type double!');
  } else {
    Log('Panda Test[S2D]: Failed the test for function call with parameter type double!');
  }

  let arg7: char = 3;
  if (funcArgType(arg7) as char == 3) {
    Log('Panda Test[S2D]: Passed the test for function call with parameter type char!');
  } else {
    Log('Panda Test[S2D]: Failed the test for function call with parameter type char!');
  }

  let arg8: boolean = true;
  if (funcArgType(arg8) as boolean == true) {
    Log('Panda Test[S2D]: Passed the test for function call with parameter type boolean!');
  } else {
    Log('Panda Test[S2D]: Failed the test for function call with parameter type boolean!');
  }

  let arg9: string = "hello";
  if (funcArgType(arg9) as string == "hello") {
    Log('Panda Test[S2D]: Passed the test for function call with parameter type string!');
  } else {
    Log('Panda Test[S2D]: Failed the test for function call with parameter type string!');
  }

  let arg10: bigint = 0n;
  if (funcArgType(arg10) as bigint == 0n) {
    Log('Panda Test[S2D]: Passed the test for function call with parameter type bigint!');
  } else {
    Log('Panda Test[S2D]: Failed the test for function call with parameter type bigint!');
  }

  // enum Color { runtime error
  //   Green = 'green',
  //   Red = 'red'
  // }
  // if (funcArgType(Color.Green) as string == "green") {
  //   Log('Panda Test[S2D]: Passed the test for function call with parameter type enum!');
  // } else {
  //   Log('Panda Test[S2D]: Failed the test for function call with parameter type enum!');
  // }

  // const etsInt = 1; compile error -> cannot find type 'literal'
  // let arg12: literal = etsInt;
  // if (funcArgType(arg12) as literal == etsInt) {
  //   Log('Panda Test[S2D]: Passed the test for function call with parameter type literal!');
  // } else {
  //   Log('Panda Test[S2D]: Failed the test for function call with parameter type literal!');
  // }

  let arg13: undefined = undefined;
  if (funcArgType(arg13) as undefined == undefined) {
    Log('Panda Test[S2D]: Passed the test for function call with parameter type undefined!');
  } else {
    Log('Panda Test[S2D]: Failed the test for function call with parameter type undefined!');
  }

  let arg14: null = null;
  if (funcArgType(arg14) as null == null) {
    Log('Panda Test[S2D]: Passed the test for function call with parameter type null!');
  } else {
    Log('Panda Test[S2D]: Failed the test for function call with parameter type null!');
  }
}

export function TestImportStatements(): void {
    Log('Panda Test[S2D]: ============ test import statements return type begin ============');

    try {
        const result = subtract(9, 1);
        if (result as number == 8) {
            Log('Panda Test[S2D]: Passed the test for funcImportAll!');
        } else {
            Log('Panda Test[S2D]: Failed the test for funcImportAll!');
        }
    } catch (error) {
        Log(`Panda Test[S2D]: Failed the test for funcImportAll with error`);
    }

    try {
        const result = multiply(3, 3);
        if (result as number == 9) {
            Log('Panda Test[S2D]: Passed the test for funcImport!');
        } else {
            Log('Panda Test[S2D]: Failed the test for funcImport!');
        }
    } catch (error) {
        Log(`Panda Test[S2D]: Failed the test for funcImport with error`);
    }
}

export function TestSimpleException(): void {
    Log('Panda Test[S2D]: ============ test simple exception return type begin ============');

    try {
        funcError();
        Log('Panda Test[S2D]: Failed the test for funcError! It did not throw an error.');
    } catch (error) {
        Log('Panda Test[S2D]: Passed the test for funcError!');
    }

    try {
        funcUserDefinedError();
        Log('Panda Test[S2D]: Failed the test for funcUserDefinedError! It did not throw an error.');
    } catch (MyError) {
        Log('Panda Test[S2D]: Passed the test for funcUserDefinedError!');
    }
}