
import { __memo_context_type as __memo_context_type, __memo_id_type as __memo_id_type, __hash as __hash } from "@koalaui/runtime";

import { memo as memo, memo_stable as memo_stable, memo_intrinsic as memo_intrinsic, memo_entry as memo_entry } from "@koalaui/runtime/annotations";

import { __context as __context, __id as __id, __key as __key } from "@koalaui/runtime";

function main(): void {}


@memo() function param_capturing(__memo_context: __memo_context_type, __memo_id: __memo_id_type, s: string): void {
  const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_param_capturing_@test.test.ets"))), 1);
  const __memo_parameter_s = __memo_scope.param(0, s);
  if (__memo_scope.unchanged) {
    __memo_scope.cached;
  return;
  }
  let x = ((): void => {
    console.log(__memo_parameter_s.value);
  });
  x();
  let y = ((s: string): void => {
    console.log(s);
  });
  y("she");
  {
    __memo_scope.recache();
    return;
  }
}

@memo() @functions.OptionalParametersAnnotation({minArgCount:3}) function memo_arg_call(__memo_context: __memo_context_type, __memo_id: __memo_id_type, arg1: number, arg2: ((x: number)=> number), @memo() arg3: ((__memo_context: __memo_context_type, __memo_id: __memo_id_type, x: number)=> number), arg4?: ((x: number)=> number), @memo() arg5?: ((__memo_context: __memo_context_type, __memo_id: __memo_id_type, x: number)=> number)): void {
  const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_memo_arg_call_@test.test.ets"))), 5);
  const __memo_parameter_arg1 = __memo_scope.param(0, arg1), __memo_parameter_arg2 = __memo_scope.param(1, arg2), __memo_parameter_arg3 = __memo_scope.param(2, arg3), __memo_parameter_arg4 = __memo_scope.param(3, arg4), __memo_parameter_arg5 = __memo_scope.param(4, arg5);
  if (__memo_scope.unchanged) {
    __memo_scope.cached;
  return;
  }
  __memo_parameter_arg2.value(__memo_parameter_arg1.value);
  __memo_parameter_arg3.value(__memo_context, ((__memo_id) + (__hash("id_arg3_@test.test.ets"))), __memo_parameter_arg1.value);
  ({let gensym%%_265 = __memo_parameter_arg4.value;
  (((gensym%%_265) == (null)) ? undefined : gensym%%_265(__memo_parameter_arg1.value))});
  ({let gensym%%_266 = __memo_parameter_arg5.value;
  (((gensym%%_266) == (null)) ? undefined : gensym%%_266(__memo_context, ((__memo_id) + (__hash("id_arg5_@test.test.ets"))), __memo_parameter_arg1.value))});
  {
    __memo_scope.recache();
    return;
  }
}


type MemoType = @memo() ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void);

@memo() type AnotherMemoType = ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void);

@memo() type OneMoreMemoType = @memo() ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void);

class A {
  public x: int;
  
  public y: int;
  
  public constructor() {}
  
}

