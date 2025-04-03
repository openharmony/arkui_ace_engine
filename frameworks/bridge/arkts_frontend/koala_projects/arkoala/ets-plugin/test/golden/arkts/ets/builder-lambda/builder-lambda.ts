import { ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent } from "@koalaui/arkts-arkui";
/* TODO: not yet implemented in the plugin */
// @AnimatableExtend
class FooAttribute {
    bar(): this {
        console.log("bar");
        return this;
    }
    qux(): this {
        console.log("qux");
        return this;
    }
}
@BuilderLambda("_Foo")
declare function Foo(arg1: string): FooAttribute;
function _Foo(builder: (instance) => FooAttribute, arg1: string): void {
    builder(new FooAttribute());
}
_Foo(__instance => {
    __instance.bar()
        .qux();
}, "label");
