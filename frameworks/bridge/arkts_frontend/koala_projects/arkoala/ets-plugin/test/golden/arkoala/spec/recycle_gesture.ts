import { ArkCommonMethodComponent, ArkFlex, ArkFlexComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, ArkTextComponent, FlexAlign, FlexDirection, GestureEvent, ItemAlign, LocalStorage, MutableState, observableProxy, stateOf } from "@koalaui/arkoala-arkui";
/** @memo:stable */
class ArkGestureTestComponent extends ArkStructBase<ArkGestureTestComponent, GestureTestOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: GestureTestOptions): void {
        this.__backing_count = stateOf<number>(initializers?.count ?? (0), this);
        this.__backing_width_value = stateOf<string>(initializers?.width_value ?? ("100%"), this);
    }
    private __backing_count?: MutableState<number>;
    private get count(): number {
        return this.__backing_count!.value;
    }
    private set count(value: number) {
        this.__backing_count!.value = observableProxy(value);
    }
    private __backing_width_value?: MutableState<string>;
    private get width_value(): string {
        return this.__backing_width_value!.value;
    }
    private set width_value(value: string) {
        this.__backing_width_value!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: GestureTestOptions) {
        ArkFlex(__instance => {
            {
                __instance.height(100).width(this.width_value).padding(60).border({ width: 1 }).margin(30)
                    .gesture(LongPressGesture({ repeat: true })
                    .onAction((event: GestureEvent) => {
                    if (event.repeat) {
                        this.count++;
                    }
                })
                    .onActionEnd(() => {
                    this.count = 0;
                }));
            }
            __builder?.(__instance);
        }, () => {
            ArkText((__instance: ArkTextComponent) => {
                __instance.height(100)
                    .width(this.width_value);
            }, undefined, 'LongPress onAction:' + this.count);
        }, { direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.SpaceBetween });
    }
}
export {};
/** @memo */
export function GestureTest(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: GestureTestOptions): void {
    const updatedInitializers: GestureTestOptions = {
        __backing_count: initializers?.__backing_count,
        __backing_width_value: initializers?.__backing_width_value
    };
    ArkGestureTestComponent._instantiate(style, () => new ArkGestureTestComponent, content, updatedInitializers);
}
export interface GestureTestOptions {
    __backing_count?: MutableState<number>;
    count?: number;
    __backing_width_value?: MutableState<string>;
    width_value?: string;
}