class Test {
  @memo() public void_method(__memo_context: __memo_context_type, __memo_id: __memo_id_type): void {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_void_method_@test.test.ets"))), 1);
    const __memo_parameter_this = __memo_scope.param(0, (this));
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
    return;
    }
    {
      __memo_scope.recache();
      return;
    }
  }
  
  @memo() public a_method_with_implicit_return_type(__memo_context: __memo_context_type, __memo_id: __memo_id_type): void {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_a_method_with_implicit_return_type_@test.test.ets"))), 1);
    const __memo_parameter_this = __memo_scope.param(0, (this));
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
    return;
    }
    {
      __memo_scope.recache();
      return;
    }
  }
  
  @memo() public void_method_with_arg(__memo_context: __memo_context_type, __memo_id: __memo_id_type, arg: string): void {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_void_method_with_arg_@test.test.ets"))), 2);
    const __memo_parameter_this = __memo_scope.param(0, (this)), __memo_parameter_arg = __memo_scope.param(1, arg);
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
    return;
    }
    {
      __memo_scope.recache();
      return;
    }
  }
  
  @memo() public void_method_with_return(__memo_context: __memo_context_type, __memo_id: __memo_id_type, arg: string): void {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_void_method_with_return_@test.test.ets"))), 2);
    const __memo_parameter_this = __memo_scope.param(0, (this)), __memo_parameter_arg = __memo_scope.param(1, arg);
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
    return;
    }
    {
      __memo_scope.recache();
      return;
    }
  }
  
  @memo() public string_method_with_return(__memo_context: __memo_context_type, __memo_id: __memo_id_type, arg: string): string {
    const __memo_scope = __memo_context.scope<string>(((__memo_id) + (__hash("id_string_method_with_return_@test.test.ets"))), 2);
    const __memo_parameter_this = __memo_scope.param(0, (this)), __memo_parameter_arg = __memo_scope.param(1, arg);
    if (__memo_scope.unchanged) {
      return __memo_scope.cached;
    }
    return __memo_scope.recache(__memo_parameter_arg.value);
  }
  
  @memo() public method_with_type_parameter<T>(__memo_context: __memo_context_type, __memo_id: __memo_id_type, arg: T): T {
    const __memo_scope = __memo_context.scope<T>(((__memo_id) + (__hash("id_method_with_type_parameter_@test.test.ets"))), 2);
    const __memo_parameter_this = __memo_scope.param(0, (this)), __memo_parameter_arg = __memo_scope.param(1, arg);
    if (__memo_scope.unchanged) {
      return __memo_scope.cached;
    }
    return __memo_scope.recache(__memo_parameter_arg.value);
  }
  
  @memo() public static static_method_with_type_parameter<T>(__memo_context: __memo_context_type, __memo_id: __memo_id_type, arg: T): void {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_static_method_with_type_parameter_@test.test.ets"))), 1);
    const __memo_parameter_arg = __memo_scope.param(0, arg);
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
    return;
    }
    {
      __memo_scope.recache();
      return;
    }
  }
  
  @memo() public internal_call(__memo_context: __memo_context_type, __memo_id: __memo_id_type): void {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_internal_call_@test.test.ets"))), 1);
    const __memo_parameter_this = __memo_scope.param(0, (this));
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
    return;
    }
    __memo_parameter_this.value.void_method(__memo_context, ((__memo_id) + (__hash("id_void_method_@test.test.ets"))));
    {
      __memo_scope.recache();
      return;
    }
  }
  
  @memo() public lambda_arg(__memo_context: __memo_context_type, __memo_id: __memo_id_type, @memo() arg: ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void)): void {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_lambda_arg_@test.test.ets"))), 2);
    const __memo_parameter_this = __memo_scope.param(0, (this)), __memo_parameter_arg = __memo_scope.param(1, arg);
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
    return;
    }
    {
      __memo_scope.recache();
      return;
    }
  }
  
  @memo() public lambda_arg_with_arg(__memo_context: __memo_context_type, __memo_id: __memo_id_type, @memo() arg: ((__memo_context: __memo_context_type, __memo_id: __memo_id_type, value: string)=> string)): void {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_lambda_arg_with_arg_@test.test.ets"))), 2);
    const __memo_parameter_this = __memo_scope.param(0, (this)), __memo_parameter_arg = __memo_scope.param(1, arg);
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
    return;
    }
    {
      __memo_scope.recache();
      return;
    }
  }
  
  @memo_intrinsic() public intrinsic_method(__memo_context: __memo_context_type, __memo_id: __memo_id_type): int {
    return 0;
  }
  
  @memo_intrinsic() public intrinsic_method_with_this(__memo_context: __memo_context_type, __memo_id: __memo_id_type): int {
    (this).void_method(__memo_context, ((__memo_id) + (__hash("id_void_method_@test.test.ets"))));
    return 0;
  }
  
  @memo() public method_with_internals(__memo_context: __memo_context_type, __memo_id: __memo_id_type): void {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_method_with_internals_@test.test.ets"))), 1);
    const __memo_parameter_this = __memo_scope.param(0, (this));
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
    return;
    }
    __memo_context;
    __memo_id;
    {
      __memo_scope.recache();
      return;
    }
  }
  
  @memo() public obj_arg(__memo_context: __memo_context_type, __memo_id: __memo_id_type, arg: A): void {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_obj_arg_@test.test.ets"))), 2);
    const __memo_parameter_this = __memo_scope.param(0, (this)), __memo_parameter_arg = __memo_scope.param(1, arg);
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
    return;
    }
    {
      __memo_scope.recache();
      return;
    }
  }
  
  @memo_entry() public memoEntry<R>(__memo_context: __memo_context_type, __memo_id: __memo_id_type, @memo() entry: ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> R)): R {
    const getContext = (() => {
      return __memo_context;
    });
    const getId = (() => {
      return __memo_id;
    });
    {
      const __memo_context = getContext();
      const __memo_id = getId();
      return entry(__memo_context, ((__memo_id) + (__hash("id_entry_@test.test.ets"))));
    }
  }
  
  @memo() public memo_content(__memo_context: __memo_context_type, __memo_id: __memo_id_type, @memo() content: ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void)): void {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_memo_content_@test.test.ets"))), 1);
    const __memo_parameter_this = __memo_scope.param(0, (this));
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
    return;
    }
    content(__memo_context, ((__memo_id) + (__hash("id_content_@test.test.ets"))));
    {
      __memo_scope.recache();
      return;
    }
  }
  
  public memo_lambda(): void {
    @memo() ((__memo_context: __memo_context_type, __memo_id: __memo_id_type): void => {
      const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id__@test.test.ets"))), 0);
      if (__memo_scope.unchanged) {
        __memo_scope.cached;
      return;
      }
      {
        __memo_scope.recache();
        return;
      }
    });
  }
  
  @memo() public memo_variables(__memo_context: __memo_context_type, __memo_id: __memo_id_type): void {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_memo_variables_@test.test.ets"))), 1);
    const __memo_parameter_this = __memo_scope.param(0, (this));
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
    return;
    }
    @memo() const f = ((__memo_context: __memo_context_type, __memo_id: __memo_id_type): number => {
      const __memo_scope = __memo_context.scope<number>(((__memo_id) + (__hash("id__@test.test.ets"))), 0);
      if (__memo_scope.unchanged) {
        return __memo_scope.cached;
      }
      return __memo_scope.recache(123);
    }), g = ((__memo_context: __memo_context_type, __memo_id: __memo_id_type, x: number): number => {
      const __memo_scope = __memo_context.scope<number>(((__memo_id) + (__hash("id__@test.test.ets"))), 1);
      const __memo_parameter_x = __memo_scope.param(0, x);
      if (__memo_scope.unchanged) {
        return __memo_scope.cached;
      }
      return __memo_scope.recache(((123) + (__memo_parameter_x.value)));
    });
    const h = @memo() ((__memo_context: __memo_context_type, __memo_id: __memo_id_type): number => {
      const __memo_scope = __memo_context.scope<number>(((__memo_id) + (__hash("id__@test.test.ets"))), 0);
      if (__memo_scope.unchanged) {
        return __memo_scope.cached;
      }
      return __memo_scope.recache(1);
    });
    f(__memo_context, ((__memo_id) + (__hash("id_f_@test.test.ets"))));
    g(__memo_context, ((__memo_id) + (__hash("id_g_@test.test.ets"))), 1);
    h(__memo_context, ((__memo_id) + (__hash("id_h_@test.test.ets"))));
    {
      __memo_scope.recache();
      return;
    }
  }
  
  @memo() public compute_test(__memo_context: __memo_context_type, __memo_id: __memo_id_type, @memo() arg1: ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void) | undefined, arg2: (()=> void) | undefined, content: (()=> void) | undefined): void {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_compute_test_@test.test.ets"))), 3);
    const __memo_parameter_this = __memo_scope.param(0, (this)), __memo_parameter_arg1 = __memo_scope.param(1, arg1), __memo_parameter_arg2 = __memo_scope.param(2, arg2);
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
    return;
    }
    {
      __memo_scope.recache();
      return;
    }
  }
  
  @memo() @functions.OptionalParametersAnnotation({minArgCount:0}) public args_with_default_values(__memo_context: __memo_context_type, __memo_id: __memo_id_type, gensym%%_1?: int, gensym%%_2?: (()=> int), gensym%%_3?: int, arg4?: int): void {
    let arg1: int = (((gensym%%_1) !== (undefined)) ? gensym%%_1 : (10 as int));
    let arg2: (()=> int) = (((gensym%%_2) !== (undefined)) ? gensym%%_2 : ((() => {
      return 20;
    }) as (()=> int)));
    let arg3: int = (((gensym%%_3) !== (undefined)) ? gensym%%_3 : (arg1 as int));
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_args_with_default_values_@test.test.ets"))), 5);
    const __memo_parameter_this = __memo_scope.param(0, (this)), __memo_parameter_arg1 = __memo_scope.param(1, arg1), __memo_parameter_arg2 = __memo_scope.param(2, arg2), __memo_parameter_arg3 = __memo_scope.param(3, arg3), __memo_parameter_arg4 = __memo_scope.param(4, arg4);
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
    return;
    }
    console.log(__memo_parameter_arg1.value, __memo_parameter_arg2.value, __memo_parameter_arg3.value, __memo_parameter_arg4.value);
    console.log(__memo_parameter_arg2.value());
    {
      __memo_scope.recache();
      return;
    }
  }
  
  @memo() @functions.OptionalParametersAnnotation({minArgCount:0}) public optional_args(__memo_context: __memo_context_type, __memo_id: __memo_id_type, arg1?: int, arg2?: (()=> int)): void {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_optional_args_@test.test.ets"))), 3);
    const __memo_parameter_this = __memo_scope.param(0, (this)), __memo_parameter_arg1 = __memo_scope.param(1, arg1), __memo_parameter_arg2 = __memo_scope.param(2, arg2);
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
    return;
    }
    console.log(__memo_parameter_arg1.value);
    console.log(__memo_parameter_arg2.value);
    console.log(({let gensym%%_264 = __memo_parameter_arg2.value;
    (((gensym%%_264) == (null)) ? undefined : gensym%%_264())}));
    {
      __memo_scope.recache();
      return;
    }
  }
  
  @memo() public type_alias(__memo_context: __memo_context_type, __memo_id: __memo_id_type, arg: MemoType): void {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_type_alias_@test.test.ets"))), 2);
    const __memo_parameter_this = __memo_scope.param(0, (this)), __memo_parameter_arg = __memo_scope.param(1, arg);
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
    return;
    }
    __memo_parameter_arg.value(__memo_context, ((__memo_id) + (__hash("id_arg_@test.test.ets"))));
    {
      __memo_scope.recache();
      return;
    }
  }
  
  @memo_intrinsic() public static intrinsicKeyAccessor(__memo_context: __memo_context_type, __memo_id: __memo_id_type): void {
    let key = __hash("id___key_@test.test.ets");
  }
  
  public constructor() {}
  
}

