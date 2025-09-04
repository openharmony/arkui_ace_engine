/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { memo, memo_stable, memo_intrinsic, memo_entry, memo_wrap } from "@koalaui/runtime/annotations"
import { __context, __id, __key } from "@koalaui/runtime"

type MemoType = @memo () => void
@memo type AnotherMemoType = () => void
@memo type OneMoreMemoType = @memo () => void


@memo function param_capturing(s: string) {
    let x = () => {
        console.log(s)
    }
    x()
    let y = (s: string) => {
        console.log(s)
    }
    y("she")
}

@memo function memo_arg_call(
    arg1: number,
    arg2: (x: number) => number,
    @memo arg3: (x: number) => number,
    arg4?: (x: number) => number,
    @memo arg5?: (x: number) => number,
) {
	arg2(arg1)
	arg3(arg1)
	arg4?.(arg1)
	arg5?.(arg1)
}

@memo function call_with_receiver(obj: A, @memo v: (this: A) => int): int {
	const x = obj.v()
	const y = v(obj)
	return x + y
}

@memo function test_call_with_receiver() {
	const a = new A()
	const f = @memo (this: A): int => {
		return 11
	}
	call_with_receiver(a, f)
}
class A {
	x: int
	y: int
}

class Test {

	@memo void_method(): void {
	}

	@memo a_method_with_implicit_return_type() {
	}

	@memo void_method_with_arg(arg: string) {
	}

	@memo void_method_with_return(arg: string) {
	 	return
	}

	@memo string_method_with_return(arg: string): string {
	 	return arg
	}

	@memo method_with_type_parameter<T>(arg: T): T {
		return arg
	}

    @memo static static_method_with_type_parameter<T>(arg: T): void {
		return
	}

	@memo internal_call() {
		this.void_method()
	}

	@memo lambda_arg(@memo arg: () => void) {

	}

	@memo lambda_arg_with_arg(@memo arg: (value: string) => string) {

	}

	@memo_intrinsic intrinsic_method(): int {
		return 0
	}

	@memo_intrinsic intrinsic_method_with_this(): int {
		this.void_method()
		return 0
	}

	@memo method_with_internals() {
		__context()
		__id()
	}

	@memo obj_arg(arg: A) {

	}

	@memo_entry memoEntry<R>(__memo_context: __memo_context_type, __memo_id: __memo_id_type, @memo entry: () => R): R {
		const getContext = () => {
			return __context()
		}
		const getId = () => {
			return __id()
		}
		{
			const __memo_context = getContext()
			const __memo_id = getId()
			return entry()
		}
	}

	@memo memo_content(@memo content: () => void) {
		content()
	}

	memo_lambda() {
		@memo () => {

		}
	}

	@memo memo_variables() {
		@memo const f = (): number => {
			return 123
		}, g = (x: number): number => {
			return 123 + x
		}

		const h = @memo (): number => {
			return 1
		}

		f()
		g(1)
		h()
	}

	@memo compute_test(
		@memo arg1: (() => void) | undefined,
		arg2: (() => void) | undefined,
		content: (() => void) | undefined
	): void {

	}

	@memo args_with_default_values(
		arg1: int = 10,
		arg2: () => int = () => { return 20 },
		arg3: int = arg1,
		arg4?: int
	): void {
		console.log(arg1, arg2, arg3, arg4)
		console.log(arg2())
	}

	@memo optional_args(
		arg1?: int,
		arg2?: () => int
	) {
		console.log(arg1)
		console.log(arg2)
		console.log(arg2?.())
	}

	@memo type_alias(
		arg: MemoType
	) {
		arg()
	}

	@memo_intrinsic
    static intrinsicKeyAccessor(): void {
        let key = __key()
    }

	@memo wrap_param_test(
        @memo_wrap obj: A
    ): void {
    }
}

declare class AbstractTest {
	test_signature(
		@memo arg1: () => void,
		@memo arg2: (() => void) | undefined,
		@memo arg3: ((() => void) | undefined) | ((() => int) | undefined),
		@memo x: (y: (z: @memo () => void) => void) => void,
	): @memo () => void
}

@memo_stable
class MemoStableClass {
	// default memo method
	@memo
	test1(x: string): string {
		return x;
	}

	// memo method returns this
	@memo
    test2(value: int): this {
        console.log(value)
        return this
    }
}

class MemoUnstableClass {
	@memo
    test2(value: int): this {
        console.log(value)
        return this
    }
}

class Use {
    @memo test() {
		const test = new Test()

		test.void_method()
		test.void_method_with_arg("an arg")
		test.void_method_with_return("a value")
		Test.static_method_with_type_parameter("I'm static")

		test.string_method_with_return("a string")
		test.method_with_type_parameter("I'm string")

		test.lambda_arg((): void => {})
		test.lambda_arg_with_arg((value: string): string => value)

		test.obj_arg({ x: 1, y: 2 })
		test.compute_test((): void => {}, (): void => {}, (): void => {})

		const MemoStableClass_instance = new MemoStableClass()
		MemoStableClass_instance.test1("a")
		MemoStableClass_instance.test2(5)

        const obj: A = new A()
        test.wrap_param_test(obj)
	}
}

interface InterfaceWithSetter {
	@memo set f(f: () => void)
}

interface InterfaceWithGetter {
	@memo get f(): () => void
}
