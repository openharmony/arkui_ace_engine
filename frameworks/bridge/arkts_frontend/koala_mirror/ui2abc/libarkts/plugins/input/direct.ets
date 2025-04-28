import { __memo_context_type, __memo_id_type } from "@koalaui/runtime"

@Retention({policy: "SOURCE"})
@interface memo { }

class A {

}

class Memo {
    @memo static memo_method(): int {
        return 1
    }

    @memo static memo_call(): int {
        @memo const f = (): int => {
            return 2
        }
        return f()
    }
}