declare class AbstractTest {
  public test_signature(@memo() arg1: ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void), @memo() arg2: ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void) | undefined, @memo() arg3: ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void) | undefined | ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> int) | undefined, @memo() x: ((__memo_context: __memo_context_type, __memo_id: __memo_id_type, y: ((z: @memo() ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void))=> void))=> void)): @memo() ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void)
  
  public constructor() {}
  
}

@memo_stable() class MemoStableClass {
  @memo() public test1(__memo_context: __memo_context_type, __memo_id: __memo_id_type, x: string): string {
    const __memo_scope = __memo_context.scope<string>(((__memo_id) + (__hash("id_test1_@test.test.ets"))), 1);
    const __memo_parameter_x = __memo_scope.param(0, x);
    if (__memo_scope.unchanged) {
      return __memo_scope.cached;
    }
    return __memo_scope.recache(__memo_parameter_x.value);
  }
  
  @memo() public test2(__memo_context: __memo_context_type, __memo_id: __memo_id_type, value: int): this {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_test2_@test.test.ets"))), 1);
    const __memo_parameter_value = __memo_scope.param(0, value);
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
    return (this);
    }
    console.log(__memo_parameter_value.value);
    {
      __memo_scope.recache();
      return (this);
    }
  }
  
  public constructor() {}
  
}

