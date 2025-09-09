
import { __memo_context_type as __memo_context_type, __memo_id_type as __memo_id_type, __hash as __hash } from "@koalaui/runtime";

import { memo as memo } from "@koalaui/runtime/annotations";

function main(): void {}



class Test {
  @memo() public memo_variables(__memo_context: __memo_context_type, __memo_id: __memo_id_type): void {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_memo_variables_@test/HQ/arrow-assignment.ets"))), 1);
    const __memo_parameter_this = __memo_scope.param(0, this);
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
      return;
    }
    @memo() const f = ((__memo_context: __memo_context_type, __memo_id: __memo_id_type): number => {
      const __memo_scope = __memo_context.scope<number>(((__memo_id) + (__hash("id__@test/HQ/arrow-assignment.ets"))), 0);
      if (__memo_scope.unchanged) {
        return __memo_scope.cached;
      }
      return __memo_scope.recache(123);
    }), g = ((__memo_context: __memo_context_type, __memo_id: __memo_id_type, x: number): number => {
      const __memo_scope = __memo_context.scope<number>(((__memo_id) + (__hash("id__@test/HQ/arrow-assignment.ets"))), 1);
      const __memo_parameter_x = __memo_scope.param(0, x);
      if (__memo_scope.unchanged) {
        return __memo_scope.cached;
      }
      return __memo_scope.recache(((123) + (__memo_parameter_x.value)));
    });
    const h = @memo() ((__memo_context: __memo_context_type, __memo_id: __memo_id_type): number => {
      const __memo_scope = __memo_context.scope<number>(((__memo_id) + (__hash("id__@test/HQ/arrow-assignment.ets"))), 0);
      if (__memo_scope.unchanged) {
        return __memo_scope.cached;
      }
      return __memo_scope.recache(1);
    });
    f(__memo_context, ((__memo_id) + (__hash("id_f_@test/HQ/arrow-assignment.ets"))));
    g(__memo_context, ((__memo_id) + (__hash("id_g_@test/HQ/arrow-assignment.ets"))), 1);
    h(__memo_context, ((__memo_id) + (__hash("id_h_@test/HQ/arrow-assignment.ets"))));
    {
      __memo_scope.recache();
      return;
    }
  }
  
  public constructor() {}
  
}

