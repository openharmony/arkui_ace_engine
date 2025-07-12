
import { __memo_context_type as __memo_context_type, __memo_id_type as __memo_id_type, __hash as __hash } from "@koalaui/runtime";

import { memo_intrinsic as memo_intrinsic } from "@koalaui/runtime/annotations";

function main(): void {}



class Test {
  @memo_intrinsic() public intrinsic_method(__memo_context: __memo_context_type, __memo_id: __memo_id_type): int {
    return 0;
  }
  
  public constructor() {}
  
}