class MemoUnstableClass {
  @memo() public test2(__memo_context: __memo_context_type, __memo_id: __memo_id_type, value: int): this {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_test2_@test.test.ets"))), 2);
    const __memo_parameter_this = __memo_scope.param(0, (this)), __memo_parameter_value = __memo_scope.param(1, value);
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
    return (this);
    }
    __memo_parameter_this.value;
    
    console.log(__memo_parameter_value.value);
    {
      __memo_scope.recache();
      return (this);
    }
  }
  
  public constructor() {}
  
}

class Use {
  @memo() public test(__memo_context: __memo_context_type, __memo_id: __memo_id_type): void {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_test_@test.test.ets"))), 1);
    const __memo_parameter_this = __memo_scope.param(0, (this));
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
    return;
    }
    const test = new Test();
    test.void_method(__memo_context, ((__memo_id) + (__hash("id_void_method_@test.test.ets"))));
    test.void_method_with_arg(__memo_context, ((__memo_id) + (__hash("id_void_method_with_arg_@test.test.ets"))), "an arg");
    test.void_method_with_return(__memo_context, ((__memo_id) + (__hash("id_void_method_with_return_@test.test.ets"))), "a value");
    Test.static_method_with_type_parameter(__memo_context, ((__memo_id) + (__hash("id_static_method_with_type_parameter_@test.test.ets"))), "I'm static");
    test.string_method_with_return(__memo_context, ((__memo_id) + (__hash("id_string_method_with_return_@test.test.ets"))), "a string");
    test.method_with_type_parameter(__memo_context, ((__memo_id) + (__hash("id_method_with_type_parameter_@test.test.ets"))), "I'm string");
    test.lambda_arg(__memo_context, ((__memo_id) + (__hash("id_lambda_arg_@test.test.ets"))), __memo_context.compute(((__memo_id) + (__hash("id_lambda_arg_@test.test.ets"))), ((): ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void) => {
      return ((__memo_context: __memo_context_type, __memo_id: __memo_id_type): void => {
        const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id__@test.test.ets"))), 0);
        if (__memo_scope.unchanged) {
          __memo_scope.cached;
        return;
        }
        {
          __memo_scope.recache();
          return;
        }
      });
    })));
    test.lambda_arg_with_arg(__memo_context, ((__memo_id) + (__hash("id_lambda_arg_with_arg_@test.test.ets"))), __memo_context.compute(((__memo_id) + (__hash("id_lambda_arg_with_arg_@test.test.ets"))), ((): ((__memo_context: __memo_context_type, __memo_id: __memo_id_type, value: string)=> string) => {
      return ((__memo_context: __memo_context_type, __memo_id: __memo_id_type, value: string): string => {
        const __memo_scope = __memo_context.scope<string>(((__memo_id) + (__hash("id__@test.test.ets"))), 1);
        const __memo_parameter_value = __memo_scope.param(0, value);
        if (__memo_scope.unchanged) {
          return __memo_scope.cached;
        }
        return __memo_scope.recache(__memo_parameter_value.value);
      });
    })));
    test.obj_arg(__memo_context, ((__memo_id) + (__hash("id_obj_arg_@test.test.ets"))), __memo_context.compute(((__memo_id) + (__hash("id_obj_arg_@test.test.ets"))), ((): A => {
      return ({
        x: 1,
        y: 2,
      } as A);
    })));
    test.compute_test(__memo_context, ((__memo_id) + (__hash("id_compute_test_@test.test.ets"))), __memo_context.compute(((__memo_id) + (__hash("id_compute_test_@test.test.ets"))), ((): ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void) => {
      return ((__memo_context: __memo_context_type, __memo_id: __memo_id_type): void => {
        const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id__@test.test.ets"))), 0);
        if (__memo_scope.unchanged) {
          __memo_scope.cached;
        return;
        }
        {
          __memo_scope.recache();
          return;
        }
      });
    })), __memo_context.compute(((__memo_id) + (__hash("id_compute_test_@test.test.ets"))), ((): (()=> void) => {
      return ((): void => {});
    })), ((): void => {}));
    const MemoStableClass_instance = new MemoStableClass();
    MemoStableClass_instance.test1(__memo_context, ((__memo_id) + (__hash("id_test1_@test.test.ets"))), "a");
    MemoStableClass_instance.test2(__memo_context, ((__memo_id) + (__hash("id_test2_@test.test.ets"))), 5);
    {
      __memo_scope.recache();
      return;
    }
  }
  
  public constructor() {}
  
}

interface InterfaceWithSetter {
  @memo() set f(f: ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void))
  
}

interface InterfaceWithGetter {
  @memo() get f(): ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void)
  
}

